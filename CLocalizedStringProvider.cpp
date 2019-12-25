#include "pch.h"
#include "CLocalizedStringProvider.h"
wxString CLocalizedStringProvider::DefineString(L"#define");
wxString CLocalizedStringProvider::EmptyString(L"");
wxString CLocalizedStringProvider::NameStartString(L"\uffff\uffff");
wxString CLocalizedStringProvider::StringStartString(L"L\"");
wxString CLocalizedStringProvider::StringEndString(L"\"");
CLocalizedStringProvider::CLocalizedStringProvider()
	:table()
{
}
CLocalizedStringProvider::~CLocalizedStringProvider()
{
	this->Clear();
}
size_t CLocalizedStringProvider::Load(CTextStream * stream)
{

	size_t define_count = 0;
	size_t full_count = 0;

	if (stream != 0) {
		std::map<wxString, std::vector<wxString>> content;
		wxString line;
		while (!stream->IsEOF())
		{
			line = stream->ReadLine().Trim();

			if (line.StartsWith(DefineString)) {

				define_count++;

				size_t pos = DefineString.length();

				this->SkipWhitespaces(stream, line, pos);

				wxString key = this->ReadName(stream, line, pos);

				std::vector<wxString> parts;

				this->ReadParts(stream, line, pos, parts); 

				content[key] = parts;
			}
		}

		std::vector<wxString> done_keys;

		bool any_progress = false;
		do
		{
			for (std::map<wxString, std::vector<wxString>>::iterator it = content.begin(); it != content.end(); it++) {
				std::vector<wxString>& parts = it->second;
				bool any_symbol = false;
				for (std::vector<wxString>::iterator pit = parts.begin(); pit != parts.end(); pit++) {
					if (pit->StartsWith(NameStartString)
						&& (content.find(pit->substr(NameStartString.length())) != content.end()))
					{
						any_symbol = true;
						break;
					}
				}
				if (any_symbol) {
					this->table[it->first] = NameStartString;
				}
				else //!any_Symbol
				{
					//this includes the situation that #define without strings
					full_count++;
					wxString full_line;
					wxString part;

					for (std::vector<wxString>::iterator pit = parts.begin(); pit != parts.end(); pit++) {
						if (pit->StartsWith(StringStartString) && pit->EndsWith(StringEndString)) {
							//remove L" and "
							full_line += pit->substr(StringStartString.length(), pit->length() - StringStartString.length() - StringEndString.length());
						}
						else { 
							//this is a direct string
							full_line += *pit;
						}
					}
					this->table[it->first] = full_line;
					done_keys.push_back(it->first);
				}
			}

			if (full_count == define_count) {
				break;
			}

			any_progress = false;

			for (std::vector<wxString>::iterator it = done_keys.begin(); it != done_keys.end(); it++) {
				content.erase(*it);
			}
			done_keys.clear();

			//try unsolved ones
			for (std::map<wxString, std::vector<wxString>>::iterator it = content.begin(); it != content.end(); it++) {
				const wxString& key = it->first;
				std::vector<wxString>& parts = it->second;

				for (std::vector<wxString>::iterator pit = parts.begin(); pit != parts.end(); pit++) {
					if (pit->StartsWith(NameStartString))
					{
						wxString tofind = *pit;

						std::unordered_map<wxString, wxString>::iterator fit
							= this->table.find(tofind.substr(NameStartString.length()));
						if (fit != this->table.end()) {
							any_progress = true;
							if (!fit->second.StartsWith(NameStartString)) {
								*pit = fit->second;
							}
							else {
								//any_progress = any_progress;
							}
						}
					}
				}
			}
		} while (any_progress);
	}
	if (full_count < define_count) {
#ifdef _DEBUG
		std::vector<wxString> unresovled;
		for (std::unordered_map<wxString, wxString>::iterator it = this->table.begin(); it != this->table.end(); it++) {
			if (it->second.Contains(NameStartString))
			{
				unresovled.push_back(it->first);
			}
		}
#endif
	}

	return define_count - full_count;
}

void CLocalizedStringProvider::Clear()
{
	this->table.clear();
}

const wxString& CLocalizedStringProvider::Find(const wxString & key)
{
	std::unordered_map<wxString,wxString>::iterator value = this->table.find(key);
	if (value == this->table.end()) {
		return EmptyString;
	}
	else {
		return (value->second);
	}
}

void CLocalizedStringProvider::Assign(const wxString & key, const wxString & value)
{
	this->table[key] = value;
}

bool CLocalizedStringProvider::SkipWhitespaces(CTextStream * stream,wxString & line, size_t & pos)
{
	if (stream != 0) {
		while (pos<line.length()) {
			wchar_t ch = line[pos];

			while (this->IsWhiteSpace(ch=line[pos]) && pos < line.length()) pos++;
			if (pos < line.length() - 1 && line[pos] == L'/' && line[pos + 1] == L'/') {
				//this is single line comment, skip this line
				pos = line.length();
				break;
			}
			if (pos < line.length() - 1 && line[pos] == L'/' && line[pos + 1] == L'*') {
				//this is multiple lines comment, skip all
				size_t ep = wxString::npos;
				do {
					line = stream->ReadLine();
					ep = line.find(L"*/");
				} while (ep == wxString::npos && !stream->IsEOF());
				if (ep != wxString::npos) {
					pos = ep;
				}
			}

			if (pos == line.length() && ch == L'\\') {
				line = stream->ReadLine();
				pos = 0;
			}
			else {
				break;
			}
		}
	}
	return pos < line.length();
}

wxString CLocalizedStringProvider::ReadName(CTextStream * stream, wxString & line, size_t & pos)
{
	wxString part;

	if (stream != 0) {
		wchar_t ch = 0;
		while (pos<line.length() && !IsWhiteSpace(ch = line[pos])) {
			part += ch;
			pos++;
		}
	}

	return part;
}

wxString CLocalizedStringProvider::ReadString(CTextStream * stream, wxString & line, size_t & pos)
{
	wxString str;
	if (stream != 0)
	{
		if (pos < line.length() - 1 && line[pos] == L'L' && line[pos + 1] == L'"')
		{
			str += line.substr(pos,2);
			pos += str.length();
			wchar_t ch = 0;
			while (pos < line.length()) {
				ch = line[pos];
				if (ch == L'\\') {
					pos++;
					if (pos == line.length()) {
						pos = 0;
						line = stream->ReadLine();
					}
					else {
						wchar_t n = line[pos];
						wchar_t t = n;
						switch (n) {
						case L'a':
							t = L'\a';
							break;
						case L'r':
							t = L'\r';
							break;
						case L'f':
							t = L'\f';
							break;
						case L'b':
							t = L'\b';
							break;
						case L'n':
							t = L'\n';
							break;
						case L't':
							t = L'\t';
							break;
						case L'v':
							t = L'\v';
							break;
						case L'\\':
							t = n;
							break;
						case L'"':
							t = n;
							break;
						case L'\'':
							t = n;
							break;
						default:
							str += ch;
							break;
						}
						str += t;
						pos++;
					}
				}
				else if (ch == L'"') {
					pos ++ ;
					str += ch;
					break;
				}
				else {
					str += ch;
					pos++;
				}
			}
		}
	}
	return str;
}

void CLocalizedStringProvider::ReadParts(CTextStream * stream, wxString & line, size_t & pos, std::vector<wxString>& parts)
{
	if (stream != 0) {
		while (pos < line.length()) {
			if(this->SkipWhitespaces(stream, line, pos))
			{ 
				if ((pos < line.length() - 1) && (line[pos] == L'L') && (line[pos + 1] == L'\"')) {
					parts.push_back(this->ReadString(stream, line, pos));
				}
				else {
					parts.push_back(NameStartString +this->ReadName(stream, line, pos));
				}
			}
		}
	}
}

bool CLocalizedStringProvider::IsWhiteSpace(wchar_t ch)
{
	return ch == L' ' || ch == '\t';
}
