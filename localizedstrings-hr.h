//
// Copyright (C) 2006 by David Costanzo
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

/////////////////////////////////////////////////////////////////////////////
// This file contains localized strings for Croatian by Domagoj Kuna
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Localization Instructions:
//
// This file a C++ header file, so if you are familiar with how C++ works, it
// will help.
//
// Each localized string is a line that takes the following form:
//
//      #define <TOKEN> "<quoted-string>" //<status>
//
//   #define         - is part of C++.  Do not change this.
//   <TOKEN>         - is how the FMSLogo source code refers to the string.
//                     This must not change, regardless of the locale.
//   <quoted-string> - is what fmslogo.exe will use whenever it refers 
//                     to <TOKEN>.  This is bit that must be translated.
//   <status>        - This is some information on whether or not the
//                     string has been localized yet.  For example, is 
//                     someone has localized FMSLogo into French, then I add
//                     a new string, I will append //NOT_YET_LOCALIZED as a
//                     reminder that we need to localized just this one string.
//
// To localize FMSLogo, you must to translate the phrases in <quoted-string>
// from English to your language.  Once you have localized a string, please
// remove the //<status> comment at the end of the line.
//
// If you think that a string should *NOT* be translated (for example "FMSLogo"),
// then just delete the //<status> comment to indicate that you have decided
// not to translate the string.  If you are not sure how to translate a string
// please leave the //<status> comment so that that someone else may investigate
// it.
//
//
// For quoted strings that refer to commands, please refer to the command
// in your language, then put the English form in parentheses.  For example:
//
//   "Can't use TO inside a procedure"
//
// is translated into French as:
//
//   "Impossible d'utiliser POUR (TO) dans une proc?dure"
//
//
// Please note that some of the quoted strings embed a <TOKEN> within them.
// For example, the phrase:
//
//   "I like FMSLogo, do you?"
//
// Might appear as:
//
//   "I like "LOCALIZED_GENERAL_PRODUCTNAME", do you?"
//
// When fmslogo.exe is built, the LOCALIZED_GENERAL_PRODUCTNAME will be 
// replaced with the localized form of FMSLogo and will look like the
// original phrase.  Please only translate the "I like " and ", do you?".
//
// Some of the quoted strings (the ones that appear in menus and buttons)
// have ampersands "&" characters in them.  For example the word "File" 
// may appear as "&File".  This tells Windows that ALT+F should take the
// user straight to this option.
// 
// Some of the quoted strings have a "%p" or a "%s" in them.  For example,
// the error message for when you give bad input looks like this:
//
//    "%p doesn't like %s as input"
//
// The "%p" and "%s" are replaced with the procedure name and the input
// that it doesn't like.  You must NOT add any "%" characters to any string, 
// nor can you change the order in which the %p and %s occur.
//
// There are some special characters that you can add to a string with a 
// special "escape sequence", which begins with a backslash "\".
//
//             +--------------------------------------+
//             | Special Character | Escape Sequence  |
//             +--------------------------------------+
//             |  Tab              |        \t        |
//             |  Newline          |        \n        |
//             |  Backslash        |        \\        |
//             |  DoubleQuote      |        \"        |
//             +--------------------------------------+
//
/////////////////////////////////////////////////////////////////////////////

//
// Localized "alternate" spellings of Logo reserved words
//
#define LOCALIZED_ALTERNATE_TRUE     L"true" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FALSE    L"false" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_END      L"end" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOPLEVEL L"toplevel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SYSTEM   L"system" // NOT_YET_LOCALIZED

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    L"caseignoredp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERRACT          L"erract" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STARTUP         L"startup" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REDEFP          L"redefp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT L"printwidthlimit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT L"printdepthlimit" // NOT_YET_LOCALIZED


//
// Localized "alternate" spellings of Logo primitives.
// These become the perferred name of the primitives.  For example,
// when you press the "reset" button, FMSLogo will write the value of
// LOCALIZED_ALTERNATE_CLEARSCREEN to the commander.
// 
// Furthermore, if one of the LOCALIZED_ALTERNATE names uses the same text 
// as the English counterpart, then the localized name will be used. 
// For example, in the English version, "ct" is short for "CLEARTEXT".
// In the French version, "ct" is short for "CACHETORTUE" (HIDETURTLE).
// So in the French FMSLogo, running "ct" will hide the turtle.
//
// That said, it is strongly recommended that you do not choose names
// that match the long English name of any command.  If you do, you may
// find that some programs won't run on the localized version of FMSLogo.
// 
// If you don't know how to translate a particular command, leave it
// as the English name and it will be ignored.
//
#define LOCALIZED_ALTERNATE__DEFMACRO              L".defmacro" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__EQ                    L".eq" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__MACRO                 L".macro" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".maybeoutput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETBF                 L".setbf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETFIRST              L".setfirst" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETITEM               L".setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"activearea" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ALLOPEN                L"allopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_AND                    L"and" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_APPLY                  L"apply" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARITY                  L"arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  L"array" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAYP                 L"arrayp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY_                 L"array?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ASCII                  L"ascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ASHIFT                 L"ashift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACK                   L"back" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"backslashedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"backslashed?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFOREP                L"beforep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFORE_                L"before?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BF                     L"bf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BFS                    L"bfs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITAND                 L"bitand" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITBLOCK               L"bitblock" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITCOPY                L"bitcopy" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITCUT                 L"bitcut" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITFIT                 L"bitfit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITINDEX               L"bitindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITLOAD                L"bitload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"bitloadsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSIZE                L"bitsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"bitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITMODE                L"bitmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITNOT                 L"bitnot" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITOR                  L"bitor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITPASTE               L"bitpaste" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"bitpastetoindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSAVE                L"bitsave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITXOR                 L"bitxor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BK                     L"bk" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BL                     L"bl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURIED                 L"buried" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURY                   L"bury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTFIRST               L"butfirst" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"butfirsts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTLAST                L"butlast" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"buttoncreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"buttondelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"buttonenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"buttonupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONP                L"buttonp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTON_                L"button?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BYE                    L"bye" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CATCH                  L"catch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHAR                   L"char" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHDIR                  L"chdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"checkboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"checkboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"checkboxenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"checkboxget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"checkboxset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEAN                  L"clean" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"clearpalette" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"clearscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"cleartext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"cleartimer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLOSE                  L"close" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLOSEALL               L"closeall" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CO                     L"co" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"comboboxaddstring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"comboboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"comboboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"comboboxenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"comboboxdeletestring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"comboboxgettext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"comboboxsettext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CONTENTS               L"contents" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CONTINUE               L"continue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COPYDEF                L"copydef" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COS                    L"cos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COUNT                  L"count" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CS                     L"cs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CT                     L"ct" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CURSOR                 L"cursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"debugwindows" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINE                 L"define" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINEDP               L"definedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINED_               L"defined?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"dialogcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"dialogenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"dialogdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"dialogfileopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"dialogfilesave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"difference" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"directories" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DLLCALL                L"dllcall" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DLLFREE                L"dllfree" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DLLLOAD                L"dllload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DOWN                   L"down" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"downpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DRIBBLE                L"dribble" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ED                     L"ed" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EDIT                   L"edit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"ellipsearc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTYP                 L"emptyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTY_                 L"empty?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EOFP                   L"eofp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EOF_                   L"eof?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EQUALP                 L"equalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EQUAL_                 L"equal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ER                     L"er" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASE                  L"erase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASEFILE              L"erasefile" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERF                    L"erf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERROR                  L"error" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"eventcheck" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EXP                    L"exp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FD                     L"fd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FENCE                  L"fence" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FILL                   L"fill" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FILES                  L"files" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FIRST                  L"first" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FIRSTS                 L"firsts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"floodcolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"fontfacenames" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FOREVER                L"forever" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORM                   L"form" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORWARD                L"forward" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FPUT                   L"fput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FS                     L"fs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"fullscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FULLTEXT               L"fulltext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GETFOCUS               L"getfocus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GOTO                   L"goto" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GIFLOAD                L"gifload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GIFSIZE                L"gifsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GIFSAVE                L"gifsave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GPROP                  L"gprop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"greaterequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"greaterequal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATERP               L"greaterp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATER_               L"greater?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"groupboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"groupboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HALT                   L"halt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                L"heading" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HELP                   L"help" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"hideturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HOME                   L"home" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HT                     L"ht" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IF                     L"if" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFELSE                 L"ifelse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFF                    L"iff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFFALSE                L"iffalse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFT                    L"ift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFTRUE                 L"iftrue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"ingameport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORT                 L"inport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORTB                L"inportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INT                    L"int" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ITEM                   L"item" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"keyboardoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"keyboardon" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"keyboardvalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYP                   L"keyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEY_                   L"key?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LABEL                  L"label" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LABELFONT              L"labelfont" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LABELSIZE              L"labelsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LAST                   L"last" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LEFT                   L"left" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LEFTROLL               L"leftroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"lessequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"lessequal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSP                  L"lessp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESS_                  L"less?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIGHT                  L"light" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIST                   L"list" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"listboxaddstring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"listboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"listboxenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"listboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"listboxdeletestring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"listboxgetselect" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTP                  L"listp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIST_                  L"list?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LN                     L"ln" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOAD                   L"load" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOCAL                  L"local" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOG10                  L"log10" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"logoversion" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOWERCASE              L"lowercase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LPUT                   L"lput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LR                     L"lr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LSHIFT                 L"lshift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LT                     L"lt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACHINE                L"machine" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACROP                 L"macrop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACRO_                 L"macro?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MAKE                   L"Make" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MCI                    L"mci" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER                 L"member" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBERP                L"memberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER_                L"member?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"messagebox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"midiclose" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"midimessage" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"midiopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MINUS                  L"minus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MKDIR                  L"mkdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MODULO                 L"modulo" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"mouseoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEON                L"mouseon" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"mousepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAMEP                  L"namep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAME_                  L"name?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAMES                  L"names" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"netacceptoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"netaccepton" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"netacceptreceivevalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"netacceptsendvalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"netconnectoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"netconnecton" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"netconnectreceivevalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"netconnectsendvalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"netshutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"netstartup" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"nobitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NODES                  L"nodes" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"nodribble" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOSTATUS               L"nostatus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOT                    L"not" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"notequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"notequal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOYIELD                L"noyield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBERP                L"numberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBER_                L"number?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OP                     L"op" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"openappend" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENREAD               L"openread" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"openupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENWRITE              L"openwrite" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OR                     L"or" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPORT                L"outport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPORTB               L"outportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPUT                 L"output" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PARSE                  L"parse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PAUSE                  L"pause" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PC                     L"pc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PD                     L"pd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PE                     L"pe" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENCOLOR               L"pencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWN                L"pendown" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWNP               L"pendownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWN_               L"pendown?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENERASE               L"penerase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENMODE                L"penmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENPAINT               L"penpaint" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENPATTERN             L"penpattern" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENREVERSE             L"penreverse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENSIZE                L"pensize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENUP                  L"penup" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"perspective" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PITCH                  L"pitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PIXEL                  L"pixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"playwave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLIST                  L"Plist" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLISTS                 L"plists" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PO                     L"po" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POPDIR                 L"popdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POLYSTART              L"polystart" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POLYEND                L"polyend" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POLYVIEW               L"polyview" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"portclose" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"portflush" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTMODE               L"portmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTOPEN               L"portopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"portreadarray" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"portreadchar" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"portwritearray" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"portwritechar" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POS                    L"pos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POSXYZ                 L"posxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POT                    L"pot" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POWER                  L"power" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PPROP                  L"Pprop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PPT                    L"ppt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PR                     L"pr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"primitivep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"primitive?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINT                  L"print" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"procedurep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"procedure?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLISTP              L"proplistp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLIST_              L"proplist?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURES             L"procedures" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRODUCT                L"product" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PU                     L"pu" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PX                     L"px" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"questionbox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_QUOTIENT               L"quotient" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCCOS              L"radarccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCSIN              L"radarcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCTAN              L"radarctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADCOS                 L"radcos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"radiobuttoncreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"radiobuttonenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"radiobuttondelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"radiobuttonget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"radiobuttonset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADSIN                 L"radsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADTAN                 L"radtan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RANDOM                 L"random" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RAWASCII               L"rawascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RC                     L"rc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RCS                    L"rcs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READCHAR               L"readchar" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READCHARS              L"readchars" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READER                 L"reader" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READLIST               L"readlist" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READPOS                L"readpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READRAWLINE            L"readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               L"readword" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REMAINDER              L"remainder" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REMPROP                L"remprop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REPCOUNT               L"repcount" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REPEAT                 L"repeat" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RERANDOM               L"rerandom" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHT                  L"right" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"rightroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RL                     L"rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  L"rmdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ROLL                   L"roll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ROUND                  L"round" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RR                     L"rr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RT                     L"rt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUN                    L"run" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUNPARSE               L"runparse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUNRESULT              L"runresult" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RW                     L"rw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SAVE                   L"save" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"screencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"scrollbarcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"scrollbarenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"scrollbardelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"scrollbarget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"scrollbarset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLX                L"scrollx" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLY                L"scrolly" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCRUNCH                L"scrunch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SE                     L"se" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SELECTBOX              L"selectbox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SENTENCE               L"sentence" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"setactivearea" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"setbitindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETBITMODE             L"setbitmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCLIP                L"setclip" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSOR              L"setcursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"setcursornowait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"setcursorwait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFC                  L"setfc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"setfloodcolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFOCUS               L"setfocus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETH                   L"seth" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETHEADING             L"setheading" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETITEM                L"setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"setlabelfont" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETLIGHT               L"setlight" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETMARGINS             L"setmargins" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPC                  L"setpc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"setpencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"setpenpattern" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"setpensize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPITCH               L"setpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPIXEL               L"setpixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPOS                 L"setpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"setposxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREAD                L"setread" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREADPOS             L"setreadpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETROLL                L"setroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSC                  L"setsc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"setscreencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"setscrunch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTIMER               L"settimer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTURTLE              L"setturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"setturtlemode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETWRITE               L"setwrite" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"setwritepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETX                   L"setx" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETXY                  L"setxy" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETXYZ                 L"setxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETY                   L"sety" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETZ                   L"setz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHELL                  L"shell" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOW                   L"show" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWNP                 L"shownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWN_                 L"shown?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"showturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SIN                    L"sin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SOUND                  L"sound" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"splitscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SQRT                   L"sqrt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SS                     L"ss" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ST                     L"st" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STANDOUT               L"standout" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICCREATE           L"staticcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICDELETE           L"staticdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"staticupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATUS                 L"status" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STEP                   L"step" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STEPPED                L"stepped" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STOP                   L"stop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"substringp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"substring?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUM                    L"sum" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TAG                    L"tag" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TAN                    L"tan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEST                   L"test" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEXT                   L"text" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"textscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_THING                  L"thing" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_THROW                  L"throw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TIME                   L"time" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"timemilli" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TO                     L"to" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TONE                   L"tone" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOWARDS                L"towards" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"towardsxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TRACE                  L"trace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TRACED                 L"traced" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TS                     L"ts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLE                 L"turtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"turtlemode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLES                L"turtles" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TYPE                   L"type" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNBURY                 L"unbury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNSTEP                 L"unstep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNTRACE                L"untrace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UP                     L"up" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UPPERCASE              L"uppercase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UPPITCH                L"uppitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WAIT                   L"wait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOW                 L"window" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"windowcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"windowenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"windowdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"windowfileedit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWSET              L"windowset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINHELP                L"winhelp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORD                   L"word" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORDP                  L"wordp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORD_                  L"word?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRAP                   L"wrap" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRITEPOS               L"writepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRITER                 L"writer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_YESNOBOX               L"yesnobox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_YIELD                  L"yield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ZOOM                   L"zoom" // NOT_YET_LOCALIZED

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"Poni?ti"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&Apply" // NOT_YET_LOCALIZED

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"FMSLogo programsko okru?enje"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&Datoteka"
#define LOCALIZED_FILE_NEW              L"&Nova\t(izbri?i radni prostor)"
#define LOCALIZED_FILE_LOAD             L"&U?itaj...\t(dodaj u radni prostor)"
#define LOCALIZED_FILE_OPEN             L"&Otvori...\t(Zamijeni radni prostor)"
#define LOCALIZED_FILE_SAVE             L"&Spremi"
#define LOCALIZED_FILE_SAVEAS           L"Spremi K&ao..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"Pos&tavi kao ?uvar ekrana"
#define LOCALIZED_FILE_EDIT             L"Ur&edi..."
#define LOCALIZED_FILE_ERASE            L"Ob&ri?i..."
#define LOCALIZED_FILE_EXIT             L"I&zlaz"

#define LOCALIZED_BITMAP               L"&Bitmapa"
#define LOCALIZED_BITMAP_NEW           L"&Nova"
#define LOCALIZED_BITMAP_LOAD          L"&U?itaj..."
#define LOCALIZED_BITMAP_SAVE          L"&Spremi"
#define LOCALIZED_BITMAP_SAVEAS        L"Spremi K&ao..."
#define LOCALIZED_BITMAP_PRINT         L"Is&pi?i..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"P&rinter Setup..." // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_ACTIVEAREA    L"A&ktivno podru?je..."

#define LOCALIZED_SET                  L"&Namjesti"
#define LOCALIZED_SET_PENSIZE          L"&Debljina pera..."
#define LOCALIZED_SET_LABELFONT        L"&Label Font..." // NOT_YET_LOCALIZED
#define LOCALIZED_SET_COMMANDERFONT    L"&Font naredbenog retka..."
#define LOCALIZED_SET_PENCOLOR         L"&Boja pera..."
#define LOCALIZED_SET_FLOODCOLOR       L"Boja &ispune..."
#define LOCALIZED_SET_SCREENCOLOR      L"Boja &ekrana..."

#define LOCALIZED_ZOOM                 L"&Zum"
#define LOCALIZED_ZOOM_IN              L"&Pove?aj"
#define LOCALIZED_ZOOM_OUT             L"&Smanji"
#define LOCALIZED_ZOOM_NORMAL          L"&Normalno"

#define LOCALIZED_HELP                 L"&Pomo?"
#define LOCALIZED_HELP_INDEX           L"&Indeks"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutorial" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_DEMO            L"&Demo"
#define LOCALIZED_HELP_EXAMPLE         L"&Primjeri"
#define LOCALIZED_HELP_RELEASENOTES    L"&Release Notes" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"&O " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"&O Multiploj sklerozi..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"LANGUAGE to English" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_ENGLISHTOLANG   L"English to LANGUAGE" // NOT_YET_LOCALIZED

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Select Active Area" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"These affect Printing and Saving Bitmaps" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-High" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Low"  // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-High" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Low" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"Turtle steps per inch printed:" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&Reset"  // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"FMSLogo Screensaver" // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"FMSLogo Screensaver Settings" // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Locate ..."  // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_FILE              L"Logo &File:"  // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"Select a " LOCALIZED_ALTERNATE_STARTUP " instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"No procedures are defined" // NOT_YET_LOCALIZED

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?" // NOT_YET_LOCALIZED

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Kopiraj"
#define LOCALIZED_POPUP_CUT                      L"Izre?i"
#define LOCALIZED_POPUP_PASTE                    L"Zalijepi"
#define LOCALIZED_POPUP_DELETE                   L"Izbri?i"
#define LOCALIZED_POPUP_UNDO                     L"Poni?ti"
#define LOCALIZED_POPUP_REDO                     L"Ponovi"
#define LOCALIZED_POPUP_SELECTALL                L"Ozna?i sve"
#define LOCALIZED_POPUP_HELP                     L"Topic Search" // NOT_YET_LOCALIZED
#define LOCALIZED_POPUP_REMOVELINES              L"Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Ure?iva? teksta"

#define LOCALIZED_EDITOR_FILE                    L"&Datoteka"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Spremi i izlaz\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"Spremi u &radni prostor"
#define LOCALIZED_EDITOR_FILE_PRINT              L"Is&pi?i..."
#define LOCALIZED_EDITOR_FILE_EXIT               L"I&zlaz"

#define LOCALIZED_EDITOR_EDIT                    L"&Uredi"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&Poni?ti\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&Ponovi\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"&Izre?i\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"C&opy\tCtrl+C" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_PASTE              L"&Zalijepi\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&Izbri?i\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"C&lear All\tCtrl+Del" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"S&elect All\tCtrl+A" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_SEARCH                  L"&Search" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SEARCH_FIND             L"&Find...\tCtrl+F" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Replace...\tCtrl+H"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Next\tF3"  // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_SET                     L"Se&t"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_SET_FONT                L"&Font..."  // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_TEST                    L"Test" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    L"&Help"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_INDEX              L"&Index" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editor" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&Topic Search\tF1" // NOT_YET_LOCALIZED


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Spremi i izi?i"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&Nemoj spremati"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"Na radnom prostoru postoje promjene koje nisu spremljene.  Ako izi?ete bez spremanja, promjene ?e biti izgubljene.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"?elite li spremiti promjene prije nego izi?ete?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Commander" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_HALT                L"Zaustavi"
#define LOCALIZED_COMMANDER_TRACE               L"Trace" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_NOTRACE             L"NoTrace" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_PAUSE               L"Pauziraj"
#define LOCALIZED_COMMANDER_STATUS              L"Stanje"
#define LOCALIZED_COMMANDER_NOSTATUS            L"Bez stanja"
#define LOCALIZED_COMMANDER_STEP                L"Step" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_UNSTEP              L"UnStep" // NOT_YET_LOCALIZED
#define LOCALIZED_COMMANDER_RESET               L"Ispo?etka"
#define LOCALIZED_COMMANDER_EXECUTE             L"Izvr?i"
#define LOCALIZED_COMMANDER_EDALL               L"Uredi sve"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Stanje"
#define LOCALIZED_STATUS_PEN                    L"Olovka"
#define LOCALIZED_STATUS_CONTACT                L"Kontakt:"
#define LOCALIZED_STATUS_WIDTH                  L"Debljina:"
#define LOCALIZED_STATUS_STYLE                  L"Stil:"
#define LOCALIZED_STATUS_ORIENTATION            L"Usmjerenje"
#define LOCALIZED_STATUS_PITCH                  L"Pitch:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_HEADING                L"Smjer:"
#define LOCALIZED_STATUS_ROLL                   L"Roll:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_TURTLE                 L"Kornja?a"
#define LOCALIZED_STATUS_POSITION               L"Pozicija(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Which:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_VISIBILITY             L"Vidljivost:"
#define LOCALIZED_STATUS_COLOR                  L"Boja"
#define LOCALIZED_STATUS_PENCOLOR               L"Olovka(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"Ispuna(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Zaslon(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"Kernel" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_CALLS                  L"Calls:" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PEAKMEMORY             L"Peak Memory:" // NOT_YET_LOCALIZED

#define LOCALIZED_STATUS_PENREVERSE     L"Reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENNORMAL      L"Normal" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_PENERASE       L"Brisanje"
#define LOCALIZED_STATUS_PENUP          L"Podignuta"
#define LOCALIZED_STATUS_PENDOWN        L"Spu?tena"
#define LOCALIZED_STATUS_PENSHOWN       L"Vidljiva"
#define LOCALIZED_STATUS_PENHIDDEN      L"Skrivena"
#define LOCALIZED_STATUS_POLYGONS       L"Polygons" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_VECTORS        L"Vectors" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_NODES          L"Nodes" // NOT_YET_LOCALIZED
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&All" // NOT_YET_LOCALIZED
#define LOCALIZED_ERASEPROCEDURE                L"Erase Procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITPROCEDURE                 L"Edit Procedure" // NOT_YET_LOCALIZED


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Set Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Pen Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"Flood Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Screen Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_RED                 L"Red" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_GREEN               L"Green" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_BLUE                L"Blue" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Pen Size" // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_SIZE              L"Thickness" // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"About " LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_VERSION             L"Version" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_CORE                L"Core by Brian Harvey\nUniversity of California Berkeley" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Special thanks to Yehuda Katz and Erich Neuwirth" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" is free software\nSee GNU Public License" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"About FMS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_FMS                  L"FMS stands for Fight Multiple Sclerosis." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

//
// Strings on the QUESTIONBOX dialog box
//
#define LOCALIZED_QUESTIONBOX_OK               LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_QUESTIONBOX_CANCEL           LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"Changes in this edit session may be lost.\n\nDo you really want to exit " LOCALIZED_GENERAL_PRODUCTNAME "?" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITSESSIONISRUNNING      L"An Edit session is running" // NOT_YET_LOCALIZED

#define LOCALIZED_COULDNOTWRITEBMP            L"Could not write .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTOPENBMP             L"Could not open .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTCREATEBMP           L"Unable to create Windows 3.0 bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTVALIDBMP                 L"Not a Windows 3.0 bitmap" // NOT_YET_LOCALIZED

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"You have not saved to disk" // NOT_YET_LOCALIZED
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"Executing a new will erase all definitions.\n\nContinue with New?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"This will erase all of your unsaved changes.\n\nContinue with Open?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITORISOPEN                  L"Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved." // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTREADFILE            L"Unable to read file \"%s\" from disk" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTWRITEFILE           L"Unable to write file \"%s\" to disk" // NOT_YET_LOCALIZED

#define LOCALIZED_SAVETOWORKSPACE                L"Save to Workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_CONTENTSCHANGED                L"Contents Changed" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"The contents have changed.\nWould you like to save the changes to the workspace?" // NOT_YET_LOCALIZED



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message." // NOT_YET_LOCALIZED
#define LOCALIZED_RETURNTOEDIT                  L"Return to the editor?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE // NOT_YET_LOCALIZED

#define LOCALIZED_ERRORINFILETITLE              L"Error in File" // NOT_YET_LOCALIZED
#define LOCALIZED_ERRORINFILEMESSAGE            L"There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?" // NOT_YET_LOCALIZED

#define LOCALIZED_CANNOTALLOCATESCREEN          L"Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue." // NOT_YET_LOCALIZED


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"Select the Logo program to load (merge into workspace)" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"Select the Logo program to open (replace the workspace with)" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"Select the file to which the workspace will be saved" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"Select the image to load" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"Select the file to which the active area will be saved" // NOT_YET_LOCALIZED

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_ALLFILES L"All Files (*.*)|*.*" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_LOGO     L"Logo Files (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_IMAGE    L"Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" stops\n" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_OUTPUTS           L" outputs %s\n" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_MAKE              L"Make %s %s" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_PPROP             L"Pprop %s %s %s" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_LOCATION          L" in %s\n%s" // NOT_YET_LOCALIZED

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Single Step" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s defined\n" // NOT_YET_LOCALIZED


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"erase" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_REVERSE  L"reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_PAINT    L"paint" // NOT_YET_LOCALIZED

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: Fatal Internal Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORY            L"Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STACKOVERFLOW          L"stack overflow" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"turtle out of bounds" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADGRAPHINIT           L"couldn't initialize graphics" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADDATA                L"%p ne voli %s za ulaznu vrijednost"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p didn't output to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"nema dovoljno ulaznih vrijednosti za %p"
#define LOCALIZED_ERROR_TOOMUCH                L"too much inside ()'s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"Ne ka?e? ?to da napravim s %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"too many ('s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOVALUE                L"%s nema zadanu vrijednost"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"unexpected ')'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"unexpected ']'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"unexpected '}'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"Ne znam ?to je %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"Can't find catch tag for %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p je ve? prije zadan"
#define LOCALIZED_ERROR_STOPPING               L"Stopping..." // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"Already dribbling" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM                   L"File system error: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"Could not open file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"Unable to open file: %t" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"File already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"File not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"Could not create editor file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"Could not launch the editor"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"Could not read editor file"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_IFWARNING              L"Assuming you mean IFELSE, not IF" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p shadowed by local in procedure call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_USER                   L"Throw \"Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p is a primitive" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TONOTINSIDE            L"Ne mo?e? koristiti TO unutar procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"Can only use %p inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"You must be in a procedure to use OUTPUT or STOP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTEST                 L"%p without TEST" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"Macro output %s instead of a list" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPEND                L"END inside multi-line instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPENDIN              L"END inside multi-line instruction in %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNKNOWN                L"Unknown error condition - internal error." // NOT_YET_LOCALIZED
#define LOCALIZED_PAUSING                      L"Pausing..." // NOT_YET_LOCALIZED


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                L"%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Gre?ka"
#define LOCALIZED_ERROR_BADINPUT             L"Bad input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"Input is not paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTOPENPORT         L"Could not open port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"Could not close port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"Could not flush port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDCBONPORT        L"Could not build dcb on port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTSETPORT          L"Could not set port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"Port is already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTNOTOPEN          L"Port is not open" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s ve? postoji"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s ne postoji"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"DLL is not loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLLOADFAILED         L"DLL load failed" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Invalid data type input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Invalid output type" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Function not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK               L"Network Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Network Receive Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSEND           L"Network Send Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Unexpected Error, Network may be shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"Not started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"Already started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYON      L"Already on" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"Already off" // NOT_YET_LOCALIZED

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Name too long" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"Not initialized" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"System not ready" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"Version is not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"Can't send after socket shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Interrupted system call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Authoritative Answer: Host not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"Non-Authoritative: Host not found. See NETSTARTUP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Non-recoverable error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNODATA              L"No data record available" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"Bad file number" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"Operation would block" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"Operation now in progress" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"Operation already in progress" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Bad address" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Destination address required" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Message too long" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Protocol family not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"Directory not empty" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Application limit has been reached" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"Disk quota exceeded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Too many open files" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Access denied" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Socket operation on non-socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"Can't assign requested address" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"Address already in use" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"Address family not supported by protocol family" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Connection timed out" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Socket type not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protocol not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"No space in buffer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"Socket is already connected" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"Socket is not connected" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Bad protocol option" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"Connection reset by peer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"Software caused connection abort" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKISDOWN              L"Network is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRESET               L"Network was reset" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"Connection refused" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"Host is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"Host is unreachable" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"Protocol is wrong type for socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Operation not supported on socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"No path to remote host was found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Too many references" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYSTART               L"PolyStart Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"You already have a Polygon started" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYEND                 L"PolyEnd Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"You have not started a Polygon" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"You must have at least 3 vectors to define a polygon" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_SOUND                 L"Sound Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MIDI                  L"MIDI Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"Invalid MIDI device" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"Already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDINOTOPEN           L"Not open" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"No Text in Clipboard" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MCI                   L"MCI Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Timer not found" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"Online help is unavailable because hhctrl.ocx could not be loaded."  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"Invalid Command Line"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"The environment variable TMP is not defined or invalid.\n" LOCALIZED_GENERAL_PRODUCTNAME " will attempt to use C:\\ for storing temporary files" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Problem Generating GIF, check memory and diskspace" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_GIFREADFAILED         L"Problem Reading GIF, check memory and diskspace" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"BitMap Index out of range" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Cut failed, Possibly not enough Memory" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Nothing to Paste"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"BitMap at Index must be initialized with a bitmap"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"Turtle %d has no picture, will Halt" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_FONTNOTFOUND            L"Sorry, no font named %s was found.  Choose one of the following:\n" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"Print driver does not support this function"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"Cannot draw image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"Cannot extract image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SUBCODE                 L"Sub Code" // NOT_YET_LOCALIZED

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Input:" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_TO     L"To Mode (Cancel to End)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_LIST   L"List Mode (Cancel to Halt)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_PAUSE  L"Pause Mode (Cancel to Continue)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_INPUT  L"Input Mode (Cancel to Halt)" // NOT_YET_LOCALIZED

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"Changed to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_CHDIRFAILED         L"Could not chdir to directory \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_POPPEDTO            L"Popped to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Now in newly created directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRFAILED         L"Failed to create directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Removed directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILED         L"Failed to remove directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"The directory does not exist." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Make sure the directory is empty before trying to remove it." // NOT_YET_LOCALIZED


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Logo slika"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"Active Area" // NOT_YET_LOCALIZED
#define LOCALIZED_INFORMATION   L"Information" // NOT_YET_LOCALIZED
#define LOCALIZED_WARNING       L"Warning" // NOT_YET_LOCALIZED
#define LOCALIZED_UNTITLED      L"Untitled" // NOT_YET_LOCALIZED
#define LOCALIZED_UNKNOWN       L"Unknown" // NOT_YET_LOCALIZED

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"nothing" // NOT_YET_LOCALIZED

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Find" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Replace"  // NOT_YET_LOCALIZED

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"Cannot find %s" // NOT_YET_LOCALIZED


//
// The words that describe color vectors.
// These words were selected from a de facto HTML standard, so you may
// be able to find translations for the entire set on the Web.
//
// As with the procedure names, these are part of the programming language,
// so once they are translated, they cannot be changed without breaking
// compatibility with older programs that may use the old name.
//
// Note that the colors have no spaces in their names.  This makes them
// easier to use, as the programmer doesn't have to escape the space
// when providing them as a literal word, as in:
//
//  SETPENCOLOR "AliceBlue
//
// In absense of the space, The PascalCase makes it easier to see the word
// separation in the documentation.
//
#define LOCALIZED_COLOR_ALICEBLUE             L"AliceBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"AntiqueWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_AQUA                  L"Aqua" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_AQUAMARINE            L"Aquamarine" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_AZURE                 L"Azure" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BEIGE                 L"Beige" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BISQUE                L"Bisque" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLACK                 L"Black" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"BlanchedAlmond" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLUE                  L"Blue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLUEVIOLET            L"BlueViolet" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BROWN                 L"Brown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BURLYWOOD             L"BurlyWood" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CADETBLUE             L"CadetBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CHARTREUSE            L"Chartreuse" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CHOCOLATE             L"Chocolate" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CORAL                 L"Coral" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"CornflowerBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CORNSILK              L"Cornsilk" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CRIMSON               L"Crimson" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CYAN                  L"Cyan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKBLUE              L"DarkBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKCYAN              L"DarkCyan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGOLDENROD         L"DarkGoldenRod" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGRAY              L"DarkGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGREEN             L"DarkGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGREY              L"DarkGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKKHAKI             L"DarkKhaki" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKMAGENTA           L"DarkMagenta" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"DarkOliveGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKORANGE            L"DarkOrange" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKORCHID            L"DarkOrchid" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKRED               L"DarkRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSALMON            L"DarkSalmon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSEAGREEN          L"DarkSeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"DarkSlateBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"DarkSlateGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSLATEGREY         L"DarkSlateGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKTURQUOISE         L"DarkTurquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKVIOLET            L"DarkViolet" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DEEPPINK              L"DeepPink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"DeepSkyBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DIMGRAY               L"DimGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DIMGREY               L"DimGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DODGERBLUE            L"DodgerBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FIREBRICK             L"FireBrick" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FLORALWHITE           L"FloralWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FORESTGREEN           L"ForestGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FUCHSIA               L"Fuchsia" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GAINSBORO             L"Gainsboro" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GHOSTWHITE            L"GhostWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GOLD                  L"Gold" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GOLDENROD             L"GoldenRod" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GRAY                  L"Gray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GREEN                 L"Green" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GREENYELLOW           L"GreenYellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GREY                  L"Grey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_HONEYDEW              L"HoneyDew" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_HOTPINK               L"HotPink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_INDIANRED             L"IndianRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_INDIGO                L"Indigo" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_IVORY                 L"Ivory" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_KHAKI                 L"Khaki" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LAVENDER              L"Lavender" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"LavenderBlush" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LAWNGREEN             L"LawnGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LEMONCHIFFON          L"LemonChiffon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTBLUE             L"LightBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTCORAL            L"LightCoral" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTCYAN             L"LightCyan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"LightGoldenRodYellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGRAY             L"LightGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGREEN            L"LightGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGREY             L"LightGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTPINK             L"LightPink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSALMON           L"LightSalmon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"LightSeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"LightSkyBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"LightSlateGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"LightSlateGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"LightSteelBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTYELLOW           L"LightYellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIME                  L"Lime" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIMEGREEN             L"LimeGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LINEN                 L"Linen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MAGENTA               L"Magenta" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MAROON                L"Maroon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"MediumAquaMarine" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMBLUE            L"MediumBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMORCHID          L"MediumOrchid" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"MediumPurple" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"MediumSeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"MediumSlateBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"MediumSpringGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"MediumTurquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"MediumVioletRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"MidnightBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MINTCREAM             L"MintCream" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MISTYROSE             L"MistyRose" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MOCCASIN              L"Moccasin" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_NAVAJOWHITE           L"NavajoWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_NAVY                  L"Navy" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_OLDLACE               L"OldLace" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_OLIVE                 L"Olive" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_OLIVEDRAB             L"OliveDrab" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ORANGE                L"Orange" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ORANGERED             L"OrangeRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ORCHID                L"Orchid" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALEGOLDENROD         L"PaleGoldenRod" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALEGREEN             L"PaleGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALETURQUOISE         L"PaleTurquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALEVIOLETRED         L"PaleVioletRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PAPAYAWHIP            L"PapayaWhip" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PEACHPUFF             L"PeachPuff" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PERU                  L"Peru" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PINK                  L"Pink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PLUM                  L"Plum" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_POWDERBLUE            L"PowderBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PURPLE                L"Purple" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_RED                   L"Red" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ROSYBROWN             L"RosyBrown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ROYALBLUE             L"RoyalBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SADDLEBROWN           L"SaddleBrown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SALMON                L"Salmon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SANDYBROWN            L"SandyBrown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SEAGREEN              L"SeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SEASHELL              L"SeaShell" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SIENNA                L"Sienna" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SILVER                L"Silver" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SKYBLUE               L"SkyBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SLATEBLUE             L"SlateBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SLATEGRAY             L"SlateGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SLATEGREY             L"SlateGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SNOW                  L"Snow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SPRINGGREEN           L"SpringGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_STEELBLUE             L"SteelBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TAN                   L"Tan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TEAL                  L"Teal" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_THISTLE               L"Thistle" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TOMATO                L"Tomato" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TURQUOISE             L"Turquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_VIOLET                L"Violet" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_WHEAT                 L"Wheat" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_WHITE                 L"White" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_WHITESMOKE            L"WhiteSmoke" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_YELLOW                L"Yellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_YELLOWGREEN           L"YellowGreen" // NOT_YET_LOCALIZED

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       L"Window" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_STATIC       L"Static" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      L"ListBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     L"ComboBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       L"Button" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    L"ScrollBar" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     L"GroupBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  L"RadioButton" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     L"CheckBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       L"Dialog" // NOT_YET_LOCALIZED


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE L"Courier New" // NOT_YET_LOCALIZED
