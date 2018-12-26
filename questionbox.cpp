#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "questionbox.h"

    #include <algorithm>

    #include <wx/sizer.h>
    #include <wx/stattext.h>
    #include <wx/button.h>
    #include <wx/textctrl.h>

    #include "stringadapter.h"
    #include "localizedstrings.h"
#endif

// ----------------------------------------------------------------------------
// CQuestionBox
// ----------------------------------------------------------------------------

CQuestionBox::CQuestionBox(
    wxWindow       * Parent,
    const wxString & Title,
    const wxString & Question
    ) : 
    wxDialog(Parent, wxID_ANY, Title),
    m_Answer(NULL)
{
    // Get the title's width
    int titleWidth;
    int titleHeight;
    wxFont titleFont = GetFont();
    titleFont.SetFaceName(wxString(L"System"));
    GetTextExtent(Title, &titleWidth, &titleHeight, NULL, NULL, &titleFont);

    // Determine a good minimum size for the dialog box,
    // which is some base minimum or the size of the title.
    const int MINIMUM_QUESTION_WIDTH = 200;
    const int minWidth = std::max(titleWidth, MINIMUM_QUESTION_WIDTH);

    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // Replace any carriage returns in the question with a linefeed
    // so that FMSLogo's behavior matches MSWLogo's behavior.
    wxString normalizedQuestion(Question);
    for (size_t i = 0; i < normalizedQuestion.Len(); i++)
    {
        // Replace '\r' with '\n' unless it's part of a \r\n sequence.
        if (normalizedQuestion[i] == '\r' &&
            (i + 1 == normalizedQuestion.Len() || normalizedQuestion[i + 1] != '\n'))
        {
            normalizedQuestion[i] = '\n';
        }
    }

    wxStaticText *question = new wxStaticText(
        this,
        wxID_ANY,
        normalizedQuestion);
    topLevelSizer->Add(question, 1, wxALL | wxEXPAND, 4);

    m_Answer = new wxTextCtrl(this, wxID_ANY);
    m_Answer->SetInitialSize(wxSize(minWidth, -1));
    topLevelSizer->Add(m_Answer, 0, wxALL | wxEXPAND, 4);

    // add the buttons
    wxBoxSizer * buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *okButton = new wxButton(
        this, 
        wxID_OK,
		GetResourceString(L"LOCALIZED_QUESTIONBOX_OK"));
    buttonSizer->Add(okButton);

    wxButton *cancelButton = new wxButton(
        this, 
        wxID_CANCEL,
		GetResourceString(L"LOCALIZED_QUESTIONBOX_CANCEL"));
    buttonSizer->Add(cancelButton, 0, wxLEFT, 4);

    topLevelSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 4);

    SetSizerAndFit(topLevelSizer);

    // Make the "OK" button the default.
    okButton->SetDefault();

    // Give focus to the text field for the control
    m_Answer->SetFocus();
}

const wxString CQuestionBox::GetAnswer() const
{
    return m_Answer->GetValue();
}

