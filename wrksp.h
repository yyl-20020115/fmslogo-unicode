/*
 *  wrksp.h      logo workspace management module
 *
 *    Copyright (C) 1993 by the Regents of the University of California
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __WORKSPACE_H_
#define __WORKSPACE_H_

#include <stdio.h> // for fpos_t
struct NODE;

// functions
extern void untreeify_procnode(NODE * procnode);
extern NODE *ltext(NODE *args);
extern NODE *lfulltext(NODE *args);
extern NODE *ldefine(NODE *args);
extern NODE *ldefmacro(NODE *args);
extern NODE *anonymous_function(NODE *text);
extern NODE *lto(NODE *args);
extern NODE *lmacro(NODE *args);
extern NODE *lmake(NODE *args);
extern NODE *lcontents(NODE *arg);
extern NODE *lstepped(NODE *arg);
extern NODE *ltraced(NODE *arg);
extern NODE *lburied(NODE *arg);
extern NODE *lprocedures(NODE *arg);
extern NODE *lnames(NODE *arg);
extern NODE *lplists(NODE *arg);
extern NODE *lpo(NODE *arg);
extern NODE *lpot(NODE *arg);
extern NODE *lerase(NODE *arg);
extern NODE *lbury(NODE *arg);
extern NODE *ltrace(NODE *arg);
extern NODE *lstep(NODE *arg);
extern NODE *lunbury(NODE *arg);
extern NODE *luntrace(NODE *arg);
extern NODE *lunstep(NODE *arg);
extern NODE *ledit(NODE *args);
extern bool endedit(void);
extern bool something_is_unburied();
extern NODE *lthing(NODE *args);
extern NODE *lnamep(NODE *args);
extern NODE *lprocedurep(NODE *args);
extern NODE *lproplistp(NODE *args);
extern NODE *lprimitivep(NODE *args);
extern NODE *ldefinedp(NODE *args);
extern NODE *lmacrop(NODE *args);
extern NODE *larity(NODE *args);
extern NODE *lcopydef(NODE *args);
extern NODE *get_all_proc_names();
extern NODE *get_all_variable_names();


// global variables
extern bool   to_pending;
extern bool   yield_flag;
extern bool   IsDirty;
extern bool   bExpert;

extern long int g_CharactersSuccessfullyParsedInEditor;

#endif // __WORKSPACE_H_
