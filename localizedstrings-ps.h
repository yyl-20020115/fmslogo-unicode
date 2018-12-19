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
// This file contains localized strings for Pseudoloc by David Costanzo
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
#define LOCALIZED_ALTERNATE_TRUE     L"pseudo.true"
#define LOCALIZED_ALTERNATE_FALSE    L"pseudo.false"
#define LOCALIZED_ALTERNATE_END      L"pseudo.end"
#define LOCALIZED_ALTERNATE_TOPLEVEL L"pseudo.toplevel"
#define LOCALIZED_ALTERNATE_SYSTEM   L"pseudo.system"

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    L"pseudo.caseignoredp"
#define LOCALIZED_ALTERNATE_ERRACT          L"pseudo.erract"
#define LOCALIZED_ALTERNATE_STARTUP         L"pseudo.startup"
#define LOCALIZED_ALTERNATE_REDEFP          L"pseudo.redefp"
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT L"pseudo.printwidthlimit"
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT L"pseudo.printdepthlimit"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              L"pseudo..defmacro"
#define LOCALIZED_ALTERNATE__EQ                    L"pseudo..eq"
#define LOCALIZED_ALTERNATE__MACRO                 L"pseudo..macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L"pseudo..maybeoutput"
#define LOCALIZED_ALTERNATE__SETBF                 L"pseudo..setbf"
#define LOCALIZED_ALTERNATE__SETFIRST              L"pseudo..setfirst"
#define LOCALIZED_ALTERNATE__SETITEM               L"pseudo..setitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"pseudo.activearea"
#define LOCALIZED_ALTERNATE_ALLOPEN                L"pseudo.allopen"
#define LOCALIZED_ALTERNATE_AND                    L"pseudo.and"
#define LOCALIZED_ALTERNATE_APPLY                  L"pseudo.apply"
#define LOCALIZED_ALTERNATE_ARCCOS                 L"pseudo.arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"pseudo.arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"pseudo.arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"pseudo.arity"
#define LOCALIZED_ALTERNATE_ARRAY                  L"pseudo.array"
#define LOCALIZED_ALTERNATE_ARRAYP                 L"pseudo.arrayp"
#define LOCALIZED_ALTERNATE_ARRAY_                 L"pseudo.array?"
#define LOCALIZED_ALTERNATE_ASCII                  L"pseudo.ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 L"pseudo.ashift"
#define LOCALIZED_ALTERNATE_BACK                   L"pseudo.back"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"pseudo.backslashedp"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"pseudo.backslashed?"
#define LOCALIZED_ALTERNATE_BEFOREP                L"pseudo.beforep"
#define LOCALIZED_ALTERNATE_BEFORE_                L"pseudo.before?"
#define LOCALIZED_ALTERNATE_BF                     L"pseudo.bf"
#define LOCALIZED_ALTERNATE_BFS                    L"pseudo.bfs"
#define LOCALIZED_ALTERNATE_BITAND                 L"pseudo.bitand"
#define LOCALIZED_ALTERNATE_BITBLOCK               L"pseudo.bitblock"
#define LOCALIZED_ALTERNATE_BITCOPY                L"pseudo.bitcopy"
#define LOCALIZED_ALTERNATE_BITCUT                 L"pseudo.bitcut"
#define LOCALIZED_ALTERNATE_BITFIT                 L"pseudo.bitfit"
#define LOCALIZED_ALTERNATE_BITINDEX               L"pseudo.bitindex"
#define LOCALIZED_ALTERNATE_BITLOAD                L"pseudo.bitload"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"pseudo.bitloadsize"
#define LOCALIZED_ALTERNATE_BITSIZE                L"pseudo.bitsize"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"pseudo.bitmapturtle"
#define LOCALIZED_ALTERNATE_BITMODE                L"pseudo.bitmode"
#define LOCALIZED_ALTERNATE_BITNOT                 L"pseudo.bitnot"
#define LOCALIZED_ALTERNATE_BITOR                  L"pseudo.bitor"
#define LOCALIZED_ALTERNATE_BITPASTE               L"pseudo.bitpaste"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"pseudo.bitpastetoindex"
#define LOCALIZED_ALTERNATE_BITSAVE                L"pseudo.bitsave"
#define LOCALIZED_ALTERNATE_BITXOR                 L"pseudo.bitxor"
#define LOCALIZED_ALTERNATE_BK                     L"pseudo.bk"
#define LOCALIZED_ALTERNATE_BL                     L"pseudo.bl"
#define LOCALIZED_ALTERNATE_BURIED                 L"pseudo.buried"
#define LOCALIZED_ALTERNATE_BURY                   L"pseudo.bury"
#define LOCALIZED_ALTERNATE_BUTFIRST               L"pseudo.butfirst"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"pseudo.butfirsts"
#define LOCALIZED_ALTERNATE_BUTLAST                L"pseudo.butlast"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"pseudo.buttoncreate"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"pseudo.buttondelete"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"pseudo.buttonenable"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"pseudo.buttonupdate"
#define LOCALIZED_ALTERNATE_BUTTONP                L"pseudo.buttonp"
#define LOCALIZED_ALTERNATE_BUTTON_                L"pseudo.button?"
#define LOCALIZED_ALTERNATE_BYE                    L"pseudo.bye"
#define LOCALIZED_ALTERNATE_CATCH                  L"pseudo.catch"
#define LOCALIZED_ALTERNATE_CHAR                   L"pseudo.char"
#define LOCALIZED_ALTERNATE_CHDIR                  L"pseudo.chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"pseudo.checkboxcreate"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"pseudo.checkboxdelete"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"pseudo.checkboxenable"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"pseudo.checkboxget"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"pseudo.checkboxset"
#define LOCALIZED_ALTERNATE_CLEAN                  L"pseudo.clean"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"pseudo.clearpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"pseudo.clearscreen"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"pseudo.cleartext"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"pseudo.cleartimer"
#define LOCALIZED_ALTERNATE_CLOSE                  L"pseudo.close"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"pseudo.closeall"
#define LOCALIZED_ALTERNATE_CO                     L"pseudo.co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"pseudo.comboboxaddstring"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"pseudo.comboboxcreate"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"pseudo.comboboxdelete"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"pseudo.comboboxenable"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"pseudo.comboboxdeletestring"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"pseudo.comboboxgettext"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"pseudo.comboboxsettext"
#define LOCALIZED_ALTERNATE_CONTENTS               L"pseudo.contents"
#define LOCALIZED_ALTERNATE_CONTINUE               L"pseudo.continue"
#define LOCALIZED_ALTERNATE_COPYDEF                L"pseudo.copydef"
#define LOCALIZED_ALTERNATE_COS                    L"pseudo.cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"pseudo.count"
#define LOCALIZED_ALTERNATE_CS                     L"pseudo.cs"
#define LOCALIZED_ALTERNATE_CT                     L"pseudo.ct"
#define LOCALIZED_ALTERNATE_CURSOR                 L"pseudo.cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"pseudo.debugwindows"
#define LOCALIZED_ALTERNATE_DEFINE                 L"pseudo.define"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"pseudo.definedp"
#define LOCALIZED_ALTERNATE_DEFINED_               L"pseudo.defined?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"pseudo.dialogcreate"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"pseudo.dialogenable"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"pseudo.dialogdelete"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"pseudo.dialogfileopen"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"pseudo.dialogfilesave"
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"pseudo.difference"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"pseudo.directories"
#define LOCALIZED_ALTERNATE_DLLCALL                L"pseudo.dllcall"
#define LOCALIZED_ALTERNATE_DLLFREE                L"pseudo.dllfree"
#define LOCALIZED_ALTERNATE_DLLLOAD                L"pseudo.dllload"
#define LOCALIZED_ALTERNATE_DOWN                   L"pseudo.down"
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"pseudo.downpitch"
#define LOCALIZED_ALTERNATE_DRIBBLE                L"pseudo.dribble"
#define LOCALIZED_ALTERNATE_ED                     L"pseudo.ed"
#define LOCALIZED_ALTERNATE_EDIT                   L"pseudo.edit"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"pseudo.ellipsearc"
#define LOCALIZED_ALTERNATE_EMPTYP                 L"pseudo.emptyp"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"pseudo.empty?"
#define LOCALIZED_ALTERNATE_EOFP                   L"pseudo.eofp"
#define LOCALIZED_ALTERNATE_EOF_                   L"pseudo.eof?"
#define LOCALIZED_ALTERNATE_EQUALP                 L"pseudo.equalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"pseudo.equal?"
#define LOCALIZED_ALTERNATE_ER                     L"pseudo.er"
#define LOCALIZED_ALTERNATE_ERASE                  L"pseudo.erase"
#define LOCALIZED_ALTERNATE_ERASEFILE              L"pseudo.erasefile"
#define LOCALIZED_ALTERNATE_ERF                    L"pseudo.erf"
#define LOCALIZED_ALTERNATE_ERROR                  L"pseudo.error"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"pseudo.eventcheck"
#define LOCALIZED_ALTERNATE_EXP                    L"pseudo.exp"
#define LOCALIZED_ALTERNATE_FD                     L"pseudo.fd"
#define LOCALIZED_ALTERNATE_FENCE                  L"pseudo.fence"
#define LOCALIZED_ALTERNATE_FILL                   L"pseudo.fill"
#define LOCALIZED_ALTERNATE_FILES                  L"pseudo.files"
#define LOCALIZED_ALTERNATE_FIRST                  L"pseudo.first"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"pseudo.firsts"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"pseudo.floodcolor"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"pseudo.fontfacenames"
#define LOCALIZED_ALTERNATE_FOREVER                L"pseudo.forever"
#define LOCALIZED_ALTERNATE_FORM                   L"pseudo.form"
#define LOCALIZED_ALTERNATE_FORWARD                L"pseudo.forward"
#define LOCALIZED_ALTERNATE_FPUT                   L"pseudo.fput"
#define LOCALIZED_ALTERNATE_FS                     L"pseudo.fs"
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"pseudo.fullscreen"
#define LOCALIZED_ALTERNATE_FULLTEXT               L"pseudo.fulltext"
#define LOCALIZED_ALTERNATE_GETFOCUS               L"pseudo.getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   L"pseudo.goto"
#define LOCALIZED_ALTERNATE_GIFLOAD                L"pseudo.gifload"
#define LOCALIZED_ALTERNATE_GIFSIZE                L"pseudo.gifsize"
#define LOCALIZED_ALTERNATE_GIFSAVE                L"pseudo.gifsave"
#define LOCALIZED_ALTERNATE_GPROP                  L"pseudo.gprop"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"pseudo.greaterequalp"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"pseudo.greaterequal?"
#define LOCALIZED_ALTERNATE_GREATERP               L"pseudo.greaterp"
#define LOCALIZED_ALTERNATE_GREATER_               L"pseudo.greater?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"pseudo.groupboxcreate"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"pseudo.groupboxdelete"
#define LOCALIZED_ALTERNATE_HALT                   L"pseudo.halt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"pseudo.hasownpenp"
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"pseudo.hasownpen?"
#define LOCALIZED_ALTERNATE_HEADING                L"pseudo.heading"
#define LOCALIZED_ALTERNATE_HELP                   L"pseudo.help"
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"pseudo.hideturtle"
#define LOCALIZED_ALTERNATE_HOME                   L"pseudo.home"
#define LOCALIZED_ALTERNATE_HT                     L"pseudo.ht"
#define LOCALIZED_ALTERNATE_IF                     L"pseudo.if"
#define LOCALIZED_ALTERNATE_IFELSE                 L"pseudo.ifelse"
#define LOCALIZED_ALTERNATE_IFF                    L"pseudo.iff"
#define LOCALIZED_ALTERNATE_IFFALSE                L"pseudo.iffalse"
#define LOCALIZED_ALTERNATE_IFT                    L"pseudo.ift"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"pseudo.iftrue"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"pseudo.ingameport"
#define LOCALIZED_ALTERNATE_INPORT                 L"pseudo.inport"
#define LOCALIZED_ALTERNATE_INPORTB                L"pseudo.inportb"
#define LOCALIZED_ALTERNATE_INT                    L"pseudo.int"
#define LOCALIZED_ALTERNATE_ITEM                   L"pseudo.item"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"pseudo.keyboardoff"
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"pseudo.keyboardon"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"pseudo.keyboardvalue"
#define LOCALIZED_ALTERNATE_KEYP                   L"pseudo.keyp"
#define LOCALIZED_ALTERNATE_KEY_                   L"pseudo.key?"
#define LOCALIZED_ALTERNATE_LABEL                  L"pseudo.label"
#define LOCALIZED_ALTERNATE_LABELFONT              L"pseudo.labelfont"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"pseudo.labelsize"
#define LOCALIZED_ALTERNATE_LAST                   L"pseudo.last"
#define LOCALIZED_ALTERNATE_LEFT                   L"pseudo.left"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"pseudo.leftroll"
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"pseudo.lessequalp"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"pseudo.lessequal?"
#define LOCALIZED_ALTERNATE_LESSP                  L"pseudo.lessp"
#define LOCALIZED_ALTERNATE_LESS_                  L"pseudo.less?"
#define LOCALIZED_ALTERNATE_LIGHT                  L"pseudo.light"
#define LOCALIZED_ALTERNATE_LIST                   L"pseudo.list"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"pseudo.listboxaddstring"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"pseudo.listboxcreate"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"pseudo.listboxenable"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"pseudo.listboxdelete"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"pseudo.listboxdeletestring"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"pseudo.listboxgetselect"
#define LOCALIZED_ALTERNATE_LISTP                  L"pseudo.listp"
#define LOCALIZED_ALTERNATE_LIST_                  L"pseudo.list?"
#define LOCALIZED_ALTERNATE_LN                     L"pseudo.ln"
#define LOCALIZED_ALTERNATE_LOAD                   L"pseudo.load"
#define LOCALIZED_ALTERNATE_LOCAL                  L"pseudo.local"
#define LOCALIZED_ALTERNATE_LOG10                  L"pseudo.log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"pseudo.logoversion"
#define LOCALIZED_ALTERNATE_LOWERCASE              L"pseudo.lowercase"
#define LOCALIZED_ALTERNATE_LPUT                   L"pseudo.lput"
#define LOCALIZED_ALTERNATE_LR                     L"pseudo.lr"
#define LOCALIZED_ALTERNATE_LSHIFT                 L"pseudo.lshift"
#define LOCALIZED_ALTERNATE_LT                     L"pseudo.lt"
#define LOCALIZED_ALTERNATE_MACHINE                L"pseudo.machine"
#define LOCALIZED_ALTERNATE_MACROP                 L"pseudo.macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 L"pseudo.macro?"
#define LOCALIZED_ALTERNATE_MAKE                   L"pseudo.Make"
#define LOCALIZED_ALTERNATE_MCI                    L"pseudo.mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"pseudo.member"
#define LOCALIZED_ALTERNATE_MEMBERP                L"pseudo.memberp"
#define LOCALIZED_ALTERNATE_MEMBER_                L"pseudo.member?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"pseudo.messagebox"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"pseudo.midiclose"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"pseudo.midimessage"
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"pseudo.midiopen"
#define LOCALIZED_ALTERNATE_MINUS                  L"pseudo.minus"
#define LOCALIZED_ALTERNATE_MKDIR                  L"pseudo.mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 L"pseudo.modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"pseudo.mouseoff"
#define LOCALIZED_ALTERNATE_MOUSEON                L"pseudo.mouseon"
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"pseudo.mousepos"
#define LOCALIZED_ALTERNATE_NAMEP                  L"pseudo.namep"
#define LOCALIZED_ALTERNATE_NAME_                  L"pseudo.name?"
#define LOCALIZED_ALTERNATE_NAMES                  L"pseudo.names"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"pseudo.netacceptoff"
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"pseudo.netaccepton"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"pseudo.netacceptreceivevalue"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"pseudo.netacceptsendvalue"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"pseudo.netconnectoff"
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"pseudo.netconnecton"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"pseudo.netconnectreceivevalue"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"pseudo.netconnectsendvalue"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"pseudo.netshutdown"
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"pseudo.netstartup"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"pseudo.nobitmapturtle"
#define LOCALIZED_ALTERNATE_NODES                  L"pseudo.nodes"
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"pseudo.nodribble"
#define LOCALIZED_ALTERNATE_NOSTATUS               L"pseudo.nostatus"
#define LOCALIZED_ALTERNATE_NOT                    L"pseudo.not"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"pseudo.notequalp"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"pseudo.notequal?"
#define LOCALIZED_ALTERNATE_NOYIELD                L"pseudo.noyield"
#define LOCALIZED_ALTERNATE_NUMBERP                L"pseudo.numberp"
#define LOCALIZED_ALTERNATE_NUMBER_                L"pseudo.number?"
#define LOCALIZED_ALTERNATE_OP                     L"pseudo.op"
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"pseudo.openappend"
#define LOCALIZED_ALTERNATE_OPENREAD               L"pseudo.openread"
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"pseudo.openupdate"
#define LOCALIZED_ALTERNATE_OPENWRITE              L"pseudo.openwrite"
#define LOCALIZED_ALTERNATE_OR                     L"pseudo.or"
#define LOCALIZED_ALTERNATE_OUTPORT                L"pseudo.outport"
#define LOCALIZED_ALTERNATE_OUTPORTB               L"pseudo.outportb"
#define LOCALIZED_ALTERNATE_OUTPUT                 L"pseudo.output"
#define LOCALIZED_ALTERNATE_PARSE                  L"pseudo.parse"
#define LOCALIZED_ALTERNATE_PAUSE                  L"pseudo.pause"
#define LOCALIZED_ALTERNATE_PC                     L"pseudo.pc"
#define LOCALIZED_ALTERNATE_PD                     L"pseudo.pd"
#define LOCALIZED_ALTERNATE_PE                     L"pseudo.pe"
#define LOCALIZED_ALTERNATE_PENCOLOR               L"pseudo.pencolor"
#define LOCALIZED_ALTERNATE_PENDOWN                L"pseudo.pendown"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"pseudo.pendownp"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"pseudo.pendown?"
#define LOCALIZED_ALTERNATE_PENERASE               L"pseudo.penerase"
#define LOCALIZED_ALTERNATE_PENMODE                L"pseudo.penmode"
#define LOCALIZED_ALTERNATE_PENPAINT               L"pseudo.penpaint"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"pseudo.penpattern"
#define LOCALIZED_ALTERNATE_PENREVERSE             L"pseudo.penreverse"
#define LOCALIZED_ALTERNATE_PENSIZE                L"pseudo.pensize"
#define LOCALIZED_ALTERNATE_PENUP                  L"pseudo.penup"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"pseudo.perspective"
#define LOCALIZED_ALTERNATE_PITCH                  L"pseudo.pitch"
#define LOCALIZED_ALTERNATE_PIXEL                  L"pseudo.pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"pseudo.playwave"
#define LOCALIZED_ALTERNATE_PLIST                  L"pseudo.Plist"
#define LOCALIZED_ALTERNATE_PLISTS                 L"pseudo.plists"
#define LOCALIZED_ALTERNATE_PO                     L"pseudo.po"
#define LOCALIZED_ALTERNATE_POPDIR                 L"pseudo.popdir"
#define LOCALIZED_ALTERNATE_POLYSTART              L"pseudo.polystart"
#define LOCALIZED_ALTERNATE_POLYEND                L"pseudo.polyend"
#define LOCALIZED_ALTERNATE_POLYVIEW               L"pseudo.polyview"
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"pseudo.portclose"
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"pseudo.portflush"
#define LOCALIZED_ALTERNATE_PORTMODE               L"pseudo.portmode"
#define LOCALIZED_ALTERNATE_PORTOPEN               L"pseudo.portopen"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"pseudo.portreadarray"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"pseudo.portreadchar"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"pseudo.portwritearray"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"pseudo.portwritechar"
#define LOCALIZED_ALTERNATE_POS                    L"pseudo.pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 L"pseudo.posxyz"
#define LOCALIZED_ALTERNATE_POT                    L"pseudo.pot"
#define LOCALIZED_ALTERNATE_POWER                  L"pseudo.power"
#define LOCALIZED_ALTERNATE_PPROP                  L"pseudo.Pprop"
#define LOCALIZED_ALTERNATE_PPT                    L"pseudo.ppt"
#define LOCALIZED_ALTERNATE_PR                     L"pseudo.pr"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"pseudo.primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"pseudo.primitive?"
#define LOCALIZED_ALTERNATE_PRINT                  L"pseudo.print"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"pseudo.procedurep"
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"pseudo.procedure?"
#define LOCALIZED_ALTERNATE_PROPLISTP              L"pseudo.proplistp"
#define LOCALIZED_ALTERNATE_PROPLIST_              L"pseudo.proplist?"
#define LOCALIZED_ALTERNATE_PROCEDURES             L"pseudo.procedures"
#define LOCALIZED_ALTERNATE_PRODUCT                L"pseudo.product"
#define LOCALIZED_ALTERNATE_PU                     L"pseudo.pu"
#define LOCALIZED_ALTERNATE_PX                     L"pseudo.px"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"pseudo.questionbox"
#define LOCALIZED_ALTERNATE_QUOTIENT               L"pseudo.quotient"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"pseudo.radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"pseudo.radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"pseudo.radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 L"pseudo.radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"pseudo.radiobuttoncreate"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"pseudo.radiobuttonenable"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"pseudo.radiobuttondelete"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"pseudo.radiobuttonget"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"pseudo.radiobuttonset"
#define LOCALIZED_ALTERNATE_RADSIN                 L"pseudo.radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 L"pseudo.radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 L"pseudo.random"
#define LOCALIZED_ALTERNATE_RAWASCII               L"pseudo.rawascii"
#define LOCALIZED_ALTERNATE_RC                     L"pseudo.rc"
#define LOCALIZED_ALTERNATE_RCS                    L"pseudo.rcs"
#define LOCALIZED_ALTERNATE_READCHAR               L"pseudo.readchar"
#define LOCALIZED_ALTERNATE_READCHARS              L"pseudo.readchars"
#define LOCALIZED_ALTERNATE_READER                 L"pseudo.reader"
#define LOCALIZED_ALTERNATE_READLIST               L"pseudo.readlist"
#define LOCALIZED_ALTERNATE_READPOS                L"pseudo.readpos"
#define LOCALIZED_ALTERNATE_READRAWLINE            L"pseudo.readrawline"
#define LOCALIZED_ALTERNATE_READWORD               L"pseudo.readword"
#define LOCALIZED_ALTERNATE_REMAINDER              L"pseudo.remainder"
#define LOCALIZED_ALTERNATE_REMPROP                L"pseudo.remprop"
#define LOCALIZED_ALTERNATE_REPCOUNT               L"pseudo.repcount"
#define LOCALIZED_ALTERNATE_REPEAT                 L"pseudo.repeat"
#define LOCALIZED_ALTERNATE_RERANDOM               L"pseudo.rerandom"
#define LOCALIZED_ALTERNATE_RIGHT                  L"pseudo.right"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"pseudo.rightroll"
#define LOCALIZED_ALTERNATE_RL                     L"pseudo.rl"
#define LOCALIZED_ALTERNATE_RMDIR                  L"pseudo.rmdir"
#define LOCALIZED_ALTERNATE_ROLL                   L"pseudo.roll"
#define LOCALIZED_ALTERNATE_ROUND                  L"pseudo.round"
#define LOCALIZED_ALTERNATE_RR                     L"pseudo.rr"
#define LOCALIZED_ALTERNATE_RT                     L"pseudo.rt"
#define LOCALIZED_ALTERNATE_RUN                    L"pseudo.run"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"pseudo.runparse"
#define LOCALIZED_ALTERNATE_RUNRESULT              L"pseudo.runresult"
#define LOCALIZED_ALTERNATE_RW                     L"pseudo.rw"
#define LOCALIZED_ALTERNATE_SAVE                   L"pseudo.save"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"pseudo.screencolor"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"pseudo.scrollbarcreate"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"pseudo.scrollbarenable"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"pseudo.scrollbardelete"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"pseudo.scrollbarget"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"pseudo.scrollbarset"
#define LOCALIZED_ALTERNATE_SCROLLX                L"pseudo.scrollx"
#define LOCALIZED_ALTERNATE_SCROLLY                L"pseudo.scrolly"
#define LOCALIZED_ALTERNATE_SCRUNCH                L"pseudo.scrunch"
#define LOCALIZED_ALTERNATE_SE                     L"pseudo.se"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"pseudo.selectbox"
#define LOCALIZED_ALTERNATE_SENTENCE               L"pseudo.sentence"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"pseudo.setactivearea"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"pseudo.setbitindex"
#define LOCALIZED_ALTERNATE_SETBITMODE             L"pseudo.setbitmode"
#define LOCALIZED_ALTERNATE_SETCLIP                L"pseudo.setclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              L"pseudo.setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"pseudo.setcursornowait"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"pseudo.setcursorwait"
#define LOCALIZED_ALTERNATE_SETFC                  L"pseudo.setfc"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"pseudo.setfloodcolor"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"pseudo.setfocus"
#define LOCALIZED_ALTERNATE_SETH                   L"pseudo.seth"
#define LOCALIZED_ALTERNATE_SETHEADING             L"pseudo.setheading"
#define LOCALIZED_ALTERNATE_SETITEM                L"pseudo.setitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"pseudo.setlabelfont"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"pseudo.setlight"
#define LOCALIZED_ALTERNATE_SETMARGINS             L"pseudo.setmargins"
#define LOCALIZED_ALTERNATE_SETPC                  L"pseudo.setpc"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"pseudo.setpencolor"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"pseudo.setpenpattern"
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"pseudo.setpensize"
#define LOCALIZED_ALTERNATE_SETPITCH               L"pseudo.setpitch"
#define LOCALIZED_ALTERNATE_SETPIXEL               L"pseudo.setpixel"
#define LOCALIZED_ALTERNATE_SETPOS                 L"pseudo.setpos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"pseudo.setposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                L"pseudo.setread"
#define LOCALIZED_ALTERNATE_SETREADPOS             L"pseudo.setreadpos"
#define LOCALIZED_ALTERNATE_SETROLL                L"pseudo.setroll"
#define LOCALIZED_ALTERNATE_SETSC                  L"pseudo.setsc"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"pseudo.setscreencolor"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"pseudo.setscrunch"
#define LOCALIZED_ALTERNATE_SETTIMER               L"pseudo.settimer"
#define LOCALIZED_ALTERNATE_SETTURTLE              L"pseudo.setturtle"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"pseudo.setturtlemode"
#define LOCALIZED_ALTERNATE_SETWRITE               L"pseudo.setwrite"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"pseudo.setwritepos"
#define LOCALIZED_ALTERNATE_SETX                   L"pseudo.setx"
#define LOCALIZED_ALTERNATE_SETXY                  L"pseudo.setxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"pseudo.setxyz"
#define LOCALIZED_ALTERNATE_SETY                   L"pseudo.sety"
#define LOCALIZED_ALTERNATE_SETZ                   L"pseudo.setz"
#define LOCALIZED_ALTERNATE_SHELL                  L"pseudo.shell"
#define LOCALIZED_ALTERNATE_SHOW                   L"pseudo.show"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"pseudo.shownp"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"pseudo.shown?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"pseudo.showturtle"
#define LOCALIZED_ALTERNATE_SIN                    L"pseudo.sin"
#define LOCALIZED_ALTERNATE_SOUND                  L"pseudo.sound"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"pseudo.splitscreen"
#define LOCALIZED_ALTERNATE_SQRT                   L"pseudo.sqrt"
#define LOCALIZED_ALTERNATE_SS                     L"pseudo.ss"
#define LOCALIZED_ALTERNATE_ST                     L"pseudo.st"
#define LOCALIZED_ALTERNATE_STANDOUT               L"pseudo.standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           L"pseudo.staticcreate"
#define LOCALIZED_ALTERNATE_STATICDELETE           L"pseudo.staticdelete"
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"pseudo.staticupdate"
#define LOCALIZED_ALTERNATE_STATUS                 L"pseudo.status"
#define LOCALIZED_ALTERNATE_STEP                   L"pseudo.step"
#define LOCALIZED_ALTERNATE_STEPPED                L"pseudo.stepped"
#define LOCALIZED_ALTERNATE_STOP                   L"pseudo.stop"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"pseudo.substringp"
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"pseudo.substring?"
#define LOCALIZED_ALTERNATE_SUM                    L"pseudo.sum"
#define LOCALIZED_ALTERNATE_TAG                    L"pseudo.tag"
#define LOCALIZED_ALTERNATE_TAN                    L"pseudo.tan"
#define LOCALIZED_ALTERNATE_TEST                   L"pseudo.test"
#define LOCALIZED_ALTERNATE_TEXT                   L"pseudo.text"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"pseudo.textscreen"
#define LOCALIZED_ALTERNATE_THING                  L"pseudo.thing"
#define LOCALIZED_ALTERNATE_THROW                  L"pseudo.throw"
#define LOCALIZED_ALTERNATE_TIME                   L"pseudo.time"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"pseudo.timemilli"
#define LOCALIZED_ALTERNATE_TO                     L"pseudo.to"
#define LOCALIZED_ALTERNATE_TONE                   L"pseudo.tone"
#define LOCALIZED_ALTERNATE_TOWARDS                L"pseudo.towards"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"pseudo.towardsxyz"
#define LOCALIZED_ALTERNATE_TRACE                  L"pseudo.trace"
#define LOCALIZED_ALTERNATE_TRACED                 L"pseudo.traced"
#define LOCALIZED_ALTERNATE_TS                     L"pseudo.ts"
#define LOCALIZED_ALTERNATE_TURTLE                 L"pseudo.turtle"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"pseudo.turtlemode"
#define LOCALIZED_ALTERNATE_TURTLES                L"pseudo.turtles"
#define LOCALIZED_ALTERNATE_TYPE                   L"pseudo.type"
#define LOCALIZED_ALTERNATE_UNBURY                 L"pseudo.unbury"
#define LOCALIZED_ALTERNATE_UNSTEP                 L"pseudo.unstep"
#define LOCALIZED_ALTERNATE_UNTRACE                L"pseudo.untrace"
#define LOCALIZED_ALTERNATE_UP                     L"pseudo.up"
#define LOCALIZED_ALTERNATE_UPPERCASE              L"pseudo.uppercase"
#define LOCALIZED_ALTERNATE_UPPITCH                L"pseudo.uppitch"
#define LOCALIZED_ALTERNATE_WAIT                   L"pseudo.wait"
#define LOCALIZED_ALTERNATE_WINDOW                 L"pseudo.window"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"pseudo.windowcreate"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"pseudo.windowenable"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"pseudo.windowdelete"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"pseudo.windowfileedit"
#define LOCALIZED_ALTERNATE_WINDOWSET              L"pseudo.windowset"
#define LOCALIZED_ALTERNATE_WINHELP                L"pseudo.winhelp"
#define LOCALIZED_ALTERNATE_WORD                   L"pseudo.word"
#define LOCALIZED_ALTERNATE_WORDP                  L"pseudo.wordp"
#define LOCALIZED_ALTERNATE_WORD_                  L"pseudo.word?"
#define LOCALIZED_ALTERNATE_WRAP                   L"pseudo.wrap"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"pseudo.writepos"
#define LOCALIZED_ALTERNATE_WRITER                 L"pseudo.writer"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"pseudo.yesnobox"
#define LOCALIZED_ALTERNATE_YIELD                  L"pseudo.yield"
#define LOCALIZED_ALTERNATE_ZOOM                   L"pseudo.zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"pseudo.OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"pseudo.Cancel"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"pseudo.&Apply"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"pseudo.FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"pseudo.The FMSLogo programming environment"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"pseudo.&File"
#define LOCALIZED_FILE_NEW              L"pseudo.&New\t(erase workspace)"
#define LOCALIZED_FILE_LOAD             L"pseudo.&Load...\t(merge into workspace)"
#define LOCALIZED_FILE_OPEN             L"pseudo.&Open...\t(replace workspace)" 
#define LOCALIZED_FILE_SAVE             L"pseudo.&Save" 
#define LOCALIZED_FILE_SAVEAS           L"pseudo.Save &As..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"pseudo.Se&t As Screen Saver"
#define LOCALIZED_FILE_EDIT             L"pseudo.&Edit..."
#define LOCALIZED_FILE_ERASE            L"pseudo.E&rase..."
#define LOCALIZED_FILE_EXIT             L"pseudo.E&xit"

#define LOCALIZED_BITMAP               L"pseudo.&Bitmap"
#define LOCALIZED_BITMAP_NEW           L"pseudo.&New"
#define LOCALIZED_BITMAP_LOAD          L"pseudo.&Load..."
#define LOCALIZED_BITMAP_SAVE          L"pseudo.&Save"
#define LOCALIZED_BITMAP_SAVEAS        L"pseudo.Save &As..."
#define LOCALIZED_BITMAP_PRINT         L"pseudo.&Print..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"pseudo.P&rinter Setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"pseudo.A&ctive Area..."

#define LOCALIZED_SET                  L"pseudo.&Set"
#define LOCALIZED_SET_PENSIZE          L"pseudo.Pen Si&ze..."
#define LOCALIZED_SET_LABELFONT        L"pseudo.&Label Font..."
#define LOCALIZED_SET_COMMANDERFONT    L"pseudo.&Commander Font..."
#define LOCALIZED_SET_PENCOLOR         L"pseudo.&Pen Color..."
#define LOCALIZED_SET_FLOODCOLOR       L"pseudo.F&lood Color..."
#define LOCALIZED_SET_SCREENCOLOR      L"pseudo.&Screen Color..."

#define LOCALIZED_ZOOM                 L"pseudo.&Zoom" 
#define LOCALIZED_ZOOM_IN              L"pseudo.&In"
#define LOCALIZED_ZOOM_OUT             L"pseudo.&Out"
#define LOCALIZED_ZOOM_NORMAL          L"pseudo.&Normal"

#define LOCALIZED_HELP                 L"pseudo.&Help" 
#define LOCALIZED_HELP_INDEX           L"pseudo.&Index"
#define LOCALIZED_HELP_TUTORIAL        L"pseudo.&Tutorial"
#define LOCALIZED_HELP_DEMO            L"pseudo.&Demo" 
#define LOCALIZED_HELP_EXAMPLE         L"pseudo.&Examples"
#define LOCALIZED_HELP_RELEASENOTES    L"pseudo.&Release Notes"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"pseudo.&About "LOCALIZED_GENERAL_PRODUCTNAME"..."
#define LOCALIZED_HELP_MS              L"pseudo.&About MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"pseudo.LANGUAGE to English"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"pseudo.English to LANGUAGE"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"pseudo.Select Active Area"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"pseudo.These affect Printing and Saving Bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"pseudo.Y-High"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"pseudo.Y-Low" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"pseudo.X-High"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"pseudo.X-Low"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"pseudo.Turtle steps per inch printed:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"pseudo.&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"pseudo.FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"pseudo.FMSLogo Screensaver Settings"
#define LOCALIZED_SCREENSAVER_LOCATE            L"pseudo.&Locate ..." 
#define LOCALIZED_SCREENSAVER_FILE              L"pseudo.Logo &File:" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"pseudo.Select a " LOCALIZED_ALTERNATE_STARTUP " instruction"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"pseudo.Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"pseudo.The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"pseudo.Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"pseudo.No procedures are defined"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"pseudo.There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"pseudo.Copy"
#define LOCALIZED_POPUP_CUT                      L"pseudo.Cut"
#define LOCALIZED_POPUP_PASTE                    L"pseudo.Paste"
#define LOCALIZED_POPUP_DELETE                   L"pseudo.Delete"
#define LOCALIZED_POPUP_UNDO                     L"pseudo.Undo"
#define LOCALIZED_POPUP_REDO                     L"pseudo.Redo"
#define LOCALIZED_POPUP_SELECTALL                L"pseudo.Select All"
#define LOCALIZED_POPUP_HELP                     L"pseudo.Topic Search"
#define LOCALIZED_POPUP_REMOVELINES              L"pseudo.Remove Selected Lines"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"pseudo.Editor"

#define LOCALIZED_EDITOR_FILE                    L"pseudo.&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"pseudo.&Save and Exit\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"pseudo.Save to &Workspace"
#define LOCALIZED_EDITOR_FILE_PRINT              L"pseudo.&Print..." 
#define LOCALIZED_EDITOR_FILE_EXIT               L"pseudo.E&xit" 

#define LOCALIZED_EDITOR_EDIT                    L"pseudo.&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"pseudo.&Undo\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"pseudo.&Redo\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"pseudo.&Cut\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"pseudo.C&opy\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"pseudo.&Paste\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"pseudo.&Delete\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"pseudo.C&lear All\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"pseudo.S&elect All\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"pseudo.&Search"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"pseudo.&Find...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"pseudo.&Replace...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"pseudo.&Next\tF3" 

#define LOCALIZED_EDITOR_SET                     L"pseudo.Se&t" 
#define LOCALIZED_EDITOR_SET_FONT                L"pseudo.&Font..." 

#define LOCALIZED_EDITOR_TEST                    L"pseudo.Test"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"pseudo.&Run Selection\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    L"pseudo.&Help" 
#define LOCALIZED_EDITOR_HELP_INDEX              L"pseudo.&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"pseudo.&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"pseudo.&Topic Search\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"pseudo.&Save and Exit"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"pseudo.&Don't Save"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"pseudo.There are unsaved changes in the workspace.  If you exit without saving, these changes will be lost.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"pseudo.Would you like to save your changes before exiting?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"pseudo.Commander"
#define LOCALIZED_COMMANDER_HALT                L"pseudo.Halt"
#define LOCALIZED_COMMANDER_TRACE               L"pseudo.Trace"
#define LOCALIZED_COMMANDER_NOTRACE             L"pseudo.NoTrace"
#define LOCALIZED_COMMANDER_PAUSE               L"pseudo.Pause"
#define LOCALIZED_COMMANDER_STATUS              L"pseudo.Status"
#define LOCALIZED_COMMANDER_NOSTATUS            L"pseudo.NoStatus"
#define LOCALIZED_COMMANDER_STEP                L"pseudo.Step"
#define LOCALIZED_COMMANDER_UNSTEP              L"pseudo.UnStep"
#define LOCALIZED_COMMANDER_RESET               L"pseudo.Reset"
#define LOCALIZED_COMMANDER_EXECUTE             L"pseudo.Execute"
#define LOCALIZED_COMMANDER_EDALL               L"pseudo.Edall"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"pseudo.Status"
#define LOCALIZED_STATUS_PEN                    L"pseudo.Pen"
#define LOCALIZED_STATUS_CONTACT                L"pseudo.Contact:"
#define LOCALIZED_STATUS_WIDTH                  L"pseudo.Width:"
#define LOCALIZED_STATUS_STYLE                  L"pseudo.Style:"
#define LOCALIZED_STATUS_ORIENTATION            L"pseudo.Orientation"
#define LOCALIZED_STATUS_PITCH                  L"pseudo.Pitch:"
#define LOCALIZED_STATUS_HEADING                L"pseudo.Heading:"
#define LOCALIZED_STATUS_ROLL                   L"pseudo.Roll:"
#define LOCALIZED_STATUS_TURTLE                 L"pseudo.Turtle"
#define LOCALIZED_STATUS_POSITION               L"pseudo.Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"pseudo.Which:"
#define LOCALIZED_STATUS_VISIBILITY             L"pseudo.Visibility:"
#define LOCALIZED_STATUS_COLOR                  L"pseudo.Color"
#define LOCALIZED_STATUS_PENCOLOR               L"pseudo.Pen(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"pseudo.Flood(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"pseudo.Screen(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"pseudo.Kernel"
#define LOCALIZED_STATUS_CALLS                  L"pseudo.Calls:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"pseudo.Peak Memory:"

#define LOCALIZED_STATUS_PENREVERSE     L"pseudo.Reverse"
#define LOCALIZED_STATUS_PENNORMAL      L"pseudo.Normal"
#define LOCALIZED_STATUS_PENERASE       L"pseudo.Erase"
#define LOCALIZED_STATUS_PENUP          L"pseudo.Up"
#define LOCALIZED_STATUS_PENDOWN        L"pseudo.Down"
#define LOCALIZED_STATUS_PENSHOWN       L"pseudo.Shown"
#define LOCALIZED_STATUS_PENHIDDEN      L"pseudo.Hidden"
#define LOCALIZED_STATUS_POLYGONS       L"pseudo.Polygons"
#define LOCALIZED_STATUS_VECTORS        L"pseudo.Vectors"
#define LOCALIZED_STATUS_NODES          L"pseudo.Nodes"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"pseudo.N/A"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"pseudo.&All"
#define LOCALIZED_ERASEPROCEDURE                L"pseudo.Erase Procedure"
#define LOCALIZED_EDITPROCEDURE                 L"pseudo.Edit Procedure"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"pseudo.Set Color"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"pseudo.Pen Color"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"pseudo.Flood Color"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"pseudo.Screen Color"
#define LOCALIZED_SETCOLOR_RED                 L"pseudo.Red"
#define LOCALIZED_SETCOLOR_GREEN               L"pseudo.Green"
#define LOCALIZED_SETCOLOR_BLUE                L"pseudo.Blue"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"pseudo.Pen Size"
#define LOCALIZED_SETPENSIZE_SIZE              L"pseudo.Thickness"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"pseudo.About "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"pseudo.Version"
#define LOCALIZED_ABOUTFMS_GUI                 L"pseudo.GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"pseudo.Core by Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"pseudo.Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"pseudo.The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"pseudo.Special thanks to Yehuda Katz and Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"pseudo.Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"pseudo.To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc."
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"pseudo.About FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"pseudo.FMS stands for Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"pseudo.Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"pseudo.Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"pseudo.An Edit session is running"

#define LOCALIZED_COULDNOTWRITEBMP            L"pseudo.Could not write .bmp"
#define LOCALIZED_COULDNOTOPENBMP             L"pseudo.Could not open .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           L"pseudo.Unable to create Windows 3.0 bitmap"
#define LOCALIZED_NOTVALIDBMP                 L"pseudo.Not a Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"pseudo.You have not saved to disk"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"pseudo.Executing a new will erase all definitions.\n\nContinue with New?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"pseudo.The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"pseudo.This will erase all of your unsaved changes.\n\nContinue with Open?"

#define LOCALIZED_EDITORISOPEN                  L"pseudo.Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved."

#define LOCALIZED_ERROR_CANTREADFILE            L"pseudo.Unable to read file \"%s\" from disk"
#define LOCALIZED_ERROR_CANTWRITEFILE           L"pseudo.Unable to write file \"%s\" to disk"

#define LOCALIZED_SAVETOWORKSPACE                L"pseudo.Save to Workspace"
#define LOCALIZED_CONTENTSCHANGED                L"pseudo.Contents Changed"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"pseudo.The contents have changed.\nWould you like to save the changes to the workspace?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"pseudo.There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message."
#define LOCALIZED_RETURNTOEDIT                  L"pseudo.Return to the editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              L"pseudo.Error in File"
#define LOCALIZED_ERRORINFILEMESSAGE            L"pseudo.There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?"

#define LOCALIZED_CANNOTALLOCATESCREEN          L"pseudo.Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue."


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"pseudo.Select the Logo program to load (merge into workspace)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"pseudo.Select the Logo program to open (replace the workspace with)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"pseudo.Select the file to which the workspace will be saved"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"pseudo.Select the image to load"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"pseudo.Select the file to which the active area will be saved"

#define LOCALIZED_LOGO_FILE_EXTENSION L"pseudo.lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"pseudo.All Files (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"pseudo.Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"pseudo.Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" pseudo.stops\n"
#define LOCALIZED_TRACING_OUTPUTS           L" pseudo.outputs %s\n"
#define LOCALIZED_TRACING_MAKE              L"pseudo.Make %s %s"
#define LOCALIZED_TRACING_PPROP             L"pseudo.Pprop %s %s %s"
#define LOCALIZED_TRACING_LOCATION          L" pseudo.in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"pseudo.Single Step"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"pseudo.%s defined\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"pseudo.erase"
#define LOCALIZED_PENMODE_REVERSE  L"pseudo.reverse"
#define LOCALIZED_PENMODE_PAINT    L"pseudo.paint"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"pseudo.Logo: Fatal Internal Error"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"pseudo.Logo: Out of memory"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"pseudo.Out of memory"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"pseudo.stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"pseudo.turtle out of bounds"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"pseudo.couldn't initialize graphics"
#define LOCALIZED_ERROR_BADDATA                L"pseudo.%p doesn't like %s as input"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"pseudo.%p didn't output to %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"pseudo.not enough inputs to %p"
#define LOCALIZED_ERROR_TOOMUCH                L"pseudo.too much inside ()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"pseudo.You don't say what to do with %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"pseudo.too many ('s"
#define LOCALIZED_ERROR_NOVALUE                L"pseudo.%s has no value"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"pseudo.unexpected ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"pseudo.unexpected ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"pseudo.unexpected '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"pseudo.I don't know how to %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"pseudo.Can't find catch tag for %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"pseudo.%p is already defined"
#define LOCALIZED_ERROR_STOPPING               L"pseudo.Stopping..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"pseudo.Already dribbling"
#define LOCALIZED_ERROR_FILESYSTEM                   L"pseudo.File system error: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"pseudo.Could not open file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"pseudo.Unable to open file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"pseudo.File already open"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"pseudo.File not open"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"pseudo.Could not create editor file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"pseudo.Could not launch the editor" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"pseudo.Could not read editor file" 
#define LOCALIZED_ERROR_IFWARNING              L"pseudo.Assuming you mean IFELSE, not IF"
#define LOCALIZED_ERROR_SHADOWWARNING          L"pseudo.%p shadowed by local in procedure call"
#define LOCALIZED_ERROR_USER                   L"pseudo.Throw \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"pseudo.%p is a primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            L"pseudo.Can't use TO inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"pseudo.Can only use %p inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"pseudo.You must be in a procedure to use OUTPUT or STOP"
#define LOCALIZED_ERROR_NOTEST                 L"pseudo.%p without TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"pseudo.Macro output %s instead of a list"
#define LOCALIZED_ERROR_DEEPEND                L"pseudo.END inside multi-line instruction"
#define LOCALIZED_ERROR_DEEPENDIN              L"pseudo.END inside multi-line instruction in %p"
#define LOCALIZED_ERROR_UNKNOWN                L"pseudo.Unknown error condition - internal error."
#define LOCALIZED_PAUSING                      L"pseudo.Pausing..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"pseudo.Invalid state for instruction: %p"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"pseudo.cannot set the mode of a turtle with a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"pseudo.cannot make a special turtle use a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"pseudo.cannot use the clipboard as a rotating bitmap"
#define LOCALIZED_ERROR_SPECIALFORM                L"pseudo.%p doesn't like %p as input because it has a special form"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"pseudo.Error"
#define LOCALIZED_ERROR_BADINPUT             L"pseudo.Bad input"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"pseudo.Input is not paired"

#define LOCALIZED_ERROR_CANTOPENPORT         L"pseudo.Could not open port"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"pseudo.Could not close port"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"pseudo.Could not flush port"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"pseudo.Could not build dcb on port"
#define LOCALIZED_ERROR_CANTSETPORT          L"pseudo.Could not set port"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"pseudo.Port is already open"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"pseudo.Port is not open"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"pseudo.%s already exists"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"pseudo.%s does not exist"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"pseudo.DLL is not loaded"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"pseudo.DLL load failed"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"pseudo.Invalid data type input"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"pseudo.Invalid output type"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"pseudo.Function not found"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"pseudo.Not all Type/Data inputs are paired"

#define LOCALIZED_ERROR_NETWORK               L"pseudo.Network Error"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"pseudo.Network Receive Error"
#define LOCALIZED_ERROR_NETWORKSEND           L"pseudo.Network Send Error"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"pseudo.Unexpected Error, Network may be shutdown"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"pseudo.Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"pseudo.Already started"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"pseudo.Already on"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"pseudo.Already off"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"pseudo.Name too long"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"pseudo.Not initialized"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"pseudo.System not ready"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"pseudo.Version is not supported"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"pseudo.Can't send after socket shutdown"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"pseudo.Interrupted system call"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"pseudo.Authoritative Answer: Host not found"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"pseudo.Non-Authoritative: Host not found. See NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"pseudo.Non-recoverable error"
#define LOCALIZED_ERROR_NETWORKNODATA              L"pseudo.No data record available"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"pseudo.Bad file number"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"pseudo.Operation would block"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"pseudo.Operation now in progress"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"pseudo.Operation already in progress"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"pseudo.Bad address"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"pseudo.Destination address required"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"pseudo.Message too long"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"pseudo.Protocol family not supported"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"pseudo.Directory not empty"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"pseudo.Application limit has been reached"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"pseudo.Disk quota exceeded"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"pseudo.Too many open files"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"pseudo.Access denied"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"pseudo.Socket operation on non-socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"pseudo.Can't assign requested address"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"pseudo.Address already in use"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"pseudo.Address family not supported by protocol family"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"pseudo.Connection timed out"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"pseudo.Socket type not supported"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"pseudo.Protocol not supported"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"pseudo.No space in buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"pseudo.Socket is already connected"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"pseudo.Socket is not connected"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"pseudo.Bad protocol option"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"pseudo.Connection reset by peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"pseudo.Software caused connection abort"
#define LOCALIZED_ERROR_NETWORKISDOWN              L"pseudo.Network is down"
#define LOCALIZED_ERROR_NETWORKRESET               L"pseudo.Network was reset"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"pseudo.Connection refused"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"pseudo.Host is down"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"pseudo.Host is unreachable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"pseudo.Protocol is wrong type for socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"pseudo.Operation not supported on socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"pseudo.No path to remote host was found"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"pseudo.Too many references"

#define LOCALIZED_ERROR_POLYSTART               L"pseudo.PolyStart Error"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"pseudo.You already have a Polygon started"

#define LOCALIZED_ERROR_POLYEND                 L"pseudo.PolyEnd Error"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"pseudo.You have not started a Polygon"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"pseudo.You must have at least 3 vectors to define a polygon"

#define LOCALIZED_ERROR_SOUND                 L"pseudo.Sound Error"

#define LOCALIZED_ERROR_MIDI                  L"pseudo.MIDI Error"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"pseudo.Invalid MIDI device"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"pseudo.Already open"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"pseudo.Not open"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"pseudo.No Text in Clipboard"

#define LOCALIZED_ERROR_MCI                   L"pseudo.MCI Error"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"pseudo.Timer not found"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"pseudo.Online help is unavailable because hhctrl.ocx could not be loaded." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"pseudo.Invalid Command Line" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"pseudo.The environment variable TMP is not defined or invalid.\n"LOCALIZED_GENERAL_PRODUCTNAME" will attempt to use C:\\ for storing temporary files"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"pseudo.Problem Generating GIF, check memory and diskspace"
#define LOCALIZED_ERROR_GIFREADFAILED         L"pseudo.Problem Reading GIF, check memory and diskspace"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"pseudo.BitMap Index out of range"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"pseudo.Cut failed, Possibly not enough Memory"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"pseudo.Nothing to Paste" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"pseudo.BitMap at Index must be initialized with a bitmap" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"pseudo.Turtle %d has no picture, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"pseudo.Sorry, no font named %s was found.  Choose one of the following:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"pseudo.Print driver does not support this function" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"pseudo.Cannot draw image"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"pseudo.Cannot extract image"
#define LOCALIZED_ERROR_SUBCODE                 L"pseudo.Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"pseudo.Input:"
#define LOCALIZED_PROMPT_TO     L"pseudo.To Mode (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   L"pseudo.List Mode (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  L"pseudo.Pause Mode (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  L"pseudo.Input Mode (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"pseudo.Changed to \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"pseudo.Could not chdir to directory \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"pseudo.Popped to \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"pseudo.Now in newly created directory \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         L"pseudo.Failed to create directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"pseudo.Removed directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         L"pseudo.Failed to remove directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"pseudo.The directory does not exist."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"pseudo.Make sure the directory is empty before trying to remove it."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"pseudo.Logo Picture"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"pseudo.Active Area"
#define LOCALIZED_INFORMATION   L"pseudo.Information"
#define LOCALIZED_WARNING       L"pseudo.Warning"
#define LOCALIZED_UNTITLED      L"pseudo.Untitled"
#define LOCALIZED_UNKNOWN       L"pseudo.Unknown"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"pseudo.nothing"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"pseudo.Find"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"pseudo.Replace" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"pseudo.Cannot find %s"


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
#define LOCALIZED_COLOR_ALICEBLUE             L"pseudo.AliceBlue"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"pseudo.AntiqueWhite"
#define LOCALIZED_COLOR_AQUA                  L"pseudo.Aqua"
#define LOCALIZED_COLOR_AQUAMARINE            L"pseudo.Aquamarine"
#define LOCALIZED_COLOR_AZURE                 L"pseudo.Azure"
#define LOCALIZED_COLOR_BEIGE                 L"pseudo.Beige"
#define LOCALIZED_COLOR_BISQUE                L"pseudo.Bisque"
#define LOCALIZED_COLOR_BLACK                 L"pseudo.Black"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"pseudo.BlanchedAlmond"
#define LOCALIZED_COLOR_BLUE                  L"pseudo.Blue"
#define LOCALIZED_COLOR_BLUEVIOLET            L"pseudo.BlueViolet"
#define LOCALIZED_COLOR_BROWN                 L"pseudo.Brown"
#define LOCALIZED_COLOR_BURLYWOOD             L"pseudo.BurlyWood"
#define LOCALIZED_COLOR_CADETBLUE             L"pseudo.CadetBlue"
#define LOCALIZED_COLOR_CHARTREUSE            L"pseudo.Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             L"pseudo.Chocolate"
#define LOCALIZED_COLOR_CORAL                 L"pseudo.Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"pseudo.CornflowerBlue"
#define LOCALIZED_COLOR_CORNSILK              L"pseudo.Cornsilk"
#define LOCALIZED_COLOR_CRIMSON               L"pseudo.Crimson"
#define LOCALIZED_COLOR_CYAN                  L"pseudo.Cyan"
#define LOCALIZED_COLOR_DARKBLUE              L"pseudo.DarkBlue"
#define LOCALIZED_COLOR_DARKCYAN              L"pseudo.DarkCyan"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"pseudo.DarkGoldenRod"
#define LOCALIZED_COLOR_DARKGRAY              L"pseudo.DarkGray"
#define LOCALIZED_COLOR_DARKGREEN             L"pseudo.DarkGreen"
#define LOCALIZED_COLOR_DARKGREY              L"pseudo.DarkGrey"
#define LOCALIZED_COLOR_DARKKHAKI             L"pseudo.DarkKhaki"
#define LOCALIZED_COLOR_DARKMAGENTA           L"pseudo.DarkMagenta"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"pseudo.DarkOliveGreen"
#define LOCALIZED_COLOR_DARKORANGE            L"pseudo.DarkOrange"
#define LOCALIZED_COLOR_DARKORCHID            L"pseudo.DarkOrchid"
#define LOCALIZED_COLOR_DARKRED               L"pseudo.DarkRed"
#define LOCALIZED_COLOR_DARKSALMON            L"pseudo.DarkSalmon"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"pseudo.DarkSeaGreen"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"pseudo.DarkSlateBlue"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"pseudo.DarkSlateGray"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"pseudo.DarkSlateGrey"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"pseudo.DarkTurquoise"
#define LOCALIZED_COLOR_DARKVIOLET            L"pseudo.DarkViolet"
#define LOCALIZED_COLOR_DEEPPINK              L"pseudo.DeepPink"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"pseudo.DeepSkyBlue"
#define LOCALIZED_COLOR_DIMGRAY               L"pseudo.DimGray"
#define LOCALIZED_COLOR_DIMGREY               L"pseudo.DimGrey"
#define LOCALIZED_COLOR_DODGERBLUE            L"pseudo.DodgerBlue"
#define LOCALIZED_COLOR_FIREBRICK             L"pseudo.FireBrick"
#define LOCALIZED_COLOR_FLORALWHITE           L"pseudo.FloralWhite"
#define LOCALIZED_COLOR_FORESTGREEN           L"pseudo.ForestGreen"
#define LOCALIZED_COLOR_FUCHSIA               L"pseudo.Fuchsia"
#define LOCALIZED_COLOR_GAINSBORO             L"pseudo.Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            L"pseudo.GhostWhite"
#define LOCALIZED_COLOR_GOLD                  L"pseudo.Gold"
#define LOCALIZED_COLOR_GOLDENROD             L"pseudo.GoldenRod"
#define LOCALIZED_COLOR_GRAY                  L"pseudo.Gray"
#define LOCALIZED_COLOR_GREEN                 L"pseudo.Green"
#define LOCALIZED_COLOR_GREENYELLOW           L"pseudo.GreenYellow"
#define LOCALIZED_COLOR_GREY                  L"pseudo.Grey"
#define LOCALIZED_COLOR_HONEYDEW              L"pseudo.HoneyDew"
#define LOCALIZED_COLOR_HOTPINK               L"pseudo.HotPink"
#define LOCALIZED_COLOR_INDIANRED             L"pseudo.IndianRed"
#define LOCALIZED_COLOR_INDIGO                L"pseudo.Indigo"
#define LOCALIZED_COLOR_IVORY                 L"pseudo.Ivory"
#define LOCALIZED_COLOR_KHAKI                 L"pseudo.Khaki"
#define LOCALIZED_COLOR_LAVENDER              L"pseudo.Lavender"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"pseudo.LavenderBlush"
#define LOCALIZED_COLOR_LAWNGREEN             L"pseudo.LawnGreen"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"pseudo.LemonChiffon"
#define LOCALIZED_COLOR_LIGHTBLUE             L"pseudo.LightBlue"
#define LOCALIZED_COLOR_LIGHTCORAL            L"pseudo.LightCoral"
#define LOCALIZED_COLOR_LIGHTCYAN             L"pseudo.LightCyan"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"pseudo.LightGoldenRodYellow"
#define LOCALIZED_COLOR_LIGHTGRAY             L"pseudo.LightGray"
#define LOCALIZED_COLOR_LIGHTGREEN            L"pseudo.LightGreen"
#define LOCALIZED_COLOR_LIGHTGREY             L"pseudo.LightGrey"
#define LOCALIZED_COLOR_LIGHTPINK             L"pseudo.LightPink"
#define LOCALIZED_COLOR_LIGHTSALMON           L"pseudo.LightSalmon"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"pseudo.LightSeaGreen"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"pseudo.LightSkyBlue"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"pseudo.LightSlateGray"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"pseudo.LightSlateGrey"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"pseudo.LightSteelBlue"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"pseudo.LightYellow"
#define LOCALIZED_COLOR_LIME                  L"pseudo.Lime"
#define LOCALIZED_COLOR_LIMEGREEN             L"pseudo.LimeGreen"
#define LOCALIZED_COLOR_LINEN                 L"pseudo.Linen"
#define LOCALIZED_COLOR_MAGENTA               L"pseudo.Magenta"
#define LOCALIZED_COLOR_MAROON                L"pseudo.Maroon"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"pseudo.MediumAquaMarine"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"pseudo.MediumBlue"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"pseudo.MediumOrchid"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"pseudo.MediumPurple"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"pseudo.MediumSeaGreen"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"pseudo.MediumSlateBlue"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"pseudo.MediumSpringGreen"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"pseudo.MediumTurquoise"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"pseudo.MediumVioletRed"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"pseudo.MidnightBlue"
#define LOCALIZED_COLOR_MINTCREAM             L"pseudo.MintCream"
#define LOCALIZED_COLOR_MISTYROSE             L"pseudo.MistyRose"
#define LOCALIZED_COLOR_MOCCASIN              L"pseudo.Moccasin"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"pseudo.NavajoWhite"
#define LOCALIZED_COLOR_NAVY                  L"pseudo.Navy"
#define LOCALIZED_COLOR_OLDLACE               L"pseudo.OldLace"
#define LOCALIZED_COLOR_OLIVE                 L"pseudo.Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             L"pseudo.OliveDrab"
#define LOCALIZED_COLOR_ORANGE                L"pseudo.Orange"
#define LOCALIZED_COLOR_ORANGERED             L"pseudo.OrangeRed"
#define LOCALIZED_COLOR_ORCHID                L"pseudo.Orchid"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"pseudo.PaleGoldenRod"
#define LOCALIZED_COLOR_PALEGREEN             L"pseudo.PaleGreen"
#define LOCALIZED_COLOR_PALETURQUOISE         L"pseudo.PaleTurquoise"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"pseudo.PaleVioletRed"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"pseudo.PapayaWhip"
#define LOCALIZED_COLOR_PEACHPUFF             L"pseudo.PeachPuff"
#define LOCALIZED_COLOR_PERU                  L"pseudo.Peru"
#define LOCALIZED_COLOR_PINK                  L"pseudo.Pink"
#define LOCALIZED_COLOR_PLUM                  L"pseudo.Plum"
#define LOCALIZED_COLOR_POWDERBLUE            L"pseudo.PowderBlue"
#define LOCALIZED_COLOR_PURPLE                L"pseudo.Purple"
#define LOCALIZED_COLOR_RED                   L"pseudo.Red"
#define LOCALIZED_COLOR_ROSYBROWN             L"pseudo.RosyBrown"
#define LOCALIZED_COLOR_ROYALBLUE             L"pseudo.RoyalBlue"
#define LOCALIZED_COLOR_SADDLEBROWN           L"pseudo.SaddleBrown"
#define LOCALIZED_COLOR_SALMON                L"pseudo.Salmon"
#define LOCALIZED_COLOR_SANDYBROWN            L"pseudo.SandyBrown"
#define LOCALIZED_COLOR_SEAGREEN              L"pseudo.SeaGreen"
#define LOCALIZED_COLOR_SEASHELL              L"pseudo.SeaShell"
#define LOCALIZED_COLOR_SIENNA                L"pseudo.Sienna"
#define LOCALIZED_COLOR_SILVER                L"pseudo.Silver"
#define LOCALIZED_COLOR_SKYBLUE               L"pseudo.SkyBlue"
#define LOCALIZED_COLOR_SLATEBLUE             L"pseudo.SlateBlue"
#define LOCALIZED_COLOR_SLATEGRAY             L"pseudo.SlateGray"
#define LOCALIZED_COLOR_SLATEGREY             L"pseudo.SlateGrey"
#define LOCALIZED_COLOR_SNOW                  L"pseudo.Snow"
#define LOCALIZED_COLOR_SPRINGGREEN           L"pseudo.SpringGreen"
#define LOCALIZED_COLOR_STEELBLUE             L"pseudo.SteelBlue"
#define LOCALIZED_COLOR_TAN                   L"pseudo.Tan"
#define LOCALIZED_COLOR_TEAL                  L"pseudo.Teal"
#define LOCALIZED_COLOR_THISTLE               L"pseudo.Thistle"
#define LOCALIZED_COLOR_TOMATO                L"pseudo.Tomato"
#define LOCALIZED_COLOR_TURQUOISE             L"pseudo.Turquoise"
#define LOCALIZED_COLOR_VIOLET                L"pseudo.Violet"
#define LOCALIZED_COLOR_WHEAT                 L"pseudo.Wheat"
#define LOCALIZED_COLOR_WHITE                 L"pseudo.White"
#define LOCALIZED_COLOR_WHITESMOKE            L"pseudo.WhiteSmoke"
#define LOCALIZED_COLOR_YELLOW                L"pseudo.Yellow"
#define LOCALIZED_COLOR_YELLOWGREEN           L"pseudo.YellowGreen"

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       L"pseudo.Window"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       L"pseudo.Static"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      L"pseudo.ListBox"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     L"pseudo.ComboBox"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       L"pseudo.Button"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    L"pseudo.ScrollBar"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     L"pseudo.GroupBox"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  L"pseudo.RadioButton"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     L"pseudo.CheckBox"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       L"pseudo.Dialog"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE L"pseudo.Courier"
