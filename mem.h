// Copyright (C) 2005 by David Costanzo

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

#ifndef __MEM_H_
#define __MEM_H_

#include "logocore.h"

// global variables
extern int memory_count;

// function declarations
extern NODE *newnode(NODETYPES type);
extern void gc(NODE *nd);
extern NODE *lnodes(NODE *args);
extern void fill_reserve_tank(void);
extern void use_reserve_tank(void);
extern void check_reserve_tank(void);
extern void free_segment_list(void);

#endif // __MEM_H_
