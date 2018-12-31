// -*- c++ -*-
#ifndef _LOGOCODECTRL_H_
#define _LOGOCODECTRL_H_

// When compiled in ANSI mode, neither wxStyledTextCtrl nor wxRichText
// supports multi-byte character sets, such as Simplified Chinese, or
// non-latin scripts, such as Cyrillic (Russian) or Greek.
// As a stop-gap solution until FMSLogo is a pure-Unicode application,
// we provide an alternate implementation that is based on the wxTextCtrl.
#if LOCALE == 2052 // Simplified Chinese
   #define USE_RICHTEXT_CODE_EDITOR
#endif
#if LOCALE == 1049 // Russian
   #define USE_RICHTEXT_CODE_EDITOR
#endif
#if LOCALE == 1032 // Greek
   #define USE_RICHTEXT_CODE_EDITOR
#endif

#include <wx/stc/stc.h>
#include <wx/fdrepdlg.h>
#include <wx/print.h>

#ifdef _WINDOWS
#define USE_RICHTEXT_CODE_EDITOR
#endif

#ifndef USE_RICHTEXT_CODE_EDITOR

class CLogoCodeCtrl : public wxStyledTextCtrl
{
public:
    CLogoCodeCtrl(
        wxWindow       * Parent,
        wxWindowID       Id       = wxID_ANY
        );

    bool SetFont(const wxFont & Font);

    void FindMatchingParen();
    void SelectMatchingParen();
    void AutoComplete();
    bool IsTextSelected();
    wxString GetText() const;
    int GetTextLength() const;
    wxString GetRange(long startPos, long endPos) const;
    void
    Find(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind
        );

    void
    Replace(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    void
    ReplaceAll(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    void Print();

    bool IsDirty() const;
    void ReopenAfterError();

    // Event handlers that a caller might delegate to.
    void OnUndo(wxCommandEvent& Event);
    void OnRedo(wxCommandEvent& Event);
    void OnCut(wxCommandEvent& Event);
    void OnCopy(wxCommandEvent& Event);
    void OnPaste(wxCommandEvent& Event);
    void OnDelete(wxCommandEvent& Event);
    void OnSelectAll(wxCommandEvent& Event);
    void OnHelpTopicSearch(wxCommandEvent& Event);
	void AddTextRaw(const wchar_t *text, int length);

    // Functions to determine if menu items should be enabled.
    bool CanCut();
    bool CanCopy();
    bool CanDelete();
    bool CanSelectAll();
	void ClearAll();
	void EmptyUndoBuffer();
	int  TextHeight(int line);
	void SetCurrentPos(int caret);

    // Event handlers
    void OnUpdateUi(wxStyledTextEvent& event);
    void OnSavePointReached(wxStyledTextEvent& event);
    void OnSavePointLeft(wxStyledTextEvent& event);
    void OnContextMenu(wxContextMenuEvent& Event);
	wxString GetSelectedText();
	void HideSelection(bool hide);
	bool AutoCompActive();
	int GetCurrentLine();
	void SetValue(const wxString &text);
	void SetText(const wxString &text);
	void SetUseHorizontalScrollBar(bool visible);
	void SetSelBackground(bool useSetting, const wxColour &back);
	void SetSelForeground(bool useSetting, const wxColour &fore);
    // Helper functions
    void ScrollCaret();
	int FormatRange(
		bool    doDraw,
		int     startPos,
		int     endPos,
		wxDC *  draw,
		wxDC *  target,
		wxRect  renderRect,
		wxRect  pageRect
	);
	void ReplaceSelection(
		const wxString &   ReplacementString
	);
	bool SearchForString(
		wxFindReplaceFlags WxSearchFlags,
		const wxString &   StringToFind
	);
	void Cancel();
	void SetSavePoint();
	void GotoPos(int caret);
	void SetUndoCollection(bool collectUndo);
    void
    SetScintillaSearchFlags(
        wxFindReplaceFlags WxSearchFlags
        );

    enum SEARCH_OPERATION
    {
        SEARCH_OPERATION_ReplaceAndFind,
        SEARCH_OPERATION_Find,
    };

    void
    DoSearchOperation(
        SEARCH_OPERATION   SearchOperation,
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    void
    FindMatchingParen(
        int & CurrentParenPosition,
        int & MatchingParenPosition
        );

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoCodeCtrl);

    // Whether or not the contents of the editor have changed
    // since they were last synchronized with the file.
    bool m_IsDirty;
};

#else
// Define a CLogoCodeCtrl that works with multi-byte character sets,
// such as Simplified Chinese.

#include <wx/fdrepdlg.h>
#include <wx/textctrl.h>

class CLogoCodeCtrl : public wxTextCtrl
{
public:
    CLogoCodeCtrl(
        wxWindow       * Parent,
        wxWindowID       Id = wxID_ANY
        );

    // wxStyledTextCtrl compatibility
    wxString GetText() const;
    int GetTextLength() const;
    wxString GetTextRange(int startPos, int endPos);
    void ClearAll();
    void EmptyUndoBuffer();
    int  TextHeight(int line);
    void SetCurrentPos(int caret);
    void SetSelBackground(bool useSetting, const wxColour &back);
    void SetSelForeground(bool useSetting, const wxColour &fore);
    wxString GetSelectedText();
    void AutoComplete();
    void SetUseHorizontalScrollBar(bool visible);
    void HideSelection(bool hide);
    bool AutoCompActive();
    int GetCurrentLine();
    void SetText(const wxString &text);
    void AddTextRaw (const wchar_t *text, int length=-1);
    void SetSavePoint();
    void Cancel();
    void SetUndoCollection(bool collectUndo);
    void GotoPos(int caret);
    //void Clear();
    void ReplaceSelection(const wxString &text);
    int
    FormatRange(
        bool    doDraw,
        int     startPos,
        int     endPos,
        wxDC *  draw,
        wxDC *  target,
        wxRect  renderRect,
        wxRect  pageRect 
    );

    // CLogoCodeCtrl compatibility
    void FindMatchingParen();
    void SelectMatchingParen();
    bool IsDirty() const;
    void Print();
    void ReopenAfterError();
    void OnDelete(wxCommandEvent& Event);
    void OnHelpTopicSearch(wxCommandEvent& Event);
    bool CanSelectAll();
    bool CanDelete();
    bool IsTextSelected();

    void
    Find(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind
        );

    void
    Replace(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    void
    ReplaceAll(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind,
        const wxString &   ReplacementString
        );

    // Override wxTextCtrl member functions behave incorrectly with
    // multibyte character sets
    virtual wxString GetRange(long startPos, long endPos) const;
    virtual void SetValue(const wxString &text);

private:

    bool
    SearchForString(
        wxFindReplaceFlags WxSearchFlags,
        const wxString &   StringToFind
        );

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CLogoCodeCtrl);
};

#endif // USE_RICHTEXT_CODE_EDITOR

#endif // _LOGOCODECTRL_H_
