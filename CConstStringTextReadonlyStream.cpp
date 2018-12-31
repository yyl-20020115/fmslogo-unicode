#include "CConstStringTextReadonlyStream.h"



CConstStringTextReadonlyStream::CConstStringTextReadonlyStream(const wchar_t* content, size_t length, const wxString& newline)
	: CTextStream(newline)
    , content(content)
	, length(length)
	, pos()
{
	if (length > 0) {
		wchar_t first = this->SwapByteOrder(*content);
		switch (first)
		{
		case UTF16LE_BOM:
			this->file_bol = CTS_LITTLE_ENDIAN;
			break;
		case UTF16BE_BOM:
			this->file_bol = CTS_BIG_ENDIAN;
			break;
		default:
			this->file_bol = 0;
			break;
		}
		if (this->file_bol != 0) {
			this->pos++;
		}
		else {
			this->file_bol = this->mem_bol;
		}
	}
}


CConstStringTextReadonlyStream::~CConstStringTextReadonlyStream()
{
}

size_t CConstStringTextReadonlyStream::Read(wchar_t * buffer, size_t length)
{
	size_t c = 0;
	if (buffer != 0) {
		off64_t ep = this->pos + length;
		for (; this->pos < ep && this->pos<(off64_t)this->length; this->pos++) {
			buffer[c] = this->EnsureEndian(this->content[(size_t)this->pos]);
			c++;
		}
	}
	return c;
}

wxString CConstStringTextReadonlyStream::ReadAll()
{
    wxString text(this->content+this->pos,(this->length-this->pos));
	return this->EnsureEndian(text);
}

const wchar_t* wcsnstr(const wchar_t* dest, const wchar_t* src, size_t dest_length, size_t src_length)
{
	size_t i = 0;
	size_t j = 0;
	while (i <= dest_length - 1 && j <= src_length - 1)
	{
		if (dest[i] == src[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == src_length)
	{
		return dest + i - src_length;
	}

	return 0;
}

wxString CConstStringTextReadonlyStream::ReadLine()
{
	if (this->IsEOF()) {
		return wxString();
	}
	else if (this->newline.length() == 0) {
		return this->ReadAll();
	}
	else
	{
		const wchar_t* fp = wcsnstr(this->content + (size_t)this->pos,this->newline,(this->length- (size_t)this->pos), this->newline.length());

		if (fp == 0) {
			return this->ReadAll();
		}
		else {
			wxString line(this->content + this->pos, fp);
			this->pos += (line.length() + this->newline.length());
			return this->EnsureEndian(line);
		}
	}
}

wchar_t CConstStringTextReadonlyStream::ReadChar()
{
	wchar_t ch = this->PeekChar();
	if (ch != (signed)WEOF) {
		this->pos++;
	}
	return ch;
}

int CConstStringTextReadonlyStream::ReadByte()
{
	int ch = this->PeekByte();
	if (ch != EOF) {
		this->pos++;
	}
	return ch;
}

wchar_t CConstStringTextReadonlyStream::PeekChar()
{
	if (this->pos < (off64_t)this->length) {
		return this->EnsureEndian(this->content[(size_t)this->pos]);
	}
	return WEOF;
}

int CConstStringTextReadonlyStream::PeekByte()
{
	return this->IsEOF() ? EOF : this->PeekChar();
}

bool CConstStringTextReadonlyStream::IsValid()
{
	return true;
}

bool CConstStringTextReadonlyStream::IsEOF()
{
	return this->pos == (signed)this->length;
}

off64_t CConstStringTextReadonlyStream::GetPosition()
{
	return this->pos;
}

int CConstStringTextReadonlyStream::SetPosition(off64_t offset, int origin)
{
	int ret = -1;
	switch (origin) {
	case SEEK_SET:
		if (offset < (off64_t)this->length) {
			this->pos = offset;
			ret = 0;
		}
		break;
	case SEEK_CUR:
		if (this->pos + offset < (off64_t)this->length) {
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
