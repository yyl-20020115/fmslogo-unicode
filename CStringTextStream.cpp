#include "CStringTextStream.h"

CStringTextStream::CStringTextStream(const wxString& content,const wxString& newline)
	:CTextStream(newline)
	,content(content)
	,pos(0LL)
{

}


CStringTextStream::~CStringTextStream()
{
}

size_t CStringTextStream::Read(wchar_t * buffer, size_t length)
{
	size_t c = 0;
	if (buffer != 0) {
		off64_t ep = this->pos + length;
		for (; this->pos < ep && this->pos< (off64_t)this->content.length(); this->pos++) {
			buffer[c] = this->content[(size_t)this->pos];
			c++;
		}
	}
	return c;
}

wxString CStringTextStream::ReadAll()
{
	return this->pos == 0LL ? this->content : this->content.substr((size_t)this->pos);
}

wxString CStringTextStream::ReadLine()
{
	size_t fp = this->content.find(this->newline, this->pos);
	if (fp == wxString::npos) {
		return this->ReadAll();
	}
	else {
		wxString line = this->content.substr(this->pos, fp - this->pos);
		this->pos += (fp + this->newline.length());
		return line;
	}
}

wchar_t CStringTextStream::ReadChar()
{
	wchar_t ch = this->PeekChar();
	if (ch != (signed)WEOF) {
		this->pos++;
	}
	return ch;
}

int CStringTextStream::ReadByte()
{
	int ch = this->PeekByte();
	if(ch!=EOF){
		this->pos++;
	}
	return ch;
}

wchar_t CStringTextStream::PeekChar()
{
	if (this->pos < (off64_t)this->content.length()) {
		return this->content[(size_t)this->pos];
	}
	return WEOF;
}

int CStringTextStream::PeekByte()
{
	return this->IsEOF() ? EOF : this->PeekChar();
}

bool CStringTextStream::WriteChar(wchar_t ch)
{
	if (this->pos < (off64_t)this->content.length()) {
		this->content[(size_t)this->pos] = ch;
		return true;
	}
	else if(this->pos == (signed)this->content.length()) {
		this->content += ch;
		this->pos++;
		return true;
	}
	return false;
}

bool CStringTextStream::WriteByte(char ch)
{
	return this->WriteChar(ch);
}

bool CStringTextStream::IsValid()
{
	return true;
}

bool CStringTextStream::IsEOF()
{
	return this->pos == (signed)this->content.length();
}

off64_t CStringTextStream::GetPosition()
{
	return this->pos;
}

int CStringTextStream::SetPosition(off64_t offset, int origin)
{
	int ret = -1;
	switch (origin) {
	case SEEK_SET:
		if (offset < (off64_t)this->content.length()) {
			this->pos = offset;
			ret = 0;
		}
		break;
	case SEEK_CUR:
		if (this->pos + offset < (off64_t)this->content.length()) {
			this->pos += offset;
			ret = 0;
		}
		break;
	case SEEK_END:
		if (this->pos >= offset) {
			this->pos -= offset;
			ret = 0;
		}
		break;
	}
	return ret;
}

void CStringTextStream::Close()
{
	this->content.Clear();
}

void CStringTextStream::Clear()
{
	this->Reset();
	this->content.Clear();
}

void CStringTextStream::Reset()
{
	this->pos = 0LL;
}

wxString & CStringTextStream::Append(const wxString & text)
{
	this->content.Append(text);
	return this->content;
}

off64_t CStringTextStream::GetLength()
{
	return this->content.length();
}

wxString & CStringTextStream::GetContent()
{
	return this->content;
}
