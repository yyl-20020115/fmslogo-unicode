// -*- c++ -*-
#ifndef _LOGOCODECTRL_H_
#define _LOGOCODECTRL_H_

// When compiled in ANSI mode, neither wxStyledTextCtrl nor wxRichText
// supports multi-byte character sets, such as Simplified Chinese, or
// non-latin scripts, such as Cyrillic (Russian) or Greek.
// As a stop-gap solution until FMSLogo is a pure-Unicode application,
// we provide an alternate implementation that is based on the wxTextCtrl.

//NOTICE: ALREADY UNICODE

#include <wx/stc/stc.h>
#include <wx/fdrepdlg.h>
#include <wx/print.h>

class CLogoCodeCtrl : public wxStyledTextCtrl
{
public:
	CLogoCodeCtrl(
		wxWindow       * Parent,
		wxWindowID       Id = wxID_ANY
	);

	bool SetFont(const wxFont & Font);

	void FindMatchingParen();
	void SelectMatchingParen();
	void AutoComplete();
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

	// Functions to determine if menu items should be enabled.
	bool CanCut();
	bool CanCopy();
	bool CanDelete();
	bool CanSelectAll();

	// Event handlers
	void OnUpdateUi(wxStyledTextEvent& event);
	void OnSavePointReached(wxStyledTextEvent& event);
	void OnSavePointLeft(wxStyledTextEvent& event);
	void OnContextMenu(wxContextMenuEvent& Event);


	// Helper functions
	void ScrollCaret();

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


#endif // _LOGOCODECTRL_H_
