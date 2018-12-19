/*
 *      sort.cpp       sorting utilities module                dvb
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

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include <stdlib.h>
    #include <string.h>

    #include "sort.h"
    #include "logocore.h"
    #include "logodata.h"
    #include "logomath.h"
#endif

// Modify a list such that each element in the list
// is inserted into its own, one-element list.
static
void ms_listlist(NODE *nd)
{
    while (nd != NIL)
    {
        NODE* temp = cons_list(car(nd));
        setcar(nd, temp);
        nd = cdr(nd);
    }
}

static
NODE *merge(NODE *a, NODE *b, bool ignorecase)
{
    if (a == NIL) 
    {
        return b;
    }

    if (b == NIL) 
    {
        return a;
    }

    NODE *ret;
    NODE *tail;
    if (compare_node(car(a), car(b), ignorecase) < 0)
    {
        ret = a;
        tail = a;
        a = cdr(a);
    }
    else
    {
        ret = b;
        tail = b;
        b = cdr(b);
    }

    while (a != NIL && b != NIL)
    {
        if (compare_node(car(a), car(b), ignorecase) < 0)
        {
            tail->nunion.ncons.ncdr = a;
            a = cdr(a);
        }
        else
        {
            tail->nunion.ncons.ncdr = b;
            b = cdr(b);
        }
        tail = cdr(tail);
    }

    if (b == NIL) 
    {
        tail->nunion.ncons.ncdr = a;
    }
    else
    {
        tail->nunion.ncons.ncdr = b;
    }

    return ret;
}

static
void mergepairs(NODE *nd, bool ignorecase)
{
    while (nd != NIL && cdr(nd) != NIL)
    {
        nd->nunion.ncons.ncar = merge(car(nd), cadr(nd), ignorecase);
        NODE * temp = cdr(nd);
        nd->nunion.ncons.ncdr = cddr(nd);
        temp->nunion.ncons.ncar = temp->nunion.ncons.ncdr = NIL;
        gc(temp);
        nd = cdr(nd);
    }
}

// Returns a sorted list of nodes.
//
// list       - A list of nodes to sort.
//              This must have a reference count of 0.
//              The list is consumed by this call.
// ignorecase - true, if the sort should be case-insensitive for strings.
//              false, otherwise.
//
// The returned list has a reference count of 0 and is the caller's
// responsiblity to free.
NODE * mergesort(NODE * list, bool ignorecase)
{
    // The empty list is already sorted.
    if (list == NIL)
    {
        return NIL;
    }

    // The calling contract with respect to reference counting only
    // makes sense if given a top-level list with no references.
    assert(getrefcnt(list) == 0);

    // A single element list is already sorted.
    if (cdr(list) == NIL) 
    {
        return list;
    }

    // Convert each element in the list into a single-element list
    // that we can then merge.
    ms_listlist(list);

    // While there is more than one list, merge the lists pair-wise.
    while (cdr(list) != NIL)
    {
        mergepairs(list, ignorecase);
    }

    // The original contents of the list has no been collected
    // in car(list).  We carefully unlink it from "list" so that
    // we can free "list" without freeing the sorted list that we
    // are going to return.
    NODE * newHead = car(list);
    list->nunion.ncons.ncar = NIL;
    gc(list);
    decrefcnt(newHead);

    // Return the sorted list with a refcount of 0.
    return newHead;
}
