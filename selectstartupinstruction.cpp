/*
*  Copyright (C) 2011 by David Costanzo
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "selectstartupinstruction.h"

    #include <wx/listbox.h>
    #include <wx/textctrl.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/stattext.h>

    #include "localizedstrings.h"
    #include "logocore.h"
    #include "guiutils.h"
    #include "wrksp.h"
    #include "stringprintednode.h"
    #include "stringadapter.h"
#endif

enum
{
   ID_INSTRUCTIONTEXT = wxID_HIGHEST,
   ID_PROCEDURELIST,
};

CSelectStartupInstructionDialog::CSelectStartupInstructionDialog(
    wxWindow    * Parent,
    EXPLAINTEXT   ExplainText
    )
    : wxDialog(
        Parent,
        wxID_ANY,
		GetResourceString(L"LOCALIZED_SELECTSTARTUP_CAPTION")),
      m_InstructionText(NULL),
      m_ProcedureList(NULL)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // Add the explain text
    const wchar_t * explainText = L"";

    switch (ExplainText)
    {
    case EXPLAINTEXT_StartupNotDefined:
        explainText = GetResourceString(L"LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED");
        break;

    case EXPLAINTEXT_StartupEmpty:
        explainText = GetResourceString(L"LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY");
        break;

    case EXPLAINTEXT_StartupNotList:
        explainText = GetResourceString(L"LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST");
        break;

    default:
        assert(0); // can't happen
    }

    wxStaticText * explainTextCtrl = new wxStaticText(
        this,
        wxID_ANY,
		wxString(explainText),
        wxDefaultPosition,
        wxDefaultSize);

    topLevelSizer->Add(
        explainTextCtrl,
        0,
        wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        5);

    // Add the text input
    m_InstructionText = new wxTextCtrl(this, ID_INSTRUCTIONTEXT);
    topLevelSizer->Add(
        m_InstructionText,
        0,
        wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        5);

    // add the procedures list
    m_ProcedureList = new wxListBox(this, ID_PROCEDURELIST);

    // get procedures
    NODE * proclist = lprocedures(NIL);
    if (proclist != NIL)
    {
        // put the name of each procedure into the list box
        for (NODE* proclist_node = proclist;
             proclist_node != NIL;
             proclist_node = cdr(proclist_node))
        {
            // REVISIT: the procedure name should be useable
            // as-is without further conversion.
            CStringPrintedNode procedureName(car(proclist_node));
            m_ProcedureList->Append(procedureName);
        }

        gcref(proclist);
    }
    else
    {
        // There are no procedures
        m_ProcedureList->Append(GetResourceString(L"LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED"));
        m_ProcedureList->Disable();
    }

    topLevelSizer->Add(
        m_ProcedureList,
        0,
        wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        5);

    // add the row of buttons
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    static const MENUITEM buttonInfo[] = {
        {GetResourceString(L"LOCALIZED_SELECTPROCEDURE_OK"),     wxID_OK},
        {GetResourceString(L"LOCALIZED_SELECTPROCEDURE_CANCEL"), wxID_CANCEL},
    };


    // HACK: 
    // Create and destroy each button to get the width and height
    // of the "exact fit" size of the largest button.  We will
    // use this size when we recreate the buttons later.
    // Ideally, we'd just be able to resize the buttons, but I haven't
    // figured out how to do that.
    int maxHeight = 0;
    int maxWidth  = 0;
    for (size_t i = 0; i < ARRAYSIZE(buttonInfo); i++)
    {
        wxButton * button = new wxButton(
            this,
            wxID_ANY,
			wxString(buttonInfo[i].MenuText),
            wxDefaultPosition,
            wxDefaultSize,
            wxBU_EXACTFIT);

        if (maxWidth < button->GetBestSize().GetWidth())
        {
            maxWidth = button->GetBestSize().GetWidth();
        }

        if (maxHeight < button->GetBestSize().GetHeight())
        {
            maxHeight = button->GetBestSize().GetHeight();
        }

        delete button;
    }

    // create all of the buttons to be the same size.
    const wxSize buttonSize(maxWidth, maxHeight);
    for (size_t i = 0; i < ARRAYSIZE(buttonInfo); i++)
    {
        wxButton * button = new wxButton(
            this,
            buttonInfo[i].MenuId,
			wxString(buttonInfo[i].MenuText),
            wxDefaultPosition,
            buttonSize);

        buttonSizer->Add(button, 0, wxLEFT, 10);

        // Make the "OK" button the default.
        if (buttonInfo[i].MenuId == wxID_OK)
        {
            button->SetDefault();
        }
    }

    topLevelSizer->Add(
        buttonSizer,
        0,
        wxALIGN_RIGHT | wxALL,
        5);

    SetSizer(topLevelSizer);
    topLevelSizer->Fit(this);
}

const wxString CSelectStartupInstructionDialog::GetSelectedInstruction() const
{
    return m_SelectedInstruction;
}

void CSelectStartupInstructionDialog::OnInstructionTextChange(wxCommandEvent& Event)
{
    // Save the new text
    m_SelectedInstruction = m_InstructionText->GetValue();

    // The user changed the text within the text box.
    // Scroll the listbox to the location of the typed text.
    const wxArrayString & allProcedures = m_ProcedureList->GetStrings();

    for (int i = 0; i < static_cast<int>(allProcedures.GetCount()); i++)
    {
        int comparison = allProcedures[i].Cmp(m_SelectedInstruction);
        if (0 <= comparison)
        {
            // We have found the item in the list box that is greater than
            // what the user has typed.  We want to scroll the listbox so
            // that this item is at the top.
            m_ProcedureList->SetFirstItem(i);

            if (comparison == 0)
            {
                // The user has typed a perfect match for
                // this item.  Select it.
                m_ProcedureList->Select(i);
            }
            else
            {
                // The text doesn't match any item.
                // Make sure that none are selected.
                m_ProcedureList->Select(wxNOT_FOUND);
            }
            break;
        }
    }
}

void CSelectStartupInstructionDialog::OnProcedureSelect(wxCommandEvent& Event)
{
    // Copy the selection to the our saved string
    m_SelectedInstruction = m_ProcedureList->GetStringSelection();

    // Copy the selection to the text control
    m_InstructionText->ChangeValue(m_SelectedInstruction);
}

void CSelectStartupInstructionDialog::OnUpdateOk(wxUpdateUIEvent& Event)
{
    // Don't enable the OK button unless a startup instruction
    // list has been selected.
    Event.Enable(!m_SelectedInstruction.IsEmpty());
}

BEGIN_EVENT_TABLE(CSelectStartupInstructionDialog, wxDialog)
    EVT_TEXT(ID_INSTRUCTIONTEXT,   CSelectStartupInstructionDialog::OnInstructionTextChange)
    EVT_LISTBOX(ID_PROCEDURELIST,  CSelectStartupInstructionDialog::OnProcedureSelect)
    EVT_UPDATE_UI(wxID_OK,         CSelectStartupInstructionDialog::OnUpdateOk)
END_EVENT_TABLE()
