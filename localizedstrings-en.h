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
// This file contains localized strings for English
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
#define LOCALIZED_ALTERNATE_TRUE     L"true"
#define LOCALIZED_ALTERNATE_FALSE    L"false"
#define LOCALIZED_ALTERNATE_END      L"end"
#define LOCALIZED_ALTERNATE_TOPLEVEL L"toplevel"
#define LOCALIZED_ALTERNATE_SYSTEM   L"system"

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    L"caseignoredp"
#define LOCALIZED_ALTERNATE_ERRACT          L"erract"
#define LOCALIZED_ALTERNATE_STARTUP         L"startup"
#define LOCALIZED_ALTERNATE_REDEFP          L"redefp"
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT L"printwidthlimit"
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT L"printdepthlimit"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              L".defmacro"
#define LOCALIZED_ALTERNATE__EQ                    L".eq"
#define LOCALIZED_ALTERNATE__MACRO                 L".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".maybeoutput"
#define LOCALIZED_ALTERNATE__SETBF                 L".setbf"
#define LOCALIZED_ALTERNATE__SETFIRST              L".setfirst"
#define LOCALIZED_ALTERNATE__SETITEM               L".setitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"activearea"
#define LOCALIZED_ALTERNATE_ALLOPEN                L"allopen"
#define LOCALIZED_ALTERNATE_AND                    L"and"
#define LOCALIZED_ALTERNATE_APPLY                  L"apply"
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"arity"
#define LOCALIZED_ALTERNATE_ARRAY                  L"array"
#define LOCALIZED_ALTERNATE_ARRAYP                 L"arrayp"
#define LOCALIZED_ALTERNATE_ARRAY_                 L"array?"
#define LOCALIZED_ALTERNATE_ASCII                  L"ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 L"ashift"
#define LOCALIZED_ALTERNATE_BACK                   L"back"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"backslashedp"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"backslashed?"
#define LOCALIZED_ALTERNATE_BEFOREP                L"beforep"
#define LOCALIZED_ALTERNATE_BEFORE_                L"before?"
#define LOCALIZED_ALTERNATE_BF                     L"bf"
#define LOCALIZED_ALTERNATE_BFS                    L"bfs"
#define LOCALIZED_ALTERNATE_BITAND                 L"bitand"
#define LOCALIZED_ALTERNATE_BITBLOCK               L"bitblock"
#define LOCALIZED_ALTERNATE_BITCOPY                L"bitcopy"
#define LOCALIZED_ALTERNATE_BITCUT                 L"bitcut"
#define LOCALIZED_ALTERNATE_BITFIT                 L"bitfit"
#define LOCALIZED_ALTERNATE_BITINDEX               L"bitindex"
#define LOCALIZED_ALTERNATE_BITLOAD                L"bitload"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"bitloadsize"
#define LOCALIZED_ALTERNATE_BITSIZE                L"bitsize"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"bitmapturtle"
#define LOCALIZED_ALTERNATE_BITMODE                L"bitmode"
#define LOCALIZED_ALTERNATE_BITNOT                 L"bitnot"
#define LOCALIZED_ALTERNATE_BITOR                  L"bitor"
#define LOCALIZED_ALTERNATE_BITPASTE               L"bitpaste"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"bitpastetoindex"
#define LOCALIZED_ALTERNATE_BITSAVE                L"bitsave"
#define LOCALIZED_ALTERNATE_BITXOR                 L"bitxor"
#define LOCALIZED_ALTERNATE_BK                     L"bk"
#define LOCALIZED_ALTERNATE_BL                     L"bl"
#define LOCALIZED_ALTERNATE_BURIED                 L"buried"
#define LOCALIZED_ALTERNATE_BURY                   L"bury"
#define LOCALIZED_ALTERNATE_BUTFIRST               L"butfirst"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"butfirsts"
#define LOCALIZED_ALTERNATE_BUTLAST                L"butlast"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"buttoncreate"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"buttondelete"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"buttonenable"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"buttonupdate"
#define LOCALIZED_ALTERNATE_BUTTONP                L"buttonp"
#define LOCALIZED_ALTERNATE_BUTTON_                L"button?"
#define LOCALIZED_ALTERNATE_BYE                    L"bye"
#define LOCALIZED_ALTERNATE_CATCH                  L"catch"
#define LOCALIZED_ALTERNATE_CHAR                   L"char"
#define LOCALIZED_ALTERNATE_CHDIR                  L"chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"checkboxcreate"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"checkboxdelete"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"checkboxenable"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"checkboxget"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"checkboxset"
#define LOCALIZED_ALTERNATE_CLEAN                  L"clean"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"clearpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"clearscreen"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"cleartext"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"cleartimer"
#define LOCALIZED_ALTERNATE_CLOSE                  L"close"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"closeall"
#define LOCALIZED_ALTERNATE_CO                     L"co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"comboboxaddstring"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"comboboxcreate"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"comboboxdelete"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"comboboxenable"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"comboboxdeletestring"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"comboboxgettext"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"comboboxsettext"
#define LOCALIZED_ALTERNATE_CONTENTS               L"contents"
#define LOCALIZED_ALTERNATE_CONTINUE               L"continue"
#define LOCALIZED_ALTERNATE_COPYDEF                L"copydef"
#define LOCALIZED_ALTERNATE_COS                    L"cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"count"
#define LOCALIZED_ALTERNATE_CS                     L"cs"
#define LOCALIZED_ALTERNATE_CT                     L"ct"
#define LOCALIZED_ALTERNATE_CURSOR                 L"cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"debugwindows"
#define LOCALIZED_ALTERNATE_DEFINE                 L"define"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"definedp"
#define LOCALIZED_ALTERNATE_DEFINED_               L"defined?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"dialogcreate"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"dialogenable"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"dialogdelete"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"dialogfileopen"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"dialogfilesave"
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"difference"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"directories"
#define LOCALIZED_ALTERNATE_DLLCALL                L"dllcall"
#define LOCALIZED_ALTERNATE_DLLFREE                L"dllfree"
#define LOCALIZED_ALTERNATE_DLLLOAD                L"dllload"
#define LOCALIZED_ALTERNATE_DOWN                   L"down"
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"downpitch"
#define LOCALIZED_ALTERNATE_DRIBBLE                L"dribble"
#define LOCALIZED_ALTERNATE_ED                     L"ed"
#define LOCALIZED_ALTERNATE_EDIT                   L"edit"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"ellipsearc"
#define LOCALIZED_ALTERNATE_EMPTYP                 L"emptyp"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"empty?"
#define LOCALIZED_ALTERNATE_EOFP                   L"eofp"
#define LOCALIZED_ALTERNATE_EOF_                   L"eof?"
#define LOCALIZED_ALTERNATE_EQUALP                 L"equalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"equal?"
#define LOCALIZED_ALTERNATE_ER                     L"er"
#define LOCALIZED_ALTERNATE_ERASE                  L"erase"
#define LOCALIZED_ALTERNATE_ERASEFILE              L"erasefile"
#define LOCALIZED_ALTERNATE_ERF                    L"erf"
#define LOCALIZED_ALTERNATE_ERROR                  L"error"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"eventcheck"
#define LOCALIZED_ALTERNATE_EXP                    L"exp"
#define LOCALIZED_ALTERNATE_FD                     L"fd"
#define LOCALIZED_ALTERNATE_FENCE                  L"fence"
#define LOCALIZED_ALTERNATE_FILL                   L"fill"
#define LOCALIZED_ALTERNATE_FILES                  L"files"
#define LOCALIZED_ALTERNATE_FIRST                  L"first"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"firsts"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"floodcolor"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"fontfacenames"
#define LOCALIZED_ALTERNATE_FOREVER                L"forever"
#define LOCALIZED_ALTERNATE_FORM                   L"form"
#define LOCALIZED_ALTERNATE_FORWARD                L"forward"
#define LOCALIZED_ALTERNATE_FPUT                   L"fput"
#define LOCALIZED_ALTERNATE_FS                     L"fs"
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"fullscreen"
#define LOCALIZED_ALTERNATE_FULLTEXT               L"fulltext"
#define LOCALIZED_ALTERNATE_GETFOCUS               L"getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   L"goto"
#define LOCALIZED_ALTERNATE_GIFLOAD                L"gifload"
#define LOCALIZED_ALTERNATE_GIFSIZE                L"gifsize"
#define LOCALIZED_ALTERNATE_GIFSAVE                L"gifsave"
#define LOCALIZED_ALTERNATE_GPROP                  L"gprop"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"greaterequalp"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"greaterequal?"
#define LOCALIZED_ALTERNATE_GREATERP               L"greaterp"
#define LOCALIZED_ALTERNATE_GREATER_               L"greater?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"groupboxcreate"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"groupboxdelete"
#define LOCALIZED_ALTERNATE_HALT                   L"halt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"hasownpenp"
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"hasownpen?"
#define LOCALIZED_ALTERNATE_HEADING                L"heading"
#define LOCALIZED_ALTERNATE_HELP                   L"help"
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"hideturtle"
#define LOCALIZED_ALTERNATE_HOME                   L"home"
#define LOCALIZED_ALTERNATE_HT                     L"ht"
#define LOCALIZED_ALTERNATE_IF                     L"if"
#define LOCALIZED_ALTERNATE_IFELSE                 L"ifelse"
#define LOCALIZED_ALTERNATE_IFF                    L"iff"
#define LOCALIZED_ALTERNATE_IFFALSE                L"iffalse"
#define LOCALIZED_ALTERNATE_IFT                    L"ift"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"iftrue"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"ingameport"
#define LOCALIZED_ALTERNATE_INPORT                 L"inport"
#define LOCALIZED_ALTERNATE_INPORTB                L"inportb"
#define LOCALIZED_ALTERNATE_INT                    L"int"
#define LOCALIZED_ALTERNATE_ITEM                   L"item"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"keyboardoff"
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"keyboardon"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"keyboardvalue"
#define LOCALIZED_ALTERNATE_KEYP                   L"keyp"
#define LOCALIZED_ALTERNATE_KEY_                   L"key?"
#define LOCALIZED_ALTERNATE_LABEL                  L"label"
#define LOCALIZED_ALTERNATE_LABELFONT              L"labelfont"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"labelsize"
#define LOCALIZED_ALTERNATE_LAST                   L"last"
#define LOCALIZED_ALTERNATE_LEFT                   L"left"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"leftroll"
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"lessequalp"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"lessequal?"
#define LOCALIZED_ALTERNATE_LESSP                  L"lessp"
#define LOCALIZED_ALTERNATE_LESS_                  L"less?"
#define LOCALIZED_ALTERNATE_LIGHT                  L"light"
#define LOCALIZED_ALTERNATE_LIST                   L"list"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"listboxaddstring"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"listboxcreate"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"listboxenable"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"listboxdelete"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"listboxdeletestring"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"listboxgetselect"
#define LOCALIZED_ALTERNATE_LISTP                  L"listp"
#define LOCALIZED_ALTERNATE_LIST_                  L"list?"
#define LOCALIZED_ALTERNATE_LN                     L"ln"
#define LOCALIZED_ALTERNATE_LOAD                   L"load"
#define LOCALIZED_ALTERNATE_LOCAL                  L"local"
#define LOCALIZED_ALTERNATE_LOG10                  L"log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"logoversion"
#define LOCALIZED_ALTERNATE_LOWERCASE              L"lowercase"
#define LOCALIZED_ALTERNATE_LPUT                   L"lput"
#define LOCALIZED_ALTERNATE_LR                     L"lr"
#define LOCALIZED_ALTERNATE_LSHIFT                 L"lshift"
#define LOCALIZED_ALTERNATE_LT                     L"lt"
#define LOCALIZED_ALTERNATE_MACHINE                L"machine"
#define LOCALIZED_ALTERNATE_MACROP                 L"macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 L"macro?"
#define LOCALIZED_ALTERNATE_MAKE                   L"Make"
#define LOCALIZED_ALTERNATE_MCI                    L"mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"member"
#define LOCALIZED_ALTERNATE_MEMBERP                L"memberp"
#define LOCALIZED_ALTERNATE_MEMBER_                L"member?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"messagebox"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"midiclose"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"midimessage"
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"midiopen"
#define LOCALIZED_ALTERNATE_MINUS                  L"minus"
#define LOCALIZED_ALTERNATE_MKDIR                  L"mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 L"modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"mouseoff"
#define LOCALIZED_ALTERNATE_MOUSEON                L"mouseon"
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"mousepos"
#define LOCALIZED_ALTERNATE_NAMEP                  L"namep"
#define LOCALIZED_ALTERNATE_NAME_                  L"name?"
#define LOCALIZED_ALTERNATE_NAMES                  L"names"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"netacceptoff"
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"netaccepton"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"netacceptreceivevalue"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"netacceptsendvalue"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"netconnectoff"
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"netconnecton"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"netconnectreceivevalue"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"netconnectsendvalue"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"netshutdown"
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"netstartup"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"nobitmapturtle"
#define LOCALIZED_ALTERNATE_NODES                  L"nodes"
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"nodribble"
#define LOCALIZED_ALTERNATE_NOSTATUS               L"nostatus"
#define LOCALIZED_ALTERNATE_NOT                    L"not"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"notequalp"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"notequal?"
#define LOCALIZED_ALTERNATE_NOYIELD                L"noyield"
#define LOCALIZED_ALTERNATE_NUMBERP                L"numberp"
#define LOCALIZED_ALTERNATE_NUMBER_                L"number?"
#define LOCALIZED_ALTERNATE_OP                     L"op"
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"openappend"
#define LOCALIZED_ALTERNATE_OPENREAD               L"openread"
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"openupdate"
#define LOCALIZED_ALTERNATE_OPENWRITE              L"openwrite"
#define LOCALIZED_ALTERNATE_OR                     L"or"
#define LOCALIZED_ALTERNATE_OUTPORT                L"outport"
#define LOCALIZED_ALTERNATE_OUTPORTB               L"outportb"
#define LOCALIZED_ALTERNATE_OUTPUT                 L"output"
#define LOCALIZED_ALTERNATE_PARSE                  L"parse"
#define LOCALIZED_ALTERNATE_PAUSE                  L"pause"
#define LOCALIZED_ALTERNATE_PC                     L"pc"
#define LOCALIZED_ALTERNATE_PD                     L"pd"
#define LOCALIZED_ALTERNATE_PE                     L"pe"
#define LOCALIZED_ALTERNATE_PENCOLOR               L"pencolor"
#define LOCALIZED_ALTERNATE_PENDOWN                L"pendown"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"pendownp"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"pendown?"
#define LOCALIZED_ALTERNATE_PENERASE               L"penerase"
#define LOCALIZED_ALTERNATE_PENMODE                L"penmode"
#define LOCALIZED_ALTERNATE_PENPAINT               L"penpaint"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"penpattern"
#define LOCALIZED_ALTERNATE_PENREVERSE             L"penreverse"
#define LOCALIZED_ALTERNATE_PENSIZE                L"pensize"
#define LOCALIZED_ALTERNATE_PENUP                  L"penup"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"perspective"
#define LOCALIZED_ALTERNATE_PITCH                  L"pitch"
#define LOCALIZED_ALTERNATE_PIXEL                  L"pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"playwave"
#define LOCALIZED_ALTERNATE_PLIST                  L"Plist"
#define LOCALIZED_ALTERNATE_PLISTS                 L"plists"
#define LOCALIZED_ALTERNATE_PO                     L"po"
#define LOCALIZED_ALTERNATE_POPDIR                 L"popdir"
#define LOCALIZED_ALTERNATE_POLYSTART              L"polystart"
#define LOCALIZED_ALTERNATE_POLYEND                L"polyend"
#define LOCALIZED_ALTERNATE_POLYVIEW               L"polyview"
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"portclose"
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"portflush"
#define LOCALIZED_ALTERNATE_PORTMODE               L"portmode"
#define LOCALIZED_ALTERNATE_PORTOPEN               L"portopen"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"portreadarray"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"portreadchar"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"portwritearray"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"portwritechar"
#define LOCALIZED_ALTERNATE_POS                    L"pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 L"posxyz"
#define LOCALIZED_ALTERNATE_POT                    L"pot"
#define LOCALIZED_ALTERNATE_POWER                  L"power"
#define LOCALIZED_ALTERNATE_PPROP                  L"Pprop"
#define LOCALIZED_ALTERNATE_PPT                    L"ppt"
#define LOCALIZED_ALTERNATE_PR                     L"pr"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"primitive?"
#define LOCALIZED_ALTERNATE_PRINT                  L"print"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"procedurep"
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"procedure?"
#define LOCALIZED_ALTERNATE_PROPLISTP              L"proplistp"
#define LOCALIZED_ALTERNATE_PROPLIST_              L"proplist?"
#define LOCALIZED_ALTERNATE_PROCEDURES             L"procedures"
#define LOCALIZED_ALTERNATE_PRODUCT                L"product"
#define LOCALIZED_ALTERNATE_PU                     L"pu"
#define LOCALIZED_ALTERNATE_PX                     L"px"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"questionbox"
#define LOCALIZED_ALTERNATE_QUOTIENT               L"quotient"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 L"radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"radiobuttoncreate"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"radiobuttonenable"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"radiobuttondelete"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"radiobuttonget"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"radiobuttonset"
#define LOCALIZED_ALTERNATE_RADSIN                 L"radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 L"radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 L"random"
#define LOCALIZED_ALTERNATE_RAWASCII               L"rawascii"
#define LOCALIZED_ALTERNATE_RC                     L"rc"
#define LOCALIZED_ALTERNATE_RCS                    L"rcs"
#define LOCALIZED_ALTERNATE_READCHAR               L"readchar"
#define LOCALIZED_ALTERNATE_READCHARS              L"readchars"
#define LOCALIZED_ALTERNATE_READER                 L"reader"
#define LOCALIZED_ALTERNATE_READLIST               L"readlist"
#define LOCALIZED_ALTERNATE_READPOS                L"readpos"
#define LOCALIZED_ALTERNATE_READRAWLINE            L"readrawline"
#define LOCALIZED_ALTERNATE_READWORD               L"readword"
#define LOCALIZED_ALTERNATE_REMAINDER              L"remainder"
#define LOCALIZED_ALTERNATE_REMPROP                L"remprop"
#define LOCALIZED_ALTERNATE_REPCOUNT               L"repcount"
#define LOCALIZED_ALTERNATE_REPEAT                 L"repeat"
#define LOCALIZED_ALTERNATE_RERANDOM               L"rerandom"
#define LOCALIZED_ALTERNATE_RIGHT                  L"right"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"rightroll"
#define LOCALIZED_ALTERNATE_RL                     L"rl"
#define LOCALIZED_ALTERNATE_RMDIR                  L"rmdir"
#define LOCALIZED_ALTERNATE_ROLL                   L"roll"
#define LOCALIZED_ALTERNATE_ROUND                  L"round"
#define LOCALIZED_ALTERNATE_RR                     L"rr"
#define LOCALIZED_ALTERNATE_RT                     L"rt"
#define LOCALIZED_ALTERNATE_RUN                    L"run"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"runparse"
#define LOCALIZED_ALTERNATE_RUNRESULT              L"runresult"
#define LOCALIZED_ALTERNATE_RW                     L"rw"
#define LOCALIZED_ALTERNATE_SAVE                   L"save"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"screencolor"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"scrollbarcreate"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"scrollbarenable"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"scrollbardelete"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"scrollbarget"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"scrollbarset"
#define LOCALIZED_ALTERNATE_SCROLLX                L"scrollx"
#define LOCALIZED_ALTERNATE_SCROLLY                L"scrolly"
#define LOCALIZED_ALTERNATE_SCRUNCH                L"scrunch"
#define LOCALIZED_ALTERNATE_SE                     L"se"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"selectbox"
#define LOCALIZED_ALTERNATE_SENTENCE               L"sentence"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"setactivearea"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"setbitindex"
#define LOCALIZED_ALTERNATE_SETBITMODE             L"setbitmode"
#define LOCALIZED_ALTERNATE_SETCLIP                L"setclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              L"setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"setcursornowait"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"setcursorwait"
#define LOCALIZED_ALTERNATE_SETFC                  L"setfc"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"setfloodcolor"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"setfocus"
#define LOCALIZED_ALTERNATE_SETH                   L"seth"
#define LOCALIZED_ALTERNATE_SETHEADING             L"setheading"
#define LOCALIZED_ALTERNATE_SETITEM                L"setitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"setlabelfont"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"setlight"
#define LOCALIZED_ALTERNATE_SETMARGINS             L"setmargins"
#define LOCALIZED_ALTERNATE_SETPC                  L"setpc"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"setpencolor"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"setpenpattern"
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"setpensize"
#define LOCALIZED_ALTERNATE_SETPITCH               L"setpitch"
#define LOCALIZED_ALTERNATE_SETPIXEL               L"setpixel"
#define LOCALIZED_ALTERNATE_SETPOS                 L"setpos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"setposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                L"setread"
#define LOCALIZED_ALTERNATE_SETREADPOS             L"setreadpos"
#define LOCALIZED_ALTERNATE_SETROLL                L"setroll"
#define LOCALIZED_ALTERNATE_SETSC                  L"setsc"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"setscreencolor"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"setscrunch"
#define LOCALIZED_ALTERNATE_SETTIMER               L"settimer"
#define LOCALIZED_ALTERNATE_SETTURTLE              L"setturtle"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"setturtlemode"
#define LOCALIZED_ALTERNATE_SETWRITE               L"setwrite"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"setwritepos"
#define LOCALIZED_ALTERNATE_SETX                   L"setx"
#define LOCALIZED_ALTERNATE_SETXY                  L"setxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"setxyz"
#define LOCALIZED_ALTERNATE_SETY                   L"sety"
#define LOCALIZED_ALTERNATE_SETZ                   L"setz"
#define LOCALIZED_ALTERNATE_SHELL                  L"shell"
#define LOCALIZED_ALTERNATE_SHOW                   L"show"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"shownp"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"shown?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"showturtle"
#define LOCALIZED_ALTERNATE_SIN                    L"sin"
#define LOCALIZED_ALTERNATE_SOUND                  L"sound"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"splitscreen"
#define LOCALIZED_ALTERNATE_SQRT                   L"sqrt"
#define LOCALIZED_ALTERNATE_SS                     L"ss"
#define LOCALIZED_ALTERNATE_ST                     L"st"
#define LOCALIZED_ALTERNATE_STANDOUT               L"standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           L"staticcreate"
#define LOCALIZED_ALTERNATE_STATICDELETE           L"staticdelete"
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"staticupdate"
#define LOCALIZED_ALTERNATE_STATUS                 L"status"
#define LOCALIZED_ALTERNATE_STEP                   L"step"
#define LOCALIZED_ALTERNATE_STEPPED                L"stepped"
#define LOCALIZED_ALTERNATE_STOP                   L"stop"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"substringp"
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"substring?"
#define LOCALIZED_ALTERNATE_SUM                    L"sum"
#define LOCALIZED_ALTERNATE_TAG                    L"tag"
#define LOCALIZED_ALTERNATE_TAN                    L"tan"
#define LOCALIZED_ALTERNATE_TEST                   L"test"
#define LOCALIZED_ALTERNATE_TEXT                   L"text"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"textscreen"
#define LOCALIZED_ALTERNATE_THING                  L"thing"
#define LOCALIZED_ALTERNATE_THROW                  L"throw"
#define LOCALIZED_ALTERNATE_TIME                   L"time"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"timemilli"
#define LOCALIZED_ALTERNATE_TO                     L"to"
#define LOCALIZED_ALTERNATE_TONE                   L"tone"
#define LOCALIZED_ALTERNATE_TOWARDS                L"towards"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"towardsxyz"
#define LOCALIZED_ALTERNATE_TRACE                  L"trace"
#define LOCALIZED_ALTERNATE_TRACED                 L"traced"
#define LOCALIZED_ALTERNATE_TS                     L"ts"
#define LOCALIZED_ALTERNATE_TURTLE                 L"turtle"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"turtlemode"
#define LOCALIZED_ALTERNATE_TURTLES                L"turtles"
#define LOCALIZED_ALTERNATE_TYPE                   L"type"
#define LOCALIZED_ALTERNATE_UNBURY                 L"unbury"
#define LOCALIZED_ALTERNATE_UNSTEP                 L"unstep"
#define LOCALIZED_ALTERNATE_UNTRACE                L"untrace"
#define LOCALIZED_ALTERNATE_UP                     L"up"
#define LOCALIZED_ALTERNATE_UPPERCASE              L"uppercase"
#define LOCALIZED_ALTERNATE_UPPITCH                L"uppitch"
#define LOCALIZED_ALTERNATE_WAIT                   L"wait"
#define LOCALIZED_ALTERNATE_WINDOW                 L"window"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"windowcreate"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"windowenable"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"windowdelete"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"windowfileedit"
#define LOCALIZED_ALTERNATE_WINDOWSET              L"windowset"
#define LOCALIZED_ALTERNATE_WINHELP                L"winhelp"
#define LOCALIZED_ALTERNATE_WORD                   L"word"
#define LOCALIZED_ALTERNATE_WORDP                  L"wordp"
#define LOCALIZED_ALTERNATE_WORD_                  L"word?"
#define LOCALIZED_ALTERNATE_WRAP                   L"wrap"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"writepos"
#define LOCALIZED_ALTERNATE_WRITER                 L"writer"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"yesnobox"
#define LOCALIZED_ALTERNATE_YIELD                  L"yield"
#define LOCALIZED_ALTERNATE_ZOOM                   L"zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"Cancel"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&Apply"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"The FMSLogo programming environment"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&File"
#define LOCALIZED_FILE_NEW              L"&New\t(erase workspace)"
#define LOCALIZED_FILE_LOAD             L"&Load...\t(merge into workspace)"
#define LOCALIZED_FILE_OPEN             L"&Open...\t(replace workspace)" 
#define LOCALIZED_FILE_SAVE             L"&Save" 
#define LOCALIZED_FILE_SAVEAS           L"Save &As..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"Se&t As Screen Saver"
#define LOCALIZED_FILE_EDIT             L"&Edit..."
#define LOCALIZED_FILE_ERASE            L"E&rase..."
#define LOCALIZED_FILE_EXIT             L"E&xit"

#define LOCALIZED_BITMAP               L"&Bitmap"
#define LOCALIZED_BITMAP_NEW           L"&New"
#define LOCALIZED_BITMAP_LOAD          L"&Load..."
#define LOCALIZED_BITMAP_SAVE          L"&Save"
#define LOCALIZED_BITMAP_SAVEAS        L"Save &As..."
#define LOCALIZED_BITMAP_PRINT         L"&Print..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"P&rinter Setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"A&ctive Area..."

#define LOCALIZED_SET                  L"&Set"
#define LOCALIZED_SET_PENSIZE          L"Pen Si&ze..."
#define LOCALIZED_SET_LABELFONT        L"&Label Font..."
#define LOCALIZED_SET_COMMANDERFONT    L"&Commander Font..."
#define LOCALIZED_SET_PENCOLOR         L"&Pen Color..."
#define LOCALIZED_SET_FLOODCOLOR       L"F&lood Color..."
#define LOCALIZED_SET_SCREENCOLOR      L"&Screen Color..."

#define LOCALIZED_ZOOM                 L"&Zoom" 
#define LOCALIZED_ZOOM_IN              L"&In"
#define LOCALIZED_ZOOM_OUT             L"&Out"
#define LOCALIZED_ZOOM_NORMAL          L"&Normal"

#define LOCALIZED_HELP                 L"&Help" 
#define LOCALIZED_HELP_INDEX           L"&Index"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutorial"
#define LOCALIZED_HELP_DEMO            L"&Demo" 
#define LOCALIZED_HELP_EXAMPLE         L"&Examples"
#define LOCALIZED_HELP_RELEASENOTES    L"&Release Notes"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"&About " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"&About MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"LANGUAGE to English"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"English to LANGUAGE"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Select Active Area"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"These affect Printing and Saving Bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-High"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Low" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-High"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Low"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"Turtle steps per inch printed:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"FMSLogo Screensaver Settings"
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Locate ..." 
#define LOCALIZED_SCREENSAVER_FILE              L"Logo &File:" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"Select a " LOCALIZED_ALTERNATE_STARTUP " instruction"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"No procedures are defined"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Copy"
#define LOCALIZED_POPUP_CUT                      L"Cut"
#define LOCALIZED_POPUP_PASTE                    L"Paste"
#define LOCALIZED_POPUP_DELETE                   L"Delete"
#define LOCALIZED_POPUP_UNDO                     L"Undo"
#define LOCALIZED_POPUP_REDO                     L"Redo"
#define LOCALIZED_POPUP_SELECTALL                L"Select All"
#define LOCALIZED_POPUP_HELP                     L"Topic Search"
#define LOCALIZED_POPUP_REMOVELINES              L"Remove Selected Lines"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Editor"

#define LOCALIZED_EDITOR_FILE                    L"&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Save and Exit\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"Save to &Workspace"
#define LOCALIZED_EDITOR_FILE_PRINT              L"&Print..." 
#define LOCALIZED_EDITOR_FILE_EXIT               L"E&xit" 

#define LOCALIZED_EDITOR_EDIT                    L"&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&Undo\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&Redo\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"&Cut\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"C&opy\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"&Paste\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&Delete\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"C&lear All\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"S&elect All\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"&Search"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"&Find...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Replace...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Next\tF3" 

#define LOCALIZED_EDITOR_SET                     L"Se&t" 
#define LOCALIZED_EDITOR_SET_FONT                L"&Font..." 

#define LOCALIZED_EDITOR_TEST                    L"Test"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"&Run Selection\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    L"&Help" 
#define LOCALIZED_EDITOR_HELP_INDEX              L"&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&Topic Search\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Save and Exit"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&Don't Save"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"There are unsaved changes in the workspace.  If you exit without saving, these changes will be lost.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"Would you like to save your changes before exiting?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Commander"
#define LOCALIZED_COMMANDER_HALT                L"Halt"
#define LOCALIZED_COMMANDER_TRACE               L"Trace"
#define LOCALIZED_COMMANDER_NOTRACE             L"NoTrace"
#define LOCALIZED_COMMANDER_PAUSE               L"Pause"
#define LOCALIZED_COMMANDER_STATUS              L"Status"
#define LOCALIZED_COMMANDER_NOSTATUS            L"NoStatus"
#define LOCALIZED_COMMANDER_STEP                L"Step"
#define LOCALIZED_COMMANDER_UNSTEP              L"UnStep"
#define LOCALIZED_COMMANDER_RESET               L"Reset"
#define LOCALIZED_COMMANDER_EXECUTE             L"Execute"
#define LOCALIZED_COMMANDER_EDALL               L"Edall"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Status"
#define LOCALIZED_STATUS_PEN                    L"Pen"
#define LOCALIZED_STATUS_CONTACT                L"Contact:"
#define LOCALIZED_STATUS_WIDTH                  L"Width:"
#define LOCALIZED_STATUS_STYLE                  L"Style:"
#define LOCALIZED_STATUS_ORIENTATION            L"Orientation"
#define LOCALIZED_STATUS_PITCH                  L"Pitch:"
#define LOCALIZED_STATUS_HEADING                L"Heading:"
#define LOCALIZED_STATUS_ROLL                   L"Roll:"
#define LOCALIZED_STATUS_TURTLE                 L"Turtle"
#define LOCALIZED_STATUS_POSITION               L"Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Which:"
#define LOCALIZED_STATUS_VISIBILITY             L"Visibility:"
#define LOCALIZED_STATUS_COLOR                  L"Color"
#define LOCALIZED_STATUS_PENCOLOR               L"Pen(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"Flood(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Screen(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"Kernel"
#define LOCALIZED_STATUS_CALLS                  L"Calls:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"Peak Memory:"

#define LOCALIZED_STATUS_PENREVERSE     L"Reverse"
#define LOCALIZED_STATUS_PENNORMAL      L"Normal"
#define LOCALIZED_STATUS_PENERASE       L"Erase"
#define LOCALIZED_STATUS_PENUP          L"Up"
#define LOCALIZED_STATUS_PENDOWN        L"Down"
#define LOCALIZED_STATUS_PENSHOWN       L"Shown"
#define LOCALIZED_STATUS_PENHIDDEN      L"Hidden"
#define LOCALIZED_STATUS_POLYGONS       L"Polygons"
#define LOCALIZED_STATUS_VECTORS        L"Vectors"
#define LOCALIZED_STATUS_NODES          L"Nodes"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/A"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&All"
#define LOCALIZED_ERASEPROCEDURE                L"Erase Procedure"
#define LOCALIZED_EDITPROCEDURE                 L"Edit Procedure"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Set Color"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Pen Color"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"Flood Color"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Screen Color"
#define LOCALIZED_SETCOLOR_RED                 L"Red"
#define LOCALIZED_SETCOLOR_GREEN               L"Green"
#define LOCALIZED_SETCOLOR_BLUE                L"Blue"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Pen Size"
#define LOCALIZED_SETPENSIZE_SIZE              L"Thickness"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"About " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"Version"
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"Core by Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Special thanks to Yehuda Katz and Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc."
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"About FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS stands for Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"Changes in this edit session may be lost.\n\nDo you really want to exit " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"An Edit session is running"

#define LOCALIZED_COULDNOTWRITEBMP            L"Could not write .bmp"
#define LOCALIZED_COULDNOTOPENBMP             L"Could not open .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           L"Unable to create Windows 3.0 bitmap"
#define LOCALIZED_NOTVALIDBMP                 L"Not a Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"You have not saved to disk"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"Executing a new will erase all definitions.\n\nContinue with New?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"This will erase all of your unsaved changes.\n\nContinue with Open?"

#define LOCALIZED_EDITORISOPEN                  L"Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved."

#define LOCALIZED_ERROR_CANTREADFILE            L"Unable to read file \"%s\" from disk"
#define LOCALIZED_ERROR_CANTWRITEFILE           L"Unable to write file \"%s\" to disk"

#define LOCALIZED_SAVETOWORKSPACE                L"Save to Workspace"
#define LOCALIZED_CONTENTSCHANGED                L"Contents Changed"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"The contents have changed.\nWould you like to save the changes to the workspace?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message."
#define LOCALIZED_RETURNTOEDIT                  L"Return to the editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              L"Error in File"
#define LOCALIZED_ERRORINFILEMESSAGE            L"There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?"

#define LOCALIZED_CANNOTALLOCATESCREEN          L"Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue."


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"Select the Logo program to load (merge into workspace)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"Select the Logo program to open (replace the workspace with)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"Select the file to which the workspace will be saved"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"Select the image to load"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"Select the file to which the active area will be saved"

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"All Files (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Logo Files (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" stops\n"
#define LOCALIZED_TRACING_OUTPUTS           L" outputs %s\n"
#define LOCALIZED_TRACING_MAKE              L"Make %s %s"
#define LOCALIZED_TRACING_PPROP             L"Pprop %s %s %s"
#define LOCALIZED_TRACING_LOCATION          L" in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Single Step"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s defined\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"erase"
#define LOCALIZED_PENMODE_REVERSE  L"reverse"
#define LOCALIZED_PENMODE_PAINT    L"paint"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: Fatal Internal Error"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Out of memory"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"Out of memory"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"turtle out of bounds"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"couldn't initialize graphics"
#define LOCALIZED_ERROR_BADDATA                L"%p doesn't like %s as input"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p didn't output to %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"not enough inputs to %p"
#define LOCALIZED_ERROR_TOOMUCH                L"too much inside ()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"You don't say what to do with %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"too many ('s"
#define LOCALIZED_ERROR_NOVALUE                L"%s has no value"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"unexpected ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"unexpected ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"unexpected '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"I don't know how to %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"Can't find catch tag for %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p is already defined"
#define LOCALIZED_ERROR_STOPPING               L"Stopping..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"Already dribbling"
#define LOCALIZED_ERROR_FILESYSTEM                   L"File system error: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"Could not open file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"Unable to open file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"File already open"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"File not open"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"Could not create editor file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"Could not launch the editor" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"Could not read editor file" 
#define LOCALIZED_ERROR_IFWARNING              L"Assuming you mean IFELSE, not IF"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p shadowed by local in procedure call"
#define LOCALIZED_ERROR_USER                   L"Throw \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p is a primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            L"Can't use TO inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"Can only use %p inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"You must be in a procedure to use OUTPUT or STOP"
#define LOCALIZED_ERROR_NOTEST                 L"%p without TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"Macro output %s instead of a list"
#define LOCALIZED_ERROR_DEEPEND                L"END inside multi-line instruction"
#define LOCALIZED_ERROR_DEEPENDIN              L"END inside multi-line instruction in %p"
#define LOCALIZED_ERROR_UNKNOWN                L"Unknown error condition - internal error."
#define LOCALIZED_PAUSING                      L"Pausing..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Invalid state for instruction: %p"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"cannot set the mode of a turtle with a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"cannot make a special turtle use a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"cannot use the clipboard as a rotating bitmap"
#define LOCALIZED_ERROR_SPECIALFORM                L"%p doesn't like %p as input because it has a special form"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Error"
#define LOCALIZED_ERROR_BADINPUT             L"Bad input"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"Input is not paired"

#define LOCALIZED_ERROR_CANTOPENPORT         L"Could not open port"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"Could not close port"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"Could not flush port"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"Could not build dcb on port"
#define LOCALIZED_ERROR_CANTSETPORT          L"Could not set port"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"Port is already open"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"Port is not open"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s already exists"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s does not exist"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"DLL is not loaded"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"DLL load failed"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Invalid data type input"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Invalid output type"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Function not found"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"Not all Type/Data inputs are paired"

#define LOCALIZED_ERROR_NETWORK               L"Network Error"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Network Receive Error"
#define LOCALIZED_ERROR_NETWORKSEND           L"Network Send Error"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Unexpected Error, Network may be shutdown"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"Already started"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"Already on"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"Already off"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Name too long"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"Not initialized"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"System not ready"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"Version is not supported"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"Can't send after socket shutdown"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Interrupted system call"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Authoritative Answer: Host not found"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"Non-Authoritative: Host not found. See NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Non-recoverable error"
#define LOCALIZED_ERROR_NETWORKNODATA              L"No data record available"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"Bad file number"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"Operation would block"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"Operation now in progress"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"Operation already in progress"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Bad address"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Destination address required"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Message too long"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Protocol family not supported"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"Directory not empty"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Application limit has been reached"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"Disk quota exceeded"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Too many open files"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Access denied"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Socket operation on non-socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"Can't assign requested address"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"Address already in use"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"Address family not supported by protocol family"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Connection timed out"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Socket type not supported"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protocol not supported"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"No space in buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"Socket is already connected"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"Socket is not connected"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Bad protocol option"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"Connection reset by peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"Software caused connection abort"
#define LOCALIZED_ERROR_NETWORKISDOWN              L"Network is down"
#define LOCALIZED_ERROR_NETWORKRESET               L"Network was reset"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"Connection refused"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"Host is down"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"Host is unreachable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"Protocol is wrong type for socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Operation not supported on socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"No path to remote host was found"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Too many references"

#define LOCALIZED_ERROR_POLYSTART               L"PolyStart Error"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"You already have a Polygon started"

#define LOCALIZED_ERROR_POLYEND                 L"PolyEnd Error"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"You have not started a Polygon"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"You must have at least 3 vectors to define a polygon"

#define LOCALIZED_ERROR_SOUND                 L"Sound Error"

#define LOCALIZED_ERROR_MIDI                  L"MIDI Error"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"Invalid MIDI device"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"Already open"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"Not open"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"No Text in Clipboard"

#define LOCALIZED_ERROR_MCI                   L"MCI Error"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Timer not found"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"Online help is unavailable because hhctrl.ocx could not be loaded." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"Invalid Command Line" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"The environment variable TMP is not defined or invalid.\n" LOCALIZED_GENERAL_PRODUCTNAME " will attempt to use C:\\ for storing temporary files"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Problem Generating GIF, check memory and diskspace"
#define LOCALIZED_ERROR_GIFREADFAILED         L"Problem Reading GIF, check memory and diskspace"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"BitMap Index out of range"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Cut failed, Possibly not enough Memory"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Nothing to Paste" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"BitMap at Index must be initialized with a bitmap" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"Turtle %d has no picture, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"Sorry, no font named %s was found.  Choose one of the following:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"Print driver does not support this function" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"Cannot draw image"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"Cannot extract image"
#define LOCALIZED_ERROR_SUBCODE                 L"Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Input:"
#define LOCALIZED_PROMPT_TO     L"To Mode (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   L"List Mode (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  L"Pause Mode (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  L"Input Mode (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"Changed to \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"Could not chdir to directory \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"Popped to \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Now in newly created directory \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         L"Failed to create directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Removed directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         L"Failed to remove directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"The directory does not exist."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Make sure the directory is empty before trying to remove it."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Logo Picture"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"Active Area"
#define LOCALIZED_INFORMATION   L"Information"
#define LOCALIZED_WARNING       L"Warning"
#define LOCALIZED_UNTITLED      L"Untitled"
#define LOCALIZED_UNKNOWN       L"Unknown"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"nothing"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Find"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Replace" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"Cannot find %s"


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
#define LOCALIZED_COLOR_ALICEBLUE             L"AliceBlue"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"AntiqueWhite"
#define LOCALIZED_COLOR_AQUA                  L"Aqua"
#define LOCALIZED_COLOR_AQUAMARINE            L"Aquamarine"
#define LOCALIZED_COLOR_AZURE                 L"Azure"
#define LOCALIZED_COLOR_BEIGE                 L"Beige"
#define LOCALIZED_COLOR_BISQUE                L"Bisque"
#define LOCALIZED_COLOR_BLACK                 L"Black"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"BlanchedAlmond"
#define LOCALIZED_COLOR_BLUE                  L"Blue"
#define LOCALIZED_COLOR_BLUEVIOLET            L"BlueViolet"
#define LOCALIZED_COLOR_BROWN                 L"Brown"
#define LOCALIZED_COLOR_BURLYWOOD             L"BurlyWood"
#define LOCALIZED_COLOR_CADETBLUE             L"CadetBlue"
#define LOCALIZED_COLOR_CHARTREUSE            L"Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             L"Chocolate"
#define LOCALIZED_COLOR_CORAL                 L"Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"CornflowerBlue"
#define LOCALIZED_COLOR_CORNSILK              L"Cornsilk"
#define LOCALIZED_COLOR_CRIMSON               L"Crimson"
#define LOCALIZED_COLOR_CYAN                  L"Cyan"
#define LOCALIZED_COLOR_DARKBLUE              L"DarkBlue"
#define LOCALIZED_COLOR_DARKCYAN              L"DarkCyan"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"DarkGoldenRod"
#define LOCALIZED_COLOR_DARKGRAY              L"DarkGray"
#define LOCALIZED_COLOR_DARKGREEN             L"DarkGreen"
#define LOCALIZED_COLOR_DARKGREY              L"DarkGrey"
#define LOCALIZED_COLOR_DARKKHAKI             L"DarkKhaki"
#define LOCALIZED_COLOR_DARKMAGENTA           L"DarkMagenta"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"DarkOliveGreen"
#define LOCALIZED_COLOR_DARKORANGE            L"DarkOrange"
#define LOCALIZED_COLOR_DARKORCHID            L"DarkOrchid"
#define LOCALIZED_COLOR_DARKRED               L"DarkRed"
#define LOCALIZED_COLOR_DARKSALMON            L"DarkSalmon"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"DarkSeaGreen"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"DarkSlateBlue"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"DarkSlateGray"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"DarkSlateGrey"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"DarkTurquoise"
#define LOCALIZED_COLOR_DARKVIOLET            L"DarkViolet"
#define LOCALIZED_COLOR_DEEPPINK              L"DeepPink"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"DeepSkyBlue"
#define LOCALIZED_COLOR_DIMGRAY               L"DimGray"
#define LOCALIZED_COLOR_DIMGREY               L"DimGrey"
#define LOCALIZED_COLOR_DODGERBLUE            L"DodgerBlue"
#define LOCALIZED_COLOR_FIREBRICK             L"FireBrick"
#define LOCALIZED_COLOR_FLORALWHITE           L"FloralWhite"
#define LOCALIZED_COLOR_FORESTGREEN           L"ForestGreen"
#define LOCALIZED_COLOR_FUCHSIA               L"Fuchsia"
#define LOCALIZED_COLOR_GAINSBORO             L"Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            L"GhostWhite"
#define LOCALIZED_COLOR_GOLD                  L"Gold"
#define LOCALIZED_COLOR_GOLDENROD             L"GoldenRod"
#define LOCALIZED_COLOR_GRAY                  L"Gray"
#define LOCALIZED_COLOR_GREEN                 L"Green"
#define LOCALIZED_COLOR_GREENYELLOW           L"GreenYellow"
#define LOCALIZED_COLOR_GREY                  L"Grey"
#define LOCALIZED_COLOR_HONEYDEW              L"HoneyDew"
#define LOCALIZED_COLOR_HOTPINK               L"HotPink"
#define LOCALIZED_COLOR_INDIANRED             L"IndianRed"
#define LOCALIZED_COLOR_INDIGO                L"Indigo"
#define LOCALIZED_COLOR_IVORY                 L"Ivory"
#define LOCALIZED_COLOR_KHAKI                 L"Khaki"
#define LOCALIZED_COLOR_LAVENDER              L"Lavender"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"LavenderBlush"
#define LOCALIZED_COLOR_LAWNGREEN             L"LawnGreen"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"LemonChiffon"
#define LOCALIZED_COLOR_LIGHTBLUE             L"LightBlue"
#define LOCALIZED_COLOR_LIGHTCORAL            L"LightCoral"
#define LOCALIZED_COLOR_LIGHTCYAN             L"LightCyan"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"LightGoldenRodYellow"
#define LOCALIZED_COLOR_LIGHTGRAY             L"LightGray"
#define LOCALIZED_COLOR_LIGHTGREEN            L"LightGreen"
#define LOCALIZED_COLOR_LIGHTGREY             L"LightGrey"
#define LOCALIZED_COLOR_LIGHTPINK             L"LightPink"
#define LOCALIZED_COLOR_LIGHTSALMON           L"LightSalmon"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"LightSeaGreen"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"LightSkyBlue"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"LightSlateGray"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"LightSlateGrey"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"LightSteelBlue"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"LightYellow"
#define LOCALIZED_COLOR_LIME                  L"Lime"
#define LOCALIZED_COLOR_LIMEGREEN             L"LimeGreen"
#define LOCALIZED_COLOR_LINEN                 L"Linen"
#define LOCALIZED_COLOR_MAGENTA               L"Magenta"
#define LOCALIZED_COLOR_MAROON                L"Maroon"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"MediumAquaMarine"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"MediumBlue"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"MediumOrchid"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"MediumPurple"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"MediumSeaGreen"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"MediumSlateBlue"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"MediumSpringGreen"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"MediumTurquoise"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"MediumVioletRed"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"MidnightBlue"
#define LOCALIZED_COLOR_MINTCREAM             L"MintCream"
#define LOCALIZED_COLOR_MISTYROSE             L"MistyRose"
#define LOCALIZED_COLOR_MOCCASIN              L"Moccasin"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"NavajoWhite"
#define LOCALIZED_COLOR_NAVY                  L"Navy"
#define LOCALIZED_COLOR_OLDLACE               L"OldLace"
#define LOCALIZED_COLOR_OLIVE                 L"Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             L"OliveDrab"
#define LOCALIZED_COLOR_ORANGE                L"Orange"
#define LOCALIZED_COLOR_ORANGERED             L"OrangeRed"
#define LOCALIZED_COLOR_ORCHID                L"Orchid"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"PaleGoldenRod"
#define LOCALIZED_COLOR_PALEGREEN             L"PaleGreen"
#define LOCALIZED_COLOR_PALETURQUOISE         L"PaleTurquoise"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"PaleVioletRed"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"PapayaWhip"
#define LOCALIZED_COLOR_PEACHPUFF             L"PeachPuff"
#define LOCALIZED_COLOR_PERU                  L"Peru"
#define LOCALIZED_COLOR_PINK                  L"Pink"
#define LOCALIZED_COLOR_PLUM                  L"Plum"
#define LOCALIZED_COLOR_POWDERBLUE            L"PowderBlue"
#define LOCALIZED_COLOR_PURPLE                L"Purple"
#define LOCALIZED_COLOR_RED                   L"Red"
#define LOCALIZED_COLOR_ROSYBROWN             L"RosyBrown"
#define LOCALIZED_COLOR_ROYALBLUE             L"RoyalBlue"
#define LOCALIZED_COLOR_SADDLEBROWN           L"SaddleBrown"
#define LOCALIZED_COLOR_SALMON                L"Salmon"
#define LOCALIZED_COLOR_SANDYBROWN            L"SandyBrown"
#define LOCALIZED_COLOR_SEAGREEN              L"SeaGreen"
#define LOCALIZED_COLOR_SEASHELL              L"SeaShell"
#define LOCALIZED_COLOR_SIENNA                L"Sienna"
#define LOCALIZED_COLOR_SILVER                L"Silver"
#define LOCALIZED_COLOR_SKYBLUE               L"SkyBlue"
#define LOCALIZED_COLOR_SLATEBLUE             L"SlateBlue"
#define LOCALIZED_COLOR_SLATEGRAY             L"SlateGray"
#define LOCALIZED_COLOR_SLATEGREY             L"SlateGrey"
#define LOCALIZED_COLOR_SNOW                  L"Snow"
#define LOCALIZED_COLOR_SPRINGGREEN           L"SpringGreen"
#define LOCALIZED_COLOR_STEELBLUE             L"SteelBlue"
#define LOCALIZED_COLOR_TAN                   L"Tan"
#define LOCALIZED_COLOR_TEAL                  L"Teal"
#define LOCALIZED_COLOR_THISTLE               L"Thistle"
#define LOCALIZED_COLOR_TOMATO                L"Tomato"
#define LOCALIZED_COLOR_TURQUOISE             L"Turquoise"
#define LOCALIZED_COLOR_VIOLET                L"Violet"
#define LOCALIZED_COLOR_WHEAT                 L"Wheat"
#define LOCALIZED_COLOR_WHITE                 L"White"
#define LOCALIZED_COLOR_WHITESMOKE            L"WhiteSmoke"
#define LOCALIZED_COLOR_YELLOW                L"Yellow"
#define LOCALIZED_COLOR_YELLOWGREEN           L"YellowGreen"

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       L"Window"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       L"Static"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      L"ListBox"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     L"ComboBox"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       L"Button"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    L"ScrollBar"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     L"GroupBox"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  L"RadioButton"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     L"CheckBox"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       L"Dialog"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE L"Courier New"
