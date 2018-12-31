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
//   #include "debugheap.h"

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

	static const PRIMTYPE prims[] =
	{
		{L"*", 2, 2, 2, PREFIX_PRIORITY + 3, lmul },
		{L"+", 2, 2, 2, PREFIX_PRIORITY + 2, ladd },
		{L"-", 2, 2, 2, PREFIX_PRIORITY + 2, lsub },
		{L"--", 1, 1, 1, PREFIX_PRIORITY + 4, lsub },
		{L".defmacro", 2, 2, 2, PREFIX_PRIORITY, ldefmacro, GetResourceString(L"LOCALIZED_ALTERNATE__DEFMACRO") },
		{L".eq", 2, 2, 2, PREFIX_PRIORITY, l_eq, GetResourceString(L"LOCALIZED_ALTERNATE__EQ") },
		{L".macro", -1, -1, -1, PREFIX_PRIORITY, lmacro, GetResourceString(L"LOCALIZED_ALTERNATE__MACRO") },
		{L".maybeoutput", 1, 1, 1, MAYBE_PRIORITY, loutput, GetResourceString(L"LOCALIZED_ALTERNATE__MAYBEOUTPUT") },
		{L".setbf", 2, 2, 2, PREFIX_PRIORITY, l_setbf, GetResourceString(L"LOCALIZED_ALTERNATE__SETBF") },
		{L".setfirst", 2, 2, 2, PREFIX_PRIORITY, l_setfirst, GetResourceString(L"LOCALIZED_ALTERNATE__SETFIRST") },
		{L".setitem", 3, 3, 3, PREFIX_PRIORITY, l_setitem, GetResourceString(L"LOCALIZED_ALTERNATE__SETITEM") },
		{L"/", 2, 2, 2, PREFIX_PRIORITY + 3, ldivide },
		{L"<", 2, 2, 2, PREFIX_PRIORITY + 1, llessp },
		{L"=", 2, 2, 2, PREFIX_PRIORITY + 1, lequalp },
		{L">", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterp },
		{L"<=", 2, 2, 2, PREFIX_PRIORITY + 1, llessequalp },
		{L"<>", 2, 2, 2, PREFIX_PRIORITY + 1, lnotequalp },
		{L">=", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterequalp },
		{L"?", 0, 0, 1, PREFIX_PRIORITY, lqm },
		{L"activearea", 0, 0, 0, PREFIX_PRIORITY, lactivearea, GetResourceString(L"LOCALIZED_ALTERNATE_ACTIVEAREA") },
		{L"allopen", 0, 0, 0, PREFIX_PRIORITY, lallopen, GetResourceString(L"LOCALIZED_ALTERNATE_ALLOPEN") },
		{L"and", 0, 2, -1, PREFIX_PRIORITY, land, GetResourceString(L"LOCALIZED_ALTERNATE_AND") },
		{L"apply", 2, 2, 2, MACRO_PRIORITY, lapply, GetResourceString(L"LOCALIZED_ALTERNATE_APPLY") },
		{L"arccos", 1, 1, 1, PREFIX_PRIORITY, lacos, GetResourceString(L"LOCALIZED_ALTERNATE_ARCCOS") },
		{L"arcsin", 1, 1, 1, PREFIX_PRIORITY, lasin, GetResourceString(L"LOCALIZED_ALTERNATE_ARCSIN") },
		{L"arctan", 1, 1, 2, PREFIX_PRIORITY, latan, GetResourceString(L"LOCALIZED_ALTERNATE_ARCTAN") },
		{L"arity", 1, 1, 1, PREFIX_PRIORITY, larity, GetResourceString(L"LOCALIZED_ALTERNATE_ARITY") },
		{L"array", 1, 1, 2, PREFIX_PRIORITY, larray, GetResourceString(L"LOCALIZED_ALTERNATE_ARRAY") },
		{L"arrayp", 1, 1, 1, PREFIX_PRIORITY, larrayp, GetResourceString(L"LOCALIZED_ALTERNATE_ARRAYP") },
		{L"array?", 1, 1, 1, PREFIX_PRIORITY, larrayp, GetResourceString(L"LOCALIZED_ALTERNATE_ARRAY_") },
		{L"ascii", 1, 1, 1, PREFIX_PRIORITY, lascii, GetResourceString(L"LOCALIZED_ALTERNATE_ASCII") },
		{L"ashift", 2, 2, 2, PREFIX_PRIORITY, lashift, GetResourceString(L"LOCALIZED_ALTERNATE_ASHIFT") },
		{L"back", 1, 1, 1, PREFIX_PRIORITY, lback, GetResourceString(L"LOCALIZED_ALTERNATE_BACK") },
		{L"backslashedp", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp, GetResourceString(L"LOCALIZED_ALTERNATE_BACKSLASHEDP") },
		{L"backslashed?", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp, GetResourceString(L"LOCALIZED_ALTERNATE_BACKSLASHED_") },
		{L"beforep", 2, 2, 2, PREFIX_PRIORITY, lbeforep, GetResourceString(L"LOCALIZED_ALTERNATE_BEFOREP") },
		{L"before?", 2, 2, 2, PREFIX_PRIORITY, lbeforep, GetResourceString(L"LOCALIZED_ALTERNATE_BEFORE_") },
		{L"bf", 1, 1, 1, PREFIX_PRIORITY, lbutfirst, GetResourceString(L"LOCALIZED_ALTERNATE_BF") },
		{L"bfs", 1, 1, 1, PREFIX_PRIORITY, lbfs, GetResourceString(L"LOCALIZED_ALTERNATE_BFS") },
		{L"bitand", 0, 2, -1, PREFIX_PRIORITY, lbitand, GetResourceString(L"LOCALIZED_ALTERNATE_BITAND") },
		{L"bitblock", 2, 2, 2, PREFIX_PRIORITY, lbitblock, GetResourceString(L"LOCALIZED_ALTERNATE_BITBLOCK") },
		{L"bitcopy", 2, 2, 2, PREFIX_PRIORITY, lbitcopy, GetResourceString(L"LOCALIZED_ALTERNATE_BITCOPY") },
		{L"bitcut", 2, 2, 2, PREFIX_PRIORITY, lbitcut, GetResourceString(L"LOCALIZED_ALTERNATE_BITCUT") },
		{L"bitfit", 2, 2, 2, PREFIX_PRIORITY, lbitfit, GetResourceString(L"LOCALIZED_ALTERNATE_BITFIT") },
		{L"bitindex", 0, 0, 0, PREFIX_PRIORITY, lbitindex, GetResourceString(L"LOCALIZED_ALTERNATE_BITINDEX") },
		{L"bitload", 1, 1, 1, PREFIX_PRIORITY, lbitload, GetResourceString(L"LOCALIZED_ALTERNATE_BITLOAD") },
		{L"bitloadsize", 1, 1, 1, PREFIX_PRIORITY, lbitloadsize, GetResourceString(L"LOCALIZED_ALTERNATE_BITLOADSIZE") },
		{L"bitsize", 0, 0, 0, PREFIX_PRIORITY, lbitsize, GetResourceString(L"LOCALIZED_ALTERNATE_BITSIZE") },
		{L"bitmapturtle", 0, 0, 1, PREFIX_PRIORITY, lbitmapturtle, GetResourceString(L"LOCALIZED_ALTERNATE_BITMAPTURTLE") },
		{L"bitmode", 0, 0, 0, PREFIX_PRIORITY, lbitmode, GetResourceString(L"LOCALIZED_ALTERNATE_BITMODE") },
		{L"bitnot", 1, 1, 1, PREFIX_PRIORITY, lbitnot, GetResourceString(L"LOCALIZED_ALTERNATE_BITNOT") },
		{L"bitor", 0, 2, -1, PREFIX_PRIORITY, lbitor, GetResourceString(L"LOCALIZED_ALTERNATE_BITOR") },
		{L"bitpaste", 0, 0, 0, PREFIX_PRIORITY, lbitpaste, GetResourceString(L"LOCALIZED_ALTERNATE_BITPASTE") },
		{L"bitpastetoindex", 3, 3, 3, PREFIX_PRIORITY, lbitpastetoindex, GetResourceString(L"LOCALIZED_ALTERNATE_BITPASTETOINDEX") },
		{L"bitsave", 1, 1, 2, PREFIX_PRIORITY, lbitsave, GetResourceString(L"LOCALIZED_ALTERNATE_BITSAVE") },
		{L"bitxor", 0, 2, -1, PREFIX_PRIORITY, lbitxor, GetResourceString(L"LOCALIZED_ALTERNATE_BITXOR") },
		{L"bk", 1, 1, 1, PREFIX_PRIORITY, lback, GetResourceString(L"LOCALIZED_ALTERNATE_BK") },
		{L"bl", 1, 1, 1, PREFIX_PRIORITY, lbutlast, GetResourceString(L"LOCALIZED_ALTERNATE_BL") },
		{L"buried", 0, 0, 0, PREFIX_PRIORITY, lburied, GetResourceString(L"LOCALIZED_ALTERNATE_BURIED") },
		{L"bury", 1, 1, 1, PREFIX_PRIORITY, lbury, GetResourceString(L"LOCALIZED_ALTERNATE_BURY") },
		{L"butfirst", 1, 1, 1, PREFIX_PRIORITY, lbutfirst, GetResourceString(L"LOCALIZED_ALTERNATE_BUTFIRST") },
		{L"butfirsts", 1, 1, 1, PREFIX_PRIORITY, lbfs, GetResourceString(L"LOCALIZED_ALTERNATE_BUTFIRSTS") },
		{L"butlast", 1, 1, 1, PREFIX_PRIORITY, lbutlast, GetResourceString(L"LOCALIZED_ALTERNATE_BUTLAST") },
		{L"buttoncreate", 8, 8, 8, PREFIX_PRIORITY, lbuttoncreate, GetResourceString(L"LOCALIZED_ALTERNATE_BUTTONCREATE") },
		{L"buttondelete", 1, 1, 1, PREFIX_PRIORITY, lbuttondelete, GetResourceString(L"LOCALIZED_ALTERNATE_BUTTONDELETE") },
		{L"buttonenable", 2, 2, 2, PREFIX_PRIORITY, lbuttonenable, GetResourceString(L"LOCALIZED_ALTERNATE_BUTTONENABLE") },
		{L"buttonupdate", 2, 2, 2, PREFIX_PRIORITY, lbuttonupdate, GetResourceString(L"LOCALIZED_ALTERNATE_BUTTONUPDATE") },
		{L"buttonp", 0, 0, 0, PREFIX_PRIORITY, lbuttonp, GetResourceString(L"LOCALIZED_ALTERNATE_BUTTONP") },
		{L"button?", 0, 0, 0, PREFIX_PRIORITY, lbuttonp, GetResourceString(L"LOCALIZED_ALTERNATE_BUTTON_") },
		{L"bye", 0, 0, 0, PREFIX_PRIORITY, lbye, GetResourceString(L"LOCALIZED_ALTERNATE_BYE") },
		{L"catch", 2, 2, 2, MACRO_PRIORITY, lcatch, GetResourceString(L"LOCALIZED_ALTERNATE_CATCH") },
		{L"char", 1, 1, 1, PREFIX_PRIORITY, lchar, GetResourceString(L"LOCALIZED_ALTERNATE_CHAR") },
		{L"chdir", 1, 1, 1, PREFIX_PRIORITY, lchdir, GetResourceString(L"LOCALIZED_ALTERNATE_CHDIR") },
		{L"checkboxcreate", 8, 8, 8, PREFIX_PRIORITY, lcheckboxcreate, GetResourceString(L"LOCALIZED_ALTERNATE_CHECKBOXCREATE") },
		{L"checkboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcheckboxdelete, GetResourceString(L"LOCALIZED_ALTERNATE_CHECKBOXDELETE") },
		{L"checkboxenable", 2, 2, 2, PREFIX_PRIORITY, lcheckboxenable, GetResourceString(L"LOCALIZED_ALTERNATE_CHECKBOXENABLE") },
		{L"checkboxget", 1, 1, 1, PREFIX_PRIORITY, lcheckboxget, GetResourceString(L"LOCALIZED_ALTERNATE_CHECKBOXGET") },
		{L"checkboxset", 2, 2, 2, PREFIX_PRIORITY, lcheckboxset, GetResourceString(L"LOCALIZED_ALTERNATE_CHECKBOXSET") },
		{L"clean", 0, 0, 0, PREFIX_PRIORITY, lclean, GetResourceString(L"LOCALIZED_ALTERNATE_CLEAN") },
		{L"clearpalette", 0, 0, 0, PREFIX_PRIORITY, lclearpalette, GetResourceString(L"LOCALIZED_ALTERNATE_CLEARPALETTE") },
		{L"clearscreen", 0, 0, 0, PREFIX_PRIORITY, lclearscreen, GetResourceString(L"LOCALIZED_ALTERNATE_CLEARSCREEN") },
		{L"cleartext", 0, 0, 0, PREFIX_PRIORITY, lcleartext, GetResourceString(L"LOCALIZED_ALTERNATE_CLEARTEXT") },
	#if !defined WX_PURE
		{L"cleartimer", 1, 1, 1, PREFIX_PRIORITY, lcleartimer, GetResourceString(L"LOCALIZED_ALTERNATE_CLEARTIMER") },
	#endif
		{L"close", 1, 1, 1, PREFIX_PRIORITY, lclose, GetResourceString(L"LOCALIZED_ALTERNATE_CLOSE") },
		{L"closeall", 0, 0, 0, PREFIX_PRIORITY, lcloseall, GetResourceString(L"LOCALIZED_ALTERNATE_CLOSEALL") },
		{L"co", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue, GetResourceString(L"LOCALIZED_ALTERNATE_CO") },
		{L"comboboxaddstring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxaddstring, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXADDSTRING") },
		{L"comboboxcreate", 6, 6, 6, PREFIX_PRIORITY, lcomboboxcreate, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXCREATE") },
		{L"comboboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcomboboxdelete, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXDELETE") },
		{L"comboboxenable", 2, 2, 2, PREFIX_PRIORITY, lcomboboxenable, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXENABLE") },
		{L"comboboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxdeletestring, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING") },
		{L"comboboxgettext", 1, 1, 1, PREFIX_PRIORITY, lcomboboxgettext, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXGETTEXT") },
		{L"comboboxsettext", 2, 2, 2, PREFIX_PRIORITY, lcomboboxsettext, GetResourceString(L"LOCALIZED_ALTERNATE_COMBOBOXSETTEXT") },
		{L"contents", 0, 0, 0, PREFIX_PRIORITY, lcontents, GetResourceString(L"LOCALIZED_ALTERNATE_CONTENTS") },
		{L"continue", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue, GetResourceString(L"LOCALIZED_ALTERNATE_CONTINUE") },
		{L"copydef", 2, 2, 2, PREFIX_PRIORITY, lcopydef, GetResourceString(L"LOCALIZED_ALTERNATE_COPYDEF") },
		{L"cos", 1, 1, 1, PREFIX_PRIORITY, lcos, GetResourceString(L"LOCALIZED_ALTERNATE_COS") },
		{L"count", 1, 1, 1, PREFIX_PRIORITY, lcount, GetResourceString(L"LOCALIZED_ALTERNATE_COUNT") },
		{L"cs", 0, 0, 0, PREFIX_PRIORITY, lclearscreen, GetResourceString(L"LOCALIZED_ALTERNATE_CS") },
		{L"ct", 0, 0, 0, PREFIX_PRIORITY, lcleartext, GetResourceString(L"LOCALIZED_ALTERNATE_CT") },
		{L"cursor", 0, 0, 0, PREFIX_PRIORITY, lcursor, GetResourceString(L"LOCALIZED_ALTERNATE_CURSOR") },
		{L"debugwindows", 0, 0, 1, PREFIX_PRIORITY, ldebugwindows, GetResourceString(L"LOCALIZED_ALTERNATE_DEBUGWINDOWS") },
		{L"define", 2, 2, 2, PREFIX_PRIORITY, ldefine, GetResourceString(L"LOCALIZED_ALTERNATE_DEFINE") },
		{L"definedp", 1, 1, 1, PREFIX_PRIORITY, ldefinedp, GetResourceString(L"LOCALIZED_ALTERNATE_DEFINEDP") },
		{L"defined?", 1, 1, 1, PREFIX_PRIORITY, ldefinedp, GetResourceString(L"LOCALIZED_ALTERNATE_DEFINED_") },
		{L"dialogcreate", 8, 8, 8, PREFIX_PRIORITY, ldialogcreate, GetResourceString(L"LOCALIZED_ALTERNATE_DIALOGCREATE") },
		{L"dialogenable", 2, 2, 2, PREFIX_PRIORITY, ldialogenable, GetResourceString(L"LOCALIZED_ALTERNATE_DIALOGENABLE") },
		{L"dialogdelete", 1, 1, 1, PREFIX_PRIORITY, ldialogdelete, GetResourceString(L"LOCALIZED_ALTERNATE_DIALOGDELETE") },
		{L"dialogfileopen", 1, 1, 1, PREFIX_PRIORITY, ldialogfileopen, GetResourceString(L"LOCALIZED_ALTERNATE_DIALOGFILEOPEN") },
		{L"dialogfilesave", 1, 1, 1, PREFIX_PRIORITY, ldialogfilesave, GetResourceString(L"LOCALIZED_ALTERNATE_DIALOGFILESAVE") },
		{L"difference", 2, 2, 2, PREFIX_PRIORITY, lsub, GetResourceString(L"LOCALIZED_ALTERNATE_DIFFERENCE") },
		{L"directories", 0, 0, 0, PREFIX_PRIORITY, ldirectories, GetResourceString(L"LOCALIZED_ALTERNATE_DIRECTORIES") },
	#if !defined WX_PURE
		{L"dllcall", 1, 1, 2, PREFIX_PRIORITY, ldllcall, GetResourceString(L"LOCALIZED_ALTERNATE_DLLCALL") },
		{L"dllfree", 0, 0, 1, PREFIX_PRIORITY, ldllfree, GetResourceString(L"LOCALIZED_ALTERNATE_DLLFREE") },
		{L"dllload", 1, 1, 1, PREFIX_PRIORITY, ldllload, GetResourceString(L"LOCALIZED_ALTERNATE_DLLLOAD") },
	#endif
		{L"down", 1, 1, 1, PREFIX_PRIORITY, ldownpitch, GetResourceString(L"LOCALIZED_ALTERNATE_DOWN") },
		{L"downpitch", 1, 1, 1, PREFIX_PRIORITY, ldownpitch, GetResourceString(L"LOCALIZED_ALTERNATE_DOWNPITCH") },
		{L"dribble", 1, 1, 1, PREFIX_PRIORITY, ldribble, GetResourceString(L"LOCALIZED_ALTERNATE_DRIBBLE") },
		{L"ed", 1, 1, 1, PREFIX_PRIORITY, ledit, GetResourceString(L"LOCALIZED_ALTERNATE_ED") },
		{L"edit", 1, 1, 1, PREFIX_PRIORITY, ledit, GetResourceString(L"LOCALIZED_ALTERNATE_EDIT") },
		{L"ellipsearc", 4, 4, 4, PREFIX_PRIORITY, lellipsearc, GetResourceString(L"LOCALIZED_ALTERNATE_ELLIPSEARC") },
		{L"emptyp", 1, 1, 1, PREFIX_PRIORITY, lemptyp, GetResourceString(L"LOCALIZED_ALTERNATE_EMPTYP") },
		{L"empty?", 1, 1, 1, PREFIX_PRIORITY, lemptyp, GetResourceString(L"LOCALIZED_ALTERNATE_EMPTY_") },
		{L"eofp", 0, 0, 0, PREFIX_PRIORITY, leofp, GetResourceString(L"LOCALIZED_ALTERNATE_EOFP") },
		{L"eof?", 0, 0, 0, PREFIX_PRIORITY, leofp, GetResourceString(L"LOCALIZED_ALTERNATE_EOF_") },
		{L"equalp", 2, 2, 2, PREFIX_PRIORITY, lequalp, GetResourceString(L"LOCALIZED_ALTERNATE_EQUALP") },
		{L"equal?", 2, 2, 2, PREFIX_PRIORITY, lequalp, GetResourceString(L"LOCALIZED_ALTERNATE_EQUAL_") },
		{L"er", 1, 1, 1, PREFIX_PRIORITY, lerase, GetResourceString(L"LOCALIZED_ALTERNATE_ER") },
		{L"erase", 1, 1, 1, PREFIX_PRIORITY, lerase, GetResourceString(L"LOCALIZED_ALTERNATE_ERASE") },
		{L"erasefile", 1, 1, 1, PREFIX_PRIORITY, lerasefile, GetResourceString(L"LOCALIZED_ALTERNATE_ERASEFILE") },
		{L"erf", 1, 1, 1, PREFIX_PRIORITY, lerasefile, GetResourceString(L"LOCALIZED_ALTERNATE_ERF") },
		{L"error", 0, 0, 0, PREFIX_PRIORITY, lerror, GetResourceString(L"LOCALIZED_ALTERNATE_ERROR") },
		{L"eventcheck", 0, 0, 0, PREFIX_PRIORITY, leventcheck, GetResourceString(L"LOCALIZED_ALTERNATE_EVENTCHECK") },
		{L"exp", 1, 1, 1, PREFIX_PRIORITY, lexp, GetResourceString(L"LOCALIZED_ALTERNATE_EXP") },
		{L"fd", 1, 1, 1, PREFIX_PRIORITY, lforward, GetResourceString(L"LOCALIZED_ALTERNATE_FD") },
		{L"fence", 0, 0, 0, PREFIX_PRIORITY, lfence, GetResourceString(L"LOCALIZED_ALTERNATE_FENCE") },
		{L"fill", 0, 0, 1, PREFIX_PRIORITY, lfill, GetResourceString(L"LOCALIZED_ALTERNATE_FILL") },
		{L"files", 0, 0, 0, PREFIX_PRIORITY, lfiles, GetResourceString(L"LOCALIZED_ALTERNATE_FILES") },
		{L"first", 1, 1, 1, PREFIX_PRIORITY, lfirst, GetResourceString(L"LOCALIZED_ALTERNATE_FIRST") },
		{L"firsts", 1, 1, 1, PREFIX_PRIORITY, lfirsts, GetResourceString(L"LOCALIZED_ALTERNATE_FIRSTS") },
		{L"floodcolor", 0, 0, 0, PREFIX_PRIORITY, lfloodcolor, GetResourceString(L"LOCALIZED_ALTERNATE_FLOODCOLOR") },
		{L"fontfacenames", 0, 0, 0, PREFIX_PRIORITY, lfontfacenames, GetResourceString(L"LOCALIZED_ALTERNATE_FONTFACENAMES") },
		{L"forever", 1, 1, 1, MACRO_PRIORITY, lforever, GetResourceString(L"LOCALIZED_ALTERNATE_FOREVER") },
		{L"form", 3, 3, 3, PREFIX_PRIORITY, lform, GetResourceString(L"LOCALIZED_ALTERNATE_FORM") },
		{L"forward", 1, 1, 1, PREFIX_PRIORITY, lforward, GetResourceString(L"LOCALIZED_ALTERNATE_FORWARD") },
		{L"fput", 2, 2, 2, PREFIX_PRIORITY, lfput, GetResourceString(L"LOCALIZED_ALTERNATE_FPUT") },
		{L"fs", 0, 0, 0, PREFIX_PRIORITY, lfullscreen, GetResourceString(L"LOCALIZED_ALTERNATE_FS") },
		{L"fullscreen", 0, 0, 0, PREFIX_PRIORITY, lfullscreen, GetResourceString(L"LOCALIZED_ALTERNATE_FULLSCREEN") },
		{L"fulltext", 1, 1, 1, PREFIX_PRIORITY, lfulltext, GetResourceString(L"LOCALIZED_ALTERNATE_FULLTEXT") },
		{L"getfocus", 0, 0, 0, PREFIX_PRIORITY, lgetfocus, GetResourceString(L"LOCALIZED_ALTERNATE_GETFOCUS") },
		// {L"goto", 1, 1, 1, MACRO_PRIORITY, lgoto, GetResourceString(L"LOCALIZED_ALTERNATE_GOTO") },
		{L"gifload", 1, 1, 1, PREFIX_PRIORITY, lgifload, GetResourceString(L"LOCALIZED_ALTERNATE_GIFLOAD") },
		{L"gifsize", 1, 1, 1, PREFIX_PRIORITY, lgifsize, GetResourceString(L"LOCALIZED_ALTERNATE_GIFSIZE") },
		{L"gifsave", 1, 1, 6, PREFIX_PRIORITY, lgifsave, GetResourceString(L"LOCALIZED_ALTERNATE_GIFSAVE") },
		{L"gprop", 2, 2, 2, PREFIX_PRIORITY, lgprop, GetResourceString(L"LOCALIZED_ALTERNATE_GPROP") },
		{L"greater?", 2, 2, 2, PREFIX_PRIORITY, lgreaterp, GetResourceString(L"LOCALIZED_ALTERNATE_GREATER_") },
		{L"greaterequal?", 2, 2, 2, PREFIX_PRIORITY, lgreaterequalp, GetResourceString(L"LOCALIZED_ALTERNATE_GREATEREQUAL_") },
		{L"greaterequalp", 2, 2, 2, PREFIX_PRIORITY, lgreaterequalp, GetResourceString(L"LOCALIZED_ALTERNATE_GREATEREQUALP") },
		{L"greaterp", 2, 2, 2, PREFIX_PRIORITY, lgreaterp, GetResourceString(L"LOCALIZED_ALTERNATE_GREATERP") },
		{L"groupboxcreate", 6, 6, 6, PREFIX_PRIORITY, lgroupboxcreate, GetResourceString(L"LOCALIZED_ALTERNATE_GROUPBOXCREATE") },
		{L"groupboxdelete", 1, 1, 1, PREFIX_PRIORITY, lgroupboxdelete, GetResourceString(L"LOCALIZED_ALTERNATE_GROUPBOXDELETE") },
		{L"halt", 0, 0, 0, PREFIX_PRIORITY, lhalt, GetResourceString(L"LOCALIZED_ALTERNATE_HALT") },
		{L"hasownpen?", 0, 0, 0, PREFIX_PRIORITY, lhasownpenp, GetResourceString(L"LOCALIZED_ALTERNATE_HASOWNPEN_") },
		{L"hasownpenp", 0, 0, 0, PREFIX_PRIORITY, lhasownpenp, GetResourceString(L"LOCALIZED_ALTERNATE_HASOWNPENP") },
		{L"heading", 0, 0, 0, PREFIX_PRIORITY, lheading, GetResourceString(L"LOCALIZED_ALTERNATE_HEADING") },
		{L"help", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lhelp, GetResourceString(L"LOCALIZED_ALTERNATE_HELP") },
		{L"hideturtle", 0, 0, 0, PREFIX_PRIORITY, lhideturtle, GetResourceString(L"LOCALIZED_ALTERNATE_HIDETURTLE") },
		{L"home", 0, 0, 0, PREFIX_PRIORITY, lhome, GetResourceString(L"LOCALIZED_ALTERNATE_HOME") },
		{L"ht", 0, 0, 0, PREFIX_PRIORITY, lhideturtle, GetResourceString(L"LOCALIZED_ALTERNATE_HT") },
		{L"if", 2, 2, 3, MACRO_PRIORITY, lif, GetResourceString(L"LOCALIZED_ALTERNATE_IF") },
		{L"ifelse", 3, 3, 3, MACRO_PRIORITY, lifelse, GetResourceString(L"LOCALIZED_ALTERNATE_IFELSE") },
		{L"iff", 1, 1, 1, MACRO_PRIORITY, liffalse, GetResourceString(L"LOCALIZED_ALTERNATE_IFF") },
		{L"iffalse", 1, 1, 1, MACRO_PRIORITY, liffalse, GetResourceString(L"LOCALIZED_ALTERNATE_IFFALSE") },
		{L"ift", 1, 1, 1, MACRO_PRIORITY, liftrue, GetResourceString(L"LOCALIZED_ALTERNATE_IFT") },
		{L"iftrue", 1, 1, 1, MACRO_PRIORITY, liftrue, GetResourceString(L"LOCALIZED_ALTERNATE_IFTRUE") },
		{L"ingameport", 1, 1, 2, PREFIX_PRIORITY, lingameport, GetResourceString(L"LOCALIZED_ALTERNATE_INGAMEPORT") },
		{L"inport", 1, 1, 1, PREFIX_PRIORITY, linport, GetResourceString(L"LOCALIZED_ALTERNATE_INPORT") },
		{L"inportb", 1, 1, 1, PREFIX_PRIORITY, linportb, GetResourceString(L"LOCALIZED_ALTERNATE_INPORTB") },
		{L"int", 1, 1, 1, PREFIX_PRIORITY, linteg, GetResourceString(L"LOCALIZED_ALTERNATE_INT") },
		{L"item", 2, 2, 2, PREFIX_PRIORITY, litem, GetResourceString(L"LOCALIZED_ALTERNATE_ITEM") },
		{L"keyboardoff", 0, 0, 0, PREFIX_PRIORITY, lkeyboardoff, GetResourceString(L"LOCALIZED_ALTERNATE_KEYBOARDOFF") },
		{L"keyboardon", 1, 1, 2, PREFIX_PRIORITY, lkeyboardon, GetResourceString(L"LOCALIZED_ALTERNATE_KEYBOARDON") },
		{L"keyboardvalue", 0, 0, 0, PREFIX_PRIORITY, lkeyboardvalue, GetResourceString(L"LOCALIZED_ALTERNATE_KEYBOARDVALUE") },
		{L"keyp", 0, 0, 0, PREFIX_PRIORITY, lkeyp, GetResourceString(L"LOCALIZED_ALTERNATE_KEYP") },
		{L"key?", 0, 0, 0, PREFIX_PRIORITY, lkeyp, GetResourceString(L"LOCALIZED_ALTERNATE_KEY_") },
		{L"label", 1, 1, 1, PREFIX_PRIORITY, llabel, GetResourceString(L"LOCALIZED_ALTERNATE_LABEL") },
		{L"labelfont", 0, 0, 0, PREFIX_PRIORITY, llabelfont, GetResourceString(L"LOCALIZED_ALTERNATE_LABELFONT") },
		{L"labelsize", 1, 1, 1, PREFIX_PRIORITY, llabelsize, GetResourceString(L"LOCALIZED_ALTERNATE_LABELSIZE") },
		{L"last", 1, 1, 1, PREFIX_PRIORITY, llast, GetResourceString(L"LOCALIZED_ALTERNATE_LAST") },
		{L"left", 1, 1, 1, PREFIX_PRIORITY, lleft, GetResourceString(L"LOCALIZED_ALTERNATE_LEFT") },
		{L"leftroll", 1, 1, 1, PREFIX_PRIORITY, lleftroll, GetResourceString(L"LOCALIZED_ALTERNATE_LEFTROLL") },
		{L"less?", 2, 2, 2, PREFIX_PRIORITY, llessp, GetResourceString(L"LOCALIZED_ALTERNATE_LESS_") },
		{L"lessequal?", 2, 2, 2, PREFIX_PRIORITY, llessequalp, GetResourceString(L"LOCALIZED_ALTERNATE_LESSEQUAL_") },
		{L"lessequalp", 2, 2, 2, PREFIX_PRIORITY, llessequalp, GetResourceString(L"LOCALIZED_ALTERNATE_LESSEQUALP") },
		{L"lessp", 2, 2, 2, PREFIX_PRIORITY, llessp, GetResourceString(L"LOCALIZED_ALTERNATE_LESSP") },
		{L"light", 0, 0, 0, PREFIX_PRIORITY, llight, GetResourceString(L"LOCALIZED_ALTERNATE_LIGHT") },
		{L"list", 0, 2, -1, PREFIX_PRIORITY, llist, GetResourceString(L"LOCALIZED_ALTERNATE_LIST") },
		{L"listboxaddstring", 2, 2, 2, PREFIX_PRIORITY, llistboxaddstring, GetResourceString(L"LOCALIZED_ALTERNATE_LISTBOXADDSTRING") },
		{L"listboxcreate", 6, 6, 6, PREFIX_PRIORITY, llistboxcreate, GetResourceString(L"LOCALIZED_ALTERNATE_LISTBOXCREATE") },
		{L"listboxenable", 2, 2, 2, PREFIX_PRIORITY, llistboxenable, GetResourceString(L"LOCALIZED_ALTERNATE_LISTBOXENABLE") },
		{L"listboxdelete", 1, 1, 1, PREFIX_PRIORITY, llistboxdelete, GetResourceString(L"LOCALIZED_ALTERNATE_LISTBOXDELETE") },
		{L"listboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, llistboxdeletestring, GetResourceString(L"LOCALIZED_ALTERNATE_LISTBOXDELETESTRING") },
		{L"listboxgetselect", 1, 1, 1, PREFIX_PRIORITY, llistboxgetselect, GetResourceString(L"LOCALIZED_ALTERNATE_LISTBOXGETSELECT") },
		{L"listp", 1, 1, 1, PREFIX_PRIORITY, llistp, GetResourceString(L"LOCALIZED_ALTERNATE_LISTP") },
		{L"list?", 1, 1, 1, PREFIX_PRIORITY, llistp, GetResourceString(L"LOCALIZED_ALTERNATE_LIST_") },
		{L"ln", 1, 1, 1, PREFIX_PRIORITY, lln, GetResourceString(L"LOCALIZED_ALTERNATE_LN") },
		{L"load", 1, 1, 1, PREFIX_PRIORITY, lload, GetResourceString(L"LOCALIZED_ALTERNATE_LOAD") },
		{L"local", 1, 1, -1, PREFIX_PRIORITY, llocal, GetResourceString(L"LOCALIZED_ALTERNATE_LOCAL") },
		{L"log10", 1, 1, 1, PREFIX_PRIORITY, llog10, GetResourceString(L"LOCALIZED_ALTERNATE_LOG10") },
		{L"logoversion", 0, 0, 0, PREFIX_PRIORITY, llogoversion, GetResourceString(L"LOCALIZED_ALTERNATE_LOGOVERSION") },
		{L"lowercase", 1, 1, 1, PREFIX_PRIORITY, llowercase, GetResourceString(L"LOCALIZED_ALTERNATE_LOWERCASE") },
		{L"lput", 2, 2, 2, PREFIX_PRIORITY, llput, GetResourceString(L"LOCALIZED_ALTERNATE_LPUT") },
		{L"lr", 1, 1, 1, PREFIX_PRIORITY, lleftroll, GetResourceString(L"LOCALIZED_ALTERNATE_LR") },
		{L"lshift", 2, 2, 2, PREFIX_PRIORITY, llshift, GetResourceString(L"LOCALIZED_ALTERNATE_LSHIFT") },
		{L"lt", 1, 1, 1, PREFIX_PRIORITY, lleft, GetResourceString(L"LOCALIZED_ALTERNATE_LT") },
		{L"machine", 0, 0, 0, PREFIX_PRIORITY, lmachine, GetResourceString(L"LOCALIZED_ALTERNATE_MACHINE") },
		{L"macrop", 1, 1, 1, PREFIX_PRIORITY, lmacrop, GetResourceString(L"LOCALIZED_ALTERNATE_MACROP") },
		{L"macro?", 1, 1, 1, PREFIX_PRIORITY, lmacrop, GetResourceString(L"LOCALIZED_ALTERNATE_MACRO_") },
		{L"make", 2, 2, 2, PREFIX_PRIORITY, lmake, GetResourceString(L"LOCALIZED_ALTERNATE_MAKE") },
	#if !defined WX_PURE
		{L"mci", 1, 1, 2, PREFIX_PRIORITY, lmci, GetResourceString(L"LOCALIZED_ALTERNATE_MCI") },
	#endif
		{L"member", 2, 2, 2, PREFIX_PRIORITY, lmember, GetResourceString(L"LOCALIZED_ALTERNATE_MEMBER") },
		{L"memberp", 2, 2, 2, PREFIX_PRIORITY, lmemberp, GetResourceString(L"LOCALIZED_ALTERNATE_MEMBERP") },
		{L"member?", 2, 2, 2, PREFIX_PRIORITY, lmemberp, GetResourceString(L"LOCALIZED_ALTERNATE_MEMBER_") },
		{L"messagebox", 2, 2, 2, PREFIX_PRIORITY, lmessagebox, GetResourceString(L"LOCALIZED_ALTERNATE_MESSAGEBOX") },
	#if !defined WX_PURE
		{L"midiclose", 0, 0, 0, PREFIX_PRIORITY, lmidiclose, GetResourceString(L"LOCALIZED_ALTERNATE_MIDICLOSE") },
		{L"midimessage", 1, 1, 1, PREFIX_PRIORITY, lmidimessage, GetResourceString(L"LOCALIZED_ALTERNATE_MIDIMESSAGE") },
		{L"midiopen", 0, 0, 1, PREFIX_PRIORITY, lmidiopen, GetResourceString(L"LOCALIZED_ALTERNATE_MIDIOPEN") },
	#endif
		{L"minus", 1, 1, 1, PREFIX_PRIORITY, lsub, GetResourceString(L"LOCALIZED_ALTERNATE_MINUS") },
		{L"mkdir", 1, 1, 1, PREFIX_PRIORITY, lmkdir, GetResourceString(L"LOCALIZED_ALTERNATE_MKDIR") },
		{L"modulo", 2, 2, 2, PREFIX_PRIORITY, lmodulo, GetResourceString(L"LOCALIZED_ALTERNATE_MODULO") },
		{L"mouseoff", 0, 0, 0, PREFIX_PRIORITY, lmouseoff, GetResourceString(L"LOCALIZED_ALTERNATE_MOUSEOFF") },
		{L"mouseon", 5, 5, 5, PREFIX_PRIORITY, lmouseon, GetResourceString(L"LOCALIZED_ALTERNATE_MOUSEON") },
		{L"mousepos", 0, 0, 0, PREFIX_PRIORITY, lmousepos, GetResourceString(L"LOCALIZED_ALTERNATE_MOUSEPOS") },
		{L"namep", 1, 1, 1, PREFIX_PRIORITY, lnamep, GetResourceString(L"LOCALIZED_ALTERNATE_NAMEP") },
		{L"name?", 1, 1, 1, PREFIX_PRIORITY, lnamep, GetResourceString(L"LOCALIZED_ALTERNATE_NAME_") },
		{L"names", 0, 0, 0, PREFIX_PRIORITY, lnames, GetResourceString(L"LOCALIZED_ALTERNATE_NAMES") },
	#if !defined WX_PURE
		{L"netacceptoff", 0, 0, 0, PREFIX_PRIORITY, lnetacceptoff, GetResourceString(L"LOCALIZED_ALTERNATE_NETACCEPTOFF") },
		{L"netaccepton", 3, 3, 3, PREFIX_PRIORITY, lnetaccepton, GetResourceString(L"LOCALIZED_ALTERNATE_NETACCEPTON") },
		{L"netacceptreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetacceptreceivevalue, GetResourceString(L"LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE") },
		{L"netacceptsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetacceptsendvalue, GetResourceString(L"LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE") },
		{L"netconnectoff", 0, 0, 0, PREFIX_PRIORITY, lnetconnectoff, GetResourceString(L"LOCALIZED_ALTERNATE_NETCONNECTOFF") },
		{L"netconnecton", 4, 4, 4, PREFIX_PRIORITY, lnetconnecton, GetResourceString(L"LOCALIZED_ALTERNATE_NETCONNECTON") },
		{L"netconnectreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetconnectreceivevalue, GetResourceString(L"LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE") },
		{L"netconnectsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetconnectsendvalue, GetResourceString(L"LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE") },
		{L"netshutdown", 0, 0, 0, PREFIX_PRIORITY, lnetshutdown, GetResourceString(L"LOCALIZED_ALTERNATE_NETSHUTDOWN") },
		{L"netstartup", 0, 0, 1, PREFIX_PRIORITY, lnetstartup, GetResourceString(L"LOCALIZED_ALTERNATE_NETSTARTUP") },
	#endif // WX_PURE
		{L"nobitmapturtle", 0, 0, 0, PREFIX_PRIORITY, lnobitmapturtle, GetResourceString(L"LOCALIZED_ALTERNATE_NOBITMAPTURTLE") },
		{L"nodes", 0, 0, 0, PREFIX_PRIORITY, lnodes, GetResourceString(L"LOCALIZED_ALTERNATE_NODES") },
		{L"nodribble", 0, 0, 0, PREFIX_PRIORITY, lnodribble, GetResourceString(L"LOCALIZED_ALTERNATE_NODRIBBLE") },
		{L"nostatus", 0, 0, 0, PREFIX_PRIORITY, lnostatus, GetResourceString(L"LOCALIZED_ALTERNATE_NOSTATUS") },
		{L"not", 1, 1, 1, PREFIX_PRIORITY, lnot, GetResourceString(L"LOCALIZED_ALTERNATE_NOT") },
		{L"notequal?", 2, 2, 2, PREFIX_PRIORITY, lnotequalp, GetResourceString(L"LOCALIZED_ALTERNATE_NOTEQUAL_") },
		{L"notequalp", 2, 2, 2, PREFIX_PRIORITY, lnotequalp, GetResourceString(L"LOCALIZED_ALTERNATE_NOTEQUALP") },
		{L"noyield", 0, 0, 0, PREFIX_PRIORITY, lnoyield, GetResourceString(L"LOCALIZED_ALTERNATE_NOYIELD") },
		{L"numberp", 1, 1, 1, PREFIX_PRIORITY, lnumberp, GetResourceString(L"LOCALIZED_ALTERNATE_NUMBERP") },
		{L"number?", 1, 1, 1, PREFIX_PRIORITY, lnumberp, GetResourceString(L"LOCALIZED_ALTERNATE_NUMBER_") },
		{L"op", 1, 1, 1, OUTPUT_PRIORITY, loutput, GetResourceString(L"LOCALIZED_ALTERNATE_OP") },
		{L"openappend", 1, 1, 2, PREFIX_PRIORITY, lopenappend, GetResourceString(L"LOCALIZED_ALTERNATE_OPENAPPEND") },
		{L"openread", 1, 1, 2, PREFIX_PRIORITY, lopenread, GetResourceString(L"LOCALIZED_ALTERNATE_OPENREAD") },
		{L"openupdate", 1, 1, 2, PREFIX_PRIORITY, lopenupdate, GetResourceString(L"LOCALIZED_ALTERNATE_OPENUPDATE") },
		{L"openwrite", 1, 1, 2, PREFIX_PRIORITY, lopenwrite, GetResourceString(L"LOCALIZED_ALTERNATE_OPENWRITE") },
		{L"or", 0, 2, -1, PREFIX_PRIORITY, lor, GetResourceString(L"LOCALIZED_ALTERNATE_OR") },
		{L"outport", 2, 2, 2, PREFIX_PRIORITY, loutport, GetResourceString(L"LOCALIZED_ALTERNATE_OUTPORT") },
		{L"outportb", 2, 2, 2, PREFIX_PRIORITY, loutportb, GetResourceString(L"LOCALIZED_ALTERNATE_OUTPORTB") },
		{L"output", 1, 1, 1, OUTPUT_PRIORITY, loutput, GetResourceString(L"LOCALIZED_ALTERNATE_OUTPUT") },
		{L"parse", 1, 1, 1, PREFIX_PRIORITY, lparse, GetResourceString(L"LOCALIZED_ALTERNATE_PARSE") },
		{L"pause", 0, 0, 0, PREFIX_PRIORITY, lpause, GetResourceString(L"LOCALIZED_ALTERNATE_PAUSE") },
		{L"pc", 0, 0, 0, PREFIX_PRIORITY, lpencolor, GetResourceString(L"LOCALIZED_ALTERNATE_PC") },
		{L"pd", 0, 0, 0, PREFIX_PRIORITY, lpendown, GetResourceString(L"LOCALIZED_ALTERNATE_PD") },
		{L"pe", 0, 0, 0, PREFIX_PRIORITY, lpenerase, GetResourceString(L"LOCALIZED_ALTERNATE_PE") },
		{L"pencolor", 0, 0, 0, PREFIX_PRIORITY, lpencolor, GetResourceString(L"LOCALIZED_ALTERNATE_PENCOLOR") },
		{L"pendown", 0, 0, 0, PREFIX_PRIORITY, lpendown, GetResourceString(L"LOCALIZED_ALTERNATE_PENDOWN") },
		{L"pendownp", 0, 0, 0, PREFIX_PRIORITY, lpendownp, GetResourceString(L"LOCALIZED_ALTERNATE_PENDOWNP") },
		{L"pendown?", 0, 0, 0, PREFIX_PRIORITY, lpendownp, GetResourceString(L"LOCALIZED_ALTERNATE_PENDOWN_") },
		{L"penerase", 0, 0, 0, PREFIX_PRIORITY, lpenerase, GetResourceString(L"LOCALIZED_ALTERNATE_PENERASE") },
		{L"penmode", 0, 0, 0, PREFIX_PRIORITY, lpenmode, GetResourceString(L"LOCALIZED_ALTERNATE_PENMODE") },
		{L"penpaint", 0, 0, 0, PREFIX_PRIORITY, lpenpaint, GetResourceString(L"LOCALIZED_ALTERNATE_PENPAINT") },
		{L"penpattern", 0, 0, 0, PREFIX_PRIORITY, lpenpattern, GetResourceString(L"LOCALIZED_ALTERNATE_PENPATTERN") },
		{L"penreverse", 0, 0, 0, PREFIX_PRIORITY, lpenreverse, GetResourceString(L"LOCALIZED_ALTERNATE_PENREVERSE") },
		{L"pensize", 0, 0, 0, PREFIX_PRIORITY, lpensize, GetResourceString(L"LOCALIZED_ALTERNATE_PENSIZE") },
		{L"penup", 0, 0, 0, PREFIX_PRIORITY, lpenup, GetResourceString(L"LOCALIZED_ALTERNATE_PENUP") },
		{L"perspective", 0, 0, 0, PREFIX_PRIORITY, lperspective, GetResourceString(L"LOCALIZED_ALTERNATE_PERSPECTIVE") },
		{L"pitch", 0, 0, 0, PREFIX_PRIORITY, lpitch, GetResourceString(L"LOCALIZED_ALTERNATE_PITCH") },
		{L"pixel", 0, 0, 0, PREFIX_PRIORITY, lpixel, GetResourceString(L"LOCALIZED_ALTERNATE_PIXEL") },
	#if !defined WX_PURE
		{L"playwave", 2, 2, 2, PREFIX_PRIORITY, lplaywave, GetResourceString(L"LOCALIZED_ALTERNATE_PLAYWAVE") },
	#endif
		{L"plist", 1, 1, 1, PREFIX_PRIORITY, lplist, GetResourceString(L"LOCALIZED_ALTERNATE_PLIST") },
		{L"plists", 0, 0, 0, PREFIX_PRIORITY, lplists, GetResourceString(L"LOCALIZED_ALTERNATE_PLISTS") },
		{L"po", 1, 1, 1, PREFIX_PRIORITY, lpo, GetResourceString(L"LOCALIZED_ALTERNATE_PO") },
		{L"popdir", 0, 0, 0, PREFIX_PRIORITY, lpopdir, GetResourceString(L"LOCALIZED_ALTERNATE_POPDIR") },
		{L"polystart", 0, 0, 0, PREFIX_PRIORITY, lpolystart, GetResourceString(L"LOCALIZED_ALTERNATE_POLYSTART") },
		{L"polyend", 0, 0, 0, PREFIX_PRIORITY, lpolyend, GetResourceString(L"LOCALIZED_ALTERNATE_POLYEND") },
		{L"polyview", 0, 0, 0, PREFIX_PRIORITY, lpolyview, GetResourceString(L"LOCALIZED_ALTERNATE_POLYVIEW") },
		{L"portclose", 0, 0, 0, PREFIX_PRIORITY, lportclose, GetResourceString(L"LOCALIZED_ALTERNATE_PORTCLOSE") },
		{L"portflush", 1, 1, 1, PREFIX_PRIORITY, lportflush, GetResourceString(L"LOCALIZED_ALTERNATE_PORTFLUSH") },
		{L"portmode", 1, 1, 1, PREFIX_PRIORITY, lportmode, GetResourceString(L"LOCALIZED_ALTERNATE_PORTMODE") },
		{L"portopen", 1, 1, 1, PREFIX_PRIORITY, lportopen, GetResourceString(L"LOCALIZED_ALTERNATE_PORTOPEN") },
		{L"portreadarray", 2, 2, 2, PREFIX_PRIORITY, lportreadarray, GetResourceString(L"LOCALIZED_ALTERNATE_PORTREADARRAY") },
		{L"portreadchar", 0, 0, 0, PREFIX_PRIORITY, lportreadchar, GetResourceString(L"LOCALIZED_ALTERNATE_PORTREADCHAR") },
		{L"portwritearray", 2, 2, 2, PREFIX_PRIORITY, lportwritearray, GetResourceString(L"LOCALIZED_ALTERNATE_PORTWRITEARRAY") },
		{L"portwritechar", 1, 1, 1, PREFIX_PRIORITY, lportwritechar, GetResourceString(L"LOCALIZED_ALTERNATE_PORTWRITECHAR") },
		{L"pos", 0, 0, 0, PREFIX_PRIORITY, lpos, GetResourceString(L"LOCALIZED_ALTERNATE_POS") },
		{L"posxyz", 0, 0, 0, PREFIX_PRIORITY, lposxyz, GetResourceString(L"LOCALIZED_ALTERNATE_POSXYZ") },
		{L"pot", 1, 1, 1, PREFIX_PRIORITY, lpot, GetResourceString(L"LOCALIZED_ALTERNATE_POT") },
		{L"power", 2, 2, 2, PREFIX_PRIORITY, lpower, GetResourceString(L"LOCALIZED_ALTERNATE_POWER") },
		{L"pprop", 3, 3, 3, PREFIX_PRIORITY, lpprop, GetResourceString(L"LOCALIZED_ALTERNATE_PPROP") },
		{L"ppt", 0, 0, 0, PREFIX_PRIORITY, lpenpaint, GetResourceString(L"LOCALIZED_ALTERNATE_PPT") },
		{L"pr", 0, 1, -1, PREFIX_PRIORITY, lprint, GetResourceString(L"LOCALIZED_ALTERNATE_PR") },
		{L"primitivep", 1, 1, 1, PREFIX_PRIORITY, lprimitivep, GetResourceString(L"LOCALIZED_ALTERNATE_PRIMITIVEP") },
		{L"primitive?", 1, 1, 1, PREFIX_PRIORITY, lprimitivep, GetResourceString(L"LOCALIZED_ALTERNATE_PRIMITIVE_") },
		{L"print", 0, 1, -1, PREFIX_PRIORITY, lprint, GetResourceString(L"LOCALIZED_ALTERNATE_PRINT") },
		{L"procedurep", 1, 1, 1, PREFIX_PRIORITY, lprocedurep, GetResourceString(L"LOCALIZED_ALTERNATE_PROCEDUREP") },
		{L"procedure?", 1, 1, 1, PREFIX_PRIORITY, lprocedurep, GetResourceString(L"LOCALIZED_ALTERNATE_PROCEDURE_") },
		{L"proplistp", 1, 1, 1, PREFIX_PRIORITY, lproplistp, GetResourceString(L"LOCALIZED_ALTERNATE_PROPLISTP") },
		{L"proplist?", 1, 1, 1, PREFIX_PRIORITY, lproplistp, GetResourceString(L"LOCALIZED_ALTERNATE_PROPLIST_") },
		{L"procedures", 0, 0, 0, PREFIX_PRIORITY, lprocedures, GetResourceString(L"LOCALIZED_ALTERNATE_PROCEDURES") },
		{L"product", 0, 2, -1, PREFIX_PRIORITY, lmul, GetResourceString(L"LOCALIZED_ALTERNATE_PRODUCT") },
		{L"pu", 0, 0, 0, PREFIX_PRIORITY, lpenup, GetResourceString(L"LOCALIZED_ALTERNATE_PU") },
		{L"px", 0, 0, 0, PREFIX_PRIORITY, lpenreverse, GetResourceString(L"LOCALIZED_ALTERNATE_PX") },
		{L"questionbox", 2, 2, 2, PREFIX_PRIORITY, lquestionbox, GetResourceString(L"LOCALIZED_ALTERNATE_QUESTIONBOX") },
		{L"quotient", 1, 2, 2, PREFIX_PRIORITY, ldivide, GetResourceString(L"LOCALIZED_ALTERNATE_QUOTIENT") },
		{L"radarccos", 1, 1, 1, PREFIX_PRIORITY, lradacos, GetResourceString(L"LOCALIZED_ALTERNATE_RADARCCOS") },
		{L"radarcsin", 1, 1, 1, PREFIX_PRIORITY, lradasin, GetResourceString(L"LOCALIZED_ALTERNATE_RADARCSIN") },
		{L"radarctan", 1, 1, 2, PREFIX_PRIORITY, lradatan, GetResourceString(L"LOCALIZED_ALTERNATE_RADARCTAN") },
		{L"radcos", 1, 1, 1, PREFIX_PRIORITY, lradcos, GetResourceString(L"LOCALIZED_ALTERNATE_RADCOS") },
		{L"radiobuttoncreate", 8, 8, 8, PREFIX_PRIORITY, lradiobuttoncreate, GetResourceString(L"LOCALIZED_ALTERNATE_RADIOBUTTONCREATE") },
		{L"radiobuttonenable", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonenable, GetResourceString(L"LOCALIZED_ALTERNATE_RADIOBUTTONENABLE") },
		{L"radiobuttondelete", 1, 1, 1, PREFIX_PRIORITY, lradiobuttondelete, GetResourceString(L"LOCALIZED_ALTERNATE_RADIOBUTTONDELETE") },
		{L"radiobuttonget", 1, 1, 1, PREFIX_PRIORITY, lradiobuttonget, GetResourceString(L"LOCALIZED_ALTERNATE_RADIOBUTTONGET") },
		{L"radiobuttonset", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonset, GetResourceString(L"LOCALIZED_ALTERNATE_RADIOBUTTONSET") },
		{L"radsin", 1, 1, 1, PREFIX_PRIORITY, lradsin, GetResourceString(L"LOCALIZED_ALTERNATE_RADSIN") },
		{L"radtan", 1, 1, 1, PREFIX_PRIORITY, lradtan, GetResourceString(L"LOCALIZED_ALTERNATE_RADTAN") },
		{L"random", 1, 1, 1, PREFIX_PRIORITY, lrandom, GetResourceString(L"LOCALIZED_ALTERNATE_RANDOM") },
		{L"rawascii", 1, 1, 1, PREFIX_PRIORITY, lrawascii, GetResourceString(L"LOCALIZED_ALTERNATE_RAWASCII") },
		{L"rc", 0, 0, 0, PREFIX_PRIORITY, lreadchar, GetResourceString(L"LOCALIZED_ALTERNATE_RC") },
		{L"rcs", 1, 1, 1, PREFIX_PRIORITY, lreadchars, GetResourceString(L"LOCALIZED_ALTERNATE_RCS") },
		{L"readchar", 0, 0, 0, PREFIX_PRIORITY, lreadchar, GetResourceString(L"LOCALIZED_ALTERNATE_READCHAR") },
		{L"readchars", 1, 1, 1, PREFIX_PRIORITY, lreadchars, GetResourceString(L"LOCALIZED_ALTERNATE_READCHARS") },
		{L"reader", 0, 0, 0, PREFIX_PRIORITY, lreader, GetResourceString(L"LOCALIZED_ALTERNATE_READER") },
		{L"readlist", 0, 0, 0, PREFIX_PRIORITY, lreadlist, GetResourceString(L"LOCALIZED_ALTERNATE_READLIST") },
		{L"readpos", 0, 0, 0, PREFIX_PRIORITY, lreadpos, GetResourceString(L"LOCALIZED_ALTERNATE_READPOS") },
		{L"readrawline", 0, 0, 0, PREFIX_PRIORITY, lreadrawline, GetResourceString(L"LOCALIZED_ALTERNATE_READRAWLINE") },
		{L"readword", 0, 0, 0, PREFIX_PRIORITY, lreadword, GetResourceString(L"LOCALIZED_ALTERNATE_READWORD") },
		{L"remainder", 2, 2, 2, PREFIX_PRIORITY, lremainder, GetResourceString(L"LOCALIZED_ALTERNATE_REMAINDER") },
		{L"remprop", 2, 2, 2, PREFIX_PRIORITY, lremprop, GetResourceString(L"LOCALIZED_ALTERNATE_REMPROP") },
		{L"repcount", 0, 0, 0, PREFIX_PRIORITY, lrepcount, GetResourceString(L"LOCALIZED_ALTERNATE_REPCOUNT") },
		{L"repeat", 2, 2, 2, MACRO_PRIORITY, lrepeat, GetResourceString(L"LOCALIZED_ALTERNATE_REPEAT") },
		{L"rerandom", 0, 0, 1, PREFIX_PRIORITY, lrerandom, GetResourceString(L"LOCALIZED_ALTERNATE_RERANDOM") },
		{L"right", 1, 1, 1, PREFIX_PRIORITY, lright, GetResourceString(L"LOCALIZED_ALTERNATE_RIGHT") },
		{L"rightroll", 1, 1, 1, PREFIX_PRIORITY, lrightroll, GetResourceString(L"LOCALIZED_ALTERNATE_RIGHTROLL") },
		{L"rl", 0, 0, 0, PREFIX_PRIORITY, lreadlist, GetResourceString(L"LOCALIZED_ALTERNATE_RL") },
		{L"rmdir", 1, 1, 1, PREFIX_PRIORITY, lrmdir, GetResourceString(L"LOCALIZED_ALTERNATE_RMDIR") },
		{L"roll", 0, 0, 0, PREFIX_PRIORITY, lroll, GetResourceString(L"LOCALIZED_ALTERNATE_ROLL") },
		{L"round", 1, 1, 1, PREFIX_PRIORITY, lround, GetResourceString(L"LOCALIZED_ALTERNATE_ROUND") },
		{L"rr", 1, 1, 1, PREFIX_PRIORITY, lrightroll, GetResourceString(L"LOCALIZED_ALTERNATE_RR") },
		{L"rt", 1, 1, 1, PREFIX_PRIORITY, lright, GetResourceString(L"LOCALIZED_ALTERNATE_RT") },
		{L"run", 1, 1, 1, MACRO_PRIORITY, lrun, GetResourceString(L"LOCALIZED_ALTERNATE_RUN") },
		{L"runparse", 1, 1, 1, PREFIX_PRIORITY, lrunparse, GetResourceString(L"LOCALIZED_ALTERNATE_RUNPARSE") },
		{L"runresult", 1, 1, 1, MACRO_PRIORITY, lrunresult, GetResourceString(L"LOCALIZED_ALTERNATE_RUNRESULT") },
		{L"rw", 0, 0, 0, PREFIX_PRIORITY, lreadword, GetResourceString(L"LOCALIZED_ALTERNATE_RW") },
		{L"save", 1, 1, 1, PREFIX_PRIORITY, lsave, GetResourceString(L"LOCALIZED_ALTERNATE_SAVE") },
		{L"screencolor", 0, 0, 0, PREFIX_PRIORITY, lscreencolor, GetResourceString(L"LOCALIZED_ALTERNATE_SCREENCOLOR") },
		{L"scrollbarcreate", 7, 7, 7, PREFIX_PRIORITY, lscrollbarcreate, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLBARCREATE") },
		{L"scrollbarenable", 2, 2, 2, PREFIX_PRIORITY, lscrollbarenable, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLBARENABLE") },
		{L"scrollbardelete", 1, 1, 1, PREFIX_PRIORITY, lscrollbardelete, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLBARDELETE") },
		{L"scrollbarget", 1, 1, 1, PREFIX_PRIORITY, lscrollbarget, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLBARGET") },
		{L"scrollbarset", 4, 4, 4, PREFIX_PRIORITY, lscrollbarset, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLBARSET") },
		{L"scrollx", 1, 1, 1, PREFIX_PRIORITY, lscrollx, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLX") },
		{L"scrolly", 1, 1, 1, PREFIX_PRIORITY, lscrolly, GetResourceString(L"LOCALIZED_ALTERNATE_SCROLLY") },
		{L"scrunch", 0, 0, 0, PREFIX_PRIORITY, lscrunch, GetResourceString(L"LOCALIZED_ALTERNATE_SCRUNCH") },
		{L"se", 0, 2, -1, PREFIX_PRIORITY, lsentence, GetResourceString(L"LOCALIZED_ALTERNATE_SE") },
		{L"selectbox", 2, 2, 2, PREFIX_PRIORITY, lselectbox, GetResourceString(L"LOCALIZED_ALTERNATE_SELECTBOX") },
		{L"sentence", 0, 2, -1, PREFIX_PRIORITY, lsentence, GetResourceString(L"LOCALIZED_ALTERNATE_SENTENCE") },
		{L"setactivearea", 1, 1, 1, PREFIX_PRIORITY, lsetactivearea, GetResourceString(L"LOCALIZED_ALTERNATE_SETACTIVEAREA") },
		{L"setbitindex", 1, 1, 1, PREFIX_PRIORITY, lsetbitindex, GetResourceString(L"LOCALIZED_ALTERNATE_SETBITINDEX") },
		{L"setbitmode", 1, 1, 1, PREFIX_PRIORITY, lsetbitmode, GetResourceString(L"LOCALIZED_ALTERNATE_SETBITMODE") },
		{L"setclip", 3, 3, 3, PREFIX_PRIORITY, lsetclip, GetResourceString(L"LOCALIZED_ALTERNATE_SETCLIP") },
		// {L"setcursor", 1, 1, 1, PREFIX_PRIORITY, lsetcursor, GetResourceString(L"LOCALIZED_ALTERNATE_SETCURSOR") },
		{L"setcursornowait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorarrow, GetResourceString(L"LOCALIZED_ALTERNATE_SETCURSORNOWAIT") },
		{L"setcursorwait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorwait, GetResourceString(L"LOCALIZED_ALTERNATE_SETCURSORWAIT") },
		{L"setfc", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor, GetResourceString(L"LOCALIZED_ALTERNATE_SETFC") },
		{L"setfloodcolor", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor, GetResourceString(L"LOCALIZED_ALTERNATE_SETFLOODCOLOR") },
		{L"setfocus", 1, 1, 1, PREFIX_PRIORITY, lsetfocus, GetResourceString(L"LOCALIZED_ALTERNATE_SETFOCUS") },
		{L"seth", 1, 1, 1, PREFIX_PRIORITY, lsetheading, GetResourceString(L"LOCALIZED_ALTERNATE_SETH") },
		{L"setheading", 1, 1, 1, PREFIX_PRIORITY, lsetheading, GetResourceString(L"LOCALIZED_ALTERNATE_SETHEADING") },
		{L"setitem", 3, 3, 3, PREFIX_PRIORITY, lsetitem, GetResourceString(L"LOCALIZED_ALTERNATE_SETITEM") },
		{L"setlabelfont", 1, 1, 1, PREFIX_PRIORITY, lsetlabelfont, GetResourceString(L"LOCALIZED_ALTERNATE_SETLABELFONT") },
		{L"setlight", 1, 1, 1, PREFIX_PRIORITY, lsetlight, GetResourceString(L"LOCALIZED_ALTERNATE_SETLIGHT") },
		{L"setmargins", 1, 1, 1, PREFIX_PRIORITY, lsetmargins, GetResourceString(L"LOCALIZED_ALTERNATE_SETMARGINS") },
		{L"setpc", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor, GetResourceString(L"LOCALIZED_ALTERNATE_SETPC") },
		{L"setpencolor", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor, GetResourceString(L"LOCALIZED_ALTERNATE_SETPENCOLOR") },
		{L"setpenpattern", 1, 1, 1, PREFIX_PRIORITY, lsetpenpattern, GetResourceString(L"LOCALIZED_ALTERNATE_SETPENPATTERN") },
		{L"setpensize", 1, 1, 1, PREFIX_PRIORITY, lsetpensize, GetResourceString(L"LOCALIZED_ALTERNATE_SETPENSIZE") },
		{L"setpitch", 1, 1, 1, PREFIX_PRIORITY, lsetpitch, GetResourceString(L"LOCALIZED_ALTERNATE_SETPITCH") },
		{L"setpixel", 1, 1, 1, PREFIX_PRIORITY, lsetpixel, GetResourceString(L"LOCALIZED_ALTERNATE_SETPIXEL") },
		{L"setpos", 1, 1, 1, PREFIX_PRIORITY, lsetpos, GetResourceString(L"LOCALIZED_ALTERNATE_SETPOS") },
		{L"setposxyz", 1, 1, 1, PREFIX_PRIORITY, lsetposxyz, GetResourceString(L"LOCALIZED_ALTERNATE_SETPOSXYZ") },
		{L"setread", 1, 1, 1, PREFIX_PRIORITY, lsetread, GetResourceString(L"LOCALIZED_ALTERNATE_SETREAD") },
		{L"setreadpos", 1, 1, 1, PREFIX_PRIORITY, lsetreadpos, GetResourceString(L"LOCALIZED_ALTERNATE_SETREADPOS") },
		{L"setroll", 1, 1, 1, PREFIX_PRIORITY, lsetroll, GetResourceString(L"LOCALIZED_ALTERNATE_SETROLL") },
		{L"setsc", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor, GetResourceString(L"LOCALIZED_ALTERNATE_SETSC") },
		{L"setscreencolor", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor, GetResourceString(L"LOCALIZED_ALTERNATE_SETSCREENCOLOR") },
		{L"setscrunch", 2, 2, 2, PREFIX_PRIORITY, lsetscrunch, GetResourceString(L"LOCALIZED_ALTERNATE_SETSCRUNCH") },
	#if !defined WX_PURE
		{L"settimer", 3, 3, 3, PREFIX_PRIORITY, lsettimer, GetResourceString(L"LOCALIZED_ALTERNATE_SETTIMER") },
	#endif
		{L"setturtle", 1, 1, 2, PREFIX_PRIORITY, lsetturtle, GetResourceString(L"LOCALIZED_ALTERNATE_SETTURTLE") },
		{L"setturtlemode", 1, 1, 1, PREFIX_PRIORITY, lsetturtlemode, GetResourceString(L"LOCALIZED_ALTERNATE_SETTURTLEMODE") },
		{L"setwrite", 1, 1, 1, PREFIX_PRIORITY, lsetwrite, GetResourceString(L"LOCALIZED_ALTERNATE_SETWRITE") },
		{L"setwritepos", 1, 1, 1, PREFIX_PRIORITY, lsetwritepos, GetResourceString(L"LOCALIZED_ALTERNATE_SETWRITEPOS") },
		{L"setx", 1, 1, 1, PREFIX_PRIORITY, lsetx, GetResourceString(L"LOCALIZED_ALTERNATE_SETX") },
		{L"setxy", 2, 2, 2, PREFIX_PRIORITY, lsetxy, GetResourceString(L"LOCALIZED_ALTERNATE_SETXY") },
		{L"setxyz", 3, 3, 3, PREFIX_PRIORITY, lsetxyz, GetResourceString(L"LOCALIZED_ALTERNATE_SETXYZ") },
		{L"sety", 1, 1, 1, PREFIX_PRIORITY, lsety, GetResourceString(L"LOCALIZED_ALTERNATE_SETY") },
		{L"setz", 1, 1, 1, PREFIX_PRIORITY, lsetz, GetResourceString(L"LOCALIZED_ALTERNATE_SETZ") },
		{L"shell", 1, 1, 2, PREFIX_PRIORITY, lshell, GetResourceString(L"LOCALIZED_ALTERNATE_SHELL") },
		{L"show", 0, 1, -1, PREFIX_PRIORITY, lshow, GetResourceString(L"LOCALIZED_ALTERNATE_SHOW") },
		{L"shownp", 0, 0, 0, PREFIX_PRIORITY, lshownp, GetResourceString(L"LOCALIZED_ALTERNATE_SHOWNP") },
		{L"shown?", 0, 0, 0, PREFIX_PRIORITY, lshownp, GetResourceString(L"LOCALIZED_ALTERNATE_SHOWN_") },
		{L"showturtle", 0, 0, 0, PREFIX_PRIORITY, lshowturtle, GetResourceString(L"LOCALIZED_ALTERNATE_SHOWTURTLE") },
		{L"sin", 1, 1, 1, PREFIX_PRIORITY, lsin, GetResourceString(L"LOCALIZED_ALTERNATE_SIN") },
	#if !defined WX_PURE
		{L"sound", 1, 1, 1, PREFIX_PRIORITY, lsound, GetResourceString(L"LOCALIZED_ALTERNATE_SOUND") },
	#endif
		{L"splitscreen", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen, GetResourceString(L"LOCALIZED_ALTERNATE_SPLITSCREEN") },
		{L"sqrt", 1, 1, 1, PREFIX_PRIORITY, lsqrt, GetResourceString(L"LOCALIZED_ALTERNATE_SQRT") },
		{L"ss", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen, GetResourceString(L"LOCALIZED_ALTERNATE_SS") },
		{L"st", 0, 0, 0, PREFIX_PRIORITY, lshowturtle, GetResourceString(L"LOCALIZED_ALTERNATE_ST") },
		{L"standout", 1, 1, 1, PREFIX_PRIORITY, lstandout, GetResourceString(L"LOCALIZED_ALTERNATE_STANDOUT") },
		{L"staticcreate", 7, 7, 7, PREFIX_PRIORITY, lstaticcreate, GetResourceString(L"LOCALIZED_ALTERNATE_STATICCREATE") },
		{L"staticdelete", 1, 1, 1, PREFIX_PRIORITY, lstaticdelete, GetResourceString(L"LOCALIZED_ALTERNATE_STATICDELETE") },
		{L"staticupdate", 2, 2, 2, PREFIX_PRIORITY, lstaticupdate, GetResourceString(L"LOCALIZED_ALTERNATE_STATICUPDATE") },
		{L"status", 0, 0, 0, PREFIX_PRIORITY, lstatus, GetResourceString(L"LOCALIZED_ALTERNATE_STATUS") },
		{L"step", 1, 1, 1, PREFIX_PRIORITY, lstep, GetResourceString(L"LOCALIZED_ALTERNATE_STEP") },
		{L"stepped", 0, 0, 0, PREFIX_PRIORITY, lstepped, GetResourceString(L"LOCALIZED_ALTERNATE_STEPPED") },
		{L"stop", 0, 0, 0, STOP_PRIORITY, lstop, GetResourceString(L"LOCALIZED_ALTERNATE_STOP") },
		{L"substringp", 2, 2, 2, PREFIX_PRIORITY, lsubstringp, GetResourceString(L"LOCALIZED_ALTERNATE_SUBSTRINGP") },
		{L"substring?", 2, 2, 2, PREFIX_PRIORITY, lsubstringp, GetResourceString(L"LOCALIZED_ALTERNATE_SUBSTRING_") },
		{L"sum", 0, 2, -1, PREFIX_PRIORITY, ladd, GetResourceString(L"LOCALIZED_ALTERNATE_SUM") },
		// {L"tag", 1, 1, 1, PREFIX_PRIORITY, ltag, GetResourceString(L"LOCALIZED_ALTERNATE_TAG") },
		{L"tan", 1, 1, 1, PREFIX_PRIORITY, ltan, GetResourceString(L"LOCALIZED_ALTERNATE_TAN") },
		{L"test", 1, 1, 1, PREFIX_PRIORITY, ltest, GetResourceString(L"LOCALIZED_ALTERNATE_TEST") },
		{L"text", 1, 1, 1, PREFIX_PRIORITY, ltext, GetResourceString(L"LOCALIZED_ALTERNATE_TEXT") },
		{L"textscreen", 0, 0, 0, PREFIX_PRIORITY, ltextscreen, GetResourceString(L"LOCALIZED_ALTERNATE_TEXTSCREEN") },
		{L"thing", 1, 1, 1, PREFIX_PRIORITY, lthing, GetResourceString(L"LOCALIZED_ALTERNATE_THING") },
		{L"throw", 1, 1, 3, PREFIX_PRIORITY, lthrow, GetResourceString(L"LOCALIZED_ALTERNATE_THROW") },
		{L"time", 0, 0, 0, PREFIX_PRIORITY, ltime, GetResourceString(L"LOCALIZED_ALTERNATE_TIME") },
		{L"timemilli", 0, 0, 0, PREFIX_PRIORITY, ltimemilli, GetResourceString(L"LOCALIZED_ALTERNATE_TIMEMILLI") },
		{L"to", -1, -1, -1, PREFIX_PRIORITY, lto, GetResourceString(L"LOCALIZED_ALTERNATE_TO") },
		{L"tone", 2, 2, 2, PREFIX_PRIORITY, ltone, GetResourceString(L"LOCALIZED_ALTERNATE_TONE") },
		{L"towards", 1, 1, 1, PREFIX_PRIORITY, ltowards, GetResourceString(L"LOCALIZED_ALTERNATE_TOWARDS") },
		{L"towardsxyz", 1, 1, 1, PREFIX_PRIORITY, ltowardsxyz, GetResourceString(L"LOCALIZED_ALTERNATE_TOWARDSXYZ") },
		{L"trace", 1, 1, 1, PREFIX_PRIORITY, ltrace, GetResourceString(L"LOCALIZED_ALTERNATE_TRACE") },
		{L"traced", 0, 0, 0, PREFIX_PRIORITY, ltraced, GetResourceString(L"LOCALIZED_ALTERNATE_TRACED") },
		{L"ts", 0, 0, 0, PREFIX_PRIORITY, ltextscreen, GetResourceString(L"LOCALIZED_ALTERNATE_TS") },
		{L"turtle", 0, 0, 0, PREFIX_PRIORITY, lturtle, GetResourceString(L"LOCALIZED_ALTERNATE_TURTLE") },
		{L"turtlemode", 0, 0, 0, PREFIX_PRIORITY, lturtlemode, GetResourceString(L"LOCALIZED_ALTERNATE_TURTLEMODE") },
		{L"turtles", 0, 0, 0, PREFIX_PRIORITY, lturtles, GetResourceString(L"LOCALIZED_ALTERNATE_TURTLES") },
		{L"type", 0, 1, -1, PREFIX_PRIORITY, ltype, GetResourceString(L"LOCALIZED_ALTERNATE_TYPE") },
		{L"unbury", 1, 1, 1, PREFIX_PRIORITY, lunbury, GetResourceString(L"LOCALIZED_ALTERNATE_UNBURY") },
		{L"unstep", 1, 1, 1, PREFIX_PRIORITY, lunstep, GetResourceString(L"LOCALIZED_ALTERNATE_UNSTEP") },
		{L"untrace", 1, 1, 1, PREFIX_PRIORITY, luntrace, GetResourceString(L"LOCALIZED_ALTERNATE_UNTRACE") },
		{L"up", 1, 1, 1, PREFIX_PRIORITY, luppitch, GetResourceString(L"LOCALIZED_ALTERNATE_UP") },
		{L"uppercase", 1, 1, 1, PREFIX_PRIORITY, luppercase, GetResourceString(L"LOCALIZED_ALTERNATE_UPPERCASE") },
		{L"uppitch", 1, 1, 1, PREFIX_PRIORITY, luppitch, GetResourceString(L"LOCALIZED_ALTERNATE_UPPITCH") },
		{L"wait", 1, 1, 1, PREFIX_PRIORITY, lwait, GetResourceString(L"LOCALIZED_ALTERNATE_WAIT") },
		{L"window", 0, 0, 0, PREFIX_PRIORITY, lwindow, GetResourceString(L"LOCALIZED_ALTERNATE_WINDOW") },
		{L"windowcreate", 8, 8, 8, PREFIX_PRIORITY, lwindowcreate, GetResourceString(L"LOCALIZED_ALTERNATE_WINDOWCREATE") },
		{L"windowenable", 2, 2, 2, PREFIX_PRIORITY, lwindowenable, GetResourceString(L"LOCALIZED_ALTERNATE_WINDOWENABLE") },
		{L"windowdelete", 1, 1, 1, PREFIX_PRIORITY, lwindowdelete, GetResourceString(L"LOCALIZED_ALTERNATE_WINDOWDELETE") },
		{L"windowfileedit", 2, 2, 2, PREFIX_PRIORITY, lwindowfileedit, GetResourceString(L"LOCALIZED_ALTERNATE_WINDOWFILEEDIT") },
		{L"windowset", 2, 2, 2, PREFIX_PRIORITY, lwindowset, GetResourceString(L"LOCALIZED_ALTERNATE_WINDOWSET") },
		{L"winhelp", 1, 1, 2, PREFIX_PRIORITY, lwinhelp, GetResourceString(L"LOCALIZED_ALTERNATE_WINHELP") },
		{L"word", 0, 2, -1, PREFIX_PRIORITY, lword, GetResourceString(L"LOCALIZED_ALTERNATE_WORD") },
		{L"wordp", 1, 1, 1, PREFIX_PRIORITY, lwordp, GetResourceString(L"LOCALIZED_ALTERNATE_WORDP") },
		{L"word?", 1, 1, 1, PREFIX_PRIORITY, lwordp, GetResourceString(L"LOCALIZED_ALTERNATE_WORD_") },
		{L"wrap", 0, 0, 0, PREFIX_PRIORITY, lwrap, GetResourceString(L"LOCALIZED_ALTERNATE_WRAP") },
		{L"writepos", 0, 0, 0, PREFIX_PRIORITY, lwritepos, GetResourceString(L"LOCALIZED_ALTERNATE_WRITEPOS") },
		{L"writer", 0, 0, 0, PREFIX_PRIORITY, lwriter, GetResourceString(L"LOCALIZED_ALTERNATE_WRITER") },
		{L"yesnobox", 2, 2, 2, PREFIX_PRIORITY, lyesnobox, GetResourceString(L"LOCALIZED_ALTERNATE_YESNOBOX") },
		{L"yield", 0, 0, 0, PREFIX_PRIORITY, lyield, GetResourceString(L"LOCALIZED_ALTERNATE_YIELD") },
		{L"zoom", 1, 1, 1, PREFIX_PRIORITY, lzoom, GetResourceString(L"LOCALIZED_ALTERNATE_ZOOM") },
	};

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
    for (size_t i = 0; i < sizeof(prims)/sizeof(PRIMTYPE); i++)
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
    for (size_t i = 0; i < sizeof(prims)/sizeof(PRIMTYPE); i++)
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


    Truex.Initialize(L"true",   GetResourceString(L"LOCALIZED_ALTERNATE_TRUE"));
    Falsex.Initialize(L"false", GetResourceString(L"LOCALIZED_ALTERNATE_FALSE"));
    To.Initialize(L"to",		GetResourceString(L"LOCALIZED_ALTERNATE_TO"));
    End.Initialize(L"end",		GetResourceString(L"LOCALIZED_ALTERNATE_END"));

    Toplevel.Initialize(L"toplevel",	GetResourceString(L"LOCALIZED_ALTERNATE_TOPLEVEL"));
    System.Initialize(L"system",		GetResourceString(L"LOCALIZED_ALTERNATE_SYSTEM"));
    Error.Initialize(L"error",			GetResourceString(L"LOCALIZED_ALTERNATE_ERROR"));

    Left_Paren = intern(make_static_strnode(L"("));
    Right_Paren = intern(make_static_strnode(L")"));
    Minus_Sign = intern(make_static_strnode(L"-"));
    Minus_Tight = intern(make_static_strnode(L"--"));
    Query = intern(make_static_strnode(L"?"));
    Null_Word = intern(make_static_strnode(L""));
    Macro = intern(make_static_strnode(L".macro"));
    If = intern(make_static_strnode(L"if"));
    Ifelse = intern(make_static_strnode(L"ifelse"));
    Redefp.Initialize(L"redefp",					GetResourceString(L"LOCALIZED_ALTERNATE_REDEFP"));
    Caseignoredp.Initialize(L"caseignoredp",		GetResourceString(L"LOCALIZED_ALTERNATE_CASEIGNOREDP"));
    Erract.Initialize(L"erract",					GetResourceString(L"LOCALIZED_ALTERNATE_ERRACT"));
    Printdepthlimit.Initialize(L"printdepthlimit",	GetResourceString(L"LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT"));
    Printwidthlimit.Initialize(L"printwidthlimit",	GetResourceString(L"LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT"));
    Pause = intern(make_static_strnode(L"pause"));
    Startup.Initialize(L"startup",					GetResourceString(L"LOCALIZED_ALTERNATE_STARTUP"));
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
