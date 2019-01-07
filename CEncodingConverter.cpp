#include "CEncodingConverter.h"

#ifndef _WINDOWS
#include <iconv.h>
#endif

const wxString CEncodingConverter::FixedEncoding = L"UTF16";

CEncodingConverter::CEncodingConverter(const wxString& OtherEncoding, bool ignore)
	:converter_to_utf16(0)
	, converter_from_utf16(0)
{
	wxString fec = FixedEncoding;
	wxString oec = OtherEncoding;
	wxString ign;
	if (ignore) {
		ign = L"//IGNORE";
	}
#ifndef _WINDOWS
	this->converter_to_utf16 = iconv_open((const char*)(fec + ign), (const char*)oec);
	this->converter_from_utf16 = iconv_open((const char*)(oec + ign), (const char*)fec);
#endif
}

CEncodingConverter::~CEncodingConverter()
{
#ifndef _WINDOWS
	if (this->converter_to_utf16 != 0) {
		iconv_close(this->converter_to_utf16);
		this->converter_to_utf16 = 0;
	}
	if (this->converter_from_utf16 != 0) {
		iconv_close(this->converter_from_utf16);
		this->converter_from_utf16 = 0;
	}
#endif
}


bool CEncodingConverter::IsValid()
{
	const void* invalid_hanlder = sizeof(void*) == 8 ? (void*)-1LL : (void*)-1;

	return this->converter_from_utf16!= invalid_hanlder
		&& this->converter_to_utf16!= invalid_hanlder;
}

void CEncodingConverter::Reset()
{
#ifndef _WINDOWS
	if (this->IsValid())
	{
		iconv((iconv_t)(this->converter_to_utf16), 0, 0, 0, 0);
		iconv((iconv_t)(this->converter_from_utf16), 0, 0, 0, 0);
	}
#endif
}

size_t CEncodingConverter::Convert(char** from_text_ptr, size_t* from_length_ptr, wchar_t ** to_text_ptr, size_t * to_length_ptr)
{
	const size_t invalid_size = sizeof(size_t) == 8 ? (size_t)-1LL : (size_t)-1;

#ifndef _WINDOWS
	if (this->IsValid() && from_text!=0 && from_length!=0 && to_text_ptr!=0 && to_length_ptr!=0) 
	{
		return iconv((iconv_t)(this->converter_to_utf16), (const char**)form_text_ptr, from_length_ptr, (const char**)to_text_ptr, to_length_ptr);
	}
#endif
	return invalid_size;
}

size_t CEncodingConverter::Convert(wchar_t** from_text_ptr, size_t* from_length_ptr, char ** to_text_ptr, size_t * to_length_ptr)
{
	const size_t invalid_size = sizeof(size_t) == 8 ? (size_t)-1LL : (size_t)-1;
#ifndef _WINDOWS
	if (this->IsValid())
	{
		return iconv((iconv_t)(this->converter_from_utf16), (const char**)form_text_ptr, from_length_ptr, (const char**)to_text_ptr, to_length_ptr);
	}
#endif
	return invalid_size;
}


