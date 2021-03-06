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

#ifndef __FILESWND_H_
#define __FILESWND_H_
#include <wx/string.h>
#include "CFileTextStream.h"
// function declarations

extern void filesave(const wxString&  Filename, FileTextStreamType Ftt);
extern bool fileload(const wxString&  Filename, bool CheckBOM, FileTextStreamType* Ftt);

#endif // __FILESWND_H_
