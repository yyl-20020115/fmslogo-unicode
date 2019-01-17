#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "aboutfmslogo.h"

   #include <wx/sizer.h>
   #include <wx/stattext.h>
   #include <wx/button.h>

   #include "localizedstrings.h"
   #include "logocore.h" // for ARRAYSIZE
   #include "stringadapter.h"
#endif

// ----------------------------------------------------------------------------
// CAboutFmsLogo
// ----------------------------------------------------------------------------

//#define LOCALIZED_ABOUTFMS_WXWIDGETS_VERSION (LOCALIZED_GENERAL_PRODUCTNAME L" " LOCALIZED_ABOUTFMS_VERSION L" " FMSLOGO_VERSION L"\n" L"http://sourceforge.net/projects/fmslogo")


CAboutFmsLogo::CAboutFmsLogo(wxWindow * Parent)
    : wxDialog(Parent, wxID_ANY, GetResourceString(L"LOCALIZED_ABOUTFMS"))
{
	// The text in all of the static controls
	static const wxString staticText[] = {
		GetResourceString(L"LOCALIZED_GENERAL_PRODUCTNAME") + 
		L" " LOCALIZED_ABOUTFMS_VERSION
		L" " FMSLOGO_VERSION 
	    L"\n"
	    L"http://sourceforge.net/projects/fmslogo",
		GetResourceString(L"LOCALIZED_ABOUTFMS_GUI")              ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_CORE")             ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_INSTALLER")        ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_ADVENTURE")        ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_SPECIALTHANKS")    ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_GPL")              ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_NEWSGROUP")        ,
		GetResourceString(L"LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC")  ,
	    GetResourceString(L"LOCALIZED_ABOUTFMS_UNICODE_VERSION"),
	};

    wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);

    for (size_t i = 0; i < ARRAYSIZE(staticText); i++)
    {
		if (!staticText->IsSameAs(ResourceStringSpaceHolder)) {
			wxStaticText *info = new wxStaticText(
				this,
				wxID_ANY,
				wxString(L"  ") + (staticText[i]) + wxString(L"  "),
				wxDefaultPosition,
				wxDefaultSize,
				wxALIGN_CENTRE | wxSUNKEN_BORDER);

			sizerTop->Add(info, 0, wxALL | wxEXPAND, 5);
		}
    }



    wxButton *okButton = new wxButton(
        this,
        wxID_CANCEL,
		GetResourceString(L"LOCALIZED_ABOUTFMS_OK"));
    sizerTop->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

    // make the "Ok" button the default
    okButton->SetFocus();
    okButton->SetDefault();
}
