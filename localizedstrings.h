#ifndef _LOCALIZEDSTRINGS_H_
#define _LOCALIZEDSTRINGS_H_ 

#include "version.h"
#ifdef USE_LOCALIZEDSTRINGS_HEADER_FILES
//
// LOCALE -
//   The LCID, as defined by Windows.
//
// CHARSETID -
//   The ID of the ANSI character set used by the locale.
//
// MANUAL_HAS_TRANSLATION_TABLES -
//   Whether or not the maual for a given locale has translation
//   tables for going between the English command names and the 
//   command names for a particular locale.
//
//   Values:
//    0 - no translation table exists
//    1 - a translation table exists
//

// This file includes the proper header file for this locale.
#ifndef LOCALE

  #error LOCALE is not defined

#elif LOCALE == 1031
  
  #include "localizedstrings-de.h"  // German
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 0

#elif LOCALE == 1032
  
  #include "localizedstrings-gr.h"  // Greek
  #define  CHARSETID 1253
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 1033

  #include "localizedstrings-en.h"  // English
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 0

#elif LOCALE == 1034

  #include "localizedstrings-es.h"  // Spanish
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 1036

  #include "localizedstrings-fr.h"  // French
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 1040

  #include "localizedstrings-it.h"  // Italian
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 1045

  #include "localizedstrings-pl.h"  // Polish
  #define  CHARSETID 1250
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 1049

  #include "localizedstrings-ru.h"  // Russian
  #define  CHARSETID 1251
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 1050

  #include "localizedstrings-hr.h"  // Croatian
  #define  CHARSETID 1250
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#elif LOCALE == 2052

  #include "localizedstrings-zh-cn.h"  // Simplified Chinese
  #define  CHARSETID 936
  #define  MANUAL_HAS_TRANSLATION_TABLES 0

#elif LOCALE == 2070

  #include "localizedstrings-pt.h"  // Portuguese
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 0

#elif LOCALE == 9999

  #include "localizedstrings-ps.h"  // Pseudoloc
  #define  CHARSETID 1252
  #define  MANUAL_HAS_TRANSLATION_TABLES 1

#else

  #error LOCALE is an unknown value!

#endif 
#endif

#define N_LOCALIZED_STRINGS_FILE_TYPE L"LOCALIZED_STRINGS_FILE"

#define N_LOCALIZED_STRINGS_FILE_START  L"localizedstrings-"
#define N_LOCALIZED_STRINGS_FILE_END    L"-ucs2le.h"
#define N_LOCALIZED_STRINGS_FILE_DE		L"de"
#define N_LOCALIZED_STRINGS_FILE_EN		L"en"
#define N_LOCALIZED_STRINGS_FILE_ES		L"es"
#define N_LOCALIZED_STRINGS_FILE_FR		L"fr"
#define N_LOCALIZED_STRINGS_FILE_GR		L"gr"
#define N_LOCALIZED_STRINGS_FILE_HR		L"hr"
#define N_LOCALIZED_STRINGS_FILE_IT		L"it"
#define N_LOCALIZED_STRINGS_FILE_PL		L"pl"
#define N_LOCALIZED_STRINGS_FILE_PS		L"ps"
#define N_LOCALIZED_STRINGS_FILE_PT		L"pt"
#define N_LOCALIZED_STRINGS_FILE_RU		L"ru"
#define N_LOCALIZED_STRINGS_FILE_ZH_CN	L"zh_cn"


#define N_LC_DE		L"German"
#define N_LC_EN		L"English"
#define N_LC_ES		L"Spanish"
#define N_LC_FR		L"French"
#define N_LC_GR		L"Greek"
#define N_LC_HR		L"Croatian"
#define N_LC_IT		L"Italian"
#define N_LC_PL		L"Polish"
#define N_LC_PS		L"Pseudoloc"
#define N_LC_PT		L"Portuguese"
#define N_LC_RU		L"Russian"
#define N_LC_ZH_CN	L"936"




void LoadLocalizedStringsFromFile(const class wxString& path);
void LoadLocalizedStringsFromResource(const class wxString& name,const class wxString& type);
void LoadLocalizedStringsFromStream(class CTextStream* stream);

extern const class wxString& GetResourceString(const wchar_t* Name);
#endif //  _LOCALIZEDSTRINGS_H_
