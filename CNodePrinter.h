#ifndef __CNODEPRINTER__
#define __CNODEPRINTER__
#include<wx/string.h>
#include"logocore.h"


class CNodePrinter
{
public:
	CNodePrinter();
	~CNodePrinter();
public:
	virtual wxString& Print(NODE* n);

	virtual wxString& GetContent() { return this->content; }

	virtual bool& GetBackslashSetting() { return this->bs; }

protected:

	virtual void PrintChar(wchar_t ch);
	virtual void PrintSpace();

	virtual void NdPrintf(const wchar_t* fmt, ...);

	virtual void NewLine();

	virtual void PrintList(const NODE *ndlist);

	virtual void PrintNode(const NODE * nd);

protected:
	wxString content;

	bool bs;

};
#endif

