#include "CUTF8FileTextStream.h"

off64_t CUTF8FileTextStream::WriteAll(const wxString& path, CTextStream * source, bool append,bool write_bom)
{
	off64_t c = 0;
	if (source != 0) {
		CUTF8FileTextStream cmfts;
		if (cmfts.Open(path, (append ? L"w+" : L"w"),false))
		{
			off64_t sp = cmfts.GetPosition();
			wchar_t ch = WEOF;
            if(write_bom)
            {
                cmfts.WriteByte((char)UTF8_BOM_C0);
                cmfts.WriteByte((char)UTF8_BOM_C1);
                cmfts.WriteByte((char)UTF8_BOM_C2);
            }
			while ((ch = source->ReadChar()) != (signed)WEOF)
			{
				cmfts.WriteChar(ch);
			}
			off64_t ep = cmfts.GetPosition();
			c = ep - sp;
		}
	}

	return c;
}
off64_t CUTF8FileTextStream::ReadAll(const wxString & path, CTextStream * dest, bool check_bom )
{
	size_t c = 0;
	if (dest != 0) {
		CUTF8FileTextStream cmfts;
		if (cmfts.Open(path, L"r",check_bom))
		{
			off64_t sp = cmfts.GetPosition();
			wchar_t ch = WEOF;
			while ((ch = cmfts.ReadChar()) != (signed)WEOF)
			{
				dest->WriteChar(ch);
			}
			off64_t ep = cmfts.GetPosition();
			c = ep - sp;
		}
	}
	return c;
}
bool CUTF8FileTextStream::IsUTF8File(const wxString & path, bool * has_bom,bool *all_ascii)
{
	bool uf = false;

	CUTF8FileTextStream cmfts;
	if (cmfts.Open(path, L"r", true))
	{
		if (cmfts.GetFileBOM() != 0) {
			uf = true;
			if (has_bom) {
				*has_bom = true;
			}
		}
		else {
			if (all_ascii != 0) {
				*all_ascii = true;
			}
			off64_t lf = cmfts.GetLength();
			wchar_t c = 0;
			while ((c=cmfts.ReadChar()) != (signed)WEOF)
			{
				if (all_ascii != 0) {
					if (c >= 0x80) {
						*all_ascii = false;
					}
				}
			}
			uf = (lf == cmfts.GetPosition() + 1);
			if (all_ascii != 0 && !uf ) {
				*all_ascii = false;
			}
		}
	}
	return uf;
}
CUTF8FileTextStream::CUTF8FileTextStream(const wxString& newline)
	: CFileTextStream(newline)
	, wbuffer(0)
	, wbufferfull(false)
	, cbuffer()
	, cbufferlength()
	, ucs4(false)
	, file_bom(0)
{
}
CUTF8FileTextStream::CUTF8FileTextStream(FILE* file, bool close_on_exit, const wxString& newline)
	: CFileTextStream(file, close_on_exit, newline)
	, wbuffer(0)
	, wbufferfull(false)
	, cbuffer()
	, cbufferlength()
	, ucs4(false)
	, file_bom(0)
{
}

CUTF8FileTextStream::~CUTF8FileTextStream()
{
}

void CUTF8FileTextStream::Close()
{
	this->ClearBuffers();
	CFileTextStream::Close();
}

bool CUTF8FileTextStream::Open(const wxString & path, const wxString & mode, bool check_bom)
{
	wxString md = mode;
	if (!md.Contains(L'b'))
	{
		md += L'b';//NOTICE: must have 'b'
	}
	bool done = (this->IsValid()) ? false :
		(this->file =
#ifdef _WINDOWS
			_wfopen(path, md)
#else
			fopen((const char*)path, (const char*)mode)
#endif
			) != 0;
    if (done)
    {
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

wchar_t CUTF8FileTextStream::ReadChar()
{
	return this->ComposeChar();
}

int CUTF8FileTextStream::ReadByte()
{
	int ch = EOF;
	if (this->IsValid()) {
		ch = getc(this->file);
	}
	return ch;
}

wchar_t CUTF8FileTextStream::PeekChar()
{
    wchar_t wc = this->wbuffer;
    bool wb = this->wbufferfull;
    
    char cbuffer[sizeof(this->cbuffer)] = {0};
    size_t cbl = this->cbufferlength;
    memcpy(cbuffer,this->cbuffer,sizeof(cbuffer));
    this->ClearBuffers();
    
    off64_t p = this->GetPosition();
    
    wchar_t ch = this->ReadChar();
	
    this->SetPosition(p,SEEK_SET);
    
    memcpy(this->cbuffer,cbuffer,sizeof(cbuffer));
    this->cbufferlength = cbl;
    this->wbufferfull = wb;
    this->wbuffer = wc;
	
    return ch == EOF ? WEOF : (wchar_t)ch;
}

int CUTF8FileTextStream::PeekByte()
{
	int ch = EOF;
	if (this->IsValid()) {
		ch = getc(this->file);
		ungetc(ch, this->file);
	}
	return ch;
}


bool CUTF8FileTextStream::WriteChar(wchar_t ch)
{
	char buffer[sizeof(this->cbuffer)] = { 0 };
	size_t c = this->CharToBytes(ch, buffer,sizeof(buffer));
	for (size_t i = 0; i < c; i++) {
		this->WriteByte(buffer[i]);
	}
	return c > 0;
}

bool CUTF8FileTextStream::WriteByte(char ch)
{
	char ret = EOF;
	if (this->IsValid()) {
		ret = putc(ch, this->file);
	}
	return ret != EOF;
}
FileTextStreamType CUTF8FileTextStream::GetStreamType()
{
	return FileTextStreamType::UTF8;
}

wchar_t CUTF8FileTextStream::WriteBOM()
{
	wchar_t bom = this->file_bom;

	this->WriteChar(bom);

	return this->file_bom;
}

wchar_t CUTF8FileTextStream::SkipBOM()
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

wchar_t CUTF8FileTextStream::GetFileBOM()
{
	return this->file_bom;
}

bool CUTF8FileTextStream::IsEOF()
{
	return CFileTextStream::IsEOF() 
		&& (this->cbufferlength == 0) 
		&& (this->ucs4 ? (!this->wbufferfull) : true);
}

void CUTF8FileTextStream::Reset()
{
	CTextStream::Reset();
	this->ClearBuffers();
}

size_t CUTF8FileTextStream::CharToBytes(wchar_t ch, char * buffer,size_t bufferlength)
{
	size_t n = 0;

	if (buffer != 0 && bufferlength >=sizeof(this->cbuffer)) {

		if (sizeof(wchar_t) == sizeof(unsigned short) || (ch>=0 && ch<=0xFFFF)) 
		{
			n = this->CharToBytes((unsigned short)ch, buffer, bufferlength);
		}
		else if (sizeof(wchar_t) == sizeof(unsigned int)) 
		{
			unsigned int ci = ch;
			if (this->ucs4) 
			{
				if (ci >= 0x10000 && ci <= 0x1FFFFF)
				{
					buffer[(n++)] = 0xF0 | (ci & 0x1C0000) >> 18;
					buffer[(n++)] = 0xC0 | (ci & 0x03F000) >> 12;
					buffer[(n++)] = 0xC0 | (ci & 0x000FC0) >> 6;
					buffer[(n++)] = 0xC0 | (ci & 0x00003F);
				}
				else if (ci >= 0x200000 && ci <= 0x3FFFFFF)
				{
					buffer[(n++)] = 0xF8 | (ci & 0x03000000) >> 24;
					buffer[(n++)] = 0xC0 | (ci & 0x00FC0000) >> 18;
					buffer[(n++)] = 0xC0 | (ci & 0x0003F000) >> 12;
					buffer[(n++)] = 0xC0 | (ci & 0x00000FC0) >> 6;
					buffer[(n++)] = 0xC0 | (ci & 0x0000003F);
				}
				else if (ci >= 0x4000000 && ci <= 0x7FFFFFFF)
				{
					buffer[(n++)] = 0xFC | (ci & 0x40000000) >> 30;
					buffer[(n++)] = 0xC0 | (ci & 0x3F000000) >> 24;
					buffer[(n++)] = 0xC0 | (ci & 0x00FC0000) >> 18;
					buffer[(n++)] = 0xC0 | (ci & 0x0003F000) >> 12;
					buffer[(n++)] = 0xC0 | (ci & 0x00000FC0) >> 6;
					buffer[(n++)] = 0xC0 | (ci & 0x0000003F);
				}
				else {
					//should not be here!
					//as we don't need negative number to represent unicode
					this->badposition = this->GetPosition();
				}
			}
			else 
			{
				int ci = ch;
				if ((ci >= 0x10000) && (ci <= 0x7FFFFFFF))
				{
					unsigned short low = (ci & 0xffff);
					unsigned short high = (ci & 0xffff0000) >> 16;

					n += this->CharToBytes(high, buffer, 4);
					n += this->CharToBytes(low, buffer + 4, 4);

				}
				else {
					this->badposition = this->GetPosition();
				}
			}
		}
	}
	
	return n;
}

size_t CUTF8FileTextStream::CharToBytes(unsigned short cs, char * buffer, size_t bufferlength)
{
	size_t n = 0;

	if (buffer != 0 && bufferlength >= sizeof(this->cbuffer)) 
	{
		if (cs>=0 && cs<=0x7F)
		{
			buffer[(n++)] = (cs & 0x7F);
		}
		else if (cs >= 0x80 && cs <= 0x7FF)
		{
			buffer[(n++)] = (0xC0 | (cs & 0x1F00) >> 8);
			buffer[(n++)] = (0x80 | (cs & 0x3F));
		}
		else if (cs >= 0x800 && cs <= 0xFFFF)
		{
			buffer[(n++)] = (0xE0 | (cs & 0x00F000) >> 12);
			buffer[(n++)] = (0x80 | (cs & 0x000FC0) >> 6);
			buffer[(n++)] = (0x80 | (cs & 0x00003F));
		}
	}
	return n;
}

wchar_t CUTF8FileTextStream::ComposeChar()
{
	bool badchar = false;
	wchar_t w = WEOF;

	if (this->IsValid())
	{
		if (this->wbufferfull) {
			w = wbuffer;
			this->wbufferfull = false;
			this->wbuffer = 0;
		}
		else {
			size_t count = 0;

			if (cbufferlength < sizeof(cbuffer)) {
				count = fread(cbuffer + cbufferlength, sizeof(char), sizeof(cbuffer) - cbufferlength, this->file);
				cbufferlength += count;
			}
			if (cbufferlength > 0)
			{
				int cx = 0;
				int c0 = cbuffer[0];
				int c1 = cbuffer[1];
				int c2 = cbuffer[2];
				int c3 = cbuffer[3];
				int c4 = cbuffer[4];
				int c5 = cbuffer[5];

				size_t n = 0;
				if ((c0 & 0x7f) == c0)
				{
					cx = c0;
					n = 1;
				}
				else if (((c0 & 0xE0) == 0xC0) && ((c1 & 0xC0) == 0x80))
				{
					cx = ((c0 & 0x1F) << 6) | (c1 & 0x3F);
					n = 2;
				}
				else if (((c0 & 0xF0) == 0xE0) && ((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80))
				{
					cx = ((c0 & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
					n = 3;
				}
				else if (((c0 & 0xF8) == 0xF0) && ((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80))
				{
					cx = ((c0 & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
					n = 4;
				}
				else if ( ((c0 & 0xFC) == 0xF8) && ((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80) && ((c4 & 0xC0) == 0x80))
				{
					if (this->ucs4) {
						cx = ((c0 & 0x03) << 24) | ((c1 & 0x3F) << 18) | ((c2 & 0x3F) << 12) | ((c3 & 0x3F) << 6) | (c4 & 0x3F);;
						n = 5;
					}
					else {
						badchar = true;
					}
				}
				else if (((c0 & 0xFE) == 0xFC) && ((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80) && ((c4 & 0xC0) == 0x80) && ((c5 & 0xC0) == 0x80))
				{
					if (this->ucs4) {
						cx = ((c0 & 0x01) << 30) | ((c1 & 0x3F) << 24) | ((c2 & 0x3F) << 18) | ((c3 & 0x3F) << 12) | ((c4 & 0x3F) << 6) | (c5 & 0x3F);
						n = 6;
					}
					else {
						badchar = true;
					}
				}
				else {
					badchar = true;
				}
				for (int i = 0; i < (int)sizeof(cbuffer) - 1; i++) {
					cbuffer[i] = (i + n) < sizeof(cbuffer) ? cbuffer[i + n] : 0;
				}

				if (!badchar)
				{
					switch (sizeof(wchar_t))
					{
						case sizeof(unsigned short) :
							if (n >= 1 && n <= 4)
							{
								w = (wchar_t)(cx & 0xffff);
							}
							else
							{
								w = (wchar_t)(cx & 0xffff);
								wbuffer = (wchar_t)((cx & 0xffff0000) >> 16);
								wbufferfull = true;
							}
							break;
						case sizeof(unsigned int) :
							w = (wchar_t)cx;
							break;
					}
				}
				else {
					this->badposition = this->GetPosition() - sizeof(cbuffer);
				}
				if (cbufferlength >= n) {
					cbufferlength -= n;
				}
				else {
					cbufferlength = 0;
				}
			}
		}
	}
	return w;
}

void CUTF8FileTextStream::ClearBuffers()
{
	this->wbuffer = 0;
	this->wbufferfull = false;
	this->cbufferlength = 0;
	memset(this->cbuffer, 0, sizeof(this->cbuffer));
}
