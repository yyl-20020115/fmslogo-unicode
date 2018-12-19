/*
 *  lists.h
 *
 *  Copyright (C) 1993 by the Regents of the University of California
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef __LISTS_H_
#define __LISTS_H_

extern NODE *list_arg(NODE *args);
extern NODE *lbutfirst(NODE *args);
extern NODE *lbutlast(NODE *args);
extern NODE *lfirst(NODE *args);
extern NODE *lfirsts(NODE *args);
extern NODE *lbfs(NODE *args);
extern NODE *llast(NODE *args);
extern NODE *llist(NODE *args);
extern NODE *lemptyp(NODE *arg);
extern NODE *lascii(NODE *args);
extern NODE *lrawascii(NODE *args);
extern NODE *lbackslashedp(NODE *args);
extern NODE *lchar(NODE *args);
extern NODE *lcount(NODE *args);
extern NODE *lfput(NODE *args);
extern NODE *llput(NODE *args);
extern NODE *string_arg(NODE *args);
extern NODE *lword(NODE *args);
extern NODE *lsentence(NODE *args);
extern NODE *lwordp(NODE *arg);
extern NODE *llistp(NODE *arg);
extern NODE *lnumberp(NODE *arg);
extern NODE *larrayp(NODE *arg);
extern NODE *lmemberp(NODE *args);
extern NODE *lsubstringp(NODE *args);
extern NODE *lmember(NODE *args);
extern NODE *integer_arg(NODE *args);
extern NODE *ranged_integer_arg(NODE *args, int MinValue, int MaxValue);
extern NODE *nonnegative_int_arg(NODE *args);
extern NODE *positive_int_arg(NODE *args);
extern FIXNUM int_arg(NODE *args);
extern NODE *litem(NODE *args);
extern NODE *lsetitem(NODE *args);
extern NODE *l_setitem(NODE *args);
extern NODE *larray(NODE *args);
extern FLONUM float_arg(NODE *args);
extern NODE *lform(NODE *args);
extern NODE *l_setfirst(NODE *args);
extern NODE *l_setbf(NODE *args);

#endif // __LISTS_H_
