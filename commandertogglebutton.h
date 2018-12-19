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
        const wchar_t * DownLabel,
        const wchar_t * UpLabel
        );

    void SetPressedState(bool IsPressed);

private:
    // Event handlers
    void OnKeyDown(wxKeyEvent& Event);

    // Private member variables
    const wchar_t * m_DownLabel;
    const wchar_t * m_UpLabel;

    DECLARE_NO_COPY_CLASS(CCommanderToggleButton);
    DECLARE_EVENT_TABLE();
};

