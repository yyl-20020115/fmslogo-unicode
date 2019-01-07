#ifndef __CUTF8FILETEXTSTREAM__
#define __CUTF8FILETEXTSTREAM__
#include "CFileTextStream.h"

#ifndef UTF8_BOM
#define UTF8_BOM
#define UTF8_BOM_C0 0xEF
#define UTF8_BOM_C1 0xBB
#define UTF8_BOM_C2 0xBF
#endif

class CUTF8FileTextStream :
	public CFileTextStream
{
public:
	static off64_t WriteAll(const wxString& path, CTextStream* source, bool append = false,bool write_bom = true);
	static off64_t ReadAll(const wxString& path, CTextStream* dest, bool check_bom =true);
	static bool IsUTF8File(const wxString& path, bool* has_bom=0, bool *all_ascii=0);
public:
    CUTF8FileTextStream(const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	CUTF8FileTextStream(FILE* file, bool close_on_exit, const wxString& newline);
	virtual ~CUTF8FileTextStream();

	virtual void Close();
public:

	virtual bool Open(const wxString& path, const wxString& mode, bool check_bom);

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
	virtual wchar_t WriteBOM();
	virtual wchar_t SkipBOM();
	virtual wchar_t GetFileBOM();
	virtual bool IsEOF();
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
	wchar_t file_bom;

};

#endif


