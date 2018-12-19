// Copyright (C) 2005 by David Costanzo

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
   #include <string.h>

   #include "appendablelist.h"
   #include "logodata.h"
   #include "debugheap.h"
#endif

CAppendableList::CAppendableList()
    : m_Head(NIL),
      m_Tail(NULL)
{
}

void CAppendableList::AppendElement(NODE * NewLastElement)
{
    assert(m_Tail == NULL || cdr(m_Tail) == NIL);

    NODE * newtail = cons_list(NewLastElement);

    // Add this node to the list
    if (m_Tail == NULL)
    {
        // list was empty
        m_Head = newtail;
        m_Tail = m_Head;
    }
    else 
    {
        // list has at least one item
        setcdr(m_Tail, newtail);
        m_Tail = newtail;
    }
}

void CAppendableList::AppendList(NODE * NewTail)
{
    assert(m_Tail  == NULL || cdr(m_Tail) == NIL);
    assert(NewTail == NIL  || nodetype(NewTail) == CONS);

    // only append something if the new list isn't empty
    if (NewTail != NIL)
    {
        // Add this node to the list
        if (m_Tail == NULL)
        {
            // list was empty
            m_Head = NewTail;
            m_Tail = m_Head;
        }
        else 
        {
            // list has at least one item
            setcdr(m_Tail, NewTail);
            m_Tail = NewTail;
        }

        // advance m_Tail to the last node in NewTail
        while (cdr(m_Tail) != NIL)
        {
            m_Tail = cdr(m_Tail);
        }
    }
}

NODE * CAppendableList::GetList()
{
    return m_Head;
}
