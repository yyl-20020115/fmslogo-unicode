#include <wx/string.h>
#include "localizedstrings.h"
#include "CLocalizedStringProvider.h"

#ifdef _WINDOWS
#include <Windows.h>
#endif
#include "CUnicodeFileTextStream.h"
#include "CConstStringTextReadonlyStream.h"

CLocalizedStringProvider Provider;

void LoadLocalizedStringsFromFile(const wxString & path)
{
	CUnicodeFileTextStream cfts;
	if (cfts.Open(path, L"r")) {
		LoadLocalizedStringsFromStream(&cfts);
	}
}

void LoadLocalizedStringsFromResource(const class wxString& name, const class wxString& type)
{
#ifdef _WINDOWS
	HMODULE hm = GetModuleHandle(NULL);
	HRSRC hrsrc = FindResource(hm, name, type);
	DWORD e = GetLastError();
	if (hrsrc != INVALID_HANDLE_VALUE) {
		DWORD length = SizeofResource(hm, hrsrc)/sizeof(wchar_t);

		HGLOBAL hgsrc = LoadResource(hm, hrsrc);
		if (hgsrc != INVALID_HANDLE_VALUE) {
			wchar_t* p = (wchar_t*)LockResource(hgsrc);
			if (p != 0)
			{
				LoadLocalizedStringsFromStream(&CConstStringTextReadonlyStream(p, length));
			}
		}
	}
#else
	//use objcpy to embeded localized strings file inside of the executable
#endif
}

void LoadLocalizedStringsFromStream(class CTextStream * stream)
{
	if (stream != 0) {

		Provider.Assign(L"LOCALIZED_GENERAL_PRODUCTNAME", LOCALIZED_GENERAL_PRODUCTNAME);

		Provider.Load(stream);
	}
}

const wxString& GetResourceString(const wchar_t * Name)
{
	static int i = 0;
	//last step,not found,return the name itself!
	const wxString& result = (Name != 0) ? Provider.Find(Name) : CLocalizedStringProvider::EmptyString;

	if (result.length() == 0) 
	{
		i++;
	}
	return result;
}
