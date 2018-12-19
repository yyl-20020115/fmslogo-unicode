#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #ifdef __WXMSW__
   #  include <windows.h>  // for LOGFONT
   #endif

   #include <wx/fontutil.h>

   #include "utils.h"
   #include "graphwin.h"
#endif

#ifdef __WXMSW__

static
const wxFont
LogFontToWxFont(
    LOGFONT * NativeLogicalFont
    )
{
    // note: this was copied from wxNativeFontInfo::ToString() in src/msw/font.cpp
    wxString nativeInfo;
    nativeInfo.Printf(
        L"%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s",
        0, // version
        NativeLogicalFont->lfHeight,
        NativeLogicalFont->lfWidth,
        NativeLogicalFont->lfEscapement,
        NativeLogicalFont->lfOrientation,
        NativeLogicalFont->lfWeight,
        NativeLogicalFont->lfItalic,
        NativeLogicalFont->lfUnderline,
        NativeLogicalFont->lfStrikeOut,
        NativeLogicalFont->lfCharSet,
        NativeLogicalFont->lfOutPrecision,
        NativeLogicalFont->lfClipPrecision,
        NativeLogicalFont->lfQuality,
        NativeLogicalFont->lfPitchAndFamily,
        NativeLogicalFont->lfFaceName);

    wxFont font;
    font.SetNativeFontInfo(nativeInfo);

    return font;
}

#endif

void
GetConfigurationFont(
    const wchar_t * ConfigName,
    wxFont &     Font
    )
{
#ifdef __WXMSW__
    // Get the font
    LOGFONT nativeFont;
    GetConfigurationFont(ConfigName, nativeFont);

    // Convert it to a wxFont
    Font = LogFontToWxFont(&nativeFont);
#else
    // TODO: figure out what to do on GNU/Linux
#endif
}


// Set this as the new default font
void
SetConfigurationFont(
    const wchar_t *   ConfigName,
    const wxFont & Font
    )
{
#ifdef __WXMSW__

    // Get the LOGFONT struct from the wxFont
    const wxNativeFontInfo * nativeFontInfo = Font.GetNativeFontInfo();
    if (nativeFontInfo != NULL)
    {
        // save the new font preference to persistent storage
        SetConfigurationFont(ConfigName, nativeFontInfo->lf);
    }
#else
    // TODO: figure out what to do on GNU/Linux
#endif
}

const wxFont
GetLabelFont()
{
#ifdef __WXMSW__
    return LogFontToWxFont(&FontRec);
#else
    // TODO: Figure out what to do on GNU/Linux
    return wxFont();
#endif
}
