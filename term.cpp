/*
 *       term.cpp        terminal cursor control                 dvb
 *
 *       Copyright (C) 1995 by the Regents of the University of California
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "term.h"

    #include "stringprintednode.h"
    #include "commander.h"
    #include "init.h"
    #include "logodata.h"
    #include "debugheap.h"
#endif

NODE *lcleartext(NODE *)
{
    clearcombobox();
    return Unbound;
}


NODE *lcursor(NODE *)
{
    // return cons_list(
    //    make_intnode((FIXNUM)(x_coord-x_margin)),
    //    make_intnode((FIXNUM)(y_coord-y_margin)));

    return cons_list(make_intnode(0), make_intnode(0));
}

NODE *lsetcursor(NODE *  /*args*/)
{
    /*
      NODE *arg;

      arg = pos_int_vector_arg(args); // can now return floats
      if (NOT_THROWING)
      {
      x_coord = x_margin + getint(car(arg));
      y_coord = y_margin + getint(cadr(arg));

      ibm_gotoxy(x_coord, y_coord);

      fflush(stdout);
      }
    */
    return Unbound;
}

NODE *lsetmargins(NODE *  /*args*/)
{
    /*
      NODE *arg;

      arg = pos_int_vector_arg(args); // can now return floats
      if (NOT_THROWING)
      {
      x_margin = getint(car(arg));
      y_margin = getint(cadr(arg));
      lcleartext(NIL);
      }
    */
    return Unbound;
}

NODE *lstandout(NODE *args)
{
    CStringPrintedNode text(car(args));
    return make_strnode(text);
}
