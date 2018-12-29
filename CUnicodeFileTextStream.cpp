#include "CUnicodeFileTextStream.h"



CUnicodeFileTextStream::CUnicodeFileTextStream(const wxString& newline)
	: CFileTextStream(newline)
	, file_bom(0)
{
}
CUnicodeFileTextStream::CUnicodeFileTextStream(FILE* file, bool close_on_exit, const wxString& newline)
	: CFileTextStream(file, close_on_exit, newline)
	, file_bom(0)
{
}


CUnicodeFileTextStream::~CUnicodeFileTextStream()
{
	this->Flush();
	this->Close();
}

bool CUnicodeFileTextStream::Open(const wxString & path, const wxString & mode, bool check_bom)
{
	bool done = (this->IsValid()) ? false :
		(this->file = _wfopen(path, mode)) != 0;
	if (done) {
		this->file_bol = 0;
		wxString m = mode.Lower();
		size_t mp = m.find(L"ccs=");
		if (mp != wxString::npos) {
			m = m.Truncate(mp); //remove "ccs=..."
		}
		if (m.Contains("w") || m.Contains("w+")) {

			this->file_bol = this->mem_bol; //file_bol defaults to mem_bol
		}
		//file_bol is determined by read if bom found
		if (check_bom && (m.Contains("r") || m.Contains("a"))) {
			off64_t sp = this->GetPosition();
			this->SetPosition(0LL, SEEK_SET);
			wchar_t p = this->PeekChar();
			switch (p) {
			case UTF16BE_BOM:
				this->file_bol = BIG_ENDIAN;
				this->file_bom = p;
				break;
			case UTF16LE_BOM:
				this->file_bol = LITTLE_ENDIAN;
				this->file_bom = p;
				break;
			default:
				this->file_bol = this->mem_bol;
				this->file_bom = 0;
				break;
			}

			this->SetPosition(sp, SEEK_SET);
		}
	}
	return done;
}

wchar_t CUnicodeFileTextStream::ReadChar()
{
	wchar_t ch = WEOF;
	if (this->IsValid()) {
		ch = getwc(this->file);
		ch = this->EnsureEndian(ch);
	}
	return ch;
}

int CUnicodeFileTextStream::ReadByte()
{
	return this->IsEOF() ? EOF : this->ReadChar();
}

wchar_t CUnicodeFileTextStream::PeekChar()
{
	wchar_t ch = WEOF;
	if (this->IsValid()) {
		ch = getwc(this->file);
		ungetwc(ch, this->file);
		ch = this->EnsureEndian(ch);
	}
	return ch;
}

int CUnicodeFileTextStream::PeekByte()
{
	return this->IsEOF() ? EOF : this->PeekChar();
}

wchar_t CUnicodeFileTextStream::SkipBOM()
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

bool CUnicodeFileTextStream::WriteBOM()
{
	return this->Write(this->GetMachineBOM());
}

bool CUnicodeFileTextStream::WriteChar(wchar_t ch)
{
	wchar_t ret = WEOF;
	if (this->IsValid()) {
		ret = putwc(this->EnsureEndian(ch), this->file);
	}
	return ret != WEOF;
}

bool CUnicodeFileTextStream::WriteByte(char ch)
{
	return this->WriteChar(ch);
}

wchar_t CUnicodeFileTextStream::GetFileBOM()
{
	return this->file_bom;
}

FileTextStreamType CUnicodeFileTextStream::GetStreamType()
{
	return FileTextStreamType::Unicode;
}

