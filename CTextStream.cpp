#include "CTextStream.h"


size_t CTextStream::Read(wchar_t * buffer, size_t length)
{
	size_t c = 0;
	if (this->IsValid() && buffer != 0) {
		wchar_t ch = WEOF;
		while ((ch = this->ReadChar()) !=(signed) WEOF) {
			buffer[c++] = ch;
			if (c == length) {
				break;
			}
		}
	}
	return c;
}

wxString CTextStream::ReadAll()
{
	wxString all;
	if (this->IsValid()) {
		wchar_t ch = WEOF;
		while ((ch = this->ReadChar()) !=(signed) WEOF) {
			all += ch;
		}
	}
	return all;
}

wxString CTextStream::ReadLine()
{
	wxString line;
	if (this->IsValid()) {
		wchar_t ch = WEOF;
		while ((ch = this->ReadChar()) !=(signed) WEOF) {
			if (line.EndsWith(this->newline)) {
				line.RemoveLast(this->newline.length());
				break;
			}
			else {
				line += ch;
			}
		}
	}
	return line;
}

wchar_t CTextStream::ReadChar()
{
	return WEOF;
}

int CTextStream::ReadByte()
{
	return EOF;
}

wchar_t CTextStream::PeekChar()
{
	return WEOF;
}

int CTextStream::PeekByte()
{
	return EOF;
}

size_t CTextStream::Write(wchar_t * buffer, size_t length)
{
	return 0;
}
size_t CTextStream::Write(const wchar_t * FormatString, ...)
{
	wxString message;
	// Format and print the message to stderr
	va_list args;
	va_start(args, FormatString);
	message = wxString::FormatV(FormatString, args);
	//vfwprintf(stderr, FormatString, args);
	va_end(args);

	return this->Write(message);
}
size_t CTextStream::Write(const wxString & text)
{
	size_t c = 0;
	if (this->IsValid()) {
		for (size_t i = 0; i < text.length(); i++) {
			if (this->WriteChar(text[i])) {
				c++;
			}
			else {
				break;
			}
		}
	}
	return c;
}

size_t CTextStream::WriteLine(const wxString & text)
{
	return this->Write(text) + this->Write(this->newline);
}

bool CTextStream::WriteChar(wchar_t ch)
{
	return false;
}

bool CTextStream::WriteByte(char ch)
{
	return false;
}

bool CTextStream::IsValid()
{
	return false;
}

bool CTextStream::IsEOF()
{
	return true;
}

off64_t CTextStream::GetPosition()
{
	return 0LL;
}

int CTextStream::SetPosition(off64_t offset, int origin)
{
	return 0;
}

off64_t CTextStream::GetLength()
{
	off64_t op = this->GetPosition();
	this->SetPosition(0, SEEK_END);
	off64_t ep = this->GetPosition();
	this->SetPosition(op, SEEK_SET);

	return ep + 1;
}

void CTextStream::Flush()
{
}

void CTextStream::Close()
{
}

wxString & CTextStream::NewLine()
{
	return this->newline;
}

CTextStream::operator FILE*()
{
	return this->GetFile();
}

FILE * CTextStream::GetFile()
{
	return 0;
}

void CTextStream::SetFile(FILE * file)
{
}

bool CTextStream::IsLittleEndian()
{
	unsigned short us = 0xff;
	unsigned char p0 = *(unsigned char*)&us;
	return p0 == 0xff;
}

wchar_t CTextStream::EnsureEndian(wchar_t ch)
{
	if (this->mem_bol != this->file_bol) {

		ch = this->SwapByteOrder(ch);
	}

	return ch;
}

wxString & CTextStream::EnsureEndian(wxString & text)
{
	if (this->file_bol != this->mem_bol) {
		for (size_t i = 0; i < text.length(); i++) {
			text[i] = this->EnsureEndian(text[i]);
		}
	}
	return text;
}
wchar_t CTextStream::SwapByteOrder(wchar_t c)
{
	wchar_t ch = c;
	if (sizeof(wchar_t) == sizeof(unsigned short)) {
		ch = this->SwapByteOrderShort((unsigned short)ch);
	}
	else if (sizeof(wchar_t) == sizeof(unsigned int))
	{
		ch = this->SwapByteOrderLong((unsigned int)ch);
	}
	return ch;

}

unsigned short CTextStream::SwapByteOrderShort(unsigned short s)
{
	return ((s & 0xff) << 8 | (s & 0xff00) >> 8);
}

unsigned int CTextStream::SwapByteOrderLong(unsigned int i)
{
	return (SwapByteOrderShort(i & 0xffff) << 16) | (SwapByteOrderShort(i & 0xffff0000) >> 16);
}

wchar_t CTextStream::GetMachineBOM()
{
	return this->IsLittleEndian() ? UTF16LE_BOM : UTF16BE_BOM;
}

CTextStream::CTextStream(const wxString& newline)
	:mem_bol(0)
	,file_bol(0)
	,newline(newline)
{
	this->file_bol = this->mem_bol = this->IsLittleEndian() ? CTS_LITTLE_ENDIAN : CTS_BIG_ENDIAN;
}

CTextStream::~CTextStream()
{
	this->Flush();
	this->Close();
}
