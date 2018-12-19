// -*- c++ -*-
#include <wx/string.h>

// WXSTRING - converts from const char * to wxString
#if wxUSE_UNICODE
//#define WXSTRING(STRING) wxString(STRING/*, wxConvISO8859_1*/)
#else
#define WXSTRING(STRING) wxString(STRING)
#endif

// WXSTRING_TO_STRING - converts from wxString to const char *.
// Note: because there is data loss in the conversion, every instance
// of this macro should be considered a bug.
#if wxUSE_UNICODE
//#define WXSTRING_TO_STRING(STRING) STRING /*((STRING).mb_str(wxConvUTF8).data())*/
#else
#define WXSTRING_TO_STRING(STRING) static_cast<const char*>((STRING).c_str())
#endif

// WXCHAR_TO_STRING - converts from wxChar * to const char *.
// Note: because there is data loss in the conversion, every instance
// of this macro should be considered a bug.
//#define WXCHAR_TO_STRING(STRING) WXSTRING_TO_STRING(WXSTRING(STRING))
