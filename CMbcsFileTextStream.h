#pragma once
#include "CFileTextStream.h"
class CMbcsFileTextStream :
	public CFileTextStream
{
public:
	static off64_t WriteAll(const wxString& path, CTextStream* source, bool append = false);
	static off64_t ReadAll(const wxString& path, CTextStream* dest);

public:
	CMbcsFileTextStream(const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	CMbcsFileTextStream(FILE* file, bool close_on_exit, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CMbcsFileTextStream();

	virtual void Close();
public:

	virtual bool Open(const wxString& path, const wxString& mode, bool check_utf8_bom = false);

public:

	virtual wchar_t ReadChar();
	virtual wchar_t PeekChar();
	virtual int ReadByte();
	virtual int PeekByte();

	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);
	virtual FileTextStreamType GetStreamType();
	virtual bool IsEOF();
    
    virtual wchar_t WriteBOM();
	virtual wchar_t SkipBOM();
	virtual wchar_t GetFileBOM();
	virtual void Reset();

protected:
	
	virtual int CharToBytes(wchar_t ch, char* buffer);
	virtual wchar_t ComposeChar();
	virtual void ClearCBuffer();

	char cbuffer[MB_LEN_MAX+1];
	size_t cbufferlength;
    wchar_t utf8_bom;
};

