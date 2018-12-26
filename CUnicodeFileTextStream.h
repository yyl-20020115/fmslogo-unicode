#ifndef __CUNICODEFILETEXTSTREAM_H__
#define __CUNICODEFILETEXTSTREAM_H__

#include "CFileTextStream.h"

class CUnicodeFileTextStream :
	public CFileTextStream
{

public:
	CUnicodeFileTextStream(const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	CUnicodeFileTextStream(FILE* file, bool close_on_exit, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CUnicodeFileTextStream();
public:

	virtual bool Open(const wxString& path, const wxString& mode, bool check_bom = true);

public:

	virtual wchar_t ReadChar();
	virtual wchar_t PeekChar();
	virtual int ReadByte();
	virtual int PeekByte();

	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);
	virtual bool WriteBOM();

	virtual wchar_t SkipBOM();
	virtual wchar_t GetFileBOM();

	virtual FileTextStreamType GetStreamType();

protected:
	wchar_t file_bom;
};

#endif
