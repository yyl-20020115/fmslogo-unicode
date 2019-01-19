/*
*      eval.cpp          logo eval/apply module                  dko
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
   #include <stdio.h>
   #include <setjmp.h>
   #include <stdlib.h> // abort()
   #include <string.h>

   #include <wx/window.h>

   #include "eval.h"
   #include "FMSLogo.h"
   #include "init.h"
   #include "files.h"
   #include "graphwin.h"
   #include "logocore.h"
   #include "logodata.h"
   #include "mem.h"
   #include "error.h"
   #include "print.h"
   #include "logomath.h"
   #include "coms.h"
   #include "paren.h"
   #include "status.h"
   #include "ibmterm.h"
   #include "localizedstrings.h"
   #include "wrksp.h"
   #include "parse.h"
   #include "unix.h"
   #include "intern.h"
   #include "lists.h"
   #include "startup.h"
   #include "stringadapter.h"
   #include "screenwindow.h"
//   #include "debugheap.h"
#endif

extern void DoEvents();

inline
bool
IsInMacro(
    FIXNUM ValueStatus
    )
{
    return 
        ValueStatus == VALUE_STATUS_NoValueInMacro ||
        ValueStatus == VALUE_STATUS_ValueMaybeOkInMacro;
}

NODE *fun = NIL;                 // current function name
NODE *ufun = NIL;                // current user-defined function name
NODE *last_ufun = NIL;           // the function that called this one
NODE *this_line = NIL;           // the current instruction line
NODE *last_line = NIL;           // the line that called this one
NODE *last_call = NIL;           // the last proc called
NODE *didnt_output_name = NIL;   // the name of the proc that didn't OP
NODE *didnt_get_output = NIL;    // the name of the proc that wanted the OP
NODE *output_node = NIL;         // the output of the current function
FIXNUM repcountup = 0;               // up count for repeat

CTRLTYPE stopping_flag = RUN;
FIXNUM tailcall;    // 0 in sequence, 1 for tail, -1 for arg

FIXNUM g_ValueStatus;

FIXNUM dont_fix_ift = 0;

long long eval_count = 0;        // current count of "evaluations" calls

int g_CatchErrorCount = 0;       // the number of nested blocks of CATCH "ERROR
                                 // This is used to disable "ERRACT processing.

bool traceflag = false;          // Flag to signal trace button is active
bool stepflag = false;           // Flag to signal step button is active

static NODE *qm_list = NIL;      // question mark list
static int trace_level = 0;      // indentation level when tracing

static NODE *var       = NIL;    // frame pointer into var_stack
static NODE *var_stack = NIL;    // The stack of local variables and their
                                 // bindings.
                                 //   car is the case object (variable name).
                                 //   obj is the variable's value.
                                 //   cdr is the next variable in the stack.

static int halt_flag = 0;        // Flag to signal it's OK to halt.
                                 // This is the number of nested evaluations
                                 // that are happening.


// Load the definition of ProcNode if the definition of ProcNode
// is currently UNDEFINED.
//
// Return the case object of ProcNode, if successful.
// Return UNDEFINED, otherwise.
NODE *
load_procedure_if_necessary(
    NODE * ProcNode
    )
{
    // try loading from ./<proc>.lgo
    if (procnode__caseobj(ProcNode) == UNDEFINED && 
        NOT_THROWING &&
        ProcNode != Null_Word)
    {
        silent_load(ProcNode, NULL);
    }

    // try loading from <logolib>/<proc>
    if (procnode__caseobj(ProcNode) == UNDEFINED && 
        NOT_THROWING &&
        ProcNode != Null_Word)
    {
        silent_load(ProcNode, g_LibPathName);
    }

    return procnode__caseobj(ProcNode);
}

// Remove the first element on stack and returns the new top of the stack.
NODE * spop(NODE *stack)
{
    assert(stack != NIL && "popping from an empty stack");

    NODE * newTop = stack->nunion.ncons.ncdr;

    if (decrefcnt(stack) == 0)
    {
        // Free this node in the stack, without freeing
        // the rest of the stack.
        stack->nunion.ncons.ncdr = NIL;
        gc(stack);
    }
    else
    {
        // Reference the new top of the stack for the
        // caller's reference.
        ref(newTop);
    }

    return newTop;
}

// Pushes "obj" onto the front of stack and returns the new stack head.
NODE * spush(NODE *obj, NODE *stack)
{
    NODE *newTop = newnode(CONS);

    newTop->nunion.ncons.ncar = vref(obj);
    newTop->nunion.ncons.ncdr = stack;
    newTop->nunion.ncons.nobj = NIL;
    ref(newTop);
    return newTop;
}

// Check if a local variable is already in this frame 
static
bool not_local(NODE *name, NODE *sp)
{
    for (; sp != var; sp = cdr(sp))
    {
        if (compare_node(car(sp), name, TRUE) == 0)
        {
            // We found a variable in the stack whose
            // case object "car(sp)" matches "name",
            // which means that it's already a local
            // variable.
            return false;
        }
    }
    return true;
}

static
void create_local_variable(NODE * caseobject, NODE * var_stack_position)
{
    assert(is_caseobject(caseobject));

    if (not_local(caseobject, var_stack_position))
    {
        // A variable by this name didn't already exist in
        // this scope, so we must create a new scope for it.
        push(caseobject, var_stack);
        setobject(var_stack, valnode__caseobj(caseobject));
    }

    if (flag__caseobj(caseobject, VAL_STEPPED))
    {
        // If the variable is stepped, emit a warning that it is being shadowed
        err_logo(SHADOW_WARN, caseobject);
    }
}

// reverse a stack in-place
static
NODE *reverse(NODE *list)
{
    NODE *ret = NIL;

    while (list != NIL)
    {
        NODE * temp = list;
        list = cdr(list);
        temp->nunion.ncons.ncdr = ret;
        ret = temp;
    }
    return ret;
}

// Returns a new list with the members of "a", followed by the members of "b".
// Neither list is modified, but "b" is referenced by the new list.
static
NODE *append(NODE *a, NODE *b)
{
    NODE * completelist     = NIL;
    NODE * completelist_end = NIL;

    // first, build up a copy of "a"
    while (a != NIL)
    {
        NODE * newnode = cons_list(car(a));

        if (completelist == NIL)
        {
            completelist = newnode;
        }
        else
        {
            setcdr(completelist_end, newnode);
        }
        completelist_end = newnode;

        a = cdr(a);
    }

    // now, append "b"
    if (completelist == NIL)
    {
        completelist = b;
    }
    else
    {
        setcdr(completelist_end, b);
    }

    return completelist;
}

// Reset the var stack to the previous place holder.
static
void reset_args(NODE *old_stack)
{
    for (; var_stack != old_stack; pop(var_stack))
    {
        setvalnode__caseobj(car(var_stack), getobject(var_stack));
    }
}


static
void trace_input(NODE * UnquotedArgument)
{
    // trace a NODE* as if it were an input to a function
    NODE * quoted_arg = vref(maybe_quote(UnquotedArgument));
    print_node(GetOutputStream(), MESSAGETYPE_Trace, quoted_arg);
    deref(quoted_arg);

    print_space(GetOutputStream(), MESSAGETYPE_Trace);
}

class CEvaluatorStack
{
private:
    struct EVALUATOR_STACK_FRAME
    {
        EVALUATOR_STACK_FRAME * NextFrame;
        enum labels             ReturnLabel; 

        NODE * ReferencedNode1;
        NODE * ReferencedNode2;
        NODE * ReferencedNode3;
        NODE * ReferencedNode4;
        NODE * ReferencedNode5;
        NODE * ReferencedNode6;
        NODE * ReferencedNode7;
        NODE * ReferencedNode8;
        NODE * ReferencedNode9;
        NODE * ReferencedNode10;

        FIXNUM Number1;
        FIXNUM Number2;
        FIXNUM Number3;
        FIXNUM Number4;

        NODE * UnreferencedNode1;
        NODE * UnreferencedNode2;
    };

    EVALUATOR_STACK_FRAME * m_StackTop;
    EVALUATOR_STACK_FRAME * m_FreeList;

public:
    CEvaluatorStack() :
        m_StackTop(NULL),
        m_FreeList(NULL)
    {
    }

    ~CEvaluatorStack()
    {
        // Assert that the number of calls to PushFrame() matched
        // match the calls to PopFrame().
        assert(m_StackTop == NULL);

        // Free all of the nodes that we were keeping around in
        // case we needed to reuse them.
        EVALUATOR_STACK_FRAME * currentNode = m_FreeList;
        while (currentNode != NULL)
        {
            EVALUATOR_STACK_FRAME * nextNode = currentNode->NextFrame;
            free(currentNode);
            currentNode = nextNode;
        }
    }

    enum labels
    GetReturnLabel() const
    {
        return m_StackTop->ReturnLabel;
    }


    void
    PushFrame(
        enum labels  ReturnLabel
        )
    {
        EVALUATOR_STACK_FRAME * stackFrame;

        // First, check the free list for a block of memory
        if (m_FreeList != NULL)
        {
            // Pop the top node off the free list and use it.
            stackFrame = m_FreeList;
            m_FreeList = m_FreeList->NextFrame;
        }
        else
        {
            // There's nothing in the free list,
            // so allocate the stack frame from the heap.
            stackFrame = static_cast<EVALUATOR_STACK_FRAME *>(malloc(sizeof(*stackFrame)));
            if (stackFrame == NULL)
            {
                err_logo(OUT_OF_MEM_UNREC, NIL);
            }
        }

        // Push the new node on top of the in-use stack.
        stackFrame->NextFrame = m_StackTop;
        m_StackTop = stackFrame;

        // Set the return point.
        stackFrame->ReturnLabel = ReturnLabel;
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1
        )
    {
        // Allocate the new stack frame.
        PushFrame(ReturnLabel);

        // Save the registers.
        m_StackTop->ReferencedNode1 = vref(Node1);
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        NODE       * Node3,
        NODE       * Node4,
        FIXNUM       Number1,
        FIXNUM       Number2
        )
    {
        // Allocate the new stack frame
        PushFrame(ReturnLabel);

        // Save the registers.
        m_StackTop->ReferencedNode1 = vref(Node1);
        m_StackTop->ReferencedNode2 = vref(Node2);
        m_StackTop->ReferencedNode3 = vref(Node3);
        m_StackTop->ReferencedNode4 = vref(Node4);

        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        NODE       * Node3,
        NODE       * Node4,
        NODE       * Node5,
        NODE       * Node6,
        NODE       * Node7,
        NODE       * Node8
        )
    {
        // Allocate the new stack frame
        PushFrame(ReturnLabel);

        // Save the registers.
        m_StackTop->ReferencedNode1 = vref(Node1);
        m_StackTop->ReferencedNode2 = vref(Node2);
        m_StackTop->ReferencedNode3 = vref(Node3);
        m_StackTop->ReferencedNode4 = vref(Node4);
        m_StackTop->ReferencedNode5 = vref(Node5);
        m_StackTop->ReferencedNode6 = vref(Node6);
        m_StackTop->ReferencedNode7 = vref(Node7);
        m_StackTop->ReferencedNode8 = vref(Node8);
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        NODE       * Node3,
        FIXNUM       Number1,
        FIXNUM       Number2,
        FIXNUM       Number3
        )
    {
        // Allocate the new stack frame
        PushFrame(ReturnLabel);

        // Save the registers
        m_StackTop->ReferencedNode1 = vref(Node1);
        m_StackTop->ReferencedNode2 = vref(Node2);
        m_StackTop->ReferencedNode3 = vref(Node3);

        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;
        m_StackTop->Number3 = Number3;
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        NODE       * Node3,
        NODE       * Node4,
        NODE       * Node5,
        NODE       * Node6,
        NODE       * Node7,
        NODE       * Node8,
        NODE       * Node9,
        FIXNUM       Number1,
        FIXNUM       Number2,
        NODE       * UnreferencedNode1,
        NODE       * UnreferencedNode2
        )
    {
        // Allocate the new stack frame.
        PushFrame(ReturnLabel);

        // Save the registers.
        m_StackTop->ReferencedNode1 = vref(Node1);
        m_StackTop->ReferencedNode2 = vref(Node2);
        m_StackTop->ReferencedNode3 = vref(Node3);
        m_StackTop->ReferencedNode4 = vref(Node4);
        m_StackTop->ReferencedNode5 = vref(Node5);
        m_StackTop->ReferencedNode6 = vref(Node6);
        m_StackTop->ReferencedNode7 = vref(Node7);
        m_StackTop->ReferencedNode8 = vref(Node8);
        m_StackTop->ReferencedNode9 = vref(Node9);

        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;

        m_StackTop->UnreferencedNode1 = UnreferencedNode1;
        m_StackTop->UnreferencedNode2 = UnreferencedNode2;
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        NODE       * Node3,
        NODE       * Node4,
        NODE       * Node5,
        NODE       * Node6,
        NODE       * Node7,
        NODE       * Node8,
        NODE       * Node9,
        NODE       * Node10,
        FIXNUM       Number1,
        FIXNUM       Number2
        )
    {
        // Allocate the new stack frame.
        PushFrame(ReturnLabel);

        // Save the registers.
        m_StackTop->ReferencedNode1  = vref(Node1);
        m_StackTop->ReferencedNode2  = vref(Node2);
        m_StackTop->ReferencedNode3  = vref(Node3);
        m_StackTop->ReferencedNode4  = vref(Node4);
        m_StackTop->ReferencedNode5  = vref(Node5);
        m_StackTop->ReferencedNode6  = vref(Node6);
        m_StackTop->ReferencedNode7  = vref(Node7);
        m_StackTop->ReferencedNode8  = vref(Node8);
        m_StackTop->ReferencedNode9  = vref(Node9);
        m_StackTop->ReferencedNode10 = vref(Node10);

        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        FIXNUM       Number1,
        FIXNUM       Number2
        )
    {
        // Allocate the new stack frame
        PushFrame(ReturnLabel);

        // Save the registers
        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;
    }


    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        FIXNUM       Number1,
        FIXNUM       Number2,
        FIXNUM       Number3,
        FIXNUM       Number4
        )
    {
        // Allocate the new stack frame
        PushFrame(ReturnLabel);

        // Save the registers
        m_StackTop->ReferencedNode1 = vref(Node1);
        m_StackTop->ReferencedNode2 = vref(Node2);

        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;
        m_StackTop->Number3 = Number3;
        m_StackTop->Number4 = Number4;
    }

    void
    PushFrame(
        enum labels  ReturnLabel,
        NODE       * Node1,
        NODE       * Node2,
        NODE       * Node3,
        FIXNUM       Number1,
        FIXNUM       Number2
        )
    {
        // Allocate the new stack frame
        PushFrame(ReturnLabel);

        // Save the registers.
        m_StackTop->ReferencedNode1  = vref(Node1);
        m_StackTop->ReferencedNode2  = vref(Node2);
        m_StackTop->ReferencedNode3  = vref(Node3);

        m_StackTop->Number1 = Number1;
        m_StackTop->Number2 = Number2;
    }

private:
    static
    void
    RestoreReferencedNode(
        NODE  *& TargetLocation,
        NODE  *  ReferencedNode
        )
    {
        deref(TargetLocation);
        TargetLocation = ReferencedNode;
    }

public:
    void
    PopFrame()
    {
        // Pop the stack frame.
        EVALUATOR_STACK_FRAME * poppedFrame = m_StackTop;
        m_StackTop = m_StackTop->NextFrame;

        // Put this node onto the free list, in case we need another one.
        poppedFrame->NextFrame = m_FreeList;
        m_FreeList = poppedFrame;
    }

    void
    PopFrame(
        NODE *& Node1
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);

        PopFrame();
    }

    void
    PopFrame(
        NODE   *& Node1,
        NODE   *& Node2,
        NODE   *& Node3,
        NODE   *& Node4,
        FIXNUM  & Number1,
        FIXNUM  & Number2
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2, m_StackTop->ReferencedNode2);
        RestoreReferencedNode(Node3, m_StackTop->ReferencedNode3);
        RestoreReferencedNode(Node4, m_StackTop->ReferencedNode4);

        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;

        PopFrame();
    }

    void
    PopFrame(
        NODE      *& Node1,
        NODE      *& Node2,
        NODE      *& Node3,
        NODE      *& Node4,
        NODE      *& Node5,
        NODE      *& Node6,
        NODE      *& Node7,
        NODE      *& Node8
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2, m_StackTop->ReferencedNode2);
        RestoreReferencedNode(Node3, m_StackTop->ReferencedNode3);
        RestoreReferencedNode(Node4, m_StackTop->ReferencedNode4);
        RestoreReferencedNode(Node5, m_StackTop->ReferencedNode5);
        RestoreReferencedNode(Node6, m_StackTop->ReferencedNode6);
        RestoreReferencedNode(Node7, m_StackTop->ReferencedNode7);
        RestoreReferencedNode(Node8, m_StackTop->ReferencedNode8);

        PopFrame();
    }

    void
    PopFrame(
        NODE      *& Node1,
        NODE      *& Node2,
        NODE      *& Node3,
        NODE      *& Node4,
        NODE      *& Node5,
        NODE      *& Node6,
        NODE      *& Node7,
        NODE      *& Node8,
        NODE      *& Node9,
        FIXNUM     & Number1,
        FIXNUM     & Number2,
        NODE      *& UnreferencedNode1,
        NODE      *& UnreferencedNode2
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2, m_StackTop->ReferencedNode2);
        RestoreReferencedNode(Node3, m_StackTop->ReferencedNode3);
        RestoreReferencedNode(Node4, m_StackTop->ReferencedNode4);
        RestoreReferencedNode(Node5, m_StackTop->ReferencedNode5);
        RestoreReferencedNode(Node6, m_StackTop->ReferencedNode6);
        RestoreReferencedNode(Node7, m_StackTop->ReferencedNode7);
        RestoreReferencedNode(Node8, m_StackTop->ReferencedNode8);
        RestoreReferencedNode(Node9, m_StackTop->ReferencedNode9);

        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;

        UnreferencedNode1 = m_StackTop->UnreferencedNode1;
        UnreferencedNode2 = m_StackTop->UnreferencedNode2;

        PopFrame();
    }

    void
    PopFrame(
        NODE       *& Node1,
        NODE       *& Node2,
        NODE       *& Node3,
        FIXNUM      & Number1,
        FIXNUM      & Number2,
        FIXNUM      & Number3
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2, m_StackTop->ReferencedNode2);
        RestoreReferencedNode(Node3, m_StackTop->ReferencedNode3);

        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;
        Number3 = m_StackTop->Number3;

        PopFrame();
    }

    void
    PopFrame(
        NODE      *& Node1,
        NODE      *& Node2,
        NODE      *& Node3,
        NODE      *& Node4,
        NODE      *& Node5,
        NODE      *& Node6,
        NODE      *& Node7,
        NODE      *& Node8,
        NODE      *& Node9,
        NODE      *& Node10,
        FIXNUM     & Number1,
        FIXNUM     & Number2
        )
    {
        RestoreReferencedNode(Node1,  m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2,  m_StackTop->ReferencedNode2);
        RestoreReferencedNode(Node3,  m_StackTop->ReferencedNode3);
        RestoreReferencedNode(Node4,  m_StackTop->ReferencedNode4);
        RestoreReferencedNode(Node5,  m_StackTop->ReferencedNode5);
        RestoreReferencedNode(Node6,  m_StackTop->ReferencedNode6);
        RestoreReferencedNode(Node7,  m_StackTop->ReferencedNode7);
        RestoreReferencedNode(Node8,  m_StackTop->ReferencedNode8);
        RestoreReferencedNode(Node9,  m_StackTop->ReferencedNode9);
        RestoreReferencedNode(Node10, m_StackTop->ReferencedNode10);

        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;

        PopFrame();
    }

    void
    PopFrame(
        FIXNUM      & Number1,
        FIXNUM      & Number2
        )
    {
        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;

        PopFrame();
    }

    void
    PopFrame(
        NODE       *& Node1,
        NODE       *& Node2,
        FIXNUM      & Number1,
        FIXNUM      & Number2,
        FIXNUM      & Number3,
        FIXNUM      & Number4
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2, m_StackTop->ReferencedNode2);

        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;
        Number3 = m_StackTop->Number3;
        Number4 = m_StackTop->Number4;

        PopFrame();
    }

    void
    PopFrame(
        NODE      *& Node1,
        NODE      *& Node2,
        NODE      *& Node3,
        FIXNUM     & Number1,
        FIXNUM     & Number2
        )
    {
        RestoreReferencedNode(Node1, m_StackTop->ReferencedNode1);
        RestoreReferencedNode(Node2, m_StackTop->ReferencedNode2);
        RestoreReferencedNode(Node3, m_StackTop->ReferencedNode3);

        Number1 = m_StackTop->Number1;
        Number2 = m_StackTop->Number2;

        PopFrame();
    }
};


// An explicit control evaluator, taken almost directly from SICP, section
// 5.2.  list is a flat list of expressions to evaluate.  where is a label to
// begin at.  Return value depends on where.
static
NODE *evaluator(NODE *list, enum labels where)
{
    CEvaluatorStack Stack;

    // Registers that get reference counted.
    NODE *exp = NIL;          // the current expression
    NODE *val = NIL;          // the value of the last expression
    NODE *proc = NIL;         // the procedure definition
    NODE *argl = NIL;         // evaluated argument list
    NODE *unev = NIL;         // list of unevaluated expressions
    NODE *catch_tag = NIL;

    // Registers that don't get reference counted.
    // These are saved/restored without changing the reference count.
    NODE * var_stack_position = NULL;  // temp ptr into var_stack
    NODE * formals = NULL;             // list of formal parameters
    FIXNUM repcount = 0;            // count for repeat

    bool tracing = false;               // are we tracing the current procedure?

    Stack.PushFrame(
        all_done,
        var,
        this_line,
        fun,
        ufun,
        tailcall,
        ift_iff_flag);

    assign(var, var_stack);
    ref(list);

    // Jump to the label described by "where".
    goto goto_cont;

begin_line:

    assign(this_line, list);
    Stack.PushFrame(end_line);
    goto begin_seq;

begin_seq:

    assign(val, Unbound);

    // Parenthesize the Logo list into something more like LISP
    treeify_line(list);
    if (!is_tree(list))
    {
        goto fetch_cont;
    }
    assign(unev, tree__tree(list));
    goto eval_sequence;

 end_line:
    Stack.PopFrame();
    if (val != Unbound)
    {
        if (NOT_THROWING)
        {
            err_logo(DK_WHAT, val);
        }
        deref(val);
    }
    val = NIL;



    goto fetch_cont;


    /* ----------------- EVAL ---------------------------------- */

 tail_eval_dispatch:
    tailcall = 1;
 eval_dispatch:
    // Evaluates "exp", sets the result in "val", and returns to the
    // continuation point, possibly dispatching to the appropriate
    // label if the evaluation requires a procedure call.
		

    switch (nodetype(exp))
    {
    case QUOTE:
        // quoted literal
        assign(val, node__quote(exp));
        goto fetch_cont;

    case COLON:
        // variable
        assign(val, valnode__colon(exp));
        while (val == Unbound && NOT_THROWING)
        {
            assign(val, err_logo(NO_VALUE, node__colon(exp)));
        }
        goto fetch_cont;

    case CONS:
        // procedure application
        if (tailcall == 1 && 
            is_macro(car(exp)) &&
            is_list(procnode__caseobj(car(exp))))
        {
            // tail call to user-defined macro must be treated as non-tail
            // because the expression returned by the macro
            // remains to be evaluated in the caller's context
            assign(unev, NIL);
            goto non_tail_eval;
        }

        // Initialize the argument list
        assign(argl, NIL);

        // the first element in the list is the function
        assign(fun, car(exp));

        // the rest of the elements are the function's inputs
        if (cdr(exp) == NIL)
        {
            // Evaluate an application of a procedure with no arguments.
            goto apply_dispatch;
        }
        else
        {
            // Evaluate an application of a procedure with arguments.
            assign(unev, cdr(exp));

            // Note: These values are restored in eval_args_done, but the control
            // flow is managed by goto, not fetch_cont, so the ReturnLabel parameter
            // is ignored.  Since eval_args_done is not part of the labels enumeration,
            // we must use some other value.
            Stack.PushFrame(
                static_cast<enum labels>(-1),
                var,
                didnt_get_output,
                didnt_output_name,
                tailcall,
                g_ValueStatus,
                ift_iff_flag);

            goto eval_arg_loop;
        }

    case ARRAY:
        // array must be copied
        {
            assign(val, make_array(getarrdim(exp)));
            setarrorg(val, getarrorg(exp));

            NODE ** p = getarrptr(exp);
            NODE ** q = getarrptr(val);
            for (int i = 0; i < getarrdim(exp); i++)
            {
                *q++ = vref(*p);
                p++;
            }
        }
        goto fetch_cont;

    default: 
        // self-evaluating (like a number or a word)
        assign(val, exp);
        goto fetch_cont;
    }

    assert(0 && !"can't fall through");

 eval_arg_loop:
    // Evaluates each of the expression in "unev" as arguments to
    // a procedure call.  In each iteration, moves the first
    // of "unev" to "exp" then jumps to eval_dispatch to evaluate "exp"
    // into "val".  This returns to "accumulate_arg", which moves "var"
    // onto the end of "argl", which is the evaluated list of arguments
    // that will be passed to the procedure.

    if (unev == NIL) 
    {
        // We've finished processing all of the arguments.
        // We can now call the procedure.
        goto eval_args_done;
    }
    assign(exp, car(unev));
    if (exp == g_ParseErrorNotEnoughInputs)
    {
        if (NOT_THROWING)
        {
            err_logo(NOT_ENOUGH, NIL);
        }
        goto eval_args_done;
    }

    Stack.PushFrame(
        accumulate_arg,
        argl,
        qm_list,
        unev,
        fun,
        ufun,
        last_ufun,
        this_line,
        last_line);

    assign(var, var_stack);
    tailcall = -1;
    g_ValueStatus = VALUE_STATUS_Required;
    assign(didnt_get_output, cons_list(fun, ufun, this_line));
    assign(didnt_output_name, NIL);
    goto eval_dispatch;                 // evaluate the current argument

 accumulate_arg:
    // The argument has been evaluted and the result is now in "var".

    // Reset the local variable state to where it was before this
    // argument was evaluated.
    reset_args(var);

    assign(last_call, fun);
    Stack.PopFrame(
        argl,
        qm_list,
        unev,
        fun,
        ufun,
        last_ufun,
        this_line,
        last_line);

    // If val is Unbound, then either an error was thrown, or
    // an expression did not output a value.  Since the expression
    // was an argument to another procedure, it's an error for
    // the expression not to ouput something.  Throw a
    // "didn't ouptut" error and give the ERRACT routine a chance
    // to supply the missing value.
    while (NOT_THROWING && val == Unbound)
    {
        assign(val, err_logo(DIDNT_OUTPUT, NIL));
    }

    // Move "val" into the list of evaluated arguments
    push(val, argl);

    // Remove the unevaluated expression, since it has now been
    // evaluated to "val".
    pop(unev);
    goto eval_arg_loop;

 eval_args_done:
    // We have finished evaluating all of the arguments in "unev"
    // or encountered an error.
    assert(unev == NIL || stopping_flag == THROWING);

    Stack.PopFrame(
        var,
        didnt_get_output,
        didnt_output_name,
        tailcall,
        g_ValueStatus,
        ift_iff_flag);

    if (stopping_flag == THROWING)
    {
        assign(val, Unbound);
        goto fetch_cont;
    }

    // Reverse "argl" because we had treated it as a stack,
    // popping from "unev" as we evaluated each argument expression
    // and prepending the result to "argl".
    argl = reverse(argl);


    /* --------------------- APPLY ---------------------------- */
 apply_dispatch:
    // This section is responsible for calling a procedure.
    // The procedure name is in "fun" and the arguments that were passed
    // to it are in "argl".

    eval_count++;
    update_status_evals();

    /* Load in the procedure's definition and decide whether it's a compound
     * procedure or a primitive procedure.
     */
    if (fun == NULL)
    { 
        // fun is NULL, so assume proc is undefined (output with no arg)
        assign(proc, UNDEFINED);
    }
    else
    {
        assign(proc, procnode__caseobj(fun));
        if (is_macro(fun))
        {
            // We are going to evalute a macro, so after we're done,
            // we'll have some extra stuff to do--either evaluate
            // whatever the macro returns in the caller's
            // context, or jump to a special continuation for the
            // primitive macros that need special evaluation logic.
            Stack.PushFrame(
                macro_return,
                g_ValueStatus,
                tailcall);
            // BUG: save didnt_get_output like UCBLogo?

            g_ValueStatus = VALUE_STATUS_Required;
        }
    }

    if (proc == UNDEFINED)
    {
        // proc is still undefined, so we can't apply it.
        // Throw a "don't know how to" error.
        if (NOT_THROWING)
        {
            assign(val, err_logo(DK_HOW, fun));
        }
        else
        {
            assign(val, Unbound);
        }
        goto fetch_cont;
    }

    if (is_list(proc))
    {
        // user-defined procedure (non-primitive)
        goto compound_apply;
    }

    /* primitive_apply */
    if (NOT_THROWING && !IsTimeToExit)
    {
        // REVISIT: Trace primitives like UCBLogo does?
        assign(val, ((logofunc) * getprimfun(proc)) (argl));
    }
    else
    {
        assign(val, Unbound);
    }

 fetch_cont:
    // Jumps back to the current continuation point, stored in "stack"
    where = Stack.GetReturnLabel();

 goto_cont:
    // Jumps to the label described by "where"
    switch (where)
    {
#define do_case(x) case x: goto x;
        do_list(do_case)
    default : abort();
    }

 compound_apply:
    // call (that is, APPLY) a non-primitive procedure/macro.

    // "argl" holds all of the arguments
    // "proc" contains the procnode of the non-primitive

    // Before we continue, check if the UI has requested that we
    // stop execution (for example, if they want to close).
    check_stop(true);

    if ((tracing = ((flag__caseobj(fun, PROC_TRACED) || traceflag))))
    {
        for (int i = 0; i < trace_level; i++) 
        {
            print_space(GetOutputStream(), MESSAGETYPE_Trace);
        }
        trace_level++;
        ndprintf(GetOutputStream(), MESSAGETYPE_Trace, L"( %s ", fun);
    }

 lambda_apply:

    // Bind the actual inputs to the formal inputs.
    // "Binding" means creating local variables for each
    // formal parameter and assigning them either a value
    // from the argument list in argl that was passed in,
    // or using the default values, specified in the procedure
    // definition.

    // Evaluating each of the arguments can add new variables
    // to var_stack.  For example, each named parameter will
    // be added as a local variable.
    // Since each parameter must be evaluated independently, we
    // need to save the current position in the var_stack so that
    // each parameter is evaluated only with the original
    // var_stack and not the accumulated one (with which the body of
    // the lambda apply will be evaluated).
    var_stack_position = var_stack;

    for (formals = formals__procnode(proc);
         formals != NIL;
         formals = cdr(formals))
    {
        NODE *parm;  // the current formal parameter

        parm = car(formals);
        if (nodetype(parm) == INTEGER) 
        {
            // Default # args

            // This is always listed after the last parameter, so we
            // can break out of the loop.
            break;
        }

        NODE * arg; // the current argument to bind to parm
        if (argl != NIL)
        {
            // An argument was supplied by the caller.
            arg = car(argl);
            if (tracing || traceflag)
            {
                // trace the input
                trace_input(arg);
            }
        }
        else
        {
            arg = Unbound;
        }

        if (nodetype(parm) == CASEOBJ)
        {
            // A named input (the common case) -- treat this a local variable
            create_local_variable(parm, var_stack_position);

            // bind the argument to the formal parameter object
            setvalnode__caseobj(parm, arg);

            if (arg == Unbound)
            {
                // we have more formal inputs than actual inputs
                err_logo(NOT_ENOUGH, fun);

                // REVISIT: Should this be moved to the front
                // of the if statement and should we break?
            }
        }
        else if (nodetype(parm) == CONS)
        {
            // parm is optional or rest 
            assert(is_caseobject(car(parm)));

            create_local_variable(car(parm), var_stack_position);

            if (cdr(parm) == NIL)
            {
                // parm is a "rest" input.
                // Bind the rest of the argument list to the formal parameter object
                setvalnode__caseobj(car(parm), argl);

                // trace the "rest" inputs, if necessary
                if (argl != NIL)
                {
                    if (tracing || traceflag)
                    {
                        // Start at cdr(argl) because we have already
                        // traced car(argl) above.
                        for (NODE * nextinput = cdr(argl);
                             nextinput != NIL;
                             nextinput = cdr(nextinput))
                        {
                            trace_input(car(nextinput));
                        }
                    }
                } 

                assign(argl, NIL);

                // Because parm was a "rest" input, we have all of the
                // inputs for this procedure call and can break out
                // of the loop.
                break;
            }
            if (arg == Unbound)
            {
                // No value was explicitly given for the argument,
                // so we use the parameter's default value, which
                // means evaluating cdr(parm).

                Stack.PushFrame(
                    set_args_continue,
                    fun,
                    var,
                    ufun,
                    last_ufun,
                    this_line,
                    last_line,
                    didnt_output_name,
                    didnt_get_output,
                    argl,
                    ift_iff_flag,
                    g_ValueStatus,
                    formals,
                    var_stack_position);

                // The expression should be processed as an argument.
                tailcall = -1;
                g_ValueStatus = VALUE_STATUS_Required;

                // Reset the local variables
                assign(var, var_stack);

                // Clear any return value that may exist.
                assign(val, Unbound);

                // Treeify the expression so that it can be evaluated.
                assign(list, cdr(parm));
                treeify_line(list);
                if (is_tree(list))
                {
                    // Run the expression to get the default value.
                    assign(unev, tree__tree(list));
                    goto eval_sequence;
                }

            set_args_continue:
                // We have evaluated the default value, which is now in "val".
                reset_args(var);
                Stack.PopFrame(
                    fun,
                    var,
                    ufun,
                    last_ufun,
                    this_line,
                    last_line,
                    didnt_output_name,
                    didnt_get_output,
                    argl,
                    ift_iff_flag,
                    g_ValueStatus,
                    formals,
                    var_stack_position);

                parm = car(formals);

                // Act like the evaluated default value for this parameter
                // was passed in as an argument.
                arg = val;
            }

            // bind the given argument to the formal argument
            setvalnode__caseobj(car(parm), arg);
        }

        // advance to the next argument in the list, if one exists
        if (argl != NIL) 
        {
            pop(argl);
        }
    }

    if (argl != NIL) 
    {
        // There were more arguments than formal parameters.
        // This shouldn't happen if everything is tree'ified
        // correctly, but it can happen in cases like:
        //
        //    APPLY [[A] [IGNORE :A]] [1 2]
        //
        err_logo(TOO_MUCH, fun);
    }
    if (check_throwing)
    {
        assign(val, Unbound);
        goto fetch_cont;
    }

    if ((tracing = ((!is_list(fun) && flag__caseobj(fun, PROC_TRACED)) || traceflag)))
    {
        if (NOT_THROWING) 
        {
            print_char(GetOutputStream(), MESSAGETYPE_Trace, ')');
        }
        new_line(GetOutputStream(), MESSAGETYPE_Trace);

        Stack.PushFrame(
            compound_apply_continue,
            fun);
    }
    assign(val, Unbound);
    assign(last_ufun, ufun);
    if (!is_list(fun))
    {
        assign(ufun, fun);
    }
    assign(last_line, this_line);
    assign(this_line, NIL);
    assign(proc, (is_list(fun) ? anonymous_function(fun) : procnode__caseobj(fun)));
    assign(list, bodylist__procnode(proc));// get the body ...
    treeify_body(list);
    if (!is_tree(list))
    {
        // Either there was some error when treeifyng the body
        // or the body consisted of nothing by empty lines.
        // In the first case, we want to jump to the next phase
        // in the evaulator so that we can error-out.
        // In the second case, trying to evaluate this function
        // would crash, but we can instead ignore this function
        // call, since it is a no-op.
        assign(val, Unbound);
        goto fetch_cont;
    }

    // Set the tree'ified expressions from "proc" to "unev" so that they
    // can be evaluated.
    assign(unev, tree__tree(list));
    if (NOT_THROWING)
    {
        stopping_flag = RUN;
    }
    assign(output_node, Unbound);

    // Set expectations on whether or not "unev" should evaluate to
    // to a value.
    if (g_ValueStatus == VALUE_STATUS_Required) 
    {
        g_ValueStatus = VALUE_STATUS_OutputOk;
    }
    else if (g_ValueStatus == VALUE_STATUS_ValueMaybeOkInMacro) 
    {
        g_ValueStatus = VALUE_STATUS_MaybeOk;
    }
    else 
    {
        g_ValueStatus = VALUE_STATUS_NotOk;
    }

eval_sequence: 
	//FIXED: need do events in windows for message loop to avoid being frozen
	DoEvents();
	check_stop(true);

    // Evaluate each expression in "unev" in the sequence.
    // Stop as soon as val != Unbound, which is when we
    // have a value to return.
    if (!RUNNING || val != Unbound)
    {
        goto fetch_cont;
    }
    if (nodetype(unev) == LINE)
    {
        // The is_tree() clause prevents a crash when a procedure 
        // is erased while it is being run.
        if (is_tree(unparsed__line(unev)) && 
            the_generation != generation__line(unev))
        {
            // Something got redefined while we're running.
            //
            // We must re-tree-ify the bodylist of the current
            // procedure to ensure that it is tree-ified with the
            // most recent procedure definitions.
            //
            // If we don't do this, the programmer would get the
            // wrong behavior, but we might also AV if the old tree
            // passed the wrong number of inputs to a primitive.

            int linenum = 0;
            assign(this_line, tree__tree(bodylist__procnode(proc)));
            while (this_line != unev) 
            {
                // If redef isn't end of line, don't try to fix,
                // but don't blow up either. (Maybe not called from here.)
                if (this_line == NULL) 
                {
                    goto no_fixup_necessary;
                }
                if (nodetype(this_line) == LINE) 
                {
                    linenum++;
                }
                assign(this_line, cdr(this_line));
            }

            treeify_body(bodylist__procnode(proc));
            assign(unev, tree__tree(bodylist__procnode(proc)));
            while (--linenum >= 0) 
            {
                do 
                {
                    pop(unev);
                } while (unev != NIL && nodetype(unev) != LINE);
            }
        }

 no_fixup_necessary:
        assign(this_line, unparsed__line(unev));
        if ((ufun != NIL && flag__caseobj(ufun, PROC_STEPPED)) || stepflag)
        {
            // this is not a lambda function and it is being stepped
            if (tracing || traceflag)
            {
                int i = 1;
                while (i++ < trace_level) 
                {
                    print_space(stdoutstream, MESSAGETYPE_Trace);
                }
            }
            // print_node(stdout, this_line);
            // ndprintf(stdout, " >>> ");
			GetInputBlocking() = true;

            if (!setjmp(iblk_buf))
            {
                single_step_box(this_line);
            }

			GetInputBlocking() = false;
            // update_coords('\n');
        }
    }

    // Move the first unevaluated expression into "exp" for evaluation.
    assign(exp, car(unev));
    pop(unev);

    if (exp != NIL &&
        is_list(exp) && 
        is_tailform(procnode__caseobj(car(exp))))
    {
        // "exp" is a procedure call.  car(exp) is the procedure's case object.
        NODE * const caseobj = car(exp);

        // Get the priority of the primitive to get the "true identity".
        // This will compare correctly, even if the procedure is a copydef
        // of another procedure.
        short expression_priority = getprimpri(procnode__caseobj(caseobj));
        if (expression_priority == OUTPUT_PRIORITY)
        {
            // They are calling some form of OUTPUT.

            if (cadr(exp) == g_ParseErrorNotEnoughInputs)
            {
                // There was a parse error when this instruction list
                // was being treeified.  We delayed reporting this error
                // until now so that any previous instructions, which were
                // parsed successfully, could be run.
                err_logo(NOT_ENOUGH, caseobj);
                assign(val, Unbound);
                goto fetch_cont;
            }

            assign(didnt_get_output, cons_list(caseobj, ufun, this_line));
            assign(didnt_output_name, NIL);
            if (g_ValueStatus == VALUE_STATUS_OutputOk || 
                g_ValueStatus == VALUE_STATUS_MaybeOk)
            {
                g_ValueStatus = VALUE_STATUS_Required;
                assign(exp, cadr(exp));
                goto tail_eval_dispatch;
            }
            else if (ufun == NIL)
            {
                // We are not in a user-defined function, so they must 
                // be calling OUTPUT at the top-level, which is an error.
                err_logo(AT_TOPLEVEL, caseobj);
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (!IsInMacro(g_ValueStatus))
            {
                g_ValueStatus = VALUE_STATUS_Required;
                assign(exp, cadr(exp));
                assign(unev, NIL);

                // compute value then give error
                goto non_tail_eval;
            }
        }
        else if (expression_priority == STOP_PRIORITY)
        {
            // they are calling some form of STOP

            if (ufun == NIL)
            {
                // We are not in a user-defined function, so they must 
                // be calling STOP at the top-level, which is an error.
                err_logo(AT_TOPLEVEL, caseobj);
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (g_ValueStatus == VALUE_STATUS_NotOk || 
                     g_ValueStatus == VALUE_STATUS_MaybeOk)
            {
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (!IsInMacro(g_ValueStatus))
            {
                assign(didnt_output_name, fun);
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (g_ValueStatus == VALUE_STATUS_ValueMaybeOkInMacro)
            {
                // pr apply [output ?] [3]
                assign(didnt_output_name, fun);
                goto tail_eval_dispatch;
            }
        }
        else
        {
            // maybeoutput
            assign(exp, cadr(exp));
            g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
            goto tail_eval_dispatch;
        }
    }


    if (unev == NIL)
    {
        // falling off tail of sequence
        if (g_ValueStatus == VALUE_STATUS_OutputOk || 
            g_ValueStatus == VALUE_STATUS_NoValueInMacro)
        {
            assign(didnt_output_name, fun);
            assign(unev, Unbound);
            goto non_tail_eval;
        }
        else
        {
            goto tail_eval_dispatch;
        }
    }



    if (car(unev) != NIL &&
        is_list(car(unev)) && 
        is_tailform(procnode__caseobj(car(car(unev)))) &&
        getprimpri(procnode__caseobj(car(car(unev)))) == STOP_PRIORITY)
    {
        // next is STOP
        if ((g_ValueStatus == VALUE_STATUS_NotOk || g_ValueStatus == VALUE_STATUS_MaybeOk) && 
            ufun != NIL)
        {
            goto tail_eval_dispatch;
        }
        else if (!IsInMacro(g_ValueStatus))
        {
            assign(didnt_output_name, fun);
            goto tail_eval_dispatch;
        }
    }
 non_tail_eval:
    // REVISIT: copy after_constant optimization from UCBLogo?
    Stack.PushFrame(
        eval_sequence_continue,
        unev,
        fun,
        ufun,
        last_ufun,
        this_line,
        last_line,
        var,
        proc,
        qm_list,
        argl,
        ift_iff_flag,
        g_ValueStatus);

    assign(var, var_stack);
    tailcall = 0;
    goto eval_dispatch;

 eval_sequence_continue:
    // This is the return point for eval_sequence executions which have
    // dispatched to eval_dispatch or tail_eval_dispatch.
    // It is responsible for splicing the return value from a macro into
    // "unev", then jumping to eval_sequence to evaluate the next expression.
    reset_args(var);
    Stack.PopFrame(
        unev,
        fun,
        ufun,
        last_ufun,
        this_line,
        last_line,
        var,
        proc,
        qm_list,
        argl,
        dont_fix_ift ? dont_fix_ift : ift_iff_flag,
        g_ValueStatus);

    dont_fix_ift = 0;

    // If we dispatched to a macro, then we must splice the
    // output of the macro (which is held in "val") into
    // the remaining unevaluated expressions "unev" so that
    // the macro can be evaluated in the context of the caller.
    if (stopping_flag == MACRO_RETURN)
    {
        if (unev == Unbound) 
        {
            assign(unev, NIL);
        }
        if (val != NIL && is_list(val) && (car(val) == Tag))
        {
            assign(unev, cdr(val)); /* from goto */
        }
        else
        {
            assign(unev, append(val, unev));
        }
        assign(val, Unbound);
        stopping_flag = RUN;
        if (unev == NIL)
        {         
            goto fetch_cont;
        }
    }
    else if (!IsInMacro(g_ValueStatus))
    {
        if (STOPPING || RUNNING)
        {
            assign(output_node, Unbound);
        }

        if (stopping_flag == OUTPUT || STOPPING)
        {
            stopping_flag = RUN;
            assign(val, output_node);

            // set errors, if appropriate
            if (NOT_THROWING)
            {
                if (val != Unbound)
                {
                    // value is bound
                    if (g_ValueStatus == VALUE_STATUS_NotOk || 
                        g_ValueStatus == VALUE_STATUS_Required) // BUG???
                    {
                        // value is bound, but no value was expected
                        assign(didnt_output_name, Output);
                        err_logo(DIDNT_OUTPUT, Output);
                    }
                }
                else 
                {
                    // value is not bound
                    if (g_ValueStatus == VALUE_STATUS_Required)
                    {
                        // a value is required, but was not given
                        assign(didnt_output_name, Stop);
                        err_logo(DIDNT_OUTPUT, Output);
                    }
                }
            }
            goto fetch_cont;
        }
    }

    if (NOT_THROWING && val != Unbound)
    {
        // we have a return value with no function to consume it
        err_logo((unev == NIL ? DK_WHAT_UP : DK_WHAT), val);
        assign(val, Unbound);
    }
    if (NOT_THROWING && (unev == NIL || unev == Unbound))
    {
        // unev is NIL or Unbound, which means that there
        // is nothing to evaluate to turn into a value.
        if (g_ValueStatus == VALUE_STATUS_Required) 
        {
            err_logo(DIDNT_OUTPUT, NIL);
        }
        goto fetch_cont;
    }

    // Evaluate the next expression in "unev".
    goto eval_sequence;
    assert(0 && !"doesn't fall through");


 compound_apply_continue:
    /* Only get here if tracing */
    Stack.PopFrame(fun);
    --trace_level;
    if (NOT_THROWING)
    {
        for (int i = 0; i < trace_level; i++) 
        {
            print_space(GetOutputStream(), MESSAGETYPE_Trace);
        }
        print_node(GetOutputStream(), MESSAGETYPE_Trace, fun);
        if (val == Unbound)
        {
            // trace that the procedure stopped (without outputting anything)
            ndprintf(
                GetOutputStream(),
                MESSAGETYPE_Trace,
				GetResourceString(L"LOCALIZED_TRACING_STOPS"));
        }
        else
        {
            // trace the output
            NODE * quoted_val = vref(maybe_quote(val));
            ndprintf(
                GetOutputStream(),
                MESSAGETYPE_Trace,
				GetResourceString(L"LOCALIZED_TRACING_OUTPUTS"),
                quoted_val);
            deref(quoted_val);
        }
    }
    goto fetch_cont;

    assert(0 && !"doesn't fall through");

    /* --------------------- MACROS ---------------------------- */

 macro_return:
    Stack.PopFrame(
        g_ValueStatus,
        tailcall);

    while (!is_list(val) && NOT_THROWING)
    {
        assign(val, err_logo(ERR_MACRO, val));
    }
    if (NOT_THROWING)
    {
        if (is_cont(val))
        {
            // continue to the continuation within val
            where = static_cast<enum labels>(cont__cont(val));
            assign(val, val__cont(val));
            goto goto_cont;
        }
        else if (tailcall == 0)
        {
            // This is a probably a macroized primative, such as
            // IF or IFELSE, which output an instructionlist to run
            // or NIL if nothing should be run.
            // Treeify the output, then continue with normal execution.
            treeify_line(val);
            if (is_tree(val)) 
            {
                assign(val, tree__tree(val));
            }
            if (stopping_flag != THROWING)
            {
                stopping_flag = MACRO_RETURN;
            }
            goto fetch_cont;
        }
        else
        {
            // Macros output lists that are to be evaluated
            // within the context of the caller.  Now that the
            // macro has returned, we can evaluate the list, which
            // is currently in "val".
            assign(list, val);
            goto begin_seq;
        }
    }
    else
    {
        assign(val, Unbound);
        goto fetch_cont;
    }

    assert(0 && !"doesn't fall through");

    /* --------------------- RUNRESULT ---------------------------- */

 runresult_continuation:
    assign(list, val);
    Stack.PushFrame(runresult_followup);
    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
    goto begin_seq;

 runresult_followup:
    Stack.PopFrame();
    if (val == Unbound)
    {
        // If the input to RUNRESULT doesn't output, 
        // then the output is []
        assign(val, NIL);
    }
    else
    {
        // If the input to RUNRESULT outputs something,
        // then the output goes in a list.
        assign(val, cons_list(val));
    }
    goto fetch_cont;


   /* --------------------- REPEAT ---------------------------- */
 repeat_continuation:
    assign(list, cdr(val));

    // Note: These values are restored in repeat_done, but the control
    // flow is managed by goto, not fetch_cont, so the ReturnLabel parameter
    // is ignored.  Since repeat_done is not part of the labels enumeration,
    // we must use some other value.
    Stack.PushFrame(
        static_cast<enum labels>(-2),
        repcount,
        repcountup);

    repcount   = getint(car(val));
    repcountup = 0;

 repeat_again:
    assign(val, Unbound);
    if (repcount != 0)
    {
        repcountup++;
        Stack.PushFrame(
            repeat_followup,
            list,
            var,
            repcount,
            repcountup,
            g_ValueStatus,
            tailcall);

        assign(var, var_stack);
        g_ValueStatus = VALUE_STATUS_NoValueInMacro;
        goto begin_seq;
    }

 repeat_done:
    // Restore the state that was set up in repeat_continuation in case
    // this was a nested REPEAT.
    Stack.PopFrame(
        repcount,
        repcountup);
    goto fetch_cont;

 repeat_followup:
    if (val != Unbound && NOT_THROWING)
    {
        ref(val);
        err_logo(DK_WHAT, val);
        unref(val);
    }

    Stack.PopFrame(
        list,
        var,
        repcount,
        repcountup,
        g_ValueStatus,
        tailcall);

    if (!IsInMacro(g_ValueStatus) && tailcall != 0)
    {
        if (STOPPING || RUNNING) 
        {
            assign(output_node, Unbound);
        }
        if (stopping_flag == OUTPUT || STOPPING)
        {
            stopping_flag = RUN;
            assign(val, output_node);
            goto repeat_done;
        }
    }
    if (repcount > 0) // negative means forever
    {
        --repcount;
    }
    check_stop(true);

    if (RUNNING)
    {
        goto repeat_again;
    }
    else
    {
        assign(val, Unbound);
        goto repeat_done;
    }

    assert(0 && !"can't fall through");


    /* --------------------- CATCH/THROW ---------------------------- */
 catch_continuation:
    assign(list, cdr(val));
    assign(catch_tag, car(val));
    if (Error.Equals(catch_tag))
    {
        // Increment the number of nested CATCH "ERROR blocks.
        // When an error does occur, this value is used to decide
        // between throwing an error or using the value of ERRACT.
        g_CatchErrorCount++;
    }

    Stack.PushFrame(
        catch_followup,
        catch_tag,
        didnt_output_name,
        didnt_get_output,
        g_ValueStatus,
        tailcall);

    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
    goto begin_seq;

 catch_followup:
    Stack.PopFrame(
        catch_tag,
        didnt_output_name,
        didnt_get_output,
        g_ValueStatus,
        tailcall);

    if (!IsInMacro(g_ValueStatus) && tailcall != 0)
    {
        if (STOPPING || RUNNING) 
        {
            assign(output_node, Unbound);
        }
        if (stopping_flag == OUTPUT || STOPPING)
        {
            stopping_flag = RUN;
            assign(val, output_node);
            if (val != Unbound)
            {
                if (g_ValueStatus == VALUE_STATUS_NotOk ||
                    g_ValueStatus == VALUE_STATUS_Required) // BUG???
                {
                    err_logo(DK_WHAT_UP, val);
                }
            }
        }
    }

    if (Error.Equals(catch_tag))
    {
        // we have reached the end of a CATCH "ERROR [] block
        assert(0 < g_CatchErrorCount);
        g_CatchErrorCount--;
    }

    if (stopping_flag == THROWING)
    {
        // if throw_node=="erreur" and catch_tag=="error", then
        // compare_node() will return false, even in the French 
        // version of FMSLogo.  Therefore, we must treat them as 
        // equal if they both equal Error.
        if (compare_node(throw_node, catch_tag, true) == 0 ||
            (Error.Equals(catch_tag) && Error.Equals(throw_node)))
        {
            assign(throw_node, Unbound);
            stopping_flag = RUN;
            assign(val, output_node);
        }
    }
    goto fetch_cont;

 goto_continuation:
    check_stop(true);

    if (ufun == NIL)
    {
        err_logo(AT_TOPLEVEL, Goto);
        assign(val, Unbound);
        goto fetch_cont;
    }
    assign(proc, procnode__caseobj(ufun));
    assign(list, bodylist__procnode(proc));
    assign(unev, tree__tree(list));
    while (unev != NIL)
    {
        if (nodetype(unev) == LINE)
        {
            assign(this_line, unparsed__line(unev));
        }
        assign(exp, car(unev));
        pop(unev);
        if (is_list(exp) &&
            (object__caseobj(car(exp)) == object__caseobj(Tag)) &&
            (nodetype(cadr(exp)) == QUOTE) &&
            compare_node(val, node__quote(cadr(exp)), TRUE) == 0)
        {
            assign(val, cons(Tag, unev));
            stopping_flag = MACRO_RETURN;
            goto fetch_cont;
        }
    }
    err_logo(BAD_DATA_UNREC, val);
    assign(val, Unbound);
    goto fetch_cont;

    /* --------------------- APPLY ---------------------------- */
 begin_apply:
    /* This is for lapply. */
    assign(fun, car(val));
    while (nodetype(fun) == ARRAY && NOT_THROWING)
    {
        assign(fun, err_logo(APPLY_BAD_DATA, fun));
    }
    assign(argl, cadr(val));
    assign(val, Unbound);
    while (!is_list(argl) && NOT_THROWING)
    {
        assign(argl, err_logo(APPLY_BAD_DATA, argl));
    }
    if (NOT_THROWING && fun != NIL)
    {
        if (is_list(fun))
        {
            // template
            if (is_list(car(fun)) && cdr(fun) != NIL)
            {
                if (is_list(cadr(fun)))
                {
                    // procedure text form [[param ...] [instr ...] ... ] 
                    assign(proc, anonymous_function(fun));
               
                    if (stopping_flag == THROWING)
                    {
                        goto fetch_cont;
                    }

                    // disable tracing for lambda functions
                    tracing = false;
                    goto lambda_apply;
                }
                else
                {
                    // lambda form [[param ...] instr ...]
                    NODE * formal_inputs = car(fun);
                    if (tailcall <= 0) 
                    {
                        // Create a new local variable scope for 
                        // the lambda function call before binding
                        // the formal inputs.
                        Stack.PushFrame(
                            after_lambda,
                            var);
                        assign(var, var_stack);
                    }

                    //numsave(tailcall);
                    tailcall = 0;
                    llocal(formal_inputs);  // bind the formals locally
                    //numrestore(tailcall);
                    for (;
                         formal_inputs != NIL && argl && NOT_THROWING;
                         formal_inputs = cdr(formal_inputs), assign(argl, cdr(argl)))
                    {
                        setvalnode__caseobj(car(formal_inputs), car(argl));
                    }

                    if (formal_inputs != NIL) 
                    {
                        // too few inputs
                        err_logo(NOT_ENOUGH, fun);
                        goto fetch_cont;
                    } 
                    else if (argl != NIL) 
                    {
                        // too many inputs.
                        err_logo(TOO_MUCH, car(argl));
                        goto fetch_cont;
                    }
                    else
                    {
                        // correct number of inputs
                        assign(list, cdr(fun));
                        goto lambda_qm;
                    }
                }
            }
            else
            {
                // question-mark form [instr ...]

                // qm_list is restored at accumulate_arg
                assign(qm_list, argl);
                assign(list, fun);
            lambda_qm:
                treeify_line(list);
                if (list == NIL || !is_tree(list))
                {
                    goto fetch_cont;
                }
                assign(unev, tree__tree(list));

                if (tailcall <= 0) 
                {
                    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;

                    // Create a new local variable scope for 
                    // the lambda function call.
                    Stack.PushFrame(
                        after_lambda,
                        var);
                    assign(var, var_stack);
                }
                goto eval_sequence;
            }
        }
        else
        {
            // name of procedure to apply
            assign(fun, intern(fun));

            // load the definition of fun, if necessary
            assign(proc, load_procedure_if_necessary(fun));
            while (proc == UNDEFINED && NOT_THROWING)
            {
                assign(val, err_logo(DK_HOW_UNREC, fun));
            }
            if (NOT_THROWING)
            {
                int min;
                int max;

                if (nodetype(proc) == CONS)
                {
                    // proc is a user-defined or library procedure
                    min = getint(minargs__procnode(proc));
                    max = getint(maxargs__procnode(proc));
                }
                else
                {
                    // proc is a primitive
                    if (getprimdflt(proc) < 0)
                    {
                        // special form (TO or .MACRO)
                        err_logo(DK_HOW_UNREC, fun); // can't apply
                        goto fetch_cont;
                    }
                    else
                    {
                        min = getprimmin(proc);
                        max = getprimmax(proc);
                    }
                }

                int n = list_length(argl);

                if (n < min)
                {
                    err_logo(NOT_ENOUGH, NIL);
                }
                else if (n > max && max >= 0)
                {
                    err_logo(TOO_MUCH, NIL);
                }
                else
                {
                    goto apply_dispatch;
                }
            }
        }
    }
    goto fetch_cont;

 after_lambda:
    reset_args(var);
    Stack.PopFrame(var);
    goto fetch_cont;

 all_done:
    deref(list);

    reset_args(var);
    Stack.PopFrame(
        var,
        this_line,
        fun,
        ufun,
        tailcall,
        ift_iff_flag);

    deref(argl);
    deref(unev);
    deref(catch_tag);
    deref(exp);
    deref(proc);
    return val;
}

// Evaluate a line of input.
void eval_driver(NODE *line)
{
    if (line != NIL)
    {
        evaluator(line, begin_line);
    }
}

// Evaluate a sequence of expressions until we get a value to return.
// (Called from erract.)
NODE *err_eval_driver(NODE *seq)
{
    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
    return evaluator(seq, begin_seq);
}


/* The logo word APPLY. */
NODE *lapply(NODE *args)
{
    return make_cont(begin_apply, args);
}

// The logo word ? <question-mark>.
// This evalutes some element within qm_list.
//
// ?  evaluates to the first element
// ?1 evaluates to the first element
// ?2 evaluates to the second element
// etc.
//
NODE *lqm(NODE *args)
{
    // Assume ?1 by default
    FIXNUM argnum = 1;
    if (args != NIL) 
    {
        // ?# was given
        argnum = getint(positive_int_arg(args));
    }
    if (stopping_flag == THROWING) 
    {
        return Unbound;
    }

    // get the argnum-th item from qm_list
    NODE *np = qm_list;
    FIXNUM i = argnum;
    while (--i > 0 && np != NIL) 
    {
        np = cdr(np);
    }
    if (np == NIL)
    {
        return err_logo(BAD_DATA_UNREC, make_intnode(argnum));
    }
    return car(np);
}


NODE *llocal(NODE *args)
{
    if (tailcall != 0)
    {
        return Unbound;
    }

    if (args == NIL) 
    {
        return Unbound;
    }

    while (is_list(car(args)) && cdr(args) != NIL && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, car(args)));
    }

    if (is_list(car(args)))
    {
        args = car(args);
    }

    NODE *var_stack_position = var_stack;

    while (args != NIL && NOT_THROWING)
    {
        NODE * arg = car(args);
        while (!is_word(arg) && NOT_THROWING)
        {
            arg = err_logo(BAD_DATA, arg);
            setcar(args, arg);            // prevent crash in lapply
        }
        if (NOT_THROWING)
        {
            arg = intern(arg);
            setcar(args, arg);            // local [a b] faster next time

            create_local_variable(arg, var_stack_position);

            setvalnode__caseobj(arg, Unbound);
            args = cdr(args);
        }
        if (check_throwing) 
        {
            break;
        }
    }
    assign(var, var_stack);  // so eval won't undo our work
    return Unbound;
}

bool process_special_conditions()
{
    bool error_happened = false;

    if (stopping_flag == THROWING)
    {
        if (Error.Equals(throw_node))
        {
            err_print();
            error_happened = true;
        }
        else if (System.Equals(throw_node))
        {
#ifndef WX_PURE
            PostQuitMessage(1); // set the exit code to 1
#endif
            exit_program();
        }
        else if (!Toplevel.Equals(throw_node))
        {
            err_logo(NO_CATCH_TAG, throw_node);
            err_print();
            error_happened = true;
        }

        stopping_flag = RUN;
    }

    if (stopping_flag == STOP || stopping_flag == OUTPUT)
    {
        // This is probably a bug, not a user error.
        // We shouldn't be able to get here without throwing
        // an AT_TOPLEVEL error, which would result in a 
        // stopping_flag of THROWING.
        ndprintf(
			stdoutstream,
            MESSAGETYPE_Normal,
            wxString(L"%t.\n")
			+ GetResourceString(L"LOCALIZED_ERROR_ATTOPLEVEL2"));
        stopping_flag = RUN;
    }

    return error_happened;
}

void start_execution()
{
    // if executing then it's ok to halt
    assert(0 <= halt_flag);

    halt_flag++;
    if (halt_flag < 1)
    {
        halt_flag = 1;
    }

    // Enable the Halt/Pause buttons since FMSLogo is running.
    UpdateUiExecutionState();
}

void stop_execution()
{
    // not ok to halt now
    assert(1 <= halt_flag);

    halt_flag--;
    if (halt_flag < 0)
    {
        halt_flag = 0;
    }

    // Disable the Halt/Pause buttons since FMSLogo is not running.
    UpdateUiExecutionState();

    if (halt_flag == 0 && IsTimeToExit)
    {
        // We have finished unwinding the Logo stack after a BYE or
        // equivalent instruction.  It is now safe to destroy the window.
        // We call Close() to give the user a chance to veto (for example,
        // if there were unsaved changes).  If the user vetos the close
        // then IsTimeToExit flag is cleared.
        IsTimeToExit = GetMainWxWindow()->Close();

        // Don't let any errors that were thrown stop FMSLogo from exiting.
        stopping_flag = RUN;
        assign(throw_node, NIL);
    }
}

extern bool IsAnyTimerActive();
bool is_executing()
{
    assert(0 <= halt_flag);
    return halt_flag != 0 || IsAnyTimerActive();
}

void do_execution(const wchar_t * cmd)
{
    // if something there continue
    if (cmd!=0 && cmd[0] != L'\0')
    {
		size_t lc = wcslen(cmd);
		wchar_t* logocommand = new wchar_t[lc + 1];
		wcsncpy(logocommand, cmd, lc +1);

        start_execution();

        // this code emulates the TTY model used in UCBLOGO main loop
        NODETYPES this_type = STRING;

        // do control character processing
        for (wchar_t * c = (wchar_t*)logocommand; *c != L'\0'; c++)
        {
            if (*c == L'\\')
            {
				//remove the \ char
                //wcscpy(c, c + 1);
				for (wchar_t* p = c + 1; *p != L'\0'; p++) {
					*(p - 1) = *p;
				}
                if (*c)
                {
                    if (*c == L'n') 
                    {
                        *c = L'\n';
                    }
                    *c = ecma_set(*c);
                }
                this_type = BACKSLASH_STRING;
            }
        }

        check_reserve_tank();

        // Set the stopping_flag to RUN so that we don't print any spurious 
        // warnings about using OUTPUT or STOP while not in a procedure.
        // This is important because do_execution() can be called to process
        // event handlers while evaluator() is running.
        // See bug #1479111 for details.
        FIXNUM   saved_value_status  = g_ValueStatus;
        CTRLTYPE saved_stopping_flag = stopping_flag;
        NODE *   saved_output_node   = vref(output_node);
        NODE *   saved_current_line  = current_line;

        stopping_flag = RUN;

        // turn text into a NODE and parse it
        current_line = vref(make_strnode(
            logocommand, 
			lc,
            this_type, 
            strnzcpy));
		
        NODE * exec_list = vref(parser(current_line, true));

        // now process it
        g_ValueStatus = VALUE_STATUS_NotOk;
        eval_driver(exec_list);

        process_special_conditions();

        // restore the stopping flag
        stopping_flag = saved_stopping_flag;
        g_ValueStatus = saved_value_status;

        deref(output_node);
        output_node = saved_output_node;

        // deallocate the line
        deref(current_line);
        current_line = saved_current_line;

        deref(exec_list);

        stop_execution();

		delete logocommand;
    }
}

void uninitialize_eval()
{
    // CONSIDER: should any of these be deref'd in evaluator()?
    deref(qm_list);
    qm_list = NIL;

    deref(last_call);
    last_call = NIL;

    deref(last_line);
    last_line = NIL;

    deref(didnt_output_name);
    didnt_output_name = NIL;

    deref(didnt_get_output);
    didnt_get_output = NIL;

    deref(last_ufun);
    last_ufun = NIL;
}
