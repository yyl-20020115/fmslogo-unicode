/*
 *      localizednode.cpp       CLocalizedNode definition
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
 *
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <string.h>

   #include "localizednode.h"
   #include "logocore.h"
   #include "intern.h"
   #include "logodata.h"
   #include "logomath.h"
   #include "init.h"
   #include "debugheap.h"
#endif
#ifndef _WINDOWS
#include <wchar.h>
#endif
CLocalizedNode::CLocalizedNode() :
    m_Primary(NIL),
    m_Alternate(NIL)
{
}
CLocalizedNode::~CLocalizedNode()
{
	//if (this->m_Primary != NIL) {
	//	gcref(this->m_Primary);
	//}
	//if (this->m_Alternate != NIL) {
	//	gcref(this->m_Alternate);
	//}
}

// Initializes this localized node.
//
// PrimaryName   - The English name of this node.
// AlternateName - The alternate (localized) name of this node.
//                 This may be NULL if this node has not been localized.
void
CLocalizedNode::Initialize(
    const wchar_t    * PrimaryName,
    const wchar_t    * AlternateName
    )
{
    // The Primary name always exists.
    m_Primary = intern(make_static_strnode(PrimaryName));

    // The Alternate name may not exist.
    if (AlternateName != NULL)
    {
        if (wcscmp(PrimaryName, AlternateName) != 0)
        {
            // the alternate name is different from the Primary name
            m_Alternate = intern(make_static_strnode(AlternateName));
        }
    }
}

// Returns an interned CASEOBJ for this node, preferring the
// alternate (localized) node to the primary (English) one,
// if it exists.
NODE *
CLocalizedNode::GetNode() const
{
    // prefer to use the alternate node, if it exists
    if (m_Alternate != NIL)
    {
        return m_Alternate;
    }
    else
    {
        return m_Primary;
    }
}

const wchar_t *
CLocalizedNode::GetName() const
{
    // Use GetNode() so that we return the alternate name, if it exists.

    // Because the nodes were created with make_static_strnode()
    // We can directly return the node's string knowing that it
    // is NUL-terminated and will not be freed.
    return getstrptr(strnode__caseobj(GetNode()));
}

bool
CLocalizedNode::Equals(
    NODE * Node
    ) const
{
    // see if this matches the primary node
    if (0 == compare_node(Node, m_Primary, true))
    {
        return true;
    }

    // See if this matches the alternate node
    if (m_Alternate != NIL)
    {
        if (0 == compare_node(Node, m_Alternate, true))
        {
            return true;
        }
    }

    return false;
}

NODE *
CLocalizedNode::GetValue() const
{
    // the primary object always exists
    NODE * value = valnode__caseobj(m_Primary);
    if (value != Unbound)
    {
        // the value is bound, which means that it has been defined.
        return value;
    }

    if (m_Alternate != NIL)
    {
        // this localized node has an alternate name.
        return valnode__caseobj(m_Alternate);
    }

    // neither the primary nor the seconary variables have values.
    return Unbound;
}
