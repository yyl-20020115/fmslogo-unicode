// -*- c++ -*-

#ifndef _MINIEDITORTEXTCTRL_H_
#define _MINIEDITORTEXTCTRL_H_

#include "logocodectrl.h"

class wxKeyEvent;

class CMiniEditorTextCtrl : public CLogoCodeCtrl
{
public:
    CMiniEditorTextCtrl(wxWindow *Parent, wxWindowID Id);
    ~CMiniEditorTextCtrl();

private:
    void OnKeyDown(wxKeyEvent& Event);

    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);
    void OnAutoComplete(wxCommandEvent& Event);

    DECLARE_NO_COPY_CLASS(CMiniEditorTextCtrl);
    DECLARE_EVENT_TABLE();
};

#endif // _MINIEDITORTEXTCTRL_H_
