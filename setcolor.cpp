#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "setcolor.h"

    #include <wx/button.h>
    #include <wx/gdicmn.h>
    #include <wx/sizer.h>
    #include <wx/slider.h>
    #include <wx/stattext.h>
    #include <wx/dcclient.h>

    #include "logocore.h"
    #include "commander.h"
    #include "graphics.h"
    #include "logodata.h"
    #include "stringadapter.h"
    #include "localizedstrings.h"
#endif

// ----------------------------------------------------------------------------
// CSetColor::CColorWindow
// ----------------------------------------------------------------------------

CSetColor::CColorWindow::CColorWindow(
    CSetColor   *    Parent,
    wxWindowID       Id,
    const wxPoint  & Position,
    const wxSize   & Size,
    const wxColour & Color
    )
    : wxWindow(Parent, Id, Position, Size)
{
    SetBackgroundColour(Color);
}

void CSetColor::CColorWindow::SetColor(
    const wxColour & NewColor
    )
{
    SetBackgroundColour(NewColor);

    // since the color changed, we must repaint the window
    Refresh();
}

void CSetColor::CColorWindow::OnClick( wxMouseEvent &WXUNUSED(event) )
{
    if (GetId() != wxID_ANY)
    {
        // This is one of the clickable buttons, not the display-only window,
        // so we pass the event on to the parent window.
        CSetColor * parent = static_cast<CSetColor *>(GetParent());

        parent->SetColor(GetBackgroundColour());
    }
}

BEGIN_EVENT_TABLE(CSetColor::CColorWindow, wxWindow)
    EVT_LEFT_DOWN(CSetColor::CColorWindow::OnClick)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// CSetColor
// ----------------------------------------------------------------------------

enum ID_SETCOLOR
{
    ID_SETCOLOR_PIXELSPERINCH = wxID_HIGHEST,
    ID_SETCOLOR_SLIDER_RED,
    ID_SETCOLOR_SLIDER_GREEN,
    ID_SETCOLOR_SLIDER_BLUE,
    ID_SETCOLOR_APPLY,
    ID_SETCOLOR_COLOR1,
    ID_SETCOLOR_COLOR2,
    ID_SETCOLOR_COLOR3,
    ID_SETCOLOR_COLOR4,
    ID_SETCOLOR_COLOR5,
    ID_SETCOLOR_COLOR6,
    ID_SETCOLOR_COLOR7,
    ID_SETCOLOR_COLOR8,
};

CSetColor::CSetColor(
    wxWindow    *    Parent,
    const wchar_t  *    Title,
    const wxColour & InitialColor,
    const wchar_t  *    LogoCommand,
    CSetColor   *  & ExternalReference
    )
    : wxDialog(Parent, wxID_ANY, wxString(Title)),
      m_ExternalReference(ExternalReference),
      m_RedSlider(NULL),
      m_GreenSlider(NULL),
      m_BlueSlider(NULL),
      m_LogoCommand(LogoCommand)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *colorSettingSizer = new wxStaticBoxSizer(wxVERTICAL, this);


    //
    // Add the left-hand pane, which has thickness setting by picture on
    // the top and thickness setting by slider on the bottom.
    //
    topLevelSizer->Add(colorSettingSizer, 0, wxEXPAND | wxALL, 5);


    //
    // Add the row of pre-computed color selections
    //
    wxBoxSizer *colorByPictures = new wxBoxSizer(wxHORIZONTAL);

    for (size_t i = 0; i < 8; i++)
    {
        const int width  = 30;
        const int height = 30;

        wxWindow * picture = new CColorWindow(
            this,
            ID_SETCOLOR_COLOR1 + i,
            wxDefaultPosition,
            wxSize(width, height),
            wxColor(colortable[i]));

        colorByPictures->Add(picture, 0, wxALIGN_CENTER | wxALL, 5);
    }
    colorSettingSizer->Add(colorByPictures, 0, wxEXPAND | wxALL, 5);


    colorSettingSizer->AddSpacer(10);

    struct {
        wxSlider **  Slider;
        const wchar_t * SliderLabel;
        int          InitialValue;
    } sliderData[] = {
        {&m_RedSlider,   LOCALIZED_SETCOLOR_RED,   InitialColor.Red()},
        {&m_GreenSlider, LOCALIZED_SETCOLOR_GREEN, InitialColor.Green()},
        {&m_BlueSlider,  LOCALIZED_SETCOLOR_BLUE,  InitialColor.Blue()},
    };

    // This is a grid sizer to keep the labels and the sliders evenly spaced.
    // We want it to look something like this:
    //
    //   Red   <--------|---------------->
    //   Green <--------------|---------->
    //   Blue  <|------------------------>
    //
    wxGridSizer *slidersSizer = new wxFlexGridSizer(2);

    //
    // Add the row of computed size selector pictures
    //
    for (size_t i = 0; i < ARRAYSIZE(sliderData); i++)
    {
        wxStaticText *colorText = new wxStaticText(
            this,
            wxID_ANY,
			wxString(sliderData[i].SliderLabel),
            wxDefaultPosition,
            wxDefaultSize,
            wxALIGN_CENTRE);
        slidersSizer->Add(
            colorText,
            0,
            wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
            5);

        *sliderData[i].Slider = new wxSlider(
            this,
            ID_SETCOLOR_SLIDER_RED + i,
            sliderData[i].InitialValue,
            0,
            255,
            wxDefaultPosition,
            wxSize(250, 24),
            wxSL_HORIZONTAL);

        slidersSizer->Add(*sliderData[i].Slider, 0, wxEXPAND | wxALL, 5);
    }
    colorSettingSizer->Add(slidersSizer, 0, wxEXPAND | wxALL, 5);


    //
    // the column with the color display, the OK, Cancel, and Apply buttons
    //
    wxBoxSizer *buttonColumn = new wxBoxSizer(wxVERTICAL);

    m_SelectedColor = new CColorWindow(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(60, 60),
        InitialColor);
    buttonColumn->Add(m_SelectedColor, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *ok = new wxButton(
        this, 
        wxID_OK,
		wxString(LOCALIZED_SETCOLOR_OK));
    buttonColumn->Add(ok, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancel = new wxButton(
        this, 
        wxID_CANCEL, 
		wxString(LOCALIZED_SETCOLOR_CANCEL));
    buttonColumn->Add(cancel, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *apply = new wxButton(
        this, 
        ID_SETCOLOR_APPLY,
		wxString(LOCALIZED_SETCOLOR_APPLY));
    buttonColumn->Add(apply, 0, wxALIGN_CENTER | wxALL, 5);

    topLevelSizer->Add(buttonColumn, 0, wxALIGN_CENTER | wxALL, 5);

    // make the "Ok" button the default
    ok->SetDefault();

    // Give the red slider focus, since it's the first one
    // that the user is likely to interact with when using
    // only the keyboard.
    m_RedSlider->SetFocus();

    SetSizer(topLevelSizer);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);

    Fit();

    // Update the slider positions to match the current color.
    SetColor(InitialColor);
}


void CSetColor::SetColor(
    const wxColour & NewColor
    )
{
    m_SelectedColor->SetColor(NewColor);
    m_RedSlider->SetValue(NewColor.Red());
    m_GreenSlider->SetValue(NewColor.Green());
    m_BlueSlider->SetValue(NewColor.Blue());
}

void CSetColor::OnApplyButton(wxCommandEvent& event)
{
    // Get the color from the sliders
    int red   = m_RedSlider->GetValue();
    int green = m_GreenSlider->GetValue();
    int blue  = m_BlueSlider->GetValue();

    // Get the uppercase form of the logo command
    // so that it looks consistent in the commaner's
    // history.
	wchar_t upperCaseCommand[MAX_BUFFER_SIZE];

    NormalizeCaseForDisplay(
        upperCaseCommand,
        m_LogoCommand,
        wcslen(m_LogoCommand));

	wchar_t logoInstruction[256];

    wprintf(
        logoInstruction,
        "%s [%d %d %d]",
        upperCaseCommand,
        red,
        green,
        blue);

    // Run the color setting instruction
    RunLogoInstructionFromGui(logoInstruction);
}

void CSetColor::OnOkButton(wxCommandEvent& Event)
{
    // Do whatever we do when we apply the changes
    OnApplyButton(Event);

    // NULL-out the reference that CMainFrame is holding
    // so that it knows the window is no longer valid.
    // This object will get deleted on its own.
    m_ExternalReference = NULL;

    // Let the window close
    Event.Skip();
}

void CSetColor::OnCancelButton(wxCommandEvent& Event)
{
    // NULL-out the reference that CMainFrame is holding
    // so that it knows the window is no longer valid.
    // This object will get deleted on its own.
    m_ExternalReference = NULL;

    // Let the window close
    Event.Skip();
}

void CSetColor::OnSliderUpdated(wxCommandEvent & WXUNUSED(event))
{
    // get the color from the sliders
    int red   = m_RedSlider->GetValue();
    int green = m_GreenSlider->GetValue();
    int blue  = m_BlueSlider->GetValue();

    // Save the new color in the "selected color" window.
    // This will also udpate the color shown in that window.
    m_SelectedColor->SetColor(wxColour(red, green, blue));
}


BEGIN_EVENT_TABLE(CSetColor, wxDialog)
    EVT_BUTTON(wxID_OK,                  CSetColor::OnOkButton)
    EVT_BUTTON(wxID_CANCEL,              CSetColor::OnCancelButton)
    EVT_BUTTON(ID_SETCOLOR_APPLY,        CSetColor::OnApplyButton)
    EVT_SLIDER(ID_SETCOLOR_SLIDER_RED,   CSetColor::OnSliderUpdated)
    EVT_SLIDER(ID_SETCOLOR_SLIDER_GREEN, CSetColor::OnSliderUpdated)
    EVT_SLIDER(ID_SETCOLOR_SLIDER_BLUE,  CSetColor::OnSliderUpdated)
END_EVENT_TABLE()
