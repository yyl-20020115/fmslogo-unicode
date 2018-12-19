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

#ifndef __COMS_H_
#define __COMS_H_

#include "logocore.h"

// function variables
extern NODE *make_cont(enum labels cont, NODE *val);
extern NODE *loutput(NODE *arg);
extern NODE *lstop(NODE *arg);
extern NODE *lthrow(NODE *arg);
extern NODE *lcatch(NODE *args);
extern NODE *lgoto(NODE *arg);
extern NODE *ltag(NODE *arg);
extern bool  boolean_arg(NODE *args);
extern NODE *lnot(NODE *args);
extern NODE *land(NODE *args);
extern NODE *lor(NODE *args);
extern NODE *runnable_arg(NODE *args);
extern NODE *lif(NODE *args);
extern NODE *lifelse(NODE *args);
extern NODE *lrun(NODE *args);
extern NODE *lrunresult(NODE *args);
extern NODE *lrepeat(NODE *args);
extern NODE *lrepcount(NODE *args);
extern NODE *lforever(NODE *args);
extern NODE *ltest(NODE *args);
extern NODE *liftrue(NODE *args);
extern NODE *liffalse(NODE *args);
extern NODE *lbye(NODE *args);
extern NODE *lwait(NODE *args);
extern NODE *ltime(NODE *args);
extern NODE *ltimemilli(NODE *args);
extern NODE *lshell(NODE *args);

// global variables
extern FIXNUM ift_iff_flag;



#endif // __COMS_H_
