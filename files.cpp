/*
 *      files.cpp         logo file management module             dvb
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
   #include <stdlib.h>
   #include <string.h>
   #include <setjmp.h>
   #ifndef WX_PURE
      #include <windows.h>
   #endif

   #include "files.h"
   #include "fileswnd.h"
   #include "logocore.h"
   #include "init.h"
   #include "parse.h"
   #include "error.h"
   #include "logomath.h"
   #include "eval.h"
   #include "coms.h"
   #include "lists.h"
   #include "wrksp.h"
   #include "print.h"
   #include "unix.h"
   #include "graphics.h"
   #include "startup.h"
   #include "screenwindow.h"
   #include "cursor.h"
   #include "debugheap.h"

   #include "localizedstrings.h"
#endif

class CFileListNode
{
public:
    CFileListNode * m_Next;
    NODE          * m_FileNameNode;
    bool            m_IsBinaryStream;
    FILE *          m_FilePtr;

    CFileListNode(NODE * FileNameNode, FILE * FilePtr, bool IsBinaryStream);
    ~CFileListNode();

private:
    CFileListNode();
};

NODE *current_line = NIL;       // current line to be parsed

static CFileListNode * g_OpenFiles;

static FILE *loadstream = stdin;

CFileStream g_Reader(stdin);
CFileStream g_Writer(stdout);

CFileListNode::CFileListNode(
    NODE * FileNameNode,
    FILE * FilePtr,
    bool   IsBinaryStream
    ) :
    m_Next(NULL),
    m_FileNameNode(vref(FileNameNode)),
    m_IsBinaryStream(IsBinaryStream),
    m_FilePtr(FilePtr)
{
}

CFileListNode::~CFileListNode()
{
    // close the file, if it's still open
    if (m_FilePtr != NULL)
    {
        fclose(m_FilePtr);
    }

    // release the filename
    deref(m_FileNameNode);
}

FILE *OpenFile(NODE *arg, const wchar_t *access)
{
    assert(arg == NIL || getrefcnt(arg) != 0);

    NODE * filenameNode = cnv_node_to_strnode(arg);
    if (filenameNode == Unbound) 
    {
        return NULL;
    }

	wchar_t * fnstr = (wchar_t *) malloc((size_t) (getstrlen(filenameNode) + 1)*sizeof(wchar_t));
    strnzcpy(fnstr, getstrptr(filenameNode), getstrlen(filenameNode));

    FILE *tstrm = NULL;
#ifndef WX_PURE
    if (_wcsicmp(fnstr, L"clipboard") == 0)
    {
        if (_wcsicmp(access, L"r") == 0)
        {
            ::OpenClipboard(GetMainWindow());

            HANDLE HText = ::GetClipboardData(CF_TEXT);

            if (HText)
            {
                LPSTR lpText = (LPSTR) GlobalLock(HText);

                FILE *clipstrm = _wfopen(TempClipName, L"w");
                if (clipstrm != NULL)
                {
                    fwrite(lpText, sizeof(char), GlobalSize(HText), clipstrm);
                    fclose(clipstrm);
                }

                GlobalUnlock(HText);
            }
            else
            {
                FILE *clipstrm = _wfopen(TempClipName, L"w");
                if (clipstrm != NULL)
                {
                    fputws(GetResourceString(L"LOCALIZED_ERROR_CLIPBOARDISEMPTY"), clipstrm);
                    fclose(clipstrm);
                }
            }

            ::CloseClipboard();

            tstrm = _wfopen(TempClipName, access);
        }
        else if (_wcsicmp(access, L"w") == 0)
        {
            tstrm = _wfopen(TempClipName, access);
        }
    }
    else
#endif // WX_PURE
    {
        tstrm = _wfopen(fnstr, access);
    }

    if (tstrm != NULL)
    {
        if (wcsncmp(access, L"r+", 2) == 0)
        {
            // When we open in "r+", we want to read/write from the
            // end of the file until the user seeks somewhere else.
            // This mode is only used from OPENUPDATE.
            fseek(tstrm, 0, SEEK_END);
        }
    }

    gcref(filenameNode);
    free(fnstr);
    return tstrm;
}

FILE *& GetInputStream()
{
	return g_Reader.GetStream();
}

FILE *& GetOutputStream()
{
	return g_Writer.GetStream();
}

FILE *& GetLoadStream()
{
	return loadstream;
}

NODE *ldribble(NODE *arg)
{
	OpenDribble(arg);

    return Unbound;
}

NODE *lnodribble(NODE *)
{
  
	CloseDribble();

    return Unbound;
}

// Searches the list of open files for the node that matches
// the given filename.
// FileNameNode - The name of the file stream to look for.
// Remove       - true, if the file should be removed from the
//                list of open files.  false, otherwise.
// IsBinary     - If not NULL and a file is found, this is set to whether
//                or not the file was opened as a binary stream.
static
FILE *
FindOrRemoveFile(
    NODE * FileNameNode,
    bool   Remove,
    bool * IsBinary
    )
{
    FILE *fp = NULL;

    for (CFileListNode ** nodePtr = &g_OpenFiles;
         (*nodePtr) != NULL;
         nodePtr = &(*nodePtr)->m_Next)
    {
        CFileListNode * node = *nodePtr;
        if (compare_node(FileNameNode, node->m_FileNameNode, false) == 0)
        {
            // found it.
            // Return the FILE* and whether or not it's a binary stream.
            fp = node->m_FilePtr;
            if (IsBinary != NULL)
            {
                *IsBinary = node->m_IsBinaryStream;
            }

            if (Remove)
            {
                node->m_FilePtr = NULL;
                *nodePtr = node->m_Next;
                delete node;
            }
            break;
        }
    }

    return fp;
}

static
FILE *
FindFile(
    NODE * FileNameNode,
    bool * IsBinary
    )
{
    return FindOrRemoveFile(FileNameNode, false, IsBinary);
}

static
FILE *
FindFile(
    NODE * FileNameNode
    )
{
    return FindOrRemoveFile(FileNameNode, false, NULL);
}

static
FILE *
RemoveFile(
    NODE * FileNameNode
    )
{
    return FindOrRemoveFile(FileNameNode, true, NULL);
}

// Arguments   - The Logo arguments passed into the file operation.
//               The first argument is the filename.
//               The first argument is the optional "BinaryMode" argument.
// DefaultMode - The mode to use if Arguments does not indicate to use a binary mode
// BinaryMode  - The mode to use if Arguments does indicates to use a binary mode
static
NODE *
open_helper(
    NODE       *Arguments, 
    const wchar_t *DefaultMode,
    const wchar_t *BinaryMode
    )
{
    bool useBinaryMode = false;

    if (cdr(Arguments) != NIL)
    {
        useBinaryMode = boolean_arg(cdr(Arguments));
    }

    if (NOT_THROWING)
    {
        const wchar_t * mode = DefaultMode;
        if (useBinaryMode)
        {
            mode = BinaryMode;
        }

        FILE * newFileStream;
        NODE * fileNameNode = car(Arguments);
        if (FindFile(fileNameNode) != NULL)
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN")));
        }
        else if ((newFileStream = OpenFile(fileNameNode, mode)) != NULL)
        {
            // create a new node for this file
            CFileListNode * newNode = new CFileListNode(
                fileNameNode,
                newFileStream,
                useBinaryMode);

            // add this to the front of the list
            newNode->m_Next = g_OpenFiles;
            g_OpenFiles     = newNode;
        }
        else
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN")));
        }
    }
    return Unbound;
}

NODE *lopenread(NODE *args)
{
    return open_helper(args, L"r", L"rb");
}

NODE *lopenwrite(NODE *args)
{
    return open_helper(args, L"w", L"wb");
}

NODE *lopenappend(NODE *args)
{
    return open_helper(args, L"a", L"ab");
}

NODE *lopenupdate(NODE *args)
{
    return open_helper(args, L"r+", L"r+b");
}

NODE *lallopen(NODE *)
{
    NODE * allopen = NIL;
    for (CFileListNode * node = g_OpenFiles; node != NULL; node = node->m_Next)
    {
        allopen = cons(node->m_FileNameNode, allopen);
    }

    return allopen;
}

NODE *lclose(NODE *arg)
{
    NODE * filename = string_arg(arg);
    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    FILE *filePtr = RemoveFile(filename);
    if (filePtr == NULL)
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_NOTOPEN")));

        return Unbound;
    }

    // close the file stream
    fclose(filePtr);

	wchar_t * fnstr = (wchar_t *) malloc(((size_t) getstrlen(filename) + 1)*sizeof(wchar_t));
    strnzcpy(fnstr, getstrptr(filename), getstrlen(filename));

#ifndef WX_PURE
    if (_wcsicmp(fnstr, L"clipboard") == 0)
    {
        ::OpenClipboard(GetMainWindow());

        ::EmptyClipboard();

        FILE *clipstrm = _wfopen(TempClipName, L"rb");
        if (clipstrm != NULL)
        {
            fseek(clipstrm, 0, SEEK_END);
            LONG iSize = ftell(clipstrm);
            fseek(clipstrm, 0, SEEK_SET);

            HGLOBAL HText = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, iSize);
            LPSTR lpText = (LPSTR) GlobalLock(HText);

            fread( lpText, sizeof(char), GlobalSize(HText), clipstrm);
            fclose(clipstrm);
            
            GlobalUnlock(HText);
            
            ::SetClipboardData(CF_TEXT, HText);

            ::CloseClipboard();
        }

        _wremove(TempClipName);
    }
#endif // WX_PURE

    free(fnstr);

    // If we closed the active reader or write stream,
    // then we should reset the stream to the default
    // (either stdin or stdout) to so that future
    // reads/writes won't crash.
    if (g_Writer.IsNamed(filename))
    {
        g_Writer.ResetToDefaultStream();
    }

    if (g_Reader.IsNamed(filename))
    {
        g_Reader.ResetToDefaultStream();
    }

    return Unbound;
}

CFileStream::CFileStream(
    FILE * DefaultFileStream
    ) :
    m_Name(NIL),
    m_Stream(DefaultFileStream),
    m_DefaultStream(DefaultFileStream),
    m_StreamIsBinary(false)
{
}

void
CFileStream::ResetToDefaultStream()
{
    deref(m_Name);
    m_Name = NIL;

    m_Stream = m_DefaultStream;
    m_StreamIsBinary = false;
}

void
CFileStream::SetStreamToOpenFile(
    NODE * FileName
    )
{
    bool   filePtrIsBinaryStream;
    FILE * filePtr;

    if (FileName == NIL)
    {
        // reset to the default stream
        ResetToDefaultStream();
    }
    else if ((filePtr = FindFile(FileName, &filePtrIsBinaryStream)) != NULL)
    {
        m_Stream         = filePtr;
        m_StreamIsBinary = filePtrIsBinaryStream;
        assign(m_Name, FileName);
    }
    else
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_NOTOPEN")));
    }
}

bool
CFileStream::IsNamed(
    NODE * FileName
    ) const
{
    return compare_node(FileName, m_Name, false) == 0;
}

bool
CFileStream::IsBinary() const
{
    return m_StreamIsBinary;
}

NODE *
CFileStream::GetName() const
{
    return m_Name;
}

NODE *
CFileStream::GetPosition() const
{
    return make_intnode(ftell(m_Stream));
}

void
CFileStream::SetPosition(
    NODE * Arguments
    )
{
    NODE *val = nonnegative_int_arg(Arguments);

    if (NOT_THROWING)
    {
        fseek(m_Stream, getint(val), SEEK_SET);
    }
}


NODE *lsetwrite(NODE *arg)
{
    g_Writer.SetStreamToOpenFile(car(arg));
    return Unbound;
}

NODE *lsetread(NODE *arg)
{
    g_Reader.SetStreamToOpenFile(car(arg));
    return Unbound;
}

NODE *lreader(NODE *)
{
    return g_Reader.GetName();
}

NODE *lwriter(NODE *)
{
    return g_Writer.GetName();
}

NODE *lerasefile(NODE *arg)
{
    arg = cnv_node_to_strnode(car(arg));
    if (arg == Unbound) 
    {
        return Unbound;
    }

	wchar_t * fnstr = (wchar_t *) malloc(((size_t) getstrlen(arg) + 1)*sizeof(wchar_t));
    strnzcpy(fnstr, getstrptr(arg), getstrlen(arg));
    remove(wxString(fnstr));
    free(fnstr);
    gcref(arg);
    return Unbound;
}


void
PrintWorkspaceToFileStream(
    FILE * FileStream
    )
{
    if (FileStream != NULL)
    {
        // HACK: change g_Writer to use the new stream
        FILE * savedWriterStream = GetOutputStream();
        g_Writer.SetStream(FileStream);

        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        NODE * entire_workspace = vref(cons_list(lcontents(NIL)));
        lpo(entire_workspace);
        deref(entire_workspace);

        fclose(GetOutputStream());
        IsDirty = false;

        lsetcursorarrow(NIL);
        yield_flag = save_yield_flag;

        // restore g_Writer
        g_Writer.SetStream(savedWriterStream);
    }
    else
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN")));
    }
}


NODE *lsave(NODE *arg)
{
    if (IsEditorOpen())
    {
        // Notify the user that the editor is open and that 
        // the changes made in that editor won't be saved.
#ifndef WX_PURE
        ::MessageBox(
            GetCommanderWindow(),
			GetResourceString(L"LOCALIZED_EDITORISOPEN"),
			GetResourceString(L"LOCALIZED_INFORMATION"),
            MB_OK | MB_ICONQUESTION);
#endif // WX_PURE
    }

    lprint(arg);

    PrintWorkspaceToFileStream(OpenFile(car(arg), L"w+"));

    return Unbound;
}

void runstartup(NODE *oldst)
{
    NODE* st = Startup.GetValue();
    if (st != oldst && st != NIL && is_list(st))
    {
        g_ValueStatus = VALUE_STATUS_NotOk;
        eval_driver(st);

        // process special conditions
        process_special_conditions();
    }
}
wxString noparitylow_strnzcpy(const wchar_t *src, int len)
{
	wxString dest;

	wchar_t* buffer = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	if (buffer != 0) {
		buffer[len] = L'0';
		noparitylow_strnzcpy(buffer, src, len);

		dest = buffer;

		free(buffer);
	}

	return dest;
}
void silent_load(NODE *arg, const wchar_t *prefix)
{

    /* This procedure is called three ways:
     *    silent_load(NIL,*argv)    loads *argv
     *    silent_load(proc,logolib) loads logolib/proc
     *    silent_load(proc,NULL)    loads proc.lgo
     * The "/" or ".lgo" is supplied by this procedure as needed.
     */
    if (prefix == NULL && arg == NIL)
    {
        return;
    }

    // construct the filename

    wxString filename;

    if (prefix != NULL)
    {
		filename = prefix;
    }

    if (arg != NIL)
    {
        arg = cnv_node_to_strnode(arg);

        if (arg == Unbound)
        {
            return;
        }

        const wchar_t * argString       = getstrptr(arg);
        int          argStringLength = getstrlen(arg);

        // Normalize the case to how we expect it to be on the file system.
        // Using lowercase was inherited from UCBLogo.
        filename += noparitylow_strnzcpy(argString, argStringLength);

        // Replace characters that are legal in procedure names, but illegal
        // in file names (such as '?') with characters that are illegal in
        // procedure names, but legal in file names (such as '+').
        // This permits us to load "?REST" as a Logolib routine.

		for (size_t i = 0; i < filename.length(); i++) {
			if (filename[i] == L'?') {
				filename[i] = L'+';
			}
		}

        if (prefix == NULL)
        {
            // this is not coming from Logolib, so append a ".lgo"
			filename += L".lgo";
        }
        gcref(arg);
    }

    bool isOk = fileload(filename);
    if (isOk)
    {
        if (stopping_flag == THROWING)
        {
            // There was an error parsing this file.
            // Open it in the editor so that it can be debugged.
            stopping_flag = RUN;
            OpenEditorToLocationOfFirstError(filename);
        }
    }
    else 
    {
        if (arg == NIL)
        {
            // we're loading argv (not from Logolib or current directory)
            // so we should display an error
            ndprintf(
                stdout,
                MESSAGETYPE_Error,
				GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2")+L"\n",
                prefix);
        }
    }
}

// CONSIDER for MAINTAINABILITY:
// CONSIDER for SIZE:
// Refactor the common parts of lload() and fileload() into a helper.
NODE *lload(NODE *arg)
{
    NODE *st = Startup.GetValue();
    FIXNUM saved_value_status = g_ValueStatus;

    bool isDirtySave = IsDirty;
    FILE * tmp = loadstream;
    NODE * tmp_line = vref(current_line);
    loadstream = OpenFile(car(arg), L"r");
    if (loadstream != NULL)
    {
        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        start_execution();

        while (!feof(loadstream) && NOT_THROWING)
        {
            assign(current_line, reader(loadstream, L""));
            NODE * exec_list = parser(current_line, true);
            g_ValueStatus = VALUE_STATUS_NotOk;
            eval_driver(exec_list);
        }
        fclose(loadstream);

        lsetcursorarrow(NIL);
        yield_flag = save_yield_flag;

        runstartup(st);
        g_ValueStatus = saved_value_status;

        stop_execution();
    }
    else
    {
        err_logo(
            FILE_ERROR, 
            make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN")));
    }

    loadstream = tmp;
    deref(current_line);
    current_line = tmp_line;
    IsDirty = isDirtySave;
    return Unbound;
}

NODE *lreadlist(NODE *)
{
	GetInputMode() = INPUTMODE_List;
    NODE * val = parser(reader(g_Reader.GetStream(), L""), false);
	GetInputMode() = INPUTMODE_None;
    if (feof(g_Reader.GetStream()) && val == NIL)
    {
        gcref(val);
        return Null_Word;
    }
    return val;
}

NODE *lreadword(NODE *)
{
    NODE * val = reader(g_Reader.GetStream(), L"RW");  // fake prompt flags no auto-continue
    if (feof(g_Reader.GetStream()) && getstrlen(val) == 0)
    {
        gcref(val);
        return NIL;
    }
    return val;
}

NODE *lreadrawline(NODE *)
{
    NODE *val = reader(g_Reader.GetStream(), L"RAW"); // fake prompt flags no specials
    if (feof(g_Reader.GetStream()) && getstrlen(val) == 0)
    {
        gcref(val);
        return NIL;
    }

    return val;
}

NODE *lreadchar(NODE *)
{
	GetInputBlocking() = true;

    wchar_t c =L'\0';

    if (!setjmp(iblk_buf))
    {
        if (g_Reader.GetStream() == stdin)
        {
            c = (wchar_t) rd_fgetwc(stdin);
        }
        else
        {
            c = (wchar_t) getwc(g_Reader.GetStream());
        }
    }
	GetInputBlocking() = false;

    if (feof(g_Reader.GetStream()))
    {
        return NIL;
    }

    if (g_Reader.IsBinary())
    {
        return make_intnode(/*(unsigned char) */c);
    }
    else
    {
        return make_strnode(
            &c,
            1,
            ecma_get(c) ? STRING : BACKSLASH_STRING,
            strnzcpy);
    }
}

NODE *lreadchars(NODE *args)
{
    NODETYPES type = STRING;

    size_t totalBytesRequested = (size_t) getint(nonnegative_int_arg(args));
    size_t totalBytesRead      = 0;

    if (stopping_flag == THROWING) 
    {
        return Unbound;
    }

    // READCHARS is documented to always return [] when the read
    // stream is set to the commander.
    if (g_Reader.GetStream() == stdin)
    {
        return NIL;
    }

	GetInputBlocking() = true;

    wchar_t *strhead = 0, *strptr = 0;
    if (!setjmp(iblk_buf))
    {
        // TODO: Don't allocate more bytes than the file contains.
        // This would allow for success when given a very large input.
		
        strhead = (wchar_t *) malloc( sizeof(unsigned short) +(totalBytesRequested + 1)*sizeof(wchar_t));
        if (strhead == NULL)
        {
            err_logo(OUT_OF_MEM, NIL);
            return Unbound;
        }

        strptr = (wchar_t*)((char*) strhead + sizeof(unsigned short));
		strptr[totalBytesRequested] = L'\0';
        totalBytesRead = fread(strptr, 1, totalBytesRequested, g_Reader.GetStream());
        unsigned short * temp = (unsigned short *) strhead;
        setstrrefcnt(temp, 0);
    }

	GetInputBlocking() = false;

    if (stopping_flag == THROWING) 
    {
        free(strhead);
        return Unbound;
    }

    if (totalBytesRead == 0)
    {
        // We read zero bytes.  This may be because we hit EOF or
        // because we requested zero bytes.  If both are true, we
        // want to return [] when we're at EOF.
        if (totalBytesRequested == 0)
        {
            // Probe to see if we're at the end of the file.
            // This will update feof().
            ungetc(getc(g_Reader.GetStream()), g_Reader.GetStream());
        }

        if (feof(g_Reader.GetStream()))
        {
            // We reached the end of the file.
            free(strhead);
            return NIL;
        }
    }

    // Check if this string has special characters in it
    for (size_t i = 0; i < totalBytesRead; i++)
    {
        if (ecma_get(strptr[i])) 
        {
            type = BACKSLASH_STRING;
            break;
        }
    }

    return make_strnode_no_copy(strptr, strhead, (int) totalBytesRead, type);
}

NODE *leofp(NODE *)
{
    ungetc(getc(g_Reader.GetStream()), g_Reader.GetStream());
    int isEof = feof(g_Reader.GetStream());
    return true_or_false(isEof);
}

NODE *lkeyp(NODE *)
{
    if (g_Reader.GetStream() == stdin)
    {
        return Truex.GetNode();
    }

    return leofp(NIL);
}

NODE *lreadpos(NODE *)
{
    return g_Reader.GetPosition();
}

NODE *lsetreadpos(NODE *arg)
{
    g_Reader.SetPosition(arg);
    return Unbound;
}

NODE *lwritepos(NODE *)
{
    return g_Writer.GetPosition();
}

NODE *lsetwritepos(NODE *arg)
{
    g_Writer.SetPosition(arg);
    return Unbound;
}

NODE *lcloseall(NODE *)
{
    // close all open file pointers
    while (g_OpenFiles != NULL)
    {
        CFileListNode * nextNode = g_OpenFiles->m_Next;
        delete g_OpenFiles;
        g_OpenFiles = nextNode;
    }

    return Unbound;
}

void uninitialize_files()
{
    lcloseall(NIL);

    g_Reader.ResetToDefaultStream();
    g_Writer.ResetToDefaultStream();
}
