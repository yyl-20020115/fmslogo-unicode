#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "fmslogo.h"

   #include <algorithm>

   #include <wx/msgdlg.h>
   #include <wx/filename.h>
   #include <wx/string.h>
   #include <wx/dcclient.h>
   #include <wx/dcmemory.h>
   #include <wx/clipbrd.h>
   #include <wx/gdicmn.h> 
   #include <wx/settings.h>
   #include <wx/stdpaths.h>

   #ifdef __WXMSW__
      #include "wx/msw/private.h"
   #endif

   #include "init.h"
   #include "localizedstrings.h"
   #include "logocore.h" // for ARRAYSIZE
   #include "mainframe.h"
   #include "graphwin.h"
   #include "error.h"
   #include "wrksp.h"
   #include "startup.h"
   #include "utils.h"
   #include "mmwind.h"
   #include "files.h"
   #include "mainwind.h"
   #include "cursor.h"
   #include "logoeventqueue.h"
   #include "eval.h"
   #include "print.h"
   #include "screenwindow.h"
   #include "workspaceeditor.h"
   #include "minieditor.h"
   #include "dynamicbuffer.h"
   #include "stringprintednode.h"
   #include "stringadapter.h"

   #include "screen.h"
   #include "commander.h"
#endif

// global variables declared in main.h
wchar_t edit_editexit[MAX_BUFFER_SIZE];     // editor callback instruction list 

int  BitMapWidth  = 1000;
int  BitMapHeight = 1000;
bool bFixed       = false;

#ifndef WX_PURE
static HANDLE g_SingleInstanceMutex = NULL;
#endif

#ifdef WX_PURE
#define MAX_PATH (260)
#endif
static wchar_t g_FileToLoad[MAX_PATH] = L""; // routine to exec on start
static bool g_EnterPerspectiveMode = false;
static bool g_CustomWidth          = false;
static bool g_CustomHeight         = false;

#ifdef MEM_DEBUG
#ifdef __WXMSW__
typedef DWORD (WINAPI *GETGUIRESOURCES)(HANDLE, DWORD);

static GETGUIRESOURCES g_GetGuiResources     = NULL;
static DWORD           g_OriginalGuiObjects  = 0;
static DWORD           g_OriginalUserObjects = 0;
static HANDLE          g_Fmslogo             = NULL;
static HMODULE         g_User32              = NULL;
#endif // __WXMSW__
#endif // MEM_DEBUG


#ifdef WX_PURE
  #if wxUSE_UNICODE
    // Use the wchar_t variants of the ANSI C string functions
    #define strtoul wcstoul
    #define strlen  wcslen
  #endif
#endif

////////////////////////////////////////////////////////////////////
// CFmsLogo
IMPLEMENT_APP(CFmsLogo)

CFmsLogo::CFmsLogo()
{
}

// Read an integer command-line argument, given as either "-W500" or "-W 500".
//
// CurrentArgument - A pointer in a string just after the switch,
//                   to where the number should begin.
//
// NextArgument    - A reference to an pointer in varg.
//                   This is incremented to the next argument if
//                   the switch is given in the form "-W 500".
static
int
ReadIntArgument(
    wxChar *    CurrentArgument,
    wxChar ** & NextArgument
    )
{
    int numericValue;

    if (*CurrentArgument != L'\0')
    {
        // The command-line was given as "-w500".
        numericValue = wcstoul(CurrentArgument, &CurrentArgument, 10);
    }
    else
    {
        // The -w isn't immediately followed by a number.
        // Try to get the next argument, as in "-w 500".
        wxChar * nextArgument = NextArgument[1];
        if (nextArgument != NULL)
        {
            // There was an argument following the -W.
            numericValue = wcstoul(nextArgument, NULL, 10);
            NextArgument++;
        }
        else
        {
            // The command-line ends in something like "-w".
            // In MSWLogo, the width would have silently been 
            // taken to be 0.

            // Since this results in an unusable workspace, we
            // now warn user of their mistake.
            wxMessageBox(
                *NextArgument,
				wxString(LOCALIZED_ERROR_BADCOMMANDLINE),
                wxOK | wxICON_INFORMATION);

            numericValue = 0;
        }
    }

    return numericValue;
}

void CFmsLogo::ProcessCommandLine()
{
    // parse the command-line parameters
    g_FileToLoad[0] = L'\0';
    bExpert        = false;
    g_CustomWidth  = false;
    g_CustomHeight = false;
    bFixed         = false;

    // For processing the -L parameter
    bool   copyRemaingArgsAsFilename = false;
    size_t fileToLoadIndex           = 0;

#if wxUSE_UNICODE
    // On wxWidgets 3.X, argv is no longer a wxChar**, but a wxCmdLineArgsArray.
    // This mostly emulates a real argv, but does not ensure that argv[argc]==0.
    // This breaks the code below in a way that would disruptive to rewrite.
    // Instead, this code creates a local variable that shadows argv and
    // initializes it how it was in wxWidgets 2.8.
    // I opened http://trac.wxwidgets.org/ticket/17531 to track this in hopes that
    // it would be accepted as a bug fixed before a Unicode FMSLogo is ever released.
    const wxArrayString & realArgv = argv.GetArguments();
    size_t argvSize = realArgv.GetCount();
    wxChar ** argv = new wxChar* [argvSize + 1];
    for (size_t i = 0; i < argvSize; i++)
    {
        // copy from realArgv[i] to argv[i]
        argv[i] = new wxChar[realArgv[i].Len() + 1];
        for (size_t j = 0; j < realArgv[i].Len(); j++)
        {
            argv[i][j] = realArgv[i][j];
        }
        argv[i][realArgv[i].Len()] = L'\0';
    }
    argv[argvSize] = NULL;
#endif

    for (wxChar ** nextArgument = argv + 1;
         *nextArgument != NULL; 
         nextArgument++)
    {
        wxChar * argument = *nextArgument;

        if (!copyRemaingArgsAsFilename)
        {
            if (*argument == L'-')
            {
                argument++; // advance beyond the -

                switch (*argument++)
                {
                case L'p':
                case L'P':
                    g_EnterPerspectiveMode = true;
                    break;

                case L'e':
                case L'E':
                    bExpert = true;
                    break;

                case L'f':
                case L'F':
                    bFixed = true;
                    break;

                case L'h':
                case L'H':
                    BitMapHeight   = ReadIntArgument(argument, nextArgument);
                    g_CustomHeight = true;
                    break;

                case L'w':
                case L'W':
                    BitMapWidth   = ReadIntArgument(argument, nextArgument);
                    g_CustomWidth = true;
                    break;

                case L'l':
                case L'L':
                    // the rest of the arguments should be taken as part of a filename
                    copyRemaingArgsAsFilename = true;
                    break;

                default:
                    // invalid command line: unrecognized switch
                    wxMessageBox(
                        argument - 2,
						wxString(LOCALIZED_ERROR_BADCOMMANDLINE),
                        wxOK | wxICON_INFORMATION);
                    break;
                }
            }
            else
            {
                // This was not a '-', so treat it as part of a filename
                copyRemaingArgsAsFilename = true;
            }
        }

        if (copyRemaingArgsAsFilename)
        {
            // Copy the rest of the line into the g_FileToLoad buffer

            // BUG: This is not backward compatible with MSWLogo.
            // This should tolerate multiple spaces, instead of assuming
            // that there's exactly one space between arguments.
            if (fileToLoadIndex != 0 &&
                fileToLoadIndex < ARRAYSIZE(g_FileToLoad))
            {
                g_FileToLoad[fileToLoadIndex++] = L' ';
            }

            wcsncpy(
                &g_FileToLoad[fileToLoadIndex],
                /*WXCHAR_TO_STRING*/(argument),
                ARRAYSIZE(g_FileToLoad) - 1 - fileToLoadIndex);

            fileToLoadIndex += wcslen(argument);
        }
    }

#if wxUSE_UNICODE
    for (wxChar ** nextArgument = argv; *nextArgument != NULL; nextArgument++)
    {
        delete [] *nextArgument;
    }
    delete [] argv;
#endif
}

bool CFmsLogo::OnInit()
{
    bool rval = true;

#ifdef MEM_DEBUG
#ifdef __WXMSW__
    g_Fmslogo = NULL;
    g_User32  = GetModuleHandle("user32.dll");
    if (g_User32 != NULL)
    {
        g_GetGuiResources = (GETGUIRESOURCES) GetProcAddress(g_User32, "GetGuiResources");
        if (g_GetGuiResources != NULL)
        {
            g_Fmslogo = OpenProcess(
                PROCESS_QUERY_INFORMATION, 
                FALSE, 
                GetCurrentProcessId());
            if (g_Fmslogo != NULL)
            {
                g_OriginalGuiObjects  = g_GetGuiResources(g_Fmslogo, GR_GDIOBJECTS);
                g_OriginalUserObjects = g_GetGuiResources(g_Fmslogo, GR_USEROBJECTS);
            }
        }
    }
#endif // __WXMSW__
#endif // MEM_DEBUG

    // Figure out the path that contains fmslogo.exe, which we
    // assume also holds Logolib.
    const wxFileName fmslogoExecutable(
        wxStandardPaths::Get().GetExecutablePath());
    const wxString & fmslogoPath = fmslogoExecutable.GetPath(
        wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);

    wcsncpy(
        g_FmslogoBaseDirectory,
        /*WXSTRING_TO_STRING*/(fmslogoPath),
        ARRAYSIZE(g_FmslogoBaseDirectory));
    g_FmslogoBaseDirectory[ARRAYSIZE(g_FmslogoBaseDirectory) - 1] = L'\0';

    ProcessCommandLine();

#ifndef WX_PURE

    // Grab the single instance lock.
    g_SingleInstanceMutex = CreateMutex(
        NULL,  // default security attributes
        FALSE, // no initial owner
        L"LogoForWindowsMutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        // A copy of Logo is already running.
        if (g_FileToLoad[0] == L'\0')
        {
            // No logo scripts were specified on the command-line.
            // We should re-use the existing window instead of creating a new 
            // instance of logo, since this was probably just an accident.

            // Find that running copy of Logo and make it visible.
            HWND runningInstance = FindWindow(NULL, LOCALIZED_GENERAL_PRODUCTNAME);
            if (runningInstance != NULL)
            {
                // bring running instance to the the foreground
                ::SetForegroundWindow(runningInstance);
                if ( ::IsIconic(runningInstance) ||
                     !::IsWindowVisible(runningInstance))
                {
                    // the running instance is not visible, so restore it
                    ::ShowWindow(runningInstance, SW_SHOWDEFAULT);
                }

                CloseHandle(g_SingleInstanceMutex);
                return false;
            }

            // We can't find the window, so we'll start up another instance.
            // The feature of not running two instances is supposed to make
            // things simpler.  If the other copy of Logo failed to exit
            // cleanly, or if some other application created the mutex,
            // it would more confusing if this Logo didn't start up.
        }
        else
        {
            // a Logo script was specified on the command-line.
            // This means that we should open up a new instance
            // of Logo, even if one is already running.
        }
    }
#endif // WX_PURE

    // Get video mode parameters
    init_videomode();

    srand(time(NULL));

    // init the timer callback array
    init_timers();

    // alloc and init the bitmap cut array
    init_bitmaps();

    // alloc and init the turtles array
    init_turtles();

    // init global pen state
    init_penstate();

    // init logo kernel
    init();

    // initialize the hourglass and arrow cursors
    init_cursors();

    // determine how big a window we would like
    int x = 0;
    int y = 0;
    int w = BitMapWidth;
    int h = BitMapHeight;

    // The main window should not exceed the size of the working area
    int maxWidth;
    int maxHeight;
    wxClientDisplayRect(NULL, NULL, &maxWidth, &maxHeight);

    // if fixed mode
    bool startMaximized;
    if (bFixed)
    {
        // FMSLogo was started with -F on the command-line.  In this case,
        // CMainFrame ignores the window size parameter (width and height)
        // and instead resizes itself to ensure that there is enough space
        // for the bitmap's width/height.  Therefore, this code block only
        // computes correct values for BitMapWidth and BitMapHeight, not
        // w and h.

        // If "-F" is given without "-W" or "-H", then FMSLogo should
        // start maximized.  This ensures the FMSLogo uses the most
        // amount of space available to it.
        startMaximized = !g_CustomHeight && !g_CustomWidth;

        // Reduce the maximum width available to the virtual service
        // that is taken up by the 3D border between the frame and the
        // screen.
        int borderWidth = wxSystemSettings::GetMetric(wxSYS_EDGE_X);
        if (borderWidth != -1)
        {
            maxWidth -= 2 * borderWidth;
        }

        // When an application is not maximized, it has a frame that reduces
        // the amount of space available to the window.
        // CMainFrame uses wxDEFAULT_FRAME_STYLE, which includes
        // wxRESIZE_BORDER.  In wx/toplevel.h, this is #define'd to be the
        // same as wxTHICK_FRAME, which is what wxSYS_FRAMESIZE_X returns.
        if (!startMaximized)
        {
            int frameWidth  = wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X);
            if (frameWidth != -1)
            {
                maxWidth -= 2 * frameWidth;
            }
        }

        if (g_CustomHeight)
        {
            // if height specified sanitize it against screen height
            BitMapHeight = std::min(h, maxHeight);
        }
        else
        {
            // Go "full screen", leaving space for the commander.
            BitMapHeight = (int) (maxHeight * ScreenSz);
        }

        if (g_CustomWidth)
        {
            // if width specified sanitize it against screen width
            BitMapWidth = std::min(w, maxWidth);
        }
        else
        {
            // Use the full width available to a window with a frame.
            BitMapWidth = maxWidth;
        }
    }
    else
    {
        // sanitize window size we would like against screen size
        w = std::min(w, maxWidth);
        h = std::min(h, (int) (maxHeight * ScreenSz));

        GetConfigurationQuadruple(L"Screen", &x, &y, &w, &h);

        // the smallest reasonable size is 400 x 400.
        h = std::max(h, 400);
        w = std::max(w, 400);

        // sanitize against screen size
        checkwindow(&x, &y, &w, &h);

        // Don't normally start maximized.
        startMaximized = false;
    }

    // initialize the values for some of the graphics-related
    // global variables.
    init_graphics();

    // create and show the main frame
    CMainFrame * frame = new CMainFrame(
        BitMapWidth,
        BitMapHeight,
        wxPoint(x, y),
        wxSize(w, h),
        startMaximized);

    frame->Show();

    return rval;
}

int CFmsLogo::OnExit()
{
    // cleanup all subsystems
    uninit();

    uninit_bitmaps();

    uninit_turtles();

    uninit_graphics();

    // release the Help subsystem
    HtmlHelpUninitialize();

#ifndef WX_PURE
    CloseHandle(g_SingleInstanceMutex);
    g_SingleInstanceMutex = NULL;
#endif // WX_PURE

#ifdef MEM_DEBUG
#ifdef __WXMSW__
    if (g_Fmslogo != NULL)
    {
        // Check if any GUI objects were leaked
        DWORD currentGuiObjects = g_GetGuiResources(g_Fmslogo, GR_GDIOBJECTS);
        if (g_OriginalGuiObjects < currentGuiObjects)
        {
            TraceOutput(
                "%d GUI objects were leaked.\n",
                currentGuiObjects - g_OriginalUserObjects);
        }

        // Check if any USER objects were leaked
        DWORD currentUserObjects = g_GetGuiResources(g_Fmslogo, GR_USEROBJECTS);
        if (g_OriginalUserObjects < currentUserObjects)
        {
            TraceOutput(
                "%d USER objects were leaked.\n",
                currentUserObjects - g_OriginalUserObjects);
        }

        CloseHandle(g_Fmslogo);
    }
#endif // __WXMSW__
#endif // MEM_DEBUG

#if wxUSE_CLIPBOARD
    // wxWidgets clears the clipboard when it exits, presumably to save memory.
    // To me, this behavior is unintuitative and confusing, as it's something
    // that Windows applications typically don't do.  To avoid this, we "flush"
    // the clipboard, which means only that if the clipboard's data came from
    // FMSLogo, it will continue to be available after FMSLogo exits.
    wxClipboard::Get()->Flush();
#endif

    return wxApp::OnExit();
}

CMainFrame * CFmsLogo::GetMainFrame()
{
    return static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
}

void CFmsLogo::OnIdle(wxIdleEvent & IdleEvent)
{
    // If -P was specified on the command line, enter perspective mode.
    if (g_EnterPerspectiveMode)
    {
        g_EnterPerspectiveMode = false;
        lperspective(NIL);
    }

    // run the script that localizes FMSLogo
    static bool hasRunStartup = false;
    if (!hasRunStartup)
    {
        hasRunStartup = true;

        wchar_t startupScript[MAX_PATH + 1];
        MakeHelpPathName(startupScript, L"startup.logoscript");
        silent_load(NIL, startupScript);
    }

    // If a file to load was given on the command line, then execute it.
    static bool hasLoadedFileToLoad = false;
    if (!hasLoadedFileToLoad && g_FileToLoad[0] != L'\0')
    {
        // Set that we have loaded the file before we actually do
        // in case loading the file causes and idle event to be sent
        // and re-executes this function.
        hasLoadedFileToLoad = true;
        silent_load(NIL, g_FileToLoad);
    }

    // Process logo events
    checkqueue();

    // Continue with the default processing
    IdleEvent.Skip();
}

BEGIN_EVENT_TABLE(CFmsLogo, wxApp)
    EVT_IDLE(CFmsLogo::OnIdle)
END_EVENT_TABLE()

void single_step_box(NODE * the_line)
{
    // Print the line into a buffer, honoring the current printing limits
    CStringPrintedNode printedLine(the_line, CStringPrintedNode::WithPrintLimits);

    // pop up single step box showing line of code
    if (wxMessageBox(
		wxString(printedLine.GetString()),
		wxString(LOCALIZED_STEPPING),
            wxOK | wxCANCEL) == wxCANCEL)
    {
        if (stepflag)
        {
            // Act like someone pressed the "UnStep" button
            CFmsLogo::GetMainFrame()->GetCommander()->ToggleStep();
        }
        else
        {
            err_logo(STOP_ERROR, NIL);
        }
    }
}

wchar_t * promptuser(const wchar_t *prompt)
{
    return CFmsLogo::GetMainFrame()->PromptUserForInput(prompt);
}

wxWindow * GetParentWindowForDialog()
{
    return CFmsLogo::GetMainFrame()->GetCommander();
}

#ifndef WX_PURE
HWND GetScreenWindow()
{
    CMainFrame* mainFrame = CFmsLogo::GetMainFrame();
    assert(mainFrame != NULL);
    return reinterpret_cast<HWND>(mainFrame->GetScreen()->GetHandle());
}

HWND GetMainWindow()
{
    CMainFrame* mainFrame = CFmsLogo::GetMainFrame();
    assert(mainFrame != NULL);
    return static_cast<HWND>(mainFrame->GetHandle());
}

HWND GetCommanderWindow()
{
    CMainFrame* mainFrame = CFmsLogo::GetMainFrame();
    assert(mainFrame != NULL);
    return reinterpret_cast<HWND>(mainFrame->GetTopLevelWindowForCommander()->GetHandle());
}
#endif // WX_PURE

wxWindow * GetMainWxWindow() {
    return CFmsLogo::GetMainFrame();
}

wxWindow * GetScreenWxWindow() {
    return CFmsLogo::GetMainFrame()->GetScreen();
}

wxWindow * GetEditorWxWindow()
{
    return CFmsLogo::GetMainFrame()->GetWorkspaceEditor();
}

int GetScreenHorizontalScrollPosition()
{
    return CFmsLogo::GetMainFrame()->GetScreen()->GetScrollPos(wxHORIZONTAL);
}

int GetScreenVerticalScrollPosition()
{
    return CFmsLogo::GetMainFrame()->GetScreen()->GetScrollPos(wxVERTICAL);
}

void SetScreenScrollPosition(int X, int Y)
{
    CFmsLogo::GetMainFrame()->GetScreen()->Scroll(X, Y);
}

bool IsEditorOpen()
{
    CMainFrame* mainFrame = CFmsLogo::GetMainFrame();

    if (mainFrame == NULL)
    {
        return false;
    }

    return mainFrame->IsEditorOpen();
}

void OpenEditorToLocationOfFirstError(const wchar_t *FileName)
{
    CFmsLogo::GetMainFrame()->PopupEditorToError(FileName);
}

#ifndef WX_PURE
HDC GetScreenDeviceContext()
{
    CMainFrame* mainFrame = CFmsLogo::GetMainFrame();
    return static_cast<HDC>(mainFrame->GetScreen()->GetScreenDeviceContext().GetHDC());
}

HDC GetMemoryDeviceContext()
{
    return static_cast<HDC>(GetWxMemoryDeviceContext()->GetHDC());
}

#endif // WX_PURE

wxDC * GetWxMemoryDeviceContext()
{
    return &CFmsLogo::GetMainFrame()->GetScreen()->GetMemoryDeviceContext();
}

wxDC * GetWxScreenDeviceContext()
{
    return &CFmsLogo::GetMainFrame()->GetScreen()->GetScreenDeviceContext();
}

wxDC * GetBackBufferDeviceContext()
{
    return &CFmsLogo::GetMainFrame()->GetScreen()->GetBackBufferDeviceContext();
}

void OpenStatusWindow()
{
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();
    mainFrame->ShowStatus();
    mainFrame->GetCommander()->UpdateStatusButtonState();
}

void UpdateUiExecutionState()
{
    // Enable/Disable the Halt/Pause buttons according to the execution state.
    CFmsLogo::GetMainFrame()->GetCommander()->UpdateHaltButtonState();
    CFmsLogo::GetMainFrame()->GetCommander()->UpdatePauseButtonState();
}

CStatusDialog * GetStatusDialog()
{
    CStatusDialog * statusDialog = CFmsLogo::GetMainFrame()->GetStatusDialog();
    assert(statusDialog != NULL);
    return statusDialog;
}

void CloseStatusWindow()
{
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();
    mainFrame->HideStatus();
    mainFrame->GetCommander()->UpdateStatusButtonState();
}

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor)
{
    CMainFrame * mainFrame = CFmsLogo::GetMainFrame();
    mainFrame->GetScreen()->AdjustScrollPositionToZoomFactor(NewZoomFactor);
}

void UndockCommanderWindow()
{
    CFmsLogo::GetMainFrame()->UndockCommanderWindow();
}

void DockCommanderWindow()
{
    CFmsLogo::GetMainFrame()->DockCommanderWindow();
}

#ifndef WX_PURE
#ifdef __WXMSW__
bool TranslateKeyboardShortcut(MSG & Message)
{
    return CFmsLogo::GetMainFrame()->TranslateKeyboardShortcut(Message);
}
#endif
#endif

int ShowEditorForFile(const wchar_t *FileName, NODE * EditArguments)
{
    return CMainFrame::PopupEditorForFile(wxString(FileName), EditArguments);
}

void 
ShowProcedureMiniEditor(
    const wchar_t     * ToLine,
    CDynamicBuffer & ReadBuffer
    )
{
    CMiniEditor miniEditor(CFmsLogo::GetMainFrame(), ToLine);

    if (wxID_OK != miniEditor.ShowModal())
    {
        // The user cancelled the definition
        err_logo(STOP_ERROR, NIL);
    }
    else
    {
        // copy the new definition into the read buffer.
        bool haveCarriageReturn = false;
        const wxString & body = miniEditor.GetProcedureBody();
        for (wxString::const_iterator i = body.begin(); i != body.end(); ++i)
        {
            if (haveCarriageReturn && *i != '\n')
            {
                // The carriage return was not followed by a newline,
                // so it was not part of an EOL sequence.
                ReadBuffer.AppendChar('\r');
            }
            if (*i == '\r')
            {
                // Delay writing the CR in case the next character is an LF.
                // This will map the CRLF into the UNIX EOL sequence.
                haveCarriageReturn = true;
                continue;
            }

            // BUG: On Unicode builds, this has data loss because it
            // converts a wchar_t to a char.
            ReadBuffer.AppendChar(*i);
            haveCarriageReturn = false;
        }

        ReadBuffer.AppendChar(L'\n');
        ReadBuffer.AppendString(End.GetName());
    }
}

void
TraceOutput(
    const wchar_t * FormatString,
    ...
    )
{
    // Format and print the message to stderr
    va_list args;
    va_start(args, FormatString);
    vfwprintf(stderr, FormatString, args);
    va_end(args);

#ifdef __WXMSW__
	wchar_t formattedString[256] = {0};

    va_start(args, FormatString);
    int bytesNeeded = _vsnwprintf(
        formattedString,
        ARRAYSIZE(formattedString) - 1,
        FormatString,
        args);
    va_end(args);

    if (0 <= bytesNeeded)
    {
        OutputDebugString(formattedString);
    }
#endif
}
