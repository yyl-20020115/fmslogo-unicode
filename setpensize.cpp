#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "setpensize.h"

    #include <wx/button.h>
    #include <wx/gdicmn.h>
    #include <wx/sizer.h>
    #include <wx/slider.h>
    #include <wx/stattext.h>
    #include <wx/dcclient.h>

    #include "logodata.h"
    #include "commander.h"
    #include "logocore.h"
    #include "stringadapter.h"
    #include "localizedstrings.h"
#endif

// ----------------------------------------------------------------------------
// CSetPenSize::CPenSizeWindow
// ----------------------------------------------------------------------------

CSetPenSize::CPenSizeWindow::CPenSizeWindow(
    CSetPenSize   * Parent,
    wxWindowID      Id,
    const wxPoint & Position,
    const wxSize  & Size,
    int             PenWidth
    )
    : wxWindow(Parent, wxID_ANY, Position, Size),
      m_PenWidth(PenWidth)
{
    SetBackgroundColour(*wxWHITE);
}

void CSetPenSize::CPenSizeWindow::SetPenSize(
    int             PenSize
    )
{
    m_PenWidth = PenSize;

    // since the size changed, we must now repaint the window
    Refresh();
}

void CSetPenSize::CPenSizeWindow::OnPaint( wxPaintEvent &WXUNUSED(event) )
{
    wxPaintDC dc(this);

    SetBackgroundColour(*wxWHITE);

    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxBLACK_BRUSH);

    const wxCoord yCoord = (GetSize().GetHeight() - m_PenWidth) / 2;

    dc.DrawRectangle(
        0, 
        yCoord, 
        GetSize().GetWidth(), 
        m_PenWidth);
}

void CSetPenSize::CPenSizeWindow::OnClick( wxMouseEvent &WXUNUSED(event) )
{
    if (GetId() != wxID_ANY)
    {
        // This is one of the clickable buttons, not the display-only window,
        // so we pass the event on to the parent window.
        CSetPenSize * parent = static_cast<CSetPenSize *>(GetParent());

        parent->SetPenSize(m_PenWidth);
    }
}

BEGIN_EVENT_TABLE(CSetPenSize::CPenSizeWindow, wxWindow)
    EVT_PAINT(CSetPenSize::CPenSizeWindow::OnPaint)
    EVT_LEFT_DOWN(CSetPenSize::CPenSizeWindow::OnClick)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// CSetPenSize
// ----------------------------------------------------------------------------

enum ID_SETPENSIZE
{
    ID_SETPENSIZE_PIXELSPERINCH = wxID_HIGHEST,
    ID_SETPENSIZE_SLIDER,
    ID_SETPENSIZE_APPLY,
    ID_SETPENSIZE_SIZE1,
    ID_SETPENSIZE_SIZE2,
    ID_SETPENSIZE_SIZE3,
    ID_SETPENSIZE_SIZE4,
    ID_SETPENSIZE_SIZE5,
    ID_SETPENSIZE_SIZE6,
    ID_SETPENSIZE_SIZE7,
    ID_SETPENSIZE_SIZE8,
};

CSetPenSize::CSetPenSize(
    wxWindow    *   Parent,
    int             InitialPenSize,
    CSetPenSize * & ExternalReference
    )
    : wxDialog(Parent, wxID_ANY, wxString(LOCALIZED_SETPENSIZE)),
      m_PenWidth(InitialPenSize),
      m_ExternalReference(ExternalReference)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *thicknessSettingSizer = new wxStaticBoxSizer(wxVERTICAL, this);


    //
    // Add the left-hand pane, which has thickness setting by picture on
    // the top and thickness setting by slider on the bottom.
    //
    topLevelSizer->Add(thicknessSettingSizer, 0, wxEXPAND | wxALL, 5);


    //
    // Add the row of computed size selector pictures
    //
    wxBoxSizer *thicknessByPictures = new wxBoxSizer(wxHORIZONTAL);

    static const struct {
        int  ChildId;
        int  PenWidth;
    } data[] = {
        {ID_SETPENSIZE_SIZE1, 1},
        {ID_SETPENSIZE_SIZE2, 2},
        {ID_SETPENSIZE_SIZE3, 3},
        {ID_SETPENSIZE_SIZE4, 4},
        {ID_SETPENSIZE_SIZE5, 6},
        {ID_SETPENSIZE_SIZE6, 8},
        {ID_SETPENSIZE_SIZE7, 16},
        {ID_SETPENSIZE_SIZE8, 32},
    };

    for (size_t i = 0; i < ARRAYSIZE(data); i++)
    {
        const int width  = 30;
        const int height = 30;

        wxWindow * picture = new CPenSizeWindow(
            this,
            data[i].ChildId, 
            wxDefaultPosition,
            wxSize(width, height),
            data[i].PenWidth);

        thicknessByPictures->Add(picture, 0, wxALIGN_CENTER | wxALL, 5);
    }
    thicknessSettingSizer->Add(thicknessByPictures, 0, wxEXPAND | wxALL, 5);


    thicknessSettingSizer->AddSpacer(10);

    //
    // Add the row of computed size selector pictures
    //
    wxBoxSizer *thicknessBySlider = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *thicknessText = new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SETPENSIZE_SIZE),
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);
    thicknessBySlider->Add(
        thicknessText,
        0,
        wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);

    m_ThicknessSlider = new wxSlider(
        this,
        ID_SETPENSIZE_SLIDER,
        m_PenWidth, 
        1,
        32,
        wxDefaultPosition,
        wxSize(250, 24),
        wxSL_HORIZONTAL);
    thicknessBySlider->Add(m_ThicknessSlider, 0, wxEXPAND | wxALL, 5);

    thicknessSettingSizer->Add(thicknessBySlider, 0, wxEXPAND | wxALL, 5);



    //
    // the column with the thickness display, the OK, Cancel, and Apply buttons
    //
    wxBoxSizer *buttonColumn = new wxBoxSizer(wxVERTICAL);

    m_ThicknessDisplay = new CPenSizeWindow(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(60, 60),
        m_PenWidth);
    m_ThicknessDisplay->SetBackgroundColour(*wxWHITE);
    buttonColumn->Add(m_ThicknessDisplay, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *ok = new wxButton(
        this, 
        wxID_OK,
		wxString(LOCALIZED_SETPENSIZE_OK));
    buttonColumn->Add(ok, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancel = new wxButton(
        this, 
        wxID_CANCEL, 
		wxString(LOCALIZED_SETPENSIZE_CANCEL));
    buttonColumn->Add(cancel, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *apply = new wxButton(
        this, 
        ID_SETPENSIZE_APPLY,
		wxString(LOCALIZED_SETPENSIZE_APPLY));
    buttonColumn->Add(apply, 0, wxALIGN_CENTER | wxALL, 5);

    topLevelSizer->Add(buttonColumn, 0, wxALIGN_CENTER | wxALL, 5);

    // make the "Ok" button the default
    ok->SetDefault();

    // Give focus to the slider, since that's the control
    // the user is mostly likely to manipulate first.
    m_ThicknessSlider->SetFocus();

    SetSizer(topLevelSizer);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);

    Fit();

    // update the slider's position to match the pen size
    SetPenSize(m_PenWidth);
}


void CSetPenSize::SetPenSize(
    int  PenSize
    )
{
    m_PenWidth = PenSize;
    m_ThicknessDisplay->SetPenSize(PenSize);
    m_ThicknessSlider->SetValue(PenSize);
}

void CSetPenSize::OnApplyButton(wxCommandEvent& Event)
{
    // Get the uppercase form of SETPENSIZE
	wchar_t setpensize[MAX_BUFFER_SIZE];
    NormalizeCaseForDisplay(
        setpensize,
        LOCALIZED_ALTERNATE_SETPENSIZE,
        STRINGLENGTH(LOCALIZED_ALTERNATE_SETPENSIZE));

    // Run "SETPENSIZE <PENSIZE>"
    wchar_t logoInstruction[256];

    wprintf(
        logoInstruction,
        L"%s %d",
        setpensize,
        m_PenWidth);

    RunLogoInstructionFromGui(logoInstruction);
}

void CSetPenSize::OnOkButton(wxCommandEvent& Event)
{
    OnApplyButton(Event);

    // NULL-out the reference that CMainFrame is holding
    // so that it knows the window is no longer valid.
    // This object will get deleted on its own.
    m_ExternalReference = NULL;

    // Let the window close
    Event.Skip();
}

void CSetPenSize::OnCancelButton(wxCommandEvent & Event)
{
    // NULL-out the reference that CMainFrame is holding
    // so that it knows the window is no longer valid.
    // This object will get deleted on its own.
    m_ExternalReference = NULL;

    // Let the window close
    Event.Skip();
}

void CSetPenSize::OnSliderUpdated(wxCommandEvent & WXUNUSED(Event))
{
    // Update the pen's preview to match the new slider value.
    m_PenWidth = m_ThicknessSlider->GetValue();
    m_ThicknessDisplay->SetPenSize(m_PenWidth);
}


BEGIN_EVENT_TABLE(CSetPenSize, wxDialog)
    EVT_BUTTON(wxID_OK,              CSetPenSize::OnOkButton)
    EVT_BUTTON(wxID_CANCEL,          CSetPenSize::OnCancelButton)
    EVT_BUTTON(ID_SETPENSIZE_APPLY,  CSetPenSize::OnApplyButton)
    EVT_SLIDER(ID_SETPENSIZE_SLIDER, CSetPenSize::OnSliderUpdated)
END_EVENT_TABLE()
