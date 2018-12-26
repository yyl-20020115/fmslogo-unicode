#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "minieditor.h"

   #include <wx/button.h>
   #include <wx/textctrl.h>
   #include <wx/sizer.h>
   #include <wx/settings.h>

   #include "minieditortextctrl.h"
   #include "fontutils.h"
   #include "stringadapter.h"
   #include "localizedstrings.h"
#endif

// Menu IDs
enum
{
    ID_MINIEDITOR_BODYTEXT = wxID_HIGHEST,

    ID_FINDMATCHINGPAREN,
    ID_SELECTMATCHINGPAREN,
    ID_AUTOCOMPLETE,
};

// ----------------------------------------------------------------------------
// CMiniEditor
// ----------------------------------------------------------------------------

CMiniEditor::CMiniEditor(
    wxWindow   * Parent, 
    const wxString& ToLineString
    )
    : wxDialog(
        Parent,
        wxID_ANY,
		wxString(ToLineString),
        wxDefaultPosition,
        wxSize(300, 400),
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
      m_TextField(NULL)
{
    wxBoxSizer * topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // Add the To Line input.
    // This is read-only because, at this point, it's too late to change it.
    // The user can only modify the body of the procedure.
    wxTextCtrl * toLine = new wxTextCtrl(
        this,
        wxID_ANY,
		(ToLineString),
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_READONLY);

    // The background color should be light gray to indicate that this
    // is a read-only control.
    toLine->SetBackgroundColour(
        wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

    topLevelSizer->Add(
        toLine,
        0,
        wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // add the procedure body (the editor)
    m_TextField = new CMiniEditorTextCtrl(this, ID_MINIEDITOR_BODYTEXT);
    topLevelSizer->Add(
        m_TextField,
        1, // expand this control with the size of the dialog box
        wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // Set the font to whatever is defined in the configuraton
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE); // default to using a fixed-width font
    GetConfigurationFont(L"EditFont", font);
    m_TextField->SetFont(font);

    // Add a row for the two buttons (End and Cancel)
    wxBoxSizer *buttonRow = new wxBoxSizer(wxHORIZONTAL);
    topLevelSizer->Add(
        buttonRow,
        0,
        wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // Add the "end" button
    wxButton * endButton = new wxButton(
        this,
        wxID_OK,
		GetResourceString(L"LOCALIZED_ALTERNATE_END"));
    buttonRow->Add(endButton);
    endButton->SetDefault();

    // Add a stretch spacer between End and Cancel so
    // that they can be on the left and right of the
    // dialog box, instead of next to each other.
    buttonRow->AddStretchSpacer();

    // Add the "Cancel" button.
    // While a Cancel button was not in the original design, wxWidgets
    // requires that it exist in order for the ESC key to act like a cancel.
    // Without it, ESC would simulate a keypress on the End button,
    // causing the definition to be accepted, instead of abandoned.
    wxButton * cancelButton = new wxButton(
        this,
        wxID_CANCEL,
		GetResourceString(L"LOCALIZED_GENERAL_CANCELBUTTON"));
    buttonRow->Add(cancelButton);

    SetSizer(topLevelSizer);

    // Ensure that the user doesn't resize the window so small
    // that the buttons overlap or are off-screen.
    SetMinSize(GetSize());

    // Make the text field have focus so that the user can start
    // typing the procedure's body immediately.
    m_TextField->SetFocus();
}

CMiniEditor::~CMiniEditor()
{
}

const wxString
CMiniEditor::GetProcedureBody() const
{
    return m_TextField->GetText();
}
