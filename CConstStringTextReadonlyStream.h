#ifndef __CCONSTSTRINGTEXTREADONLYSTREAM_H__
#define __CCONSTSTRINGTEXTREADONLYSTREAM_H__

#include "CTextStream.h"
class CConstStringTextReadonlyStream :
	public CTextStream
{
public:
	CConstStringTextReadonlyStream(const wchar_t* content, size_t length, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CConstStringTextReadonlyStream();

public:

	virtual size_t Read(wchar_t* buffer, size_t length);
	virtual wxString ReadAll();
	virtual wxString ReadLine();
	virtual wchar_t ReadChar();
	virtual int ReadByte();
	virtual wchar_t PeekChar();
	virtual int PeekByte();

	virtual bool IsValid();
	virtual bool IsEOF();
	virtual off64_t GetPosition();
	virtual int SetPosition(off64_t offset, int origin);

protected:
	const wchar_t* content;
	size_t length;
	off64_t pos;
};

#endif


