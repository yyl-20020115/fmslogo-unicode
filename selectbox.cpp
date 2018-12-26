#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "selectbox.h"

    #include <wx/listbox.h>
    #include <wx/textctrl.h>
    #include <wx/sizer.h>
    #include <wx/button.h>

    #include "guiutils.h"
    #include "localizedstrings.h"
    #include "stringadapter.h" // for WXSTRING
    #include "logocore.h"      // for ARRAYSIZE
#endif

// Control IDs
enum
{
   ID_CHOICELIST = wxID_HIGHEST,
};

// ----------------------------------------------------------------------------
// CSelectBox
// ----------------------------------------------------------------------------

CSelectBox::CSelectBox(
    wxWindow            * Parent, 
    const wxString      & Caption,
    const wxArrayString & Choices
    )
    : wxDialog(
        Parent,
        wxID_ANY,
        Caption,
        wxDefaultPosition,
        wxDefaultSize,
        wxCAPTION | wxCLOSE_BOX | wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE),
      m_Choices(NULL),
      m_Selection(-1)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxHORIZONTAL);

    // Add the choices list
    m_Choices = new wxListBox(
        this,
        ID_CHOICELIST,
        wxDefaultPosition,
        wxDefaultSize,
        Choices);
    m_Choices->SetMinSize(wxSize(200, 150));

    topLevelSizer->Add(
        m_Choices,
        1,
        wxTOP | wxLEFT | wxBOTTOM | wxEXPAND,
        15);

    // add the column of buttons
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxVERTICAL);

    static const MENUITEM buttonInfo[] = {
        {GetResourceString(L"LOCALIZED_SELECTBOX_OK"),     wxID_OK},
        {GetResourceString(L"LOCALIZED_SELECTBOX_CANCEL"), wxID_CANCEL},
    };
    for (size_t i = 0; i < ARRAYSIZE(buttonInfo); i++)
    {
        wxButton * button = new wxButton(
            this,
            buttonInfo[i].MenuId,
			wxString(buttonInfo[i].MenuText),
            wxDefaultPosition,
            wxDefaultSize);

        buttonSizer->Add(
            button,
            0,
            wxALIGN_CENTER | wxALL,
            10);

        // Make the "OK" button the default.
        if (buttonInfo[i].MenuId == wxID_OK)
        {
            button->SetDefault();
        }
    }

    topLevelSizer->Add(
        buttonSizer,
        0,
        wxALIGN_CENTER_VERTICAL | wxALL,
        15);

    SetSizer(topLevelSizer);
    topLevelSizer->Fit(this);

    // Set a minimum size of the overall
    SetMinSize(GetSize());

    // select the first item
    if (!m_Choices->IsEmpty())
    {
        m_Choices->SetSelection(0);
    }
}

CSelectBox::~CSelectBox()
{
}

int CSelectBox::DoDialog()
{
    // Show the dialog as a modal box
    int returnCode = ShowModal();
    if (returnCode != wxID_OK)
    {
        return -1;
    }

    // For compatibility with MSWLogo, if there are
    // no choices and the user presses OK, return 0.
    if (m_Choices->IsEmpty())
    {
        return 0;
    }

    // Return the index of the selection
    return m_Choices->GetSelection();
}

void CSelectBox::OnDoubleClick(wxCommandEvent& Event)
{
    // A double-click is the same as pressing OK
    SetReturnCode(wxID_OK);
    Destroy();
}

BEGIN_EVENT_TABLE(CSelectBox, wxDialog)
    EVT_LISTBOX_DCLICK(ID_CHOICELIST, CSelectBox::OnDoubleClick)
END_EVENT_TABLE()
