#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
  #include "commanderhistory.h"

  #include <wx/settings.h>
  #include <wx/button.h>
  #include <wx/menu.h>

  #include "commander.h"
  #include "commanderinput.h"
  #include "helputils.h" // for ContextHelp()
  #include "guiutils.h"  // for FillMenu()
  #include "logocore.h"  // for ARRAYSIZE

  #include "localizedstrings.h"
#endif

// Menu IDs
enum
{
   ID_REMOVELINES = wxID_HIGHEST,
};

CCommanderHistory::CCommanderHistory(
    CCommander *    Parent, 
    wxWindowID      Id
    ) : wxRichTextCtrl(
        Parent, 
        Id, 
        wxEmptyString,
        wxDefaultPosition,
        wxDefaultSize,
        wxRE_READONLY | wxWANTS_CHARS)
{
    // The background color should be light gray to indicate that this
    // is a read-only control.
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

    // Nothing that we write to the control should be undoable by
    // the user.
    BeginSuppressUndo();
}

CCommander * CCommanderHistory::GetCommander() const
{
    return static_cast<CCommander*>(GetParent());
}

bool CCommanderHistory::IsCursorAtBottom() const
{
    long caretPosition = GetCaretPosition();
    long lastPosition  = GetLastPosition();

    return lastPosition <= caretPosition + 1;
}

void CCommanderHistory::CopyCurrentLineToCommanderInput() const
{
    wxRichTextLine * line = GetVisibleLineForCaretPosition(GetCaretPosition());
    if (line != NULL)
    {
        wxRichTextParagraph* paragraph = GetBuffer().GetParagraphForLine(line);
        if (paragraph != NULL)
        {
            wxRichTextRange range(paragraph->GetRange());

            const wxString & text = GetRange(range.GetStart(), range.GetEnd());

            GetCommander()->GetInput()->SetText(text);
        }
    }
}

void CCommanderHistory::OnContextHelp(wxCommandEvent& Event)
{
    ContextHelp(GetStringSelection());
}

void CCommanderHistory::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    int  flags      = (Event.ShiftDown()) ? wxRICHTEXT_SHIFT_DOWN : 0;
    bool movedCaret = false;

    if (keyCode == WXK_RETURN)
    {
        // Enter does the same as pressing the Execute button.
        GetCommander()->GiveControlToInputBox();
        GetCommander()->Execute();
    }
    else if (Event.ControlDown() && keyCode == WXK_HOME)
    {
        // CTRL+HOME scrolls to the top
        MoveHome(flags);
        movedCaret = true;
    }
    else if (Event.ControlDown() && keyCode == WXK_END)
    {
        // CTRL+END scrolls to the bottom
        MoveEnd(flags);
        movedCaret = true;
    }
    else if (Event.GetModifiers() == wxMOD_CONTROL && keyCode == 'C')
    {
        // CTRL+C should copy
        Copy();
    }
    else if (Event.GetModifiers() == wxMOD_NONE && keyCode == WXK_F1)
    {
        // F1 displays the help
        ContextHelp(GetStringSelection());
    }
    else if (keyCode == WXK_PAGEUP || keyCode == WXK_NUMPAD_PAGEUP)
    {
        // Page Up moves one screen up
        PageUp(1, flags);
        movedCaret = true;
    }
    else if (keyCode == WXK_PAGEDOWN || keyCode == WXK_NUMPAD_PAGEDOWN)
    {
        // Page Down moves one screen down
        PageDown(1, flags);
        movedCaret = true;
    }
    else if (keyCode == WXK_DOWN || keyCode == WXK_NUMPAD_DOWN)
    {
        // If the caret is already at the bottom, then give focus to edit box.
        if (!HasSelection() && IsCursorAtBottom())
        {
            GetCommander()->GetInput()->SetFocus();
        }
        else if (IsCursorAtBottom())
        {
            // The cursor is already at the bottom
            // so we don't have to move it.
            if (!Event.ControlDown())
            {
                // clear the selection to be consistent with MSWLogo
                SelectNone();
            }
        }
        else
        {
            MoveDown(1, flags);
            movedCaret = true;
        }
    }
    else if (keyCode == WXK_UP || keyCode == WXK_NUMPAD_UP)
    {
        MoveUp(1, flags);
        movedCaret = true;
    }
    else if (keyCode == WXK_LEFT || keyCode == WXK_NUMPAD_LEFT)
    {
        if (Event.ControlDown())
        {
            WordLeft(1, flags);
        }
        else
        {
            MoveLeft(1, flags);
        }
        movedCaret = true;
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
    else if (CCommanderInput::WantsKeyEvent(keyCode))
    {
        GetCommander()->ProcessKeyDownEventAtInputControl(Event);
    }
    else
    {
        // default processing
        Event.Skip();
    }

    if (movedCaret)
    {
        ScrollIntoView(GetCaretPosition(), keyCode);
        CopyCurrentLineToCommanderInput();
    }
}

void CCommanderHistory::ScrollToBottom()
{
    long lastPosition = GetLastPosition();
    ShowPosition(lastPosition);
}

void CCommanderHistory::OnLeftMouseButtonDown(wxMouseEvent& Event)
{
    // Have the base class process the mouse click so that
    // the cursor will be moved to the location of the click.
    OnLeftClick(Event);
    OnLeftUp(Event);

    // On a single click, the contents of the current line
    // gets copied to the commander's input box.
    CopyCurrentLineToCommanderInput();

    // Continue with the default processing for the event.
    Event.Skip();
}

void CCommanderHistory::OnLeftMouseButtonDoubleClick(wxMouseEvent& Event)
{
    // On a double-click, the contents of the current line are executed.
    CopyCurrentLineToCommanderInput();
    GetCommander()->GiveControlToInputBox();
    GetCommander()->Execute();

    // Don't call Event.Skip() because GetCommander()->Execute can run
    // TEXTSCREEN, which would delete this control.  Therefore we cannot
    // safely do any further processing on this control.
}

// Removes the selected lines, which are assumed to be whole lines.
void CCommanderHistory::OnRemoveSelectedLines(wxCommandEvent& Event)
{
    wxTextPos start;
    wxTextPos end;
    GetSelection(&start, &end);

    if (start != 0 &&                            // not the start of the buffer
        GetRange(start - 1, start)[0] != L'\n' && // not on the start of a line
        GetRange(start, start + 1)[0] == L'\n')   // on the end of a line
    {
        // The selection is not at the start of a line, but
        // it includes the newline from the previous line.
        // This is a natural way to select a line if the user
        // moves the mouse up one line, instead of to the left
        // end of the top line.
        // In this case, we want to do what the user expects,
        // which is not to delete the newline character, thereby
        // joining the lines before and after the selection onto
        // the same line, but instead, remove the lines which are
        // selected.
        start++;
    }

    if (GetRange(end - 1, end)[0] != L'\n' && // not immediately after a newline
        GetRange(end, end + 1)[0] == L'\n')   // at a newline
    {
        // The selection does not continue through the
        // end of the line, but it ends at a line.
        // This a natural way for the user to select
        // a line, but deleting the selection will
        // not do what they want.
        end++;
    }
    
    // Fix the selection to be whole lines.
    SetSelection(start, end);
 
    // Remove the selected lines.
    DeleteSelectedContent();
}

void CCommanderHistory::OnUpdateRemoveSelectedLines(wxUpdateUIEvent& Event)
{
    if (!HasSelection())
    {
        Event.Enable(false);
    }
    else
    {
        // Allow the user to remove selected lines only if they have
        // selected whole lines
        wxTextPos start;
        wxTextPos end;
        GetSelection(&start, &end);

        // Check if the selection's start is at the start of the line
        bool selectionStartIsAtStartOfLine;
        if (start == 0                            || // the start of the buffer
            GetRange(start - 1, start)[0] == L'\n' || // the start of a line
            GetRange(start, start + 1)[0] == L'\n')   // at the end of a line
        {
            selectionStartIsAtStartOfLine = true;
        }
        else
        {
            selectionStartIsAtStartOfLine = false;
        }

        // Check if the selection's end is at the end of the line
        bool selectionEndIsAtEndOfLine;
        if (GetRange(end - 1, end)[0] == L'\n' || // just after a newline
            GetRange(end, end + 1)[0] == L'\n')   // at a newline
        {
            selectionEndIsAtEndOfLine = true;
        }
        else
        {
            selectionEndIsAtEndOfLine = false;
        }

        Event.Enable(selectionStartIsAtStartOfLine && selectionEndIsAtEndOfLine);
    }
}

void CCommanderHistory::OnContextMenu(wxContextMenuEvent& Event)
{
    // The history only supports a limited set of editing
    static const MENUITEM contextMenuItems[] = {
        {LOCALIZED_POPUP_COPY,        wxID_COPY},
        {LOCALIZED_POPUP_REMOVELINES, ID_REMOVELINES},
        {LOCALIZED_POPUP_SELECTALL,   wxID_SELECTALL},
        {0},
        {LOCALIZED_POPUP_HELP,        wxID_HELP_INDEX},
    };

    wxMenu menu;
    FillMenu(&menu, contextMenuItems, ARRAYSIZE(contextMenuItems));

    PopupMenu(&menu);
}

void CCommanderHistory::OnSetFocus(wxFocusEvent & Event)
{
    // When the control gets keyboard focus, copy the current selection
    // to the commander input control.
    CopyCurrentLineToCommanderInput();
    Event.Skip();
}

BEGIN_EVENT_TABLE(CCommanderHistory, wxRichTextCtrl)
    EVT_MENU(wxID_HELP_INDEX, CCommanderHistory::OnContextHelp)
    EVT_KEY_DOWN(CCommanderHistory::OnKeyDown)
    EVT_LEFT_DOWN(CCommanderHistory::OnLeftMouseButtonDown)
    EVT_LEFT_DCLICK(CCommanderHistory::OnLeftMouseButtonDoubleClick)
    EVT_CONTEXT_MENU(CCommanderHistory::OnContextMenu)
    EVT_SET_FOCUS(CCommanderHistory::OnSetFocus)
    EVT_MENU(ID_REMOVELINES,      CCommanderHistory::OnRemoveSelectedLines)
    EVT_UPDATE_UI(ID_REMOVELINES, CCommanderHistory::OnUpdateRemoveSelectedLines)
END_EVENT_TABLE()
