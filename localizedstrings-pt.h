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
// This file contains localized strings for Portuguese by Alexandre R Soares
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
#define LOCALIZED_ALTERNATE_TRUE     L"verd"
#define LOCALIZED_ALTERNATE_FALSE    L"falso"
#define LOCALIZED_ALTERNATE_END      L"fim"
#define LOCALIZED_ALTERNATE_TOPLEVEL L"n?velacima"
#define LOCALIZED_ALTERNATE_SYSTEM   L"sistema"

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
#define LOCALIZED_ALTERNATE__DEFMACRO              L".defMacro"
#define LOCALIZED_ALTERNATE__EQ                    L".ig"
#define LOCALIZED_ALTERNATE__MACRO                 L".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           L".talvezDevolva"
#define LOCALIZED_ALTERNATE__SETBF                 L".mude?ltimos"
#define LOCALIZED_ALTERNATE__SETFIRST              L".mudePrimeiro"
#define LOCALIZED_ALTERNATE__SETITEM               L".mudeItem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             L"?reaAtiva"
#define LOCALIZED_ALTERNATE_ALLOPEN                L"arqabertos"
#define LOCALIZED_ALTERNATE_AND                    L"e"
#define LOCALIZED_ALTERNATE_APPLY                  L"aplique"
#define LOCALIZED_ALTERNATE_ARCCOS                 L"arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 L"arcsen"
#define LOCALIZED_ALTERNATE_ARCTAN                 L"arctan"
#define LOCALIZED_ALTERNATE_ARITY                  L"arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  L"vetor"
#define LOCALIZED_ALTERNATE_ARRAYP                 L"?vetor?"
#define LOCALIZED_ALTERNATE_ARRAY_                 L"evetor?"
#define LOCALIZED_ALTERNATE_ASCII                  L"ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 L"desloquebitsa"
#define LOCALIZED_ALTERNATE_BACK                   L"paratr?s"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           L"tembarrainvertida?"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           L"tembarrainv?"
#define LOCALIZED_ALTERNATE_BEFOREP                L"?anterior?"
#define LOCALIZED_ALTERNATE_BEFORE_                L"eant?"
#define LOCALIZED_ALTERNATE_BF                     L"sp"
#define LOCALIZED_ALTERNATE_BFS                    L"sps"
#define LOCALIZED_ALTERNATE_BITAND                 L"bitE"
#define LOCALIZED_ALTERNATE_BITBLOCK               L"blocobmp"
#define LOCALIZED_ALTERNATE_BITCOPY                L"copiebmp"
#define LOCALIZED_ALTERNATE_BITCUT                 L"recortebmp"
#define LOCALIZED_ALTERNATE_BITFIT                 L"mudebmp"
#define LOCALIZED_ALTERNATE_BITINDEX               L"?ndicebmp"
#define LOCALIZED_ALTERNATE_BITLOAD                L"carreguebmp"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            L"tamcarreguebmp"
#define LOCALIZED_ALTERNATE_BITSIZE                L"tamBmp"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           L"tatbmp"
#define LOCALIZED_ALTERNATE_BITMODE                L"modobmp"
#define LOCALIZED_ALTERNATE_BITNOT                 L"bitN?o" // "bitInverso"
#define LOCALIZED_ALTERNATE_BITOR                  L"bitOu"
#define LOCALIZED_ALTERNATE_BITPASTE               L"colebmp"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        L"colebmp?ndice"
#define LOCALIZED_ALTERNATE_BITSAVE                L"salvebmp"
#define LOCALIZED_ALTERNATE_BITXOR                 L"bitXou"
#define LOCALIZED_ALTERNATE_BK                     L"pt"
#define LOCALIZED_ALTERNATE_BL                     L"su"
#define LOCALIZED_ALTERNATE_BURIED                 L"enterrados"
#define LOCALIZED_ALTERNATE_BURY                   L"enterre"
#define LOCALIZED_ALTERNATE_BUTFIRST               L"semPrimeiro"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              L"semPrimeiros"
#define LOCALIZED_ALTERNATE_BUTLAST                L"sem?ltimo"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           L"crieBot?o"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           L"apagueBot?o"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           L"ativeBot?o"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           L"atualizeBot?o"
#define LOCALIZED_ALTERNATE_BUTTONP                L"?bot?o?"
#define LOCALIZED_ALTERNATE_BUTTON_                L"ebotao?"
#define LOCALIZED_ALTERNATE_BYE                    L"adeus"
#define LOCALIZED_ALTERNATE_CATCH                  L"pegue"
#define LOCALIZED_ALTERNATE_CHAR                   L"car"
#define LOCALIZED_ALTERNATE_CHDIR                  L"mudeDir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         L"crieCaixamarca??o"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         L"apagueCaixamarca??o"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         L"ativeCaixamarca??o"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            L"estadoCaixamarca??o"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            L"mudeCaixamarca??o"
#define LOCALIZED_ALTERNATE_CLEAN                  L"apagueDesenho"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           L"limpePaleta"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            L"tartaruga"
#define LOCALIZED_ALTERNATE_CLEARTEXT              L"limpeJanelaComandos"
#define LOCALIZED_ALTERNATE_CLEARTIMER             L"desativeTemporizador"
#define LOCALIZED_ALTERNATE_CLOSE                  L"fechearq"
#define LOCALIZED_ALTERNATE_CLOSEALL               L"fecheTodosArq"
#define LOCALIZED_ALTERNATE_CO                     L"co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      L"adicionenaCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         L"crieCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         L"apagueCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         L"ativeCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   L"retiredaCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        L"leiatextoCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        L"mudetextoCaixaCombo"
#define LOCALIZED_ALTERNATE_CONTENTS               L"desenterrados"
#define LOCALIZED_ALTERNATE_CONTINUE               L"continue"
#define LOCALIZED_ALTERNATE_COPYDEF                L"copieDef"
#define LOCALIZED_ALTERNATE_COS                    L"cos"
#define LOCALIZED_ALTERNATE_COUNT                  L"conteItem" //"numelem"
#define LOCALIZED_ALTERNATE_CS                     L"tat"
#define LOCALIZED_ALTERNATE_CT                     L"ljc"
#define LOCALIZED_ALTERNATE_CURSOR                 L"cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           L"rastreieJanela"
#define LOCALIZED_ALTERNATE_DEFINE                 L"defina"
#define LOCALIZED_ALTERNATE_DEFINEDP               L"?definido?"
#define LOCALIZED_ALTERNATE_DEFINED_               L"edef?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           L"crieDi?logo"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           L"ativeDi?logo"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           L"apagueDi?logo"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         L"di?logoAbreArq"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         L"di?logoSalveArq"
#define LOCALIZED_ALTERNATE_DIFFERENCE             L"diferen?a"
#define LOCALIZED_ALTERNATE_DIRECTORIES            L"diret?rios"
#define LOCALIZED_ALTERNATE_DLLCALL                L"chameDLL"
#define LOCALIZED_ALTERNATE_DLLFREE                L"libereDLL"
#define LOCALIZED_ALTERNATE_DLLLOAD                L"carregueDLL"
#define LOCALIZED_ALTERNATE_DOWN                   L"baixenz"
#define LOCALIZED_ALTERNATE_DOWNPITCH              L"baixeNariz"
#define LOCALIZED_ALTERNATE_DRIBBLE                L"registre"
#define LOCALIZED_ALTERNATE_ED                     L"ed"
#define LOCALIZED_ALTERNATE_EDIT                   L"edite"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             L"arcoElipse"
#define LOCALIZED_ALTERNATE_EMPTYP                 L"?vazia?"
#define LOCALIZED_ALTERNATE_EMPTY_                 L"evazia?"
#define LOCALIZED_ALTERNATE_EOFP                   L"efimarq?"
#define LOCALIZED_ALTERNATE_EOF_                   L"?fimarq?"
#define LOCALIZED_ALTERNATE_EQUALP                 L"s?oiguais?"
#define LOCALIZED_ALTERNATE_EQUAL_                 L"saoig?"
#define LOCALIZED_ALTERNATE_ER                     L"el"
#define LOCALIZED_ALTERNATE_ERASE                  L"apague"
#define LOCALIZED_ALTERNATE_ERASEFILE              L"apagueArquivo"
#define LOCALIZED_ALTERNATE_ERF                    L"apagueArq"
#define LOCALIZED_ALTERNATE_ERROR                  L"erro"
#define LOCALIZED_ALTERNATE_EVENTCHECK             L"verifiqueEventos"
#define LOCALIZED_ALTERNATE_EXP                    L"exp"
#define LOCALIZED_ALTERNATE_FD                     L"pf"
#define LOCALIZED_ALTERNATE_FENCE                  L"ponhalimite"
#define LOCALIZED_ALTERNATE_FILL                   L"pinte"
#define LOCALIZED_ALTERNATE_FILES                  L"arquivos"
#define LOCALIZED_ALTERNATE_FIRST                  L"primeiro"
#define LOCALIZED_ALTERNATE_FIRSTS                 L"primeiros"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             L"cordePreenchimento"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          L"tiposDeLetra"
#define LOCALIZED_ALTERNATE_FOREVER                L"parasempre"
#define LOCALIZED_ALTERNATE_FORM                   L"formatoN?mero"
#define LOCALIZED_ALTERNATE_FORWARD                L"parafrente"
#define LOCALIZED_ALTERNATE_FPUT                   L"juntenoIn?cio"
#define LOCALIZED_ALTERNATE_FS                     L"tc"
#define LOCALIZED_ALTERNATE_FULLSCREEN             L"telaCheia"
#define LOCALIZED_ALTERNATE_FULLTEXT               L"todoTexto"
#define LOCALIZED_ALTERNATE_GETFOCUS               L"foco"
#define LOCALIZED_ALTERNATE_GOTO                   L"v?Para"
#define LOCALIZED_ALTERNATE_GIFLOAD                L"carregueGif"
#define LOCALIZED_ALTERNATE_GIFSIZE                L"tamGif"
#define LOCALIZED_ALTERNATE_GIFSAVE                L"salveGif"
#define LOCALIZED_ALTERNATE_GPROP                  L"propriedade"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          L"maior.ou.igual?"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          L"maiorig?"
#define LOCALIZED_ALTERNATE_GREATERP               L"?maior?"
#define LOCALIZED_ALTERNATE_GREATER_               L"maior?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         L"criecaixagrupo"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         L"apaguecaixagrupo"
#define LOCALIZED_ALTERNATE_HALT                   L"paretudo"
#define LOCALIZED_ALTERNATE_HASOWNPENP             L"hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             L"hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                L"dire??o"
#define LOCALIZED_ALTERNATE_HELP                   L"ajuda"
#define LOCALIZED_ALTERNATE_HIDETURTLE             L"oculteTat"
#define LOCALIZED_ALTERNATE_HOME                   L"paracentro"
#define LOCALIZED_ALTERNATE_HT                     L"ot"
#define LOCALIZED_ALTERNATE_IF                     L"se"
#define LOCALIZED_ALTERNATE_IFELSE                 L"seSen?o"
#define LOCALIZED_ALTERNATE_IFF                    L"sef"
#define LOCALIZED_ALTERNATE_IFFALSE                L"seFalso"
#define LOCALIZED_ALTERNATE_IFT                    L"sev"
#define LOCALIZED_ALTERNATE_IFTRUE                 L"seVerd"
#define LOCALIZED_ALTERNATE_INGAMEPORT             L"portaJoystick"
#define LOCALIZED_ALTERNATE_INPORT                 L"portaEntrada"
#define LOCALIZED_ALTERNATE_INPORTB                L"portaEntradab"
#define LOCALIZED_ALTERNATE_INT                    L"inteiro"
#define LOCALIZED_ALTERNATE_ITEM                   L"item"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            L"desativeTecla"
#define LOCALIZED_ALTERNATE_KEYBOARDON             L"ativeTecla"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          L"asciiTecla"
#define LOCALIZED_ALTERNATE_KEYP                   L"tecla?"
#define LOCALIZED_ALTERNATE_KEY_                   L"temarq"
#define LOCALIZED_ALTERNATE_LABEL                  L"rotule"
#define LOCALIZED_ALTERNATE_LABELFONT              L"tiporotule"
#define LOCALIZED_ALTERNATE_LABELSIZE              L"tamanhorotule"
#define LOCALIZED_ALTERNATE_LAST                   L"?ltimo"
#define LOCALIZED_ALTERNATE_LEFT                   L"paraesquerda"
#define LOCALIZED_ALTERNATE_LEFTROLL               L"roleparaesquerda"
#define LOCALIZED_ALTERNATE_LESSEQUALP             L"menor.ou.igual?"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             L"menorig?"
#define LOCALIZED_ALTERNATE_LESSP                  L"?menor?"
#define LOCALIZED_ALTERNATE_LESS_                  L"menor?"
#define LOCALIZED_ALTERNATE_LIGHT                  L"luz"
#define LOCALIZED_ALTERNATE_LIST                   L"lista"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       L"adicioneCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          L"crieCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          L"ativeCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          L"apagueCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    L"retiredaCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       L"selecioneCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTP                  L"?lista?"
#define LOCALIZED_ALTERNATE_LIST_                  L"elista?"
#define LOCALIZED_ALTERNATE_LN                     L"ln"
#define LOCALIZED_ALTERNATE_LOAD                   L"carregue"
#define LOCALIZED_ALTERNATE_LOCAL                  L"local"
#define LOCALIZED_ALTERNATE_LOG10                  L"log"
#define LOCALIZED_ALTERNATE_LOGOVERSION            L"vers?oLogo"
#define LOCALIZED_ALTERNATE_LOWERCASE              L"min?sculas"
#define LOCALIZED_ALTERNATE_LPUT                   L"juntenofim"
#define LOCALIZED_ALTERNATE_LR                     L"rolepe"
#define LOCALIZED_ALTERNATE_LSHIFT                 L"desloquebitsl"
#define LOCALIZED_ALTERNATE_LT                     L"pe"
#define LOCALIZED_ALTERNATE_MACHINE                L"meupc"
#define LOCALIZED_ALTERNATE_MACROP                 L"?macro?"
#define LOCALIZED_ALTERNATE_MACRO_                 L"emacro?"
#define LOCALIZED_ALTERNATE_MAKE                   L"atribua"
#define LOCALIZED_ALTERNATE_MCI                    L"mci"
#define LOCALIZED_ALTERNATE_MEMBER                 L"membro"
#define LOCALIZED_ALTERNATE_MEMBERP                L"?membro?"
#define LOCALIZED_ALTERNATE_MEMBER_                L"emembro?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             L"mensagem"
#define LOCALIZED_ALTERNATE_MIDICLOSE              L"fecheMidi"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            L"mensagemMidi"
#define LOCALIZED_ALTERNATE_MIDIOPEN               L"abraMidi"
#define LOCALIZED_ALTERNATE_MINUS                  L"oposto"
#define LOCALIZED_ALTERNATE_MKDIR                  L"crieDir"
#define LOCALIZED_ALTERNATE_MODULO                 L"m?dulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               L"ativeMouse"
#define LOCALIZED_ALTERNATE_MOUSEON                L"desativeMouse"
#define LOCALIZED_ALTERNATE_MOUSEPOS               L"posMouse"
#define LOCALIZED_ALTERNATE_NAMEP                  L"?nome?"
#define LOCALIZED_ALTERNATE_NAME_                  L"enome?"
#define LOCALIZED_ALTERNATE_NAMES                  L"nomes"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           L"recuseRede" // "n?oaceiteconex?o"
#define LOCALIZED_ALTERNATE_NETACCEPTON            L"aceiteRede" // "aceiteconex?o"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  L"recebaValorRedeAceita" // "Recebavalorconex?oaceita"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     L"envieValorRedeAceita" // "Envievalorconex?oaceita"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          L"desconecteRede" // "desligueConex?o"
#define LOCALIZED_ALTERNATE_NETCONNECTON           L"conecteRede" // "ligueConex?o"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE L"recebavalorRede" // "recebavalorconex?o"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    L"envieValorRede" // "envievalorconex?o"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            L"termineRede"
#define LOCALIZED_ALTERNATE_NETSTARTUP             L"inicieRede" // "inicializeRede"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         L"semtatbmp"
#define LOCALIZED_ALTERNATE_NODES                  L"n?s"
#define LOCALIZED_ALTERNATE_NODRIBBLE              L"n?oregistre"
#define LOCALIZED_ALTERNATE_NOSTATUS               L"semEstado"
#define LOCALIZED_ALTERNATE_NOT                    L"n?o"
#define LOCALIZED_ALTERNATE_NOTEQUALP              L"s?odiferentes?"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              L"saodif?"
#define LOCALIZED_ALTERNATE_NOYIELD                L"monotarefa"
#define LOCALIZED_ALTERNATE_NUMBERP                L"?n?mero?"
#define LOCALIZED_ALTERNATE_NUMBER_                L"enum?"
#define LOCALIZED_ALTERNATE_OP                     L"dev"
#define LOCALIZED_ALTERNATE_OPENAPPEND             L"abraparaAdicionar"
#define LOCALIZED_ALTERNATE_OPENREAD               L"abraparaLer"
#define LOCALIZED_ALTERNATE_OPENUPDATE             L"abraparaAtualizar"
#define LOCALIZED_ALTERNATE_OPENWRITE              L"abraparaEscrever"
#define LOCALIZED_ALTERNATE_OR                     L"ou"
#define LOCALIZED_ALTERNATE_OUTPORT                L"escrevaPorta"
#define LOCALIZED_ALTERNATE_OUTPORTB               L"escrevaPortab"
#define LOCALIZED_ALTERNATE_OUTPUT                 L"devolva"
#define LOCALIZED_ALTERNATE_PARSE                  L"analise"
#define LOCALIZED_ALTERNATE_PAUSE                  L"pausa"
#define LOCALIZED_ALTERNATE_PC                     L"cl"
#define LOCALIZED_ALTERNATE_PD                     L"pd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PE                     L"ub"
#define LOCALIZED_ALTERNATE_PENCOLOR               L"cordoL?pis"
#define LOCALIZED_ALTERNATE_PENDOWN                L"useL?pis"
#define LOCALIZED_ALTERNATE_PENDOWNP               L"?useL?pis?"
#define LOCALIZED_ALTERNATE_PENDOWN_               L"euseLapis?"
#define LOCALIZED_ALTERNATE_PENERASE               L"useborracha"
#define LOCALIZED_ALTERNATE_PENMODE                L"modoL?pis"
#define LOCALIZED_ALTERNATE_PENPAINT               L"useRisco"
#define LOCALIZED_ALTERNATE_PENPATTERN             L"padr?oL?pis"
#define LOCALIZED_ALTERNATE_PENREVERSE             L"useInversor"
#define LOCALIZED_ALTERNATE_PENSIZE                L"espL"
#define LOCALIZED_ALTERNATE_PENUP                  L"useNada"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            L"Logo3D"
#define LOCALIZED_ALTERNATE_PITCH                  L"dire??oNariz"
#define LOCALIZED_ALTERNATE_PIXEL                  L"pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               L"toqueWave"
#define LOCALIZED_ALTERNATE_PLIST                  L"listaProp"
#define LOCALIZED_ALTERNATE_PLISTS                 L"listaProps"
#define LOCALIZED_ALTERNATE_PO                     L"moDefs" // "mot"
#define LOCALIZED_ALTERNATE_POPDIR                 L"voltedir"
#define LOCALIZED_ALTERNATE_POLYSTART              L"iniciePol?gono"
#define LOCALIZED_ALTERNATE_POLYEND                L"terminePol?gono"
#define LOCALIZED_ALTERNATE_POLYVIEW               L"mostrePol?gono"
#define LOCALIZED_ALTERNATE_PORTCLOSE              L"fechePorta"
#define LOCALIZED_ALTERNATE_PORTFLUSH              L"descarregaPorta"
#define LOCALIZED_ALTERNATE_PORTMODE               L"mudemodoPorta"
#define LOCALIZED_ALTERNATE_PORTOPEN               L"abraPorta"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          L"leiaVetorPorta"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           L"leiaCarPorta"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         L"escrevaVetorPorta"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          L"escrevaCarPorta"
#define LOCALIZED_ALTERNATE_POS                    L"pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 L"posxyz"
#define LOCALIZED_ALTERNATE_POT                    L"mostreT?tulo"
#define LOCALIZED_ALTERNATE_POWER                  L"pot?ncia"
#define LOCALIZED_ALTERNATE_PPROP                  L"mudeprop"
#define LOCALIZED_ALTERNATE_PPT                    L"ul"
#define LOCALIZED_ALTERNATE_PR                     L"esc"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             L"?primitiva?"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             L"eprim?"
#define LOCALIZED_ALTERNATE_PRINT                  L"escreva"
#define LOCALIZED_ALTERNATE_PROCEDUREP             L"?procedimento?" // "?definido?"
#define LOCALIZED_ALTERNATE_PROCEDURE_             L"eproced?"
#define LOCALIZED_ALTERNATE_PROPLISTP              L"lProp?"
#define LOCALIZED_ALTERNATE_PROPLIST_              L"lProp?"
#define LOCALIZED_ALTERNATE_PROCEDURES             L"lProcs"
#define LOCALIZED_ALTERNATE_PRODUCT                L"produto"
#define LOCALIZED_ALTERNATE_PU                     L"un"
#define LOCALIZED_ALTERNATE_PX                     L"ui"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            L"caixadeQuest?o"
#define LOCALIZED_ALTERNATE_QUOTIENT               L"quociente"
#define LOCALIZED_ALTERNATE_RADARCCOS              L"arcCosRad"
#define LOCALIZED_ALTERNATE_RADARCSIN              L"arcSenRad"
#define LOCALIZED_ALTERNATE_RADARCTAN              L"arcTanRad"
#define LOCALIZED_ALTERNATE_RADCOS                 L"cosRad"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      L"crieBot?oR?dio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      L"ativeBot?oR?dio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      L"apagueBot?oR?dio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         L"bot?oR?dio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         L"mudeBot?oR?dio"
#define LOCALIZED_ALTERNATE_RADSIN                 L"senRad"
#define LOCALIZED_ALTERNATE_RADTAN                 L"tanRad"
#define LOCALIZED_ALTERNATE_RANDOM                 L"sorteien?mero"
#define LOCALIZED_ALTERNATE_RAWASCII               L"rawascii" // "asciiPuro"
#define LOCALIZED_ALTERNATE_RC                     L"leiacar"
#define LOCALIZED_ALTERNATE_RCS                    L"leiacars"
#define LOCALIZED_ALTERNATE_READCHAR               L"leiaCaractere"
#define LOCALIZED_ALTERNATE_READCHARS              L"leiaCaracteres"
#define LOCALIZED_ALTERNATE_READER                 L"arqLeitura"
#define LOCALIZED_ALTERNATE_READLIST               L"leiaLista"
#define LOCALIZED_ALTERNATE_READPOS                L"readpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READRAWLINE            L"readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               L"leiaPalavra"
#define LOCALIZED_ALTERNATE_REMAINDER              L"resto"
#define LOCALIZED_ALTERNATE_REMPROP                L"retireProp"
#define LOCALIZED_ALTERNATE_REPCOUNT               L"conteVezes"
#define LOCALIZED_ALTERNATE_REPEAT                 L"repita"
#define LOCALIZED_ALTERNATE_RERANDOM               L"repitasorteie"
#define LOCALIZED_ALTERNATE_RIGHT                  L"paradireita"
#define LOCALIZED_ALTERNATE_RIGHTROLL              L"roleparadireita"
#define LOCALIZED_ALTERNATE_RL                     L"rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  L"apagueDir"
#define LOCALIZED_ALTERNATE_ROLL                   L"dire??oRolagem"
#define LOCALIZED_ALTERNATE_ROUND                  L"arredonde"
#define LOCALIZED_ALTERNATE_RR                     L"rolepd"
#define LOCALIZED_ALTERNATE_RT                     L"pd"
#define LOCALIZED_ALTERNATE_RUN                    L"fa?a"
#define LOCALIZED_ALTERNATE_RUNPARSE               L"fa?aAnalise"
#define LOCALIZED_ALTERNATE_RUNRESULT              L"fa?aDevolva"
#define LOCALIZED_ALTERNATE_RW                     L"leiap"
#define LOCALIZED_ALTERNATE_SAVE                   L"salve"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            L"cordofundo"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        L"crieBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        L"ativeBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        L"apagueBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           L"barraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           L"mudeBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLX                L"rolex"
#define LOCALIZED_ALTERNATE_SCROLLY                L"roley"
#define LOCALIZED_ALTERNATE_SCRUNCH                L"propor??o"
#define LOCALIZED_ALTERNATE_SE                     L"fr"
#define LOCALIZED_ALTERNATE_SELECTBOX              L"caixasele??o"
#define LOCALIZED_ALTERNATE_SENTENCE               L"frase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          L"mude?reaAtiva"
#define LOCALIZED_ALTERNATE_SETBITINDEX            L"mude?ndicebmp"
#define LOCALIZED_ALTERNATE_SETBITMODE             L"mudeModobmp"
#define LOCALIZED_ALTERNATE_SETCLIP                L"mudeClip"
#define LOCALIZED_ALTERNATE_SETCURSOR              L"mudeCursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        L"mudeCursorSeta"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          L"mudeCursorEspera"
#define LOCALIZED_ALTERNATE_SETFC                  L"mudecp"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          L"mudeCordePreenchimento"
#define LOCALIZED_ALTERNATE_SETFOCUS               L"mudeFoco"
#define LOCALIZED_ALTERNATE_SETH                   L"mudedc"
#define LOCALIZED_ALTERNATE_SETHEADING             L"mudeDire??o"
#define LOCALIZED_ALTERNATE_SETITEM                L"mudeItem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           L"mudeTipo"
#define LOCALIZED_ALTERNATE_SETLIGHT               L"mudeLuz"
#define LOCALIZED_ALTERNATE_SETMARGINS             L"mudeMargens"
#define LOCALIZED_ALTERNATE_SETPC                  L"mudeCL"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            L"mudeCordoL?pis"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          L"mudePadr?oL?pis"
#define LOCALIZED_ALTERNATE_SETPENSIZE             L"mudeEspL"
#define LOCALIZED_ALTERNATE_SETPITCH               L"mudeDire??oNariz"
#define LOCALIZED_ALTERNATE_SETPIXEL               L"mudePixel"
#define LOCALIZED_ALTERNATE_SETPOS                 L"mudePos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              L"mudeposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                L"mudeLeitura"
#define LOCALIZED_ALTERNATE_SETREADPOS             L"mudePosLeitura"
#define LOCALIZED_ALTERNATE_SETROLL                L"mudeDire??oRolagem"
#define LOCALIZED_ALTERNATE_SETSC                  L"mudeCF"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         L"mudeCordoFundo"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             L"mudePropor??o"
#define LOCALIZED_ALTERNATE_SETTIMER               L"mudeTemporizador" // "mudecontador"
#define LOCALIZED_ALTERNATE_SETTURTLE              L"ativetat"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          L"mudeModoTat"
#define LOCALIZED_ALTERNATE_SETWRITE               L"mudeEscrita"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            L"mudePosEscrita"
#define LOCALIZED_ALTERNATE_SETX                   L"mudex"
#define LOCALIZED_ALTERNATE_SETXY                  L"mudexy"
#define LOCALIZED_ALTERNATE_SETXYZ                 L"mudexyz"
#define LOCALIZED_ALTERNATE_SETY                   L"mudey"
#define LOCALIZED_ALTERNATE_SETZ                   L"mudez"
#define LOCALIZED_ALTERNATE_SHELL                  L"shell"
#define LOCALIZED_ALTERNATE_SHOW                   L"mostre"
#define LOCALIZED_ALTERNATE_SHOWNP                 L"?vis?vel?"
#define LOCALIZED_ALTERNATE_SHOWN_                 L"evisivel?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             L"mostreTat"
#define LOCALIZED_ALTERNATE_SIN                    L"sen"
#define LOCALIZED_ALTERNATE_SOUND                  L"som"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            L"fixeJanelaComandos"
#define LOCALIZED_ALTERNATE_SQRT                   L"raizq"
#define LOCALIZED_ALTERNATE_SS                     L"fixeJC"
#define LOCALIZED_ALTERNATE_ST                     L"mt"
#define LOCALIZED_ALTERNATE_STANDOUT               L"standout" //
#define LOCALIZED_ALTERNATE_STATICCREATE           L"crieEst?tico"
#define LOCALIZED_ALTERNATE_STATICDELETE           L"apagueEst?tico"
#define LOCALIZED_ALTERNATE_STATICUPDATE           L"mudeEst?tico"
#define LOCALIZED_ALTERNATE_STATUS                 L"estado"
#define LOCALIZED_ALTERNATE_STEP                   L"siga" //"passoapasso"
#define LOCALIZED_ALTERNATE_STEPPED                L"seguidos"
#define LOCALIZED_ALTERNATE_STOP                   L"pare"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             L"?subseq??ncia?"
#define LOCALIZED_ALTERNATE_SUBSTRING_             L"esubseq?"
#define LOCALIZED_ALTERNATE_SUM                    L"soma"
#define LOCALIZED_ALTERNATE_TAG                    L"etiqueta"
#define LOCALIZED_ALTERNATE_TAN                    L"tan"
#define LOCALIZED_ALTERNATE_TEST                   L"teste"
#define LOCALIZED_ALTERNATE_TEXT                   L"texto"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             L"libereJanelaComandos"
#define LOCALIZED_ALTERNATE_THING                  L"valor"
#define LOCALIZED_ALTERNATE_THROW                  L"lance"
#define LOCALIZED_ALTERNATE_TIME                   L"diahora"
#define LOCALIZED_ALTERNATE_TIMEMILLI              L"tempoMili"
#define LOCALIZED_ALTERNATE_TO                     L"aprenda"
#define LOCALIZED_ALTERNATE_TONE                   L"tom"
#define LOCALIZED_ALTERNATE_TOWARDS                L"dire??opara"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             L"dire??oparaxyz"
#define LOCALIZED_ALTERNATE_TRACE                  L"rastreie"
#define LOCALIZED_ALTERNATE_TRACED                 L"rastreados"
#define LOCALIZED_ALTERNATE_TS                     L"libereJC"
#define LOCALIZED_ALTERNATE_TURTLE                 L"tatativa"
#define LOCALIZED_ALTERNATE_TURTLEMODE             L"modoTat"
#define LOCALIZED_ALTERNATE_TURTLES                L"tartarugas"
#define LOCALIZED_ALTERNATE_TYPE                   L"guardeparaescrever"
#define LOCALIZED_ALTERNATE_UNBURY                 L"desenterre"
#define LOCALIZED_ALTERNATE_UNSTEP                 L"n?oSiga" //"n?oPassoaPasso"
#define LOCALIZED_ALTERNATE_UNTRACE                L"n?oRastreie"
#define LOCALIZED_ALTERNATE_UP                     L"levantenz"
#define LOCALIZED_ALTERNATE_UPPERCASE              L"mai?sculas"
#define LOCALIZED_ALTERNATE_UPPITCH                L"levantenariz"
#define LOCALIZED_ALTERNATE_WAIT                   L"espere"
#define LOCALIZED_ALTERNATE_WINDOW                 L"semlimite"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           L"crieJanela"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           L"ativeJanela"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           L"apagueJanela"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         L"janelaediteArquivo"
#define LOCALIZED_ALTERNATE_WINDOWSET              L"mudeEstadoJanela"
#define LOCALIZED_ALTERNATE_WINHELP                L"socorro"
#define LOCALIZED_ALTERNATE_WORD                   L"palavra"
#define LOCALIZED_ALTERNATE_WORDP                  L"?palavra?"
#define LOCALIZED_ALTERNATE_WORD_                  L"epal?"
#define LOCALIZED_ALTERNATE_WRAP                   L"dobrejanela"
#define LOCALIZED_ALTERNATE_WRITEPOS               L"posLeitura"
#define LOCALIZED_ALTERNATE_WRITER                 L"arqescrita"
#define LOCALIZED_ALTERNATE_YESNOBOX               L"CaixaSimN?o"
#define LOCALIZED_ALTERNATE_YIELD                  L"multiTarefa"
#define LOCALIZED_ALTERNATE_ZOOM                   L"zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      L"&OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  L"&Cancelar"
#define LOCALIZED_GENERAL_APPLYBUTTON   L"&Aplicar"

#define LOCALIZED_GENERAL_PRODUCTNAME   L"FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  L"O ambiente de programa??o FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  L"&Arquivo"
#define LOCALIZED_FILE_NEW              L"&Novo\t(apaga o trabalho atual)"
#define LOCALIZED_FILE_LOAD             L"&Carregar...\t(une ao trabalho atual)"
#define LOCALIZED_FILE_OPEN             L"A&brir...\t(substitui o trabalho atual)"
#define LOCALIZED_FILE_SAVE             L"&Guardar"
#define LOCALIZED_FILE_SAVEAS           L"G&uardar como..."
#define LOCALIZED_FILE_SETASSCREENSAVER L"Coloque como Protetor de &Tela"
#define LOCALIZED_FILE_EDIT             L"&Editar..."
#define LOCALIZED_FILE_ERASE            L"A&pagar..."
#define LOCALIZED_FILE_EXIT             L"&Sair"

#define LOCALIZED_BITMAP               L"&Bitmap"
#define LOCALIZED_BITMAP_NEW           L"&Novo"
#define LOCALIZED_BITMAP_LOAD          L"&Carregar..."
#define LOCALIZED_BITMAP_SAVE          L"&Guardar"
#define LOCALIZED_BITMAP_SAVEAS        L"G&uardar como..."
#define LOCALIZED_BITMAP_PRINT         L"&Imprimir..."
#define LOCALIZED_BITMAP_PRINTERSETUP  L"C&onfigurar p?gina..."
#define LOCALIZED_BITMAP_ACTIVEAREA    L"?rea &Ativa..."

#define LOCALIZED_SET                  L"&Configurar"
#define LOCALIZED_SET_PENSIZE          L"&Tamanho do l?pis..."
#define LOCALIZED_SET_LABELFONT        L"Tipo de letra para &r?tulo..."
#define LOCALIZED_SET_COMMANDERFONT    L"Tipo de letra para &comandos..."
#define LOCALIZED_SET_PENCOLOR         L"Cor de &l?pis..."
#define LOCALIZED_SET_FLOODCOLOR       L"Cor de &preenchimento..."
#define LOCALIZED_SET_SCREENCOLOR      L"Color de &fundo..."

#define LOCALIZED_ZOOM                 L"&Zoom"
#define LOCALIZED_ZOOM_IN              L"&Ampliar"
#define LOCALIZED_ZOOM_OUT             L"&Reduzir"
#define LOCALIZED_ZOOM_NORMAL          L"&Normal"

#define LOCALIZED_HELP                 L"A&juda"
#define LOCALIZED_HELP_INDEX           L"&In?cio"
#define LOCALIZED_HELP_TUTORIAL        L"&Tutorial"
#define LOCALIZED_HELP_DEMO            L"&Demo"
#define LOCALIZED_HELP_EXAMPLE         L"&Exemplos"
#define LOCALIZED_HELP_RELEASENOTES    L"&Notas da vers?o"
#define LOCALIZED_HELP_ABOUTFMSLOGO    L"&Sobre o " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              L"Sobre o &FMS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   L"Portugu?s para Ingl?s"
#define LOCALIZED_HELP_ENGLISHTOLANG   L"Ingl?s para Portugu?s"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              L"Selecionar ?rea activa"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       L"Isto afeta a impress?o e grava??o de bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        L"Y-Sup"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         L"Y-Inf"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        L"X-Sup"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         L"X-Inf"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH L"pontos por polegada impressa:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        L"&Restaurar"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       L"Protetor de tela de FMSLogo"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    L"Protetor de tela de FMSLogo"
#define LOCALIZED_SCREENSAVER_LOCATE            L"&Localize ..."
#define LOCALIZED_SCREENSAVER_FILE              L"Logo &Arquivo:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               L"Selecione uma instru??o de " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED L"O espa?o de trabalho n?o possui uma lista de instru??o de " LOCALIZED_ALTERNATE_STARTUP " definida, nada vai\nacontecer quando o protetor de tela ? carregado.\nPor favor, selecione um procedimento para executar quando o programa ? carregado."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   L"A vari?vel " LOCALIZED_ALTERNATE_STARTUP " n?o ? uma lista, nada vai\nacontecer quando o protetor de tela ? carregado.\nPor favor, selecione um procedimento para executar quando o programa ? carregado."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     L"Seu espa?o de trabalho tem uma lista de instru??o de vazio " LOCALIZED_ALTERNATE_STARTUP " definida, nada vai\nacontecer quando o protetor de tela ? carregado.\nPor favor, selecione um procedimento para executar quando o programa ? carregado."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   L"N?o h? procedimentos definidos"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              L"N?o h? nenhum procedimentos, vari?veis ou listas de propriedades definidas,\nassim que o espa?o de trabalho ser? salvo como um arquivo vazio.\n\nVoc? quer salvar o espa?o de trabalho de qualquer maneira?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     L"Copiar"
#define LOCALIZED_POPUP_CUT                      L"Cortar"
#define LOCALIZED_POPUP_PASTE                    L"Colar"
#define LOCALIZED_POPUP_DELETE                   L"Apagar"
#define LOCALIZED_POPUP_UNDO                     L"Desfazer"
#define LOCALIZED_POPUP_REDO                     L"Refazer"
#define LOCALIZED_POPUP_SELECTALL                L"Selecionar Tudo"
#define LOCALIZED_POPUP_HELP                     L"Busca por Tema"
#define LOCALIZED_POPUP_REMOVELINES              L"Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   L"Editor"

#define LOCALIZED_EDITOR_FILE                    L"&Arquivo"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        L"&Guardar e Sair\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    L"Guardar na &?rea de trabalho"
#define LOCALIZED_EDITOR_FILE_PRINT              L"&Imprimir..."
#define LOCALIZED_EDITOR_FILE_EXIT               L"&Sair"

#define LOCALIZED_EDITOR_EDIT                    L"&Editar"
#define LOCALIZED_EDITOR_EDIT_UNDO               L"&Desfazer\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               L"&Refazer\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                L"Recor&tar\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               L"&Copiar\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              L"Co&lar\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             L"&Apagar\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           L"Apagar &tudo\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          L"&Selecionar Tudo\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  L"&Buscar"
#define LOCALIZED_EDITOR_SEARCH_FIND             L"&Localizar...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          L"&Substituir...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             L"&Pr?ximo\tF3"

#define LOCALIZED_EDITOR_SET                     L"&Configurar"
#define LOCALIZED_EDITOR_SET_FONT                L"&Tipo de letra..."

#define LOCALIZED_EDITOR_TEST                    L"&Testar"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      L"&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    L"Aj&uda"
#define LOCALIZED_EDITOR_HELP_INDEX              L"?&ndice"
#define LOCALIZED_EDITOR_HELP_EDITOR             L"&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        L"&Busca contextual\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    L"&Guardar e Sair"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       L"&N?o guardar"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       L"H? altera??es n?o salvas em sua ?rea de trabalho. Se sair sem guardar, estas altera??es ser?o perdidas."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       L"Deseja guardar suas altera??es antes de sair?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     L"Janela de Comandos"
#define LOCALIZED_COMMANDER_HALT                L"PareTudo"
#define LOCALIZED_COMMANDER_TRACE               L"Rastreie"
#define LOCALIZED_COMMANDER_NOTRACE             L"N?o Rastreie"
#define LOCALIZED_COMMANDER_PAUSE               L"Pause"
#define LOCALIZED_COMMANDER_STATUS              L"Estado"
#define LOCALIZED_COMMANDER_NOSTATUS            L"SemEstado"
#define LOCALIZED_COMMANDER_STEP                L"Siga"
#define LOCALIZED_COMMANDER_UNSTEP              L"N?oSiga"
#define LOCALIZED_COMMANDER_RESET               L"Tat"
#define LOCALIZED_COMMANDER_EXECUTE             L"Execute"
#define LOCALIZED_COMMANDER_EDALL               L"EdTudo"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        L"Estado"
#define LOCALIZED_STATUS_PEN                    L"L?pis"
#define LOCALIZED_STATUS_CONTACT                L"Contato:"
#define LOCALIZED_STATUS_WIDTH                  L"Largura:"
#define LOCALIZED_STATUS_STYLE                  L"Estilo:"
#define LOCALIZED_STATUS_ORIENTATION            L"Orienta??o"
#define LOCALIZED_STATUS_PITCH                  L"Cabeceio:"
#define LOCALIZED_STATUS_HEADING                L"Dire??o:"
#define LOCALIZED_STATUS_ROLL                   L"Rolamento:"
#define LOCALIZED_STATUS_TURTLE                 L"Tartaruga"
#define LOCALIZED_STATUS_POSITION               L"Posi??o(XYZ):"
#define LOCALIZED_STATUS_WHICH                  L"Tat Ativa:"
#define LOCALIZED_STATUS_VISIBILITY             L"Visibilidade:"
#define LOCALIZED_STATUS_COLOR                  L"Cor"
#define LOCALIZED_STATUS_PENCOLOR               L"L?pis(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             L"Preenchimento(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            L"Fundo(RGB):"
#define LOCALIZED_STATUS_KERNEL                 L"N?cleo"
#define LOCALIZED_STATUS_CALLS                  L"Chamadas:"
#define LOCALIZED_STATUS_PEAKMEMORY             L"Mem?ria:"

#define LOCALIZED_STATUS_PENREVERSE     L"Invertido"
#define LOCALIZED_STATUS_PENNORMAL      L"Normal"
#define LOCALIZED_STATUS_PENERASE       L"Borracha"
#define LOCALIZED_STATUS_PENUP          L"Erguido"
#define LOCALIZED_STATUS_PENDOWN        L"Baixado"
#define LOCALIZED_STATUS_PENSHOWN       L"Vis?vel"
#define LOCALIZED_STATUS_PENHIDDEN      L"Oculta"
#define LOCALIZED_STATUS_POLYGONS       L"Pol?gonos"
#define LOCALIZED_STATUS_VECTORS        L"Vetores"
#define LOCALIZED_STATUS_NODES          L"N?s"
#define LOCALIZED_STATUS_NOT_APPLICABLE L"N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           L"&Tudo"
#define LOCALIZED_ERASEPROCEDURE                L"Apagar"
#define LOCALIZED_EDITPROCEDURE                 L"Editar"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     L"Mudar Cor"
#define LOCALIZED_SETCOLOR_PENCOLOR            L"Cor do L?pis"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          L"Cor de Preenchimento"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         L"Cor de Fundo"
#define LOCALIZED_SETCOLOR_RED                 L"Vermelho"
#define LOCALIZED_SETCOLOR_GREEN               L"Verde"
#define LOCALIZED_SETCOLOR_BLUE                L"Azul"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   L"Tamanho do L?pis"
#define LOCALIZED_SETPENSIZE_SIZE              L"Espessura"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     L"Sobre o " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             L"Vers?o"
#define LOCALIZED_ABOUTFMS_GUI                 L"GUI por George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                L"N?cleo por Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           L"Instalador baseado no Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           L"Recursos para Logo em Portugu?s\nDispon?veis em http://mondragon.angeltowns.net/paradiso/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       L"Agradecimento a Yehuda Katz e a Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME L" ? software livre\nVer a Licen?a P?blica GNU"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           L"Perguntas, coment?rios, sugest?es?\nParticipe da lista Logo em Espanhol\nhttp://mondragon.angeltowns.net/paradiso/ListaLogo.html"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     L"Tradu??o feita por Alexandre R. Soares"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      L"Sobre o FMS"
#define LOCALIZED_ABOUTMS_FMS                  L"FMS quer dizer Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     L"Considere fazer uma doa??o ?\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  L"As mudan?as da edi??o podem ser perdidas.\n\nRealmente quer sair do " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      L"Uma sess?o de edi??o est? ativa"

#define LOCALIZED_COULDNOTWRITEBMP            L"N?o pude guardar .bmp"
#define LOCALIZED_COULDNOTOPENBMP             L"N?o pude abrir .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           L"N?o pude criar bitmat tipo Windows 3.0"
#define LOCALIZED_NOTVALIDBMP                 L"N?o ? um bitmap tipo Windows 3.0"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         L"N?o foi guardado no disco"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     L"Escolher Novo apagar? todas as defini??es.\n\nContinuar com Novo?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE L"O arquivo que est? sendo carregado ser? unido ao seu trabalho atual\ne substituir? suas altera??es n?o guardadas.\n\nContinuar com Carregar?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    L"Isto apagar? todas as suas altera??es n?o guardadas.\n\nContinuar com Abrir?"

#define LOCALIZED_EDITORISOPEN                  L"Sabia que est? com uma sess?o de edi??o ativa?\n\nToda altera??o nesta sess?o de edi??o n?o ser? guardada."

#define LOCALIZED_ERROR_CANTREADFILE            L"N?o posso ler o arquivo \"%s\" do disco"
#define LOCALIZED_ERROR_CANTWRITEFILE           L"N?o posso escrever o arquivo \"%s\" no disco"

#define LOCALIZED_SAVETOWORKSPACE                L"Guardar na ?rea de trabalho"
#define LOCALIZED_CONTENTSCHANGED                L"O conte?do foi alterado"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE L"O conte?do foi alterado.\nDeseja guard?-los na ?rea de trabalho?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  L"Houve um erro ao guardar o conte?do do editor na ?rea de trabalho.  O cursor ser? posicionado ante a ?ltima defini??o correta.\n\nVerifique uma poss?vel mensagem de erro na ?rea de Comandos."
#define LOCALIZED_RETURNTOEDIT                  L"Voltar ao editor?"

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

#define LOCALIZED_LOGO_FILE_EXTENSION L"lgo"
#define LOCALIZED_FILEFILTER_ALLFILES L"Todos os Arquivos (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     L"Arquivos do Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    L"Arquivos Bitmap (*.bmp)|*.bmp|Arquivos GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             L" interrompido\n"
#define LOCALIZED_TRACING_OUTPUTS           L" devolve %s\n"
#define LOCALIZED_TRACING_MAKE              L"atribua %s %s"
#define LOCALIZED_TRACING_PPROP             L"mudePROP %s %s %s"
#define LOCALIZED_TRACING_LOCATION          L" em %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  L"Passo Simples"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  L"%s definido\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    L"Borracha"
#define LOCALIZED_PENMODE_REVERSE  L"UseInversor"
#define LOCALIZED_PENMODE_PAINT    L"UseL?pis"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          L"Logo: Erro Interno Fatal"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       L"Logo: Falta de Mem?ria"
#define LOCALIZED_ERROR_OUTOFMEMORY            L"sem espa?o"
#define LOCALIZED_ERROR_STACKOVERFLOW          L"esvaziamento de pilha"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      L"tat fora dos limites"
#define LOCALIZED_ERROR_BADGRAPHINIT           L"n?o pude inicializar gr?fico"
#define LOCALIZED_ERROR_BADDATA                L"%p n?o sabe o que fazer com %s"
#define LOCALIZED_ERROR_DIDNTOUTPUT            L"%p n?o devolveu nada para %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        L"%p necessita de algum complemento"
#define LOCALIZED_ERROR_TOOMUCH                L"muitas coisas entre par?nteses ()"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    L"Voc? n?o disse o que devo fazer com %s"
#define LOCALIZED_ERROR_PARENMISMATCH          L"muitos par?nteses '('"
#define LOCALIZED_ERROR_NOVALUE                L"%s n?o possui um valor"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        L"par?nteses ')' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      L"colchete ']' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        L"chave '}' inesperada"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          L"n?o sei como fazer %p"
#define LOCALIZED_ERROR_NOCATCHTAG             L"n?o pude encontrar a etiqueta LANCE (THROW) para %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         L"%p j? est? definido"
#define LOCALIZED_ERROR_STOPPING               L"Parando..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       L"ECO est? ativado"
#define LOCALIZED_ERROR_FILESYSTEM                   L"Erro do sistema de arquivos: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          L"N?o pude abrir esse arquivo"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         L"N?o pude abrir o arquivo: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       L"Arquivo j? est? aberto"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           L"Arquivo n?o est? aberto"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  L"N?o pude criar arquivo para editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   L"N?o pude iniciar editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    L"N?o pude ler arquivo do editor"
#define LOCALIZED_ERROR_IFWARNING              L"Creio que queira usar SESEN?O (IFELSE), n?o SEFOR (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          L"%p coberta por local em chamada a procedimento"
#define LOCALIZED_ERROR_USER                   L"PEGUE \"Erro"
#define LOCALIZED_ERROR_ISPRIMITIVE            L"%p ? uma primitiva"
#define LOCALIZED_ERROR_TONOTINSIDE            L"S? ? poss?vel usar APRENDA (TO) dentro de um procedimento"
#define LOCALIZED_ERROR_ATTOPLEVEL             L"S? ? poss?vel usar %p dentro de um procedimento"
#define LOCALIZED_ERROR_ATTOPLEVEL2            L"? necess?rio estar dentro de um procedimento para usar DEVOLVA (OUTPUT) ou PARE (STOP)."
#define LOCALIZED_ERROR_NOTEST                 L"%p sem TESTE"
#define LOCALIZED_ERROR_BADMACROOUTPUT         L"Macro devolveu %s em lugar de uma lista"
#define LOCALIZED_ERROR_DEEPEND                L"FIM dentro de uma instru??o multilinha"
#define LOCALIZED_ERROR_DEEPENDIN              L"FIM dentro de uma instru??o multilinha em %p"
#define LOCALIZED_ERROR_UNKNOWN                L"Estado de erro desconhecido  - erro interno."
#define LOCALIZED_PAUSING                      L"Pausando..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION L"Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             L"cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        L"cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            L"cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                L"%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      L"Erro"
#define LOCALIZED_ERROR_BADINPUT             L"Entrada incorreta"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    L"Entrada sem par"

#define LOCALIZED_ERROR_CANTOPENPORT         L"N?o foi poss?vel ABRIR a porta"
#define LOCALIZED_ERROR_CANTCLOSEPORT        L"N?o foi poss?vel FECHAR a porta"
#define LOCALIZED_ERROR_CANTFLUSHPORT        L"N?o foi poss?vel ESVAZIAR a porta"
#define LOCALIZED_ERROR_CANTDCBONPORT        L"N?o foi poss?vel construir dcb na porta"
#define LOCALIZED_ERROR_CANTSETPORT          L"N?o foi poss?vel mudar a porta"
#define LOCALIZED_ERROR_PORTALREADYOPEN      L"PORTA j? aberta"
#define LOCALIZED_ERROR_PORTNOTOPEN          L"PORTA n?o aberta"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   L"%s j? existe"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    L"%s n?o existe"

#define LOCALIZED_ERROR_DLLNOTLOADED          L"A DLL n?o est? carregada"
#define LOCALIZED_ERROR_DLLLOADFAILED         L"Falha ao carregar a DLL"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    L"Tipo inv?lido de entrada"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  L"Tipo inv?lido de sa?da"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   L"Fun??o n?o encontrada"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  L"Nem todas as entradas est?o emparelhadas"

#define LOCALIZED_ERROR_NETWORK               L"Erro de Rede"
#define LOCALIZED_ERROR_NETWORKRECEIVE        L"Erro de Recep??o de Rede"
#define LOCALIZED_ERROR_NETWORKSEND           L"Erro de Envio de Rede"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       L"Erro Inesperado, a Rede poderia estar inativa"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     L"N?o iniciada"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED L"J? iniciada"
#define LOCALIZED_ERROR_NETWORKALREADYON      L"J? est? pronta"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     L"J? desligada"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         L"Nome muito longo"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      L"N?o inicializado"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      L"O sistema n?o est? pronto"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED L"Vers?o desconhecida"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   L"N?o posso enviar ap?s desativar o soquete"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         L"Chamada o sistema interrompida"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    L"Resposta Autoritativa: Dominio n?o encontrado"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH L"N?o-Autoritativa: Dominio no encontrado. Ver INICIARED"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      L"Erro irrecuper?vel"
#define LOCALIZED_ERROR_NETWORKNODATA              L"Registro de dados n?o dispon?vel"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       L"N?mero de arquivo incorreto"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          L"A opera??o bloquearia"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       L"Opera??o em curso"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   L"Opera??o j? em curso"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          L"Endere?o incorreto"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     L"Necessito endere?o de destino"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      L"Mensagem muito longa"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      L"Famil?a do protocolo desconhecida"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         L"O diret?rio n?o est? vazio"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     L"Atingido limite da aplica??o"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           L"Superado limite do disco"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        L"Muitos arquivos abertos"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        L"Acesso negado"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          L"Opera??o de soquete em algo que n?o ? um soquete"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    L"N?o pude encontrar endere?o pedido"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           L"O endere?o j? est? em uso"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      L"Fam?lia de endere?o n?o ? reconhecida pelo protocolo"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            L"Tempo de tentativa de conex?o excedido"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    L"Tipo de soquete desconhecido"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   L"Protocolo desconhecido"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            L"Sem espa?o na mem?ria tempor?ria"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    L"Soquete j? est? conectado"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        L"Soquete n?o est? conectado"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         L"Op??o de protocolo incorreta"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     L"Conex?o reiniciada pelo interlocutor"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     L"O software ocasionou o fim da conex?o"
#define LOCALIZED_ERROR_NETWORKISDOWN              L"A rede caiu"
#define LOCALIZED_ERROR_NETWORKRESET               L"A rede foi reiniciada"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   L"Conex?o recusada"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          L"Dom?nio caiu"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   L"Dom?nio n?o alcan??vel"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        L"O protocolo ? de tipo equivocado para o soquete"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   L"Opera??o n?o permitida no soquete"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         L"N?o foi encontrada rota para o dom?nio remoto"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         L"Demasiadas refer?ncias"

#define LOCALIZED_ERROR_POLYSTART               L"Erro em IniciePol?gono"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED L"Voc? j? havia iniciado um pol?gono"

#define LOCALIZED_ERROR_POLYEND                 L"Erro em MostrePol?gono"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       L"Voc? n?o iniciou um pol?gono"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     L"? necess?rio ao menos 3 vetores para definir um pol?gono"

#define LOCALIZED_ERROR_SOUND                 L"Erro de Som"

#define LOCALIZED_ERROR_MIDI                  L"Erro de MIDI"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     L"Dispositivo Midi incorreto"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       L"J? est? aberto"
#define LOCALIZED_ERROR_MIDINOTOPEN           L"N?o est? aberto"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      L"N?o h? texto no clipboard"

#define LOCALIZED_ERROR_MCI                   L"Erro de MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         L"Temporizador n?o encontrado"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       L"Ajuda on line n?o dispon?vel pois n?o pude carregar hhctrl.ocx"

#define LOCALIZED_ERROR_BADCOMMANDLINE        L"Linha de comandos incorreta"

#define LOCALIZED_ERROR_TMPNOTDEFINED         L"A vari?vel de ambiente TMP n?o est? definida ou ? incorreta.\n" LOCALIZED_GENERAL_PRODUCTNAME " tentar? usar C:\\ para guardar arquivos tempor?rios"

#define LOCALIZED_ERROR_GIFSAVEFAILED         L"Problema ao criar GIF, revise quantidade de mem?ria ou espa?o em disco"
#define LOCALIZED_ERROR_GIFREADFAILED         L"Problema ao ler GIF, revise quantidade de mem?ria ou espa?o em disco"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  L"?ndice de BitMap fora do campo"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        L"Recortar falhou, possivelmente n?o haja mem?ria suficiente"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    L"Nada para Colar"
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  L"O BitMap no ?ndice deve ser inicializado com um mapa de bits"

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      L"A Tat %d n?o tem figura, farei uma parada"

#define LOCALIZED_ERROR_FONTNOTFOUND            L"N?o encontrei o tipo de letra chamado %s. Escolhe um dos seguintes:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        L"O gerenciador de impress?o n?o conhece esta fun??o"
#define LOCALIZED_ERROR_CANTDRAWIMAGE           L"N?o posso desenhar a imagem"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        L"N?o posso extrair a imagem"
#define LOCALIZED_ERROR_SUBCODE                 L"Subc?digo"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         L"Entrada:"
#define LOCALIZED_PROMPT_TO     L"Modo Para (Cancelar para Finalizar)"
#define LOCALIZED_PROMPT_LIST   L"Modo de Lista (Cancelar para Parar)"
#define LOCALIZED_PROMPT_PAUSE  L"Modo de Pausa (Cancelar para Continuar)"
#define LOCALIZED_PROMPT_INPUT  L"Modo de Entrada (Cancelar para Parar)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      L"Mudado para  \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         L"N?o pude mudar para o diret?rio \"%s\""
#define LOCALIZED_FILE_POPPEDTO            L"Mudado para \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      L"Agora estamos no novo diret?rio criado \"%s\""
#define LOCALIZED_FILE_MKDIRFAILED         L"N?o pude criar diret?rio \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      L"Diret?rio Eliminado \"%s\""
#define LOCALIZED_FILE_RMDIRFAILED         L"N?o pude eliminar o diret?rio \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  L"O diret?rio n?o existe"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY L"Assegure-se que o diret?rio esteja vazio antes de elimin?-lo."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       L"Desenho no Logo"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    L"?rea Ativa"
#define LOCALIZED_INFORMATION   L"Informa??o"
#define LOCALIZED_WARNING       L"Aten??o"
#define LOCALIZED_UNTITLED      L"Sem nome"
#define LOCALIZED_UNKNOWN       L"Desconhecido"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       L"N?o demarcado"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     L"Localizar"
#define LOCALIZED_EDITOR_TITLE_REPLACE  L"Substituir"

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
#define LOCALIZED_COLOR_ALICEBLUE             L"AzulAlice"
#define LOCALIZED_COLOR_ANTIQUEWHITE          L"BrancoAntigo"
#define LOCALIZED_COLOR_AQUA                  L"?gua"
#define LOCALIZED_COLOR_AQUAMARINE            L"?guamarinha"
#define LOCALIZED_COLOR_AZURE                 L"AzulCeleste"
#define LOCALIZED_COLOR_BEIGE                 L"Bege"
#define LOCALIZED_COLOR_BISQUE                L"CremeDeMarisco"
#define LOCALIZED_COLOR_BLACK                 L"Preto"
#define LOCALIZED_COLOR_BLANCHEDALMOND        L"Am?ndoa"
#define LOCALIZED_COLOR_BLUE                  L"Azul"
#define LOCALIZED_COLOR_BLUEVIOLET            L"AzulVioleta"
#define LOCALIZED_COLOR_BROWN                 L"MarromClaro"
#define LOCALIZED_COLOR_BURLYWOOD             L"Madeira"
#define LOCALIZED_COLOR_CADETBLUE             L"AzulCadete"
#define LOCALIZED_COLOR_CHARTREUSE            L"VerdeParis"
#define LOCALIZED_COLOR_CHOCOLATE             L"Chocolate"
#define LOCALIZED_COLOR_CORAL                 L"Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        L"AzulFlordeMilho"
#define LOCALIZED_COLOR_CORNSILK              L"Milho"
#define LOCALIZED_COLOR_CRIMSON               L"Carmim"
#define LOCALIZED_COLOR_CYAN                  L"Ciano"
#define LOCALIZED_COLOR_DARKBLUE              L"AzulEscuro"
#define LOCALIZED_COLOR_DARKCYAN              L"CianoEscuro"
#define LOCALIZED_COLOR_DARKGOLDENROD         L"DouradoEscuro"
#define LOCALIZED_COLOR_DARKGRAY              L"CinzaEscuro"
#define LOCALIZED_COLOR_DARKGREEN             L"VerdeEscuro"
#define LOCALIZED_COLOR_DARKGREY              L"CinzaEscuro"
#define LOCALIZED_COLOR_DARKKHAKI             L"CaquiEscuro"
#define LOCALIZED_COLOR_DARKMAGENTA           L"MagentaEscuro"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        L"OlivaEscuro"
#define LOCALIZED_COLOR_DARKORANGE            L"LaranjaEscuro"
#define LOCALIZED_COLOR_DARKORCHID            L"Orqu?deaEscuro"
#define LOCALIZED_COLOR_DARKRED               L"VermelhoEscuro"
#define LOCALIZED_COLOR_DARKSALMON            L"Salm?oEscuro"
#define LOCALIZED_COLOR_DARKSEAGREEN          L"VerdeMarEscuro"
#define LOCALIZED_COLOR_DARKSLATEBLUE         L"AzulPardoEscuro"
#define LOCALIZED_COLOR_DARKSLATEGRAY         L"CinzaPardoEscuro"
#define LOCALIZED_COLOR_DARKSLATEGREY         L"CinzaPardoEscuro"
#define LOCALIZED_COLOR_DARKTURQUOISE         L"TurquesaEscuro"
#define LOCALIZED_COLOR_DARKVIOLET            L"VioletaEscuro"
#define LOCALIZED_COLOR_DEEPPINK              L"RosaProfundo"
#define LOCALIZED_COLOR_DEEPSKYBLUE           L"AzulCelesteProfundo"
#define LOCALIZED_COLOR_DIMGRAY               L"CinzaFosco"
#define LOCALIZED_COLOR_DIMGREY               L"CinzaSuave"
#define LOCALIZED_COLOR_DODGERBLUE            L"AzulFurtivo"
#define LOCALIZED_COLOR_FIREBRICK             L"VermelhoTijolo"
#define LOCALIZED_COLOR_FLORALWHITE           L"BrancoFloral"
#define LOCALIZED_COLOR_FORESTGREEN           L"VerdeFloresta"
#define LOCALIZED_COLOR_FUCHSIA               L"F?csia"
#define LOCALIZED_COLOR_GAINSBORO             L"CinzaM?dio"
#define LOCALIZED_COLOR_GHOSTWHITE            L"BrancoLigeiro"
#define LOCALIZED_COLOR_GOLD                  L"Ouro"
#define LOCALIZED_COLOR_GOLDENROD             L"Dourado"
#define LOCALIZED_COLOR_GRAY                  L"Prata"
#define LOCALIZED_COLOR_GREEN                 L"Verde"
#define LOCALIZED_COLOR_GREENYELLOW           L"AmareloEsverdeado"
#define LOCALIZED_COLOR_GREY                  L"Cinza"
#define LOCALIZED_COLOR_HONEYDEW              L"Man?"
#define LOCALIZED_COLOR_HOTPINK               L"RosaQuente"
#define LOCALIZED_COLOR_INDIANRED             L"VermelhoIndiano"
#define LOCALIZED_COLOR_INDIGO                L"Anil"
#define LOCALIZED_COLOR_IVORY                 L"Marfim"
#define LOCALIZED_COLOR_KHAKI                 L"Caqui"
#define LOCALIZED_COLOR_LAVENDER              L"Lavanda"
#define LOCALIZED_COLOR_LAVENDERBLUSH         L"RosaLavanda"
#define LOCALIZED_COLOR_LAWNGREEN             L"VerdeGrama"
#define LOCALIZED_COLOR_LEMONCHIFFON          L"Seda"
#define LOCALIZED_COLOR_LIGHTBLUE             L"AzulClaro"
#define LOCALIZED_COLOR_LIGHTCORAL            L"CoralClaro"
#define LOCALIZED_COLOR_LIGHTCYAN             L"CianoClaro"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  L"AmareloDouradoClaro"
#define LOCALIZED_COLOR_LIGHTGRAY             L"CinzaClaro"
#define LOCALIZED_COLOR_LIGHTGREEN            L"VerdeClaro"
#define LOCALIZED_COLOR_LIGHTGREY             L"CinzaClaro"
#define LOCALIZED_COLOR_LIGHTPINK             L"RosaClaro"
#define LOCALIZED_COLOR_LIGHTSALMON           L"Salm?oClaro"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         L"VerdeMarinhoClaro"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          L"AzulCelesteClaro"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        L"CinzaPardoClaro"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        L"CinzaPardoClaro"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        L"AzulA?oClaro"
#define LOCALIZED_COLOR_LIGHTYELLOW           L"AmareloClaro"
#define LOCALIZED_COLOR_LIME                  L"Lima"
#define LOCALIZED_COLOR_LIMEGREEN             L"VerdeLima"
#define LOCALIZED_COLOR_LINEN                 L"Linho"
#define LOCALIZED_COLOR_MAGENTA               L"Magenta"
#define LOCALIZED_COLOR_MAROON                L"Marrom"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      L"?guaMarinhaM?dio"
#define LOCALIZED_COLOR_MEDIUMBLUE            L"AzulM?dio"
#define LOCALIZED_COLOR_MEDIUMORCHID          L"Orqu?deaM?dio"
#define LOCALIZED_COLOR_MEDIUMPURPLE          L"P?rpuraM?dio"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        L"VerdeMarM?dio"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       L"AzulPardoM?dio"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     L"VerdePrimaveraM?dio"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       L"TurquesaM?dio"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       L"VioletaM?dio"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          L"AzulMeiaNoite"
#define LOCALIZED_COLOR_MINTCREAM             L"CremeDeMenta"
#define LOCALIZED_COLOR_MISTYROSE             L"RosaBrumoso"
#define LOCALIZED_COLOR_MOCCASIN              L"Mocassim"
#define LOCALIZED_COLOR_NAVAJOWHITE           L"BrancoNavajo"
#define LOCALIZED_COLOR_NAVY                  L"Marinho"
#define LOCALIZED_COLOR_OLDLACE               L"RendaAntiga"
#define LOCALIZED_COLOR_OLIVE                 L"Oliva"
#define LOCALIZED_COLOR_OLIVEDRAB             L"OlivaPardo"
#define LOCALIZED_COLOR_ORANGE                L"Laranja"
#define LOCALIZED_COLOR_ORANGERED             L"Alaranjado"
#define LOCALIZED_COLOR_ORCHID                L"Orqu?dea"
#define LOCALIZED_COLOR_PALEGOLDENROD         L"DouradoP?lido"
#define LOCALIZED_COLOR_PALEGREEN             L"VerdeP?lido"
#define LOCALIZED_COLOR_PALETURQUOISE         L"TurquesaP?lido"
#define LOCALIZED_COLOR_PALEVIOLETRED         L"VioletaP?lido"
#define LOCALIZED_COLOR_PAPAYAWHIP            L"Papaia"
#define LOCALIZED_COLOR_PEACHPUFF             L"P?ssego"
#define LOCALIZED_COLOR_PERU                  L"Peru"
#define LOCALIZED_COLOR_PINK                  L"Rosa"
#define LOCALIZED_COLOR_PLUM                  L"Ameixa"
#define LOCALIZED_COLOR_POWDERBLUE            L"AzulP?lvora"
#define LOCALIZED_COLOR_PURPLE                L"P?rpura"
#define LOCALIZED_COLOR_RED                   L"Vermelho"
#define LOCALIZED_COLOR_ROSYBROWN             L"MarromRosado"
#define LOCALIZED_COLOR_ROYALBLUE             L"AzulReal"
#define LOCALIZED_COLOR_SADDLEBROWN           L"MarromTelha"
#define LOCALIZED_COLOR_SALMON                L"Salm?o"
#define LOCALIZED_COLOR_SANDYBROWN            L"MarromAreia"
#define LOCALIZED_COLOR_SEAGREEN              L"VerdeMarinho"
#define LOCALIZED_COLOR_SEASHELL              L"Concha"
#define LOCALIZED_COLOR_SIENNA                L"Siena"
#define LOCALIZED_COLOR_SILVER                L"Prata"
#define LOCALIZED_COLOR_SKYBLUE               L"AzulC?u"
#define LOCALIZED_COLOR_SLATEBLUE             L"AzulPardo"
#define LOCALIZED_COLOR_SLATEGRAY             L"CinzaPardo"
#define LOCALIZED_COLOR_SLATEGREY             L"CinzaPardo"
#define LOCALIZED_COLOR_SNOW                  L"Neve"
#define LOCALIZED_COLOR_SPRINGGREEN           L"VerdePrimavera"
#define LOCALIZED_COLOR_STEELBLUE             L"AzulA?o"
#define LOCALIZED_COLOR_TAN                   L"Bronzeado"
#define LOCALIZED_COLOR_TEAL                  L"VerdeAzulado"
#define LOCALIZED_COLOR_THISTLE               L"Cardo"
#define LOCALIZED_COLOR_TOMATO                L"Tomate"
#define LOCALIZED_COLOR_TURQUOISE             L"Turquesa"
#define LOCALIZED_COLOR_VIOLET                L"Violeta"
#define LOCALIZED_COLOR_WHEAT                 L"Trigo"
#define LOCALIZED_COLOR_WHITE                 L"Branco"
#define LOCALIZED_COLOR_WHITESMOKE            L"Fuma?aBranca"
#define LOCALIZED_COLOR_YELLOW                L"Amarelo"
#define LOCALIZED_COLOR_YELLOWGREEN           L"VerdeAmarelado"

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
