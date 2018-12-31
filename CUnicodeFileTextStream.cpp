#include "CUnicodeFileTextStream.h"



CUnicodeFileTextStream::CUnicodeFileTextStream(const wxString& newline)
	: CFileTextStream(newline)
	, file_bom()
{
}
CUnicodeFileTextStream::CUnicodeFileTextStream(FILE* file, bool close_on_exit, const wxString& newline)
	: CFileTextStream(file, close_on_exit, newline)
	, file_bom()
{
}


CUnicodeFileTextStream::~CUnicodeFileTextStream()
{
	this->Flush();
	this->Close();
}

bool CUnicodeFileTextStream::Open(const wxString & path, const wxString & mode, bool check_bom)
{
	wxString md = mode;
#ifdef _WINDOWS
	md += L",ccs=UNICODE";
#else
	//TODO: how to set unicode file in unix?
#endif
	bool done = (this->IsValid()) ? false :
		(this->file = 
#ifdef _WINDOWS
        _wfopen(path, md)
#else
		fopen((const char*)path, (const char*)mode)
#endif
        ) != 0;
	if (done) {
		this->file_bol = 0;
		if (md.Contains("w") || md.Contains("w+")) {

			this->file_bol = this->mem_bol; //file_bol defaults to mem_bol
			this->file_bom = IsLittleEndian() ? UTF16LE_BOM : UTF16BE_BOM;
		}
		//file_bol is determined by read if bom found
		if (check_bom && (md.Contains("r") || md.Contains("a"))) {
			off64_t sp = this->GetPosition();
			this->SetPosition(0LL, SEEK_SET);

			wchar_t first = this->ReadChar();

			switch (first) {
			case UTF16BE_BOM:
				this->file_bol = CTS_BIG_ENDIAN;
				this->file_bom = first;
				break;
			case UTF16LE_BOM:
				this->file_bol = CTS_LITTLE_ENDIAN;
				this->file_bom = first;
				break;
			default:
				this->file_bol = this->mem_bol;
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
		//ch = this->EnsureEndian(ch);
	}
	return ch;
}

int CUnicodeFileTextStream::ReadByte()
{
	wchar_t ch = this->ReadChar();
	return ch == (signed)WEOF ? EOF : ch;
}

wchar_t CUnicodeFileTextStream::PeekChar()
{
	wchar_t ch = WEOF;
	if (this->IsValid()) {
		ch = getwc(this->file);
		ungetwc(ch, this->file);
	}
	return ch;
}

int CUnicodeFileTextStream::PeekByte()
{
	wchar_t ch = this->PeekChar();
	return ch==(signed)WEOF ? EOF : ch;
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

bool CUnicodeFileTextStream::WriteChar(wchar_t ch)
{
	wchar_t ret = WEOF;
	if (this->IsValid()) {
		ret = putwc(ch, this->file);
	}
	return ret != (signed)WEOF;
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

