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

#ifndef __GRAPHWIN_H_
#define __GRAPHWIN_H_

#include <wx/gdicmn.h> // wxRect

#include "logocore.h"
#include "graphics.h"

#ifdef WX_PURE
  typedef struct __HDC * HDC;
#endif

// global variable declarations
extern wxRect g_FullRect;

extern int xoffset;
extern int yoffset;

extern int BaseUnitsx;
extern int BaseUnitsy;

extern bool IsTimeToExit;
extern bool IsTimeToPause;
extern bool IsTimeToHalt;
extern bool CheckDoingEvents();
extern bool zoom_flag;

extern FLONUM the_zoom;

#ifndef WX_PURE

  extern LOGFONT FontRec;

  extern LOGPEN g_LogicalNormalPen;
  extern HPEN   g_NormalPen;

  extern LOGPEN g_LogicalErasePen;
  extern HPEN   g_ErasePen;

  extern HBITMAP MemoryBitMap;

#endif // WX_PURE

// function declarations
extern ERR_TYPES gifsave_helper(const wxString& GifFileName, int iDelay_, int bAppendMode_, int iLoop_, int iTrans, int iMaxColorDepth);
extern ERR_TYPES gifload_helper(const wxString& GifFileName, unsigned int &dwPixelWidth, unsigned int &dwPixelHeight);
extern bool HtmlHelpInitialize();
extern void HtmlHelpUninitialize();
extern NODE *lstatus(NODE *arg);
extern NODE *lnostatus(NODE *arg);
extern void zoom_helper(FLONUM temp_zoom);
extern void UpdateZoomControlFlag();
extern NODE *lzoom(NODE *arg);
extern NODE *lwinhelp(NODE *arg);
extern NODE *lhelp(NODE *arg);
extern NODE *lsetlabelfont(NODE *arg);
extern NODE *lfontfacenames(NODE *arg);
extern NODE *llabelfont(NODE *arg);
extern NODE *lsetfocus(NODE *args);
extern NODE *lgetfocus(NODE *arg);
extern NODE *lwindowset(NODE *args);
extern void logofill(bool fillUntilPenColor);
#ifndef WX_PURE // for SIZE
extern SIZE labelsize(const wxString& s);
#endif
extern void label(const wxString& s);
extern void UpdateErasePen(int Width, RGBCOLOR Color);
extern void UpdateNormalPen(int Width, RGBCOLOR Color);
extern void ChangeActivePenColor(int Red, int Green, int Blue);
extern void ChangeActiveFloodColor(int Red, int Green, int Blue);
extern void ChangeActiveScreenColor(int Red, int Green, int Blue);
extern void init_penstate();
extern void init_bitmaps();
extern void uninit_bitmaps();
extern void init_turtles();
extern void uninit_turtles();
extern void init_videomode();
extern void ibmturt(bool hide);
extern void do_help(const wxString& arg);
extern void ibm_clear_screen(void);
extern int get_pen_width(void);
extern void set_pen_width(int w);
extern int get_pen_height(void);
extern void set_pen_height(int h);
extern void GetWorkingAreaDimensions(int & workingAreaWidth, int & workingAreaHeight);
extern struct PENSTATE & GetPenStateForSelectedTurtle();
extern void paste_all_turtles(class wxDC & DeviceContext, FLONUM zoom);
extern void exit_program();
extern void MyMessageScan(void);
extern void checkwindow(int *x, int *y, int *w, int *h);

#endif // __GRAPHWIN_H_
