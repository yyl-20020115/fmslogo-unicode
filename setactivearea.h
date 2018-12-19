// -*- c++ -*-

#include <wx/dialog.h>
#include <wx/textctrl.h>


class CSetActiveArea : public wxDialog
{
public:
    CSetActiveArea(
        wxWindow * Parent,
        int        XLow,
        int        XHigh,
        int        YLow,
        int        YHigh,
        int        PixelsPerInch
        );

    void GetActiveArea(int & XLow, int & XHigh, int & YLow, int & YHigh) const;
    void GetPixelsPerInch(int & PixelsPerInch) const;

private:
    // A thin wrapper on wxTextCtrl for storing the integers.
    class CSmallIntegerCtrl : public wxTextCtrl
    {
    public:
        CSmallIntegerCtrl(
            wxWindow *      Parent,
            wxWindowID      Id,
            int             Value,
            const wxPoint & Position = wxDefaultPosition
            );

        int  GetIntegerValue() const;
        void SetIntegerValue(int NewValue);
    };

    // event handlers
    void OnReset(wxCommandEvent& Event);

    // member variables
    CSmallIntegerCtrl * m_XLow;
    CSmallIntegerCtrl * m_XHigh;
    CSmallIntegerCtrl * m_YLow;
    CSmallIntegerCtrl * m_YHigh;
    CSmallIntegerCtrl * m_PixelsPerInch;

    DECLARE_EVENT_TABLE();
};
