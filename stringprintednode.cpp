// Copyright (C) 2012 by David Costanzo
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
    #include "stringprintednode.h"

    #include "logocore.h"
    #include "print.h"
    #include "init.h"
    #include "debugheap.h"
#include <stdlib.h>
#endif


CStringPrintedNode::CStringPrintedNode(
    const NODE *        Node,
    PRINTLIMITSPECIFIER PrintLimit
    ) :
    m_DynamicBuffer(NULL)
{
    int printDepthLimit;
    int printWidthLimit;
    if (PrintLimit == WithPrintLimits)
    {
        // Use the current limits for printing.
        printDepthLimit = find_limit(Printdepthlimit);
        printWidthLimit = find_limit(Printwidthlimit);
    }
    else
    {
        // There are no limits for printing.
        printDepthLimit = -1;
        printWidthLimit = -1;
    }

    // First, try to print the node into the fixed-size buffer.
    size_t totalCharsNeeded = PrintNodeToString(
        Node,
        m_FixedBuffer,
        sizeof(m_FixedBuffer)/sizeof(wchar_t),
        printDepthLimit,
        printWidthLimit);

    if (sizeof(m_FixedBuffer) / sizeof(wchar_t) < totalCharsNeeded)
    {
        // More space is needed than exists in the fixed-sized buffer.
        m_DynamicBuffer = (wchar_t*)malloc((totalCharsNeeded+1)*sizeof(wchar_t));
        if (m_DynamicBuffer != NULL)
        {
			m_DynamicBuffer[totalCharsNeeded] = L'\0';
            // Print the node into the correctly sized buffer.
            size_t newTotalBytesNeeded = PrintNodeToString(
                Node,
                m_DynamicBuffer,
                totalCharsNeeded,
                printDepthLimit,
                printWidthLimit);

            // The number of bytes needed shouldn't have changed
            // from the first attempt to the second attempt.
            assert(totalCharsNeeded == newTotalBytesNeeded);
        }
    }
}

CStringPrintedNode::~CStringPrintedNode()
{
	if (m_DynamicBuffer != 0) {
		free(m_DynamicBuffer);
		m_DynamicBuffer = 0;
	}
}

const wchar_t *
CStringPrintedNode::GetString() const
{
    if (m_DynamicBuffer != NULL)
    {
        return m_DynamicBuffer;
    }
    else
    {
        return m_FixedBuffer;
    }
}

wchar_t *
CStringPrintedNode::GetString()
{
    if (m_DynamicBuffer != NULL)
    {
        return m_DynamicBuffer;
    }
    else
    {
        return m_FixedBuffer;
    }
}


CStringPrintedNode::operator const wchar_t *() const
{
    return GetString();
}

CStringPrintedNode::operator wchar_t *()
{
    return GetString();
}
