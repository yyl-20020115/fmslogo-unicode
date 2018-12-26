// -*- c++ -*-
// Copyright (C) 2012 by the David Costanzo
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
//

#ifndef _STRINGPRINTEDNODE_H_
#define _STRINGPRINTEDNODE_H_
#include "CStringTextStream.h"

// A helper class for printing a node into a buffer, dynamically
// allocating the buffer if necessary.
class CStringPrintedNode
{
public:

    enum PRINTLIMITSPECIFIER
    {
        WithoutPrintLimits,
        WithPrintLimits,
    };
    
    CStringPrintedNode(
        const struct NODE * Node,
        PRINTLIMITSPECIFIER PrintLimit = WithoutPrintLimits
        );

    ~CStringPrintedNode();
public:

    //const wchar_t * GetString();
	//wchar_t * GetString();

    //operator const wchar_t *();
    operator const wxString&();

public:
	const wxString& GetContent();

private:
    // block the compiler-generated constructors
    CStringPrintedNode();
    CStringPrintedNode(const CStringPrintedNode &);

	CStringTextStream m_Buffer;
};

#endif // _STRINGPRINTEDNODE_H_
