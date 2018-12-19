#ifndef _LOCALIZEDSTRINGS_H_
#define _LOCALIZEDSTRINGS_H_ 

#include "version.h"

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

#endif //  _LOCALIZEDSTRINGS_H_
