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
//   "Impossible d'utiliser POUR (TO) dans une proc閐ure"
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
#define LOCALIZED_GENERAL_OKBUTTON      L"确定"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"取消"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"应用(&A)"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"FMSLogo开发环境"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"文件(&F)"
#define LOCALIZED_FILE_NEW              L"新建(&N)\t(清除工作区)"
#define LOCALIZED_FILE_LOAD             L"载入(&L)...\t(合并至当前工作区)"
#define LOCALIZED_FILE_OPEN             L"打开(&O)...\t(替换当前工作区)" 
#define LOCALIZED_FILE_SAVE             L"保存(&S)" 
#define LOCALIZED_FILE_SAVEAS           L"另存为(&A)..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"设为屏保(&T)"
#define LOCALIZED_FILE_EDIT             L"编辑(&E)..."
#define LOCALIZED_FILE_ERASE            L"清除(&R)..."
#define LOCALIZED_FILE_EXIT             L"退出(&X)"

#define LOCALIZED_BITMAP               L"图片(&B)"
#define LOCALIZED_BITMAP_NEW           L"新建(&N)"
#define LOCALIZED_BITMAP_LOAD          L"载入(&L)..."
#define LOCALIZED_BITMAP_SAVE          L"保存(&S)"
#define LOCALIZED_BITMAP_SAVEAS        L"另存为(&A)..."
#define LOCALIZED_BITMAP_PRINT         L"打印(&P)..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"打印机设置(&R)..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"活动区域(&C)..."

#define LOCALIZED_SET                  L"设置(&S)"
#define LOCALIZED_SET_PENSIZE          L"画笔大小(&Z)..."
#define LOCALIZED_SET_LABELFONT        L"标注字体(&L)..."
#define LOCALIZED_SET_COMMANDERFONT    L"命令窗口字体(&C)..."
#define LOCALIZED_SET_PENCOLOR         L"画笔颜色(&P)..."
#define LOCALIZED_SET_FLOODCOLOR       L"填充颜色(&L)..."
#define LOCALIZED_SET_SCREENCOLOR      L"画布颜色(&S)..."

#define LOCALIZED_ZOOM                 L"缩放(&Z)" 
#define LOCALIZED_ZOOM_IN              L"放大(&I)"
#define LOCALIZED_ZOOM_OUT             L"缩小(&O)"
#define LOCALIZED_ZOOM_NORMAL          L"还原(&N)"

#define LOCALIZED_HELP                 L"帮助(&H)" 
#define LOCALIZED_HELP_INDEX           L"索引(&I)"
#define LOCALIZED_HELP_TUTORIAL        L"教程(&T)"
#define LOCALIZED_HELP_DEMO            L"演示(&D)" 
#define LOCALIZED_HELP_EXAMPLE         L"示例(&E)"
#define LOCALIZED_HELP_RELEASENOTES    L"发布说明(&R)"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"关于" LOCALIZED_GENERAL_PRODUCTNAME L"(&A)..."
#define LOCALIZED_HELP_MS              L"关于FMS(&B)..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"中文转英文"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"英文转中文"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"选择活动区域"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"这些设置影响图片的打印和保存"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-高"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-低"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-高"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-低"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"打印的海龟像素/英寸:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"重置(&R)"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"FMSLogo屏保"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"FMSLogo屏保设置"
#define LOCALIZED_SCREENSAVER_LOCATE            L"定位(&L)..." 
#define LOCALIZED_SCREENSAVER_FILE              L"Logo文件(&F):" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"选择一个" LOCALIZED_ALTERNATE_STARTUP L"指令"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"您的工作区没有定义" LOCALIZED_ALTERNATE_STARTUP L"指令列表, 因此载入屏保时\n什么也不会发生.\n请在程序载入时选择一个过程."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   LOCALIZED_ALTERNATE_STARTUP L"变量不是列表, 因此载入屏保时\n什么也不会发生.\n请在程序载入时选择一个过程."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"您的工作区定义了一个空" LOCALIZED_ALTERNATE_STARTUP L"指令列表, 因此载入屏保时\n什么也不会发生.\n请在程序载入时选择一个过程."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"过程未定义"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"过程、变量、属性列表还没有定义,\n隐藏工作区将保存为空文件.\n\n您确定保存吗?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"复制(&C)"
#define LOCALIZED_POPUP_CUT                      L"剪切(&X)"
#define LOCALIZED_POPUP_PASTE                    L"粘贴(&P)"
#define LOCALIZED_POPUP_DELETE                   L"删除(&D)"
#define LOCALIZED_POPUP_UNDO                     L"撤销(&U)"
#define LOCALIZED_POPUP_REDO                     L"恢复(&R)"
#define LOCALIZED_POPUP_SELECTALL                L"全选(&A)"
#define LOCALIZED_POPUP_HELP                     L"搜索主题(&T)"
#define LOCALIZED_POPUP_REMOVELINES              L"清除已选线条(&L)"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"代码编辑器"

#define LOCALIZED_EDITOR_FILE                    L"文件(&F)"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"保存后退出(&S)\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"保存到工作区(&W)"
#define LOCALIZED_EDITOR_FILE_PRINT              L"打印(&P)..." 
#define LOCALIZED_EDITOR_FILE_EXIT               L"退出(&X)" 

#define LOCALIZED_EDITOR_EDIT                    L"编辑(&E)"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"撤销(&U)\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"恢复(&R)\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"剪切(&X)\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"复制(&C)\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"粘贴(&P)\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"删除(&D)\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"全部清除(&L)\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"全选(&A)\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"搜索(&S)"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"查找(&F)...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"替换(&R)...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"下一个(&N)\tF3"

#define LOCALIZED_EDITOR_SET                     L"设置(&T)"
#define LOCALIZED_EDITOR_SET_FONT                L"字体(&F)..." 

#define LOCALIZED_EDITOR_TEST                    L"测试"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"运行(&R)\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    L"帮助(&H)"
#define LOCALIZED_EDITOR_HELP_INDEX              L"索引(&I)"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"代码编辑器(&E)"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"主题搜索(&T)\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"保存后退出(&S)"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"不保存(&D)"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"工作区已改变.  如果现在退出, 所做操作将丢失."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"退出前保存您的操作吗？"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"命令窗口"
#define LOCALIZED_COMMANDER_HALT                L"终止"
#define LOCALIZED_COMMANDER_TRACE               L"跟踪"
#define LOCALIZED_COMMANDER_NOTRACE             L"不跟踪"
#define LOCALIZED_COMMANDER_PAUSE               L"暂停"
#define LOCALIZED_COMMANDER_STATUS              L"显示状态"
#define LOCALIZED_COMMANDER_NOSTATUS            L"隐藏状态"
#define LOCALIZED_COMMANDER_STEP                L"单步"
#define LOCALIZED_COMMANDER_UNSTEP              L"停止单步"
#define LOCALIZED_COMMANDER_RESET               L"重置"
#define LOCALIZED_COMMANDER_EXECUTE             L"执行"
#define LOCALIZED_COMMANDER_EDALL               L"代码编辑器"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"状态窗口"
#define LOCALIZED_STATUS_PEN                    L"画笔"
#define LOCALIZED_STATUS_CONTACT                L"触点:"
#define LOCALIZED_STATUS_WIDTH                  L"宽度:"
#define LOCALIZED_STATUS_STYLE                  L"风格:"
#define LOCALIZED_STATUS_ORIENTATION            L"方向"
#define LOCALIZED_STATUS_PITCH                  L"最高点:"
#define LOCALIZED_STATUS_HEADING                L"角度:"
#define LOCALIZED_STATUS_ROLL                   L"滚动:"
#define LOCALIZED_STATUS_TURTLE                 L"海龟"
#define LOCALIZED_STATUS_POSITION               L"位置(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"位置:"
#define LOCALIZED_STATUS_VISIBILITY             L"可见性:"
#define LOCALIZED_STATUS_COLOR                  L"颜色"
#define LOCALIZED_STATUS_PENCOLOR               L"画笔(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"填充(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"画布(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"内核"
#define LOCALIZED_STATUS_CALLS                  L"调用次数:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"内存峰值:"

#define LOCALIZED_STATUS_PENREVERSE     L"反向"
#define LOCALIZED_STATUS_PENNORMAL      L"正常"
#define LOCALIZED_STATUS_PENERASE       L"擦除"
#define LOCALIZED_STATUS_PENUP          L"向上"
#define LOCALIZED_STATUS_PENDOWN        L"向下"
#define LOCALIZED_STATUS_PENSHOWN       L"显示"
#define LOCALIZED_STATUS_PENHIDDEN      L"隐藏"
#define LOCALIZED_STATUS_POLYGONS       L"多边形"
#define LOCALIZED_STATUS_VECTORS        L"立体"
#define LOCALIZED_STATUS_NODES          L"节点"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"不适用/适用"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"所有(&A)"
#define LOCALIZED_ERASEPROCEDURE                L"清除过程"
#define LOCALIZED_EDITPROCEDURE                 L"编辑过程"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"颜色设置"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"画笔颜色"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"填充颜色"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"画布颜色"
#define LOCALIZED_SETCOLOR_RED                 L"红色"
#define LOCALIZED_SETCOLOR_GREEN               L"绿色"
#define LOCALIZED_SETCOLOR_BLUE                L"蓝色"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"画笔大小"
#define LOCALIZED_SETPENSIZE_SIZE              L"大小"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"关于" LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"版本"
#define LOCALIZED_ABOUTFMS_GUI                 L"界面编写:  George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"内核编写: Brian Harvey\n加利福利亚大学，伯克利分校"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"安装包采用Nullsoft Scriptable Install System制作\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"《The Great Logo Adventure》(ISBN 0-9651934-6-2)\n作者: Jim Muller\n请访问http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"特别鸣谢Yehuda Katz和Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L"是自由软件\n参见GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"网络新闻组: comp.lang.logo\nLogo论坛\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"如需学习计算机原理,\n请与Softronics, Inc.联系索取MultiMedia Logic"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"关于FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS是Fight Multiple Sclerosis的缩写"
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"请捐助\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"所有操作将丢失，\n\n您确定退出吗？ L" LOCALIZED_GENERAL_PRODUCTNAME L"?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"编辑对话正在运行"

#define LOCALIZED_COULDNOTWRITEBMP            L"图片保存失败"
#define LOCALIZED_COULDNOTOPENBMP             L"图片打开失败"
#define LOCALIZED_COULDNOTCREATEBMP           L"不能创建Windows 3.0位图"
#define LOCALIZED_NOTVALIDBMP                 L"不是Windows 3.0位图"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"还未保存"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"如果新建将清空所有定义.\n\n确定新建吗?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"载入的文件将合并当前工作区\n并覆盖您的修改.\n\n继续载入吗?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"未保存的操作将丢失.\n\n确定打开吗?"

#define LOCALIZED_EDITORISOPEN                  L"您正在执行一个编辑.\n\n所做操作还未保存."

#define LOCALIZED_ERROR_CANTREADFILE            L"不能读取文件\"%s\""
#define LOCALIZED_ERROR_CANTWRITEFILE           L"不能写文件\"%s\""

#define LOCALIZED_SAVETOWORKSPACE                L"保存到工作区"
#define LOCALIZED_CONTENTSCHANGED                L"内容已更改"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"内容已更改, \n您要保存更改吗?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"保存出错, \n\n请查看命令窗口的错误提示。"
#define LOCALIZED_RETURNTOEDIT                  L"返回编辑器?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              L"文件有错误"
#define LOCALIZED_ERRORINFILEMESSAGE            L"载入文件时出错 \"%s\".\n\n请查看命令窗口的错误提示.\n\n您要在编辑器打开文件查看错误吗？"

#define LOCALIZED_CANNOTALLOCATESCREEN          L"分配画布窗口内存失败.  可能您申请的尺寸超过了可用内存.\n\n" LOCALIZED_GENERAL_PRODUCTNAME


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"载入Logo程序(合并至当前工作区)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"打开Logo程序(替换当前工作区)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"选择工作区文件"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"载入图片"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"选择当前区域保存文件"

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"所有文件(*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Logo文件(*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"图片文件(*.bmp)|*.bmp|GIF文件(*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



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
#define LOCALIZED_STEPPING                  L"单步"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s已定义\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"擦除"
#define LOCALIZED_PENMODE_REVERSE  L"反向"
#define LOCALIZED_PENMODE_PAINT    L"画图"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: 致命内部错误"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: 内存不足"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"内存不足"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"堆栈溢出"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"海龟超出范围"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"图形初始化失败"
#define LOCALIZED_ERROR_BADDATA                L"%p 不喜欢 %s 作为输入"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p 未输出至%p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"输入不足: %p"
#define LOCALIZED_ERROR_TOOMUCH                L"太多内部()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"您没有指定如何处理%s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"太多('s"
#define LOCALIZED_ERROR_NOVALUE                L"%s未赋值"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"意外的')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"意外的']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"意外的'}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"我不知道如何%p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"不能发现%p的捕获标记"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p已定义"
#define LOCALIZED_ERROR_STOPPING               L"正在停止..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"已泄漏"
#define LOCALIZED_ERROR_FILESYSTEM                   L"文件系统错误: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"打开文件失败"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"不能打开文件: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"文件已打开"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"文件未打开"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"创建编辑器文件失败"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"加载编辑器失败" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"读取编辑器文件失败" 
#define LOCALIZED_ERROR_IFWARNING              L"假定你使用的是IFELSE, 不是IF"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p过程中内部变量屏蔽"
#define LOCALIZED_ERROR_USER                   L"抛出 \"错误"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p是原语"
#define LOCALIZED_ERROR_TONOTINSIDE            L"过程内部不能使用TO"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"%p只能在过程内部使用"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"OUTPUT和STOP只能在过程内使用"
#define LOCALIZED_ERROR_NOTEST                 L"%p未测试"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"宏输出%s代替列表"
#define LOCALIZED_ERROR_DEEPEND                L"多行指令中含有END"
#define LOCALIZED_ERROR_DEEPENDIN              L"多行指令%p中含有END"
#define LOCALIZED_ERROR_UNKNOWN                L"未知错误条件-内部错误."
#define LOCALIZED_PAUSING                      L"暂停..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"%p指令的状态无效"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"当乌龟带有旋转的图片时，不能设置其模式"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"不能用旋转图片制作乌龟图片"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"不能用剪贴板作为旋转图片"
#define LOCALIZED_ERROR_SPECIALFORM                L"%p不能用%p作为输入, 因其有特殊格式"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"错误"
#define LOCALIZED_ERROR_BADINPUT             L"无效输入"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"输入不配对"

#define LOCALIZED_ERROR_CANTOPENPORT         L"打开端口失败"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"关闭端口失败"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"刷新端口失败"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"在端口建立dcb失败"
#define LOCALIZED_ERROR_CANTSETPORT          L"设置端口失败"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"端口已打开"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"端口未打开"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s已存在"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s不存在"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"DLL还未装入"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"DLL装入失败"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"输入的数据类型无效"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"输出的类型无效"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"函数未发现"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"有的类型/数据未配对"

#define LOCALIZED_ERROR_NETWORK               L"网络错误"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"网络接收错误"
#define LOCALIZED_ERROR_NETWORKSEND           L"网络发生错误"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"未知错误, 网络可能已关闭"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"还未开始"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"已开始"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"已打开"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"已关闭"

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

#define LOCALIZED_ERROR_POLYSTART               L"多边形起始错误"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"已开始多边形绘制"

#define LOCALIZED_ERROR_POLYEND                 L"多边形结束错误"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"还没有开始绘制多边形"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"定义一个多边形至少要三条线段"

#define LOCALIZED_ERROR_SOUND                 L"声音错误"

#define LOCALIZED_ERROR_MIDI                  L"MIDI错误"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"无效的MIDI设备"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"已打开"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"未打开"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"剪贴板没有文本"

#define LOCALIZED_ERROR_MCI                   L"MCI错误"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"未发现定时器"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"在线帮助无效, hhctrl.ocx加载失败"

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"命令行无效" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"环境变量TMP未定义或无效.\n" LOCALIZED_GENERAL_PRODUCTNAME L" 尝试保存临时文件到C:\\"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"生成GIF失败, 请检查内存和硬盘"
#define LOCALIZED_ERROR_GIFREADFAILED         L"读取GIF失败, 请检查内存和硬盘"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"图片索引超出范围"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"剪切失败, 可能内存不足"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"剪贴板空" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"索引中的图片必须用位图初始化" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"海龟%d没有图片, 将终止"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"字体名%s未发现.  请选择:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"打印机驱动不支持该功能" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"画图失败"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"抽取图像失败"
#define LOCALIZED_ERROR_SUBCODE                 L"子过程"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"输入:"
#define LOCALIZED_PROMPT_TO     L"To模式(Cancel to End)"
#define LOCALIZED_PROMPT_LIST   L"列表模式(Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  L"暂停模式(Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  L"输入模式(Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"切换至\"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"chdir\"%s\"失败"
#define LOCALIZED_FILE_POPPEDTO            L"弹出\"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"位于新建文件夹\"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         L"创建文件夹失败\"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"文件夹已删除\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         L"删除文件夹失败\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"文件夹不存在."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"请文件夹为空"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"活动区域"
#define LOCALIZED_INFORMATION   L"提示"
#define LOCALIZED_WARNING       L"警告"
#define LOCALIZED_UNTITLED      L"无标题"
#define LOCALIZED_UNKNOWN       L"未知"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"空"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"查找"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"替换" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"%s未找到"


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
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       L"窗体"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       L"文本框"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      L"列表框"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     L"组合框"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       L"按钮"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    L"滚动条"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     L"分组框"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  L"单选按钮"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     L"复选框"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       L"对话框"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE L"宋体"
