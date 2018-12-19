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

#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#ifdef WX_PURE
   typedef unsigned int DWORD;
#else
   #include <windows.h>
#endif

#include <wx/defs.h>   // wxUint32
#include <wx/gdicmn.h> // wxPoint

#include "logocore.h"
#include "vector.h"
#include "3dsolid.h"

// types
struct Color
{
    int   red;
    int   green;
    int   blue;
};

struct PENSTATE
{
    int          Width;
    struct Color Color;

    // TODO: combine Mode and IsErasing
    int          Mode;
    bool         IsErasing;
};


struct LINEX
{
    wxPoint from;
    wxPoint to;
    bool    bValid;
};

struct Turtle
{
    MATRIX   Matrix;
    VECTOR   Position;
    FLONUM   Heading;
    DWORD    BitmapRasterMode; // 0 if not bitmapped.  Windows raster mode, otherwise.
    bool     IsShown;
    bool     IsPenUp;
    bool     IsSpecial;

    bool     IsSprite; // true if the bitmap rotates with the turtle, false otherwise.

    bool     HasOwnPenState;
    PENSTATE PenState;

    // a cache for lines that make up a turtle's body
    LINEX    Points[4];
};

// global variables
extern long vector_count;

// function declarations
extern wxUint32 GetColorArgument(NODE* args);

extern FIXNUM g_round(FLONUM n);
extern FLONUM numeric_node_to_flonum(const NODE* numeric_node);
extern FIXNUM numeric_node_to_fixnum(const NODE* numeric_node);
extern int GetSelectedTurtleIndex();
extern void InitializeTurtle(struct Turtle * TurtleToInitialize);
extern NODE *lscrunch(NODE *arg);
extern void draw_turtle(bool erase);
extern void draw_turtles(bool erase);
extern NODE *numeric_arg(NODE *args);
extern NODE *nonnegative_numeric_arg(NODE *args);
extern NODE *positive_numeric_arg(NODE *args);
extern NODE *lright(NODE *arg);
extern NODE *lleft(NODE *arg);
extern NODE *lrightroll(NODE *arg);
extern NODE *lleftroll(NODE *arg);
extern NODE *ldownpitch(NODE *arg);
extern NODE *luppitch(NODE *arg);
extern FLONUM rotation_z();
extern FLONUM rotation_y();
extern FLONUM rotation_x();
extern NODE *lforward(NODE *arg);
extern NODE *lback(NODE *arg);
extern NODE *lshowturtle(NODE *arg);
extern NODE *lhideturtle(NODE *arg);
extern NODE *lbitmapturtle(NODE *arg);
extern NODE *lnobitmapturtle(NODE *arg);
extern NODE *lshownp(NODE *arg);
extern NODE *lsetheading(NODE *arg);
extern NODE *lsetroll(NODE *arg);
extern NODE *lsetclip(NODE *arg);
extern NODE *lsetpitch(NODE *arg);
extern NODE *lsetturtle(NODE *arg);
extern NODE *lturtle(NODE *arg);
extern NODE *lturtles(NODE *arg);
extern NODE *lhasownpenp(NODE *arg);
extern NODE *lheading(NODE *arg);
extern NODE *lroll(NODE *arg);
extern NODE *lpitch(NODE *arg);
extern NODE *vector_arg(NODE *args);
extern NODE *int_vector_4_arg(NODE *args);
extern NODE *pos_int_vector_arg(NODE *args);
extern NODE *ltowards(NODE *args);
extern NODE *ltowardsxyz(NODE *args);
extern NODE *llight(NODE *arg);
extern NODE *lpos(NODE *arg);
extern NODE *lposxyz(NODE *arg);
extern NODE *lhome(NODE *arg);
extern NODE *lclearscreen(NODE *arg);
extern NODE *lclean(NODE *arg);
extern NODE *lsetlight(NODE *args);
extern NODE *lsetpos(NODE *args);
extern NODE *lsetposxyz(NODE *args);
extern NODE *lsetxy(NODE *args);
extern NODE *lsetxyz(NODE *args);
extern NODE *lellipsearc(NODE *args);
extern NODE *lsetx(NODE *args);
extern NODE *lsety(NODE *args);
extern NODE *lsetz(NODE *args);
extern NODE *lwrap(NODE *arg);
extern NODE *lfence(NODE *arg);
extern NODE *lwindow(NODE *arg);
extern NODE *lpolystart(NODE *arg);
extern NODE *lpolyend(NODE *arg);
extern NODE *lpolyview(NODE *arg);
extern NODE *lperspective(NODE *arg);
extern NODE *lfill(NODE *arg);
extern NODE *llabel(NODE *arg);
extern NODE *llabelsize(NODE *arg);
extern NODE *ltextscreen(NODE *arg);
extern NODE *lsplitscreen(NODE *arg);
extern NODE *lfullscreen(NODE *arg);
extern NODE *lpendownp(NODE *arg);
extern NODE *lpenmode(NODE *arg);
extern NODE *lpencolor(NODE *arg);
extern NODE *lpixel(NODE *arg);
extern NODE *lsetpixel(NODE *args);
extern NODE *lfloodcolor(NODE *arg);
extern NODE *lscreencolor(NODE *arg);
extern NODE *lpensize(NODE *arg);
extern NODE *lpenpattern(NODE *arg);
extern NODE *lpendown(NODE *arg);
extern NODE *lpenup(NODE *arg);
extern NODE *lpenpaint(NODE *arg);
extern NODE *lpenerase(NODE *arg);
extern NODE *lpenreverse(NODE *arg);
extern NODE *lclearpalette(NODE *arg);
extern NODE *lbitload(NODE *arg);
extern NODE *lbitloadsize(NODE *arg);
extern NODE *lbitsize(NODE *arg);
extern NODE *lbitsave(NODE *arg);
extern NODE *lgifsave(NODE *arg);
extern NODE *lgifload(NODE *arg);
extern NODE *lgifsize(NODE *arg);
extern NODE *lbitcut(NODE *arg);
extern NODE *lbitcopy(NODE *arg);
extern NODE *lbitpaste(NODE *arg);
extern NODE *lbitpastetoindex(NODE *arg);
extern NODE *lbitmode(NODE *arg);
extern NODE *lturtlemode(NODE *arg);
extern NODE *lmachine(NODE *arg);
extern NODE *lsetbitmode(NODE *arg);
extern NODE *lsetturtlemode(NODE *arg);
extern NODE *lbitindex(NODE *arg);
extern NODE *lsetbitindex(NODE *arg);
extern NODE *lbitfit(NODE *arg);
extern NODE *lbitblock(NODE *arg);
extern NODE *lscrollx(NODE *arg);
extern NODE *lscrolly(NODE *arg);
extern NODE *lsetpencolor(NODE *arg);
extern NODE *lsetfloodcolor(NODE *arg);
extern NODE *lsetscreencolor(NODE *arg);
extern NODE *lsetpensize(NODE *args);
extern NODE *lsetpenpattern(NODE *args);
extern NODE *lsetscrunch(NODE *args);
extern NODE *lmousepos(NODE *args);
extern NODE *lkeyboardvalue(NODE *args);
extern NODE *lbuttonp(NODE *args);
extern NODE *ltone(NODE *args);
extern void keyboard_uninit(void);
extern void mouse_uninit(void);

// global variables
extern mode_type   current_mode;

const int COLORTABLESIZE = 16;
extern const wxUint32 colortable[];

extern Turtle * g_Turtles;
extern int      g_MaxTurtle;        // the index of the largest real turtle
extern size_t   g_TurtlesLimit;     // the physical limit of g_Turtles
extern Turtle   g_SpecialTurtles[TOTAL_SPECIAL_TURTLES];
extern Turtle * g_SelectedTurtle;
extern Point    g_Wanna;

#endif // __GRAPHICS_H_
