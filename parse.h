// Copyright (C) 2005 by David Costanzo

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __PARSER_H_
#define __PARSER_H_

#include <stdio.h>
#include "pch.h"
// types
struct NODE;

enum INPUTMODE
{
    INPUTMODE_None,
    INPUTMODE_To,
    INPUTMODE_List,
    INPUTMODE_Pause,
};

// function variables
extern wchar_t rd_fgetwc(FILE *strm, bool unicode = false);
extern void rd_clearbuffer(FILE *strm);
extern NODE *reader(FILE *strm, const wchar_t *prompt,bool unicode = false);
extern NODE *parser(NODE *nd, bool semi, bool unicode = false);
extern NODE *lparse(NODE *args);
extern NODE *lparse(NODE *args,bool unicode);
extern NODE *runparse(NODE *ndlist);
extern NODE *runparse(NODE *ndlist, bool unicode);
extern NODE *lrunparse(NODE *args);
extern NODE *lrunparse(NODE *args, bool unicode);
extern void uninitialize_parser(void);

// global variables

extern bool& GetInputBlocking();
extern INPUTMODE& GetInputMode();
extern void SetErrorProcName(NODE * name);
extern void SetErrorToLine(NODE * line);
extern void OpenDribble(NODE * arg);
extern void CloseDribble();
extern void DribbleWriteChar(wchar_t ch);
extern void DribbleWriteText(const wchar_t * text);
extern void DribbleWriteLine(const wchar_t * text);
#endif // __PARSER_H_
