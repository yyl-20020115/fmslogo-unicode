/*
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
#include <wx/string.h>
#ifdef _WINDOWS
    #include <windows.h>
#endif
    #include "mmwind.h"
    #include "argumentutils.h"
    #include "stringprintednode.h"
    #include "logocore.h"
    #include "logodata.h"
    #include "lists.h"
    #include "messagebox.h"
    #include "graphics.h"
    #include "error.h"
    #include "init.h"
    #include "eval.h"
    #include "parse.h"
    #include "ibmterm.h"
    #include "screenwindow.h"
//    #include "debugheap.h"

    #include "devwind.h"

    #include "localizedstrings.h"
#endif

// global variables
wxString mci_callback;    // MCI callback code
wxString timer_callback[MAX_TIMERS];      // timer cb malloc'd as needed

static HMIDIOUT hMidiOut = 0;

NODE *lsound(NODE *arg)
{
    /* open sound and get arg list */
    NODE *args = car(arg);

    /* must be a list that contains something */
    if (is_list(args) && (args != NIL))
    {

        /* count items in list and check that they are pairs */
        int total_args = list_length(args);
        bool even_args = even_p(total_args);

        /* if sound creation ok and we have pairs continue */
        if (even_args)
        {
            /* play each freq/duration pair */
            for (arg = args;
                 arg != NIL;
                 arg = cdr(arg))
            {
                int duration = 0;

                int hertz = int_arg(arg);
                if (cdr(arg) != NIL)
                {
                    duration = int_arg(arg = cdr(arg));
                }

                /* play it */
                tone(hertz, duration);
            }
        }
        else
        {
            ShowMessageAndStop(
                GetResourceString(L"LOCALIZED_ERROR_SOUND"), 
                GetResourceString(L"LOCALIZED_ERROR_BADINPUTNOTPAIRED"));
        }
    }
    else
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_SOUND"),
            GetResourceString(L"LOCALIZED_ERROR_BADINPUT"));
    }

    return Unbound;
}

static
void
ThrowGeneralMidiError(
    UINT MidiError
    )
{
	wchar_t midiErrorBuffer[MAX_BUFFER_SIZE + 1] = { 0 };
    midiOutGetErrorText(MidiError, midiErrorBuffer, ARRAYSIZE(midiErrorBuffer)-1);

    // report the error
    err_logo(MIDI_GENERAL, make_strnode(midiErrorBuffer));
}


NODE *lmidiopen(NODE *args)
{
    if (hMidiOut != NULL)
    {
        // The device is already open.
        err_logo(MIDI_DEVICE_ALREADY_OPEN, NIL);
        return Unbound;
    }

    // The device is not already open, so open it.
    UINT id = MIDIMAPPER;

    if (args != NIL)
    {
        id = int_arg(args);
        if (stopping_flag == THROWING)
        {
            // non-integer input
            return Unbound;
        }
        if (id > midiOutGetNumDevs())
        {
            err_logo(MIDI_INVALID_DEVICE, NIL);
            return Unbound;
        }
    }

	MIDIOUTCAPS moc = { 0 };
    UINT MidiError = midiOutGetDevCaps(id, &moc, sizeof(moc));
    if (!MidiError) 
    {
        MidiError = midiOutOpen(&hMidiOut, id, NULL, 0L, 0L);
    }

    if (MidiError)
    {
        // report the midi error
        ThrowGeneralMidiError(MidiError);
        return Unbound;
    }

    NODE * targ = make_strnode(moc.szPname);
    NODE * val = parser(targ, false);
    return val;
}

NODE *lmidiclose(NODE *  /*args*/)
{
    if (hMidiOut == NULL)
    {
        // the MIDI device isn't open
        err_logo(MIDI_NOT_OPEN, NIL);
        return Unbound;
    }

    // Close the device
    UINT MidiError = midiOutClose(hMidiOut);
    hMidiOut = 0;

    if (MidiError)
    {
        ThrowGeneralMidiError(MidiError);
        return Unbound;
    }

    return Unbound;
}

NODE *lmidimessage(NODE *arg)
{
    union
    {
        long mylong;
        char mybyte[4];
    }
    bytetolong;

    if (hMidiOut == NULL)
    {
        // the MIDI device isn't open
        err_logo(MIDI_NOT_OPEN, NIL);
        return Unbound;
    }

    NODE * args = car(arg);

    if (!is_list(args) || (args == NIL))
    {
        // The input must be a list with something in it.
        err_logo(BAD_DATA_UNREC, args);
        return Unbound;
    }

    UINT MidiError;

    // if not system exclusive then use shortmsg else use longmsg
    if (int_arg(args) != 0xF0)
    {

        // pack 3 bytes at a time and send them as short messages
        arg = args;

        while (arg != NIL)
        {
            bytetolong.mylong = 0L;
            bytetolong.mybyte[0] = int_arg(arg);
            if (cdr(arg) != NIL) bytetolong.mybyte[1] = int_arg(arg = cdr(arg));
            if (cdr(arg) != NIL) bytetolong.mybyte[2] = int_arg(arg = cdr(arg));
            MidiError = midiOutShortMsg(hMidiOut, bytetolong.mylong);
            if (MidiError) break;
            if (arg != NIL) arg = cdr(arg);
        }

    }
    else
    {
        // count elements in list so we can allocate buffer 
        int i = list_length(args);

        /* allocate structure buffer */
        // REVISIT: why not use malloc()?
        HANDLE    HdrHandle = (HANDLE) GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, sizeof(MIDIHDR));
        MIDIHDR * MidiOutHdr = (MIDIHDR *) GlobalLock((HGLOBAL) HdrHandle);

        HANDLE DataHandle = (HANDLE) GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, i);
        LPSTR  MidiOutData = (CHAR *) GlobalLock((HGLOBAL) DataHandle);

        /* pack the buffer array and set size */
        arg = args;

        for (int j = 0; j < i; j++)
        {
            MidiOutData[j] = int_arg(arg);
            arg = cdr(arg);
        }

        MidiOutHdr->dwBufferLength = i;

        MidiOutHdr->lpData = MidiOutData;

        /* prepare it, send it out, and unprepare it */

        MidiError = midiOutPrepareHeader(hMidiOut, MidiOutHdr, sizeof(MIDIHDR));
        if (!MidiError) MidiError = midiOutLongMsg(hMidiOut, MidiOutHdr, sizeof(MIDIHDR));
        if (!MidiError) MidiError = midiOutUnprepareHeader(hMidiOut, MidiOutHdr, sizeof(MIDIHDR));

        /* free buffer and struct */

        GlobalUnlock(DataHandle);
        GlobalFree(DataHandle);

        GlobalUnlock(HdrHandle);
        GlobalFree(HdrHandle);
    }

    if (MidiError)
    {
        // Let the user know that a midi error occured.
        ThrowGeneralMidiError(MidiError);
        return Unbound;
    }

    return Unbound;
}

NODE *lmci(NODE *args)
{
    // get mci command string
    CStringPrintedNode command(car(args));

    // check for optional callback routine 
	wxString callback;
    if (cdr(args) != NIL)
    {
        callback = cnv_strnode_string(cdr(args));
    }

	wchar_t mciReturnBuffer[MAX_BUFFER_SIZE + 1] = { 0 };

    // send out command 
    DWORD mciError = mciSendString(
		(const wxString&)command,
        mciReturnBuffer,
        ARRAYSIZE(mciReturnBuffer)-1,
        GetMainWindow());

    if (mciError != ERROR_SUCCESS)
    {
        // let user know about the error
		wchar_t mciErrorBuffer[MAX_BUFFER_SIZE + 1] = { 0 };
        mciGetErrorString(mciError, mciErrorBuffer, ARRAYSIZE(mciErrorBuffer)-1);
        ShowMessageAndStop(GetResourceString(L"LOCALIZED_ERROR_MCI"), mciErrorBuffer);
    }
    else
    {
        // if something was returned then return it to user 
        if (mciReturnBuffer[0] != '\0')
        {
            NODE * targ = make_strnode(mciReturnBuffer);
            NODE * val = parser(targ, false);
            return val;
        }
    }

    return Unbound;
}

NODE *lsettimer(NODE *args)
{
    // get the timer id 
    int id = getint(ranged_integer_arg(args, 1, MAX_TIMERS - 1));

    // get delay
    int delay = getint(nonnegative_int_arg(args = cdr(args)));

    // get callback
	wxString callback = cnv_strnode_string(args = cdr(args));

    if (NOT_THROWING)
    {
		timer_callback[id] = callback;

        // if not set sucessfully error
        if (!::SetTimer(GetMainWindow(), id, delay, NULL))
        {
            err_logo(OUT_OF_MEM, NIL);
            return Unbound;
        }
    }

    return Unbound;
}

NODE *lcleartimer(NODE *args)
{
    // get args
    int id = getint(ranged_integer_arg(args, 1, MAX_TIMERS - 1));
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // if timer was not set let user know
    if (!::KillTimer(GetMainWindow(), id))
    {
        err_logo(TIMER_NOT_FOUND, NIL);
        return Unbound;
    }

    return Unbound;
}

void init_timers()
{
    //for (size_t i = 0; i < MAX_TIMERS; i++)
    //{
    //    timer_callback[i].clear();
    //}
}

void halt_all_timers()
{
    for (int i = 1; i < MAX_TIMERS; i++)
    {
        ::KillTimer(GetMainWindow(), i);
    }
}

void uninitialize_timers()
{
    for (int id = 0; id < MAX_TIMERS; id++)
    {
        if (timer_callback[id].length()>0)
        {
            KillTimer(GetMainWindow(), id);

            //free(timer_callback[id]);
            //timer_callback[id] = NULL;
        }
    }
}

NODE *lplaywave(NODE *args)
{
    CStringPrintedNode fileName(car(args));

    int flag = getint(nonnegative_int_arg(args = cdr(args)));

    if (((const wxString&)fileName).length() == 0)
    {
        sndPlaySound(NULL, flag);
    }
    else
    {
        sndPlaySound((const wxString&)fileName, flag);
    }

    return Unbound;
}
