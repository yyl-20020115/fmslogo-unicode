#include "CEncodingFileTextStream.h"

off64_t CEncodingFileTextStream::WriteAll(const wxString& encoding, const wxString& path, CTextStream * source, bool append)
{
	off64_t c = 0;
	if (source != 0) {
		CEncodingFileTextStream cefts;
		if (cefts.Open(path, (append ? L"w+" : L"w"), encoding))
		{
			off64_t sp = cefts.GetPosition();
			wchar_t ch = WEOF;
			while ((ch = source->ReadChar()) != (signed)WEOF)
			{
				cefts.WriteChar(ch);
			}
			off64_t ep = cefts.GetPosition();
			c = ep - sp;
		}
	}

	return c;
}
off64_t CEncodingFileTextStream::ReadAll(const wxString& encoding, const wxString & path, CTextStream * dest)
{
	size_t c = 0;
	if (dest != 0) {
		CEncodingFileTextStream cefts;
		if (cefts.Open(path, L"r",encoding))
		{
			off64_t sp = cefts.GetPosition();
			wchar_t ch = WEOF;
			while ((ch = cefts.ReadChar()) != (signed)WEOF)
			{
				dest->WriteChar(ch);
			}
			off64_t ep = cefts.GetPosition();
			c = ep - sp;
		}
	}
	return c;
}
CEncodingFileTextStream::CEncodingFileTextStream(const wxString& newline)
	: CFileTextStream(newline)
	, cbuffer()
	, cbufferlength()
	, converter(0)
{
}
CEncodingFileTextStream::CEncodingFileTextStream(FILE* file, bool close_on_exit, const wxString& newline)
	: CFileTextStream(file, close_on_exit, newline)
	, cbuffer()
	, cbufferlength()
	, converter(0)
{
}

CEncodingFileTextStream::~CEncodingFileTextStream()
{
	this->FreeConverter();
}

void CEncodingFileTextStream::Close()
{
	this->ClearCBuffer();
	CFileTextStream::Close();
}

bool CEncodingFileTextStream::Open(const wxString & path, const wxString & mode, const wxString& encoding)
{
	bool done = (this->IsValid()) ? false :
		(this->file =
#ifdef _WINDOWS
			_wfopen(path, mode)
#else
			fopen((const char*)path, (const char*)mode)
#endif
			) != 0;
	if (done)
	{
		this->for_reading = mode.Contains(L"r");
		this->for_writing = mode.Contains(L"w") || mode.Contains(L"a");
		
		this->FreeConverter() = new CEncodingConverter(encoding);
	}
	return done;
}

wchar_t CEncodingFileTextStream::ReadChar()
{
	return this->ComposeChar();
}

int CEncodingFileTextStream::ReadByte()
{
	int ch = EOF;
	if (this->IsValid()) {
		ch = getc(this->file);
	}
	return ch;
}

wchar_t CEncodingFileTextStream::PeekChar()
{
	char cbuffer[sizeof(this->cbuffer)] = { 0 };
	size_t cbl = this->cbufferlength;
	memcpy(cbuffer, this->cbuffer, sizeof(cbuffer));
	this->ClearCBuffer();

	off64_t p = this->GetPosition();

	wchar_t ch = this->ReadChar();

	this->SetPosition(p, SEEK_SET);

	memcpy(this->cbuffer, cbuffer, sizeof(cbuffer));
	this->cbufferlength = cbl;

	return ch == EOF ? WEOF : (wchar_t)ch;
}

int CEncodingFileTextStream::PeekByte()
{
	int ch = EOF;
	if (this->IsValid()) {
		ch = getc(this->file);
		ungetc(ch, this->file);
	}
	return ch;
}


bool CEncodingFileTextStream::WriteChar(wchar_t ch)
{
	char buffer[MB_LEN_MAX + 1] = { 0 };
	int c = this->CharToBytes(ch, buffer,sizeof(buffer));
	for (int i = 0; i < c; i++) {
		this->WriteByte(buffer[i]);
	}
	return c > 0;
}

bool CEncodingFileTextStream::WriteByte(char ch)
{
	char ret = EOF;
	if (this->IsValid()) {
		ret = putc(ch, this->file);
	}
	return ret != EOF;
}
FileTextStreamType CEncodingFileTextStream::GetStreamType()
{
	return FileTextStreamType::OTHER;
}

bool CEncodingFileTextStream::IsEOF()
{
	return CFileTextStream::IsEOF() && this->cbufferlength == 0;
}
const wxString& CEncodingFileTextStream::GetEncoding()
{
    return this->converter!=0 ? this->converter->GetOtherEncoding():CEncodingConverter::FixedEncoding;
}

int CEncodingFileTextStream::CharToBytes(wchar_t ch, char * buffer, size_t bufferlength)
{
	int c = 0;
	if (this->converter != 0) {
        memset(buffer,0,bufferlength);
	
		wchar_t chbuffer[2] = { ch,0 };
		wchar_t* pch = chbuffer;
		char* pret = buffer;
		size_t pch_length = sizeof(chbuffer);
		size_t pret_length = bufferlength;
		size_t pret_backup = pret_length;
		size_t converted = this->converter->Convert(&pch, &pch_length, &pret, &pret_length);
		if (converted != CEncodingConverter::invalid_size) //this is good, just convert one wchar_t
		{
			return strlen(buffer);
		}
		else {
			c = 0; //should not happen
		}
	}
	return c;
}

wchar_t CEncodingFileTextStream::ComposeChar()
{
	wchar_t c = WEOF;
	if (this->IsValid() && this->converter!=0)
	{
		const size_t invalid_size = sizeof(size_t) == 8 ? (size_t)-1LL : (size_t)-1L;
		size_t count = 0;

		if (cbufferlength < MB_LEN_MAX) {
			count = fread(cbuffer + cbufferlength, sizeof(char), MB_LEN_MAX - cbufferlength, this->file);
			cbufferlength += count;
		}
		if (cbufferlength > 0)
		{
			char* pcb = this->cbuffer;
			wchar_t tbuffer[2] = { 0 };
			wchar_t* ptb = 0;
			size_t ptl = sizeof(tbuffer);
			size_t n = 1;
            size_t ret = 0;
			for (size_t pcl = 1; pcl < this->cbufferlength; pcl++) {
                size_t pcl_backup = pcl;
				pcb = this->cbuffer;				
				ptb = tbuffer;
				ptl = sizeof(tbuffer);
                tbuffer[0] = 0;
                tbuffer[1] = 0;
                ret = this->converter->Convert(&pcb, &pcl, &ptb, &ptl);
				if (ret != invalid_size) {
					n = pcl_backup - pcl;
					c = tbuffer[0];
					break;
				}
			}
			if(ret == invalid_size)
            {
                n = 1;
                c = (unsigned)cbuffer[0];
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

void CEncodingFileTextStream::ClearCBuffer()
{
	this->ResetConverter();
	this->cbufferlength = 0;
	memset(this->cbuffer, 0, sizeof(this->cbuffer));
}

CEncodingConverter*& CEncodingFileTextStream::FreeConverter()
{
	if (this->converter != 0) {
		delete this->converter;
		this->converter = 0;
	}
	return this->converter;
}

CEncodingConverter *& CEncodingFileTextStream::ResetConverter()
{
	if (this->converter != 0) {
		this->converter->Reset();
	}
	return this->converter;
}

void CEncodingFileTextStream::Reset()
{
	CTextStream::Reset();
	this->ClearCBuffer();
}



wchar_t CEncodingFileTextStream::WriteBOM()
{
	return 0;
}
wchar_t CEncodingFileTextStream::SkipBOM()
{
	return 0;
}
wchar_t CEncodingFileTextStream::GetFileBOM()
{
	return 0;
}
