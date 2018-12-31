// Copyright (C) 2005 by David Costanzo
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <stdlib.h>
   #include <stdio.h>
   #include <string.h>
   #include <ctype.h>

//   #include "debugheap.h"
   #include "logocore.h"
   #include "graphwin.h"
   #include "print.h"
   #include "screenwindow.h" // for TraceOutput
#endif

#ifdef DEBUG

// ASSUME_NO_INVALID_FREES
// false - Check that each block is in our list before freeing it.
//         This is computationally expensive, but catches double-frees and
//         freeing invalid memory.
// true  - Assume that every block that is freed was previously allocated.
//
const bool ASSUME_NO_INVALID_FREES = true;

#undef malloc
#undef calloc
#undef realloc
#undef free
#undef strdup

struct memory_header_t
{
    size_t                    blocksize;
    long                      id;
    struct memory_header_t *  prev;
    struct memory_header_t *  next;
};

struct node_information_t
{
    const NODE * node;
    long         block_id;
    long         actual_reference_count;
};

static struct memory_header_t g_allocated_blocks;
static long g_nextid             = 1;
static long g_break_alloc_id     = 0;


// get a pointer to the header
static
memory_header_t *
debug_userptr_to_header(
    void *  userptr
    )
{
    // cast the data to the block header
    char * headerptr = static_cast<char*>(userptr) - sizeof(memory_header_t);
    return reinterpret_cast<memory_header_t*>(headerptr);
}


// return a pointer beyond the header
static
unsigned char *
debug_header_to_userptr(
    memory_header_t *  header
    )
{
    return reinterpret_cast<unsigned char *>(header + 1);
}

static
const unsigned char *
debug_header_to_userptr(
    const memory_header_t * header
    )
{
    return reinterpret_cast<const unsigned char *>(header + 1);
}

const char *debug_typename_to_string(const NODE *nd)
{
    static char buf[30];
    switch (nodetype(nd))
    {
    case PNIL: return "PNIL";
    case PUNBOUND: return "PUNBOUND";
    case CONS: return "CONS";
    case STRING: return "STRING";
    case INTEGER: return "INTEGER";
    case FLOATINGPOINT: return "FLOATINGPOINT";
    case PRIM: return "PRIM";
    case MACRO: return "MACRO";
    case TAILFORM: return "TAILFORM";
    case CASEOBJ: return "CASEOBJ";
    case INFIX: return "INFIX";
    case TREE: return "TREE";
    case RUN_PARSE: return "RUN_PARSE";
    case QUOTE: return "QUOTE";
    case COLON: return "COLON";
    case BACKSLASH_STRING: return "BACKSLASH_STRING";
    case VBAR_STRING: return "VBAR_STRING";
    case ARRAY: return "ARRAY";
    case LINE: return "LINE";
    case CONT: return "CONT";
    case NT_FREE: return "FREED_OBJECT";
    default:
        sprintf(buf, "UNKNOWN_0x%X", nodetype(nd));
        return buf;
    }
}

static
char *
debug_print_node(const NODE* node)
{
    // Preserve the machine state
    bool savedIsTimeToHalt  = IsTimeToHalt;
    bool savedIsTimeToPause = IsTimeToPause;

    // Clear these flags so that real_print_node doesn't crash in check_stop().
    IsTimeToHalt  = false;
    IsTimeToPause = false;

    // Figure out how many bytes are required.
    size_t totalBytesNeeded = PrintNodeToString(node, NULL, 0);
    
    // Allocate the buffer.
    // Note that this buffer may be leaked when this is called from gdb.
    // To prevent it from showing up as a leaked allocation in the debug
    // heap, we use malloc() instead of debug_malloc().
    char * buffer = static_cast<char*>(malloc(totalBytesNeeded));
    if (buffer != NULL)
    {
        // Print the node into the buffer
        PrintNodeToString(node, buffer, totalBytesNeeded);

        // Print the buffer
        fprintf(stderr, "%s\n", buffer);
    }

    // Restore the machine state
    IsTimeToHalt  = savedIsTimeToHalt;
    IsTimeToPause = savedIsTimeToPause;

    // Return the string form of the buffer.
    // This is because gdb doesn't always show the output from fprintf,
    // but it can print any string that is returned to it.
    return buffer;
}

static
const NODE *
get_node(const struct memory_header_t * block)
{
    const void * userptr = debug_header_to_userptr(block);

    if (block->blocksize == sizeof(NODE) &&
        0 == memcmp(userptr, "NODE", 4))
    {
        return static_cast<const NODE*>(userptr);
    }
    else
    {
        return NULL;
    }
}

static
void
note_reference(
    const NODE                * node,
    struct node_information_t * elements,
    long                        total_elements
    )
{
    for (long i = 0; i < total_elements; i++)
    {
        if (elements[i].node == node)
        {
            // found it
            elements[i].actual_reference_count++;
            return;
        }
    }
}

static
void 
debug_report_leaks(void)
{
    if (g_allocated_blocks.next != &g_allocated_blocks)
    {
        // the list is not empty
        TraceOutput("Memory Leaks detected!\n");

        // count the number of leaked memory blocks
        long total_blocks_leaked = 0;
        long total_bytes_leaked  = 0;
        long total_nodes_leaked  = 0;
        for (struct memory_header_t * current_block = g_allocated_blocks.next; 
             current_block != &g_allocated_blocks;
             current_block = current_block->next)
        {
            total_bytes_leaked += current_block->blocksize;
            total_blocks_leaked++;

            if (get_node(current_block) != NULL)
            {
                total_nodes_leaked++;
            }
        }

        TraceOutput(
            "Leaked %lu bytes in %lu blocks\n",
            total_bytes_leaked,
            total_blocks_leaked);

        // dump each leaked memory block
        for (struct memory_header_t * current_block = g_allocated_blocks.next; 
             current_block != &g_allocated_blocks;
             current_block = current_block->next)
        {
            void * userptr      = debug_header_to_userptr(current_block);
            unsigned char * ptr = static_cast<unsigned char*>(userptr);

            TraceOutput(
                "(id=%8lu) %8u bytes at 0x%08X: <",
                current_block->id,
                current_block->blocksize,
                ptr);

            // dump some bytes (at most eight) of the allocation to help
            // the user figure out what is being leaked.
            const int MAX_BYTES_TO_DUMP = 8;
            int dumpbytes = current_block->blocksize;
            if (dumpbytes > MAX_BYTES_TO_DUMP)
            {
                dumpbytes = MAX_BYTES_TO_DUMP;
            }

            // dump the first eight bytes as an ASCII string
            for (int i = 0; i < dumpbytes; i++)
            {
                if (isprint(ptr[i]))
                {
                    TraceOutput("%c", ptr[i]);
                }
                else
                {
                    TraceOutput(" ");
                }
            }
            for (int i = dumpbytes; i < MAX_BYTES_TO_DUMP; i++)
            {
                TraceOutput(" ");
            }

            TraceOutput("> ");

            // dump the first eight bytes as binary octets
            for (int i = 0; i < dumpbytes; i++)
            {
                char nibbletohex[] = "0123456789ABCDEF";
                TraceOutput(
                    "%c%c ", 
                    nibbletohex[0xF & (ptr[i] >> 4)],
                    nibbletohex[0xF & (ptr[i] >> 0)]);
            }

            TraceOutput("\n");
        }

        if (total_nodes_leaked != 0)
        {
            struct node_information_t * node_information = 
                static_cast<struct node_information_t *>(calloc(
                    total_nodes_leaked,
                    sizeof(struct node_information_t)));

            if (node_information != NULL)
            {
                // Initialize the additional node information array.
                int i = 0;
                for (const struct memory_header_t * current_block = g_allocated_blocks.next;
                     current_block != &g_allocated_blocks;
                     current_block = current_block->next)
                {
                    const NODE * current_node = get_node(current_block);
                    if (current_node != NULL)
                    {
                        if (node_information != NULL)
                        {
                            node_information[i].node                   = current_node;
                            node_information[i].block_id               = current_block->id;
                            node_information[i].actual_reference_count = 0;
                        }

                        i++;
                    }
                }

                // Populate the additional node information.
                for (const struct memory_header_t * current_block = g_allocated_blocks.next;
                     current_block != &g_allocated_blocks;
                     current_block = current_block->next)
                {
                    const NODE * current_node = get_node(current_block);
                    if (current_node != NULL)
                    {
                        switch (nodetype(current_node))
                        {
                        case LINE:
                        case CONS:
                        case CASEOBJ:
                        case RUN_PARSE:
                        case QUOTE:
                        case COLON:
                        case TREE:
                            // These node types may have a CAR, a CDR, and an OBJ
                            note_reference(
                                car(current_node),
                                node_information,
                                total_nodes_leaked);

                            note_reference(
                                cdr(current_node),
                                node_information,
                                total_nodes_leaked);

                            note_reference(
                                getobject(current_node),
                                node_information,
                                total_nodes_leaked);
                            break;

                        case CONT:
                            // Continuation nodes only have a valid cdr.
                            note_reference(
                                cdr(current_node),
                                node_information,
                                total_nodes_leaked);
                            break;

                        case ARRAY:
                            {
                                NODE ** pp        = getarrptr(current_node);
                                int     dimension = getarrdim(current_node);
                                while (--dimension >= 0)
                                {
                                    note_reference(
                                        *pp,
                                        node_information,
                                        total_nodes_leaked);

                                    pp++;
                                }
                            }
                            break;
                        }
                    }
                }

                // Display the leaked nodes
                TraceOutput("\n");
                TraceOutput("Dumping leaked NODEs\n");
                for (i = 0; i < total_nodes_leaked; i++)
                {
                    TraceOutput(
                        "(id=%8lu) at 0x%08X %s reported_refs=%d computed_refs=%d:%s\n",
                        node_information[i].block_id,
                        node_information[i].node,
                        debug_typename_to_string(node_information[i].node),
                        getrefcnt(node_information[i].node),
                        node_information[i].actual_reference_count,
                        node_information[i].actual_reference_count == 0 ?
                            " <--- TOP_LEVEL_LEAK" :
                            "");

                    char * str = debug_print_node(node_information[i].node);
                    free(str);

                    TraceOutput("\n");
                }
            }

            free(node_information);
        }
    }
}

static
void
initialize_memory_tracking(
    void
    )
{
    static bool is_initialized = false;
    if (!is_initialized)
    {
        // make the list circular
        g_allocated_blocks.next = &g_allocated_blocks;
        g_allocated_blocks.prev = &g_allocated_blocks;

        g_allocated_blocks.blocksize = 0;

        const char * break_alloc_id = getenv("BREAKALLOC");
        if (break_alloc_id != NULL)
        {
            g_break_alloc_id = atoi(break_alloc_id);
        }

        atexit(debug_report_leaks);

        is_initialized = true;
    }
}


void * debug_malloc(size_t blocksize)
{
    size_t realsize = blocksize + sizeof(memory_header_t);
    if (realsize < blocksize) 
    {
        // There was integer overflow, so blocksize it
        // too large to allocate.
        return NULL;
    }

    void * realptr = malloc(sizeof(memory_header_t) + blocksize);
    if (realptr == NULL) 
    {
        return NULL;
    }

    if (g_break_alloc_id == g_nextid)
    {
        // The user has requested that we break on this allocation.
#ifndef WX_PURE
        DebugBreak();
#endif
    }

    // cast the data to the block header
    memory_header_t * header = static_cast<memory_header_t*>(realptr);
    header->blocksize = blocksize;

    header->id = g_nextid++;

    // link the new block into the head of the list
    initialize_memory_tracking();
    header->next = g_allocated_blocks.next;
    header->prev = &g_allocated_blocks;

    g_allocated_blocks.next->prev = header;
    g_allocated_blocks.next       = header;

    // get a pointer to the user's memory
    unsigned char * ptr = debug_header_to_userptr(header);

    // fill uninitialized memory with a recognizable bit pattern
    memset(ptr, 0xDD, blocksize);

    return ptr;
}

void debug_free(void * userptr)
{
    if (userptr == NULL)
    {
        // free(NULL) is defined to be a no-op
        return;
    }

    memory_header_t * header = debug_userptr_to_header(userptr);

    bool userptr_is_allocated = false;
    if (ASSUME_NO_INVALID_FREES)
    {
        // just assume that the caller is freeing a valid memory block
        userptr_is_allocated = true;
    }
    else
    {
        // before doing anything destructive, make sure this block is on our list
        for (struct memory_header_t * current_block = g_allocated_blocks.next; 
             current_block != &g_allocated_blocks;
             current_block = current_block->next)
        {
            if (header == current_block)
            {
                userptr_is_allocated = true;
                break;
            }
        }
    }

    if (userptr_is_allocated)
    {
        // unlink this block from the list
        header->next->prev = header->prev;
        header->prev->next = header->next;

        // fill the memory with a recognizable bit pattern
        memset(header, 0xCC, header->blocksize + sizeof(*header));
        free(header);
    }
    else
    {
#ifndef WX_PURE
        // calling free in invalid memory
        DebugBreak();
#endif
    }
}

void * debug_calloc(size_t arraylength, size_t elementsize)
{
    size_t blocksize = arraylength * elementsize;
    if (blocksize < elementsize || blocksize < arraylength)
    {
        // Integer overflow when calculating the size
        // This is too large to allocate.
        return NULL;
    }

    void * ptr = debug_malloc(blocksize);
    if (ptr == NULL) 
    {
        return NULL;
    }

    // calloc requires that the memory is set to 0.
    memset(ptr, 0x00, blocksize);
    return ptr;
}

void * debug_realloc(void * userptr, size_t newsize)
{
    if (userptr == NULL) 
    {
        // realloc with a NULL first parameter means malloc()
        return debug_malloc(newsize);
    }

   if (newsize == 0)
   {
       // realloc with a size of 0 means free()
       debug_free(userptr);
       return NULL;
   }

   // this is a real realloc()
   memory_header_t * header = debug_userptr_to_header(userptr);
   if (header->blocksize < newsize)
   {
       // this is a realloc() to a larger size
       void * returnptr = debug_malloc(newsize);
       if (returnptr != NULL)
       {
           // copy the old memory block's contents to the new block
           memcpy(returnptr, userptr, header->blocksize);

           // release the old memory
           debug_free(userptr);
       }

       return returnptr;
   }

   // They are reallocating to a smaller size.
   // We can ignore this.
   header->blocksize = newsize;
   return userptr;
}


wchar_t * debug_strdup(const wchar_t * string)
{
    size_t length = wcslen(string);
    void * newstring = debug_malloc(length + 1);
    if (newstring == NULL) 
    {
        return NULL;
    }

    wcsncpy(newstring, string, (length + 1));
    return static_cast<wchar_t *>(newstring);
}

void * operator new (size_t size)
{
    return debug_malloc(size);
}

void operator delete (void * block)
{
    debug_free(block);
}

#endif // DEBUG
