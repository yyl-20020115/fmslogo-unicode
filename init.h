/*
 *  init.h      intern header file
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

#ifndef __INIT_H_
#define __INIT_H_

#include "localizednode.h"

struct NODE;

extern CLocalizedNode Truex;
extern CLocalizedNode Falsex;
extern NODE *Left_Paren;
extern NODE *Right_Paren;
extern NODE *Null_Word;
extern CLocalizedNode Toplevel;
extern CLocalizedNode System;
extern CLocalizedNode Error;
extern CLocalizedNode End;
extern CLocalizedNode Redefp;
extern CLocalizedNode Caseignoredp;
extern CLocalizedNode Erract;
extern CLocalizedNode Printdepthlimit;
extern CLocalizedNode Printwidthlimit;
extern NODE *Pause;
extern NODE *If;
extern NODE *Ifelse;
extern CLocalizedNode To;
extern NODE *Macro;
extern NODE *Unbound;
extern NODE *Minus_Sign;
extern NODE *Minus_Tight;
extern CLocalizedNode Startup;
extern NODE *Query;
extern NODE *Output;
extern NODE *Stop;
extern NODE *Goto;
extern NODE *Tag;

extern NODE *g_ParseErrorNotEnoughInputs;

extern void init(void);
extern void uninit(void);

#endif // __INIT_H_
