/*
 *      mem.cpp         logo memory management module           dvb 6/28/88
 *
 *       Copyright (C) 1995 by the Regents of the University of California
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef WX_PURE
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "logodata.h"
#include "error.h"
#include "status.h"
#include "debugheap.h"


// a segment is a pool of nodes that is allocated in a single malloc.
struct segment
{
    segment * next;
    NODE      nodes[SEG_SIZE];
};

// A NODE* that is cast to a form that is more convenient for storing an
// unused NODE* such that it is ready to be reused.
struct LIST_NODE
{
    // Pointer to the next item in the list.
    LIST_NODE * Next;

    // As many pointers as can fit into a NODE
    NODE * Nodes[3];
};

// Global Variables
int memory_count = 0;                  // Current amount of logo segments malloc'd

static NODE    *free_list    = NIL;    // global ptr to free node list
static segment *segment_list = NULL;   // global ptr to segment list

static long int mem_nodes = 0;
static long int mem_max = 0;

static NODE *reserve_tank;


#ifdef DEBUG

NODE * tracked_node = NIL;

void set_tracked_node(struct NODE * node)
{
    tracked_node = node;
}

void trace_node_change(struct NODE * Node)
{
    if (Node != NULL && Node == tracked_node)
    {
#ifndef WX_PURE
        DebugBreak();
#endif
    }
}

#endif // DEBUG

static
void push_to_free_list(NODE * node)
{
#ifdef MEM_DEBUG
    settype(node, NT_FREE);
#endif
    node->nunion.ncons.ncdr = free_list;
    free_list = node;
}

static
bool free_list_is_empty()
{
    return free_list == NIL;
}

static
NODE * pop_from_free_list()
{
    assert(!free_list_is_empty());

    NODE *newnd = free_list;
    free_list = free_list->nunion.ncons.ncdr;
#ifdef MEM_DEBUG
    assert(newnd->type == NT_FREE);
    memset(newnd, 0xDA, sizeof *newnd);
    newnd->type = NT_FREE;
#endif
    return newnd;
}

static
void addseg()
{
#ifdef MEM_DEBUG
    // allocate the nodes one at a time
    NODE* new_node = (NODE*) malloc(sizeof(*new_node));
    if (new_node != NULL)
    {
        memcpy(&new_node->magic, "NODE", 4);
        push_to_free_list(new_node);
    }
#else

    // Update the number of segments that were allocated.
    memory_count++;
    update_status_memory();

    // Allocate a large block of nodes at one time
    // and link them into the free_list.
    segment *newseg = (segment *) malloc(sizeof(*newseg));
    if (newseg != NULL)
    {
        newseg->next = segment_list;
        segment_list = newseg;
        for (int p = 0; p < SEG_SIZE; p++)
        {
            push_to_free_list(&newseg->nodes[p]);
        }
    }
#endif
}

// Returns a new NODE with the given type and a reference count of 0.
// None of the type-specific members are initialized.
NODE *newnode(NODETYPES type)
{
    // Make sure that there's a node on the free list
    if (free_list_is_empty())
    {
        // There's nothing on the free list.
        // Try to allocate a new segment
        addseg();
        if (free_list_is_empty())
        {
            // There's still nothing.
            // Raise an error and see if the ERRACT
            // routine frees any nodes.
            err_logo(OUT_OF_MEM, NIL);
            if (free_list_is_empty())
            {
                // We're out of options.
                // Log an unrecoverable error, which will exit.
                err_logo(OUT_OF_MEM_UNREC, NIL);
            }
        }
    }

    // Pop the top node off the free list and use it.
    NODE *newnd = pop_from_free_list();

    // Initialize the new node
    settype(newnd, type);
    newnd->ref_count = 0;

    // Note the creation of this node for the next call to NODES
    mem_nodes++;
    if (mem_nodes > mem_max) 
    {
        mem_max = mem_nodes;
    }

    // Return the new node
    return newnd;
}

struct FREED_ARRAY_LIST
{
    // Pointer to the next item in the list.
    FREED_ARRAY_LIST * Next;

    // The maximum number of elements that ToFree can hold
    int ToFreeMax;

    // A pointer to a stack of nodes to free
    NODE ** ToFree;
};

// A garbage collection stack is a set of NODE objects that are
// scheduled to be garbage collected.  This is used by gc() to
// avoid the need to allocate memory in order to free children
// NODEs by using the space within each NODE that it has freed
// to hold the scheduled NODEs.
//
// As an optimization, it uses the global free_list to hold any
// freed nodes that are not needed for book-keeping, instead
// of its own list.  This saves the effort of transfering its
// list to the free_list when gc() exits.
//
// The stack of nodes to free is actually a linked list of very
// small arrays.  Each node in the linked list is a freed NODE
// and so only has enough space to hold a "next" pointer and three
// NODE pointers to free.
//
// Since gc'ing a NODE can only cause three additional nodes to be
// gc'd (cdr, car, and obj), and since each NODE has enough space
// for three NODEs and a "next" pointer, even in the worst case,
// gc() does not need to allocate new memory.
//
// The ARRAY nodes need special handling, since gc'ing an ARRAY can
// result in the need to free an arbitrary number of nodes (however
// many the ARRAY held).
//
class CGarbageCollectionStack
{
public:
    CGarbageCollectionStack() :
        m_TopNode(NULL),
        m_TopNodeIndex(ARRAYSIZE(m_TopNode->Nodes)),
        m_DeferredArrayNodeList(NULL)
    {
    }

    void Initialize()
    {
        m_TopNode               = NULL;
        m_TopNodeIndex          = ARRAYSIZE(m_TopNode->Nodes);
        m_DeferredArrayNodeList = NULL;
    }

    void AddMemory(NODE * UnusedLogoNode)
    {
        // Assert that we can use an unused NODE as a LIST_NODE.
        assert(sizeof(LIST_NODE) <= sizeof *UnusedLogoNode);

        // Add this node to the head of the free list.
        push_to_free_list(UnusedLogoNode);
    }

    void PushDeferredArray(NODE * DeferredArray)
    {
        assert(nodetype(DeferredArray) == ARRAY);

        // Assert that we can use an unused NODE as a LIST_NODE.
        assert(sizeof(FREED_ARRAY_LIST) <= sizeof *DeferredArray);

        // Get the information we need from DeferredArray
        // before we "free" it.
        NODE ** deferredNodes = getarrptr(DeferredArray);
        int dimension         = getarrdim(DeferredArray);
   
        // From this point forward, DeferredArray is now freed.
        FREED_ARRAY_LIST * freedArray = reinterpret_cast<FREED_ARRAY_LIST*>(DeferredArray);
        freedArray->ToFreeMax = dimension;
        freedArray->ToFree    = deferredNodes;

        // Add this to the head of the deferred list.
        freedArray->Next = m_DeferredArrayNodeList;
        m_DeferredArrayNodeList = freedArray;
    }

    void PushDeferredNode(NODE * DeferredNode)
    {
        if (m_TopNodeIndex == ARRAYSIZE(m_TopNode->Nodes))
        {
            // The current stack element is full.
            // Get another one from the free list.
            // The caller is responsible for ensuring that
            // there are enough elements in the free list.
            assert(!free_list_is_empty());

            // Pop the node off the free list
            NODE * freedNode = pop_from_free_list();
            LIST_NODE * newNode = reinterpret_cast<LIST_NODE*>(freedNode);

#ifdef MEM_DEBUG
            // Initialize the unused node slots to a recognizable value
            for (size_t i = 0; i < ARRAYSIZE(newNode->Nodes); i++)
            {
                newNode->Nodes[i] = (NODE*)0xDCDCDCDC;
            }
#endif

            // Push this node onto the deferred stack
            newNode->Next  = m_TopNode;
            m_TopNode      = newNode;
            m_TopNodeIndex = 0;
        }

        // Now m_TopNode[m_TopNodeIndex] is an open slot.  Use it.
        m_TopNode->Nodes[m_TopNodeIndex] = DeferredNode;
        m_TopNodeIndex++;
    }

    void MaybeGarbageCollect(NODE * Node)
    {
        // REVISIT: Should this be reconciled with deref?
        if (Node != NIL)
        {
            if (decrefcnt(Node) == 0)
            {
                PushDeferredNode(Node);
            }
        }
    }

    bool DeferredStackIsEmpty()
    {
        return m_TopNode == NULL;
    }

    NODE * PopDeferredNode()
    {
        if (m_TopNode == NULL)
        {
            // There are no normal deferred nodes remaining.
            assert(m_TopNodeIndex == ARRAYSIZE(m_TopNode->Nodes));

            // Try to pull a node from the deferred array list.
            while (m_DeferredArrayNodeList != NULL)
            {
                for (int i = 0; i < m_DeferredArrayNodeList->ToFreeMax; i++)
                {
                    if (m_DeferredArrayNodeList->ToFree[i] != NIL)
                    {
                        // Remove this node from the deferred list and return it.
                        NODE * nextDeferredNode = m_DeferredArrayNodeList->ToFree[i];
                        m_DeferredArrayNodeList->ToFree[i] = NIL;
                        return nextDeferredNode;
                    }
                }

                // There are no more deferred nodes in this array NODE.
                // Free it.
                FREED_ARRAY_LIST * nodeToFree = m_DeferredArrayNodeList;
                free(nodeToFree->ToFree); // free the array
                m_DeferredArrayNodeList = m_DeferredArrayNodeList->Next; // next node
                AddMemory(reinterpret_cast<NODE*>(nodeToFree)); // free the node
            }

            return NIL;
        }

        // Decrement m_TopNodeIndex to the next used slot.
        m_TopNodeIndex--;

        // Return the node in the m_TopNodeIndex slot.
        NODE * deferredNode = m_TopNode->Nodes[m_TopNodeIndex];

#ifdef MEM_DEBUG
        // Set the now freed slot to a recognizable value.
        m_TopNode->Nodes[m_TopNodeIndex] = (NODE*)0xABABABAB;
#endif

        if (m_TopNodeIndex == 0)
        {
            // That was the last node in this block.
            // Move it back to the free list.

            // Pop this node from the deferred GC list.
            LIST_NODE * node = m_TopNode;
            m_TopNode      = m_TopNode->Next;
            m_TopNodeIndex = ARRAYSIZE(m_TopNode->Nodes);

            // Push it node onto the free list.
            push_to_free_list(reinterpret_cast<NODE*>(node));
        }

        return deferredNode;
    }

    void Uninitialize()
    {
        // If the GC stack is going to be uninitialized, there shouldn't
        // be any nodes which are pending garbage collection.
        assert(m_TopNode == NULL);
        assert(m_TopNodeIndex == ARRAYSIZE(m_TopNode->Nodes));
        assert(m_DeferredArrayNodeList == NULL);

#ifdef MEM_DEBUG
        // To make debugging memory leaks easier in debug builds,
        // aggressively free all nodes as soon as they are no longer needed.
        // This also ensures that gc() doesn't assume that free_list has
        // available memory at the time it is called.
        while (!free_list_is_empty())
        {
            NODE * freedNode = pop_from_free_list();
            free(freedNode);
        }
#endif
    }

private:
    // This is the first node in the GC deferred list that has
    // NODE* in it that still need to be garbage collected.
    LIST_NODE       * m_TopNode;
    int               m_TopNodeIndex;

    // A linked list of FREED_ARRAY_LIST pointers, whose arrays
    // need to be garbage collected.
    FREED_ARRAY_LIST * m_DeferredArrayNodeList;
};


void gc(NODE *nd)
{
    assert(nd != NULL);

    CGarbageCollectionStack gc_deferred_list;

    do
    {
        NODE *tcar;
        NODE *tcdr;
        NODE *tobj;

        switch (nodetype(nd))
        {
        case PUNBOUND:
            // Since this is a single-instanced node that is never
            // garbage collected, we can increase the reference count
            // to make it less likely that this node will come back
            // to be gc'd.
            nd->ref_count = 100000;

            // get ready to garbage collect the next node
            nd = gc_deferred_list.PopDeferredNode();
            continue;

        case LINE:
        case CONS:
        case CASEOBJ:
        case RUN_PARSE:
        case QUOTE:
        case COLON:
        case TREE:
            tcar = car(nd);
            tcdr = cdr(nd);
            tobj = getobject(nd);
            break;

        case CONT:
            // Continuation nodes only have a valid cdr.
            tcar = NIL;   // the car is a labels, not a NODE*
            tcdr = cdr(nd);
            tobj = NIL;   // the object shouldn't exist
            break;

        case ARRAY:
            // deref each of the nodes within the array
            {
                NODE ** pp = getarrptr(nd);
                for (int i = getarrdim(nd); 0 != i; --i, pp++)
                {
                    // Logically, we are calling deref(*pp).
                    // However, actually doing this could call gc() recursively,
                    // so it could cause a stack overflow.
                    // Instead, we NIL-out any NODE that does NOT need garbage
                    // collection, so we are left with an array of deferred
                    // nodes.
                    if (*pp != NIL)
                    {
                        if (decrefcnt(*pp) != 0)
                        {
                            // This node must NOT need to be gc'd.
                            *pp = NIL;
                        }
                    }
                }
            }

            mem_nodes--;

            // At this point, we no longer need "nd", so we can surrender it
            // to the garbage collection stack, which will reuse the node's
            // memory and schedule all of the array's nodes with no more
            // references for garbage collection.
            gc_deferred_list.PushDeferredArray(nd);

            // get ready to garbage collect the next node
            nd = gc_deferred_list.PopDeferredNode();
            continue;

        case STRING:
        case BACKSLASH_STRING:
        case VBAR_STRING:
            if (getstrhead(nd) != NULL)
            {
                // The string was allocated on the heap 
                // (it's not a string literal).
                // Decrement the reference count and free it, if necessary.
                unsigned short *temp = (unsigned short *) getstrhead(nd);

                assert(*temp != 0); // the string was already freed
                if (decstrrefcnt(temp) == 0) 
                {
                    free(getstrhead(nd));
                }
            }

        case INTEGER:
        case FLOATINGPOINT:
        case PRIM:
        case MACRO:
        case TAILFORM:
        case INFIX:
            // All of these nodes are scalars with no
            // cdr, car, or obj.  To save some processing
            // time, we omit the code with attempts to
            // garbage collect them.
            mem_nodes--;

            // At this point, we no longer need "nd", so we can
            // use its memory as bookkeeping space for the nodes
            // that we wish to free.
            gc_deferred_list.AddMemory(nd);

            // get ready to garbage collect the next node
            nd = gc_deferred_list.PopDeferredNode();
            continue;

        default:
            assert(!"freeing unrecognized node type");
        }

        mem_nodes--;

        // At this point, we no longer need "nd", so we can
        // use its memory as bookkeeping space for the nodes
        // that we wish to free.
        gc_deferred_list.AddMemory(nd);

        // Check if any of the child nodes can be garbage collected
        gc_deferred_list.MaybeGarbageCollect(tcar);
        gc_deferred_list.MaybeGarbageCollect(tcdr);
        gc_deferred_list.MaybeGarbageCollect(tobj);

        // get ready to garbage collect the next node
        nd = gc_deferred_list.PopDeferredNode();
    } while (nd != NIL);

    // Free all of the nodes which were marked as having
    // no further references as a result of freeing nd.
    gc_deferred_list.Uninitialize();
}

NODE *lnodes(NODE *  /* args */)
{
    // snapshot of total nodes when this was called
    long int temp_max   = mem_max;
    long int temp_nodes = mem_nodes;

    mem_max = mem_nodes;

    return cons_list(
        make_intnode(temp_nodes),
        make_intnode(temp_max));
}

void fill_reserve_tank()
{
    // grow the reserve tank by 50 nodes
    for (int i = 0; i < 50; i++)
    {
        reserve_tank = cons(NIL, reserve_tank);
    }
}

void use_reserve_tank()
{
    // release all nodes in the reserve tank
    gcref(reserve_tank);
    reserve_tank = NIL;
}

void check_reserve_tank()
{
    if (reserve_tank == NIL) 
    {
        fill_reserve_tank();
    }
}

void free_segment_list()
{
    while (segment_list != NULL)
    {
        segment *next_segment = segment_list->next;
        free(segment_list);
        segment_list = next_segment;
    }
}
