#ifndef __CSTRINGTEXTSTREAM_H__
#define __CSTRINGTEXTSTREAM_H__

#include "CTextStream.h"

class CStringTextStream :
	public CTextStream
{
public:
	CStringTextStream(const wxString& content = L"",const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CStringTextStream();

public:

	virtual size_t Read(wchar_t* buffer, size_t length);
	virtual wxString ReadAll();
	virtual wxString ReadLine();
	virtual wchar_t ReadChar();
	virtual int ReadByte();
	virtual wchar_t PeekChar();
	virtual int PeekByte();

	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);
	virtual bool IsValid();
	virtual bool IsEOF();
	virtual off64_t GetPosition();
	virtual int SetPosition(off64_t offset, int origin);

	virtual void Close();
public:
	virtual void Clear();
	virtual void Reset();
	wxString& Append(const wxString& text);
	virtual off64_t GetLength();
public:

	wxString& GetContent();

protected:
	wxString content;
	off64_t pos;
};
#endif

