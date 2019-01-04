#ifndef __CUTF8FILETEXTSTREAM__
#define __CUTF8FILETEXTSTREAM__
#include "CFileTextStream.h"

class CUTF8FileTextStream :
	public CFileTextStream
{
public:
	static off64_t WriteAll(const wxString& path, CTextStream* source, bool append = false);
	static off64_t ReadAll(const wxString& path, CTextStream* dest);

public:
	CUTF8FileTextStream(const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	CUTF8FileTextStream(FILE* file, bool close_on_exit, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	virtual ~CUTF8FileTextStream();

	virtual void Close();
public:

	virtual bool Open(const wxString& path, const wxString& mode);

public:

	virtual wchar_t ReadChar();
	virtual wchar_t PeekChar();
	virtual int ReadByte();
	virtual int PeekByte();

	virtual bool WriteChar(wchar_t ch);
	virtual bool WriteByte(char ch);
	virtual FileTextStreamType GetStreamType();

	virtual bool& EnableUCS4() { return this->ucs4; }
	virtual off64_t GetBadFilePostion() { return this->badfileposition; }

protected:

	virtual size_t CharToBytes(wchar_t ch, char* buffer, size_t bufferlength);
	virtual size_t CharToBytes(unsigned short ch, char* buffer, size_t bufferlength);
	virtual wchar_t ComposeChar();
	virtual void ClearBuffers();

	wchar_t wbuffer;
	bool wbufferfull;
	char cbuffer[8];
	size_t cbufferlength;
	off64_t badfileposition;
	bool ucs4;

};

#endif


