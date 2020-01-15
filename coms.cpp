/*
 * coms.cpp     program execution control module      dvb
 *
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
  #include <math.h>
  #include <time.h>
  #include <string.h>


  #include "coms.h"
  #include "logocore.h"
  #include "logodata.h"
  #include "eval.h"
  #include "init.h"
  #include "error.h"
  #include "logomath.h"
  #include "parse.h"
  #include "lists.h"
  #include "graphwin.h"
  #include "graphics.h"
  #include "stringprintednode.h"
  #include "stringadapter.h"

  #include <wx/utils.h>
  #include <wx/time.h>

#endif

// ift_iff_flag: flag for if TEST has been called within the scope
// -1 : TEST has not been called.
//  0 : TEST "FALSE has been called.
//  1 : TEST "TRUE has been called.
FIXNUM ift_iff_flag = -1;

NODE *make_cont(enum labels cont, NODE *val)
{
    NODE *retval = cons(NIL, val);
    retval->nunion.ncons.ncar = reinterpret_cast<NODE *>(cont);
    settype(retval, CONT);
    return retval;
}

NODE *loutput(NODE *arg)
{
    if (NOT_THROWING)
    {
        stopping_flag = OUTPUT;
        assign(output_node, car(arg));
    }
    return Unbound;
}

NODE *lstop(NODE *)
{
    if (NOT_THROWING)
    {
        stopping_flag = STOP;
    }
    return Unbound;
}

NODE *lthrow(NODE *arg)
{
    if (NOT_THROWING)
    {
        if (Error.Equals(car(arg)))
        {
            // this a THROW "ERROR
            if (cdr(arg) != NIL)
            {
                NODE * secondInput = cadr(arg);

                // A third input was specified.
                // If it's a number, then we may have a special case 
                // to throw an error as if it were an internal error.
                NODE * number = cnv_node_to_numnode(secondInput);

                // convert floating point numbers to integers
                FIXNUM value = -1;
                FLONUM f;
                if (nodetype(number) == INTEGER)
                {
                    value = getint(number);
                }
                else if (nodetype(number) == FLOATINGPOINT &&
                         fmod((f = getfloat(number)), 1.0) == 0.0 && 
                         f >= -(FLONUM) FIXNUM_MAX && 
                         f < (FLONUM) FIXNUM_MAX)
                {
                    value = f;
                }

                gcref(number);

                if (value == BAD_DATA_UNREC)
                {
                    if (cddr(arg))
                    {
                        NODE * thirdInput = car(cddr(arg));
                        err_logo(BAD_DATA_UNREC, thirdInput, true);
                    }
                    else
                    {
                        // the second input is a simple error text
                        err_logo(USER_ERR, secondInput);
                    }
                }
                else
                {
                    // the second input is a simple error text
                    err_logo(USER_ERR, secondInput);
                }
            }
            else
            {
                err_logo(USER_ERR, Unbound);
            }
        }
        else
        {
            stopping_flag = THROWING;
            assign(throw_node, car(arg));
            if (cdr(arg) != NIL)
            {
                assign(output_node, cadr(arg));
            }
            else
            {
                assign(output_node, Unbound);
            }
        }
    }
    return Unbound;
}

NODE *lcatch(NODE *args)
{
    return make_cont(catch_continuation, cons(car(args), lrun(cdr(args))));
}

bool boolean_arg(NODE *args)
{
    NODE *arg = car(args);

    while (NOT_THROWING)
    {
        if (Truex.Equals(arg)) 
        {
            return true;
        }
        if (Falsex.Equals(arg))
        {
            return false;
        }
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }

    // default to "true" for backward compatability.
    // (This used to return to -1, which is more likely to behave like "true" than "false").
    return true;
}

NODE *lgoto(NODE *args)
{
    return make_cont(goto_continuation, car(args));
}

NODE *ltag(NODE * /* args */)
{
    return Unbound;
}

NODE *lnot(NODE *args)
{
    bool arg = boolean_arg(args);

    if (NOT_THROWING)
    {
        return true_or_false(!arg);
    }

    return Unbound;
}

NODE *land(NODE *args)
{
    // if there are no false inputs, then the entire expression is true
    NODE * rval = Truex.GetNode();
   
    for (NODE* current_arg = args;
         current_arg != NIL;
         current_arg = cdr(current_arg))
    {
        bool arg = boolean_arg(current_arg);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        if (!arg)
        {
            // found a false input, so entire expression is false
            rval = Falsex.GetNode();

            // Don't break because we want to validate 
            // the rest of the inputs.
        }
    }

    return rval;
}

NODE *lor(NODE *args)
{
    // if there are no true inputs, then the entire expression is false
    NODE * rval = Falsex.GetNode();
   
    for (NODE* current_arg = args;
         current_arg != NIL;
         current_arg = cdr(current_arg))
    {
        bool arg = boolean_arg(current_arg);
        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        if (arg)
        {
            // found a true input, so entire expression is true
            rval = Truex.GetNode();

            // Don't break because we want to validate 
            // the rest of the inputs.
        }
    }

    return rval;
}

NODE *runnable_arg(NODE *args)
{
    NODE *arg = car(args);

    if (!is_aggregate(arg))
    {
        setcar(args, parser(arg, TRUE));
        arg = car(args);
    }
    while (!is_list(arg) && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, arg));
        arg = car(args);
    }
    return arg;
}

NODE *lif(NODE *args)  // macroized
{
    if (cddr(args) != NIL)
    {
        return lifelse(args);
    }

    bool pred = boolean_arg(args);
    NODE * yes = runnable_arg(cdr(args));
    if (NOT_THROWING)
    {
        if (pred) 
        {
            return yes;
        }
        return NIL;
    }

    return Unbound;
}

NODE *lifelse(NODE *args)              // macroized
{
    bool pred = boolean_arg(args);
    NODE* yes = runnable_arg(cdr(args));
    NODE* no = runnable_arg(cddr(args));
    if (NOT_THROWING)
    {
        if (pred) 
        {
            return yes;
        }
        return no;
    }
    return Unbound;
}

NODE *lrun(NODE *args)                 // macroized
{
    NODE *arg = runnable_arg(args);

    if (NOT_THROWING)
    {
        return arg;
    }
    return Unbound;
}

NODE *lrunresult(NODE *args)
{
    return make_cont(runresult_continuation, lrun(args));
}

NODE *lrepeat(NODE *args)
{
    NODE * cnt       = nonnegative_int_arg(args);
    NODE * to_repeat = lrun(cdr(args));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    return make_cont(repeat_continuation, cons(cnt, to_repeat));
}

NODE *lrepcount(NODE *)
{
    return make_intnode((FIXNUM) repcountup);
}

NODE *lforever(NODE *args)
{
    NODE *to_repeat = lrun(args);

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    return make_cont(repeat_continuation, cons(make_intnode(-1), to_repeat));
}

NODE *ltest(NODE *args)
{
    bool arg = boolean_arg(args);

    if (tailcall != 0)
    {
        return Unbound;
    }

    if (NOT_THROWING)
    {
        ift_iff_flag = arg ? 1 : 0;
        dont_fix_ift = 1;
    }
    return Unbound;
}

NODE *liftrue(NODE *args)
{
    if (ift_iff_flag < 0)
    {
        // TEST has not been run in this scope
        return err_logo(NO_TEST, NIL);
    }
    else if (ift_iff_flag > 0)
    {
        // TEST "TRUE has been run in this scope
        return lrun(args);
    }
    else
    {
        // TEST "FALSE has been run in this scope
        return NIL;
    }
}

NODE *liffalse(NODE *args)
{
    if (ift_iff_flag < 0)
    {
        // TEST has not been run in this scope
        return err_logo(NO_TEST, NIL);
    }
    else if (ift_iff_flag == 0)
    {
        // TEST "FALSE has been run in this scope
        return lrun(args);
    }
    else
    {
        // TEST "TRUE has been run in this scope
        return NIL;
    }
}


NODE *lbye(NODE *)
{
    exit_program();
    return Unbound;
}

/* LOGO time */
NODE *ltime(NODE *)
{
    // Get the current time.
    time_t tvec;
    time(&tvec);

    // There is a mutual incompatibility in Microsoft's C runtime
    // and GNU's libc in the behavior of ctime.  Specifically, they
    // both read the timezone from the "TZ" environment variable before
    // checking the system localtime.  The problem is that they interpret
    // the value differently and if you give a GNU variable to Microsoft's
    // C runtime, it acts as if the time zone were GMT.  As a result, if
    // you invoke FMSLogo from a GNU environment, like cygwin's bash, TIME
    // returns the wrong time.
    //
    // To work around this, we unset the TZ so that ctime() only reads the
    // time zone from the operating system.  We are careful to reset TZ
    // afterwards so that any invocations of SHELL will include all of the
    // inherited environment variables.
    const wxString tz(L"TZ");
    wxString tzEnvironmentVariable;
    bool mustResetEnvironmentVariable = wxGetEnv(tz, &tzEnvironmentVariable);
    if (mustResetEnvironmentVariable)
    {
        wxUnsetEnv(tz);
    }

    // Convert the time to the local timezone and render it as a
    // string.  ctime() formats a string contains that exactly 26
    // characters and has the form:
    //    Sat Nov 05 20:46:46 2016\n\0
    //this is for compatible with linux
    wxString formattedTime = ctime(&tvec);

    // Remove the trailing newline.
    NODE * arg = make_strnode(
        formattedTime,
        formattedTime.length(),
        STRING,
        strnzcpy);

    // Put the string into a list.
    NODE * val = parser(arg, false);

    if (mustResetEnvironmentVariable)
    {
        wxSetEnv(tz, tzEnvironmentVariable);
    }

    return val;
}

/* LOGO time */
NODE *ltimemilli(NODE *)
{
    FIXNUM timeInMilliseconds = 0;
#ifdef _WINDOWS
    timeInMilliseconds = GetTickCount();
#else
    // TIMEMILLI is defined to output the number of milliseconds which
    // have elapsed since Windows started (that is, ::GetTickCount()).
    // This is difficult on a GNU/Linux system and not worth the
    // effort.  It should be acceptable to have an ever-increasing
    // time in the granularity of milliseconds which can occasionally
    // wrap around.
    wxLongLong utcTimeMilliAtStartup = wxGetUTCTimeMillis(); 

    // Get the lower 32 bits from the wxLongLong.  This is
    // similar to a wrap-around, assuming that the system started
    // at the last wrap-around.
    timeInMilliseconds = utcTimeMilliAtStartup.GetLo();
#endif
    return make_intnode(timeInMilliseconds);
}

NODE *lwait(NODE *args)
{
    NODE * num = nonnegative_numeric_arg(args);
    if (NOT_THROWING)
    {
        FLONUM input = numeric_node_to_flonum(num);

        // The input is in 60ths of a second.  To convert to milliseconds:  
        //   (input / 60) * 1000 = input * 50 / 3 
        DWORD totalTicksToWait = g_round(input * 50.0 / 3.0);

        // Do a busy sleep so that a long WAIT can be interrupted by a HALT
        wxLongLong endTime = wxGetUTCTimeMillis() + totalTicksToWait;
        while (wxGetUTCTimeMillis() < endTime && !IsTimeToHalt) 
        {
            MyMessageScan();

            if (wxGetUTCTimeMillis() + 10 < endTime)
            {
                // We're more than 10 ms away from the target time,
                // so we don't risk missing our target time by yielding.
                wxMilliSleep(1);  // yield
            }
        }     
    }

    return Unbound;
}

NODE *lshell(NODE *args)
{
  bool isOk = false;
#ifdef _WINDOWS
  CStringPrintedNode shellCommand(car(args));

  bool waitForChildProcess=false;
  if (cdr(args) != NIL)
  {
      // a second input was given
      waitForChildProcess = boolean_arg(cdr(args));
  }
  else
  {
      // no second input was given
      waitForChildProcess = false;
  }

  if (stopping_flag == THROWING)
  {
      // we were passed invalid arguments
      return Unbound;
  }
	STARTUPINFO         startupInfo = { 0 };
	PROCESS_INFORMATION processInfo = { 0 };

	const wxString& content = shellCommand.GetContent();

	wchar_t* shellBuffer = (wchar_t*)malloc(sizeof(wchar_t)*(content.length() + 1));
	if (shellBuffer != 0) {
    wcsncpy(shellBuffer, content, content.length() + 1);

    isOk = CreateProcess(
			NULL,
			shellBuffer,
			NULL,  // process security attribute
			NULL,  // thread security attributes
			FALSE, // don't inherit handles
			0,     // creation flags
			NULL,  // use FMSLogo's environment
			NULL,  // use FMSLogo's current working directory
			&startupInfo,
			&processInfo)!=0;
		if (isOk)
		{
			if (waitForChildProcess)
			{
				// Wait for the child process to exit.
				// Do a busy wait so that it can be interrupted by a HALT
				DWORD waitStatus = WAIT_TIMEOUT;
				while (waitStatus == WAIT_TIMEOUT && !IsTimeToHalt)
				{
					MyMessageScan();
					waitStatus = ::WaitForSingleObject(processInfo.hProcess, 10);
				}
			}

			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		free(shellBuffer);
	}

#endif
    return true_or_false(isOk);
}
