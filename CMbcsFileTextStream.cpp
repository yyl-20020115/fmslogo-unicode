#include "CMbcsFileTextStream.h"

#ifdef _WINDOWS
#include <mbstring.h>
#endif
off64_t CMbcsFileTextStream::WriteAll(const wxString& path, CTextStream * source, bool append)
{
	off64_t c = 0;
	if (source != 0) {
		CMbcsFileTextStream cmfts;
		if (cmfts.Open(path, (append ? L"w+" : L"w")))
		{
			off64_t sp = cmfts.GetPosition();
			wchar_t ch = WEOF;
			while ((ch = source->ReadChar()) !=(signed) WEOF) 
			{
				cmfts.WriteChar(ch);
			}
			off64_t ep = cmfts.GetPosition();
			c = ep - sp;
		}
	}

	return c;
}
off64_t CMbcsFileTextStream::ReadAll(const wxString & path, CTextStream * dest)
{
	size_t c = 0;
	if (dest != 0) {
		CMbcsFileTextStream cmfts;
		if (cmfts.Open(path, L"r"))
		{
			off64_t sp = cmfts.GetPosition();
			wchar_t ch = WEOF;
			while ((ch = cmfts.ReadChar()) != (signed)WEOF)
			{
				dest->WriteChar(ch);
			}
			off64_t ep = cmfts.GetPosition();
			c = ep - sp;
		}
	}
	return c;
}
CMbcsFileTextStream::CMbcsFileTextStream(const wxString& newline)
	: CFileTextStream(newline)
    , cbuffer()
	, cbufferlength()
	
{
}
CMbcsFileTextStream::CMbcsFileTextStream(FILE* file, bool close_on_exit,const wxString& newline)
	: CFileTextStream(file, close_on_exit,newline)
    , cbuffer()
	, cbufferlength()
{
}

CMbcsFileTextStream::~CMbcsFileTextStream()
{

}

void CMbcsFileTextStream::Close()
{
	this->ClearCBuffer();
	CFileTextStream::Close();
}

bool CMbcsFileTextStream::Open(const wxString & path, const wxString & mode)
{
	bool done =  (this->IsValid()) ? false :
		(this->file =
#ifdef _WINDOWS
        _wfopen(path,mode)
#else
		fopen((const char*)path, (const char*)mode)
#endif
        ) != 0;
    if(done)
    {
		this->for_reading = mode.Contains(L"r");
        this->for_writing = mode.Contains(L"w") || mode.Contains(L"a");
    }
    return done;
}

wchar_t CMbcsFileTextStream::ReadChar()
{
	return this->ComposeChar();
}

int CMbcsFileTextStream::ReadByte()
{
	int ch = EOF;
	if (this->IsValid()) {
		ch = getc(this->file);
	}
	return ch;
}

wchar_t CMbcsFileTextStream::PeekChar()
{
	int ch = this->PeekByte();
	return ch == EOF ? WEOF : (wchar_t)ch;
}

int CMbcsFileTextStream::PeekByte()
{
	int ch = EOF;
	if (this->IsValid()) {
		ch = getc(this->file);
		ungetc(ch, this->file);
	}
	return ch;
}


bool CMbcsFileTextStream::WriteChar(wchar_t ch)
{
	char buffer[MB_LEN_MAX + 1] = { 0 };
	int c = this->CharToBytes(ch, buffer);
	for (int i = 0; i < c; i++) {
		this->WriteByte(buffer[i]);
	}
	return c>0;
}

bool CMbcsFileTextStream::WriteByte(char ch)
{
	char ret = EOF;
	if (this->IsValid()) {
		ret = putc(ch, this->file);
	}
	return ret != EOF;
}
FileTextStreamType CMbcsFileTextStream::GetStreamType()
{
	return FileTextStreamType::MBCS;
}

bool CMbcsFileTextStream::IsEOF()
{
	return CFileTextStream::IsEOF() && this->cbufferlength == 0;
}

int CMbcsFileTextStream::CharToBytes(wchar_t ch, char * buffer)
{
	int c = 0;
	int converted = wctomb(buffer, ch);
	if (converted > 0)
	{
#ifdef _WINDOWS
		c = _mbclen((unsigned char*)buffer);
#else
        c = mblen(buffer,MB_CUR_MAX);
#endif
	}
	else if (converted == 0) {
		c = 0; //should not happen
	}
	else {
		//treat as ansi, as we don't know how to convert
		*buffer = (char)(ch & 0xff);
		c = 1;
	}
	return c;
}

wchar_t CMbcsFileTextStream::ComposeChar()
{
	wchar_t c = WEOF;
	if (this->IsValid())
	{
		size_t count = 0;

		if (cbufferlength < MB_LEN_MAX) {
			count = fread(cbuffer + cbufferlength, sizeof(char), MB_LEN_MAX - cbufferlength, this->file);
			cbufferlength += count;
		}
		if (cbufferlength > 0)
		{
#ifdef _WINDOWS
			size_t n = _mbclen((unsigned char*)cbuffer);
#else
			size_t n = mblen(cbuffer,MB_CUR_MAX);
#endif
			n = (n == 1 || n == 2) ? n : 1;
			int ret = mbtowc(&c, cbuffer, n);
			if (ret <= 0) {
				//bad input, we treat the first char as value
				c = cbuffer[0];
				n = 1;
			}
			for (int i = 0; i < (int)sizeof(cbuffer) - 1; i++) {
				cbuffer[i] = (i + n) < sizeof(cbuffer) ? cbuffer[i + n] : 0;
			}
			if (cbufferlength >= n) {
				cbufferlength -= n;
			}
			else {
				cbufferlength = 0;
			}
		}
	}
	return c;
}

void CMbcsFileTextStream::ClearCBuffer()
{
	this->cbufferlength = 0;
	memset(this->cbuffer, 0, sizeof(this->cbuffer));
}
