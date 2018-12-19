// -*- c++ -*-

#ifndef _MINIEDITOR_H_
#define _MINIEDITOR_H_

#include <wx/dialog.h>

class CMiniEditorTextCtrl;

class CMiniEditor : public wxDialog
{
public:
    CMiniEditor(wxWindow *Parent, const wchar_t * ToLine);
    ~CMiniEditor();

    const wxString GetProcedureBody() const;

private:
    CMiniEditorTextCtrl * m_TextField;

    DECLARE_NO_COPY_CLASS(CMiniEditor);
};

#endif // _MINIEDITOR_H_
