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

#ifndef _DYNAMICBUFFER_H_
#define _DYNAMICBUFFER_H_

#include <stddef.h>
#include <wx/string.h>
class CDynamicBuffer
{
public:
    friend class CDynamicBufferInvariant;

    CDynamicBuffer();
    ~CDynamicBuffer();

    bool IsEmpty() const;
    void Empty();
    void Dispose();
    void AppendString(const wchar_t * ToAppend);
    void AppendChar(wchar_t ToAppend);

	const wxString& GetBuffer();
    size_t GetBufferLength() const;
    int    PopChar();

private:

	wxString text;
};

#endif // _DYNAMICBUFFER_H_
