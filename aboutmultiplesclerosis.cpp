// -*- c++ -*-
#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER

  #include "aboutmultiplesclerosis.h"

  #include <wx/sizer.h>
  #include <wx/stattext.h>
  #include <wx/button.h>

  #include "localizedstrings.h"
  #include "stringadapter.h"

#endif


// ----------------------------------------------------------------------------
// CAboutMultipleSclerosis
// ----------------------------------------------------------------------------

CAboutMultipleSclerosis::CAboutMultipleSclerosis(wxWindow * Parent)
    : wxDialog(Parent, wxID_ANY,GetResourceString(L"LOCALIZED_ABOUTMS"))
{
    wxStaticText *text1 = new wxStaticText(
        this,
        wxID_ANY,
		wxString(L"\n  ")+ GetResourceString(L"LOCALIZED_ABOUTMS_FMS")+ wxString(L"  \n"), // add some padding to the sunken border
        wxDefaultPosition,
        wxDefaultSize, 
        wxALIGN_CENTRE | wxSUNKEN_BORDER);

    wxStaticText *text2 = new wxStaticText(
        this,
        wxID_ANY,
		GetResourceString(L"LOCALIZED_ABOUTMS_CONSIDERDONATING"),
        wxDefaultPosition,
        wxDefaultSize, 
        wxALIGN_CENTRE | wxSUNKEN_BORDER);

    wxButton *okButton = new wxButton(
        this,
        wxID_CANCEL,
		GetResourceString(L"LOCALIZED_ABOUTMS_OK"));

    wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(text1,    0, wxALL | wxEXPAND, 5);
    sizerTop->Add(text2,    0, wxALL | wxEXPAND, 5);
    sizerTop->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

    // make the "Ok" button the default
    okButton->SetFocus();
    okButton->SetDefault();
}
