#ifndef __CTEXTSTREAM_H__
#define __CTEXTSTREAM_H__

#include <wx/string.h>
#ifdef _WINDOWS
typedef long long off64_t;
#endif

#ifndef TEXTSTREAM_DEFUALT_NEWLINE
#define TEXTSTREAM_DEFUALT_NEWLINE L"\r\n"
#endif

#ifndef UTF16LE_BOM
#define UTF16LE_BOM 0xfeff
#endif

#ifndef UTF16BE_BOM
#define UTF16BE_BOM 0xfffe
#endif

class CTextStream
{
public:
	const int LITTLE_ENDIAN = -1;
	const int BIG_ENDIAN = 1;

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
	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);

	virtual bool IsValid();
	virtual bool IsEOF();
	virtual off64_t GetPosition();
	virtual int SetPosition(off64_t offset,int origin);
	virtual void Flush();

	virtual void Close();

	virtual wxString& NewLine();
protected:
	virtual bool IsLittleEndian();
	virtual wchar_t EnsureEndian(wchar_t ch);
	virtual wxString& EnsureEndian(wxString& text);
	virtual unsigned short SwapByteOrder(unsigned short s);
	virtual unsigned int SwapByteOrder(unsigned int i);
	virtual wchar_t GetMachineBOM();
protected:
	int file_bol;
	int mem_bol;
	wxString newline;

};

#endif

