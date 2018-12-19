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
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #ifndef WX_PURE
      #include <windows.h>
    #endif

    #include <stdio.h>
    #include <string.h>
    #include <errno.h>

    #ifdef __GNUC__
        #include <unistd.h>
        #include <sys/stat.h>
    #else
        #include <direct.h>
    #endif

    #include "unix.h"
    #include "init.h"
    #include "logodata.h"
    #include "parse.h"
    #include "commander.h"
    #include "stringprintednode.h"
    #include "dynamicbuffer.h"
    #include "appendablelist.h"
    #include "sort.h"
    #include "debugheap.h"
    #include "localizedstrings.h"
#endif



jmp_buf iblk_buf;

static CDynamicBuffer g_ComboBuffer;

static
void
mputcombobox(
    const wchar_t *str
    )
{
    // Append the string to the buffer
    g_ComboBuffer.AppendString(str);

    // process lines
	wchar_t * rawBuffer       = g_ComboBuffer.GetBuffer();
    size_t rawBufferLength = g_ComboBuffer.GetBufferLength();

	wchar_t * next_line = rawBuffer;
    for (size_t i = 0; i < rawBufferLength; i++)
    {
        if (rawBuffer[i] == L'\n')
        {
            // if <lf> pump it out
            rawBuffer[i] = L'\0';
            putcombobox(next_line, MESSAGETYPE_Normal);
            rawBuffer[i] = L'\n';
            next_line = &rawBuffer[i + 1];
        }
    }

    // flush the last line (which doesn't end in \n)
    if (next_line[0] != L'\0')
    {
        putcombobox(next_line, MESSAGETYPE_Normal);
    }

    // clear the contents of the buffer, since we wrote the entire thing
    g_ComboBuffer.Empty();
}

void putcombochar(MESSAGETYPE type, wchar_t ch)
{
    if (ch == L'\n')
    {
        // if <lf> pump it out
        putcombobox(g_ComboBuffer.GetBuffer(), type);
        g_ComboBuffer.Empty();
    }
    else
    {
        g_ComboBuffer.AppendChar(ch);
    }
}


int printfx(const wchar_t *str)
{
    mputcombobox(str);

    return wcslen(str);
}

int printfx(const wchar_t *fmt, const wchar_t *str)
{
    size_t bufferSize =
        wcslen(fmt) +
        (str ? wcslen(str) : 0) +
        1;

	wchar_t * buff = new wchar_t[bufferSize + 1];
	//TODO: need to check override
    int cnt = _swprintf(buff, /*bufferSize, */fmt, str);

    // check for a buffer overflow
    assert(cnt < (int)bufferSize);

    mputcombobox(buff);

    delete [] buff;

    return cnt;
}

NODE *lchdir(NODE *arg)
{
    CStringPrintedNode directoryName(car(arg));

    if (_chdir(wxString(directoryName)))
    {
        printfx(LOCALIZED_FILE_CHDIRFAILED, directoryName);
    }
    else
    {
        // Get the directory that we are now in.
        char newDirectoryName[MAX_BUFFER_SIZE + 1];
        _getcwd(newDirectoryName, sizeof newDirectoryName);

        printfx(LOCALIZED_FILE_CHDIRSUCCEEDED, wxString(newDirectoryName).wc_str());
    }

    return Unbound;
}

NODE *lpopdir(NODE *)
{
    _chdir("..");

    char fname[MAX_BUFFER_SIZE + 1];
    _getcwd(fname, sizeof fname);

    printfx(LOCALIZED_FILE_POPPEDTO, wxString(fname));

    return Unbound;
}

NODE *lmkdir(NODE *arg)
{
    CStringPrintedNode directoryName(car(arg));

#ifndef WX_PURE
    if (_mkdir(wxString(directoryName)))
    {
        // mkdir returns -1 on error
        printfx(LOCALIZED_FILE_MKDIRFAILED, directoryName);
    }
    else
    {
        // mkdir returns 0 on success
        _chdir(wxString(directoryName));
        printfx(LOCALIZED_FILE_MKDIRSUCCEEDED, directoryName);
    }
#endif

    return Unbound;
}

NODE *lrmdir(NODE *arg)
{
    CStringPrintedNode directoryName(car(arg));

    if (_rmdir(wxString(directoryName)))
    {
        printfx(LOCALIZED_FILE_RMDIRFAILED, directoryName);
        if (errno == EEXIST)
        {
            printfx(LOCALIZED_FILE_RMDIRFAILEDNOEXIST);
        }
        else if (errno == EEXIST || errno == EPERM)
        {
            printfx(LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY);
        }
        else
        {
            printfx(wxString(strerror(errno)));
        }
    }
    else
    {
        printfx(LOCALIZED_FILE_RMDIRSUCCEEDED, directoryName);
    }

    return Unbound;
}

static
NODE *directory_helper(bool OnlyListDirectories)
{
    CAppendableList directory; 

    // Flags for whether the special directories "." and ".." have been found.
    // Because these are special entries, we always want them to be first,
    // even if there's an entry that comes before them alphabetically,
    // like "!MyDirectory".
    bool foundDot    = false;
    bool foundDotDot = false;

#ifndef WX_PURE
    WIN32_FIND_DATA findFileData;

    HANDLE searchHandle = FindFirstFile(
        L"*.*",
        &findFileData); 
    if (searchHandle != INVALID_HANDLE_VALUE)
    {
        BOOL moreToCome = TRUE;
        while (moreToCome)
        {
            bool isADirectory = findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 
                true : 
                false;
            if ((OnlyListDirectories && isADirectory) ||
                (!OnlyListDirectories && !isADirectory))
            {
                // We have found an entry type that we are looking for.
                if (OnlyListDirectories && 0 == wcscmp(L".", findFileData.cFileName))
                {
                    // This the "." directory.  Flag it to be added later.
                    foundDot = true;
                }
                else if (OnlyListDirectories && 0 == wcscmp(L"..", findFileData.cFileName))
                {
                    // This the ".." directory.  Flag it to be added later.
                    foundDotDot = true;
                }
                else
                {
                    // This is a regular directory entry.  Add it to the list.
                    NODE* file = make_strnode(findFileData.cFileName);
                    directory.AppendElement(file);
                }
            }

            // Iterate to the next file/directory
            moreToCome = FindNextFile(searchHandle, &findFileData);
        }

        FindClose(searchHandle);
    }
#endif

    // The MSDN reports that FindNextFile doesn't guarantee a order, so we sort
    // the list according to the locale.
    // CONSIDER FOR SPEED: From what I've seen, FindNextFile usually does sort
    // the list.  If this is too slow, we could track if sorting is needed above
    // and only sort when necessary.
    NODE * sortedList = mergesort(directory.GetList(), true);

    // Add "." and ".." to the front of the list, if applicable.
    if (foundDotDot)
    {
        sortedList = cons(make_strnode(L".."), sortedList);
    }
    if (foundDot)
    {
        sortedList = cons(make_strnode(L"."), sortedList);
    }

    return sortedList;
}

NODE *lfiles(NODE *)
{
    return directory_helper(false);
}

NODE *ldirectories(NODE *)
{
    return directory_helper(true);
}

void unblock_input()
{
    if (input_blocking)
    {
        input_blocking = false;
        longjmp(iblk_buf, 1);
    }
}

void uninitialize_combobox()
{
    g_ComboBuffer.Dispose();
}
