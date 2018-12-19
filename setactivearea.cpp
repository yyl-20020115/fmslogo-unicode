#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "setactivearea.h"

    #include <wx/button.h>
    #include <wx/gdicmn.h>
    #include <wx/sizer.h>
    #include <wx/statbox.h>
    #include <wx/statline.h>
    #include <wx/stattext.h>
    #include <wx/textctrl.h>

    #include "fmslogo.h"
    #include "localizedstrings.h"
    #include "stringadapter.h"
#endif

// ----------------------------------------------------------------------------
// CSetActiveArea::CSmallIntegerCtrl
// ----------------------------------------------------------------------------
CSetActiveArea::CSmallIntegerCtrl::CSmallIntegerCtrl(
    wxWindow *      Parent,
    wxWindowID      Id,
    int             InitialValue,
    const wxPoint & Position
    ) : wxTextCtrl(
        Parent,
        Id,
        wxString::Format(wxString(L"%d"), InitialValue),
        Position)
{
    // keep this input small--it should only hold 3-4 characters
    SetSize(50, GetSize().GetHeight());
}

int CSetActiveArea::CSmallIntegerCtrl::GetIntegerValue() const
{
    long value;
    if (!GetValue().ToLong(&value))
    {
        // Compatible with MSWLogo behavior
        return 0;
    }

    return value;
}

void CSetActiveArea::CSmallIntegerCtrl::SetIntegerValue(int NewValue)
{
    ChangeValue(wxString::Format(wxString(L"%d"), NewValue));
}

// ----------------------------------------------------------------------------
// CSetActiveArea
// ----------------------------------------------------------------------------

enum ID_SETACTIVEAREA
{
    ID_PIXELSPERINCH = wxID_HIGHEST,
    ID_XLOW,
    ID_XHIGH,
    ID_YLOW,
    ID_YHIGH,
    ID_RESET,
};

CSetActiveArea::CSetActiveArea(
    wxWindow * Parent,
    int        XLow,
    int        XHigh,
    int        YLow,
    int        YHigh,
    int        PixelsPerInch
    ) : wxDialog(Parent, wxID_ANY, wxString(LOCALIZED_SELECTACTIVEAREA)),
      m_XLow(NULL),
      m_XHigh(NULL),
      m_YLow(NULL),
      m_YHigh(NULL),
      m_PixelsPerInch(NULL)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // The "body" of this dialog box: 
    // the group box that holds the dimensions of the active area.
    const wxSize  boxSize(168, 144);
    wxStaticBox *box = new wxStaticBox(
        this,
        wxID_ANY,
        wxEmptyString,
        wxDefaultPosition,
        boxSize);
    topLevelSizer->Add(box, 0, wxEXPAND | wxALL, 5);

    // The contents of the main group box are too complex for any of the
    // sizer classes.  Therefore, we must do the layout the old-fashioned
    // way, by specifying x,y coordinates and size (width, height) of each 
    // widget.
    const wxPoint effectPosition(40, 16);
    new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SELECTACTIVEAREA_EFFECT),
        effectPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    // draw the cross-hairs
    const wxPoint verticalLinePosition(effectPosition.x + 105, effectPosition.y + 58);
    const wxSize  verticalLineSize(2, 44);
    new wxStaticLine(
        this,
        wxID_ANY,
        verticalLinePosition,
        verticalLineSize,
        wxLI_VERTICAL);

    const wxPoint horizontalLinePosition(effectPosition.x + 60, effectPosition.y + 78);
    const wxSize  horizontalLineSize(88, 2);
    new wxStaticLine(
        this,
        wxID_ANY,
        horizontalLinePosition,
        horizontalLineSize,
        wxLI_HORIZONTAL);


    const wxPoint yHighTextPosition(effectPosition.x + 32, effectPosition.y + 38);
    new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SELECTACTIVEAREA_YHIGH),
        yHighTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    const wxPoint xLowTextPosition(effectPosition.x + 8, effectPosition.y + 52);
    new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SELECTACTIVEAREA_XLOW),
        xLowTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    const wxPoint xHighTextPosition(effectPosition.x + 150, effectPosition.y + 52);
    new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SELECTACTIVEAREA_XHIGH),
        xHighTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    const wxPoint yLowTextPosition(effectPosition.x + 32, effectPosition.y + 105);
    new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SELECTACTIVEAREA_YLOW),
        yLowTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);


    m_YHigh = new CSmallIntegerCtrl(
        this,
        ID_YHIGH,
        YHigh,
        wxPoint(effectPosition.x + 80, effectPosition.y + 35));

    m_XLow = new CSmallIntegerCtrl(
        this,
        ID_XLOW,
        XLow,
        wxPoint(effectPosition.x + 8, effectPosition.y + 68));

    m_XHigh = new CSmallIntegerCtrl(
        this,
        ID_XHIGH,
        XHigh,
        wxPoint(effectPosition.x + 150, effectPosition.y + 68));

    m_YLow = new CSmallIntegerCtrl(
        this,
        ID_YLOW,
        YLow,
        wxPoint(effectPosition.x + 80, effectPosition.y + 103));



    //
    // the "pixels per inch" row
    //
    wxBoxSizer *pixelsPerInchRow = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *pixelsPerInchLabel = new wxStaticText(
        this,
        wxID_ANY,
		wxString(LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH));
    pixelsPerInchRow->Add(
        pixelsPerInchLabel,
        0,
        wxFIXED_MINSIZE | wxALIGN_CENTER_VERTICAL,
        5);

    m_PixelsPerInch = new CSmallIntegerCtrl(
        this,
        ID_PIXELSPERINCH,
        PixelsPerInch);
    pixelsPerInchRow->Add(
        m_PixelsPerInch,
        0,
        wxFIXED_MINSIZE | wxALIGN_CENTER_VERTICAL | wxALL,
        5);

    topLevelSizer->Add(pixelsPerInchRow, 0, wxALIGN_RIGHT);


    //
    // the row of buttons at the bottom: Reset | Cancel | Ok
    //
    wxBoxSizer *buttonRow = new wxBoxSizer(wxHORIZONTAL);

    wxButton *reset = new wxButton(
        this, 
        ID_RESET, 
		wxString(LOCALIZED_SELECTACTIVEAREA_RESET));
    buttonRow->Add(reset, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *cancel = new wxButton(
        this, 
        wxID_CANCEL, 
		wxString(LOCALIZED_SELECTACTIVEAREA_CANCEL));
    buttonRow->Add(cancel, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *ok = new wxButton(
        this,
        wxID_OK,
		wxString(LOCALIZED_SELECTACTIVEAREA_OK));
    buttonRow->Add(ok, 0, wxALIGN_CENTER | wxALL, 10);

    topLevelSizer->Add(buttonRow, 0, wxALIGN_CENTER | wxALL);



    // make the "Ok" button the default
    ok->SetDefault();

    SetSizer(topLevelSizer);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);

    Fit();
}

void CSetActiveArea::OnReset(wxCommandEvent& Event)
{
    // Restore to defaults -- defined in init_graphics()
    m_XLow->SetIntegerValue(  -BitMapWidth  / 2);
    m_XHigh->SetIntegerValue( +BitMapWidth  / 2);
    m_YLow->SetIntegerValue(  -BitMapHeight / 2);
    m_YHigh->SetIntegerValue( +BitMapHeight / 2);

    m_PixelsPerInch->SetIntegerValue(std::max(BitMapWidth, BitMapHeight) / 8);
}

void
CSetActiveArea::GetActiveArea(
    int & XLow,
    int & XHigh,
    int & YLow,
    int & YHigh
    ) const
{
    XLow  = m_XLow->GetIntegerValue();
    XHigh = m_XHigh->GetIntegerValue();
    YLow  = m_YLow->GetIntegerValue();
    YHigh = m_YHigh->GetIntegerValue();
}

void
CSetActiveArea::GetPixelsPerInch(int & PixelsPerInch) const
{
    PixelsPerInch = m_PixelsPerInch->GetIntegerValue();
}

BEGIN_EVENT_TABLE(CSetActiveArea, wxDialog)
    EVT_BUTTON(ID_RESET,     CSetActiveArea::OnReset)
END_EVENT_TABLE()
