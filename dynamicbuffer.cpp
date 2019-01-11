// Copyright (C) 2006 by the David Costanzo
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

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "dynamicbuffer.h"

   #include <assert.h>
   #include <stdlib.h>
   #include <string.h>
   #include <algorithm>

//   #include "debugheap.h"
#endif

#ifndef _WINDOWS
#include <wchar.h>
#endif

// constructs an empty buffer
CDynamicBuffer::CDynamicBuffer()
	:text()
{
}

CDynamicBuffer::~CDynamicBuffer()
{
    Dispose();
}

// deletes the contents of the internal buffer
void CDynamicBuffer::Dispose()
{
	this->text.clear();
}


// empties the contents of the enternal buffer, but doesn't free it.
void CDynamicBuffer::Empty()
{
	this->text.clear();
}

// returns if the buffer contains no data
bool CDynamicBuffer::IsEmpty() const
{
	return this->text.length() == 0;
}


// Append a NUL-terminated string to the buffer
void 
CDynamicBuffer::AppendString(
    const wchar_t * ToAppend
    )
{
	if (ToAppend != 0) {
		this->text.Append(ToAppend);
  }
}

void 
CDynamicBuffer::AppendChar(
	wchar_t         ToAppend
    )
{

	this->text.Append(ToAppend);
}

// Returns a pointer to the contents of the buffer.
// This is always NUL-terminated, but it may be NULL
// if the string length is 0.
const wxString&
CDynamicBuffer::GetBuffer(
    void
    )
{

	return this->text;
}

size_t
CDynamicBuffer::GetBufferLength(
    void
    ) const
{
	return this->text.length();
}

// Returns the next character from the buffer and removes it.
// Returns '\0' if the buffer is empty.
int
CDynamicBuffer::PopChar(
    void
    )
{
    int ch = 0;

    if (!this->IsEmpty())
    {
		ch = this->text[0];
		this->text.Remove(0, 1);
    }

    return ch;
}
