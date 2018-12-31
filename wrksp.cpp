/*
 *      wrksp.cpp       logo workspace management module                dvb
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
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include <stdlib.h>
    #include <string.h>

    #include <wx/wx.h>

    #include <wx/arrstr.h>
    #include <wx/dir.h>
    #include <wx/filename.h>
    #include <wx/window.h>

    #include "wrksp.h"
    #include "logodata.h"
    #include "appendablelist.h"
    #include "localizednode.h"
    #include "intern.h"
    #include "init.h"
    #include "mem.h"
    #include "parse.h"
    #include "eval.h"
    #include "error.h"
    #include "logomath.h"
    #include "paren.h"
    #include "ibmterm.h"
    #include "startup.h"
    #include "print.h"
    #include "files.h"
    #include "unix.h"
    #include "avltree.h"
    #include "sort.h"
    #include "stringadapter.h"
    #include "localizedstrings.h"
    #include "cursor.h"
    #include "graphwin.h"
    #include "screenwindow.h"
//    #include "debugheap.h"
#endif

bool bExpert    = false;               // Expert mode
bool yield_flag = true;                // Flag to signal yield state
bool IsDirty    = false;               // Flag to signal to query user ok to quit
bool to_pending = false;

long int g_CharactersSuccessfullyParsedInEditor;

static
NODE *make_procnode(NODE *lst, NODE *wrds, short min, short df, short max)
{
    return cons_list(
        lst, 
        wrds,
        make_intnode((FIXNUM) min),
        make_intnode((FIXNUM) df),
        make_intnode((FIXNUM) max));
}


static
NODE *get_bodywords(NODE *proc, NODE *name)
{
    NODE *bodywords = bodywords__procnode(proc);

    if (bodywords != NIL) 
    {
        // bodywords__procnode(proc) was already created.
        // Just return it.
        return bodywords;
    }

    // bodywords__procnode(proc) isn't set yet.  Set it.

    // Create the "TO" line, which also contains the inputs
    CAppendableList toline;
    name = intern(name);
    toline.AppendElement(is_macro(name) ? Macro : To.GetNode());
    toline.AppendElement(name);
    for (NODE * formals = formals__procnode(proc);
         formals != NIL;
         formals = cdr(formals))
    {
        NODE * formal = car(formals);

        NODE * tnode;
        if (is_list(formal))
        {
            // an input with a default value or a "rest" input
            tnode = cons(make_colon(car(formal)), cdr(formal));
        }
        else if (nodetype(formal) == INTEGER)
        {
            // a number, which indicates the default number of inputs
            tnode = formal;
        }
        else
        {
            // the name of a formal parameter (add a colon in front of it).
            tnode = make_colon(formal);
        }

        // append tnode to the "TO" line
        toline.AppendElement(tnode);
    }


    // Add the body of the procedure
    CAppendableList bodywordslist;
    bodywordslist.AppendElement(toline.GetList());
    for (NODE * line = bodylist__procnode(proc);
         line != NIL;
         line = cdr(line))
    {
        NODE * bodywords = runparse(car(line));

        bodywordslist.AppendElement(bodywords);
    }

    // add the END line
    bodywordslist.AppendElement(cons_list(End.GetNode()));

    // we're done making the bodywords list
    bodywords = bodywordslist.GetList();

    // cache the value of the bodywords so we won't have to
    // create it the next time.
    setbodywords__procnode(proc, bodywords);

    // return the bodywords
    return bodywords;
}


// Gets the first argument in the args list as a name of a variable or plist.
// Throws recoverable bad input errors until it gets one.
static
NODE *name_arg(NODE *args)
{
    while (is_aggregate(car(args)) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, car(args)));
    }
    return car(args);
}


// Gets the first argument in the args list as a name of a procedure.
// Throws recoverable bad input errors until it gets one.
static
NODE *proc_name_arg(NODE *args)
{
    while ((is_aggregate(car(args)) || numberp(car(args))) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, car(args)));
    }
    return car(args);
}

void untreeify_procnode(NODE * procnode)
{
    if (procnode != NIL && procnode != UNDEFINED)
    {
        // untreeify the body
        if (!is_prim(procnode) && is_tree(bodylist__procnode(procnode)))
        {
            untreeify_body(bodylist__procnode(procnode));
        }
    }
}

NODE *ltext(NODE *args)
{
    NODE* name = proc_name_arg(args);
    if (NOT_THROWING)
    {
        NODE* val = procnode__caseobj(intern(name));
        if (val == UNDEFINED)
        {
            err_logo(DK_HOW_UNREC, name);
            return Unbound;
        }
        else if (is_prim(val))
        {
            err_logo(IS_PRIM, name);
            return Unbound;
        }
        else
        {
            return text__procnode(val);
        }
    }
    return Unbound;
}

NODE *lfulltext(NODE *args)
{
    NODE* name = proc_name_arg(args);
    if (NOT_THROWING)
    {
        NODE* val = procnode__caseobj(intern(name));
        if (val == UNDEFINED)
        {
            err_logo(DK_HOW_UNREC, name);
            return Unbound;
        }
        else if (is_prim(val))
        {
            err_logo(IS_PRIM, name);
            return Unbound;
        }
        else
        {
            return get_bodywords(val, name);
        }
    }
    return Unbound;
}

static
void set_new_generation()
{
    assign(the_generation, cons_list(NIL));
}

static
bool is_list_of_lists(const NODE *val) 
{
    if (val == NIL) 
    {
        // base case: empty list
        return true;
    }

    if (!is_list(val))
    {
        // not even a list
        return false;
    }

    if (!is_list(car(val))) 
    {
        // a list of something other than lists
        return false;
    }

    return is_list_of_lists(cdr(val));
}


// returns the number of default arguments for a procedure node
static
int
get_default_args_for_procedure(const NODE * procedure)
{
    return is_prim(procedure) ? 
        getprimdflt(procedure) :
        getint(dfltargs__procnode(procedure));
}

static
NODE *define_helper(NODE *args, int macro_flag)
{
    /* macro_flag is -1 for anonymous function */
    NODE *name;
    NODE *val;
    int minimum = 0;
    int deflt = 0;
    int maximum = 0;
    int old_default = -1;

    if (macro_flag >= 0)
    {
        // macro or procedure
        name = proc_name_arg(args);
        if (NOT_THROWING)
        {
            name = intern(name);
            val = procnode__caseobj(name);
            bool redef = canRedefinePrimitives();
            if (!redef && is_prim(val))
            {
                err_logo(IS_PRIM, name);
                return Unbound;
            }
            else if (val != UNDEFINED)
            {
                untreeify_procnode(val);
                old_default = get_default_args_for_procedure(val);
            }
        }
        if (NOT_THROWING)
        {
            // make sure the bodylist is valid input
            val = cadr(args);
            while ((val == NIL || !is_list_of_lists(val)) &&
                   NOT_THROWING)
            {
                setcar(cdr(args), err_logo(BAD_DATA, val));
                val = cadr(args);
            }
        }
    }
    else
    {
        // lambda 
        val = args;
    }


    if (NOT_THROWING)
    {
        args = car(val);
        if (args != NIL)
        {
            make_runparse(args);
            args = parsed__runparse(args);
        }
        setcar(val, args);
        while (args != NIL)
        {
            NODE* arg = car(args);
            if (arg != NIL && is_list(arg) && maximum != -1)
            {
                make_runparse(arg);
                arg = parsed__runparse(arg);
                setcar(args, arg);
                maximum++;
                if (cdr(arg) == NIL)
                {
                    maximum = -1;
                }
            }
            else if (nodetype(arg) == INTEGER &&
                     getint(arg) <=/* (unsigned) */maximum &&
                     getint(arg) >= minimum)
            {
                deflt = getint(arg);
            }
            else if (maximum == minimum)
            {
                minimum++;
                maximum++;
                deflt++;
            }
            else
            {
                err_logo(BAD_DATA_UNREC, arg);
                break;
            }

            args = cdr(args);
            if (check_throwing) 
            {
                break;
            }
        }
    }

    if (macro_flag < 0)
    {
        // lambda
        return make_procnode(val, NIL, minimum, deflt, maximum);
    }
    else if (NOT_THROWING)
    {
        // macro or procedure
        setprocnode__caseobj(
            name,
            make_procnode(val, NIL, minimum, deflt, maximum));

        if (macro_flag)
        {
            setflag__caseobj(name, PROC_MACRO);
        }
        else
        {
            clearflag__caseobj(name, PROC_MACRO);
        }

        if (deflt != old_default && old_default >= 0)
        {
            set_new_generation();
        }
    }
    return Unbound;
}

NODE *ldefine(NODE *args)
{
    return define_helper(args, FALSE);
}

NODE *ldefmacro(NODE *args)
{
    return define_helper(args, TRUE);
}

NODE *anonymous_function(NODE *text)
{
    return define_helper(text, -1);
}

static
NODE *to_helper(NODE *args, bool is_macro)
{
    if (ufun != NIL && *GetLoadStream() == stdin)
    {
        err_logo(NOT_INSIDE, NIL);
        return Unbound;
    }

    if (args == NIL)
    {
        err_logo(NOT_ENOUGH, NIL);
        return Unbound;
    }

	GetInputMode() = INPUTMODE_To;

    NODE *formals = NIL;

    int minimum = 0;
    int deflt = 0;
    int maximum = 0;
    int old_default = -1;

    NODE * proc_name = car(args);

    SetErrorProcName(vref(proc_name));  // for error reporting

    if (nodetype(proc_name) != CASEOBJ)
    {
        err_logo(BAD_DATA_UNREC, proc_name);
    }
    else if ((procnode__caseobj(proc_name) != UNDEFINED && *GetLoadStream() == stdin)
             || is_prim(procnode__caseobj(proc_name)))
    {
        err_logo(ALREADY_DEFINED, proc_name);
    }
    else
    {
        NODE *old_proc = procnode__caseobj(proc_name);
        if (old_proc != UNDEFINED)
        {
            untreeify_procnode(old_proc);
            old_default = getint(dfltargs__procnode(old_proc));
        }

        //
        // read the formal parameters
        //
        NODE *formals_lastnode = NIL;
        args = cdr(args);
        while (args != NIL)
        {
            NODE * arg = car(args);
            args = cdr(args);
            if (nodetype(arg) == CONS && maximum != -1)
            {
                // this is either an input with a default value or a "rest" input
                make_runparse(arg);
                arg = parsed__runparse(arg);
                if (nodetype(car(arg)) != COLON)
                {
                    // input names must begin with a colon
                    err_logo(BAD_DATA_UNREC, arg);
                    break;
                }

                setcar(arg, node__colon(car(arg)));
                if (cdr(arg) == NIL)
                {
                    // this is a "rest" input
                    maximum = -1;
                }
                else
                {
                    // this is an input with a default value
                    maximum++;
                }
            }
            else if (nodetype(arg) == COLON && maximum == minimum)
            {
                // this is a regular input
                arg = node__colon(arg);
                minimum++;
                maximum++;
                deflt++;
            }
            else if (nodetype(arg) == INTEGER &&
                     getint(arg) <= /*(unsigned) */maximum &&
                     getint(arg) >= minimum)
            {
                // this is a number that specifies the number of default inputs
                deflt = getint(arg);
            }
            else
            {
                // unknown input type
                err_logo(BAD_DATA_UNREC, arg);
                break;
            }

            // append arg to the end of the "formals" list
            NODE *tnode = cons_list(arg);
            if (formals == NIL) 
            {
                formals = tnode;
            }
            else
            { 
                setcdr(formals_lastnode, tnode);
            }
            formals_lastnode = tnode;
        }
    }

    //
    // read the procedure body
    //
    if (NOT_THROWING)
    {
        NODE * body_words          = cons_list(current_line);
        NODE * body_words_lastnode = body_words;

        NODE * body_list          = cons_list(formals);
        NODE * body_list_lastnode = body_list;

		SetErrorToLine(body_words);
        to_pending = true;      // for int or quit signal
        while (NOT_THROWING && to_pending && !(GetLoadStream()->IsEOF()))
        {
            NODE * ttnode = reader(GetLoadStream(), L"> ");

            // append ttnode to body_words
            NODE * tnode = cons_list(ttnode);
            setcdr(body_words_lastnode, tnode);
            body_words_lastnode = tnode;

            NODE * next_line = parser(car(body_words_lastnode), true);
            if (next_line != NIL && End.Equals(car(next_line)))
            {
                // This line only contains "End", which denotes 
                // the end of this procedure.
                // Stop reading lines.
                gcref(next_line);
                break;
            }
            else if (next_line != NIL)
            {
                // append next_line to body_list
                NODE * next_line_list = cons_list(next_line);
                setcdr(body_list_lastnode, next_line_list);
                body_list_lastnode = next_line_list;
            }
            else
            {
                // the line is empty--ignore it
                gcref(next_line);
            }
        }


        //
        // package the procedure definition into the case object
        //
        if (to_pending && NOT_THROWING)
        {
            setprocnode__caseobj(
                proc_name,
                make_procnode(body_list, body_words, minimum, deflt, maximum));
            if (is_macro)
            {
                setflag__caseobj(proc_name, PROC_MACRO);
            }
            else
            {
                clearflag__caseobj(proc_name, PROC_MACRO);
            }

            if (deflt != old_default && old_default >= 0)
            {
                set_new_generation();
            }
            if (*GetLoadStream() == stdin)
            {
                ndprintf(
					stdoutstream,
                    MESSAGETYPE_Normal,
					GetResourceString(L"LOCALIZED_PROCEDUREDEFINED"),
                    proc_name);
            }

            // Set the "dirty" flag so that closing FMSLogo will
            // prompt the user that they have unsaved changes.
            IsDirty = true;
        }
        else
        {
            // cleanup on error
            gcref(body_words);
            gcref(body_list);
        }

        rd_clearbuffer(GetLoadStream());
		SetErrorToLine(NIL);
        to_pending = false;
    }
    else
    {
        gcref(formals);
    }
	SetErrorProcName(NIL);
	GetInputMode() = INPUTMODE_None;
    return Unbound;
}

NODE *lto(NODE *args)
{
    to_helper(args, false);
    return Unbound;
}

NODE *lmacro(NODE *args)
{
    to_helper(args, true);
    return Unbound;
}

NODE *lmake(NODE *args)
{
    NODE * what = name_arg(args);
    if (NOT_THROWING)
    {
        what = intern(what);
        setvalnode__caseobj(what, cadr(args));
        if (flag__caseobj(what, VAL_TRACED))
        {
            // This variable is traced.
            // Trace the assignment to the write stream.
            NODE *new_value            = vref(maybe_quote(cadr(args)));
            NODE *quoted_variable_name = vref(make_quote(what));

            ndprintf(
                GetOutputStream(),
                MESSAGETYPE_Normal,
				GetResourceString(L"LOCALIZED_TRACING_MAKE"),
                quoted_variable_name,
                new_value);

            deref(quoted_variable_name);
            deref(new_value);

            // trace the name of the procedure where the assignment happened.
            if (ufun != NIL)
            {
                ndprintf(
                    GetOutputStream(),
                    MESSAGETYPE_Normal,
					GetResourceString(L"LOCALIZED_TRACING_LOCATION"),
                    ufun,
                    this_line);
            }
            new_line(GetOutputStream(), MESSAGETYPE_Normal);
        }
    }
    return Unbound;
}

// want_buried can be one of four values:
//  0            - get unburied objects
//  PROC_BURIED  - get buried objects
//  PROC_STEPPED - get stepped objects
//  PROC_TRACED  - get traced objects
static int want_buried = 0;

enum CNTLSTTYP
{
    c_PROCS, 
    c_VARS, 
    c_PLISTS,
};


static
int bck(int flag)
{
    return (want_buried ? !flag : flag);
}

// Appends the canonical form of sym into contents_list
// if it matches the given filter.
//
// contents_list      - The list to which matching symbols should be appened.
// sym                - The object from the symbol table
// contents_list_type - The type of object we're looking for.
static
void 
contents_map(
    CAppendableList & contents_list,
    NODE *            sym,
    CNTLSTTYP         contents_list_type
    )
{
    // flag_check starts out as one of three values,
    // PROC_BURIED, PROC_TRACED, or PROC_STEPPED.
    int flag_check = PROC_BURIED;
	
    if (want_buried != 0)
    {
        // The caller has specified that they want
        // something specific: either BURIED, TRACED,
        // or STEPPED.
        flag_check = want_buried;
    }
	
    switch (contents_list_type)
    {
    case c_PROCS:
        // We're looking for procedures.

        if (procnode__object(sym) == UNDEFINED ||
            is_prim(procnode__object(sym)))
        {
            // Either symbol doesn't have a procedure
            // definition, or its a primative, so it
            // cannot be UNBURIED, BURIED, STEPPED, or TRACED.
            return;
        }

        // Check if the procedure matches
        // what we're looking for.
        if (bck(flag__object(sym, flag_check)))
        {
            // The procedure doesn't match the filter.
            return;
        }
        break;

    case c_VARS:
        if (valnode__object(sym) == Unbound) 
        {
            // The symbol doesn't have a variable.
            return;
        }

        // Shift up one bit to the corresponding flag for variables.
        // For example, from PROC_BURIED to VAL_BURIED.
        flag_check <<= 1;
        if (bck(flag__object(sym, flag_check))) 
        {
            // The variable doesn't match the filter.
            return;
        }
        break;

    case c_PLISTS:
        if (plist__object(sym) == NIL) 
        {
            // The symbol doesn't have a property list.
            return;
        }

        // Shift up one bit to the corresponding flag for property lists.
        // For example, from VAL_BURIED to PLIST_BURIED.
        flag_check <<= 2;
        if (bck(flag__object(sym, flag_check))) 
        {
            // The propery list doesn't match the filter.
            return;
        }
        break;
    }

    // Append the canonical form of symbol
    contents_list.AppendElement(canonical__object(sym));
}

static
NODE *
get_contents(
    CNTLSTTYP contents_type
    )
{
    CAppendableList contents_list;

    for (int i = 0; i < HASH_LEN; i++)
    {
        for (NODE * nd = hash_table[i]; nd != NIL; nd = cdr(nd))
        {
            contents_map(contents_list, car(nd), contents_type);
        }
    }

    // We can ignore the case when sorting because the contents
    // list is already mapping into lower-case.
    return mergesort(contents_list.GetList(), false);
}

// Return a contents list (a list of three lists)
// that match the given filter: PROC_BURIED, PROC_TRACED,
// or PROC_STEPPED.  The returned list takes the following
// form.
//  [ [matching procs] [matching variables] [matching plists] ]
//
static
NODE *get_contents_list(int filter)
{
    want_buried = filter;

    NODE *ret = NIL;

    // Get all property lists that match the filter
    // and wrap them in a list.
    ret = cons(get_contents(c_PLISTS), ret);

    // Get all variables that match the filter
    // and prepend them to the contents list
    ret = cons(get_contents(c_VARS), ret);

    // Get all procedures that match the filter
    // and prepend them to the contents list
    ret = cons(get_contents(c_PROCS), ret);
	
    return ret;
}

NODE *lcontents(NODE *)
{
    return get_contents_list(0);
}

NODE *ltraced(NODE *)
{
    return get_contents_list(PROC_TRACED);
}

NODE *lstepped(NODE *)
{
    return get_contents_list(PROC_STEPPED);
}

NODE *lburied(NODE *)
{
    return get_contents_list(PROC_BURIED);
}

NODE *lprocedures(NODE *)
{
    want_buried = 0;

    return get_contents(c_PROCS);
}

NODE *lnames(NODE *)
{
    want_buried = 0;

    return cons_list(NIL, get_contents(c_VARS));
}

NODE *lplists(NODE *)
{
    want_buried = 0;

    return cons_list(NIL, NIL, get_contents(c_PLISTS));
}

static
NODE *one_list(NODE *nd)
{
    if (!is_list(nd))
    {
        return cons_list(nd);
    }
    return nd;
}

// constructs three separate lists from a "contents list" arg.
static
void three_lists(NODE *arg, NODE **proclst, NODE **varlst, NODE **plistlst)
{
    // initialize all lists to the empty list
    *plistlst = *varlst = *proclst = NIL;

    if (nodetype(car(arg)) == CONS)
    {
        // The input is a list of something.
        // Advance to the first item in the list.
        arg = car(arg);
    }

    if (!is_list(car(arg)))
    {
        // the contents list is a list of procedure names
        *proclst = arg;
    }
    else
    {
        // the contents list is a list of lists
        *proclst = car(arg);
        if (cdr(arg) != NIL)
        {
            *varlst = one_list(cadr(arg));
            if (cddr(arg) != NIL)
            {
                *plistlst = one_list(car(cddr(arg)));
            
                if (cdr(cddr(arg)) != NIL)
                {
                    // this was a list of more than three lists
                    err_logo(BAD_DATA_UNREC, arg);
                    *plistlst = *varlst = *proclst = NIL;
                }
            }
        }
    }

    if (!is_list(*proclst) || !is_list(*varlst) || !is_list(*plistlst))
    {
        err_logo(BAD_DATA_UNREC, arg);
        *plistlst = *varlst = *proclst = NIL;
    }
}

static
wchar_t *expand_slash(const NODE *wd)
{
    // figure out how many characters we need to expand
    int len = getstrlen(wd);
    int i = 0;
    int j = len;
    for (const wchar_t * cp = getstrptr(wd); 
         --j >= 0;
        )
    {
        if (ecma_get(*cp++)) 
        {
            i++;
        }
    }

    // allocate space for the expanded string
	wchar_t * result = (wchar_t *) malloc((len + i + 1)*sizeof(wchar_t));
    if (result == NULL)
    {
        err_logo(OUT_OF_MEM, NIL);
        return NULL;
    }

    // copy the string to result and add backslashes as we go
	wchar_t *cp2 = result;
    j = len;
    for (const wchar_t * cp = getstrptr(wd);
         --j >= 0;
        )
    {
        if (ecma_get(*cp))
        {
            // backslash this character
            *cp2++ = L'\\';
        }
        *cp2++ = ecma_clear(*cp++);
    }
    *cp2 = L'\0';

    return result;
}

static
void
po_helper_print_plist(
    void * Context,
    NODE * Key,
    NODE * Value
    )
{
    NODE * const quoted_plist_name = static_cast<NODE *>(Context);
    NODE * quoted_property_name  = maybe_quote(Key);
    NODE * quoted_property_value = maybe_quote(Value);

    // PPROP "list "name "value
    ndprintf(
        GetOutputStream(), 
        MESSAGETYPE_Normal,
        L"%t %s %s %s\n",
		GetResourceString(L"LOCALIZED_ALTERNATE_PPROP"),
        quoted_plist_name,
        quoted_property_name,
        quoted_property_value);

    gcref(quoted_property_name);
    gcref(quoted_property_value);
}

static
void po_helper(NODE *arg, int just_titles)  /* >0 for POT, 0 for PO, <0 for EDIT */
{
    print_backslashes = true;

    NODE *proclst;
    NODE *varlst;
    NODE *plistlst;
    three_lists(arg, &proclst, &varlst, &plistlst);

    // print all of the requested procedures
    while (proclst != NIL)
    {
        if (is_aggregate(car(proclst)))
        {
            err_logo(BAD_DATA_UNREC, car(proclst));
            break;
        }

        NODE * tvar = procnode__caseobj(intern(car(proclst)));

        if (tvar == UNDEFINED)
        {
            // the procedure hasn't been defined.

            if (just_titles < 0)
            {
                // We're doing an EDIT, so it's okay that the
                // procedure hasn't been defined.
                // Print the following boilerplate for the user:
                //   TO <proc>\n
                //   END\n
                //   \n
                ndprintf(
                    GetOutputStream(), 
                    MESSAGETYPE_Normal,
                    L"%t %p\n%t\n\n", 
                    To.GetName(),
                    car(proclst),
                    End.GetName());
            }
            else
            {
                err_logo(DK_HOW_UNREC, car(proclst));
                break;
            }
        }
        else if (is_prim(tvar))
        {
            err_logo(IS_PRIM, car(proclst));
            break;
        }
        else
        {
            NODE * bodywords = get_bodywords(tvar, car(proclst));
            if (just_titles > 0)
            {
                // only print the title line 
                NODE * titleline = car(bodywords);
                if (is_list(titleline))
                {
                    print_helper(
                        GetOutputStream(),
                        MESSAGETYPE_Normal,
                        titleline);
                }
                else
                {
					wchar_t *str = expand_slash(titleline);
                    ndprintf(
                        GetOutputStream(),
                        MESSAGETYPE_Normal,
                        L"%t",
                        str);
                    free(str);
                }
            }
            else 
            {
                // Print the entire procedure definition one line at a time.
                while (bodywords != NIL)
                {
                    NODE * currentline = car(bodywords);
                    if (is_list(currentline))
                    {
                        print_helper(
                            GetOutputStream(),
                            MESSAGETYPE_Normal,
                            currentline);
                    }
                    else
                    {
						wchar_t *str = expand_slash(currentline);
                        if (GetOutputStream()->GetFile() == stdout)
                        {
                            if (str[0] == L'\0')
                            {
                                // str doesn't end in a newline.  
                                // printfx() always writes a newline to the
                                // commander history, regardless of if the 
                                // string ends in a newline (in essence, the 
                                // newline is optional).  However, it doesn't
                                // write anything when given the empty
                                // string, which is what happens when there's a
                                // blank line in the procedure definition.
                                // To ensure that blank lines are preserved, we
                                // write a newline.
                                // Note that we can't just call 
                                //   printfx("%s\n", str);
                                // because that could overflow the buffer in
                                // printfx()
                                printfx(L"\n");
                            }
                            else
                            {
                                printfx(str);
                            }

							DribbleWriteLine(str);
                        }
                        else
                        {
							GetOutputStream()->Write(str);
                        }
                        free(str);
                    }

                    if (*GetOutputStream() != stdout) 
                    {
                        new_line(GetOutputStream(), MESSAGETYPE_Normal);
                    }

                    bodywords = cdr(bodywords);
                }
            }
            new_line(GetOutputStream(), MESSAGETYPE_Normal);
        }
        proclst = cdr(proclst);
        if (check_throwing) break;
    }

    // print all of the requested variables
    for (NODE * current_varlist_node = varlst;
         current_varlist_node != NIL;
         current_varlist_node = cdr(current_varlist_node))
    {
        if (check_throwing) 
        {
            break;
        }

        NODE * current_variable = car(current_varlist_node);
        if (is_aggregate(current_variable))
        {
            err_logo(BAD_DATA_UNREC, current_variable);
            break;
        }

        NODE * quoted_value = maybe_quote(valnode__caseobj(intern(current_variable)));
        if (quoted_value == Unbound)
        {
            if (just_titles >= 0)
            {
                err_logo(NO_VALUE, current_variable);
                break;
            }
        }
        else
        {
            NODE * quoted_variable_name = make_quote(current_variable);

            // MAKE "name "value
            ndprintf(
                GetOutputStream(),
                MESSAGETYPE_Normal,
                L"%t %s %s\n",
				GetResourceString(L"LOCALIZED_ALTERNATE_MAKE"),
                quoted_variable_name,
                quoted_value);

            gcref(quoted_variable_name);
        }
        gcref(quoted_value);
    }

    // print all of the requested property lists
    while (plistlst != NIL && NOT_THROWING)
    {
        if (is_aggregate(car(plistlst)))
        {
            err_logo(BAD_DATA_UNREC, car(plistlst));
            break;
        }

        NODE * plist_name        = car(plistlst);
        NODE * quoted_plist_name = maybe_quote(plist_name);

        NODE * plist = plist__caseobj(intern(plist_name));
        if (plist != NIL && just_titles > 0)
        {
            NODE * flat_plist = AvlTreeFlatten(plist);

            // PLIST "name = [name1 value1 name2 value2]
            ndprintf(
                GetOutputStream(),
                MESSAGETYPE_Normal,
                L"%t %s = %s\n",
				GetResourceString(L"LOCALIZED_ALTERNATE_PLIST"),
                quoted_plist_name, 
                flat_plist);

            gcref(flat_plist);
        }
        else 
        {
            // PPROP "list "name "value
            AvlTreeEach(plist, quoted_plist_name, po_helper_print_plist);
        }

        gcref(quoted_plist_name);

        plistlst = cdr(plistlst);
        if (check_throwing) break;
    }

    print_backslashes = false;

    gcref(proclst);
    gcref(varlst);
    gcref(plistlst);
}

NODE *lpo(NODE *arg)
{
    lsetcursorwait(NIL);
    po_helper(arg, 0);
    lsetcursorarrow(NIL);

    return Unbound;
}

NODE *lpot(NODE *arg)
{
    po_helper(arg, 1);
    return Unbound;
}

NODE *lerase(NODE *arg)
{
    NODE *proclst;
    NODE *varlst;
    NODE *plistlst;
    three_lists(arg, &proclst, &varlst, &plistlst);

    if (proclst != NIL)
    {
        set_new_generation();
    }

    while (proclst != NIL)
    {
        if (is_aggregate(car(proclst)))
        {
            err_logo(BAD_DATA_UNREC, car(proclst));
            break;
        }
        NODE * nd = intern(car(proclst));
        bool redef = canRedefinePrimitives();
        if (!redef && is_prim(procnode__caseobj(nd)))
        {
            err_logo(IS_PRIM, nd);
            break;
        }

        untreeify_procnode(procnode__caseobj(nd));

        setprocnode__caseobj(nd, UNDEFINED);

        proclst = cdr(proclst);
    }

    while (varlst != NIL && NOT_THROWING)
    {
        if (is_aggregate(car(varlst)))
        {
            err_logo(BAD_DATA_UNREC, car(varlst));
            break;
        }
        setvalnode__caseobj(intern(car(varlst)), Unbound);
        varlst = cdr(varlst);
    }

    while (plistlst != NIL && NOT_THROWING)
    {
        if (is_aggregate(car(plistlst)))
        {
            err_logo(BAD_DATA_UNREC, car(plistlst));
            break;
        }
        setplist__caseobj(intern(car(plistlst)), NIL);
        plistlst = cdr(plistlst);
    }

    gcref(proclst);
    gcref(varlst);
    gcref(plistlst);
    return Unbound;
}

// Sets or clears a flag on each interned object in the list.
// The flag must be one of PROC_BURIED, PROC_STEPPED, or PROC_TRACED.
// If setflag is true, the flag is set.  Otherwise the flag is cleared.
static
void bury_or_unbury_list(NODE * list, int flag, bool setflag)
{
    while (list != NIL && NOT_THROWING)
    {
        if (is_aggregate(car(list)))
        {
            err_logo(BAD_DATA_UNREC, car(list));
            break;
        }

        // set or clear the flag, depending on setflag
        NODE * caseobject = intern(car(list));
        if (setflag)
        {
            setflag__caseobj(caseobject, flag);
        }
        else
        {
            clearflag__caseobj(caseobject, flag);
        }

        list = cdr(list);
        if (check_throwing) break;
    }
}

// Buries, unburies, steps, unsteps, traces, or untraces
// all objects in the workspace that are in the contents
// list.
//
// arg     - The contents list of objects to modify.
// flag    - PROC_BURIED to bury or unbury the objects in arg.
//           PROC_STEPPED to step or unstep the objects in arg.
//           PROC_TRACED to trace or untrace the objects in arg.
// setflag - true, if the contents should be buried, stepped, or traced.
//           false, if the contents should be unburied, unstepped, or untraced.
static
NODE *bury_helper(NODE *arg, int flag, bool setflag)
{
    NODE *proclst;
    NODE *varlst;
    NODE *plistlst;
    three_lists(arg, &proclst, &varlst, &plistlst);

    if (NOT_THROWING)
    {
        // first bury/unbury procedures
        bury_or_unbury_list(proclst, flag, setflag);

        // Left-shifting the flag now refers to variables
        flag <<= 1;
        bury_or_unbury_list(varlst, flag, setflag);

        // Left-shifting the flag now refers propery lists
        flag <<= 1;
        bury_or_unbury_list(plistlst, flag, setflag);
    }

    gcref(proclst);
    gcref(varlst);
    gcref(plistlst);
    return Unbound;
}

NODE *lbury(NODE *arg)
{
    return bury_helper(arg, PROC_BURIED, true);
}

NODE *ltrace(NODE *arg)
{
    return bury_helper(arg, PROC_TRACED, true);
}

NODE *lstep(NODE *arg)
{
    return bury_helper(arg, PROC_STEPPED, true);
}

NODE *lunbury(NODE *arg)
{
    return bury_helper(arg, PROC_BURIED, false);
}

NODE *luntrace(NODE *arg)
{
    return bury_helper(arg, PROC_TRACED, false);
}

NODE *lunstep(NODE *arg)
{
    return bury_helper(arg, PROC_STEPPED, false);
}

// returns true iff something would appear in a workspace
// if it were opened with EDALL.
bool something_is_unburied()
{
    for (int i = 0; i < HASH_LEN; i++)
    {
        for (NODE * nd = hash_table[i]; nd != NIL; nd = cdr(nd))
        {
            NODE * symbol = car(nd);

            if (procnode__object(symbol) != UNDEFINED &&
                !is_prim(procnode__object(symbol)) &&
                !flag__object(symbol, PROC_BURIED))
            {
                // We found a procedure that's not buried.
                return true;
            }

            if (valnode__object(symbol) != Unbound &&
                !flag__object(symbol, VAL_BURIED))
            {
                // We found a variable that's not buried.
                return true;
            }

            if (plist__object(symbol) != NIL &&
                !flag__object(symbol, PLIST_BURIED))
            {
                // We found a property list that isn't buried
                return true;
            }
        }
    }

    // We walked through all symbols and didn't
    // find one that would appear in the workspace.
    return false;
}

NODE *ledit(NODE *args)
{
    if (!bExpert)
    {
        // non-experts shouldn't have to understand the complexities of 
        // having multiple editors open.  So if an editor is open, give
        // it focus instead of opening a new one.
        wxWindow * editor = GetEditorWxWindow();
        if (editor != NULL)
        {
            editor->Show();
            editor->Raise();
            editor->SetFocus();
            return Unbound;
        }
    }
	bool success = false;
    bool save_yield_flag = yield_flag;
    yield_flag = false;
    lsetcursorwait(NIL);

    // Write the requested contents to a file
    if (args != NIL)
    {
		CTextStream * fileStream = CFileTextStream::OpenForWrite(TempPathName, true);
        if (fileStream != NULL)
        {
            // HACK: change g_Writer to use the new stream
			CTextStream * savedWriterStream = GetOutputStream();

			SetOutputStream(fileStream);

            po_helper(args, -1);

            // restore g_Writer
			SetOutputStream(savedWriterStream);

			delete fileStream;
			success = true;
        }

        if(!success)
        {
            err_logo(
                FILE_ERROR,
                make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR")));
        }
    }

    // open the file inside an editor
    if (NOT_THROWING)
    {
        NODE * args_list = vref(args);
        if (ShowEditorForFile(TempPathName, args_list))
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR")));
        }
        else
        {
#ifdef _WINDOWS
        _wremove(TempPathName);
#else
        remove((const char*)TempPathName);
#endif
            IsDirty = true;
        }
    }

    lsetcursorarrow(NIL);
    yield_flag = save_yield_flag;

    return Unbound;
}

// Loads the contents of the temp file (which was presumably saved by the
// workspace editor) and sets a flag if an error was encountered.
//
// Returns true if the file was loaded (with or witout errors)
// Returns false if the file was not loaded.
bool endedit(void)
{
    bool realsave = false;

    g_CharactersSuccessfullyParsedInEditor = 0;

    if (!IsTimeToExit)
    {

        NODE * tmp_line = vref(current_line);
        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        start_execution();

        CTextStream* holdstrm = GetLoadStream();
		CTextStream* filestream = CFileTextStream::OpenForRead(TempPathName,true);

        if (filestream != NULL)
        {
			SetLoadStream(filestream);
			
			FIXNUM saved_value_status = g_ValueStatus;

            realsave = true;
            while (!GetLoadStream()->IsEOF() && NOT_THROWING)
            {
                g_CharactersSuccessfullyParsedInEditor = GetLoadStream()->GetPosition();
                assign(current_line, reader(GetLoadStream(), L""));

                NODE * exec_list = parser(current_line, true);

                g_ValueStatus = VALUE_STATUS_NotOk;
                eval_driver(exec_list);
            }
            g_ValueStatus = saved_value_status;
			SetLoadStream(holdstrm);
			assign(current_line, tmp_line);
			delete filestream;

		}
		else
		{
			// err_logo(
			//    FILE_ERROR,
			//    make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR));
		}

		stop_execution();

		lsetcursorarrow(NIL);
		yield_flag = save_yield_flag;
    }

    return realsave;
}

NODE *lthing(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = name_arg(args);
    if (NOT_THROWING)
    {
        val = valnode__caseobj(intern(arg));
    }

    while (val == Unbound && NOT_THROWING)
    {
        val = err_logo(NO_VALUE, car(args));
    }

    return val;
}

NODE *lnamep(NODE *args)
{
    NODE *arg = name_arg(args);
    if (NOT_THROWING)
    {
        return true_or_false(valnode__caseobj(intern(arg)) != Unbound);
    }
    return Unbound;
}

NODE *lprocedurep(NODE *args)
{
    NODE *arg = name_arg(args);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    NODE * procnode = load_procedure_if_necessary(intern(arg));
    return true_or_false(procnode != UNDEFINED);
}

NODE *lproplistp(NODE *args)
{
    NODE *arg = name_arg(args);
    if (NOT_THROWING)
    {
        return true_or_false(plist__caseobj(intern(arg)) != NIL);
    }
    return Unbound;
}


enum PROCTYPE
{
    PROCTYPE_UserDefined,
    PROCTYPE_Primitive,
    PROCTYPE_Macro,
};

static
NODE *check_proctype(NODE *args, PROCTYPE wanted)
{
    NODE * arg = proc_name_arg(args);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    NODE * interned_arg = intern(arg);

    NODE * procnode;
    if (wanted == PROCTYPE_Primitive)
    {
        procnode = procnode__caseobj(interned_arg);
    }
    else
    {
        // macros and user-defined functions may be implemented 
        // as a library routine, so we try to load it if it's not
        // already loaded.
        procnode = load_procedure_if_necessary(interned_arg);
    }

    if (procnode == UNDEFINED)
    {
        // this isn't even a procedure
        return Falsex.GetNode();
    }

    bool istype = false;

    switch (wanted)
    {
    case PROCTYPE_UserDefined:
        istype = is_prim(procnode) ? false : true;
        break;

    case PROCTYPE_Primitive:
        istype = is_prim(procnode) ? true : false;
        break;

    case PROCTYPE_Macro:
        istype = is_macro(interned_arg);
        break;

    default:
        assert(!"Internal Error: Bad Argument");
    }

    return true_or_false(istype);
}

NODE *lprimitivep(NODE *args)
{
    return check_proctype(args, PROCTYPE_Primitive);
}

NODE *ldefinedp(NODE *args)
{
    return check_proctype(args, PROCTYPE_UserDefined);
}

NODE *lmacrop(NODE *args)
{
    return check_proctype(args, PROCTYPE_Macro);
}

// Copies the title line from a procedure definition
// while replacing the name of the function.
static
NODE *cpdf_newname(NODE * Name, NODE * TitleLine)
{
    // Get the string from Name
    NODE *nname = cnv_node_to_strnode(Name);
    const wchar_t * namestr = getstrptr(nname);

    // For the purpose of this function, the title line
    // consists of three parts:
    // (TO|.MACRO) (procname) (args)*
    const wchar_t * titlestr = getstrptr(TitleLine);

    // Set p1 to just before the procedure name
    // Either "TO" or ".MACRO" comes before it.
    const wchar_t * p1 = titlestr + wcscspn(titlestr, L" \t");
    p1 = p1 + wcsspn(p1, L" \t");

    // Set p2 to just after the procedure name.
    const wchar_t * p2 = p1 + wcsspn(p1, L" \t");

	//FIXED
    // Contruct the new title line by replacing only
    // the name part of the original title line.
	//wchar_t newTitleLine[2000] = { 0 };
 //   wsprintf(
 //       newTitleLine,
 //       L"%.*s%.*s%s",
 //       p1-titlestr, titlestr,
 //       getstrlen(nname), namestr,
 //       p2);

    return make_strnode(wxString::Format(L"%.*s%.*s%s",
		p1 - titlestr, titlestr,
		getstrlen(nname), namestr,
		p2));
}

NODE *larity(NODE *args)
{
    NODE *arg = proc_name_arg(args);
    if (NOT_THROWING)
    {
        arg = intern(arg);
        load_procedure_if_necessary(arg);
        arg = procnode__caseobj(arg);
        if (is_prim(arg))
        {
            // This is a primitive
            FIXNUM min = getprimmin(arg);
            if (min < 0)
            {
                // This is a special form (TO or .MACRO) which
                // reads its inputs as its run.  As such, the
                // the notion of arity is meaningless.
                err_logo(SPECIAL_FORM_PROC_UNREC, car(args));
                return Unbound;
            }
            if (min == OK_NO_ARG)
            {
                min = 0;
            }

            return cons_list(
                make_intnode(min),
                make_intnode(getprimdflt(arg)),
                make_intnode(getprimmax(arg)));

        }
        else if (arg == UNDEFINED)
        {
            // Even after trying to load the procedure,
            // it's still not defined.
            err_logo(DK_HOW_UNREC, car(args));
            return Unbound;
        }
        else
        {
            // This is a user-defined procedure.
            return cons_list(
                minargs__procnode(arg),
                dfltargs__procnode(arg),
                maxargs__procnode(arg));
        }
    }

    return Unbound;
}


NODE *lcopydef(NODE *args)
{
    NODE * arg1 = proc_name_arg(args);
    NODE * arg2 = proc_name_arg(cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    arg1 = intern(arg1);
    arg2 = intern(arg2);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // load the procedure, in case we're copydef'ing a library routine
    NODE * new_proc = load_procedure_if_necessary(arg2);
    if (new_proc == UNDEFINED)
    {
        // the second input isn't the name of a procedure
        err_logo(DK_HOW, arg2);
        return Unbound;
    }

    bool redef = canRedefinePrimitives();
    if (!redef && is_prim(procnode__caseobj(arg1)))
    {
        // attempted to redefine a primitive
        err_logo(IS_PRIM, arg1);
        return Unbound;
    }

    NODE *old_proc = procnode__caseobj(arg1);
    if (old_proc != UNDEFINED)
    {
        // The first input was already defined as something,
        // so we must redefine it.
        untreeify_procnode(old_proc);

        int old_default = get_default_args_for_procedure(old_proc);
        int new_default = get_default_args_for_procedure(new_proc);

        if (old_default != new_default)
        {
            set_new_generation();
        }
    }

    if (!is_prim(new_proc))
    {
        // We are copying a user-defined function.
        // We must copy the body of the procedure, but change
        // the name of the procedure in the TO line,
        // or else the new procedure will have the same name
        // as the old procudure, which is confusing if the
        // function is ever printed out.
        NODE *bwds = get_bodywords(new_proc, arg1);
        new_proc = make_procnode(
            text__procnode(new_proc),
            cons(cpdf_newname(arg1,car(bwds)), cdr(bwds)),
            getint(minargs__procnode(new_proc)),
            getint(dfltargs__procnode(new_proc)),
            getint(maxargs__procnode(new_proc)));
    }

    // set the first input to have the same procedure as the second input
    setprocnode__caseobj(arg1, new_proc);

    setflag__caseobj(arg1, PROC_BURIED);
    if (is_macro(arg2)) 
    {
        setflag__caseobj(arg1, PROC_MACRO);
    }
    else 
    {
        clearflag__caseobj(arg1, PROC_MACRO);
    }

    return Unbound;
}

// Gets the names of all unburied procedures
NODE* get_all_proc_names()
{
    CAppendableList allProcedureNames;

    // Start by collecting the names of all procedures in LOGOLIB.
    wxArrayString libraryProcedureNames;
    wxDir::GetAllFiles(g_LibPathName, &libraryProcedureNames);
    for (wxArrayString::const_iterator i = libraryProcedureNames.begin();
         i != libraryProcedureNames.end();
         ++i)
    {
        // The string in the iterator is the full path.
        // The file name (without the path) is the name of the
        // procedure contained within.
        const wxFileName libraryFile(*i);
        const wxString & procedureNameString = libraryFile.GetFullName();
        const wchar_t * procedureName = /*WXSTRING_TO_STRING*/(procedureNameString);
        NODE * procedureNameNode;
        if (0 == wcscmp(procedureName, L"+rest"))
        {
            // There is one file in the LOGOLIB directory whose name doesn't
            // match the procedure that is defined within it because windows
            // file systems don't support file names with ? in them.  We
            // don't want to suggest that "+rest" as a valid command, so we
            // hard-code mapping it back to its real name.
            procedureNameNode = make_static_strnode(L"?rest");
        }
        else
        {
            procedureNameNode = make_strnode(procedureName);
        }

        // Add this library routine to the list of procedures.
        allProcedureNames.AppendElement(procedureNameNode);
    }

    // Next, collect all procedures that are included in
    // the global symbol table.
    for (int i = 0; i < HASH_LEN; i++)
    {
        for (NODE * nd = hash_table[i]; nd != NIL; nd = cdr(nd))
        {
            NODE * object = car(nd);

            // If this symbol has no associated procedure, then skip it.
            NODE * procnode = procnode__object(object);
            if (procnode__object(object) == UNDEFINED)
            {
                continue;
            }

            // Remove infix operators
            if (is_prim(procnode) && PREFIX_PRIORITY < getprimpri(procnode))
            {
                continue;
            }

            // If this symbol is buried, then skip it.
            // This should omit any LOGOLIB routine.
            if (flag__object(object,PROC_BURIED))
            {
                continue;
            }

            allProcedureNames.AppendElement(canonical__object(object));
        }
    }

    return mergesort(allProcedureNames.GetList(), true);
}

// Gets the names of all unburied non-local variables, including special variables.
NODE* get_all_variable_names()
{
    CAppendableList allVariableNames;

    // Start by collecting the names of all variables which have
    // special meaning, whether they are defined or not.
    static const CLocalizedNode * const specialVariables[] =
    {
        &Redefp,
        &Caseignoredp,
        &Erract,
        &Printdepthlimit,
        &Printwidthlimit,
        &Startup,
    };
    for (size_t i = 0; i < ARRAYSIZE(specialVariables); i++)
    {
        NODE * caseNode = specialVariables[i]->GetNode();
        allVariableNames.AppendElement(strnode__caseobj(caseNode));
    }


    // Next, collect all variables that are included in
    // the global symbol table.
    for (int i = 0; i < HASH_LEN; i++)
    {
        for (NODE * nd = hash_table[i]; nd != NIL; nd = cdr(nd))
        {
            NODE * object = car(nd);

            // If this symbol has no associated procedure, then skip it.
            if (valnode__object(object) == Unbound)
            {
                continue;
            }

            // If this symbol is buried, then skip it.
            if (flag__object(object, VAL_BURIED))
            {
                continue;
            }

            // Skip the special variables we added above.
            bool isSpecialVariable = false;
            NODE * canonicalName = canonical__object(object);
            for (size_t i = 0; i < ARRAYSIZE(specialVariables); i++)
            {
                NODE * specialVariableName = specialVariables[i]->GetNode();
                if (compare_node(canonicalName, specialVariableName, true) == 0)
                {
                    isSpecialVariable = true;
                    break;
                }
            }
            if (isSpecialVariable)
            {
                continue;
            }

            allVariableNames.AppendElement(canonicalName);
        }
    }

    return mergesort(allVariableNames.GetList(), true);
}
