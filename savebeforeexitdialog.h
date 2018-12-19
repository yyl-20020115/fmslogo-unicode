// -*- c++ -*-

#include <wx/dialog.h>

class CSaveBeforeExitDialog : public wxDialog
{
public:
    CSaveBeforeExitDialog(wxWindow *Parent);

    static const int SAVEBEFOREEXIT_Cancel            = 0;
    static const int SAVEBEFOREEXIT_ExitWithoutSaving = 1;
    static const int SAVEBEFOREEXIT_SaveAndExit       = 2;

private:
    // event handlers
    void OnExitWithoutSaving(wxCommandEvent& Event);
    void OnSaveBeforeExit(wxCommandEvent& Event);
    void OnCancel(wxCommandEvent& Event);

    DECLARE_NO_COPY_CLASS(CSaveBeforeExitDialog);
    DECLARE_EVENT_TABLE();
};
