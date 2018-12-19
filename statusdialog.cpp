#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "statusdialog.h"

    #include <wx/sizer.h>
    #include <wx/stattext.h>
    #include <wx/button.h>
    #include <wx/statbox.h>

    #include "commander.h"
    #include "fmslogo.h"
    #include "mainframe.h"
    #include "localizedstrings.h"
    #include "logocore.h" // for ARRAYSIZE
    #include "utils.h"
    #include "status.h"
    #include "startup.h"
    #include "graphics.h"
    #include "graphwin.h"
    #include "eval.h"
    #include "mem.h"
    #include "stringadapter.h"
    #include "screenwindow.h"
    #include "debugheap.h"
#endif

bool status_flag = false;   // Flag to signal status box is popped up

// Menu IDs
enum
{
   ID_STATUS_CONTACT = wxID_HIGHEST,
   ID_STATUS_PENCOLOR,
   ID_STATUS_FLOODCOLOR,
   ID_STATUS_SCREENCOLOR,
   ID_STATUS_WIDTH,
   ID_STATUS_VISIBILITY,
   ID_STATUS_STYLE,
   ID_STATUS_HEADING,
   ID_STATUS_PITCH,
   ID_STATUS_ROLL,
   ID_STATUS_PEN,
   ID_STATUS_ORIENTATION,
   ID_STATUS_TURTLE,
   ID_STATUS_COLOR,
   ID_STATUS_KERNEL,
   ID_STATUS_CALLS,
   ID_STATUS_PEAKMEMORY,
};

// ----------------------------------------------------------------------------
// CStatusDialog
// ----------------------------------------------------------------------------

CStatusDialog::CStatusDialog(wxWindow * Parent)
    : wxDialog(
        Parent, 
        wxID_ANY, 
		wxString(LOCALIZED_STATUS),
        wxDefaultPosition, 
        wxDefaultSize, 
        wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU)
{
    // build default coords
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    // Get last location and size of command window from configuration settings.
    GetConfigurationQuadruple(L"Status", &x, &y, &w, &h); 
    checkwindow(&x, &y, &w, &h);

    // now set position
    Move(x, y);

    struct STATICBOX
    {
        const wchar_t *        Category;
        const wchar_t *        FieldName[4];
        wxStaticText * *    FieldValue[4];
    } data[] = {
        {
            LOCALIZED_STATUS_PEN,
            {
                LOCALIZED_STATUS_CONTACT,
                LOCALIZED_STATUS_WIDTH, 
                LOCALIZED_STATUS_STYLE,
            },
            {
                &m_PenContact,
                &m_PenWidth,
                &m_PenStyle,
            },
        },
        {
            LOCALIZED_STATUS_ORIENTATION,
            {
                LOCALIZED_STATUS_HEADING,
                LOCALIZED_STATUS_PITCH, 
                LOCALIZED_STATUS_ROLL,
            },
            {
                &m_TurtleHeading,
                &m_TurtlePitch,
                &m_TurtleRoll,
            },
        },
        {
            LOCALIZED_STATUS_TURTLE,
            {
                LOCALIZED_STATUS_POSITION,
                LOCALIZED_STATUS_WHICH, 
                LOCALIZED_STATUS_VISIBILITY,
            },
            {
                &m_TurtlePosition,
                &m_TurtleId,
                &m_TurtleVisibility,
            },
        },
        {
            LOCALIZED_STATUS_COLOR,
            {
                LOCALIZED_STATUS_PENCOLOR,
                LOCALIZED_STATUS_FLOODCOLOR, 
                LOCALIZED_STATUS_SCREENCOLOR,
            },
            {
                &m_PenColor,
                &m_FloodColor,
                &m_ScreenColor,
            },
        },
        {
            LOCALIZED_STATUS_KERNEL,
            {
                LOCALIZED_STATUS_CALLS,
                LOCALIZED_STATUS_PEAKMEMORY, 
                LOCALIZED_STATUS_VECTORS":",
                LOCALIZED_STATUS_POLYGONS":",
            },
            {
                &m_TotalCalls,
                &m_PeakMemory,
                &m_TotalVectors,
                &m_TotalPolygons,
            },
        },
    };

    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    for (size_t i = 0; i < ARRAYSIZE(data); i++)
    {
        wxStaticBoxSizer * staticBoxSizer = new wxStaticBoxSizer(
            wxHORIZONTAL,
            this, 
			wxString(data[i].Category));

        topLevelSizer->Add(staticBoxSizer, 0, wxALL | wxEXPAND, 5);

        wxBoxSizer * fieldNameSizer  = new wxBoxSizer(wxVERTICAL);
        staticBoxSizer->Add(fieldNameSizer);

        wxBoxSizer * fieldValueSizer = new wxBoxSizer(wxVERTICAL);
        staticBoxSizer->Add(fieldValueSizer);

        for (size_t j = 0; j < ARRAYSIZE(data[i].FieldName); j++)
        {
            if (data[i].FieldName[j] == NULL)
            {
                // we've done all the fields for this static box
                break;
            }

            wxStaticText * fieldName = new wxStaticText(
                this,
                wxID_ANY,
				wxString(data[i].FieldName[j]),
                wxDefaultPosition,
                wxDefaultSize, 
                wxALIGN_LEFT);

            fieldNameSizer->Add(fieldName, 0, wxEXPAND);

            wxStaticText * fieldValue = new wxStaticText(
                this,
                wxID_ANY,
                wxEmptyString,
                wxDefaultPosition,
                wxDefaultSize, 
                wxALIGN_LEFT);

            fieldValueSizer->Add(
                fieldValue,
                0, 
                wxEXPAND | wxLEFT | wxRIGHT,
                5);

            *data[i].FieldValue[j] = fieldValue;
        }
    }

    SetSizer(topLevelSizer);

    // Populate with long data to determine the maximum
    // extents which we'll need to show the data without
    // truncation.
    SetPenContact(true);
    SetPenWidth(100);
    SetPenStyle(LOCALIZED_STATUS_PENREVERSE);
    SetTurtleHeading(350.1234);
    SetTurtlePitch(350.1234);
    SetTurtleRoll(350.1234);
    SetTurtlePosition(8888, 8888, 8888);
    SetTurtleId(1000);
    SetTurtleVisibility(true);
    SetPenColor(255, 255, 255);
    SetFloodColor(255, 255, 255);
    SetScreenColor(255, 255, 255);
    SetCalls(8888888);
    SetPeakMemory(8888888);
    SetVectors(8888888);
    SetPolygons(8888888);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);
}

void CStatusDialog::PopulateAllFields()
{
    // flag so that updates are sent
    status_flag = true;

    // update all fields
    update_status_evals();
    update_status_floodcolor();
    update_status_memory();
    update_status_pencolor();
    update_status_pencontact();
    update_status_penstyle();
    update_status_penwidth();
    update_status_screencolor();
    update_status_turtleheading();
    update_status_turtlepitch();
    update_status_turtleposition();
    update_status_turtleroll();
    update_status_turtlevisability();
    update_status_turtlewhich();
    update_status_vectors();
}

void CStatusDialog::SetPenContact(bool PenIsUp)
{
    const wchar_t * text;

    if (PenIsUp)
    {
        text = LOCALIZED_STATUS_PENUP;
    }
    else
    {
        text = LOCALIZED_STATUS_PENDOWN;
    }

    m_PenContact->SetLabel(wxString(text));
}

void CStatusDialog::SetPenWidth(int PenWidth)
{
    wxString penWidthString;
    penWidthString.Printf(wxString(L"%d"), PenWidth);

    m_PenWidth->SetLabel(penWidthString);
}

void CStatusDialog::SetPenStyle(const wchar_t * PenStyle)
{
    m_PenStyle->SetLabel(wxString(PenStyle));
}


void CStatusDialog::SetTurtleHeading(double Heading)
{
    wxString headingString;
    headingString.Printf(wxString(L"%1.2f"), Heading);

    m_TurtleHeading->SetLabel(headingString);
}


void CStatusDialog::SetTurtlePitch(double Pitch)
{
    wxString pitchString;
    pitchString.Printf(wxString(L"%1.2f"), Pitch);

    m_TurtlePitch->SetLabel(pitchString);
}

void CStatusDialog::SetTurtleRoll(double Roll)
{
    wxString rollString;
    rollString.Printf(wxString(L"%1.2f"), Roll);

    m_TurtleRoll->SetLabel(rollString);
}

void CStatusDialog::SetTurtlePosition(double X, double Y, double Z)
{
    wxString positionString;
    positionString.Printf(wxString(L"%1.0f,%1.0f,%1.0f"), X, Y, Z);

    m_TurtlePosition->SetLabel(positionString);
}

void CStatusDialog::SetTurtleId(int TurtleId)
{
    wxString turtleIdString;
    turtleIdString.Printf(wxString(L"%d"), TurtleId);

    m_TurtleId->SetLabel(turtleIdString);
}

void CStatusDialog::SetTurtleVisibility(bool IsShown)
{
    const wchar_t * text;

    if (IsShown)
    {
        text = LOCALIZED_STATUS_PENSHOWN;
    }
    else
    {
        text = LOCALIZED_STATUS_PENHIDDEN;
    }

    m_TurtleVisibility->SetLabel(wxString(text));
}

void CStatusDialog::SetPenColor(int Red, int Green, int Blue)
{
    wxString colorString;
    colorString.Printf(wxString(L"%d,%d,%d"), Red, Green, Blue);

    m_PenColor->SetLabel(colorString);
}

void CStatusDialog::SetScreenColor(int Red, int Green, int Blue)
{
    wxString colorString;
    colorString.Printf(wxString(L"%d,%d,%d"), Red, Green, Blue);

    m_ScreenColor->SetLabel(colorString);
}

void CStatusDialog::SetFloodColor(int Red, int Green, int Blue)
{
    wxString colorString;
    colorString.Printf(wxString(L"%d,%d,%d"), Red, Green, Blue);

    m_FloodColor->SetLabel(colorString);
}

void CStatusDialog::SetCalls(long long TotalCalls)
{
    // Use operator<< instead of wxString::Printf() to format the
    // "long long", as the C runtime on Windows XP does not support
    // the ANSI C99 "%lld" format sequence and would treat TotalCalls
    // as a 32-bit number.
    wxString totalCallsString;
    totalCallsString << TotalCalls;

    m_TotalCalls->SetLabel(totalCallsString);
}

void CStatusDialog::SetPeakMemory(int TotalNodes)
{
    wxString peakMemoryString;
    peakMemoryString.Printf(wxString(L"%d " LOCALIZED_STATUS_NODES), TotalNodes);

    m_PeakMemory->SetLabel(peakMemoryString);
}

void CStatusDialog::SetVectors(int TotalVectors)
{
    wxString totalVectorsString;
    if (TotalVectors < 0)
    {
        totalVectorsString = wxString(LOCALIZED_STATUS_NOT_APPLICABLE);
    }
    else
    {
        totalVectorsString.Printf(wxString(L"%d"), TotalVectors);
    }

    m_TotalVectors->SetLabel(totalVectorsString);
}

void CStatusDialog::SetPolygons(int TotalPolygons)
{
    wxString totalPolygonsString;

    if (TotalPolygons < 0)
    {
        totalPolygonsString = wxString(LOCALIZED_STATUS_NOT_APPLICABLE);
    }
    else
    {
        totalPolygonsString.Printf(wxString(L"%d"), TotalPolygons);
    }

    m_TotalPolygons->SetLabel(totalPolygonsString);
}

void CStatusDialog::OnClose(wxCloseEvent& Event)
{
    // No longer accept updates to the status fields
    status_flag = false;

#ifdef __WXMSW__ // utils.cpp only builds on Windows

    // Get location of our window on the screen so we can
    // come back up in the same spot next time we are invoked.

    // build default coords
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    GetPosition(&x, &y);

    // save the current location
    SetConfigurationQuadruple(L"Status", x, y, w, h);

#endif

#ifdef FMSLOGO_WXWIDGETS
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();

    mainFrame->ClearStatusDialog();
    mainFrame->GetCommander()->UpdateStatusButtonState();
#endif

    // default processing will destroy the dialog box
    Event.Skip();
}

BEGIN_EVENT_TABLE(CStatusDialog, wxDialog)
    EVT_CLOSE(CStatusDialog::OnClose)
END_EVENT_TABLE()

void update_status_turtleposition(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetTurtlePosition(
            g_SelectedTurtle->Position.x,
            g_SelectedTurtle->Position.y,
            g_SelectedTurtle->Position.z);
    }
}


void update_status_pencolor(void)
{
    if (status_flag)
    {
        const Color & penColor = GetPenStateForSelectedTurtle().Color;

        GetStatusDialog()->SetPenColor(
            penColor.red,
            penColor.green,
            penColor.blue);
    }
}

void update_status_floodcolor(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetFloodColor(dfld.red, dfld.green, dfld.blue);
    }
}

void update_status_screencolor(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetScreenColor(dscn.red, dscn.green, dscn.blue);
    }
}

void update_status_penwidth(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetPenWidth(GetPenStateForSelectedTurtle().Width);
    }
}


void update_status_turtleheading(void)
{
    if (status_flag)
    {
        FLONUM heading;
        if (current_mode == perspectivemode)
        {
            heading = rotation_z();
        }
        else
        {
            heading = g_SelectedTurtle->Heading;
        }

        GetStatusDialog()->SetTurtleHeading(heading);
    }
}

void update_status_penstyle(void)
{
    if (status_flag)
    {
        // TODO: merge with get_node_pen_mode()
        const wchar_t * penStyle;
        if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
        {
            penStyle = LOCALIZED_STATUS_PENREVERSE;
        }
        else
        {
            penStyle = LOCALIZED_STATUS_PENNORMAL;
        }

        if (GetPenStateForSelectedTurtle().IsErasing)
        {
            penStyle = LOCALIZED_STATUS_PENERASE;
        }

        GetStatusDialog()->SetPenStyle(penStyle);
    }
}

void update_status_pencontact(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetPenContact(g_SelectedTurtle->IsPenUp);
    }
}

void update_status_turtlevisability(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetTurtleVisibility(g_SelectedTurtle->IsShown);
    }
}

void update_status_turtlepitch(void)
{
    if (status_flag)
    {
        FLONUM pitch;

        if (current_mode == perspectivemode)
        {
            pitch = rotation_x();
        }
        else
        {
            pitch = 0.0;
        }

        GetStatusDialog()->SetTurtlePitch(pitch);
    }
}

void update_status_turtleroll(void)
{
    if (status_flag)
    {
        FLONUM roll;

        if (current_mode == perspectivemode)
        {
            roll = rotation_y();
        }
        else
        {
            roll = 0.0;
        }

        GetStatusDialog()->SetTurtleRoll(roll);
    }
}

void update_status_turtlewhich(void)
{
    if (status_flag)
    {
        int turtleId = GetSelectedTurtleIndex();
        GetStatusDialog()->SetTurtleId(turtleId);
    }
}

void update_status_evals(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetCalls(eval_count);
    }
}

void update_status_vectors(void)
{
    if (status_flag)
    {
#ifndef WX_PURE
        if (ThreeD.m_iPolyCount)
        {
            GetStatusDialog()->SetPolygons(ThreeD.m_iPolyCount);
            GetStatusDialog()->SetVectors(-1);
        }
        else
        {
            GetStatusDialog()->SetPolygons(-1);
            GetStatusDialog()->SetVectors(vector_count);
        }
#endif
    }
}

void update_status_memory(void)
{
    if (status_flag)
    {
        GetStatusDialog()->SetPeakMemory(memory_count * SEG_SIZE);
    }
}
