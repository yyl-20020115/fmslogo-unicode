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
// This file contains localized strings for Italian by Stefano Federici and Francesco Simone Carta
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
#define LOCALIZED_ALTERNATE_TRUE     L"vero"
#define LOCALIZED_ALTERNATE_FALSE    L"falso"
#define LOCALIZED_ALTERNATE_END      L"fine"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              L".defmacro"
#define LOCALIZED_ALTERNATE__EQ                    L".uguale"
#define LOCALIZED_ALTERNATE__MACRO                 L".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".forseriporta"
#define LOCALIZED_ALTERNATE__SETBF                 L".asmenpri"
#define LOCALIZED_ALTERNATE__SETFIRST              L".asprimo"
#define LOCALIZED_ALTERNATE__SETITEM               L".aselemento"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"areaattiva"
#define LOCALIZED_ALTERNATE_ALLOPEN                L"arcaperti"
#define LOCALIZED_ALTERNATE_AND                    L"e"
#define LOCALIZED_ALTERNATE_APPLY                  L"applica"
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsen"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"rango"
#define LOCALIZED_ALTERNATE_ARRAY                  L"vettore"
#define LOCALIZED_ALTERNATE_ARRAYP                 L"vettorep"
#define LOCALIZED_ALTERNATE_ARRAY_                 L"vettore?"
#define LOCALIZED_ALTERNATE_ASCII                  L"ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 L"scorriaritmetico"
#define LOCALIZED_ALTERNATE_BACK                   L"indietro"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"barrarovesciatap"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"barrarovesciata?"
#define LOCALIZED_ALTERNATE_BEFOREP                L"primap"
#define LOCALIZED_ALTERNATE_BEFORE_                L"prima?"
#define LOCALIZED_ALTERNATE_BF                     L"mp"
#define LOCALIZED_ALTERNATE_BFS                    L"mpi"
#define LOCALIZED_ALTERNATE_BITAND                 L"bitand"
#define LOCALIZED_ALTERNATE_BITBLOCK               L"bloccodis"
#define LOCALIZED_ALTERNATE_BITCOPY                L"copiadis"
#define LOCALIZED_ALTERNATE_BITCUT                 L"tagliadis"
#define LOCALIZED_ALTERNATE_BITFIT                 L"adattadis"
#define LOCALIZED_ALTERNATE_BITINDEX               L"indicedis"
#define LOCALIZED_ALTERNATE_BITLOAD                L"caricadis"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"caricadisdim"
#define LOCALIZED_ALTERNATE_BITSIZE                L"dimdis"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"tartadis"
#define LOCALIZED_ALTERNATE_BITMODE                L"mododis"
#define LOCALIZED_ALTERNATE_BITNOT                 L"bitnot"
#define LOCALIZED_ALTERNATE_BITOR                  L"bitor"
#define LOCALIZED_ALTERNATE_BITPASTE               L"incolladis"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"incollaindicedis"
#define LOCALIZED_ALTERNATE_BITSAVE                L"salvadis"
#define LOCALIZED_ALTERNATE_BITXOR                 L"bitxor"
#define LOCALIZED_ALTERNATE_BK                     L"i"
#define LOCALIZED_ALTERNATE_BL                     L"mu"
#define LOCALIZED_ALTERNATE_BURIED                 L"nascosto"
#define LOCALIZED_ALTERNATE_BURY                   L"nascondi"
#define LOCALIZED_ALTERNATE_BUTFIRST               L"menpri"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"menprimi"
#define LOCALIZED_ALTERNATE_BUTLAST                L"menult"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"pulsantecrea"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"pulsantecancella"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"pulsanteattiva"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"pulsanteaggiorna"
#define LOCALIZED_ALTERNATE_BUTTONP                L"pulsantep"
#define LOCALIZED_ALTERNATE_BUTTON_                L"pulsante?"
#define LOCALIZED_ALTERNATE_BYE                    L"ciao"
#define LOCALIZED_ALTERNATE_CATCH                  L"acchiappa"
#define LOCALIZED_ALTERNATE_CHAR                   L"car"
#define LOCALIZED_ALTERNATE_CHDIR                  L"chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"casellacrea"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"casellacancella"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"casellaattiva"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"casellavalore"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"casellaassegna"
#define LOCALIZED_ALTERNATE_CLEAN                  L"pulisci"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"puliscipaletta"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"puliscischermo"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"puliscitesto"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"cancetempo"
#define LOCALIZED_ALTERNATE_CLOSE                  L"chiudi"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"chiuditutti"
#define LOCALIZED_ALTERNATE_CO                     L"co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"comboaggiungi"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"combocrea"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"combocancella"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"comboattiva"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"combotogli"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"combotesto"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"comboassegnatesto"
#define LOCALIZED_ALTERNATE_CONTENTS               L"contenuti"
#define LOCALIZED_ALTERNATE_CONTINUE               L"continua"
#define LOCALIZED_ALTERNATE_COPYDEF                L"copiadef"
#define LOCALIZED_ALTERNATE_COS                    L"cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"conta"
#define LOCALIZED_ALTERNATE_CS                     L"ps"
#define LOCALIZED_ALTERNATE_CT                     L"pt"
#define LOCALIZED_ALTERNATE_CURSOR                 L"cursore"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"finestradebug"
#define LOCALIZED_ALTERNATE_DEFINE                 L"definisci"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"definitap"
#define LOCALIZED_ALTERNATE_DEFINED_               L"definita?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"dialogocrea"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"dialogoattiva"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"dialogocancella"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"dialogoaprifile"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"dialogosalvafile"
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"differenza"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"cartelle"
#define LOCALIZED_ALTERNATE_DLLCALL                L"chiamadll"
#define LOCALIZED_ALTERNATE_DLLFREE                L"liberadll"
#define LOCALIZED_ALTERNATE_DLLLOAD                L"caricadll"
#define LOCALIZED_ALTERNATE_DOWN                   L"eg"
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"elevagiu"
#define LOCALIZED_ALTERNATE_DRIBBLE                L"registra"
#define LOCALIZED_ALTERNATE_ED                     L"ed"
#define LOCALIZED_ALTERNATE_EDIT                   L"edita"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"arcoellisse"
#define LOCALIZED_ALTERNATE_EMPTYP                 L"vuotop"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"vuoto?"
#define LOCALIZED_ALTERNATE_EOFP                   L"finefilep"
#define LOCALIZED_ALTERNATE_EOF_                   L"finefile?"
#define LOCALIZED_ALTERNATE_EQUALP                 L"ugualep"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"uguale?"
#define LOCALIZED_ALTERNATE_ER                     L"ca"
#define LOCALIZED_ALTERNATE_ERASE                  L"erase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASEFILE              L"cancellafile"
#define LOCALIZED_ALTERNATE_ERF                    L"caf"
#define LOCALIZED_ALTERNATE_ERROR                  L"errore"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"controllaevento"
#define LOCALIZED_ALTERNATE_EXP                    L"esp"
#define LOCALIZED_ALTERNATE_FD                     L"a"
#define LOCALIZED_ALTERNATE_FENCE                  L"muro"
#define LOCALIZED_ALTERNATE_FILL                   L"riempi"
#define LOCALIZED_ALTERNATE_FILES                  L"catalogo"
#define LOCALIZED_ALTERNATE_FIRST                  L"pri"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"primi"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"coloreriempi"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"nomicaratteri"
#define LOCALIZED_ALTERNATE_FOREVER                L"persempre"
#define LOCALIZED_ALTERNATE_FORM                   L"formato"
#define LOCALIZED_ALTERNATE_FORWARD                L"avanti"
#define LOCALIZED_ALTERNATE_FPUT                   L"inpri"
#define LOCALIZED_ALTERNATE_FS                     L"sp"
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"schermopieno"
#define LOCALIZED_ALTERNATE_FULLTEXT               L"fulltext"
#define LOCALIZED_ALTERNATE_GETFOCUS               L"getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   L"goto"
#define LOCALIZED_ALTERNATE_GIFLOAD                L"caricagif"
#define LOCALIZED_ALTERNATE_GIFSIZE                L"grandezzagif"
#define LOCALIZED_ALTERNATE_GIFSAVE                L"salvagif"
#define LOCALIZED_ALTERNATE_GPROP                  L"prop"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"maggioreougualep"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"maggioreouguale?"
#define LOCALIZED_ALTERNATE_GREATERP               L"maggiorep"
#define LOCALIZED_ALTERNATE_GREATER_               L"maggiore?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"gruppocrea"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"gruppocancella"
#define LOCALIZED_ALTERNATE_HALT                   L"alt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"possiedepennap"
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"possiedepenna?"
#define LOCALIZED_ALTERNATE_HEADING                L"direzione"
#define LOCALIZED_ALTERNATE_HELP                   L"aiuto"
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"nastarta"
#define LOCALIZED_ALTERNATE_HOME                   L"tana"
#define LOCALIZED_ALTERNATE_HT                     L"nt"
#define LOCALIZED_ALTERNATE_IF                     L"se"
#define LOCALIZED_ALTERNATE_IFELSE                 L"seallora"
#define LOCALIZED_ALTERNATE_IFF                    L"sef"
#define LOCALIZED_ALTERNATE_IFFALSE                L"sefalso"
#define LOCALIZED_ALTERNATE_IFT                    L"sev"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"severo"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"inportagiochi"
#define LOCALIZED_ALTERNATE_INPORT                 L"inporta"
#define LOCALIZED_ALTERNATE_INPORTB                L"inportabyte"
#define LOCALIZED_ALTERNATE_INT                    L"intero"
#define LOCALIZED_ALTERNATE_ITEM                   L"elemento"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"tastierano"
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"tastierasi"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"tasto"
#define LOCALIZED_ALTERNATE_KEYP                   L"tastop"
#define LOCALIZED_ALTERNATE_KEY_                   L"tasto?"
#define LOCALIZED_ALTERNATE_LABEL                  L"etichetta"
#define LOCALIZED_ALTERNATE_LABELFONT              L"fontetichetta"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"grandezzaetichetta"
#define LOCALIZED_ALTERNATE_LAST                   L"ultimo"
#define LOCALIZED_ALTERNATE_LEFT                   L"sinistra"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"rolliosinistra"
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"minoreougualep"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"minoreouguale?"
#define LOCALIZED_ALTERNATE_LESSP                  L"minorep"
#define LOCALIZED_ALTERNATE_LESS_                  L"minore?"
#define LOCALIZED_ALTERNATE_LIGHT                  L"luce"
#define LOCALIZED_ALTERNATE_LIST                   L"lista"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"listasceltaaggiungi"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"listasceltacrea"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"listasceltaattiva"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"listasceltacancella"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"listasceltatogli"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"listasceltascegli"
#define LOCALIZED_ALTERNATE_LISTP                  L"listap"
#define LOCALIZED_ALTERNATE_LIST_                  L"lista?"
#define LOCALIZED_ALTERNATE_LN                     L"ln"
#define LOCALIZED_ALTERNATE_LOAD                   L"apri"
#define LOCALIZED_ALTERNATE_LOCAL                  L"locale"
#define LOCALIZED_ALTERNATE_LOG10                  L"log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"versionelogo"
#define LOCALIZED_ALTERNATE_LOWERCASE              L"minuscolo"
#define LOCALIZED_ALTERNATE_LPUT                   L"inult"
#define LOCALIZED_ALTERNATE_LR                     L"rs"
#define LOCALIZED_ALTERNATE_LSHIFT                 L"scorrisin"
#define LOCALIZED_ALTERNATE_LT                     L"s"
#define LOCALIZED_ALTERNATE_MACHINE                L"macchina"
#define LOCALIZED_ALTERNATE_MACROP                 L"macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 L"macro?"
#define LOCALIZED_ALTERNATE_MAKE                   L"assegna"
#define LOCALIZED_ALTERNATE_MCI                    L"mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"membro"
#define LOCALIZED_ALTERNATE_MEMBERP                L"elementop"
#define LOCALIZED_ALTERNATE_MEMBER_                L"elemento?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"messaggio"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"chiudimidi"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"messaggiomidi"
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"aprimidi"
#define LOCALIZED_ALTERNATE_MINUS                  L"minus"
#define LOCALIZED_ALTERNATE_MKDIR                  L"mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 L"modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"disattivamouse"
#define LOCALIZED_ALTERNATE_MOUSEON                L"attivamouse"
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"posizionemouse"
#define LOCALIZED_ALTERNATE_NAMEP                  L"nomep"
#define LOCALIZED_ALTERNATE_NAME_                  L"nome?"
#define LOCALIZED_ALTERNATE_NAMES                  L"nomi"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"reteaccettano"
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"reteaccettasi"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"reteaccettaricevivalore"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"reteaccettainviavalore"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"reteconnettino"
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"reteconnettisi"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"reteconnettiricevivalore"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"reteconnettiinviavalore"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"retechiudi"
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"reteavvia"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"nodisegnotarta"
#define LOCALIZED_ALTERNATE_NODES                  L"nodi"
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"nodirigi"
#define LOCALIZED_ALTERNATE_NOSTATUS               L"nostato"
#define LOCALIZED_ALTERNATE_NOT                    L"non"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"nonugualep"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"nonuguale?"
#define LOCALIZED_ALTERNATE_NOYIELD                L"eventino"
#define LOCALIZED_ALTERNATE_NUMBERP                L"numerop"
#define LOCALIZED_ALTERNATE_NUMBER_                L"numero?"
#define LOCALIZED_ALTERNATE_OP                     L"ri"
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"apriaccoda"
#define LOCALIZED_ALTERNATE_OPENREAD               L"aprilettura"
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"apriaggiorna"
#define LOCALIZED_ALTERNATE_OPENWRITE              L"apriscrittura"
#define LOCALIZED_ALTERNATE_OR                     L"unovero?"
#define LOCALIZED_ALTERNATE_OUTPORT                L"scrivisuporta"
#define LOCALIZED_ALTERNATE_OUTPORTB               L"scrivisuportab"
#define LOCALIZED_ALTERNATE_OUTPUT                 L"riporta"
#define LOCALIZED_ALTERNATE_PARSE                  L"analizza"
#define LOCALIZED_ALTERNATE_PAUSE                  L"pausa"
#define LOCALIZED_ALTERNATE_PC                     L"cp"
#define LOCALIZED_ALTERNATE_PD                     L"giu"
#define LOCALIZED_ALTERNATE_PE                     L"pe" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENCOLOR               L"colpenna"
#define LOCALIZED_ALTERNATE_PENDOWN                L"pennagiu"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"pennagiup"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"pennagiu?"
#define LOCALIZED_ALTERNATE_PENERASE               L"cancella"
#define LOCALIZED_ALTERNATE_PENMODE                L"cancepenna"
#define LOCALIZED_ALTERNATE_PENPAINT               L"pennadisegna"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"motivopenna"
#define LOCALIZED_ALTERNATE_PENREVERSE             L"pennainversa"
#define LOCALIZED_ALTERNATE_PENSIZE                L"trattopenna"
#define LOCALIZED_ALTERNATE_PENUP                  L"sulapenna"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"prospettiva"
#define LOCALIZED_ALTERNATE_PITCH                  L"elevazione"
#define LOCALIZED_ALTERNATE_PIXEL                  L"pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"suovawave"
#define LOCALIZED_ALTERNATE_PLIST                  L"listaprop"
#define LOCALIZED_ALTERNATE_PLISTS                 L"pliste"
#define LOCALIZED_ALTERNATE_PO                     L"sc"
#define LOCALIZED_ALTERNATE_POPDIR                 L"dirsu"
#define LOCALIZED_ALTERNATE_POLYSTART              L"iniziopoli"
#define LOCALIZED_ALTERNATE_POLYEND                L"finepoli"
#define LOCALIZED_ALTERNATE_POLYVIEW               L"vedipoli"
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"chiudiporta"
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"svuotaporta"
#define LOCALIZED_ALTERNATE_PORTMODE               L"modoporta"
#define LOCALIZED_ALTERNATE_PORTOPEN               L"apriporta"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"leggivettoredaporta"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"leggicardaporta"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"scrivivettoresuporta"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"scrivicarsuporta"
#define LOCALIZED_ALTERNATE_POS                    L"pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 L"posxyz"
#define LOCALIZED_ALTERNATE_POT                    L"scp"
#define LOCALIZED_ALTERNATE_POWER                  L"potenza"
#define LOCALIZED_ALTERNATE_PPROP                  L"asprop"
#define LOCALIZED_ALTERNATE_PPT                    L"ped"
#define LOCALIZED_ALTERNATE_PR                     L"st"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"primitivap"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"primitiva?"
#define LOCALIZED_ALTERNATE_PRINT                  L"stampa"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"procedurap"
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"procedura?"
#define LOCALIZED_ALTERNATE_PROPLISTP              L"listapropp"
#define LOCALIZED_ALTERNATE_PROPLIST_              L"listaprop?"
#define LOCALIZED_ALTERNATE_PROCEDURES             L"procedure"
#define LOCALIZED_ALTERNATE_PRODUCT                L"prodotto"
#define LOCALIZED_ALTERNATE_PU                     L"su"
#define LOCALIZED_ALTERNATE_PX                     L"pi"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"finestradomanda"
#define LOCALIZED_ALTERNATE_QUOTIENT               L"quoziente"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"radarcsen"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 L"radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"pulsanteradiocrea"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"pulsanteradioattiva"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"pulsanteradiocancella"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"pulsanteradiovalore"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"pulsanteradioassegna"
#define LOCALIZED_ALTERNATE_RADSIN                 L"radsen"
#define LOCALIZED_ALTERNATE_RADTAN                 L"radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 L"acaso"
#define LOCALIZED_ALTERNATE_RAWASCII               L"rawascii"
#define LOCALIZED_ALTERNATE_RC                     L"lc"
#define LOCALIZED_ALTERNATE_RCS                    L"lcs"
#define LOCALIZED_ALTERNATE_READCHAR               L"leggicar"
#define LOCALIZED_ALTERNATE_READCHARS              L"leggicaratteri"
#define LOCALIZED_ALTERNATE_READER                 L"dacheleggi"
#define LOCALIZED_ALTERNATE_READLIST               L"leggilista"
#define LOCALIZED_ALTERNATE_READPOS                L"poslettura"
#define LOCALIZED_ALTERNATE_READRAWLINE            L"leggirigagrezza"
#define LOCALIZED_ALTERNATE_READWORD               L"leggiparola"
#define LOCALIZED_ALTERNATE_REMAINDER              L"resto"
#define LOCALIZED_ALTERNATE_REMPROP                L"togliprop"
#define LOCALIZED_ALTERNATE_REPCOUNT               L"iterazioni"
#define LOCALIZED_ALTERNATE_REPEAT                 L"ripeti"
#define LOCALIZED_ALTERNATE_RERANDOM               L"riacaso"
#define LOCALIZED_ALTERNATE_RIGHT                  L"destra"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"rolliodestro"
#define LOCALIZED_ALTERNATE_RL                     L"rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  L"eliminadir"
#define LOCALIZED_ALTERNATE_ROLL                   L"rollio"
#define LOCALIZED_ALTERNATE_ROUND                  L"arrotonda"
#define LOCALIZED_ALTERNATE_RR                     L"rd"
#define LOCALIZED_ALTERNATE_RT                     L"d"
#define LOCALIZED_ALTERNATE_RUN                    L"esegui"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"analizzaesegui"
#define LOCALIZED_ALTERNATE_RUNRESULT              L"risultatoesegui"
#define LOCALIZED_ALTERNATE_RW                     L"lp"
#define LOCALIZED_ALTERNATE_SAVE                   L"salva"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"colsfondo"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"barrascorrimentocrea"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"barrascorrimentoattiva"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"barrascorrimentocancella"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"barrascorrimentovalore"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"barrascorrimentoassegna"
#define LOCALIZED_ALTERNATE_SCROLLX                L"scorrix"
#define LOCALIZED_ALTERNATE_SCROLLY                L"scorriy"
#define LOCALIZED_ALTERNATE_SCRUNCH                L"schia"
#define LOCALIZED_ALTERNATE_SE                     L"fr"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"selezione"
#define LOCALIZED_ALTERNATE_SENTENCE               L"frase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"asareaattiva"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"asindicedis"
#define LOCALIZED_ALTERNATE_SETBITMODE             L"asmododis"
#define LOCALIZED_ALTERNATE_SETCLIP                L"assegnaclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              L"setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"ascursorenoattesa"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"ascursoreattesa"
#define LOCALIZED_ALTERNATE_SETFC                  L"ascr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"ascolriempi"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"asfuoco"
#define LOCALIZED_ALTERNATE_SETH                   L"asdir"
#define LOCALIZED_ALTERNATE_SETHEADING             L"asdir"
#define LOCALIZED_ALTERNATE_SETITEM                L"aselem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"asfontetichetta"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"asluce"
#define LOCALIZED_ALTERNATE_SETMARGINS             L"asmargini"
#define LOCALIZED_ALTERNATE_SETPC                  L"ascp"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"ascolpenna"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"asmotivopenna"
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"astrattopenna"
#define LOCALIZED_ALTERNATE_SETPITCH               L"aselevazione"
#define LOCALIZED_ALTERNATE_SETPIXEL               L"aspixel"
#define LOCALIZED_ALTERNATE_SETPOS                 L"aspos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"asposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                L"leggida"
#define LOCALIZED_ALTERNATE_SETREADPOS             L"leggipos"
#define LOCALIZED_ALTERNATE_SETROLL                L"asrollio"
#define LOCALIZED_ALTERNATE_SETSC                  L"ascs"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"ascoloreschermo"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"asschia"
#define LOCALIZED_ALTERNATE_SETTIMER               L"astempo"
#define LOCALIZED_ALTERNATE_SETTURTLE              L"astarta"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"asmodotarta"
#define LOCALIZED_ALTERNATE_SETWRITE               L"scrivisu"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"scrivipos"
#define LOCALIZED_ALTERNATE_SETX                   L"vax"
#define LOCALIZED_ALTERNATE_SETXY                  L"vaxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"vaxyz"
#define LOCALIZED_ALTERNATE_SETY                   L"vay"
#define LOCALIZED_ALTERNATE_SETZ                   L"vaz"
#define LOCALIZED_ALTERNATE_SHELL                  L"shell"
#define LOCALIZED_ALTERNATE_SHOW                   L"mostra"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"inmostra?"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"invista?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"mostarta"
#define LOCALIZED_ALTERNATE_SIN                    L"sen"
#define LOCALIZED_ALTERNATE_SOUND                  L"suona"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"splitscreen"
#define LOCALIZED_ALTERNATE_SQRT                   L"radq"
#define LOCALIZED_ALTERNATE_SS                     L"ss"
#define LOCALIZED_ALTERNATE_ST                     L"mt"
#define LOCALIZED_ALTERNATE_STANDOUT               L"standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           L"etichettacrea"
#define LOCALIZED_ALTERNATE_STATICDELETE           L"etichettacancella"
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"etichettaaggiorna"
#define LOCALIZED_ALTERNATE_STATUS                 L"stato"
#define LOCALIZED_ALTERNATE_STEP                   L"passo"
#define LOCALIZED_ALTERNATE_STEPPED                L"listapassi"
#define LOCALIZED_ALTERNATE_STOP                   L"stop"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"sottostringap"
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"sottostringa?"
#define LOCALIZED_ALTERNATE_SUM                    L"somma"
#define LOCALIZED_ALTERNATE_TAG                    L"tag"
#define LOCALIZED_ALTERNATE_TAN                    L"tan"
#define LOCALIZED_ALTERNATE_TEST                   L"verifica"
#define LOCALIZED_ALTERNATE_TEXT                   L"testo"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"textscreen"
#define LOCALIZED_ALTERNATE_THING                  L"cosa"
#define LOCALIZED_ALTERNATE_THROW                  L"lancia"
#define LOCALIZED_ALTERNATE_TIME                   L"tempo"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"millisec"
#define LOCALIZED_ALTERNATE_TO                     L"per"
#define LOCALIZED_ALTERNATE_TONE                   L"nota"
#define LOCALIZED_ALTERNATE_TOWARDS                L"verso"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"versoxyz"
#define LOCALIZED_ALTERNATE_TRACE                  L"traccia"
#define LOCALIZED_ALTERNATE_TRACED                 L"listatraccia"
#define LOCALIZED_ALTERNATE_TS                     L"ts"
#define LOCALIZED_ALTERNATE_TURTLE                 L"tarta"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"modotarta"
#define LOCALIZED_ALTERNATE_TURTLES                L"maxturta"
#define LOCALIZED_ALTERNATE_TYPE                   L"scrivi"
#define LOCALIZED_ALTERNATE_UNBURY                 L"scopri"
#define LOCALIZED_ALTERNATE_UNSTEP                 L"nopasso"
#define LOCALIZED_ALTERNATE_UNTRACE                L"notraccia"
#define LOCALIZED_ALTERNATE_UP                     L"es"
#define LOCALIZED_ALTERNATE_UPPERCASE              L"maiuscolo"
#define LOCALIZED_ALTERNATE_UPPITCH                L"elevasu"
#define LOCALIZED_ALTERNATE_WAIT                   L"aspetta"
#define LOCALIZED_ALTERNATE_WINDOW                 L"finestra"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"finestracrea"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"finestraattiva"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"finestracancella"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"finestraedita"
#define LOCALIZED_ALTERNATE_WINDOWSET              L"finestraimposta"
#define LOCALIZED_ALTERNATE_WINHELP                L"finestraaiuto"
#define LOCALIZED_ALTERNATE_WORD                   L"parola"
#define LOCALIZED_ALTERNATE_WORDP                  L"parolap"
#define LOCALIZED_ALTERNATE_WORD_                  L"parola?"
#define LOCALIZED_ALTERNATE_WRAP                   L"circolare"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"posscrittura"
#define LOCALIZED_ALTERNATE_WRITER                 L"scritturasu"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"finestrasino"
#define LOCALIZED_ALTERNATE_YIELD                  L"eventisi"
#define LOCALIZED_ALTERNATE_ZOOM                   L"zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"Annulla"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&Applica"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"L'ambiente di programmazione FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&File"
#define LOCALIZED_FILE_NEW              L"&Nuovo\t(cancella Spazio di Lavoro)"
#define LOCALIZED_FILE_LOAD             L"&Carica...\t(aggiunge allo Spazio di Lavoro)"
#define LOCALIZED_FILE_OPEN             L"&Apri...\t(sostituisce Spazio di Lavoro)"
#define LOCALIZED_FILE_SAVE             L"&Salva"
#define LOCALIZED_FILE_SAVEAS           L"Salva con &nome..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"Impostare come Salvaschermo"
#define LOCALIZED_FILE_EDIT             L"&Modifica..."
#define LOCALIZED_FILE_ERASE            L"&Cancella..."
#define LOCALIZED_FILE_EXIT             L"&Esci"

#define LOCALIZED_BITMAP               L"&Disegno"
#define LOCALIZED_BITMAP_NEW           L"&Nuovo"
#define LOCALIZED_BITMAP_LOAD          L"&Carica..."
#define LOCALIZED_BITMAP_SAVE          L"&Salva"
#define LOCALIZED_BITMAP_SAVEAS        L"Salva con &nome..."
#define LOCALIZED_BITMAP_PRINT         L"Stam&pa..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"&Imposta stampante..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"&Area attiva..."

#define LOCALIZED_SET                  L"&Opzioni"
#define LOCALIZED_SET_PENSIZE          L"Dimensione &Penna..."
#define LOCALIZED_SET_LABELFONT        L"Carattere &etichette..."
#define LOCALIZED_SET_COMMANDERFONT    L"Carattere finestra &Comandi..."
#define LOCALIZED_SET_PENCOLOR         L"Co&lore Penna..."
#define LOCALIZED_SET_FLOODCOLOR       L"Colore &Riempimento..."
#define LOCALIZED_SET_SCREENCOLOR      L"Colore &Schermo..."

#define LOCALIZED_ZOOM                 L"&Zoom"
#define LOCALIZED_ZOOM_IN              L"&Ingrandisci"
#define LOCALIZED_ZOOM_OUT             L"&Rimpicciolisci"
#define LOCALIZED_ZOOM_NORMAL          L"&Normale"

#define LOCALIZED_HELP                 L"&Aiuto"
#define LOCALIZED_HELP_INDEX           L"&Indice"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutorial"
#define LOCALIZED_HELP_DEMO            L"&Dimostrazione"
#define LOCALIZED_HELP_EXAMPLE         L"&Esempi"
#define LOCALIZED_HELP_RELEASENOTES    L"Note di &rilascio"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"Informazioni su &" LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"Informazioni su &MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"da Italiano a Inglese"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"English to Italian"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Selezione area di stampa attiva"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"Queste impostazioni agiscono su Salva e Stampa"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-Alto"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Basso"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-Sinistra"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Destra"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"Passi di Tartaruga stampati per pollice:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&Reimposta"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"FMSLogo Screensaver Impostazioni"
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Individuare ..."
#define LOCALIZED_SCREENSAVER_FILE              L"Logo &File:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"Selezionare un'istruzione " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"L'area di lavoro non ha una lista di istruzioni " LOCALIZED_ALTERNATE_STARTUP " definita,\nquindi non succeder? nulla quando viene caricato il salvaschermo.\nSi prega di selezionare una procedura da eseguire quando viene caricato il programma."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"La variabile " LOCALIZED_ALTERNATE_STARTUP " non ? un elenco,\nquindi non succeder? nulla quando viene caricato il salvaschermo.\nSi prega di selezionare una procedura da eseguire quando viene caricato il programma."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"Area di lavoro ha definita in lista istruzioni una vuoto " LOCALIZED_ALTERNATE_STARTUP ", quindi non succeder?? nulla quando viene caricato il salvaschermo.\nSi prega di selezionare una procedura da eseguire quando viene caricato il programma."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"Nessuna procedura ? definita"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"Non esistono procedure, variabili o elenchi di propriet? definiti,\nquindi l'area di lavoro verr? salvato come un file vuoto.\n\nVuoi salvare l'area di lavoro comunque?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Copia"
#define LOCALIZED_POPUP_CUT                      L"Taglia"
#define LOCALIZED_POPUP_PASTE                    L"Incolla"
#define LOCALIZED_POPUP_DELETE                   L"Cancella"
#define LOCALIZED_POPUP_UNDO                     L"Annulla"
#define LOCALIZED_POPUP_REDO                     L"Ripristina"
#define LOCALIZED_POPUP_SELECTALL                L"Seleziona Tutto"
#define LOCALIZED_POPUP_HELP                     L"Cerca Argomento"
#define LOCALIZED_POPUP_REMOVELINES              L"Rimuovi Righe Selezionate"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Editor"

#define LOCALIZED_EDITOR_FILE                    L"&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Salva ed esci\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"Salva su &Cartella"
#define LOCALIZED_EDITOR_FILE_PRINT              L"Stam&pa..."
#define LOCALIZED_EDITOR_FILE_EXIT               L"Esci"

#define LOCALIZED_EDITOR_EDIT                    L"&Modifica"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&Annulla\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&Ripristina\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"&Taglia\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"&Copia\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"&Incolla\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&Elimina\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"Ca&ncella Tutto\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"&Seleziona Tutto\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"&Cerca"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"&Trova...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Sostituisci...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Successivo\tF3"

#define LOCALIZED_EDITOR_SET                     L"&Opzioni"
#define LOCALIZED_EDITOR_SET_FONT                L"&Carattere..."

#define LOCALIZED_EDITOR_TEST                    L"Prova"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"P&rova Selezione\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    L"&Aiuto"
#define LOCALIZED_EDITOR_HELP_INDEX              L"&Indice"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&Cerca Argomento\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Salva e Esci"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&Non Salvare"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"Il contenuto ? stato modificato.  Se esci senza salvare, queste modifiche andranno perse.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"Vorresti salvare le modifiche prima di uscire?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Comandi"
#define LOCALIZED_COMMANDER_HALT                L"Alt"
#define LOCALIZED_COMMANDER_TRACE               L"Traccia"
#define LOCALIZED_COMMANDER_NOTRACE             L"NoTraccia"
#define LOCALIZED_COMMANDER_PAUSE               L"Pausa"
#define LOCALIZED_COMMANDER_STATUS              L"Stato"
#define LOCALIZED_COMMANDER_NOSTATUS            L"NoStato"
#define LOCALIZED_COMMANDER_STEP                L"Passo"
#define LOCALIZED_COMMANDER_UNSTEP              L"NoPasso"
#define LOCALIZED_COMMANDER_RESET               L"Reimposta"
#define LOCALIZED_COMMANDER_EXECUTE             L"Esegui"
#define LOCALIZED_COMMANDER_EDALL               L"EdTutto"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Stato"
#define LOCALIZED_STATUS_PEN                    L"Penna"
#define LOCALIZED_STATUS_CONTACT                L"Contatto:"
#define LOCALIZED_STATUS_WIDTH                  L"Ampiezza:"
#define LOCALIZED_STATUS_STYLE                  L"Stile:"
#define LOCALIZED_STATUS_ORIENTATION            L"Orientamento"
#define LOCALIZED_STATUS_PITCH                  L"Inclinazione:"
#define LOCALIZED_STATUS_HEADING                L"Direzione:"
#define LOCALIZED_STATUS_ROLL                   L"Rotazione:"
#define LOCALIZED_STATUS_TURTLE                 L"Tartaruga"
#define LOCALIZED_STATUS_POSITION               L"Posizione(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Numero:"
#define LOCALIZED_STATUS_VISIBILITY             L"Visibilit?:"
#define LOCALIZED_STATUS_COLOR                  L"Colore"
#define LOCALIZED_STATUS_PENCOLOR               L"Penna(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"Riempimento(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Schermo(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"Kernel"
#define LOCALIZED_STATUS_CALLS                  L"Chiamate:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"Picco Memoria Allocata:"

#define LOCALIZED_STATUS_PENREVERSE     L"Inverso"
#define LOCALIZED_STATUS_PENNORMAL      L"Normale"
#define LOCALIZED_STATUS_PENERASE       L"Cancella"
#define LOCALIZED_STATUS_PENUP          L"Su"
#define LOCALIZED_STATUS_PENDOWN        L"Gi?"
#define LOCALIZED_STATUS_PENSHOWN       L"Visibile"
#define LOCALIZED_STATUS_PENHIDDEN      L"Nascosta"
#define LOCALIZED_STATUS_POLYGONS       L"Poligoni"
#define LOCALIZED_STATUS_VECTORS        L"Vettori"
#define LOCALIZED_STATUS_NODES          L"Nodi"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/D"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&Tutte"
#define LOCALIZED_ERASEPROCEDURE                L"Elimina Procedura"
#define LOCALIZED_EDITPROCEDURE                 L"Modifica Procedura"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Colore"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Colore Penna"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"Colore Riempimento"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Colore Schermo"
#define LOCALIZED_SETCOLOR_RED                 L"Rosso"
#define LOCALIZED_SETCOLOR_GREEN               L"Verde"
#define LOCALIZED_SETCOLOR_BLUE                L"Blu"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Dimensione Penna"
#define LOCALIZED_SETPENSIZE_SIZE              L"Spessore"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"Informazioni su " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"Versione"
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI di George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"Core di Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Installatore basato su Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"The Great Logo Adventure (ISBN 0-9651934-6-2)\nScritto e donato da Jim Muller\nDisponibile a http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Ringrazimenti a Yehuda Katz e Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" ? free software\nVedere la Licenza Pubblica GNU"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"Internet News Group: comp.lang.logo\nVisita il Forum Logo a\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"Traduzione italiana di Stefano Federici, aggiunte e correzioni di Francesco Simone Carta"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"Informazioni su FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS sta per Fight Multiple Sclerosis (Combatti la Sclerosi Multipla)"
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"Ti preghiamo di considerare una donazione a\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"Le modifiche effettuate in questa sessione possono essere perse.\n\nSei sicuro di voler uscire da " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"L'Editor ? gi? in esecuzione"

#define LOCALIZED_COULDNOTWRITEBMP            L"Impossibile scrivere il file .bmp"
#define LOCALIZED_COULDNOTOPENBMP             L"Impossibile aprire il file .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           L"Impossibile creare una bitmap Windows 3.0"
#define LOCALIZED_NOTVALIDBMP                 L"Il file non ? una bitmap Windows 3.0"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"Le modifiche non sono state salvate sul disco"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"L'esecuzione di questo comando canceller? tutte le procedure definite.\n\nConfermi l'esecuzione del comando Nuovo?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"Le definizioni delle procedure definire nel file di cui si ? richiesto il caricamento verranno mescolate alle definizioni gi? presenti nello Spazio di Lavoro\ne potrebbero sovrascrivere eventuali modifiche non ancora salvate.\n\nConfermi l'esecuzione del comando Carica?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"Questa operazioni causer? la perdita di tutte le modifiche non salvate.\n\nConfermi l'esecuzione del comando Apri?"

#define LOCALIZED_EDITORISOPEN                  L"Sapevi di avere un'altra sessione di Editor gi? in esecuzione?\n\nQualunque modifica in questa sessione di Editor non verr? salvata."

#define LOCALIZED_ERROR_CANTREADFILE            L"Impossibile leggere il file \"%s\" dal disco"
#define LOCALIZED_ERROR_CANTWRITEFILE           L"Impossibile scrivere il file \"%s\" sul disco"

#define LOCALIZED_SAVETOWORKSPACE                L"Salva nello Spazio di Lavoro"
#define LOCALIZED_CONTENTSCHANGED                L"Il contenuto ? stato modificato"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"Il contenuto ? stato modificato.\nVuoi salvare le modifiche nello Spazio di Lavoro?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"Il salvataggio del contenuto dell'Editor nello Spazio di Lavoro non ? riuscito.  Il cursose verr? posto subito dopo l'ultima definizione salvata con successo.\n\nControlla l'area Comandi per eventuali messaggi d'errore."
#define LOCALIZED_RETURNTOEDIT                  L"Vuoi tornare all'Editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              L"Errore nel file"
#define LOCALIZED_ERRORINFILEMESSAGE            L"C'? stato un problema durante il caricamento del file \"%s\".\n\nControlla l'elenco Comandi per possibili messaggi di errore.\n\nVuoi aprire l'Editor e vedere l'errore?"

#define LOCALIZED_CANNOTALLOCATESCREEN          L"Impossibile allocare la memoria per la finestra. Potresti avere richiesto altezza e larghezza che eccedono la quantit? di memoria video disponibile.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " impossibile continuare."


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"Scegli il programma Logo da caricare (aggiunge allo Spazio di Lavoro)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"Scegli il programma Logo da aprire (sostituisce lo Spazio di Lavoro)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"Scegli il file in cui salvare lo Spazio di Lavoro"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"Scegli l'immagine da caricare"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"Scegli il file in cui salvare l'area attiva"

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"Tutti i File (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"File Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"File Bitmap (*.bmp)|*.bmp|File GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" ferma\n"
#define LOCALIZED_TRACING_OUTPUTS           L" scrive %s\n"
#define LOCALIZED_TRACING_MAKE              L"Assegna %s %s"
#define LOCALIZED_TRACING_PPROP             L"AsProp %s %s %s"
#define LOCALIZED_TRACING_LOCATION          L" in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Passo Singolo"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s ? stata definita\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"cancella"
#define LOCALIZED_PENMODE_REVERSE  L"inversa"
#define LOCALIZED_PENMODE_PAINT    L"disegna"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: Errore Interno Irreversibile"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Memoria esaurita"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"Memoria esaurita"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"la tartaruga ha superato i confini"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"impossibile inizializzare il modulo grafico"
#define LOCALIZED_ERROR_BADDATA                L"%p non pu? avere %s come argomento"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p non ha prodotto un risultato che invece occorre a %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"argomenti insufficienti per %p"
#define LOCALIZED_ERROR_TOOMUCH                L"superato il numero massimo di oggetti permessi all'interno di ()"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"Non so cosa fare con %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"Troppe (" //
#define LOCALIZED_ERROR_NOVALUE                L"%s non ha valore"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"')' inattesa"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"']' inattesa"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"'}' inattesa"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"Non so come fare %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"Impossibile trovare il tag %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p ? gi? definita"
#define LOCALIZED_ERROR_STOPPING               L"Sto fermando..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"Sto gi? registrando"
#define LOCALIZED_ERROR_FILESYSTEM                   L"Errore del File System: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"Impossibile aprire il file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"Impossibile aprire il file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"File gi? aperto"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"File non aperto"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"Impossibile creare il file dell'Editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"Impossibile eseguire l'Editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"Impossibile leggere il file dell'Editor"
#define LOCALIZED_ERROR_IFWARNING              L"Penso sia SEALTRIMENTI, non SE"
#define LOCALIZED_ERROR_SHADOWWARNING          L"La variabile globale %p ? nascosta da una variabile locale nella procedura chiamata"
#define LOCALIZED_ERROR_USER                   L"Lancia \"Errore"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p ? una primitiva"
#define LOCALIZED_ERROR_TONOTINSIDE            L"Non ? possibile usare PER all'interno di una procedura"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"%p pu? essere usato solo all'interno di una procedura"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"E' necessario trovarsi all'interno di una procedura per usare RIPORTA o STOP"
#define LOCALIZED_ERROR_NOTEST                 L"%p senza VERIFICA"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"La Macro ha restituito %s invece di una lista"
#define LOCALIZED_ERROR_DEEPEND                L"FINE all'interno di un'istruzione multi-riga"
#define LOCALIZED_ERROR_DEEPENDIN              L"FINE FINE all'interno di un'istruzione multi-riga in %p"
#define LOCALIZED_ERROR_UNKNOWN                L"Errore sconosciuto - errore interno."
#define LOCALIZED_PAUSING                      L"In pausa..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Stato non valido per l'istruzione: %p"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"impossibile impostare il modo per una tartaruga con bitmap rotante"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"impossibile creare una tartaruga speciale con una bitmap rotante"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"non posso usare gli appunti come bitmap rotante"
#define LOCALIZED_ERROR_SPECIALFORM                L"a %p non piace %p come argomento perch? ha una forma speciale"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Errore"
#define LOCALIZED_ERROR_BADINPUT             L"Argomento errato"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"I dati inseriti non sono accoppiati correttamente"

#define LOCALIZED_ERROR_CANTOPENPORT         L"Impossibile aprire la porta"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"Impossibile chiudere la porta"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"Impossibile inviare i dati alla porta"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"Impossibile costruire il blocco DCB sulla porta"
#define LOCALIZED_ERROR_CANTSETPORT          L"Impossibile configurare la porta"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"La porta ? gi? aperta"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"La porta non ? aperta"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s esiste gi?"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s non esiste"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"La DLL non ? stata caricata"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"Il caricamento della DLL ? fallito"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Il tipo dell'argomento non ? valido"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Il tipo del risultato non ? valido"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Funzione non trovata"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"Non tutte le coppie Tipo/Dato sono correttamente accoppiate"

#define LOCALIZED_ERROR_NETWORK               L"Errore di rete"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Errore di ricezione dalla rete"
#define LOCALIZED_ERROR_NETWORKSEND           L"Errore di invio alla rete"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Errore inatteso, E' possibile che la connessione di rete sia caduta"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"Non avviata"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"Gi? avviata"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"Gi? attiva"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"Gi? disattivata"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Nome troppo lungo"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"Non inzializzata"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"Il sistema non ? pronto"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"La versione non ? supportata"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"Impossibile inviare i dati dopo la disconnessione"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Chiamata di sistema interrotta"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Risposta Authoritative: Host non trovato"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"Non-Authoritative: Host non trovato. Vedi RETEAVVIA"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Errore irreversibile"
#define LOCALIZED_ERROR_NETWORKNODATA              L"Data Record non disponibile"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"File Number errato"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"Questa operazione causerebbe un blocco"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"L'Operazione ? ora in corso"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"L'Operazione ? gi? in corso"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Indirizzo errato"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Indirizzo di destinazione obbligatorio"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Messaggio troppo lungo"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Famiglia di protocolli non supportata"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"La cartella non ? vuota"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Il limite dell'applicazione ? stato raggiunto"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"La quota di disco ? stata superata"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Troppi file aperti"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Accesso negato"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Richiesta un'operazione di socket su qualcosa che non ? un socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"Impossibile assegnare l'indirizzo richiesto"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"Indirizzo gi? in uso"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"Famiglia di indirizzi non supportata dalla famiglia di protocolli"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Connessione scaduta"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Tipo di socket non supportato"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protocollo non supportato"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"Spazio insufficiente nel buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"Il socket ? gi? connesso"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"Il socket non ? connesso"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Opzioni errata per questo protocollo"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"La connessione ? stata resettata dall'altro computer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"Il programma ha causato la perdita della connessione"
#define LOCALIZED_ERROR_NETWORKISDOWN              L"La connessione di rete non ? attiva"
#define LOCALIZED_ERROR_NETWORKRESET               L"La connessione di rete ? stata resettata"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"La richiesta di connessione ? stat rifiutata"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"L'host non ? attivo"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"L'host non ? raggiungibile"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"Il tipo di protocollo non ? corretto per questo socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Questa operazione non ? supportata da questo socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"L'host remoto non ? raggiungibile"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Troppi riferimenti"

#define LOCALIZED_ERROR_POLYSTART               L"Errore INIZIOPOLI"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"Hai gi? un poligono avviato"

#define LOCALIZED_ERROR_POLYEND                 L"Errore FINEPOLI"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"Non hai iniziato un poligono"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"Devi avere almeno 3 segmenti per definire un poligono"

#define LOCALIZED_ERROR_SOUND                 L"Errore Suono"

#define LOCALIZED_ERROR_MIDI                  L"Errore MIDI"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"Dispositivo MIDI non valido"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"Gi? aperto"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"Gi? chiuso"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"La Clipboard ? vuota"

#define LOCALIZED_ERROR_MCI                   L"Errore MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Timer non trovato"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"Help online non disponibile in quanto non ? stato possibile caricare il file hhctrl.ocx"

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"Linea di comando non valida"

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"La variabile di ambiente TMP non ? definita oppure ? non valida.\n" LOCALIZED_GENERAL_PRODUCTNAME " tenter? di usare C:\\ per memorizzare i file temporanei"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Si ? verificato un problema nella generazione del file GIF, controlla la memoria e lo spazio disponibile sul disco"
#define LOCALIZED_ERROR_GIFREADFAILED         L"Si ? verificato un problema nella lettura del file GIF, controlla la memoria e lo spazio disponibile sul disco"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"Indice BitMap fuori dall'intervallo"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Taglia fallito, E' possibile che non ci sia abbastanza memoria disponibile"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Non c'? niente da incollare"
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"L'indice fornito non ? un indice di BitMap valido"

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"La tartaruga %d non ha una immagine associate e verr? quindi fermata"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"Spiacente ma non ? stato trovato alcun carattere il cui nome sia %s.  Scegli uno dei seguenti caratteri:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"Il driver della stampante non supporta questa funzionalit?"
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"Impossibile disegnare l'immagine"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"Impossibile estrarre l'immagine"
#define LOCALIZED_ERROR_SUBCODE                 L"Codice di errore di Windows"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Immissione:"
#define LOCALIZED_PROMPT_TO     L"Modo PER (Annulla per terminare)"
#define LOCALIZED_PROMPT_LIST   L"Modo Lista (Annulla per terminare)"
#define LOCALIZED_PROMPT_PAUSE  L"Modo Pausa (Annulla per continuare)"
#define LOCALIZED_PROMPT_INPUT  L"Modo Immissione (Annulla per terminare)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"La nuova cartella ? \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"Impossibile chdir nella cartella \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"Salito alla cartella \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Spostato nella nuova cartella \"%s\""
#define LOCALIZED_FILE_MKDIRFAILED         L"Impossibile create la cartella \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Eliminata la cartella \"%s\""
#define LOCALIZED_FILE_RMDIRFAILED         L"Impossibile eliminare la cartella \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"La cartella non eiste."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Assicurarsi che la cartella sia vuota prima di provare ad eliminarla."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Immagine Logo"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"Area Attiva"
#define LOCALIZED_INFORMATION   L"Informazioni"
#define LOCALIZED_WARNING       L"Avviso"
#define LOCALIZED_UNTITLED      L"Senzatitolo"
#define LOCALIZED_UNKNOWN       L"Sconosciuto"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"Non inzializzato"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Trova"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Sostituisci"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"%s non trovato"


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
#define LOCALIZED_COLOR_ALICEBLUE             L"BluAlice"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"BiancoDiTitanio"
#define LOCALIZED_COLOR_AQUA                  L"Acqua"
#define LOCALIZED_COLOR_AQUAMARINE            L"Acquamarina"
#define LOCALIZED_COLOR_AZURE                 L"Azzurro"
#define LOCALIZED_COLOR_BEIGE                 L"Beige"
#define LOCALIZED_COLOR_BISQUE                L"Biscotto"
#define LOCALIZED_COLOR_BLACK                 L"Nero"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"MandorlaBollita"
#define LOCALIZED_COLOR_BLUE                  L"Blu"
#define LOCALIZED_COLOR_BLUEVIOLET            L"IndacoScuro"
#define LOCALIZED_COLOR_BROWN                 L"Marrone"
#define LOCALIZED_COLOR_BURLYWOOD             L"Radica"
#define LOCALIZED_COLOR_CADETBLUE             L"BluCadetto"
#define LOCALIZED_COLOR_CHARTREUSE            L"Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             L"Cioccolato"
#define LOCALIZED_COLOR_CORAL                 L"Corallo"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"BluFiordaliso"
#define LOCALIZED_COLOR_CORNSILK              L"SetaMais"
#define LOCALIZED_COLOR_CRIMSON               L"Cremisi"
#define LOCALIZED_COLOR_CYAN                  L"Ciano"
#define LOCALIZED_COLOR_DARKBLUE              L"BluScuro"
#define LOCALIZED_COLOR_DARKCYAN              L"CianoScuro"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"SolidagoScuro"
#define LOCALIZED_COLOR_DARKGRAY              L"GrigioScuro"
#define LOCALIZED_COLOR_DARKGREEN             L"VerdeScuro"
#define LOCALIZED_COLOR_DARKGREY              L"GrigioScuro"
#define LOCALIZED_COLOR_DARKKHAKI             L"KakiScuro"
#define LOCALIZED_COLOR_DARKMAGENTA           L"MagentaScuro"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"VerdeOlivaScuro"
#define LOCALIZED_COLOR_DARKORANGE            L"ArancioneScuro"
#define LOCALIZED_COLOR_DARKORCHID            L"OrchideaScuro"
#define LOCALIZED_COLOR_DARKRED               L"RossoScuro"
#define LOCALIZED_COLOR_DARKSALMON            L"SalmoneScuro"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"VerdeMarinoScuro"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"BluArdesiaScuro"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"GrigioArdesiaScuro"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"GrigioArdesiaScuro"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"TurcheseScuro"
#define LOCALIZED_COLOR_DARKVIOLET            L"ViolettaScuro"
#define LOCALIZED_COLOR_DEEPPINK              L"RosaProfondo"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"CelesteProfondo"
#define LOCALIZED_COLOR_DIMGRAY               L"GrigioTenue"
#define LOCALIZED_COLOR_DIMGREY               L"GrigioTenue"
#define LOCALIZED_COLOR_DODGERBLUE            L"BluDodger"
#define LOCALIZED_COLOR_FIREBRICK             L"RossoMattone"
#define LOCALIZED_COLOR_FLORALWHITE           L"BiancoFloreale"
#define LOCALIZED_COLOR_FORESTGREEN           L"VerdeForesta"
#define LOCALIZED_COLOR_FUCHSIA               L"Fucsia"
#define LOCALIZED_COLOR_GAINSBORO             L"Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            L"BiancoFantasma"
#define LOCALIZED_COLOR_GOLD                  L"Oro"
#define LOCALIZED_COLOR_GOLDENROD             L"Solidago"
#define LOCALIZED_COLOR_GRAY                  L"Grigio"
#define LOCALIZED_COLOR_GREEN                 L"Verde"
#define LOCALIZED_COLOR_GREENYELLOW           L"VerdeGiallo"
#define LOCALIZED_COLOR_GREY                  L"Grigio"
#define LOCALIZED_COLOR_HONEYDEW              L"MeloneVerde"
#define LOCALIZED_COLOR_HOTPINK               L"RosaCaldo"
#define LOCALIZED_COLOR_INDIANRED             L"Castagno"
#define LOCALIZED_COLOR_INDIGO                L"Indaco"
#define LOCALIZED_COLOR_IVORY                 L"Avorio"
#define LOCALIZED_COLOR_KHAKI                 L"Kaki"
#define LOCALIZED_COLOR_LAVENDER              L"Lavanda"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"LavandaRosata"
#define LOCALIZED_COLOR_LAWNGREEN             L"VerdePrato"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"LimoneCrema"
#define LOCALIZED_COLOR_LIGHTBLUE             L"BluChiaro"
#define LOCALIZED_COLOR_LIGHTCORAL            L"CoralloChiaro"
#define LOCALIZED_COLOR_LIGHTCYAN             L"CianoChiaro"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"SolidagoChiaro"
#define LOCALIZED_COLOR_LIGHTGRAY             L"GrigioChiaro"
#define LOCALIZED_COLOR_LIGHTGREEN            L"VerdeChiaro"
#define LOCALIZED_COLOR_LIGHTGREY             L"GrigioChiaro"
#define LOCALIZED_COLOR_LIGHTPINK             L"RosaChiaro"
#define LOCALIZED_COLOR_LIGHTSALMON           L"SalmoneChiaro"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"VerdemareChiaro"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"CelesteChiaro"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"GrigioArdesiaChiaro"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"GrigioArdesiaChiaro"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"BluAcciaioChiaro"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"GialloChiaro"
#define LOCALIZED_COLOR_LIME                  L"Lime"
#define LOCALIZED_COLOR_LIMEGREEN             L"LimeVerde"
#define LOCALIZED_COLOR_LINEN                 L"Lino"
#define LOCALIZED_COLOR_MAGENTA               L"Magenta"
#define LOCALIZED_COLOR_MAROON                L"Bord?"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"AcquamarinaMedio"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"BluMedio"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"OrchideaMedio"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"ViolaMedio"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"VerdemareMedio"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"BluArdesiaMedio"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"VerdePrimaveraMedio"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"TurcheseMedio"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"RossoViolaceoMedio"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"BluNotte"
#define LOCALIZED_COLOR_MINTCREAM             L"CremaMenta"
#define LOCALIZED_COLOR_MISTYROSE             L"RosaRugiada"
#define LOCALIZED_COLOR_MOCCASIN              L"Mocassino"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"BiancoNavajo"
#define LOCALIZED_COLOR_NAVY                  L"BluMarino"
#define LOCALIZED_COLOR_OLDLACE               L"VecchioPizzo"
#define LOCALIZED_COLOR_OLIVE                 L"VerdeOliva"
#define LOCALIZED_COLOR_OLIVEDRAB             L"VerdeOlivastro"
#define LOCALIZED_COLOR_ORANGE                L"Arancione"
#define LOCALIZED_COLOR_ORANGERED             L"Vermiglione"
#define LOCALIZED_COLOR_ORCHID                L"Orchidea"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"SolidagoPallido"
#define LOCALIZED_COLOR_PALEGREEN             L"VerdePallido"
#define LOCALIZED_COLOR_PALETURQUOISE         L"TurchesePallido"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"RossoViolaceoPallido"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"Papaia"
#define LOCALIZED_COLOR_PEACHPUFF             L"PescaScuro"
#define LOCALIZED_COLOR_PERU                  L"MarroneChiaro"
#define LOCALIZED_COLOR_PINK                  L"Rosa"
#define LOCALIZED_COLOR_PLUM                  L"Prugna"
#define LOCALIZED_COLOR_POWDERBLUE            L"BluPolvere"
#define LOCALIZED_COLOR_PURPLE                L"Viola"
#define LOCALIZED_COLOR_RED                   L"Rosso"
#define LOCALIZED_COLOR_ROSYBROWN             L"MarroneRosato"
#define LOCALIZED_COLOR_ROYALBLUE             L"BluReale"
#define LOCALIZED_COLOR_SADDLEBROWN           L"MarroneSella"
#define LOCALIZED_COLOR_SALMON                L"Salmone"
#define LOCALIZED_COLOR_SANDYBROWN            L"Sabbia"
#define LOCALIZED_COLOR_SEAGREEN              L"VerdeMarino"
#define LOCALIZED_COLOR_SEASHELL              L"Conchiglia"
#define LOCALIZED_COLOR_SIENNA                L"TerraDiSiena"
#define LOCALIZED_COLOR_SILVER                L"Argento"
#define LOCALIZED_COLOR_SKYBLUE               L"Celeste"
#define LOCALIZED_COLOR_SLATEBLUE             L"BluArdesia"
#define LOCALIZED_COLOR_SLATEGRAY             L"GrigioArdesia"
#define LOCALIZED_COLOR_SLATEGREY             L"GrigioArdesia"
#define LOCALIZED_COLOR_SNOW                  L"Neve"
#define LOCALIZED_COLOR_SPRINGGREEN           L"VerdePrimavera"
#define LOCALIZED_COLOR_STEELBLUE             L"BluAcciaio"
#define LOCALIZED_COLOR_TAN                   L"Catrame"
#define LOCALIZED_COLOR_TEAL                  L"BluT?"
#define LOCALIZED_COLOR_THISTLE               L"Cardo"
#define LOCALIZED_COLOR_TOMATO                L"RossoPomodoro"
#define LOCALIZED_COLOR_TURQUOISE             L"Turchese"
#define LOCALIZED_COLOR_VIOLET                L"Violetta"
#define LOCALIZED_COLOR_WHEAT                 L"Grano"
#define LOCALIZED_COLOR_WHITE                 L"Bianco"
#define LOCALIZED_COLOR_WHITESMOKE            L"BiancoFumo"
#define LOCALIZED_COLOR_YELLOW                L"Giallo"
#define LOCALIZED_COLOR_YELLOWGREEN           L"GialloVerde"

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       L"Finestra"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       L"Etichetta"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      L"ListaScelta"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     L"Combo"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       L"Pulsante"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    L"BarraScorrimento"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     L"Gruppo"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  L"PulsanteRadio"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     L"Casella"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       L"Dialogo"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE L"Courier New" // NOT_YET_LOCALIZED
