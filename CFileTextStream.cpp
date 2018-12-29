#include "CFileTextStream.h"
#include "CUnicodeFileTextStream.h"
#include "CMbcsFileTextStream.h"

CFileTextStream * CFileTextStream::OpenForRead(const wxString & path, const wxString & newline, bool check_bom)
{
	CFileTextStream* ts = 0;
	bool has_bom = false;

	CUnicodeFileTextStream* cufts = new CUnicodeFileTextStream(newline);
	if (cufts->Open(path, L"r", true)) {
		has_bom = cufts->GetFileBOM() != 0;
	}
	if (has_bom) {
		ts = cufts;
	}
	else {
		delete cufts;
		CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
		if (cmfts->Open(path,L"r")) {
			ts = cmfts;
		}
		else {
			delete cmfts;
		}
	}
	return ts;
}

CFileTextStream * CFileTextStream::OpenForWrite(const wxString & path, const wxString& newline, bool use_unicode)
{
	CFileTextStream *ts = 0;
	if (use_unicode) {
		CUnicodeFileTextStream* cufts = new CUnicodeFileTextStream(newline);
		if (cufts->Open(path, "w", false)) {
			ts = cufts;
		}
		else {
			delete cufts;
		}
	}
	else {
		CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
		if (cmfts->Open(path, L"w")) {
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
CFileTextStream* CFileTextStream::CreateStdInWarpper(FileTextStreamType type, const wxString& newline)
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

FILE*& CFileTextStream::GetFile()
{
	return this->file;
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
