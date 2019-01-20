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

#ifndef __MULTIMEDIA_WINDOW_H_
#define __MULTIMEDIA_WINDOW_H_

// types
struct NODE;

// global variables
extern class wxString mci_callback;
extern class wxString timer_callback[];

// function declarations
extern NODE *lmci(NODE *arg);
extern NODE *lmidiopen(NODE *arg);
extern NODE *lmidiclose(NODE *arg);
extern NODE *lmidimessage(NODE *arg);
extern NODE *lsound(NODE *arg);
extern NODE *lplaywave(NODE *args);
extern NODE *lsettimer(NODE *arg);
extern NODE *lcleartimer(NODE *arg);
extern bool IsAnyTimerActive();
extern void init_timers();
extern void halt_all_timers();
extern void clear_all_timers();
extern void uninitialize_timers();

#endif // __MULTIMEDIA_WINDOW_H_
