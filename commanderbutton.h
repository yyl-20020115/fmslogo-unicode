#ifndef WX_PRECOMP
    #include "wx/button.h"
#endif

class CCommander;

class CCommanderButton : public wxButton
{
public:
    CCommanderButton(CCommander* Parent, wxWindowID Id, const wchar_t * Label);

private:
    // Event Handlers
    void OnKeyDown(wxKeyEvent& Event);

    DECLARE_NO_COPY_CLASS(CCommanderButton);
    DECLARE_EVENT_TABLE();
};
