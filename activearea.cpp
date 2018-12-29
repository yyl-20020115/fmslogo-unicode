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

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "activearea.h"
   #include "FMSLogo.h"
   #include "logocore.h"
   #include "graphics.h"
   #include "eval.h"
   #include "error.h"
   #include "utils.h"
   #include "logodata.h"
   #include "init.h"
   #include "debugheap.h"
#endif

// Active area dimensions
int g_PrinterAreaXLow;
int g_PrinterAreaXHigh;
int g_PrinterAreaYLow;
int g_PrinterAreaYHigh;
int g_PrinterAreaPixels;

bool IsActiveAreaOneToOneWithScreen()
{
    bool isOneToOne;

    if ((g_PrinterAreaXLow  == -BitMapWidth  / 2) &&
        (g_PrinterAreaXHigh == +BitMapWidth  / 2) &&
        (g_PrinterAreaYLow  == -BitMapHeight / 2) &&
        (g_PrinterAreaYHigh == +BitMapHeight / 2))
    {
        isOneToOne = true;
    }
    else
    {
        isOneToOne = false;
    }

    return isOneToOne;
}

NODE *lsetactivearea(NODE *args)
{
    NODE * vector = int_vector_4_arg(args);
    while (NOT_THROWING)
    {
        // All arguments are integers.
        const NODE * xLowNode  = car(vector);
        const NODE * yLowNode  = car(cdr(vector));
        const NODE * xHighNode = car(cdr(cdr(vector)));
        const NODE * yHighNode = car(cdr(cdr(cdr(vector))));

        const int xLow  = getint(xLowNode);
        const int yLow  = getint(yLowNode);
        const int xHigh = getint(xHighNode); 
        const int yHigh = getint(yHighNode); 

        // Confirm that the four integers defines a positive area.
        if (xLow < xHigh && yLow < yHigh)
        {
            // Now that we have validated the input, we can commit to it
            g_PrinterAreaXLow  = xLow;
            g_PrinterAreaYLow  = yLow;
            g_PrinterAreaXHigh = xHigh; 
            g_PrinterAreaYHigh = yHigh; 

            SetConfigurationInt(L"Printer.XLow",   g_PrinterAreaXLow);
            SetConfigurationInt(L"Printer.XHigh",  g_PrinterAreaXHigh);
            SetConfigurationInt(L"Printer.YLow",   g_PrinterAreaYLow);
            SetConfigurationInt(L"Printer.YHigh",  g_PrinterAreaYHigh);
            break;
        }

        // This vector of four integers does not define a positive area.
        // Throw a recoverable bad data error to give the programmer
        // a chance to replace it with good data.
        setcar(args, err_logo(BAD_DATA, vector));
        vector = int_vector_4_arg(args);
    }

    return Unbound;
}

NODE *lactivearea(NODE *)
{
    return cons_list(
        make_intnode((FIXNUM) g_PrinterAreaXLow),
        make_intnode((FIXNUM) g_PrinterAreaYLow),
        make_intnode((FIXNUM) g_PrinterAreaXHigh),
        make_intnode((FIXNUM) g_PrinterAreaYHigh));
}
