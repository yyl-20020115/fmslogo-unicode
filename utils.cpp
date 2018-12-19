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
    #include "debugheap.h"

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

static
HKEY
OpenFmsLogoKeyForSettingValue()
{
    HKEY fmslogoKey;

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

static
HKEY
OpenFmsLogoKeyForGettingValue()
{
    HKEY fmslogoKey;

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

void
SetConfigurationInt(
    const wchar_t *        Name,
    int                 Value
    )
{
#ifdef WX_PURE
    wxConfig config("fmslogo");
    config.Write(WXSTRING(Name), Value);
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

int
GetConfigurationInt(
    const wchar_t *        Name,
    int                 DefaultValue
    )
{
#ifdef WX_PURE
    wxConfig config("fmslogo");
    long longValue = config.ReadLong(WXSTRING(Name), DefaultValue);
    return longValue;
#else    
    int returnValue = DefaultValue;

    HKEY fmslogoKey = OpenFmsLogoKeyForGettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD value;
        DWORD valueSize = sizeof value;
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

void
SetConfigurationString(
    const wchar_t *        Name,
    const wchar_t *        Value
    )
{
#ifdef WX_PURE
    wxConfig config("fmslogo");
    config.Write(WXSTRING(Name), WXSTRING(Value));
#else
    HKEY fmslogoKey = OpenFmsLogoKeyForSettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD valueLength    = wcslen(Value) + sizeof(char);   // include NUL
        const BYTE *valuePtr = reinterpret_cast<const BYTE*>(Value);

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

void
GetConfigurationString(
    const wchar_t *        Name,
	wchar_t *              Value,
    size_t              ValueLength,
    const wchar_t *        DefaultValue
    )
{
#ifdef DEBUG
    memset(Value, 0xDD, ValueLength);
#endif

#ifdef WX_PURE    
    wxConfig config("fmslogo");
    wxString value = config.Read(WXSTRING(Name), WXSTRING(DefaultValue));

    // Copy the configuration into the Value buffer
    size_t lengthToCopy = std::min(ValueLength - 1, value.Len());
    memcpy(Value, WXSTRING_TO_STRING(value), lengthToCopy);
    Value[lengthToCopy] = '\0';
#else
    bool useDefaultValue = true;

    HKEY fmslogoKey = OpenFmsLogoKeyForGettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD valueSize = ValueLength - 1;  // leave room for NUL
        BYTE *valuePtr  = reinterpret_cast<BYTE*>(Value);
        DWORD valueType;

        LONG result = RegQueryValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            &valueType,
            valuePtr,
            &valueSize);
        if (result == ERROR_SUCCESS && 
            valueType == REG_SZ     &&
            valueSize < ValueLength - 1)
        {
            // we successfully read the value as a string
            Value[valueSize] = L'\0';
            useDefaultValue  = false;
        }

        RegCloseKey(fmslogoKey);
    }

    if (useDefaultValue)
    {
        wcscpy(Value, DefaultValue);
    }
#endif // WX_PURE
}

void
GetConfigurationQuadruple(
    const wchar_t *        Name,
    int *               Value1,
    int *               Value2,
    int *               Value3,
    int *               Value4
    )
{
	wchar_t defaultString[256];
    wprintf(
        defaultString,
        L"%d,%d,%d,%d",
        *Value1,
        *Value2,
        *Value3,
        *Value4);

	wchar_t outputString[256];

    // Get the quadruple from the configuration settings
    GetConfigurationString(
        Name,
        outputString,
        sizeof(outputString),
        defaultString);

    // Decode the quadruple string into numbers
	wchar_t * cp = outputString;

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
    const wchar_t *        Name,
    int                 Value1,
    int                 Value2,
    int                 Value3,
    int                 Value4
    )
{
	wchar_t quadruple[256];

    wprintf(
        quadruple,
        L"%d,%d,%d,%d",
        Value1,
        Value2,
        Value3,
        Value4);

    // Set the quadruple in the configuration.
    SetConfigurationString(
        Name,
        quadruple);
}

#ifndef WX_PURE

static
wchar_t *
GetRelativeFontPropertyPointer(
	wchar_t *  FullyQualifiedName
    )
{
    // find where the relative property name should start
	wchar_t * relativeName = wcschr(FullyQualifiedName, L'\0');

    // add a '.' to distigush the relative part from the absolute part.
    *relativeName++ = L'.';

    return relativeName;
}

void
GetConfigurationFont(
    const wchar_t * Name,
    LOGFONT  &   LogFont
    )
{
    memset(&LogFont, 0, sizeof(LogFont));

	wchar_t fullyQualifiedName[256];

    wcscpy(fullyQualifiedName, Name);

    // find the end of the fullyQualifiedName
	wchar_t * relativeName = GetRelativeFontPropertyPointer(fullyQualifiedName);
   
    wcscpy(relativeName, FONTPROPERTY_FaceName);
    GetConfigurationString(
        fullyQualifiedName, 
        LogFont.lfFaceName,
        LF_FACESIZE,
        LOCALIZED_DEFAULT_FONT_FACE);

	wcscpy(relativeName, FONTPROPERTY_Height);
    LogFont.lfHeight = GetConfigurationInt(fullyQualifiedName, -13);

	wcscpy(relativeName, FONTPROPERTY_Weight);
    LogFont.lfWeight = GetConfigurationInt(fullyQualifiedName, 400);

	wcscpy(relativeName, FONTPROPERTY_Italic);
    LogFont.lfItalic = GetConfigurationInt(fullyQualifiedName, 0);

	wcscpy(relativeName, FONTPROPERTY_CharSet);
    LogFont.lfCharSet = GetConfigurationInt(fullyQualifiedName, 0);

	wcscpy(relativeName, FONTPROPERTY_OutPrecision);
    LogFont.lfOutPrecision = GetConfigurationInt(fullyQualifiedName, 1);

	wcscpy(relativeName, FONTPROPERTY_ClipPrecision);
    LogFont.lfClipPrecision = GetConfigurationInt(fullyQualifiedName, 2);

	wcscpy(relativeName, FONTPROPERTY_Quality);
    LogFont.lfQuality = GetConfigurationInt(fullyQualifiedName, 1);

	wcscpy(relativeName, FONTPROPERTY_PitchAndFamily);
    LogFont.lfPitchAndFamily = GetConfigurationInt(fullyQualifiedName, 49);
}

void
SetConfigurationFont(
    const wchar_t *       Name,
    const LOGFONT  &   LogFont
    )
{
	wchar_t fullyQualifiedName[256];

	wcscpy(fullyQualifiedName, Name);

    // find where the relative property name should start
	wchar_t * relativeName = GetRelativeFontPropertyPointer(fullyQualifiedName);

	wcscpy(relativeName, FONTPROPERTY_FaceName);
    SetConfigurationString(fullyQualifiedName, LogFont.lfFaceName);

    const struct PROPERTY {
        const wchar_t * Name;
        int          Value;
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
		wcscpy(relativeName, properties[i].Name);
        SetConfigurationInt(fullyQualifiedName, properties[i].Value);
    }
}

#endif // !defined WX_PURE
