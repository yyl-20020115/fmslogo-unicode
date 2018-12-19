// -*- c++ -*-
// Copyright (C) 2009 by David Costanzo
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __SELECTSTARTUPINSTRUCTION_H_
#define __SELECTSTARTUPINSTRUCTION_H_

#include <wx/dialog.h>

class wxListBox;
class wxTextCtrl;

class CSelectStartupInstructionDialog : public wxDialog
{
public:
    enum EXPLAINTEXT
    {
        EXPLAINTEXT_None,
        EXPLAINTEXT_StartupNotDefined,
        EXPLAINTEXT_StartupEmpty,
        EXPLAINTEXT_StartupNotList,
    };

    CSelectStartupInstructionDialog(
        wxWindow   * Parent,
        EXPLAINTEXT  ExplainText
        );

    const wxString GetSelectedInstruction() const;

private:
    // event handlers
    void OnProcedureSelect(wxCommandEvent& Event);
    void OnInstructionTextChange(wxCommandEvent& Event);
    void OnUpdateOk(wxUpdateUIEvent& Event);

    // private members
    wxString     m_SelectedInstruction;
    wxTextCtrl * m_InstructionText;
    wxListBox  * m_ProcedureList;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CSelectStartupInstructionDialog);
};

#endif //__SELECTSTARTUPINSTRUCTION_H_
