// Copyright (C) 2005 by David Costanzo
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

#ifndef _DEBUGHEAP_H_
#define _DEBUGHEAP_H_

#ifdef DEBUG

#include <stddef.h> // for size_t

#define malloc    debug_malloc
#define calloc    debug_calloc
#define realloc   debug_realloc
#define free      debug_free
#define strdup    debug_strdup

void * debug_malloc(size_t blocksize);
void   debug_free(void * userptr);
void * debug_calloc(size_t arraylength, size_t elementsize);
void * debug_realloc(void * userptr, size_t newsize);
wchar_t * debug_strdup(const wchar_t * string);

#endif // DEBUG

#endif // _DEBUGHEAP_H_
