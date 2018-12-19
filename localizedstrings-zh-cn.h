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
// This file contains localized strings for Chinese by Pachleng
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
//   "Impossible d'utiliser POUR (TO) dans une proc�dure"
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
#define LOCALIZED_GENERAL_OKBUTTON      L"ȷ��"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"ȡ��"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"Ӧ��(&A)"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"FMSLogo��������"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"�ļ�(&F)"
#define LOCALIZED_FILE_NEW              L"�½�(&N)\t(���������)"
#define LOCALIZED_FILE_LOAD             L"����(&L)...\t(�ϲ�����ǰ������)"
#define LOCALIZED_FILE_OPEN             L"��(&O)...\t(�滻��ǰ������)" 
#define LOCALIZED_FILE_SAVE             L"����(&S)" 
#define LOCALIZED_FILE_SAVEAS           L"���Ϊ(&A)..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"��Ϊ����(&T)"
#define LOCALIZED_FILE_EDIT             L"�༭(&E)..."
#define LOCALIZED_FILE_ERASE            L"���(&R)..."
#define LOCALIZED_FILE_EXIT             L"�˳�(&X)"

#define LOCALIZED_BITMAP               L"ͼƬ(&B)"
#define LOCALIZED_BITMAP_NEW           L"�½�(&N)"
#define LOCALIZED_BITMAP_LOAD          L"����(&L)..."
#define LOCALIZED_BITMAP_SAVE          L"����(&S)"
#define LOCALIZED_BITMAP_SAVEAS        L"���Ϊ(&A)..."
#define LOCALIZED_BITMAP_PRINT         L"��ӡ(&P)..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"��ӡ������(&R)..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"�����(&C)..."

#define LOCALIZED_SET                  L"����(&S)"
#define LOCALIZED_SET_PENSIZE          L"���ʴ�С(&Z)..."
#define LOCALIZED_SET_LABELFONT        L"��ע����(&L)..."
#define LOCALIZED_SET_COMMANDERFONT    L"���������(&C)..."
#define LOCALIZED_SET_PENCOLOR         L"������ɫ(&P)..."
#define LOCALIZED_SET_FLOODCOLOR       L"�����ɫ(&L)..."
#define LOCALIZED_SET_SCREENCOLOR      L"������ɫ(&S)..."

#define LOCALIZED_ZOOM                 L"����(&Z)" 
#define LOCALIZED_ZOOM_IN              L"�Ŵ�(&I)"
#define LOCALIZED_ZOOM_OUT             L"��С(&O)"
#define LOCALIZED_ZOOM_NORMAL          L"��ԭ(&N)"

#define LOCALIZED_HELP                 L"����(&H)" 
#define LOCALIZED_HELP_INDEX           L"����(&I)"
#define LOCALIZED_HELP_TUTORIAL        L"�̳�(&T)"
#define LOCALIZED_HELP_DEMO            L"��ʾ(&D)" 
#define LOCALIZED_HELP_EXAMPLE         L"ʾ��(&E)"
#define LOCALIZED_HELP_RELEASENOTES    L"����˵��(&R)"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"����" LOCALIZED_GENERAL_PRODUCTNAME L"(&A)..."
#define LOCALIZED_HELP_MS              L"����FMS(&B)..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"����תӢ��"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"Ӣ��ת����"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"ѡ������"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"��Щ����Ӱ��ͼƬ�Ĵ�ӡ�ͱ���"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-��"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-��"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-��"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-��"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"��ӡ�ĺ�������/Ӣ��:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"����(&R)"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"FMSLogo����"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"FMSLogo��������"
#define LOCALIZED_SCREENSAVER_LOCATE            L"��λ(&L)..." 
#define LOCALIZED_SCREENSAVER_FILE              L"Logo�ļ�(&F):" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"ѡ��һ��" LOCALIZED_ALTERNATE_STARTUP L"ָ��"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"���Ĺ�����û�ж���" LOCALIZED_ALTERNATE_STARTUP L"ָ���б�, �����������ʱ\nʲôҲ���ᷢ��.\n���ڳ�������ʱѡ��һ������."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   LOCALIZED_ALTERNATE_STARTUP L"���������б�, �����������ʱ\nʲôҲ���ᷢ��.\n���ڳ�������ʱѡ��һ������."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"���Ĺ�����������һ����" LOCALIZED_ALTERNATE_STARTUP L"ָ���б�, �����������ʱ\nʲôҲ���ᷢ��.\n���ڳ�������ʱѡ��һ������."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"����δ����"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"���̡������������б�û�ж���,\n���ع�����������Ϊ���ļ�.\n\n��ȷ��������?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"����(&C)"
#define LOCALIZED_POPUP_CUT                      L"����(&X)"
#define LOCALIZED_POPUP_PASTE                    L"ճ��(&P)"
#define LOCALIZED_POPUP_DELETE                   L"ɾ��(&D)"
#define LOCALIZED_POPUP_UNDO                     L"����(&U)"
#define LOCALIZED_POPUP_REDO                     L"�ָ�(&R)"
#define LOCALIZED_POPUP_SELECTALL                L"ȫѡ(&A)"
#define LOCALIZED_POPUP_HELP                     L"��������(&T)"
#define LOCALIZED_POPUP_REMOVELINES              L"�����ѡ����(&L)"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"����༭��"

#define LOCALIZED_EDITOR_FILE                    L"�ļ�(&F)"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"������˳�(&S)\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"���浽������(&W)"
#define LOCALIZED_EDITOR_FILE_PRINT              L"��ӡ(&P)..." 
#define LOCALIZED_EDITOR_FILE_EXIT               L"�˳�(&X)" 

#define LOCALIZED_EDITOR_EDIT                    L"�༭(&E)"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"����(&U)\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"�ָ�(&R)\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"����(&X)\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"����(&C)\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"ճ��(&P)\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"ɾ��(&D)\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"ȫ�����(&L)\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"ȫѡ(&A)\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"����(&S)"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"����(&F)...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"�滻(&R)...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"��һ��(&N)\tF3"

#define LOCALIZED_EDITOR_SET                     L"����(&T)"
#define LOCALIZED_EDITOR_SET_FONT                L"����(&F)..." 

#define LOCALIZED_EDITOR_TEST                    L"����"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"����(&R)\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    L"����(&H)"
#define LOCALIZED_EDITOR_HELP_INDEX              L"����(&I)"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"����༭��(&E)"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"��������(&T)\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"������˳�(&S)"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"������(&D)"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"�������Ѹı�.  ��������˳�, ������������ʧ."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"�˳�ǰ�������Ĳ�����"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"�����"
#define LOCALIZED_COMMANDER_HALT                L"��ֹ"
#define LOCALIZED_COMMANDER_TRACE               L"����"
#define LOCALIZED_COMMANDER_NOTRACE             L"������"
#define LOCALIZED_COMMANDER_PAUSE               L"��ͣ"
#define LOCALIZED_COMMANDER_STATUS              L"��ʾ״̬"
#define LOCALIZED_COMMANDER_NOSTATUS            L"����״̬"
#define LOCALIZED_COMMANDER_STEP                L"����"
#define LOCALIZED_COMMANDER_UNSTEP              L"ֹͣ����"
#define LOCALIZED_COMMANDER_RESET               L"����"
#define LOCALIZED_COMMANDER_EXECUTE             L"ִ��"
#define LOCALIZED_COMMANDER_EDALL               L"����༭��"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"״̬����"
#define LOCALIZED_STATUS_PEN                    L"����"
#define LOCALIZED_STATUS_CONTACT                L"����:"
#define LOCALIZED_STATUS_WIDTH                  L"���:"
#define LOCALIZED_STATUS_STYLE                  L"���:"
#define LOCALIZED_STATUS_ORIENTATION            L"����"
#define LOCALIZED_STATUS_PITCH                  L"��ߵ�:"
#define LOCALIZED_STATUS_HEADING                L"�Ƕ�:"
#define LOCALIZED_STATUS_ROLL                   L"����:"
#define LOCALIZED_STATUS_TURTLE                 L"����"
#define LOCALIZED_STATUS_POSITION               L"λ��(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"λ��:"
#define LOCALIZED_STATUS_VISIBILITY             L"�ɼ���:"
#define LOCALIZED_STATUS_COLOR                  L"��ɫ"
#define LOCALIZED_STATUS_PENCOLOR               L"����(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"���(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"����(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"�ں�"
#define LOCALIZED_STATUS_CALLS                  L"���ô���:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"�ڴ��ֵ:"

#define LOCALIZED_STATUS_PENREVERSE     L"����"
#define LOCALIZED_STATUS_PENNORMAL      L"����"
#define LOCALIZED_STATUS_PENERASE       L"����"
#define LOCALIZED_STATUS_PENUP          L"����"
#define LOCALIZED_STATUS_PENDOWN        L"����"
#define LOCALIZED_STATUS_PENSHOWN       L"��ʾ"
#define LOCALIZED_STATUS_PENHIDDEN      L"����"
#define LOCALIZED_STATUS_POLYGONS       L"�����"
#define LOCALIZED_STATUS_VECTORS        L"����"
#define LOCALIZED_STATUS_NODES          L"�ڵ�"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"������/����"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"����(&A)"
#define LOCALIZED_ERASEPROCEDURE                L"�������"
#define LOCALIZED_EDITPROCEDURE                 L"�༭����"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"��ɫ����"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"������ɫ"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"�����ɫ"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"������ɫ"
#define LOCALIZED_SETCOLOR_RED                 L"��ɫ"
#define LOCALIZED_SETCOLOR_GREEN               L"��ɫ"
#define LOCALIZED_SETCOLOR_BLUE                L"��ɫ"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"���ʴ�С"
#define LOCALIZED_SETPENSIZE_SIZE              L"��С"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"����" LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"�汾"
#define LOCALIZED_ABOUTFMS_GUI                 L"�����д:  George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"�ں˱�д: Brian Harvey\n���������Ǵ�ѧ����������У"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"��װ������Nullsoft Scriptable Install System����\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"��The Great Logo Adventure��(ISBN 0-9651934-6-2)\n����: Jim Muller\n�����http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"�ر���лYehuda Katz��Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L"���������\n�μ�GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"����������: comp.lang.logo\nLogo��̳\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"����ѧϰ�����ԭ��,\n����Softronics, Inc.��ϵ��ȡMultiMedia Logic"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"����FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS��Fight Multiple Sclerosis����д"
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"�����\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the QUESTIONBOX dialog box
//
#define LOCALIZED_QUESTIONBOX_OK               LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_QUESTIONBOX_CANCEL           LOCALIZED_GENERAL_CANCELBUTTON


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"���в�������ʧ��\n\n��ȷ���˳��� L" LOCALIZED_GENERAL_PRODUCTNAME L"?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"�༭�Ի���������"

#define LOCALIZED_COULDNOTWRITEBMP            L"ͼƬ����ʧ��"
#define LOCALIZED_COULDNOTOPENBMP             L"ͼƬ��ʧ��"
#define LOCALIZED_COULDNOTCREATEBMP           L"���ܴ���Windows 3.0λͼ"
#define LOCALIZED_NOTVALIDBMP                 L"����Windows 3.0λͼ"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"��δ����"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"����½���������ж���.\n\nȷ���½���?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"������ļ����ϲ���ǰ������\n�����������޸�.\n\n����������?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"δ����Ĳ�������ʧ.\n\nȷ������?"

#define LOCALIZED_EDITORISOPEN                  L"������ִ��һ���༭.\n\n����������δ����."

#define LOCALIZED_ERROR_CANTREADFILE            L"���ܶ�ȡ�ļ�\"%s\""
#define LOCALIZED_ERROR_CANTWRITEFILE           L"����д�ļ�\"%s\""

#define LOCALIZED_SAVETOWORKSPACE                L"���浽������"
#define LOCALIZED_CONTENTSCHANGED                L"�����Ѹ���"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"�����Ѹ���, \n��Ҫ���������?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"�������, \n\n��鿴����ڵĴ�����ʾ��"
#define LOCALIZED_RETURNTOEDIT                  L"���ر༭��?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              L"�ļ��д���"
#define LOCALIZED_ERRORINFILEMESSAGE            L"�����ļ�ʱ���� \"%s\".\n\n��鿴����ڵĴ�����ʾ.\n\n��Ҫ�ڱ༭�����ļ��鿴������"

#define LOCALIZED_CANNOTALLOCATESCREEN          L"���仭�������ڴ�ʧ��.  ����������ĳߴ糬���˿����ڴ�.\n\n" LOCALIZED_GENERAL_PRODUCTNAME


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"����Logo����(�ϲ�����ǰ������)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"��Logo����(�滻��ǰ������)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"ѡ�������ļ�"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"����ͼƬ"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"ѡ��ǰ���򱣴��ļ�"

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"�����ļ�(*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Logo�ļ�(*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"ͼƬ�ļ�(*.bmp)|*.bmp|GIF�ļ�(*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



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
#define LOCALIZED_STEPPING                  L"����"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s�Ѷ���\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"����"
#define LOCALIZED_PENMODE_REVERSE  L"����"
#define LOCALIZED_PENMODE_PAINT    L"��ͼ"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: �����ڲ�����"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: �ڴ治��"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"�ڴ治��"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"��ջ���"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"���곬����Χ"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"ͼ�γ�ʼ��ʧ��"
#define LOCALIZED_ERROR_BADDATA                L"%p ��ϲ�� %s ��Ϊ����"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p δ�����%p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"���벻��: %p"
#define LOCALIZED_ERROR_TOOMUCH                L"̫���ڲ�()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"��û��ָ����δ���%s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"̫��('s"
#define LOCALIZED_ERROR_NOVALUE                L"%sδ��ֵ"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"�����')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"�����']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"�����'}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"�Ҳ�֪�����%p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"���ܷ���%p�Ĳ�����"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p�Ѷ���"
#define LOCALIZED_ERROR_STOPPING               L"����ֹͣ..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"��й©"
#define LOCALIZED_ERROR_FILESYSTEM                   L"�ļ�ϵͳ����: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"���ļ�ʧ��"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"���ܴ��ļ�: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"�ļ��Ѵ�"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"�ļ�δ��"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"�����༭���ļ�ʧ��"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"���ر༭��ʧ��" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"��ȡ�༭���ļ�ʧ��" 
#define LOCALIZED_ERROR_IFWARNING              L"�ٶ���ʹ�õ���IFELSE, ����IF"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p�������ڲ���������"
#define LOCALIZED_ERROR_USER                   L"�׳� \"����"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p��ԭ��"
#define LOCALIZED_ERROR_TONOTINSIDE            L"�����ڲ�����ʹ��TO"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"%pֻ���ڹ����ڲ�ʹ��"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"OUTPUT��STOPֻ���ڹ�����ʹ��"
#define LOCALIZED_ERROR_NOTEST                 L"%pδ����"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"�����%s�����б�"
#define LOCALIZED_ERROR_DEEPEND                L"����ָ���к���END"
#define LOCALIZED_ERROR_DEEPENDIN              L"����ָ��%p�к���END"
#define LOCALIZED_ERROR_UNKNOWN                L"δ֪��������-�ڲ�����."
#define LOCALIZED_PAUSING                      L"��ͣ..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"%pָ���״̬��Ч"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"���ڹ������ת��ͼƬʱ������������ģʽ"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"��������תͼƬ�����ڹ�ͼƬ"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"�����ü�������Ϊ��תͼƬ"
#define LOCALIZED_ERROR_SPECIALFORM                L"%p������%p��Ϊ����, �����������ʽ"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"����"
#define LOCALIZED_ERROR_BADINPUT             L"��Ч����"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"���벻���"

#define LOCALIZED_ERROR_CANTOPENPORT         L"�򿪶˿�ʧ��"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"�رն˿�ʧ��"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"ˢ�¶˿�ʧ��"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"�ڶ˿ڽ���dcbʧ��"
#define LOCALIZED_ERROR_CANTSETPORT          L"���ö˿�ʧ��"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"�˿��Ѵ�"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"�˿�δ��"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s�Ѵ���"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s������"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"DLL��δװ��"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"DLLװ��ʧ��"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"���������������Ч"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"�����������Ч"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"����δ����"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"�е�����/����δ���"

#define LOCALIZED_ERROR_NETWORK               L"�������"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"������մ���"
#define LOCALIZED_ERROR_NETWORKSEND           L"���緢������"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"δ֪����, ��������ѹر�"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"��δ��ʼ"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"�ѿ�ʼ"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"�Ѵ�"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"�ѹر�"

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

#define LOCALIZED_ERROR_POLYSTART               L"�������ʼ����"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"�ѿ�ʼ����λ���"

#define LOCALIZED_ERROR_POLYEND                 L"����ν�������"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"��û�п�ʼ���ƶ����"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"����һ�����������Ҫ�����߶�"

#define LOCALIZED_ERROR_SOUND                 L"��������"

#define LOCALIZED_ERROR_MIDI                  L"MIDI����"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"��Ч��MIDI�豸"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"�Ѵ�"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"δ��"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"������û���ı�"

#define LOCALIZED_ERROR_MCI                   L"MCI����"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"δ���ֶ�ʱ��"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"���߰�����Ч, hhctrl.ocx����ʧ��"

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"��������Ч" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"��������TMPδ�������Ч.\n" LOCALIZED_GENERAL_PRODUCTNAME L" ���Ա�����ʱ�ļ���C:\\"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"����GIFʧ��, �����ڴ��Ӳ��"
#define LOCALIZED_ERROR_GIFREADFAILED         L"��ȡGIFʧ��, �����ڴ��Ӳ��"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"ͼƬ����������Χ"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"����ʧ��, �����ڴ治��"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"�������" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"�����е�ͼƬ������λͼ��ʼ��" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"����%dû��ͼƬ, ����ֹ"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"������%sδ����.  ��ѡ��:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"��ӡ��������֧�ָù���" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"��ͼʧ��"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"��ȡͼ��ʧ��"
#define LOCALIZED_ERROR_SUBCODE                 L"�ӹ���"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"����:"
#define LOCALIZED_PROMPT_TO     L"Toģʽ(Cancel to End)"
#define LOCALIZED_PROMPT_LIST   L"�б�ģʽ(Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  L"��ͣģʽ(Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  L"����ģʽ(Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"�л���\"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"chdir\"%s\"ʧ��"
#define LOCALIZED_FILE_POPPEDTO            L"����\"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"λ���½��ļ���\"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         L"�����ļ���ʧ��\"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"�ļ�����ɾ��\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         L"ɾ���ļ���ʧ��\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"�ļ��в�����."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"���ļ���Ϊ��"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"�����"
#define LOCALIZED_INFORMATION   L"��ʾ"
#define LOCALIZED_WARNING       L"����"
#define LOCALIZED_UNTITLED      L"�ޱ���"
#define LOCALIZED_UNKNOWN       L"δ֪"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"��"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"����"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"�滻" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"%sδ�ҵ�"


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
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       L"����"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       L"�ı���"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      L"�б��"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     L"��Ͽ�"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       L"��ť"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    L"������"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     L"�����"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  L"��ѡ��ť"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     L"��ѡ��"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       L"�Ի���"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE L"����"
