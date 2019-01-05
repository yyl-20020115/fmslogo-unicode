#ifndef __CUTF16FILETEXTSTREAM_H__
#define __CUTF16FILETEXTSTREAM_H__

#include "CFileTextStream.h"

class CUTF16FileTextStream :
	public CFileTextStream
{

public:
	CUTF16FileTextStream(const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	CUTF16FileTextStream(FILE* file, bool close_on_exit, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CUTF16FileTextStream();
public:

	virtual bool Open(const wxString& path, const wxString& mode, bool check_bom = true);

public:

	virtual wchar_t ReadChar();
	virtual wchar_t PeekChar();
	virtual int ReadByte();
	virtual int PeekByte();


	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);

	virtual wchar_t WriteBOM();
	virtual wchar_t SkipBOM();
	virtual wchar_t GetFileBOM();

	virtual FileTextStreamType GetStreamType();

protected:
	wchar_t file_bom;
};

#endif
