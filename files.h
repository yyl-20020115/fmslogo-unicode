// -*- c++ -*-
// Copyright (C) 1995 by George Mills
//
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

#ifndef __FILES_H_
#define __FILES_H_

#include <stdio.h>
#include <assert.h>

struct NODE;

// types
class CFileStream
{
public:
    CFileStream(FILE * DefaultStream);

    void   SetStreamToOpenFile(NODE * FileName);
    void   ResetToDefaultStream();
    bool   IsNamed(NODE * FileName) const;
    bool   IsBinary() const;
    NODE * GetName() const;
    NODE * GetPosition() const;
    void   SetPosition(NODE * Arguments);

    FILE *& GetStream()
    {
        assert(m_Stream != NULL);
        return m_Stream;
    }

    void SetStream(FILE * Stream)
    {
        assert(m_Stream != NULL);
        m_Stream = Stream;
        assert(m_Stream != NULL);
    }

private:
    NODE *  m_Name;
    FILE *  m_Stream;
    FILE *  m_DefaultStream;
    bool    m_StreamIsBinary;
};

// global variables
extern NODE *current_line;

// function declarations
extern void PrintWorkspaceToFileStream(FILE * FileStream);
extern NODE *ldribble(NODE *arg);
extern NODE *lnodribble(NODE *arg);
extern NODE *lopenread(NODE *arg);
extern NODE *lopenwrite(NODE *arg);
extern NODE *lopenappend(NODE *arg);
extern NODE *lopenupdate(NODE *arg);
extern NODE *lallopen(NODE *arg);
extern NODE *lclose(NODE *arg);
extern NODE *lsetwrite(NODE *arg);
extern NODE *lsetread(NODE *arg);
extern NODE *lreader(NODE *arg);
extern NODE *lwriter(NODE *arg);
extern NODE *lerasefile(NODE *arg);
extern NODE *lsave(NODE *arg);
extern void runstartup(NODE *oldst);
extern void silent_load(NODE *arg, const wchar_t *prefix);
extern NODE *lload(NODE *arg);
extern NODE *lreadlist(NODE *arg);
extern NODE *lreadword(NODE *arg);
extern NODE *lreadrawline(NODE *arg);
extern NODE *lreadchar(NODE *arg);
extern NODE *lreadchars(NODE *args);
extern NODE *leofp(NODE *arg);
extern NODE *lkeyp(NODE *arg);
extern NODE *lreadpos(NODE *arg);
extern NODE *lsetreadpos(NODE *arg);
extern NODE *lwritepos(NODE *arg);
extern NODE *lsetwritepos(NODE *arg);
extern NODE *lcloseall(NODE * arg);
extern void uninitialize_files(void);
extern FILE *OpenFile(NODE *arg, const wchar_t *access);

// global variables

FILE*& GetInputStream();
FILE*& GetOutputStream();


#endif // __FILES_H_
