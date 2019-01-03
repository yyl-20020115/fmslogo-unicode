#include "CFileTextStream.h"
#include "CUnicodeFileTextStream.h"
#include "CMbcsFileTextStream.h"

CFileTextStream * CFileTextStream::OpenForRead(const wxString & path, bool check_bom, bool binary, const wxString & newline)
{
	CFileTextStream* ts = 0;
	bool has_bom = false;
	wxString mode(L"r");
	if (binary) {
		mode += L'b';
	}
	CUnicodeFileTextStream* cufts = new CUnicodeFileTextStream(newline);
	if (cufts->Open(path, mode, true)) {
		has_bom = cufts->GetFileBOM() != 0;
	}
	if (has_bom) {
		ts = cufts;
	}
	else {
		delete cufts;
		CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
		if (cmfts->Open(path, mode)) {
			ts = cmfts;
		}
		else {
			delete cmfts;
		}
	}
	return ts;
}

CFileTextStream * CFileTextStream::OpenForWrite(const wxString & path, bool use_unicode, bool binary, const wxString& newline)
{
	CFileTextStream *ts = 0;
	wxString mode(L"w");
	if (binary) {
		mode += L'b';
	}
	if (use_unicode) {
		CUnicodeFileTextStream* cufts = new CUnicodeFileTextStream(newline);
		if (cufts->Open(path, mode, false)) {
			ts = cufts;
		}
		else {
			delete cufts;
		}
	}
	else {
		CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
		if (cmfts->Open(path, mode)) {
			ts = cmfts;
		}
		else {
			delete cmfts;
		}
	}
	return ts;
}

CFileTextStream * CFileTextStream::CreateForType(FileTextStreamType type, const wxString & newline)
{
	switch (type) {
	case FileTextStreamType::Mbcs:
		return new CMbcsFileTextStream(newline);
	case FileTextStreamType::Unicode:
		return new CUnicodeFileTextStream(newline);
	case FileTextStreamType::Utf8:
		return 0; //TODO:
	default:
		return new CMbcsFileTextStream(newline);
	}
}
CFileTextStream * CFileTextStream::CreateForType(bool unicode, const wxString & newline)
{
	return CreateForType((unicode ? FileTextStreamType::Unicode : FileTextStreamType::Mbcs),newline);
}
CFileTextStream* CFileTextStream::CreateWrapper(FILE* file, FileTextStreamType type, bool close_on_exit,const wxString& newline)
{
	switch (type) {
	case FileTextStreamType::Mbcs:
		return new CMbcsFileTextStream(file, close_on_exit,newline);
	case FileTextStreamType::Unicode:
		return new CUnicodeFileTextStream(file, close_on_exit, newline);
	case FileTextStreamType::Utf8:
		return 0; //TODO:
	default:
		return new CMbcsFileTextStream(file, close_on_exit,newline);
	}
}
CFileTextStream * CFileTextStream::CreateWrapper(FILE * file, bool unicode, bool close_on_exit, const wxString & newline)
{
	return CreateWrapper(file,(unicode ? FileTextStreamType::Unicode : FileTextStreamType::Mbcs),close_on_exit,newline);
}
CFileTextStream* CFileTextStream::CreateStdInWrapper(FileTextStreamType type, const wxString& newline)
{
	return CreateWrapper(stdin, type, false, newline);
}
CFileTextStream* CFileTextStream::CreateStdOutWrapper(FileTextStreamType type, const wxString& newline)
{
	return CreateWrapper(stdout, type, false, newline);
}
CFileTextStream* CFileTextStream::CreateStdErrWrapper(FileTextStreamType type, const wxString& newline) 
{
	return CreateWrapper(stderr, type, false, newline);
}

CFileTextStream::CFileTextStream(const wxString& newline)
	:CTextStream(newline)
    ,file(0)
	,close_on_exit(true)
{
}
CFileTextStream::CFileTextStream(FILE* file, bool close_on_exit, const wxString& newline)
	: CTextStream(newline)
    , file(file)
	, close_on_exit(close_on_exit)
{
}


CFileTextStream::~CFileTextStream()
{
	this->Flush();
	this->Close();
}

bool CFileTextStream::IsValid()
{
	return this->file != 0;
}

bool CFileTextStream::IsEOF()
{
	if (this->IsValid()) {
		return feof(this->file);
	}
	return true;
}

void CFileTextStream::Flush()
{
	if (this->IsValid()) {
		fflush(this->file);
	}
}

void CFileTextStream::Close()
{
	if (this->IsValid()) {
		fclose(this->file);
		this->file = 0;
	}
}

FileTextStreamType CFileTextStream::GetStreamType()
{
	return FileTextStreamType::DONTKNOW;
}

bool& CFileTextStream::CloseOnExit() {
	return this->close_on_exit;
}

FILE* CFileTextStream::GetFile()
{
	return this->file;
}

void CFileTextStream::SetFile(FILE * file)
{
	this->file = file;
}

CFileTextStream::operator FILE*()
{
	return this->GetFile();
}

off64_t CFileTextStream::GetPosition()
{
	off64_t p = 0LL;
	if (this->IsValid()) {
#ifdef _WINDOWS
		p = _ftelli64(this->file);
#else
		//TODO: unix
#endif
	}

	return p;
}

int CFileTextStream::SetPosition(off64_t offset, int origin)
{
	int ret = -1;

	if (this->IsValid()) {
#ifdef _WINDOWS
		ret = _fseeki64(this->file, offset, origin);
#else
		//TODO: unix
#endif

	}
	return ret;
}
