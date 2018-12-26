/*
*      error.cpp         logo error module                       dvb
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
   #include <stdlib.h>
   #include <string.h>
   #include <setjmp.h>

   #include "error.h"
   #include "logocore.h"
   #include "print.h"
   #include "eval.h"
   #include "localizedstrings.h"
   #include "coms.h"
   #include "unix.h"
   #include "mem.h"
   #include "wrksp.h"
   #include "graphwin.h" // for MyMessageScan
   #include "init.h"
   #include "parse.h"
   #include "logomath.h"
   #include "ibmterm.h"
   #include "logoeventqueue.h"
   #include "mmwind.h"
   #include "debugheap.h"
#include "files.h"
#include "CStringTextStream.h"
#endif


NODE *    throw_node = NIL;

// Holds the values for ERROR
static wxString g_ErrorFormatString;
static NODE *       g_ErrorArguments    = NIL;
static NODE *       g_ErrorCode         = NIL;
static NODE *       g_ErrorFunction     = NIL;
static NODE *       g_ErrorLine         = NIL;

static bool g_IsRunningErractInstructionList = false;

static
void set_is_running_erract_flag()
{
    g_IsRunningErractInstructionList = true;
}

// REVISIT: does this really need to be callable from other files?
void clear_is_running_erract_flag()
{
    g_IsRunningErractInstructionList = false;
}

static
bool last_error_exists()
{
    return g_ErrorFormatString.length()>0;
}

static
void clear_last_error()
{
	g_ErrorFormatString.clear();

    deref(g_ErrorArguments);
    g_ErrorArguments = NIL;

    deref(g_ErrorCode);
    g_ErrorCode = NIL;

    deref(g_ErrorFunction);
    g_ErrorFunction = NIL;

    deref(g_ErrorLine);
    g_ErrorLine = NIL;
}

static
void 
err_print_helper(CTextStream* Buffer = 0)
{
    if (!last_error_exists())
    {
        // there is no error to print
        return;
    }

	CTextStream* fp = 0;
    if (Buffer == NULL)
    {
        // No buffer was supplied, so the printing should
        // go to "stdout" (which is the commander history).
        fp = stdoutstream;
    }
    else
    {
        // A buffer was supplied, so the error message
        // should be written there.
        fp = NULL;
        InitializeStringPrintInformation(Buffer);
    }

    CTRLTYPE save_flag = stopping_flag;
    stopping_flag = RUN;
    print_backslashes = true;

    if (g_ErrorArguments == NIL)
    {
        // this is a zero-argument error message
        ndprintf(
            fp,
            MESSAGETYPE_Error,
            g_ErrorFormatString);
    }
    else if (cdr(g_ErrorArguments) == NIL)
    {
        // this is a one-argument error message
        ndprintf(
            fp,
            MESSAGETYPE_Error,
            g_ErrorFormatString,
            car(g_ErrorArguments));
    }
    else
    {
        // this is a two-argument error message
        ndprintf(
            fp,
            MESSAGETYPE_Error,
            g_ErrorFormatString,
            car(g_ErrorArguments),
            cadr(g_ErrorArguments));
    }

    // Print the location where the error happened, if applicable.
    if (g_ErrorFunction != NIL && Buffer == NULL)
    {
        ndprintf(
            fp,
            MESSAGETYPE_Error,
            GetResourceString(L"LOCALIZED_TRACING_LOCATION"),
            g_ErrorFunction,
            g_ErrorLine);
    }

    // flush the file stream
    if (Buffer == NULL)
    {
        new_line(stdoutstream, MESSAGETYPE_Error);
    }
    else
    {
        FinalizeStringPrintInformation();
    }

    print_backslashes = false;
    stopping_flag = save_flag;
}

void err_print()
{
    // print the error to stdout
    err_print_helper();

    // clear the error now that it has been consumed
    clear_last_error();
}

NODE *
err_logo(
    ERR_TYPES ErrorType, 
    NODE *    ErrorMessageParameters,
    bool      IsUpLevel
    )
{
    clear_last_error();

    bool recoverable = false;
    bool warning = false;

    NODE * error_message = NIL;

    ref(ErrorMessageParameters);
    switch (ErrorType)
    {
    case FATAL:
        printfx(GetResourceString(L"LOCALIZED_ERROR_FATALINTERNAL"));
        exit(EXIT_FAILURE);

    case OUT_OF_MEM_UNREC:
        printfx(GetResourceString(L"LOCALIZED_ERROR_OUTOFMEMORY"));
        exit(EXIT_FAILURE);

    case OUT_OF_MEM:
        use_reserve_tank();
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_OUTOFMEMORY");
        break;

    case STACK_OVERFLOW:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_STACKOVERFLOW");
        break;

    case TURTLE_OUT_OF_BOUNDS:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_TURTLEOUTOFBOUNDS");
        break;

    case BAD_GRAPH_INIT:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_BADGRAPHINIT");
        break;

    case BAD_DATA_UNREC:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_BADDATA");
        error_message = cons_list(IsUpLevel ? ufun : fun, ErrorMessageParameters);
        break;
         
    case DIDNT_OUTPUT:
        if (didnt_output_name != NIL)
        {
            assign(last_call, didnt_output_name);
        }
        if (ErrorMessageParameters == NIL)
        {
            ErrorMessageParameters = vref(car(didnt_get_output));
            assign(ufun,      cadr(didnt_get_output));
            assign(this_line, cadr(cdr(didnt_get_output)));
        }

        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DIDNTOUTPUT");
        error_message = cons_list(last_call, ErrorMessageParameters);
        recoverable = true;
        break;

    case NOT_ENOUGH:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_NOTENOUGHINPUTS");
        error_message = cons_list(ErrorMessageParameters == NIL ? fun : ErrorMessageParameters);
        break;

    case BAD_DATA:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_BADDATA");
        error_message = cons_list(fun, ErrorMessageParameters);
        recoverable = true;
        break;

    case APPLY_BAD_DATA:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_BADDATA");
        error_message = cons_list(make_static_strnode(L"APPLY"), ErrorMessageParameters);
        recoverable = true;
        break;

    case TOO_MUCH:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_TOOMUCH");
        break;

    case DK_WHAT_UP:
        IsUpLevel = true;
        // FALLTHROUGH
    case DK_WHAT:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DONTSAYWHATTODOWITH");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case PAREN_MISMATCH:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_PARENMISMATCH");
        break;

    case NO_VALUE:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_NOVALUE");
        error_message = cons_list(ErrorMessageParameters);
        recoverable = true;
        break;

    case UNEXPECTED_PAREN:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_UNEXPECTEDPAREN");
        break;

    case UNEXPECTED_BRACKET:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_UNEXPECTEDBRACKET");
        break;

    case UNEXPECTED_BRACE:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_UNEXPECTEDBRACE");
        break;

    case DK_HOW:
        recoverable = true;
        /* FALLTHROUGH */

    case DK_HOW_UNREC:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DONTKNOWHOWTO");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case NO_CATCH_TAG:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_NOCATCHTAG");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case ALREADY_DEFINED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_ALREADYDEFINED");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case STOP_ERROR:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_STOPPING");
        yield_flag = true;
        break;

    case ALREADY_DRIBBLING:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_ALREADYDRIBBLING");
        break;

    case FILE_ERROR:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case IF_WARNING:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_IFWARNING");
        warning = true;
        break;

    case SHADOW_WARN:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_SHADOWWARNING");
        error_message = cons_list(ErrorMessageParameters);
        warning = true;
        break;

    case USER_ERR:
        if (ErrorMessageParameters == Unbound)
        {
            g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_USER");
        }
        else
        {
            IsUpLevel = true;

            g_ErrorFormatString = L"%p";
            error_message = cons_list(ErrorMessageParameters);
        }
        break;
         
    case IS_PRIM:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_ISPRIMITIVE");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case NOT_INSIDE:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_TONOTINSIDE");
        break;
         
    case AT_TOPLEVEL:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_ATTOPLEVEL");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case NO_TEST:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_NOTEST");
        error_message = cons_list(fun);
        break;

    case ERR_MACRO:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_BADMACROOUTPUT");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case DEEPEND:
        if (ErrorMessageParameters == NIL)
        {
            g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DEEPEND");
        }
        else
        {
            g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DEEPENDIN");
            error_message = cons_list(ErrorMessageParameters);
        }
        break;

    case WINDOW_ALREADY_EXISTS:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_WINDOWALREADYEXISTS");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case WINDOW_DOES_NOT_EXIST:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_WINDOWDOESNOTEXIST");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case DLL_LOAD_FAILED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DLLLOADFAILED");
        break;

    case DLL_NOT_LOADED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DLLNOTLOADED");
        break;

    case DLL_TYPE_DATA_NOT_PAIRED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED");
        break;

    case DLL_FUNCTION_NOT_FOUND:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND");
        break;

    case DLL_INVALID_DATA_TYPE:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DLLINVALIDDATATYPE");
        break;

    case DLL_INVALID_OUTPUT_TYPE:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE");
        break;

    case IMAGE_GENERAL:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_UNKNOWN");
        break;

    case IMAGE_GIF_LOAD_FAILED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_GIFREADFAILED");
        break;

    case IMAGE_GIF_SAVE_FAILED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_GIFSAVEFAILED");
        break;

    case IMAGE_BMP_OPEN_FAILED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_COULDNOTOPENBMP");
        break;

    case IMAGE_BMP_CREATE_FAILED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_COULDNOTCREATEBMP");
        break;

    case IMAGE_BMP_WRITE_FAILED:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_COULDNOTWRITEBMP");
        break;

    case IMAGE_BMP_INVALID:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_NOTVALIDBMP");
        break;

    case MIDI_GENERAL:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_MIDI")+L": %s";
        error_message = cons_list(ErrorMessageParameters);
        break;

    case MIDI_DEVICE_ALREADY_OPEN:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_MIDI") + L": " + GetResourceString(L"LOCALIZED_ERROR_MIDIALREADYOPEN");
        break;

    case MIDI_INVALID_DEVICE:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_MIDI") + L": " + GetResourceString(L"LOCALIZED_ERROR_MIDIINVALIDDEVICE");
        break;

    case MIDI_NOT_OPEN:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_MIDI") + L": " + GetResourceString(L"LOCALIZED_ERROR_MIDINOTOPEN");
        break;

    case TIMER_NOT_FOUND:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_TIMERNOTFOUND");
        break;

    case INVALID_STATE_FOR_INSTRUCTION:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION");
        error_message = cons_list(ErrorMessageParameters);
        break;

    case SPECIAL_FORM_PROC_UNREC:
        g_ErrorFormatString = GetResourceString(L"LOCALIZED_ERROR_SPECIALFORM");
        error_message = cons_list(IsUpLevel ? ufun : fun, ErrorMessageParameters);
        break;

    default:
        assert(!"Unexpected error code in err_logo()");
        printfx(GetResourceString(L"LOCALIZED_ERROR_UNKNOWN"));
        exit(EXIT_FAILURE);
    }

    deref(didnt_output_name);
    didnt_output_name = NIL;
    if (IsUpLevel && ufun != NIL)
    {
        assign(ufun,      last_ufun);
        assign(this_line, last_line);
    }

    g_ErrorCode = vref(make_intnode((FIXNUM) ErrorType));

    // replace the old error parameters with the new ones
    g_ErrorArguments = vref(error_message);

    if (ufun != NIL)
    {
        g_ErrorFunction = vref(ufun);
        g_ErrorLine     = vref(this_line);
    }

    deref(ErrorMessageParameters);

    if (warning)
    {
        err_print();
        return Unbound;
    }

    // If this error is recoverable and ERRACT is defined,
    // then we should run :ERRACT to get a new value.
    NODE * err_act_value = Erract.GetValue();
    NODE * new_throw_node;
    
    if (g_CatchErrorCount == 0 && 
        !g_IsRunningErractInstructionList && 
        err_act_value != NIL && 
        err_act_value != UNDEFINED)
    {
        // don't let one erract interrupt another
        set_is_running_erract_flag();

        // run the erract instruction list
        FIXNUM saved_value_status = g_ValueStatus;

        NODE * val = err_eval_driver(err_act_value);

        g_ValueStatus = saved_value_status;

        // reset the erract-is-running flag so that it can be called again
        clear_is_running_erract_flag();

        if (val != Unbound)
        {
            if (recoverable)
            {
                // Return the value returned from :ERRACT so that the
                // caller can replace the bad value with this one.
                return unref(val);
            }
            else
            {
                // This error wasn't recoverable, so ERRACT shouldn't
                // have output a new value to use.
                ndprintf(
					stdoutstream,
                    MESSAGETYPE_Error,
					GetResourceString(L"LOCALIZED_ERROR_DONTSAYWHATTODOWITH")+L"\n",
                    val);
                deref(val);
                new_throw_node = Toplevel.GetNode();
            }
        }
        else
        {
            // val is Unbound
            //
            // If the error is recoverable, this is a problem because
            // Erract didn't output a replacement value.
            //
            // If the error is not recoverable, then the Error was not handled.
            //
            // Either way, we throw Error
            new_throw_node = Error.GetNode();
        }
    }
    else
    {
        // We're in a catch block, or no erract is defined, or the erract 
        // instruction list that we are currently processing threw an error.
        // Either way, we should throw the error.
        new_throw_node = Error.GetNode();
    }

    stopping_flag = THROWING;
    assign(throw_node, new_throw_node);
    assign(output_node, Unbound);
    return Unbound;
}

NODE *err_logo(ERR_TYPES ErrorType, NODE *ErrorMessageParameters)
{
    return err_logo(ErrorType, ErrorMessageParameters, false);
}

NODE *lerror(NODE *)
{
    if (!last_error_exists())
    {
        return NIL;
    }

    // format the error message into a buffer
	CStringTextStream cts;

    err_print_helper(&cts);

    // return the ERROR 4-tuple [code message function line]
    NODE * val = cons_list(
        g_ErrorCode,
        make_strnode(cts.GetContent()),
        g_ErrorFunction,
        g_ErrorLine);

    clear_last_error();

    return val;
}

NODE *lpause(NODE*)
{
    if (last_error_exists())
    {
        err_print();
    }

    NODE * uname = vref(ufun);
    ufun = NIL;

    // Print "Pausing..." to the commander history box.
    // This does not print a newline, because the pausing
    // line may also include the name of the procedure
    // which ran PAUSE.
    ndprintf(stdoutstream, MESSAGETYPE_Normal, GetResourceString(L"LOCALIZED_PAUSING"));

    jmp_buf sav_iblk;
    memcpy(sav_iblk, iblk_buf, sizeof(sav_iblk));

    // Loop reading commands from the user until they
    // exit Pause mode.
    bool saved_input_blocking = GetInputBlocking();
	GetInputBlocking() = false;
    FIXNUM saved_value_status = g_ValueStatus;
    while (RUNNING)
    {
        // uname is the CASEOBJ for the procedure that was running
        // when PAUSE was invoked (either directly by calling PAUSE
        // or when the Pause button was pressed).
        // If PAUSE was run at the toplevel, then uname is NIL.
        if (uname != NIL) 
        {
            print_node(stdoutstream, MESSAGETYPE_Normal, uname);
        }

        // Flush the line, which might look something like
        // "Pausing...<procedure name>" on the first iteration
        // and just "<procedure name>" on subsequent iterations.
        // This made a lot more sense in UCBLogo, when the prompt
        // was "<procedure name>? ", but now that the input
        // is taken from separate dialog box, this just looks weird,
        // especially when uname is NIL.
        new_line(stdoutstream, MESSAGETYPE_Normal);

        // get the interactive input for the "pause"
        GetInputMode() = INPUTMODE_Pause;
        NODE * elist = vref(reader(stdinstream, L"? "));
        if (NOT_THROWING) 
        {
            assign(elist, parser(elist, true));
        }
        else 
        {
            assign(elist, NIL);
        }
		GetInputMode() = INPUTMODE_None;

        // check if there are other things to do
        MyMessageScan();

        // REVISIT: This might legacy from UCBLogo that is
        // inappropriate in FMSLogo, since "stdin" is the commander
        // and never reaches the end of the file.
        if (feof(stdin)) 
        {
            lbye(NIL);
        }

        // Evaluate the command that the given by the user.
        // If the user pressed Cancel, then they'll run CONTINUE.
        g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
        eval_driver(elist);
 
        if (stopping_flag == THROWING)
        {
            if (compare_node(throw_node, Pause, true) == 0)
            {
                // The user ran CONTINUE, which is implemented by
                // throwing to the "Pause" label.
                // Reset back to a running node, cleanup, and return.
                NODE * val = vref(output_node);
                assign(output_node, Unbound);
                stopping_flag = RUN;

                // REVISIT: This is the same cleanup logic
                // that is run on exit, so it should be possible
                // to turn this into a break.
                memcpy(iblk_buf, sav_iblk, sizeof(sav_iblk));

				GetInputBlocking() = saved_input_blocking;
                g_ValueStatus  = saved_value_status;
                if (uname != NIL)
                {
                    assign(ufun, uname);
                    deref(uname);
                }

                deref(elist);
                return unref(val);
            }
            else if (Error.Equals(throw_node))
            {
                // There was an error in the instruction that the
                // user provided.  Print the error, but remain in
                // pause mode.
                err_print();
                stopping_flag = RUN;
            }
        }

        check_stop(false);

        deref(elist);
    }

    memcpy(iblk_buf, sav_iblk, sizeof(sav_iblk));

	GetInputBlocking() = saved_input_blocking;
    unblock_input();
    g_ValueStatus = saved_value_status;
    if (uname != NIL)
    {
        assign(ufun, uname);
        deref(uname);
    }
   
    return Unbound;
}

NODE *lhalt(NODE *)
{
    // End all timers that could have been started
    // by a call to SETTIMER.
    halt_all_timers();

    // Cancel any pending events that may execute more code.
    emptyqueue();

    // throw a Stop error to stop the current execution.
    err_logo(STOP_ERROR, NIL);

    return Unbound;
}

NODE *lyield(NODE *)
{
    // set flag
    yield_flag = true;
    return Unbound;
}

NODE *lnoyield(NODE *)
{
    // clear flag
    yield_flag = false;
    return Unbound;
}

NODE *lcontinue(NODE *args)
{
    stopping_flag = THROWING;
    assign(throw_node, Pause);
    if (args != NIL)
    {
        assign(output_node, car(args));
    }
    else
    {
        assign(output_node, Unbound);
    }

    return Unbound;
}


void uninitialize_error()
{
    deref(throw_node);
    throw_node = NIL;

    clear_last_error();
}
