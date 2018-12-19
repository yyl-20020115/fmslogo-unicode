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
// This file contains localized strings for German by Stephan Vogel
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
#define LOCALIZED_ALTERNATE_TRUE     L"wahr"
#define LOCALIZED_ALTERNATE_FALSE    L"falsch"
#define LOCALIZED_ALTERNATE_END      L"ende"
#define LOCALIZED_ALTERNATE_TOPLEVEL L"Ausstieg"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              L".defMakro"
#define LOCALIZED_ALTERNATE__EQ                    L".eq"
#define LOCALIZED_ALTERNATE__MACRO                 L".Makro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".maybeoutput"
#define LOCALIZED_ALTERNATE__SETBF                 L".setbf"
#define LOCALIZED_ALTERNATE__SETFIRST              L".setfirst"
#define LOCALIZED_ALTERNATE__SETITEM               L".setitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"aktiverBereich"
#define LOCALIZED_ALTERNATE_ALLOPEN                L"offenZ"
#define LOCALIZED_ALTERNATE_AND                    L"alle?"
#define LOCALIZED_ALTERNATE_APPLY                  L"benutze"
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  L"Array"
#define LOCALIZED_ALTERNATE_ARRAYP                 L"arrayp"
#define LOCALIZED_ALTERNATE_ARRAY_                 L"Array?"
#define LOCALIZED_ALTERNATE_ASCII                  L"asc"
#define LOCALIZED_ALTERNATE_ASHIFT                 L"ashift"
#define LOCALIZED_ALTERNATE_BACK                   L"r?ckw?rts"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"backslashedp"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"backslashed?"
#define LOCALIZED_ALTERNATE_BEFOREP                L"beforep"
#define LOCALIZED_ALTERNATE_BEFORE_                L"vorher?"
#define LOCALIZED_ALTERNATE_BF                     L"oe"
#define LOCALIZED_ALTERNATE_BFS                    L"oea"
#define LOCALIZED_ALTERNATE_BITAND                 L"bitund"
#define LOCALIZED_ALTERNATE_BITBLOCK               L"Bitblock"
#define LOCALIZED_ALTERNATE_BITCOPY                L"Bitkopieren"
#define LOCALIZED_ALTERNATE_BITCUT                 L"Bitausschneiden"
#define LOCALIZED_ALTERNATE_BITFIT                 L"bitfit"
#define LOCALIZED_ALTERNATE_BITINDEX               L"Bitindex"
#define LOCALIZED_ALTERNATE_BITLOAD                L"Bitladen"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"bitloadsize"
#define LOCALIZED_ALTERNATE_BITSIZE                L"Bitgr??e"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"bitmapturtle"
#define LOCALIZED_ALTERNATE_BITMODE                L"bitmodus"
#define LOCALIZED_ALTERNATE_BITNOT                 L"bitnicht"
#define LOCALIZED_ALTERNATE_BITOR                  L"bitoder"
#define LOCALIZED_ALTERNATE_BITPASTE               L"Biteinf?gen"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"Biteinf?geninindex"
#define LOCALIZED_ALTERNATE_BITSAVE                L"Bitbewahren"
#define LOCALIZED_ALTERNATE_BITXOR                 L"bitxoder"
#define LOCALIZED_ALTERNATE_BK                     L"rw"
#define LOCALIZED_ALTERNATE_BL                     L"ol"
#define LOCALIZED_ALTERNATE_BURIED                 L"versteckt"
#define LOCALIZED_ALTERNATE_BURY                   L"verstecke"
#define LOCALIZED_ALTERNATE_BUTFIRST               L"ohneerstes"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"butfirsts"
#define LOCALIZED_ALTERNATE_BUTLAST                L"ohneletztes"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"Knopfschaffen"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"Knopfl?schen"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"Knopfstatus"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"Knopfneu"
#define LOCALIZED_ALTERNATE_BUTTONP                L"buttonp"
#define LOCALIZED_ALTERNATE_BUTTON_                L"Knopf?"
#define LOCALIZED_ALTERNATE_BYE                    L"ade"
#define LOCALIZED_ALTERNATE_CATCH                  L"fange"
#define LOCALIZED_ALTERNATE_CHAR                   L"Zeichen"
#define LOCALIZED_ALTERNATE_CHDIR                  L"chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"Kontrollboxschaffen"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"Kontrollboxl?schen"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"Kontrollboxstatus"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"Kontrollboxstatus?"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"Kontrollboxset"
#define LOCALIZED_ALTERNATE_CLEAN                  L"lb"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"L?schePalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"bild"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"L?scheText"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"L?scheZeitnehmer"
#define LOCALIZED_ALTERNATE_CLOSE                  L"schlie?e"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"schlie?ealles"
#define LOCALIZED_ALTERNATE_CO                     L"wt"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"Komtaboxtext"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"Komtaboxschaffen"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"Komtaboxl?schen"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"Komtaboxstatus"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"Komtaboxtextl?schen"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"Komtaboxtextliste"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"Komtaboxsetzetext"
#define LOCALIZED_ALTERNATE_CONTENTS               L"Titelliste"
#define LOCALIZED_ALTERNATE_CONTINUE               L"weiter"
#define LOCALIZED_ALTERNATE_COPYDEF                L"copydef"
#define LOCALIZED_ALTERNATE_COS                    L"cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"L?nge"
#define LOCALIZED_ALTERNATE_CS                     L"cs"
#define LOCALIZED_ALTERNATE_CT                     L"ls"
#define LOCALIZED_ALTERNATE_CURSOR                 L"BO"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"Fensterbaum"
#define LOCALIZED_ALTERNATE_DEFINE                 L"def"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"def?"
#define LOCALIZED_ALTERNATE_DEFINED_               L"definiert?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"Dialogschaffen"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"Dialogstatus"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"Dialogl?schen"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"dialogfileopen"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"dialogfilesave"
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"Differenz"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"directories"
#define LOCALIZED_ALTERNATE_DLLCALL                L"dllrufen"
#define LOCALIZED_ALTERNATE_DLLFREE                L"dllfrei"
#define LOCALIZED_ALTERNATE_DLLLOAD                L"dllladen"
#define LOCALIZED_ALTERNATE_DOWN                   L"down"
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"downpitch"
#define LOCALIZED_ALTERNATE_DRIBBLE                L"dribble"
#define LOCALIZED_ALTERNATE_ED                     L"ed"
#define LOCALIZED_ALTERNATE_EDIT                   L"edit"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"ellipsearc"
#define LOCALIZED_ALTERNATE_EMPTYP                 L"emptyp"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"leer?"
#define LOCALIZED_ALTERNATE_EOFP                   L"eofp"
#define LOCALIZED_ALTERNATE_EOF_                   L"Dateiende?"
#define LOCALIZED_ALTERNATE_EQUALP                 L"equalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"gleich?"
#define LOCALIZED_ALTERNATE_ER                     L"erstes"
#define LOCALIZED_ALTERNATE_ERASE                  L"vg"
#define LOCALIZED_ALTERNATE_ERASEFILE              L"vergissDatei"
#define LOCALIZED_ALTERNATE_ERF                    L"vd"
#define LOCALIZED_ALTERNATE_ERROR                  L"Fehler"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"EreignisProtokoll"
#define LOCALIZED_ALTERNATE_EXP                    L"exp"
#define LOCALIZED_ALTERNATE_FD                     L"vw"
#define LOCALIZED_ALTERNATE_FENCE                  L"Rand"
#define LOCALIZED_ALTERNATE_FILL                   L"f?lle"
#define LOCALIZED_ALTERNATE_FILES                  L"files"
#define LOCALIZED_ALTERNATE_FIRST                  L"er"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"aer"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"F?llfarbez"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"fontfacenames"
#define LOCALIZED_ALTERNATE_FOREVER                L"andauernd"
#define LOCALIZED_ALTERNATE_FORM                   L"Zahlformat"
#define LOCALIZED_ALTERNATE_FORWARD                L"vorw?rts"
#define LOCALIZED_ALTERNATE_FPUT                   L"me"
#define LOCALIZED_ALTERNATE_FS                     L"vb"
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"Vollbild"
#define LOCALIZED_ALTERNATE_FULLTEXT               L"Prtext"
#define LOCALIZED_ALTERNATE_GETFOCUS               L"getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   L"gehe"
#define LOCALIZED_ALTERNATE_GIFLOAD                L"gifload"
#define LOCALIZED_ALTERNATE_GIFSIZE                L"gifsize"
#define LOCALIZED_ALTERNATE_GIFSAVE                L"gifsave"
#define LOCALIZED_ALTERNATE_GPROP                  L"gibEg"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"greaterequalp"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"gr??ergleich?"
#define LOCALIZED_ALTERNATE_GREATERP               L"greaterp"
#define LOCALIZED_ALTERNATE_GREATER_               L"gr??er?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"Gruppenboxschaffen"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"Gruppenboxl?schen"
#define LOCALIZED_ALTERNATE_HALT                   L"halt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                L"Kurs"
#define LOCALIZED_ALTERNATE_HELP                   L"help"
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"vergissIgel"
#define LOCALIZED_ALTERNATE_HOME                   L"Mitte"
#define LOCALIZED_ALTERNATE_HT                     L"vi"
#define LOCALIZED_ALTERNATE_IF                     L"wenn"
#define LOCALIZED_ALTERNATE_IFELSE                 L"wennsonst"
#define LOCALIZED_ALTERNATE_IFF                    L"wf"
#define LOCALIZED_ALTERNATE_IFFALSE                L"wennfalsch"
#define LOCALIZED_ALTERNATE_IFT                    L"ww"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"wennwahr"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"Ingameport"
#define LOCALIZED_ALTERNATE_INPORT                 L"inport"
#define LOCALIZED_ALTERNATE_INPORTB                L"inportb"
#define LOCALIZED_ALTERNATE_INT                    L"ganzzahl"
#define LOCALIZED_ALTERNATE_ITEM                   L"Element"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"keyboardaus"
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"keyboardein"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"TastEG"
#define LOCALIZED_ALTERNATE_KEYP                   L"keyp"
#define LOCALIZED_ALTERNATE_KEY_                   L"Taste?"
#define LOCALIZED_ALTERNATE_LABEL                  L"Igeltext"
#define LOCALIZED_ALTERNATE_LABELFONT              L"labelfont"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"l?ngeigeltext"
#define LOCALIZED_ALTERNATE_LAST                   L"lz"
#define LOCALIZED_ALTERNATE_LEFT                   L"links"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"leftroll"
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"lessequalp"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"kleinergleich?"
#define LOCALIZED_ALTERNATE_LESSP                  L"lessp"
#define LOCALIZED_ALTERNATE_LESS_                  L"kleiner?"
#define LOCALIZED_ALTERNATE_LIGHT                  L"light"
#define LOCALIZED_ALTERNATE_LIST                   L"Liste"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"Listeboxtext"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"Listeboxschaffen"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"Listeboxstatus"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"Listeboxl?schen"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"Listeboxl?schetext"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"Listeboxwahl"
#define LOCALIZED_ALTERNATE_LISTP                  L"listp"
#define LOCALIZED_ALTERNATE_LIST_                  L"Liste?"
#define LOCALIZED_ALTERNATE_LN                     L"ln"
#define LOCALIZED_ALTERNATE_LOAD                   L"lade"
#define LOCALIZED_ALTERNATE_LOCAL                  L"lokal"
#define LOCALIZED_ALTERNATE_LOG10                  L"log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"Logoversion"
#define LOCALIZED_ALTERNATE_LOWERCASE              L"klein"
#define LOCALIZED_ALTERNATE_LPUT                   L"ml"
#define LOCALIZED_ALTERNATE_LR                     L"lr"
#define LOCALIZED_ALTERNATE_LSHIFT                 L"lshift"
#define LOCALIZED_ALTERNATE_LT                     L"li"
#define LOCALIZED_ALTERNATE_MACHINE                L"machine"
#define LOCALIZED_ALTERNATE_MACROP                 L"macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 L"Makro?"
#define LOCALIZED_ALTERNATE_MAKE                   L"setze"
#define LOCALIZED_ALTERNATE_MCI                    L"mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"Elementab"
#define LOCALIZED_ALTERNATE_MEMBERP                L"Element?"
#define LOCALIZED_ALTERNATE_MEMBER_                L"El?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"Meldungsbox"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"Midischlie?en"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"Midimeldung"
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"Midi?ffnen"
#define LOCALIZED_ALTERNATE_MINUS                  L"minus"
#define LOCALIZED_ALTERNATE_MKDIR                  L"mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 L"modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"Mausaus"
#define LOCALIZED_ALTERNATE_MOUSEON                L"Mausan"
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"MausOrt"
#define LOCALIZED_ALTERNATE_NAMEP                  L"namep"
#define LOCALIZED_ALTERNATE_NAME_                  L"Name?"
#define LOCALIZED_ALTERNATE_NAMES                  L"Namen"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"netzannahmeaus"
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"netzannahmeein"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"netzannahmewertempfangen"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"netzannahmewertsenden"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"netzunterbrechen"
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"netzverbinden"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"netzverbundwertempfangen"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"netzverbundwertsenden"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"netzbeenden"
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"netstarten"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"nobitmapturtle"
#define LOCALIZED_ALTERNATE_NODES                  L"Knoten"
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"nodribble"
#define LOCALIZED_ALTERNATE_NOSTATUS               L"K.Status"
#define LOCALIZED_ALTERNATE_NOT                    L"nicht?"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"notequalp"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"nichtgleich?"
#define LOCALIZED_ALTERNATE_NOYIELD                L"noyield"
#define LOCALIZED_ALTERNATE_NUMBERP                L"numberp"
#define LOCALIZED_ALTERNATE_NUMBER_                L"Zahl?"
#define LOCALIZED_ALTERNATE_OP                     L"rg"
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"openappend"
#define LOCALIZED_ALTERNATE_OPENREAD               L"openread"
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"openupdate"
#define LOCALIZED_ALTERNATE_OPENWRITE              L"openwrite"
#define LOCALIZED_ALTERNATE_OR                     L"eines?"
#define LOCALIZED_ALTERNATE_OUTPORT                L"outport"
#define LOCALIZED_ALTERNATE_OUTPORTB               L"outportb"
#define LOCALIZED_ALTERNATE_OUTPUT                 L"R?ckgabe"
#define LOCALIZED_ALTERNATE_PARSE                  L"parse"
#define LOCALIZED_ALTERNATE_PAUSE                  L"Pause"
#define LOCALIZED_ALTERNATE_PC                     L"pc"
#define LOCALIZED_ALTERNATE_PD                     L"sa"
#define LOCALIZED_ALTERNATE_PE                     L"rd"
#define LOCALIZED_ALTERNATE_PENCOLOR               L"FarbeZ"
#define LOCALIZED_ALTERNATE_PENDOWN                L"Stiftab"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"pendownp"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"Stiftab?"
#define LOCALIZED_ALTERNATE_PENERASE               L"radiere"
#define LOCALIZED_ALTERNATE_PENMODE                L"Stiftmodus"
#define LOCALIZED_ALTERNATE_PENPAINT               L"Normalstift"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"Stiftform"
#define LOCALIZED_ALTERNATE_PENREVERSE             L"Umkehrstift"
#define LOCALIZED_ALTERNATE_PENSIZE                L"StiftZ"
#define LOCALIZED_ALTERNATE_PENUP                  L"Stifthoch"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"Perspektive"
#define LOCALIZED_ALTERNATE_PITCH                  L"pitch"
#define LOCALIZED_ALTERNATE_PIXEL                  L"pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"spielewave"
#define LOCALIZED_ALTERNATE_PLIST                  L"Egliste"
#define LOCALIZED_ALTERNATE_PLISTS                 L"Eglisten"
#define LOCALIZED_ALTERNATE_PO                     L"zg"
#define LOCALIZED_ALTERNATE_POPDIR                 L"popdir"
#define LOCALIZED_ALTERNATE_POLYSTART              L"Polystart"
#define LOCALIZED_ALTERNATE_POLYEND                L"polyende"
#define LOCALIZED_ALTERNATE_POLYVIEW               L"Polysehen"
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"portschlie?en"
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"portfluten"
#define LOCALIZED_ALTERNATE_PORTMODE               L"portmodus"
#define LOCALIZED_ALTERNATE_PORTOPEN               L"port?ffnen"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"portliesarray"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"portlieszeichen"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"portschreibearray"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"portschreibezeichen"
#define LOCALIZED_ALTERNATE_POS                    L"Ort"
#define LOCALIZED_ALTERNATE_POSXYZ                 L"Ortxyz"
#define LOCALIZED_ALTERNATE_POT                    L"zt"
#define LOCALIZED_ALTERNATE_POWER                  L"Potenz"
#define LOCALIZED_ALTERNATE_PPROP                  L"MitEg"
#define LOCALIZED_ALTERNATE_PPT                    L"SMale"
#define LOCALIZED_ALTERNATE_PR                     L"dz"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"Grundwort?"
#define LOCALIZED_ALTERNATE_PRINT                  L"druckezeile"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"procedurep"
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"Prozedur?"
#define LOCALIZED_ALTERNATE_PROPLISTP              L"proplistp"
#define LOCALIZED_ALTERNATE_PROPLIST_              L"proplist?"
#define LOCALIZED_ALTERNATE_PROCEDURES             L"Prozedurliste"
#define LOCALIZED_ALTERNATE_PRODUCT                L"Produkt"
#define LOCALIZED_ALTERNATE_PU                     L"sh"
#define LOCALIZED_ALTERNATE_PX                     L"sr"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"Fragebox"
#define LOCALIZED_ALTERNATE_QUOTIENT               L"Quotient"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 L"radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"Radioknopfschaffen"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"Radioknopfstatus"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"Radioknopfl?schen"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"Radioknopfstatus?"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"Radioknopfaktiv"
#define LOCALIZED_ALTERNATE_RADSIN                 L"radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 L"radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 L"zz"
#define LOCALIZED_ALTERNATE_RAWASCII               L"rawascii"
#define LOCALIZED_ALTERNATE_RC                     L"Liestaste"
#define LOCALIZED_ALTERNATE_RCS                    L"Liestasten"
#define LOCALIZED_ALTERNATE_READCHAR               L"readchar"
#define LOCALIZED_ALTERNATE_READCHARS              L"liesZeichen"
#define LOCALIZED_ALTERNATE_READER                 L"reader"
#define LOCALIZED_ALTERNATE_READLIST               L"liesListe"
#define LOCALIZED_ALTERNATE_READPOS                L"Liespos"
#define LOCALIZED_ALTERNATE_READRAWLINE            L"readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               L"liesWort"
#define LOCALIZED_ALTERNATE_REMAINDER              L"Rest"
#define LOCALIZED_ALTERNATE_REMPROP                L"vgEg"
#define LOCALIZED_ALTERNATE_REPCOUNT               L"whZahl"
#define LOCALIZED_ALTERNATE_REPEAT                 L"wh"
#define LOCALIZED_ALTERNATE_RERANDOM               L"sZ"
#define LOCALIZED_ALTERNATE_RIGHT                  L"rechts"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"rightroll"
#define LOCALIZED_ALTERNATE_RL                     L"ll"
#define LOCALIZED_ALTERNATE_RMDIR                  L"rmdir"
#define LOCALIZED_ALTERNATE_ROLL                   L"roll"
#define LOCALIZED_ALTERNATE_ROUND                  L"runde"
#define LOCALIZED_ALTERNATE_RR                     L"rr"
#define LOCALIZED_ALTERNATE_RT                     L"re"
#define LOCALIZED_ALTERNATE_RUN                    L"tue"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"runparse"
#define LOCALIZED_ALTERNATE_RUNRESULT              L"tueWert"
#define LOCALIZED_ALTERNATE_RW                     L"rw"
#define LOCALIZED_ALTERNATE_SAVE                   L"bw"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"hgz"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"Rollbalkenschaffen"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"Rollbalkenstatus"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"Rollbalkenl?schen"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"Rollbalkenwert"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"Rollbalkendef"
#define LOCALIZED_ALTERNATE_SCROLLX                L"scrollx"
#define LOCALIZED_ALTERNATE_SCROLLY                L"scrolly"
#define LOCALIZED_ALTERNATE_SCRUNCH                L"Skalaz"
#define LOCALIZED_ALTERNATE_SE                     L"se"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"auswahlbox"
#define LOCALIZED_ALTERNATE_SENTENCE               L"satz"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"setactivearea"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"setbitindex"
#define LOCALIZED_ALTERNATE_SETBITMODE             L"setbitmode"
#define LOCALIZED_ALTERNATE_SETCLIP                L"setclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              L"setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"setcursornowait"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"setcursorwait"
#define LOCALIZED_ALTERNATE_SETFC                  L"setfc"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"F?llfarbe"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"setfocus"
#define LOCALIZED_ALTERNATE_SETH                   L"ak"
#define LOCALIZED_ALTERNATE_SETHEADING             L"aufkurs"
#define LOCALIZED_ALTERNATE_SETITEM                L"setitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"setKennungSchrift"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"setlight"
#define LOCALIZED_ALTERNATE_SETMARGINS             L"setmargins"
#define LOCALIZED_ALTERNATE_SETPC                  L"Farbe"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"Stiftfarbe"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"StiftFarbMuster"
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"Stiftdicke"
#define LOCALIZED_ALTERNATE_SETPITCH               L"setpitch"
#define LOCALIZED_ALTERNATE_SETPIXEL               L"setpixel"
#define LOCALIZED_ALTERNATE_SETPOS                 L"auf"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"setposxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREAD                L"LiesDatei"
#define LOCALIZED_ALTERNATE_SETREADPOS             L"setreadpos"
#define LOCALIZED_ALTERNATE_SETROLL                L"setroll"
#define LOCALIZED_ALTERNATE_SETSC                  L"hg"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"Hintergrundfarbe"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"Skala"
#define LOCALIZED_ALTERNATE_SETTIMER               L"setzeZeitnehmer"
#define LOCALIZED_ALTERNATE_SETTURTLE              L"setzeigel"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"setzeigelmodus"
#define LOCALIZED_ALTERNATE_SETWRITE               L"Kopieein"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"setwritepos"
#define LOCALIZED_ALTERNATE_SETX                   L"aufx"
#define LOCALIZED_ALTERNATE_SETXY                  L"aufxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"aufxyz"
#define LOCALIZED_ALTERNATE_SETY                   L"aufy"
#define LOCALIZED_ALTERNATE_SETZ                   L"aufz"
#define LOCALIZED_ALTERNATE_SHELL                  L"shell"
#define LOCALIZED_ALTERNATE_SHOW                   L"dzl"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"shownp"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"sichtbar?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"zeigIgel"
#define LOCALIZED_ALTERNATE_SIN                    L"sin"
#define LOCALIZED_ALTERNATE_SOUND                  L"Sound"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"Teilbild"
#define LOCALIZED_ALTERNATE_SQRT                   L"qw"
#define LOCALIZED_ALTERNATE_SS                     L"ss"
#define LOCALIZED_ALTERNATE_ST                     L"zi"
#define LOCALIZED_ALTERNATE_STANDOUT               L"hervorheben"
#define LOCALIZED_ALTERNATE_STATICCREATE           L"Statuszeileschaffen"
#define LOCALIZED_ALTERNATE_STATICDELETE           L"Statuszeilel?schen"
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"Statuszeileneu"
#define LOCALIZED_ALTERNATE_STATUS                 L"Status"
#define LOCALIZED_ALTERNATE_STEP                   L"PSe"
#define LOCALIZED_ALTERNATE_STEPPED                L"stepped"
#define LOCALIZED_ALTERNATE_STOP                   L"rk"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"substringp"
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"substring?"
#define LOCALIZED_ALTERNATE_SUM                    L"Summe"
#define LOCALIZED_ALTERNATE_TAG                    L"tag"
#define LOCALIZED_ALTERNATE_TAN                    L"tan"
#define LOCALIZED_ALTERNATE_TEST                   L"pr?fe"
#define LOCALIZED_ALTERNATE_TEXT                   L"PrListe"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"TextSchirm"
#define LOCALIZED_ALTERNATE_THING                  L"Wert"
#define LOCALIZED_ALTERNATE_THROW                  L"wirf"
#define LOCALIZED_ALTERNATE_TIME                   L"Zeit"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"ZeitMilli"
#define LOCALIZED_ALTERNATE_TO                     L"pr"
#define LOCALIZED_ALTERNATE_TONE                   L"Ton"
#define LOCALIZED_ALTERNATE_TOWARDS                L"ri"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"Richtungxyz"
#define LOCALIZED_ALTERNATE_TRACE                  L"Pein"
#define LOCALIZED_ALTERNATE_TRACED                 L"traced"
#define LOCALIZED_ALTERNATE_TS                     L"ts"
#define LOCALIZED_ALTERNATE_TURTLE                 L"Igel"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"turtlemode"
#define LOCALIZED_ALTERNATE_TURTLES                L"Igelschar"
#define LOCALIZED_ALTERNATE_TYPE                   L"drucke"
#define LOCALIZED_ALTERNATE_UNBURY                 L"grabeaus"
#define LOCALIZED_ALTERNATE_UNSTEP                 L"PSa"
#define LOCALIZED_ALTERNATE_UNTRACE                L"Pa"
#define LOCALIZED_ALTERNATE_UP                     L"up"
#define LOCALIZED_ALTERNATE_UPPERCASE              L"gro?"
#define LOCALIZED_ALTERNATE_UPPITCH                L"uppitch"
#define LOCALIZED_ALTERNATE_WAIT                   L"warte"
#define LOCALIZED_ALTERNATE_WINDOW                 L"fenster"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"Fensterschaffen"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"Fensterstatus"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"Fensterl?schen"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"windowfileedit"
#define LOCALIZED_ALTERNATE_WINDOWSET              L"windowset"
#define LOCALIZED_ALTERNATE_WINHELP                L"winhelp"
#define LOCALIZED_ALTERNATE_WORD                   L"Wort"
#define LOCALIZED_ALTERNATE_WORDP                  L"wordp?"
#define LOCALIZED_ALTERNATE_WORD_                  L"Wort?"
#define LOCALIZED_ALTERNATE_WRAP                   L"Randsprung"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"writepos"
#define LOCALIZED_ALTERNATE_WRITER                 L"writer"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"JaNeinBox"
#define LOCALIZED_ALTERNATE_YIELD                  L"yield"
#define LOCALIZED_ALTERNATE_ZOOM                   L"Zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"Abbruch"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&?bernahme"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"Die FMSLogo-Programmierumgebung"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&Datei"
#define LOCALIZED_FILE_NEW              L"&Neu\t(l?scht Arbeitsspeicher)"
#define LOCALIZED_FILE_LOAD             L"&Lade...\t(stellt in den Arbeitsspeicher)"
#define LOCALIZED_FILE_OPEN             L"?&ffne...\t(ersetzt Arbeitsspeicher)" 
#define LOCALIZED_FILE_SAVE             L"&Speichern" 
#define LOCALIZED_FILE_SAVEAS           L"Speichern &unter..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"Legen Sie als Bildschirmschoner"
#define LOCALIZED_FILE_EDIT             L"&Edit..."
#define LOCALIZED_FILE_ERASE            L"&L?schen..."
#define LOCALIZED_FILE_EXIT             L"&Beenden"

#define LOCALIZED_BITMAP               L"&Bild"
#define LOCALIZED_BITMAP_NEW           L"&Neu"
#define LOCALIZED_BITMAP_LOAD          L"&Lade..."
#define LOCALIZED_BITMAP_SAVE          L"&Bewahre..."
#define LOCALIZED_BITMAP_SAVEAS        L"Speichern &als..."
#define LOCALIZED_BITMAP_PRINT         L"&Drucken..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"Drucker&setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"A&ktiver Bereich..."

#define LOCALIZED_SET                  L"&Optionen"
#define LOCALIZED_SET_PENSIZE          L"Stift&dicke..."
#define LOCALIZED_SET_LABELFONT        L"&Grafik-Schrift..."
#define LOCALIZED_SET_COMMANDERFONT    L"&Befehle-Schrift..."
#define LOCALIZED_SET_PENCOLOR         L"&Stiftfarbe..."
#define LOCALIZED_SET_FLOODCOLOR       L"&F?llfarbe..."
#define LOCALIZED_SET_SCREENCOLOR      L"&Hintergrundfarbe..."

#define LOCALIZED_ZOOM                 L"&Zoom" 
#define LOCALIZED_ZOOM_IN              L"&<<"
#define LOCALIZED_ZOOM_OUT             L"&>>"
#define LOCALIZED_ZOOM_NORMAL          L"&Normal"

#define LOCALIZED_HELP                 L"&Hilfen" 
#define LOCALIZED_HELP_INDEX           L"&Index"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutorial"
#define LOCALIZED_HELP_DEMO            L"&Demo" 
#define LOCALIZED_HELP_EXAMPLE         L"&Beispiele"
#define LOCALIZED_HELP_RELEASENOTES    L"&Anmerkungen"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"&?ber " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"?ber &MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"Deutsch -> Englisch"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"Englisch -> Deutsch"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Aktiver Bereich w?hlen"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"Wirkt auf Drucken und Speichern der Bilder"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-Pos"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Neg" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-Pos"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Neg"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"Igelschritte in Inch gedruckt:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"FMSLogo Bildschirmschoner-Einstellungen"
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Suchen Sie ..."
#define LOCALIZED_SCREENSAVER_FILE              L"Logo &Datei:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"W?hlen Sie eine " LOCALIZED_ALTERNATE_STARTUP "-Anweisung"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"Der Arbeitsbereich hat keine Anweisungsliste " LOCALIZED_ALTERNATE_STARTUP " definiert, so dass nichts passieren wird,\nwenn der Bildschirmschoner geladen wird. Bitte w?hlen Sie eine Prozedur aus, wenn das Programm geladen wird."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"Die Variable " LOCALIZED_ALTERNATE_STARTUP " ist keine Liste, so dass nichts passieren wird,\nwenn der Bildschirmschoner geladen wird. Bitte w?hlen Sie eine Prozedur aus, wenn das Programm geladen wird."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"Arbeitsbereich hat eine leere " LOCALIZED_ALTERNATE_STARTUP "-Anweisungsliste definiert,\nwenn der Bildschirmschoner geladen wird. Bitte w??hlen Sie eine Prozedur aus, wenn das Programm geladen wird."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"Keine Prozeduren sind definiert"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"Es gibt keine Prozeduren, Variablen oder Eigenschaftslisten definiert,\nso der Arbeitsbereich als eine leere Datei gespeichert werden soll.\n\nM?chten Sie den Arbeitsbereich trotzdem speichern?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Kopieren"
#define LOCALIZED_POPUP_CUT                      L"Ausschneiden"
#define LOCALIZED_POPUP_PASTE                    L"Einf?gen"
#define LOCALIZED_POPUP_DELETE                   L"L?schen"
#define LOCALIZED_POPUP_UNDO                     L"R?ckg?ngig"
#define LOCALIZED_POPUP_REDO                     L"Wiederholen"
#define LOCALIZED_POPUP_SELECTALL                L"Alles markieren"
#define LOCALIZED_POPUP_HELP                     L"Begriffsuche"
#define LOCALIZED_POPUP_REMOVELINES              L"Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Editor"

#define LOCALIZED_EDITOR_FILE                    L"&Datei"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Lerne und Ende\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"Speichern in den &Arbeitsspeicher"
#define LOCALIZED_EDITOR_FILE_PRINT              L"&Drucken..." 
#define LOCALIZED_EDITOR_FILE_EXIT               L"&Beenden" 

#define LOCALIZED_EDITOR_EDIT                    L"&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&R?ckg?ngig\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&Wiederholen\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"Aus&schneiden\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"&Kopieren\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"&Einf?gen\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&L?schen\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"&Alles l?schen\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"Alles &markieren\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"&Suchen"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"&Finden...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Ersetzen...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Weitersuchen\tF3" 

#define LOCALIZED_EDITOR_SET                     L"&Option" 
#define LOCALIZED_EDITOR_SET_FONT                L"&Schrift..." 

#define LOCALIZED_EDITOR_TEST                    L"Test" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    L"&Hilfen" 
#define LOCALIZED_EDITOR_HELP_INDEX              L"&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&Begriffsuche\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Lerne und Ende"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&Nicht speichern"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"Es gibt nicht abgespeicherte ?nderungen im Arbeitsspeicher. Wenn Sie beenden ohne abzuspeichern, gehen diese ?nderungen verloren.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"W?rden Sie gerne Ihre ?nderungen speichern bevor Sie beenden?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Kommandos"
#define LOCALIZED_COMMANDER_HALT                L"Halt"
#define LOCALIZED_COMMANDER_TRACE               L"Protokoll"
#define LOCALIZED_COMMANDER_NOTRACE             L"K. Prot."
#define LOCALIZED_COMMANDER_PAUSE               L"Pause"
#define LOCALIZED_COMMANDER_STATUS              L"Status"
#define LOCALIZED_COMMANDER_NOSTATUS            L"K. Status"
#define LOCALIZED_COMMANDER_STEP                L"Einzelschritt"
#define LOCALIZED_COMMANDER_UNSTEP              L"Turbo"
#define LOCALIZED_COMMANDER_RESET               L"Reset"
#define LOCALIZED_COMMANDER_EXECUTE             L"Ausf?hren"
#define LOCALIZED_COMMANDER_EDALL               L"Editor"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Status"
#define LOCALIZED_STATUS_PEN                    L"Stift"
#define LOCALIZED_STATUS_CONTACT                L"Zustand:"
#define LOCALIZED_STATUS_WIDTH                  L"Dicke:"
#define LOCALIZED_STATUS_STYLE                  L"Modus:"
#define LOCALIZED_STATUS_ORIENTATION            L"Lagekennung"
#define LOCALIZED_STATUS_PITCH                  L"->y,z:"
#define LOCALIZED_STATUS_HEADING                L"Kurs:->x,y"
#define LOCALIZED_STATUS_ROLL                   L"->x,z:"
#define LOCALIZED_STATUS_TURTLE                 L"Igel"
#define LOCALIZED_STATUS_POSITION               L"Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Igel-Nr.:"
#define LOCALIZED_STATUS_VISIBILITY             L"Sichtbar:"
#define LOCALIZED_STATUS_COLOR                  L"Farbe"
#define LOCALIZED_STATUS_PENCOLOR               L"Stift(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"F?lle(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Hinterg(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"L-Kern"
#define LOCALIZED_STATUS_CALLS                  L"Aufrufe:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"Speicherlast:"

#define LOCALIZED_STATUS_PENREVERSE     L"Umkehrstift"
#define LOCALIZED_STATUS_PENNORMAL      L"Normalstift"
#define LOCALIZED_STATUS_PENERASE       L"l?schen"
#define LOCALIZED_STATUS_PENUP          L"Hoch"
#define LOCALIZED_STATUS_PENDOWN        L"Ab"
#define LOCALIZED_STATUS_PENSHOWN       L"Sichtbar"
#define LOCALIZED_STATUS_PENHIDDEN      L"Versteckt"
#define LOCALIZED_STATUS_POLYGONS       L"Polygone"
#define LOCALIZED_STATUS_VECTORS        L"Vektoren"
#define LOCALIZED_STATUS_NODES          L"Knoten"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&Alle"
#define LOCALIZED_ERASEPROCEDURE                L"L?sche Prozedur"
#define LOCALIZED_EDITPROCEDURE                 L"Edit Prozedur"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Farbe setzen"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Stiftfarbe"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"F?llfarbe"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Hintergrundfarbe"
#define LOCALIZED_SETCOLOR_RED                 L"Rot"
#define LOCALIZED_SETCOLOR_GREEN               L"Gr?n"
#define LOCALIZED_SETCOLOR_BLUE                L"Blau"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Stiftdicke"
#define LOCALIZED_SETPENSIZE_SIZE              L"Dicke"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"?ber " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"Version"
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"Core by Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/\nPapert, Seymour: Gedankenblitze 8126 rororo"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Special Thanks to Yehuda Katz and Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc.\nVer?ndert/?bersetzt von Stephan Vogel\nAugust-Ruf-Bildungszentrum Ettenheim/S?dbaden\nSeine Logo-Projekte: http://www.lehrer.uni-karlsruhe.de/~za1880/itg/index.htm"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"?ber FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS steht f?r 'Fight Multiple Sclerosis'." 
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"Spenden f?r National Multiple Sclerosis Society\nerbeten, http://www.nmss.org, 1-800-FIGHT-MS\nRechnen und Steuern in M, Inf, Ph und Te.\nFraktale und Rekursionen in Oberstufen"
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the QUESTIONBOX dialog box
//
#define LOCALIZED_QUESTIONBOX_OK               LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_QUESTIONBOX_CANCEL           LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"?nderungen in dieser Edit-Sitzung k?nnen verloren gehen.\n\nWollen Sie wirklich " LOCALIZED_GENERAL_PRODUCTNAME " verlassen?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"Eine Edit-Sitzung l?uft gerade"

#define LOCALIZED_COULDNOTWRITEBMP            L"Konnte nicht .bmp schreiben"
#define LOCALIZED_COULDNOTOPENBMP             L"Konnte nicht .bmp ?ffnen"
#define LOCALIZED_COULDNOTCREATEBMP           L"Unf?hig Windows 3.0 Bitmap zu erstellen"
#define LOCALIZED_NOTVALIDBMP                 L"Kein Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"Sie haben nicht auf der Disk abgespeichert"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"Ein Neu (New) auszuf?hren wird alle Definitionen l?schen.\n\nFortfahren mit Neu (New)?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"Die zu ladende Datei wird in Ihren Arbeitsspeicher hinein gestellt\nund kann Ihre nicht gespeicherten ?nderungen ?berschreiben.\n\nFortfahren mit Laden (Load)?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"Dies wird alle Ihre nicht gespeicherten ?nderungen l?schen.\n\nFortfahren mit ?ffnen (Open)?"

#define LOCALIZED_EDITORISOPEN                  L"Wussten Sie, dass eine Edit-Sitzung gerade l?uft?\n\n?nderungen in dieser Edit-Sitzung sind noch nicht abgespeichert."

#define LOCALIZED_ERROR_CANTREADFILE            L"Unf?hig Datei \"%s\" von der Disk zu lesen"
#define LOCALIZED_ERROR_CANTWRITEFILE           L"Unf?hig Datei \"%s\" auf Disk zu schreiben"

#define LOCALIZED_SAVETOWORKSPACE                L"Speichern in den Arbeitsspeicher"
#define LOCALIZED_CONTENTSCHANGED                L"Inhalte ge?ndert"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"Die Inhalte sind ge?ndert.\nW?rden Sie gerne die ?nderungen im Arbeitsspeicher festhalten?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"Es gab ein Problem, die Inhalte des Editors in den Arbeitsspeicher zu ?bernehmen.  Der Cursor wird gleich nach der letzten erfolgreichen Definition positioniert.\n\n?berpr?fe den Commander nach m?glicher Fehlermeldung."
#define LOCALIZED_RETURNTOEDIT                  L"Zur?ck zum Editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

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

#define LOCALIZED_LOGO_FILE_EXTENSION L"log"
#define LOCALIZED_FILEFILTER_ALLFILES L"Alle Dateien (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Logo Dateien (*.log)|*.log;*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"Bitmap Dateien (*.bmp)|*.bmp|GIF Dateien (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" stoppt\n"
#define LOCALIZED_TRACING_OUTPUTS           L" gibt zur?ck %s\n"
#define LOCALIZED_TRACING_MAKE              L"Setze %s %s"
#define LOCALIZED_TRACING_PPROP             L"GibEg %s %s %s"
#define LOCALIZED_TRACING_LOCATION          L" in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Einzelschritt"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s gelernt\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"l?sche"
#define LOCALIZED_PENMODE_REVERSE  L"umgekehrt"
#define LOCALIZED_PENMODE_PAINT    L"zeichne"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: Fataler interner Fehler"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Speicher?berlauf!"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"Speicher?berlauf"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"Stack?berlauf"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"Igel au?erhalb der Grenzen"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"Konnte Grafiken nicht initialisieren"
#define LOCALIZED_ERROR_BADDATA                L"%p mag nicht %s als Eingabe"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p gab nicht nach %p aus"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"fehlende Eingaben in %p"
#define LOCALIZED_ERROR_TOOMUCH                L"zu viel innerhalb der ()'n"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"Sie sagen nicht, was mit %s zu machen ist"
#define LOCALIZED_ERROR_PARENMISMATCH          L"zu viele ('n"
#define LOCALIZED_ERROR_NOVALUE                L"%s hat keinen Wert"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"unerwartete ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"unerwartete ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"unerwartete '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"Was soll geschehen mit %p ?"
#define LOCALIZED_ERROR_NOCATCHTAG             L"Konnte FANGE-Schild f?r %p nicht finden"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p ist schon definiert"
#define LOCALIZED_ERROR_STOPPING               L"Gestoppt..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"Bereits in Arbeit"
#define LOCALIZED_ERROR_FILESYSTEM                   L"File-Systemfehler: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"Konnte Datei nicht ?ffnen"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"Kann nicht Datei: %t ?ffnen"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"Datei ist schon ge?ffnet"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"Datei ist nicht ge?ffnet"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"Konnte Editor-File nicht aufnehmen"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"Konnte den Editor nicht starten" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"Konnte Editor-File nicht lesen" 
#define LOCALIZED_ERROR_IFWARNING              L"Annahme: Sie meinen wohl WENNSONST (IFELSE), nicht WENN (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p ?berwacht von LOKAL (local) im Prozeduraufruf"
#define LOCALIZED_ERROR_USER                   L"Wirf \"Fehler"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p ist ein Grundwort"
#define LOCALIZED_ERROR_TONOTINSIDE            L"Kann PR (TO) verwenden innerhalb einer Prozedur"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"Kann nur %p  verwenden innerhalb einer Prozedur"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"Nur innerhalb einer Prozedur R?CKGABE (OUTPUT) oder RK (STOP) verwenden"
#define LOCALIZED_ERROR_NOTEST                 L"%p ohne TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"Makro-R?ckgabe %s anstatt einer Liste"
#define LOCALIZED_ERROR_DEEPEND                L"ENDE(END) innerhalb vielzeiliger Instruktion"
#define LOCALIZED_ERROR_DEEPENDIN              L"ENDE (END) innerhalb vielzeiliger Instruktion in %p"
#define LOCALIZED_ERROR_UNKNOWN                L"Unbekannte Fehlerbedingung - interner Fehler."
#define LOCALIZED_PAUSING                      L"Pausiere..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                L"%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Fehler"
#define LOCALIZED_ERROR_BADINPUT             L"Falsche Eingabe"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"Eingabe wird nicht vermittelt"

#define LOCALIZED_ERROR_CANTOPENPORT         L"Konnte Port nicht ?ffnen"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"Konnte Port nicht schlie?en"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"Konnte Port nicht durchstr?men"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"Konnte dcb nicht aufbauen auf Port"
#define LOCALIZED_ERROR_CANTSETPORT          L"Konnte Port nicht setzen"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"Port ist schon offen"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"Port ist nicht offen"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s ist bereits vorhanden"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s ist nicht vorhanden"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"DLL ist nicht geladen"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"DLL-Ladevorgang nicht erfolgreich"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Ung?ltiger Dateneingangstyp"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Ung?ltiger Ausgang-Typ"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Funktion nicht gefunden"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"Nicht alle Typen/Daten Eingaben werden vermittelt"

#define LOCALIZED_ERROR_NETWORK               L"Network Fehler"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Network Empfangsfehler"
#define LOCALIZED_ERROR_NETWORKSEND           L"Network Sendefehler"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Unerwarteter Fehler, Network d?rfte heruntergefahren sein"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"Nicht gestartet"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"Schon gestartet"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"Schon an"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"Schon aus"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Name zu lang"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"Nicht initialisiert"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"System nicht bereit"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"Version wird nicht unterst?tzt"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"Kann nicht senden, nachdem Socket heruntergefahren ist"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Interrupt-System Ruf"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Autorisierte Antwort: Host nicht gefunden"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"Nicht-autorisiert: Host nicht gefunden. Vgl. NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Kein wieder gut zu machender Fehler"
#define LOCALIZED_ERROR_NETWORKNODATA              L"Kein Daten-Record verf?gbar"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"Falsche Datei-Nummer"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"Operation w?rde blockieren"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"Operation jetzt im Fortschreiten"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"Operation jetzt im Fortschreiten"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Falsche Adresse"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Zieladresse gefordert"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Meldung zu lang"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Protokollfamilie wird nicht unterst?tzt"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"Verzeichnis ist nicht leer"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Anwendungsgrenze erreicht"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"Diskquote ?berschritten"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Zu viele offene Dateien"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Zugang verweigert"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Socket-Operation auf fehlendem Socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"Kann gesuchte Adresse nicht zuteilen"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"Adresse schon im Gebrauch"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"Adressenfamilie wird nicht unterst?tzt von der Protokollfamilie"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Zeit f?r Verbindung ?berschritten"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Socket-Typ wird nicht unterst?tzt"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protokoll wird nicht unterst?tzt"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"Kein Platz im Puffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"Socket ist schon verbunden"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"Socket wird nicht verbunden"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Falsche Protokolloption"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"Verbindungsreset von Peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"Software verursachte Verbindungsabbruch"
#define LOCALIZED_ERROR_NETWORKISDOWN              L"Network ist heruntergefahren"
#define LOCALIZED_ERROR_NETWORKRESET               L"Network wurde wieder gestartet"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"Verbindung verweigert"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"Host ist heruntergefahren"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"Host ist nicht erreichbar"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"Protokoll ist falsch gesetzt f?r Socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Operation wird nicht unterst?tzt auf dem Socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"kein Weg gefunden, um Host zu starten (to remote)"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Zu viele Verweisungen"

#define LOCALIZED_ERROR_POLYSTART               L"PolyStart - Fehler"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"Sie haben schon ein Polygon gestartet"

#define LOCALIZED_ERROR_POLYEND                 L"PolyEnde (PolyEnd) Fehler"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"Sie haben kein Polygon gestartet"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"Sie m?ssen mindestens 3 Vektoren haben, um ein Polygon zu definieren"

#define LOCALIZED_ERROR_SOUND                 L"Sound - Fehler"

#define LOCALIZED_ERROR_MIDI                  L"MIDI Fehler"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"Ung?ltiges MIDI-Interface"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"Schon offen"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"Nicht offen"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"Kein Text im Clipboard"

#define LOCALIZED_ERROR_MCI                   L"MCI Fehler"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Zeitnehmer nicht gefunden"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"Online-Hilfe ist nicht verf?gbar, weil hhctrl.ocx nicht geladen werden konnte." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"Ung?ltige Befehlszeile" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"Die Umgebungsvariable TMP ist nicht definiert oder ung?ltig.\n" LOCALIZED_GENERAL_PRODUCTNAME " wird versuchen C:\\ zu verwenden, um tempor?re Dateien zu speichern"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Generierungs-Problem GIF, ?berpr?fen Sie Speicher und Diskkapazit?t"
#define LOCALIZED_ERROR_GIFREADFAILED         L"Lese-Problem GIF, ?berpr?fen Sie Speicher und Datentr?gerkapazit?t"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"BitMap-Index liegt au?erhalb des Bereiches"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Ausschneiden ohne Erfolg, m?glicherweise nicht gen?gend Speicher vorhanden"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Nichts einzuf?gen" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"BitMap im Index muss mit einem Bitmap initialisiert sein" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"Igel %d hat kein Bild, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"Entschuldigung, es wurde kein Schrifttyp, genannt %s, gefunden.  W?hlen Sie einen im folgenden:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"Druckertreiber unterst?tzt nicht diese Funktion" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"Kann Bild nicht zeichnen"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"Kann Bild nicht extrahieren"
#define LOCALIZED_ERROR_SUBCODE                 L"Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Eingabe:"
#define LOCALIZED_PROMPT_TO     L"Pr-Modus (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   L"Liste-Modus (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  L"Pause-Modus (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  L"Eingabe-Modus (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"Erfolgreich gewechselt nach \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"Kein chdir zum Verzeichnis \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"Gewechselt nach \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Jetzt im neu eingerichteten Verzeichnis \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         L"Verzeichnis \"%s\" nicht einrichtbar" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Verzeichnis \"%s\" gel?scht" 
#define LOCALIZED_FILE_RMDIRFAILED         L"L?schvorgang des Verzeichnisses \"%s\" nicht erfolgreich" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"Das Verzeichnis existiert nicht."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Das Verzeichnis leeren bevor man es zu l?schen versucht."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Logo Bild"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"Aktiver Bereich"
#define LOCALIZED_INFORMATION   L"Information"
#define LOCALIZED_WARNING       L"Achtung"
#define LOCALIZED_UNTITLED      L"Unbetitelt"
#define LOCALIZED_UNKNOWN       L"Unbekannt"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"Ungebunden"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Finden"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Ersetzen"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"%s nicht gefunden"


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
#define LOCALIZED_COLOR_ALICEBLUE             L"AliceBlau"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"AntikWei?"
#define LOCALIZED_COLOR_AQUA                  L"WasserBlau"
#define LOCALIZED_COLOR_AQUAMARINE            L"Aquamarin"
#define LOCALIZED_COLOR_AZURE                 L"Azur"
#define LOCALIZED_COLOR_BEIGE                 L"Beige"
#define LOCALIZED_COLOR_BISQUE                L"Krebs"
#define LOCALIZED_COLOR_BLACK                 L"Schwarz"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"gebleichteMandel"
#define LOCALIZED_COLOR_BLUE                  L"Blau"
#define LOCALIZED_COLOR_BLUEVIOLET            L"BlauViolett"
#define LOCALIZED_COLOR_BROWN                 L"Braun"
#define LOCALIZED_COLOR_BURLYWOOD             L"StammHolz"
#define LOCALIZED_COLOR_CADETBLUE             L"KadettBlau"
#define LOCALIZED_COLOR_CHARTREUSE            L"Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             L"Schokolade"
#define LOCALIZED_COLOR_CORAL                 L"Korallen"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"KornblumenBlau"
#define LOCALIZED_COLOR_CORNSILK              L"KornBraun"
#define LOCALIZED_COLOR_CRIMSON               L"Karmesin"
#define LOCALIZED_COLOR_CYAN                  L"Zyan"
#define LOCALIZED_COLOR_DARKBLUE              L"DunkelBlau"
#define LOCALIZED_COLOR_DARKCYAN              L"DunkelZyan"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"DarkGoldenRod"
#define LOCALIZED_COLOR_DARKGRAY              L"DunkelGrau"
#define LOCALIZED_COLOR_DARKGREEN             L"DunkelGr?n"
#define LOCALIZED_COLOR_DARKGREY              L"DunkelGrau"
#define LOCALIZED_COLOR_DARKKHAKI             L"Khakirot"
#define LOCALIZED_COLOR_DARKMAGENTA           L"DunkelMagenta"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"DunkelOlivGr?n"
#define LOCALIZED_COLOR_DARKORANGE            L"DunkelOrange"
#define LOCALIZED_COLOR_DARKORCHID            L"DunkelOrchidee"
#define LOCALIZED_COLOR_DARKRED               L"DunkelRot"
#define LOCALIZED_COLOR_DARKSALMON            L"DunkelLachs"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"DunkelSeeGr?n"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"DunkelSchieferBlau"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"DunkelSchieferGrau"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"DunkelSchieferGrau"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"DunkelT?rkis"
#define LOCALIZED_COLOR_DARKVIOLET            L"DunkelViolett"
#define LOCALIZED_COLOR_DEEPPINK              L"TiefPink"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"TiefHimmelBlau"
#define LOCALIZED_COLOR_DIMGRAY               L"MattGrau"
#define LOCALIZED_COLOR_DIMGREY               L"MattGrau"
#define LOCALIZED_COLOR_DODGERBLUE            L"DodgerBlau"
#define LOCALIZED_COLOR_FIREBRICK             L"FeuerZiegel"
#define LOCALIZED_COLOR_FLORALWHITE           L"Bl?tenWei?"
#define LOCALIZED_COLOR_FORESTGREEN           L"WaldGr?n"
#define LOCALIZED_COLOR_FUCHSIA               L"Helllila"
#define LOCALIZED_COLOR_GAINSBORO             L"Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            L"GeistWei?"
#define LOCALIZED_COLOR_GOLD                  L"Gold"
#define LOCALIZED_COLOR_GOLDENROD             L"Goldrute"
#define LOCALIZED_COLOR_GRAY                  L"Grau"
#define LOCALIZED_COLOR_GREEN                 L"Gr?n"
#define LOCALIZED_COLOR_GREENYELLOW           L"Gr?ngelb"
#define LOCALIZED_COLOR_GREY                  L"Grau"
#define LOCALIZED_COLOR_HONEYDEW              L"Tau"
#define LOCALIZED_COLOR_HOTPINK               L"Knallpink"
#define LOCALIZED_COLOR_INDIANRED             L"Indischrot"
#define LOCALIZED_COLOR_INDIGO                L"Indigo"
#define LOCALIZED_COLOR_IVORY                 L"Elfenbein"
#define LOCALIZED_COLOR_KHAKI                 L"Khaki"
#define LOCALIZED_COLOR_LAVENDER              L"Lavendel"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"LavendelR?te"
#define LOCALIZED_COLOR_LAWNGREEN             L"RasenGr?n"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"Zitronengelb"
#define LOCALIZED_COLOR_LIGHTBLUE             L"HellBlau"
#define LOCALIZED_COLOR_LIGHTCORAL            L"HellKorallen"
#define LOCALIZED_COLOR_LIGHTCYAN             L"HellZyan"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"SchwimmbadBlau"
#define LOCALIZED_COLOR_LIGHTGRAY             L"HellGrau"
#define LOCALIZED_COLOR_LIGHTGREEN            L"HellGr?n"
#define LOCALIZED_COLOR_LIGHTGREY             L"HellGrau"
#define LOCALIZED_COLOR_LIGHTPINK             L"HellPink"
#define LOCALIZED_COLOR_LIGHTSALMON           L"HellLachs"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"HellSeeGr?n"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"HellHimmelBlau"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"HellSchieferGrau"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"HellSchieferGrau"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"HellStahlBlau"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"HellGelb"
#define LOCALIZED_COLOR_LIME                  L"HellGr?n"
#define LOCALIZED_COLOR_LIMEGREEN             L"KalkGr?n"
#define LOCALIZED_COLOR_LINEN                 L"Leinen"
#define LOCALIZED_COLOR_MAGENTA               L"Magenta"
#define LOCALIZED_COLOR_MAROON                L"Dunkelrot"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"MittelAquaMarin"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"MittelBlau"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"MittelOrchidee"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"MittelPurpurn"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"MittelSeeGr?n"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"MittelSchieferBlau"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"MittelFr?hlingGr?n"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"MittelT?rkis"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"MittelViolettRot"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"MitternachtsBlau"
#define LOCALIZED_COLOR_MINTCREAM             L"MintCreme"
#define LOCALIZED_COLOR_MISTYROSE             L"MistyRose"
#define LOCALIZED_COLOR_MOCCASIN              L"Mokassin"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"Navajowei?"
#define LOCALIZED_COLOR_NAVY                  L"DunkelBlau"
#define LOCALIZED_COLOR_OLDLACE               L"Altespitze"
#define LOCALIZED_COLOR_OLIVE                 L"Oliv"
#define LOCALIZED_COLOR_OLIVEDRAB             L"OlivDRAB"
#define LOCALIZED_COLOR_ORANGE                L"Orange"
#define LOCALIZED_COLOR_ORANGERED             L"OrangeRot"
#define LOCALIZED_COLOR_ORCHID                L"Orchidee"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"PaleGoldenRod"
#define LOCALIZED_COLOR_PALEGREEN             L"BlassGr?n"
#define LOCALIZED_COLOR_PALETURQUOISE         L"BlassT?rkis"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"BlassViolettRot"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"PapayaWhip"
#define LOCALIZED_COLOR_PEACHPUFF             L"ApfelGr?n"
#define LOCALIZED_COLOR_PERU                  L"Peru"
#define LOCALIZED_COLOR_PINK                  L"Pink"
#define LOCALIZED_COLOR_PLUM                  L"Pflaume"
#define LOCALIZED_COLOR_POWDERBLUE            L"PuderBlau"
#define LOCALIZED_COLOR_PURPLE                L"Purpurn"
#define LOCALIZED_COLOR_RED                   L"Rot"
#define LOCALIZED_COLOR_ROSYBROWN             L"PastellBraun"
#define LOCALIZED_COLOR_ROYALBLUE             L"K?nigsBlau"
#define LOCALIZED_COLOR_SADDLEBROWN           L"SattelBraun"
#define LOCALIZED_COLOR_SALMON                L"Lachs"
#define LOCALIZED_COLOR_SANDYBROWN            L"SandBraun"
#define LOCALIZED_COLOR_SEAGREEN              L"SeeGr?n"
#define LOCALIZED_COLOR_SEASHELL              L"MeerMuschel"
#define LOCALIZED_COLOR_SIENNA                L"Siena"
#define LOCALIZED_COLOR_SILVER                L"Silber"
#define LOCALIZED_COLOR_SKYBLUE               L"HimmelBlau"
#define LOCALIZED_COLOR_SLATEBLUE             L"SchieferBlau"
#define LOCALIZED_COLOR_SLATEGRAY             L"SchieferGrau"
#define LOCALIZED_COLOR_SLATEGREY             L"SchieferGrau"
#define LOCALIZED_COLOR_SNOW                  L"Schnee"
#define LOCALIZED_COLOR_SPRINGGREEN           L"Fr?hlingsGr?n"
#define LOCALIZED_COLOR_STEELBLUE             L"StahlBlau"
#define LOCALIZED_COLOR_TAN                   L"Lohe"
#define LOCALIZED_COLOR_TEAL                  L"Gr?nBlau"
#define LOCALIZED_COLOR_THISTLE               L"Distel"
#define LOCALIZED_COLOR_TOMATO                L"TomatenRot"
#define LOCALIZED_COLOR_TURQUOISE             L"T?rkis"
#define LOCALIZED_COLOR_VIOLET                L"Violett"
#define LOCALIZED_COLOR_WHEAT                 L"Weizen"
#define LOCALIZED_COLOR_WHITE                 L"Wei?"
#define LOCALIZED_COLOR_WHITESMOKE            L"RauchWei?"
#define LOCALIZED_COLOR_YELLOW                L"Gelb"
#define LOCALIZED_COLOR_YELLOWGREEN           L"GelbGr?n"

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
