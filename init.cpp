/*
 *      init.cpp     logo init module                      dvb
 *
 *       Copyright (C) 1995 by the Regents of the University of California
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <string.h>

   #include "localizednode.h"
   #include "eval.h"
   #include "paren.h"
   #include "intern.h"
   #include "logodata.h"
   #include "logomath.h"
   #include "wrksp.h"
   #include "coms.h"
   #include "lists.h"
   #include "activearea.h"
   #include "files.h"
   #include "graphics.h"
   #include "unix.h"
   #include "error.h"
   #include "mem.h"
   #include "parse.h"
   #include "print.h"
   #include "term.h"
   #include "logocore.h"

   #include "mmwind.h"
   #include "dllwind.h"
   #include "devwind.h"
   #include "logoeventqueue.h"
   #include "netwind.h"
   #include "graphwin.h"
   #include "dlgwind.h"
   #include "cursor.h"
   #include "debugheap.h"

   #include "localizedstrings.h"
#endif

struct PRIMTYPE
{
    const wchar_t * name;
    short        minargs;
    short        defargs;
    short        maxargs;
    short        priority;
    logofunc     prim;
    const wchar_t * alternatename;
};

CLocalizedNode Truex;
CLocalizedNode Falsex;
NODE *Right_Paren;
NODE *Left_Paren;
CLocalizedNode Toplevel;
CLocalizedNode System;
CLocalizedNode Error;
CLocalizedNode End;
CLocalizedNode Redefp;
CLocalizedNode Caseignoredp;
CLocalizedNode Erract;
CLocalizedNode Printdepthlimit;
CLocalizedNode Printwidthlimit;
NODE *Pause;
NODE *If;
NODE *Ifelse;
CLocalizedNode To;
NODE *Macro;
NODE *Unbound;         // a special node that means nothing (or void) was returned
                       // This is different from NIL, which is the empty list.
NODE *Minus_Sign;
NODE *Minus_Tight;
CLocalizedNode Startup;
NODE *Query;
NODE *Output;
NODE *Stop;
NODE *Goto;
NODE *Tag;
NODE *Null_Word = NIL;

// A special node that acts as a marker of where a parse error occured.
// This is set by the parser and interpreted by the evaluator when it
// reaches the point of the error.
NODE *g_ParseErrorNotEnoughInputs;

static const PRIMTYPE prims[] =
{
    {L"*", 2, 2, 2, PREFIX_PRIORITY + 3, lmul },
    {L"+", 2, 2, 2, PREFIX_PRIORITY + 2, ladd },
    {L"-", 2, 2, 2, PREFIX_PRIORITY + 2, lsub },
    {L"--", 1, 1, 1, PREFIX_PRIORITY + 4, lsub },
    {L".defmacro", 2, 2, 2, PREFIX_PRIORITY, ldefmacro, LOCALIZED_ALTERNATE__DEFMACRO },
    {L".eq", 2, 2, 2, PREFIX_PRIORITY, l_eq, LOCALIZED_ALTERNATE__EQ },
    {L".macro", -1, -1, -1, PREFIX_PRIORITY, lmacro, LOCALIZED_ALTERNATE__MACRO },
    {L".maybeoutput", 1, 1, 1, MAYBE_PRIORITY, loutput, LOCALIZED_ALTERNATE__MAYBEOUTPUT },
    {L".setbf", 2, 2, 2, PREFIX_PRIORITY, l_setbf, LOCALIZED_ALTERNATE__SETBF },
    {L".setfirst", 2, 2, 2, PREFIX_PRIORITY, l_setfirst, LOCALIZED_ALTERNATE__SETFIRST },
    {L".setitem", 3, 3, 3, PREFIX_PRIORITY, l_setitem, LOCALIZED_ALTERNATE__SETITEM },
    {L"/", 2, 2, 2, PREFIX_PRIORITY + 3, ldivide },
    {L"<", 2, 2, 2, PREFIX_PRIORITY + 1, llessp },
    {L"=", 2, 2, 2, PREFIX_PRIORITY + 1, lequalp },
    {L">", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterp },
    {L"<=", 2, 2, 2, PREFIX_PRIORITY + 1, llessequalp },
    {L"<>", 2, 2, 2, PREFIX_PRIORITY + 1, lnotequalp },
    {L">=", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterequalp },
    {L"?", 0, 0, 1, PREFIX_PRIORITY, lqm },
    {L"activearea", 0, 0, 0, PREFIX_PRIORITY, lactivearea, LOCALIZED_ALTERNATE_ACTIVEAREA },
    {L"allopen", 0, 0, 0, PREFIX_PRIORITY, lallopen, LOCALIZED_ALTERNATE_ALLOPEN },
    {L"and", 0, 2, -1, PREFIX_PRIORITY, land, LOCALIZED_ALTERNATE_AND },
    {L"apply", 2, 2, 2, MACRO_PRIORITY, lapply, LOCALIZED_ALTERNATE_APPLY },
    {L"arccos", 1, 1, 1, PREFIX_PRIORITY, lacos, LOCALIZED_ALTERNATE_ARCCOS },
    {L"arcsin", 1, 1, 1, PREFIX_PRIORITY, lasin, LOCALIZED_ALTERNATE_ARCSIN },
    {L"arctan", 1, 1, 2, PREFIX_PRIORITY, latan, LOCALIZED_ALTERNATE_ARCTAN },
    {L"arity", 1, 1, 1, PREFIX_PRIORITY, larity, LOCALIZED_ALTERNATE_ARITY },
    {L"array", 1, 1, 2, PREFIX_PRIORITY, larray, LOCALIZED_ALTERNATE_ARRAY },
    {L"arrayp", 1, 1, 1, PREFIX_PRIORITY, larrayp, LOCALIZED_ALTERNATE_ARRAYP },
    {L"array?", 1, 1, 1, PREFIX_PRIORITY, larrayp, LOCALIZED_ALTERNATE_ARRAY_ },
    {L"ascii", 1, 1, 1, PREFIX_PRIORITY, lascii, LOCALIZED_ALTERNATE_ASCII },
    {L"ashift", 2, 2, 2, PREFIX_PRIORITY, lashift, LOCALIZED_ALTERNATE_ASHIFT },
    {L"back", 1, 1, 1, PREFIX_PRIORITY, lback, LOCALIZED_ALTERNATE_BACK },
    {L"backslashedp", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp, LOCALIZED_ALTERNATE_BACKSLASHEDP },
    {L"backslashed?", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp, LOCALIZED_ALTERNATE_BACKSLASHED_ },
    {L"beforep", 2, 2, 2, PREFIX_PRIORITY, lbeforep, LOCALIZED_ALTERNATE_BEFOREP },
    {L"before?", 2, 2, 2, PREFIX_PRIORITY, lbeforep, LOCALIZED_ALTERNATE_BEFORE_ },
    {L"bf", 1, 1, 1, PREFIX_PRIORITY, lbutfirst, LOCALIZED_ALTERNATE_BF },
    {L"bfs", 1, 1, 1, PREFIX_PRIORITY, lbfs, LOCALIZED_ALTERNATE_BFS },
    {L"bitand", 0, 2, -1, PREFIX_PRIORITY, lbitand, LOCALIZED_ALTERNATE_BITAND },
    {L"bitblock", 2, 2, 2, PREFIX_PRIORITY, lbitblock, LOCALIZED_ALTERNATE_BITBLOCK },
    {L"bitcopy", 2, 2, 2, PREFIX_PRIORITY, lbitcopy, LOCALIZED_ALTERNATE_BITCOPY },
    {L"bitcut", 2, 2, 2, PREFIX_PRIORITY, lbitcut, LOCALIZED_ALTERNATE_BITCUT },
    {L"bitfit", 2, 2, 2, PREFIX_PRIORITY, lbitfit, LOCALIZED_ALTERNATE_BITFIT },
    {L"bitindex", 0, 0, 0, PREFIX_PRIORITY, lbitindex, LOCALIZED_ALTERNATE_BITINDEX },
    {L"bitload", 1, 1, 1, PREFIX_PRIORITY, lbitload, LOCALIZED_ALTERNATE_BITLOAD },
    {L"bitloadsize", 1, 1, 1, PREFIX_PRIORITY, lbitloadsize, LOCALIZED_ALTERNATE_BITLOADSIZE },
    {L"bitsize", 0, 0, 0, PREFIX_PRIORITY, lbitsize, LOCALIZED_ALTERNATE_BITSIZE },
    {L"bitmapturtle", 0, 0, 1, PREFIX_PRIORITY, lbitmapturtle, LOCALIZED_ALTERNATE_BITMAPTURTLE },
    {L"bitmode", 0, 0, 0, PREFIX_PRIORITY, lbitmode, LOCALIZED_ALTERNATE_BITMODE },
    {L"bitnot", 1, 1, 1, PREFIX_PRIORITY, lbitnot, LOCALIZED_ALTERNATE_BITNOT },
    {L"bitor", 0, 2, -1, PREFIX_PRIORITY, lbitor, LOCALIZED_ALTERNATE_BITOR },
    {L"bitpaste", 0, 0, 0, PREFIX_PRIORITY, lbitpaste, LOCALIZED_ALTERNATE_BITPASTE },
    {L"bitpastetoindex", 3, 3, 3, PREFIX_PRIORITY, lbitpastetoindex, LOCALIZED_ALTERNATE_BITPASTETOINDEX },
    {L"bitsave", 1, 1, 2, PREFIX_PRIORITY, lbitsave, LOCALIZED_ALTERNATE_BITSAVE },
    {L"bitxor", 0, 2, -1, PREFIX_PRIORITY, lbitxor, LOCALIZED_ALTERNATE_BITXOR },
    {L"bk", 1, 1, 1, PREFIX_PRIORITY, lback, LOCALIZED_ALTERNATE_BK },
    {L"bl", 1, 1, 1, PREFIX_PRIORITY, lbutlast, LOCALIZED_ALTERNATE_BL },
    {L"buried", 0, 0, 0, PREFIX_PRIORITY, lburied, LOCALIZED_ALTERNATE_BURIED },
    {L"bury", 1, 1, 1, PREFIX_PRIORITY, lbury, LOCALIZED_ALTERNATE_BURY },
    {L"butfirst", 1, 1, 1, PREFIX_PRIORITY, lbutfirst, LOCALIZED_ALTERNATE_BUTFIRST },
    {L"butfirsts", 1, 1, 1, PREFIX_PRIORITY, lbfs, LOCALIZED_ALTERNATE_BUTFIRSTS },
    {L"butlast", 1, 1, 1, PREFIX_PRIORITY, lbutlast, LOCALIZED_ALTERNATE_BUTLAST },
    {L"buttoncreate", 8, 8, 8, PREFIX_PRIORITY, lbuttoncreate, LOCALIZED_ALTERNATE_BUTTONCREATE },
    {L"buttondelete", 1, 1, 1, PREFIX_PRIORITY, lbuttondelete, LOCALIZED_ALTERNATE_BUTTONDELETE },
    {L"buttonenable", 2, 2, 2, PREFIX_PRIORITY, lbuttonenable, LOCALIZED_ALTERNATE_BUTTONENABLE },
    {L"buttonupdate", 2, 2, 2, PREFIX_PRIORITY, lbuttonupdate, LOCALIZED_ALTERNATE_BUTTONUPDATE },
    {L"buttonp", 0, 0, 0, PREFIX_PRIORITY, lbuttonp, LOCALIZED_ALTERNATE_BUTTONP },
    {L"button?", 0, 0, 0, PREFIX_PRIORITY, lbuttonp, LOCALIZED_ALTERNATE_BUTTON_ },
    {L"bye", 0, 0, 0, PREFIX_PRIORITY, lbye, LOCALIZED_ALTERNATE_BYE },
    {L"catch", 2, 2, 2, MACRO_PRIORITY, lcatch, LOCALIZED_ALTERNATE_CATCH },
    {L"char", 1, 1, 1, PREFIX_PRIORITY, lchar, LOCALIZED_ALTERNATE_CHAR },
    {L"chdir", 1, 1, 1, PREFIX_PRIORITY, lchdir, LOCALIZED_ALTERNATE_CHDIR },
    {L"checkboxcreate", 8, 8, 8, PREFIX_PRIORITY, lcheckboxcreate, LOCALIZED_ALTERNATE_CHECKBOXCREATE },
    {L"checkboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcheckboxdelete, LOCALIZED_ALTERNATE_CHECKBOXDELETE },
    {L"checkboxenable", 2, 2, 2, PREFIX_PRIORITY, lcheckboxenable, LOCALIZED_ALTERNATE_CHECKBOXENABLE },
    {L"checkboxget", 1, 1, 1, PREFIX_PRIORITY, lcheckboxget, LOCALIZED_ALTERNATE_CHECKBOXGET },
    {L"checkboxset", 2, 2, 2, PREFIX_PRIORITY, lcheckboxset, LOCALIZED_ALTERNATE_CHECKBOXSET },
    {L"clean", 0, 0, 0, PREFIX_PRIORITY, lclean, LOCALIZED_ALTERNATE_CLEAN },
    {L"clearpalette", 0, 0, 0, PREFIX_PRIORITY, lclearpalette, LOCALIZED_ALTERNATE_CLEARPALETTE },
    {L"clearscreen", 0, 0, 0, PREFIX_PRIORITY, lclearscreen, LOCALIZED_ALTERNATE_CLEARSCREEN },
    {L"cleartext", 0, 0, 0, PREFIX_PRIORITY, lcleartext, LOCALIZED_ALTERNATE_CLEARTEXT },
#if !defined WX_PURE
    {L"cleartimer", 1, 1, 1, PREFIX_PRIORITY, lcleartimer, LOCALIZED_ALTERNATE_CLEARTIMER },
#endif
    {L"close", 1, 1, 1, PREFIX_PRIORITY, lclose, LOCALIZED_ALTERNATE_CLOSE },
    {L"closeall", 0, 0, 0, PREFIX_PRIORITY, lcloseall, LOCALIZED_ALTERNATE_CLOSEALL },
    {L"co", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue, LOCALIZED_ALTERNATE_CO },
    {L"comboboxaddstring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxaddstring, LOCALIZED_ALTERNATE_COMBOBOXADDSTRING },
    {L"comboboxcreate", 6, 6, 6, PREFIX_PRIORITY, lcomboboxcreate, LOCALIZED_ALTERNATE_COMBOBOXCREATE },
    {L"comboboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcomboboxdelete, LOCALIZED_ALTERNATE_COMBOBOXDELETE },
    {L"comboboxenable", 2, 2, 2, PREFIX_PRIORITY, lcomboboxenable, LOCALIZED_ALTERNATE_COMBOBOXENABLE },
    {L"comboboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxdeletestring, LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING },
    {L"comboboxgettext", 1, 1, 1, PREFIX_PRIORITY, lcomboboxgettext, LOCALIZED_ALTERNATE_COMBOBOXGETTEXT },
    {L"comboboxsettext", 2, 2, 2, PREFIX_PRIORITY, lcomboboxsettext, LOCALIZED_ALTERNATE_COMBOBOXSETTEXT },
    {L"contents", 0, 0, 0, PREFIX_PRIORITY, lcontents, LOCALIZED_ALTERNATE_CONTENTS },
    {L"continue", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue, LOCALIZED_ALTERNATE_CONTINUE },
    {L"copydef", 2, 2, 2, PREFIX_PRIORITY, lcopydef, LOCALIZED_ALTERNATE_COPYDEF },
    {L"cos", 1, 1, 1, PREFIX_PRIORITY, lcos, LOCALIZED_ALTERNATE_COS },
    {L"count", 1, 1, 1, PREFIX_PRIORITY, lcount, LOCALIZED_ALTERNATE_COUNT },
    {L"cs", 0, 0, 0, PREFIX_PRIORITY, lclearscreen, LOCALIZED_ALTERNATE_CS },
    {L"ct", 0, 0, 0, PREFIX_PRIORITY, lcleartext, LOCALIZED_ALTERNATE_CT },
    {L"cursor", 0, 0, 0, PREFIX_PRIORITY, lcursor, LOCALIZED_ALTERNATE_CURSOR },
    {L"debugwindows", 0, 0, 1, PREFIX_PRIORITY, ldebugwindows, LOCALIZED_ALTERNATE_DEBUGWINDOWS },
    {L"define", 2, 2, 2, PREFIX_PRIORITY, ldefine, LOCALIZED_ALTERNATE_DEFINE },
    {L"definedp", 1, 1, 1, PREFIX_PRIORITY, ldefinedp, LOCALIZED_ALTERNATE_DEFINEDP },
    {L"defined?", 1, 1, 1, PREFIX_PRIORITY, ldefinedp, LOCALIZED_ALTERNATE_DEFINED_ },
    {L"dialogcreate", 8, 8, 8, PREFIX_PRIORITY, ldialogcreate, LOCALIZED_ALTERNATE_DIALOGCREATE },
    {L"dialogenable", 2, 2, 2, PREFIX_PRIORITY, ldialogenable, LOCALIZED_ALTERNATE_DIALOGENABLE },
    {L"dialogdelete", 1, 1, 1, PREFIX_PRIORITY, ldialogdelete, LOCALIZED_ALTERNATE_DIALOGDELETE },
    {L"dialogfileopen", 1, 1, 1, PREFIX_PRIORITY, ldialogfileopen, LOCALIZED_ALTERNATE_DIALOGFILEOPEN },
    {L"dialogfilesave", 1, 1, 1, PREFIX_PRIORITY, ldialogfilesave, LOCALIZED_ALTERNATE_DIALOGFILESAVE },
    {L"difference", 2, 2, 2, PREFIX_PRIORITY, lsub, LOCALIZED_ALTERNATE_DIFFERENCE },
    {L"directories", 0, 0, 0, PREFIX_PRIORITY, ldirectories, LOCALIZED_ALTERNATE_DIRECTORIES },
#if !defined WX_PURE
    {L"dllcall", 1, 1, 2, PREFIX_PRIORITY, ldllcall, LOCALIZED_ALTERNATE_DLLCALL },
    {L"dllfree", 0, 0, 1, PREFIX_PRIORITY, ldllfree, LOCALIZED_ALTERNATE_DLLFREE },
    {L"dllload", 1, 1, 1, PREFIX_PRIORITY, ldllload, LOCALIZED_ALTERNATE_DLLLOAD },
#endif
    {L"down", 1, 1, 1, PREFIX_PRIORITY, ldownpitch, LOCALIZED_ALTERNATE_DOWN },
    {L"downpitch", 1, 1, 1, PREFIX_PRIORITY, ldownpitch, LOCALIZED_ALTERNATE_DOWNPITCH },
    {L"dribble", 1, 1, 1, PREFIX_PRIORITY, ldribble, LOCALIZED_ALTERNATE_DRIBBLE },
    {L"ed", 1, 1, 1, PREFIX_PRIORITY, ledit, LOCALIZED_ALTERNATE_ED },
    {L"edit", 1, 1, 1, PREFIX_PRIORITY, ledit, LOCALIZED_ALTERNATE_EDIT },
    {L"ellipsearc", 4, 4, 4, PREFIX_PRIORITY, lellipsearc, LOCALIZED_ALTERNATE_ELLIPSEARC },
    {L"emptyp", 1, 1, 1, PREFIX_PRIORITY, lemptyp, LOCALIZED_ALTERNATE_EMPTYP },
    {L"empty?", 1, 1, 1, PREFIX_PRIORITY, lemptyp, LOCALIZED_ALTERNATE_EMPTY_ },
    {L"eofp", 0, 0, 0, PREFIX_PRIORITY, leofp, LOCALIZED_ALTERNATE_EOFP },
    {L"eof?", 0, 0, 0, PREFIX_PRIORITY, leofp, LOCALIZED_ALTERNATE_EOF_ },
    {L"equalp", 2, 2, 2, PREFIX_PRIORITY, lequalp, LOCALIZED_ALTERNATE_EQUALP },
    {L"equal?", 2, 2, 2, PREFIX_PRIORITY, lequalp, LOCALIZED_ALTERNATE_EQUAL_ },
    {L"er", 1, 1, 1, PREFIX_PRIORITY, lerase, LOCALIZED_ALTERNATE_ER },
    {L"erase", 1, 1, 1, PREFIX_PRIORITY, lerase, LOCALIZED_ALTERNATE_ERASE },
    {L"erasefile", 1, 1, 1, PREFIX_PRIORITY, lerasefile, LOCALIZED_ALTERNATE_ERASEFILE },
    {L"erf", 1, 1, 1, PREFIX_PRIORITY, lerasefile, LOCALIZED_ALTERNATE_ERF },
    {L"error", 0, 0, 0, PREFIX_PRIORITY, lerror, LOCALIZED_ALTERNATE_ERROR },
    {L"eventcheck", 0, 0, 0, PREFIX_PRIORITY, leventcheck, LOCALIZED_ALTERNATE_EVENTCHECK },
    {L"exp", 1, 1, 1, PREFIX_PRIORITY, lexp, LOCALIZED_ALTERNATE_EXP },
    {L"fd", 1, 1, 1, PREFIX_PRIORITY, lforward, LOCALIZED_ALTERNATE_FD },
    {L"fence", 0, 0, 0, PREFIX_PRIORITY, lfence, LOCALIZED_ALTERNATE_FENCE },
    {L"fill", 0, 0, 1, PREFIX_PRIORITY, lfill, LOCALIZED_ALTERNATE_FILL },
    {L"files", 0, 0, 0, PREFIX_PRIORITY, lfiles, LOCALIZED_ALTERNATE_FILES },
    {L"first", 1, 1, 1, PREFIX_PRIORITY, lfirst, LOCALIZED_ALTERNATE_FIRST },
    {L"firsts", 1, 1, 1, PREFIX_PRIORITY, lfirsts, LOCALIZED_ALTERNATE_FIRSTS },
    {L"floodcolor", 0, 0, 0, PREFIX_PRIORITY, lfloodcolor, LOCALIZED_ALTERNATE_FLOODCOLOR },
    {L"fontfacenames", 0, 0, 0, PREFIX_PRIORITY, lfontfacenames, LOCALIZED_ALTERNATE_FONTFACENAMES },
    {L"forever", 1, 1, 1, MACRO_PRIORITY, lforever, LOCALIZED_ALTERNATE_FOREVER },
    {L"form", 3, 3, 3, PREFIX_PRIORITY, lform, LOCALIZED_ALTERNATE_FORM },
    {L"forward", 1, 1, 1, PREFIX_PRIORITY, lforward, LOCALIZED_ALTERNATE_FORWARD },
    {L"fput", 2, 2, 2, PREFIX_PRIORITY, lfput, LOCALIZED_ALTERNATE_FPUT },
    {L"fs", 0, 0, 0, PREFIX_PRIORITY, lfullscreen, LOCALIZED_ALTERNATE_FS },
    {L"fullscreen", 0, 0, 0, PREFIX_PRIORITY, lfullscreen, LOCALIZED_ALTERNATE_FULLSCREEN },
    {L"fulltext", 1, 1, 1, PREFIX_PRIORITY, lfulltext, LOCALIZED_ALTERNATE_FULLTEXT },
    {L"getfocus", 0, 0, 0, PREFIX_PRIORITY, lgetfocus, LOCALIZED_ALTERNATE_GETFOCUS },
    // {L"goto", 1, 1, 1, MACRO_PRIORITY, lgoto, LOCALIZED_ALTERNATE_GOTO },
    {L"gifload", 1, 1, 1, PREFIX_PRIORITY, lgifload, LOCALIZED_ALTERNATE_GIFLOAD },
    {L"gifsize", 1, 1, 1, PREFIX_PRIORITY, lgifsize, LOCALIZED_ALTERNATE_GIFSIZE },
    {L"gifsave", 1, 1, 6, PREFIX_PRIORITY, lgifsave, LOCALIZED_ALTERNATE_GIFSAVE },
    {L"gprop", 2, 2, 2, PREFIX_PRIORITY, lgprop, LOCALIZED_ALTERNATE_GPROP },
    {L"greater?", 2, 2, 2, PREFIX_PRIORITY, lgreaterp, LOCALIZED_ALTERNATE_GREATER_ },
    {L"greaterequal?", 2, 2, 2, PREFIX_PRIORITY, lgreaterequalp, LOCALIZED_ALTERNATE_GREATEREQUAL_ },
    {L"greaterequalp", 2, 2, 2, PREFIX_PRIORITY, lgreaterequalp, LOCALIZED_ALTERNATE_GREATEREQUALP },
    {L"greaterp", 2, 2, 2, PREFIX_PRIORITY, lgreaterp, LOCALIZED_ALTERNATE_GREATERP },
    {L"groupboxcreate", 6, 6, 6, PREFIX_PRIORITY, lgroupboxcreate, LOCALIZED_ALTERNATE_GROUPBOXCREATE },
    {L"groupboxdelete", 1, 1, 1, PREFIX_PRIORITY, lgroupboxdelete, LOCALIZED_ALTERNATE_GROUPBOXDELETE },
    {L"halt", 0, 0, 0, PREFIX_PRIORITY, lhalt, LOCALIZED_ALTERNATE_HALT },
    {L"hasownpen?", 0, 0, 0, PREFIX_PRIORITY, lhasownpenp, LOCALIZED_ALTERNATE_HASOWNPEN_ },
    {L"hasownpenp", 0, 0, 0, PREFIX_PRIORITY, lhasownpenp, LOCALIZED_ALTERNATE_HASOWNPENP },
    {L"heading", 0, 0, 0, PREFIX_PRIORITY, lheading, LOCALIZED_ALTERNATE_HEADING },
    {L"help", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lhelp, LOCALIZED_ALTERNATE_HELP },
    {L"hideturtle", 0, 0, 0, PREFIX_PRIORITY, lhideturtle, LOCALIZED_ALTERNATE_HIDETURTLE },
    {L"home", 0, 0, 0, PREFIX_PRIORITY, lhome, LOCALIZED_ALTERNATE_HOME },
    {L"ht", 0, 0, 0, PREFIX_PRIORITY, lhideturtle, LOCALIZED_ALTERNATE_HT },
    {L"if", 2, 2, 3, MACRO_PRIORITY, lif, LOCALIZED_ALTERNATE_IF },
    {L"ifelse", 3, 3, 3, MACRO_PRIORITY, lifelse, LOCALIZED_ALTERNATE_IFELSE },
    {L"iff", 1, 1, 1, MACRO_PRIORITY, liffalse, LOCALIZED_ALTERNATE_IFF },
    {L"iffalse", 1, 1, 1, MACRO_PRIORITY, liffalse, LOCALIZED_ALTERNATE_IFFALSE },
    {L"ift", 1, 1, 1, MACRO_PRIORITY, liftrue, LOCALIZED_ALTERNATE_IFT },
    {L"iftrue", 1, 1, 1, MACRO_PRIORITY, liftrue, LOCALIZED_ALTERNATE_IFTRUE },
    {L"ingameport", 1, 1, 2, PREFIX_PRIORITY, lingameport, LOCALIZED_ALTERNATE_INGAMEPORT },
    {L"inport", 1, 1, 1, PREFIX_PRIORITY, linport, LOCALIZED_ALTERNATE_INPORT },
    {L"inportb", 1, 1, 1, PREFIX_PRIORITY, linportb, LOCALIZED_ALTERNATE_INPORTB },
    {L"int", 1, 1, 1, PREFIX_PRIORITY, linteg, LOCALIZED_ALTERNATE_INT },
    {L"item", 2, 2, 2, PREFIX_PRIORITY, litem, LOCALIZED_ALTERNATE_ITEM },
    {L"keyboardoff", 0, 0, 0, PREFIX_PRIORITY, lkeyboardoff, LOCALIZED_ALTERNATE_KEYBOARDOFF },
    {L"keyboardon", 1, 1, 2, PREFIX_PRIORITY, lkeyboardon, LOCALIZED_ALTERNATE_KEYBOARDON },
    {L"keyboardvalue", 0, 0, 0, PREFIX_PRIORITY, lkeyboardvalue, LOCALIZED_ALTERNATE_KEYBOARDVALUE },
    {L"keyp", 0, 0, 0, PREFIX_PRIORITY, lkeyp, LOCALIZED_ALTERNATE_KEYP },
    {L"key?", 0, 0, 0, PREFIX_PRIORITY, lkeyp, LOCALIZED_ALTERNATE_KEY_ },
    {L"label", 1, 1, 1, PREFIX_PRIORITY, llabel, LOCALIZED_ALTERNATE_LABEL },
    {L"labelfont", 0, 0, 0, PREFIX_PRIORITY, llabelfont, LOCALIZED_ALTERNATE_LABELFONT },
    {L"labelsize", 1, 1, 1, PREFIX_PRIORITY, llabelsize, LOCALIZED_ALTERNATE_LABELSIZE },
    {L"last", 1, 1, 1, PREFIX_PRIORITY, llast, LOCALIZED_ALTERNATE_LAST },
    {L"left", 1, 1, 1, PREFIX_PRIORITY, lleft, LOCALIZED_ALTERNATE_LEFT },
    {L"leftroll", 1, 1, 1, PREFIX_PRIORITY, lleftroll, LOCALIZED_ALTERNATE_LEFTROLL },
    {L"less?", 2, 2, 2, PREFIX_PRIORITY, llessp, LOCALIZED_ALTERNATE_LESS_ },
    {L"lessequal?", 2, 2, 2, PREFIX_PRIORITY, llessequalp, LOCALIZED_ALTERNATE_LESSEQUAL_ },
    {L"lessequalp", 2, 2, 2, PREFIX_PRIORITY, llessequalp, LOCALIZED_ALTERNATE_LESSEQUALP },
    {L"lessp", 2, 2, 2, PREFIX_PRIORITY, llessp, LOCALIZED_ALTERNATE_LESSP },
    {L"light", 0, 0, 0, PREFIX_PRIORITY, llight, LOCALIZED_ALTERNATE_LIGHT },
    {L"list", 0, 2, -1, PREFIX_PRIORITY, llist, LOCALIZED_ALTERNATE_LIST },
    {L"listboxaddstring", 2, 2, 2, PREFIX_PRIORITY, llistboxaddstring, LOCALIZED_ALTERNATE_LISTBOXADDSTRING },
    {L"listboxcreate", 6, 6, 6, PREFIX_PRIORITY, llistboxcreate, LOCALIZED_ALTERNATE_LISTBOXCREATE },
    {L"listboxenable", 2, 2, 2, PREFIX_PRIORITY, llistboxenable, LOCALIZED_ALTERNATE_LISTBOXENABLE },
    {L"listboxdelete", 1, 1, 1, PREFIX_PRIORITY, llistboxdelete, LOCALIZED_ALTERNATE_LISTBOXDELETE },
    {L"listboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, llistboxdeletestring, LOCALIZED_ALTERNATE_LISTBOXDELETESTRING },
    {L"listboxgetselect", 1, 1, 1, PREFIX_PRIORITY, llistboxgetselect, LOCALIZED_ALTERNATE_LISTBOXGETSELECT },
    {L"listp", 1, 1, 1, PREFIX_PRIORITY, llistp, LOCALIZED_ALTERNATE_LISTP },
    {L"list?", 1, 1, 1, PREFIX_PRIORITY, llistp, LOCALIZED_ALTERNATE_LIST_ },
    {L"ln", 1, 1, 1, PREFIX_PRIORITY, lln, LOCALIZED_ALTERNATE_LN },
    {L"load", 1, 1, 1, PREFIX_PRIORITY, lload, LOCALIZED_ALTERNATE_LOAD },
    {L"local", 1, 1, -1, PREFIX_PRIORITY, llocal, LOCALIZED_ALTERNATE_LOCAL },
    {L"log10", 1, 1, 1, PREFIX_PRIORITY, llog10, LOCALIZED_ALTERNATE_LOG10 },
    {L"logoversion", 0, 0, 0, PREFIX_PRIORITY, llogoversion, LOCALIZED_ALTERNATE_LOGOVERSION },
    {L"lowercase", 1, 1, 1, PREFIX_PRIORITY, llowercase, LOCALIZED_ALTERNATE_LOWERCASE },
    {L"lput", 2, 2, 2, PREFIX_PRIORITY, llput, LOCALIZED_ALTERNATE_LPUT },
    {L"lr", 1, 1, 1, PREFIX_PRIORITY, lleftroll, LOCALIZED_ALTERNATE_LR },
    {L"lshift", 2, 2, 2, PREFIX_PRIORITY, llshift, LOCALIZED_ALTERNATE_LSHIFT },
    {L"lt", 1, 1, 1, PREFIX_PRIORITY, lleft, LOCALIZED_ALTERNATE_LT },
    {L"machine", 0, 0, 0, PREFIX_PRIORITY, lmachine, LOCALIZED_ALTERNATE_MACHINE },
    {L"macrop", 1, 1, 1, PREFIX_PRIORITY, lmacrop, LOCALIZED_ALTERNATE_MACROP },
    {L"macro?", 1, 1, 1, PREFIX_PRIORITY, lmacrop, LOCALIZED_ALTERNATE_MACRO_ },
    {L"make", 2, 2, 2, PREFIX_PRIORITY, lmake, LOCALIZED_ALTERNATE_MAKE },
#if !defined WX_PURE
    {L"mci", 1, 1, 2, PREFIX_PRIORITY, lmci, LOCALIZED_ALTERNATE_MCI },
#endif
    {L"member", 2, 2, 2, PREFIX_PRIORITY, lmember, LOCALIZED_ALTERNATE_MEMBER },
    {L"memberp", 2, 2, 2, PREFIX_PRIORITY, lmemberp, LOCALIZED_ALTERNATE_MEMBERP },
    {L"member?", 2, 2, 2, PREFIX_PRIORITY, lmemberp, LOCALIZED_ALTERNATE_MEMBER_ },
    {L"messagebox", 2, 2, 2, PREFIX_PRIORITY, lmessagebox, LOCALIZED_ALTERNATE_MESSAGEBOX },
#if !defined WX_PURE
    {L"midiclose", 0, 0, 0, PREFIX_PRIORITY, lmidiclose, LOCALIZED_ALTERNATE_MIDICLOSE },
    {L"midimessage", 1, 1, 1, PREFIX_PRIORITY, lmidimessage, LOCALIZED_ALTERNATE_MIDIMESSAGE },
    {L"midiopen", 0, 0, 1, PREFIX_PRIORITY, lmidiopen, LOCALIZED_ALTERNATE_MIDIOPEN },
#endif
    {L"minus", 1, 1, 1, PREFIX_PRIORITY, lsub, LOCALIZED_ALTERNATE_MINUS },
    {L"mkdir", 1, 1, 1, PREFIX_PRIORITY, lmkdir, LOCALIZED_ALTERNATE_MKDIR },
    {L"modulo", 2, 2, 2, PREFIX_PRIORITY, lmodulo, LOCALIZED_ALTERNATE_MODULO },
    {L"mouseoff", 0, 0, 0, PREFIX_PRIORITY, lmouseoff, LOCALIZED_ALTERNATE_MOUSEOFF },
    {L"mouseon", 5, 5, 5, PREFIX_PRIORITY, lmouseon, LOCALIZED_ALTERNATE_MOUSEON },
    {L"mousepos", 0, 0, 0, PREFIX_PRIORITY, lmousepos, LOCALIZED_ALTERNATE_MOUSEPOS },
    {L"namep", 1, 1, 1, PREFIX_PRIORITY, lnamep, LOCALIZED_ALTERNATE_NAMEP },
    {L"name?", 1, 1, 1, PREFIX_PRIORITY, lnamep, LOCALIZED_ALTERNATE_NAME_ },
    {L"names", 0, 0, 0, PREFIX_PRIORITY, lnames, LOCALIZED_ALTERNATE_NAMES },
#if !defined WX_PURE
    {L"netacceptoff", 0, 0, 0, PREFIX_PRIORITY, lnetacceptoff, LOCALIZED_ALTERNATE_NETACCEPTOFF },
    {L"netaccepton", 3, 3, 3, PREFIX_PRIORITY, lnetaccepton, LOCALIZED_ALTERNATE_NETACCEPTON },
    {L"netacceptreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetacceptreceivevalue, LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE },
    {L"netacceptsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetacceptsendvalue, LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE },
    {L"netconnectoff", 0, 0, 0, PREFIX_PRIORITY, lnetconnectoff, LOCALIZED_ALTERNATE_NETCONNECTOFF },
    {L"netconnecton", 4, 4, 4, PREFIX_PRIORITY, lnetconnecton, LOCALIZED_ALTERNATE_NETCONNECTON },
    {L"netconnectreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetconnectreceivevalue, LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE },
    {L"netconnectsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetconnectsendvalue, LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE },
    {L"netshutdown", 0, 0, 0, PREFIX_PRIORITY, lnetshutdown, LOCALIZED_ALTERNATE_NETSHUTDOWN },
    {L"netstartup", 0, 0, 1, PREFIX_PRIORITY, lnetstartup, LOCALIZED_ALTERNATE_NETSTARTUP },
#endif // WX_PURE
    {L"nobitmapturtle", 0, 0, 0, PREFIX_PRIORITY, lnobitmapturtle, LOCALIZED_ALTERNATE_NOBITMAPTURTLE },
    {L"nodes", 0, 0, 0, PREFIX_PRIORITY, lnodes, LOCALIZED_ALTERNATE_NODES },
    {L"nodribble", 0, 0, 0, PREFIX_PRIORITY, lnodribble, LOCALIZED_ALTERNATE_NODRIBBLE },
    {L"nostatus", 0, 0, 0, PREFIX_PRIORITY, lnostatus, LOCALIZED_ALTERNATE_NOSTATUS },
    {L"not", 1, 1, 1, PREFIX_PRIORITY, lnot, LOCALIZED_ALTERNATE_NOT },
    {L"notequal?", 2, 2, 2, PREFIX_PRIORITY, lnotequalp, LOCALIZED_ALTERNATE_NOTEQUAL_ },
    {L"notequalp", 2, 2, 2, PREFIX_PRIORITY, lnotequalp, LOCALIZED_ALTERNATE_NOTEQUALP },
    {L"noyield", 0, 0, 0, PREFIX_PRIORITY, lnoyield, LOCALIZED_ALTERNATE_NOYIELD },
    {L"numberp", 1, 1, 1, PREFIX_PRIORITY, lnumberp, LOCALIZED_ALTERNATE_NUMBERP },
    {L"number?", 1, 1, 1, PREFIX_PRIORITY, lnumberp, LOCALIZED_ALTERNATE_NUMBER_ },
    {L"op", 1, 1, 1, OUTPUT_PRIORITY, loutput, LOCALIZED_ALTERNATE_OP },
    {L"openappend", 1, 1, 2, PREFIX_PRIORITY, lopenappend, LOCALIZED_ALTERNATE_OPENAPPEND },
    {L"openread", 1, 1, 2, PREFIX_PRIORITY, lopenread, LOCALIZED_ALTERNATE_OPENREAD },
    {L"openupdate", 1, 1, 2, PREFIX_PRIORITY, lopenupdate, LOCALIZED_ALTERNATE_OPENUPDATE },
    {L"openwrite", 1, 1, 2, PREFIX_PRIORITY, lopenwrite, LOCALIZED_ALTERNATE_OPENWRITE },
    {L"or", 0, 2, -1, PREFIX_PRIORITY, lor, LOCALIZED_ALTERNATE_OR },
    {L"outport", 2, 2, 2, PREFIX_PRIORITY, loutport, LOCALIZED_ALTERNATE_OUTPORT },
    {L"outportb", 2, 2, 2, PREFIX_PRIORITY, loutportb, LOCALIZED_ALTERNATE_OUTPORTB },
    {L"output", 1, 1, 1, OUTPUT_PRIORITY, loutput, LOCALIZED_ALTERNATE_OUTPUT },
    {L"parse", 1, 1, 1, PREFIX_PRIORITY, lparse, LOCALIZED_ALTERNATE_PARSE },
    {L"pause", 0, 0, 0, PREFIX_PRIORITY, lpause, LOCALIZED_ALTERNATE_PAUSE },
    {L"pc", 0, 0, 0, PREFIX_PRIORITY, lpencolor, LOCALIZED_ALTERNATE_PC },
    {L"pd", 0, 0, 0, PREFIX_PRIORITY, lpendown, LOCALIZED_ALTERNATE_PD },
    {L"pe", 0, 0, 0, PREFIX_PRIORITY, lpenerase, LOCALIZED_ALTERNATE_PE },
    {L"pencolor", 0, 0, 0, PREFIX_PRIORITY, lpencolor, LOCALIZED_ALTERNATE_PENCOLOR },
    {L"pendown", 0, 0, 0, PREFIX_PRIORITY, lpendown, LOCALIZED_ALTERNATE_PENDOWN },
    {L"pendownp", 0, 0, 0, PREFIX_PRIORITY, lpendownp, LOCALIZED_ALTERNATE_PENDOWNP },
    {L"pendown?", 0, 0, 0, PREFIX_PRIORITY, lpendownp, LOCALIZED_ALTERNATE_PENDOWN_ },
    {L"penerase", 0, 0, 0, PREFIX_PRIORITY, lpenerase, LOCALIZED_ALTERNATE_PENERASE },
    {L"penmode", 0, 0, 0, PREFIX_PRIORITY, lpenmode, LOCALIZED_ALTERNATE_PENMODE },
    {L"penpaint", 0, 0, 0, PREFIX_PRIORITY, lpenpaint, LOCALIZED_ALTERNATE_PENPAINT },
    {L"penpattern", 0, 0, 0, PREFIX_PRIORITY, lpenpattern, LOCALIZED_ALTERNATE_PENPATTERN },
    {L"penreverse", 0, 0, 0, PREFIX_PRIORITY, lpenreverse, LOCALIZED_ALTERNATE_PENREVERSE },
    {L"pensize", 0, 0, 0, PREFIX_PRIORITY, lpensize, LOCALIZED_ALTERNATE_PENSIZE },
    {L"penup", 0, 0, 0, PREFIX_PRIORITY, lpenup, LOCALIZED_ALTERNATE_PENUP },
    {L"perspective", 0, 0, 0, PREFIX_PRIORITY, lperspective, LOCALIZED_ALTERNATE_PERSPECTIVE },
    {L"pitch", 0, 0, 0, PREFIX_PRIORITY, lpitch, LOCALIZED_ALTERNATE_PITCH },
    {L"pixel", 0, 0, 0, PREFIX_PRIORITY, lpixel, LOCALIZED_ALTERNATE_PIXEL },
#if !defined WX_PURE
    {L"playwave", 2, 2, 2, PREFIX_PRIORITY, lplaywave, LOCALIZED_ALTERNATE_PLAYWAVE },
#endif
    {L"plist", 1, 1, 1, PREFIX_PRIORITY, lplist, LOCALIZED_ALTERNATE_PLIST },
    {L"plists", 0, 0, 0, PREFIX_PRIORITY, lplists, LOCALIZED_ALTERNATE_PLISTS },
    {L"po", 1, 1, 1, PREFIX_PRIORITY, lpo, LOCALIZED_ALTERNATE_PO },
    {L"popdir", 0, 0, 0, PREFIX_PRIORITY, lpopdir, LOCALIZED_ALTERNATE_POPDIR },
    {L"polystart", 0, 0, 0, PREFIX_PRIORITY, lpolystart, LOCALIZED_ALTERNATE_POLYSTART },
    {L"polyend", 0, 0, 0, PREFIX_PRIORITY, lpolyend, LOCALIZED_ALTERNATE_POLYEND },
    {L"polyview", 0, 0, 0, PREFIX_PRIORITY, lpolyview, LOCALIZED_ALTERNATE_POLYVIEW },
    {L"portclose", 0, 0, 0, PREFIX_PRIORITY, lportclose, LOCALIZED_ALTERNATE_PORTCLOSE },
    {L"portflush", 1, 1, 1, PREFIX_PRIORITY, lportflush, LOCALIZED_ALTERNATE_PORTFLUSH },
    {L"portmode", 1, 1, 1, PREFIX_PRIORITY, lportmode, LOCALIZED_ALTERNATE_PORTMODE },
    {L"portopen", 1, 1, 1, PREFIX_PRIORITY, lportopen, LOCALIZED_ALTERNATE_PORTOPEN },
    {L"portreadarray", 2, 2, 2, PREFIX_PRIORITY, lportreadarray, LOCALIZED_ALTERNATE_PORTREADARRAY },
    {L"portreadchar", 0, 0, 0, PREFIX_PRIORITY, lportreadchar, LOCALIZED_ALTERNATE_PORTREADCHAR },
    {L"portwritearray", 2, 2, 2, PREFIX_PRIORITY, lportwritearray, LOCALIZED_ALTERNATE_PORTWRITEARRAY },
    {L"portwritechar", 1, 1, 1, PREFIX_PRIORITY, lportwritechar, LOCALIZED_ALTERNATE_PORTWRITECHAR },
    {L"pos", 0, 0, 0, PREFIX_PRIORITY, lpos, LOCALIZED_ALTERNATE_POS },
    {L"posxyz", 0, 0, 0, PREFIX_PRIORITY, lposxyz, LOCALIZED_ALTERNATE_POSXYZ },
    {L"pot", 1, 1, 1, PREFIX_PRIORITY, lpot, LOCALIZED_ALTERNATE_POT },
    {L"power", 2, 2, 2, PREFIX_PRIORITY, lpower, LOCALIZED_ALTERNATE_POWER },
    {L"pprop", 3, 3, 3, PREFIX_PRIORITY, lpprop, LOCALIZED_ALTERNATE_PPROP },
    {L"ppt", 0, 0, 0, PREFIX_PRIORITY, lpenpaint, LOCALIZED_ALTERNATE_PPT },
    {L"pr", 0, 1, -1, PREFIX_PRIORITY, lprint, LOCALIZED_ALTERNATE_PR },
    {L"primitivep", 1, 1, 1, PREFIX_PRIORITY, lprimitivep, LOCALIZED_ALTERNATE_PRIMITIVEP },
    {L"primitive?", 1, 1, 1, PREFIX_PRIORITY, lprimitivep, LOCALIZED_ALTERNATE_PRIMITIVE_ },
    {L"print", 0, 1, -1, PREFIX_PRIORITY, lprint, LOCALIZED_ALTERNATE_PRINT },
    {L"procedurep", 1, 1, 1, PREFIX_PRIORITY, lprocedurep, LOCALIZED_ALTERNATE_PROCEDUREP },
    {L"procedure?", 1, 1, 1, PREFIX_PRIORITY, lprocedurep, LOCALIZED_ALTERNATE_PROCEDURE_ },
    {L"proplistp", 1, 1, 1, PREFIX_PRIORITY, lproplistp, LOCALIZED_ALTERNATE_PROPLISTP },
    {L"proplist?", 1, 1, 1, PREFIX_PRIORITY, lproplistp, LOCALIZED_ALTERNATE_PROPLIST_ },
    {L"procedures", 0, 0, 0, PREFIX_PRIORITY, lprocedures, LOCALIZED_ALTERNATE_PROCEDURES },
    {L"product", 0, 2, -1, PREFIX_PRIORITY, lmul, LOCALIZED_ALTERNATE_PRODUCT },
    {L"pu", 0, 0, 0, PREFIX_PRIORITY, lpenup, LOCALIZED_ALTERNATE_PU },
    {L"px", 0, 0, 0, PREFIX_PRIORITY, lpenreverse, LOCALIZED_ALTERNATE_PX },
    {L"questionbox", 2, 2, 2, PREFIX_PRIORITY, lquestionbox, LOCALIZED_ALTERNATE_QUESTIONBOX },
    {L"quotient", 1, 2, 2, PREFIX_PRIORITY, ldivide, LOCALIZED_ALTERNATE_QUOTIENT },
    {L"radarccos", 1, 1, 1, PREFIX_PRIORITY, lradacos, LOCALIZED_ALTERNATE_RADARCCOS },
    {L"radarcsin", 1, 1, 1, PREFIX_PRIORITY, lradasin, LOCALIZED_ALTERNATE_RADARCSIN },
    {L"radarctan", 1, 1, 2, PREFIX_PRIORITY, lradatan, LOCALIZED_ALTERNATE_RADARCTAN },
    {L"radcos", 1, 1, 1, PREFIX_PRIORITY, lradcos, LOCALIZED_ALTERNATE_RADCOS },
    {L"radiobuttoncreate", 8, 8, 8, PREFIX_PRIORITY, lradiobuttoncreate, LOCALIZED_ALTERNATE_RADIOBUTTONCREATE },
    {L"radiobuttonenable", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonenable, LOCALIZED_ALTERNATE_RADIOBUTTONENABLE },
    {L"radiobuttondelete", 1, 1, 1, PREFIX_PRIORITY, lradiobuttondelete, LOCALIZED_ALTERNATE_RADIOBUTTONDELETE },
    {L"radiobuttonget", 1, 1, 1, PREFIX_PRIORITY, lradiobuttonget, LOCALIZED_ALTERNATE_RADIOBUTTONGET },
    {L"radiobuttonset", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonset, LOCALIZED_ALTERNATE_RADIOBUTTONSET },
    {L"radsin", 1, 1, 1, PREFIX_PRIORITY, lradsin, LOCALIZED_ALTERNATE_RADSIN },
    {L"radtan", 1, 1, 1, PREFIX_PRIORITY, lradtan, LOCALIZED_ALTERNATE_RADTAN },
    {L"random", 1, 1, 1, PREFIX_PRIORITY, lrandom, LOCALIZED_ALTERNATE_RANDOM },
    {L"rawascii", 1, 1, 1, PREFIX_PRIORITY, lrawascii, LOCALIZED_ALTERNATE_RAWASCII },
    {L"rc", 0, 0, 0, PREFIX_PRIORITY, lreadchar, LOCALIZED_ALTERNATE_RC },
    {L"rcs", 1, 1, 1, PREFIX_PRIORITY, lreadchars, LOCALIZED_ALTERNATE_RCS },
    {L"readchar", 0, 0, 0, PREFIX_PRIORITY, lreadchar, LOCALIZED_ALTERNATE_READCHAR },
    {L"readchars", 1, 1, 1, PREFIX_PRIORITY, lreadchars, LOCALIZED_ALTERNATE_READCHARS },
    {L"reader", 0, 0, 0, PREFIX_PRIORITY, lreader, LOCALIZED_ALTERNATE_READER },
    {L"readlist", 0, 0, 0, PREFIX_PRIORITY, lreadlist, LOCALIZED_ALTERNATE_READLIST },
    {L"readpos", 0, 0, 0, PREFIX_PRIORITY, lreadpos, LOCALIZED_ALTERNATE_READPOS },
    {L"readrawline", 0, 0, 0, PREFIX_PRIORITY, lreadrawline, LOCALIZED_ALTERNATE_READRAWLINE },
    {L"readword", 0, 0, 0, PREFIX_PRIORITY, lreadword, LOCALIZED_ALTERNATE_READWORD },
    {L"remainder", 2, 2, 2, PREFIX_PRIORITY, lremainder, LOCALIZED_ALTERNATE_REMAINDER },
    {L"remprop", 2, 2, 2, PREFIX_PRIORITY, lremprop, LOCALIZED_ALTERNATE_REMPROP },
    {L"repcount", 0, 0, 0, PREFIX_PRIORITY, lrepcount, LOCALIZED_ALTERNATE_REPCOUNT },
    {L"repeat", 2, 2, 2, MACRO_PRIORITY, lrepeat, LOCALIZED_ALTERNATE_REPEAT },
    {L"rerandom", 0, 0, 1, PREFIX_PRIORITY, lrerandom, LOCALIZED_ALTERNATE_RERANDOM },
    {L"right", 1, 1, 1, PREFIX_PRIORITY, lright, LOCALIZED_ALTERNATE_RIGHT },
    {L"rightroll", 1, 1, 1, PREFIX_PRIORITY, lrightroll, LOCALIZED_ALTERNATE_RIGHTROLL },
    {L"rl", 0, 0, 0, PREFIX_PRIORITY, lreadlist, LOCALIZED_ALTERNATE_RL },
    {L"rmdir", 1, 1, 1, PREFIX_PRIORITY, lrmdir, LOCALIZED_ALTERNATE_RMDIR },
    {L"roll", 0, 0, 0, PREFIX_PRIORITY, lroll, LOCALIZED_ALTERNATE_ROLL },
    {L"round", 1, 1, 1, PREFIX_PRIORITY, lround, LOCALIZED_ALTERNATE_ROUND },
    {L"rr", 1, 1, 1, PREFIX_PRIORITY, lrightroll, LOCALIZED_ALTERNATE_RR },
    {L"rt", 1, 1, 1, PREFIX_PRIORITY, lright, LOCALIZED_ALTERNATE_RT },
    {L"run", 1, 1, 1, MACRO_PRIORITY, lrun, LOCALIZED_ALTERNATE_RUN },
    {L"runparse", 1, 1, 1, PREFIX_PRIORITY, lrunparse, LOCALIZED_ALTERNATE_RUNPARSE },
    {L"runresult", 1, 1, 1, MACRO_PRIORITY, lrunresult, LOCALIZED_ALTERNATE_RUNRESULT },
    {L"rw", 0, 0, 0, PREFIX_PRIORITY, lreadword, LOCALIZED_ALTERNATE_RW },
    {L"save", 1, 1, 1, PREFIX_PRIORITY, lsave, LOCALIZED_ALTERNATE_SAVE },
    {L"screencolor", 0, 0, 0, PREFIX_PRIORITY, lscreencolor, LOCALIZED_ALTERNATE_SCREENCOLOR },
    {L"scrollbarcreate", 7, 7, 7, PREFIX_PRIORITY, lscrollbarcreate, LOCALIZED_ALTERNATE_SCROLLBARCREATE },
    {L"scrollbarenable", 2, 2, 2, PREFIX_PRIORITY, lscrollbarenable, LOCALIZED_ALTERNATE_SCROLLBARENABLE },
    {L"scrollbardelete", 1, 1, 1, PREFIX_PRIORITY, lscrollbardelete, LOCALIZED_ALTERNATE_SCROLLBARDELETE },
    {L"scrollbarget", 1, 1, 1, PREFIX_PRIORITY, lscrollbarget, LOCALIZED_ALTERNATE_SCROLLBARGET },
    {L"scrollbarset", 4, 4, 4, PREFIX_PRIORITY, lscrollbarset, LOCALIZED_ALTERNATE_SCROLLBARSET },
    {L"scrollx", 1, 1, 1, PREFIX_PRIORITY, lscrollx, LOCALIZED_ALTERNATE_SCROLLX },
    {L"scrolly", 1, 1, 1, PREFIX_PRIORITY, lscrolly, LOCALIZED_ALTERNATE_SCROLLY },
    {L"scrunch", 0, 0, 0, PREFIX_PRIORITY, lscrunch, LOCALIZED_ALTERNATE_SCRUNCH },
    {L"se", 0, 2, -1, PREFIX_PRIORITY, lsentence, LOCALIZED_ALTERNATE_SE },
    {L"selectbox", 2, 2, 2, PREFIX_PRIORITY, lselectbox, LOCALIZED_ALTERNATE_SELECTBOX },
    {L"sentence", 0, 2, -1, PREFIX_PRIORITY, lsentence, LOCALIZED_ALTERNATE_SENTENCE },
    {L"setactivearea", 1, 1, 1, PREFIX_PRIORITY, lsetactivearea, LOCALIZED_ALTERNATE_SETACTIVEAREA },
    {L"setbitindex", 1, 1, 1, PREFIX_PRIORITY, lsetbitindex, LOCALIZED_ALTERNATE_SETBITINDEX },
    {L"setbitmode", 1, 1, 1, PREFIX_PRIORITY, lsetbitmode, LOCALIZED_ALTERNATE_SETBITMODE },
    {L"setclip", 3, 3, 3, PREFIX_PRIORITY, lsetclip, LOCALIZED_ALTERNATE_SETCLIP },
    // {L"setcursor", 1, 1, 1, PREFIX_PRIORITY, lsetcursor, LOCALIZED_ALTERNATE_SETCURSOR },
    {L"setcursornowait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorarrow, LOCALIZED_ALTERNATE_SETCURSORNOWAIT },
    {L"setcursorwait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorwait, LOCALIZED_ALTERNATE_SETCURSORWAIT },
    {L"setfc", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor, LOCALIZED_ALTERNATE_SETFC },
    {L"setfloodcolor", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor, LOCALIZED_ALTERNATE_SETFLOODCOLOR },
    {L"setfocus", 1, 1, 1, PREFIX_PRIORITY, lsetfocus, LOCALIZED_ALTERNATE_SETFOCUS },
    {L"seth", 1, 1, 1, PREFIX_PRIORITY, lsetheading, LOCALIZED_ALTERNATE_SETH },
    {L"setheading", 1, 1, 1, PREFIX_PRIORITY, lsetheading, LOCALIZED_ALTERNATE_SETHEADING },
    {L"setitem", 3, 3, 3, PREFIX_PRIORITY, lsetitem, LOCALIZED_ALTERNATE_SETITEM },
    {L"setlabelfont", 1, 1, 1, PREFIX_PRIORITY, lsetlabelfont, LOCALIZED_ALTERNATE_SETLABELFONT },
    {L"setlight", 1, 1, 1, PREFIX_PRIORITY, lsetlight, LOCALIZED_ALTERNATE_SETLIGHT },
    {L"setmargins", 1, 1, 1, PREFIX_PRIORITY, lsetmargins, LOCALIZED_ALTERNATE_SETMARGINS },
    {L"setpc", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor, LOCALIZED_ALTERNATE_SETPC },
    {L"setpencolor", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor, LOCALIZED_ALTERNATE_SETPENCOLOR },
    {L"setpenpattern", 1, 1, 1, PREFIX_PRIORITY, lsetpenpattern, LOCALIZED_ALTERNATE_SETPENPATTERN },
    {L"setpensize", 1, 1, 1, PREFIX_PRIORITY, lsetpensize, LOCALIZED_ALTERNATE_SETPENSIZE },
    {L"setpitch", 1, 1, 1, PREFIX_PRIORITY, lsetpitch, LOCALIZED_ALTERNATE_SETPITCH },
    {L"setpixel", 1, 1, 1, PREFIX_PRIORITY, lsetpixel, LOCALIZED_ALTERNATE_SETPIXEL },
    {L"setpos", 1, 1, 1, PREFIX_PRIORITY, lsetpos, LOCALIZED_ALTERNATE_SETPOS },
    {L"setposxyz", 1, 1, 1, PREFIX_PRIORITY, lsetposxyz, LOCALIZED_ALTERNATE_SETPOSXYZ },
    {L"setread", 1, 1, 1, PREFIX_PRIORITY, lsetread, LOCALIZED_ALTERNATE_SETREAD },
    {L"setreadpos", 1, 1, 1, PREFIX_PRIORITY, lsetreadpos, LOCALIZED_ALTERNATE_SETREADPOS },
    {L"setroll", 1, 1, 1, PREFIX_PRIORITY, lsetroll, LOCALIZED_ALTERNATE_SETROLL },
    {L"setsc", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor, LOCALIZED_ALTERNATE_SETSC },
    {L"setscreencolor", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor, LOCALIZED_ALTERNATE_SETSCREENCOLOR },
    {L"setscrunch", 2, 2, 2, PREFIX_PRIORITY, lsetscrunch, LOCALIZED_ALTERNATE_SETSCRUNCH },
#if !defined WX_PURE
    {L"settimer", 3, 3, 3, PREFIX_PRIORITY, lsettimer, LOCALIZED_ALTERNATE_SETTIMER },
#endif
    {L"setturtle", 1, 1, 2, PREFIX_PRIORITY, lsetturtle, LOCALIZED_ALTERNATE_SETTURTLE },
    {L"setturtlemode", 1, 1, 1, PREFIX_PRIORITY, lsetturtlemode, LOCALIZED_ALTERNATE_SETTURTLEMODE },
    {L"setwrite", 1, 1, 1, PREFIX_PRIORITY, lsetwrite, LOCALIZED_ALTERNATE_SETWRITE },
    {L"setwritepos", 1, 1, 1, PREFIX_PRIORITY, lsetwritepos, LOCALIZED_ALTERNATE_SETWRITEPOS },
    {L"setx", 1, 1, 1, PREFIX_PRIORITY, lsetx, LOCALIZED_ALTERNATE_SETX },
    {L"setxy", 2, 2, 2, PREFIX_PRIORITY, lsetxy, LOCALIZED_ALTERNATE_SETXY },
    {L"setxyz", 3, 3, 3, PREFIX_PRIORITY, lsetxyz, LOCALIZED_ALTERNATE_SETXYZ },
    {L"sety", 1, 1, 1, PREFIX_PRIORITY, lsety, LOCALIZED_ALTERNATE_SETY },
    {L"setz", 1, 1, 1, PREFIX_PRIORITY, lsetz, LOCALIZED_ALTERNATE_SETZ },
    {L"shell", 1, 1, 2, PREFIX_PRIORITY, lshell, LOCALIZED_ALTERNATE_SHELL },
    {L"show", 0, 1, -1, PREFIX_PRIORITY, lshow, LOCALIZED_ALTERNATE_SHOW },
    {L"shownp", 0, 0, 0, PREFIX_PRIORITY, lshownp, LOCALIZED_ALTERNATE_SHOWNP },
    {L"shown?", 0, 0, 0, PREFIX_PRIORITY, lshownp, LOCALIZED_ALTERNATE_SHOWN_ },
    {L"showturtle", 0, 0, 0, PREFIX_PRIORITY, lshowturtle, LOCALIZED_ALTERNATE_SHOWTURTLE },
    {L"sin", 1, 1, 1, PREFIX_PRIORITY, lsin, LOCALIZED_ALTERNATE_SIN },
#if !defined WX_PURE
    {L"sound", 1, 1, 1, PREFIX_PRIORITY, lsound, LOCALIZED_ALTERNATE_SOUND },
#endif
    {L"splitscreen", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen, LOCALIZED_ALTERNATE_SPLITSCREEN },
    {L"sqrt", 1, 1, 1, PREFIX_PRIORITY, lsqrt, LOCALIZED_ALTERNATE_SQRT },
    {L"ss", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen, LOCALIZED_ALTERNATE_SS },
    {L"st", 0, 0, 0, PREFIX_PRIORITY, lshowturtle, LOCALIZED_ALTERNATE_ST },
    {L"standout", 1, 1, 1, PREFIX_PRIORITY, lstandout, LOCALIZED_ALTERNATE_STANDOUT },
    {L"staticcreate", 7, 7, 7, PREFIX_PRIORITY, lstaticcreate, LOCALIZED_ALTERNATE_STATICCREATE },
    {L"staticdelete", 1, 1, 1, PREFIX_PRIORITY, lstaticdelete, LOCALIZED_ALTERNATE_STATICDELETE },
    {L"staticupdate", 2, 2, 2, PREFIX_PRIORITY, lstaticupdate, LOCALIZED_ALTERNATE_STATICUPDATE },
    {L"status", 0, 0, 0, PREFIX_PRIORITY, lstatus, LOCALIZED_ALTERNATE_STATUS },
    {L"step", 1, 1, 1, PREFIX_PRIORITY, lstep, LOCALIZED_ALTERNATE_STEP },
    {L"stepped", 0, 0, 0, PREFIX_PRIORITY, lstepped, LOCALIZED_ALTERNATE_STEPPED },
    {L"stop", 0, 0, 0, STOP_PRIORITY, lstop, LOCALIZED_ALTERNATE_STOP },
    {L"substringp", 2, 2, 2, PREFIX_PRIORITY, lsubstringp, LOCALIZED_ALTERNATE_SUBSTRINGP },
    {L"substring?", 2, 2, 2, PREFIX_PRIORITY, lsubstringp, LOCALIZED_ALTERNATE_SUBSTRING_ },
    {L"sum", 0, 2, -1, PREFIX_PRIORITY, ladd, LOCALIZED_ALTERNATE_SUM },
    // {L"tag", 1, 1, 1, PREFIX_PRIORITY, ltag, LOCALIZED_ALTERNATE_TAG },
    {L"tan", 1, 1, 1, PREFIX_PRIORITY, ltan, LOCALIZED_ALTERNATE_TAN },
    {L"test", 1, 1, 1, PREFIX_PRIORITY, ltest, LOCALIZED_ALTERNATE_TEST },
    {L"text", 1, 1, 1, PREFIX_PRIORITY, ltext, LOCALIZED_ALTERNATE_TEXT },
    {L"textscreen", 0, 0, 0, PREFIX_PRIORITY, ltextscreen, LOCALIZED_ALTERNATE_TEXTSCREEN },
    {L"thing", 1, 1, 1, PREFIX_PRIORITY, lthing, LOCALIZED_ALTERNATE_THING },
    {L"throw", 1, 1, 3, PREFIX_PRIORITY, lthrow, LOCALIZED_ALTERNATE_THROW },
    {L"time", 0, 0, 0, PREFIX_PRIORITY, ltime, LOCALIZED_ALTERNATE_TIME },
    {L"timemilli", 0, 0, 0, PREFIX_PRIORITY, ltimemilli, LOCALIZED_ALTERNATE_TIMEMILLI },
    {L"to", -1, -1, -1, PREFIX_PRIORITY, lto, LOCALIZED_ALTERNATE_TO },
    {L"tone", 2, 2, 2, PREFIX_PRIORITY, ltone, LOCALIZED_ALTERNATE_TONE },
    {L"towards", 1, 1, 1, PREFIX_PRIORITY, ltowards, LOCALIZED_ALTERNATE_TOWARDS },
    {L"towardsxyz", 1, 1, 1, PREFIX_PRIORITY, ltowardsxyz, LOCALIZED_ALTERNATE_TOWARDSXYZ },
    {L"trace", 1, 1, 1, PREFIX_PRIORITY, ltrace, LOCALIZED_ALTERNATE_TRACE },
    {L"traced", 0, 0, 0, PREFIX_PRIORITY, ltraced, LOCALIZED_ALTERNATE_TRACED },
    {L"ts", 0, 0, 0, PREFIX_PRIORITY, ltextscreen, LOCALIZED_ALTERNATE_TS },
    {L"turtle", 0, 0, 0, PREFIX_PRIORITY, lturtle, LOCALIZED_ALTERNATE_TURTLE },
    {L"turtlemode", 0, 0, 0, PREFIX_PRIORITY, lturtlemode, LOCALIZED_ALTERNATE_TURTLEMODE },
    {L"turtles", 0, 0, 0, PREFIX_PRIORITY, lturtles, LOCALIZED_ALTERNATE_TURTLES },
    {L"type", 0, 1, -1, PREFIX_PRIORITY, ltype, LOCALIZED_ALTERNATE_TYPE },
    {L"unbury", 1, 1, 1, PREFIX_PRIORITY, lunbury, LOCALIZED_ALTERNATE_UNBURY },
    {L"unstep", 1, 1, 1, PREFIX_PRIORITY, lunstep, LOCALIZED_ALTERNATE_UNSTEP },
    {L"untrace", 1, 1, 1, PREFIX_PRIORITY, luntrace, LOCALIZED_ALTERNATE_UNTRACE },
    {L"up", 1, 1, 1, PREFIX_PRIORITY, luppitch, LOCALIZED_ALTERNATE_UP },
    {L"uppercase", 1, 1, 1, PREFIX_PRIORITY, luppercase, LOCALIZED_ALTERNATE_UPPERCASE },
    {L"uppitch", 1, 1, 1, PREFIX_PRIORITY, luppitch, LOCALIZED_ALTERNATE_UPPITCH },
    {L"wait", 1, 1, 1, PREFIX_PRIORITY, lwait, LOCALIZED_ALTERNATE_WAIT },
    {L"window", 0, 0, 0, PREFIX_PRIORITY, lwindow, LOCALIZED_ALTERNATE_WINDOW },
    {L"windowcreate", 8, 8, 8, PREFIX_PRIORITY, lwindowcreate, LOCALIZED_ALTERNATE_WINDOWCREATE },
    {L"windowenable", 2, 2, 2, PREFIX_PRIORITY, lwindowenable, LOCALIZED_ALTERNATE_WINDOWENABLE },
    {L"windowdelete", 1, 1, 1, PREFIX_PRIORITY, lwindowdelete, LOCALIZED_ALTERNATE_WINDOWDELETE },
    {L"windowfileedit", 2, 2, 2, PREFIX_PRIORITY, lwindowfileedit, LOCALIZED_ALTERNATE_WINDOWFILEEDIT },
    {L"windowset", 2, 2, 2, PREFIX_PRIORITY, lwindowset, LOCALIZED_ALTERNATE_WINDOWSET },
    {L"winhelp", 1, 1, 2, PREFIX_PRIORITY, lwinhelp, LOCALIZED_ALTERNATE_WINHELP },
    {L"word", 0, 2, -1, PREFIX_PRIORITY, lword, LOCALIZED_ALTERNATE_WORD },
    {L"wordp", 1, 1, 1, PREFIX_PRIORITY, lwordp, LOCALIZED_ALTERNATE_WORDP },
    {L"word?", 1, 1, 1, PREFIX_PRIORITY, lwordp, LOCALIZED_ALTERNATE_WORD_ },
    {L"wrap", 0, 0, 0, PREFIX_PRIORITY, lwrap, LOCALIZED_ALTERNATE_WRAP },
    {L"writepos", 0, 0, 0, PREFIX_PRIORITY, lwritepos, LOCALIZED_ALTERNATE_WRITEPOS },
    {L"writer", 0, 0, 0, PREFIX_PRIORITY, lwriter, LOCALIZED_ALTERNATE_WRITER },
    {L"yesnobox", 2, 2, 2, PREFIX_PRIORITY, lyesnobox, LOCALIZED_ALTERNATE_YESNOBOX },
    {L"yield", 0, 0, 0, PREFIX_PRIORITY, lyield, LOCALIZED_ALTERNATE_YIELD },
    {L"zoom", 1, 1, 1, PREFIX_PRIORITY, lzoom, LOCALIZED_ALTERNATE_ZOOM },
};

// Interns a primitive procedure by its name.
// If a procedure was previously interned with the same Name,
// then the new procedure will be called in its place (that is,
// the later call wins).
static
void
intern_primitive(
    const wchar_t * Name,
    short        MinimumArgs,
    short        DefaultArgs,
    short        MaximumArgs,
    short        Priority,
    logofunc     Primitive
    )
{
    NODE *proc;
    if (Priority == MACRO_PRIORITY)
    {
        proc = vref(newnode(MACRO));
    }
    else if (Priority <= TAIL_PRIORITY)
    {
        // .MAYBEOUTPUT, OUTPUT, or STOP.
        proc = vref(newnode(TAILFORM));
    }
    else if ((Priority & ~4) == (PREFIX_PRIORITY & ~4))
    {
        proc = vref(newnode(PRIM)); // include "--"
    }
    else
    {
        proc = vref(newnode(INFIX));
    }
   
    setprimpri(proc,  Priority);
    setprimfun(proc,  Primitive);
    setprimdflt(proc, DefaultArgs);
    setprimmax(proc,  MaximumArgs);
    setprimmin(proc,  MinimumArgs);

    // Make a new case object for this name.
    // The call to make_instance() is what interns the name in the global hash table.
    NODE * primitive_name = vref(make_static_strnode(Name));
    NODE * lowercase_name = vref(make_lowercase_strnode_from_strnode(primitive_name));
    NODE * case_node      = vref(make_instance(primitive_name, lowercase_name));
    setprocnode__caseobj(case_node, proc);

    if (nodetype(proc) == MACRO)
    {
        setflag__caseobj(case_node, PROC_MACRO);
    }

    deref(proc);
    deref(case_node);
    deref(primitive_name);
    deref(lowercase_name);
}


// Initialize the language engine and all associated variables.
void init()
{
    init_intern();

    fill_reserve_tank();
    Unbound = newnode(PUNBOUND);

    init_ecma_array();
   
    // intern all of the primitives.
    //
    // We intern all of the English forms first so if there
    // are conflicts between an English command and a localized command,
    // the localized one will win.  For example, in the French version,
    // we want "ct" to mean "cachetortue" (HIDETURTLE), not "CLEARTEXT",
    // even though all other locales will use "ct" to mean "CLEARTEXT".
    // 

    // intern all of the primitives by their English name
    for (size_t i = 0; i < ARRAYSIZE(prims); i++)
    {
        // intern the current primitive
        intern_primitive(
            prims[i].name,
            prims[i].minargs,
            prims[i].defargs,
            prims[i].maxargs,
            prims[i].priority,
            prims[i].prim);
    }

    // Now intern the commands by their localized name
    for (size_t i = 0; i < ARRAYSIZE(prims); i++)
    {
        // If there is an alternate name for the primitive,
        // and it's different from the normal name, make a
        // primivite out of it, too.
        if (prims[i].alternatename != NULL && 
            0 != wcscmp(prims[i].name, prims[i].alternatename))
        {
            intern_primitive(
                prims[i].alternatename,
                prims[i].minargs,
                prims[i].defargs,
                prims[i].maxargs,
                prims[i].priority,
                prims[i].prim);
        }
    }


    Truex.Initialize(L"true",   LOCALIZED_ALTERNATE_TRUE);
    Falsex.Initialize(L"false", LOCALIZED_ALTERNATE_FALSE);
    To.Initialize(L"to",        LOCALIZED_ALTERNATE_TO);
    End.Initialize(L"end",      LOCALIZED_ALTERNATE_END);

    Toplevel.Initialize(L"toplevel",  LOCALIZED_ALTERNATE_TOPLEVEL);
    System.Initialize(L"system",      LOCALIZED_ALTERNATE_SYSTEM);
    Error.Initialize(L"error",        LOCALIZED_ALTERNATE_ERROR);

    Left_Paren = intern(make_static_strnode(L"("));
    Right_Paren = intern(make_static_strnode(L")"));
    Minus_Sign = intern(make_static_strnode(L"-"));
    Minus_Tight = intern(make_static_strnode(L"--"));
    Query = intern(make_static_strnode(L"?"));
    Null_Word = intern(make_static_strnode(L""));
    Macro = intern(make_static_strnode(L".macro"));
    If = intern(make_static_strnode(L"if"));
    Ifelse = intern(make_static_strnode(L"ifelse"));
    Redefp.Initialize(L"redefp",                   LOCALIZED_ALTERNATE_REDEFP);
    Caseignoredp.Initialize(L"caseignoredp",       LOCALIZED_ALTERNATE_CASEIGNOREDP);
    Erract.Initialize(L"erract",                   LOCALIZED_ALTERNATE_ERRACT);
    Printdepthlimit.Initialize(L"printdepthlimit", LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT);
    Printwidthlimit.Initialize(L"printwidthlimit", LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT);
    Pause = intern(make_static_strnode(L"pause"));
    Startup.Initialize(L"startup",           LOCALIZED_ALTERNATE_STARTUP);
    Output = intern(make_static_strnode(L"output"));
    Stop = intern(make_static_strnode(L"stop"));
    Goto = intern(make_static_strnode(L"goto"));
    Tag = intern(make_static_strnode(L"Tag"));
    the_generation = vref(cons_list(NIL));   // some unique pointer
    g_ParseErrorNotEnoughInputs = vref(cons_list(NIL));  // some unique pointer

    repcountup = -1;
}

void uninit()
{
#ifndef WX_PURE
    // uninitialize the network subsystem
    lnetshutdown(NIL);
#endif

    // uninitialize the file subsystem
    uninitialize_files();

    deref(g_ParseErrorNotEnoughInputs);
    deref(the_generation);

    // free the nodes associated with error handling
    uninitialize_error();

    // free the state associated with the evaluator
    uninitialize_eval();

    // free the state associated with the windowing subsystem
    uninitialize_windows();

    // free the objects
    release_all_objects();

    // free our reserve tank of nodes
    use_reserve_tank();

    // free all outstanding nodes
    free_segment_list();

    // free the parser
    uninitialize_parser();

    // free the internal buffer for the combobox
    uninitialize_combobox();
   
    // free the memory associated with keyboard capture
    keyboard_uninit();

    // free the memory associated with mouse capture
    mouse_uninit();

    // free the state associated with the timer events
    uninitialize_timers();

    // free the state associated with DLLs which the programmer loaded.
    uninitialize_dlls();
}
