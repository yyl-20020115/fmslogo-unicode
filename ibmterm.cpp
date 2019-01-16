/* ibmterm.cpp         IBM screen module             mak
 *
 *   Copyright (C) 1995 by the Regents of the University of California
 *   Copyright (C) 1995 by George Mills
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
   #include "ibmterm.h"
   #include "error.h"
   #include "wrksp.h"
   #include "logodata.h"
   #include "graphwin.h"
   #include "logoeventqueue.h"
//   #include "debugheap.h"

   #include "localizedstrings.h"
#endif
#ifndef _WINDOWS
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>
#endif
/************************************************************/

bool check_stop(bool scan_for_messages)
{
    if (scan_for_messages)
    {
        MyMessageScan();
    }

    if (IsTimeToHalt)
    {
        IsTimeToHalt = false;
        emptyqueue();
        err_logo(STOP_ERROR, NIL);
        return true;
    }

    if (IsTimeToPause)
    {
        IsTimeToPause = false;
        to_pending = false;
        lpause(NIL);
    }

    return false;
}


void pen_down()
{
    PENSTATE & penState = GetPenStateForSelectedTurtle();

    penState.Mode      = COPY_PUT;
    penState.IsErasing = false;
}

void pen_reverse()
{
    PENSTATE & penState = GetPenStateForSelectedTurtle();

    penState.Mode      = XOR_PUT;
    penState.IsErasing = false;
}

void pen_erase()
{
    PENSTATE & penState = GetPenStateForSelectedTurtle();

    if (!penState.IsErasing)
    {
        penState.Mode      = COPY_PUT;
        penState.IsErasing = true;
    }
}

void set_list_pen_pattern(NODE *arg)
{
    unsigned char pat[8];

    NODE * cur_num = arg;
    for (int count = 0; count < 8; count++)
    {
        NODE * temp = cnv_node_to_numnode(car(cur_num));
        pat[count] = (char) getint(temp);
        if (cdr(cur_num) != NIL)
        {
            cur_num = cdr(cur_num);
        }
        gcref(temp);
    }
    // setfillpattern(pat, getcolor());
}

void get_pen_pattern(char * /* pat */)
{
    // getfillpattern(pat);
}

NODE *get_node_pen_pattern()
{
    /*
      unsigned char pat[8];

      getfillpattern(pat);
      return(cons(make_intnode((FIXNUM)(pat[0])),
          cons(make_intnode((FIXNUM)(pat[1])),
          cons(make_intnode((FIXNUM)(pat[2])),
          cons(make_intnode((FIXNUM)(pat[3])),
          cons(make_intnode((FIXNUM)(pat[4])),
          cons(make_intnode((FIXNUM)(pat[5])),
          cons(make_intnode((FIXNUM)(pat[6])),
          cons(make_intnode((FIXNUM)(pat[7])),
          NIL)))))))));
    */
    return NIL;
}

NODE *get_node_pen_mode()
{
    const wchar_t * mode;

    if (GetPenStateForSelectedTurtle().IsErasing)
    {
        mode = GetResourceString(L"LOCALIZED_PENMODE_ERASE");
    }
    else if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
    {
        mode = GetResourceString(L"LOCALIZED_PENMODE_REVERSE");
    }
    else
    {
        mode = GetResourceString(L"LOCALIZED_PENMODE_PAINT");
    }

    return make_static_strnode(mode);
}

void erase_screen()
{
    ibm_clear_screen();
}

bool button()
{
    return false;
}
#ifndef _WINDOWS
int console_fd = -1;
void init_tone()
{
	if ((console_fd = open("/dev/console", O_WRONLY)) == -1)
	{
		//BAD_FD
	}
}

void uninit_tone()
{
	if (console_fd != -1) {
		close(console_fd);
	}
}
#else
void init_tone() {

}
void uninit_tone() {

}
#endif
void tone(FIXNUM frequency, FIXNUM duration)
{
    if (frequency < 37)
    {
        frequency = 37;
    }

#ifdef _WINDOWS
    // use the Win32 Beep
    Beep(frequency, duration);
#else
	if (console_fd != -1) 
	{
		int magical_fairy_number = 1190000 / frequency;

		ioctl(console_fd, KIOCSOUND, magical_fairy_number);
		usleep(1000 * duration);
		ioctl(console_fd, KIOCSOUND, 0);
	}
#endif
}
