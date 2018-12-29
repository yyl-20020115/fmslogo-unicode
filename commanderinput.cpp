#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #ifdef __WXMSW__
   #  include <windows.h>  // for keybd_event
   #endif

   #include <wx/clipbrd.h>

   #include "commanderinput.h"

   #include "commander.h"
   #include "logocore.h"  // for ARRAYSIZE
   #include "helputils.h" // for ContextHelp
#endif

enum 
{
    ID_FINDMATCHINGPAREN = wxID_HIGHEST,
    ID_SELECTMATCHINGPAREN,
    ID_AUTOCOMPLETE,
};

CCommanderInput::CCommanderInput(
    CCommander *    Parent, 
    wxWindowID      Id
    ) :
    CLogoCodeCtrl(Parent, Id)
{
    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[10];

    acceleratorEntries[0].Set(wxACCEL_CTRL,      'A', wxID_SELECTALL);
    acceleratorEntries[1].Set(wxACCEL_CTRL,      'Z', wxID_UNDO);
    acceleratorEntries[2].Set(wxACCEL_CTRL,      'Y', wxID_REDO);
    acceleratorEntries[3].Set(wxACCEL_CTRL,      'X', wxID_CUT);
    acceleratorEntries[4].Set(wxACCEL_CTRL,      'C', wxID_COPY);
    acceleratorEntries[5].Set(wxACCEL_CTRL,      'V', wxID_PASTE);
    acceleratorEntries[6].Set(wxACCEL_NORMAL, WXK_F1, wxID_HELP_INDEX);

    // Ctrl+] moves to matching paren
    acceleratorEntries[7].Set(wxACCEL_CTRL, ']', ID_FINDMATCHINGPAREN);

    // Ctrl+Shift+] selects to matching paren
    acceleratorEntries[8].Set(
        wxACCEL_CTRL | wxACCEL_SHIFT,
        ']',
        ID_SELECTMATCHINGPAREN);

    // Ctrl+Space does auto-complete
    acceleratorEntries[9].Set(wxACCEL_CTRL, WXK_SPACE, ID_AUTOCOMPLETE);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);
    SetAcceleratorTable(acceleratorTable);

    SetUseHorizontalScrollBar(false);

    // Show the selection as white on dark blue, as in MSWLogo.
    SetSelForeground(true, *wxWHITE);
    SetSelBackground(true, wxColor(0x00, 0x00, 0x80)); // dark blue
}

bool
CCommanderInput::WantsKeyEvent(
    int KeyCode
    )
{
    // we want the space bar
    if (KeyCode == WXK_SPACE)
    {
        return true;
    }

    // we want the backspace and delete keys
    if (KeyCode == WXK_BACK || KeyCode == WXK_DELETE)
    {
        return true;
    }

    // we want all printing characters
    if (WXK_SPACE <= KeyCode && KeyCode < WXK_START)
    {
        return true;
    }

    // we want the printing characters from the numpad
    if ((WXK_NUMPAD0 <= KeyCode && KeyCode <= WXK_NUMPAD9) ||
        (WXK_NUMPAD_SPACE <= KeyCode && KeyCode <= WXK_NUMPAD_ENTER) ||
        (WXK_NUMPAD_EQUAL <= KeyCode && KeyCode <= WXK_NUMPAD_DIVIDE))
    {
        return true;
    }

    // we want the "hardware-specific keys".
    // I hope these correpond to the windows OEM keys which are usually
    // punctuation and international characters.
    if (WXK_SPECIAL1 <= KeyCode && KeyCode <= WXK_SPECIAL20)
    {
        return true;
    }

    // there are a few navigational keys that we also want.
    if (KeyCode == WXK_NUMPAD_HOME  || 
        KeyCode == WXK_NUMPAD_END   || 
        KeyCode == WXK_NUMPAD_RIGHT || 
        KeyCode == WXK_HOME         || 
        KeyCode == WXK_END          || 
        KeyCode == WXK_RIGHT)
    {
        return true;
    }

    // reject everything else
    return false;
}

void CCommanderInput::SimulateKeyPress(wxKeyEvent & KeyEvent)
{
#ifdef __WXMSW__
    // Emulating a keyboard event is not possible with the current
    // wxStyledCtrl class and it's even difficult with platform-specific
    // calls like SendMessage, as wxStyledCtrl keeps a handle to the
    // real Scintilla window without exposing how to use it.
    //
    // Instead we use an ancient API that still works.
    // This assumes that the caller has set focus to this window.
    BYTE code = static_cast<BYTE>(KeyEvent.GetRawKeyCode());
    ::keybd_event(code, 0, 0 /* key press */, 0);
    ::keybd_event(code, 0, KEYEVENTF_KEYUP, 0);
#else
    wxChar key = KeyEvent.GetUnicodeKey();
    if (KeyEvent.HasModifiers() || key == WXK_NONE || key < 32 || key == 0x7F)
    {
        // This character has no character representation or it's
        // control key, or there's a modifier (like Ctrl being down)
        // that makes it not intended to be treated literally.
        // In short, it's some kind of navigation or selection
        // keystroke, such as Ctrl+Shift+Right to extend the selection.
        // Forward this to Scintilla to be handled correctly.
//#define USE_RICHTEXT_CODE_EDITOR
#ifndef USE_RICHTEXT_CODE_EDITOR
        wxStyledTextCtrl::OnKeyDown(KeyEvent);
#else
        //TODO:how?
        //wxTextCtrl::OnKeyDown(KeyEvent);
#endif
        // Ctrl+A doesn't select all, possibly because we disable all
        // built-in Scintilla acelerators.  Therefore, we must have
        // a special case for it.
        if (key == 'A' || KeyEvent.GetModifiers() == wxMOD_CONTROL)
        {
            SelectAll();
        }
    }
    else
    {
        // Some normal text is being typed.  Figure out what it is.
        wxString character(key);
        if (KeyEvent.ShiftDown())
        {
            // TODO: handle remapping like Shift+; to :
        }
        else
        {
            // All key event are interpreted as capital letters.
            // Since the Shift key is NOT pressed, we need to make
            // the character lowercase.
            character.MakeLower();
        }

        // Insert tbe character at the insertion point.
        WriteText(character);
    }
#endif
}

void CCommanderInput::SetText(const wxString & NewText)
{
    CLogoCodeCtrl::SetText(NewText);
    SetSelection(0, 0);
    ShowPosition(0);
    EmptyUndoBuffer();
}

void CCommanderInput::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    switch (keyCode)
    {
    case WXK_UP:
    case WXK_NUMPAD_UP:
        if (AutoCompActive())
        {
            // Send the Up arrow to the autocomplete popup.
            Event.Skip();
        }
        else
        {
            if (GetCurrentLine() == 0)
            {
                // The caret is already at the first line of the input control,
                // so move up into the history box.
                static_cast<CCommander*>(GetParent())->GiveControlToHistoryBox();
            }
            else
            {
                // Move the caret one line within the input control.
                // Normally, you cannot have more than one line of text
                // within this control, but you can if you paste multiple
                // lines.
                Event.Skip();
            }
        }
        break;

    case WXK_TAB:
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
        break;

    case WXK_RETURN:
    case WXK_NUMPAD_ENTER:
        if (AutoCompActive())
        {
            // Send the Enter to the autocomplete popup.
            Event.Skip();
        }
        else
        {
            static_cast<CCommander*>(GetParent())->Execute();
        }
        break;

    default:
        // default processing
        Event.Skip();
        break;
    }
}

void CCommanderInput::OnChar(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();
    switch (keyCode)
    {
    case WXK_RETURN:
    case WXK_NUMPAD_ENTER:
        // Do nothing -- we already handled this on OnKeyDown().
        // According to the wxWidgets documentation, this isn't supposed to
        // generate a call to OnChar() because we didn't call Event.Skip(),
        // but it does.  To prevent a carriage return from being written to
        // the input field, we need to ignore this event.
        break;

    default:
        // default processing
        Event.Skip();
        break;
    }
}

void CCommanderInput::OnFindMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    FindMatchingParen();
}

void CCommanderInput::OnSelectMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    SelectMatchingParen();
}

void CCommanderInput::OnAutoComplete(wxCommandEvent& WXUNUSED(Event))
{
    AutoComplete();
}

void CCommanderInput::OnKillFocus(wxFocusEvent & Event)
{
    // When the control loses focus, the selection should become invisible.
    HideSelection(true);
    Event.Skip();
}

void CCommanderInput::OnSetFocus(wxFocusEvent & Event)
{
    // When the control gets focus, the selection should become visible.
    HideSelection(false);
    Event.Skip();
}

#if defined USE_RICHTEXT_CODE_EDITOR

void CCommanderInput::Paste()
{
    // This overrides the default paste handler to strip out
    // and trailing newlines, which are present when copying
    // and pasting code snippets from the manual or the Web.
    // Because the commander input is only one line tall, if we
    // included the trailing newline, then the user would see a
    // blank line after the pasting and it wouldn't be clear that
    // the contents of the clipboard was pasted.

    // A more comprehensive solution would be to increase the size
    // of the commander input to show everything that was pasted,
    // or at least up to four lines.
    if (wxTheClipboard->Open())
    {
        // Only special processing for text.
        if (wxTheClipboard->IsSupported(wxDF_TEXT))
        {
            // Get the text that is being pasted.
            wxTextDataObject data;
            wxTheClipboard->GetData(data);
            wxString pastedText = data.GetText();

            // Determine where trailing newlines (if any) start.
            size_t pastedTextLength = pastedText.length();
            int lastIndex;
            for (lastIndex = pastedTextLength - 1;
                 0 <= lastIndex;
                 lastIndex--)
            {
                if (pastedText[lastIndex] == L'\\')
                {
                    // We shouldn't remove a quoted newline,
                    // so put it back.
                    lastIndex++;
                    break;
                }
                else if (pastedText[lastIndex] != L'\n' &&
                         pastedText[lastIndex] != L'\r')
                {
                    // We have found a trailing character
                    // that isn't a newline, so we're done.
                    break;
                }
            }

            // Strip the trailing newlines
            pastedText = pastedText.Truncate(lastIndex + 1);

            // Perform the paste.
            ReplaceSelection(pastedText);
        }

        wxTheClipboard->Close();
    }
}

#elif wxCHECK_VERSION(3, 1, 0)
// wxStyledTextCtrl on wxWidgets 3.1.0 or greater has a special
// hook for modifying pasted text.  If it exists, we use it instead
// of override the entire paste.

void CCommanderInput::OnClipboardPaste(wxStyledTextEvent& Event)
{
    // This overrides the default clipboard paste handler to
    // strip out any trailing newlines, which may be present when
    // copying and pasting code snippets from the manual or the Web.
    // Because the commander input is only one line tall, if we
    // included the trailing newline, then the user would see a
    // blank line after the pasting and it wouldn't be clear that
    // the contents of the clipboard was pasted.

    // A more comprehensive solution would be to increase the size
    // of the commander input to show everything that was pasted,
    // or at least up to four lines.

    // Determine where trailing newlines (if any) start, starting
    // at the end of the string and moving toward the beginning while
    // we see newlines.
    wxString pastedText = Event.GetString();
    int lastIndex;
    for (lastIndex = pastedText.length() - 1; 0 <= lastIndex; lastIndex--)
    {
        if (pastedText[lastIndex] == L'\\')
        {
            // We shouldn't remove a quoted newline,
            // so put it back.
            lastIndex++;
            break;
        }
        else if (pastedText[lastIndex] != L'\n' &&
                 pastedText[lastIndex] != L'\r')
        {
            // We have found a trailing character
            // that isn't a newline, so we're done.
            break;
        }
    }

    // Strip the trailing newlines
    pastedText.Truncate(lastIndex + 1);

    // Perform the replacement
    Event.SetString(pastedText);
}

#else

void CCommanderInput::OnPaste(wxCommandEvent& Event)
{
    // This overrides the default paste handler to strip out
    // and trailing newlines, which are present when copying
    // and pasting code snippets from the manual or the Web.
    // Because the commander input is only one line tall, if we
    // included the trailing newline, then the user would see a
    // blank line after the pasting and it wouldn't be clear that
    // the contents of the clipboard was pasted.

    // A more comprehensive solution would be to increase the size
    // of the commander input to show everything that was pasted,
    // or at least up to four lines.

    bool handledEvent = false;
    if (wxTheClipboard->Open())
    {
        // Only special processing for text.
        if (wxTheClipboard->IsSupported(wxDF_TEXT))
        {
            // Get the text that is being pasted.
            wxTextDataObject data;
            wxTheClipboard->GetData(data);
            wxString pastedText = data.GetText();

            // Determine where trailing newlines (if any) start.
            size_t pastedTextLength = pastedText.length();
            int lastIndex;
            for (lastIndex = pastedTextLength - 1;
                 0 <= lastIndex;
                 lastIndex--)
            {
                if (pastedText[lastIndex] == L'\\')
                {
                    // We shouldn't remove a quoted newline,
                    // so put it back.
                    lastIndex++;
                    break;
                }
                else if (pastedText[lastIndex] != L'\n' &&
                         pastedText[lastIndex] != L'\r')
                {
                    // We have found a trailing character
                    // that isn't a newline, so we're done.
                    break;
                }
            }

            // Strip the trailing newlines
            pastedText = pastedText.Truncate(lastIndex + 1);

            // Perform the paste.
            ReplaceSelection(pastedText);
            handledEvent = true;
        }

        wxTheClipboard->Close();
    }
   
    if (!handledEvent)
    {
        // Standard processing.
        Event.Skip();
    }
}

#endif

BEGIN_EVENT_TABLE(CCommanderInput, CLogoCodeCtrl)
    EVT_KEY_DOWN(CCommanderInput::OnKeyDown)
    EVT_CHAR(CCommanderInput::OnChar)
    EVT_SET_FOCUS(CCommanderInput::OnSetFocus)
    EVT_KILL_FOCUS(CCommanderInput::OnKillFocus)
    EVT_MENU(ID_FINDMATCHINGPAREN,   CCommanderInput::OnFindMatchingParen)
    EVT_MENU(ID_SELECTMATCHINGPAREN, CCommanderInput::OnSelectMatchingParen)
    EVT_MENU(ID_AUTOCOMPLETE,        CCommanderInput::OnAutoComplete)
#ifndef USE_RICHTEXT_CODE_EDITOR
  #if wxCHECK_VERSION(3, 1, 0)
    EVT_STC_CLIPBOARD_PASTE(wxID_ANY, CCommanderInput::OnClipboardPaste)
  #else
    EVT_MENU(wxID_PASTE,              CCommanderInput::OnPaste)
  #endif
#endif
END_EVENT_TABLE()
