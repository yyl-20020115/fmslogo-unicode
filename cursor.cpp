/*
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
   #include <wx/cursor.h>
   #include <wx/window.h>

   #include "cursor.h"
   #include "init.h"
   #include "screenwindow.h"
   #include "logocore.h"
   #include "debugheap.h"
#endif


NODE *lsetcursorwait(NODE *)
{
	wxWindow* mainWindow = GetMainWxWindow();

	if (mainWindow != 0)
	{
		mainWindow->SetCursor(*wxHOURGLASS_CURSOR);
	}
    return Unbound;
}

NODE *lsetcursorarrow(NODE *)
{
	wxWindow* mainWindow = GetMainWxWindow();

	if (mainWindow != 0)
	{
		mainWindow->SetCursor(wxNullCursor);
	}
    return Unbound;
}

void init_cursors()
{
}
