#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
  #ifdef __WXMSW__
  #  include <windows.h>  // for LOGFONT
  #endif

  #include "commander.h"

  #include <wx/msgdlg.h>
  #include <wx/sizer.h>
  #include <wx/defs.h>
  #include <wx/fontdlg.h>
  #include <wx/richtext/richtextctrl.h>

  #include "FMSLogo.h"
  #include "mainframe.h"
  #include "statusdialog.h"
  #include "workspaceeditor.h"
  #include "localizedstrings.h"
  #include "utils.h"
  #include "logocore.h"
  #include "logodata.h"
  #include "commanderbutton.h"
  #include "commandertogglebutton.h"
  #include "commanderinput.h"
  #include "commanderhistory.h"
  #include "dynamicbuffer.h"
  #include "parse.h"
  #include "error.h"
  #include "eval.h"
  #include "graphics.h"
  #include "graphwin.h"
  #include "status.h"
  #include "fontutils.h"
  #include "mmwind.h"
  #include "print.h" // for MESSAGETYPE
  #include "stringadapter.h"
#include "files.h"
#endif
extern wxString cap_strnzcpy(wxString text);

bool g_IsOkayToUseCommanderWindow = true;

// holds the history
static CDynamicBuffer g_HistoryBuffer;

// Menu IDs
enum FMSLogoMenuIDs
{
   ID_COMMANDER_HALT = wxID_HIGHEST+32,
   ID_COMMANDER_TRACE,
   ID_COMMANDER_PAUSE,
   ID_COMMANDER_STATUS,
   ID_COMMANDER_STEP,
   ID_COMMANDER_UNSTEP,
   ID_COMMANDER_RESET,
   ID_COMMANDER_EXECUTE,
   ID_COMMANDER_EDALL,
   ID_COMMANDER_HISTORY,
   ID_COMMANDER_NEXTINSTRUCTION,

   ID_COMMANDER_NEXT_WINDOW,
};

// ----------------------------------------------------------------------------
// CCommander
// ----------------------------------------------------------------------------

CCommander::CCommander(wxWindow *Parent)
    : wxPanel(Parent, wxID_ANY)
{
    m_History = new CCommanderHistory(this, ID_COMMANDER_HISTORY);

    m_NextInstruction = new CCommanderInput(this, ID_COMMANDER_NEXTINSTRUCTION);

    m_HaltButton = new CCommanderButton(
        this,
        ID_COMMANDER_HALT,
        GetResourceString(L"LOCALIZED_COMMANDER_HALT"));

    m_TraceButton = new CCommanderToggleButton(
        this,
        ID_COMMANDER_TRACE,
		GetResourceString(L"LOCALIZED_COMMANDER_NOTRACE"),
		GetResourceString(L"LOCALIZED_COMMANDER_TRACE"));

    m_PauseButton = new CCommanderButton(
        this,
        ID_COMMANDER_PAUSE,
		GetResourceString(L"LOCALIZED_COMMANDER_PAUSE"));

    m_StatusButton = new CCommanderToggleButton(
        this,
        ID_COMMANDER_STATUS,
		GetResourceString(L"LOCALIZED_COMMANDER_NOSTATUS"),
        GetResourceString(L"LOCALIZED_COMMANDER_STATUS"));

    m_StepButton = new CCommanderToggleButton(
        this,
        ID_COMMANDER_STEP,
        GetResourceString(L"LOCALIZED_COMMANDER_UNSTEP"),
		GetResourceString(L"LOCALIZED_COMMANDER_STEP"));

    m_ResetButton = new CCommanderButton(
        this,
        ID_COMMANDER_RESET,
		GetResourceString(L"LOCALIZED_COMMANDER_RESET"));

    m_ExecuteButton = new CCommanderButton(
        this,
        ID_COMMANDER_EXECUTE,
		GetResourceString(L"LOCALIZED_COMMANDER_EXECUTE"));

    m_EdallButton = new CCommanderButton(
        this,
        ID_COMMANDER_EDALL,
		GetResourceString(L"LOCALIZED_COMMANDER_EDALL"));

    // set the button font to be 10 points
    wxFont buttonFont = m_HaltButton->GetFont();
    buttonFont.SetPointSize(10);

    m_HaltButton->SetFont(buttonFont);
    m_TraceButton->SetFont(buttonFont);
    m_PauseButton->SetFont(buttonFont);
    m_StatusButton->SetFont(buttonFont);
    m_StepButton->SetFont(buttonFont);
    m_ResetButton->SetFont(buttonFont);
    m_ExecuteButton->SetFont(buttonFont);
    m_EdallButton->SetFont(buttonFont);

    // Pick a good size for the buttons.
    // The rest will be re-sized to match it
    m_TraceButton->SetSize(0, 0, 100, 20);

    m_NextInstructionHeight = 10 * BaseUnitsy / 8;
    m_ButtonWidth           = 34 * BaseUnitsx / 4;

    // set the font to whatever is defined in the configuraton
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE); // default to using a fixed-width font
    GetConfigurationFont(L"CommanderFont", font);
    UpdateFont(font);


    // calculate the desired width for the buttons
    // by iterating through all labels that we put on buttons 
    // and figuring out the length of the longest one.
    wxString buttonLabels[] = {
        GetResourceString(L"LOCALIZED_COMMANDER_HALT"),
		GetResourceString(L"LOCALIZED_COMMANDER_TRACE"),
		GetResourceString(L"LOCALIZED_COMMANDER_NOTRACE"),
		GetResourceString(L"LOCALIZED_COMMANDER_PAUSE"),
		GetResourceString(L"LOCALIZED_COMMANDER_STATUS"),
		GetResourceString(L"LOCALIZED_COMMANDER_NOSTATUS"),
		GetResourceString(L"LOCALIZED_COMMANDER_STEP"),
		GetResourceString(L"LOCALIZED_COMMANDER_UNSTEP"),
		GetResourceString(L"LOCALIZED_COMMANDER_RESET"),
		GetResourceString(L"LOCALIZED_COMMANDER_EXECUTE"),
		GetResourceString(L"LOCALIZED_COMMANDER_EDALL"),
    };

    int largestWidth  = 0;
    int largestHeight = 0;

    for (size_t i = 0; i < ARRAYSIZE(buttonLabels); i++)
    {
        int  buttonWidth;
        int  buttonHeight;

        m_EdallButton->GetTextExtent(
			wxString(buttonLabels[i]),
            &buttonWidth,
            &buttonHeight);
        if (largestWidth < buttonWidth)
        {
            largestWidth = buttonWidth;
        }

        if (largestHeight < buttonHeight)
        {
            largestHeight = buttonHeight;
        }
    }

    m_ButtonWidth  = largestWidth  + 20;
    m_ButtonHeight = largestHeight + 8;

    // Update the state of all the toggle buttons.
    UpdateStepButtonState();
    UpdateStatusButtonState();
    UpdateTraceButtonState();

    // Disable/Enable the Halt+Pause buttons depending on execution.
    UpdateHaltButtonState();
    UpdatePauseButtonState();

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[1];

    // Ctrl+D is identical to EDALL
    acceleratorEntries[0].Set(wxACCEL_CTRL, 'D', ID_COMMANDER_EDALL);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);

    SetAcceleratorTable(acceleratorTable);
}

CCommander::~CCommander()
{
}

void CCommander::ChooseNewFont()
{
    wxFontDialog fontChooser;

    // Disable color selection, since we don't honor it.
    fontChooser.GetFontData().EnableEffects(false);

    // Seed the font picker with the current configuration
    wxFont currentCommanderFont;
    currentCommanderFont.SetFamily(wxFONTFAMILY_TELETYPE);
    GetConfigurationFont(L"CommanderFont", currentCommanderFont);
    fontChooser.GetFontData().SetInitialFont(currentCommanderFont);

    // Show the font picker
    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // Get the font which the user selected.
        const wxFont & newCommanderFont = fontChooser.GetFontData().GetChosenFont();

        // Save the new font preference to persistent storage.
        SetConfigurationFont(L"CommanderFont", newCommanderFont);

        // Update the font which the UI is using.
        UpdateFont(newCommanderFont);

        // Resize the UI controls to account for the new font.
        RecalculateLayout();
        Refresh(true);
    }
}

void CCommander::UpdateStepButtonState()
{
    m_StepButton->SetPressedState(stepflag);
}


CCommanderHistory * CCommander::GetHistory()
{
    return m_History;
}

CCommanderInput * CCommander::GetInput()
{
    return m_NextInstruction;
}

void CCommander::UpdateTraceButtonState()
{
    m_TraceButton->SetPressedState(traceflag);
}

void CCommander::UpdateStatusButtonState()
{
    bool isShowing = CFmsLogo::GetMainFrame()->StatusDialogIsShowing();
    m_StatusButton->SetPressedState(isShowing);
}

void CCommander::UpdateHaltButtonState()
{
    m_HaltButton->Enable(is_executing());
}

void CCommander::UpdatePauseButtonState()
{
    m_PauseButton->Enable(is_executing());
}

void CCommander::Halt()
{
    // End all timers that could have been started
    // by a call to SETTIMER.
    halt_all_timers();

    // Set a flag so that the Logo engine will halt
    // when it has finished processing the current
    // instruction.
    if (is_executing())
    {
        IsTimeToHalt = true;
    }
}

void CCommander::OnHaltButton(wxCommandEvent& WXUNUSED(Event))
{
    Halt();
	this->UpdateHaltButtonState();
	this->UpdateStepButtonState();
	this->UpdatePauseButtonState();
}

void CCommander::OnTraceButton(wxCommandEvent& WXUNUSED(Event))
{
    // toggle trace state 
    traceflag = !traceflag;
    UpdateTraceButtonState();
}

void CCommander::OnPauseButton(wxCommandEvent& WXUNUSED(Event))
{
    // If it's ok to halt then it's ok to pause.
    if (is_executing())
    {
        IsTimeToPause = true;
    }
}

void CCommander::OnStatusButton(wxCommandEvent& WXUNUSED(Event))
{
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();
    if (mainFrame->StatusDialogIsShowing())
    {
        // the status dialog is currently showing, so we want to hide it.
        mainFrame->HideStatus();
    }
    else
    {
        // the status dialog is not showing, so we want to show it.
        mainFrame->ShowStatus();
        m_StatusButton->SetFocus();
    }
    UpdateStatusButtonState();
}

void CCommander::ToggleStep()
{
    // Toggle the single-step state
    stepflag = !stepflag;
    UpdateStepButtonState();
}

void CCommander::OnStepButton(wxCommandEvent& WXUNUSED(Event))
{
    ToggleStep();
}

void CCommander::OnResetButton(wxCommandEvent& WXUNUSED(Event))
{
	//call halt first to stop program
	this->Halt();

	//NOTICE: for requirement to reset almost everythong about drawing,
	//we added draw command (like in PCLogo) into logolib
	//and we call it here
    RunLogoInstructionFromGui(L"draw");
}

void clearcombobox()
{
    // clear the recall box
    CCommanderHistory * commanderHistory = CFmsLogo::GetMainFrame()->GetCommander()->GetHistory();

    commanderHistory->Clear();
}

// Appends Text to the end of the what is in the Commander's Recall box.
void putcombobox(const wchar_t *Text, MESSAGETYPE MessageType)
{
    // Check that the commander's history field is ready for input.
    if (g_IsOkayToUseCommanderWindow)
    {
        CCommanderHistory * commanderHistory = CFmsLogo::GetMainFrame()->GetCommander()->m_History;

        // Output to commander history.
        // Don't append the empty string because that results in appending
        // a newline.  When combined with the newline that gets added
        // below, this would have the side-effect of inserting two lines.
        if (Text != NULL && Text[0] != L'\0')
        {
            if (MessageType == MESSAGETYPE_Error)
            {
                commanderHistory->SetInsertionPointEnd();
                commanderHistory->BeginTextColour(*wxRED);
                commanderHistory->WriteText(wxString(Text));
                commanderHistory->EndTextColour();
            }
            else
            {
                commanderHistory->SetInsertionPointEnd();
                commanderHistory->BeginTextColour(*wxBLACK);
                commanderHistory->WriteText(wxString(Text));
                commanderHistory->EndTextColour();
            }
        }

        // Append the newline
        commanderHistory->AppendText(wxString(L"\n"));

        // Scroll to the bottom to show what was just added.
        commanderHistory->ScrollToBottom();
    }
}


// Process a Logo instruction, as it is processed by the GUI when you click
// on the "Execute" button.  This can be used by other UI elements, such as
// the "Reset" button, to teach the user what a UI element is doing.
void
RunLogoInstructionFromGui(
    const wchar_t * LogoInstruction
    )
{
    if (LogoInstruction[0] != L'\0')
    {
        // The instruction is real.  Do something with it.

        // copy to list box for command recall
        putcombobox(LogoInstruction, MESSAGETYPE_Normal);

        DribbleWriteLine(LogoInstruction);

        // reset erract loop error history
        clear_is_running_erract_flag();

        // reset evaluation counter (call counter) and execute
        eval_count = 0;
        update_status_evals();

        vector_count = 0;
        update_status_vectors();

        do_execution(LogoInstruction);
    }
}

void CCommander::Execute()
{
    // Read what's in the input control.
    wxString logoInstruction(m_NextInstruction->GetText());

    // Clear the input control, now that we have read its contents.
    m_NextInstruction->ClearAll();

    // Block Undo from working across executions.  To get back to a
    // previously executed instruction, the user should use the commander
    // history.
    m_NextInstruction->EmptyUndoBuffer();

    // In the event that multiple lines were pasted into the input control,
    // we must replace CRLF with LF, since that's what do_execution expects.
    logoInstruction.Replace(wxString(L"\r\n"), wxString(L"\n"));

    // BUG: This can modify the contents of wxString's buffer
	//RunLogoInstructionFromGui(const_cast<wchar_t*>(WXSTRING_TO_STRING(logoInstruction)));
	RunLogoInstructionFromGui(logoInstruction);
}

void CCommander::OnExecuteButton(wxCommandEvent& WXUNUSED(Event))
{
    Execute();
}

void CCommander::OnEdallButton(wxCommandEvent& WXUNUSED(Event))
{
    do_execution(L"edall");
}

void CCommander::OnEnter(wxCommandEvent & Event)
{
    if (is_executing())
    {
#ifndef WX_PURE
        // For compatibility with MSWLogo, simply beep if Logo is currently
        // running when the user presses Enter.  It might be preferable to
        // run the command anyway, but that was too significant a change for
        // a micro release.
        MessageBeep(MB_OK);
#endif // WX_PURE
    }
    else
    {
        Execute();
    }
}

CCommander * CCommander::GetCommander()
{
    return this;
}

const wxSize CCommander::GetRecommendedMinimumSize() const
{
    const int x_border = 4;
    const int y_border = 4;
    const int padding  = 6;

    const int minHistoryWidth = 100;

    const int minX = 
        x_border + 
        minHistoryWidth +
        padding +
        m_ButtonWidth +
        m_ButtonWidth +
        x_border;

    // height of one of the columns with buttons
    const int minButtonY =
        y_border +
        m_ButtonHeight * 4 +
        y_border;

    // height of the history/input column,
    // assuming history shows at least two rows
    const int minHistoryY =
        y_border +
        m_NextInstructionHeight * 2 +
        padding +
        m_NextInstructionHeight +
        y_border;

    return wxSize(
        minX,
        std::max(minButtonY, minHistoryY));
}

void CCommander::RecalculateLayout()
{
    // NOTE: This cannot use a wxSizer because different localized
    // versions of FMSLogo use different lengths of text for the buttons.
    // The problems:
    // 1) All buttons must be the same size, so the wxBoxSizer is inadequate.
    // 2) There must be a variable amount of space between the first three
    //    buttons and the fourth button in each column. This makes the
    //    wxGridSizer inadequate.
    // 3) The toggle buttons can change their text, but should be sized for
    //    the longer of the two text possibilities.

    // scale and pos. each sub-window in commander window based on its size
    const wxSize commanderSize = GetClientSize();

    const int total_width   = commanderSize.GetWidth();
    const int total_height  = commanderSize.GetHeight();
    const int button_height = m_ButtonHeight;
    const int button_width  = m_ButtonWidth;

    const int x_border = 4;
    const int y_border = 4;
    const int padding  = 6;

    m_EdallButton->SetSize(
        total_width - button_width * 1 - x_border, 
        total_height - button_height - y_border, 
        button_width, 
        button_height);

    m_ExecuteButton->SetSize(
        total_width - button_width * 2 - x_border, 
        total_height - button_height - y_border, 
        button_width, 
        button_height);

    m_ResetButton->SetSize(
        total_width - button_width * 1 - x_border, 
        button_height * 2 + y_border, 
        button_width, 
        button_height);

    m_StepButton->SetSize(
        total_width - button_width * 2 - x_border,
        button_height * 2 + y_border,
        button_width,
        button_height);

    m_StatusButton->SetSize(
        total_width - button_width * 1 - x_border, 
        button_height * 1 + y_border, 
        button_width, 
        button_height);

    m_PauseButton->SetSize( 
        total_width - button_width * 2 - x_border,
        button_height * 1 + y_border,
        button_width,
        button_height);

    m_TraceButton->SetSize(
        total_width - button_width * 1 - x_border, 
        button_height * 0 + y_border, 
        button_width, 
        button_height);

    m_HaltButton->SetSize( 
        total_width - button_width * 2 - x_border,
        button_height * 0 + y_border,
        button_width,
        button_height);

    m_NextInstruction->SetSize(
        x_border,
        total_height - m_NextInstructionHeight - y_border,
        total_width - button_width * 2 - x_border - padding,
        m_NextInstructionHeight);

    m_History->SetSize(
        x_border, 
        0,
        total_width - button_width * 2 - x_border - padding, 
        total_height - m_NextInstructionHeight - padding);
}

void
CCommander::UpdateFont(const wxFont & NewFont)
{
    m_History->SetFont(NewFont);
    m_NextInstruction->SetFont(NewFont);

    // HACK: We need to force an internal Scintilla ViewStule::Refresh() after
    // setting the font before TextHeight() will reflect the size of NewFont.
    m_NextInstruction->SetSize(0, 0);

    // font height + some padding
    m_NextInstructionHeight = m_NextInstruction->TextHeight(0) + 6;
}

void CCommander::OnSize(wxSizeEvent& Event)
{
    RecalculateLayout();
    Event.Skip();
}

void CCommander::ProcessKeyDownEventAtInputControl(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    // Special case for redirecting the right-arrow key press
    // in the commander history: move the insertion point to
    // the far left.
    if (keyCode == WXK_RIGHT || keyCode == WXK_NUMPAD_RIGHT)
    {
        m_NextInstruction->SetCurrentPos(0);
    }

    m_NextInstruction->SetFocus();
    m_NextInstruction->SimulateKeyPress(Event);
}

void CCommander::GiveControlToInputBox()
{
    // Give focus to the input edit control
    m_NextInstruction->SetFocus();
}

void CCommander::GiveControlToHistoryBox()
{
    // Advance to the bottom of the listbox
    m_History->MoveEnd();
    const wxTextPos & endPosition = m_History->GetLastPosition();
    m_History->ShowPosition(endPosition);

    // Give focus to the listbox.
    // This will copy the current line (which is blank) to
    // the commander input, as it did in the MSWLogo.
    m_History->SetFocus();
}

void
CCommander::AppendToCommanderHistory(
    const wchar_t * String
    )
{
    // Append the string to the buffer
    g_HistoryBuffer.AppendString(String);

    // process lines
    wxString rawBuffer = g_HistoryBuffer.GetBuffer();

	wxString next_line;

    for (size_t i = 0; i < rawBuffer.length(); i++)
    {
        if (rawBuffer[i] == L'\n')
        {
            // if <lf> pump it out
			next_line = rawBuffer.substr(0, i);
			rawBuffer = rawBuffer.substr(i + 1);
            putcombobox(next_line, MESSAGETYPE_Normal);
        }
    }

    // flush the last line (which doesn't end in \n)
    if (next_line[0] != L'\0')
    {
        putcombobox(next_line, MESSAGETYPE_Normal);
    }

    // clear the contents of the buffer, since we wrote the entire thing
    g_HistoryBuffer.Empty();
}

void
CCommander::AppendToCommanderHistory(
    wchar_t Char
    )
{
    if (Char == L'\n')
    {
        // if <lf> pump it out
        putcombobox(g_HistoryBuffer.GetBuffer(), MESSAGETYPE_Normal);
        g_HistoryBuffer.Empty();
    }
    else
    {
        g_HistoryBuffer.AppendChar(Char);
    }
}

BEGIN_EVENT_TABLE(CCommander, wxPanel)
    EVT_BUTTON(ID_COMMANDER_HALT,    CCommander::OnHaltButton)
    EVT_BUTTON(ID_COMMANDER_PAUSE,   CCommander::OnPauseButton)
    EVT_BUTTON(ID_COMMANDER_RESET,   CCommander::OnResetButton)
    EVT_BUTTON(ID_COMMANDER_EXECUTE, CCommander::OnExecuteButton)
    EVT_BUTTON(ID_COMMANDER_EDALL,   CCommander::OnEdallButton)
    EVT_TOGGLEBUTTON(ID_COMMANDER_TRACE,   CCommander::OnTraceButton)
    EVT_TOGGLEBUTTON(ID_COMMANDER_STATUS,  CCommander::OnStatusButton)
    EVT_TOGGLEBUTTON(ID_COMMANDER_STEP,    CCommander::OnStepButton)
    EVT_TEXT_ENTER(ID_COMMANDER_NEXTINSTRUCTION, CCommander::OnEnter)
    EVT_SIZE(CCommander::OnSize)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// CCommanderDialog
// ----------------------------------------------------------------------------

CCommanderDialog::CCommanderDialog(
    wxWindow   * Parent,
    CCommander * CommanderPanel
    ) :
    wxDialog(
        Parent,
        wxID_ANY,
        GetResourceString(L"LOCALIZED_COMMANDER"),
        wxDefaultPosition,
        wxDefaultSize,
        wxSYSTEM_MENU | wxCAPTION |  wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER)
{
    // Put the commander inside the dialog box
    wxSizer * sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(CommanderPanel, 1, wxEXPAND);
    SetSizer(sizer);

    // Set the minimum size based on what's recommended to show
    // all of the controls in the commander.
    SetMinSize(ClientToWindowSize(CommanderPanel->GetRecommendedMinimumSize()));

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[1];

    // Ctrl+Tab navigates to the next window.
    acceleratorEntries[0].Set(wxACCEL_CTRL, WXK_TAB, ID_COMMANDER_NEXT_WINDOW);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);

    SetAcceleratorTable(acceleratorTable);
}

void CCommanderDialog::OnClose(wxCloseEvent& Event)
{
    // Veto whenever possible so that we don't ever
    // close this dialog by user interaction.
    if (Event.CanVeto())
    {
        Event.Veto();
    }
    else
    {
        Event.Skip();
    }
}

void CCommanderDialog::OnNavigateNextWindow(wxCommandEvent& Event)
{
    CFmsLogo::GetMainFrame()->KeyboardNavigateTopLevelWindow(
        this,
        wxNavigationKeyEvent::IsForward);
}

BEGIN_EVENT_TABLE(CCommanderDialog, wxDialog)
    EVT_CLOSE(CCommanderDialog::OnClose)
    EVT_MENU(ID_COMMANDER_NEXT_WINDOW, CCommanderDialog::OnNavigateNextWindow)
END_EVENT_TABLE()
