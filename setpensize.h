// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;
class wxSlider;

class CSetPenSize : public wxDialog
{
    // private class for the window that set the pen size
    class CPenSizeWindow : public wxWindow
    {
    public:
        CPenSizeWindow(
            CSetPenSize   * Parent,
            wxWindowID      Id,
            const wxPoint & Pos,
            const wxSize  & Size,
            int             PenSize
           );

        void SetPenSize(int PenSize);

    private:
        // event handlers
        void OnPaint(wxPaintEvent & event);
        void OnClick(wxMouseEvent & event);

        // member variables
        int m_PenWidth;

        DECLARE_NO_COPY_CLASS(CPenSizeWindow);
        DECLARE_EVENT_TABLE()
    };

public:
    CSetPenSize(
        wxWindow    *   Parent,
        int             InitialPenSize,
        CSetPenSize * & ExternalReference
        );

private:

    // Private helper funtions
    void SetPenSize(int PenSize);

    // Event handlers
    void OnOkButton(wxCommandEvent& event);
    void OnCancelButton(wxCommandEvent& event);
    void OnApplyButton(wxCommandEvent& event);
    void OnSliderUpdated(wxCommandEvent& event);

    // Member variables

    // Even though the slider can hold the pen width, we
    // store it separately in case the initial pen width
    // is one that doesn't fall within the range of the
    // slider.
    int m_PenWidth;

    CSetPenSize    * & m_ExternalReference;
    CPenSizeWindow *   m_ThicknessDisplay;
    wxSlider       *   m_ThicknessSlider;

    DECLARE_NO_COPY_CLASS(CSetPenSize);
    DECLARE_EVENT_TABLE()
};
