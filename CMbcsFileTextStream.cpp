#include "CMbcsFileTextStream.h"
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <wchar.h>

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
	, utf8_bom(0)
{
}
CMbcsFileTextStream::CMbcsFileTextStream(FILE* file, bool close_on_exit,const wxString& newline)
	: CFileTextStream(file, close_on_exit,newline)
    , cbuffer()
	, cbufferlength()
	, utf8_bom(0)
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

bool CMbcsFileTextStream::Open(const wxString & path, const wxString & mode, bool check_utf8_bom)
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
        

		//file_bol is determined by read if bom found
		if (check_utf8_bom && (mode.Contains(L"r") || mode.Contains(L"a"))) {

			wchar_t first = this->PeekChar();

			switch (first) {
			case UTF16BE_BOM:
				this->utf8_bom = first;
				break;
			case UTF16LE_BOM:
				this->utf8_bom = first;
				break;
			default:
				break;
			}
		}
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
    
    char cbuffer[sizeof(this->cbuffer)] = {0};
    size_t cbl = this->cbufferlength;
    memcpy(cbuffer,this->cbuffer,sizeof(cbuffer));
    this->ClearCBuffer();
    
    off64_t p = this->GetPosition();
    
    wchar_t ch = this->ReadChar();
	
    this->SetPosition(p,SEEK_SET);
    
    memcpy(this->cbuffer,cbuffer,sizeof(cbuffer));
    this->cbufferlength = cbl;
   
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
            int n = 0;
#ifdef _WINDOWS
            n = _mbclen((unsigned char*)cbuffer);
#else
			n = mblen(cbuffer,MB_CUR_MAX);
#endif
			if (n <= 0) {
				this->badposition = this->GetPosition() - sizeof(cbuffer);
			}
			n = (n>=1) ? n : 1;
			int ret = mbtowc(&c, cbuffer, n);
			if (ret <= 0) {
				//bad input, we treat the first char as value
				c = cbuffer[0];
				c &= 0xff; //NOTICE: maybe wrong , but we have to make it in the range of char!
				n = 1;
			}
			for (int i = 0; i < (int)sizeof(cbuffer) - 1; i++) {
				cbuffer[i] = (i + (unsigned)n) < sizeof(cbuffer) ? cbuffer[i + n] : 0;
			}
			if (cbufferlength >= (unsigned)n) {
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

    
wchar_t CMbcsFileTextStream::WriteBOM()
{
    wchar_t bom = this->utf8_bom;
    if(bom == UTF16LE_BOM || bom == UTF16BE_BOM)
    {
        this->WriteChar(bom);
    }
	return this->utf8_bom;
}
wchar_t CMbcsFileTextStream::SkipBOM()
{
    wchar_t ch = this->PeekChar();

	if (ch == UTF16LE_BOM || ch == UTF16BE_BOM) {
		this->ReadChar();
	}
	else {
		ch = 0;
	}
	return ch;
}
wchar_t CMbcsFileTextStream::GetFileBOM()
{
    return this->utf8_bom;
}

void CMbcsFileTextStream::Reset()
{
	CTextStream::Reset();
	this->ClearCBuffer();
}
    
