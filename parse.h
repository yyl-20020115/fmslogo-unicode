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
extern int rd_getc(FILE *strm);
extern void rd_clearbuffer(FILE *strm);
extern NODE *reader(FILE *strm, const wchar_t *prompt);
extern NODE *parser(NODE *nd, bool semi);
extern NODE *lparse(NODE *args);
extern NODE *runparse(NODE *ndlist);
extern NODE *lrunparse(NODE *args);
extern void uninitialize_parser(void);

// global variables
extern FILE *loadstream;
extern FILE *dribblestream;
extern bool input_blocking;
extern enum INPUTMODE input_mode;
extern NODE *deepend_proc_name;
extern NODE *g_ToLine;

#endif // __PARSER_H_
