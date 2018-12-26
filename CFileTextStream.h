#ifndef __CFILETEXTSTREAM_H__
#define __CFILETEXTSTREAM_H__
#include "CTextStream.h"

typedef enum _FileTextStreamType
{
	DONTKNOW,
	Mbcs,
	Unicode,
	Utf8
}FileTextStreamType;

class CFileTextStream :
	public CTextStream
{
public:

	static CFileTextStream* OpenForRead(const wxString& path, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE, bool check_bom = true);
	static CFileTextStream* OpenForWrite(const wxString& path, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE, bool use_unicode = false);
	static CFileTextStream* CreateForType(FileTextStreamType type, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateWrapper(FILE* file, FileTextStreamType type, bool close_on_exit = true, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateStdInWarpper(FileTextStreamType type, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateStdOutWrapper(FileTextStreamType type,const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateStdErrWrapper(FileTextStreamType type, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);

protected:
	CFileTextStream(const wxString& newline);
	CFileTextStream(FILE* file, bool close_on_exit,const wxString& newline);
public:
	virtual ~CFileTextStream();

public:

	virtual off64_t GetPosition();
	virtual int SetPosition(off64_t offset, int origin);

	virtual bool IsValid();
	virtual bool IsEOF();
	virtual void Flush();
	virtual void Close();

	virtual FileTextStreamType GetStreamType();

	virtual bool& CloseOnExit();
	virtual FILE*& GetFile();

	virtual operator FILE*();
protected:
	bool close_on_exit;
	FILE* file;
};

#endif


