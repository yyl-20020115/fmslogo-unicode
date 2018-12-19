// -*- c++ -*-

#include <wx/dialog.h>

class wxTextCtrl;

class CQuestionBox : public wxDialog
{
public:
    CQuestionBox(
        wxWindow       * Parent,
        const wxString & Title,
        const wxString & Question
        );

    const wxString GetAnswer() const;

private:
    // private member variables
    wxTextCtrl * m_Answer;

    DECLARE_NO_COPY_CLASS(CQuestionBox);
};
