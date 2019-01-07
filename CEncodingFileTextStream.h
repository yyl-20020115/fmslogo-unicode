#ifndef __CENCODINGFILETEXTSTREAM_H__
#define __CENCODINGFILETEXTSTREAM_H__

#include "CFileTextStream.h"
#include "CEncodingConverter.h"
class CEncodingFileTextStream :
	public CFileTextStream
{
public:
	static off64_t WriteAll(const wxString& encoding,const wxString& path, CTextStream* source, bool append = false);
	static off64_t ReadAll(const wxString& encoding, const wxString& path, CTextStream* dest);

public:
	CEncodingFileTextStream(const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	CEncodingFileTextStream(FILE* file, bool close_on_exit, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CEncodingFileTextStream();

	virtual void Close();
public:

	virtual bool Open(const wxString& path, const wxString& mode, const wxString& encoding);

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
    
    virtual const wxString& GetEncoding();
    
protected:

	virtual int CharToBytes(wchar_t ch, char* buffer, size_t bufferlength);
	virtual wchar_t ComposeChar();
	virtual void ClearCBuffer();

	char cbuffer[MB_LEN_MAX + 1];
	size_t cbufferlength;

	virtual CEncodingConverter*& FreeConverter();
	virtual CEncodingConverter*& ResetConverter();

protected:
	CEncodingConverter* converter;
};

#endif
