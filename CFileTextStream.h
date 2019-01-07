#ifndef __CFILETEXTSTREAM_H__
#define __CFILETEXTSTREAM_H__
#include "CTextStream.h"

typedef enum _FileTextStreamType
{
	DONTKNOW,
	MBCS,
	UTF16,
	UTF8,
	OTHER
}FileTextStreamType;

class CFileTextStream :
	public CTextStream
{
public:
    static wxString SystemEncoding;
public:

	static CFileTextStream* OpenForRead(const wxString& path, bool check_bom = true, bool binary = false, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* OpenForWrite(const wxString& path, FileTextStreamType ftt = FileTextStreamType::MBCS, bool binary = false, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateForType(FileTextStreamType type, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateForType(bool unicode, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateWrapper(FILE* file, FileTextStreamType type, bool close_on_exit = true, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateWrapper(FILE* file, bool unicode, bool close_on_exit = true, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
	static CFileTextStream* CreateStdInWrapper(FileTextStreamType type, const wxString& newline = TEXTSTREAM_DEFUALT_NEWLINE);
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

    virtual bool ForWriting();
    virtual bool ForReading();
	virtual bool& CloseOnExit();
	virtual FILE* GetFile();
	virtual void SetFile(FILE* file);
	virtual operator FILE*();
	virtual wchar_t WriteBOM();
	virtual wchar_t SkipBOM();
	virtual wchar_t GetFileBOM();
	virtual off64_t GetLastBadPosition();

protected:
	FILE* file;
	bool close_on_exit;
    bool for_writing;
    bool for_reading;
	off64_t badposition;
};

#endif


