/*
 *  math.h
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

#ifndef __MATH_H_
#define __MATH_H_

extern int numberp(NODE *snd);
extern NODE *lrandom(NODE *arg);
extern NODE *lrerandom(NODE *arg);
extern NODE *ladd(NODE *args);
extern NODE *lsub(NODE *args);
extern NODE *lmul(NODE *args);
extern NODE *ldivide(NODE *args);
extern NODE *lremainder(NODE *args);
extern NODE *lmodulo(NODE *args);
extern NODE *lbitand(NODE *args);
extern NODE *lbitor(NODE *args);
extern NODE *lbitxor(NODE *args);
extern NODE *lashift(NODE *args);
extern NODE *llshift(NODE *args);
extern NODE *lbitnot(NODE *args);
extern NODE *lsin(NODE *args);
extern NODE *lasin(NODE *args);
extern NODE *lcos(NODE *args);
extern NODE *lacos(NODE *args);
extern NODE *ltan(NODE *args);
extern NODE *latan(NODE *args);
extern NODE *lradsin(NODE *args);
extern NODE *lradasin(NODE *args);
extern NODE *lradcos(NODE *args);
extern NODE *lradacos(NODE *args);
extern NODE *lradtan(NODE *args);
extern NODE *lradatan(NODE *args);
extern NODE *lsqrt(NODE *args);
extern NODE *linteg(NODE *args);
extern NODE *lround(NODE *args);
extern NODE *lexp(NODE *args);
extern NODE *llog10(NODE *args);
extern NODE *lln(NODE *args);
extern NODE *lpower(NODE *args);
extern NODE *true_or_false(bool tf);
extern NODE *llessp(NODE *args);
extern NODE *llessequalp(NODE *args);
extern NODE *lgreaterp(NODE *args);
extern NODE *lgreaterequalp(NODE *args);
extern int compare_node(NODE *n1, NODE *n2, bool ignorecase);
extern bool equalp_help(NODE *arg1, NODE *arg2, bool ingc);
extern NODE *lequalp(NODE *args);
extern NODE *lnotequalp(NODE *args);
extern NODE *l_eq(NODE *args);
extern NODE *lbeforep(NODE *args);

#endif // __MATH_H_
