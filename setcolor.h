// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;
class wxSlider;

class CSetColor : public wxDialog
{
    // private class for the colored rectangles that can set
    // the color when they are clicked.
    class CColorWindow : public wxWindow
    {
    public:
        CColorWindow(
            CSetColor      * Parent,
            wxWindowID       Id,
            const wxPoint  & Pos,
            const wxSize   & Size,
            const wxColour & Color
           );

        void SetColor(const wxColour & NewColor);

    private:
        // event handlers
        void OnClick(wxMouseEvent & Event);

        DECLARE_NO_COPY_CLASS(CColorWindow);
        DECLARE_EVENT_TABLE()
    };

public:
    CSetColor(
        wxWindow  *     Parent,
        const wchar_t *    WindowTitle,
        const wxColor & InitialColor,
        const wchar_t *    LogoCommand,
        CSetColor * &   ExternalReference
        );

private:
    // event handlers
    void OnOkButton(wxCommandEvent& Event);
    void OnApplyButton(wxCommandEvent& Event);
    void OnCancelButton(wxCommandEvent& Event);
    void OnSliderUpdated(wxCommandEvent& Event);

    // private helper functions
    void SetColor(const wxColor & NewColor);

    // member variables
    CSetColor    * & m_ExternalReference;

    wxSlider     * m_RedSlider;
    wxSlider     * m_GreenSlider;
    wxSlider     * m_BlueSlider;
    CColorWindow * m_SelectedColor;
    const wchar_t   * m_LogoCommand;

    DECLARE_NO_COPY_CLASS(CSetColor);
    DECLARE_EVENT_TABLE()
};
