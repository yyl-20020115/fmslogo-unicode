// -*- c++ -*-

#include <wx/frame.h>
#include <wx/fdrepdlg.h>

class  CLogoCodeCtrl;
struct NODE;

class CWorkspaceEditor : public wxFrame
{
public:
    CWorkspaceEditor(
        wxWindow       * Parent,
        const wxString & Title,
        const wxPoint  & Position,
        const wxSize   & Size,
        const wxString & FileName,
        NODE           * EditArguments,
        bool             CheckForErrors,
        bool             OpenToError
        );

#ifndef WX_PURE
    bool TranslateKeyboardShortcut(WXMSG * Message);
#endif

private:

    // Helpers for reading/writing the contents of the editor
    // to and from a file.
    bool Save();
    bool Read(const wxString & FileName = wxEmptyString);
    bool Write(const wxString & FileName = wxEmptyString);
    void SetFileName(const wxString & FileName = wxEmptyString);
    const wxString SelectFile(const wxString & GivenFileName) const;

    // Menu commands event handlers
    void OnExit(wxCommandEvent& Event);
    void OnSaveAndExit(wxCommandEvent& Event);
    void OnSaveToWorkspace(wxCommandEvent& Event);
    void OnPrint(wxCommandEvent& Event);

    void OnUndo(wxCommandEvent& Event);
    void OnUpdateUndo(wxUpdateUIEvent& Event);
    void OnRedo(wxCommandEvent& Event);
    void OnUpdateRedo(wxUpdateUIEvent& Event);
    void OnCut(wxCommandEvent& Event);
    void OnUpdateCut(wxUpdateUIEvent& Event);
    void OnCopy(wxCommandEvent& Event);
    void OnUpdateCopy(wxUpdateUIEvent& Event);
    void OnPaste(wxCommandEvent& Event);
    void OnUpdatePaste(wxUpdateUIEvent& Event);
    void OnDelete(wxCommandEvent& Event);
    void OnUpdateDelete(wxUpdateUIEvent& Event);
    void OnClear(wxCommandEvent& Event);
    void OnUpdateClear(wxUpdateUIEvent& Event);
    void OnSelectAll(wxCommandEvent& Event);
    void OnUpdateSelectAll(wxUpdateUIEvent& Event);

    void OnFind(wxCommandEvent& Event);
    void OnUpdateFind(wxUpdateUIEvent& Event);
    void OnReplace(wxCommandEvent& Event);
    void OnUpdateReplace(wxUpdateUIEvent& Event);
    void OnFindNext(wxCommandEvent& Event);
    void OnUpdateFindNext(wxUpdateUIEvent& Event);

    void OnSetFont(wxCommandEvent& Event);
    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);
    void OnAutoComplete(wxCommandEvent& Event);

    void OnRunSelection(wxCommandEvent& Event);
    void OnUpdateRunSelection(wxUpdateUIEvent& Event);

    void OnFindDialog(wxFindDialogEvent& Event);
    void OnFindDialogNext(wxFindDialogEvent& Event);
    void OnFindDialogReplace(wxFindDialogEvent& Event);
    void OnFindDialogReplaceAll(wxFindDialogEvent& Event);
    void OnFindDialogClose(wxFindDialogEvent& Event);

    void OnHelp(wxCommandEvent& Event);
    void OnHelpEditor(wxCommandEvent& Event);
    void OnHelpTopicSearch(wxCommandEvent& Event);

    void OnClose(wxCloseEvent& Event);
    void OnNavigateNextWindow(wxCommandEvent& Event);

    // Internal helper functions
    bool CanClose();
    bool EndEdit();

    // member variables
    CLogoCodeCtrl       * m_LogoCodeControl;
    wxFindReplaceDialog * m_FindReplaceDialog;
    wxFindReplaceData     m_FindReplaceData;

    // The file that is associated with the editor.
    wxString m_FileName;

    // The arguments that were passed to Edit.
    // This contains the parts of the workspace that are being
    // edited.
    NODE * m_EditArguments;

    // Whether or not the editor should check for errors when
    // saving and re-launch itself on error.
    const bool m_CheckForErrors;

    // If an error was detected when evaluating the workspace.
    bool m_ErrorDetected;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CWorkspaceEditor);
};
