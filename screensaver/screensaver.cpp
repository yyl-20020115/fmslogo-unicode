#include <windows.h>
#include <time.h>
#include <string>
#include <scrnsave.h>
#include <stdlib.h>

#include <wx/window.h>
#include <wx/app.h>
#include <wx/dc.h>
#include <wx/dcmemory.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/filefn.h>   // for wxSetWorkingDirectory
#include <wx/filename.h>

#include <wx/msw/dc.h> // for wxDCTemp

#include "init.h"
#include "graphwin.h"
#include "startup.h"
#include "print.h"
#include "error.h"
#include "mmwind.h"
#include "wrksp.h"
#include "utils.h"
#include "files.h"
#include "localizedstrings.h"
#include "logoeventqueue.h"
#include "mainwind.h"
#include "devwind.h"
#include "eval.h"
#include "logorc.h"
#include "netwind.h"
#include "screenwindow.h"
#include "statusdialog.h"
#include "stringadapter.h"

#include "resource.h"

int BitMapWidth  = 0;
int BitMapHeight = 0;

char edit_editexit[MAX_BUFFER_SIZE];     // editor callback instruction list

static UINT   g_Timer;
static CHAR   g_FileToLoad[MAX_PATH] = "";
static HANDLE g_SingleInstanceMutex  = NULL;

static bool g_IsLoadingFile          = false;

#ifdef MEM_DEBUG
typedef DWORD (WINAPI *GETGUIRESOURCES)(HANDLE, DWORD);

static GETGUIRESOURCES g_GetGuiResources     = NULL;
static DWORD           g_OriginalGuiObjects  = 0;
static DWORD           g_OriginalUserObjects = 0;
static HANDLE          g_Fmslogo             = NULL;
static HMODULE         g_User32              = NULL;
#endif

// TODO: These native handles are from when the screensaver didn't use
// wxWidgets.  Now, all of these should be replaceable with a structured
// wxWidgets class.
static HWND       g_ScreenWindow = NULL;
static HDC        g_ScreenDeviceContext = NULL;
static HDC        g_BackBufferDeviceContext = NULL;
static HBITMAP    g_BackBuffer = NULL;

static wxWindow      * g_WxScreenWindow = NULL;
static wxMemoryDC    * g_WxMemoryDeviceContext = NULL;
static wxDC          * g_WxScreenDeviceContext = NULL;
static wxBitmap      * g_WxMemoryBitmap = NULL;
static wxApp         * g_DummyApp = NULL;
static CStatusDialog * g_StatusDialog = NULL;
static wxDC          * g_WxBackBufferDeviceContext = NULL;

static DWORD g_TickCountOfMostRecentLoad = 0;

static int   g_NextTextLine = 0;


const DWORD DELAYTIME_MILLISECONDS = 10000;



static
void
UninitializeLogoEngine()
{
    // cleanup all subsystems
    uninit();

    uninit_bitmaps();

    uninit_turtles();

    uninit_graphics();

    // release the HTML Help subsystem
    HtmlHelpUninitialize();

    CloseHandle(g_SingleInstanceMutex);
    g_SingleInstanceMutex = NULL;

#ifdef MEM_DEBUG
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
#endif // MEM_DEBUG
}

static wxWindow * WrapNativeHwnd(HWND NativeHwnd)
{
    wxWindow * wrapperWindow = new wxWindow();
    wrapperWindow->SetHWND(NativeHwnd);
    wrapperWindow->AdoptAttributesFromHWND();
    return wrapperWindow;
}

static void DeleteWrapperWindow(wxWindow * WrapperWindow)
{
    WrapperWindow->SetHWND(NULL);
    WrapperWindow->Destroy();
}

LRESULT WINAPI ScreenSaverProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT     rval = 0;
    callthing * callevent;

    // used for WM_PAINT
    BOOL updateRectangleExists;
    RECT updateRectangle;

    int argc = 0;

    switch(message)
    {
    case WM_CREATE:

        // Initialize the wxWidget library.
        // Normally, ::wxInitialize() would be sufficient, but since
        // some FMSLogo commands require the wxWindow subsystem, we
        // must instanciate a full wxApp and initialize it.
        g_DummyApp = new wxApp();
        g_DummyApp->Initialize(argc, NULL);

        // Wrap the native HWND in a wxWindow object so that
        // it can be passed to other parts of the system.
        g_WxScreenWindow = WrapNativeHwnd(hwnd);
        g_FullRect = g_WxScreenWindow->GetClientRect();

        // Lower the screen saver.  This is counter-intuitive, since the screen
        // saver is supposed to be on top of all windows, but it is needed so
        // that any dialog boxes which the screensaver program creates (for
        // example SELECTBOX) appear on top of the screensaver window and are
        // visible.  While is possible for them to specific the wxSTAY_ON_TOP
        // flag, that doesn't work for DIALOGFILEOPEN, because on Windows
        // wxFileDialog is a dummy window that then uses the Windows common
        // control for the file picker.  wxWidgets doesn't honor all of the
        // styles, includin wxSTAY_ON_TOP.
        //
        // Surprisingly, this still keeps the screensaver window above other
        // applications that are running, perhaps because it's called from
        // the context of a WM_CREATE.
        g_WxScreenWindow->Lower();

        g_ScreenWindow = hwnd;

        // Size-to-fit
        BitMapHeight = g_FullRect.GetHeight();
        BitMapWidth  = g_FullRect.GetWidth();

        // Create a device context to write to the screen.
        g_ScreenDeviceContext   = GetDC(g_ScreenWindow);
        g_WxScreenDeviceContext = new wxDCTemp(g_ScreenDeviceContext);

        // Create the in-memory image of the bitmap
        g_WxMemoryBitmap        = new wxBitmap(BitMapWidth, BitMapHeight);
        g_WxMemoryDeviceContext = new wxMemoryDC(*g_WxMemoryBitmap);

        // Get native handles to the in-memory image of the screen
        MemoryBitMap = static_cast<HBITMAP>(g_WxMemoryBitmap->GetHBITMAP());

#ifdef MEM_DEBUG
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
#endif // MEM_DEBUG

        // Figure out the path that contains fmslogo.exe
        HKEY fmslogoKey;
        LONG result;
        result = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            "Software\\FMSLogo",
            0, // reserved
            KEY_QUERY_VALUE,
            &fmslogoKey);
        if (result == ERROR_SUCCESS)
        {
            DWORD valueSize = ARRAYSIZE(g_FmslogoBaseDirectory) - 2;  // leave room for the backslash and NUL
            BYTE *valuePtr  = reinterpret_cast<BYTE*>(g_FmslogoBaseDirectory);
            DWORD valueType;

            LONG result = RegQueryValueEx(
                fmslogoKey,
                "Install_Dir",
                0,   // reserved
                &valueType,
                valuePtr,
                &valueSize);
            if (result == ERROR_SUCCESS && 
                valueType == REG_SZ     &&
                valueSize < ARRAYSIZE(g_FmslogoBaseDirectory) - 2)
            {
                // we successfully read the value as a string.
                // Append the missing backslash
                if (valueSize != 0 && g_FmslogoBaseDirectory[valueSize] == '\0')
                {
                    valueSize--;
                }
                g_FmslogoBaseDirectory[valueSize + 0] = '\\';
                g_FmslogoBaseDirectory[valueSize + 1] = '\0';
            }

            RegCloseKey(fmslogoKey);
        }
        else
        {
            TraceOutput("Unable to locate FMSLogo installation directory\n");
        }

        // Grab the single instance lock.
        // We don't want to fail if Logo is running, since we are a screen saver.
        // But we do want to prevent Logo from being uninstalled.
        g_SingleInstanceMutex = CreateMutex(
            NULL,  // default security attributes
            FALSE, // no initial owner
            "LogoForWindowsMutex");

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

        // initialize the values for some of the graphics-related
        // global variables.
        init_graphics();

        // run the startup script that localizes logo
        char startupScript[MAX_PATH + 1];
        MakeHelpPathName(startupScript, "startup.logoscript");
        silent_load(NIL, startupScript);

        // force the next WM_TIMER update to run the program
        g_TickCountOfMostRecentLoad = 0;

        // Start the timer.
        // Use the minimum timer tick time so that we can run
        // the next instruction as soon as the previous one completes.
        g_Timer = SetTimer(hwnd, 33, USER_TIMER_MINIMUM, NULL);
        break;

    case WM_PAINT:

        updateRectangleExists = GetUpdateRect(hwnd, &updateRectangle, FALSE);
        if (updateRectangleExists)
        {
            // There is a dirty rectangle that needs to be redrawn.
            PAINTSTRUCT repaintInfo = {0};
            repaintInfo.rcPaint = updateRectangle;

            HDC deviceContext = BeginPaint(hwnd, &repaintInfo);
            if (deviceContext)
            {
                wxDCTemp wxDeviceContext(deviceContext, g_FullRect.GetSize());
                PaintToScreen(
                    wxDeviceContext,
                    wxRegion(g_FullRect),
                    0,
                    0);

                EndPaint(hwnd, &repaintInfo);
            }
        }

        break;

    case WM_ERASEBKGND:
        updateRectangleExists = GetUpdateRect(hwnd, &updateRectangle, FALSE);
        if (updateRectangleExists)
        {
            // Fill the dirty region with whiteness.
            FillRect(
                reinterpret_cast<HDC>(wParam),
                &updateRectangle,
                reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
        }

        // mark the background as being erased
        rval = 1;
        break;

    case WM_KEYUP:
        if (keyboard_keyup != NULL)
        {
            callevent = callthing::CreateKeyboardEvent(keyboard_keyup, wParam);

            calllists.insert(callevent);
            checkqueue();
        }
        else
        {
            rval = DefScreenSaverProc(hwnd, message, wParam, lParam);
        }
        break;

    case WM_KEYDOWN:
        if (keyboard_keydown != NULL)
        {
            callevent = callthing::CreateKeyboardEvent(keyboard_keydown, wParam);

            calllists.insert(callevent);
            checkqueue();
        }
        else
        {
            rval = DefScreenSaverProc(hwnd, message, wParam, lParam);
        }
        break;

    case WM_TIMER:

        if (wParam < 16)
        {
            // not safe to yield
            callthing * callevent = callthing::CreateNoYieldFunctionEvent(timer_callback[wParam]);
            calllists.insert(callevent);
            PostMessage(hwnd, WM_CHECKQUEUE, 0, 0);
        }
        else if (wParam < 32)
        {
            // yieldable
            callevent = callthing::CreateFunctionEvent(timer_callback[wParam]);
            calllists.insert(callevent);
            PostMessage(hwnd, WM_CHECKQUEUE, 0, 0);
        }
        else if (wParam == 33)
        {
            // This is the screen saver's event
            if (!g_IsLoadingFile)
            {
                // Run the file to load if it's been more than DELAYTIME
                // milliseconds since the last time we ran it.
                if (g_TickCountOfMostRecentLoad + DELAYTIME_MILLISECONDS <= GetTickCount())
                {
                    // reset the screen and text area
                    lclearscreen(NULL);
                    g_NextTextLine = 0;

                    // Always re-read the file to load from the registry, in case it changed.
                    GetConfigurationString(
                        "ScreenSaverFile",
                        g_FileToLoad,
                        ARRAYSIZE(g_FileToLoad),
                        "");
                    if (g_FileToLoad[0] != '\0')
                    {
                        // In order for LOAD to work with relative paths, we
                        // set the working directory to the directory which
                        // holds the file to load.  This is primarily done for
                        // testing, but the programmer may benefit from this
                        // as well, as the working directory would otherwise
                        // be system32, which won't have any Logo files, nor
                        // will it be writable.
                        const wxString & fileToLoadString = WXSTRING(g_FileToLoad);
                        const wxFileName fileToLoad(fileToLoadString);
                        wxSetWorkingDirectory(fileToLoad.GetPath());

                        g_IsLoadingFile = true;

                        silent_load(NIL, g_FileToLoad);
                        g_TickCountOfMostRecentLoad = GetTickCount();

                        g_IsLoadingFile = false;

                        if (IsTimeToExit)
                        {
                            // In case BYE was run by the screensaver file.
                            DestroyWindow(hwnd);
                        }
                    }
                }
            }
        }
        else
        {
            // this is an unknown event
        }
        break;

    case WM_CHECKQUEUE:
        checkqueue();
        break;

    case MM_MCINOTIFY:
        // if user fired up a callback mci event then queue it up here
        callevent = callthing::CreateNoYieldFunctionEvent(mci_callback);
        calllists.insert(callevent);
        PostMessage(hwnd, WM_CHECKQUEUE, 0, 0);
        break;

    case WM_NETWORK_CONNECTSENDACK:
        g_ClientConnection.OnConnectSendAck(hwnd, lParam);
        break;

    case WM_NETWORK_CONNECTSENDFINISH:
        g_ClientConnection.OnConnectSendFinish(hwnd, lParam);
        break;

    case WM_NETWORK_LISTENRECEIVEACK:
        g_ServerConnection.OnListenReceiveAck(hwnd, lParam);
        break;

    case WM_CLOSE:
        if (is_executing())
        {
            // The language engine is still running, so we wait for it to stop.
            // Once it stops, it will resend a WM_CLOSE.
            exit_program();
        }
        else
        {
            // Let the window be destroyed.
            DestroyWindow(hwnd);
        }
        break;

    case WM_DESTROY:
        if (g_Timer != 0)
        {
            KillTimer(g_ScreenWindow, g_Timer);
            g_Timer = 0;
        }

        if (g_WxMemoryDeviceContext != NULL)
        {
            g_WxMemoryDeviceContext->SelectObject(wxNullBitmap);
            delete g_WxMemoryDeviceContext;
            g_WxMemoryDeviceContext = NULL;
        }

        if (g_WxMemoryBitmap != NULL)
        {
            delete g_WxMemoryBitmap;
            g_WxMemoryBitmap = NULL;
        }

        if (g_BackBuffer != NULL)
        {
            DeleteObject(g_BackBuffer);
            g_BackBuffer = NULL;
        }

        if (g_BackBufferDeviceContext != NULL)
        {
            DeleteDC(g_BackBufferDeviceContext);
            g_BackBufferDeviceContext = NULL;
        }

        delete g_WxBackBufferDeviceContext;
        g_WxBackBufferDeviceContext = NULL;

        delete g_WxScreenDeviceContext;
        g_WxScreenDeviceContext = NULL;

        if (g_ScreenDeviceContext != NULL)
        {
            ReleaseDC(g_ScreenWindow, g_ScreenDeviceContext);
            g_ScreenDeviceContext = NULL;
        }

        g_ScreenWindow = NULL;
 
        // Cleanup the language engine.
        UninitializeLogoEngine();

        // Note that we cannot delete the wxWindow while the Logo
        // engine is running because it could be calling a modal
        // wxWidgets routine, like a CQuestionBox, which, although
        // it's created as a child of g_WxScreenWindow, is cleaned
        // up by the Logo engine on proper shutdown.  Destroying
        // g_WxScreenWindow while such a CQuestionBox exists would
        // cause a double-free.
        if (g_WxScreenWindow != NULL)
        {
            DeleteWrapperWindow(g_WxScreenWindow);
            g_WxScreenWindow = NULL;
        }

        if (g_DummyApp != NULL)
        {
            g_DummyApp->CleanUp();
            delete g_DummyApp;
            g_DummyApp = NULL;
        }

        PostQuitMessage(0);
        break;

    default: 
        rval = DefScreenSaverProc(hwnd, message, wParam, lParam);
    }

    return rval;
}

// This is the function Windows calls to launch our dialog box.
BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    DWORD      bytesWritten;
    wxFileName fileToLoad;
    wxWindow * dialog;

    switch (message)
    {
    case WM_INITDIALOG:
        // WM_INITDIALOG - initialize the dialog box with values.

        // Read which file to use from the registry.
        GetConfigurationString(
            "ScreenSaverFile",
            g_FileToLoad,
            ARRAYSIZE(g_FileToLoad),
            "");

        // Update the field in the dialog box to reflect this
        return ::SetDlgItemText(hDlg, IDC_LOGOFILEEDIT, g_FileToLoad);

    case WM_COMMAND:
        // WM_COMMAND will be given to us as the message for the main execution of the
        // dialog box.  This happens when the user hits a button, like OK, Cancel, Reset, etc.

        switch LOWORD(wParam)
        {
        case IDOK:
            // The use pressed the OK button.
            // Copy all of the values which the user entered into the dialog box
            // and transfer it to the all the values from each control and store them in global variables
            // so that we can later persist them to the registry.
            bytesWritten = GetDlgItemText(
                hDlg,
                IDC_LOGOFILEEDIT,
                g_FileToLoad,
                ARRAYSIZE(g_FileToLoad));
            if (bytesWritten != 0)
            {
                // Persist the values
                SetConfigurationString(
                    "ScreenSaverFile",
                    g_FileToLoad);
            }

            EndDialog(hDlg, TRUE);
            return TRUE;

        case IDCANCEL:
            // They hit the Cancel button, so ignore what they put into the
            // dialog box and just exit.
            EndDialog(hDlg, FALSE);
            return TRUE;
   
        case IDC_LOCATE:
            // The user pressed the "Locate" button to look for a file.
            fileToLoad.Assign(WXSTRING(g_FileToLoad));

            // Wrap the hDlg in a wxWindow so that we can use it as
            // the parent window for a wxFileSelector (which we only do
            // so that we can use the LOCALIZED_FILEFILTER_LOGO without
            // modifying it for the win32 API.
            dialog = WrapNativeHwnd(hDlg);

            const wxString selectedFilename = wxFileSelector(
                wxEmptyString,                            // title/message
                fileToLoad.GetPath(),                     // default path
                fileToLoad.GetFullName(),                 // default file name
                WXSTRING(LOCALIZED_LOGO_FILE_EXTENSION),  // default file extension
                WXSTRING(LOCALIZED_FILEFILTER_LOGO),      // file filters
                wxFD_OPEN | wxFD_FILE_MUST_EXIST,         // flags
                dialog);                                  // parent window
            if (!selectedFilename.empty()) {
                // Update the global variable so if the user presses "Locate"
                // again, they will start at the same file that they just
                // selected.
                strncpy(
                    g_FileToLoad,
                    WXSTRING_TO_STRING(selectedFilename),
                    ARRAYSIZE(g_FileToLoad));

                // update the dialog box item
                ::SetDlgItemText(hDlg, IDC_LOGOFILEEDIT, g_FileToLoad);
            }

            DeleteWrapperWindow(dialog);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
    return TRUE;
}

void single_step_box(NODE *the_line)
{
}

// This function is called when Logo wants to write a line of text to the commander's
// recall box.  Since we don't have a recall box, we instead write directly to the
// screen.
void putcombobox(const char *Text, MESSAGETYPE type)
{
    HDC     memoryDeviceContext = GetMemoryDeviceContext();
    HBITMAP oldBitmap           = (HBITMAP) SelectObject(memoryDeviceContext, MemoryBitMap);

    SetBkColor(memoryDeviceContext, scolor);
    SetBkMode(memoryDeviceContext, TRANSPARENT);
    if (type == MESSAGETYPE_Error)
    {
        // Errors are written as red text.
        SetTextColor(memoryDeviceContext, RGB(255, 0, 0));
    }
    else
    {
        // All other messages use the pen color.
        SetTextColor(memoryDeviceContext, pcolor);
    }

    FontRec.lfEscapement = 0;
    HFONT tempFont = CreateFontIndirect(&FontRec);
    HFONT oldFont = (HFONT) SelectObject(memoryDeviceContext, tempFont);

    // figure out how much space this text will take up
    SIZE size;
    GetTextExtentPoint(memoryDeviceContext, Text, strlen(Text), &size);

    if (BitMapHeight < g_NextTextLine + size.cy)
    {
        // The text won't fit on the screen,
        // so wrap it back to the beginning.
        g_NextTextLine = 0;
    }

    TextOut(
        memoryDeviceContext,
        0,
        g_NextTextLine,
        Text,
        strlen(Text));

    SelectObject(memoryDeviceContext, oldFont);
    SelectObject(memoryDeviceContext, oldBitmap);

    DeleteObject(tempFont);

    // Update the screen to show the text.
    RECT textRect;
    textRect.left   = 0;
    textRect.top    = g_NextTextLine;
    textRect.right  = size.cx;
    textRect.bottom = g_NextTextLine + size.cy;

    InvalidateRect(GetScreenWindow(), &textRect, TRUE);

    // Move to the next line
    g_NextTextLine += size.cy + 10;
}

void clearcombobox()
{
    // reset the screen and text area
    lclearscreen(NULL);
    g_NextTextLine = 0;
}

char * promptuser(const char *prompt)
{
    return NULL;
}

HWND GetScreenWindow()
{
    return g_ScreenWindow;
}

HWND GetMainWindow()
{
    // Return the screen so that WM_TIMER events that are
    // created by SetTimer() get posted to the ScreenSaverProc.
    return g_ScreenWindow;
}

wxWindow * GetMainWxWindow()
{
    return g_WxScreenWindow;
}

wxWindow * GetScreenWxWindow()
{
    return g_WxScreenWindow;
}

HWND GetCommanderWindow()
{
    return NULL;
}

wxWindow * GetParentWindowForDialog()
{
    // Because the screen window is full screen and always on top,
    // it must be the parent of any dialog box that we want to
    // show, or else that dialog wouldn't be visible.
    return g_WxScreenWindow;
}

wxWindow * GetEditorWxWindow()
{
    return NULL;
}

int GetScreenHorizontalScrollPosition()
{
    return 0;
}

int GetScreenVerticalScrollPosition()
{
    return 0;
}

void SetScreenScrollPosition(int X, int Y)
{
}

bool IsEditorOpen()
{
    return false;
}

void OpenEditorToLocationOfFirstError(const char *FileName)
{
}


HDC GetScreenDeviceContext()
{
    return static_cast<HDC>(g_WxScreenDeviceContext->GetHDC());
}

HDC GetMemoryDeviceContext()
{
    return static_cast<HDC>(g_WxMemoryDeviceContext->GetHDC());
}

wxDC * GetWxMemoryDeviceContext()
{
    return g_WxMemoryDeviceContext;
}

wxDC * GetWxScreenDeviceContext()
{
    return g_WxScreenDeviceContext;
}

wxDC * GetBackBufferDeviceContext()
{
    // The back buffer is only needed if there are sprite bitmaps.
    // To avoid making all programmer pay the cost of creating a
    // duplicate memory bitmap, we create it lazily.
    if (g_WxBackBufferDeviceContext == NULL)
    {
        g_BackBufferDeviceContext = CreateCompatibleDC(g_ScreenDeviceContext);
        g_BackBuffer = CreateCompatibleBitmap(g_ScreenDeviceContext, BitMapWidth, BitMapHeight);
        SelectObject(g_BackBufferDeviceContext, g_BackBuffer);

        g_WxBackBufferDeviceContext = new wxDCTemp(g_BackBufferDeviceContext);
    }

    return g_WxBackBufferDeviceContext;
}

void UpdateUiExecutionState()
{
}

void OpenStatusWindow()
{
    // create a new status dialog, if necessary
    if (g_StatusDialog == NULL)
    {
        g_StatusDialog = new CStatusDialog(g_WxScreenWindow);
        g_StatusDialog->PopulateAllFields();
        g_StatusDialog->Show();
    }
}

CStatusDialog * GetStatusDialog()
{
    assert(g_StatusDialog != NULL);
    return g_StatusDialog;
}

void CloseStatusWindow()
{
    if (g_StatusDialog != NULL)
    {
        // Close the status window
        g_StatusDialog->Close();
        g_StatusDialog = NULL;
    }
}

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor)
{
    // The screen saver's drawing surface is not resizable, so there
    // are never scrollbars to adjust.
}

void UndockCommanderWindow()
{
    // The screen saver doesn't have a commander window,
    // so there is nothing to undock.
}

void DockCommanderWindow()
{
    // The screen saver doesn't have a commander window,
    // so there is nothing to dock.
}

bool TranslateKeyboardShortcut(MSG & Message)
{
    // The screen saver doesn't have windows with keyboard accelerators.
    return false;
}

int ShowEditorForFile(const char *FileName, NODE *args)
{
    return 0;
}

void
ShowProcedureMiniEditor(
    const char           * ToLine,
    class CDynamicBuffer & ReadBuffer
    )
{
    // Reading from stdin is not supported in the screensaver
    err_logo(STOP_ERROR, NIL);
}

void
TraceOutput(
    const char * FormatString,
    ...
    )
{
    char formattedString[256] = {0};

    va_list args;

    va_start(args, FormatString);

    int bytesNeeded = vsnprintf(
        formattedString,
        ARRAYSIZE(formattedString) - 1,
        FormatString,
        args);
    if (0 <= bytesNeeded)
    {
        OutputDebugString(formattedString);
    }

    va_end(args);
}
