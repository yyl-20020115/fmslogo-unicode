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

#ifndef __TERM_H_
#define __TERM_H_

struct NODE;
extern NODE *lcleartext(NODE *args);
extern NODE *lcursor(NODE *args);
extern NODE *lsetcursor(NODE *args);
extern NODE *lsetmargins(NODE *args);
extern NODE *lstandout(NODE *args);

#endif // __TERM_H_
