#include <wx/string.h>
#include "localizedstrings.h"
#include "CLocalizedStringProvider.h"

#ifdef _WINDOWS
#include <Windows.h>
#elif defined(LINUX)

extern unsigned short _binary_localizedstrings_zh_cn_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_zh_cn_ucs2le_h_end;
extern size_t         _binary_localizedstrings_zh_cn_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_de_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_de_ucs2le_h_end;
extern size_t         _binary_localizedstrings_de_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_en_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_en_ucs2le_h_end;
extern size_t         _binary_localizedstrings_en_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_es_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_es_ucs2le_h_end;
extern size_t         _binary_localizedstrings_es_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_fr_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_fr_ucs2le_h_end;
extern size_t         _binary_localizedstrings_fr_ucs2le_h_size;


extern unsigned short _binary_localizedstrings_gr_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_gr_ucs2le_h_end;
extern size_t         _binary_localizedstrings_gr_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_hr_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_hr_ucs2le_h_end;
extern size_t         _binary_localizedstrings_hr_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_it_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_it_ucs2le_h_end;
extern size_t         _binary_localizedstrings_it_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_pl_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_pl_ucs2le_h_end;
extern size_t         _binary_localizedstrings_pl_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_pt_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_pt_ucs2le_h_end;
extern size_t         _binary_localizedstrings_pt_ucs2le_h_size;

extern unsigned short _binary_localizedstrings_ru_ucs2le_h_start;
extern unsigned short _binary_localizedstrings_ru_ucs2le_h_end;
extern size_t         _binary_localizedstrings_ru_ucs2le_h_size;
#endif

#include "CUnicodeFileTextStream.h"
#include "CConstStringTextReadonlyStream.h"

// objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-zh-cn-ucs2le.h localizedstrings-zh-cn-ucs2le.o
// objdump -ht localizedstrings-zh-cn-ucs2le.o

// localizedstrings-zh-cn-ucs2le.o£º     format elf64-x86-64

// Idx Name          Size      VMA               LMA               File off  Algn
//   0 .data         0002b978  0000000000000000  0000000000000000  00000040  2**0
//                  CONTENTS, ALLOC, LOAD, DATA
// SYMBOL TABLE:
// 0000000000000000 l    d  .data	0000000000000000 .data
// 0000000000000000 g       .data	0000000000000000 _binary_localizedstrings_zh_cn_ucs2le_h_start
// 000000000002b978 g       .data	0000000000000000 _binary_localizedstrings_zh_cn_ucs2le_h_end
// 000000000002b978 g       *ABS*	0000000000000000 _binary_localizedstrings_zh_cn_ucs2le_h_size



CLocalizedStringProvider Provider;
 
void LoadLocalizedStringsFromFile(const wxString & path)
{
	CUnicodeFileTextStream cfts;
	if (cfts.Open(path, L"rb")) {
		cfts.SkipBOM();
		LoadLocalizedStringsFromStream(&cfts);
	}
}
#ifdef LINUX


bool TranslateLocalizedStringResourcePointer(const wxString& name, uchar*& ptr, size_t& length)
{
    ptr = 0;
    length = 0;
    wxString n = name;
    
    n.MakeLower();
    
    if(n.Contains(N_LOCALIZED_STRINGS_FILE_DE))
    {
        ptr=&_binary_localizedstrings_de_ucs2le_h_start;
        length = &_binary_localizedstrings_de_ucs2le_h_end - &_binary_localizedstrings_de_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_EN))
    {
        ptr=&_binary_localizedstrings_en_ucs2le_h_start;
        length = &_binary_localizedstrings_en_ucs2le_h_end - &_binary_localizedstrings_en_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_ES))
    {
        ptr=&_binary_localizedstrings_es_ucs2le_h_start;
        length = &_binary_localizedstrings_es_ucs2le_h_end - &_binary_localizedstrings_es_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_FR))
    {
        ptr=&_binary_localizedstrings_fr_ucs2le_h_start;
        length = &_binary_localizedstrings_fr_ucs2le_h_end - &_binary_localizedstrings_fr_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_GR))
    {
        ptr=&_binary_localizedstrings_gr_ucs2le_h_start;
        length = &_binary_localizedstrings_gr_ucs2le_h_end - &_binary_localizedstrings_gr_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_HR))
    {
        ptr=&_binary_localizedstrings_hr_ucs2le_h_start;
        length = &_binary_localizedstrings_hr_ucs2le_h_end - &_binary_localizedstrings_hr_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_IT))
    {
        ptr=&_binary_localizedstrings_it_ucs2le_h_start;
        length = &_binary_localizedstrings_it_ucs2le_h_end - &_binary_localizedstrings_it_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_PL))
    {
        ptr=&_binary_localizedstrings_pl_ucs2le_h_start;
        length = &_binary_localizedstrings_pl_ucs2le_h_end - &_binary_localizedstrings_pl_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_PT))
    {
        ptr=&_binary_localizedstrings_pt_ucs2le_h_start;
        length = &_binary_localizedstrings_pt_ucs2le_h_end - &_binary_localizedstrings_pt_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_RU))
    {
        ptr=&_binary_localizedstrings_ru_ucs2le_h_start;
        length = &_binary_localizedstrings_ru_ucs2le_h_end - &_binary_localizedstrings_ru_ucs2le_h_start;
    }
    else if(n.Contains(N_LOCALIZED_STRINGS_FILE_ZH_CN))
    {
        ptr=&_binary_localizedstrings_zh_cn_ucs2le_h_start;
        length = &_binary_localizedstrings_zh_cn_ucs2le_h_end - &_binary_localizedstrings_zh_cn_ucs2le_h_start;
    }
    else
    {
        ptr=&_binary_localizedstrings_en_ucs2le_h_start;
        length = &_binary_localizedstrings_en_ucs2le_h_end - &_binary_localizedstrings_en_ucs2le_h_start;
    }
    return ptr!=0;
}
#endif
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
				CConstStringTextReadonlyStream cstrs(p, length);
				LoadLocalizedStringsFromStream(&cstrs);
			}
		}
	}
#elif defined(LINUX)
    uchar* p = 0;
    size_t length = 0;
    if (TranslateLocalizedStringResourcePointer(name,p,length))
    {
        CConstStringTextReadonlyStream cstrs(p, length);
        LoadLocalizedStringsFromStream(&cstrs);
    }

    
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
