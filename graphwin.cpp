/*
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
   #include <math.h>
   #include <stdlib.h>
   #include <string.h>
   #include <algorithm>

   #include <wx/window.h>
   #include <wx/dc.h>
   #include <wx/pen.h>
   #include <wx/brush.h>
   #include <wx/help.h>
   #include <wx/msgdlg.h> 

   #ifdef WX_PURE
      typedef struct __BITMAP      * HBITMAP;
      typedef struct __WND         * HWND;

      typedef int LONG;

      struct RECT {
          int left;
          int top;
          int right;
          int bottom;
      };

      #include <wx/gdicmn.h>
      #include "fmslogo.h"
      #include "screen.h"
      #include "mainframe.h"

   #else
      #include <windows.h>

      #ifdef max // MS compilers #define max in windows.h
         #undef max
      #endif

      #ifdef min // MS compilers #define min in windows.h
         #undef min
      #endif

   #endif

   #include "activearea.h"
   #include "graphwin.h"
   #include "mainwind.h"

   #include "devwind.h"
   #include "cursor.h"
   #include "status.h"

   #include "utils.h"
   #include "stringprintednode.h"
   #include "appendablelist.h"
   #include "logomath.h"
   #include "dib.h"
   #include "logodata.h"
   #include "vector.h"
   #include "parse.h"
   #include "error.h"
   #include "fmslogo.h" // BitMapWidth, BitMapHeight
   #include "messagebox.h" // ShowErrorMessage
   #include "wrksp.h"
   #include "lists.h"
   #include "eval.h"
   #include "init.h"
   #include "coms.h"
   #include "unix.h"
   #include "const.h"
   #include "threed.h"
   #include "screenwindow.h"
   #include "startup.h" // g_HelpFileName
   #include "stringadapter.h"
   #include "debugheap.h"

   #include "localizedstrings.h"
#endif

struct CUTMAP
{
    HBITMAP    MemoryBitMap;  // Used to store the bitmap
    RGBCOLOR * Pixels;        // The bitmap in a flat buffer (32bpp)
    int        Height;        // current cut height
    int        Width;         // current cut width
    bool       IsValid;       // flag to signal something in cut buffer
};


#define X_ROTATED(X, Y, COSINE, SINE) ((X)*(COSINE) + (Y)*(SINE))
#define Y_ROTATED(X, Y, COSINE, SINE) ((Y)*(COSINE) - (X)*(SINE))

extern bool bIndexMode;

extern int gbmBmpToGif(const wchar_t *BmpName, const wchar_t *GifName);
extern int gbmGifToBmp(const wchar_t *GifName, const wchar_t *BmpName);

// global variables
int iDelay;
int bAppendMode;
int iLoop;
int iTrans;

wxRect g_FullRect;                     // rectangle of the full screen

#ifndef WX_PURE
LOGFONT FontRec;                       // record for label font

LOGPEN g_LogicalNormalPen;             // Handle to "Normal" logical Pen
HPEN   g_NormalPen;                    // Handle to "Normal" Pen

LOGPEN g_LogicalErasePen;              // Handle to "Erase" logical Pen
HPEN   g_ErasePen;                     // Handle to "Erase" Pen

#endif  // WX_PURE

int xoffset = 0;                       // Used to go from logo to windows coords x
int yoffset = 0;                       // Used to go from logo to windows coords y

int BaseUnitsx = 0;                    // X Units Windows uses to for units in dialog
int BaseUnitsy = 0;                    // Y Units Windows uses to for units in dialog

bool IsTimeToExit = false;             // Flag to signal it's time to exit
bool IsTimeToPause = false;            // UCBLOGO? pause flag
bool IsTimeToHalt = false;             // UCBLOGO? halt flag
bool zoom_flag = false;                // flag to signal in zoomed state
FLONUM the_zoom = 1.0;                 // current zoom factor

HBITMAP MemoryBitMap;                  // Backing store bitmap

static wxHelpController * g_HelpController;
static wxWindow         * g_HelpParent;

static CUTMAP * g_SelectedBitmap;
static CUTMAP * g_Bitmaps;               // an array of bitmaps
static int      g_BitmapsLimit;          // number of bitmaps in g_Bitmaps array

static PENSTATE g_PenState;              // The state of the current pen (color, mode, etc.)

struct font_find_t
{
    const char *fontname;
    bool        found;
};

struct LINE3D
{
    VECTOR from;
    VECTOR to;
};

static const LINE3D turtle_vertices[4] =
{
    {{-16.0, 0.0, 0.0}, { 16.0,  0.0, 0.0}},
    {{ 16.0, 0.0, 0.0}, {  0.0, 16.0, 0.0}},
    {{  0.0,16.0, 0.0}, {-16.0,  0.0, 0.0}},
    {{  8.0, 0.0, 0.0}, {  8.0,  8.0, 0.0}},
};

#ifndef WX_PURE
static DWORD g_BitMode = SRCCOPY;
#endif

#ifdef NDEBUG
#  define ASSERT_TURTLE_INVARIANT
#else
#  define ASSERT_TURTLE_INVARIANT CTurtlesInvariant invariant

class CTurtlesInvariant
{
public:

    CTurtlesInvariant()
    {
        AssertInvariant();
    }

    ~CTurtlesInvariant()
    {
        AssertInvariant();
    }

    void
    AssertInvariant(
        void
        )
    {
        // make sure g_MaxTurtle is within range
        assert(0 <= g_MaxTurtle);
        assert(g_MaxTurtle < g_TurtlesLimit);

        // we can never have less than one turtle
        assert(0 < g_TurtlesLimit);

        // g_SelectedTurtle is in either g_Turtles or g_SpecialTurtles
        assert(
            (g_Turtles <= g_SelectedTurtle && g_SelectedTurtle <= &g_Turtles[g_MaxTurtle]) || 
            (g_SpecialTurtles <= g_SelectedTurtle && g_SelectedTurtle < &g_SpecialTurtles[TOTAL_SPECIAL_TURTLES]));

        for (volatile int i = 0; i <= g_MaxTurtle; i++)
        {
            // test that all values are valid (none are uninitialized)
            assert(
                g_Turtles[i].IsShown == true ||
                g_Turtles[i].IsShown == false);

            assert(
                g_Turtles[i].IsPenUp == true ||
                g_Turtles[i].IsPenUp == false);

            assert(
                g_Turtles[i].IsSpecial == true ||
                g_Turtles[i].IsSpecial == false);

#ifndef WX_PURE

            assert(
                g_Turtles[i].BitmapRasterMode == 0           ||
                g_Turtles[i].BitmapRasterMode == SRCCOPY     ||
                g_Turtles[i].BitmapRasterMode == SRCPAINT    ||
                g_Turtles[i].BitmapRasterMode == SRCAND      ||
                g_Turtles[i].BitmapRasterMode == SRCINVERT   ||
                g_Turtles[i].BitmapRasterMode == SRCERASE    ||
                g_Turtles[i].BitmapRasterMode == NOTSRCCOPY  ||
                g_Turtles[i].BitmapRasterMode == NOTSRCERASE ||
                g_Turtles[i].BitmapRasterMode == MERGEPAINT  ||
                g_Turtles[i].BitmapRasterMode == DSTINVERT);

            if (g_Turtles[i].IsSprite)
            {
                // Even though the raster mode is not used,
                // it is set to indicate that the turtle
                // is drawn with a bitmap.
                assert(g_Turtles[i].BitmapRasterMode != 0);

                // For now, require that all sprites have a
                // default mode.
                assert(g_Turtles[i].BitmapRasterMode == SRCCOPY);
            }
#endif
        }

        // g_SelectedBitmap is within the g_Bitmaps array
        assert(g_Bitmaps <= g_SelectedBitmap);
        assert(g_SelectedBitmap < g_Bitmaps + g_BitmapsLimit);

        assert(0 < g_BitmapsLimit);

#ifndef WX_PURE
        assert(
            g_BitMode == SRCCOPY     ||
            g_BitMode == SRCPAINT    ||
            g_BitMode == SRCAND      ||
            g_BitMode == SRCINVERT   ||
            g_BitMode == SRCERASE    ||
            g_BitMode == NOTSRCCOPY  ||
            g_BitMode == NOTSRCERASE ||
            g_BitMode == MERGEPAINT  ||
            g_BitMode == DSTINVERT);
#endif
    }
};

#endif

static
bool
ClipboardIsSelectedBitmap()
{
    return g_SelectedBitmap == &g_Bitmaps[0];
}

static
void
GrowBitmapsArray(int NewSize)
{
    // assert that the array needs to grow
    assert(NewSize > g_BitmapsLimit);

    if (NewSize > (size_t)-1 / sizeof(*g_Bitmaps))
    {
        // this allocation would result in an integer overflow
        err_logo(OUT_OF_MEM, NIL);
        return;
    }

    CUTMAP * newBitmaps = (CUTMAP*) realloc(g_Bitmaps, NewSize * sizeof(*g_Bitmaps));
    if (newBitmaps == NULL)
    {
        // could not grow the turtles array to hold turtleId
        err_logo(OUT_OF_MEM, NIL);
        return;
    }

    // initialize the newly allocated bitmap structures
    for (int i = g_BitmapsLimit; i < NewSize; i++)
    {
        newBitmaps[i].MemoryBitMap = NULL;
        newBitmaps[i].Pixels       = NULL;
        newBitmaps[i].Width        = 0;
        newBitmaps[i].Height       = 0;
        newBitmaps[i].IsValid      = false;
    }

    g_Bitmaps      = newBitmaps;
    g_BitmapsLimit = NewSize;
}

#ifndef WX_PURE

static
void
UpdatePen(
    LOGPEN   & LogicalPen,
    HPEN     & Pen,
    int        Width,
    RGBCOLOR   Color
    )
{
    LogicalPen.lopnStyle   = PS_INSIDEFRAME;
    LogicalPen.lopnWidth.x = Width;
    LogicalPen.lopnColor   = Color;

    if (Pen)
    {
        DeleteObject(Pen);
    }
    Pen = CreatePenIndirect(&LogicalPen);
}

#endif



void
UpdateErasePen(
    int      Width,
    RGBCOLOR Color
    )
{
#ifndef WX_PURE
    UpdatePen(g_LogicalErasePen, g_ErasePen, Width, Color);
#endif
}

void
UpdateNormalPen(
    int      Width,
    RGBCOLOR Color
    )
{
#ifndef WX_PURE
    UpdatePen(g_LogicalNormalPen, g_NormalPen, Width, Color);
#endif
}

ERR_TYPES
gifsave_helper(
    const wchar_t *GifFileName,
    int         iDelay_,
    int         bAppendMode_,
    int         iLoop_,
    int         iTrans_,
    int         iMaxColorDepth
    )
{
    iDelay      = iDelay_;
    bAppendMode = bAppendMode_;
    iLoop       = iLoop_;
    iTrans      = iTrans_;

    ERR_TYPES status = DumpBitmapFile(TempBmpName, iMaxColorDepth);
    if (status != SUCCESS)
    {
        // an error occured.
        return status;
    }

    lsetcursorwait(NIL);
    if (gbmBmpToGif(TempBmpName, GifFileName) != 0)
    {
        status = IMAGE_GIF_SAVE_FAILED;
    }
    lsetcursorarrow(NIL);
    remove(wxString(TempBmpName));

    return status;
}

PENSTATE & GetPenStateForSelectedTurtle()
{
    if (g_SelectedTurtle->HasOwnPenState)
    {
        return g_SelectedTurtle->PenState;
    }

    // the current turtle uses the global pen state
    return g_PenState;
}

// returns the dimensions of the working area, that is
// the size of the desktop without the task bar.
void GetWorkingAreaDimensions(int & Width, int & Height)
{
#ifdef WX_PURE
    Width  = 500;
    Height = 500;
#else
    RECT workingArea;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &workingArea, 0);
    Width  = workingArea.right  - workingArea.left;
    Height = workingArea.bottom - workingArea.top;
#endif
}



NODE *lgifsave(NODE *args)
{
    // same as BITMAP-SAVE but gets file name from logo command
    CStringPrintedNode gifFileName(car(args));

    // setup default values for the optional inputs
    int  iDelay = -1;
    bool bAppendMode = false;
    int  iLoop = -1;
    int  iMaxColorDepth = 8;
    int  iTrans = -1;

    if (cdr(args) != NIL)
    {
        NODE *val1 = integer_arg(cdr(args));
        if (NOT_THROWING)
        {
            iDelay = getint(val1);
            if (cdr(cdr(args)) != NIL)
            {
                bAppendMode = boolean_arg(cdr(cdr(args)));
                if (NOT_THROWING)
                {
                    if (cdr(cdr(cdr(args))) != NIL)
                    {
                        NODE *val3 = integer_arg(cdr(cdr(cdr(args))));
                        if (NOT_THROWING)
                        {
                            iLoop = getint(val3);
                            if (cdr(cdr(cdr(cdr(args)))) != NIL)
                            {
                                NODE *val4 = integer_arg(cdr(cdr(cdr(cdr(args)))));
                                if (NOT_THROWING)
                                {
                                    iMaxColorDepth = getint(val4);
                                    if ((iMaxColorDepth != 4) && (iMaxColorDepth != 1))
                                    {
                                        iMaxColorDepth = 8;
                                    }

                                    if (cdr(cdr(cdr(cdr(cdr(args))))) != NIL)
                                    {
                                        iTrans = GetColorArgument(cdr(cdr(cdr(cdr(cdr(args))))));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (NOT_THROWING)
    {
        ERR_TYPES status = gifsave_helper(
            gifFileName,
            iDelay,
            bAppendMode,
            iLoop,
            iTrans,
            iMaxColorDepth);
        if (status != SUCCESS)
        {
            err_logo(status, NIL);
        }
    }

    return Unbound;
}

NODE *lbitsave(NODE *args)
{
    // same as BITMAP-SAVE but gets file name from logo instruction
    CStringPrintedNode bmpFileName(car(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    int iMaxBitCount = 32;
    if (cdr(args) != NIL)
    {
        NODE *val1 = integer_arg(cdr(args));
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }
        iMaxBitCount = getint(val1);
    }

    ERR_TYPES status = DumpBitmapFile(bmpFileName, iMaxBitCount);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

ERR_TYPES
gifload_helper(
    const wchar_t   * GifFileName,
    unsigned int & dwPixelWidth,
    unsigned int & dwPixelHeight
    )
{
    // convert the GIF to a DIB
    lsetcursorwait(NIL);
    int rval = gbmGifToBmp(GifFileName, TempBmpName);
    lsetcursorarrow(NIL);

    if (rval != 0)
    {
        return IMAGE_GIF_LOAD_FAILED;
    }

    // load the bitmap
    ERR_TYPES status = LoadBitmapFile(
        TempBmpName,
        dwPixelWidth,
        dwPixelHeight);

    // cleanup
    remove(wxString(TempBmpName));
    return status;
}

NODE *lgifload(NODE *arg)
{
    CStringPrintedNode gifFileName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    unsigned int pixelWidth = 1;
    unsigned int pixelHeight = 1;
    ERR_TYPES status = gifload_helper(gifFileName, pixelWidth, pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

NODE *lgifsize(NODE *args)
{
    CStringPrintedNode gifFileName(car(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    unsigned int pixelWidth = 0;
    unsigned int pixelHeight = 0;
    ERR_TYPES status = gifload_helper(gifFileName, pixelWidth, pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return cons_list(
        make_intnode((FIXNUM) pixelWidth),
        make_intnode((FIXNUM) pixelHeight));
}

NODE *lbitload(NODE *arg)
{
    // same as BITMAP-LOAD except callable from logo command
    CStringPrintedNode bitmapFileName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }


    unsigned int pixelWidth = 1;
    unsigned int pixelHeight = 1;
    ERR_TYPES status = LoadBitmapFile(
        bitmapFileName,
        pixelWidth,
        pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return Unbound;
}

NODE *lbitloadsize(NODE *arg)
{
    // same as BITMAP-LOAD except callable from logo command
    CStringPrintedNode bitmapFileName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    unsigned int pixelWidth = 0;
    unsigned int pixelHeight = 0;
    ERR_TYPES status = LoadBitmapFile(bitmapFileName, pixelWidth, pixelHeight);
    if (status != SUCCESS)
    {
        err_logo(status, NIL);
        return Unbound;
    }

    return cons_list(
        make_intnode((FIXNUM) pixelWidth),
        make_intnode((FIXNUM) pixelHeight));
}

NODE *lbitsize(NODE *)
{
#ifdef WX_PURE
    return NIL;
#else
    BITMAP temp;
    temp.bmWidth  = 0;
    temp.bmHeight = 0;

    if (ClipboardIsSelectedBitmap())
    {
        // The selected bitmap is whatever is on the clipboard
        ::OpenClipboard(GetMainWindow());

        // Try a DIB first
        HANDLE hDIB = (HBITMAP) ::GetClipboardData(CF_DIB);

        // If it exists get the size
        if (hDIB)
        {
            LPBITMAPINFOHEADER lpDIBHdr = (LPBITMAPINFOHEADER) GlobalLock(hDIB);

            if (lpDIBHdr)
            {
                temp.bmWidth  = lpDIBHdr->biWidth;
                temp.bmHeight = lpDIBHdr->biHeight;
                GlobalUnlock(hDIB);
            }
        }
        else
        {
            // else try for a bitmap
            HBITMAP hMemoryBitMap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

            // If it exists get the size
            if (hMemoryBitMap)
            {
                ::GetObject(hMemoryBitMap, sizeof(BITMAP), (LPSTR) &temp);
            }
        }

        // we have everything we need
        ::CloseClipboard();
    }
    else
    {
        // if we have something fetch its size
        if (g_SelectedBitmap->IsValid)
        {
            ::GetObject(
                g_SelectedBitmap->MemoryBitMap,
                sizeof(BITMAP),
                (LPSTR)&temp);
        }
    }

    return cons_list(
        make_intnode((FIXNUM) temp.bmWidth),
        make_intnode((FIXNUM) temp.bmHeight));
#endif
}

// Fills TurtlePoint with the location of the current
// turtle on the 2D screen (before zooming and scrolling)
//
// returns true on success.
// returns false on error.
static
bool
WorldCoordinateToScreenCoordinate(
    const VECTOR &  TurtleWorldPosition,
    wxPoint &       TurtleScreenPosition
    )
{
    if (current_mode == perspectivemode)
    {
        VECTOR from3d;

        from3d.x = TurtleWorldPosition.x / WorldWidth;
        from3d.y = TurtleWorldPosition.y / WorldHeight;
        from3d.z = TurtleWorldPosition.z / WorldDepth;

        if (!ThreeD.TransformPoint(from3d, TurtleScreenPosition))
        {
            return false;
        }
    }
    else
    {
        TurtleScreenPosition.x = g_round(TurtleWorldPosition.x);
        TurtleScreenPosition.y = g_round(TurtleWorldPosition.y);
    }

    return true;
}

// Invalidates a rectangle on the screen.
// It adjusts for the zoom factor and scroll position.
static void InvalidateRectangleOnScreen(const RECT & ScreenRectangle)
{
    RECT adjustedRectangle;

    // Expand the bounding box a little to make sure that it covers everything
    adjustedRectangle.left   = ScreenRectangle.left   - 2;
    adjustedRectangle.top    = ScreenRectangle.top    - 2;
    adjustedRectangle.right  = ScreenRectangle.right  + 2;
    adjustedRectangle.bottom = ScreenRectangle.bottom + 2;

    // Expand/contract the bounding box based on the zoom
    if (zoom_flag)
    {
        adjustedRectangle.left   *= the_zoom;
        adjustedRectangle.top    *= the_zoom;
        adjustedRectangle.right  *= the_zoom;
        adjustedRectangle.bottom *= the_zoom;
    }

    const int scrollerX = GetScreenHorizontalScrollPosition();
    const int scrollerY = GetScreenVerticalScrollPosition();

    // Move the bounding box based on scroll position.
    adjustedRectangle.left   -= scrollerX;
    adjustedRectangle.right  -= scrollerX;
    adjustedRectangle.top    -= scrollerY;
    adjustedRectangle.bottom -= scrollerY;

#ifdef WX_PURE
    wxRect refreshRegion;
    refreshRegion.SetLeft(adjustedRectangle.left);
    refreshRegion.SetRight(adjustedRectangle.right);
    refreshRegion.SetTop(adjustedRectangle.top);
    refreshRegion.SetBottom(adjustedRectangle.bottom);
    CFmsLogo::GetMainFrame()->GetScreen()->RefreshRect(refreshRegion, false);
#else
    ::InvalidateRect(GetScreenWindow(), &adjustedRectangle, FALSE);
#endif
}

static
void
InvalidateRectangleOnScreen(
    int Left,
    int Top,
    int Right,
    int Bottom)
{
    RECT screenRectangle;
    screenRectangle.left   = Left;
    screenRectangle.top    = Top;
    screenRectangle.right  = Right;
    screenRectangle.bottom = Bottom;
    InvalidateRectangleOnScreen(screenRectangle);
}

static void InvalidateRectangleOnScreen(const wxRect & MemoryRectangle)
{
    InvalidateRectangleOnScreen(
        MemoryRectangle.GetLeft(),
        MemoryRectangle.GetTop(),
        MemoryRectangle.GetRight(),
        MemoryRectangle.GetBottom());
}

static
void
InvalidateTopBottomWrappingMemoryRectangle(
    int Left,
    int Top,
    int Right,
    int Bottom)
{
    // This should only be called after the left-right wrapping
    // has been performed.
    assert(0 <= Left);
    assert(Left <= Right);
    assert(Right < BitMapWidth);

    if (Top < 0 && BitMapHeight <= Bottom)
    {
        // The box wraps around both the top and bottom
        // edges of the memory bitmap, which is to say,
        // it covers the entire height.
        InvalidateRectangleOnScreen(Left, 0, Right, BitMapHeight - 1);
    }
    else if (Top < 0)
    {
        // The box wraps around the top edge of the memory bitmap (only)

        // Invalidate the portion on the top edge.
        InvalidateRectangleOnScreen(Left, 0, Right, Bottom);
  
        // Invalidate the portion that wrapped to the bottom.
        InvalidateRectangleOnScreen(
            Left,
            BitMapHeight - 1 + Top,
            Right,
            BitMapHeight - 1);
    }
    else if (BitMapHeight <= Bottom)
    {
        // The box wraps around the bottom edge of the memory bitmap (only)

        // Invalidate the portion that wrapped to the top edge.
        InvalidateRectangleOnScreen(Left, 0, Right, Bottom - BitMapHeight + 1); 

        // Invalidate the portion on the bottom edge.
        InvalidateRectangleOnScreen(Left, Top, Right, BitMapHeight - 1);
    }
    else
    {
        // The rectangle does not wrap across the left or right edges.
        InvalidateRectangleOnScreen(Left, Top, Right, Bottom);
    }
}

static
void
InvalidateWrappingMemoryRectangle(
    int Left,
    int Top,
    int Right,
    int Bottom)
{
    if (Left < 0 && BitMapWidth <= Right)
    {
        // The box wraps around both the left and right
        // edges of the memory bitmap, which is to say,
        // it covers the entire width.
        InvalidateTopBottomWrappingMemoryRectangle(
            0,
            Top,
            BitMapWidth - 1,
            Bottom);
    }
    else if (Left < 0)
    {
        // The box wraps around the left edge of the memory bitmap (only)

        // Invalidate the portion on the left edge.
        InvalidateTopBottomWrappingMemoryRectangle(0, Top, Right, Bottom);
  
        // Invalidate the portion that wrapped to the right.
        InvalidateTopBottomWrappingMemoryRectangle(
            BitMapWidth - 1 + Left,
            Top,
            BitMapWidth - 1,
            Bottom);
    }
    else if (BitMapWidth <= Right)
    {
        // The box wraps around the right edge of the memory bitmap (only)

        // Invalidate the portion that wrapped to the left edge.
        InvalidateTopBottomWrappingMemoryRectangle(
            0,
            Top,
            Right - BitMapWidth + 1,
            Bottom);
  
        // Invalidate the portion on the right edge.
        InvalidateTopBottomWrappingMemoryRectangle(
            Left,
            Top,
            BitMapWidth - 1,
            Bottom);
    }
    else
    {
        // The rectangle does not wrap across the left or right edges.
        InvalidateTopBottomWrappingMemoryRectangle(Left, Top, Right, Bottom);
    }
}

// ibmturt() calculates what needs to be done to either draw or erase
// the turte, but it does not actually do either of these operations.
// If draw==true, then the points of the turtle's vertices are computed.
// If draw==false, then the points of the turtle's vertices are simply used
// to invalidate the turtle's bounding box (so it will get erased).
void ibmturt(bool draw)
{
    // special turtles must not be drawn
    assert(!g_SelectedTurtle->IsSpecial);

    if (draw)
    {
        // We are supposed to draw the turtle in a new position, we
        // we need to re-calculate its points.

        if (current_mode == perspectivemode)
        {
            // in 3D mode
            for (int j = 0; j < 4; j++)
            {
                VECTOR rp = MVxyMultiply(g_SelectedTurtle->Matrix, turtle_vertices[j].from);

                VECTOR from3d;
                from3d.x = (g_SelectedTurtle->Position.x + rp.x) / BitMapWidth;
                from3d.y = (g_SelectedTurtle->Position.y + rp.y) / BitMapWidth;
                from3d.z = (g_SelectedTurtle->Position.z + rp.z) / BitMapWidth;

                rp = MVxyMultiply(g_SelectedTurtle->Matrix, turtle_vertices[j].to);

                VECTOR to3d;
                to3d.x = (g_SelectedTurtle->Position.x + rp.x) / BitMapWidth;
                to3d.y = (g_SelectedTurtle->Position.y + rp.y) / BitMapWidth;
                to3d.z = (g_SelectedTurtle->Position.z + rp.z) / BitMapWidth;

                wxPoint from2d;
                wxPoint to2d;
                if (ThreeD.TransformSegment(from3d, to3d, from2d, to2d))
                {
                    long iFromx =  from2d.x + xoffset;
                    long iFromy = -from2d.y + yoffset;
                    long iTox   =  to2d.x   + xoffset;
                    long iToy   = -to2d.y   + yoffset;
               
                    g_SelectedTurtle->Points[j].from.x = iFromx;
                    g_SelectedTurtle->Points[j].from.y = iFromy;
                    g_SelectedTurtle->Points[j].to.x   = iTox;
                    g_SelectedTurtle->Points[j].to.y   = iToy;
                    g_SelectedTurtle->Points[j].bValid = true;
                }
                else
                {
                    g_SelectedTurtle->Points[j].bValid = false;
                }
            }
        }
        else
        {
            // 2D mode
            for (int j = 0; j < 3; j++)
            {
                FLONUM cosine = cos(g_SelectedTurtle->Heading * rads_per_degree);
                FLONUM sine   = sin(g_SelectedTurtle->Heading * rads_per_degree);

                FLONUM rx = X_ROTATED(turtle_vertices[j].from.x, turtle_vertices[j].from.y, cosine, sine);
                FLONUM ry = Y_ROTATED(turtle_vertices[j].from.x, turtle_vertices[j].from.y, cosine, sine);

                FLONUM oldx = g_SelectedTurtle->Position.x + rx;
                FLONUM oldy = g_SelectedTurtle->Position.y + ry;

                rx = X_ROTATED(turtle_vertices[j].to.x, turtle_vertices[j].to.y, cosine, sine);
                ry = Y_ROTATED(turtle_vertices[j].to.x, turtle_vertices[j].to.y, cosine, sine);

                FLONUM newx = g_SelectedTurtle->Position.x + rx;
                FLONUM newy = g_SelectedTurtle->Position.y + ry;

                long iOldx = g_round(oldx);
                long iOldy = g_round(oldy);
                long iNewx = g_round(newx);
                long iNewy = g_round(newy);

                long iFromx =  iOldx + xoffset;
                long iFromy = -iOldy + yoffset;
                long iTox   =  iNewx + xoffset;
                long iToy   = -iNewy + yoffset;

                g_SelectedTurtle->Points[j].from.x = iFromx;
                g_SelectedTurtle->Points[j].from.y = iFromy;
                g_SelectedTurtle->Points[j].to.x   = iTox;
                g_SelectedTurtle->Points[j].to.y   = iToy;

                g_SelectedTurtle->Points[j].bValid = true;
            }

            // The line that distingiushes left from right is not needed
            // in 2D modes.
            g_SelectedTurtle->Points[3].bValid = false;
        }
    }

    if (g_SelectedTurtle->BitmapRasterMode != 0)
    {
        // The turtle is bitmapped, we need to invalidate the bounding box of the bitmap.
        wxPoint dest;
        bool needsInvalidation = WorldCoordinateToScreenCoordinate(
            g_SelectedTurtle->Position,
            dest);

        // If the turtle is on the screen, then calculate the bounding box.
        if (needsInvalidation)
        {
            // figure out the index into the bitmaps array.
            const CUTMAP & turtleBitmap = g_Bitmaps[g_SelectedTurtle - g_Turtles];

            FLONUM leftOffset;
            FLONUM rightOffset;
            FLONUM topOffset;
            FLONUM bottomOffset;

            if (g_SelectedTurtle->IsSprite)
            {
                FLONUM cosine = cos(g_SelectedTurtle->Heading * rads_per_degree);
                FLONUM sine   = sin(g_SelectedTurtle->Heading * rads_per_degree);

                // Compute the location of the four corners of the sprite's image
                // rotated about its center.  These values are initially relative
                // to the turtle's location.
                FLONUM x0 = X_ROTATED(-turtleBitmap.Width/2.0, -turtleBitmap.Height/2.0, cosine, sine);
                FLONUM y0 = Y_ROTATED(-turtleBitmap.Width/2.0, -turtleBitmap.Height/2.0, cosine, sine);

                FLONUM x1 = X_ROTATED(-turtleBitmap.Width/2.0, turtleBitmap.Height/2.0, cosine, sine);
                FLONUM y1 = Y_ROTATED(-turtleBitmap.Width/2.0, turtleBitmap.Height/2.0, cosine, sine);

                FLONUM x2 = X_ROTATED(turtleBitmap.Width/2.0, turtleBitmap.Height/2.0, cosine, sine);
                FLONUM y2 = Y_ROTATED(turtleBitmap.Width/2.0, turtleBitmap.Height/2.0, cosine, sine);

                FLONUM x3 = X_ROTATED(turtleBitmap.Width/2.0, -turtleBitmap.Height/2.0, cosine, sine);
                FLONUM y3 = Y_ROTATED(turtleBitmap.Width/2.0, -turtleBitmap.Height/2.0, cosine, sine);

                // Compute the bounding box, again relative to the turtle's location.
                // We grow the box by one to account for rounding errors.
                leftOffset   = std::min(x0,std::min(x1, std::min(x2,x3))) - 1;
                topOffset    = std::min(y0,std::min(y1, std::min(y2,y3))) - 1;
                rightOffset  = std::max(x0,std::max(x1, std::max(x2,x3))) + 1;
                bottomOffset = std::max(y0,std::max(y1, std::max(y2,y3))) + 1;

                // Map from turtle coordinates to memory bitmap coordinates.
                int memoryBoundingBoxLeft   = +dest.x + xoffset + leftOffset;
                int memoryBoundingBoxTop    = -dest.y + yoffset + topOffset;
                int memoryBoundingBoxRight  = +dest.x + xoffset + rightOffset;
                int memoryBoundingBoxBottom = -dest.y + yoffset + bottomOffset;

                if (current_mode == wrapmode)
                {
                    // In "wrapmode" sprite bitmaps wrap around the screen just
                    // like the turtle movement.
                    InvalidateWrappingMemoryRectangle(
                        memoryBoundingBoxLeft,
                        memoryBoundingBoxTop,
                        memoryBoundingBoxRight,
                        memoryBoundingBoxBottom);
                }
                else
                {
                    InvalidateRectangleOnScreen(
                        memoryBoundingBoxLeft,
                        memoryBoundingBoxTop,
                        memoryBoundingBoxRight,
                        memoryBoundingBoxBottom);
                }
            }
            else
            {
                // Compute the bounding box of the non-rotating sprite in screen cordinate.
                // The lower-left corner of this bitmap is the location of the turtle.
                InvalidateRectangleOnScreen(
                    +dest.x + xoffset + 0,                        // left
                    -dest.y + yoffset + LL - turtleBitmap.Height, // top
                    +dest.x + xoffset + turtleBitmap.Width,       // right
                    -dest.y + yoffset + LL);                      // bottom
            }
        }
    }
    else
    {
        // The turtle is drawn with lines, so we need to calculate the bounding box
        // of these lines.

        // Calculate the bounding box independent of zoom and scroll position.
        bool  needsInvalidation = false;
        RECT  invalidationBoundingBox;

        invalidationBoundingBox.left   =  100000;
        invalidationBoundingBox.top    =  100000;
        invalidationBoundingBox.right  = -100000;
        invalidationBoundingBox.bottom = -100000;
        for (int j = 0; j < 4; j++)
        {
            if (g_SelectedTurtle->Points[j].bValid)
            {
                invalidationBoundingBox.left   = std::min(invalidationBoundingBox.left,   (LONG) (g_SelectedTurtle->Points[j].from.x));
                invalidationBoundingBox.top    = std::min(invalidationBoundingBox.top,    (LONG) (g_SelectedTurtle->Points[j].from.y));
                invalidationBoundingBox.right  = std::max(invalidationBoundingBox.right,  (LONG) (g_SelectedTurtle->Points[j].from.x));
                invalidationBoundingBox.bottom = std::max(invalidationBoundingBox.bottom, (LONG) (g_SelectedTurtle->Points[j].from.y));
                needsInvalidation = true;
            }
        }

        if (needsInvalidation)
        {
            InvalidateRectangleOnScreen(invalidationBoundingBox);
        }
    }
}

NODE *lsetpixel(NODE *args)
{
    ASSERT_TURTLE_INVARIANT;

    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    // get args
    wxUint32 color = GetColorArgument(args);

    if (NOT_THROWING)
    {
        // Draw the pixel on the memory bitmap.
        wxDC * memoryDeviceContext = GetWxMemoryDeviceContext();

        // Set the foreground mix mode in case a previous call had set it
        // to something that would modify the pixel.
        memoryDeviceContext->SetLogicalFunction(wxCOPY);

        const wxPen oldPen(memoryDeviceContext->GetPen());
        memoryDeviceContext->SetPen(wxColor(color));
#ifdef __WXMSW__
        memoryDeviceContext->DrawPoint(
            +dest.x + xoffset,
            -dest.y + yoffset);
#else
        // On non-MSW implementations of wxWidgets, wxDC::DrawPoint
        // draws a line from (x,y) to (x+1,y+1).  To work around
        // this, we set the pixel by drawing a single point.
        // See http://trac.wxwidgets.org/ticket/9674
        memoryDeviceContext->DrawLine(
            +dest.x + xoffset,
            -dest.y + yoffset,
            +dest.x + xoffset,
            -dest.y + yoffset);
#endif
        memoryDeviceContext->SetPen(oldPen);

        //screen
        draw_turtle(false);

        if (zoom_flag)
        {
            // Refresh the pixel on the screen so that pixel on the memory
            // bitmap is immediatly drawn to the screen.
            wxRect pixelRect(+dest.x + xoffset, -dest.y + yoffset, 1, 1);
            InvalidateRectangleOnScreen(pixelRect);
        }
        else
        {
            // We are not zoomed, so the screen is 1:1 with the memory bitmap.
            // This makes it easy to update the screen without an expensive repaint.
            wxDC * screenDeviceContext = GetWxScreenDeviceContext();

            const wxPen oldScreenPen(screenDeviceContext->GetPen());
            screenDeviceContext->SetPen(wxColour(color));

            // Set the foreground mix mode in case a previous call had set it
            // to something that would modify the pixel.
            screenDeviceContext->SetLogicalFunction(wxCOPY);

#ifdef __WXMSW__        
        screenDeviceContext->DrawPoint(
            +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
            -dest.y - GetScreenVerticalScrollPosition()   + yoffset);
#else
        screenDeviceContext->DrawLine(
            +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
            -dest.y - GetScreenVerticalScrollPosition()   + yoffset,
            +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
            -dest.y - GetScreenVerticalScrollPosition()   + yoffset);
#endif

            screenDeviceContext->SetPen(oldScreenPen);
        }

        draw_turtle(true);
    }

    return Unbound;
}

static
int
getindexcolor(
    wxUint32 Color
    )
{
    for (size_t i = 0; i < COLORTABLESIZE; i++)
    {
        if (Color == colortable[i])
        {
            return i;
        }
    }
    return -1;
}

static NODE* color_helper(const wxColour & Color)
{
    if (bIndexMode)
    {
        // We're in "index mode", so colors are returned as
        // an index, if possible.
        int colorIndex = getindexcolor(Color.GetRGB());
        if (colorIndex >= 0)
        {
            return make_intnode(colorIndex);
        }
    }

    return cons_list(
        make_intnode((FIXNUM) Color.Red()),
        make_intnode((FIXNUM) Color.Green()),
        make_intnode((FIXNUM) Color.Blue()));
}

static NODE* color_helper(const Color & col)
{
    if (bIndexMode)
    {
        int icolor = getindexcolor(MAKERGB(col.red, col.green, col.blue));
        if (icolor >= 0)
        {
            return make_intnode(icolor);
        }
    }

    return cons_list(
        make_intnode((FIXNUM) col.red),
        make_intnode((FIXNUM) col.green),
        make_intnode((FIXNUM) col.blue));
}



// function that returns the RGB vector of the pixel the turtle is on top of
NODE *lpixel(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return cons_list(
            make_intnode((FIXNUM) -1),
            make_intnode((FIXNUM) -1),
            make_intnode((FIXNUM) -1));
    }

    // Read the pixel from the memory bitmap.
    wxDC * memoryDeviceContext = GetWxMemoryDeviceContext();

    wxColour pixelColor;
    memoryDeviceContext->GetPixel(
        dest.x + xoffset,
        -dest.y + yoffset,
        &pixelColor);

    // Return the pixel as a NODE
    return color_helper(pixelColor);
}

void logofill(bool fillUntilPenColor)
{
    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return;
    }

    // memory
    wxDC * memoryDeviceContext = GetWxMemoryDeviceContext();

    // Select the fill brush, saving the old one.
    wxColor fillColor(fcolor);
    wxBrush fillBrush(fillColor);
    const wxBrush oldBrush = memoryDeviceContext->GetBrush();
    memoryDeviceContext->SetBrush(fillBrush);

    if (fillUntilPenColor)
    {
        memoryDeviceContext->FloodFill(
            +dest.x + xoffset,
            -dest.y + yoffset,
            wxColor(pcolor),
            wxFLOOD_BORDER);
    }
    else
    {
        wxColor colorUnderTurtle;
        memoryDeviceContext->GetPixel(
            +dest.x + xoffset,
            -dest.y + yoffset,
            &colorUnderTurtle);

        memoryDeviceContext->FloodFill(
            +dest.x + xoffset,
            -dest.y + yoffset,
            colorUnderTurtle,
            wxFLOOD_SURFACE);
    }

    // Restore the previous brush
    memoryDeviceContext->SetBrush(oldBrush);

    // Since we don't have a way to cacluate how much of the
    // memory region was filled, we mark the entire screen as
    // invalid.
    wxWindow * screen = GetScreenWxWindow();
    screen->Refresh(false);

    // Update the screen immediately so that FILL within
    // a timer event will take place (otherwise the repainting
    // events will wait until FMSLogo is idle).
    screen->Update();
}

NODE *lpencolor(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
    return color_helper(GetPenStateForSelectedTurtle().Color);
}


// Do all of the things necessary when the pen color changes:
// * Sets the pen color on the active turtle
// * Updates the global pen
// * Updates the values in the status window
void ChangeActivePenColor(int Red, int Green, int Blue)
{
    Color & penColor = GetPenStateForSelectedTurtle().Color;
    penColor.red   = Red;
    penColor.green = Green;
    penColor.blue  = Blue;

    pcolor = MAKERGB(Red, Green, Blue);

    UpdateNormalPen(GetPenStateForSelectedTurtle().Width, pcolor);

    update_status_pencolor();
}


// function to return flood color as a RGB list
NODE *lfloodcolor(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
    return color_helper(dfld);
}

// Do all of the things necessary when the flood color changes:
// * Sets the global flood color
// * Updates the global flood color brush
// * Updates the values in the status window
void ChangeActiveFloodColor(int Red, int Green, int Blue)
{
    dfld.red   = Red;
    dfld.green = Green;
    dfld.blue  = Blue;

    fcolor = MAKERGB(dfld.red, dfld.green, dfld.blue);

    update_status_floodcolor();
}

// function to return screen color as a RGB list
NODE *lscreencolor(NODE *)
{
    return color_helper(dscn);
}

// Do all of the things necessary when the screen color changes:
// * Sets the global screen color
// * Updates the global screen brush (and erase brush)
// * Updates the values in the status window
void ChangeActiveScreenColor(int Red, int Green, int Blue)
{
    dscn.red   = Red;
    dscn.green = Green;
    dscn.blue  = Blue;

    scolor = MAKERGB(dscn.red, dscn.green, dscn.blue);

    // When the screen changes we change the erase pen which basically
    // writes the screen color
    UpdateErasePen(GetPenStateForSelectedTurtle().Width, scolor);

    // Clear the screen using the new color
    ibm_clear_screen();

    update_status_screencolor();
}

int get_pen_width()
{
    return GetPenStateForSelectedTurtle().Width;
}

int get_pen_height()
{
    return get_pen_width();
}

void set_pen_width(int w)
{
    GetPenStateForSelectedTurtle().Width = w;

    // we erase with the same pen width as we write
    UpdateNormalPen(w, pcolor);
    UpdateErasePen(w,  scolor);
}

void set_pen_height(int h)
{
    set_pen_width(h);
}

NODE *lclearpalette(NODE *)
{
    // MSWLogo supported display depths of 256 and under.
    // FMSLogo no longer supports these, but retains the
    // procedure as a no-op for compatibility.
    return Unbound;
}

NODE *lstatus(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    OpenStatusWindow();
    return Unbound;
}

NODE *lnostatus(NODE *)
{
    CloseStatusWindow();
    return Unbound;
}


// The zoom control flag determines whether or not we can use the faster line
// drawing method of drawing directly to the screen buffer, or use the slower
// method of drawing to the backbuffer and invalidating part of the screen.
// This is only faster when there is no zooming.
// And it's only correct to do when there are no widgets on the screen, such
// as ones created with BUTTONCREATE or LISTBOXCREATE.
void UpdateZoomControlFlag()
{
    if ((the_zoom != 1.0) || CheckOnScreenControls())
    {
        zoom_flag = true;
    }
    else
    {
        zoom_flag = false;
    }
}

// The real work of zooming is done in Paint this just adjusts the scroller
// to something reasonable so that what was basically in the center of the
// screen still is. It also readjusts the ranges on the scrollers.
void zoom_helper(FLONUM NewZoomFactor)
{
    if (the_zoom != NewZoomFactor)
    {
        the_zoom = NewZoomFactor;

        AdjustScrollPositionToZoomFactor(NewZoomFactor);

        // hide turtle while we do this
        draw_turtle(false);

        UpdateZoomControlFlag();

        draw_turtle(true);

#ifndef WX_PURE
        // paint the entire window
        InvalidateRect(GetScreenWindow(), NULL, FALSE);
#endif
    }
}

NODE *lzoom(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    NODE *val = positive_numeric_arg(arg);
    if (stopping_flag != THROWING)
    {
        FLONUM temp_zoom = numeric_node_to_flonum(val);

        zoom_helper(temp_zoom);
    }

    return Unbound;
}


NODE *lbitblock(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    wxPoint turtleLocation;
    if (!WorldCoordinateToScreenCoordinate(
            g_SelectedTurtle->Position,
            turtleLocation))
    {
        // the turtle is not on the screen
        return Unbound;
    }

    // get args
    int cutWidth  = getint(nonnegative_int_arg(arg));
    int cutHeight = getint(nonnegative_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
        // only do the blit if a non-zero area was specified
        if (cutWidth != 0 && cutHeight != 0)
        {
            // Select the fill brush, saving the old one.
            wxColor fillColor(fcolor);
            wxBrush fillBrush(fillColor);
            wxDC * memoryDeviceContext = GetWxMemoryDeviceContext();
            const wxBrush oldBrush(memoryDeviceContext->GetBrush());
            memoryDeviceContext->SetBrush(fillBrush);

            // Also change the pen to be transparent, or else
            // an outline will be drawn around the filled region.
            const wxPen oldPen(memoryDeviceContext->GetPen());
            memoryDeviceContext->SetPen(*wxTRANSPARENT_PEN);

            wxRect memoryRect(
                +turtleLocation.x + xoffset,                  // left
                -turtleLocation.y + yoffset - cutHeight + LL, // top
                cutWidth,                                     // width
                cutHeight);                                   // height

            memoryDeviceContext->DrawRectangle(memoryRect);

            // Restore the brush/pen
            memoryDeviceContext->SetBrush(oldBrush);
            memoryDeviceContext->SetPen(oldPen);

            //screen
            if (zoom_flag)
            {
                // It's easier to invalidate the screen and force a 
                // repaint from the image memory.
                GetScreenWxWindow()->Refresh(false);
            }
            else
            {
                // Invalidate the portion of the screen that corresponds
                // to the region of memory that we filled.
                // Ever since we stopped calling GetDC() and ReleaseDC()
                // to get the screen DC, simply calling FillRect() on the
                // screen causes repainting problems.
                // I suspect that calling ReleaseDC() implicitly invalidated
                // the screen, which may be why it was so much slower.
                InvalidateRectangleOnScreen(memoryRect);
            }
        }
    }

    return Unbound;
}


// Converts the FMSLogo bitmode to the Window raster mode

#ifndef WX_PURE
static
DWORD
BitModeToRasterMode(
    FIXNUM BitMode
    )
{
    switch (BitMode)
    {
    case 1:
        return SRCCOPY;

    case 2:
        return SRCPAINT;

    case 3: 
        return SRCAND;

    case 4:
        return SRCINVERT;

    case 5:
        return SRCERASE;

    case 6:
        return NOTSRCCOPY;

    case 7:
        return NOTSRCERASE;

    case 8:
        return MERGEPAINT;

    case 9:
        return DSTINVERT;

    default:
        // notify the caller that the bitmode was invalid
        return 0;
    }
}

// Converts the Window raster mode to a FMSLogo bitmode.
static
FIXNUM
RasterModeToBitMode(
    DWORD RasterMode
    )
{
    // return the logo "code" for the bit mode
    switch (RasterMode)
    {
    case 0:
    case SRCCOPY: 
        return 1;

    case SRCPAINT: 
        return 2;

    case SRCAND: 
        return 3;

    case SRCINVERT: 
        return 4;

    case SRCERASE:
        return 5;

    case NOTSRCCOPY:
        return 6;

    case NOTSRCERASE:
        return 7;

    case MERGEPAINT: 
        return 8;

    case DSTINVERT:
        return 9;
    }

    assert(0 && "can't happen");
    return 0;
}

static
DWORD
BitModeArgsToRasterMode(
    NODE * BitModeArguments
    )
{
    NODE * bitModeNode = ranged_integer_arg(BitModeArguments, 1, 9);
    if (stopping_flag == THROWING)
    {
        return 0;
    }

    return BitModeToRasterMode(getint(bitModeNode));
}

#endif // WX_PURE


NODE *lbitmode(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

#ifdef WX_PURE
    FIXNUM temp = 0;
#else
    // return the logo "code" for the bit mode
    FIXNUM temp = RasterModeToBitMode(g_BitMode);
#endif

    return make_intnode(temp);
}

NODE *lsetbitmode(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
#ifndef WX_PURE
    // convert from logo "code" to Windows constants
    FIXNUM bitmode = BitModeArgsToRasterMode(arg);
    if (NOT_THROWING)
    {
        g_BitMode = bitmode;
    }
#endif
    return Unbound;
}

NODE *lturtlemode(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
#ifdef WX_PURE
    FIXNUM turtlemode = 0;
#else
    // return the logo "code" for the bit mode
    FIXNUM turtlemode = RasterModeToBitMode(g_SelectedTurtle->BitmapRasterMode);
#endif
    return make_intnode(turtlemode);
}

NODE *lsetturtlemode(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
#ifndef WX_PURE
    if (g_SelectedTurtle->BitmapRasterMode)
    {
        if (g_SelectedTurtle->IsSprite)
        {
            // The code for drawing rotating sprites does not
            // honor the turtle's mode.  However, it could
            // someday, so prevent to its introduction from
            // being a breaking change, we prevent anyone
            // from setting it today.
            err_logo(
                INVALID_STATE_FOR_INSTRUCTION,
                cons_list(make_strnode(LOCALIZED_ERROR_MODE_ON_SPRITE)));
        }

        // convert from logo "code" to Windows constants
        FIXNUM rastermode = BitModeArgsToRasterMode(arg);
        if (NOT_THROWING)
        {
            draw_turtle(false);
            g_SelectedTurtle->BitmapRasterMode = rastermode;
            draw_turtle(true);
        }
    }
#endif
    return Unbound;
}

NODE *lbitindex(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
    // return the current bitmap index
    return make_intnode((FIXNUM) (g_SelectedBitmap - g_Bitmaps));
}

NODE *lsetbitindex(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // set the current bitmap index if within range
    int i = getint(nonnegative_int_arg(arg));
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_BitmapsLimit <= i)
    {
        GrowBitmapsArray(i + 1);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }
    }

    g_SelectedBitmap = g_Bitmaps + i;

    return Unbound;
}


static
void
CopyFromBitmapArrayToClipboard()
{
#ifndef WX_PURE
    // Open the clipboard, dump what's in there and return the Bitmap
    ::OpenClipboard(GetMainWindow());

    ::EmptyClipboard();

    ::SetClipboardData(
        CF_BITMAP,
        g_Bitmaps[0].MemoryBitMap);

    // give him a DIB using system palette
    ::SetClipboardData(
        CF_DIB,
        BitmapToDIB(
            g_Bitmaps[0].MemoryBitMap,
            NULL));

    ::CloseClipboard();
#endif

    // Never mung with bitmaps that belong to ClipBoard
    g_Bitmaps[0].IsValid = false;
}

static
void
PasteFromClipboardToBitmapArray()
{
#ifndef WX_PURE
    ::OpenClipboard(GetMainWindow());

    // Try a DIB first
    HANDLE tempDIB = (HBITMAP) ::GetClipboardData(CF_DIB);
    if (tempDIB != NULL)
    {
        // The clipboard holds a DIB.  Try to get the palette.
        HPALETTE tempPal = (HPALETTE) ::GetClipboardData(CF_PALETTE);

        // we work in bmps here
        g_Bitmaps[0].MemoryBitMap = ::DIBToBitmap(tempDIB, tempPal);

        // Let code know below that we have something
        g_Bitmaps[0].IsValid = true;

        // We created a BitMap from the DIB that we only need for the
        // purpose of this "paste", next paste could be something new.
        // so get rid of it once we have pasted it here.

        ::EmptyClipboard();
        ::SetClipboardData(CF_BITMAP, g_Bitmaps[0].MemoryBitMap);

        // give him a DIB using system palette
        ::SetClipboardData(
            CF_DIB,
            BitmapToDIB(g_Bitmaps[0].MemoryBitMap, NULL));
    }
    else
    {
        // else try for a bitmap
        g_Bitmaps[0].MemoryBitMap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

        // flag that we have one if it exists, no need to delete the
        // bitmap here because clipboard still owns it.

        if (g_Bitmaps[0].MemoryBitMap != NULL)
        {
            g_Bitmaps[0].IsValid = true;
        }
        else
        {
            g_Bitmaps[0].IsValid = false;
        }
    }

    // if we have something fetch its size

    if (g_Bitmaps[0].IsValid)
    {
        BITMAP temp;

        ::GetObject(
            g_Bitmaps[0].MemoryBitMap,
            sizeof(BITMAP),
            (LPSTR) &temp);

        g_Bitmaps[0].Width = temp.bmWidth;
        g_Bitmaps[0].Height = temp.bmHeight;

        // Clear any cached version of the bitmap
        free(g_Bitmaps[0].Pixels);
        g_Bitmaps[0].Pixels = NULL;
    }

    // we have everything we need
    ::CloseClipboard();
#endif
}

static
NODE *
BitCopyOrCut(NODE *arg, bool IsCut)
{
    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    int tempWidth  = getint(nonnegative_int_arg(arg));
    int tempHeight = getint(nonnegative_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
#ifndef WX_PURE
        bool havebitmap = false;

        // if we had a old cut get rid of it, we won't go in for clipboard
        if (g_SelectedBitmap->IsValid)
        {
            // if same size reuse the bitmap
            if ((tempWidth == g_SelectedBitmap->Width) &&
                (tempHeight == g_SelectedBitmap->Height))
            {
                havebitmap = true;
            }
            else
            {
                // else get rid of it and make a new one later
                DeleteObject(g_SelectedBitmap->MemoryBitMap);
                g_SelectedBitmap->MemoryBitMap = NULL;
            }
            g_SelectedBitmap->IsValid = false;

            // Always free any pixel buffer.  Because this is filled in lazily,
            // we don't want to keep an old image around merely because it's
            // the same size as the one we might allocate in the future.
            free(g_SelectedBitmap->Pixels);
            g_SelectedBitmap->Pixels = NULL;
        }

        g_SelectedBitmap->Width  = tempWidth;
        g_SelectedBitmap->Height = tempHeight;

        // only if we have a surface continue
        if ((g_SelectedBitmap->Width != 0) && (g_SelectedBitmap->Height != 0))
        {
            // flag it so we will delete it
            g_SelectedBitmap->IsValid = true;

            HDC screenDC = GetScreenDeviceContext();
            HDC memDC    = GetMemoryDeviceContext();

            if (!havebitmap)
            {
                g_SelectedBitmap->MemoryBitMap = CreateCompatibleBitmap(
                    screenDC,
                    g_SelectedBitmap->Width,
                    g_SelectedBitmap->Height);
            }

            if (g_SelectedBitmap->MemoryBitMap == NULL)
            {
                ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPCUTFAILED);
                return Unbound;
            }


            HDC tempMemDC = CreateCompatibleDC(screenDC);

            HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
                tempMemDC,
                g_SelectedBitmap->MemoryBitMap);

            BitBlt(
                tempMemDC,
                0,
                0,
                g_SelectedBitmap->Width,
                g_SelectedBitmap->Height,
                memDC,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - g_SelectedBitmap->Height,
                SRCCOPY);

            SelectObject(tempMemDC, oldBitmap2);
            DeleteDC(tempMemDC);


            if (IsCut)
            {
                // This is a cut operation (as opposed to a copy operation)
                // Replace the cut bitmap with the screen color.

                // memory
                RECT tempRect;
                SetRect(
                    &tempRect,
                    +dest.x + xoffset,
                    -dest.y + yoffset + LL - g_SelectedBitmap->Height,
                    +dest.x + xoffset + g_SelectedBitmap->Width,
                    -dest.y + yoffset + LL);

                LOGBRUSH screenBrushLog;
                screenBrushLog.lbStyle = BS_SOLID;
                screenBrushLog.lbColor = scolor;
                screenBrushLog.lbHatch = HS_VERTICAL;
                HBRUSH tempBrush = CreateBrushIndirect(&screenBrushLog);

                FillRect(memDC, &tempRect, tempBrush);

                //screen
                draw_turtle(false);

                if (zoom_flag)
                {
                    // TRect temp;
                    //
                    // temp.Set(
                    //   (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
                    //   (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - g_SelectedBitmap->Height) * the_zoom,
                    //   (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset + g_SelectedBitmap->Width      ) * the_zoom,
                    //   (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
                    //
                    // temp.Normalize();
                    // temp.Inflate(1+the_zoom,1+the_zoom);
                    InvalidateRect(GetScreenWindow(), NULL, FALSE);
                }
                else
                {
                    RECT tempRect;
                    SetRect(
                        &tempRect,
                        +g_SelectedTurtle->Position.x - GetScreenHorizontalScrollPosition() + xoffset,
                        -g_SelectedTurtle->Position.y - GetScreenVerticalScrollPosition()   + yoffset + LL - g_SelectedBitmap->Height,
                        +g_SelectedTurtle->Position.x - GetScreenHorizontalScrollPosition() + xoffset + g_SelectedBitmap->Width,
                        -g_SelectedTurtle->Position.y - GetScreenVerticalScrollPosition()   + yoffset + LL);

                    FillRect(screenDC, &tempRect, tempBrush);
                }

                DeleteObject(tempBrush);

                draw_turtle(true);
            }

            if (ClipboardIsSelectedBitmap())
            {
                CopyFromBitmapArrayToClipboard();
            }
        }
#endif
    }

    return Unbound;
}


NODE *lbitcut(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
    return BitCopyOrCut(arg, true);
}

NODE *lbitcopy(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
    return BitCopyOrCut(arg, false);
}

NODE *lbitfit(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    FIXNUM newWidth  = getint(nonnegative_int_arg(arg));
    FIXNUM newHeight = getint(nonnegative_int_arg(cdr(arg)));

    if (NOT_THROWING)
    {
#ifndef WX_PURE
        // If clipboard check with clipboard only
        if (ClipboardIsSelectedBitmap())
        {
            PasteFromClipboardToBitmapArray();
        }

        // resize the bitmap if we have a surface to fit to and from
        if (newWidth != 0 && newHeight != 0 && g_SelectedBitmap->IsValid)
        {
            HDC ScreenDC = GetScreenDeviceContext();
            HDC MemDC    = GetMemoryDeviceContext();

            // TODO: Use bitmap device context.
            HBITMAP savedMemBitmap = (HBITMAP) SelectObject(MemDC, g_SelectedBitmap->MemoryBitMap);

            HBITMAP newMemoryBitmap = CreateCompatibleBitmap(ScreenDC, newWidth, newHeight);
            if (newMemoryBitmap != NULL)
            {
                HDC tempMemDC = CreateCompatibleDC(ScreenDC);
                HBITMAP savedTempMemoryBitmap = (HBITMAP) SelectObject(tempMemDC, newMemoryBitmap);

                // Enable anti-aliasing on the strech blit.
                SetStretchBltMode(tempMemDC, HALFTONE);

                // Load hour-glass cursor.
                lsetcursorwait(NIL);

                StretchBlt(
                    tempMemDC,
                    0,
                    0,
                    newWidth,
                    newHeight,
                    MemDC,
                    0,
                    0,
                    g_SelectedBitmap->Width,
                    g_SelectedBitmap->Height,
                    SRCCOPY);

                // Restore the arrow cursor
                lsetcursorarrow(NIL);

                SelectObject(tempMemDC, savedTempMemoryBitmap);
                DeleteDC(tempMemDC);

                // commit to using the new "bitfitted" bitmap
                DeleteObject(g_SelectedBitmap->MemoryBitMap);
                g_SelectedBitmap->MemoryBitMap = newMemoryBitmap;

                g_SelectedBitmap->Width  = newWidth;
                g_SelectedBitmap->Height = newHeight;
            }
            else
            {
                err_logo(OUT_OF_MEM, NIL);
            }

            SelectObject(MemDC, savedMemBitmap);

            if (ClipboardIsSelectedBitmap())
            {
                CopyFromBitmapArrayToClipboard();
            }
        }
#endif
    }

    return Unbound;
}

NODE *lbitpaste(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return Unbound;
    }

    if (NOT_THROWING)
    {
#ifndef WX_PURE
        // If clipboard check with clipboard only
        if (ClipboardIsSelectedBitmap())
        {
            PasteFromClipboardToBitmapArray();
        }

        // only if we have something to paste
        if (g_SelectedBitmap->IsValid)
        {

            if (ClipboardIsSelectedBitmap())
            {
                // never leave the clipboard's IsValid flag true
                g_SelectedBitmap->IsValid = false;
            }

            // TODO: use device context in CUTMAP.
            HDC ScreenDC = GetScreenDeviceContext();
            HDC TempMemDC = CreateCompatibleDC(ScreenDC);
            SelectObject(TempMemDC, g_SelectedBitmap->MemoryBitMap);

            //memory
            HDC MemDC = GetMemoryDeviceContext();

            BitBlt(
                MemDC,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - g_SelectedBitmap->Height,
                (int) (g_SelectedBitmap->Width),
                (int) (g_SelectedBitmap->Height),
                TempMemDC,
                0,
                0,
                g_BitMode);

            //screen
            draw_turtle(false);

            if (zoom_flag)
            {
                // TRect temp;
                //
                // temp.Set(
                //     (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset                                  ) * the_zoom,
                //     (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL - g_SelectedBitmap->Height) * the_zoom,
                //     (+g_SelectedTurtle->Position.x - MainWindowx->Scroller->XPos / the_zoom + xoffset + g_SelectedBitmap->Width      ) * the_zoom,
                //     (-g_SelectedTurtle->Position.y - MainWindowx->Scroller->YPos / the_zoom + yoffset + LL                             ) * the_zoom);
                //
                // temp.Normalize();
                // temp.Inflate(1+the_zoom,1+the_zoom);

                InvalidateRect(GetScreenWindow(), NULL, FALSE);
            }
            else
            {
                BitBlt(
                    ScreenDC,
                    +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
                    -dest.y - GetScreenVerticalScrollPosition()   + yoffset + LL - g_SelectedBitmap->Height,
                    (int) (g_SelectedBitmap->Width),
                    (int) (g_SelectedBitmap->Height),
                    TempMemDC,
                    0,
                    0,
                    g_BitMode);
            }

            draw_turtle(true);

            DeleteDC(TempMemDC);

            // Clipboard owns what we paste in not what we converted
        }
        else
        {
            // notify the user that the clipboard is empty
            ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE);
        }
#endif
    }

    return Unbound;
}

NODE *lbitpastetoindex(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // set the current bitmap index if within range
    int i = getint(nonnegative_int_arg(arg));
    int x = int_arg(cdr(arg));
    int y = int_arg(cdr(cdr(arg)));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    if (g_BitmapsLimit <= i)
    {
        // notify the user that the bitmap index is out of range
        ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE);
        return Unbound;
    }
    
    if (!g_Bitmaps[i].IsValid)
    {
        // nofity the user that there is no bitmap at this index
        ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP);
        return Unbound;
    }

#ifndef WX_PURE
    // If ClipBoard check with ClipBoard only
    if (ClipboardIsSelectedBitmap())
    {
        PasteFromClipboardToBitmapArray();
    }

    // only if we have something to paste
    if (g_SelectedBitmap->IsValid)
    {

        if (ClipboardIsSelectedBitmap())
        {
            // never leave the clipboard's IsValid flag true
            g_SelectedBitmap->IsValid = false;
        }

        HDC ScreenDC = GetScreenDeviceContext();

        // TODO: Use device context in CUTMAP.
        HDC sourceDeviceContext = CreateCompatibleDC(ScreenDC);
        SelectObject(sourceDeviceContext, g_SelectedBitmap->MemoryBitMap);

        // TODO: Use device context in CUTMAP.
        HDC destinationDeviceContext = CreateCompatibleDC(ScreenDC);
        SelectObject(destinationDeviceContext, g_Bitmaps[i].MemoryBitMap);

        BitBlt(
            destinationDeviceContext,
            +x,
            g_Bitmaps[i].Height - y - g_SelectedBitmap->Height,
            g_SelectedBitmap->Width,
            g_SelectedBitmap->Height,
            sourceDeviceContext,
            0,
            0,
            g_BitMode);

        DeleteDC(sourceDeviceContext);
        DeleteDC(destinationDeviceContext);
    }
    else
    {
        // notify the user that the clipboard is empty
        ShowErrorMessageAndStop(LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE);
    }
#endif
    return Unbound;
}

NODE *lsetturtle(NODE *args)
{
    ASSERT_TURTLE_INVARIANT;

    NODE * val = ranged_integer_arg(args, -TOTAL_SPECIAL_TURTLES, FIXNUM_MAX);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    int turtleId = getint(val);
    if (turtleId < 0)
    {
        if (cdr(args) != NIL)
        {
            // unique pen modes are meaningless for the special
            // turtles, so we consider this bad input.
            err_logo(TOO_MUCH, NIL);
            return Unbound;
        }

        // this is a special turtle.
        // Remap <-1, -2, -3> to <0, 1, 2>
        g_SelectedTurtle = g_SpecialTurtles - turtleId - 1;
    }
    else
    {
        // This is a normal turtle

        // read the optional "has unique pen" input
        bool hasUniquePen         = false; // by default, share a global pen
        bool overrideHasUniquePen = false; // by default, keep the current setting
        if (cdr(args) != NIL)
        {
            hasUniquePen         = boolean_arg(cdr(args));
            overrideHasUniquePen = true;
            if (stopping_flag == THROWING)
            {
                return Unbound;
            }
        }

        if (g_TurtlesLimit <= turtleId)
        {
            // The physical array is smaller than the requested turtle
            // index, so we must grow the turtle array.

            if (turtleId + 1 > (size_t)-1 / sizeof(*g_Turtles))
            {
                // this allocation would result in an integer overflow
                err_logo(OUT_OF_MEM, NIL);
                return Unbound;
            }

            size_t newSize = (turtleId + 1) * sizeof(*g_Turtles);
            Turtle * newTurtles = (Turtle*) realloc(g_Turtles, newSize);
            if (newTurtles == NULL)
            {
                // could not grow the turtles array to hold turtleId
                err_logo(OUT_OF_MEM, NIL);
                return Unbound;
            }

            // commit to the new array
            g_Turtles      = newTurtles;
            g_TurtlesLimit = turtleId + 1;
        }

        g_SelectedTurtle = &g_Turtles[turtleId];
        if (turtleId > g_MaxTurtle)
        {
            // This turtle has not yet been created.
            // Create this turtle and all of the turtles up to it.
            for (int i = g_MaxTurtle + 1; i <= turtleId; i++)
            {
                InitializeTurtle(&g_Turtles[i]);
                g_Turtles[i].HasOwnPenState = hasUniquePen;
            }
            
            g_MaxTurtle = turtleId;
        }

        if (overrideHasUniquePen)
        {
            // The caller specified a UseUniquePen input, so
            // we override whatever value was set in the turtle.
            g_SelectedTurtle->HasOwnPenState = hasUniquePen;
        }

        // Update the current brush.
        // ChangeActivePenColor() updates the brushes color and width.
        const Color & activePenColor = GetPenStateForSelectedTurtle().Color;
        ChangeActivePenColor(
            activePenColor.red,
            activePenColor.green,
            activePenColor.blue);
    }

    draw_turtles(false);

    // update everything in the status window that can change
    // when the turtle changes.
    update_status_penstyle();
    update_status_penwidth();
    update_status_turtleposition();
    update_status_pencontact();
    update_status_turtlevisability();
    update_status_turtleheading();
    update_status_turtlepitch();
    update_status_turtleroll();
    update_status_turtlewhich();

    g_Wanna = g_SelectedTurtle->Position;

    draw_turtles(true);

    return Unbound;
}

NODE *lturtle(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    int active_turtle = GetSelectedTurtleIndex();
    return make_intnode(active_turtle);
}

NODE *lturtles(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
    return make_intnode(g_MaxTurtle);
}

NODE *lhasownpenp(NODE*)
{
    return true_or_false(g_SelectedTurtle->HasOwnPenState);
}

static RGBCOLOR InterpolateColors(RGBCOLOR A, RGBCOLOR B, double Alpha)
{
    if (A == B)
    {
        return A;
    }

    // Alpha used to go from 0 -> 1.
    // The domain of each color component is only 0-255, so
    // without a loss of precision, we can change this to integral
    // math.
    const int alphaInt         = (int)(Alpha * 4096.5);
    const int oneMinusAlphaInt = 4096 - alphaInt;

    unsigned char red   = (RedValue(A)   * oneMinusAlphaInt + RedValue(B)   * alphaInt) / 4096;
    unsigned char green = (GreenValue(A) * oneMinusAlphaInt + GreenValue(B) * alphaInt) / 4096;
    unsigned char blue  = (BlueValue(A)  * oneMinusAlphaInt + BlueValue(B)  * alphaInt) / 4096;

    return MAKERGB(red, green, blue);
}

static void SetWrappedPixel(HDC DeviceContext, int X, int Y, RGBCOLOR Pixel)
{
    if (current_mode == wrapmode)
    {
        if (X < 0)
        {
            // Wrap from the left side to the right.
            X += BitMapWidth;
        }
        else if (BitMapWidth <= X)
        {
            // Wrap from the right side to the left.
            X -= BitMapWidth - 1;
        }
        
        if (Y < 0)
        {
            // Wrap from the top to the bottom.
            Y += BitMapHeight;
        }
        else if (BitMapHeight <= Y)
        {
            // Wrap from the right side to the left.
            Y -= BitMapHeight + 1;
        }
    }

#ifndef WX_PURE
    SetPixelV(DeviceContext, X, Y, Pixel);
#endif
}

static RGBCOLOR GetWrappedPixel(HDC DeviceContext, int X, int Y)
{
    if (current_mode == wrapmode)
    {
        if (X < 0)
        {
            // Wrap from the left side to the right.
            X += BitMapWidth;
        }
        else if (BitMapWidth <= X)
        {
            // Wrap from the right side to the left.
            X -= BitMapWidth - 1;
        }
        
        if (Y < 0)
        {
            // Wrap from the top to the bottom.
            Y += BitMapHeight;
        }
        else if (BitMapHeight <= Y)
        {
            // Wrap from the right side to the left.
            Y -= BitMapHeight + 1;
        }
    }
    
#ifdef WX_PURE
    return 0;
#else
    return GetPixel(DeviceContext, X, Y);
#endif 
}

// Copies a bitmap that is associated with a given turtle onto a
// device context.
//
// PaintDeviceContext - The device context on which to paste the bitmap.
// TurtleToPaste      - The index of the turtle (and bitmap) that should
//                      be copied to the screen.
// zoom               - A multiplier that says how much the bitmap
//                      should be expanded when being copied.
//
// The calling contract is very strange for performance reasons and
// hopefully will not last long.
// 1) This is only called for turtles that are bitmapped.
// 2) Sprite turtles MUST ignore the zoom, as this is handled by the caller.
// 3) This MUST ignore the scroll positions.
static void turtlepaste(HDC PaintDeviceContext, int TurtleToPaste, FLONUM zoom)
{
    ASSERT_TURTLE_INVARIANT;
    assert(0 <= TurtleToPaste);
    assert(TurtleToPaste <= g_MaxTurtle);

    if (g_BitmapsLimit <= TurtleToPaste)
    {
        // There is no bitmap which corresponds to this turtle.
        // We do nothing, equivalent to if the bitmap size is 0x0.
        return;
    }

    Turtle * const turtle = &g_Turtles[TurtleToPaste];
    CUTMAP * const bitmap = &g_Bitmaps[TurtleToPaste];

    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(turtle->Position, dest))
    {
        return;
    }

#ifndef WX_PURE
    // If clipboard check with clipboard only
    if (TurtleToPaste == 0)
    {
        PasteFromClipboardToBitmapArray();
    }

    // only if we have something to paste
    if (bitmap->IsValid)
    {
        // if clipboard then never leave Cut Flag true
        if (TurtleToPaste == 0)
        {
            bitmap->IsValid = false;
        }

        HDC TempMemDC = CreateCompatibleDC(PaintDeviceContext);

        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(
            TempMemDC,
            bitmap->MemoryBitMap);

        if (turtle->IsSprite)
        {
            // TODO: figure out how to merge this with the bounding box
            // computation logic in ibmturt()

            // Compute the sine and cosine of the heading, but add special cases
            // for the multiples of 90 degress so that we get a crisp square
            // rotation instead of a slight deviation due to the imprecision
            // of sin() and cos() functions.
            FLONUM cosine;
            FLONUM sine;

            if (turtle->Heading == 90)
            {
                cosine = 0;
                sine   = 1;
            }
            else if (turtle->Heading == 180)
            {
                cosine = -1;
                sine   = 0;
            }
            else if (turtle->Heading == 270)
            {
                cosine = 0;
                sine   = -1;
            }
            else
            {
                cosine = cos(turtle->Heading * rads_per_degree);
                sine   = sin(turtle->Heading * rads_per_degree);
            }
            
            const FLONUM sourceWidth  = bitmap->Width;
            const FLONUM sourceHeight = bitmap->Height;

            // The location of the centerpoint (or origin) of the turtle's bitmap about which to rotate
            const FLONUM xOrigin = sourceWidth  / 2.0;
            const FLONUM yOrigin = sourceHeight / 2.0;
                
            // Compute points of the image rotated about its center.
            FLONUM x0 = X_ROTATED(-xOrigin, -yOrigin, cosine, sine);
            FLONUM y0 = Y_ROTATED(-xOrigin, -yOrigin, cosine, sine);

            FLONUM x1 = X_ROTATED(-xOrigin, yOrigin, cosine, sine);
            FLONUM y1 = Y_ROTATED(-xOrigin, yOrigin, cosine, sine);

            FLONUM x2 = X_ROTATED(xOrigin, yOrigin, cosine, sine);
            FLONUM y2 = Y_ROTATED(xOrigin, yOrigin, cosine, sine);

            FLONUM x3 = X_ROTATED(xOrigin, -yOrigin, cosine, sine);
            FLONUM y3 = Y_ROTATED(xOrigin, -yOrigin, cosine, sine);

            // Compute the bounding box.  We grow the box by one to account for truncation.
            const int minx = (int) std::min(x0,std::min(x1, std::min(x2,x3)));
            const int miny = (int) std::min(y0,std::min(y1, std::min(y2,y3)));
            const int maxx = (int) std::max(x0,std::max(x1, std::max(x2,x3))) + 1;
            const int maxy = (int) std::max(y0,std::max(y1, std::max(y2,y3))) + 1;

            // Figure out where on the memory bitmap the turtle belongs.
            const int xScreenOffset = (+dest.x + xoffset);
            const int yScreenOffset = (-dest.y + yoffset);

            const RGBCOLOR TRANSPARENT_COLOR = MAKERGB(255, 255, 255);

            // Read the bitmap into a local buffer for faster access.
            // Because this takes a long time, we also cache this in the CUTMAP.
            if (bitmap->Pixels == NULL) 
            {
                bitmap->Pixels = (RGBCOLOR *) malloc(bitmap->Width * bitmap->Height * sizeof(RGBCOLOR));

                RGBCOLOR * nextPixel = bitmap->Pixels;
                for (int y = 0; y < bitmap->Height; y++)
                {
                    for (int x = 0; x < bitmap->Width; x++)
                    {
                        RGBCOLOR pixel = ::GetPixel(TempMemDC, x, y);
                        *nextPixel++ = pixel;
                    }
                }
            }
            RGBCOLOR const * const sourceBitmap = bitmap->Pixels;

            // Now do the rotating, one pixel at a time.
            // Find the pixel that cooresponds to each point in the destination
            // rectangle to guarantee that each pixel gets covered.
            const FLONUM deltaSourceX =  cosine;
            const FLONUM deltaSourceY = -sine;

            // Use bilinear interpolation to make the picture look nice at rough angles.
            for (int y = miny; y < maxy; y++)
            {
                FLONUM sourceX = X_ROTATED(minx, y, cosine, sine) + xOrigin - 0.5;
                FLONUM sourceY = Y_ROTATED(minx, y, cosine, sine) + yOrigin - 0.5;

                for (int x = minx; x < maxx; x++)
                {
                    // sourceX and sourceY look like this if computed in an absolute manner.
                    // sourceX = X_ROTATED(x, y, cosine, sine) + xOrigin - 0.5;
                    // sourceY = Y_ROTATED(x, y, cosine, sine) + yOrigin - 0.5;

                    if (-1.0 < sourceX && sourceX < sourceWidth &&
                        -1.0 < sourceY && sourceY < sourceHeight)
                    {
                        // Perform bilinear interpolation across the (potentially)
                        // four pixels on the source bitmap on which this screen
                        // pixel falls.
                        FLONUM sourceXInt;
                        FLONUM xFraction = modf(sourceX, &sourceXInt);
                        if (sourceX < 0)
                        {
                            sourceXInt = -1.0;
                            xFraction  = 1.0 + xFraction;
                        }

                        FLONUM sourceYInt;
                        FLONUM yFraction = modf(sourceY, &sourceYInt);
                        if (sourceY < 0)
                        {
                            sourceYInt = -1.0;
                            yFraction  = 1.0 + yFraction;
                        }

                        int sourceXInteger = static_cast<int>(sourceXInt);
                        int sourceYInteger = static_cast<int>(sourceYInt);
                        const RGBCOLOR * x0y0Ptr = sourceBitmap + sourceYInteger * bitmap->Width + sourceXInteger;
                        const RGBCOLOR * x0y1Ptr = x0y0Ptr + bitmap->Width;

                        // Read the four pixels from the bitmap. If any pixel falls
                        // outside the bitmap, then use the screen's pixel, instead.
                        RGBCOLOR pixelx0y0;
                        RGBCOLOR pixelx1y0;
                        RGBCOLOR pixelx0y1;
                        RGBCOLOR pixelx1y1;
                        if (0 <= sourceXInteger && sourceXInteger < bitmap->Width - 1)
                        {
                            // The "X0" and "X1" pixels both fall on the bitmap

                            if (0 <= sourceYInteger && sourceYInteger < bitmap->Height - 1)
                            {
                                // All four source pixels are on the bitmap.
                                pixelx0y0 = x0y0Ptr[0];
                                pixelx1y0 = x0y0Ptr[1];
                                pixelx0y1 = x0y1Ptr[0];
                                pixelx1y1 = x0y1Ptr[1];
                            }
                            else if (sourceYInteger < 0)
                            {
                                // The "Y0" pixels falls below the bitmap.
                                pixelx0y0 = TRANSPARENT_COLOR;
                                pixelx1y0 = TRANSPARENT_COLOR;
                                pixelx0y1 = x0y1Ptr[0];
                                pixelx1y1 = x0y1Ptr[1];
                            }
                            else
                            {
                                // The "Y1" pixels fall above the bitmap.
                                pixelx0y0 = x0y0Ptr[0];
                                pixelx1y0 = x0y0Ptr[1];
                                pixelx0y1 = TRANSPARENT_COLOR;
                                pixelx1y1 = TRANSPARENT_COLOR;
                            }
                        }
                        else if (sourceXInteger < 0)
                        {
                            // The "X0" pixels fall to the left of the bitmap.
                            pixelx0y0 = TRANSPARENT_COLOR;
                            pixelx0y1 = TRANSPARENT_COLOR;

                            if (0 <= sourceYInteger && sourceYInteger < bitmap->Height - 1)
                            {
                                // The Y0 and Y1 are on the bitmap.
                                pixelx1y0 = x0y0Ptr[1];
                                pixelx1y1 = x0y1Ptr[1];
                            }
                            else if (sourceYInteger < 0)
                            {
                                // The "Y0" pixels fall below the bitmap.
                                pixelx1y0 = TRANSPARENT_COLOR;
                                pixelx1y1 = x0y1Ptr[1];
                            }
                            else
                            {
                                // The "Y1" pixels fall above the bitmap.
                                pixelx1y0 = x0y0Ptr[1];
                                pixelx1y1 = TRANSPARENT_COLOR;
                            }
                        }
                        else
                        {
                            // The "X1" pixels fall to the right of the bitmap.
                            pixelx1y0 = TRANSPARENT_COLOR;
                            pixelx1y1 = TRANSPARENT_COLOR;

                            if (0 <= sourceYInteger && sourceYInteger < bitmap->Height - 1)
                            {
                                // The Y0 and Y1 are on the bitmap.
                                pixelx0y0 = x0y0Ptr[0];
                                pixelx0y1 = x0y1Ptr[0];
                            }
                            else if (sourceYInteger < 0)
                            {
                                // The "Y0" pixels fall below the bitmap.
                                pixelx0y0 = TRANSPARENT_COLOR;
                                pixelx0y1 = x0y1Ptr[0];
                            }
                            else
                            {
                                // The "Y1" pixels fall above the bitmap.
                                pixelx0y0 = x0y0Ptr[0];
                                pixelx0y1 = TRANSPARENT_COLOR;
                            }
                        }

                        if (pixelx0y0 == pixelx0y1 &&
                            pixelx0y0 == pixelx1y0 &&
                            pixelx0y0 == pixelx1y1)
                        {
                            // If all of the adjacent pixels are the same, then
                            // bilinear interpolation is unnecessary.  For a typical
                            // sprite image, this optimization yields a 10% speed
                            // improvement.
                            if (pixelx0y0 != TRANSPARENT_COLOR)
                            {
                                SetWrappedPixel(
                                    PaintDeviceContext,
                                    x + xScreenOffset,
                                    y + yScreenOffset,
                                    pixelx0y0);
                            }
                        }
                        else
                        {
                            // Get the screen's value for each of the transparent pixels.
                            // If there aren't any, then we don't need to read the screen
                            // pixel.
                            if (pixelx0y0 == TRANSPARENT_COLOR ||
                                pixelx1y0 == TRANSPARENT_COLOR ||
                                pixelx0y1 == TRANSPARENT_COLOR ||
                                pixelx1y1 == TRANSPARENT_COLOR)
                            {
                                const RGBCOLOR screenPixel = GetWrappedPixel(
                                    PaintDeviceContext,
                                    x + xScreenOffset,
                                    y + yScreenOffset);

                                if (pixelx0y0 == TRANSPARENT_COLOR)
                                {
                                    pixelx0y0 = screenPixel;
                                }
                                if (pixelx1y0 == TRANSPARENT_COLOR)
                                {
                                    pixelx1y0 = screenPixel;
                                }
                                if (pixelx0y1 == TRANSPARENT_COLOR)
                                {
                                    pixelx0y1 = screenPixel;
                                }
                                if (pixelx1y1 == TRANSPARENT_COLOR)
                                {
                                    pixelx1y1 = screenPixel;
                                }
                            }

                            // interpolate in the X direction, then the Y direction
                            RGBCOLOR pixely0 = InterpolateColors(pixelx0y0, pixelx1y0, xFraction);
                            RGBCOLOR pixely1 = InterpolateColors(pixelx0y1, pixelx1y1, xFraction);
                            RGBCOLOR pixel   = InterpolateColors(pixely0, pixely1, yFraction);

                            SetWrappedPixel(
                                PaintDeviceContext,
                                x + xScreenOffset,
                                y + yScreenOffset,
                                pixel);
                        }
                    }

                    sourceX += deltaSourceX;
                    sourceY += deltaSourceY;
                }
            }
        }
        else
        {
            // Non-rotating bitmaps can simply be copied to the target context.
            if (zoom != 1.0)
            {
                // Configure BitBlit to support the zoom.
                SetMapMode(PaintDeviceContext, MM_ANISOTROPIC);
                SetWindowOrgEx(PaintDeviceContext, 0, 0, 0);
                SetWindowExtEx(PaintDeviceContext, BitMapWidth, BitMapHeight, 0);

                SetViewportOrgEx(
                    PaintDeviceContext,
                    (int) (GetScreenHorizontalScrollPosition() * zoom),
                    (int) (GetScreenVerticalScrollPosition()   * zoom),
                    0);

                SetViewportExtEx(
                    PaintDeviceContext, 
                    (int) (BitMapWidth  * zoom),
                    (int) (BitMapHeight * zoom),
                    0);
            }

            BitBlt(
                PaintDeviceContext,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - bitmap->Height,
                bitmap->Width,
                bitmap->Height,
                TempMemDC,
                0,
                0,
                turtle->BitmapRasterMode);
        }

        SelectObject(TempMemDC, oldBitmap2);
        DeleteDC(TempMemDC);
    }
    else
    {
        // notify the user that this turtle has no picture
		wchar_t errorMessage[255];
        wprintf(errorMessage, LOCALIZED_ERROR_TURTLEHASNOPICTURE, TurtleToPaste);
        ShowErrorMessage(errorMessage);

        // un-bitmap this turtle to prevent future errors
        turtle->BitmapRasterMode = 0;
        turtle->IsSprite         = false;
    }
#endif
}

void paste_all_turtles(wxDC & DeviceContext, FLONUM zoom)
{
    for (int j = 0; j <= g_MaxTurtle; j++)
    {
        if (g_Turtles[j].IsShown)
        {
            if (g_Turtles[j].BitmapRasterMode)
            {
                DeviceContext.SetLogicalFunction(wxCOPY);
#ifndef WX_PURE
                turtlepaste(static_cast<HDC>(DeviceContext.GetHDC()), j, zoom);
#endif
            }
            else
            {
#ifndef __WXGTK__
                // wxINVERT seems to be broken in wxWidgets 3.0.2 for GTK.
                // If this were called, then nothing would be drawn.
                DeviceContext.SetLogicalFunction(wxINVERT);
#endif
                for (int i = 0; i < 4; i++)
                {
                    if (g_Turtles[j].Points[i].bValid)
                    {
                        DeviceContext.DrawLine(
                            g_Turtles[j].Points[i].from.x * zoom,
                            g_Turtles[j].Points[i].from.y * zoom,
                            g_Turtles[j].Points[i].to.x * zoom,
                            g_Turtles[j].Points[i].to.y * zoom);
                    }
                }
            }
        }
    }
}

NODE *lscrollx(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
#ifndef WX_PURE
    // get args and scroll the scroller
    NODE *args = numeric_arg(arg);

    if (NOT_THROWING)
    {
        int delta = getint(args);

        if (delta == 0)
        {
            RECT screenRect;
            GetClientRect(GetScreenWindow(), &screenRect);

            SetScreenScrollPosition(
                ((BitMapWidth * the_zoom) / 2) - (0.5 * screenRect.right),
                GetScreenVerticalScrollPosition());
        }
        else
        {
            SetScreenScrollPosition(
                GetScreenHorizontalScrollPosition() + delta,
                GetScreenVerticalScrollPosition());
        }
    }
#endif
    return Unbound;
}

NODE *lscrolly(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    // get args and scroll the scroller
    NODE * args = numeric_arg(arg);

    if (NOT_THROWING)
    {
        int delta = getint(args);
#ifndef WX_PURE
        if (delta == 0)
        {
            RECT screenRect;
            GetClientRect(GetScreenWindow(), &screenRect);

            SetScreenScrollPosition(
                GetScreenHorizontalScrollPosition(),
                ((BitMapHeight * the_zoom)/ 2) - (0.5 * screenRect.bottom));
        }
        else
        {
            SetScreenScrollPosition(
                GetScreenHorizontalScrollPosition(),
                GetScreenVerticalScrollPosition() + delta);
        }
#endif
    }

    return Unbound;
}

NODE *lsetfocus(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
#ifndef WX_PURE
    CStringPrintedNode windowCaption(car(arg));

    HWND window;

    if (0 == _wcsicmp(L"FMSLogo", windowCaption) ||
        0 == _wcsicmp(L"MSWLogo Screen", windowCaption) ||
        0 == _wcsicmp(L"FMSLogo Screen", windowCaption))
    {
        // special-case: set the focus on the screen
        window = GetScreenWindow();
    }
    else
    {
        // get handle to Window with arg as Caption
        window = FindWindow(NULL, windowCaption);
    }

    // Now set focus to it, if it exists
    if (window != NULL)
    {
        ::SetFocus(window);
    }
#endif

    return Unbound;
}

NODE *lgetfocus(NODE *)
{
    ASSERT_TURTLE_INVARIANT;

    wchar_t textbuf[MAX_BUFFER_SIZE];
    memset(textbuf, 0, MAX_BUFFER_SIZE*sizeof(wchar_t));

#ifndef WX_PURE
    // Get handle to active window
    HWND TempH = GetActiveWindow();

    // It better exist, get its caption
    if (TempH != NULL)
    {
        ::GetWindowText(TempH, textbuf, ARRAYSIZE(textbuf));
    }
#endif

    // Return caption as a list
    NODE * arg = make_strnode(textbuf);
    NODE * val = arg; // parser(arg, false);
    return val;
}

NODE *lwindowset(NODE *args)
{
#ifndef WX_PURE
    CStringPrintedNode caption(car(args));

    int mode = getint(nonnegative_int_arg(cdr(args)));

    if (NOT_THROWING)
    {
        HWND window;

        // For compatibility with other translations of FMSLogo (with
        // possibly alternate names for the commander), we always treat
        // the window "commander" as meaning the commander.
        if (0 == _wcsicmp(caption, L"commander"))
        {
            // For backward compatibility with MSWLogo, we must undock
            // the commander into its own window so that window operations
            // on it have the expected effect.
            UndockCommanderWindow();

            window = GetCommanderWindow();
        }
        else
        {
            // get handle to Window with arg as Caption
            window = FindWindow(NULL, caption);
        }

        // if it exists set its state.
        if (window != NULL)
        {
            ShowWindow(window, mode);
        }
    }
#endif
    return Unbound;
}

void ibm_clear_screen()
{
    ASSERT_TURTLE_INVARIANT;

    wxColour screenColor(dscn.red, dscn.green, dscn.blue);
    wxBrush  screenBrush(screenColor);

    // Reset the on-screen bitmap.
    wxDC * memoryDeviceContext = GetWxMemoryDeviceContext();
    memoryDeviceContext->SetBackground(screenColor);
    memoryDeviceContext->Clear();

    // Refresh the screen window so that it will repainted
    // to match the memory device context.
    GetScreenWxWindow()->Refresh(false);
}

#ifndef WX_PURE

static
int CALLBACK
FindFont(
    const LOGFONT    *  LogFont,     // pointer to logical-font data
    const TEXTMETRIC *  TextMetric,  // pointer to physical-font data
    unsigned long       FontType,    // type of font
    LPARAM              lParam       // address of application-defined data
    )
{
    struct font_find_t * context = reinterpret_cast<struct font_find_t *>(lParam);

    // check for a match
    if (_wcsicmp(wxString(context->fontname), LogFont->lfFaceName) == 0)
    {
        // take a copy, flag one was found and return
        FontRec = *LogFont;
        context->found = true;
        return 0;  // stop enumerating fonts
    }

    return 1; // keep enumerating fonts
}


static
int CALLBACK
GatherFontFaces(
    const LOGFONT    *  LogFont,     // pointer to logical-font data
    const TEXTMETRIC *  TextMetric,  // pointer to physical-font data
    unsigned long       FontType,    // type of font
    LPARAM              lParam       // address of application-defined data
    )
{
    CAppendableList * fontfaces = reinterpret_cast<CAppendableList *>(lParam);

    // Create a new node for this font face name.
    // By convention font face names are a list containing a string.
    NODE * fontFaceNode = cons_list(make_strnode(LogFont->lfFaceName));

    // Append the font face name to the end of the list.
    fontfaces->AppendElement(fontFaceNode);

    return 1; // keep enumerating fonts
}


static
int CALLBACK
PrintFont(
    const LOGFONT    * LogFont,     // pointer to logical-font data
    const TEXTMETRIC * TextMetric,  // pointer to physical-font data
    unsigned long      FontType,    // type of font
    LPARAM             lParam       // address of application-defined data
    )
{
    printfx(L"[%s]", LogFont->lfFaceName);
    return 1; // keep enumerating fonts
}


static
void
setfont(
    const wchar_t *fontname
    )
{
    HDC hdc = GetDC(::GetFocus());

    // set the font name that we're looking for (FontRec will get filled if found)
    struct font_find_t context; 
    context.found    = false;
    context.fontname = wxString(fontname);
    EnumFontFamilies(
        hdc,
        NULL,
        FindFont,
        reinterpret_cast<LPARAM>(&context));

    if (!context.found)
    {
        // The font wasn't found.  Print all available fonts
        printfx(
            LOCALIZED_ERROR_FONTNOTFOUND,
            fontname);

        EnumFontFamilies(hdc, NULL, PrintFont, 0L);
    }

    ReleaseDC(::GetFocus(), hdc);
}

#endif // WX_PURE

bool
HtmlHelpInitialize(
    void
    )
{
    if (g_HelpController != NULL)
    {
        // The Help subsystem has already been initialized
        return true;
    }

#ifdef __WXMSW__
    // For compatibility with MSWLogo, the deskop is the parent of the help.
    // This ensures that the window for the main environment can be positioned
    // over the help and gives the help window a unique icon.
    g_HelpParent = new wxWindow();
    g_HelpParent->SetHWND(GetDesktopWindow());
    g_HelpParent->AdoptAttributesFromHWND();

    g_HelpController = new wxHelpController(g_HelpParent);
#else
    g_HelpController = new wxHelpController();
#endif


    // This is the only place that reads g_HelpFileName,
    // so its allocation should be part of this
    // lazy initialization.
    if (!g_HelpController->Initialize(*g_HelpFileName))
    {
        wxMessageBox(
			wxString(LOCALIZED_ERROR_HHCTRLNOTLOADED),
			wxString(LOCALIZED_ERROR));

        HtmlHelpUninitialize();
        return false;
    }

    // success
    return true;
}

void
HtmlHelpUninitialize(
    void
    )
{
    if (g_HelpController != NULL)
    {
        // Close the help.
        g_HelpController->Quit();

        delete g_HelpController;
        g_HelpController = NULL;

#ifdef __WXMSW__
        g_HelpParent->SetHWND(NULL);
        g_HelpParent->Destroy();
        g_HelpParent = NULL;
#endif
    }
}

// if arg is NULL then we jump to index
void do_help(const wchar_t *arg)
{
    if (!HtmlHelpInitialize())
    {
        return;
    }

    if (arg != NULL)
    {
        // A specific help topic was requested.
        g_HelpController->KeywordSearch(wxString(arg));
    }
    else
    {
        g_HelpController->DisplaySection(wxString(L"index.htm"));
    }
}

NODE *lhelp(NODE *arg)
{
    // if arg then pass to do_help
    if (arg != NIL)
    {
        CStringPrintedNode item(car(arg));
        do_help(item);
    }
    else
    {
        // else just pop up help
        do_help(NULL);
    }

    return Unbound;
}

NODE *lwinhelp(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;
#ifndef WX_PURE
    CStringPrintedNode textbuf(car(arg));

    // if 2nd arg then pass to winhelp
    if (cdr(arg) != NIL)
    {
        CStringPrintedNode textbuf2(car(cdr(arg)));

        WinHelp(
            GetMainWindow(),
            textbuf,
            HELP_PARTIALKEY,
            reinterpret_cast<DWORD>(textbuf2.GetString()));
    }
    else
    {
        // else just give help on file (arg 1)
        WinHelp(GetMainWindow(), textbuf, HELP_INDEX, 0L);
    }
#endif
    return Unbound;
}

NODE *lfontfacenames(NODE *arg)
{
    CAppendableList fontFaceNames; 

#ifndef WX_PURE
    HDC hdc = GetDC(::GetFocus());

    EnumFontFamilies(
        hdc,
        NULL,
        GatherFontFaces,
        reinterpret_cast<LPARAM>(&fontFaceNames));

    ReleaseDC(::GetFocus(), hdc);
#endif

    return fontFaceNames.GetList();
}

NODE *lsetlabelfont(NODE *arg)
{
    ASSERT_TURTLE_INVARIANT;

    NODE *args = list_arg(arg);
    if (NOT_THROWING)
    {
#ifndef WX_PURE
        if (args == NIL)
        {
            // no font name was given.
            setfont(L"");
            return Unbound;
        }

        CStringPrintedNode textbuf(car(args));

        // Get the FontRec filled with a match to textbuf
        setfont(textbuf);

        // now fill in the rest of the (optional) fields if given
        if (cdr(args) != NIL)
        {
            FontRec.lfHeight = int_arg(args = cdr(args));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfWidth = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfOrientation = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfWeight = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfItalic = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfUnderline = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfStrikeOut = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfCharSet = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfOutPrecision = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfClipPrecision = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfQuality = getint(nonnegative_int_arg(args = cdr(args)));
        }
        if (cdr(args) != NIL)
        {
            FontRec.lfPitchAndFamily = getint(nonnegative_int_arg(args = cdr(args)));
        }
#endif
    }

    return Unbound;
}

NODE *llabelfont(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
#ifdef WX_PURE
    return NIL;
#else
    // put the Font name in a list
    NODE *targ = make_strnode(FontRec.lfFaceName);
    NODE *val = parser(targ, false);

    // now return the whole thing as a list

    return
        cons(val,
        cons(make_intnode((FIXNUM) FontRec.lfHeight),
        cons(make_intnode((FIXNUM) FontRec.lfWidth),
        cons(make_intnode((FIXNUM) FontRec.lfOrientation),
        cons(make_intnode((FIXNUM) FontRec.lfWeight),
        cons(make_intnode((FIXNUM) FontRec.lfItalic),
        cons(make_intnode((FIXNUM) FontRec.lfUnderline),
        cons(make_intnode((FIXNUM) FontRec.lfStrikeOut),
        cons(make_intnode((FIXNUM) FontRec.lfCharSet),
        cons(make_intnode((FIXNUM) FontRec.lfOutPrecision),
        cons(make_intnode((FIXNUM) FontRec.lfClipPrecision),
        cons(make_intnode((FIXNUM) FontRec.lfQuality),
        cons(make_intnode((FIXNUM) FontRec.lfPitchAndFamily),
        NIL)))))))))))));
#endif
}

NODE *lmachine(NODE *)
{
    ASSERT_TURTLE_INVARIANT;
#ifdef WX_PURE
    return NIL;
#else
    // Get the desktop dimensions
    HDC tempDC = GetDC(0);

    int ScreenWidth  = GetDeviceCaps(tempDC, HORZRES);
    int ScreenHeight = GetDeviceCaps(tempDC, VERTRES);

    ReleaseDC(0, tempDC);


    // Get the working area dimensions
    int workingAreaWidth;
    int workingAreaHeight;
    GetWorkingAreaDimensions(workingAreaWidth, workingAreaHeight);


    // Get FMSLogo's window dimensions
    RECT mainWindowRect;
    GetWindowRect(GetMainWindow(), &mainWindowRect);

    // Get Screen window's dimensions
    RECT screenWindowRect;
    GetWindowRect(GetScreenWindow(), &screenWindowRect);

    // return a list with system specific information
    return
        cons(make_intnode((FIXNUM) 1),
        cons(make_intnode((FIXNUM) 32),
        cons(make_intnode((FIXNUM) BitMapWidth),
        cons(make_intnode((FIXNUM) BitMapHeight),
        cons(make_intnode((FIXNUM) 0),
        cons(make_intnode((FIXNUM) (LOBYTE(LOWORD(GetVersion())))),
        cons(make_intnode((FIXNUM) (HIBYTE(LOWORD(GetVersion())))),
        cons(make_intnode((FIXNUM) workingAreaWidth),
        cons(make_intnode((FIXNUM) workingAreaHeight),
        cons(make_intnode((FIXNUM) ScreenWidth),
        cons(make_intnode((FIXNUM) ScreenHeight),
        cons(make_intnode((FIXNUM) (mainWindowRect.right  - mainWindowRect.left)),
        cons(make_intnode((FIXNUM) (mainWindowRect.bottom - mainWindowRect.top)),
        cons(make_intnode((FIXNUM) (screenWindowRect.right  - screenWindowRect.left)),
        cons(make_intnode((FIXNUM) (screenWindowRect.bottom - screenWindowRect.top)),
        NIL)))))))))))))));
#endif
}

#ifndef WX_PURE

SIZE labelsize(const wchar_t *s)
{
    ASSERT_TURTLE_INVARIANT;

    SIZE size = {0};

    HDC screen = GetScreenDeviceContext();

    // Update the escapement exactly as LABEL does.
    // While GetTextExtentPoint claims that it ignores this value,
    // it returns slightly different sizes depending on the angle,
    // which looks like its due to variation in intercharacter spacing.
    FontRec.lfEscapement = (360.0 - (g_SelectedTurtle->Heading - 90.0)) * 10;

    // get a handle to the label's font
    HFONT tempFont = CreateFontIndirect(&FontRec);
    if (tempFont != NULL)
    {
        HFONT oldFont = (HFONT) SelectObject(screen, tempFont);

        GetTextExtentPoint(screen, s, wcslen(s), &size);

        // restore the original font
        SelectObject(screen, oldFont);

        DeleteObject(tempFont);
    }

    return size;
}

void label(const wchar_t *s)
{
    ASSERT_TURTLE_INVARIANT;

    wxPoint dest;
    if (!WorldCoordinateToScreenCoordinate(g_SelectedTurtle->Position, dest))
    {
        return;
    }

    // memory
    HDC MemDC = GetMemoryDeviceContext();

    SetBkColor(MemDC, scolor);
    SetBkMode(MemDC, TRANSPARENT);

    if (GetPenStateForSelectedTurtle().IsErasing)
    {
        SetTextColor(MemDC, scolor);
    }
    else
    {
        SetTextColor(MemDC, pcolor);
    }


    // Update the "escapement", which is the angle at which the text
    // is rendered (baseline angle), in 10ths of a degree from positive X.
    // Because the device contexts are in GM_COMPATIBLE mode, the
    // lfEscapement will take priority over the lfOrientation, so that
    // all characters follow the escapement.
    FontRec.lfEscapement = (360.0 - (g_SelectedTurtle->Heading - 90.0)) * 10;

    HFONT tempFont = CreateFontIndirect(&FontRec);
    HFONT oldFont = (HFONT) SelectObject(MemDC, tempFont);

    TextOut(
        MemDC,
        +dest.x + xoffset,
        -dest.y + yoffset,
        s,
        wcslen(s));

    SelectObject(MemDC, oldFont);


    // screen
    HDC ScreenDC = GetScreenDeviceContext();
    SetBkColor(ScreenDC, scolor);
    SetBkMode(ScreenDC, TRANSPARENT);

    if (GetPenStateForSelectedTurtle().IsErasing)
    {
        SetTextColor(ScreenDC, scolor);
    }
    else
    {
        SetTextColor(ScreenDC, pcolor);
    }

    oldFont = (HFONT) SelectObject(ScreenDC, tempFont);

    if (zoom_flag)
    {
        // no need to erase, we're just drawing over it
        InvalidateRect(GetScreenWindow(), NULL, FALSE);
    }
    else
    {
        TextOut(
            ScreenDC,
            +dest.x - GetScreenHorizontalScrollPosition() + xoffset,
            -dest.y - GetScreenVerticalScrollPosition()   + yoffset,
            s,
            wcslen(s));
    }

    SelectObject(ScreenDC, oldFont);
    DeleteObject(tempFont);
}

#endif

void checkwindow(int *x, int *y, int *w, int *h)
{
    const wxRect & displayRect = wxGetClientDisplayRect();

    int minX      = displayRect.GetLeft();
    int minY      = displayRect.GetTop();
    int maxWidth  = displayRect.GetWidth();
    int maxHeight = displayRect.GetHeight();

    // sanity check window coordinates
    if (*x < minX)
    {
        *x = minX;
    }
    if (*y < minY) 
    {
        *y = minY;
    }
    if (*w > maxWidth) 
    {
        *w = maxWidth;
    }
    if (*h > maxHeight) 
    {
        *h = maxHeight;
    }

    // Move the window so that it's on-screen.
    if (*x + *w > displayRect.GetRight())
    {
        *x = displayRect.GetRight() - *w;
    }
    if (*y + *h > displayRect.GetBottom())
    {
        *y = displayRect.GetBottom() - *h;
    }
}

void MyMessageScan()
{
    // depending on yield flag check for messages
    if (yield_flag)
    {
#ifndef WX_PURE
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If this is a keydown event, then it might be a keyboard shortcut.
            // Checking this before calling TranslateKeyboardShortcut is an
            // optimization.
            if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN)
            {
                if (TranslateKeyboardShortcut(msg))
                {
                    // This message represents a keyboard shortcut and it
                    // has been and dispatched appropriately.
                    // Move on to the next message.
                    continue;
                }
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#endif
    }
}


void init_videomode()
{
#ifdef WX_PURE
    // Choose dialog units that map 1:2 to pixels
    // This creates dialog close to the way MSWLogo did.
    BaseUnitsx = 8;
    BaseUnitsy = 16;
#else
    // Get Dialog Units for Controls
    BaseUnitsx = LOWORD(GetDialogBaseUnits());
    BaseUnitsy = HIWORD(GetDialogBaseUnits());
#endif
}

void init_bitmaps()
{
    // allocate the array of bitmaps
    g_BitmapsLimit   = 1;
    g_Bitmaps        = (CUTMAP *) calloc(sizeof(*g_Bitmaps), g_BitmapsLimit);
    g_SelectedBitmap = &g_Bitmaps[0];
}

void uninit_bitmaps()
{
    // Note Bitmap index 0 belongs to clipboard
    for (CUTMAP* bmp = g_Bitmaps + 1;
         bmp < g_Bitmaps + g_BitmapsLimit;
         bmp++)
    {
        if (bmp->IsValid)
        {
#ifndef WX_PURE
            DeleteObject(bmp->MemoryBitMap);
#endif
        }

        free(bmp->Pixels);
    }

    free(g_Bitmaps);
}

void init_penstate()
{
    g_PenState.Color.red   = 0x00;
    g_PenState.Color.green = 0x00;
    g_PenState.Color.blue  = 0x00;
    g_PenState.Width     = 1;
    g_PenState.Mode      = COPY_PUT;
    g_PenState.IsErasing = false;
}


void init_turtles()
{
    g_TurtlesLimit = 1;
    g_MaxTurtle    = 0;
    g_Turtles      = (Turtle *) calloc(sizeof(*g_Turtles), g_TurtlesLimit);
    g_SelectedTurtle = &g_Turtles[g_MaxTurtle];

    InitializeTurtle(g_SelectedTurtle);

    // init the special turtles
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].IsSpecial   = true;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].IsSpecial = true;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].IsSpecial   = true;
}

void uninit_turtles()
{
    free(g_Turtles);
}

void exit_program()
{
    if (is_executing())
    {
        IsTimeToHalt = true;
    }
    IsTimeToExit = true;
}
