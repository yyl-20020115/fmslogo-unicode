#ifndef __CENCODINGCONVERTER__
#define __CENCODINGCONVERTER__
#include <wx/string.h>

class CEncodingConverter
{
public:
	static const wxString FixedEncoding;
public:
	CEncodingConverter(const wxString& OtherEncoding, bool ignore = true);
	~CEncodingConverter();
public:
	virtual bool IsValid();
	virtual void Reset();

	virtual size_t Convert(char** from_text_ptr, size_t* from_length_ptr, wchar_t** to_text_ptr, size_t* to_length_ptr);

	virtual size_t Convert(wchar_t** from_text_ptr, size_t* from_length_ptr, char** to_text_ptr, size_t* to_length_ptr);

protected:
	void* converter_to_utf16;
	void* converter_from_utf16;
};
#endif

