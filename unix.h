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

#ifndef __UNIX_H_
#define __UNIX_H_

#include <setjmp.h>
#include "print.h" // for MESSAGETYPE

struct NODE;

// function declarations
extern int printfx(const wchar_t *fmt);
extern int printfx(const wchar_t *fmt, const wchar_t *str);
extern void unblock_input(void);
extern void putcombochar(MESSAGETYPE type, wchar_t c);
extern NODE *lchdir(NODE *arg);
extern NODE *lpopdir(NODE *arg);
extern NODE *lmkdir(NODE *arg);
extern NODE *lrmdir(NODE *arg);
extern NODE *ldirectories(NODE *arg);
extern NODE *lfiles(NODE *arg);
extern void uninitialize_combobox(void);

// global variables
extern jmp_buf iblk_buf;


#endif // __UNIX_H_
