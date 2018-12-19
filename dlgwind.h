// -*- c++ -*-
// Copyright (C) 1995 by the Regents of the University of California
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

#ifndef __DLGWND_H_
#define __DLGWND_H_

struct NODE;

extern NODE *lmessagebox(NODE *args);
extern NODE *lquestionbox(NODE *args);
extern NODE *lyesnobox(NODE *args);
extern NODE *lselectbox(NODE *args);
extern NODE *ldialogcreate(NODE *args);
extern NODE *ldialogenable(NODE *args);
extern NODE *ldialogdelete(NODE *arg);
extern NODE *lwindowcreate(NODE *args);
extern NODE *lwindowenable(NODE *args);
extern NODE *lwindowdelete(NODE *arg);
extern NODE *lbuttoncreate(NODE *args);
extern NODE *lbuttonupdate(NODE *args);
extern NODE *lbuttonenable(NODE *args);
extern NODE *lbuttondelete(NODE *arg);
extern NODE *lscrollbarcreate(NODE *args);
extern NODE *lscrollbarenable(NODE *args);
extern NODE *lscrollbardelete(NODE *arg);
extern NODE *lscrollbarset(NODE *args);
extern NODE *lscrollbarget(NODE *arg);
extern NODE *llistboxcreate(NODE *args);
extern NODE *llistboxenable(NODE *args);
extern NODE *llistboxdelete(NODE *arg);
extern NODE *llistboxgetselect(NODE *arg);
extern NODE *llistboxaddstring(NODE *args);
extern NODE *llistboxdeletestring(NODE *args);
extern NODE *lcomboboxcreate(NODE *args);
extern NODE *lcomboboxenable(NODE *args);
extern NODE *lcomboboxdelete(NODE *arg);
extern NODE *lcomboboxgettext(NODE *arg);
extern NODE *lcomboboxsettext(NODE *arg);
extern NODE *lcomboboxaddstring(NODE *args);
extern NODE *lcomboboxdeletestring(NODE *args);
extern NODE *lstaticcreate(NODE *args);
extern NODE *lstaticupdate(NODE *args);
extern NODE *lstaticdelete(NODE *arg);
extern NODE *lgroupboxcreate(NODE *args);
extern NODE *lgroupboxdelete(NODE *arg);
extern NODE *lradiobuttoncreate(NODE *args);
extern NODE *lradiobuttonenable(NODE *args);
extern NODE *lradiobuttondelete(NODE *arg);
extern NODE *lradiobuttonset(NODE *args);
extern NODE *lradiobuttonget(NODE *arg);
extern NODE *lcheckboxcreate(NODE *args);
extern NODE *lcheckboxenable(NODE *args);
extern NODE *lcheckboxdelete(NODE *arg);
extern NODE *lcheckboxset(NODE *args);
extern NODE *lcheckboxget(NODE *arg);
extern NODE *ldialogfileopen(NODE *arg);
extern NODE *ldialogfilesave(NODE *arg);
extern NODE *lwindowfileedit(NODE *arg);
extern void uninitialize_windows();

#endif // __DLGWND_H_

