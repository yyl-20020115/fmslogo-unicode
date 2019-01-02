#ifndef __CTEXTSTREAM_H__
#define __CTEXTSTREAM_H__

#include <wx/string.h>
#ifdef _WINDOWS
typedef long long off64_t;
#endif

#ifndef TEXTSTREAM_DEFUALT_NEWLINE
#define TEXTSTREAM_DEFUALT_NEWLINE L"\r\n"
#endif
//LE: ff fe
#ifndef UTF16LE_BOM
#define UTF16LE_BOM 0xfffe
#define UTF16LE_BOM_0 0xff
#define UTF16LE_BOM_1 0xfe
#endif
//BE: fe ff
#ifndef UTF16BE_BOM
#define UTF16BE_BOM 0xfeff
#define UTF16BE_BOM_0 0xfe
#define UTF16BE_BOM_1 0xff
#endif

#ifdef _WINDOWS
typedef wchar_t uchar;
#else
typedef unsigned short uchar;
#endif

class CTextStream
{
public:
    static const int CTS_LITTLE_ENDIAN = -1;
    static const int CTS_BIG_ENDIAN = 1;
	static bool IsLittleEndian();

public:
	CTextStream(const wxString& newline= TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CTextStream();
public:
	virtual size_t Read(wchar_t* buffer, size_t length);
	virtual wxString ReadAll();
	virtual wxString ReadLine();
	virtual wchar_t ReadChar();
	virtual int ReadByte();
	virtual wchar_t PeekChar();
	virtual int PeekByte();

	virtual size_t Write(wchar_t* buffer, size_t length);
	virtual size_t Write(const wxString& text) ;
	virtual size_t WriteLine(const wxString& text);
	virtual size_t Write(const wchar_t * FormatString, ...);
	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);

	virtual bool IsValid();
	virtual bool IsEOF();
	virtual off64_t GetPosition();
	virtual int SetPosition(off64_t offset,int origin);
	virtual off64_t GetLength();

	virtual void Flush();

	virtual void Close();

	virtual void Reset();

	virtual wxString& NewLine();

	virtual operator FILE*();

	virtual FILE* GetFile();
	virtual void SetFile(FILE* file);

protected:
	virtual wchar_t EnsureEndian(wchar_t ch);
	virtual wxString& EnsureEndian(wxString& text);
	virtual wchar_t SwapByteOrder(wchar_t c);
	virtual unsigned short SwapByteOrderShort(unsigned short s);
	virtual unsigned int SwapByteOrderLong(unsigned int i);
	virtual wchar_t GetMachineBOM();
protected:
	int mem_bol;
	int file_bol;
	wxString newline;

};

#endif

