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

#ifndef __UTILS_H
#define __UTILS_H
#include <wx/string.h>
void SetConfigurationInt(
    const wxString&     Name,
    int                 Value
    );

int GetConfigurationInt(
    const wxString&     Name,
    int                 DefaultValue
    );

void SetConfigurationString(
    const wxString&        Name,
    const wxString&        Value
    );

wxString GetConfigurationString(
    const wxString&        Name,
    const wxString&        DefaultValue
    );

void GetConfigurationQuadruple(
    const wxString&     Name,
    int &               Value1,
    int &               Value2,
    int &               Value3,
    int &               Value4
    );

void SetConfigurationQuadruple(
    const wxString&     Name,
    int                 Value1,
    int                 Value2,
    int                 Value3,
    int                 Value4
    );

#ifdef _WINDOWS
void GetConfigurationFont(
    const wxString&   Name,
    LOGFONT&   LogFont
    );

void SetConfigurationFont(
    const wxString&   Name,
    const LOGFONT &   LogFont
    );
#endif
#endif // __UTILS_H_
