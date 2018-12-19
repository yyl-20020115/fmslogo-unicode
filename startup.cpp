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
    #ifndef WX_PURE
        #include <windows.h>

        #ifdef max // MS compilers #define max in windows.h
            #undef max
        #endif
    #endif

    #include <algorithm>
    #include <string.h>

    #include <wx/defs.h>
    #include <wx/string.h>
    #include <wx/filename.h>

    #include "startup.h"
    #include "activearea.h"
    #include "graphwin.h"
    #include "utils.h"
    #include "fmslogo.h"
    #include "stringadapter.h"
    #include "debugheap.h"

    #include "localizedstrings.h"
#endif

Color dfld;                        // Current flood color
Color dscn;                        // Current screen color

wxString * g_LibPathName = NULL;          // path to library
wxString * g_HelpFileName = NULL;         // path to help file
wchar_t TempPathName[MAX_PATH + 1] = { 0 };   // path to temp edit file
wchar_t TempBmpName[MAX_PATH + 1] = { 0 };    // path to temp bitmap file
wchar_t TempClipName[MAX_PATH + 1] = { 0 };   // path to temp clipboard file

wxUint32 scolor;                   // screen color
wxUint32 fcolor;                   // flood color
wxUint32 pcolor;                   // pen color

wxString g_FmslogoBaseDirectory; // The directory that contains fmslogo.exe

// Creates path relative to the directory in which FMSLogo is installed.
void MakeHelpPathName(wchar_t *OutBuffer, const wchar_t * TheFileName)
{
    wcsncpy(OutBuffer, g_FmslogoBaseDirectory, MAX_PATH);
    wcsncat(OutBuffer, TheFileName, MAX_PATH - wcslen(OutBuffer));
}

// Creates a unique filename relative to TempPath
static
void MakeTempFilename(wchar_t *OutBuffer, const wchar_t * TempPath, const wchar_t * FileName)
{
    // the first part of the temp filename is TempPath
	wchar_t * ptr       = OutBuffer;
    const wchar_t * src = TempPath;
    while (*src != L'\0')
    {
        *ptr++ = *src++;
    }

    // make sure that the path ends in a directory delimiter
    if (*ptr != L'\\')
    {
        *ptr++ = L'\\';
    }
   
    // append the filename
    wcscpy(ptr, FileName);
}

void init_graphics()
{
    // set appropriate default colors
    pcolor = 0x00000000;
    scolor = 0x00FFFFFF;
    fcolor = 0x00000000;

    dfld.red   = 0x00;
    dfld.green = 0x00;
    dfld.blue  = 0x00;

    dscn.red   = 0xFF;
    dscn.green = 0xFF;
    dscn.blue  = 0xFF;

#ifndef WX_PURE
    // init the font structure
    FontRec.lfHeight         = 24;
    FontRec.lfWidth          = 0;
    FontRec.lfOrientation    = 0;
    FontRec.lfWeight         = 400;
    FontRec.lfItalic         = 0;
    FontRec.lfUnderline      = 0;
    FontRec.lfStrikeOut      = 0;
    FontRec.lfCharSet        = ANSI_CHARSET;
    FontRec.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    FontRec.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    FontRec.lfQuality        = DEFAULT_QUALITY;
    FontRec.lfPitchAndFamily = DEFAULT_PITCH;
    wcscpy(FontRec.lfFaceName, L"Arial");
#endif

    // Set handy rectangle of full bitmap
    g_FullRect.SetWidth(BitMapWidth);
    g_FullRect.SetHeight(BitMapHeight);

    // turtle coords are in center
    xoffset = BitMapWidth  / 2;
    yoffset = BitMapHeight / 2;

    // Init active area even if off
    g_PrinterAreaXLow  = -BitMapWidth  / 2;
    g_PrinterAreaXHigh = +BitMapWidth  / 2;
    g_PrinterAreaYLow  = -BitMapHeight / 2;
    g_PrinterAreaYHigh = +BitMapHeight / 2;

    g_PrinterAreaPixels = std::max(BitMapWidth, BitMapHeight) / 8;

    // init paths to library and help files based on location of .EXE
    wxString fmslogoDirectory =(g_FmslogoBaseDirectory);

    const wxFileName libPathName(fmslogoDirectory + wxString(L"logolib/"));
    g_LibPathName  = new wxString(libPathName.GetPathWithSep());

    const wxFileName helpFileName(fmslogoDirectory + wxString(L"logohelp.chm"));
    g_HelpFileName = new wxString(helpFileName.GetFullPath());

//#ifdef WX_PURE
//    const char * tempPath = getenv("TMP");
//    if (tempPath == NULL)
//    {
//        tempPath = "~";
//    }
//#else
    DWORD tempPathLength;

	wchar_t  tempPath[MAX_PATH + 1] = { 0 };
    bool  tempPathIsValid = false;

    tempPathLength = GetTempPath(
        sizeof(tempPath)/sizeof(wchar_t),
        tempPath);
    if (tempPathLength != 0)
    {
        DWORD tempPathAttributes = GetFileAttributes(tempPath);
        if (tempPathAttributes != 0xFFFFFFFF)
        {
            // tempPath must be a directory that we can write to
            if ( (tempPathAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                 !(tempPathAttributes & FILE_ATTRIBUTE_READONLY))
            {
                tempPathIsValid = true;
            }
        }
    }

    if (!tempPathIsValid)
    {
        // warn the user that no TMP variable was defined.
        MessageBox(
            0,
            LOCALIZED_ERROR_TMPNOTDEFINED,
            LOCALIZED_WARNING,
            MB_OK);

        wcscpy(tempPath, L"C:");
    }
//#endif

    // construct the name of the temporary editor file
    MakeTempFilename(TempPathName, tempPath, L"mswlogo.tmp");

    // construct the name of the temporary bitmap file
    MakeTempFilename(TempBmpName, tempPath, L"mswlogo.bmp");

    // construct the name of the clipboard file
    MakeTempFilename(TempClipName, tempPath, L"mswlogo.clp");

    g_PrinterAreaXLow   = GetConfigurationInt(L"Printer.Xlow",  -BitMapWidth  / 2);
    g_PrinterAreaXHigh  = GetConfigurationInt(L"Printer.XHigh", +BitMapWidth  / 2);
    g_PrinterAreaYLow   = GetConfigurationInt(L"Printer.Ylow",  -BitMapHeight / 2);
    g_PrinterAreaYHigh  = GetConfigurationInt(L"Printer.YHigh", +BitMapHeight / 2);
    g_PrinterAreaPixels = GetConfigurationInt(L"Printer.Pixels", std::max(BitMapWidth, BitMapHeight) / 8);
}

void uninit_graphics()
{
    delete g_LibPathName;
    g_LibPathName = NULL;

    delete g_HelpFileName;
    g_HelpFileName = NULL;
}
