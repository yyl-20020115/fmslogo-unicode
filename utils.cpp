/*
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
 */

// This file implements functions for saving and reading global configuration
// options.  It has a Windows-specific native implementation in addition to the
// WX_PURE portion to ensure that configuration set in older version of FMSLogo
// continue to work.  This could be rewritten to be platform-independent if the
// installer included some migration logic to move from the legacy FMSLogo format
// to a wxWidgets-compatible format.

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER

    #ifndef WX_PURE
        #include <windows.h>
    #endif

    #include <stdio.h>
    #include <string.h>
    #include <wx/config.h>
    #include "stringadapter.h"

    #include "localizedstrings.h"
//    #include "debugheap.h"

#endif

#ifndef WX_PURE

// the name of the FMSLogo registry key under HKCU
const wchar_t FMSLOGO_REGISTRY_KEY_NAME[] = L"Software\\FMSLogo";

// manifest constants to help protect against typos
const wchar_t FONTPROPERTY_FaceName[]       = L"FaceName";
const wchar_t FONTPROPERTY_Height[]         = L"Height";
const wchar_t FONTPROPERTY_Weight[]         = L"Weight";
const wchar_t FONTPROPERTY_Italic[]         = L"Italic";
const wchar_t FONTPROPERTY_CharSet[]        = L"CharSet";
const wchar_t FONTPROPERTY_OutPrecision[]   = L"OutPrecision";
const wchar_t FONTPROPERTY_ClipPrecision[]  = L"ClipPrecision";
const wchar_t FONTPROPERTY_Quality[]        = L"Quality";
const wchar_t FONTPROPERTY_PitchAndFamily[] = L"PitchAndFamily";

static HKEY OpenFmsLogoKeyForSettingValue()
{
    HKEY fmslogoKey = 0;

    // Use RegCreateKeyEx() instead of RegOpenKeyEx() because
    // the key may not already exist.  For example, if FMSlogo 
    // were "installed" with XCOPY or by uncompressing a ZIP file.

    LONG result = RegCreateKeyEx(
        HKEY_CURRENT_USER,
        FMSLOGO_REGISTRY_KEY_NAME,
        0,      // reserved
        NULL,   // ignored
        REG_OPTION_NON_VOLATILE,
        KEY_SET_VALUE,
        NULL,   // default security attributes
        &fmslogoKey,
        NULL);  // don't care if the key already existed
    if (result != ERROR_SUCCESS)
    {
        // failed!
        fmslogoKey = NULL;
    }

    return fmslogoKey;
}

static HKEY OpenFmsLogoKeyForGettingValue()
{
    HKEY fmslogoKey = 0;

    LONG result = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        FMSLOGO_REGISTRY_KEY_NAME,
        0, // reserved
        KEY_QUERY_VALUE,
        &fmslogoKey);
    if (result != ERROR_SUCCESS)
    {
        // failed!
        fmslogoKey = NULL;
    }

    return fmslogoKey;
}

#endif // !define WX_PURE

void SetConfigurationInt(
    const wxString&  Name,
    int              Value
    )
{
#ifdef WX_PURE
    wxConfig config("fmslogo");
    config.Write(Name, Value);
#else
    HKEY fmslogoKey = OpenFmsLogoKeyForSettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD value          = static_cast<DWORD>(Value);
        const BYTE *valuePtr = reinterpret_cast<BYTE*>(&value);

        RegSetValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            REG_DWORD,
            valuePtr,
            sizeof value);

        RegCloseKey(fmslogoKey);
    }
#endif // WX_PURE    
}

int GetConfigurationInt(
    const wxString&     Name,
    int                 DefaultValue
    )
{
#ifdef WX_PURE
    wxConfig config("fmslogo");
    long longValue = config.ReadLong((Name), DefaultValue);
    return longValue;
#else    
    int returnValue = DefaultValue;

    HKEY fmslogoKey = OpenFmsLogoKeyForGettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD value = 0;
        DWORD valueSize = sizeof(value);
        BYTE *valuePtr  = reinterpret_cast<BYTE*>(&value);
        DWORD type      = REG_DWORD;

        LONG result = RegQueryValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            &type,
            valuePtr,
            &valueSize);
        if (result    == ERROR_SUCCESS && 
            type      == REG_DWORD     &&
            valueSize == sizeof(value))
        {
            // we successfully read the value as a DWORD
            returnValue = value;
        }

        RegCloseKey(fmslogoKey);
    }

    return returnValue;
#endif // WX_PURE    
}

void SetConfigurationString(
    const wxString&        Name,
    const wxString&        Value
    )
{
#ifdef WX_PURE
    wxConfig config("fmslogo");
    config.Write((Name), (Value));
#else
    HKEY fmslogoKey = OpenFmsLogoKeyForSettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD valueLength    = (Value.length() + 1) * sizeof(wchar_t);   // include NUL
        const BYTE *valuePtr = reinterpret_cast<const BYTE*>((const wchar_t*)Value);

        RegSetValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            REG_SZ,
            valuePtr,
            valueLength);

        RegCloseKey(fmslogoKey);
    }
#endif // WX_PURE    
}

wxString GetConfigurationString(
    const wxString&        Name,
    const wxString&        DefaultValue
    )
{
	wxString              Value;

#ifdef WX_PURE    
    wxConfig config("fmslogo");
    Value = config.Read(Name, (DefaultValue));

#else
    bool useDefaultValue = true;

    HKEY fmslogoKey = OpenFmsLogoKeyForGettingValue();
    if (fmslogoKey != NULL)
    {
		size_t nc = 4096;
		BYTE* valuePtr = (BYTE*)malloc(sizeof(wchar_t) * (nc+1));
		memset(valuePtr, 0, sizeof(wchar_t)*(nc + 1));
   		DWORD valueSize = sizeof(wchar_t)* nc;  // leave room for NUL
        DWORD valueType = 0;
        LONG result = RegQueryValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            &valueType,
            valuePtr,
            &valueSize);
        if (result == ERROR_SUCCESS && 
            valueType == REG_SZ)
        {
			*(wchar_t*)(valuePtr + valueSize) = L'\0';
			Value = (wchar_t*)valuePtr;
            // we successfully read the value as a string
            useDefaultValue  = false;
        }

        RegCloseKey(fmslogoKey);
		if (valuePtr != 0) {
			free(valuePtr);
		}
	}

    if (useDefaultValue)
    {
		Value = DefaultValue;
	}
#endif // WX_PURE
	return Value;
}

void
GetConfigurationQuadruple(
    const wxString&      Name,
    int *               Value1,
    int *               Value2,
    int *               Value3,
    int *               Value4
    )
{
	wxString defaultString=wxString::Format(
        L"%d,%d,%d,%d",
        *Value1,
        *Value2,
        *Value3,
        *Value4);

	
    // Get the quadruple from the configuration settings
    wxString outputString = GetConfigurationString(
        Name,
        defaultString);

    // Decode the quadruple string into numbers
    wchar_t * cp = const_cast<wchar_t*>((const wchar_t*)outputString);

    *Value1 = (int)wcstol(cp, &cp, 10);
    cp++;

    *Value2 = (int)wcstol(cp, &cp, 10);
    cp++;

    *Value3 = (int)wcstol(cp, &cp, 10);
    cp++;

    *Value4 = (int)wcstol(cp, &cp, 10);
}


void
SetConfigurationQuadruple(
    const wxString&        Name,
    int                 Value1,
    int                 Value2,
    int                 Value3,
    int                 Value4
    )
{
	wxString quadruple = wxString::Format(L"%d,%d,%d,%d",
        Value1,
        Value2,
        Value3,
        Value4);

    // Set the quadruple in the configuration.
    SetConfigurationString(Name, quadruple);
}

#ifndef WX_PURE
void GetConfigurationFont(
    const wxString& Name,
    LOGFONT  &   LogFont
    )
{
    memset(&LogFont, 0, sizeof(LogFont));

    // find the end of the fullyQualifiedName
	wxString relativeName = Name + L'.';
   
    wxString ret = GetConfigurationString(
        relativeName + FONTPROPERTY_FaceName,
        GetResourceString(L"LOCALIZED_DEFAULT_FONT_FACE"));

	if (ret.length() > 0) {
		wcsncpy(LogFont.lfFaceName, (const wchar_t*)ret, LF_FACESIZE);
	}

    LogFont.lfHeight = GetConfigurationInt(relativeName + FONTPROPERTY_Height, -13);

    LogFont.lfWeight = GetConfigurationInt(relativeName + FONTPROPERTY_Weight, 400);

    LogFont.lfItalic = GetConfigurationInt(relativeName + FONTPROPERTY_Italic, 0);

    LogFont.lfCharSet = GetConfigurationInt(relativeName + FONTPROPERTY_CharSet, 0);

    LogFont.lfOutPrecision = GetConfigurationInt(relativeName + FONTPROPERTY_OutPrecision, 1);

    LogFont.lfClipPrecision = GetConfigurationInt(relativeName + FONTPROPERTY_ClipPrecision, 2);

    LogFont.lfQuality = GetConfigurationInt(relativeName + FONTPROPERTY_Quality, 1);

    LogFont.lfPitchAndFamily = GetConfigurationInt(relativeName + FONTPROPERTY_PitchAndFamily, 49);
}

void
SetConfigurationFont(
    const wxString&    Name,
    const LOGFONT  &   LogFont
    )
{
    // find where the relative property name should start
	wxString relativeName = Name + L'.';

    SetConfigurationString(relativeName + FONTPROPERTY_FaceName, LogFont.lfFaceName);

    const struct PROPERTY {
        const wchar_t * Name;
        int Value;
    } properties[] = {
        {FONTPROPERTY_Height,          LogFont.lfHeight},
        {FONTPROPERTY_Weight,          LogFont.lfWeight},
        {FONTPROPERTY_Italic,          LogFont.lfItalic},
        {FONTPROPERTY_CharSet,         LogFont.lfCharSet},
        {FONTPROPERTY_OutPrecision,    LogFont.lfOutPrecision},
        {FONTPROPERTY_ClipPrecision,   LogFont.lfClipPrecision},
        {FONTPROPERTY_Quality,         LogFont.lfQuality},
        {FONTPROPERTY_PitchAndFamily,  LogFont.lfPitchAndFamily},
    };

    for (size_t i = 0; i < sizeof(properties) / sizeof(*properties); i++)
    {
        SetConfigurationInt(relativeName + properties[i].Name, properties[i].Value);
    }
}

#endif // !defined WX_PURE
