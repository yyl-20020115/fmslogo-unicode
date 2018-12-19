#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "commanderbutton.h"
   #include "commander.h"
   #include "commanderinput.h"
   #include "stringadapter.h"
#endif

CCommanderButton::CCommanderButton(
    CCommander *    Parent, 
    wxWindowID      Id, 
    const wchar_t *    Label
    ) :
    wxButton(
        Parent,
        Id,
		wxString(Label),
        wxDefaultPosition,
        wxDefaultSize,
        wxWANTS_CHARS)
{
}

void CCommanderButton::OnKeyDown(wxKeyEvent& Event)
{
    const int keyCode = Event.GetKeyCode();

    if (keyCode == WXK_SPACE)
    {
        // Spaces are transformed into button presses,
        // so we want to handle this event.
        Event.Skip();
    }
    else if (keyCode == WXK_TAB)
    {
        if (Event.ShiftDown())
        {
            // Shift+Tab means navigate backward.
            Navigate(wxNavigationKeyEvent::IsBackward);
        }
        else
        {
            // Tab means navigate forward.
            Navigate(wxNavigationKeyEvent::IsForward);
        }
    }
    else if (keyCode == WXK_RETURN)
    {
        // Convert this into a button press
        wxCommandEvent remappedEvent(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
        ProcessEvent(remappedEvent);
    }
    else if (keyCode == WXK_UP ||
             keyCode == WXK_NUMPAD_UP ||
             CCommanderInput::WantsKeyEvent(keyCode))
    {
        // We don't handle this key stroke.
        // Give focus to the edit box and send the press to it.
        CCommander * commander = static_cast<CCommander*>(GetParent());
        commander->ProcessKeyDownEventAtInputControl(Event);
    }
    else
    {
        // Continue with default event processing.
        Event.Skip();
    }
}


BEGIN_EVENT_TABLE(CCommanderButton, wxButton)
    EVT_KEY_DOWN(CCommanderButton::OnKeyDown)
END_EVENT_TABLE()
