// -*- c++ -*-
// Copyright (C) 1995 by George Mills
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

#ifndef __LOCALIZEDNODE_H_
#define __LOCALIZEDNODE_H_

class CLocalizedNode
{
public:
    CLocalizedNode();

	~CLocalizedNode();

    void Initialize(
        const wchar_t    * PrimaryName,
        const wchar_t    * AlternateName
        );

    struct NODE * GetNode() const;
    const wchar_t *  GetName() const;
    bool          Equals(struct NODE * Node) const;

    // used only for special variables, like "caseignorep"
    struct NODE * GetValue() const;

private:
    struct NODE * m_Primary;
    struct NODE * m_Alternate;
};

#endif // __LOCALIZEDNODE_H_
