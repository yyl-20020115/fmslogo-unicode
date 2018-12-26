/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
  #include "argumentutils.h"
#include "logodata.h"
  #include "logocore.h"
  #include "print.h"
  #include "debugheap.h"
#include<wx/string.h>
#include "CStringTextStream.h"
#endif

wxString cnv_strnode_string(NODE * arg)
{
	CStringTextStream cts;

	PrintNodeToString(car(arg),&cts);

	return cts.GetContent();
}

wxString NormalizeCaseForDisplay(wxString text) {
	wxString ret;
	if (text.length() > 0) {
		wchar_t* buffer = (wchar_t*)malloc(sizeof(wchar_t)*(text.length() + 1));
		if (buffer != 0) {
			memset(buffer, 0, sizeof(buffer));
			NormalizeCaseForDisplay(buffer, text, text.length());
			ret = buffer;
			free(buffer);
		}
	}

	return ret;
}

wxString cap_strnzcpy(wxString text)
{
	wxString ret;
	if (text.length() > 0) {
		wchar_t* buffer = (wchar_t*)malloc(sizeof(wchar_t)*(text.length() + 1));
		if (buffer != 0) {
			memset(buffer, 0, sizeof(buffer));
			cap_strnzcpy(buffer, text, text.length());
			ret = buffer;
			free(buffer);
		}
	}

	return ret;
}