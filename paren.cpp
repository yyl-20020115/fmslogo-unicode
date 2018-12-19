/*
 *      paren.cpp            logo parenthesizing module          dko
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
    #include "paren.h"
    #include "logodata.h"
    #include "eval.h"
    #include "init.h"
    #include "error.h"
    #include "lists.h"
    #include "logomath.h"
    #include "appendablelist.h"
    #include "logocore.h"
    #include "debugheap.h"
#endif

NODE *the_generation;
bool tree_dk_how;

static NODE *gather_args(NODE *proc, NODE **args, bool inparen, NODE **ifnode);
static NODE *paren_infix(NODE *left_arg, NODE **rest, int old_pri, bool inparen);

// Set the line pointer for a tree.
static
void make_line(NODE *tree, NODE *line)
{
    setobject(tree, line);
    settype(tree, LINE);
}

static
void untreeify(NODE *node)
{
    settreepair__tree(node, NIL);
    settype(node, CONS);
}

static
void untreeify_line(NODE *line)
{
    if (line != NIL && is_list(line))
    {
        untreeify_line(car(line));
        untreeify_line(cdr(line));
        untreeify(line);
    }
}

void untreeify_body(NODE *body)
{
    NODE *body_ptr;

    for (body_ptr = body; body_ptr != NIL; body_ptr = cdr(body_ptr))
    {
        untreeify_line(car(body_ptr));
    }
    untreeify(body);
}

// Treeify a procedure's bodylines by appending the trees of the lines.
//
// is_tree(body) will return zero on error and if all body lines were empty.
// is_tree(body) will return non-zero if the body was treeified and there was
// at least one non-empty line within the body.
void treeify_body(NODE *body)
{
    if (body == NIL ||
        (is_tree(body) && generation__tree(body) == the_generation))
    {
        return;
    }

    if (is_tree(body)) 
    {
        // The definition of something has changed.
        // We must re-treeify this body in case it calls the 
        // procedure which changed.
        assert(generation__tree(body) != the_generation);
        untreeify_body(body);
    }

    NODE *treelist_end = NIL;
    for (NODE * body_ptr = body; body_ptr != NIL; body_ptr = cdr(body_ptr))
    {
        NODE * line = car(body_ptr);
        if (line == NIL)
        {
            // skip blank lines or else we'd error out at is_tree()
            continue;
        }

        // store the current line (for error reporting)
        assign(this_line, line);

        // tree-ify this line
        treeify_line(line);
        if (is_tree(line))
        {
            NODE * tree = tree__tree(line);
            make_line(tree, line);

            // append the treeified line to the end of body's tree list
            if (treelist_end == NIL)
            {
                settree__tree(body, tree);
            }
            else
            {
                setcdr(treelist_end, tree);
            }

            // If the current line needs to be re-treeified later, then
            // flag the firt line in the tree as needing to be re-treeified.
            if (generation__tree(line) == Unbound)
            {
                setgeneration__tree(body, Unbound);
            }

            // advance treelist_end to the end of body's tree list
            while (cdr(tree) != NIL)
            {
                tree = cdr(tree);
            }
            treelist_end = tree;
        }
        else
        {
            // error while treeifying 
            untreeify(body);
            return;
        }
    }

    if (treelist_end != NIL)
    {
        // body can not be considered "treeified" unless there was at least one
        // line to treeify so that treepair__tree() is not NIL.
        // To a caller that only checks the status of this function by calling
        // is_tree(body), this looks the same as an error.
        // This is okay because the evaulator considers a treeification error
        // the same as a body consisting of only empty lines
        // (there's nothing to evaulate in either case).
        //
        // REVISIT: Fix the evaluator to handle when
        //     is_tree(body) && treepair__tree(body)==NIL
        // so that we can more clearly distinguish between the error case and
        // the "empty tree" case.
        settype(body, TREE);
    }
}


// Parenthesize an expression. 
// Set expr to the node after the first full expression.
static
NODE *paren_expr(NODE **expr, bool inparen)
{
    if (*expr == NIL)
    {
        if (inparen) 
        {
            err_logo(PAREN_MISMATCH, NIL);
        }
        return NIL;
    }

    NODE *retval;

    // REVISIT: do we really need to ref and deref first?
    NODE * first = vref(car(*expr));
    pop(*expr);
    if (nodetype(first) == CASEOBJ && !numberp(first))
    {
        if (first == Left_Paren)
        {
            deref(first);

            // Parse this sub-expression.
            NODE * tree = paren_expr(expr, true);
            tree = paren_infix(tree, expr, -1, true);

            if (*expr == NIL)
            {
                err_logo(PAREN_MISMATCH, NIL);
            }
            else if (car(*expr) != Right_Paren)
            {
                // There was a problem parenthesizing expr.
                NODE * proc = car(tree);
                if (nodetype(proc) != CASEOBJ ||
                    procnode__caseobj(proc) == Unbound)
                {
                    // The procedure is not defined, so we don't know
                    // how many parameters it takes.
                    err_logo(DK_HOW_UNREC, proc);
                }
                else
                {
                    // There were too many inputs.
                    err_logo(TOO_MUCH, NIL);
                }
            }
            else
            {
                pop(*expr);
            }
            retval = tree;
        }
        else if (first == Right_Paren)
        {
            deref(first);
            err_logo(UNEXPECTED_PAREN, NIL);
            if (inparen) 
            {
                push(first, *expr);
            }
            retval = NIL;
        }
        else if (first == Minus_Sign)
        {
            // pretend that -X is really 0 - X
            deref(first);
            push(Minus_Tight, *expr);
            retval = paren_infix(make_intnode(0), expr, -1, inparen);
        }
        else
        {
            // it must be a procedure
            NODE * proc = load_procedure_if_necessary(first);
            if (proc == UNDEFINED)
            {
                // Even after attempting a silent load of
                // the procedure, it couldn't be defined.
                retval = cons_list(first);
                tree_dk_how = true;
            }
            else if (nodetype(proc) == INFIX && NOT_THROWING)
            {
                // If proc is an infix operator, then an operand should
                // have come before it, but didn't.
                // This makes sure that 5**6 says "not enough inputs to *"
                err_logo(NOT_ENOUGH, first);
                retval = cons_list(first);
            }
            else
            {
                NODE **ifnode = (NODE **) NIL;

                if (compare_node(first, If, true) == 0)
                {
                    // Kludge: turn IF to IFELSE sometimes.
                    ifnode = &first;
                }

                // update "fun" in case this is a special form (TO or .MACRO)
                // and can encounter an error within gather_args().
                // This allows proper error reporting if fun receives bad input.
                assign(fun, first);

                retval = gather_args(proc, expr, inparen, ifnode);
                if (retval != Unbound)
                {
                    retval = cons(first, retval);
                }
            }
            deref(first);
        }
    }
    else if (is_list(first))
    {
        /* quoted list */
        retval = make_quote(first);
        deref(first);
    }
    else
    {
        unref(first);
        return first;
    }
    return retval;
}

// Fully parenthesize a complete line.
// i.e. transform it from a flat list to a tree.
static
NODE *paren_line(NODE *line)
{
    CAppendableList parenthesizedLine;

    while (line != NIL)
    {
        NODE * addition = paren_expr(&line, false);
        if (stopping_flag == THROWING || addition == Unbound)
        {
            // Something went wrong. 
            // For example, a syntax error was detected.
            // Clean up whatever hasn't been consumed.
            deref(line);
            gcref(addition);
            gcref(parenthesizedLine.GetList());
            return Unbound;
        }

        addition = paren_infix(addition, &line, -1, false);
        parenthesizedLine.AppendElement(addition);
    }

    return parenthesizedLine.GetList();
}


static
bool
gather_more_args(
    NODE *  RemainingArguments
    )
{
    if (RemainingArguments == NIL)
    {
        // no more arguments in the list
        return false;
    }
    if (car(RemainingArguments) == Right_Paren)
    {
        // we hit a right-paren (which ends this)
        return false;
    }
    if (nodetype(car(RemainingArguments)) == CASEOBJ &&
        nodetype(procnode__caseobj(car(RemainingArguments))) == INFIX)
    {
        // we hit an infix procedure, which indicates the end of the inputs
        return false;
    }

    return true;
}

// Make a list of the next n expressions, where n is between min and max.
// Set args to immediately after the last expression.
NODE *gather_some_args(int min, int max, NODE **args, bool inparen, NODE **ifnode)
{
    CAppendableList inputs;

    while (gather_more_args(*args))
    {
        if (max == 0)
        {
            if (ifnode != (NODE **) NIL && is_list(car(*args)))
            {
                /* if -> ifelse kludge */
                err_logo(IF_WARNING, NIL);
                assign(*ifnode, Ifelse);
            }
            else
            {
                // we have gathered enough arguments
                break;
            }
        }
        else
        {
            if (max < 0) 
            { 
                // negative max means unlimited 
                max = 0;
            }

            min--;
            max--;
        }

        NODE *nextinput = paren_expr(args, false);
        nextinput = paren_infix(nextinput, args, -1, inparen);

        inputs.AppendElement(nextinput);
    }

    if (min > 0)
    {
        // We weren't able to find enough inputs.
        gcref(inputs.GetList());

        // Set a special marker at this point in the parse
        // tree so that evaluator() knows to report the error.        
        return cons_list(g_ParseErrorNotEnoughInputs);
    }

    return inputs.GetList();
}

// Gather the correct number of inputs to proc starting at *args.
// Upon exit, this sets *args to immediately after the last arg.
// If inparen is true, then *args is set to Right_Paren.
//
// ifnode is a hack that allows for IF->IFELSE conversion.
// If proc is IF, then *ifnode is a pointer to the proc.
// If it should be an IFELSE, then *ifnode is changed to IfElse.
static
NODE *gather_args(NODE *proc, NODE **args, bool inparen, NODE **ifnode)
{
    int min, max;

    if (nodetype(proc) == CONS)
    {
        // user-defined procedure
        min = (inparen ? getint(minargs__procnode(proc))
               : getint(dfltargs__procnode(proc)));
        max = (inparen ? getint(maxargs__procnode(proc))
               : getint(dfltargs__procnode(proc)));
    }
    else
    {
        // primitive
        min = (inparen ? getprimmin(proc) : getprimdflt(proc));
        if (min < 0)
        {
            // Special form (either TO or .MACRO)
            // Invoking the primitive gathers its arguments.
            return ((logofunc) *getprimfun(proc)) (*args);
        }

        if (getprimmin(proc) == OK_NO_ARG) 
        {
            // Kludge: allow EDIT and CO without input without paren 
            min = 0;
        }

        max = (inparen ? getprimmax(proc) : getprimdflt(proc));
    }

    return gather_some_args(min, max, args, inparen, ifnode);
}

// Treeify a list of tokens (runparsed or not).
// This essentially tokenizes the list and builds a parse tree according
// to how many inputs each procedure currently expects.
//
// On success is_tree(newtree) will be non-zero.
// On some errors, stopping_node is set to THROWING.
//
// Note that NIL cannot be tree'ified, but it can be run.
void treeify_line(NODE *newtree)
{
    if (newtree == NIL ||
        (is_tree(newtree) && generation__tree(newtree) == the_generation))
    {
        // already a tree
        return;
    }

    // make sure the tree-to-be is runparsed
    if (!runparsed(newtree)) 
    {
        make_runparse(newtree);

        // must reference parsed_node because paren_line() derefs it
        ref(parsed__runparse(newtree));
    }

    tree_dk_how = false;
    NODE * childtree = paren_line(parsed__runparse(newtree));
    if (childtree != NIL && childtree != Unbound)
    {
        settype(newtree, TREE);
        settree__tree(newtree, childtree);

        if (tree_dk_how || stopping_flag == THROWING)
        {
            // make sure this gets re-treeified later
            setgeneration__tree(newtree, Unbound);
        }
    }
    else
    {
        // cleanup on error
        untreeify_line(newtree);
    }
}


// Calculate the priority of a procedure.
static
int priority(NODE *proc_obj)
{
    if (proc_obj == Minus_Tight)
    {
        return PREFIX_PRIORITY + 4;
    }

    NODE *proc;
    if (nodetype(proc_obj) != CASEOBJ ||
        (proc = procnode__caseobj(proc_obj)) == UNDEFINED ||
        nodetype(proc) != INFIX)
    {
        return STOP_PRIORITY;
    }

    return is_prim(proc) ? getprimpri(proc) : PREFIX_PRIORITY;
}

// Parenthesize an infix expression.
// left_arg is the expression on the left (already parenthesized).
// rest is a pointer to the list starting with the infix procedure, if it's there.
// Set rest to after the right end of the infix expression.
static 
NODE *paren_infix(NODE *left_arg, NODE **rest, int old_pri, bool inparen)
{
    while (*rest != NIL) // not end of expression
    {
        NODE * infix_proc = car(*rest);
        int    new_pri    = priority(infix_proc);

        if (new_pri == STOP_PRIORITY || new_pri <= old_pri)
        {
            // We've either encountered a non-infix procedure
            // or infix_proc has a higher priority than previous node.
            // Either way, we want to stop.
            break;
        }

        if (cdr(*rest) == NIL)
        {
            // we have an infix procedure without a right operand.
            err_logo(NOT_ENOUGH, infix_proc);
            break;
        }

        ref(infix_proc);
        pop(*rest);

        // parenthesize the right input
        NODE * right_arg = paren_expr(rest, inparen);
        right_arg = paren_infix(right_arg, rest, new_pri, inparen);

        // change the infix notation to prefix notation
        right_arg = cons_list(infix_proc, left_arg, right_arg);

        deref(infix_proc);

        // move on to the next possible infix expression
        left_arg = right_arg;
    }

    return left_arg;
}
