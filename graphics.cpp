/*
 * graphics.cpp          logo graphics module          mak
 *
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
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

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <algorithm>
   #include <string.h>
   #include <math.h>
   #include <float.h>
   #include <limits.h>

   #include <wx/defs.h> // wxUint32

   #ifdef WX_PURE

      #include <wx/dc.h>
      #include <wx/dcmemory.h>

      struct LOGPEN;
      typedef struct __PEN * HPEN;
      typedef struct __HDC * HDC;

      #include "screen.h"
      #include "mainframe.h"

   #else // WX_PURE

      #include <windows.h>

      #ifdef max // MS compilers #define max in windows.h
         #undef max
      #endif
   #endif

   #include "FMSLogo.h"
   #include "wrksp.h"
   #include "graphics.h"
   #include "stringprintednode.h"
   #include "messagebox.h"
   #include "logodata.h"
   #include "init.h"
   #include "eval.h"
   #include "lists.h"
   #include "error.h"
   #include "ibmterm.h"
   #include "graphwin.h"
   #include "coms.h"
   #include "logomath.h"
   #include "const.h"
   #include "screenwindow.h"
   #include "startup.h"
//   #include "debugheap.h"

   #include "graphwin.h"
   #include "status.h"

   #include "localizedstrings.h"
#endif

#ifdef __GNUC__
   #define _finite(D) isfinite(D)
#endif

#define screen_left   (-BitMapWidth/2)
#define screen_right  ( BitMapWidth/2)
#define screen_bottom (-BitMapHeight/2)
#define screen_top    ( BitMapHeight/2)

#define turtle_left_max   (-BitMapWidth/2)
#define turtle_right_max  ( BitMapWidth/2)
#define turtle_bottom_max (-BitMapHeight/2)
#define turtle_top_max    ( BitMapHeight/2)

const wxUint32 colortable[] =
{
    0x00000000, // black
    0x00FF0000, // blue
    0x0000FF00, // green
    0x00FFFF00, // cyan
    0x000000FF, // red
    0x00FF00FF, // magenta
    0x0000FFFF, // yellow
    0x00FFFFFF, // white
    0x003B609B, // brown
    0x001288C5, // tan
    0x0040A264, // forest
    0x00BBBB78, // aqua
    0x007795FF, // salmon
    0x00D07190, // purple
    0x0000A3FF, // orange
    0x00B7B7B7, // grey
};

mode_type current_mode = wrapmode;

Turtle g_SpecialTurtles[TOTAL_SPECIAL_TURTLES];

Turtle * g_Turtles = 0;
size_t   g_TurtlesLimit = 0;

Turtle * g_SelectedTurtle = 0;
int      g_MaxTurtle = 0;

// a point where the turtle wants to go
Point  g_Wanna = {0.0, 0.0, 0.0};

long vector_count = 0;                 // current count of vectors drawn

// global store for x,y,z "From" routine
static Point  g_OldPos = {0.0, 0.0, 0.0};

// used to scale a picture in scrunch mode.
static VECTOR g_Scale = {1.0, 1.0, 1.0};

// 1 / g_Scale (replaces divides with multiplies)
static VECTOR g_OneOverScale  = {1.0, 1.0, 1.0}; 


static bool out_of_bounds = false;

#define sq(z) ((z)*(z))

struct NAMEDCOLOR
{
    const wxString& EnglishName;
	const wxString& LocalizedName;
    wxUint32        Color;
};


bool bIndexMode = false;

static bool        bPolyFlag  = false;
static VERTEXLIST* ThePolygon = NULL;

static void forward_helper(FLONUM d);

static
double positive_fmod(double x, double y)
{
    double temp = fmod(x, y);

    if (temp < 0.0)
    {
        return temp + y;
    }
    return temp;
}

// In non-expert mode, rounds a floating point to the nearest 1/1000000 of a whole number.
// This is used to snap a turtle's position into a more discrete number space in order to
// hide rounding errors caused by the impercision of FLONUM.
// For example, "FORWARD 500" shouldn't appear to make the turtle move 500.000000000001 steps.
static
FLONUM cut_error(FLONUM n)
{
    if (!bExpert)
    {
        n *= 1000000.0;
        n = (n > 0.0 ? floor(n) : ceil(n));
        n /= 1000000.0;
        if (n == -0.0) 
        {
            n = 0.0;
        }
    }

    return n;
}

FIXNUM g_round(FLONUM n)
{
    n += (n < 0.0 ? -0.5 : 0.5);

    if (n > (FLONUM) LONG_MAX)
    {
        return LONG_MAX;
    }
    else if (n < (FLONUM) LONG_MIN)
    {
        return LONG_MIN;
    }
    else
    {
        return (FIXNUM) n;
    }
}


FLONUM
numeric_node_to_flonum(
    const NODE * numeric_node
    )
{
    FLONUM number;

    if (nodetype(numeric_node) == INTEGER)
    {
        number = (FLONUM) getint(numeric_node);
    }
    else
    {
        assert(nodetype(numeric_node) == FLOATINGPOINT);
        number = getfloat(numeric_node);
    }

    return number;
}


FIXNUM 
numeric_node_to_fixnum(
    const NODE * numeric_node
    )
{
    FIXNUM number;

    if (nodetype(numeric_node) == INTEGER)
    {
        number = getint(numeric_node);
    }
    else
    {
        assert(nodetype(numeric_node) == FLOATINGPOINT);
        FLONUM flonum = getfloat(numeric_node);

        // A cast of a large floating point value to a FIXNUM
        // will crash when compiled with Borland C compiler.
        // To prevent this, we have special cases for floating
        // point values outside the range.
        // It's impossible to give a correct FIXNUM for this
        // value, so it's a bug if this happens (the caller
        // should have thrown a "doesn't like input" error.
        assert(-FIXNUM_MAX < flonum && flonum < FIXNUM_MAX);

        if (flonum >= FIXNUM_MAX)
        {
            number = FIXNUM_MAX;
        }
        else if (flonum <= -FIXNUM_MAX)
        {
            number = -FIXNUM_MAX;
        }
        else
        {
            number = static_cast<FIXNUM>(getfloat(numeric_node));
        }
    }

    return number;
}

/************************************************************/
int GetSelectedTurtleIndex()
{
    int selectedTurtleIndex;

    if (g_SelectedTurtle->IsSpecial)
    {
        // this is one of the special turtles (below 0)
        // remap the position within the array <0, 1, 2> to <-1, -2, -3>.
        selectedTurtleIndex = g_SpecialTurtles - g_SelectedTurtle - 1;
    }
    else
    {
        // this is a normal turtle
        selectedTurtleIndex = g_SelectedTurtle - g_Turtles;
    }

    return selectedTurtleIndex;
}

void InitializeTurtle(Turtle * TurtleToInitialize)
{
    TurtleToInitialize->Position.x = 0.0;
    TurtleToInitialize->Position.y = 0.0;
    TurtleToInitialize->Position.z = 0.0;

    TurtleToInitialize->Heading    = 0.0;

    TurtleToInitialize->BitmapRasterMode = 0;

    TurtleToInitialize->IsShown    = true;
    TurtleToInitialize->IsPenUp    = false;
    TurtleToInitialize->IsSpecial  = false;

    TurtleToInitialize->IsSprite   = false;
    TurtleToInitialize->HasOwnPenState = false;

    // initialize to default color
    TurtleToInitialize->PenState.Color.red   = 0x00;
    TurtleToInitialize->PenState.Color.green = 0x00;
    TurtleToInitialize->PenState.Color.blue  = 0x00;
    TurtleToInitialize->PenState.Width     = 1;
    TurtleToInitialize->PenState.Mode      = COPY_PUT;
    TurtleToInitialize->PenState.IsErasing = false;

    TurtleToInitialize->Matrix.e11 = 1.0;
    TurtleToInitialize->Matrix.e12 = 0.0;
    TurtleToInitialize->Matrix.e13 = 0.0;
    TurtleToInitialize->Matrix.e21 = 0.0;
    TurtleToInitialize->Matrix.e22 = 1.0;
    TurtleToInitialize->Matrix.e23 = 0.0;
    TurtleToInitialize->Matrix.e31 = 0.0;
    TurtleToInitialize->Matrix.e32 = 0.0;
    TurtleToInitialize->Matrix.e33 = 1.0;

    TurtleToInitialize->Points[0].bValid = false;
    TurtleToInitialize->Points[1].bValid = false;
    TurtleToInitialize->Points[2].bValid = false;
    TurtleToInitialize->Points[3].bValid = false;
}

void draw_turtles(bool draw)
{
    Turtle * savedSelectedTurtle = g_SelectedTurtle;

    for (g_SelectedTurtle = g_Turtles;
         g_SelectedTurtle <= g_Turtles + g_MaxTurtle;
         g_SelectedTurtle++)
    {
        draw_turtle(draw);
    }

    g_SelectedTurtle = savedSelectedTurtle;
}

void draw_turtle(bool draw)
{
    if (g_SelectedTurtle->IsSpecial)
    {
        // either the eye, the eye fixation, or the light turtle is selected
        ThreeD.SetFrom();
        ThreeD.SetAt();
        ThreeD.SetUp();
        ThreeD.SetVolume();
        ThreeD.SetEye();
        ThreeD.SetLight();
        // if (ThreeD.Tree) ThreeD.View();

        // special turtles are never drawn
        return;
    }

    if (g_SelectedTurtle->IsShown)
    {
        ibmturt(draw);
    }
}

/************************************************************/

static
void
transline_helper(
    const LOGPEN & LogicalPen,
    HPEN           Pen,
    int            LineMode,
    int            FromX,
    int            FromY,
    int            ToX,
    int            ToY
    )
{
    // Convert from Cartesian coordinates to logical window coordinates.
    FromX =  FromX + xoffset;
    FromY = -FromY + yoffset;
    ToX   =  ToX   + xoffset;
    ToY   = -ToY   + yoffset;

#ifdef WX_PURE
    if (!zoom_flag)
    {
        // Draw the line in the memory back buffer.
        CScreen * screen = CFmsLogo::GetMainFrame()->GetScreen();
        wxMemoryDC & memoryDeviceContext = screen->GetMemoryDeviceContext();
        memoryDeviceContext.DrawLine(FromX, FromY, ToX, ToY);

        // Determine the part of the screen that we need to invalidate so that the
	// memory device context is copied to the screen.
        wxRect screenRect;
        if (FromX < ToX)
        {
            screenRect.x      = FromX;
            screenRect.width  = ToX - FromX;
        }
        else
        {
            screenRect.x      = ToX;
            screenRect.width  = FromX - ToX;
        }

        if (FromY < ToY)
        {
            screenRect.y      = FromY;
            screenRect.height = ToY - FromY;
        }
        else
        {
            screenRect.y      = ToY;
            screenRect.height = FromY - ToY;
        }

        // Invalidate enough to cover the thickness of the pen
	PENSTATE & penState = GetPenStateForSelectedTurtle();
	screenRect.Inflate(penState.Width);

        // Reposition the invalidated rectangle, accounting for scrolling.
        const int scrollerX = GetScreenHorizontalScrollPosition();
        const int scrollerY = GetScreenVerticalScrollPosition();
        screenRect.Offset(-scrollerX, -scrollerY);

	screen->RefreshRect(screenRect, false);
    }
#else
    HDC MemDC = GetMemoryDeviceContext();

    SetROP2(MemDC, LineMode);

    HPEN oldPen = (HPEN) SelectObject(MemDC, Pen);

    MoveToEx(MemDC, FromX, FromY, 0);
    LineTo(MemDC, ToX, ToY);

    // HACK:
    // LineTo() API does not draw a pixel in the location where it moves to.
    // As a result, moving forward changing colors, then moving backward leaves
    // a dot of the previous color at the location where the direction changed.
    // To address this, we SetPixel to color the end point.
    //
    // This isn't necessary when the pensize != 1.
    // This would be bad to do in penreverse mode.
    //
    PENSTATE & penState = GetPenStateForSelectedTurtle();
    if (penState.Width < 2 && penState.Mode != XOR_PUT)
    {
        SetPixel(MemDC, ToX, ToY, LogicalPen.lopnColor);
    }

    // restore the previous bitmap and pen
    SelectObject(MemDC, oldPen);


    // update the screen
    if (zoom_flag)
    {
        // We are zoomed, so it would be very difficult to just
        // draw the line on the screen.  Instead, invalidate the
        // portion of the screen window that corresponds
        // to the region containing the line which we just drew.
        RECT screenRect;
        if (FromX < ToX)
        {
            screenRect.left   = FromX - penState.Width;
            screenRect.right  = ToX   + penState.Width;
        }
        else
        {
            screenRect.left   = ToX    - penState.Width;
            screenRect.right  = FromX  + penState.Width;
        }

        if (FromY < ToY)
        {
            screenRect.top    = FromY - penState.Width;
            screenRect.bottom = ToY   + penState.Width;
        }
        else
        {
            screenRect.top    = ToY   - penState.Width;
            screenRect.bottom = FromY + penState.Width;
        }

        // remap the screen rectangle based on the zoom factor
        screenRect.left   *= the_zoom;
        screenRect.right  *= the_zoom;
        screenRect.top    *= the_zoom;
        screenRect.bottom *= the_zoom;

        const UINT scrollerX = GetScreenHorizontalScrollPosition();
        const UINT scrollerY = GetScreenVerticalScrollPosition();

        screenRect.left   -= scrollerX;
        screenRect.right  -= scrollerX;
        screenRect.top    -= scrollerY;
        screenRect.bottom -= scrollerY;

        InvalidateRect(GetScreenWindow(), &screenRect, false);
    }
    else
    {
        // We are not zoomed.
        // Draw the line directly on the screen, rather than invalidating
        // the region containing the line because doing is 400% faster
        // on the squiral benchmark.
        HDC ScreenDC = GetScreenDeviceContext();
        SetROP2(ScreenDC, LineMode);

        oldPen = (HPEN) SelectObject(ScreenDC, Pen);

        UINT screenFromX = FromX - GetScreenHorizontalScrollPosition();
        UINT screenFromY = FromY - GetScreenVerticalScrollPosition();

        UINT screenToX   = ToX   - GetScreenHorizontalScrollPosition();
        UINT screenToY   = ToY   - GetScreenVerticalScrollPosition();

        MoveToEx(ScreenDC, screenFromX, screenFromY, 0);
        LineTo(ScreenDC, screenToX, screenToY);

        PENSTATE & penState = GetPenStateForSelectedTurtle();
        if (penState.Width < 2 && penState.Mode != XOR_PUT)
        {
            SetPixel(ScreenDC, screenFromX, screenFromY, LogicalPen.lopnColor);
        }

        // restore the previous pen
        SelectObject(ScreenDC, oldPen);
    }
#endif
}

static
void 
transline3d(
    const LOGPEN &logPen, 
    HPEN         &pen, 
    long          modex, 
    const Point & from,
    const Point & to
    )
{
    // First, project the point from world coordinates to
    // window coordinates.
    VECTOR from3d;
    from3d.x = from.x / WorldWidth;
    from3d.y = from.y / WorldHeight;
    from3d.z = from.z / WorldDepth;

    VECTOR to3d;
    to3d.x = to.x / WorldWidth;
    to3d.y = to.y / WorldHeight;
    to3d.z = to.z / WorldDepth;

    if (bPolyFlag)
    {
        if (!ThePolygon ||
            (fabs(ThePolygon->Vertex.x - to3d.x) > FLONUM_EPSILON) ||
            (fabs(ThePolygon->Vertex.y - to3d.y) > FLONUM_EPSILON) ||
            (fabs(ThePolygon->Vertex.z - to3d.z) > FLONUM_EPSILON))
        {
            ThreeD.AddPoint(&ThePolygon, to3d);
        }
    }

    wxPoint from2d;
    wxPoint to2d;
    if (!ThreeD.TransformSegment(from3d, to3d, from2d, to2d))
    {
        return;
    }

    // Now that we have projected this line into the
    // window coordinates, we can call the 2D version to
    // actually draw the line.
    transline_helper(
        logPen,
        pen,
        modex,
        from2d.x,
        from2d.y,
        to2d.x,
        to2d.y);
}

static
void 
transline(
    const LOGPEN &logPen, 
    HPEN         &pen, 
    long          modex, 
    const Point & from,
    const Point & to
    )
{
    transline_helper(
        logPen,
        pen,
        modex,
        g_round(from.x),
        g_round(from.y),
        g_round(to.x),
        g_round(to.y));
}


static
void move_to(FLONUM x, FLONUM y)
{
    g_OldPos.x = x;
    g_OldPos.y = y;
}

static
void move_to_3d(FLONUM x, FLONUM y, FLONUM z)
{
    g_OldPos.x = x;
    g_OldPos.y = y;
    g_OldPos.z = z;
}

static
void line_to(FLONUM x, FLONUM y)
{
    if (g_SelectedTurtle->IsSpecial)
    {
        // special turtles don't draw lines when they move
        return;
    }

    if (!g_SelectedTurtle->IsPenUp)
    {
        vector_count++;
        update_status_vectors();

        Point toPoint;
        toPoint.x = x;
        toPoint.y = y;

        HPEN           pen = 0;
        const LOGPEN * logicalPen = 0;
        int            rasterMode = 0;
#ifndef WX_PURE
        if (GetPenStateForSelectedTurtle().IsErasing)
        {
            pen        = g_ErasePen;
            logicalPen = &g_LogicalErasePen;
            rasterMode = R2_COPYPEN;
        }
        else
        {
            pen        = g_NormalPen;
            logicalPen = &g_LogicalNormalPen;

            if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
            {
                rasterMode = R2_NOT;
            }
            else
            {
                rasterMode = R2_COPYPEN;
            }
        }
#endif
        transline(
            *logicalPen,
            pen,
            rasterMode,
            g_OldPos,
            toPoint);
    }
}

static
void line_to_3d(const Point & ToPoint)
{
    if (g_SelectedTurtle->IsSpecial)
    {
        // special turtles don't draw lines when they move
        return;
    }

    if (!g_SelectedTurtle->IsPenUp)
    {
        vector_count++;
        update_status_vectors();

        HPEN           pen = 0;
        const LOGPEN * logicalPen =0;
        int            rasterMode = 0;

#ifndef WX_PURE
        if (GetPenStateForSelectedTurtle().IsErasing)
        {
            pen        = g_ErasePen;
            logicalPen = &g_LogicalErasePen;
            rasterMode = R2_COPYPEN;
        }
        else
        {
            pen        = g_NormalPen;
            logicalPen = &g_LogicalNormalPen;

            if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
            {
                rasterMode = R2_NOT;
            }
            else
            {
                rasterMode = R2_COPYPEN;
            }
        }
#endif

        transline3d(
            *logicalPen,
            pen,
            rasterMode,
            g_OldPos,
            ToPoint);
    }
}


static
void uppitch(FLONUM a)
{

//  if (bPolyFlag)
//  {
//      bPolyFlag = false;
//      ThreeD.DisposeVertices(ThePolygon);
//      ThePolygon = NULL;
//      ShowMessageAndStop("Pitch Error", "You cannot change pitch while defining a planar polygon");
//  }
//  else
    {
        draw_turtle(false);

        a = positive_fmod(a, 360.0);
        FLONUM Cx = cos(a * rads_per_degree);
        FLONUM Sx = sin(a * rads_per_degree);

        MATRIX pitch;
        pitch.e11 = 1.0; pitch.e12 = 0.0; pitch.e13 = 0.0;
        pitch.e21 = 0.0; pitch.e22 = Cx;  pitch.e23 = -Sx;
        pitch.e31 = 0.0; pitch.e32 = Sx;  pitch.e33 = Cx;

        g_SelectedTurtle->Matrix = MMMultiply(
            g_SelectedTurtle->Matrix,
            pitch);

        update_status_turtleheading();
        update_status_turtlepitch();
        update_status_turtleroll();

        draw_turtle(true);
    }
}

static
void rightroll(FLONUM a)
{
//  if (bPolyFlag)
//  {
//      bPolyFlag = false;
//      ThreeD.DisposeVertices(ThePolygon);
//      ThePolygon = NULL;
//      ShowMessageAndStop("Roll Error", "You cannot change roll while defining a planar polygon");
//  }
//  else
    {
        draw_turtle(false);

        a = positive_fmod(a, 360.0);
        FLONUM Cy = cos(a * rads_per_degree);
        FLONUM Sy = sin(a * rads_per_degree);

        MATRIX roll;
        roll.e11 = Cy;  roll.e12 = 0.0; roll.e13 = Sy;
        roll.e21 = 0.0; roll.e22 = 1.0; roll.e23 = 0.0;
        roll.e31 = -Sy; roll.e32 = 0.0; roll.e33 = Cy;

        g_SelectedTurtle->Matrix = MMMultiply(
            g_SelectedTurtle->Matrix,
            roll);

        update_status_turtleheading();
        update_status_turtlepitch();
        update_status_turtleroll();

        draw_turtle(true);
    }
}

static
void right_helper(FLONUM a)
{
    draw_turtle(false);
   
    a = positive_fmod(a, 360.0);
    g_SelectedTurtle->Heading += a;
    g_SelectedTurtle->Heading = positive_fmod(g_SelectedTurtle->Heading, 360.0);

    if (current_mode == perspectivemode)
    {
        FLONUM Cz = cos(-a * rads_per_degree);
        FLONUM Sz = sin(-a * rads_per_degree);

        MATRIX turn;
        turn.e11 = Cz;  turn.e12 = -Sz; turn.e13 = 0.0;
        turn.e21 = Sz;  turn.e22 = Cz;  turn.e23 = 0.0;
        turn.e31 = 0.0; turn.e32 = 0.0; turn.e33 = 1.0;

        g_SelectedTurtle->Matrix = MMMultiply(
            g_SelectedTurtle->Matrix,
            turn);
    }

    update_status_turtleheading();
    update_status_turtlepitch();
    update_status_turtleroll();

    draw_turtle(true);
}

// If the first element in args can be interpreted as a number
// then it is changed into an numeric node and returned.
// The programmer is given the opportunity to fix bad arguments using ERRACT.
NODE *numeric_arg(NODE *args)
{
    NODE *arg = car(args);

    NODE * val = cnv_node_to_numnode(arg);
    while (val == Unbound && NOT_THROWING)
    {
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
        val = cnv_node_to_numnode(arg);
    }
    setcar(args, val);
    return val;
}

// If the first element in args can be interpreted as a non-negative number
// then it is changed into a non-negative numeric node and returned.
// The programmer is given the opportunity to fix bad arguments using ERRACT.
NODE *nonnegative_numeric_arg(NODE *args)
{
    NODE *arg = car(args);

    NODE * val = cnv_node_to_numnode(arg);
    while (NOT_THROWING && 
           (val == Unbound || numeric_node_to_flonum(val) < 0))
    {
        // The arg node is either non-numeric or negative.
        // Try to get a different value.
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
        val = cnv_node_to_numnode(arg);
    }
    setcar(args, val);
    return val;
}

// If the first element in args can be interpreted as a positive number
// then it is changed into a positive numeric node and returned.
// The programmer is given the opportunity to fix bad arguments using ERRACT.
NODE *positive_numeric_arg(NODE *args)
{
    NODE *arg = car(args);

    NODE * val = cnv_node_to_numnode(arg);
    while (NOT_THROWING && 
           (val == Unbound || numeric_node_to_flonum(val) <= 0))
    {
        // The arg node is either non-numeric or not positive.
        // Try to get a different value.
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
        val = cnv_node_to_numnode(arg);
    }
    setcar(args, val);
    return val;
}

NODE *luppitch(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        uppitch(a);
    }
    return Unbound;
}

NODE *ldownpitch(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        uppitch(-a);
    }

    return Unbound;
}

NODE *lrightroll(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        rightroll(a);
    }

    return Unbound;
}

NODE *lleftroll(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        rightroll(-a);
    }
    return Unbound;
}

NODE *lright(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        right_helper(a);
    }

    return Unbound;
}

NODE *lleft(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        right_helper(-a);
    }

    return Unbound;
}

static
FLONUM towards_helper(FLONUM x, FLONUM y, FLONUM from_x, FLONUM from_y)
{
    FLONUM tx = from_x * g_OneOverScale.x;
    FLONUM ty = from_y * g_OneOverScale.y;

    if (x != tx || y != ty)
    {
        FLONUM a;
        if (x == tx)
        {
            a = (y < ty) ? -90 : 90;
        }
        else
        {
            FLONUM slope = (y - ty) / (x - tx);
            a = atan(slope) * degrees_per_rad;
            if (x < tx) 
            {
                a = fmod(a + 180.0, 360.0);
            }
        }
        a = 90.0 - a;
        return a < 0 ? 360.0 + a : a;
    }

    return 0.0;
}

static
void 
setpos_helper_2d(
    FLONUM x, 
    FLONUM y
    )
{
    assert(current_mode != perspectivemode);

    move_to(
        g_SelectedTurtle->Position.x,
        g_SelectedTurtle->Position.y);

    Point target;
    target.x = x;
    target.y = y;

    Point scaled;
    scaled.x = target.x * g_Scale.x;
    scaled.y = target.y * g_Scale.y;

    bool wrapping =
        scaled.x > turtle_right_max ||
        scaled.x < turtle_left_max ||
        scaled.y > turtle_top_max ||
        scaled.y < turtle_bottom_max;

    if ((current_mode == fencemode) && wrapping)
    {
        err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
    }
    else if ((current_mode == wrapmode) && (wrapping || out_of_bounds))
    {
        FLONUM save_heading = g_SelectedTurtle->Heading;

        g_SelectedTurtle->Heading = towards_helper(
            target.x,
            target.y, 
            g_Wanna.x, 
            g_Wanna.y);

        FLONUM tx = g_Wanna.x * g_OneOverScale.x;
        FLONUM ty = g_Wanna.y * g_OneOverScale.y;
        forward_helper(sqrt(sq(target.x - tx) + sq(target.y - ty)));

        g_SelectedTurtle->Heading = save_heading;
        g_Wanna.x = scaled.x;
        g_Wanna.y = scaled.y;
        out_of_bounds = wrapping;
    }
    else
    {
        g_Wanna.x = g_SelectedTurtle->Position.x = scaled.x;
        g_Wanna.y = g_SelectedTurtle->Position.y = scaled.y;
        out_of_bounds = false;
        line_to(
            g_SelectedTurtle->Position.x, 
            g_SelectedTurtle->Position.y);
        update_status_turtleposition();
    }
}

static
void 
setpos_helper_3d(
    FLONUM x, 
    FLONUM y,
    FLONUM z
    )
{
    assert(current_mode == perspectivemode);

    move_to_3d(
        g_SelectedTurtle->Position.x,
        g_SelectedTurtle->Position.y,
        g_SelectedTurtle->Position.z);

    Point target;
    target.x = x;
    target.y = y;
    target.z = z;

    g_Wanna = g_SelectedTurtle->Position = target;
    out_of_bounds = false;
    line_to_3d(g_SelectedTurtle->Position);
    update_status_turtleposition();
}

static
void 
setpos_helper(
    NODE *xnode, 
    NODE *ynode, 
    NODE *znode
    )
{
    if (NOT_THROWING)
    {
        draw_turtle(false);

        Point target;
        target.x = (xnode == NIL) ?
            g_SelectedTurtle->Position.x :
            numeric_node_to_flonum(xnode);

        target.y = (ynode == NIL) ?
            g_SelectedTurtle->Position.y :
            numeric_node_to_flonum(ynode);

        target.z = (znode == NIL) ?
            g_SelectedTurtle->Position.z :
            numeric_node_to_flonum(znode);

        if (current_mode == perspectivemode)
        {
            setpos_helper_3d(target.x, target.y, target.z);
        }
        else
        {
            setpos_helper_2d(target.x, target.y);
        }

        draw_turtle(true);
    }
}

NODE *lellipsearc(NODE *arg)
{
    bool pen_state = g_SelectedTurtle->IsPenUp;

    // get args
    FLONUM angle      = float_arg(arg);
    FLONUM radius_x   = float_arg(cdr(arg));
    FLONUM radius_y   = float_arg(cdr(cdr(arg)));
    FLONUM startangle = float_arg(cdr(cdr(cdr(arg))));

    if (NOT_THROWING)
    {
        draw_turtle(false);

        if (360.0 < fabs(angle))
        {
            // the angle is either greater than 360 or less than -360. 
            // To speed things up, we limit it to just 360.
            // This also fixes a crash (floating-point exception) for large angles.
            angle = 360.0;
        }

        // save and force turtle state
        bool turtle_state = g_SelectedTurtle->IsShown;
        g_SelectedTurtle->IsShown = false;

        // grab things before they change and use for restore
        FLONUM th = g_SelectedTurtle->Heading;
        FLONUM tx = g_SelectedTurtle->Position.x;
        FLONUM ty = g_SelectedTurtle->Position.y;
        FLONUM tz = g_SelectedTurtle->Position.z;

        // calculate resolution parameters
        FLONUM flt_count = fabs(angle * std::max(radius_x, radius_y) / 200.0);
        FIXNUM count;
        if (flt_count < 1.0)
        {
            // very small radius or angle
            count = 1;
        }
        else if (flt_count > (FLONUM)(FIXNUM_MAX))
        {
            // a degenerate case - very large radius
            // it's okay to limit the count because the arc is 
            // too large to draw correctly, anyway.
            count = FIXNUM_MAX;
        }
        else
        { 
            // a normal radius/angle.
            count = static_cast<FIXNUM>(flt_count);
        }
        FLONUM delta = angle / count;

        // jump to begin of first line segment without drawing
        g_SelectedTurtle->IsPenUp = true;

        if (current_mode == perspectivemode)
        {
            // 3D mode
            VECTOR r;
            VECTOR rp;

            // iterate based on count, instead of on "ang"
            // because angle may be negative.
            FLONUM ang = startangle;
            for (FIXNUM i = 0; i <= count; i++)
            {
                // calc x y
                FLONUM x = -sin(ang * rads_per_degree) * radius_x;
                FLONUM y = -cos(ang * rads_per_degree) * radius_y;

                // rotate delta point according to roll around y axis
                r.x = x;
                r.y = y;

                rp = MVxyMultiply(g_SelectedTurtle->Matrix, r);

                setpos_helper_3d(
                    tx + rp.x,
                    ty + rp.y,
                    tz + rp.z);
            
                // restore pen (in case saved)
                g_SelectedTurtle->IsPenUp = pen_state;

                ang += delta;

                // every now and then, check for a HALT message
                if (check_stop(true))
                {
                    break;
                }
            }

            // restore pen (in case saved)
            g_SelectedTurtle->IsPenUp = pen_state;
         
            // assure we draw something and end in the exact right place
            FLONUM endangle = startangle + angle;
            r.x = -sin(endangle * rads_per_degree) * radius_x;
            r.y = -cos(endangle * rads_per_degree) * radius_y;

            rp = MVxyMultiply(g_SelectedTurtle->Matrix, r);
         
            setpos_helper_3d(
                tx + rp.x,
                ty + rp.y,
                tz + rp.z);
        }
        else
        {
            // 2D mode
            const FLONUM cos_th = cos(th * rads_per_degree);
            const FLONUM sin_th = sin(th * rads_per_degree);

            // draw each line segment of arc (will do wrap)
            FLONUM ang = startangle;
            for (FIXNUM i = 0; i <= count; i++)
            {
                // calc x y
                FLONUM x = -sin(ang * rads_per_degree) * radius_x;
                FLONUM y = -cos(ang * rads_per_degree) * radius_y;

                // now rotate about position
                FLONUM rx =  sin_th * y + cos_th * x;
                FLONUM ry = -sin_th * x + cos_th * y;

                setpos_helper_2d(
                    tx + rx,
                    ty + ry);

                // restore pen (in case saved)
                g_SelectedTurtle->IsPenUp = pen_state;

                ang += delta;

                // every now and then, check for a HALT message
                if (check_stop(true))
                {
                    break;
                }
            }

            // restore pen (in case saved)
            g_SelectedTurtle->IsPenUp = pen_state;

            // assure we draw something and end in the exact right place
            FLONUM endangle = startangle + angle;
            FLONUM x = -sin(endangle * rads_per_degree) * radius_x;
            FLONUM y = -cos(endangle * rads_per_degree) * radius_y;

            // now rotate about position
            FLONUM rx =  sin_th * y + cos_th * x;
            FLONUM ry = -sin_th * x + cos_th * y;

            setpos_helper_2d(
                tx + rx,
                ty + ry);
        }

        // restore state
        g_SelectedTurtle->IsShown = turtle_state;

        g_SelectedTurtle->Position.x = tx;
        g_SelectedTurtle->Position.y = ty;
        g_SelectedTurtle->Position.z = tz;

        update_status_turtleposition();

        draw_turtle(true);
        g_Wanna = g_SelectedTurtle->Position;
        out_of_bounds = false;
    }

    return Unbound;
}


static
bool wrap_right(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
{
    if (screen_right < cut_error(x2))
    {
        // The turtle position moves past the right of the right-most pixel.
        // We need to wrap around to the left.

        // Compute the Y position where the line intersects the right border.
        FLONUM yi = ((y2 - y1) / (x2 - x1)) * (screen_right - x1) + y1;
        if (screen_bottom <= yi && yi <= screen_top)
        {
            // The Y intersection position is within the boundaries so we can draw
            // the line and continue forward movement from the left of the screen.
            line_to(screen_right, yi);
            update_status_turtleposition();
            g_SelectedTurtle->Position.x = turtle_left_max;
            g_SelectedTurtle->Position.y = yi;
            if (current_mode == wrapmode)
            {
                forward_helper(d * ((x2 - screen_right) / (x2 - x1)));
                return true;
            }
            // We are in fence mode
            g_SelectedTurtle->Position.x = turtle_right_max;
            err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
        }
    }
    return false;
}

static
bool wrap_up(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
{
    if (screen_top < cut_error(y2))
    {
        // The turtle position moves past the top of the top-most pixel.
        // We need to wrap around to the bottom.
        
        // Compute the X position where the line intersects the top border.
        FLONUM xi = ((x2 - x1) / (y2 - y1)) * (screen_top - y1) + x1;
        if (screen_left <= xi && xi <= screen_right)
        {
            // The X intersection position is within the boundaries so we can draw
            // the line and continue forward movement from the bottom of the screen.
            line_to(xi, screen_top);
            update_status_turtleposition();
            g_SelectedTurtle->Position.x = xi;
            g_SelectedTurtle->Position.y = turtle_bottom_max;
            if (current_mode == wrapmode)
            {
                forward_helper(d * ((y2 - screen_top) / (y2 - y1)));
                return true;
            }
            // We are in fence mode
            g_SelectedTurtle->Position.y = turtle_top_max;
            err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
        }
    }
    return false;
}

static
bool wrap_left(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
{
    if (cut_error(x2) < screen_left)
    {
        // The turtle position moves past the left of the left-most pixel.
        // We need to wrap around to the right.

        // Compute the Y position where the line intersects the left border.
        FLONUM yi = ((y2 - y1) / (x1 - x2)) * (x1 - screen_left) + y1;
        if (screen_bottom <= yi && yi <= screen_top)
        {
            // The Y intersection position is within the boundaries so we can draw
            // the line and continue forward movement from the right of the screen.
            line_to(screen_left, yi);
            update_status_turtleposition();
            g_SelectedTurtle->Position.x = turtle_right_max;
            g_SelectedTurtle->Position.y = yi;
            if (current_mode == wrapmode)
            {
                forward_helper(d * ((screen_left - x2) / (x1 - x2)));
                return true;
            }
            // We are in fence mode
            g_SelectedTurtle->Position.x = turtle_left_max;
            err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
        }
    }
    return false;
}

static
bool wrap_down(FLONUM d, FLONUM x1, FLONUM y1, FLONUM x2, FLONUM y2)
{
    if (cut_error(y2) < screen_bottom)
    {
        // The turtle position moves past the bottom of the bottom-most pixel.
        // We need to wrap around to the top.

        // Compute the X position where the line intersects the bottom.
        FLONUM xi = ((x2 - x1) / (y1 - y2)) * (y1 - screen_bottom) + x1;
        if (screen_left <= xi && xi <= screen_right)
        {
            // The X intersection position is within the boundaries so we can draw
            // the line and continue forward movement from the top of the screen.
            line_to(xi, screen_bottom);
            update_status_turtleposition();
            g_SelectedTurtle->Position.x = xi;
            g_SelectedTurtle->Position.y = turtle_top_max;
            if (current_mode == wrapmode)
            {
                forward_helper(d * ((screen_bottom - y2) / (y1 - y2)));
                return true;
            }
            // We are in fence mode.
            g_SelectedTurtle->Position.y = turtle_bottom_max;
            err_logo(TURTLE_OUT_OF_BOUNDS, NIL);
        }
    }
    return false;
}

void forward_helper(FLONUM d)
{
    static int forward_count = 0; // DELETEME

    if ((forward_count > 32) || !_finite(d))
    {
        return;
    }

    forward_count++;

    // Convert to the "real" heading (the way cos() and sin() want them).
    // Note that we should add 90 degrees, but instead we use trig identities
    // to make that unnecessary.
    FLONUM heading_minus_ninety = g_SelectedTurtle->Heading * rads_per_degree;

    FLONUM x1 = g_SelectedTurtle->Position.x;
    FLONUM y1 = g_SelectedTurtle->Position.y;
    FLONUM dx = sin(heading_minus_ninety) * d * g_Scale.x;
    FLONUM dy = cos(heading_minus_ninety) * d * g_Scale.y;
    FLONUM x2 = x1 + dx;
    FLONUM y2 = y1 + dy;

    move_to(x1, y1);

    // if (check_throwing) return;
    // if (stopping_flag == THROWING) return;

    if (current_mode == windowmode ||
        (screen_left   <= cut_error(x2) && cut_error(x2) <= screen_right &&
         screen_bottom <= cut_error(y2) && cut_error(y2) <= screen_top))
    {
        // no wrapping/fencing needed
        g_SelectedTurtle->Position.x = x2;
        g_SelectedTurtle->Position.y = y2;
        line_to(x2, y2);
        update_status_turtleposition();
    }
    else
    {
        // wrapping/fencing is needed
        if (!wrap_right(d, x1, y1, x2, y2))
            if (!wrap_left(d, x1, y1, x2, y2))
                if (!wrap_up(d, x1, y1, x2, y2))
                    wrap_down(d, x1, y1, x2, y2);
    }

    forward_count--;
}

static
void forward_helper3d(FLONUM d)
{
    VECTOR direction;

    move_to_3d(
        g_SelectedTurtle->Position.x, 
        g_SelectedTurtle->Position.y, 
        g_SelectedTurtle->Position.z);

    direction.x = 0.0;
    direction.y = d;
    direction.z = 0.0;

    direction = MVyMultiply(g_SelectedTurtle->Matrix, direction);

    g_SelectedTurtle->Position.x += direction.x;
    g_SelectedTurtle->Position.y += direction.y;
    g_SelectedTurtle->Position.z += direction.z;

    line_to_3d(g_SelectedTurtle->Position);
    update_status_turtleposition();
}

static
void forward(FLONUM d)
{
    draw_turtle(false);
    if (current_mode == perspectivemode) 
    {
        forward_helper3d(d);
    }
    else
    {
        forward_helper(d);
    }

    draw_turtle(true);
    g_Wanna = g_SelectedTurtle->Position;
    out_of_bounds = false;
}

NODE *lforward(NODE *arg)
{
    FLONUM d = float_arg(arg);
    if (NOT_THROWING)
    {
        forward(d);
    }
    return Unbound;
}

NODE *lback(NODE *arg)
{
    FLONUM d = float_arg(arg);
    if (NOT_THROWING)
    {
        forward(-d);
    }
    return Unbound;
}

NODE *lbitmapturtle(NODE * arg)
{
    bool rotatingBitmap = false;
    if (arg != NULL)
    {
        rotatingBitmap = boolean_arg(arg);
    }
    if (rotatingBitmap)
    {
        int turtleIndex = GetSelectedTurtleIndex();

        if (turtleIndex < 0)
        {
            // It is non-sensisical to try to map a bitmap
            // one of the "special" turtles that are never
            // rendered, but used to control 3D modes.
            err_logo(
                INVALID_STATE_FOR_INSTRUCTION,
                cons_list(make_strnode(GetResourceString(L"LOCALIZED_ERROR_BITMAPSPECIALTUTRLE"))));
        }
        else if (turtleIndex == 0)
        {
            // In order to implement rotating bitmaps efficiently,
            // the pixels are read from the HBITMAP into a buffer
            // and cached.  This is not possible to do with the
            // clipboard bitmap, since it can change without
            // notifying us.
            err_logo(
                INVALID_STATE_FOR_INSTRUCTION,
                cons_list(make_strnode(GetResourceString(L"LOCALIZED_ERROR_BITMAPCLIPBOARD"))));
        }
    }

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    draw_turtle(false);
#ifndef WX_PURE
    g_SelectedTurtle->BitmapRasterMode = SRCCOPY;
#endif
    g_SelectedTurtle->IsSprite         = rotatingBitmap;
    draw_turtle(true);
    return Unbound;
}

NODE *lnobitmapturtle(NODE *)
{
    draw_turtle(false);
    g_SelectedTurtle->BitmapRasterMode = 0;
    g_SelectedTurtle->IsSprite         = false;
    draw_turtle(true);
    return Unbound;
}

NODE *lshowturtle(NODE *)
{
    if (!g_SelectedTurtle->IsShown)
    {
        g_SelectedTurtle->IsShown = true;
        update_status_turtlevisability();
        draw_turtle(true);
    }
    return Unbound;
}

NODE *lhideturtle(NODE *)
{
    if (g_SelectedTurtle->IsShown)
    {
        draw_turtle(false);
        g_SelectedTurtle->IsShown = false;
        update_status_turtlevisability();
    }
    return Unbound;
}

NODE *lshownp(NODE *)
{
    return true_or_false(g_SelectedTurtle->IsShown);
}

NODE *lsetheading(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        draw_turtle(false);

        a = positive_fmod(a, 360.0);

        if (current_mode == perspectivemode)
        {
            right_helper(a - rotation_z());
        }
        else
        {
            g_SelectedTurtle->Heading = a;
        }

        update_status_turtleheading();
        update_status_turtlepitch();
        update_status_turtleroll();

        draw_turtle(true);
    }
    return Unbound;
}

NODE *lsetroll(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        draw_turtle(false);

        a -= rotation_y();
        a = positive_fmod(a, 360.0);
        rightroll(a);

        update_status_turtleheading();
        update_status_turtlepitch();
        update_status_turtleroll();

        draw_turtle(true);
    }
    return Unbound;
}

NODE *lsetpitch(NODE *arg)
{
    FLONUM a = float_arg(arg);
    if (NOT_THROWING)
    {
        draw_turtle(false);

        a -= rotation_x();
        a = positive_fmod(a, 360.0);
        uppitch(a);

        update_status_turtleheading();
        update_status_turtlepitch();
        update_status_turtleroll();

        draw_turtle(true);
    }
    return Unbound;
}

NODE *lsetclip(NODE *args)
{
    FLONUM angle = float_arg(args);
    FLONUM zmin = float_arg(cdr(args));
    FLONUM zmax = float_arg(cdr(cdr(args)));

    if (NOT_THROWING)
    {
        draw_turtle(false);
        ThreeD.SetClip(angle, zmin, zmax);
        draw_turtle(true);
    }

    return Unbound;
}

static
FLONUM
normalize_angle(
    FLONUM  Angle
    )
{
    double angle = fmod(Angle, 360.0);

    if (fabs(angle) < FLONUM_EPSILON) 
    {
        return 0.0; 
    }
    else if (fabs(angle - 360.0) < FLONUM_EPSILON) 
    {
        return 0.0; 
    }
    else if (angle < 0.0) 
    {
        return angle + 360.0; 
    }
    else 
    {
        return angle;
    }
}

/* rotations such that heading has no dependencies */
FLONUM rotation_z()
{
    FLONUM m11 = g_SelectedTurtle->Matrix.e11;
    FLONUM m12 = g_SelectedTurtle->Matrix.e12;
    FLONUM m21 = g_SelectedTurtle->Matrix.e21;
    FLONUM m22 = g_SelectedTurtle->Matrix.e22;
    FLONUM m23 = g_SelectedTurtle->Matrix.e23;

    FLONUM result;

    if ((1.0 - fabs(m23)) < FLONUM_EPSILON)
    {
        result = atan2(m12, m11) * degrees_per_rad;
    }
    else
    {
        result = atan2(-m21, m22) * degrees_per_rad;
    }

    return normalize_angle(result);
}

FLONUM rotation_y()
{
    FLONUM m13 = g_SelectedTurtle->Matrix.e13;
    FLONUM m23 = g_SelectedTurtle->Matrix.e23;
    FLONUM m33 = g_SelectedTurtle->Matrix.e33;

    FLONUM result;

    if ((1.0 - fabs(m23)) < FLONUM_EPSILON)
    {
        return 0.0;
    }
    else
    {
        result = atan2(m13, m33) * degrees_per_rad;
    }

    return normalize_angle(result);
}

FLONUM rotation_x()
{
    FLONUM m13 = g_SelectedTurtle->Matrix.e13;
    FLONUM m23 = g_SelectedTurtle->Matrix.e23;
    FLONUM m33 = g_SelectedTurtle->Matrix.e33;

    FLONUM result;

    if ((1.0 - fabs(m23)) < FLONUM_EPSILON)
    {
        return (m23 < 0.0) ? 90.0 : 270.0;
    }
    else
    {
        FLONUM ry = atan2(-m13, m33);

        FLONUM a;
        if (fabs(fabs(ry) - 90.0 * rads_per_degree) < FLONUM_EPSILON)
        {
            a = m13 / sin(-ry);
        }
        else
        {
            a = m33 / cos(ry);
        }

        result = atan2(-m23, a) * degrees_per_rad;
    }

    return normalize_angle(result);
}

NODE *lheading(NODE *)
{
    FLONUM heading;

    if (current_mode == perspectivemode)
    {
        heading = rotation_z();
    }
    else
    {
        heading = g_SelectedTurtle->Heading;
    }

    return make_floatnode(heading);
}

NODE *lroll(NODE *)
{
    FLONUM roll;

    if (current_mode == perspectivemode)
    {
        roll = rotation_y();
    }
    else
    {
        roll = 0.0;
    }

    return make_floatnode(roll);
}

NODE *lpitch(NODE *)
{
    FLONUM pitch;

    if (current_mode == perspectivemode)
    {
        pitch = rotation_x();
    }
    else
    {
        pitch = 0.0;
    }

    return make_floatnode(pitch);
}

// returns true if the node is zero or positive.
// returns false, otherwise
static
bool
NumericNodeIsNotNegative(
    const NODE * NumericNode
    )
{
    assert(nodetype(NumericNode) == INTEGER || nodetype(NumericNode) == FLOATINGPOINT);

    if (nodetype(NumericNode) == INTEGER && getint(NumericNode) >= 0)
    {
        return true;
    }

    if (nodetype(NumericNode) == FLOATINGPOINT && getfloat(NumericNode) >= 0.0)
    {
        return true;
    }

    return false;
}

static NODE *vec_arg_helper(NODE *Arguments, bool NegativeIsOk)
{
    NODE *arg = car(Arguments);

    while (NOT_THROWING)
    {
        if (arg != NIL &&
            is_list(arg) &&
            cdr(arg) != NIL &&
            cddr(arg) == NIL)
        {

            NODE * val1 = cnv_node_to_numnode(car(arg));
            NODE * val2 = cnv_node_to_numnode(cadr(arg));

            if (val1 != Unbound && 
                val2 != Unbound && (
                    NegativeIsOk || (
                        NumericNodeIsNotNegative(val1) && 
                        NumericNodeIsNotNegative(val2))))
            {
                setcar(arg, val1);
                setcar(cdr(arg), val2);
                return (arg);
            }
            gcref(val1);
            gcref(val2);
        }
        setcar(Arguments, err_logo(BAD_DATA, arg));
        arg = car(Arguments);
    }
    return Unbound;
}

// Verfies that the first item in args is a list of four nodes that can be
// converted into integer nodes.  If so, it converts each of them to an
// integer node and return the list of four.
//
// If not, it returns Unbound.
//
// The programmer is given the opportunity to fix bad arguments using ERRACT.
NODE * int_vector_4_arg(NODE *args)
{
    NODE *arg = car(args);

    while (NOT_THROWING)
    {
        if (arg != NIL &&
            is_list(arg) &&
            cdr(arg) != NIL &&
            cdr(cdr(arg)) != NIL &&
            cdr(cdr(cdr(arg))) != NIL &&
            cdr(cdr(cdr(cdr(arg)))) == NIL)
        {
            // We have a list of four nodes.
            // Try to convert each of them to an integer.
            NODE* int1 = cnv_node_to_intnode(car(arg));
            NODE* int2 = cnv_node_to_intnode(car(cdr(arg)));
            NODE* int3 = cnv_node_to_intnode(car(cdr(cdr(arg))));
            NODE* int4 = cnv_node_to_intnode(car(cdr(cdr(cdr(arg)))));
            if (int1 != Unbound &&
                int2 != Unbound &&
                int3 != Unbound &&
                int4 != Unbound)
            {
                // Success.
                // Replace each of the nodes with its integer equivalent.
                setcar(arg, int1);
                setcar(cdr(arg), int2);
                setcar(cdr(cdr(arg)), int3);
                setcar(cdr(cdr(cdr(arg))), int4);
                return arg;
            }

            // Clean up and try again.
            gcref(int1);
            gcref(int2);
            gcref(int3);
            gcref(int4);
        }

        // This is not a vector of four integer nodes.
        // Throw a recoverable bad data error to give the programmer
        // a chance to replace it with good data.
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }

    // The input is bad.
    return Unbound;
}

NODE *vector_arg(NODE *args)
{
    return vec_arg_helper(args, true);
}

static NODE *vector_3_arg(NODE *args)
{
    NODE *arg = car(args);

    while (NOT_THROWING)
    {
        if (arg != NIL &&
            is_list(arg) &&
            cdr(arg) != NIL &&
            cddr(arg) != NIL &&
            cddr(cdr(arg)) == NIL)
        {
            NODE * val1 = cnv_node_to_numnode(car(arg));
            NODE * val2 = cnv_node_to_numnode(cadr(arg));
            NODE * val3 = cnv_node_to_numnode(cadr(cdr(arg)));
            if (val1 != Unbound && val2 != Unbound && val3 != Unbound)
            {
                setcar(arg, val1);
                setcar(cdr(arg), val2);
                setcar(cddr(arg), val3);
                return arg;
            }

            gcref(val1);
            gcref(val2);
            gcref(val3);
        }
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }

    return Unbound;
}

NODE *pos_int_vector_arg(NODE *args)
{
    return vec_arg_helper(args, false);
}

NODE *ltowards(NODE *args)
{
    NODE * arg = vector_arg(args);
    if (NOT_THROWING)
    {
        NODE * xnode = car(arg);
        NODE * ynode = cadr(arg);

        FLONUM x = numeric_node_to_flonum(xnode);
        FLONUM y = numeric_node_to_flonum(ynode);

        FLONUM heading = towards_helper(
            x, 
            y, 
            g_SelectedTurtle->Position.x, 
            g_SelectedTurtle->Position.y);

        return make_floatnode(heading);
    }

    return Unbound;
}

NODE *ltowardsxyz(NODE *args)
{
    NODE * arg = vector_3_arg(args);
    if (NOT_THROWING)
    {
        NODE * xnode = car(arg);
        NODE * ynode = cadr(arg);
        NODE * znode = cadr(cdr(arg));

        VECTOR to;
        to.x = numeric_node_to_flonum(xnode);
        to.y = numeric_node_to_flonum(ynode);
        to.z = numeric_node_to_flonum(znode);

        // Generate a Vector to represent direction we need to head
        VECTOR diff = Subtract(to, g_SelectedTurtle->Position);
        Normalize(diff);

        // Compute angle between Y Axis and Vector [DOT] (Rotation about Z)
        FLONUM Rz = acos(diff.y) * degrees_per_rad;

        // Project point onto X-Z plane and renormalize to measure roll
        diff.y = 0.0;
        Normalize(diff);

        // Compute angle between X Axis and Projection [DOT] (Rotation about Y)
        FLONUM Ry = acos(diff.x) * degrees_per_rad;

        // Heading was limited to 0 to 180 but we must be able to roll -180 to 180
        // if point is in positive Z hemisphere then "roll" left to it.
        if (diff.z > 0.0) 
        {
            Ry = -Ry;
        }

        // No Pitch needed
        FLONUM Rx = 0.0;

        return cons_list(
            make_floatnode(Ry),
            make_floatnode(Rx),
            make_floatnode(Rz));
    }

    return Unbound;
}

NODE *lpos(NODE *)
{
    return cons_list(
        make_floatnode(cut_error(g_SelectedTurtle->Position.x * g_OneOverScale.x)),
        make_floatnode(cut_error(g_SelectedTurtle->Position.y * g_OneOverScale.y)));
}

NODE *lposxyz(NODE *)
{
    return cons_list(
        make_floatnode(cut_error(g_SelectedTurtle->Position.x * g_OneOverScale.x)),
        make_floatnode(cut_error(g_SelectedTurtle->Position.y * g_OneOverScale.y)),
        make_floatnode(cut_error(g_SelectedTurtle->Position.z * g_OneOverScale.z)));
}

NODE *lscrunch(NODE *)
{
    return cons_list(
        make_floatnode(g_Scale.x),
        make_floatnode(g_Scale.y));
}

NODE *lhome(NODE *)
{
    NODE *zero;

    out_of_bounds = false;
    zero = make_intnode((FIXNUM) 0);
    setpos_helper(zero, zero, zero);
    gcref(zero);

    draw_turtle(false);
    g_SelectedTurtle->Heading = 0.0;
    g_SelectedTurtle->Matrix.e11 = 1.0;
    g_SelectedTurtle->Matrix.e12 = 0.0;
    g_SelectedTurtle->Matrix.e13 = 0.0;
    g_SelectedTurtle->Matrix.e21 = 0.0;
    g_SelectedTurtle->Matrix.e22 = 1.0;
    g_SelectedTurtle->Matrix.e23 = 0.0;
    g_SelectedTurtle->Matrix.e31 = 0.0;
    g_SelectedTurtle->Matrix.e32 = 0.0;
    g_SelectedTurtle->Matrix.e33 = 1.0;
    draw_turtle(true);

    update_status_turtleheading();
    update_status_turtlepitch();
    update_status_turtleroll();

    return Unbound;
}

static
void cs_helper(bool centerp, bool clearp)
{
    bPolyFlag = false;
    ThreeD.DisposeVertices(ThePolygon);
    ThePolygon = NULL;
    ThreeD.DisposeTree();

    update_status_vectors();

    if (clearp) 
    {
        erase_screen();
    }

    if (centerp)
    {
        // remove all turtles other than the first one
        g_Turtles        = (Turtle*) realloc(g_Turtles, sizeof(*g_Turtles));
        g_TurtlesLimit   = 1;
        g_SelectedTurtle = &g_Turtles[0];
        g_MaxTurtle      = 0;

        const bool isShown = g_SelectedTurtle->IsShown;
        const bool isPenUp = g_SelectedTurtle->IsPenUp;

        InitializeTurtle(g_SelectedTurtle);

        g_SelectedTurtle->IsShown = isShown;
        g_SelectedTurtle->IsPenUp = isPenUp;

        g_Wanna.x = 0.0;
        g_Wanna.y = 0.0;
        g_Wanna.z = 0.0;

        update_status_turtleheading();
        update_status_turtleposition();
        update_status_turtleroll();
        update_status_turtlepitch();
        update_status_turtlewhich();

        out_of_bounds = false;
    }
    draw_turtle(true);
}

NODE *lclearscreen(NODE *)
{
    cs_helper(true, true);
    return Unbound;
}

NODE *lclean(NODE *)
{
    cs_helper(false, true);
    return Unbound;
}

NODE *lsetpos(NODE *args)
{
    NODE *arg = vector_arg(args);

    if (NOT_THROWING)
    {
        setpos_helper(car(arg), cadr(arg), NIL);
    }
    return Unbound;
}

NODE *lsetposxyz(NODE *args)
{
    NODE *arg = vector_3_arg(args);

    if (NOT_THROWING)
    {
        setpos_helper(car(arg), cadr(arg), cadr(cdr(arg)));
    }
    return Unbound;
}

NODE *lsetxy(NODE *args)
{
    NODE * xnode = numeric_arg(args);
    NODE * ynode = numeric_arg(cdr(args));
    if (NOT_THROWING)
    {
        setpos_helper(xnode, ynode, NIL);
    }
    return Unbound;
}

NODE *lsetxyz(NODE *args)
{
    NODE * xnode = numeric_arg(args);
    NODE * ynode = numeric_arg(cdr(args));
    NODE * znode = numeric_arg(cdr(cdr(args)));
    if (NOT_THROWING)
    {
        setpos_helper(xnode, ynode, znode);
    }
    return Unbound;
}

NODE *lsetx(NODE *args)
{
    NODE * xnode = numeric_arg(args);
    if (NOT_THROWING)
    {
        setpos_helper(xnode, NIL, NIL);
    }
    return Unbound;
}

NODE *lsety(NODE *args)
{
    NODE * ynode = numeric_arg(args);
    if (NOT_THROWING)
    {
        setpos_helper(NIL, ynode, NIL);
    }
    return Unbound;
}

NODE *lsetz(NODE *args)
{
    NODE *znode = numeric_arg(args);
    if (NOT_THROWING)
    {
        setpos_helper(NIL, NIL, znode);
    }
    return Unbound;
}

NODE *lwrap(NODE *)
{
    draw_turtle(false);
    cs_helper(true, false);
    current_mode = wrapmode;
    draw_turtle(true);
    return Unbound;
}

NODE *lfence(NODE *)
{
    draw_turtle(false);
    current_mode = fencemode;
    draw_turtle(true);
    return Unbound;
}

NODE *lwindow(NODE *)
{
    draw_turtle(false);
    current_mode = windowmode;
    draw_turtle(true);

    return Unbound;
}

NODE *lsetlight(NODE *args)
{
    NODE * arg = vector_arg(args);
    if (NOT_THROWING)
    {
        NODE * ambient = car(arg);
        NODE * diffuse = cadr(arg);

        ThreeD.m_Ambient = numeric_node_to_flonum(ambient);
        ThreeD.m_Diffuse = numeric_node_to_flonum(diffuse);

        if (ThreeD.m_Tree)
        {
            ThreeD.View();
        }
    }

    return Unbound;
}

NODE *llight(NODE *)
{
    return cons_list(
        make_floatnode(ThreeD.m_Ambient),
        make_floatnode(ThreeD.m_Diffuse));
}

NODE *lpolystart(NODE *)
{
    if (bPolyFlag)
    {
        bPolyFlag = false;
        ThreeD.DisposeVertices(ThePolygon);
        ThePolygon = NULL;
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_POLYSTART"), 
			GetResourceString(L"LOCALIZED_ERROR_POLYSTARTALREADYSTARTED"));
    }
    else
    {
        bPolyFlag = true;
    }

    return Unbound;
}

NODE *lpolyview(NODE *)
{
    if (ThreeD.m_Tree) 
    {
        ThreeD.View();
    }

    return Unbound;
}

NODE *lpolyend(NODE *)
{
    if (bPolyFlag)
    {
        if (ThePolygon &&                         // polygon was started
            ThePolygon != ThePolygon->Next &&     // at least one vertex
            ThePolygon != ThePolygon->Next->Next) // at least two vertices
        {
            // There are at least three vertices in the polygon.
            ThreeD.AddPolygon(ThePolygon, pcolor);
        }
        else
        {
            // The polygon doesn't have three vertices.
            ThreeD.DisposeVertices(ThePolygon);
            ThePolygon = NULL;
            ShowMessageAndStop(
                GetResourceString(L"LOCALIZED_ERROR_POLYEND"),
                GetResourceString(L"LOCALIZED_ERROR_POLYENDNEED3VECTORS"));
        }
    }
    else
    {
        ThreeD.DisposeVertices(ThePolygon);
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_POLYEND"),
			GetResourceString(L"LOCALIZED_ERROR_POLYENDNOTSTARTED"));
    }

    ThePolygon = NULL;
    bPolyFlag = false;

    return Unbound;
}

NODE *lperspective(NODE *)
{
    draw_turtle(false);
    current_mode = perspectivemode;

    // From
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Position.x = 400.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Position.y = 400.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Position.z = 600.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Heading = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e11 = 1.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e12 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e13 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e21 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e22 = 1.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e23 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e31 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e32 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Matrix.e33 = 1.0;

    // At
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Position.x = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Position.y = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Position.z = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Heading = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e11 = 1.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e12 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e13 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e21 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e22 = 1.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e23 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e31 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e32 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix.e33 = 1.0;

    // Light
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Position.x = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Position.y = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Position.z = 1000.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Heading = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e11 = 1.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e12 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e13 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e21 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e22 = 1.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e23 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e31 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e32 = 0.0;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Matrix.e33 = 1.0;

    ThreeD.SetLight();
    ThreeD.SetFrom();
    ThreeD.SetAt();
    ThreeD.SetUp();
    ThreeD.SetVolume();
    ThreeD.SetEye();
    ThreeD.SetClip(60.0, 100000.0, -100000.0);
    if (ThreeD.m_Tree)
    {
        ThreeD.View();
    }

    draw_turtle(true);
    return Unbound;
}

NODE *lfill(NODE *arg)
{
    bool fillUntilPenColor;
    if (arg != NIL)
    {
        fillUntilPenColor = boolean_arg(arg);
    }
    else
    {
        fillUntilPenColor = false;
    }

    draw_turtles(false);

    logofill(fillUntilPenColor);

    draw_turtles(true);

    return Unbound;
}

NODE *llabelsize(NODE *arg)
{
#ifndef WX_PURE
    CStringPrintedNode textbuf(car(arg), CStringPrintedNode::WithPrintLimits);

    if (NOT_THROWING)
    {
        SIZE size = labelsize(textbuf);
        return cons_list(
            make_intnode((FIXNUM) size.cx),
            make_intnode((FIXNUM) size.cy));
    }
#endif
    return Unbound;
}

NODE *llabel(NODE *arg)
{
#ifndef WX_PURE
    // print the node as a string
    CStringPrintedNode textbuf(car(arg), CStringPrintedNode::WithPrintLimits);

    if (NOT_THROWING)
    {
        draw_turtle(false);
        label(textbuf);
        draw_turtle(true);
    }
#endif
    return Unbound;
}

NODE *ltextscreen(NODE *)
{
    UndockCommanderWindow();
    return Unbound;
}

NODE *lsplitscreen(NODE *)
{
    DockCommanderWindow();
    return Unbound;
}

NODE *lfullscreen(NODE *)
{
    UndockCommanderWindow();
    return Unbound;
}

NODE *lpendownp(NODE *)
{
    return true_or_false(!g_SelectedTurtle->IsPenUp);
}

NODE *lpenmode(NODE *)
{
    return get_node_pen_mode();
}

NODE *lpensize(NODE *)
{
    return cons_list(
        make_intnode((FIXNUM) get_pen_width()),
        make_intnode((FIXNUM) get_pen_height()));
}

NODE *lpenpattern(NODE *)
{
    return get_node_pen_pattern();
}

NODE *lpendown(NODE *)
{
    g_SelectedTurtle->IsPenUp = false;
    update_status_pencontact();
    return Unbound;
}

NODE *lpenup(NODE *)
{
    g_SelectedTurtle->IsPenUp = true;
    update_status_pencontact();
    return Unbound;
}

NODE *lpenpaint(NODE *)
{
    pen_down();
    update_status_penstyle();
    return lpendown(NIL);
}

NODE *lpenerase(NODE *)
{
    pen_erase();
    update_status_penstyle();
    return lpendown(NIL);
}

NODE *lpenreverse(NODE *)
{
    pen_reverse();
    update_status_penstyle();
    return lpendown(NIL);
}

typedef 
int 
(*COMPAREFUNC) (
    const wchar_t * StringA, 
    const wchar_t * StringB,
    int          CompareLength
    );

static
bool
StringNodeEqualsString(
    NODE       * StringNode,
    const wchar_t * String,
    COMPAREFUNC  CompareFunc
    )
{
    assert(is_string(StringNode));

    int stringLength = wcslen(String);

    if (stringLength != getstrlen(StringNode))
    {
        // the strings aren't even the same length--they can't be the same
        return false;
    }
    else
    {
        // the strings are the same length, so we must compare them
        return 0 == CompareFunc(getstrptr(StringNode), String, stringLength);
    }
}

// Gets an integral value from 0-255 from Node, or returns
// -1 if this cannot be done.
static
int
GetColorComponent(
    NODE * Node
    )
{
    if (Node == NIL)
    {
        return -1;
    }

    NODE * value = cnv_node_to_numnode(Node);
    if (value == Unbound)
    {
        return -1;
    }
 
    // initialize the return value to indicates an error.
    int colorComponent = -1;

    if (nodetype(value) == FLOATINGPOINT)
    {
        // We got a floating point value.
        FLONUM flonum = getfloat(value);
        if (0 <= flonum && flonum <= FIXNUM_MAX)
        {
            colorComponent = g_round(flonum) % 256;
        }
    }
    else if (nodetype(value) == INTEGER)
    {
        // We got an integer.
        int i = getint(value);
        if (0 <= i)
        {
            colorComponent = i % 256;
        }
    }

    gcref(value);
    return colorComponent;
}

wxUint32
GetColorArgument(
    NODE* args
    )
{

	static const NAMEDCOLOR g_NamedColors[] =
	{
		{L"AliceBlue",             GetResourceString(L"LOCALIZED_COLOR_ALICEBLUE"),             0x00FFF8F0},
		{L"AntiqueWhite",          GetResourceString(L"LOCALIZED_COLOR_ANTIQUEWHITE"),          0x00D7EBFA},
		{L"Aqua",                  GetResourceString(L"LOCALIZED_COLOR_AQUA"),                  0x00FFFF00},
		{L"Aquamarine",            GetResourceString(L"LOCALIZED_COLOR_AQUAMARINE"),            0x00D4FF7F},
		{L"Azure",                 GetResourceString(L"LOCALIZED_COLOR_AZURE"),                 0x00FFFFF0},
		{L"Beige",                 GetResourceString(L"LOCALIZED_COLOR_BEIGE"),                 0x00DCF5F5},
		{L"Bisque",                GetResourceString(L"LOCALIZED_COLOR_BISQUE"),                0x00C4E4FF},
		{L"Black",                 GetResourceString(L"LOCALIZED_COLOR_BLACK"),                 0x00000000},
		{L"BlanchedAlmond",        GetResourceString(L"LOCALIZED_COLOR_BLANCHEDALMOND"),        0x00CDEBFF},
		{L"Blue",                  GetResourceString(L"LOCALIZED_COLOR_BLUE"),                  0x00FF0000},
		{L"BlueViolet",            GetResourceString(L"LOCALIZED_COLOR_BLUEVIOLET"),            0x00E22B8A},
		{L"Brown",                 GetResourceString(L"LOCALIZED_COLOR_BROWN"),                 0x002A2AA5},
		{L"BurlyWood",             GetResourceString(L"LOCALIZED_COLOR_BURLYWOOD"),             0x0087B8DE},
		{L"CadetBlue",             GetResourceString(L"LOCALIZED_COLOR_CADETBLUE"),             0x00A09E5F},
		{L"Chartreuse",            GetResourceString(L"LOCALIZED_COLOR_CHARTREUSE"),            0x0000FF7F},
		{L"Chocolate",             GetResourceString(L"LOCALIZED_COLOR_CHOCOLATE"),             0x001E69D2},
		{L"Coral",                 GetResourceString(L"LOCALIZED_COLOR_CORAL"),                 0x00507FFF},
		{L"CornflowerBlue",        GetResourceString(L"LOCALIZED_COLOR_CORNFLOWERBLUE"),        0x00ED9564},
		{L"Cornsilk",              GetResourceString(L"LOCALIZED_COLOR_CORNSILK"),              0x00DCF8FF},
		{L"Crimson",               GetResourceString(L"LOCALIZED_COLOR_CRIMSON"),               0x003C14DC},
		{L"Cyan",                  GetResourceString(L"LOCALIZED_COLOR_CYAN"),                  0x00FFFF00},
		{L"DarkBlue",              GetResourceString(L"LOCALIZED_COLOR_DARKBLUE"),              0x008B0000},
		{L"DarkCyan",              GetResourceString(L"LOCALIZED_COLOR_DARKCYAN"),              0x008B8B00},
		{L"DarkGoldenRod",         GetResourceString(L"LOCALIZED_COLOR_DARKGOLDENROD"),         0x000B86B8},
		{L"DarkGray",              GetResourceString(L"LOCALIZED_COLOR_DARKGRAY"),              0x00A9A9A9},
		{L"DarkGreen",             GetResourceString(L"LOCALIZED_COLOR_DARKGREEN"),             0x00006400},
		{L"DarkGrey",              GetResourceString(L"LOCALIZED_COLOR_DARKGREY"),              0x00A9A9A9},
		{L"DarkKhaki",             GetResourceString(L"LOCALIZED_COLOR_DARKKHAKI"),             0x006BB7BD},
		{L"DarkMagenta",           GetResourceString(L"LOCALIZED_COLOR_DARKMAGENTA"),           0x008B008B},
		{L"DarkOliveGreen",        GetResourceString(L"LOCALIZED_COLOR_DARKOLIVEGREEN"),        0x002F6B55},
		{L"DarkOrange",            GetResourceString(L"LOCALIZED_COLOR_DARKORANGE"),            0x00008CFF},
		{L"DarkOrchid",            GetResourceString(L"LOCALIZED_COLOR_DARKORCHID"),            0x00CC3299},
		{L"DarkRed",               GetResourceString(L"LOCALIZED_COLOR_DARKRED"),               0x0000008B},
		{L"DarkSalmon",            GetResourceString(L"LOCALIZED_COLOR_DARKSALMON"),            0x007A96E9},
		{L"DarkSeaGreen",          GetResourceString(L"LOCALIZED_COLOR_DARKSEAGREEN"),          0x008FBC8F},
		{L"DarkSlateBlue",         GetResourceString(L"LOCALIZED_COLOR_DARKSLATEBLUE"),         0x008B3D48},
		{L"DarkSlateGray",         GetResourceString(L"LOCALIZED_COLOR_DARKSLATEGRAY"),         0x004F4F2F},
		{L"DarkSlateGrey",         GetResourceString(L"LOCALIZED_COLOR_DARKSLATEGREY"),         0x004F4F2F},
		{L"DarkTurquoise",         GetResourceString(L"LOCALIZED_COLOR_DARKTURQUOISE"),         0x00D1CE00},
		{L"DarkViolet",            GetResourceString(L"LOCALIZED_COLOR_DARKVIOLET"),            0x00D30094},
		{L"DeepPink",              GetResourceString(L"LOCALIZED_COLOR_DEEPPINK"),              0x009314FF},
		{L"DeepSkyBlue",           GetResourceString(L"LOCALIZED_COLOR_DEEPSKYBLUE"),           0x00FFBF00},
		{L"DimGray",               GetResourceString(L"LOCALIZED_COLOR_DIMGRAY"),               0x00696969},
		{L"DimGrey",               GetResourceString(L"LOCALIZED_COLOR_DIMGREY"),               0x00696969},
		{L"DodgerBlue",            GetResourceString(L"LOCALIZED_COLOR_DODGERBLUE"),            0x00FF901E},
		{L"FireBrick",             GetResourceString(L"LOCALIZED_COLOR_FIREBRICK"),             0x002222B2},
		{L"FloralWhite",           GetResourceString(L"LOCALIZED_COLOR_FLORALWHITE"),           0x00F0FAFF},
		{L"ForestGreen",           GetResourceString(L"LOCALIZED_COLOR_FORESTGREEN"),           0x00228B22},
		{L"Fuchsia",               GetResourceString(L"LOCALIZED_COLOR_FUCHSIA"),               0x00FF00FF},
		{L"Gainsboro",             GetResourceString(L"LOCALIZED_COLOR_GAINSBORO"),             0x00DCDCDC},
		{L"GhostWhite",            GetResourceString(L"LOCALIZED_COLOR_GHOSTWHITE"),            0x00FFF8F8},
		{L"Gold",                  GetResourceString(L"LOCALIZED_COLOR_GOLD"),                  0x0000D7FF},
		{L"GoldenRod",             GetResourceString(L"LOCALIZED_COLOR_GOLDENROD"),             0x0020A5DA},
		{L"Gray",                  GetResourceString(L"LOCALIZED_COLOR_GRAY"),                  0x00808080},
		{L"Green",                 GetResourceString(L"LOCALIZED_COLOR_GREEN"),                 0x00008000},
		{L"GreenYellow",           GetResourceString(L"LOCALIZED_COLOR_GREENYELLOW"),           0x002FFFAD},
		{L"Grey",                  GetResourceString(L"LOCALIZED_COLOR_GREY"),                  0x00808080},
		{L"HoneyDew",              GetResourceString(L"LOCALIZED_COLOR_HONEYDEW"),              0x00F0FFF0},
		{L"HotPink",               GetResourceString(L"LOCALIZED_COLOR_HOTPINK"),               0x00B469FF},
		{L"IndianRed",             GetResourceString(L"LOCALIZED_COLOR_INDIANRED"),             0x005C5CCD},
		{L"Indigo",                GetResourceString(L"LOCALIZED_COLOR_INDIGO"),                0x0082004B},
		{L"Ivory",                 GetResourceString(L"LOCALIZED_COLOR_IVORY"),                 0x00F0FFFF},
		{L"Khaki",                 GetResourceString(L"LOCALIZED_COLOR_KHAKI"),                 0x008CE6F0},
		{L"Lavender",              GetResourceString(L"LOCALIZED_COLOR_LAVENDER"),              0x00FAE6E6},
		{L"LavenderBlush",         GetResourceString(L"LOCALIZED_COLOR_LAVENDERBLUSH"),         0x00F5F0FF},
		{L"LawnGreen",             GetResourceString(L"LOCALIZED_COLOR_LAWNGREEN"),             0x0000FC7C},
		{L"LemonChiffon",          GetResourceString(L"LOCALIZED_COLOR_LEMONCHIFFON"),          0x00CDFAFF},
		{L"LightBlue",             GetResourceString(L"LOCALIZED_COLOR_LIGHTBLUE"),             0x00E6D8AD},
		{L"LightCoral",            GetResourceString(L"LOCALIZED_COLOR_LIGHTCORAL"),            0x008080F0},
		{L"LightCyan",             GetResourceString(L"LOCALIZED_COLOR_LIGHTCYAN"),             0x00FFFFE0},
		{L"LightGoldenRodYellow",  GetResourceString(L"LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW"),  0x00D2FAFA},
		{L"LightGray",             GetResourceString(L"LOCALIZED_COLOR_LIGHTGRAY"),             0x00D3D3D3},
		{L"LightGreen",            GetResourceString(L"LOCALIZED_COLOR_LIGHTGREEN"),            0x0090EE90},
		{L"LightGrey",             GetResourceString(L"LOCALIZED_COLOR_LIGHTGREY"),             0x00D3D3D3},
		{L"LightPink",             GetResourceString(L"LOCALIZED_COLOR_LIGHTPINK"),             0x00C1B6FF},
		{L"LightSalmon",           GetResourceString(L"LOCALIZED_COLOR_LIGHTSALMON"),           0x007AA0FF},
		{L"LightSeaGreen",         GetResourceString(L"LOCALIZED_COLOR_LIGHTSEAGREEN"),         0x00AAB220},
		{L"LightSkyBlue",          GetResourceString(L"LOCALIZED_COLOR_LIGHTSKYBLUE"),          0x00FACE87},
		{L"LightSlateGray",        GetResourceString(L"LOCALIZED_COLOR_LIGHTSLATEGRAY"),        0x00998877},
		{L"LightSlateGrey",        GetResourceString(L"LOCALIZED_COLOR_LIGHTSLATEGREY"),        0x00998877},
		{L"LightSteelBlue",        GetResourceString(L"LOCALIZED_COLOR_LIGHTSTEELBLUE"),        0x00DEC4B0},
		{L"LightYellow",           GetResourceString(L"LOCALIZED_COLOR_LIGHTYELLOW"),           0x00E0FFFF},
		{L"Lime",                  GetResourceString(L"LOCALIZED_COLOR_LIME"),                  0x0000FF00},
		{L"LimeGreen",             GetResourceString(L"LOCALIZED_COLOR_LIMEGREEN"),             0x0032CD32},
		{L"Linen",                 GetResourceString(L"LOCALIZED_COLOR_LINEN"),                 0x00E6F0FA},
		{L"Magenta",               GetResourceString(L"LOCALIZED_COLOR_MAGENTA"),               0x00FF00FF},
		{L"Maroon",                GetResourceString(L"LOCALIZED_COLOR_MAROON"),                0x00000080},
		{L"MediumAquaMarine",      GetResourceString(L"LOCALIZED_COLOR_MEDIUMAQUAMARINE"),      0x00AACD66},
		{L"MediumBlue",            GetResourceString(L"LOCALIZED_COLOR_MEDIUMBLUE"),            0x00CD0000},
		{L"MediumOrchid",          GetResourceString(L"LOCALIZED_COLOR_MEDIUMORCHID"),          0x00D355BA},
		{L"MediumPurple",          GetResourceString(L"LOCALIZED_COLOR_MEDIUMPURPLE"),          0x00D87093},
		{L"MediumSeaGreen",        GetResourceString(L"LOCALIZED_COLOR_MEDIUMSEAGREEN"),        0x0071B33C},
		{L"MediumSlateBlue",       GetResourceString(L"LOCALIZED_COLOR_MEDIUMSLATEBLUE"),       0x00EE687B},
		{L"MediumSpringGreen",     GetResourceString(L"LOCALIZED_COLOR_MEDIUMSPRINGGREEN"),     0x009AFA00},
		{L"MediumTurquoise",       GetResourceString(L"LOCALIZED_COLOR_MEDIUMTURQUOISE"),       0x00CCD148},
		{L"MediumVioletRed",       GetResourceString(L"LOCALIZED_COLOR_MEDIUMVIOLETRED"),       0x008515C7},
		{L"MidnightBlue",			GetResourceString(L"LOCALIZED_COLOR_MIDNIGHTBLUE"),          0x00701919},
		{L"MintCream",				GetResourceString(L"LOCALIZED_COLOR_MINTCREAM"),             0x00FAFFF5},
		{L"MistyRose",				GetResourceString(L"LOCALIZED_COLOR_MISTYROSE"),             0x00E1E4FF},
		{L"Moccasin",				GetResourceString(L"LOCALIZED_COLOR_MOCCASIN"),              0x00B5E4FF},
		{L"NavajoWhite",			GetResourceString(L"LOCALIZED_COLOR_NAVAJOWHITE"),           0x00ADDEFF},
		{L"Navy",					GetResourceString(L"LOCALIZED_COLOR_NAVY"),                  0x00800000},
		{L"OldLace",				GetResourceString(L"LOCALIZED_COLOR_OLDLACE"),               0x00E6F5FD},
		{L"Olive",					GetResourceString(L"LOCALIZED_COLOR_OLIVE"),                 0x00008080},
		{L"OliveDrab",				GetResourceString(L"LOCALIZED_COLOR_OLIVEDRAB"),             0x00238E6B},
		{L"Orange",					GetResourceString(L"LOCALIZED_COLOR_ORANGE"),                0x0000A5FF},
		{L"OrangeRed",				GetResourceString(L"LOCALIZED_COLOR_ORANGERED"),             0x000045FF},
		{L"Orchid",					GetResourceString(L"LOCALIZED_COLOR_ORCHID"),                0x00D670DA},
		{L"PaleGoldenRod",			GetResourceString(L"LOCALIZED_COLOR_PALEGOLDENROD"),         0x00AAE8EE},
		{L"PaleGreen",				GetResourceString(L"LOCALIZED_COLOR_PALEGREEN"),             0x0098FB98},
		{L"PaleTurquoise",			GetResourceString(L"LOCALIZED_COLOR_PALETURQUOISE"),         0x00EEEEAF},
		{L"PaleVioletRed",			GetResourceString(L"LOCALIZED_COLOR_PALEVIOLETRED"),         0x009370D8},
		{L"PapayaWhip",				GetResourceString(L"LOCALIZED_COLOR_PAPAYAWHIP"),            0x00D5EFFF},
		{L"PeachPuff",				GetResourceString(L"LOCALIZED_COLOR_PEACHPUFF"),             0x00B9DAFF},
		{L"Peru",					GetResourceString(L"LOCALIZED_COLOR_PERU"),                  0x003F85CD},
		{L"Pink",					GetResourceString(L"LOCALIZED_COLOR_PINK"),                  0x00CBC0FF},
		{L"Plum",					GetResourceString(L"LOCALIZED_COLOR_PLUM"),                  0x00DDA0DD},
		{L"PowderBlue",				GetResourceString(L"LOCALIZED_COLOR_POWDERBLUE"),            0x00E6E0B0},
		{L"Purple",					GetResourceString(L"LOCALIZED_COLOR_PURPLE"),                0x00800080},
		{L"Red",					GetResourceString(L"LOCALIZED_COLOR_RED"),                   0x000000FF},
		{L"RosyBrown",				GetResourceString(L"LOCALIZED_COLOR_ROSYBROWN"),             0x008F8FBC},
		{L"RoyalBlue", 				GetResourceString(L"LOCALIZED_COLOR_ROYALBLUE"),             0x00E16941},
		{L"SaddleBrown", 			GetResourceString(L"LOCALIZED_COLOR_SADDLEBROWN"),           0x0013458B},
		{L"Salmon", 				GetResourceString(L"LOCALIZED_COLOR_SALMON"),                0x007280FA},
		{L"SandyBrown", 			GetResourceString(L"LOCALIZED_COLOR_SANDYBROWN"),            0x0060A4F4},
		{L"SeaGreen", 				GetResourceString(L"LOCALIZED_COLOR_SEAGREEN"),              0x00578B2E},
		{L"SeaShell", 				GetResourceString(L"LOCALIZED_COLOR_SEASHELL"),              0x00EEF5FF},
		{L"Sienna", 				GetResourceString(L"LOCALIZED_COLOR_SIENNA"),                0x002D52A0},
		{L"Silver", 				GetResourceString(L"LOCALIZED_COLOR_SILVER"),                0x00C0C0C0},
		{L"SkyBlue", 				GetResourceString(L"LOCALIZED_COLOR_SKYBLUE"),               0x00EBCE87},
		{L"SlateBlue", 				GetResourceString(L"LOCALIZED_COLOR_SLATEBLUE"),             0x00CD5A6A},
		{L"SlateGray", 				GetResourceString(L"LOCALIZED_COLOR_SLATEGRAY"),             0x00908070},
		{L"SlateGrey", 				GetResourceString(L"LOCALIZED_COLOR_SLATEGREY"),             0x00908070},
		{L"Snow", 					GetResourceString(L"LOCALIZED_COLOR_SNOW"),                  0x00FAFAFF},
		{L"SpringGreen", 			GetResourceString(L"LOCALIZED_COLOR_SPRINGGREEN"),           0x007FFF00},
		{L"SteelBlue", 				GetResourceString(L"LOCALIZED_COLOR_STEELBLUE"),             0x00B48246},
		{L"Tan", 					GetResourceString(L"LOCALIZED_COLOR_TAN"),                   0x008CB4D2},
		{L"Teal",					GetResourceString(L"LOCALIZED_COLOR_TEAL"),                  0x00808000},
		{L"Thistle", 				GetResourceString(L"LOCALIZED_COLOR_THISTLE"),               0x00D8BFD8},
		{L"Tomato", 				GetResourceString(L"LOCALIZED_COLOR_TOMATO"),                0x004763FF},
		{L"Turquoise", 				GetResourceString(L"LOCALIZED_COLOR_TURQUOISE"),             0x00D0E040},
		{L"Violet", 				GetResourceString(L"LOCALIZED_COLOR_VIOLET"),                0x00EE82EE},
		{L"Wheat", 					GetResourceString(L"LOCALIZED_COLOR_WHEAT"),                 0x00B3DEF5},
		{L"White", 					GetResourceString(L"LOCALIZED_COLOR_WHITE"),                 0x00FFFFFF},
		{L"WhiteSmoke",				GetResourceString(L"LOCALIZED_COLOR_WHITESMOKE"),            0x00F5F5F5},
		{L"Yellow",					GetResourceString(L"LOCALIZED_COLOR_YELLOW"),                0x0000FFFF},
		{L"YellowGreen",			GetResourceString(L"LOCALIZED_COLOR_YELLOWGREEN"),           0x0032CD9A},
	};
    NODE * arg = car(args);

    RGBCOLOR color = 0;

    bool haveColor = false;
    while (stopping_flag != THROWING && !haveColor)
    {
        if (arg == NIL)
        {
        }
        else if (is_list(arg))
        {
            // check to see if this is a three member list
            if (cdr(arg)       != NIL &&
                cddr(arg)      != NIL &&
                cdr(cddr(arg)) == NIL)
            {
                // check to see if this is a color vector
                int red = GetColorComponent(car(arg));
                if (red != -1)
                {
                    int green = GetColorComponent(car(cdr(arg)));
                    if (green != -1)
                    {
                        int blue = GetColorComponent(car(cddr(arg)));
                        if (blue != -1)
                        {
                            // got a value color vector
                            color = MAKERGB(red, green, blue);
                            haveColor  = true;
                            bIndexMode = false;
                        }
                    }
                }
            }
        }
        else if (numberp(arg))
        {
            // this is a number, so it may be a valid index
            NODE * cnode = cnv_node_to_numnode(arg);

            int colorIndex = -1;
            if (nodetype(cnode) == INTEGER)
            {
                colorIndex = getint(cnode) % COLORTABLESIZE;
            }
            else
            {
                // We got a floating point value.
                // See if it can be converted into a small integer.
                FLONUM f = getfloat(cnode);
                if (0 <= f && f <= FIXNUM_MAX && fmod(f, 1.0) == 0.0)
                {
                    colorIndex = ((int) f) % COLORTABLESIZE;
                }
            }

            if (colorIndex != -1)
            {
                color = colortable[colorIndex];
                haveColor  = true;
                bIndexMode = true;
            }

            gcref(cnode);
        }
        else
        {
            // Try to convert this to a string, then see
            // if it matches.
            NODE * strnode = cnv_node_to_strnode(arg);
            if (strnode != Unbound)
            {
                COMPAREFUNC compareFunc = isCaseIgnored() ? 
                    low_strncmp : 
                    (COMPAREFUNC) strncmp;

                // search for the color name in g_NamedColors
                for (size_t i = 0; i < ARRAYSIZE(g_NamedColors); i++)
                {
                    if (StringNodeEqualsString(strnode, g_NamedColors[i].EnglishName,   compareFunc) ||
                        StringNodeEqualsString(strnode, g_NamedColors[i].LocalizedName, compareFunc))
                    {
                        color      = g_NamedColors[i].Color;
                        haveColor  = true;
                        bIndexMode = false;
                        break;
                    }
                }

                gcref(strnode);
            }
        }

        if (!haveColor)
        {
            // The argument isn't a valid color.
            // Throw a recoverable error and try again.
            setcar(args, err_logo(BAD_DATA, arg));
            arg = car(args);
        }
    }

    return color;
}

static
NODE *
setcolor_helper(
    NODE *args,
    void (*setcolorfunc)  (int, int, int)
    )
{
    RGBCOLOR color = GetColorArgument(args);

    if (stopping_flag != THROWING)
    {
        if (!GetPenStateForSelectedTurtle().IsErasing)
        {
            setcolorfunc(
                RedValue(color),
                GreenValue(color),
                BlueValue(color));
        }
    }

    return Unbound;
}

NODE *lsetpencolor(NODE *args)
{
    return setcolor_helper(args, ChangeActivePenColor);
}

NODE *lsetfloodcolor(NODE *args)
{
    return setcolor_helper(args, ChangeActiveFloodColor);
}

NODE *lsetscreencolor(NODE *args)
{
    return setcolor_helper(args, ChangeActiveScreenColor);
}

NODE *lsetpensize(NODE *args)
{
    int width;
    int height;

    if (is_list(car(args)))
    {
        // input is of the form [width height]
        NODE * arg = pos_int_vector_arg(args);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        width  = numeric_node_to_fixnum(car(arg));
        height = numeric_node_to_fixnum(cadr(arg));
    }
    else
    {
        // the input is just the width
        NODE * arg = nonnegative_int_arg(args);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        width  = getint(arg);
        height = width;
    }

    set_pen_width(width);
    set_pen_height(height);
    update_status_penwidth();
    return Unbound;
}

NODE *lsetpenpattern(NODE *args)
{

    NODE * arg = car(args);
    ref(arg);
    while ((arg == NIL || !is_list(arg)) && NOT_THROWING)
    {
        assign(arg, err_logo(BAD_DATA, arg));
    }

    if (NOT_THROWING)
    {
        set_list_pen_pattern(arg);
    }

    deref(arg);
    return Unbound;
}

NODE *lsetscrunch(NODE *args)
{
    NODE * xnode = numeric_arg(args);
    NODE * ynode = numeric_arg(cdr(args));

    if (NOT_THROWING)
    {
        draw_turtle(false);
        g_Scale.x = numeric_node_to_flonum(xnode);
        g_Scale.y = numeric_node_to_flonum(ynode);

        // computer 1/g_Scale (if possible)
        if (g_Scale.x != 0.0)
        {
            g_OneOverScale.x = 1.0 / g_Scale.x;
        }
        else 
        {
            g_OneOverScale.x = FLONUM_MAX;
        }

        if (g_Scale.y != 0.0)
        {
            g_OneOverScale.y = 1.0 / g_Scale.y;
        }
        else
        {
            g_OneOverScale.y = FLONUM_MAX;
        }

        draw_turtle(true);
    }
    return Unbound;
}

NODE *lbuttonp(NODE *)
{
    bool btn = button();
    return true_or_false(btn);
}

NODE *ltone(NODE *args) 
{
    NODE * pitchnode    = nonnegative_int_arg(args);
    NODE * durationnode = nonnegative_int_arg(cdr(args));

    if (NOT_THROWING)
    { 
        FIXNUM pitch    = numeric_node_to_fixnum(pitchnode);
        FIXNUM duration = numeric_node_to_fixnum(durationnode);
        tone(pitch, duration);
    }
         
    return Unbound;
}
