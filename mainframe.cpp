    // ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "pch.h"

#ifndef USE_PRECOMPILED_HEADER
    #include <wx/log.h>

    #include <wx/app.h>
    #include <wx/frame.h>
    #include <wx/sizer.h>

    #include <wx/scrolwin.h>
    #include <wx/menu.h>
    #include <wx/msgdlg.h>

    #include <wx/splitter.h>
    #include <wx/statusbr.h>
    #include <wx/dcmirror.h>
    #include <wx/dcclient.h>
    #include <wx/fontdlg.h>
    #include <wx/printdlg.h>
    #include <wx/filedlg.h>
    #include <wx/dcmemory.h>
    #include <wx/settings.h>

    #include <wx/fontutil.h> // for wxNativeFontInfo
    #include <wx/msgdlg.h>   // for wxMessageBox
    #include <wx/filefn.h>   // for wxSetWorkingDirectory

    #include <algorithm>

    #ifndef WX_PURE
        #include <shlobj.h>
    #endif

    //#ifdef WX_PURE
    //    #define MAX_PATH (260)
    //#endif

    #include "logorc.h" // for WM_*
    #include "guiutils.h"
    #include "commander.h"
    #include "activearea.h"
    #include "setactivearea.h"
    #include "aboutfmslogo.h"
    #include "aboutmultiplesclerosis.h"
    #include "savebeforeexitdialog.h"
    #include "logocore.h"
    #include "localizedstrings.h"
    #include "FMSLogo.h"
    #include "mainframe.h"
    #include "setpensize.h"
    #include "utils.h"
    #include "statusdialog.h"
    #include "screen.h"
    #include "selectstartupinstruction.h"
    #include "editproceduredialog.h"
    #include "eraseproceduredialog.h"
    #include "commanderhistory.h"
    #include "commanderinput.h"
    #include "minieditor.h"
    #include "workspaceeditor.h"
    #include "logodata.h"
    #include "setcolor.h"
    #include "graphwin.h"
    #include "init.h"
    #include "error.h"          // for err_logo
    #include "messagebox.h"     // for ShowErrorMessage
    #include "screenwindow.h"   // for TraceOutput
    #include "mainwind.h"
    #include "logoeventqueue.h"
    #include "wrksp.h"
    #include "eval.h"
    #include "fileswnd.h"
    #include "graphwin.h"
    #include "mmwind.h" // for uninitialize_timers()
    #include "startup.h"
    #include "fontutils.h"
    #include "netwind.h"
    #include "questionbox.h"
    #include "cursor.h" // lsetcursorarrow
    #include "files.h" // silent_load
    #include "stringadapter.h"
//    #include "debugheap.h"
#endif

extern wxString NormalizeCaseForDisplay(wxString text);

// ----------------------------------------------------------------------------
// CMainFrame::CLogoPicturePrintout
// ----------------------------------------------------------------------------

CMainFrame::CLogoPicturePrintout::CLogoPicturePrintout(
    const wxString        & Title,
    wxWindow              & Screen,
    wxPageSetupDialogData & PageSetup
    ) :
    wxPrintout(Title),
    m_Screen(Screen),
    m_PageSetup(PageSetup)
{
}

bool
CMainFrame::CLogoPicturePrintout::OnPrintPage(
    int Page
    )
{
#ifdef WX_PURE
    return false;
#else
    // Must of rewrote this at least 26 times and it still does not
    // Work in some situations. This is just the "Paint" of printing.
    // See the print module for all the other stuff.
    wxDC * dc = GetDC();
    if (dc == NULL)
    {
        return false;
    }

    HDC PrintDC = static_cast<HDC>(dc->GetHDC());

    // do we even have a chance?
    if ((GetDeviceCaps(PrintDC, RASTERCAPS) & RC_STRETCHDIB) == 0)
    {
        // notify the user that the printer does not support scaling
        wxMessageBox(
			GetResourceString(L"LOCALIZED_ERROR_PRINTERCANTSCALE"),
			GetResourceString(L"LOCALIZED_ERROR"),
            wxICON_ERROR);
        return false;
    }

    int printBitCount = GetDeviceCaps(PrintDC, BITSPIXEL);
    printBitCount *= GetDeviceCaps(PrintDC, PLANES);

    if (printBitCount == 1)
    {
        // This is a monochrome mono printer.
        // Let's let it try to dither a 256 grey scale image
        printBitCount = 8;
    }

    // Get screen bitCount
    wxClientDC * screenDeviceContext = new wxClientDC(&m_Screen);
    HDC screenDc = static_cast<HDC>(screenDeviceContext->GetHDC());

    int screenBitCount = GetDeviceCaps(screenDc, BITSPIXEL);
    screenBitCount *= GetDeviceCaps(screenDc, PLANES);

    // Don't bother creating a DIB with more colors than we have
    if (screenBitCount < printBitCount) 
    {
        printBitCount = screenBitCount;
    }

    // Round to nearest legal bitmap color depth
    if      (                        (printBitCount <  1)) printBitCount =  1;
    else if ((printBitCount >  1) && (printBitCount <  4)) printBitCount =  4;
    else if ((printBitCount >  4) && (printBitCount <  8)) printBitCount =  8;
    else if ((printBitCount >  8) && (printBitCount < 16)) printBitCount = 16;
    else if ((printBitCount > 16) && (printBitCount < 24)) printBitCount = 24;
    else if ((printBitCount > 24)                        ) printBitCount = 32;

    printBitCount = GetConfigurationInt(L"PrintColorDepth", printBitCount);

    size_t size;
    if (printBitCount <= 8)
    {
        size = sizeof(BITMAPINFOHEADER) + ((
#ifdef _WIN64
			1LL
#else
			1
#endif
			<< printBitCount) * sizeof(RGBQUAD));
    }
    else
    {
        size = sizeof(BITMAPINFOHEADER);
    }

    BITMAPINFO * bitmapInfo = (BITMAPINFO *) new char[size];

    bitmapInfo->bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    bitmapInfo->bmiHeader.biWidth    = BitMapWidth;
    bitmapInfo->bmiHeader.biHeight   = BitMapHeight;
    bitmapInfo->bmiHeader.biPlanes   = 1;
    bitmapInfo->bmiHeader.biBitCount = printBitCount;
    bitmapInfo->bmiHeader.biCompression = BI_RGB;
    bitmapInfo->bmiHeader.biSizeImage   = ((((bitmapInfo->bmiHeader.biWidth * bitmapInfo->bmiHeader.biBitCount) + 31) / 32) * 4) * bitmapInfo->bmiHeader.biHeight;
    bitmapInfo->bmiHeader.biXPelsPerMeter = 0;
    bitmapInfo->bmiHeader.biYPelsPerMeter = 0;
    bitmapInfo->bmiHeader.biClrUsed       = 0;
    bitmapInfo->bmiHeader.biClrImportant  = 0;

    // we don't need hour glass here because print module takes care of it 

    // allocate space for the raw DIB data
    unsigned char * bitsPtr = new unsigned char [bitmapInfo->bmiHeader.biSizeImage];
    memset(bitsPtr, 0x00, bitmapInfo->bmiHeader.biSizeImage);

    // get printer size per inch 
    int tempWidth  = GetDeviceCaps(PrintDC, LOGPIXELSX);
    int tempHeight = GetDeviceCaps(PrintDC, LOGPIXELSY);

    // set up an assured contrast ?
    SetTextColor(PrintDC, 0x00000000L);
    SetBkColor(PrintDC, 0x00ffffffL);

    bool isOk = true;

    int scanLines = GetDIBits(
        screenDc,
        MemoryBitMap,
        0,
        BitMapHeight,
        bitsPtr,
        bitmapInfo,
        DIB_RGB_COLORS);
    if (scanLines != 0)
    {
        // there is something to print.

        // print only the active area
        int status = StretchDIBits(
            PrintDC,
            0,
            0,
            (tempWidth  * (g_PrinterAreaXHigh - g_PrinterAreaXLow)) / g_PrinterAreaPixels,
            (tempHeight * (g_PrinterAreaYHigh - g_PrinterAreaYLow)) / g_PrinterAreaPixels,
            +g_PrinterAreaXLow + xoffset,
            BitMapHeight - (-g_PrinterAreaYLow + yoffset),
            g_PrinterAreaXHigh - g_PrinterAreaXLow,
            g_PrinterAreaYHigh - g_PrinterAreaYLow,
            bitsPtr,
            bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY);
        if (status <= 0)
        {
            // TODO: message the last error into the current locale
            DWORD lastError = GetLastError();
            const wxString & message = wxString::Format(
                L"%s\n%s: %lu",
                GetResourceString(L"LOCALIZED_ERROR_CANTDRAWIMAGE"),
                GetResourceString(L"LOCALIZED_ERROR_SUBCODE"),
                lastError);

            wxMessageBox(message, GetResourceString(L"LOCALIZED_ERROR"), wxICON_ERROR);
            isOk = false;
        }
    }
    else
    {
        // can't do it
        wxMessageBox(
			GetResourceString(L"LOCALIZED_ERROR_CANTEXTRACTIMAGE"),
			GetResourceString(L"LOCALIZED_ERROR"),
            wxICON_ERROR);
        isOk = false;
    }

    delete [] bitsPtr;

    delete bitmapInfo;
    delete screenDeviceContext;

    return isOk;
#endif
}

void
CMainFrame::CLogoPicturePrintout::GetPageInfo(
    int *MinPage,
    int *MaxPage,
    int *SelPageFrom,
    int *SelPageTo
    )
{
    *MinPage     = 1;
    *MaxPage     = 1;
    *SelPageFrom = 1;
    *SelPageTo   = 1;
}

bool
CMainFrame::CLogoPicturePrintout::HasPage(int Page)
{
    return Page == 1;
}


// ----------------------------------------------------------------------------
// CMainFrame
// ----------------------------------------------------------------------------

enum MainFrameMenuIds
{
    ID_FILENEW = wxID_HIGHEST + 256,
    ID_FILELOAD,
    ID_FILEOPEN,
    ID_FILESAVE,
	ID_FILESAVEAS,
	ID_FILESAVEAS_UTF8,
	ID_FILESAVEAS_UTF16,
	ID_FILESETASSCREENSAVER,
    ID_FILEEDIT,
    ID_FILEERASE,

    ID_BITMAPNEW,
    ID_BITMAPOPEN,
    ID_BITMAPSAVE,
    ID_BITMAPSAVEAS,

    ID_BITMAPPRINT,
    ID_BITMAPPRINTERSETUP,

    ID_BITMAPPRINTERAREA,

    ID_SETPENSIZE,

    ID_SETLABELFONT,
    ID_SETCOMMANDERFONT,

    ID_SETPENCOLOR,
    ID_SETFLOODCOLOR,
    ID_SETSCREENCOLOR,

#if MANUAL_HAS_TRANSLATION_TABLES
    // options for translating to/from English
    ID_HELPLANGTOENGLISH,
    ID_HELPENGLISHTOLANG,
#endif

    ID_HELPTUTORIAL,
    ID_HELPDEMO,
    ID_HELPEXAMPLES,
    ID_HELPRELEASENOTES,

    ID_HELPABOUTMS,
};
wxString CMainFrame::ModifyMenuTextForUnicode(wxString text, wxString suffix)
{
	if (suffix.length() > 0) {
		int i = text.Find(L'('), t = text.Find(L')');
		if (i >= 0 && t > i) {
			text.Remove(i, t - i + 1);
			text.insert(i, suffix);
		}
		else {
			text += suffix;
		}
	}
	return text;
}
wxString CMainFrame::ModifyMenuTextForNonWindows(wxString text)
{
#ifndef _WINDOWS
    if(text.length()>0)
    {
        int i = text.Find(L'\t');
        if(i>=0){
            text[i] = L' ';    
            text.insert(i,L"     ");
        }
    }
#endif
    return text;
}
// ScreenWidth    - the size of the screen window.
// ScreenHeight   - the size of the screen window.
// Position       - where the frame window should be placed.
// Size           - The size of the frame window.
//                  In bFixed mode, this is ignored, as the width and height
//                  are derived from ScreenWidth and ScreenHeight.
// StartMaximized - true, if the window should start maximized (without a frame).
//                  false, if it should start in a restored mode.
CMainFrame::CMainFrame(
    int             ScreenWidth,
    int             ScreenHeight,
    const wxPoint & Position,
    const wxSize  & Size,
    bool            StartMaximized
    ) : wxFrame(
        NULL, 
        wxID_ANY, 
		GetResourceString(L"LOCALIZED_GENERAL_PRODUCTNAME"),
        Position,
        Size,
        wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE |
            (StartMaximized ? wxMAXIMIZE : 0)),
      m_Screen(NULL),
      m_Commander(NULL),
      m_RealCommander(NULL),
      m_StatusDialog(NULL),
      m_SetPenSizeDialog(NULL),
      m_Splitter(NULL),
      m_OriginalWidth(ScreenWidth),
      m_OriginalHeight(ScreenHeight),
      m_CommanderIsDocked(false),
      m_IsNewFile(true),
      m_IsNewBitmap(true),
      m_SetPenColorDialog(NULL),
      m_SetFloodColorDialog(NULL),
      m_SetScreenColorDialog(NULL),
		Unicode(false)

{
	wxString SaveAsText = GetResourceString(L"LOCALIZED_FILE_SAVEAS");

	//
    // Construct the main menu
    //
    static const MENUITEM fileMenuItems[] = {
        {ModifyMenuTextForNonWindows(GetResourceString(L"LOCALIZED_FILE_NEW")),              ID_FILENEW},
        {ModifyMenuTextForNonWindows(GetResourceString(L"LOCALIZED_FILE_LOAD")),             ID_FILELOAD},
        {ModifyMenuTextForNonWindows(GetResourceString(L"LOCALIZED_FILE_OPEN")),             ID_FILEOPEN},
        {GetResourceString(L"LOCALIZED_FILE_SAVE"),             ID_FILESAVE},
		{SaveAsText,           ID_FILESAVEAS},
		{this->ModifyMenuTextForUnicode(SaveAsText,L"-UTF&8"), ID_FILESAVEAS_UTF8},
		{this->ModifyMenuTextForUnicode(SaveAsText,L"-&UTF16"), ID_FILESAVEAS_UTF16},
		{GetResourceString(L"LOCALIZED_FILE_SETASSCREENSAVER"), ID_FILESETASSCREENSAVER},
        {L"",0},
        {GetResourceString(L"LOCALIZED_FILE_EDIT"),             ID_FILEEDIT},
        {GetResourceString(L"LOCALIZED_FILE_ERASE"),            ID_FILEERASE},
        {L"",0},
        {GetResourceString(L"LOCALIZED_FILE_EXIT"),             wxID_EXIT},
    };

    static const MENUITEM bitmapMenuItems[] = {
        {GetResourceString(L"LOCALIZED_BITMAP_NEW"),           ID_BITMAPNEW},
        {GetResourceString(L"LOCALIZED_BITMAP_LOAD"),          ID_BITMAPOPEN},
        {GetResourceString(L"LOCALIZED_BITMAP_SAVE"),          ID_BITMAPSAVE},
        {GetResourceString(L"LOCALIZED_BITMAP_SAVEAS"),        ID_BITMAPSAVEAS},
        {L"",0},
        {GetResourceString(L"LOCALIZED_BITMAP_PRINT"),         ID_BITMAPPRINT},
        {GetResourceString(L"LOCALIZED_BITMAP_PRINTERSETUP"),  ID_BITMAPPRINTERSETUP},
        {L"",0},
        {GetResourceString(L"LOCALIZED_BITMAP_ACTIVEAREA"),    ID_BITMAPPRINTERAREA},
    };

    static const MENUITEM setMenuItems[] = {
        {GetResourceString(L"LOCALIZED_SET_PENSIZE"),       ID_SETPENSIZE},
        {L"",0},
        {GetResourceString(L"LOCALIZED_SET_LABELFONT"),     ID_SETLABELFONT},
        {GetResourceString(L"LOCALIZED_SET_COMMANDERFONT"), ID_SETCOMMANDERFONT},
        {L"",},
        {GetResourceString(L"LOCALIZED_SET_PENCOLOR"),      ID_SETPENCOLOR},
        {GetResourceString(L"LOCALIZED_SET_FLOODCOLOR"),    ID_SETFLOODCOLOR},
        {GetResourceString(L"LOCALIZED_SET_SCREENCOLOR"),   ID_SETSCREENCOLOR},
    };

    static const MENUITEM zoomMenuItems[] = {
        {GetResourceString(L"LOCALIZED_ZOOM_IN"),     wxID_ZOOM_IN},
        {GetResourceString(L"LOCALIZED_ZOOM_OUT"),    wxID_ZOOM_OUT},
        {GetResourceString(L"LOCALIZED_ZOOM_NORMAL"), wxID_ZOOM_100},
    };
 
    static const MENUITEM helpMenuItems[] = {
        {GetResourceString(L"LOCALIZED_HELP_INDEX"),         wxID_HELP_INDEX},
#if MANUAL_HAS_TRANSLATION_TABLES
        // options for translating to/from English
        {GetResourceString(L"LOCALIZED_HELP_LANGTOENGLISH"), ID_HELPLANGTOENGLISH},
        {GetResourceString(L"LOCALIZED_HELP_ENGLISHTOLANG"), ID_HELPENGLISHTOLANG},
#endif
        {L"",0},
        {GetResourceString(L"LOCALIZED_HELP_TUTORIAL"),      ID_HELPTUTORIAL},
        {GetResourceString(L"LOCALIZED_HELP_DEMO"),          ID_HELPDEMO},
        {GetResourceString(L"LOCALIZED_HELP_EXAMPLE"),       ID_HELPEXAMPLES},
        {GetResourceString(L"LOCALIZED_HELP_RELEASENOTES"),  ID_HELPRELEASENOTES},
        {L"",0},
        {GetResourceString(L"LOCALIZED_HELP_ABOUTFMSLOGO"),  wxID_ABOUT},
        {GetResourceString(L"LOCALIZED_HELP_MS"),            ID_HELPABOUTMS},
    };

    // Make a menubar
    wxMenuBar * mainMenu = new wxMenuBar;

    AppendChildMenu(mainMenu, GetResourceString(L"LOCALIZED_FILE"),   fileMenuItems, sizeof(fileMenuItems)/sizeof(MENUITEM));
    AppendChildMenu(mainMenu, GetResourceString(L"LOCALIZED_BITMAP"), bitmapMenuItems, sizeof(bitmapMenuItems) / sizeof(MENUITEM));
    AppendChildMenu(mainMenu, GetResourceString(L"LOCALIZED_SET"),    setMenuItems, sizeof(setMenuItems) / sizeof(MENUITEM));
    AppendChildMenu(mainMenu, GetResourceString(L"LOCALIZED_ZOOM"),   zoomMenuItems, sizeof(zoomMenuItems) / sizeof(MENUITEM));
    AppendChildMenu(mainMenu, GetResourceString(L"LOCALIZED_HELP"),   helpMenuItems, sizeof(helpMenuItems) / sizeof(MENUITEM));

    SetMenuBar(mainMenu);

    SetFmsLogoIcon(*this);

    //
    // Add the splitter to separate the screen from the commander
    //

    // Without wxSP_NO_XP_THEME, the splitter is invisible in
    // Windows XP, Windows Aero, and Windows 7 Basic themes.
    m_Splitter = new wxSplitterWindow(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN | wxSP_NO_XP_THEME);

    m_Splitter->SetMinimumPaneSize(MIN_COMMANDER_HEIGHT);

    m_Screen = new CScreen(m_Splitter, ScreenWidth, ScreenHeight);

    m_RealCommander = new CCommander(m_Splitter);
    DockCommanderWindow();


    m_Screen->Show();
    m_Commander->Show();

    // Set a flag that the printer data needs to be initialized.
    // We delay the initialization because it can be block
    // if the default printer is an offline network printer.
    m_PageSetupData.SetDefaultInfo(true);

#ifndef WX_PURE
    // init the pens based on the color
    UpdateNormalPen(GetPenStateForSelectedTurtle().Width, pcolor);
    UpdateErasePen(GetPenStateForSelectedTurtle().Width,  scolor);
#endif

    // it's show time for our little friend
    draw_turtle(true);
}

CMainFrame::~CMainFrame()
{
}

// Resizes the frame window so that the screen window matches the
// width/height that was originally requested.
void CMainFrame::ResizeToFitScreen()
{
    // HACK: fix up the frame window's size so that the screen's
    // size matches what the client passed in on the command line.
    // There MUST be a simpler/better way, but I do not know
    // how to set the size of the screen client area directly.
    wxSize screenRectangle = m_Screen->GetClientSize();
    int deltaX = m_OriginalWidth  - screenRectangle.GetWidth();
    int deltaY = m_OriginalHeight - screenRectangle.GetHeight();

    if (deltaX != 0 || deltaY != 0)
    {
        // The screen is the wrong size, so we adjust the
        // frame window to account for this.
        wxSize frameRectangle = GetClientSize();
        SetClientSize(
            frameRectangle.GetWidth() + deltaX,
            frameRectangle.GetHeight() + deltaY);
    }
}


void CMainFrame::UndockCommanderWindow()
{
    if (m_CommanderIsDocked)
    {
        // Remove the commander from whatever sizer it may be in,
        // before calling CCommanderDialog, which may want to add
        // the commander to its own sizer.
        wxSizer * oldSizer = m_RealCommander->GetContainingSizer();
        if (oldSizer != NULL)
        {
            oldSizer->Detach(m_RealCommander);
        }

        CCommanderDialog * newCommander = new CCommanderDialog(
            this,
            m_RealCommander);

        if (!bFixed)
        {
            // Save the current commander's height.
            SetConfigurationInt(
                L"CommanderHeight",
                m_Commander->GetSize().GetHeight());

            // Restore the previous size and position of the
            // undocked commander window.
            const wxRect & currentRect = newCommander->GetRect();
            int x      = currentRect.GetX();
            int y      = currentRect.GetY();
            int width  = currentRect.GetWidth();
            int height = currentRect.GetHeight();
            GetConfigurationQuadruple(L"CommanderWindow", &x, &y, &width, &height);
            checkwindow(&x, &y, &width, &height);
            newCommander->SetSize(x, y, width, height);
        }

        // commit to the new commander
        m_Splitter->Unsplit(m_RealCommander);
        m_RealCommander->Reparent(newCommander);
        m_RealCommander->Show();

        m_Commander = newCommander;
        m_Commander->Show();

        m_RealCommander->GiveControlToInputBox();
        m_CommanderIsDocked = false;

        if (bFixed)
        {
            // Fix up the frame window's size so that the screen's
            // size matches what the client passed in on the command line.
            ResizeToFitScreen();
        }
    }
}

void CMainFrame::DockCommanderWindow()
{
    if (!m_CommanderIsDocked) 
    {
#ifdef __WXMSW__ // utils.cpp only builds on Windows

        // Restore the commander window's height.
        int commanderWindowHeight = GetConfigurationInt(
            L"CommanderHeight",
            DEFAULT_COMMANDER_HEIGHT);

        // sanity-check the input
        commanderWindowHeight = std::max(
            commanderWindowHeight,
            MIN_COMMANDER_HEIGHT);
#else
        int commanderWindowHeight = MIN_COMMANDER_HEIGHT;
#endif

        if (bFixed)
        {
            // The user requested that we never change the size of the drawing surface,
            // so we must grow the main window to hold the commander window.
            int mainFrameWidth;
            int mainFrameHeight;
            GetClientSize(&mainFrameWidth, &mainFrameHeight);

            // grow the main window to hold the splitter and the commander
            const int newHeight =
                mainFrameHeight +
                m_Splitter->GetSashSize() +
                commanderWindowHeight;

            SetClientSize(mainFrameWidth, newHeight);
        }
        else
        {
            if (m_Commander != NULL &&
                !static_cast<CCommanderDialog*>(m_Commander)->IsIconized())
            {
                // Save the Commander's dialog's position
                const wxRect windowRectangle = m_Commander->GetRect();

                SetConfigurationQuadruple(
                    L"CommanderWindow",
                    windowRectangle.GetLeft(),
                    windowRectangle.GetTop(),
                    windowRectangle.GetWidth(),
                    windowRectangle.GetHeight());
            }
        }

        m_RealCommander->Reparent(m_Splitter);

        m_Splitter->SplitHorizontally(m_Screen, m_RealCommander, -commanderWindowHeight);


        if (bFixed)
        {
            // Fix up the frame window's size so that the screen's
            // size matches what the client passed in on the command line.
            // It would be better to somehow unify this logic with the
            // logic in the above "bFixed" block, but I haven't figure out
            // how to do that.
            ResizeToFitScreen();

            SetSashPosition(m_OriginalHeight);
        }

        m_RealCommander->GetHistory()->ScrollToBottom();

        // Commit to the docked commander.
        // m_Commander is NULL when this is called from the constructor.
        if (m_Commander != NULL)
        {
            // The wxWidgets documentation states that Destroy() does not
            // immediately destroy the window, but waits until the program is
            // idle.  This causes problems for test FMSLogo test pass, as
            // FMSLogo may not become idle if running many commands, leading to
            // a blank "Commander" dialog box being shown to the user, along
            // with the docked commander. To work around this, we hide this
            // commander from the user and rename it to hide it from
            // FindWindow().
            wxDialog * commander = static_cast<wxDialog*>(m_Commander);
            commander->Hide();
            commander->SetTitle(GetResourceString(L"LOCALIZED_COMMANDER")+ L" ");
            commander->Destroy();
        }
        m_Commander = m_RealCommander;
        m_Commander->Show();

        m_RealCommander->GiveControlToInputBox();

        m_CommanderIsDocked = true;
    }
}

void CMainFrame::SetSashPosition(int position)
{
    // The splitter is created with the SP_3D style, which means that it
    // has a 3D edge.  However, wxSplitterWindow::SetSashPosition() doesn't
    // consider this part of the sash and so will place the sash such that
    // the edge is above position.  Since we need pixel-exact placement
    // of the splitter, we subtract the top of the edge from position.
    int edgeHeight = wxSystemSettings::GetMetric(wxSYS_EDGE_Y);
    if (edgeHeight != -1)
    {
        position += edgeHeight;
    }

    m_Splitter->SetSashPosition(position);
}

#ifndef WX_PURE
#ifdef __WXMSW__

static bool IsDescendentOf(HWND PossibleDescendant, const wxWindow * Ancestor)
{
    for (HWND currentWindow = PossibleDescendant;
         currentWindow != NULL;
         currentWindow = GetParent(currentWindow))
    {
        if (currentWindow == static_cast<HWND>(Ancestor->GetHandle()))
        {
            return true;
        }
    }
         
    return false;
}

bool CMainFrame::TranslateKeyboardShortcut(MSG & Message)
{
    WXMSG * const message = static_cast<WXMSG*>(&Message);

    // Check if the message was generated on the commander's input.
    if (IsDescendentOf(Message.hwnd, m_RealCommander->GetInput()))
    {
        bool isHandled = m_RealCommander->GetInput()->GetAcceleratorTable()->Translate(
            m_RealCommander->GetInput(),
            message);
        if (isHandled)
        {
            return true;
        }
    }

    // Check if the message was generated on the commander's history.
    if (IsDescendentOf(Message.hwnd, m_RealCommander->GetHistory()))
    {
        bool isHandled = m_RealCommander->GetHistory()->GetAcceleratorTable()->Translate(
            m_RealCommander->GetHistory(),
            message);
        if (isHandled)
        {
            return true;
        }
    }

    // Check if the message was generated on the commander.
    if (IsDescendentOf(Message.hwnd, m_RealCommander))
    {
        bool isHandled = m_RealCommander->GetAcceleratorTable()->Translate(
            m_RealCommander,
            message);
        if (isHandled)
        {
            return true;
        }
    }

    // Search across all editors to see if this belongs to it.
    for (std::map<CWorkspaceEditor*,CWorkspaceEditor*>::const_iterator cursor = m_Editors.begin();
         cursor != m_Editors.end();
         ++cursor) {
        CWorkspaceEditor * const editor = cursor->first;
        if (IsDescendentOf(Message.hwnd, editor))
        {
            bool isHandled = editor->TranslateKeyboardShortcut(message);
            if (isHandled)
            {
                return true;
            }
        }
    }
        
    // Check if this message originated from the main frame.
    if (IsDescendentOf(Message.hwnd, this))
    {
        bool isHandled = MSWDoTranslateMessage(this, message);
        if (isHandled)
        {
            return true;
        }
    }

    // This was not translated as an accelerator.
    return false;
}

#endif // __WXMSW__
#endif // WX_PURE

bool CMainFrame::IsEditorOpen() const
{
    return !m_Editors.empty();
}

CWorkspaceEditor * CMainFrame::GetWorkspaceEditor()
{
    if (m_Editors.empty())
    {
        return NULL;
    }

    // return any of the editors (doesn't matter which one)
    return (*m_Editors.begin()).first;
}

CWorkspaceEditor *
CMainFrame::CreateWorkspaceEditor(
    const wxString & FileName,
    NODE           * EditArguments,
    bool             CheckForErrors,
    bool             OpenToError
    )
{
    // Construct the default coordinates of the editor's window
    // to be about 1/2 of the working area and placed in the center.
    int maxWidth;
    int maxHeight;
    GetWorkingAreaDimensions(maxWidth, maxHeight);

    int x = (int) (maxWidth * 0.25);
    int y = (int) (maxHeight * 0.25);
    int w = (int) (maxWidth * 0.75);
    int h = (int) (maxHeight * ScreenSz * 0.75);

    // If the user has some coordinates saved, use them, instead.
    GetConfigurationQuadruple(L"Editor", &x, &y, &w, &h); 
    checkwindow(&x, &y, &w, &h);

    // Determine the title
    wxString editorWindowTitle;
    if (EditArguments != NIL || CheckForErrors)
    {
        editorWindowTitle = GetResourceString(L"LOCALIZED_EDITOR_TITLE");
    }
    else
    {
        editorWindowTitle = FileName;
    }

    CWorkspaceEditor * editor = new CWorkspaceEditor(
        this,
        editorWindowTitle,
        wxPoint(x, y),
        wxSize(w, h),
        FileName,
        EditArguments,
        CheckForErrors,
        OpenToError);

    // Add this editor the the list of known editors.
    m_Editors.insert(std::pair<CWorkspaceEditor*,CWorkspaceEditor*>(editor,editor));

    return editor;
}

wxString CMainFrame::PromptUserForInput(const wchar_t *Prompt)
{
    // prompt the user for input
    CQuestionBox questionBox(this, Prompt, GetResourceString(L"LOCALIZED_INPUT"));
    int exitCode = questionBox.ShowModal();
    if (exitCode != wxID_OK)
    {
        return L"";
    }

    // Copy the user input to the Output string
    return questionBox.GetAnswer();
}

void
CMainFrame::PopupEditor(
    const wxString & FileName,
    NODE           * EditArguments,
    bool             CheckForErrors,
    bool             OpenToError
    )
{
    this->CreateWorkspaceEditor(
        FileName,
        EditArguments,
        CheckForErrors,
        OpenToError);
}

void CMainFrame::PopupEditorToError(const wchar_t *FileName)
{
    bool fileNameIsTempPathName = TempPathName.IsSameAs(FileName);
 
    // Copy the input file to the editor's temporary file.
    if (!fileNameIsTempPathName)
    {
        FILE * srcfile = 0;
#ifdef _WINDOWS
        srcfile= _wfopen(FileName, L"rb");
#else
        srcfile = fopen((const char*)FileName,"rb");
#endif
        if (srcfile != NULL)
        {
            FILE * dstfile = 0;
#ifdef _WINDOWS
            dstfile = _wfopen(TempPathName, L"wb");
#else
            dstfile = fopen((const char*)TempPathName,"wb");
#endif
            if (dstfile != NULL)
            {
                int ch = 0;
                while ((ch = fgetc(srcfile)) != EOF)
                {
                    fputc(ch, dstfile); //do not use fputwc!
                }
                fclose(dstfile);
            }
            fclose(srcfile);
        }
    }

    // Force the contents of the file to be processed for errors.
    // This updates g_CharactersSuccessfullyParsedInEditor so that the
    // editor can be opened to the point of the first error.
    endedit();

    // Calling endedit() throws an error.
    // We must clear the error from the evaluating engine and put
    // it into the commander.
    process_special_conditions();

    // Prompt the user to decide if they want to
    // open FileName in the editor.
    int rval = wxMessageBox(
        wxString::Format(GetResourceString(L"LOCALIZED_ERRORINFILEMESSAGE"), FileName),
		GetResourceString(L"LOCALIZED_ERRORINFILETITLE"),
        wxYES_NO | wxICON_ERROR);
    if (rval != wxYES)
    {
        // The user doesn't want to open the editor.

        // Cleanup the file that we created.
        if (!fileNameIsTempPathName)
        {
#ifdef _WINDOWS
            _wunlink(TempPathName);
#else
            unlink((const char*)TempPathName);
#endif
        }
        return;
    }

    this->CreateWorkspaceEditor(
		TempPathName, // use the temp file, in case the user saves changes
        NIL,
        true,  // check for errors
        true); // open to the error
}

static
void
CreateTemplateLogoFileForEditor(
    const wxString & FileName,
    NODE           * EditArguments
    )
{
	CFileTextStream* cfts = CFileTextStream::OpenForWrite(FileName, true);
	if (cfts != 0) {
		if (EditArguments != NIL) {
			cfts->WriteLine(To.GetName());
			cfts->WriteLine(End.GetName());
		}
		else 
		{
			cfts->WriteLine(wxString());
		}
		delete cfts;
	}
}


int
CMainFrame::PopupEditorForFile(
    const wxString & FileName,
    NODE           * EditArguments
    )
{
    // If no file (or empty) create template
	bool NeedToCreate = !wxFileExists(FileName);

	if (!NeedToCreate) {
		CFileTextStream* cfts = CFileTextStream::OpenForRead(FileName, false, true);
		if (cfts != 0) {			
			NeedToCreate = cfts->GetLength() == 0;
			delete cfts;
		}
	}

    if(NeedToCreate)
    {
        // file doesn't exist.  Create it.
        CreateTemplateLogoFileForEditor(FileName, EditArguments);
    }

    CFmsLogo::GetMainFrame()->PopupEditor(
        FileName,
        EditArguments,
        false,  // don't check for errors
        false); // no errors
    return 0;
}


void CMainFrame::CloseWorkspaceEditor(CWorkspaceEditor * Editor)
{
    m_Editors.erase(Editor);
}

CStatusDialog *
CMainFrame::GetStatusDialog()
{
    return m_StatusDialog;
}

void
CMainFrame::ClearStatusDialog()
{
    m_StatusDialog = NULL;
}

CScreen * CMainFrame::GetScreen()
{
    return m_Screen;
}

CCommander * CMainFrame::GetCommander()
{
    return m_RealCommander;
}

// Returns the window to which is it appropriate to send state change
// messages, such as minimizing, that are intended for the commander.
//
// If the commander is docked, this is the commander panel.
// If the commander is not docked, this is the top-level window that
// contains the commander panel.
//
wxWindow * CMainFrame::GetTopLevelWindowForCommander()
{
    return m_Commander;
}

// Gives focus to the next top-level window in the top-level window order.
// This should be called in response to processing a Ctrl+Tab keyboard
// sequence.
//
// From MSWLogo, the window order is:
//
//   Screen -> Commander -> Editor
//
// CurrentWindowFocus - The window that is currently selected.
// DirectionFlags     - wxNavigationKeyEvent::IsForward to move forward.
//
void
CMainFrame::KeyboardNavigateTopLevelWindow(
    wxWindow * CurrentWindowFocus,
    int        DirectionFlags
    )
{
    // In MSWLogo, the top-level window order is:
    //   Screen -> Commander -> Editor
    if (DirectionFlags & wxNavigationKeyEvent::IsForward)
    {
        if (CurrentWindowFocus == m_Screen)
        {
            if (m_CommanderIsDocked)
            {
                // Do nothing when the commander is docked.
                // This is the current FMSLogo behavior and there's
                // a separate bug to fix this.
            }
            else
            {
                m_Commander->SetFocus();
            }
        }
        else if (CurrentWindowFocus == m_Commander)
        {
            if (m_CommanderIsDocked)
            {
                // Do nothing when the commander is docked.
                // This is the current FMSLogo behavior and there's
                // a separate bug to fix this.
            }
            else
            {
                CWorkspaceEditor * editor = GetWorkspaceEditor();
                if (editor != NULL)
                {
                    // An editor exists, so give it focus
                    editor->SetFocus();
                }
                else
                {
                    // No editor exists, so skip it and move
                    // to the next window (the screen).
                    m_Screen->SetFocus();
                }
            }
        }
        else
        {
            // If this didn't come from the commander or the screen,
            // then it must have come from the editor.
            m_Screen->SetFocus();
        }
    }
    else
    {
        // MSWLogo doesn't support backward navigation.
    }
}

void CMainFrame::OnResize(wxSizeEvent& Event)
{
    if (m_CommanderIsDocked && bFixed && IsMaximized())
    {
        // If FMSLogo was started with the -F, then it is supposed
        // show the full screen without needing scrollbars.
        // However, if the splitter is manually moved or the frame
        // window is resized, then the full screen may no longer be visible.
        // Therefore, when FMSLogo is maximized and there are no expectations
        // about where the splitter should be placed, we can position it
        // back to showing the screen.  This allows a straight-forward was to
        // correct the splitter position.
        SetSashPosition(m_OriginalHeight);
    }

    Event.Skip();
}


void CMainFrame::OnClose(wxCloseEvent& Event)
{
    if (Event.CanVeto())
    {
        if (is_executing())
        {
            // The logo evaluation engine is still executing instructions.
            // We cannot safely close the application until it has finished.
            // Instead, we notify the evaluator that it should halt.
            // Once the evaluation stack has been unwound, it will post a new
            // close event which we will handle.
            exit_program();            
            Event.Veto();
            return;
        }

        // If an editor is running we could lose unsaved changes.
        CWorkspaceEditor * editor = GetWorkspaceEditor();
        if (editor != NULL)
        {
            // make sure that the editor is visible
            editor->Iconize(false);
            editor->Show();
            editor->Raise();

            // Notify the user that they will lose the changes
            // in this editor if they continue.

            // REVISIT: It might be better to invoke the wxID_EXIT
            // for each of the editors, so that we don't prompt the
            // user unless there really are changes to save, and so
            // that we prompt for all editors.
            if (wxMessageBox(
				GetResourceString(L"LOCALIZED_CHANGESINEDITORMAYBELOST"),
					GetResourceString(L"LOCALIZED_EDITSESSIONISRUNNING"),
                    wxOK | wxCANCEL | wxICON_QUESTION) != wxOK)
            {
                // The user doesn't want to shutdown.
                Event.Veto();
                return;
            }

            // The user wants to exit, anyway.
            // Close all of the editors to give them a chance
            // to clean up.
            while (editor != NULL)
            {
                // Close without a chance to veto
                editor->Close(true);

                // Get the next workspace
                editor = GetWorkspaceEditor();
            }
        }

        // If the workspace has unsaved changes, then give the
        // user a chance to abort shutdown.
        if (IsDirty)
        {
            CSaveBeforeExitDialog saveChangesDialog(this);
            int exitCode = saveChangesDialog.ShowModal();
            switch (exitCode)
            {
            case CSaveBeforeExitDialog::SAVEBEFOREEXIT_Cancel:
                // Don't exit FMSLogo
                IsTimeToHalt  = false;
                IsTimeToExit  = false;
                stopping_flag = RUN;
                Event.Veto();
                return;

            case CSaveBeforeExitDialog::SAVEBEFOREEXIT_SaveAndExit:
                // save and then exit

                // HACK: Set IsTimeToExit and IsTimeToHalt to false
                // so that writing the file to disk doesn't abort.
                // This is hack because the code should not modify
                // global variables--there should be a way to tell 
                // FileSave() to ignore errors.
                bool savedIsTimeToExit = IsTimeToExit;
                bool savedIsTimeToHalt = IsTimeToHalt;

                IsTimeToExit = false;
                IsTimeToHalt = false;
                bool isOk = FileSave(this->Unicode);
                if (!isOk)
                {
                    // Something went wrong (most likely, the user 
                    // pressed "Cancel" when asked to choose a filename).
                    // Give the user a chance to fix the problem.
                    IsTimeToHalt  = false;
                    IsTimeToExit  = false;
                    stopping_flag = RUN;
                    Event.Veto();
                    return;
                }

                IsTimeToExit = savedIsTimeToExit;
                IsTimeToHalt = savedIsTimeToHalt;
                break;
            }
        }
    }

    // If we made it here we are OK to exit.

    // Don't save the window size if it's minimized, the commander is undocked,
    // or if FMSLogo was started with the -F option.
    if (!IsIconized() && !bFixed)
    {
        if (m_CommanderIsDocked)
        {
            // Get location and size of our window on the screen so we can
            // come back up in the same spot next time we are invoked.
            const wxRect mainWindowRect = GetRect();

            // Save the current location of the screen.
            SetConfigurationQuadruple(
                L"Screen",
                mainWindowRect.GetLeft(),
                mainWindowRect.GetTop(),
                mainWindowRect.GetWidth(),
                mainWindowRect.GetHeight());

            // Save the location of the splitter.
            SetConfigurationInt(
                L"CommanderHeight",
                m_Commander->GetSize().GetHeight());
        }
        else
        {
            if (!static_cast<CCommanderDialog*>(m_Commander)->IsIconized())
            {
                // Save the commander's position
                const wxRect windowRectangle = m_Commander->GetRect();

                SetConfigurationQuadruple(
					L"CommanderWindow",
                    windowRectangle.GetLeft(),
                    windowRectangle.GetTop(),
                    windowRectangle.GetWidth(),
                    windowRectangle.GetHeight());
            }
        }
    }

    // Cleanup the pens
#ifndef WX_PURE
    // REVISIT: This is where the pens were destroyed in MSWLogo,
    // but it doesn't seem like the right place for it.
    if (g_NormalPen != NULL)
    {
        DeleteObject(g_NormalPen);
        g_NormalPen = NULL;
    }

    if (g_ErasePen != NULL)
    {
        DeleteObject(g_ErasePen);
        g_ErasePen = NULL;
    }
#endif

    // Because the timer events are scheduled on
    // the main window's HWND, we must uninitialize them
    // before the main window is destroyed.
    uninitialize_timers();

    // Invoke the default handler, which is to destroy
    // the window and shut down.
    Event.Skip();
}

void CMainFrame::OnSetCursor(wxSetCursorEvent& Event)
{
    // For compatability with MSWLogo, when FMSLogo is able to process
    // messages, any call to SETCURSORWAIT which may have set the cursor
    // to an hourglass is implicitly cleared.
    // This happened as a side-effect of the win32 ::SetCursor() function,
    // which restores the cursor when the mouse is moved.
    lsetcursorarrow(NIL);

    // Invoke the default handler.
    Event.Skip();
}


// menu command handlers
void CMainFrame::OnExit(wxCommandEvent& WXUNUSED(Event))
{
    // Attempt to close the application while
    // giving the user an opportunity to abort
    // the operation.
    Close(false);
}

// CONSIDER: move this to wrksp.c, since it has no coheasion
// with the UI.
static void EraseContentsOfWorkspace()
{
    NODE * workspace_contents;

    // erase the unburied contents of the workspace
    workspace_contents = cons_list(lcontents(NIL));
    lerase(workspace_contents);
    gcref(workspace_contents);

    // erase the buried contents of the workspace
    workspace_contents = cons_list(lburied(NIL));
    lerase(workspace_contents);
    gcref(workspace_contents);

    // Many non-English translations either translate the names of
    // library procedures using a COPYDEF or implement complete replacements
    // within their startup.logoscript file.  Since the intention of erasing the
    // workspace was to restore FMSLogo to its original state (not to erase
    // translated versions of library procedures), we restore them by reloading
    // the startup.logoscript file.

    // If a startup.logscript file contains a COPYDEF, then loading it will
    // load any file whose name matches the copied routine. For example,
    // if startup.logoscript runs the instruction
    //  
    //     COPYDEF "MYPROC "PROC
    //
    // Then FMSLogo would attempt to load "PROC.LGO from the current working
    // directory.  If such a file exists and contains logo procedures, then
    // instead of erasing the workspace, we'd end up with the contents of that
    // file in the workpace, which is not what was desired.
    //
    // To avoid this, or rather to have the same behavior as when FMSLogo first
    // started, we switch to the FMSLogo directory before loading the
    // startup.logoscript file.
    const wxString savedWorkingDirectory(wxGetCwd());
    wxSetWorkingDirectory(g_FmslogoBaseDirectory);

    // Load the startup script.
    fileload(g_FmslogoBaseDirectory + L"startup.logoscript");

    // Restore the previous working directory.
    wxSetWorkingDirectory(savedWorkingDirectory);

    // Now that the workspace has no user changes, mark it as not needing to
    // be saved.
    IsDirty = false;
}

void CMainFrame::OnFileNew(wxCommandEvent& WXUNUSED(Event))
{
    if (IsDirty)
    {
        // Warn the user that File-New will erase the contents 
        // of the workspace and give them a chance to cancel the
        // operation.
        if (wxMessageBox(
			GetResourceString(L"LOCALIZED_FILENEWWILLERASEWORKSPACE"),
			GetResourceString(L"LOCALIZED_YOUHAVEUNSAVEDCHANGES"),
                wxOK | wxCANCEL | wxICON_QUESTION,
                GetTopLevelWindowForCommander()) == wxCANCEL)
        {
            return;
        }
    }

    // else start with a clean plate
    m_IsNewFile = true;
	this->Unicode = false;
    EraseContentsOfWorkspace();
}

void CMainFrame::OnFileLoad(wxCommandEvent& WXUNUSED(Event))
{
    if (IsDirty)
    {
        // Warn the user that File-Load may erase the contents 
        // of the workspace and give them a chance to cancel the
        // operation.
        if (wxMessageBox(
			GetResourceString(L"LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE"),
				GetResourceString(L"LOCALIZED_YOUHAVEUNSAVEDCHANGES"),
                wxOK | wxCANCEL | wxICON_QUESTION,
                GetTopLevelWindowForCommander()) == wxCANCEL)
        {
            return;
        }
    }

    // show the user a file-picker dialog
    const wxString fileToLoad = wxFileSelector(
		GetResourceString(L"LOCALIZED_FILE_LOAD_DIALOG_TITLE"), // title/message
        m_LastLoadedLogoFile.GetPath(),             // default path
        m_LastLoadedLogoFile.GetFullName(),         // default file name
		GetResourceString(L"LOCALIZED_LOGO_FILE_EXTENSION"),    // default file extension
		GetResourceString(L"LOCALIZED_FILEFILTER_LOGO"),        // file filters
        wxFD_OPEN | wxFD_FILE_MUST_EXIST,           // flags
        this);                                      // parent window
    if (!fileToLoad.empty())
    {
        // The user made a selection.
        // Save it for seeding a default in future dialog boxes.
        m_LastLoadedLogoFile.Assign(fileToLoad);

        // For compatibility with MSWLogo, we adopt the same logic that
        // exists within the win32 API, which is to change the current
        // working directory to whatever directory the file is in.
        // Otherwise, files which are loaded by this dialog cannot
        // "LOAD" other files within the same directory.
        wxSetWorkingDirectory(m_LastLoadedLogoFile.GetPath());

        m_IsNewFile = false;

        start_execution();

        bool isOk = fileload(fileToLoad,&this->Unicode);
        if (!isOk)
        {
            err_logo(
                FILE_ERROR,
                make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN")));
        }

        // handle any error that may have occured
        process_special_conditions();

        stop_execution();
    }
}

void CMainFrame::OnFileOpen(wxCommandEvent& WXUNUSED(Event))
{
    if (IsDirty)
    {
        // Warn the user that File-Open will erase the contents 
        // of the workspace and give them a chance to cancel the
        // operation.
        if (wxMessageBox(
			GetResourceString(L"LOCALIZED_FILEOPENWILLERASEWORKSPACE"),
			GetResourceString(L"LOCALIZED_YOUHAVEUNSAVEDCHANGES"),
                wxOK | wxCANCEL | wxICON_QUESTION,
                GetTopLevelWindowForCommander()) == wxCANCEL)
        {
            return;
        }
    }

    // show the user a file-picker dialog
    const wxString fileToLoad = wxFileSelector(
		GetResourceString(L"LOCALIZED_FILE_OPEN_DIALOG_TITLE"), // title/message
        m_LastLoadedLogoFile.GetPath(),             // default path
        m_LastLoadedLogoFile.GetFullName(),         // default file name
		GetResourceString(L"LOCALIZED_LOGO_FILE_EXTENSION"),    // default file extension
		GetResourceString(L"LOCALIZED_FILEFILTER_LOGO"),        // file filters
        wxFD_OPEN | wxFD_FILE_MUST_EXIST,           // flags
        this);                                      // parent window
    if (!fileToLoad.empty())
    {
        // erase the contents of the workspace
        EraseContentsOfWorkspace();

        // The user made a selection.
        // Save it for seeding a default in future dialog boxes.
        m_LastLoadedLogoFile.Assign(fileToLoad);

        // For compatibility with MSWLogo, we adopt the same logic that
        // exists within the win32 API, which is to change the current
        // working directory to whatever directory the file is in.
        // Otherwise, files which are loaded by this dialog cannot
        // "LOAD" other files within the same directory.
        wxSetWorkingDirectory(m_LastLoadedLogoFile.GetPath());

        // start with a clean plate
        m_IsNewFile = false;

        start_execution();

        bool isOk = fileload(fileToLoad, &this->Unicode);
        if (!isOk)
        {
            err_logo(
                FILE_ERROR,
                make_static_strnode(GetResourceString(L"LOCALIZED_ERROR_FILESYSTEM_CANTOPEN")));
        }

        // handle any error that may have occured
        process_special_conditions();

        stop_execution();
    }
}

// Displays a warning if the workspace is empty
// and therefore if saving it would save an empty
// file, which is probably not what the user expects.
//
// returns true, if we should continue to save the workspace.
// returns false, if we should not save the workspace.
bool CMainFrame::WarnIfSavingEmptyWorkspace()
{
    // Check if there's something in the workspace that
    // isn't buried (which would be saved).
    if (!something_is_unburied())
    {
#ifndef WX_PURE
        // TODO: use wxMessageBox if it supports default buttons
        if (MessageBox(
                static_cast<HWND>(GetHandle()),
                GetResourceString(L"LOCALIZED_EMPTYWORKSPACE_MESSAGE"),
                GetResourceString(L"LOCALIZED_EMPTYWORKSPACE_TITLE"),
                MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        {
            return false;
        }
#endif
    }

    return true;
}

// Prompts the user for the name of the file to save
// the contents as, then saves the file.
//
// Returns "true" if the user saves the file.
// Returns "false" if the user cancels the save or if the 
// file couldn't be saved for other reasons.
bool CMainFrame::SaveFileAs(bool Unicode)
{
    // if new, then nulify File name
    if (m_IsNewFile)
    {
        m_LastLoadedLogoFile.Clear();
    }

    // Get file name from user and then save the file
    bool isOk = false;
    const wxString fileToSave = wxFileSelector(
		GetResourceString(L"LOCALIZED_FILE_SAVE_DIALOG_TITLE"), // title/message
        m_LastLoadedLogoFile.GetPath(),             // default path
        m_LastLoadedLogoFile.GetFullName(),         // default file name
		GetResourceString(L"LOCALIZED_LOGO_FILE_EXTENSION"),    // default file extension
		GetResourceString(L"LOCALIZED_FILEFILTER_LOGO"),        // file filters
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT,          // flags
        this);                                      // parent window
    if (!fileToSave.empty())
    {
        // The user made a selection.
        // Save it for seeding a default in future dialog boxes.
        m_LastLoadedLogoFile.Assign(fileToSave);
		//alsol keep the unicode choice of this operation
		this->Unicode = Unicode;
        // For compatibility with MSWLogo, we adopt the same logic that
        // exists within the win32 API, which is to change the current
        // working directory to whatever directory the file is in.
        // This is more important for load/open, and I don't know if this
        // is even needed for saving.
        wxSetWorkingDirectory(m_LastLoadedLogoFile.GetPath());

        m_IsNewFile = false;
        isOk = SaveFile(Unicode);
    }
    else
    {
        isOk = false;
    }

    return isOk;
}

bool CMainFrame::SaveFile(bool Unicode)
{
    filesave(m_LastLoadedLogoFile.GetFullPath(),Unicode);

    // handle any error that may have occured
    process_special_conditions();

    // BUG: don't assume the file was saved
    return true;
}


bool CMainFrame::FileSave(bool Unicode)
{
    bool isOk = false;

    if (m_IsNewFile)
    {
        // The file has never been saved, so we don't know
        // what file we should save it to.
        // Ask the user with a "Save As" dialog.
        isOk = SaveFileAs(Unicode);
    }
    else
    {
        // Save the file
        isOk = SaveFile(Unicode);
    }

    return isOk;
}

void CMainFrame::OnFileSave(wxCommandEvent& WXUNUSED(Event))
{
    if (!WarnIfSavingEmptyWorkspace())
    {
        return;
    }

    FileSave(this->Unicode);
}

void CMainFrame::OnFileSaveAs(wxCommandEvent& WXUNUSED(Event))
{
    if (!WarnIfSavingEmptyWorkspace())
    {
        return;
    }
	//use unicode if it is oringinally set as unicode
    SaveFileAs(this->Unicode);
}

void CMainFrame::OnFileSaveAsUTF8(wxCommandEvent & Event)
{
	//TODO:
}

void CMainFrame::OnFileSaveAsUTF16(wxCommandEvent & Event)
{
	if (!WarnIfSavingEmptyWorkspace())
	{
		return;
	}
	//force unicode this time
	SaveFileAs(true);
}

#ifndef WX_PURE

// Gets the full path to where the FMSLogo screensaver
// should be located (if it's installed).
static
wxString
GetScreenSaverFilePath()
{
    static const wchar_t screenSaverFileName[] = L"\\fmslogo.scr";

	wxString sysDir = GetFullTextReversed(GetSystemDirectory);
	
	return sysDir + screenSaverFileName;
}

#endif


static
bool ScreenSaverIsInstalled()
{
#ifdef WX_PURE
    return false;
#else
	wxString screenSaverPath = GetScreenSaverFilePath();

    // check for the file's existence
    DWORD fileAttributes = GetFileAttributes(screenSaverPath);
    if (fileAttributes == INVALID_FILE_ATTRIBUTES)
    {
        // The screen saver does not exist.
        return false;
    }

    // The screen saver exists.
    return true;
#endif // WX_PURE
}

void CMainFrame::OnUpdateFileSetAsScreenSaver(wxUpdateUIEvent& Event)
{
    // Enable this option if a screen saver is installed.
    Event.Enable(ScreenSaverIsInstalled());
}

void CMainFrame::OnFileSetAsScreenSaver(wxCommandEvent& WXUNUSED(Event))
{
    // Before we save the workspace, we should ensure that a
    // startup procedure exists.  If not, their screen saver won't
    // do anything.
    NODE * startup = Startup.GetValue();

    CSelectStartupInstructionDialog::EXPLAINTEXT explainText;
    if (startup == Unbound)
    {
        explainText = CSelectStartupInstructionDialog::EXPLAINTEXT_StartupNotDefined;
    }
    else if (startup == NIL)
    {
        explainText = CSelectStartupInstructionDialog::EXPLAINTEXT_StartupEmpty;
    }
    else if (!is_list(startup))
    {
        explainText = CSelectStartupInstructionDialog::EXPLAINTEXT_StartupNotList;
    }
    else
    {
        explainText = CSelectStartupInstructionDialog::EXPLAINTEXT_None;
    }

    if (explainText != CSelectStartupInstructionDialog::EXPLAINTEXT_None)
    {
        CSelectStartupInstructionDialog dialog(this, explainText);
        int exitCode = dialog.ShowModal();
        if (exitCode == wxID_CANCEL)
        {
            // The user hasn't selected a startup instruction list,
            // so there's no sense in setting this program to
            // be a screen saver.
            return;
        }

        // Make "Startup [<instructionlist>]

        RunLogoInstructionFromGui(wxString::Format(L"%s \"%s [%s]", 
			GetResourceString(L"LOCALIZED_ALTERNATE_MAKE"), 
			GetResourceString(L"LOCALIZED_ALTERNATE_STARTUP"), 
			(const wchar_t*)dialog.GetSelectedInstruction()));
        
    }

#ifdef __WXMSW__
    LPITEMIDLIST itemIdList;

    // Get a handle to a folder where we can store personal documents.
    // Note that we call the defunct SHGetSpecialFolderLocation()
    // because it is supported as far back as Windows 95.
    HRESULT hr = SHGetSpecialFolderLocation(
        NULL,
        CSIDL_PERSONAL,
        &itemIdList);
    if (SUCCEEDED(hr))
    {
		wchar_t screenSaverProgramBuffer[MAX_PATH + 1] = { 0 };

        // Get a handle to a folder where we can store personal documents.
        BOOL isOk = SHGetPathFromIDList(
            itemIdList,
			screenSaverProgramBuffer);
        if (isOk)
        {
			wxString screenSaverProgramName = screenSaverProgramBuffer;

			screenSaverProgramName += L"\\screensaver.lgo";

            filesave(screenSaverProgramName);

            // handle any error that may have occured
            process_special_conditions();

            // Configure this file as the screensaver
            SetConfigurationString(L"ScreenSaverFile", screenSaverProgramName);

            // Best-effort to set the Logo screensaver 
            // to be the active screensaver
			wxString screenSaverPath = GetScreenSaverFilePath();
            if (screenSaverPath.length()>0)
            {
                HKEY desktopKey = NULL;

                LONG result = RegOpenKeyEx(
                    HKEY_CURRENT_USER,
                    L"Control Panel\\Desktop",
                    0,      // reserved
                    KEY_SET_VALUE,
                    &desktopKey);
                if (result == ERROR_SUCCESS)
                {
                    result = RegSetValueEx(
                        desktopKey,
                        L"SCRNSAVE.EXE",
                        0,
                        REG_SZ,
                        (BYTE*)((const wchar_t*)screenSaverPath),
                        wcslen(screenSaverPath) + 1);

                    RegCloseKey(desktopKey);
                }
            }
        }
        CoTaskMemFree(itemIdList);
    }
#endif

}

void CMainFrame::OnEditProcedure(wxCommandEvent& WXUNUSED(Event))
{
    CEditProcedureDialog dlg(this);
    dlg.DoDialog();
}

void CMainFrame::OnEraseProcedure(wxCommandEvent& WXUNUSED(Event))
{
    CEraseProcedureDialog dlg(this);
    dlg.DoDialog();
}

void CMainFrame::OnBitmapNew(wxCommandEvent& WXUNUSED(Event))
{
    // Reset the on-screen bitmap
    ibm_clear_screen();

    // Mark the bitmap as not ever having been saved.
    m_IsNewBitmap = true;
}

void CMainFrame::OnBitmapOpen(wxCommandEvent& WXUNUSED(Event))
{
    const wxString fileToLoad = wxFileSelector(
		GetResourceString(L"LOCALIZED_BITMAP_OPEN_DIALOG_TITLE"), // title/message
        m_LastLoadedBitmapFile.GetPath(),             // default path
        m_LastLoadedBitmapFile.GetFullName(),         // default file name
		wxString(L".bmp"),                             // default file extension
		GetResourceString(L"LOCALIZED_FILEFILTER_IMAGE"),         // file filters
        wxFD_OPEN | wxFD_FILE_MUST_EXIST,             // flags
        this);                                        // parent window
    if (!fileToLoad.empty())
    {
        // The user made a selection.
        // Save it for seeding a default in future dialog boxes.
        m_LastLoadedBitmapFile.Assign(fileToLoad);

        unsigned int dwPixelWidth  = 1;
        unsigned int dwPixelHeight = 1;

        m_IsNewBitmap = false;

        ERR_TYPES status;
        if (m_LastLoadedBitmapFile.GetExt().IsSameAs(wxString(L".gif"), false))
        {
            status = gifload_helper(
				/*WXSTRING_TO_STRING*/(m_LastLoadedBitmapFile.GetFullPath()),
                dwPixelWidth,
                dwPixelHeight);
        }
        else
        {
            status = LoadBitmapFile(
				/*WXSTRING_TO_STRING*/(m_LastLoadedBitmapFile.GetFullPath()),
                dwPixelWidth,
                dwPixelHeight);
        }

        if (status != SUCCESS)
        {
            ShowErrorMessage(status);
        }
    }
}

void CMainFrame::SaveBitmap()
{
    ERR_TYPES status;
    if (m_LastLoadedBitmapFile.GetExt().IsSameAs(wxString(L".gif"), false))
    {
        status = gifsave_helper(
			/*WXSTRING_TO_STRING*/(m_LastLoadedBitmapFile.GetFullPath()),
            -1,
            0,
            -1,
            -1,
            8);
    }
    else
    {
        status = DumpBitmapFile(
			/*WXSTRING_TO_STRING*/(m_LastLoadedBitmapFile.GetFullPath()),
            32);
    }

    if (status != SUCCESS)
    {
        ShowErrorMessage(status);
    }
}

void CMainFrame::SaveBitmapAs()
{
    // if new then nulify File name
    if (m_IsNewBitmap)
    {
        m_LastLoadedBitmapFile.Clear();
    }

    // Get file name from user
    const wxString fileToSave = wxFileSelector(
		GetResourceString(L"LOCALIZED_BITMAP_SAVE_DIALOG_TITLE"), // title/message
        m_LastLoadedBitmapFile.GetPath(),             // default path
        m_LastLoadedBitmapFile.GetFullName(),         // default file name
		wxString(L".bmp"),                             // default file extension
		GetResourceString(L"LOCALIZED_FILEFILTER_IMAGE"),         // file filters
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT,            // flags
        this);                                        // parent window
    if (!fileToSave.empty())
    {
        // The user made a selection.
        // Save it for seeding a default in future dialog boxes.
        m_LastLoadedBitmapFile.Assign(fileToSave);

        // Save the bitmap using the new file name
        m_IsNewBitmap = false;
        SaveBitmap();
    }
}

void CMainFrame::OnBitmapSave(wxCommandEvent& WXUNUSED(Event))
{
    // if new file then switch to save file as, else save
    if (m_IsNewBitmap)
    {
        SaveBitmapAs();
    }
    else
    {
        SaveBitmap();
    }
}

void CMainFrame::OnBitmapSaveAs(wxCommandEvent& WXUNUSED(Event))
{
    SaveBitmapAs();
}

void CMainFrame::InitializePrinter()
{
    // Read the default page settings.
    // On Windows, even though we call ShowModal, no
    // dialog box is displayed because we set the
    // default info to true.
    if (m_PageSetupData.GetDefaultInfo())
    {
#ifdef __WXMSW__
        m_PageSetupData.SetDefaultMinMargins(true);
        wxPageSetupDialog pageSetup(this, &m_PageSetupData);
        if (pageSetup.ShowModal() == wxID_OK)
        {
            // Save the updated preferences.
            m_PageSetupData = pageSetup.GetPageSetupData();
        }
#endif

        // Mark the printer data as having been initialized.
        m_PageSetupData.SetDefaultInfo(false);
    }
}

void CMainFrame::OnBitmapPrint(wxCommandEvent& WXUNUSED(Event))
{
    InitializePrinter();

    wxPrintDialogData printDialogData(m_PageSetupData.GetPrintData());

    // Show the printer selection dialog box.
    wxPrinter printer(&printDialogData);

    // FMSLogo always scales the active area of the screen to fit on a
    // single page, so we disable page number selection to prevent confusion.
    printDialogData.EnablePageNumbers(false);

    CLogoPicturePrintout printout(
		GetResourceString(L"LOCALIZED_GENERAL_PRODUCTNAME"),
        *m_Screen,
        m_PageSetupData);

    if (!printer.Print(this, &printout, true))
    {
        // This can happen in two cases:
        // 1) If there was an error while printing, in which
        //    case the operating system will have communicated
        //    the problem to the user, so we don't need to.
        // 2) If the print job was cancelled by the user,
        //    in which case we don't need to tell the user
        //    that they cancelled the job.
        //
        // Therefore, all we need to do is exit.
        return;
    }

    // Preserve the printr settings for the next time.
    m_PageSetupData.SetPrintData(printer.GetPrintDialogData().GetPrintData());
}

void CMainFrame::OnBitmapPrinterSetup(wxCommandEvent& WXUNUSED(Event))
{
    InitializePrinter();

    // Show a dialog box for updating the page setup
    wxPageSetupDialog pageSetup(this, &m_PageSetupData);
    if (pageSetup.ShowModal() == wxID_OK)
    {
        // The user pressed OK on the dialog box.
        // Save the updated preferences.
        m_PageSetupData = pageSetup.GetPageSetupData();
    }
}

void CMainFrame::OnSetPenSize(wxCommandEvent& WXUNUSED(Event))
{
    if (m_SetPenSizeDialog == NULL)
    {
        const int initialSize = get_pen_width();

        m_SetPenSizeDialog = new CSetPenSize(
            this,
            initialSize,
            m_SetPenSizeDialog);

        m_SetPenSizeDialog->Show();
    }
    else
    {
        m_SetPenSizeDialog->SetFocus();
    }
}

void
CMainFrame::SetColorHelper(
    CSetColor * &   SetColorDialog,
    const wchar_t  *   DialogTitle,
    wxUint32        InitialColor,
    const wchar_t  *   LogoCommand
    )
{
    if (SetColorDialog == NULL)
    {
        const wxColor initialColor(InitialColor);

        SetColorDialog = new CSetColor(
            this,
            DialogTitle,
            initialColor,
            LogoCommand,
            SetColorDialog);

        SetColorDialog->Show();
    }
    else
    {
        SetColorDialog->SetFocus();
    }
}


void CMainFrame::OnSetPenColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetPenColorDialog,
        GetResourceString(L"LOCALIZED_SETCOLOR_PENCOLOR"),
        pcolor,
        GetResourceString(L"LOCALIZED_ALTERNATE_SETPENCOLOR"));
}

void CMainFrame::OnSetFloodColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetFloodColorDialog,
        GetResourceString(L"LOCALIZED_SETCOLOR_FLOODCOLOR"),
        fcolor,
			GetResourceString(L"LOCALIZED_ALTERNATE_SETFLOODCOLOR"));
}

void CMainFrame::OnSetScreenColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetScreenColorDialog,
        GetResourceString(L"LOCALIZED_SETCOLOR_SCREENCOLOR"),
        scolor,
        GetResourceString(L"LOCALIZED_ALTERNATE_SETSCREENCOLOR"));
}

void CMainFrame::ShowStatus()
{
    // create a new status dialog, if necessary
    if (!StatusDialogIsShowing())
    {
        m_StatusDialog = new CStatusDialog(this);
        m_StatusDialog->PopulateAllFields();
        m_StatusDialog->Show();
    }
}

void CMainFrame::HideStatus()
{
    // destroy the status dialog
    if (StatusDialogIsShowing())
    {
        m_StatusDialog->Close();
        m_StatusDialog = NULL;
    }
}

bool CMainFrame::StatusDialogIsShowing()
{
    return m_StatusDialog != NULL;
}

void CMainFrame::OnSetActiveArea(wxCommandEvent& WXUNUSED(Event))
{
    bool isOk;

    do
    {
        isOk = true;

        CSetActiveArea printerArea(
            this,
            g_PrinterAreaXLow,
            g_PrinterAreaXHigh,
            g_PrinterAreaYLow,
            g_PrinterAreaYHigh,
            g_PrinterAreaPixels);
        if (printerArea.ShowModal() == wxID_OK)
        {
            // the user did not cancel, so commit to the new settings
            int xLow;
            int xHigh;
            int yLow;
            int yHigh;
            printerArea.GetActiveArea(xLow, xHigh, yLow, yHigh);

            // Validate the area
            if (xLow >= xHigh || yLow >= yHigh)
            {
                // The settings are no good.  Notify the user and try again.
                wxMessageBox(
					GetResourceString(L"LOCALIZED_ERROR_BADINPUT"),
						GetResourceString(L"LOCALIZED_ACTIVEAREA"));
                isOk = false;
            }
            else
            {
                // The settings are ok.
                // Use them.
                int pixelsPerInch;
                printerArea.GetPixelsPerInch(pixelsPerInch);

                g_PrinterAreaXLow   = xLow;
                g_PrinterAreaXHigh  = xHigh;
                g_PrinterAreaYLow   = yLow;
                g_PrinterAreaYHigh  = yHigh;
                g_PrinterAreaPixels = pixelsPerInch;
                if (g_PrinterAreaPixels < 1)
                {
                    g_PrinterAreaPixels = 1;
                }
 
                // Persist the new settings
                SetConfigurationInt(L"Printer.XLow",   g_PrinterAreaXLow);
                SetConfigurationInt(L"Printer.XHigh",  g_PrinterAreaXHigh);
                SetConfigurationInt(L"Printer.YLow",   g_PrinterAreaYLow);
                SetConfigurationInt(L"Printer.YHigh",  g_PrinterAreaYHigh);
                SetConfigurationInt(L"Printer.Pixels", g_PrinterAreaPixels);
            }
        }
    } while (!isOk);
}
extern wxString NormalizeCaseForDisplay(wxString text);

void CMainFrame::OnSetLabelFont(wxCommandEvent& WXUNUSED(Event))
{
    wxFontDialog fontChooser;

    // Seed the font picker with the current label font
    const wxFont labelFont = GetLabelFont();
    fontChooser.GetFontData().SetInitialFont(labelFont);

    // Disable color selection, since we use the pencolor instead.
    fontChooser.GetFontData().EnableEffects(false);

    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // The user selected a new font.

#ifdef __WXMSW__ 

        // Get the LOGFONT struct from the wxFont
        const wxFont newFont = fontChooser.GetFontData().GetChosenFont();
        const class wxNativeFontInfo * fontInfo = newFont.GetNativeFontInfo();
        if (fontInfo != NULL)
        {
            const class wxNativeFontInfo * nativeFontInfo = (class wxNativeFontInfo*)fontInfo;

            // commit to the new font
			wxString slf = GetResourceString(L"LOCALIZED_ALTERNATE_SETLABELFONT");
			wxString setlabelfont = NormalizeCaseForDisplay(slf);

			wxString logoInstruction = wxString::Format(
                L"%s [[%s] %ld %ld %ld %ld %d %d %d %d %d %d %d %d]",
                setlabelfont,
                nativeFontInfo->lf.lfFaceName,
                nativeFontInfo->lf.lfHeight,
                nativeFontInfo->lf.lfWidth,
                nativeFontInfo->lf.lfOrientation,
                nativeFontInfo->lf.lfWeight,
                nativeFontInfo->lf.lfItalic,
                nativeFontInfo->lf.lfUnderline,
                nativeFontInfo->lf.lfStrikeOut,
                nativeFontInfo->lf.lfCharSet,
                nativeFontInfo->lf.lfOutPrecision,
                nativeFontInfo->lf.lfClipPrecision,
                nativeFontInfo->lf.lfQuality,
                nativeFontInfo->lf.lfPitchAndFamily);

            RunLogoInstructionFromGui(logoInstruction);
        }
#endif
    }
}

void CMainFrame::OnSetCommanderFont(wxCommandEvent& WXUNUSED(Event))
{
    m_RealCommander->ChooseNewFont();
}

void CMainFrame::OnZoomIn(wxCommandEvent& WXUNUSED(Event))
{
    zoom_helper(the_zoom * 2.0);
}

void CMainFrame::OnZoomOut(wxCommandEvent& WXUNUSED(Event))
{
    zoom_helper(the_zoom * 0.5);
}

void CMainFrame::OnZoomNormal(wxCommandEvent& WXUNUSED(Event))
{
    zoom_helper(1.0);

#if wxUSE_STATUSBAR
    // TODO: Delete this.  It's just a reminder on how to write
    // to the status bar.
    wxLogStatus(this, wxString(L"Zoom is now %f"), the_zoom);
#endif
}

void CMainFrame::OnHelp(wxCommandEvent& WXUNUSED(Event))
{
    do_help(wxString());
}

#if MANUAL_HAS_TRANSLATION_TABLES

void CMainFrame::OnHelpLanguageToEnglish(wxCommandEvent& WXUNUSED(Event))
{
    do_help("To English (procedure names)");
}

void CMainFrame::OnHelpEnglishToLanguage(wxCommandEvent& WXUNUSED(Event))
{
    do_help("From English (procedure names)");
}

#endif // MANUAL_HAS_TRANSLATION_TABLES

void CMainFrame::OnHelpTutorial(wxCommandEvent& WXUNUSED(Event))
{
    do_help(L"Where to Start");
}

void CMainFrame::OnHelpDemo(wxCommandEvent& WXUNUSED(Event))
{
    do_execution(L"demo");
}

void
CMainFrame::OpenFileWithDefaultApplication(
    const wchar_t *  FileName
    )
{
#ifndef WX_PURE
    HINSTANCE childApplication = ShellExecute(
        static_cast<HWND>(GetHandle()), // handle to parent window
        L"open",                         // operation to perform
        FileName,                       // pointer to filename string
        NULL,                           // pointer to string that specifies executable-file parameters
        NULL,                           // pointer to string that specifies default directory
        SW_SHOWNORMAL);                 // whether file is shown when opened
    if (childApplication != NULL)
    {
		//TODO: why invalid handle?
        //CloseHandle(childApplication);
    }
#endif
}

void CMainFrame::OnHelpExamples(wxCommandEvent& WXUNUSED(Event))
{
    OpenFileWithDefaultApplication(g_FmslogoBaseDirectory + L"EXAMPLES\\INDEX.HTML");
}

void CMainFrame::OnHelpReleaseNotes(wxCommandEvent& WXUNUSED(Event))
{
    OpenFileWithDefaultApplication(g_FmslogoBaseDirectory + L"README.TXT");
}

void CMainFrame::OnAboutFmsLogo(wxCommandEvent& WXUNUSED(Event))
{
    // show the "About FMSLogo" dialog box
    CAboutFmsLogo dlg(this);
    dlg.ShowModal();
}

void CMainFrame::OnAboutMultipleSclerosis(wxCommandEvent& WXUNUSED(Event))
{
    // show the "About FMS" dialog box
    CAboutMultipleSclerosis dlg(this);
    dlg.ShowModal();
}

void
CMainFrame::PostCheckQueueMessage()
{
#ifndef WX_PURE
    PostMessage(
        static_cast<HWND>(GetHandle()),
        WM_CHECKQUEUE,
        0,
        0);
#endif
}

#ifndef WX_PURE

WXLRESULT
CMainFrame::MSWWindowProc(
    WXUINT   Message,
    WXWPARAM WParam,
    WXLPARAM LParam
    )
{
    switch (Message)
    {
    case WM_TIMER:
        if (WParam < 16)
        {
            // not safe to yield
            callthing * callevent = callthing::CreateNoYieldFunctionEvent(timer_callback[WParam]);
            calllists.insert(callevent);
            PostCheckQueueMessage();
        }
        else if (WParam < 32)
        {
            // yieldable
            callthing * callevent = callthing::CreateFunctionEvent(timer_callback[WParam]);
            calllists.insert(callevent);
            PostCheckQueueMessage();
        }
        break;

    case WM_CHECKQUEUE:
        checkqueue();
        break;

    case MM_MCINOTIFY:
        // if user fired up a callback mci event then queue it up here
        {
            callthing * callevent = callthing::CreateNoYieldFunctionEvent(mci_callback);
            calllists.insert(callevent);
            PostCheckQueueMessage();
        }
        break;

    case WM_NETWORK_CONNECTSENDACK:
        g_ClientConnection.OnConnectSendAck(
            static_cast<HWND>(GetHandle()),
            LParam);
        break;

    case WM_NETWORK_CONNECTSENDFINISH:
        g_ClientConnection.OnConnectSendFinish(
            static_cast<HWND>(GetHandle()),
            LParam);
        break;

    case WM_NETWORK_LISTENRECEIVEACK:
        g_ServerConnection.OnListenReceiveAck(
            static_cast<HWND>(GetHandle()),
            LParam);
        break;
    }

    return wxFrame::MSWWindowProc(Message, WParam, LParam);
}

#endif // WX_PURE

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_MENU(ID_FILENEW, CMainFrame::OnFileNew)
EVT_MENU(ID_FILELOAD, CMainFrame::OnFileLoad)
EVT_MENU(ID_FILEOPEN, CMainFrame::OnFileOpen)
EVT_MENU(ID_FILESAVE, CMainFrame::OnFileSave)
EVT_MENU(ID_FILESAVEAS, CMainFrame::OnFileSaveAs)
EVT_MENU(ID_FILESAVEAS_UTF8, CMainFrame::OnFileSaveAsUTF8)
EVT_MENU(ID_FILESAVEAS_UTF16, CMainFrame::OnFileSaveAsUTF16)
EVT_MENU(ID_FILESETASSCREENSAVER, CMainFrame::OnFileSetAsScreenSaver)
EVT_UPDATE_UI(ID_FILESETASSCREENSAVER, CMainFrame::OnUpdateFileSetAsScreenSaver)
EVT_MENU(ID_FILEEDIT, CMainFrame::OnEditProcedure)
EVT_MENU(ID_FILEERASE, CMainFrame::OnEraseProcedure)
EVT_MENU(wxID_EXIT, CMainFrame::OnExit)
EVT_MENU(ID_BITMAPNEW, CMainFrame::OnBitmapNew)
EVT_MENU(ID_BITMAPOPEN, CMainFrame::OnBitmapOpen)
EVT_MENU(ID_BITMAPSAVE, CMainFrame::OnBitmapSave)
EVT_MENU(ID_BITMAPSAVEAS, CMainFrame::OnBitmapSaveAs)
EVT_MENU(ID_BITMAPPRINT, CMainFrame::OnBitmapPrint)
EVT_MENU(ID_BITMAPPRINTERSETUP, CMainFrame::OnBitmapPrinterSetup)
EVT_MENU(ID_BITMAPPRINTERAREA, CMainFrame::OnSetActiveArea)
EVT_MENU(ID_SETPENSIZE, CMainFrame::OnSetPenSize)
EVT_MENU(ID_SETLABELFONT, CMainFrame::OnSetLabelFont)
EVT_MENU(ID_SETCOMMANDERFONT, CMainFrame::OnSetCommanderFont)
EVT_MENU(ID_SETPENCOLOR, CMainFrame::OnSetPenColor)
EVT_MENU(ID_SETSCREENCOLOR, CMainFrame::OnSetScreenColor)
EVT_MENU(ID_SETFLOODCOLOR, CMainFrame::OnSetFloodColor)
EVT_MENU(wxID_HELP_INDEX, CMainFrame::OnHelp)
#if MANUAL_HAS_TRANSLATION_TABLES
// options for translating to/from English
EVT_MENU(ID_HELPLANGTOENGLISH, CMainFrame::OnHelpLanguageToEnglish)
EVT_MENU(ID_HELPENGLISHTOLANG, CMainFrame::OnHelpEnglishToLanguage)
#endif
EVT_MENU(ID_HELPTUTORIAL, CMainFrame::OnHelpTutorial)
EVT_MENU(ID_HELPDEMO, CMainFrame::OnHelpDemo)
EVT_MENU(ID_HELPEXAMPLES, CMainFrame::OnHelpExamples)
EVT_MENU(ID_HELPRELEASENOTES, CMainFrame::OnHelpReleaseNotes)
EVT_MENU(wxID_ABOUT, CMainFrame::OnAboutFmsLogo)
EVT_MENU(ID_HELPABOUTMS, CMainFrame::OnAboutMultipleSclerosis)
EVT_MENU(wxID_ZOOM_IN, CMainFrame::OnZoomIn)
EVT_MENU(wxID_ZOOM_OUT, CMainFrame::OnZoomOut)
EVT_MENU(wxID_ZOOM_100, CMainFrame::OnZoomNormal)
EVT_SIZE(CMainFrame::OnResize)
EVT_CLOSE(CMainFrame::OnClose)
EVT_SET_CURSOR(CMainFrame::OnSetCursor)
END_EVENT_TABLE()
