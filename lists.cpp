/*
 *      lists.cpp       logo list functions module              dvb
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
   #include <math.h>
   #include <stdio.h>

   #include "logodata.h"
   #include "init.h"
   #include "eval.h"
   #include "error.h"
   #include "ibmterm.h"
   #include "logomath.h"
   #include "lists.h"
   #include "appendablelist.h"
   #include "graphics.h"
//   #include "debugheap.h"
#endif

static
NODE *bfable_arg(NODE *args)
{
    NODE *arg = car(args);

    while ((arg == NIL || arg == Unbound || arg == Null_Word ||
            nodetype(arg) == ARRAY) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }
    return arg;
}

static
NODE *firstable_arg(NODE *args)
{
    NODE *arg = car(args);

    while ((arg == NIL       ||  // empty list
            arg == Unbound   ||  // uninitialized
            arg == Null_Word ||  // empty string
            (nodetype(arg) == ARRAY && getarrdim(arg) == 0))  // empty array
           && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }

    return arg;
}

NODE *list_arg(NODE *args)
{
    NODE *arg = car(args);

    while (arg != NIL && !is_list(arg) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }
    return arg;
}

NODE *lbutfirst(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = bfable_arg(args);
    if (NOT_THROWING)
    {
        if (is_list(arg))
        {
            val = cdr(arg);
        }
        else
        {
            setcar(args, cnv_node_to_strnode(arg));
            arg = car(args);
            if (getstrlen(arg) > 1)
            {
                val = make_strnode(
                    getstrptr(arg) + 1,
                    getstrlen(arg) - 1,
                    nodetype(arg),
                    strnzcpy);
            }
            else
            {
                val = Null_Word;
            }
        }
    }
    return val;
}

NODE *lbutlast(NODE *args)
{
    NODE *val = Unbound, *lastnode, *tnode;

    NODE * arg = bfable_arg(args);
    if (NOT_THROWING)
    {
        if (is_list(arg))
        {
            args = arg;
            val = NIL;
            while (cdr(args) != NIL)
            {
                tnode = cons_list(car(args));
                if (val == NIL)
                {
                    val = tnode;
                    lastnode = tnode;
                }
                else
                {
                    setcdr(lastnode, tnode);
                    lastnode = tnode;
                }
                args = cdr(args);
                if (check_throwing) 
                {
                    break;
                }
            }
        }
        else
        {
            setcar(args, cnv_node_to_strnode(arg));
            arg = car(args);
            if (getstrlen(arg) > 1)
            {
                val = make_strnode(
                    getstrptr(arg),
                    getstrlen(arg) - 1,
                    nodetype(arg),
                    strnzcpy);
            }
            else
            {
                val = Null_Word;
            }
        }
    }
    return val;
}

NODE *lfirst(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = firstable_arg(args);
    if (NOT_THROWING)
    {
        if (nodetype(arg) == ARRAY)
        {
            // arg is an array -- output the origin
            val = make_intnode((FIXNUM) getarrorg(arg));
        }
        else if (is_list(arg))
        {
            // arg is a list -- output the first item
            val = car(arg);
        }
        else
        {
            // arg is a string -- output a string of the first character
            setcar(args, cnv_node_to_strnode(arg));
            arg = car(args);
            val = make_strnode(getstrptr(arg), 1, nodetype(arg), strnzcpy);
        }
    }

    return val;
}

NODE *lfirsts(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = list_arg(args);
    if (car(args) == NIL)
    {
        return NIL;
    }
    if (NOT_THROWING)
    {
        val = cons_list(lfirst(arg));
        NODE * tail = val;
        for (NODE * argp = cdr(arg); argp != NIL; argp = cdr(argp))
        {
            setcdr(tail, cons_list(lfirst(argp)));
            tail = cdr(tail);
            if (check_throwing)
            {
                break;
            }
        }
        if (stopping_flag == THROWING)
        {
            gcref(val);
            return Unbound;
        }
    }
    return val;
}

NODE *lbfs(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = list_arg(args);
    if (car(args) == NIL) 
    {
        return NIL;
    }
    if (NOT_THROWING)
    {
        val = cons_list(lbutfirst(arg));
        NODE * tail = val;
        for (NODE * argp = cdr(arg); argp != NIL; argp = cdr(argp))
        {
            setcdr(tail, cons_list(lbutfirst(argp)));
            tail = cdr(tail);
            if (check_throwing) 
            {
                break;
            }
        }
        if (stopping_flag == THROWING)
        {
            gcref(val);
            return Unbound;
        }
    }
    return val;
}

NODE *llast(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = bfable_arg(args);
    if (NOT_THROWING)
    {
        if (is_list(arg))
        {
            args = arg;
            while (cdr(args) != NIL)
            {
                args = cdr(args);
                if (check_throwing) 
                {
                    break;
                }
            }
            val = car(args);
        }
        else
        {
            setcar(args, cnv_node_to_strnode(arg));
            arg = car(args);
            val = make_strnode(
                getstrptr(arg) + getstrlen(arg) - 1,
                1, 
                nodetype(arg),
                strnzcpy);
        }
    }
    return val;
}

NODE *llist(NODE *args)
{
    return args;
}

NODE *lemptyp(NODE *arg)
{
    return true_or_false(car(arg) == NIL || car(arg) == Null_Word);
}

static
NODE *char_arg(NODE *args)
{
    NODE * arg = car(args);
    NODE * val = cnv_node_to_strnode(arg);
    while ((val == Unbound || getstrlen(val) != 1) && NOT_THROWING)
    {
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
        val = cnv_node_to_strnode(arg);
    }
    setcar(args, val);
    return val;
}

NODE *lascii(NODE *args)
{
    NODE * val = Unbound;

    NODE * arg = char_arg(args);
    if (NOT_THROWING)
    {
        FIXNUM i = (FIXNUM) ecma_clear(*getstrptr(arg)) & 0xFF;
        val = make_intnode(i);
    }
    return val;
}

NODE *lrawascii(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = char_arg(args);
    if (NOT_THROWING)
    {
        // must be cast to unsigned or this can return a negative number
		//NOTICE: changed here
        unsigned int i = *reinterpret_cast<const wchar_t*>(getstrptr(arg));
        val = make_intnode(i);
    }
    return val;
}

NODE *lbackslashedp(NODE *args)
{
    NODE * arg = char_arg(args);
    if (NOT_THROWING)
    {
        wchar_t i = *getstrptr(arg);
        return true_or_false(ecma_get(i));
    }
    return Unbound;
}

NODE *lchar(NODE *args)
{
    NODE *val = Unbound;

    NODE * arg = nonnegative_int_arg(args);
    if (NOT_THROWING)
    {
        wchar_t c = getint(arg);
        val = make_strnode(
            &c, 
            1,
            (ecma_get(c) ? STRING : BACKSLASH_STRING), 
            strnzcpy);
    }
    return val;
}

NODE *lcount(NODE *args)
{
    int cnt = 0;

    NODE* arg = car(args);
    if (arg != NIL && arg != Null_Word)
    {
        if (is_list(arg))
        {
            args = arg;
            for (; args != NIL; cnt++)
            {
                args = cdr(args);
                if (check_throwing) 
                {
                    break;
                }
            }
        }
        else if (nodetype(arg) == ARRAY)
        {
            cnt = getarrdim(arg);
        }
        else
        {
            setcar(args, cnv_node_to_strnode(arg));
            cnt = getstrlen(car(args));
        }
    }
    return make_intnode((FIXNUM) cnt);
}

NODE *lfput(NODE *args)
{
    NODE * arg = car(args);
    NODE * lst = list_arg(cdr(args));
    if (NOT_THROWING)
    {
        return cons(arg, lst);
    }
    else
    {
        return Unbound;
    }
}

NODE *llput(NODE *args)
{
    NODE * newtail = car(args);
    NODE * lst = list_arg(cdr(args));
    if (stopping_flag == THROWING)
    {
        // something is wrong with the inputs
        return Unbound;
    }

    // copy the list
    NODE * lastnode = NIL;
    NODE * val = NIL;

    while (lst != NIL)
    {
        NODE * tnode = cons_list(car(lst));
        if (val == NIL)
        {
            val = tnode;
        }
        else
        {
            setcdr(lastnode, tnode);
        }
        lastnode = tnode;
        lst = cdr(lst);
        if (check_throwing) 
        {
            break;
        }
    }

    // append the new tail element
    if (val == NIL)
    {
        val = cons_list(newtail);
    }
    else
    {
        setcdr(lastnode, cons_list(newtail));
    }

    return val;
}

NODE *string_arg(NODE *args)
{
    NODE *arg = car(args);

    NODE * val = cnv_node_to_strnode(arg);
    while (val == Unbound && NOT_THROWING)
    {
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
        val = cnv_node_to_strnode(arg);
    }
    setcar(args, val);
    return val;
}

NODE *lword(NODE *args)
{

    if (args == NIL)
    {
        return Null_Word;
    }

    int length = 0;
    NODETYPES str_type = STRING;
    NODE * val = args;
    while (val != NIL && NOT_THROWING)
    {
        NODE * arg = string_arg(val);
        if (NOT_THROWING)
        {
            if (backslashed(arg))
            {
                str_type = VBAR_STRING;
            }
            length += getstrlen(arg);
        }
         
        val = cdr(val);
    }

    if (NOT_THROWING)
    {
        val = make_strnode_from_wordlist(args, length, str_type);
    }
    else
    {
        val = Unbound;
    }

    return val;
}

NODE *lsentence(NODE *args)
{
    CAppendableList sentence;

    while (args != NIL && NOT_THROWING)
    {
        NODE * arg = car(args);

        while (nodetype(arg) == ARRAY && NOT_THROWING)
        {
            setcar(args, err_logo(BAD_DATA, arg));
            arg = car(args);
        }

        args = cdr(args);
        if (stopping_flag == THROWING) 
        {
            break;
        }

        if (is_list(arg))
        {
            // arg is a list.
            // Append each element in the list, instead of appending
            // the list so that we don't change the input.
            while (arg != NIL && NOT_THROWING)
            {
                sentence.AppendElement(car(arg));

                arg = cdr(arg);
            }
        }
        else
        {
            // arg must be a word
            sentence.AppendElement(arg);
        }
    }

    if (stopping_flag == THROWING)
    {
        gcref(sentence.GetList());
        return Unbound;
    }

    return sentence.GetList();
}

NODE *lwordp(NODE *arg)
{
    arg = car(arg);
    return true_or_false(arg != Unbound && !is_aggregate(arg));
}

NODE *llistp(NODE *arg)
{
    arg = car(arg);
    return true_or_false(is_list(arg));
}

NODE *lnumberp(NODE *arg)
{
    setcar(arg, cnv_node_to_numnode(car(arg)));
    return true_or_false(car(arg) != Unbound);
}

NODE *larrayp(NODE *arg)
{
    return true_or_false(nodetype(car(arg)) == ARRAY);
}

static
NODE *memberp_helper(NODE *args, bool notp, bool substr)
{
    bool caseig = isCaseIgnored();

    NODE * obj1 = car(args);
    NODE * obj2 = cadr(args);
    if (is_list(obj2))
    {
        if (substr)
        {
            return Falsex.GetNode();
        }

        while (obj2 != NIL && NOT_THROWING)
        {
            if (equalp_help(obj1, car(obj2), caseig))
            {
                return notp ? obj2 : Truex.GetNode();
            }
            obj2 = cdr(obj2);
            if (check_throwing)
            {
                break;
            }
        }
        return notp ? NIL : Falsex.GetNode();
    }
    else if (nodetype(obj2) == ARRAY)
    {
        int len = getarrdim(obj2);
        NODE **data = getarrptr(obj2);

        if (notp)
        {
            err_logo(BAD_DATA_UNREC, obj2);
        }

        if (substr)
        {
            return Falsex.GetNode();
        }

        while (--len >= 0 && NOT_THROWING)
        {
            if (equalp_help(obj1, *data++, caseig))
            {
                return Truex.GetNode();
            }
        }
        return Falsex.GetNode();
    }
    else
    {
        if (is_aggregate(obj1))
        {
            return (notp ? Null_Word : Falsex.GetNode());
        }

        setcar(cdr(args), cnv_node_to_strnode(obj2));
        obj2 = cadr(args);

        setcar(args, cnv_node_to_strnode(obj1));
        obj1 = car(args);

        if (obj1 != Unbound &&
            obj2 != Unbound &&
            getstrlen(obj1) <= getstrlen(obj2) &&
            (substr || (getstrlen(obj1) == 1)))
        {
            // how many different places are there to compare obj1 in obj2
            int leng = getstrlen(obj2) - getstrlen(obj1);

            // create a copy of obj2 with obj1's length so that we can
            // quicky extract all potential matches of obj1 within obj2
            // REVISIT: why modify args?  why not just keep tmp separate?
            setcar(
                cdr(args),
                make_strnode(getstrptr(obj2), getstrlen(obj2), nodetype(obj2), strnzcpy));

            NODE * tmp = cadr(args);
            setstrlen(tmp, getstrlen(obj1));
            for (int i = 0; i <= leng; i++)
            {
                if (equalp_help(obj1, tmp, caseig))
                {
                    if (notp)
                    {
                        setstrlen(tmp, leng + getstrlen(obj1) - i);
                        return tmp;
                    }
                    else
                    {
                        return Truex.GetNode();
                    }
                }
                // Slide the potential string match down one byte.
                // Note that the string length remains the same.
                setstrptr(tmp, getstrptr(tmp) + 1);
            }
        }
        return notp ? Null_Word : Falsex.GetNode();
    }
}

NODE *lmemberp(NODE *args)
{
    return memberp_helper(args, false, false);
}

NODE *lsubstringp(NODE *args)
{
    return memberp_helper(args, false, true);
}

NODE *lmember(NODE *args)
{
    return memberp_helper(args, true, false);
}

// If the first element in args can be interpreted as an integer
// then it is changed into an integer node and returned.
// Otherwise, the stopping_flag is set to THROWING.
NODE *integer_arg(NODE *args)
{
    NODE *arg = car(args);

    NODE * val = cnv_node_to_intnode(arg);
    while (val == Unbound && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
        val = cnv_node_to_intnode(arg);
    }

    setcar(args, val);
    if (nodetype(val) == INTEGER) 
    {
        return val;
    }

    return Unbound;
}

// If the first element in args can be interpreted as an integer
// within the specified range, then it is changed into an integer
// node and returned.
// Otherwise the programmer is given a chance to correct it with ERRACT.
NODE *ranged_integer_arg(NODE *args, int MinValue, int MaxValue)
{
    while (NOT_THROWING)
    {
        NODE * arg = car(args);
        NODE * val = cnv_node_to_intnode(arg);

        if (nodetype(val) == INTEGER &&
            MinValue <= getint(val) && getint(val) <= MaxValue)
        {
            // This is an integer within the requested range.
            // Update the arguments with the new node and return it.
            setcar(args, val);
            return val;
        }

        // grab a new value from ERRACT and try again
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
    }

    return Unbound;
}

// Returns an integer node if args can be interpreted as a non-negative integer.
// otherwise sets an error in args and returns Unbound.
NODE *nonnegative_int_arg(NODE *args)
{
    return ranged_integer_arg(args, 0, FIXNUM_MAX);
}

// Returns an integer node if args can be interpreted as a positive integer.
// otherwise sets an error in args and returns Unbound.
NODE *positive_int_arg(NODE *args)
{
    return ranged_integer_arg(args, 1, FIXNUM_MAX);
}

FIXNUM int_arg(NODE *args)
{
    NODE *arg = integer_arg(args);

    if (NOT_THROWING) 
    {
        return getint(arg);
    }
    return 0;
}

NODE *litem(NODE *args)
{
    NODE * obj = cadr(args);
    while ((obj == NIL || obj == Null_Word) && NOT_THROWING)
    {
        setcar(cdr(args), err_logo(BAD_DATA, obj));
        obj = cadr(args);
    }

    NODE * val = integer_arg(args);
    while (NOT_THROWING)
    {
        int i = getint(val);
        if (is_list(obj))
        {
            if (i <= 0)
            {
                // all list indices must be positive
                setcar(args, err_logo(BAD_DATA, car(args)));
                val = integer_arg(args);
                continue;
            }

            // advance item to the ith element in obj
            NODE * item = obj;
            while (--i > 0)
            {
                item = cdr(item);
                if (item == NIL)
                {
                    // reached the end of the list
                    break;
                }
            }

            if (item == NIL)
            {
                // the index goes beyond the length of the list
                setcar(args, err_logo(BAD_DATA, car(args)));
                val = integer_arg(args);
                continue;
            }

            return car(item);
        }
        else if (nodetype(obj) == ARRAY)
        {
            i -= getarrorg(obj);
            if (i < 0 || i >= getarrdim(obj))
            {
                // i is out of range
                setcar(args, err_logo(BAD_DATA, car(args)));
                val = integer_arg(args);
                continue;
            }
            return getarrptr(obj)[i];
        }
        else
        {
            // we will treat obj as a word
            if (i <= 0)
            {
                // letters of a word are 1-indexed
                setcar(args, err_logo(BAD_DATA, car(args)));
                val = integer_arg(args);
                continue;
            }
            setcar(cdr(args), cnv_node_to_strnode(obj));
            obj = cadr(args);
            if (i > getstrlen(obj))
            {
                // letters of a word are 1-indexed
                setcar(args, err_logo(BAD_DATA, car(args)));
                val = integer_arg(args);
                continue;
            }
            return make_strnode(
                getstrptr(obj) + i - 1,
                1, 
                nodetype(obj), 
                strnzcpy);
        }
    }
    return Unbound;
}

static
bool circular(NODE *arr, NODE *newx)
{
    if (newx == NIL) 
    {
        return false;
    }
    else if (nodetype(newx) == ARRAY)
    {
        int i = getarrdim(newx);
        NODE **p = getarrptr(newx);

        if (newx == arr) 
        {
            return true;
        }
        while (--i >= 0)
        {
            if (circular(arr, *p++)) 
            {
                return true;
            }
        }
        return false;
    }
    else if (is_list(newx))
    {
        while (newx != NIL)
        {
            if (circular(arr, car(newx)))
            {
                return true;
            }
            newx = cdr(newx);
        }
        return false;
    }
    else 
    {
        return false;
    }
}

static
NODE *setitem_helper(NODE *args, bool safe)
{
    NODE * val = integer_arg(args);
    NODE * obj = cadr(args);
    while (nodetype(obj) != ARRAY && NOT_THROWING)
    {
        setcar(cdr(args), err_logo(BAD_DATA, obj));
        obj = cadr(args);
    }

    NODE * cont = car(cddr(args));
    if (NOT_THROWING)
    {
        int i = getint(val);
        if (safe)
        {
            while (circular(obj, cont) && NOT_THROWING)
            {
                setcar(cddr(args), err_logo(BAD_DATA, cont));
                cont = car(cddr(args));
            }
        }
        if (NOT_THROWING)
        {
            i -= getarrorg(obj);
            if (i < 0 || i >= getarrdim(obj))
            {
                err_logo(BAD_DATA_UNREC, val);
            }
            else
            {
                val = (getarrptr(obj))[i];
                (getarrptr(obj))[i] = vref(cont);
                deref(val);
            }
        }
    }
    return Unbound;
}

NODE *lsetitem(NODE *args)
{
    return setitem_helper(args, true);
}

NODE *l_setitem(NODE *args)
{
    return setitem_helper(args, false);
}

NODE *larray(NODE *args)
{
    int o;

    NODE * arg = nonnegative_int_arg(args);
    if (cdr(args) != NIL)
    {
        o = int_arg(cdr(args));
    }
    else 
    {
        o = 1;
    }

    if (NOT_THROWING)
    {
        int d = getint(arg);
        arg = make_array(d);

        if (NOT_THROWING)
        {
            setarrorg(arg, o);
            return arg;
        }
    }
    return Unbound;
}

FLONUM float_arg(NODE *args)
{
    for (;;)
    {
        NODE *arg = car(args);
        NODE *val = cnv_node_to_numnode(arg);

        if (stopping_flag == THROWING)
        {
            // Encountered an error.  Stop processing.
            return 0.0;
        }

        if (is_number(val))
        {
            // got a number, just like we wanted
            FLONUM value = numeric_node_to_flonum(val);
            gcref(val);
            return value;
        }

        // try to get a new value from ERRACT
        gcref(val);
        setcar(args, err_logo(BAD_DATA, arg));
    }

    // shouldn't be reachable
    return 0.0;
}

NODE *lform(NODE *args)
{
    FLONUM number = float_arg(args);

    NODE * width_arg = cdr(args);
    int    width = (int) int_arg(width_arg);
    if (width < 0)
    {
        NODE * error_node = err_logo(BAD_DATA, car(width_arg));
        setcar(args, error_node);
        return Unbound;
    }

    int precision = (int) int_arg(cddr(args));

    if (NOT_THROWING)
    {
		//FIXED
		//wchar_t result[100] = { 0 };
      
        // Take care not to overflow the buffer
        //if (width >= sizeof(result))
        //{
        //    width = sizeof(result) - 1;
        //}
        //if (precision > sizeof(result))
        //{
        //    precision = sizeof(result) - 1;
        //}

        //wsprintf(result, L"%*.*f", width, precision, number);

        return make_strnode(wxString::Format(L"%*.*f", width, precision, number));
    }

    return Unbound;
}

NODE *l_setfirst(NODE *args)
{
    NODE * list = car(args);
    NODE * newval = cadr(args);
    while (NOT_THROWING && (list == NIL || !is_list(list)))
    {
        setcar(args, err_logo(BAD_DATA, list));
        list = car(args);
    }

    if (NOT_THROWING)
    {
        setcar(list, newval);
    }

    return Unbound;
}

NODE *l_setbf(NODE *args)
{
    NODE * list = car(args);
    NODE * newval = cadr(args);
    while (NOT_THROWING && (list == NIL || !is_list(list)))
    {
        setcar(args, err_logo(BAD_DATA, list));
        list = car(args);
    }

    if (NOT_THROWING)
    {
        setcdr(list, newval);
    }

    return Unbound;
}
