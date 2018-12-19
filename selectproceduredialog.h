// -*- c++ -*-

#ifndef _SELECTPROCEDUREDIALOG_H_
#define _SELECTPROCEDUREDIALOG_H_

#include <wx/dialog.h>

class CSelectProcedureDialog : public wxDialog
{
public:
    CSelectProcedureDialog(wxWindow *Parent, const wchar_t * Caption);
    ~CSelectProcedureDialog();

    void DoDialog();

protected:
    virtual void OnChoice(struct NODE * Procedures) = 0;

private:
    // event handlers
    void OnAll(wxCommandEvent& Event);
    void OnProcedureTextChange(wxCommandEvent& Event);
    void OnProcedureSelect(wxCommandEvent& Event);
    void OnProcedureDoubleClick(wxCommandEvent& Event);

    // member variables

    // In MSWLogo, the procedure selection was a combobox with
    // a simple listbox.  We use two separate controls because
    // wxWidgets doesn't support this sort of combobox cross-platform
    // and doesn't support a double-click event on the listbox portion.
    class wxTextCtrl * m_SelectedProcedure;
    class wxListBox  * m_ProcedureList;

    DECLARE_NO_COPY_CLASS(CSelectProcedureDialog);
    DECLARE_EVENT_TABLE();
};

#endif // _SELECTPROCEDUREDIALOG_H_
