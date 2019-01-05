/*
 *      parse.cpp       logo parser module              dvb
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
#include <string.h>
#include <setjmp.h>
#include <algorithm>

#include "parse.h"
#include "argumentutils.h"
#include "FMSLogo.h"
#include "logocore.h"
#include "dynamicbuffer.h"
#include "error.h"
#include "init.h"
#include "ibmterm.h"
#include "unix.h"
#include "logodata.h"
#include "lists.h"
#include "eval.h"
#include "intern.h"
#include "logomath.h"
#include "appendablelist.h"
#include "stringprintednode.h"
#include "graphics.h"
#include "screenwindow.h"
#include "localizedstrings.h"
//#include "debugheap.h"
#include "files.h"
#endif

#include "CNodePrinter.h"

bool input_blocking = false;
NODE *deepend_proc_name = NIL;
NODE *g_ToLine = NIL;

INPUTMODE input_mode = INPUTMODE_None;
static CDynamicBuffer g_ReadBuffer;

bool& GetInputBlocking()
{
	return input_blocking;
}

INPUTMODE& GetInputMode()
{
	return input_mode;
}

void SetErrorProcName(NODE * name)
{
	assign(deepend_proc_name, name);
}

void SetErrorToLine(NODE * line)
{
	assign(g_ToLine, line);
}
#if 0
//this class is commented out because it's a bit of buggy
//
// A class for allocating and manipulating a buffer that
// is suitable for use with make_strnode_from_allocated_buffer().
// The intent of this class is to eliminate the need to copy
// the buffer when allocating a string node.
class CStringNodeBuffer
{
	friend class CStringNodeBufferInvariant;

public:
	CStringNodeBuffer();
	~CStringNodeBuffer();

	void TakeOwnershipOfBuffer();

	wchar_t* GetStringLengthPtr();
	wchar_t* GetString();
	size_t GetStringLength() const;

	void AppendString(const wchar_t * ToAppend);
	void AppendChar(wchar_t ToAppend);

private:
	void GrowBy(size_t ExtraLength);

	char  *  m_Buffer;       // the buffer that holds the string
	wchar_t* m_StringStart;
	size_t   m_BufferLengthInBytes; // the length in bytes of the allocated buffer
	wchar_t *   m_StringLimit;  // a pointer to one beyond the end of the string
	bool     m_IsOwner;      // if this object must free m_Buffer
};

#ifdef NDEBUG
#  define ASSERT_STRINGNODE_INVARIANT
#else
#  define ASSERT_STRINGNODE_INVARIANT CStringNodeBufferInvariant invariant(*this)

class CStringNodeBufferInvariant
{
public:
	CStringNodeBufferInvariant(const CStringNodeBuffer & StringNodeBuffer)
		: m_StringNodeBuffer(StringNodeBuffer)
	{
		AssertInvariant();
	}

	~CStringNodeBufferInvariant()
	{
		AssertInvariant();
	}

	void AssertInvariant() const
	{
		assert(m_StringNodeBuffer.m_Buffer != NULL);
		assert((wchar_t*)(m_StringNodeBuffer.m_Buffer + sizeof(unsigned short)) <= m_StringNodeBuffer.m_StringLimit);
		assert((char*)m_StringNodeBuffer.m_StringLimit - m_StringNodeBuffer.m_Buffer < (int)m_StringNodeBuffer.m_BufferLengthInBytes);
	}

private:
	const CStringNodeBuffer & m_StringNodeBuffer;
};

#endif // NDEBUG

CStringNodeBuffer::CStringNodeBuffer()
{
	const size_t DEFAULT_SIZE = 256;

	// allocate enough for the header, the string, and the NUL terminator
	this->m_BufferLengthInBytes = sizeof(unsigned short) + (DEFAULT_SIZE + 1) * sizeof(wchar_t);
	this->m_Buffer = static_cast<char *>(malloc(m_BufferLengthInBytes));
	this->m_StringLimit = this->m_StringStart = (wchar_t*)(m_Buffer + sizeof(unsigned short));
	*this->m_StringLimit = L'\0';
	this->m_IsOwner = true;
}

CStringNodeBuffer::~CStringNodeBuffer()
{
	if (m_IsOwner)
	{
		free(m_Buffer);
		this->m_Buffer = 0;
	}
}
wchar_t* CStringNodeBuffer::GetStringLengthPtr()
{
	return (wchar_t*)this->m_Buffer;
}
void CStringNodeBuffer::TakeOwnershipOfBuffer()
{
	ASSERT_STRINGNODE_INVARIANT;

	size_t StrLength = this->GetStringLength();

	// Reduce the size of the buffer to only what is needed.
	size_t newBufferLengthInBytes = (StrLength + 1) * sizeof(wchar_t) + sizeof(unsigned short);
	void * smallerBuffer = realloc(this->m_Buffer, newBufferLengthInBytes);
	if (smallerBuffer != NULL)
	{
		// The reallocation should always succeed, but the C standard
		// does not guarantee this.
		this->m_Buffer = (char *)(smallerBuffer);
		this->m_StringStart = (wchar_t*)(this->m_Buffer + sizeof(unsigned short));
		this->m_StringLimit = m_StringStart + StrLength;
		*this->m_StringLimit = L'\0';
	}

	// initialize the reference count to zero.
	*this->GetStringLengthPtr() = 0;

	// set a flag that we don't own m_Buffer.
	m_IsOwner = false;
}
wchar_t * CStringNodeBuffer::GetString()
{
	ASSERT_STRINGNODE_INVARIANT;

	// NUL-terminate the buffer
	*this->m_StringLimit = L'\0';
	return this->m_StringStart;
}

size_t CStringNodeBuffer::GetStringLength() const
{
	ASSERT_STRINGNODE_INVARIANT;

	return this->m_StringLimit - this->m_StringStart;
}

void CStringNodeBuffer::GrowBy(size_t ExtraLength)
{
	ASSERT_STRINGNODE_INVARIANT;

	// if it won't fit, then make the buffer bigger
	size_t requiredLengthInBytes = (this->GetStringLength() + ExtraLength + 1) * sizeof(wchar_t);
	if (this->m_BufferLengthInBytes < requiredLengthInBytes)
	{
		// Double the size of the buffer, instead of only requesting 
		// requiredLength bytes.  If we don't do this, then reading
		// long words takes a *very* long time because we repeatedly
		// reallocate the buffer to be one byte larger.
		size_t usedPortion = this->GetStringLength();
		size_t newLengthInBytes = requiredLengthInBytes << 1;

		char* pb = (char *)realloc(m_Buffer, newLengthInBytes);
		assert(pb != NULL);
		if ((this->m_Buffer = pb) != NULL) {
			this->m_StringStart = (wchar_t*)(this->m_Buffer + sizeof(unsigned short));
			this->m_StringLimit = this->m_StringStart + usedPortion;
			*this->m_StringLimit = L'\0';
			this->m_BufferLengthInBytes = newLengthInBytes;
		}
	}
}

// Append a NUL-terminated string to the combo buffer
void CStringNodeBuffer::AppendString(const wchar_t * ToAppend)
{
	ASSERT_STRINGNODE_INVARIANT;

	// resize combo_buff to be large enough to hold ToAppend
	size_t toAppendLength = wcslen(ToAppend);
	GrowBy(toAppendLength);

	// append ToAppend
	wcsncpy(m_StringLimit, ToAppend, toAppendLength);
	m_StringLimit += toAppendLength;
}

void CStringNodeBuffer::AppendChar(wchar_t ToAppend)
{
	ASSERT_STRINGNODE_INVARIANT;

	// resize combo_buff to be large enough to hold ToAppend
	GrowBy(1);

	// append ToAppend
	*m_StringLimit = ToAppend;
	m_StringLimit++;
}
#else
class CStringNodeBuffer
{
public:

	CStringNodeBuffer() :buffer(){

	}
	~CStringNodeBuffer() {

	}
public:
	void AppendChar(wchar_t ch) {
		this->buffer.Append(ch);
	}
	void AppendString(const wchar_t* text) {
		this->buffer.Append(text);
	}
	size_t GetContentLength() { return this->buffer.length(); }
	const wxString& GetContent() { return this->buffer; }
	void Clear() { this->buffer.Clear(); }
	void* TakeContent()
	{
		size_t length = this->buffer.length();

		void* ptr = malloc((length+1) * sizeof(wchar_t) + sizeof(unsigned short));
		if (ptr != 0) {
			*(unsigned short*)ptr = 0;
			wcsncpy((wchar_t*)((char*)ptr + sizeof(unsigned short)), (const wchar_t*)this->buffer, length + 1);
		}

		return ptr;
	}
protected:
	wxString buffer;
};

#endif

// This is a hack to purge the "INPUTMODE_TO" buffer when
// loading from the editor.  If this is not done, any unused
// portion will hang around and be silently used the next time
// TO is run.
void rd_clearbuffer(CTextStream *strm)
{
	if (input_mode == INPUTMODE_To && strm->GetFile() == stdin)
	{
		g_ReadBuffer.Empty();
	}
}
wchar_t rd_fgetwc(CTextStream *stream)
{
	wchar_t c = 0;

	if (*stream != stdin)
	{
		c = stream->ReadChar();
	}
	else //strm == stdin (actually it's the buffer)
	{
		wxString userInput;
		if (g_ReadBuffer.IsEmpty())
		{
			// the buffer is empty, so we should read more
			switch (input_mode)
			{
			case INPUTMODE_To:
			{
				CStringPrintedNode parsedToLine(g_ToLine);
				ShowProcedureMiniEditor(parsedToLine, g_ReadBuffer);
				break;
			}

			case INPUTMODE_List:
				userInput = promptuser(GetResourceString(L"LOCALIZED_PROMPT_LIST"));
				if (userInput.length()==0)
				{
					// Halt when done
					err_logo(STOP_ERROR, NIL);
				}
				else
				{
					g_ReadBuffer.AppendString(userInput);
					userInput.clear();
				}
				break;

			case INPUTMODE_Pause:
				userInput = promptuser(GetResourceString(L"LOCALIZED_PROMPT_PAUSE"));
				if (userInput.length() == 0)
				{
					// continue when done
					g_ReadBuffer.AppendString(L"continue");
				}
				else
				{
					g_ReadBuffer.AppendString(userInput);
					userInput.clear();
				}
				break;

			case INPUTMODE_None:
				userInput = promptuser(GetResourceString(L"LOCALIZED_PROMPT_INPUT"));
				if (userInput.length()==0)
				{
					// Halt when done
					err_logo(STOP_ERROR, NIL);
				}
				else
				{
					g_ReadBuffer.AppendString(userInput);
					userInput.clear();
				}
				break;
			}

			check_stop(true);
			g_ReadBuffer.AppendChar(L'\n');
		}

		c = g_ReadBuffer.PopChar();
	}

	return c;
}

//static
//inline
//void rd_print_prompt(const wchar_t * /*str*/)
//{
//	//ndprintf(stdout,"%t",str);
//}
static bool IsDribbling(CTextStream* fileStream) {
	return (GetDribbleStream() != NULL && *fileStream == stdin);

}
// Reads the next complete line from FileStream into a string node.
// This may be more than a physical line of text if the line contains
// an open delimiter, such as "|", "[", or "(",  or if it ends in the
// line continuation character "~".  In this case, the physical lines
// will be concatenated into a single line.
//
// Note that reader() does not parse the line.
//
// FileStream - The stream to read the line from.
// Prompt     - Mostly ignored by FMSLogo.  If it's "RW", then
//              the characters "(", ")", "{", "}", "[", "]", and ';'
//              have no special meaning.
//
NODE *reader(CTextStream *fileStream, const wchar_t * Prompt)
{
	int paren = 0;
	int bracket = 0;
	int brace = 0;

	bool vbar = false;
	bool contin = true;
	bool incomment = false;
	bool raw = false;

	static wxString lender = wxString(L"\n") + GetResourceString(L"LOCALIZED_ALTERNATE_END") + wxString(L"\n");

	static const wchar_t ender[] = L"\nEND\n";
	const wchar_t *enderProgress = ender;

	const wchar_t *localizedEnderProgress = lender;

	NODETYPES this_type = STRING;

	if (!wcscmp(Prompt, L"RW"))
	{
		/* called by readword */
		Prompt = L"";
		contin = false;
	}
	else if (!wcscmp(Prompt, L"RAW"))
	{
		/* called by readrawline */
		Prompt = L"";
		contin = false;
		raw = true;
	}

	bool dribbling = IsDribbling(fileStream);

	if (*fileStream == stdin)
	{
		if (*Prompt != L'\0')
		{
			//rd_print_prompt(Prompt);

			if (dribbling)
			{
				DribbleWriteText(Prompt);
			}
		}

		input_blocking = true;
		clear_is_running_erract_flag();
	}

	CStringNodeBuffer lineBuffer;

	// this setjmp matches with the longjmp in unblock_input(), which 
	// is called when a PAUSE continues
	if (!setjmp(iblk_buf))
	{
		wchar_t c = rd_fgetwc(fileStream);
		while (c != (signed)WEOF && (c != L'\n' || vbar || paren || bracket || brace))
		{
			if (dribbling)
			{
				DribbleWriteChar(c);
			}

			// if c is a backslash, then read the next character and escape it
			if (!raw && c == L'\\')
			{
				c = rd_fgetwc(fileStream);
				if (c == (signed)WEOF)
				{
					break;
				}

				if (dribbling)
				{
					DribbleWriteChar(c);
				}
				if (c == 'n')
				{
					c = '\n'; //ggm
				}

				// mark this character as being backslashed
				c = ecma_set(c);

				// the resulting string will be backslashed
				this_type = BACKSLASH_STRING;

				if (c == ecma_set(L'\n') && *fileStream == stdin)
				{
					//rd_print_prompt(L"\\ ");
					if (dribbling)
					{
						DribbleWriteText(L"\\ ");
					}
				}
			}

			lineBuffer.AppendChar(c);

			if (raw)
			{
				c = rd_fgetwc(fileStream);
				continue;
			}

			if (input_mode == INPUTMODE_To)
			{
				// We are parsing a TO.  Check if we hit the TO ender.

				// Is this the English ender?
				if (uncapital(c) == uncapital(*enderProgress))
				{
					enderProgress++;
					if (*enderProgress == L'\0')
					{
						// We found the ender while still 
						// inside a [, |, (, or {.
						err_logo(DEEPEND, deepend_proc_name);
						break;
					}
				}
				else
				{
					// start over on the ender
					enderProgress = ender;
				}

				// Is this the localized (non-English) ender?
				if (uncapital(c) == uncapital(*localizedEnderProgress))
				{
					localizedEnderProgress++;
					if (*localizedEnderProgress == L'\0')
					{
						// We found the ender while still 
						// inside a [, |, (, or {.
						err_logo(DEEPEND, deepend_proc_name);
						break;
					}
				}
				else
				{
					// start over on the localized ender
					localizedEnderProgress = lender;
				}
			}

			if (!incomment)
			{
				if (c == L'|')
				{
					vbar = !vbar;
				}
				else if (contin && !vbar)
				{
					switch (c)
					{
					case L'(':
						paren++;
						break;

					case L')':
						if (paren)
						{
							paren--;
						}
						break;

					case L'[':
						bracket++;
						break;

					case L']':
						if (bracket)
						{
							bracket--;
						}
						break;

					case L'{':
						brace++;
						break;

					case L'}':
						if (brace)
						{
							brace--;
						}
						break;

					case L';':
						incomment = true;
						break;
					}
				}
			}

			// any string that contains special characters needs to be
			// converted to a VBAR string so that it can be printed
			// out and re-read without a loss of data.  See bug #2516248.
			if (this_type == STRING && is_special_character(c))
			{
				this_type = VBAR_STRING;
			}

			if (c == L'\n')
			{
				// newlines end comment
				incomment = false;
				if (*fileStream == stdin)
				{
					//rd_print_prompt(vbar ? L"| " : L"~ ");

					if (dribbling)
					{
						DribbleWriteText(vbar ? L"| " : L"~ ");
					}
				}
			}

			while (!vbar && c == L'~' && (c = rd_fgetwc(fileStream)) != (signed)WEOF)
			{
				CDynamicBuffer whitespace;

				// Copy linear whitespace to the "whitespace" buffer.
				// We want to ignore if it the goes to the end of the
				// line, but we want to keep it if it does not.
				while (c == L' ' || c == L'\t')
				{
					whitespace.AppendChar(c);
					c = rd_fgetwc(fileStream);
				}

				if (c != L'\n')
				{
					// append the linear whitespace that we skipped (if any)
					if (whitespace.GetBufferLength() != 0)
					{
						const wchar_t * ws = whitespace.GetBuffer();
						lineBuffer.AppendString(ws);
						if (dribbling)
						{
							DribbleWriteText(ws);
						}
					}
				}

				if (dribbling)
				{
					DribbleWriteChar(c);
				}

				lineBuffer.AppendChar(c);

				if (c == L'\n' && *fileStream == stdin)
				{
					incomment = false;

					//rd_print_prompt(L"~ ");

					if (dribbling)
					{
						DribbleWriteText(L"~ ");
					}
				}
			}

			c = rd_fgetwc(fileStream);
		}
	}

	input_blocking = false;

	if (dribbling)
	{
		DribbleWriteChar(L'\n');
	}

	size_t l = lineBuffer.GetContentLength();

	void* p = lineBuffer.TakeContent();

	NODE * line = make_strnode_no_copy(
		(const wchar_t*)((char*)p+sizeof(unsigned short)),
		(wchar_t*)p,
		l,
		this_type);
#ifdef _WINDOWS
#ifdef _DEBUG
	OutputDebugString(lineBuffer.GetContent());
	OutputDebugString(L"\n");
#endif
#endif
	return line;
}

static NODE *list_to_array(NODE *list)
{
	int len = list_length(list);

	NODE * result = make_array(len);
	if (NOT_THROWING)
	{
		setarrorg(result, 1);

		int i = 0;
		for (NODE * np = list; np; np = cdr(np))
		{
			(getarrptr(result))[i++] = vref(car(np));
		}
	}

	return result;
}

#define parens(ch)      (ch == L'(' || ch == L')' || ch == L';')
#define infixs(ch)      (ch == L'*' || ch == L'/' || ch == L'+' || ch == L'-' || ch == L'=' || ch == L'<' || ch == L'>')
#define white_space(ch) (ch == L' ' || ch == L'\t' || ch == L'\n')

// Parses the text from "*inln" to "inlimit", or until the first "endchar" is found.
// If endchar==-1, then the only limit is inlimit, which is interpreted as the EOF.
// *inln is updated to be the character on which parsing stopped and it may end up pointing
// to a NUL character that it not within the original string.
// The parsed text is returned as a NODE* list.
// Nested arrays and lists are parsed into their structured form.
// parser_iterate() sets stopping_flag to THROWING if it encounters a syntax error.
//
// if "ignore_comments" is true then comments should be stripped out of the parsed stream.
//
static NODE * parser_iterate(
	const wchar_t **inln,
	const wchar_t *inlimit,
	bool        ignore_comments,
	int         endchar
)
{
	const wchar_t *word_start = NULL;
	static const wchar_t terminate = L'\0'; // KLUDGE

	int word_length = 0;

	NODETYPES this_type = STRING;

	bool broken = false;
	bool vbar = false;

	CAppendableList return_list;

	wchar_t ch = L'\0';
	do
	{
		/* get the current character and increase pointer */
		ch = **inln;
		if (!vbar && word_length == 0)
		{
			word_start = *inln;
		}
		if (++(*inln) >= inlimit)
		{
			// Fake a NUL terminator
			*inln = inlimit = &terminate;
		}

		/* skip through comments and line continuations */
		while (!vbar &&
			((ignore_comments && ch == L';') || (ch == L'~' && **inln == L'\n')))
		{
			// If this is a line continuation, keep going 
			// until we reach the end of the next line
			while (ch == L'~' && **inln == L'\n')
			{
				// Advance to the next character.
				if (++(*inln) >= inlimit)
				{
					// Fake a NUL terminator
					*inln = inlimit = &terminate;
				}
				ch = **inln;

				if (word_length == 0)
				{
					// The line continuation character wasn't inserted in the
					// middle of a word, so start a new one.
					word_start = *inln;
				}
				else
				{
					// if we are in the middle of a word and we continued into
					// the start of an array/list, then set "ch" to insert a word
					// boundary.
					if (ch == L'[' || ch == L']' || ch == L'{' || ch == L'}')
					{
						ch = L' ';
						break;
					}
					else
					{
						// The logical line requires mending across physical lines.
						broken = true;
					}
				}

				// Mark the we have processed "ch".
				if (++(*inln) >= inlimit)
				{
					// Fake a NUL terminator
					*inln = inlimit = &terminate;
				}
			}

			// If this is a comment and we're supposed to ignore
			// comments keep going until the end of the line.
			if (ignore_comments && ch == L';')
			{
				// While ch is not the end of the string and
				// the next char is not the end of the line
				while (ch != L'\0' && **inln != L'\n')
				{
					// advance to the next character
					ch = **inln;
					if (word_length == 0)
					{
						// The comment character wasn't inserted in the
						// middle of a word, so start a new one.
						word_start = *inln;
					}
					else
					{
						// The comment character was inserted in the middle of a word,
						// so flag that this line needs mending.
						broken = true;
					}

					if (++(*inln) >= inlimit)
					{
						// Fake a NUL terminator
						*inln = inlimit = &terminate;
					}
				}

				// mark this as the end of a line
				if (ch != L'\0' && ch != L'~')
				{
					ch = L'\n';
				}
			}
		}

		// flag that this word will be of BACKSLASH_STRING type
		if (ecma_get(ch))
		{
			this_type = BACKSLASH_STRING;
		}

		if (ch == L'|')
		{
			vbar = !vbar;
			this_type = VBAR_STRING;
			broken = true;   // so we'll copy the chars
		}
		else if (vbar || (!white_space(ch) && ch != L']' &&
			ch != L'{' && ch != L'}' &&
			ch != L'[' && ch != L'\0'))
		{
			// This is another character in a simple word, like "abc
			// or a vbar quoted word like "| abc |
			// Either way, extend the word to include this character.
			word_length++;
		}

		NODE *tnode = NIL;

		if (endchar == -1 && **inln == L'\0')
		{
			// We have reached the EOF for the outermost invocation.
			if (ch == L'~')
			{
				// We were parsing a line continuation.
				// Since there's nothing to continue to, close the
				// string where we are.
				word_length--;
				ch = L'\0';
			}
		}

		if (vbar)
		{
			continue;
		}
		else if (ch == endchar && endchar != -1)
		{
			// We have reached the character that we were seeking.
			// Break out of the loop, leaving endchar for the caller
			// to process.
			break;
		}
		else if (ch == L']')
		{
			err_logo(UNEXPECTED_BRACKET, NIL);
		}
		else if (ch == L'}')
		{
			err_logo(UNEXPECTED_BRACE, NIL);
		}
		else if (ch == L'[')
		{
			// this is a '[', parse a new list (until we see a ])
			tnode = cons_list(parser_iterate(inln, inlimit, ignore_comments, L']'));
			if (**inln == L'\0')
			{
				ch = L'\0';
			}
		}
		else if (ch == L'{')
		{
			// this is a '{', parse a new array (until we see a })
			NODE * array_as_list = parser_iterate(inln, inlimit, ignore_comments, L'}');
			NODE * array = list_to_array(array_as_list);
			gcref(array_as_list);

			if (NOT_THROWING)
			{
				tnode = cons_list(array);
				if (**inln == L'@')
				{
					// parse the origin as a decimal number
					wchar_t * unparsedPortion;
					long origin = wcstol((*inln) + 1, &unparsedPortion, 10);
					*inln = unparsedPortion;

					setarrorg(car(tnode), origin);
				}
				if (**inln == L'\0')
				{
					ch = L'\0';
				}
			}
			else
			{
				tnode = NIL;
			}
		}
		else if (white_space(ch) || ch == L'\0' ||
			**inln == L']' || **inln == L'[' ||
			**inln == L'{' || **inln == L'}')
		{
			// this character or the next one will terminate string
			if (word_length > 0)
			{
				// Create any word that we have parsed up until now.
				wchar_t * (*copyRoutine) (wchar_t *, const wchar_t *, int);

				if (broken)
				{
					// The logical line is broken across several lines,
					// so it must be mended.
					copyRoutine = ignore_comments ? mend_strnzcpy : mend_nosemi;
				}
				else
				{
					// The logical line is entirely on a single line,
					// so a normal string copy will suffice.
					copyRoutine = strnzcpy;
				}

				NODE * string_node = make_strnode(
					word_start,
					word_length,
					this_type,
					copyRoutine);

				tnode = cons_list(string_node);
				this_type = STRING;
				word_length = 0;
				broken = false;
			}
		}

		// put the word onto the end of the return list
		return_list.AppendList(tnode);
	} while (ch != L'\0');


	return return_list.GetList();
}

NODE *parser(NODE *nd, bool ignore_comments)
{
	NODE * string_node = cnv_node_to_strnode(nd);
	ref(string_node);

	int slen = getstrlen(string_node);
	const wchar_t * lnsav = getstrptr(string_node);
	NODE * rtn = parser_iterate(&lnsav, lnsav + slen, ignore_comments, -1);

	gcref(nd);
	deref(string_node);
	return rtn;
}

NODE *lparse(NODE *args)
{
	NODE *val = Unbound;

	NODE * arg = string_arg(args);
	if (NOT_THROWING)
	{
		val = parser(arg, false);
	}
	return val;
}

static NODE *runparse_node(NODE *nd, NODE **ndsptr)
{
	if (nd == Minus_Tight)
	{
		return cons_list(nd);
	}

	NODE * snd = cnv_node_to_strnode(nd);
	ref(snd);
	const wchar_t *wptr = getstrptr(snd);
	const int   wlen = getstrlen(snd);
	NODETYPES   wtyp = nodetype(snd);
	int         wcnt = 0;

	CAppendableList return_list;

	bool monadic_minus = false;

	while (wcnt < wlen)
	{
		if (*wptr == L';')
		{
			*ndsptr = NIL;
			break;
		}

		NODE *tnode;

		if (*wptr == L'"')
		{
			int tcnt = 0;
			const wchar_t * tptr = ++wptr;
			wcnt++;
			while (wcnt < wlen && !parens(*wptr))
			{
				if (wtyp == BACKSLASH_STRING && ecma_get(*wptr))
				{
					wtyp = PUNBOUND; // flag for "\( case
				}
				wptr++, wcnt++, tcnt++;
			}

			NODE * strnode;
			if (wtyp == PUNBOUND)
			{
				wtyp = BACKSLASH_STRING;
				strnode = make_strnode(tptr, tcnt, wtyp, noparity_strnzcpy);
			}
			else
			{
				strnode = make_strnode(tptr, tcnt, wtyp, strnzcpy);
			}
			tnode = make_quote(intern(strnode));
		}
		else if (*wptr == L':')
		{
			int tcnt = 0;
			const wchar_t * tptr = ++wptr;
			wcnt++;
			while (wcnt < wlen && !parens(*wptr) && !infixs(*wptr))
			{
				wptr++, wcnt++, tcnt++;
			}
			tnode = make_colon(intern(make_strnode(tptr, tcnt, wtyp, strnzcpy)));
		}
		else if (wcnt == 0 && *wptr == L'-' && !monadic_minus &&
			wcnt + 1 < wlen && !white_space(*(wptr + 1)))
		{
			/* minus sign with space before and no space after is unary */
			tnode = make_intnode(0);
			monadic_minus = true;
		}
		else if (parens(*wptr) || infixs(*wptr))
		{
			if (monadic_minus)
			{
				tnode = Minus_Tight;
				monadic_minus = false;
			}
			else if (wcnt + 1 < wlen &&
				((wptr[0] == L'<' && (wptr[1] == L'=' || wptr[1] == L'>')) ||
				(wptr[0] == L'>' && wptr[1] == L'=')))
			{
				// This is a two character infix operator: "<=" or ">=" or "<>"
				tnode = intern(make_strnode(wptr, 2, STRING, strnzcpy));
				wptr++, wcnt++;
			}
			else
			{
				tnode = intern(make_strnode(wptr, 1, STRING, strnzcpy));
			}
			wptr++, wcnt++;
		}
		else
		{
			int tcnt = 0;
			const wchar_t * tptr = wptr;
			// isnumb
			// 0 means digits so far, 
			// 1 means just saw 'e' so minus can be next
			// 2 means no longer eligible even if an 'e' comes along 
			// 3 means we saw a '?'
			// 4 means nothing yet;
			int isnumb = 4;
			if (*wptr == L'?')
			{
				// turn ?5 to (? 5)
				isnumb = 3;
				wptr++, wcnt++, tcnt++;
			}

			bool gotdot = false;
			while (wcnt < wlen &&
				!parens(*wptr) &&
				(!infixs(*wptr) || (isnumb == 1 && (*wptr == L'-' || *wptr == L'+'))))
			{
				if (isnumb == 4 && IsDigit(*wptr))
				{
					// could be a number
					isnumb = 0;
				}

				if (isnumb == 0 && (*wptr == L'e' || *wptr == L'E'))
				{
					// just saw an 'e', so a '-' or '+' could be next
					isnumb = 1;
				}
				else if ((!IsDigit(*wptr) && (*wptr != L'.' || gotdot)) || isnumb == 1)
				{
					// can't be a number
					// REVISIT: can we break out of the loop here?
					isnumb = 2;
				}

				if (*wptr == L'.')
				{
					gotdot = true;
				}
				wptr++, wcnt++, tcnt++;
			}

			if (MAX_NUMBER <= tcnt)
			{
				// too many characters to be a valid number
				isnumb = 2;
			}

			if (isnumb == 3 && tcnt > 1)
			{
				// turn ?5 into (? 5)

				// append "( ? 5" now
				NODE * qmtnode = cons_list(
					Left_Paren,
					Query,
					cnv_node_to_numnode(make_strnode(tptr + 1, tcnt - 1, wtyp, strnzcpy)));

				return_list.AppendList(qmtnode);

				// append ")" later
				tnode = Right_Paren;
			}
			else if (isnumb < 2)
			{
				tnode = cnv_node_to_numnode(make_strnode(tptr, tcnt, wtyp, strnzcpy));
			}
			else
			{
				tnode = intern(make_strnode(tptr, tcnt, wtyp, strnzcpy));
			}
		}

		// append tnode to the end of return_list
		return_list.AppendElement(tnode);
	}
	deref(snd);
	return return_list.GetList();
}
NODE *runparse(NODE *ndlist)
{
	if (nodetype(ndlist) == RUN_PARSE)
	{
		// already run-parsed
		return parsed__runparse(ndlist);
	}

	if (!is_list(ndlist))
	{
		err_logo(BAD_DATA_UNREC, ndlist);
		return NIL;
	}

	if (ndlist != NIL)
	{
		NODE * curnd = car(ndlist);
		if (is_string(curnd) &&
			getstrlen(curnd) >= 2 &&
			getstrptr(curnd)[0] == L'#' &&
			getstrptr(curnd)[1] == L'!')
		{
			// shell-script #! treated as comment line
			return NIL;
		}
	}

	CAppendableList return_list;

	while (ndlist != NIL)
	{
		NODE *tnode;

		NODE * curnd = car(ndlist);
		ndlist = cdr(ndlist);
		if (!is_word(curnd))
		{
			tnode = cons_list(curnd);
		}
		else
		{
			if (!numberp(curnd))
			{
				tnode = runparse_node(curnd, &ndlist);
			}
			else
			{
				tnode = cons_list(cnv_node_to_numnode(curnd));
			}
		}

		// append tnode to the end of return_list
		return_list.AppendList(tnode);

		if (check_throwing)
		{
			break;
		}
	}

	return return_list.GetList();
}
NODE *lrunparse(NODE *args)
{
	NODE * arg = car(args);
	while (nodetype(arg) == ARRAY && NOT_THROWING)
	{
		setcar(args, err_logo(BAD_DATA, arg));
		arg = car(args);
	}

	if (NOT_THROWING && !is_aggregate(arg))
	{
		arg = parser(arg, true);
	}

	if (NOT_THROWING)
	{
		return runparse(arg);
	}

	return Unbound;
}


void uninitialize_parser()
{
	deref(deepend_proc_name);
	deepend_proc_name = NIL;
	g_ReadBuffer.Dispose();
}
