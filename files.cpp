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
#include "CStringTextStream.h"

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
CFileListNode * g_OpenFiles = 0;

CTextStream *stdinstream = CFileTextStream::CreateStdInWarpper(FileTextStreamType::Unicode);
CTextStream *stdoutstream = CFileTextStream::CreateStdInWarpper(FileTextStreamType::Unicode);

CTextStream *loadstream = CFileTextStream::CreateStdInWarpper(FileTextStreamType::Unicode);
CTextStream *inputstream = CFileTextStream::CreateStdInWarpper(FileTextStreamType::Unicode);
CTextStream *outputstream = CFileTextStream::CreateStdOutWrapper(FileTextStreamType::Unicode);
CTextStream *dribblestream = NULL;

void OpenDribble(NODE * arg)
{
	if (dribblestream != NULL)
	{
		err_logo(ALREADY_DRIBBLING, NIL);
	}
	else
	{
		dribblestream = CFileTextStream::CreateWrapper(OpenFile(car(arg), L"w"), FileTextStreamType::Unicode);
		if (dribblestream == NULL)
		{
			err_logo(FILE_ERROR, NIL);
		}
	}
}

void CloseDribble()
{
	if (dribblestream != NULL)
	{
		delete dribblestream;
		dribblestream = NULL;
	}
}

void DribbleWriteChar(wchar_t ch)
{
	if (dribblestream != NULL) {
		dribblestream->WriteChar(ch);
	}
}

void DribbleWriteText(const wchar_t * text)
{
	if (dribblestream != NULL) {
		dribblestream->Write(text != 0 ? text : L"");
	}
}

void DribbleWriteLine(const wchar_t * text)
{
	if (dribblestream != NULL) {
		dribblestream->WriteLine(text != 0 ? text : L"");
	}
}

void FreeAllPredefinedStreams()
{
	CloseDribble();
	if (stdinstream != 0)
	{
		delete stdinstream;
		stdinstream = 0;
	}	
	if (stdoutstream != 0)
	{
		delete stdoutstream;
		stdoutstream = 0;
	}	
	if (inputstream != 0)
	{
		delete inputstream;
		inputstream = 0;
	}	
	if (outputstream != 0)
	{
		delete outputstream;
		outputstream = 0;
	}	
	if (loadstream != 0)
	{
		delete loadstream;
		loadstream = 0;
	}
}


CFileStream g_Reader(inputstream);
CFileStream g_Writer(outputstream);

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
#ifdef _WINDOWS
        tstrm = _wfopen(fnstr, access);
#else
        tstrm = fopen(wxString(fnstr),wxString(access));
#endif
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

CTextStream* GetInputStream()
{
	return inputstream;
}

CTextStream* GetOutputStream()
{
	return outputstream;
}

CTextStream * GetLoadStream()
{
	return loadstream;
}

CTextStream * GetDribbleStream()
{
	return dribblestream;
}

void SetInputStream(CTextStream * stream)
{
	inputstream = stream;
}

void SetOutputStream(CTextStream * stream)
{
	outputstream = stream;
}

void SetLoadStream(CTextStream * stream)
{
	loadstream = stream;
}

void SetDribbleStream(CTextStream * stream)
{
	dribblestream = stream;
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


#ifndef WX_PURE
	wchar_t * fnstr = (wchar_t *) malloc(((size_t) getstrlen(filename) + 1)*sizeof(wchar_t));
    strnzcpy(fnstr, getstrptr(filename), getstrlen(filename));
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
    free(fnstr);
#endif // WX_PURE


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
	CTextStream * DefaultFileStream
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
        m_Stream->SetFile(filePtr);
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
    return make_intnode((m_Stream->GetPosition()));
}

void
CFileStream::SetPosition(
    NODE * Arguments
    )
{
    NODE *val = nonnegative_int_arg(Arguments);

    if (NOT_THROWING)
    {
        m_Stream->SetPosition(getint(val), SEEK_SET);
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


void PrintWorkspaceToStream(CTextStream *stream)
{
    if (stream != NULL)
    {
		CTextStream* savedWriterStream = GetOutputStream();
        
		SetOutputStream(stream);;

        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        NODE * entire_workspace = vref(cons_list(lcontents(NIL)));
        lpo(entire_workspace);
        deref(entire_workspace);
		GetOutputStream()->Flush();
        GetOutputStream()->Close();
        IsDirty = false;

        lsetcursorarrow(NIL);
        yield_flag = save_yield_flag;

        // restore g_Writer
		SetOutputStream(savedWriterStream);
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
	CFileTextStream* stream = CFileTextStream::CreateWrapper(OpenFile(car(arg), L"w+"), FileTextStreamType::Unicode);
    PrintWorkspaceToStream(stream);
	delete stream;

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
				stdoutstream,
                MESSAGETYPE_Error,
				GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2")+L"\n",
                prefix);
        }
    }
}

FileTextStreamType DefaultFileTextStreamType = FileTextStreamType::Mbcs;

FileTextStreamType& GetDefaultFileTextStreamType()
{
	return DefaultFileTextStreamType;
}

// CONSIDER for MAINTAINABILITY:
// CONSIDER for SIZE:
// Refactor the common parts of lload() and fileload() into a helper.
NODE *lload(NODE *arg)
{
    NODE *st = Startup.GetValue();
    FIXNUM saved_value_status = g_ValueStatus;

    bool isDirtySave = IsDirty;
    CTextStream* temporarystream = GetLoadStream();
    NODE * tmp_line = vref(current_line);
	CFileTextStream* filestream = CFileTextStream::CreateWrapper(OpenFile(car(arg), L"r"), DefaultFileTextStreamType);
    if (filestream != NULL)
    {
		SetLoadStream(filestream);

        bool save_yield_flag = yield_flag;
        yield_flag = false;
        lsetcursorwait(NIL);

        start_execution();

        while (!GetLoadStream()->IsEOF() && NOT_THROWING)
        {
            assign(current_line, reader(loadstream, L""));
            NODE * exec_list = parser(current_line, true);
            g_ValueStatus = VALUE_STATUS_NotOk;
            eval_driver(exec_list);
        }
		GetLoadStream()->Close();

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

	SetLoadStream(temporarystream);

	delete filestream;

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
    if (g_Reader.GetStream()->IsEOF() && val == NIL)
    {
        gcref(val);
        return Null_Word;
    }
    return val;
}

NODE *lreadword(NODE *)
{
    NODE * val = reader(g_Reader.GetStream(), L"RW");  // fake prompt flags no auto-continue
    if (g_Reader.GetStream()->IsEOF() && getstrlen(val) == 0)
    {
        gcref(val);
        return NIL;
    }
    return val;
}

NODE *lreadrawline(NODE *)
{
    NODE *val = reader(g_Reader.GetStream(), L"RAW"); // fake prompt flags no specials
    if (g_Reader.GetStream()->IsEOF() && getstrlen(val) == 0)
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
        if (g_Reader.GetStream()->GetFile() == stdin)
        {
            c = rd_fgetwc(stdinstream);
        }
        else
        {
            c = g_Reader.GetStream()->ReadChar();
        }
    }
	GetInputBlocking() = false;

    if (GetInputStream()->IsEOF())
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

    size_t totalCharsRequested = (size_t) getint(nonnegative_int_arg(args));
    size_t totalCharsRead      = 0;

    if (stopping_flag == THROWING) 
    {
        return Unbound;
    }

    // READCHARS is documented to always return [] when the read
    // stream is set to the commander.
    if (GetInputStream()->GetFile() == stdin)
    {
        return NIL;
    }

	GetInputBlocking() = true;

    wchar_t *strhead = 0, *strptr = 0;
    if (!setjmp(iblk_buf))
    {
        // TODO: Don't allocate more bytes than the file contains.
        // This would allow for success when given a very large input.
		off64_t cp = g_Reader.GetStream()->GetPosition();
		g_Reader.GetStream()->SetPosition(0,SEEK_END);
		off64_t dp = g_Reader.GetStream()->GetPosition();
		g_Reader.GetStream()->SetPosition(cp, SEEK_SET);
		
		size_t left_size = (size_t)(dp - cp);
		size_t full_size = sizeof(unsigned short) + (totalCharsRequested + 1) * sizeof(wchar_t);
		size_t buff_size = (full_size> left_size ? left_size:full_size);

        strhead = (wchar_t *) malloc(buff_size);
        if (strhead == NULL)
        {
            err_logo(OUT_OF_MEM, NIL);
            return Unbound;
        }
		memset(strhead, 0, buff_size);
        strptr = (wchar_t*)((char*) strhead + sizeof(unsigned short));
		//totalBytesRead = fread(strptr, 1, totalBytesRequested, g_Reader.GetStream());
		totalCharsRead = g_Reader.GetStream()->Read(strptr, totalCharsRequested);
		unsigned short * temp = (unsigned short *) strhead;
        setstrrefcnt(temp, 0);
    }

	GetInputBlocking() = false;

    if (stopping_flag == THROWING) 
    {
        free(strhead);
        return Unbound;
    }

    if (totalCharsRead == 0)
    {
        // We read zero bytes.  This may be because we hit EOF or
        // because we requested zero bytes.  If both are true, we
        // want to return [] when we're at EOF.
        if (totalCharsRequested == 0)
        {
            // Probe to see if we're at the end of the file.
            // This will update feof().
            //ungetc(getc(g_Reader.GetStream()), g_Reader.GetStream());
			GetInputStream()->PeekChar();
        }

        if (GetInputStream()->IsEOF())
        {
            // We reached the end of the file.
            free(strhead);
            return NIL;
        }
    }

    // Check if this string has special characters in it
    for (size_t i = 0; i < totalCharsRead; i++)
    {
        if (ecma_get(strptr[i])) 
        {
            type = BACKSLASH_STRING;
            break;
        }
    }

    return make_strnode_no_copy(strptr, strhead, (int) totalCharsRead, type);
}

NODE *leofp(NODE *)
{
    //ungetc(getc(g_Reader.GetStream()), g_Reader.GetStream());
	GetInputStream()->PeekChar();
	int isEof = GetInputStream()->IsEOF();
    return true_or_false(isEof);
}

NODE *lkeyp(NODE *)
{
    if (GetInputStream()->GetFile() == stdin)
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

	FreeAllPredefinedStreams();
}

//TODO: needs to check
