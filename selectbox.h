// -*- c++ -*-

#ifndef _SELECTBOX_H_
#define _SELECTBOX_H_

#include <wx/dialog.h>

class CSelectBox : public wxDialog
{
public:
    CSelectBox(
        wxWindow            * Parent, 
        const wxString      & Caption,
        const wxArrayString & Choices
        );
    ~CSelectBox();

    int DoDialog();

private:
    // event handlers
    void OnDoubleClick(wxCommandEvent & Event);

    // member variables
    class wxListBox  * m_Choices;
    int                m_Selection;

    DECLARE_NO_COPY_CLASS(CSelectBox);
    DECLARE_EVENT_TABLE();
};

#endif // _SELECTBOX_H_
