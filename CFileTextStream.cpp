#include "CFileTextStream.h"
#include "CMbcsFileTextStream.h"
#include "CUTF8FileTextStream.h"
#include "CUTF16FileTextStream.h"

//file checking logic:
//windows:utf16->utf8(bom,all_ascii)->mbcs(local)
CFileTextStream * CFileTextStream::OpenForRead(const wxString & path, bool check_bom, bool binary, const wxString & newline)
{
	CFileTextStream* result = 0;
	bool has_bom = false;
	wxString mode(L"r");
	if (binary) {
		mode += L'b';
	}
	CUTF16FileTextStream* cufts = new CUTF16FileTextStream(newline);
	if (cufts->Open(path, mode, true)) {
		has_bom = cufts->GetFileBOM() != 0;
	}
	if (has_bom) 
	{
		result = cufts;
	}
	else
	{
		delete cufts;
	}
	if(result == 0)
	{
#ifdef _WINDOWS
		bool all_ascii = false;
		bool is_utf8 = CUTF8FileTextStream::IsUTF8File(path, &has_bom, &all_ascii);

		bool use_utf8 = is_utf8 &&(has_bom || !all_ascii);
        //only windows requires all_ascii,
        //because linux and macosx are all utf-8 systems by default
		if (use_utf8) 
		{
			CUTF8FileTextStream * cu8ts = new CUTF8FileTextStream(newline);
			if (cu8ts->Open(path, mode, true)) 
			{
				result = cu8ts;
			}
			else {
				delete cu8ts;
			}
		}
		else 
		{
			CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
			if (cmfts->Open(path, mode))
			{
				result = cmfts;
			}
			else 
			{
				delete cmfts;
			}
		}
#else
			CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
			if (cmfts->Open(path, mode,true))
			{
                has_bom = cmfts->GetFileBOM() != 0;
                        
				result = cmfts;
			}
			else 
			{
				delete cmfts;
			}
#endif
	}
	if (result != 0 && has_bom) {
		result->SkipBOM();
	}
	return result;
}

CFileTextStream * CFileTextStream::OpenForWrite(const wxString & path, FileTextStreamType ftt, bool binary, const wxString& newline)
{
	CFileTextStream *ts = 0;
	wxString mode(L"w");
	if (binary) {
		mode += L'b';
	}
	if (ftt == FileTextStreamType::UTF16) {
		CUTF16FileTextStream* cufts = new CUTF16FileTextStream(newline);
		if (cufts->Open(path, mode, false)) {
			ts = cufts;
		}
		else {
			delete cufts;
		}
	}
	else if (ftt == FileTextStreamType::UTF8)
	{
		CUTF8FileTextStream * cu8ts = new CUTF8FileTextStream(newline);
		if (cu8ts->Open(path, mode, false)) {
			ts = cu8ts;
		}
		else {
			delete cu8ts;
		}
	}
	else if(ftt == FileTextStreamType::MBCS)
	{
		CMbcsFileTextStream* cmfts = new CMbcsFileTextStream(newline);
		if (cmfts->Open(path, mode)) {
			ts = cmfts;
		}
		else {
			delete cmfts;
		}
	}
	if (ts != 0) {
		ts->WriteBOM();
	}
	return ts;
}

CFileTextStream * CFileTextStream::CreateForType(FileTextStreamType type, const wxString & newline)
{
	switch (type) {
	case FileTextStreamType::MBCS:
		return new CMbcsFileTextStream(newline);
	case FileTextStreamType::UTF16:
		return new CUTF16FileTextStream(newline);
	case FileTextStreamType::UTF8:
		return new CUTF8FileTextStream(newline);
	default:
		return new CMbcsFileTextStream(newline);
	}
}
CFileTextStream * CFileTextStream::CreateForType(bool unicode, const wxString & newline)
{
	return CreateForType((unicode ? FileTextStreamType::UTF16 : FileTextStreamType::MBCS),newline);
}
CFileTextStream* CFileTextStream::CreateWrapper(FILE* file, FileTextStreamType type, bool close_on_exit,const wxString& newline)
{
	switch (type) {
	case FileTextStreamType::MBCS:
		return new CMbcsFileTextStream(file, close_on_exit,newline);
	case FileTextStreamType::UTF16:
		return new CUTF16FileTextStream(file, close_on_exit, newline);
	case FileTextStreamType::UTF8:
		return new CUTF8FileTextStream(file, close_on_exit,newline);
	default:
		return new CMbcsFileTextStream(file, close_on_exit,newline);
	}
}
CFileTextStream * CFileTextStream::CreateWrapper(FILE * file, bool unicode, bool close_on_exit, const wxString & newline)
{
	return CreateWrapper(file,(unicode ? FileTextStreamType::UTF16 : FileTextStreamType::MBCS),close_on_exit,newline);
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
bool CFileTextStream::ForWriting()
{
    return this->for_writing;
}
bool CFileTextStream::ForReading()
{
    return this->for_reading;
}
void CFileTextStream::Flush()
{
	if (this->IsValid() && this->ForWriting()) {
#ifdef _WINDOWS
        //NOTICE: fflush corrupts the stack on Ubuntu, for unsure reason,
        //so we just don't use it.
		fflush(this->file);
#endif
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

wchar_t CFileTextStream::GetFileBOM()
{
	return L'\0';
}

CFileTextStream::operator FILE*()
{
	return this->GetFile();
}

wchar_t CFileTextStream::WriteBOM()
{
	return L'\0';
}

wchar_t CFileTextStream::SkipBOM()
{
	return L'\0';
}

off64_t CFileTextStream::GetPosition()
{
	off64_t p = 0LL;
	if (this->IsValid()) {
#ifdef _WINDOWS
		p = _ftelli64(this->file);
#else
		p = ftello(this->file);
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
        ret = fseeko(this->file, offset, origin);
#endif

	}
	return ret;
}
