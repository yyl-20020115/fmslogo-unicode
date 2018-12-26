#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "selectproceduredialog.h"

    #include <wx/listbox.h>
    #include <wx/textctrl.h>
    #include <wx/sizer.h>
    #include <wx/button.h>

    #include "logocore.h"          // for ARRAYSIZE
    #include "wrksp.h"             // for lprocedures
    #include "stringprintednode.h" // for CStringPrintedNode
    #include "logodata.h"          // for make_strnode
    #include "screenwindow.h"      // for TraceOutput
    #include "guiutils.h"
    #include "stringadapter.h"
    #include "localizedstrings.h"
#endif

// Control IDs
enum
{
   ID_PROCEDURETEXT = wxID_HIGHEST,
   ID_PROCEDURELIST,
   ID_ALL,
};

// ----------------------------------------------------------------------------
// CSelectProcedureDialog
// ----------------------------------------------------------------------------

CSelectProcedureDialog::CSelectProcedureDialog(
    wxWindow   * Parent, 
    const wchar_t * Caption
    )
    : wxDialog(
        Parent,
        wxID_ANY,
		wxString(Caption),
        wxDefaultPosition,
        wxDefaultSize, 
        wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE),
      m_SelectedProcedure(NULL),
      m_ProcedureList(NULL)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // add the text input
    m_SelectedProcedure = new wxTextCtrl(this, ID_PROCEDURETEXT);
    topLevelSizer->Add(
        m_SelectedProcedure,
        0,
        wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        15);

    // add the procedures list
    m_ProcedureList = new wxListBox(this, ID_PROCEDURELIST);

    // get procedures
    NODE * proclist = lprocedures(NIL);

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

    topLevelSizer->Add(
        m_ProcedureList,
        0,
        wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        15);

    // add the row of buttons
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    static const MENUITEM buttonInfo[] = {
        {GetResourceString(L"LOCALIZED_SELECTPROCEDURE_OK"),     wxID_OK},
        {GetResourceString(L"LOCALIZED_SELECTPROCEDURE_ALL"),    ID_ALL},
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

        buttonSizer->Add(
            button,
            0,
            wxALIGN_CENTER | wxLEFT | wxRIGHT,
            5);

        // Make the "OK" button the default.
        if (buttonInfo[i].MenuId == wxID_OK)
        {
            button->SetDefault();
        }
    }


    topLevelSizer->Add(
        buttonSizer,
        0,
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT,
        15);

    SetSizer(topLevelSizer);
    topLevelSizer->Fit(this);
}

CSelectProcedureDialog::~CSelectProcedureDialog()
{
}

void CSelectProcedureDialog::DoDialog()
{
    // Show the dialog as a modal box
    int returnCode = ShowModal();
    switch (returnCode)
    {
    case wxID_OK:
    case ID_ALL:

        NODE *arg;
        if (returnCode == ID_ALL)
        {
            // The user clicked ALL get all procedures
            arg = vref(lprocedures(NIL));
        }
        else
        {
            // else find what user selected
            const wxString & procedure = m_SelectedProcedure->GetValue();
            arg = vref(cons_list(make_strnode(/*WXSTRING_TO_STRING*/(procedure))));
        }

        // if something edit/erase it
        if (arg != NIL) 
        {
            // Dispatch to the subclass to process the procedure.
            OnChoice(arg);

            // Release the reference from the vref, above
            deref(arg);
        }

        break;

    default:
        // The user canceled the dialog
        break;
    }
}

void CSelectProcedureDialog::OnAll(wxCommandEvent& Event)
{
    SetReturnCode(ID_ALL);
    Destroy();
}

void CSelectProcedureDialog::OnProcedureTextChange(wxCommandEvent& Event)
{
    // The user changed the text within the text box.
    // To be compatible with the MSWLogo behavior, we scroll the listbox to
    // the location of the typed text.
    const wxString      & newProcedure  = m_SelectedProcedure->GetValue();
    const wxArrayString & allProcedures = m_ProcedureList->GetStrings();

    for (int i = 0; i < static_cast<int>(allProcedures.GetCount()); i++)
    {
        int comparison = allProcedures[i].Cmp(newProcedure);
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

void CSelectProcedureDialog::OnProcedureSelect(wxCommandEvent& Event)
{
    // Copy the selection to the text control
    const wxString & selectedProcedure = m_ProcedureList->GetStringSelection();
    m_SelectedProcedure->ChangeValue(selectedProcedure);
}

void CSelectProcedureDialog::OnProcedureDoubleClick(wxCommandEvent& Event)
{
    // A double-click is the same as pressing OK
    SetReturnCode(wxID_OK);
    Destroy();
}

BEGIN_EVENT_TABLE(CSelectProcedureDialog, wxDialog)
    EVT_BUTTON(ID_ALL,                   CSelectProcedureDialog::OnAll)
    EVT_TEXT(ID_PROCEDURETEXT,           CSelectProcedureDialog::OnProcedureTextChange)
    EVT_LISTBOX(ID_PROCEDURELIST,        CSelectProcedureDialog::OnProcedureSelect)
    EVT_LISTBOX_DCLICK(ID_PROCEDURELIST, CSelectProcedureDialog::OnProcedureDoubleClick)
END_EVENT_TABLE()
