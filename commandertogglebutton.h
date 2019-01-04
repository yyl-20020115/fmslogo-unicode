#ifndef WX_PRECOMP
    #include <wx/tglbtn.h>
#endif

class CCommander;
class wxKeyEvent;

class CCommanderToggleButton : public wxToggleButton
{
public:

    CCommanderToggleButton(
        CCommander * Parent, 
        wxWindowID   Id,
        const wxString& DownLabel,
        const wxString& UpLabel
        );

    void SetPressedState(bool IsPressed);

private:
    // Event handlers
    void OnKeyDown(wxKeyEvent& Event);

    // Private member variables
    wxString m_DownLabel;
    wxString m_UpLabel;

    DECLARE_NO_COPY_CLASS(CCommanderToggleButton);
    DECLARE_EVENT_TABLE();
};

