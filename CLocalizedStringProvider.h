#ifndef __CLOCALIZEDSTRINGPROVIDER_H__
#define __CLOCALIZEDSTRINGPROVIDER_H__

#include "CTextStream.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <wx/string.h>

using namespace std;
class CLocalizedStringProvider
{
public:
	static wxString DefineString;
	static wxString EmptyString;
	static wxString NameStartString;
	static wxString StringStartString;
	static wxString StringEndString;
public:
	CLocalizedStringProvider();
	~CLocalizedStringProvider();

public:
	size_t Load(CTextStream* stream);
	void Clear();
	const wxString& Find(const wxString& key);

	void Assign(const wxString& key, const wxString& value);

protected:
	bool  SkipWhitespaces(CTextStream * stream, wxString& line, size_t& pos);
	wxString ReadName(CTextStream * stream, wxString& line, size_t& pos);
	wxString ReadString(CTextStream * stream, wxString& line, size_t& pos);
	void ReadParts(CTextStream * stream, wxString& line, size_t& pos, std::vector<wxString>& parts);
	bool IsWhiteSpace(wchar_t ch);

protected:
	std::unordered_map<wxString,wxString> table;
};
#endif

