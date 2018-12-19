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
// This file contains localized strings for Spanish by Daniel Ajoy
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
#define LOCALIZED_ALTERNATE_TRUE     L"cierto"
#define LOCALIZED_ALTERNATE_FALSE    L"falso"
#define LOCALIZED_ALTERNATE_END      L"fin"
#define LOCALIZED_ALTERNATE_TOPLEVEL L"toplevel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SYSTEM   L"system" // NOT_YET_LOCALIZED

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    L"IgnoraMayusculas?"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              L".defMacro"
#define LOCALIZED_ALTERNATE__EQ                    L".ig"
#define LOCALIZED_ALTERNATE__MACRO                 L".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".quizaDevuelve"
#define LOCALIZED_ALTERNATE__SETBF                 L".ponMP"
#define LOCALIZED_ALTERNATE__SETFIRST              L".ponPrimero"
#define LOCALIZED_ALTERNATE__SETITEM               L".ponElemento"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"areaActiva"
#define LOCALIZED_ALTERNATE_ALLOPEN                L"abiertos"
#define LOCALIZED_ALTERNATE_AND                    L"y"
#define LOCALIZED_ALTERNATE_APPLY                  L"aplica"
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsen"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  L"vector"
#define LOCALIZED_ALTERNATE_ARRAYP                 L"vector?"
#define LOCALIZED_ALTERNATE_ARRAY_                 L"vector?"
#define LOCALIZED_ALTERNATE_ASCII                  L"ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 L"desplaza"
#define LOCALIZED_ALTERNATE_BACK                   L"retrocede"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"tieneBarra?"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"tieneBarra?"
#define LOCALIZED_ALTERNATE_BEFOREP                L"anterior?"
#define LOCALIZED_ALTERNATE_BEFORE_                L"anterior?"
#define LOCALIZED_ALTERNATE_BF                     L"mp"
#define LOCALIZED_ALTERNATE_BFS                    L"mps"
#define LOCALIZED_ALTERNATE_BITAND                 L"bitand" // "bity"
#define LOCALIZED_ALTERNATE_BITBLOCK               L"rectanguloRelleno"
#define LOCALIZED_ALTERNATE_BITCOPY                L"copiaArea"
#define LOCALIZED_ALTERNATE_BITCUT                 L"cortaArea"
#define LOCALIZED_ALTERNATE_BITFIT                 L"ajusta"
#define LOCALIZED_ALTERNATE_BITINDEX               L"indiceImagen"
#define LOCALIZED_ALTERNATE_BITLOAD                L"cargaDib"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"tama?oCargaDib"
#define LOCALIZED_ALTERNATE_BITSIZE                L"tama?oDibujo"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"ponForma" // "ponformatortuga"
#define LOCALIZED_ALTERNATE_BITMODE                L"modoBitmap?"
#define LOCALIZED_ALTERNATE_BITNOT                 L"bitNot" // "bitinverso"
#define LOCALIZED_ALTERNATE_BITOR                  L"bitOr" // "bito"
#define LOCALIZED_ALTERNATE_BITPASTE               L"bitPega" // "pega"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"bitPegaEnIndice" // "pegaenindice"
#define LOCALIZED_ALTERNATE_BITSAVE                L"guardaDib"
#define LOCALIZED_ALTERNATE_BITXOR                 L"bitXor"
#define LOCALIZED_ALTERNATE_BK                     L"re"
#define LOCALIZED_ALTERNATE_BL                     L"mu"
#define LOCALIZED_ALTERNATE_BURIED                 L"tapado"
#define LOCALIZED_ALTERNATE_BURY                   L"tapa"
#define LOCALIZED_ALTERNATE_BUTFIRST               L"menosPrimero"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"menosPrimeros"
#define LOCALIZED_ALTERNATE_BUTLAST                L"menosUltimo"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"creaBoton"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"borraBoton"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"habilitaBoton"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"actualizaBoton"
#define LOCALIZED_ALTERNATE_BUTTONP                L"boton?"
#define LOCALIZED_ALTERNATE_BUTTON_                L"boton?"
#define LOCALIZED_ALTERNATE_BYE                    L"adios"
#define LOCALIZED_ALTERNATE_CATCH                  L"atrapa" // "coge"
#define LOCALIZED_ALTERNATE_CHAR                   L"car"
#define LOCALIZED_ALTERNATE_CHDIR                  L"cambiaDir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"creaCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"borraCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"habilitaCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"estadoCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"ponCheckbox"
#define LOCALIZED_ALTERNATE_CLEAN                  L"limpia"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"borraPaleta"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"borraPantalla"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"borraTexto"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"temporizadorACero"
#define LOCALIZED_ALTERNATE_CLOSE                  L"cierra"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"cierraTodo"
#define LOCALIZED_ALTERNATE_CO                     L"co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"a?adeLineaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"creaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"borraCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"habilitaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"borralineaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"leetextoCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"pontextoCombobox"
#define LOCALIZED_ALTERNATE_CONTENTS               L"contenido"
#define LOCALIZED_ALTERNATE_CONTINUE               L"sigue"
#define LOCALIZED_ALTERNATE_COPYDEF                L"copiaDef"
#define LOCALIZED_ALTERNATE_COS                    L"cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"cuenta"
#define LOCALIZED_ALTERNATE_CS                     L"bp"
#define LOCALIZED_ALTERNATE_CT                     L"bt"
#define LOCALIZED_ALTERNATE_CURSOR                 L"cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"ventanaDepurador"
#define LOCALIZED_ALTERNATE_DEFINE                 L"define"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"definido?"
#define LOCALIZED_ALTERNATE_DEFINED_               L"definido?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"creaDialogo"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"habilitaDialogo"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"borraDialogo"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"abreDialogo"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"guardaDialogo"
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"diferencia"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"directorios"
#define LOCALIZED_ALTERNATE_DLLCALL                L"llamaDLL"
#define LOCALIZED_ALTERNATE_DLLFREE                L"quitaDLL"
#define LOCALIZED_ALTERNATE_DLLLOAD                L"cargaDLL"
#define LOCALIZED_ALTERNATE_DOWN                   L"abajo"
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"bajaNariz"
#define LOCALIZED_ALTERNATE_DRIBBLE                L"eco"
#define LOCALIZED_ALTERNATE_ED                     L"ed"
#define LOCALIZED_ALTERNATE_EDIT                   L"edita"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"arcoElipse"
#define LOCALIZED_ALTERNATE_EMPTYP                 L"vacio?"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"vacio?"
#define LOCALIZED_ALTERNATE_EOFP                   L"finlec?"
#define LOCALIZED_ALTERNATE_EOF_                   L"finlec?"
#define LOCALIZED_ALTERNATE_EQUALP                 L"iguales?"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"iguales?"
#define LOCALIZED_ALTERNATE_ER                     L"bo"
#define LOCALIZED_ALTERNATE_ERASE                  L"borra"
#define LOCALIZED_ALTERNATE_ERASEFILE              L"borraArchivo"
#define LOCALIZED_ALTERNATE_ERF                    L"boArchivo"
#define LOCALIZED_ALTERNATE_ERROR                  L"error"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"siEvento"
#define LOCALIZED_ALTERNATE_EXP                    L"exp"
#define LOCALIZED_ALTERNATE_FD                     L"av"
#define LOCALIZED_ALTERNATE_FENCE                  L"modoJaula"
#define LOCALIZED_ALTERNATE_FILL                   L"rellena"
#define LOCALIZED_ALTERNATE_FILES                  L"listaArchivos" // "listaarch"
#define LOCALIZED_ALTERNATE_FIRST                  L"primero"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"primeros"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"colorRelleno"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"tiposDeLetra"
#define LOCALIZED_ALTERNATE_FOREVER                L"siempre"
#define LOCALIZED_ALTERNATE_FORM                   L"formatoNumero"
#define LOCALIZED_ALTERNATE_FORWARD                L"avanza"
#define LOCALIZED_ALTERNATE_FPUT                   L"ponPrimero"
#define LOCALIZED_ALTERNATE_FS                     L"pg"
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"pantallaGrafica"
#define LOCALIZED_ALTERNATE_FULLTEXT               L"textoCompleto"
#define LOCALIZED_ALTERNATE_GETFOCUS               L"leeFoco"
#define LOCALIZED_ALTERNATE_GOTO                   L"saltoA"
#define LOCALIZED_ALTERNATE_GIFLOAD                L"cargaGif"
#define LOCALIZED_ALTERNATE_GIFSIZE                L"tama?oGif"
#define LOCALIZED_ALTERNATE_GIFSAVE                L"guardaGif"
#define LOCALIZED_ALTERNATE_GPROP                  L"propiedad"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"mayorOigual?"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"mayorOigual?"
#define LOCALIZED_ALTERNATE_GREATERP               L"mayor?"
#define LOCALIZED_ALTERNATE_GREATER_               L"mayor?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"creaGroupbox"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"borraGroupbox"
#define LOCALIZED_ALTERNATE_HALT                   L"halt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                L"rumbo"
#define LOCALIZED_ALTERNATE_HELP                   L"ayuda"
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"ocultaTortuga"
#define LOCALIZED_ALTERNATE_HOME                   L"centro"
#define LOCALIZED_ALTERNATE_HT                     L"ot"
#define LOCALIZED_ALTERNATE_IF                     L"si"
#define LOCALIZED_ALTERNATE_IFELSE                 L"siSino"
#define LOCALIZED_ALTERNATE_IFF                    L"siFalso"
#define LOCALIZED_ALTERNATE_IFFALSE                L"siFalso"
#define LOCALIZED_ALTERNATE_IFT                    L"sicierto"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"sicierto"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"leePuertoJuego"
#define LOCALIZED_ALTERNATE_INPORT                 L"leePuerto2"
#define LOCALIZED_ALTERNATE_INPORTB                L"leePuerto"
#define LOCALIZED_ALTERNATE_INT                    L"entero"
#define LOCALIZED_ALTERNATE_ITEM                   L"elemento"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"inHabilitaTeclado"
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"habilitaTeclado"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"leeTecla" // "leecar"
#define LOCALIZED_ALTERNATE_KEYP                   L"tecla?" // "tecla"
#define LOCALIZED_ALTERNATE_KEY_                   L"tecla?"
#define LOCALIZED_ALTERNATE_LABEL                  L"rotulo"
#define LOCALIZED_ALTERNATE_LABELFONT              L"tipo"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"rotuloTam"
#define LOCALIZED_ALTERNATE_LAST                   L"ultimo"
#define LOCALIZED_ALTERNATE_LEFT                   L"giraIzquierda"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"balanceaIzquierda"
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"menorOigual?"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"menorOigual?"
#define LOCALIZED_ALTERNATE_LESSP                  L"menor?"
#define LOCALIZED_ALTERNATE_LESS_                  L"menor?"
#define LOCALIZED_ALTERNATE_LIGHT                  L"luz"
#define LOCALIZED_ALTERNATE_LIST                   L"lista"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"a?adeCadenaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"creaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"habilitaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"borraListbox"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"borraCadenaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"leeSeleccionListbox"
#define LOCALIZED_ALTERNATE_LISTP                  L"lista?"
#define LOCALIZED_ALTERNATE_LIST_                  L"lista?"
#define LOCALIZED_ALTERNATE_LN                     L"ln"
#define LOCALIZED_ALTERNATE_LOAD                   L"carga"
#define LOCALIZED_ALTERNATE_LOCAL                  L"local"
#define LOCALIZED_ALTERNATE_LOG10                  L"log"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"versionLogo"
#define LOCALIZED_ALTERNATE_LOWERCASE              L"minusculas"
#define LOCALIZED_ALTERNATE_LPUT                   L"ponUltimo"
#define LOCALIZED_ALTERNATE_LR                     L"bi"
#define LOCALIZED_ALTERNATE_LSHIFT                 L"desplazaIzquierda"
#define LOCALIZED_ALTERNATE_LT                     L"gi"
#define LOCALIZED_ALTERNATE_MACHINE                L"sistema"
#define LOCALIZED_ALTERNATE_MACROP                 L"macro?"
#define LOCALIZED_ALTERNATE_MACRO_                 L"macro?"
#define LOCALIZED_ALTERNATE_MAKE                   L"haz"
#define LOCALIZED_ALTERNATE_MCI                    L"mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"miembro"
#define LOCALIZED_ALTERNATE_MEMBERP                L"miembro?"
#define LOCALIZED_ALTERNATE_MEMBER_                L"miembro?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"mensaje"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"cierraMidi"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"mensajeMidi"
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"abreMidi"
#define LOCALIZED_ALTERNATE_MINUS                  L"cambiaSigno"
#define LOCALIZED_ALTERNATE_MKDIR                  L"creaDir"
#define LOCALIZED_ALTERNATE_MODULO                 L"modulo" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"inHabilitaRaton"
#define LOCALIZED_ALTERNATE_MOUSEON                L"habilitaRaton"
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"posRaton"
#define LOCALIZED_ALTERNATE_NAMEP                  L"var?"
#define LOCALIZED_ALTERNATE_NAME_                  L"var?"
#define LOCALIZED_ALTERNATE_NAMES                  L"lVars"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"inhabilitaAceptaRed"
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"habilitaAceptaRed"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"recibeValorAceptaRed"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"enviaValorAceptaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"inhabilitaConectaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"habilitaConectaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"recibeValorConectaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"enviaValorConectaRed"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"finRed"
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"iniciaRed"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"quitaForma"
#define LOCALIZED_ALTERNATE_NODES                  L"nodos"
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"noEco"
#define LOCALIZED_ALTERNATE_NOSTATUS               L"quitaEstado"
#define LOCALIZED_ALTERNATE_NOT                    L"no"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"noIguales?"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"noIguales?"
#define LOCALIZED_ALTERNATE_NOYIELD                L"exclusivo"
#define LOCALIZED_ALTERNATE_NUMBERP                L"numero?"
#define LOCALIZED_ALTERNATE_NUMBER_                L"numero?"
#define LOCALIZED_ALTERNATE_OP                     L"dev"
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"abreA?adir"
#define LOCALIZED_ALTERNATE_OPENREAD               L"abreLectura"
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"abreActualizar"
#define LOCALIZED_ALTERNATE_OPENWRITE              L"abreEscritura"
#define LOCALIZED_ALTERNATE_OR                     L"o"
#define LOCALIZED_ALTERNATE_OUTPORT                L"escribePuerto2"
#define LOCALIZED_ALTERNATE_OUTPORTB               L"escribePuerto"
#define LOCALIZED_ALTERNATE_OUTPUT                 L"devuelve"
#define LOCALIZED_ALTERNATE_PARSE                  L"analiza"
#define LOCALIZED_ALTERNATE_PAUSE                  L"pausa"
#define LOCALIZED_ALTERNATE_PC                     L"cl"
#define LOCALIZED_ALTERNATE_PD                     L"bl"
#define LOCALIZED_ALTERNATE_PE                     L"goma"
#define LOCALIZED_ALTERNATE_PENCOLOR               L"colorLapiz"
#define LOCALIZED_ALTERNATE_PENDOWN                L"bajaLapiz"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"bajaLapiz?"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"bajaLapiz?"
#define LOCALIZED_ALTERNATE_PENERASE               L"goma"
#define LOCALIZED_ALTERNATE_PENMODE                L"lapizModo"
#define LOCALIZED_ALTERNATE_PENPAINT               L"lapizNormal"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"patronLapiz"
#define LOCALIZED_ALTERNATE_PENREVERSE             L"lapizInvierte"
#define LOCALIZED_ALTERNATE_PENSIZE                L"grosor"
#define LOCALIZED_ALTERNATE_PENUP                  L"subeLapiz"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"perspectiva"
#define LOCALIZED_ALTERNATE_PITCH                  L"cabeceo"
#define LOCALIZED_ALTERNATE_PIXEL                  L"pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"suenaWave"
#define LOCALIZED_ALTERNATE_PLIST                  L"lProp"
#define LOCALIZED_ALTERNATE_PLISTS                 L"lProps"
#define LOCALIZED_ALTERNATE_PO                     L"imDefs"
#define LOCALIZED_ALTERNATE_POPDIR                 L"directorioPadre"
#define LOCALIZED_ALTERNATE_POLYSTART              L"empiezaPoligono"
#define LOCALIZED_ALTERNATE_POLYEND                L"terminaPoligono"
#define LOCALIZED_ALTERNATE_POLYVIEW               L"muestraPoligono"
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"cierraPuerto"
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"limpiaPuerto"
#define LOCALIZED_ALTERNATE_PORTMODE               L"modoPuerto"
#define LOCALIZED_ALTERNATE_PORTOPEN               L"abrePuerto"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"leeCadenaPuerto"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"leeCaracterPuerto"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"escribeCadenaPuerto"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"escribeCaracterPuerto"
#define LOCALIZED_ALTERNATE_POS                    L"pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 L"pos3d"
#define LOCALIZED_ALTERNATE_POT                    L"imTitulosTodo"
#define LOCALIZED_ALTERNATE_POWER                  L"potencia"
#define LOCALIZED_ALTERNATE_PPROP                  L"ponprop"
#define LOCALIZED_ALTERNATE_PPT                    L"lNormal"
#define LOCALIZED_ALTERNATE_PR                     L"es"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"primitiva?"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"primitiva?"
#define LOCALIZED_ALTERNATE_PRINT                  L"escribe"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"procedimiento?" // "definido?"
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"procedimiento?"
#define LOCALIZED_ALTERNATE_PROPLISTP              L"lProp?"
#define LOCALIZED_ALTERNATE_PROPLIST_              L"lProp?"
#define LOCALIZED_ALTERNATE_PROCEDURES             L"lProcs"
#define LOCALIZED_ALTERNATE_PRODUCT                L"producto"
#define LOCALIZED_ALTERNATE_PU                     L"sl"
#define LOCALIZED_ALTERNATE_PX                     L"lInvierte"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"preguntaBox"
#define LOCALIZED_ALTERNATE_QUOTIENT               L"cociente"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"radarcCos"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"radarcSen"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"radarcTan"
#define LOCALIZED_ALTERNATE_RADCOS                 L"radCos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"creaBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"habilitaBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"borraBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"leeBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"escribeBotonRadio"
#define LOCALIZED_ALTERNATE_RADSIN                 L"radSen"
#define LOCALIZED_ALTERNATE_RADTAN                 L"radTan"
#define LOCALIZED_ALTERNATE_RANDOM                 L"azar"
#define LOCALIZED_ALTERNATE_RAWASCII               L"asciiPuro" // "ascii"
#define LOCALIZED_ALTERNATE_RC                     L"lc"
#define LOCALIZED_ALTERNATE_RCS                    L"lcs"
#define LOCALIZED_ALTERNATE_READCHAR               L"leeCar"
#define LOCALIZED_ALTERNATE_READCHARS              L"LeeCars"
#define LOCALIZED_ALTERNATE_READER                 L"lectura"
#define LOCALIZED_ALTERNATE_READLIST               L"leeLista"
#define LOCALIZED_ALTERNATE_READPOS                L"posLectura"
#define LOCALIZED_ALTERNATE_READRAWLINE            L"readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               L"leePalabra"
#define LOCALIZED_ALTERNATE_REMAINDER              L"resto"
#define LOCALIZED_ALTERNATE_REMPROP                L"boProp"
#define LOCALIZED_ALTERNATE_REPCOUNT               L"cuentaRepite"
#define LOCALIZED_ALTERNATE_REPEAT                 L"repite"
#define LOCALIZED_ALTERNATE_RERANDOM               L"reAzar"
#define LOCALIZED_ALTERNATE_RIGHT                  L"giraDerecha"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"balanceaDerecha" // "balancea"
#define LOCALIZED_ALTERNATE_RL                     L"ll"
#define LOCALIZED_ALTERNATE_RMDIR                  L"eliminaDir"
#define LOCALIZED_ALTERNATE_ROLL                   L"balanceo" // "balanceo?"
#define LOCALIZED_ALTERNATE_ROUND                  L"redondea"
#define LOCALIZED_ALTERNATE_RR                     L"bd"
#define LOCALIZED_ALTERNATE_RT                     L"gd"
#define LOCALIZED_ALTERNATE_RUN                    L"ejecuta"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"ejecutaAnaliza"
#define LOCALIZED_ALTERNATE_RUNRESULT              L"resultadoEjecuta"
#define LOCALIZED_ALTERNATE_RW                     L"lp"
#define LOCALIZED_ALTERNATE_SAVE                   L"guarda"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"colorFondo"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"creaBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"habilitaBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"borraBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"leeBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"ponBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLX                L"desplazax"
#define LOCALIZED_ALTERNATE_SCROLLY                L"desplazay"
#define LOCALIZED_ALTERNATE_SCRUNCH                L"ronzal"
#define LOCALIZED_ALTERNATE_SE                     L"fr"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"seleccionBox"
#define LOCALIZED_ALTERNATE_SENTENCE               L"frase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"ponAreaActiva"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"ponIndiceBit"
#define LOCALIZED_ALTERNATE_SETBITMODE             L"ponModobit"
#define LOCALIZED_ALTERNATE_SETCLIP                L"ponClip"
#define LOCALIZED_ALTERNATE_SETCURSOR              L"ponCursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"setCursorNoEspera"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"ponCursorEspera"
#define LOCALIZED_ALTERNATE_SETFC                  L"poncr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"ponColorRelleno"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"ponFoco"
#define LOCALIZED_ALTERNATE_SETH                   L"ponr"
#define LOCALIZED_ALTERNATE_SETHEADING             L"ponRumbo"
#define LOCALIZED_ALTERNATE_SETITEM                L"ponElemento"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"ponTipo"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"ponLuz"
#define LOCALIZED_ALTERNATE_SETMARGINS             L"ponMargenes"
#define LOCALIZED_ALTERNATE_SETPC                  L"ponCL"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"ponColorLapiz"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"ponPatronLapiz"
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"ponGrosor"
#define LOCALIZED_ALTERNATE_SETPITCH               L"ponCabeceo"
#define LOCALIZED_ALTERNATE_SETPIXEL               L"ponPixel"
#define LOCALIZED_ALTERNATE_SETPOS                 L"ponPos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"posicionate"
#define LOCALIZED_ALTERNATE_SETREAD                L"ponLectura"
#define LOCALIZED_ALTERNATE_SETREADPOS             L"ponPosLectura"
#define LOCALIZED_ALTERNATE_SETROLL                L"ponBalanceo"
#define LOCALIZED_ALTERNATE_SETSC                  L"ponCF"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"ponColorFondo"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"ponRonzal"
#define LOCALIZED_ALTERNATE_SETTIMER               L"ponTemporizador" // "poncontador"
#define LOCALIZED_ALTERNATE_SETTURTLE              L"activa"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"ponModoTortuga"
#define LOCALIZED_ALTERNATE_SETWRITE               L"ponEscritura"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"ponPosEscritura"
#define LOCALIZED_ALTERNATE_SETX                   L"ponX"
#define LOCALIZED_ALTERNATE_SETXY                  L"ponXY"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"ponXYZ"
#define LOCALIZED_ALTERNATE_SETY                   L"ponY"
#define LOCALIZED_ALTERNATE_SETZ                   L"ponZ"
#define LOCALIZED_ALTERNATE_SHELL                  L"shell"
#define LOCALIZED_ALTERNATE_SHOW                   L"muestra"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"visible?"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"visible?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"muestraTortuga"
#define LOCALIZED_ALTERNATE_SIN                    L"sen"
#define LOCALIZED_ALTERNATE_SOUND                  L"suena"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"pantallaPartida"
#define LOCALIZED_ALTERNATE_SQRT                   L"rc"
#define LOCALIZED_ALTERNATE_SS                     L"pa"
#define LOCALIZED_ALTERNATE_ST                     L"muestraTortuga"
#define LOCALIZED_ALTERNATE_STANDOUT               L"standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           L"creaEstatico"
#define LOCALIZED_ALTERNATE_STATICDELETE           L"borraEstatico"
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"actualizaEstatico"
#define LOCALIZED_ALTERNATE_STATUS                 L"estado"
#define LOCALIZED_ALTERNATE_STEP                   L"paso"
#define LOCALIZED_ALTERNATE_STEPPED                L"listaPaso"
#define LOCALIZED_ALTERNATE_STOP                   L"alto"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"contiene?"
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"contiene?"
#define LOCALIZED_ALTERNATE_SUM                    L"adicion"
#define LOCALIZED_ALTERNATE_TAG                    L"etiqueta"
#define LOCALIZED_ALTERNATE_TAN                    L"tan"
#define LOCALIZED_ALTERNATE_TEST                   L"prueba"
#define LOCALIZED_ALTERNATE_TEXT                   L"texto"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"pantallaTexto"
#define LOCALIZED_ALTERNATE_THING                  L"valor"
#define LOCALIZED_ALTERNATE_THROW                  L"lanza" // "envia"
#define LOCALIZED_ALTERNATE_TIME                   L"hora"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"horaMili"
#define LOCALIZED_ALTERNATE_TO                     L"para"
#define LOCALIZED_ALTERNATE_TONE                   L"tono"
#define LOCALIZED_ALTERNATE_TOWARDS                L"hacia"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"haciaXYZ"
#define LOCALIZED_ALTERNATE_TRACE                  L"traza"
#define LOCALIZED_ALTERNATE_TRACED                 L"trazados"
#define LOCALIZED_ALTERNATE_TS                     L"pt"
#define LOCALIZED_ALTERNATE_TURTLE                 L"quien"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"modoTortuga"
#define LOCALIZED_ALTERNATE_TURTLES                L"tortugas"
#define LOCALIZED_ALTERNATE_TYPE                   L"muestrat"
#define LOCALIZED_ALTERNATE_UNBURY                 L"destapa"
#define LOCALIZED_ALTERNATE_UNSTEP                 L"noPaso"
#define LOCALIZED_ALTERNATE_UNTRACE                L"noTraza"
#define LOCALIZED_ALTERNATE_UP                     L"arriba"
#define LOCALIZED_ALTERNATE_UPPERCASE              L"mayusculas"
#define LOCALIZED_ALTERNATE_UPPITCH                L"cabecea"
#define LOCALIZED_ALTERNATE_WAIT                   L"espera"
#define LOCALIZED_ALTERNATE_WINDOW                 L"modoVentana"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"creaVentana"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"habilitaVentana"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"borraVentana"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"editaArchivo" // "editafichero"
#define LOCALIZED_ALTERNATE_WINDOWSET              L"activaVentana"
#define LOCALIZED_ALTERNATE_WINHELP                L"ayudaDeWindows"
#define LOCALIZED_ALTERNATE_WORD                   L"palabra"
#define LOCALIZED_ALTERNATE_WORDP                  L"palabra?"
#define LOCALIZED_ALTERNATE_WORD_                  L"palabra?"
#define LOCALIZED_ALTERNATE_WRAP                   L"modoVuelta"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"posEscritura"
#define LOCALIZED_ALTERNATE_WRITER                 L"escritura"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"siNoBox"
#define LOCALIZED_ALTERNATE_YIELD                  L"noExclusivo"
#define LOCALIZED_ALTERNATE_ZOOM                   L"ponLupa"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"Cancelar"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&Aplicar"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"El entorno de programaci?n FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&Archivo"
#define LOCALIZED_FILE_NEW              L"&Nuevo\t(borra el trabajo actual)"
#define LOCALIZED_FILE_LOAD             L"&Cargar...\t(une al trabajo actual)"
#define LOCALIZED_FILE_OPEN             L"A&brir...\t(reemplaza el trabajo actual)"
#define LOCALIZED_FILE_SAVE             L"&Guardar"
#define LOCALIZED_FILE_SAVEAS           L"G&uardar como..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"Establecer como &Protector de Pantalla"
#define LOCALIZED_FILE_EDIT             L"&Editar..."
#define LOCALIZED_FILE_ERASE            L"&Borrar..."
#define LOCALIZED_FILE_EXIT             L"&Salir"

#define LOCALIZED_BITMAP               L"&Bitmap"
#define LOCALIZED_BITMAP_NEW           L"&Nuevo"
#define LOCALIZED_BITMAP_LOAD          L"&Cargar..."
#define LOCALIZED_BITMAP_SAVE          L"&Guardar"
#define LOCALIZED_BITMAP_SAVEAS        L"G&uardar como..."
#define LOCALIZED_BITMAP_PRINT         L"&Imprimir..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"C&onfigurar impresora..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"&Area Activa..."

#define LOCALIZED_SET                  L"&Configurar"
#define LOCALIZED_SET_PENSIZE          L"&Tama?o del l?piz..."
#define LOCALIZED_SET_LABELFONT        L"Tipo de letra de &rotulador..."
#define LOCALIZED_SET_COMMANDERFONT    L"Tipo de letra del &centro de comandos..."
#define LOCALIZED_SET_PENCOLOR         L"Color de &l?piz..."
#define LOCALIZED_SET_FLOODCOLOR       L"Color de r&elleno..."
#define LOCALIZED_SET_SCREENCOLOR      L"Color de &fondo..."

#define LOCALIZED_ZOOM                 L"&Zoom"
#define LOCALIZED_ZOOM_IN              L"&Acercar"
#define LOCALIZED_ZOOM_OUT             L"A&lejar"
#define LOCALIZED_ZOOM_NORMAL          L"&Normal"

#define LOCALIZED_HELP                 L"A&yuda"
#define LOCALIZED_HELP_INDEX           L"&Indice"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutorial"
#define LOCALIZED_HELP_DEMO            L"&Demostraci?n"
#define LOCALIZED_HELP_EXAMPLE         L"&Ejemplos"
#define LOCALIZED_HELP_RELEASENOTES    L"&Notas de la versi?n"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"&Acerca de " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"Acerca de &FMS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"Espa?ol a Ingl?s"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"Ingl?s a Espa?ol"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Seleccionar ?rea activa"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"Esto afecta la impresi?n y grabaci?n de bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-Sup"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Inf"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-Sup"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Inf"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"Puntos por pulgada impresa:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&Restaurar"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"Protector de pantalla de FMSLogo"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"Configuraci?n del protector de pantalla de FMSLogo"
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Localizar ..."
#define LOCALIZED_SCREENSAVER_FILE              L"&Archivo de Logo"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"Seleccionar una instrucci?n " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"El ?rea de trabajo no tiene una lista de instrucciones de " LOCALIZED_ALTERNATE_STARTUP " definida, por lo tanto nada va a pasar cuando se carga el protector de pantalla.\n\nPor favor, selecciona un procedimiento que se ejecuta cuando se carga el programa." 
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"La variable " LOCALIZED_ALTERNATE_STARTUP " no es una lista, por lo tanto nada va a pasar cuando se carga el protector de pantalla.\n\nPor favor, selecciona un procedimiento que se ejecuta cuando se carga el programa."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"El ?rea de trabajo tiene " LOCALIZED_ALTERNATE_STARTUP " definida como una lista vac?a, por lo tanto nada va a pasar cuando se carga el protector de pantalla.\n\nPor favor, selecciona un procedimiento que se ejecuta cuando se carga el programa."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"No hay procedimientos definidos"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"No hay procedimientos, variables ni listas de propiedades definidas, por lo tanto el ?rea de trabajo ser? guardada como un archivo vac?o.\n\n?Deseas guardar el ?rea de trabajo de todas formas?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Copiar"
#define LOCALIZED_POPUP_CUT                      L"Cortar"
#define LOCALIZED_POPUP_PASTE                    L"Pegar"
#define LOCALIZED_POPUP_DELETE                   L"Borrar"
#define LOCALIZED_POPUP_UNDO                     L"Deshacer"
#define LOCALIZED_POPUP_REDO                     L"Rehacer"
#define LOCALIZED_POPUP_SELECTALL                L"Seleccionar Todo"
#define LOCALIZED_POPUP_HELP                     L"B?squeda por Tema"
#define LOCALIZED_POPUP_REMOVELINES              L"Eliminar L?neas Seleccionadas"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Editor"

#define LOCALIZED_EDITOR_FILE                    L"&Archivo"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Guardar y Salir\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"Guardar en &?rea de trabajo"
#define LOCALIZED_EDITOR_FILE_PRINT              L"&Imprimir..."
#define LOCALIZED_EDITOR_FILE_EXIT               L"&Salir"

#define LOCALIZED_EDITOR_EDIT                    L"&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&Deshacer\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&Rehacer\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"&Cortar\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"C&opiar\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"&Pegar\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&Borrar\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"Borrar &todo\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"&Seleccionar Todo\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"&Buscar"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"&Encontrar...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Reemplazar...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Siguiente\tF3"

#define LOCALIZED_EDITOR_SET                     L"&Configurar"
#define LOCALIZED_EDITOR_SET_FONT                L"&Tipo de letra..."

#define LOCALIZED_EDITOR_TEST                    L"&Probar"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"&Ejecutar selecci?n\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    L"A&yuda"
#define LOCALIZED_EDITOR_HELP_INDEX              L"&Indice"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&B?squeda por tema\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Guardar y Salir"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&No guardar"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"Hay cambios no guardados en tu espacio de trabajo. Si sales sin guardar, estos cambios se perder?n."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"?Deseas guardar tus cambios antes de salir?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Centro de Comandos"
#define LOCALIZED_COMMANDER_HALT                L"Alto"
#define LOCALIZED_COMMANDER_TRACE               L"Trazar"
#define LOCALIZED_COMMANDER_NOTRACE             L"NoTrazar"
#define LOCALIZED_COMMANDER_PAUSE               L"Pausa"
#define LOCALIZED_COMMANDER_STATUS              L"Estado"
#define LOCALIZED_COMMANDER_NOSTATUS            L"NoEstado"
#define LOCALIZED_COMMANDER_STEP                L"Paso"
#define LOCALIZED_COMMANDER_UNSTEP              L"NoPaso"
#define LOCALIZED_COMMANDER_RESET               L"Reiniciar"
#define LOCALIZED_COMMANDER_EXECUTE             L"Ejecutar"
#define LOCALIZED_COMMANDER_EDALL               L"EdTodo"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Estado"
#define LOCALIZED_STATUS_PEN                    L"L?piz"
#define LOCALIZED_STATUS_CONTACT                L"Contacto:"
#define LOCALIZED_STATUS_WIDTH                  L"Ancho:"
#define LOCALIZED_STATUS_STYLE                  L"Estilo:"
#define LOCALIZED_STATUS_ORIENTATION            L"Orientaci?n"
#define LOCALIZED_STATUS_PITCH                  L"Cabeceo:"
#define LOCALIZED_STATUS_HEADING                L"Rumbo:"
#define LOCALIZED_STATUS_ROLL                   L"Balanceo:"
#define LOCALIZED_STATUS_TURTLE                 L"Tortuga"
#define LOCALIZED_STATUS_POSITION               L"Posici?n(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Cu?l:"
#define LOCALIZED_STATUS_VISIBILITY             L"Visibilidad:"
#define LOCALIZED_STATUS_COLOR                  L"Color"
#define LOCALIZED_STATUS_PENCOLOR               L"L?piz(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"Relleno(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Fondo(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"N?cleo"
#define LOCALIZED_STATUS_CALLS                  L"Llamadas:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"Memoria Pico:"

#define LOCALIZED_STATUS_PENREVERSE     L"LapizInvierte"
#define LOCALIZED_STATUS_PENNORMAL      L"LapizNormal"
#define LOCALIZED_STATUS_PENERASE       L"Goma"
#define LOCALIZED_STATUS_PENUP          L"Arriba"
#define LOCALIZED_STATUS_PENDOWN        L"Abajo"
#define LOCALIZED_STATUS_PENSHOWN       L"Mostrada"
#define LOCALIZED_STATUS_PENHIDDEN      L"Oculta"
#define LOCALIZED_STATUS_POLYGONS       L"Pol?gonos"
#define LOCALIZED_STATUS_VECTORS        L"Vectores"
#define LOCALIZED_STATUS_NODES          L"Nodos"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&Todo"
#define LOCALIZED_ERASEPROCEDURE                L"Borrar"
#define LOCALIZED_EDITPROCEDURE                 L"Editar"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Poner Color"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Color de L?piz"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"Color de Relleno"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Color de Fondo"
#define LOCALIZED_SETCOLOR_RED                 L"Rojo"
#define LOCALIZED_SETCOLOR_GREEN               L"Verde"
#define LOCALIZED_SETCOLOR_BLUE                L"Az?l"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Tama?o de L?piz"
#define LOCALIZED_SETPENSIZE_SIZE              L"Grosor"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"Acerca de " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"Versi?n"
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI por George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"N?cleo por Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Instalador basado en el Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"Recursos para FMSLogo en Espa?ol\nDisponibles en http://neoparaiso.com/logo/mswlogo.html"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Gracias a Yehuda Katz y a Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" es software libre\nVer la Licencia P?blica de GNU"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"?Preguntas, dudas, comentarios?\nParticipa en la lista de Logo\nhttp://neoparaiso.com/logo/lista-logo.html"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"Traducci?n hecha por Daniel Ajoy"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"Acerca de FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS quiere decir Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"Considera hacer una donaci?n a la\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"Los cambios de la edici?n pueden perderse.\n\n?Realmente quieres salir de " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"Una sesi?n de edici?n est? activa"

#define LOCALIZED_COULDNOTWRITEBMP            L"No puedo guardar .bmp"
#define LOCALIZED_COULDNOTOPENBMP             L"No puedo abrir .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           L"No puedo crear bitmap tipo Windows 3.0"
#define LOCALIZED_NOTVALIDBMP                 L"No es un bitmap tipo Windows 3.0"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"Nos haz guardado a disco"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"Escoger Nuevo borrar? todas las definiciones.\n\n?Continuar con Nuevo?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"El archivo que est? siendo cargado ser? unido a tu trabajo actual\ny reemplazar? tus cambios no guardados.\n\n?Continuar con Cargar?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"Esto borrar? todos tus cambios no guardados.\n\n?Continuar con Abrir?"

#define LOCALIZED_EDITORISOPEN                  L"?Sabes que tienes una sesi?n de edici?n activa?\n\nTodo cambio en esta sesi?n de edici?n no ser? guardado."

#define LOCALIZED_ERROR_CANTREADFILE            L"No puedo leer el archivo \"%s\" desde disco"
#define LOCALIZED_ERROR_CANTWRITEFILE           L"No puedo escribir el archivo \"%s\" a disco"

#define LOCALIZED_SAVETOWORKSPACE                L"Guardar al ?rea de trabajo"
#define LOCALIZED_CONTENTSCHANGED                L"El contenido cambi?"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"El contenido cambi?.\n?Deseas guardar los cambios al ?rea de trabajo?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"Hubo un error al guardar el contenido de editor en el ?rea de trabajo.  El cursor se situar? tras la ?ltima definici?n correcta.\n\nBusca un posible mensaje de error en el Area de Comandos."
#define LOCALIZED_RETURNTOEDIT                  L"?Regresar al editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              L"Error in File" // NOT_YET_LOCALIZED
#define LOCALIZED_ERRORINFILEMESSAGE            L"There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?" // NOT_YET_LOCALIZED

#define LOCALIZED_CANNOTALLOCATESCREEN          L"Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue." // NOT_YET_LOCALIZED


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    L"Seleccionar el programa Logo a cargar (unirlo al ?rea de trabajo actual)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    L"Seleccionar el programa Logo a abrir (reemplazar el ?rea de trabajo actual)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    L"Seleccionar el archivo a que el ?rea de trabajo ser? guardardo"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  L"Seleccionar la imagen a cargar"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  L"Seleccionar el archivo a que el ?rea activa ser? guardardo"

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"Todos los Archivos (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Archivos de Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"Archivos Bitmap (*.bmp)|*.bmp|Archivos GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" se detuvo\n"
#define LOCALIZED_TRACING_OUTPUTS           L" devuelve %s\n"
#define LOCALIZED_TRACING_MAKE              L"HAZ %s %s"
#define LOCALIZED_TRACING_PPROP             L"PONPROP %s %s %s"
#define LOCALIZED_TRACING_LOCATION          L" en %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Paso Simple"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s definido\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"Goma"
#define LOCALIZED_PENMODE_REVERSE  L"LapizInvierte"
#define LOCALIZED_PENMODE_PAINT    L"LapizNormal"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: Error Interno Fatal"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Falta de Memoria"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"no hay espacio"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"desborde de pila"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"tortuga fuera de los l?mites"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"no pude inicializar gr?ficas"
#define LOCALIZED_ERROR_BADDATA                L"a %p no le gust? recibir %s"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p no devolvi? valor a %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"%p necesita recibir m?s cosas"
#define LOCALIZED_ERROR_TOOMUCH                L"demasiadas cosas entre par?ntesis ()"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"No dices qu? debo hacer con %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"demasiados par?ntesis '('"
#define LOCALIZED_ERROR_NOVALUE                L"%s no tiene un valor todav?a"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"par?ntesis ')' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"corchete ']' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"llave '}' inesperada"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"no s? c?mo realizar %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"no puedo encontrar la etiqueta LANZA (THROW) para %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p ya est? definido"
#define LOCALIZED_ERROR_STOPPING               L"Parando..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"ECO est? activado"
#define LOCALIZED_ERROR_FILESYSTEM                   L"Error del sistema de archivos: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"No puedo abrir ese archivo"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"No puedo abrir ese archivo: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"Archivo ya est? abierto"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"Archivo no est? abierto"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"No pude crear archivo para editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"No pude iniciar editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"No pude leer archivo de editor"
#define LOCALIZED_ERROR_IFWARNING              L"Asumo que quer?as decir SISINO (IFELSE), no SI (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p cubierta por local en llamada a procedimiento"
#define LOCALIZED_ERROR_USER                   L"ATRAPA \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p es una primitiva"
#define LOCALIZED_ERROR_TONOTINSIDE            L"No puedes usar PARA (TO) dentro de un procedimiento"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"Solo puedes usar %p dentro de un procedimiento"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"Debes estar dentro de un procedimiento para usar DEVUELVE (OUTPUT) o ALTO (STOP)."
#define LOCALIZED_ERROR_NOTEST                 L"%p sin PRUEBA (TEST)"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"Macro devolvi? %s en lugar de una lista"
#define LOCALIZED_ERROR_DEEPEND                L"FIN (END) dentro de una instrucci?n multi-l?nea"
#define LOCALIZED_ERROR_DEEPENDIN              L"FIN (END) dentro de una instrucci?n multi-l?nea en %p"
#define LOCALIZED_ERROR_UNKNOWN                L"Estado de error desconocido  - error interno."
#define LOCALIZED_PAUSING                      L"Pausando..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                L"a %p no le gust? recibir %p porque toma sus entradas de manera especial"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Error"
#define LOCALIZED_ERROR_BADINPUT             L"Entrada incorrecta"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"La entrada no tiene pareja"

#define LOCALIZED_ERROR_CANTOPENPORT         L"No se puede abrir el PUERTO"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"No se puede CERRAR el puerto"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"No se pudo vaciar el PUERTO"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"No se puede construir dcb en el PUERTO"
#define LOCALIZED_ERROR_CANTSETPORT          L"No se puede poner el PUERTO"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"PUERTO ya abierto"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"PUERTO no abierto"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s ya existe"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s no existe"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"La DLL no est? cargada"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"Fall? la carga de la DLL"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Tipo de dato de la entrada inv?lido"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Tipo de dato de retorno inv?lido"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Funci?n no encontrada"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"No coincide los tipos de datos"

#define LOCALIZED_ERROR_NETWORK               L"Error de Red"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Error de Recepci?n de Red"
#define LOCALIZED_ERROR_NETWORKSEND           L"Error de Env?o de Red"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Error Inesperado, la Red podr?a estar inactiva"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"Ya est? activa"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"Ya est? encendida"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"Ya est? apagada"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Nombre Demasiado largo"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"No inicializado"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"El sistema no est? listo"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"Versi?n desconocida"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"No puedo enviar despu?s de desactivaci?n de socket"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Llamada al sistema interrumpida"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Respuesta Autoritativa: Dominio no encontrado"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"No-Autoritativa: Dominio no encontrado. Ver INICIARED"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Error sin posible recuperaci?n"
#define LOCALIZED_ERROR_NETWORKNODATA              L"Registro de datos no disponible"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"N?mero de archivo incorrecto"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"La operaci?n bloquear?a"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"Operaci?n en progreso ahora"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"Operaci?n ya en progreso"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Direcci?n incorrecta"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Necesito direcci?n de destino"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Mensaje demasiado largo"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Familia del protocolo desconocida"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"El directorio no est? vac?o"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Se ha alcanzado el l?mite de la aplicaci?n"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"Se ha excedido la cuota de disco"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Demasiados archivos abiertos"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Accesso negado"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Operaci?n de socket en algo que no es un socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"No puedo asignar direcci?n pedida"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"La direcci?n ya est? en uso"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"La familia de la direcci?n no es conocida por la familia del protocolo"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Tiempo de intento de conexi?n excedido"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Tipo de socket desconocido"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protocolo desconocido"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"No hay espacio en memoria temporal"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"El socket ya est? conectado"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"El socket no est? conectado"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Opci?n de protocolo incorrecta"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"Conexi?n reiniciada por interlocutor"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"El software ocasion? el cierre de la conexi?n"
#define LOCALIZED_ERROR_NETWORKISDOWN              L"La red est? ca?da"
#define LOCALIZED_ERROR_NETWORKRESET               L"La red fue reiniciada"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"Conexi?n rechazada"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"Dominio est? caido"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"Dominio inalcanzable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"El protocolo es del tipo equivocado para el socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Operaci?n no permitida en el socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"No se encontr? ruta al dominio remoto"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Demasiadas referencias"

#define LOCALIZED_ERROR_POLYSTART               L"Error en EmpiezaPoligono"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"Ya tienes un pol?gono empezado"

#define LOCALIZED_ERROR_POLYEND                 L"Error en TerminaPoligono"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"No haz empezado un pol?gono"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"Debes tener al menos 3 vectores para definir un pol?gono"

#define LOCALIZED_ERROR_SOUND                 L"Error de Sonido"

#define LOCALIZED_ERROR_MIDI                  L"Error de MIDI"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"Dispositivo Midi incorrecto"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"Ya est? abierto"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"No est? abierto"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"No hay texto en el portapapeles"

#define LOCALIZED_ERROR_MCI                   L"Error de MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Temporizador no encontrado"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"Ayuda en l?nea no disponible porque no se pudo cargar hhctrl.ocx"

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"L?nea de comandos incorrecta"

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"La variable de ambiente TMP no est? definida o es incorrecta.\n" LOCALIZED_GENERAL_PRODUCTNAME " intentar? utilizar C:\\ para guardar archivos temporales"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Problema al generar GIF, revisa cantidad de memoria o espacio en disco"
#define LOCALIZED_ERROR_GIFREADFAILED         L"Problema al leer GIF, revisa memoria o espacio en disco"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"Indice de BitMap fuera de rango"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Cortar fall?, posiblemente no hay memoria"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Nada para Pegar"
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"El BitMap en ?ndice debe ser inicializado con un mapa de bits"

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"La tortuga %d no tiene figura, realizar? un Alto"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"No encontr? el tipo de letra llamado %s. Elige uno de lo siguientes:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"El manejador de impresi?n no conoce esta funci?n"
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"No puedo dibujar la imagen"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"No pueda extraer la imagen"
#define LOCALIZED_ERROR_SUBCODE                 L"Sub C?digo"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Entrada:"
#define LOCALIZED_PROMPT_TO     L"Modo Para (Cancel para Finalizar)"
#define LOCALIZED_PROMPT_LIST   L"Modo de Lista (Cancel para Alto)"
#define LOCALIZED_PROMPT_PAUSE  L"Modo de Pausa (Cancel para Continuar)"
#define LOCALIZED_PROMPT_INPUT  L"Modo de Entrada (Cancel para Alto)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"Cambiado a  \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"No pude cambiar a directorio \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"Cambiado a \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Ahora estamos en el nuevo directorio creado \"%s\""
#define LOCALIZED_FILE_MKDIRFAILED         L"No pude crear directorio \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Directorio Eliminado \"%s\""
#define LOCALIZED_FILE_RMDIRFAILED         L"No pude eliminar directorio \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"El directorio no existe"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Aseg?rate que el directorio est? vac?o antes de eliminarlo."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Dibujo en Logo"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"Area Activa"
#define LOCALIZED_INFORMATION   L"Informaci?n"
#define LOCALIZED_WARNING       L"Atenci?n"
#define LOCALIZED_UNTITLED      L"Sin nombre"
#define LOCALIZED_UNKNOWN       L"Desconocido"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"No acotado"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Encontrar"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Reemplazar"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING L"%s no encontrado"


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
#define LOCALIZED_COLOR_ALICEBLUE             L"BlancoAlicia"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"BlancoAntiguo"
#define LOCALIZED_COLOR_AQUA                  L"Agua"
#define LOCALIZED_COLOR_AQUAMARINE            L"Aguamarina"
#define LOCALIZED_COLOR_AZURE                 L"AzulCeleste"
#define LOCALIZED_COLOR_BEIGE                 L"Beige"
#define LOCALIZED_COLOR_BISQUE                L"Bizcocho"
#define LOCALIZED_COLOR_BLACK                 L"Negro"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"BlancoAlmendra"
#define LOCALIZED_COLOR_BLUE                  L"Azul"
#define LOCALIZED_COLOR_BLUEVIOLET            L"AzulVioleta"
#define LOCALIZED_COLOR_BROWN                 L"Marr?n"
#define LOCALIZED_COLOR_BURLYWOOD             L"MaderaFuerte"
#define LOCALIZED_COLOR_CADETBLUE             L"AzulCadete"
#define LOCALIZED_COLOR_CHARTREUSE            L"Cartuja"
#define LOCALIZED_COLOR_CHOCOLATE             L"Chocolate"
#define LOCALIZED_COLOR_CORAL                 L"Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"AzulMa?z"
#define LOCALIZED_COLOR_CORNSILK              L"Ma?z"
#define LOCALIZED_COLOR_CRIMSON               L"Carmes?"
#define LOCALIZED_COLOR_CYAN                  L"C?an"
#define LOCALIZED_COLOR_DARKBLUE              L"AzulOscuro"
#define LOCALIZED_COLOR_DARKCYAN              L"C?anOscuro"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"DoradoOscuro"
#define LOCALIZED_COLOR_DARKGRAY              L"GrisOscuro"
#define LOCALIZED_COLOR_DARKGREEN             L"VerdeOscuro"
#define LOCALIZED_COLOR_DARKGREY              L"GrisOscuro"
#define LOCALIZED_COLOR_DARKKHAKI             L"CaquiOscuro"
#define LOCALIZED_COLOR_DARKMAGENTA           L"FuchsiaOscuro"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"VerdeOlivaOscuro"
#define LOCALIZED_COLOR_DARKORANGE            L"NaranjaOscuro"
#define LOCALIZED_COLOR_DARKORCHID            L"Orqu?deaOscuro"
#define LOCALIZED_COLOR_DARKRED               L"RojoOscuro"
#define LOCALIZED_COLOR_DARKSALMON            L"Salm?nOscuro"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"VerdeMarOscuro"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"AzulPizarraOscuro"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"GrisPizarraOscuro"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"GrisPizarraOscuro"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"TorquesaOscuro"
#define LOCALIZED_COLOR_DARKVIOLET            L"VioletaOscuro"
#define LOCALIZED_COLOR_DEEPPINK              L"RosaOscuro"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"AzulCieloOscuro"
#define LOCALIZED_COLOR_DIMGRAY               L"GrisSuave"
#define LOCALIZED_COLOR_DIMGREY               L"GrisSuave"
#define LOCALIZED_COLOR_DODGERBLUE            L"AzulRegata"
#define LOCALIZED_COLOR_FIREBRICK             L"LadrilloFuego"
#define LOCALIZED_COLOR_FLORALWHITE           L"BlancoFloral"
#define LOCALIZED_COLOR_FORESTGREEN           L"VerdeBosque"
#define LOCALIZED_COLOR_FUCHSIA               L"Fucsia"
#define LOCALIZED_COLOR_GAINSBORO             L"AzulGainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            L"BlancoLigero"
#define LOCALIZED_COLOR_GOLD                  L"Oro"
#define LOCALIZED_COLOR_GOLDENROD             L"Dorado"
#define LOCALIZED_COLOR_GRAY                  L"Plata"
#define LOCALIZED_COLOR_GREEN                 L"Verde"
#define LOCALIZED_COLOR_GREENYELLOW           L"AmarilloVerdoso"
#define LOCALIZED_COLOR_GREY                  L"Gris"
#define LOCALIZED_COLOR_HONEYDEW              L"FlorDeRoc?o"
#define LOCALIZED_COLOR_HOTPINK               L"RosaC?lido"
#define LOCALIZED_COLOR_INDIANRED             L"RojoIndio"
#define LOCALIZED_COLOR_INDIGO                L"Anil"
#define LOCALIZED_COLOR_IVORY                 L"Marfil"
#define LOCALIZED_COLOR_KHAKI                 L"Caqui"
#define LOCALIZED_COLOR_LAVENDER              L"Lavanda"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"Rosalavanda"
#define LOCALIZED_COLOR_LAWNGREEN             L"VerdeC?sped"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"GasaLim?n"
#define LOCALIZED_COLOR_LIGHTBLUE             L"AzulClaro"
#define LOCALIZED_COLOR_LIGHTCORAL            L"CoralClaro"
#define LOCALIZED_COLOR_LIGHTCYAN             L"C?anClaro"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"AmarilloDoradoClaro"
#define LOCALIZED_COLOR_LIGHTGRAY             L"GrisClaro"
#define LOCALIZED_COLOR_LIGHTGREEN            L"VerdeClaro"
#define LOCALIZED_COLOR_LIGHTGREY             L"GrisClaro"
#define LOCALIZED_COLOR_LIGHTPINK             L"RosaClaro"
#define LOCALIZED_COLOR_LIGHTSALMON           L"Salm?nClaro"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"VerdeMarClaro"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"AzulCieloClaro"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"GrisPizarraClaro"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"GrisPizarraClaro"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"AzulAceroClaro"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"AmariloClaro"
#define LOCALIZED_COLOR_LIME                  L"Lima"
#define LOCALIZED_COLOR_LIMEGREEN             L"VerdeLima"
#define LOCALIZED_COLOR_LINEN                 L"Lino"
#define LOCALIZED_COLOR_MAGENTA               L"Magenta"
#define LOCALIZED_COLOR_MAROON                L"Marr?n"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"AguamarinaIntermedio"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"AzulIntermedio"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"Orqu?deaIntermedio"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"MoradoIntermedio"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"VerdeMarIntermedio"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"AzulPizarraIntermedia"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"VedrePrimaveraIntermedio"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"TorquesaIntermedio"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"VioletaIntermedio"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"AzulMedianoche"
#define LOCALIZED_COLOR_MINTCREAM             L"CremaMenta"
#define LOCALIZED_COLOR_MISTYROSE             L"RosaBrumoso"
#define LOCALIZED_COLOR_MOCCASIN              L"Mocas?n"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"BlancoNavajo"
#define LOCALIZED_COLOR_NAVY                  L"Marino"
#define LOCALIZED_COLOR_OLDLACE               L"Gal?nAntiguo"
#define LOCALIZED_COLOR_OLIVE                 L"Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             L"VerdeOliva"
#define LOCALIZED_COLOR_ORANGE                L"Naranja"
#define LOCALIZED_COLOR_ORANGERED             L"Anaranjado"
#define LOCALIZED_COLOR_ORCHID                L"Orqu?dea"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"DoradoP?lido"
#define LOCALIZED_COLOR_PALEGREEN             L"VerdeP?lido"
#define LOCALIZED_COLOR_PALETURQUOISE         L"TurquesaP?lido"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"VioletaP?lido"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"Papaya"
#define LOCALIZED_COLOR_PEACHPUFF             L"Melocot?n"
#define LOCALIZED_COLOR_PERU                  L"Per?"
#define LOCALIZED_COLOR_PINK                  L"Rosa"
#define LOCALIZED_COLOR_PLUM                  L"Ciruela"
#define LOCALIZED_COLOR_POWDERBLUE            L"AzulP?lido"
#define LOCALIZED_COLOR_PURPLE                L"Morado"
#define LOCALIZED_COLOR_RED                   L"Rojo"
#define LOCALIZED_COLOR_ROSYBROWN             L"Marr?nRosado"
#define LOCALIZED_COLOR_ROYALBLUE             L"AzulReal"
#define LOCALIZED_COLOR_SADDLEBROWN           L"Marr?nTeja"
#define LOCALIZED_COLOR_SALMON                L"Salm?n"
#define LOCALIZED_COLOR_SANDYBROWN            L"Marr?nArena"
#define LOCALIZED_COLOR_SEAGREEN              L"VerdeMar"
#define LOCALIZED_COLOR_SEASHELL              L"ConchaDeMar"
#define LOCALIZED_COLOR_SIENNA                L"Siena"
#define LOCALIZED_COLOR_SILVER                L"Plata"
#define LOCALIZED_COLOR_SKYBLUE               L"AzulCielo"
#define LOCALIZED_COLOR_SLATEBLUE             L"AzulPizarra"
#define LOCALIZED_COLOR_SLATEGRAY             L"GrisPizarra"
#define LOCALIZED_COLOR_SLATEGREY             L"GrisPizarra"
#define LOCALIZED_COLOR_SNOW                  L"Nieve"
#define LOCALIZED_COLOR_SPRINGGREEN           L"VerdePrimavera"
#define LOCALIZED_COLOR_STEELBLUE             L"AzulAcero"
#define LOCALIZED_COLOR_TAN                   L"Tostado"
#define LOCALIZED_COLOR_TEAL                  L"AzulCerceta"
#define LOCALIZED_COLOR_THISTLE               L"Morado"
#define LOCALIZED_COLOR_TOMATO                L"Tomate"
#define LOCALIZED_COLOR_TURQUOISE             L"Turquesa"
#define LOCALIZED_COLOR_VIOLET                L"Violeta"
#define LOCALIZED_COLOR_WHEAT                 L"Trigo"
#define LOCALIZED_COLOR_WHITE                 L"Blanco"
#define LOCALIZED_COLOR_WHITESMOKE            L"GrisBlanquecino"
#define LOCALIZED_COLOR_YELLOW                L"Amarillo"
#define LOCALIZED_COLOR_YELLOWGREEN           L"VerdeAmarillento"

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
