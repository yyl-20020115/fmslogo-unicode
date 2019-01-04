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
	//ccs is determined by first operation in linux,which is actually getwc or putwc.
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
        this->for_reading = md.Contains(L"r");
        this->for_writing = md.Contains(L"w") || md.Contains(L"a");
		this->file_bol = 0;
		if (md.Contains(L"w") || md.Contains(L"w+")) {
			this->file_bol = this->mem_bol; //file_bol defaults to mem_bol
			this->file_bom = IsLittleEndian() ? UTF16LE_BOM : UTF16BE_BOM;
		}

		//file_bol is determined by read if bom found
		if (check_bom && (md.Contains(L"r") || md.Contains(L"a"))) {
			wchar_t first = this->PeekChar();

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
		}
	}
	return done;
}

wchar_t CUnicodeFileTextStream::ReadChar()
{
	wchar_t ch = WEOF;
	if (this->IsValid()) {
#ifdef _WINDOWS
		ch = getwc(this->file);
#else
        int c0 = getc(this->file);
        int c1 = getc(this->file);
        if(c0!=EOF && c1!=EOF){
            if(this->file_bol== CTS_BIG_ENDIAN)
            {
                ch = (c0<<8)|c1;
            }
            else //little endian
            {
                ch = (c1<<8)|c0;
            }
        }
#endif
	}
	return ch;
}

int CUnicodeFileTextStream::ReadByte()
{
#ifdef _WINDOWS
	wchar_t ch = this->ReadChar();
	return ch == (signed)WEOF ? EOF : ch;
#else
    return this->IsValid()? getc(this->file) : EOF;
#endif
}

wchar_t CUnicodeFileTextStream::PeekChar()
{
	wchar_t ch = WEOF;
	if (this->IsValid()) {
        off64_t sp= this->GetPosition();
        ch = this->ReadChar();
	    this->SetPosition(sp, SEEK_SET);
	}
	return ch;
}

int CUnicodeFileTextStream::PeekByte()
{
#ifdef _WINDOWS
	wchar_t ch = this->PeekChar();
	return ch==(signed)WEOF ? EOF : ch;
#else
    int c = EOF;
    if(this->IsValid())
    {
        c = getc(this->file);
        ungetc(c,this->file);
    }
    return c;
#endif
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

wchar_t CUnicodeFileTextStream::WriteBOM()
{
    wchar_t bom = this->file_bom;

	this->WriteChar(bom);
    
	return this->file_bom;
}

bool CUnicodeFileTextStream::WriteChar(wchar_t ch)
{
	wchar_t ret = WEOF;
	if (this->IsValid()) {
#ifdef _WINDOWS
        ret = putwc(ch, this->file);
#else
        int c0 = 0;
        int c1 = 0;
        if(this->file_bol== CTS_BIG_ENDIAN)
        {
            c0 = (ch&0xff00)>>8;
            c1 = (ch&0xff);
        }
        else //little endian
        {
            c0 = (ch&0xff);
            c1 = (ch&0xff00)>>8;
        }
        return (putc(c0,this->file)!=EOF)
            && (putc(c1,this->file)!=EOF);
#endif
	}
	return ret != (signed)WEOF;
}

bool CUnicodeFileTextStream::WriteByte(char ch)
{
#ifdef _WINDOWS
    if(this->IsValid()){
        return this->WriteChar(ch);
    }
#else
    if(this->IsValid()){
        return putc(ch,this->file)!=EOF;
    }

#endif
    return false;
}

wchar_t CUnicodeFileTextStream::GetFileBOM()
{
	return this->file_bom;
}

FileTextStreamType CUnicodeFileTextStream::GetStreamType()
{
	return FileTextStreamType::Unicode;
}

