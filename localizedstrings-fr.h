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
// This file contains localized strings for French by Bertrand CARETTE
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
#define LOCALIZED_ALTERNATE_TRUE     L"vrai"
#define LOCALIZED_ALTERNATE_FALSE    L"faux"
#define LOCALIZED_ALTERNATE_END      L"fin"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              L".d?fmacro" // 
#define LOCALIZED_ALTERNATE__EQ                    L".identique?" // 
#define LOCALIZED_ALTERNATE__MACRO                 L".macro" // 
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".retournepeut?tre" // 
#define LOCALIZED_ALTERNATE__SETBF                 L".fixesp"
#define LOCALIZED_ALTERNATE__SETFIRST              L".fixepremier"
#define LOCALIZED_ALTERNATE__SETITEM               L".fixeitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"zoneactive" 
#define LOCALIZED_ALTERNATE_ALLOPEN                L"fluxouverts" // 
#define LOCALIZED_ALTERNATE_AND                    L"et"
#define LOCALIZED_ALTERNATE_APPLY                  L"applique" // 
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  L"tableau" // 
#define LOCALIZED_ALTERNATE_ARRAYP                 L"tableaup" // 
#define LOCALIZED_ALTERNATE_ARRAY_                 L"tableau?" // 
#define LOCALIZED_ALTERNATE_ASCII                  L"ascii" // 
#define LOCALIZED_ALTERNATE_ASHIFT                 L"d?cale" // 
#define LOCALIZED_ALTERNATE_BACK                   L"recule"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"antislash" // 
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"antislash?" // 
#define LOCALIZED_ALTERNATE_BEFOREP                L"pr?c?dep"
#define LOCALIZED_ALTERNATE_BEFORE_                L"pr?c?de?"
#define LOCALIZED_ALTERNATE_BF                     L"sp"
#define LOCALIZED_ALTERNATE_BFS                    L"sps"
#define LOCALIZED_ALTERNATE_BITAND                 L"etbit" // 
#define LOCALIZED_ALTERNATE_BITBLOCK               L"pav?" // 
#define LOCALIZED_ALTERNATE_BITCOPY                L"copiedessin"
#define LOCALIZED_ALTERNATE_BITCUT                 L"coupedessin"
#define LOCALIZED_ALTERNATE_BITFIT                 L"ajustedessin" // 
#define LOCALIZED_ALTERNATE_BITINDEX               L"indexdessin"
#define LOCALIZED_ALTERNATE_BITLOAD                L"ram?nedessin"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"ram?netailledes"
#define LOCALIZED_ALTERNATE_BITSIZE                L"tailledessin"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"formetortue"
#define LOCALIZED_ALTERNATE_BITMODE                L"modedessin" // 
#define LOCALIZED_ALTERNATE_BITNOT                 L"nonbit" // 
#define LOCALIZED_ALTERNATE_BITOR                  L"oubit" // 
#define LOCALIZED_ALTERNATE_BITPASTE               L"colledessin"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"collesurindex"
#define LOCALIZED_ALTERNATE_BITSAVE                L"sauvedessin"
#define LOCALIZED_ALTERNATE_BITXOR                 L"ouxbit" // 
#define LOCALIZED_ALTERNATE_BK                     L"re"
#define LOCALIZED_ALTERNATE_BL                     L"sd"
#define LOCALIZED_ALTERNATE_BURIED                 L"enterr?es" // 
#define LOCALIZED_ALTERNATE_BURY                   L"enterre" // 
#define LOCALIZED_ALTERNATE_BUTFIRST               L"saufpremier"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"saufpremiers" // 
#define LOCALIZED_ALTERNATE_BUTLAST                L"saufdernier" // 
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"cr?ebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"effacebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"activebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"actualisebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONP                L"boutonp" // 
#define LOCALIZED_ALTERNATE_BUTTON_                L"bouton?" // 
#define LOCALIZED_ALTERNATE_BYE                    L"aurevoir"
#define LOCALIZED_ALTERNATE_CATCH                  L"attrape"
#define LOCALIZED_ALTERNATE_CHAR                   L"car"
#define LOCALIZED_ALTERNATE_CHDIR                  L"chr?p" // 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"cr?ecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"effacecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"activecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"casechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"fixecasechoix" // 
#define LOCALIZED_ALTERNATE_CLEAN                  L"nettoie"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"videpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"vide?cran"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"videtexte"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"videchrono" // 
#define LOCALIZED_ALTERNATE_CLOSE                  L"ferme"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"fermetout"
#define LOCALIZED_ALTERNATE_CO                     L"co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"ajouteitemcombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"cr?ecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"effacecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"activecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"effaceitemcombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"textecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"fixetextecombo" // 
#define LOCALIZED_ALTERNATE_CONTENTS               L"contenu" // 
#define LOCALIZED_ALTERNATE_CONTINUE               L"continue"
#define LOCALIZED_ALTERNATE_COPYDEF                L"donned?f" // 
#define LOCALIZED_ALTERNATE_COS                    L"cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"compte"
#define LOCALIZED_ALTERNATE_CS                     L"v?"
#define LOCALIZED_ALTERNATE_CT                     L"vt"
#define LOCALIZED_ALTERNATE_CURSOR                 L"curseur" // 
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"d?boguefen?tres" // 
#define LOCALIZED_ALTERNATE_DEFINE                 L"d?finis"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"definedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINED_               L"defined?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"cr?edialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"activedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"effacedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"ouvrefichier" // 
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"sauvefichier" // 
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"diff?rence"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"r?pertoires"
#define LOCALIZED_ALTERNATE_DLLCALL                L"appelledll" // 
#define LOCALIZED_ALTERNATE_DLLFREE                L"lib?redll" // 
#define LOCALIZED_ALTERNATE_DLLLOAD                L"chargedll" // 
#define LOCALIZED_ALTERNATE_DOWN                   L"pique" // 
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"pique" // 
#define LOCALIZED_ALTERNATE_DRIBBLE                L"transcription" // 
#define LOCALIZED_ALTERNATE_ED                     L"?d"
#define LOCALIZED_ALTERNATE_EDIT                   L"?dite"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"ellipsearc" // 
#define LOCALIZED_ALTERNATE_EMPTYP                 L"videp"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"vide?"
#define LOCALIZED_ALTERNATE_EOFP                   L"eofp" // 
#define LOCALIZED_ALTERNATE_EOF_                   L"ff?" // 
#define LOCALIZED_ALTERNATE_EQUALP                 L"?galp"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"?gal?"
#define LOCALIZED_ALTERNATE_ER                     L"ef" // 
#define LOCALIZED_ALTERNATE_ERASE                  L"efface"
#define LOCALIZED_ALTERNATE_ERASEFILE              L"effacefichier" // 
#define LOCALIZED_ALTERNATE_ERF                    L"eff" // 
#define LOCALIZED_ALTERNATE_ERROR                  L"erreur"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"test?v" // 
#define LOCALIZED_ALTERNATE_EXP                    L"exp" // 
#define LOCALIZED_ALTERNATE_FD                     L"av"
#define LOCALIZED_ALTERNATE_FENCE                  L"clos"
#define LOCALIZED_ALTERNATE_FILL                   L"remplis"
#define LOCALIZED_ALTERNATE_FILES                  L"fichiers"
#define LOCALIZED_ALTERNATE_FIRST                  L"premier"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"premiers"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"couleurremplissage"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"listepolices" // 
#define LOCALIZED_ALTERNATE_FOREVER                L"pourtoujours" // 
#define LOCALIZED_ALTERNATE_FORM                   L"formate" // 
#define LOCALIZED_ALTERNATE_FORWARD                L"avance"
#define LOCALIZED_ALTERNATE_FPUT                   L"metspremier"
#define LOCALIZED_ALTERNATE_FS                     L"p?c" // 
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"plein?cran" // 
#define LOCALIZED_ALTERNATE_FULLTEXT               L"pleintexte" // 
#define LOCALIZED_ALTERNATE_GETFOCUS               L"focus" // 
#define LOCALIZED_ALTERNATE_GOTO                   L"vavers" // 
#define LOCALIZED_ALTERNATE_GIFLOAD                L"ram?negif" // 
#define LOCALIZED_ALTERNATE_GIFSIZE                L"taillegif" // 
#define LOCALIZED_ALTERNATE_GIFSAVE                L"sauvegif" // 
#define LOCALIZED_ALTERNATE_GPROP                  L"rprop" // 
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"sup?rieur?galp" // 
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"sup?rieur?gal?" // 
#define LOCALIZED_ALTERNATE_GREATERP               L"sup?rieurp" // 
#define LOCALIZED_ALTERNATE_GREATER_               L"sup?rieur?" // 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"cr?egroupe" // 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"effacegroupe" // 
#define LOCALIZED_ALTERNATE_HALT                   L"arr?tetout" // 
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                L"cap" //
#define LOCALIZED_ALTERNATE_HELP                   L"aide" // 
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"cachetortue"
#define LOCALIZED_ALTERNATE_HOME                   L"origine"
#define LOCALIZED_ALTERNATE_HT                     L"ct"
#define LOCALIZED_ALTERNATE_IF                     L"si"
#define LOCALIZED_ALTERNATE_IFELSE                 L"sisinon"
#define LOCALIZED_ALTERNATE_IFF                    L"sif"
#define LOCALIZED_ALTERNATE_IFFALSE                L"sifaux"
#define LOCALIZED_ALTERNATE_IFT                    L"siv"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"sivrai"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"lisportjeu" // 
#define LOCALIZED_ALTERNATE_INPORT                 L"lisport" // 
#define LOCALIZED_ALTERNATE_INPORTB                L"lisportb" // 
#define LOCALIZED_ALTERNATE_INT                    L"tronque"
#define LOCALIZED_ALTERNATE_ITEM                   L"item" // 
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"d?sactiveclavier" //
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"activeclavier" //
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"clavier" //
#define LOCALIZED_ALTERNATE_KEYP                   L"touchep"
#define LOCALIZED_ALTERNATE_KEY_                   L"touche?"
#define LOCALIZED_ALTERNATE_LABEL                  L"?tiquette"
#define LOCALIZED_ALTERNATE_LABELFONT              L"police?tiquette"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"taille?tiquette" // 
#define LOCALIZED_ALTERNATE_LAST                   L"dernier" // 
#define LOCALIZED_ALTERNATE_LEFT                   L"gauche"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"inclinegauche" // 
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"inf?rieur?galp" // 
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"inf?rieur?gal?" // 
#define LOCALIZED_ALTERNATE_LESSP                  L"inf?rieurp" // 
#define LOCALIZED_ALTERNATE_LESS_                  L"inf?rieur?" // 
#define LOCALIZED_ALTERNATE_LIGHT                  L"lumi?re" // 
#define LOCALIZED_ALTERNATE_LIST                   L"liste"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"ajouteitemliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"cr?eliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"activeliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"effaceliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"effaceitemliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"choixliste" // 
#define LOCALIZED_ALTERNATE_LISTP                  L"listep"
#define LOCALIZED_ALTERNATE_LIST_                  L"liste?"
#define LOCALIZED_ALTERNATE_LN                     L"ln" // 
#define LOCALIZED_ALTERNATE_LOAD                   L"ram?ne"
#define LOCALIZED_ALTERNATE_LOCAL                  L"locale"
#define LOCALIZED_ALTERNATE_LOG10                  L"log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"versionlogo" // 
#define LOCALIZED_ALTERNATE_LOWERCASE              L"minuscule"
#define LOCALIZED_ALTERNATE_LPUT                   L"metsdernier"
#define LOCALIZED_ALTERNATE_LR                     L"ig" // 
#define LOCALIZED_ALTERNATE_LSHIFT                 L"d?caleg" // 
#define LOCALIZED_ALTERNATE_LT                     L"ga"
#define LOCALIZED_ALTERNATE_MACHINE                L"machine" // 
#define LOCALIZED_ALTERNATE_MACROP                 L"macrop" // 
#define LOCALIZED_ALTERNATE_MACRO_                 L"macro?" // 
#define LOCALIZED_ALTERNATE_MAKE                   L"donne"
#define LOCALIZED_ALTERNATE_MCI                    L"mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"membre"
#define LOCALIZED_ALTERNATE_MEMBERP                L"membrep"
#define LOCALIZED_ALTERNATE_MEMBER_                L"membre?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"message"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"fermemidi" // 
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"messagemidi" // 
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"ouvremidi" // 
#define LOCALIZED_ALTERNATE_MINUS                  L"moins"
#define LOCALIZED_ALTERNATE_MKDIR                  L"fixer?p" // 
#define LOCALIZED_ALTERNATE_MODULO                 L"modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"d?sactivesouris" // 
#define LOCALIZED_ALTERNATE_MOUSEON                L"activesouris" // 
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"possouris"
#define LOCALIZED_ALTERNATE_NAMEP                  L"nomp"
#define LOCALIZED_ALTERNATE_NAME_                  L"nom?"
#define LOCALIZED_ALTERNATE_NAMES                  L"noms"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"finaccepte" // 
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"accepte" // 
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"accepte.re?u" // 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"accepte.envoy?" // 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"finconnecte" //
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"connecte" //
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"connecte.re?u" // 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"connecte.envoy?" // 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"fermer?seau" // 
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"ouvrer?seau" // 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"finformetortue" // 
#define LOCALIZED_ALTERNATE_NODES                  L"noeuds" // 
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"fintranscription" // 
#define LOCALIZED_ALTERNATE_NOSTATUS               L"ferme?tat" // 
#define LOCALIZED_ALTERNATE_NOT                    L"non"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"non?galp" // 
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"non?gal?" // 
#define LOCALIZED_ALTERNATE_NOYIELD                L"finpartage" // 
#define LOCALIZED_ALTERNATE_NUMBERP                L"nombrep" // 
#define LOCALIZED_ALTERNATE_NUMBER_                L"nombre?" // 
#define LOCALIZED_ALTERNATE_OP                     L"ret" // 
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"ajouteflux" // 
#define LOCALIZED_ALTERNATE_OPENREAD               L"lisflux" // 
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"actualiseflux" // 
#define LOCALIZED_ALTERNATE_OPENWRITE              L"?crisflux" // 
#define LOCALIZED_ALTERNATE_OR                     L"ou" // 
#define LOCALIZED_ALTERNATE_OUTPORT                L"?crisport" // 
#define LOCALIZED_ALTERNATE_OUTPORTB               L"?crisportb" // 
#define LOCALIZED_ALTERNATE_OUTPUT                 L"retourne"
#define LOCALIZED_ALTERNATE_PARSE                  L"analyse" // 
#define LOCALIZED_ALTERNATE_PAUSE                  L"pause" // 
#define LOCALIZED_ALTERNATE_PC                     L"cc"
#define LOCALIZED_ALTERNATE_PD                     L"bc"
#define LOCALIZED_ALTERNATE_PE                     L"go"
#define LOCALIZED_ALTERNATE_PENCOLOR               L"couleurcrayon"
#define LOCALIZED_ALTERNATE_PENDOWN                L"baissecrayon"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"baissecrayonp"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"baissecrayon?"
#define LOCALIZED_ALTERNATE_PENERASE               L"gomme"
#define LOCALIZED_ALTERNATE_PENMODE                L"modecrayon"
#define LOCALIZED_ALTERNATE_PENPAINT               L"dessine"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"motifcrayon" // 
#define LOCALIZED_ALTERNATE_PENREVERSE             L"inversecrayon"
#define LOCALIZED_ALTERNATE_PENSIZE                L"taillecrayon" // 
#define LOCALIZED_ALTERNATE_PENUP                  L"l?vecrayon"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"perspective"
#define LOCALIZED_ALTERNATE_PITCH                  L"cabrement" // 
#define LOCALIZED_ALTERNATE_PIXEL                  L"point"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"jouewave" // 
#define LOCALIZED_ALTERNATE_PLIST                  L"lprop" // 
#define LOCALIZED_ALTERNATE_PLISTS                 L"lprops" // 
#define LOCALIZED_ALTERNATE_PO                     L"im" // 
#define LOCALIZED_ALTERNATE_POPDIR                 L"r?pparent" // 
#define LOCALIZED_ALTERNATE_POLYSTART              L"d?butpoly" // 
#define LOCALIZED_ALTERNATE_POLYEND                L"finpoly" // 
#define LOCALIZED_ALTERNATE_POLYVIEW               L"affichepoly" // 
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"fermeport" // 
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"purgeport" // 
#define LOCALIZED_ALTERNATE_PORTMODE               L"modeport" // 
#define LOCALIZED_ALTERNATE_PORTOPEN               L"ouvreport" // 
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"listableauport" // 
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"liscarport" // 
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"?cristableauport" // 
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"?criscarport" // 
#define LOCALIZED_ALTERNATE_POS                    L"pos" // 
#define LOCALIZED_ALTERNATE_POSXYZ                 L"posxyz" // 
#define LOCALIZED_ALTERNATE_POT                    L"imt" // 
#define LOCALIZED_ALTERNATE_POWER                  L"puissance"
#define LOCALIZED_ALTERNATE_PPROP                  L"dprop" // 
#define LOCALIZED_ALTERNATE_PPT                    L"de"
#define LOCALIZED_ALTERNATE_PR                     L"?c"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"primitive?"
#define LOCALIZED_ALTERNATE_PRINT                  L"?cris"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"proc?durep" // 
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"proc?dure?" // 
#define LOCALIZED_ALTERNATE_PROPLISTP              L"lpropp" // 
#define LOCALIZED_ALTERNATE_PROPLIST_              L"lprop?" // 
#define LOCALIZED_ALTERNATE_PROCEDURES             L"proc?dures" // 
#define LOCALIZED_ALTERNATE_PRODUCT                L"produit"
#define LOCALIZED_ALTERNATE_PU                     L"lc"
#define LOCALIZED_ALTERNATE_PX                     L"ic"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"question" // 
#define LOCALIZED_ALTERNATE_QUOTIENT               L"divise"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 L"radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"cr?eboutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"activeboutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"effaceboutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"boutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"fixeboutonradio" // 
#define LOCALIZED_ALTERNATE_RADSIN                 L"radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 L"radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 L"hasard"
#define LOCALIZED_ALTERNATE_RAWASCII               L"asciibrut" // 
#define LOCALIZED_ALTERNATE_RC                     L"lcar"
#define LOCALIZED_ALTERNATE_RCS                    L"lcars"
#define LOCALIZED_ALTERNATE_READCHAR               L"liscar"
#define LOCALIZED_ALTERNATE_READCHARS              L"liscars"
#define LOCALIZED_ALTERNATE_READER                 L"fluxlecture"
#define LOCALIZED_ALTERNATE_READLIST               L"lisliste"
#define LOCALIZED_ALTERNATE_READPOS                L"poslecture"
#define LOCALIZED_ALTERNATE_READRAWLINE            L"readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               L"lismot"
#define LOCALIZED_ALTERNATE_REMAINDER              L"reste"
#define LOCALIZED_ALTERNATE_REMPROP                L"eprop" // 
#define LOCALIZED_ALTERNATE_REPCOUNT               L"compteur"
#define LOCALIZED_ALTERNATE_REPEAT                 L"r?p?te"
#define LOCALIZED_ALTERNATE_RERANDOM               L"rehasard" // 
#define LOCALIZED_ALTERNATE_RIGHT                  L"droite"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"inclinedroite" // 
#define LOCALIZED_ALTERNATE_RL                     L"ll" // 
#define LOCALIZED_ALTERNATE_RMDIR                  L"efr?p" // 
#define LOCALIZED_ALTERNATE_ROLL                   L"inclinaison" // 
#define LOCALIZED_ALTERNATE_ROUND                  L"arrondis"
#define LOCALIZED_ALTERNATE_RR                     L"id" // 
#define LOCALIZED_ALTERNATE_RT                     L"dr"
#define LOCALIZED_ALTERNATE_RUN                    L"ex?cute"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"ex?cuteanalyse" // 
#define LOCALIZED_ALTERNATE_RUNRESULT              L"ex?cuter?sultat" // 
#define LOCALIZED_ALTERNATE_RW                     L"lm" // 
#define LOCALIZED_ALTERNATE_SAVE                   L"sauve"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"couleurfond" // 
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"cr?eascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"activeascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"effaceascenceur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"ascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"fixeascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLX                L"d?filex" // 
#define LOCALIZED_ALTERNATE_SCROLLY                L"d?filey" // 
#define LOCALIZED_ALTERNATE_SCRUNCH                L"?chelle" // 
#define LOCALIZED_ALTERNATE_SE                     L"ph"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"choix" // 
#define LOCALIZED_ALTERNATE_SENTENCE               L"phrase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"fixezoneactive"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"fixeindexbmp" // 
#define LOCALIZED_ALTERNATE_SETBITMODE             L"fixemodebmp" // 
#define LOCALIZED_ALTERNATE_SETCLIP                L"setclip" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSOR              L"fixecurseur" // 
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"fincurseurattente" // 
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"fixecurseurattente" // 
#define LOCALIZED_ALTERNATE_SETFC                  L"fcr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"fixecouleurremplissage"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"fixefocus" // 
#define LOCALIZED_ALTERNATE_SETH                   L"fcap" // 
#define LOCALIZED_ALTERNATE_SETHEADING             L"fixecap"
#define LOCALIZED_ALTERNATE_SETITEM                L"fixeitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"fixepolice"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"fixelumi?re" // 
#define LOCALIZED_ALTERNATE_SETMARGINS             L"fixemarges" // 
#define LOCALIZED_ALTERNATE_SETPC                  L"fcc"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"fixecouleurcrayon"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"fixemotifcrayon" // 
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"fixetaillecrayon"
#define LOCALIZED_ALTERNATE_SETPITCH               L"fixecabrement" // 
#define LOCALIZED_ALTERNATE_SETPIXEL               L"fixepoint" // 
#define LOCALIZED_ALTERNATE_SETPOS                 L"fixeposition"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"fixepositionxyz"
#define LOCALIZED_ALTERNATE_SETREAD                L"fixelecture" // 
#define LOCALIZED_ALTERNATE_SETREADPOS             L"fixeposlecture" // 
#define LOCALIZED_ALTERNATE_SETROLL                L"fixeinclinaison" // 
#define LOCALIZED_ALTERNATE_SETSC                  L"fcf"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"fixecouleurfond"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"fixe?chelle" // 
#define LOCALIZED_ALTERNATE_SETTIMER               L"fixechrono" // 
#define LOCALIZED_ALTERNATE_SETTURTLE              L"fixetortue"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"fixemodetortue" 
#define LOCALIZED_ALTERNATE_SETWRITE               L"fixe?criture" // 
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"fixepos?criture" // 
#define LOCALIZED_ALTERNATE_SETX                   L"fixex"
#define LOCALIZED_ALTERNATE_SETXY                  L"fixexy"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"fixexyz"
#define LOCALIZED_ALTERNATE_SETY                   L"fixey"
#define LOCALIZED_ALTERNATE_SETZ                   L"fixez"
#define LOCALIZED_ALTERNATE_SHELL                  L"lance" // 
#define LOCALIZED_ALTERNATE_SHOW                   L"montre"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"visiblep"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"visible?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"montretortue"
#define LOCALIZED_ALTERNATE_SIN                    L"sin"
#define LOCALIZED_ALTERNATE_SOUND                  L"son" // 
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"?cranmixte" // 
#define LOCALIZED_ALTERNATE_SQRT                   L"racine"
#define LOCALIZED_ALTERNATE_SS                     L"?cm" // 
#define LOCALIZED_ALTERNATE_ST                     L"mt"
#define LOCALIZED_ALTERNATE_STANDOUT               L"contour" // 
#define LOCALIZED_ALTERNATE_STATICCREATE           L"cr?etexte" // 
#define LOCALIZED_ALTERNATE_STATICDELETE           L"effacetexte" // 
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"actualisetexte" // 
#define LOCALIZED_ALTERNATE_STATUS                 L"?tat" // 
#define LOCALIZED_ALTERNATE_STEP                   L"pas" // 
#define LOCALIZED_ALTERNATE_STEPPED                L"pas?" // 
#define LOCALIZED_ALTERNATE_STOP                   L"arr?te" // 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"appartientp" // 
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"appartient?" // 
#define LOCALIZED_ALTERNATE_SUM                    L"somme"
#define LOCALIZED_ALTERNATE_TAG                    L"balise" // 
#define LOCALIZED_ALTERNATE_TAN                    L"tan"
#define LOCALIZED_ALTERNATE_TEST                   L"teste" // 
#define LOCALIZED_ALTERNATE_TEXT                   L"d?finition" // 
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"?crantexte" // 
#define LOCALIZED_ALTERNATE_THING                  L"chose"
#define LOCALIZED_ALTERNATE_THROW                  L"renvoie"
#define LOCALIZED_ALTERNATE_TIME                   L"temps"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"tempsms" // 
#define LOCALIZED_ALTERNATE_TO                     L"pour"
#define LOCALIZED_ALTERNATE_TONE                   L"ton" // 
#define LOCALIZED_ALTERNATE_TOWARDS                L"vers"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"versxyz"
#define LOCALIZED_ALTERNATE_TRACE                  L"suivi" // 
#define LOCALIZED_ALTERNATE_TRACED                 L"suivi?" // 
#define LOCALIZED_ALTERNATE_TS                     L"?ct" // 
#define LOCALIZED_ALTERNATE_TURTLE                 L"tortue"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"modetortue"
#define LOCALIZED_ALTERNATE_TURTLES                L"tortues"
#define LOCALIZED_ALTERNATE_TYPE                   L"tape"
#define LOCALIZED_ALTERNATE_UNBURY                 L"d?terre" // 
#define LOCALIZED_ALTERNATE_UNSTEP                 L"finpas" // 
#define LOCALIZED_ALTERNATE_UNTRACE                L"finsuivi" // 
#define LOCALIZED_ALTERNATE_UP                     L"cabre" // 
#define LOCALIZED_ALTERNATE_UPPERCASE              L"majuscule"
#define LOCALIZED_ALTERNATE_UPPITCH                L"cabre" // 
#define LOCALIZED_ALTERNATE_WAIT                   L"attends"
#define LOCALIZED_ALTERNATE_WINDOW                 L"fen?tre"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"cr?efen?tre" // 
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"activefen?tre" // 
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"effacefen?tre" // 
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"?ditefichier" // 
#define LOCALIZED_ALTERNATE_WINDOWSET              L"modefen?tre" // 
#define LOCALIZED_ALTERNATE_WINHELP                L"aidewin" // 
#define LOCALIZED_ALTERNATE_WORD                   L"mot"
#define LOCALIZED_ALTERNATE_WORDP                  L"motp"
#define LOCALIZED_ALTERNATE_WORD_                  L"mot?"
#define LOCALIZED_ALTERNATE_WRAP                   L"enroule"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"pos?criture" // 
#define LOCALIZED_ALTERNATE_WRITER                 L"flux?criture"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"choixouinon"
#define LOCALIZED_ALTERNATE_YIELD                  L"partage" // 
#define LOCALIZED_ALTERNATE_ZOOM                   L"zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"Valider"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"Annuler"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&Appliquer"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"L'environnement de programmation FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&Fichier"
#define LOCALIZED_FILE_NEW              L"&Nouveau\t(supprime l'espace de travail)"
#define LOCALIZED_FILE_LOAD             L"&Ram?ne...\t(fusionne avec l'espace de travail)"
#define LOCALIZED_FILE_OPEN             L"&Ouvrir...\t(remplace l'espace de travail)"
#define LOCALIZED_FILE_SAVE             L"&Enregistrer"
#define LOCALIZED_FILE_SAVEAS           L"En&registrer sous..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"&Mettre comme ?conomiseur d'?cran"
#define LOCALIZED_FILE_EDIT             L"E&diter..."
#define LOCALIZED_FILE_ERASE            L"E&ffacer..."
#define LOCALIZED_FILE_EXIT             L"&Quitter"

#define LOCALIZED_BITMAP               L"&Dessin"
#define LOCALIZED_BITMAP_NEW           L"&Nouveau"
#define LOCALIZED_BITMAP_LOAD          L"&Ram?ne..."
#define LOCALIZED_BITMAP_SAVE          L"&Enregistrer"
#define LOCALIZED_BITMAP_SAVEAS        L"En&registrer sous..."
#define LOCALIZED_BITMAP_PRINT         L"&Imprimer..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"&Param?tres Impr...."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"&Zone active..."

#define LOCALIZED_SET                  L"&Options"
#define LOCALIZED_SET_PENSIZE          L"&Taille Crayon..."
#define LOCALIZED_SET_LABELFONT        L"&Police de Caract?res pour ?tiquette..."
#define LOCALIZED_SET_COMMANDERFONT    L"Police de Caract?res du &Poste de Commande..."
#define LOCALIZED_SET_PENCOLOR         L"&Couleur Crayon..."
#define LOCALIZED_SET_FLOODCOLOR       L"Couleur &Remplissage..."
#define LOCALIZED_SET_SCREENCOLOR      L"Couleur &Fond..."

#define LOCALIZED_ZOOM                 L"&Zoom"
#define LOCALIZED_ZOOM_IN              L"&Avant"
#define LOCALIZED_ZOOM_OUT             L"&Arri?re"
#define LOCALIZED_ZOOM_NORMAL          L"&Normal"

#define LOCALIZED_HELP                 L"&Aide"
#define LOCALIZED_HELP_INDEX           L"&Manuel (en Anglais)"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutoriel (en Anglais)"
#define LOCALIZED_HELP_DEMO            L"&D?mo"
#define LOCALIZED_HELP_EXAMPLE         L"&Exemples"
#define LOCALIZED_HELP_RELEASENOTES    L"&Notes M?J"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"&A propos de " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"A &propos de MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"Fran?ais ? Anglais"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"Anglais ? Fran?ais"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Zone active"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"Zone d'impression et de sauvegarde"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-Haut"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Bas"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-Droite"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Gauche"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"Points Tortue par pouce"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&R?Z"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"L'?conomiseur d'?cran de FMSLogo"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"Param?tres de l'?conomiseur d'?cran de FMSLogo"
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Recherchez ..."
#define LOCALIZED_SCREENSAVER_FILE              L"Logo &fichier:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"S?lectionnez une instruction de " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"L'espace de travail n'a pas d'une liste d'instructions de " LOCALIZED_ALTERNATE_STARTUP " d?finie, donc rien\nne se passera lorsque l'?conomiseur d'?cran est charg?.\nVeuillez s?lectionner une proc?dure ? ex?cuter lorsque le programme est charg?."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"La variable " LOCALIZED_ALTERNATE_STARTUP " n'est pas une liste, donc rien\nne se passera lorsque l'?conomiseur d'?cran est charg?.\nVeuillez s?lectionner une proc?dure ? ex?cuter lorsque le programme est charg?."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"Votre espace de travail a une liste d'instructions vide " LOCALIZED_ALTERNATE_STARTUP " d?finie, donc rien\nne se passera lorsque l'?conomiseur d'?cran est charg?.\nVeuillez s?lectionner une proc?dure ? ex?cuter lorsque le programme est charg?."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"Aucuns proc?dures ne sont d?finis"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"Il n'y a aucune proc?dures, variables ou des listes de propri?t? d?finies,\ndonc l'espace de travail sera enregistr? comme un fichier vide.\n\nVous voulez enregistrer l'espace de travail de toute fa?on?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Copier"
#define LOCALIZED_POPUP_CUT                      L"Couper"
#define LOCALIZED_POPUP_PASTE                    L"Coller"
#define LOCALIZED_POPUP_DELETE                   L"Effacer"
#define LOCALIZED_POPUP_UNDO                     L"Annuler"
#define LOCALIZED_POPUP_REDO                     L"R?tablir"
#define LOCALIZED_POPUP_SELECTALL                L"S?lectionner tout"
#define LOCALIZED_POPUP_HELP                     L"Recherche th?matique"
#define LOCALIZED_POPUP_REMOVELINES              L"Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Editeur"

#define LOCALIZED_EDITOR_FILE                    L"&Espace de travail"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Interpr?ter et Quitter\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"E&nregistrer"
#define LOCALIZED_EDITOR_FILE_PRINT              L"&Imprimer..."
#define LOCALIZED_EDITOR_FILE_EXIT               L"&Quitter"

#define LOCALIZED_EDITOR_EDIT                    L"&Edition"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&Annuler frappe\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&R?tablir\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"&Couper\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"C&opier\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"&Coller\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&Effacer\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"E&ffacer Tout\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"&S?lectionner tout\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"&Outils"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"Re&chercher...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Remplacer...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Suivant\tF3"

#define LOCALIZED_EDITOR_SET                     L"&Options"
#define LOCALIZED_EDITOR_SET_FONT                L"&Police..."

#define LOCALIZED_EDITOR_TEST                    L"Test" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    L"&Aide"
#define LOCALIZED_EDITOR_HELP_INDEX              L"&Index" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editeur"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&Recherche th?matique\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Enregistrer et quitter" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&Ne pas enregistrer" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"Il y a des changements non enregistr?s dans l'espace de travail. Si vous quittez sans enregistrer les changements seront perdus.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"Voulez-vous enregistrer les changements avant de quitter?"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Poste de commande"
#define LOCALIZED_COMMANDER_HALT                L"Arr?t"
#define LOCALIZED_COMMANDER_TRACE               L"Suivi"
#define LOCALIZED_COMMANDER_NOTRACE             L"Fin Suivi"
#define LOCALIZED_COMMANDER_PAUSE               L"Pause"
#define LOCALIZED_COMMANDER_STATUS              L"Etat"
#define LOCALIZED_COMMANDER_NOSTATUS            L"Fin Etat"
#define LOCALIZED_COMMANDER_STEP                L"Pas"
#define LOCALIZED_COMMANDER_UNSTEP              L"Fin Pas"
#define LOCALIZED_COMMANDER_RESET               L"R?Z"
#define LOCALIZED_COMMANDER_EXECUTE             L"Ex?cute"
#define LOCALIZED_COMMANDER_EDALL               L"Edite tout" // 

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Etat"
#define LOCALIZED_STATUS_PEN                    L"Crayon"
#define LOCALIZED_STATUS_CONTACT                L"Position:"
#define LOCALIZED_STATUS_WIDTH                  L"Largeur:"
#define LOCALIZED_STATUS_STYLE                  L"Style:"
#define LOCALIZED_STATUS_ORIENTATION            L"Orientation"
#define LOCALIZED_STATUS_PITCH                  L"Cabr:"
#define LOCALIZED_STATUS_HEADING                L"Cap:"
#define LOCALIZED_STATUS_ROLL                   L"Incl:"
#define LOCALIZED_STATUS_TURTLE                 L"Tortue"
#define LOCALIZED_STATUS_POSITION               L"Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Laquelle:"
#define LOCALIZED_STATUS_VISIBILITY             L"Visibilit?:"
#define LOCALIZED_STATUS_COLOR                  L"Couleurs"
#define LOCALIZED_STATUS_PENCOLOR               L"Crayon(RVB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"Remplis(RVB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Ecran(RVB):"
#define LOCALIZED_STATUS_KERNEL                 L"Noyau"
#define LOCALIZED_STATUS_CALLS                  L"Appels:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"M?moire:"

#define LOCALIZED_STATUS_PENREVERSE     L"Inverse"
#define LOCALIZED_STATUS_PENNORMAL      L"Normal"
#define LOCALIZED_STATUS_PENERASE       L"Efface"
#define LOCALIZED_STATUS_PENUP          L"Haut"
#define LOCALIZED_STATUS_PENDOWN        L"Bas"
#define LOCALIZED_STATUS_PENSHOWN       L"Visible"
#define LOCALIZED_STATUS_PENHIDDEN      L"Cach?"
#define LOCALIZED_STATUS_POLYGONS       L"Polygones" // 
#define LOCALIZED_STATUS_VECTORS        L"Vecteurs"
#define LOCALIZED_STATUS_NODES          L"Noeuds"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&Toutes"
#define LOCALIZED_ERASEPROCEDURE                L"Proc?dure ? effacer"
#define LOCALIZED_EDITPROCEDURE                 L"Proc?dure ? ?diter"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Couleur"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Couleur Crayon"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"Couleur de Remplissage"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Couleur Fond"
#define LOCALIZED_SETCOLOR_RED                 L"Rouge"
#define LOCALIZED_SETCOLOR_GREEN               L"Vert"
#define LOCALIZED_SETCOLOR_BLUE                L"Bleu"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Taille Crayon"
#define LOCALIZED_SETPENSIZE_SIZE              L"Dimension"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"A propos de " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"Version" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_CORE                L"Core by Brian Harvey\nUniversity of California Berkeley" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Special thanks to Yehuda Katz and Erich Neuwirth" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" is free software\nSee GNU Public License" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"Adaptation fran?aise partielle de Bertrand Carette" // 
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"A propos de FMS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"Des modifications dans l'?diteur peuvent ?tre perdues.\n\nVoulez-vous vraiment quitter " LOCALIZED_GENERAL_PRODUCTNAME "?" // 
#define LOCALIZED_EDITSESSIONISRUNNING      L"L'?diteur est d?j? ouvert" // 

#define LOCALIZED_COULDNOTWRITEBMP            L"Impossible d'?crire .bmp" //
#define LOCALIZED_COULDNOTOPENBMP             L"Impossible d'ouvrir .bmp" // 
#define LOCALIZED_COULDNOTCREATEBMP           L"Ne peut pas cr?er un bitmap Windows 3.0" // 
#define LOCALIZED_NOTVALIDBMP                 L"Ce n'est pas un bitmap Windows 3.0 valide" // 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"Non enregistr?"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"Nouveau supprime toutes les d?finitions.\n\nContinuer avec nouveau?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"Le fichier sera fusionn? dans l'espace de travail\net peut ?craser des modifications non enregistr?esand may overwrite your unsaved changes.\n\nContinuer le chargement?" // 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"Le chargement du fichier va ?craser l'espace de travail.\n\nContinuer le chargement?"

#define LOCALIZED_EDITORISOPEN                  L"Savez-vous que l'?diteur est ouvert?\n\nDes changements dans cette session ne sont pas enregistr?s." // 

#define LOCALIZED_ERROR_CANTREADFILE            L"Impossible de lire le fichier  \"%s\" sur le disque" // 
#define LOCALIZED_ERROR_CANTWRITEFILE           L"Impossible d'?crire le fichier \"%s\" tsur le disque" // 

#define LOCALIZED_SAVETOWORKSPACE                L"Sauve l'espace de travail"
#define LOCALIZED_CONTENTSCHANGED                L"Changement du contenu"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"Le contenu a ?t? modifi?. Voulez-vous interpr?ter l'espace de travail?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"Le curseur est plac? apr?s la derni?re bonne d?finition.\nRegarder la fen?tre de commande pour le message d'erreur."
#define LOCALIZED_RETURNTOEDIT                  L"Retour ? l'?diteur?"

#define LOCALIZED_EDITFAILEDTOLOAD              L"L'?diteur n'a pas r?ussi le chargement"

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

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"Tous les fichiers (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Fichiers Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"Fichiers Bitmap (*.bmp)|*.bmp|Fichiers GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" arr?te\n"
#define LOCALIZED_TRACING_OUTPUTS           L" sort %s\n"
#define LOCALIZED_TRACING_MAKE              L"Donne %s %s"  // 
#define LOCALIZED_TRACING_PPROP             L"Dprop %s %s %s" // 
#define LOCALIZED_TRACING_LOCATION          L" dans %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Simple pas" // 

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s d?finie\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"erase" //
#define LOCALIZED_PENMODE_REVERSE  L"reverse" // 
#define LOCALIZED_PENMODE_PAINT    L"paint" // 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: erreur interne fatale"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Plus assez de m?moire (fatale)"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"Plus assez de m?moire"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"D?bordement de pile"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"Tortue en dehors des limites"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"Impossible d'initialiser le graphisme"
#define LOCALIZED_ERROR_BADDATA                L"%p n'aime pas l'argument %s"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p ne donne pas de valeur ? %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"Pas assez d'arguments pour %p"
#define LOCALIZED_ERROR_TOOMUCH                L"Trop de choses entre les ( )"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"Vous ne dites pas ce qu'il faut faire de %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"Trop de '('"
#define LOCALIZED_ERROR_NOVALUE                L"%s n'a pas de valeur"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"')' inattendue"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"']' inattendue"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"'}' inattendue"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"Je ne connais pas la proc?dure %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"Pas de ATTRAPE (CATCH) correspondant ? la balise (tag) %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p est d?j? d?finie"
#define LOCALIZED_ERROR_STOPPING               L"Arr?t..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"D?j? en train d'appliquer TRANSCRIPTION (DRIBBLE)"
#define LOCALIZED_ERROR_FILESYSTEM                   L"Erreur syst?me de fichiers: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"Impossible d'ouvrir fichier"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"Impossible d'ouvrir fichier: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"Fichier d?j? ouvert"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"Fichier non ouvert"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"Impossible de cr?er un fichier ?diteur" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"Impossible de lancer l'?diteur"  // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"Impossible de lire un fichier ?diteur"  // 
#define LOCALIZED_ERROR_IFWARNING              L"Vous voulez sans doute dire SISINON (IFELSE) et non SI (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p masqu?e dans un appel de proc?dure"
#define LOCALIZED_ERROR_USER                   L"RENVOIE (THROW) \"Erreur" // 
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p est une primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            L"Impossible d'utiliser POUR (TO) dans une proc?dure"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"Ne peux utiliser %p que dans une proc?dure" // 
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"Ne peux utiliser RETOURNE (OUTPUT) ou ARR?TE (STOP) que dans une proc?dure"
#define LOCALIZED_ERROR_NOTEST                 L"%p sans TESTE (TEST)"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"La macro retourne %s au lieu d'une liste"
#define LOCALIZED_ERROR_DEEPEND                L"FIN (END) dans une instruction multi-ligne"
#define LOCALIZED_ERROR_DEEPENDIN              L"FIN (END) dans une instruction multi-ligne dans %p"
#define LOCALIZED_ERROR_UNKNOWN                L"Unknown error condition - internal error." // NOT_YET_LOCALIZED
#define LOCALIZED_PAUSING                      L"Pause..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                L"%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Erreur"
#define LOCALIZED_ERROR_BADINPUT             L"Entr?e invalide" // 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"Input is not paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTOPENPORT         L"Impossible d'ouvrir le port" // 
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"Impossible de fermer le port" // 
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"Impossible de purger le port" // 
#define LOCALIZED_ERROR_CANTDCBONPORT        L"Could not build dcb on port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTSETPORT          L"Impossible de param?trer le port" // 
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"Le port est d?j? ouvert" // 
#define LOCALIZED_ERROR_PORTNOTOPEN          L"Le port n'est pas ouvert" // 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s existe d?j?"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s n'existe pas"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"DLL non charg?e" // 
#define LOCALIZED_ERROR_DLLLOADFAILED         L"Echec chargement DLL" // 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Type de donn?e en entr?e invalide" //
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Type de donn?e en sortie invalide" // 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Fonction introuvable" // 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK               L"Erreur r?seau" // 
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Erreur r?seau en r?ception" // 
#define LOCALIZED_ERROR_NETWORKSEND           L"Erreur r?seau en ?mission" // 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Erreur inattendue, coupure du r?seau" // 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"Non d?marr?" // 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"D?j? d?marr?" // 
#define LOCALIZED_ERROR_NETWORKALREADYON      L"D?j? connect?" // 
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"D?j? d?connect?" // 

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Nom trop long" // 
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"Non initialis?" // 
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"Le syst?me n'est pas pr?t" // 
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"Cette version n'est pas support?e" // 
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"Envoi impossible apr?s coupure socket" // 
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Appel syst?me interrompu" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Authoritative Answer: Host not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"Non-Authoritative: Host not found. See NETSTARTUP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Erreur irr?cup?rable" // 
#define LOCALIZED_ERROR_NETWORKNODATA              L"Pas d'enregistrement disponible" // 
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"Mauvais num?ro de fichier" //
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"Operation would block" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"Op?ration en cours de d?marrage" // 
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"Op?ration d?j? en cours" // 
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Mauvaise addresse" // 
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Adresse de destination demand?e" // 
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Message trop long" // 
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Famille de protocole non support?e" // 
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"R?pertoire non vide" // 
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Limite de l'application atteinte" // 
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"Quota disque d?pass?" // 
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Trop de fichiers ouverts" // 
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Acc?s refus?"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Socket operation on non-socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"Impossible d'assigner l'adresse demand?e" // 
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"Adresse d?j? utilis?e" // 
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"Address family not supported by protocol family" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Temps de connection d?pass?" // 
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Tye de socket non support?" // 
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protocole non support?" // 
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"Tampon plein" // 
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"Socket d?j? connect?" // 
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"Socket non connect?" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Option de protocole non valide" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"Connection reset by peer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"Le programme a caus? l'abandon de la connection" // 
#define LOCALIZED_ERROR_NETWORKISDOWN              L"Le r?seau est coup?" // 
#define LOCALIZED_ERROR_NETWORKRESET               L"Le r?seau a ?t? r?initialis?" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"Connection refus?e" // 
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"Host is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"Host is unreachable" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"Protocol is wrong type for socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Operation not supported on socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"No path to remote host was found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Trop de r?f?rences" // 

#define LOCALIZED_ERROR_POLYSTART               L"Erreur D?butPoly" // 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"Il y a d?j? un Polygone en cours" // 

#define LOCALIZED_ERROR_POLYEND                 L"Erreur FinPoly" // 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"Aucun Polygone n'est d?marr?" // 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"Il faut au moins 3 vecteurs pour d?finir un polygone"  // 

#define LOCALIZED_ERROR_SOUND                 L"Erreur Son" // 

#define LOCALIZED_ERROR_MIDI                  L"Erreur Midi"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"P?riph?rique MIDI non valide" // 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"D?ja ouvert"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"D?ja ferm?"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"Le presse-papier est vide" // 

#define LOCALIZED_ERROR_MCI                   L"Erreur MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Chrono non trouv?"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"L'aide en ligne n'est pas disponible car hhctrl.ocx ne peut ?tre charg?."  // 

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"Ligne de commande non valide"  // 

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"La variable d'environnement TMP est non d?finie ou non valide.\n" LOCALIZED_GENERAL_PRODUCTNAME " va essayer d'utiliser C:\\ pour stocker les fichiers temporaires" // 

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Probl?me pour cr?er un GIF, v?rifier la m?moire et l'espace disque" // 
#define LOCALIZED_ERROR_GIFREADFAILED         L"Problem Reading GIF, check memory and diskspace" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"Index BitMap hors limite" // 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Echec Coupe, probablement pas assez de m?moire" // 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Rien ? coller"  // 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"BitMap at Index must be initialized with a bitmap"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"La TortueT %d n'a pas d'image, arr?t" // 

#define LOCALIZED_ERROR_FONTNOTFOUND            L"Sorry, no font named %s was found.  Choose one of the following:\n" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"Print driver does not support this function"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"Cannot draw image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"Cannot extract image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SUBCODE                 L"Sub Code" // NOT_YET_LOCALIZED

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Entr?e:"
#define LOCALIZED_PROMPT_TO     L"Mode POUR (TO) - Annuler pour FIN (END)"
#define LOCALIZED_PROMPT_LIST   L"Mode List Annuler pour HALT"
#define LOCALIZED_PROMPT_PAUSE  L"Mode Pause - Annuler pour CONTINUE"
#define LOCALIZED_PROMPT_INPUT  L"Mode Entr?e - Annuler pour HALT"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"Changement vers \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"Impossible changement vers le r?pertoire \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"D?sempiler dans \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Le r?pertoire \"%s\" est cr??"
#define LOCALIZED_FILE_MKDIRFAILED         L"Impossible de cr?er le r?pertoire \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Le r?pertoire \"%s\" est supprim?"
#define LOCALIZED_FILE_RMDIRFAILED         L"Imposible de supprimer le r?pertoire \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"Le r?pertoire n'existe pas"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Le r?pertoire est-il vide?"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Image Logo" // 

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"Zone Active"
#define LOCALIZED_INFORMATION   L"Information" // 
#define LOCALIZED_WARNING       L"Attention" // 
#define LOCALIZED_UNTITLED      L"Sans titre" // 
#define LOCALIZED_UNKNOWN       L"Inconnu" // 

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"nothing" // NOT_YET_LOCALIZED

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Rechercher"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Remplacer"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"'%s' non trouv?"


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
#define LOCALIZED_COLOR_ALICEBLUE             L"Bleu Alice"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"Blanc antique"
#define LOCALIZED_COLOR_AQUA                  L"Vert d'eau"
#define LOCALIZED_COLOR_AQUAMARINE            L"Bleu vert"
#define LOCALIZED_COLOR_AZURE                 L"Azur"
#define LOCALIZED_COLOR_BEIGE                 L"Beige"
#define LOCALIZED_COLOR_BISQUE                L"Bisque"
#define LOCALIZED_COLOR_BLACK                 L"Noir"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"Amande blanchie"
#define LOCALIZED_COLOR_BLUE                  L"Bleu"
#define LOCALIZED_COLOR_BLUEVIOLET            L"Bleu violet"
#define LOCALIZED_COLOR_BROWN                 L"Brun"
#define LOCALIZED_COLOR_BURLYWOOD             L"Bois brut"
#define LOCALIZED_COLOR_CADETBLUE             L"Blue cadet"
#define LOCALIZED_COLOR_CHARTREUSE            L"Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             L"Chocolat"
#define LOCALIZED_COLOR_CORAL                 L"Corail"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"Bleu barbeau"
#define LOCALIZED_COLOR_CORNSILK              L"Barbe de ma?s"
#define LOCALIZED_COLOR_CRIMSON               L"Cramoisi"
#define LOCALIZED_COLOR_CYAN                  L"Cyan"
#define LOCALIZED_COLOR_DARKBLUE              L"Bleu fonc?"
#define LOCALIZED_COLOR_DARKCYAN              L"Cyan fonc?"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"Verge d'or fonc?"
#define LOCALIZED_COLOR_DARKGRAY              L"Gris fonc?"
#define LOCALIZED_COLOR_DARKGREEN             L"Vert fonc?"
#define LOCALIZED_COLOR_DARKGREY              L"Gris fonc?"
#define LOCALIZED_COLOR_DARKKHAKI             L"Kaki fonc?"
#define LOCALIZED_COLOR_DARKMAGENTA           L"Magenta fonc?"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"Olive fonc?"
#define LOCALIZED_COLOR_DARKORANGE            L"Orange fonc?"
#define LOCALIZED_COLOR_DARKORCHID            L"Orchid?e fonc?"
#define LOCALIZED_COLOR_DARKRED               L"Rouge fonc?"
#define LOCALIZED_COLOR_DARKSALMON            L"Saumon fonc?"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"Vert marin fonc?"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"Bleu ardoise fonc?"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"Gris ardoise fonc?"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"Gris ardoise fonc?"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"Turquoise fonc?"
#define LOCALIZED_COLOR_DARKVIOLET            L"Violet fonc?"
#define LOCALIZED_COLOR_DEEPPINK              L"Rose soutenu"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"Bleu ciel intense"
#define LOCALIZED_COLOR_DIMGRAY               L"Gris p?le"
#define LOCALIZED_COLOR_DIMGREY               L"Gris p?le"
#define LOCALIZED_COLOR_DODGERBLUE            L"Bleut?"
#define LOCALIZED_COLOR_FIREBRICK             L"Brique feu"
#define LOCALIZED_COLOR_FLORALWHITE           L"Blanc floral"
#define LOCALIZED_COLOR_FORESTGREEN           L"Vert for?t"
#define LOCALIZED_COLOR_FUCHSIA               L"Fuchsia"
#define LOCALIZED_COLOR_GAINSBORO             L"Gainsborough"
#define LOCALIZED_COLOR_GHOSTWHITE            L"Blanc fant?me"
#define LOCALIZED_COLOR_GOLD                  L"Or"
#define LOCALIZED_COLOR_GOLDENROD             L"Verge d'or"
#define LOCALIZED_COLOR_GRAY                  L"Gris"
#define LOCALIZED_COLOR_GREEN                 L"Vert"
#define LOCALIZED_COLOR_GREENYELLOW           L"Vert jaune"
#define LOCALIZED_COLOR_GREY                  L"Gris"
#define LOCALIZED_COLOR_HONEYDEW              L"Miell?"
#define LOCALIZED_COLOR_HOTPINK               L"Cuisse de nymphe ?mue"
#define LOCALIZED_COLOR_INDIANRED             L"Rouge indien"
#define LOCALIZED_COLOR_INDIGO                L"Indigo"
#define LOCALIZED_COLOR_IVORY                 L"Ivoire"
#define LOCALIZED_COLOR_KHAKI                 L"Kaki"
#define LOCALIZED_COLOR_LAVENDER              L"Lavande"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"Bleu lavande"
#define LOCALIZED_COLOR_LAWNGREEN             L"Vert herbe"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"Mousseline citron"
#define LOCALIZED_COLOR_LIGHTBLUE             L"Bleu clair"
#define LOCALIZED_COLOR_LIGHTCORAL            L"Corail clair"
#define LOCALIZED_COLOR_LIGHTCYAN             L"Cyan clair"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"Verge d'or jaun?tre"
#define LOCALIZED_COLOR_LIGHTGRAY             L"Gris clair"
#define LOCALIZED_COLOR_LIGHTGREEN            L"Vert clair"
#define LOCALIZED_COLOR_LIGHTGREY             L"Gris clair"
#define LOCALIZED_COLOR_LIGHTPINK             L"Rose clair"
#define LOCALIZED_COLOR_LIGHTSALMON           L"Saumon clair"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"Vert marin clair"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"Bleu ciel clair"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"Gris ardoise clair"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"Gris ardoise clair"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"Bleu acier clair"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"Jaune clair"
#define LOCALIZED_COLOR_LIME                  L"Tilleul"
#define LOCALIZED_COLOR_LIMEGREEN             L"Citrone vert"
#define LOCALIZED_COLOR_LINEN                 L"Linon"
#define LOCALIZED_COLOR_MAGENTA               L"Magenta"
#define LOCALIZED_COLOR_MAROON                L"Marron"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"Bleu vert moyen"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"Bleu moyen"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"Orchid?e moyen"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"Pourpre moyen"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"Vert marin moyen"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"Bleu ardoise moyen"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"Vert printemps moyen"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"Turquoise moyen"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"Rouge violet moyen"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"Bleu nuit moyen"
#define LOCALIZED_COLOR_MINTCREAM             L"Creme de menthe"
#define LOCALIZED_COLOR_MISTYROSE             L"Rose fan?"
#define LOCALIZED_COLOR_MOCCASIN              L"Moccasin"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"Blanc navajo"
#define LOCALIZED_COLOR_NAVY                  L"Marine"
#define LOCALIZED_COLOR_OLDLACE               L"Vieille dentelle"
#define LOCALIZED_COLOR_OLIVE                 L"Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             L"Olive terne"
#define LOCALIZED_COLOR_ORANGE                L"Orange"
#define LOCALIZED_COLOR_ORANGERED             L"Rouge orang?"
#define LOCALIZED_COLOR_ORCHID                L"Orchid?e"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"Verge d'or p?le"
#define LOCALIZED_COLOR_PALEGREEN             L"Vert p?le"
#define LOCALIZED_COLOR_PALETURQUOISE         L"Turquoise p?le"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"Rouge violet p?le"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"Mousse a la papaye"
#define LOCALIZED_COLOR_PEACHPUFF             L"Fleur de p?cher"
#define LOCALIZED_COLOR_PERU                  L"P?rou"
#define LOCALIZED_COLOR_PINK                  L"Rose"
#define LOCALIZED_COLOR_PLUM                  L"Prune"
#define LOCALIZED_COLOR_POWDERBLUE            L"Bleu l?ger"
#define LOCALIZED_COLOR_PURPLE                L"Pourpre"
#define LOCALIZED_COLOR_RED                   L"Rouge"
#define LOCALIZED_COLOR_ROSYBROWN             L"Brun ros?"
#define LOCALIZED_COLOR_ROYALBLUE             L"Bleu roi"
#define LOCALIZED_COLOR_SADDLEBROWN           L"Brun selle"
#define LOCALIZED_COLOR_SALMON                L"Saumon"
#define LOCALIZED_COLOR_SANDYBROWN            L"Brun sable"
#define LOCALIZED_COLOR_SEAGREEN              L"Vert marin"
#define LOCALIZED_COLOR_SEASHELL              L"Coquillage"
#define LOCALIZED_COLOR_SIENNA                L"Terre de Sienne"
#define LOCALIZED_COLOR_SILVER                L"Argent"
#define LOCALIZED_COLOR_SKYBLUE               L"Bleu ciel"
#define LOCALIZED_COLOR_SLATEBLUE             L"Bleu ardoise"
#define LOCALIZED_COLOR_SLATEGRAY             L"Gris ardoise"
#define LOCALIZED_COLOR_SLATEGREY             L"Gris ardoise"
#define LOCALIZED_COLOR_SNOW                  L"Neige"
#define LOCALIZED_COLOR_SPRINGGREEN           L"Vert printemps"
#define LOCALIZED_COLOR_STEELBLUE             L"Bleu acier"
#define LOCALIZED_COLOR_TAN                   L"Tan"
#define LOCALIZED_COLOR_TEAL                  L"Sarcelle"
#define LOCALIZED_COLOR_THISTLE               L"Chardon"
#define LOCALIZED_COLOR_TOMATO                L"Tomate"
#define LOCALIZED_COLOR_TURQUOISE             L"Turquoise"
#define LOCALIZED_COLOR_VIOLET                L"Violet"
#define LOCALIZED_COLOR_WHEAT                 L"Froment"
#define LOCALIZED_COLOR_WHITE                 L"Blanc"
#define LOCALIZED_COLOR_WHITESMOKE            L"Fum?e blanche"
#define LOCALIZED_COLOR_YELLOW                L"Jaune"
#define LOCALIZED_COLOR_YELLOWGREEN           L"Jaune vert"

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
