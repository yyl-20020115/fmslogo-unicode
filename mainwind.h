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

#ifndef __MAINWIND_H_
#define __MAINWIND_H_

#include <stdio.h>
#include "logocore.h"

// function declarations
ERR_TYPES
DumpBitmapFile(
    const wchar_t * Filename,
    int          MaxBitCount
    );

ERR_TYPES
LoadBitmapFile(
    const wchar_t   * Filename,
    unsigned int & dwPixelWidth,
    unsigned int & dwPixelHeight
    );

void
PaintToScreen(
    class wxDC     & PaintDeviceContext,
    class wxRegion   UpdateRegion,
    int              ScrollX,
    int              ScrollY
    );

#endif // __MAINWIND_H_
