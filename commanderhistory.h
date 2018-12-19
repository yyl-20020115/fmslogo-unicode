#ifndef WX_PRECOMP
  #include "wx/richtext/richtextctrl.h"
#endif

class CCommander;

class CCommanderHistory : public wxRichTextCtrl
{
public:
    CCommanderHistory(CCommander* Parent, wxWindowID Id);
    void ScrollToBottom();

private:
    // Event handlers
    void OnContextHelp(wxCommandEvent& Event);
    void OnKeyDown(wxKeyEvent& Event);
    void OnLeftMouseButtonDown(wxMouseEvent& Event);
    void OnLeftMouseButtonDoubleClick(wxMouseEvent& Event);
    void OnContextMenu(wxContextMenuEvent& Event);
    void OnSetFocus(wxFocusEvent & Event);
    void OnRemoveSelectedLines(wxCommandEvent& Event);
    void OnUpdateRemoveSelectedLines(wxUpdateUIEvent& Event);

    // Private helper functions
    CCommander * GetCommander() const;
    bool IsCursorAtBottom() const;
    void CopyCurrentLineToCommanderInput() const;

    DECLARE_NO_COPY_CLASS(CCommanderHistory);
    DECLARE_EVENT_TABLE();
};
