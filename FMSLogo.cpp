#include "pch.h"

#ifndef USE_PRECOMPILED_HEADER
#include "FMSLogo.h"

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
#include "Resource.h"
#endif
#include <locale.h>
#include "CMbcsFileTextStream.h"

// global variables declared in main.h
wxString edit_editexit;     // editor callback instruction list 

int  BitMapWidth = 1000;
int  BitMapHeight = 1000;
bool bFixed = false;

#ifndef WX_PURE
static HANDLE g_SingleInstanceMutex = NULL;
#endif
//
//#ifdef WX_PURE
//#define MAX_PATH (260)
//#endif
static wxString g_FileToLoad; // routine to exec on start
static bool g_EnterPerspectiveMode = false;
static bool g_CustomWidth = false;
static bool g_CustomHeight = false;

#ifdef MEM_DEBUG
#ifdef __WXMSW__
typedef DWORD(WINAPI *GETGUIRESOURCES)(HANDLE, DWORD);

static GETGUIRESOURCES g_GetGuiResources = NULL;
static DWORD           g_OriginalGuiObjects = 0;
static DWORD           g_OriginalUserObjects = 0;
static HANDLE          g_Fmslogo = NULL;
static HMODULE         g_User32 = NULL;
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
	: hasLoadedFileToLoad(false)
	, hasRunStartup(false)
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

static int ReadIntArgument(
	const wxString&    CurrentArgument,
	const wxString&    NextArgument
)
{
	wchar_t* endptr = 0;

	int numericValue = 0;

	if (CurrentArgument.length() > 2)
	{
		// The command-line was given as "-w500".
		numericValue = wcstoul((const wchar_t*)CurrentArgument, &endptr, 10);
	}
	else
	{
		// The -w isn't immediately followed by a number.
		// Try to get the next argument, as in "-w 500".
		if (NextArgument.length() > 0)
		{
			// There was an argument following the -W.
			numericValue = wcstoul(NextArgument, NULL, 10);
		}
		else
		{
			// The command-line ends in something like "-w".
			// In MSWLogo, the width would have silently been 
			// taken to be 0.

			// Since this results in an unusable workspace, we
			// now warn user of their mistake.
			wxMessageBox(
				CurrentArgument,
				GetResourceString(L"LOCALIZED_ERROR_BADCOMMANDLINE"),
				wxOK | wxICON_INFORMATION);

			numericValue = 0;
		}
	}

	return numericValue;
}

wxString CFmsLogo::ProcessCommandLine(wxString lang)
{
	// parse the command-line parameters
	bExpert = false;
	g_CustomWidth = false;
	g_CustomHeight = false;
	bFixed = false;

	// For processing the -L parameter
	bool   copyRemaingArgsAsFilename = false;
	size_t fileToLoadIndex = 0;

	const wxArrayString & realArgv = argv.GetArguments();
	size_t argvSize = realArgv.GetCount();

	//skip self path
	for (size_t i = 1; i < argvSize; i++) {
		const wxString& a = realArgv[i];
		const wxString& next = i < argvSize - 1 ? realArgv[i + 1] : wxString();
		if (!copyRemaingArgsAsFilename) {
			if (a.length() > 0) {
				if (a[0] == L'-' && a.length() > 1) {
					switch ((wchar_t)a[1]) {
					case L'c':
					case L'C':
						if (a.length() > 2)
						{
							lang = a.substr(2);
						}
						else if (next.length() > 0) {
							lang = next;
						}
						break;
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
						BitMapHeight = ReadIntArgument(a, next);
						g_CustomHeight = true;
						break;

					case L'w':
					case L'W':
						BitMapWidth = ReadIntArgument(a, next);
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
							a,
							GetResourceString(L"LOCALIZED_ERROR_BADCOMMANDLINE"),
							wxOK | wxICON_INFORMATION);

						break;
					}
				}
			}
		}
		else
		{
			if (fileToLoadIndex != 0)
			{
				g_FileToLoad += L' ';
			}
			g_FileToLoad += a;

			fileToLoadIndex += a.length();
		}
	}
	return lang;
}

struct LanguagePair {
	const wchar_t* Language;
	const wchar_t* ShortName;
};
LanguagePair Pairs[] = {
	{N_LC_ZH_CN,N_LOCALIZED_STRINGS_FILE_ZH_CN},
	{N_LC_EN,N_LOCALIZED_STRINGS_FILE_EN},
	{N_LC_DE,N_LOCALIZED_STRINGS_FILE_DE},
	{N_LC_ES,N_LOCALIZED_STRINGS_FILE_ES},
	{N_LC_FR,N_LOCALIZED_STRINGS_FILE_FR},
	{N_LC_GR,N_LOCALIZED_STRINGS_FILE_GR},
	{N_LC_HR,N_LOCALIZED_STRINGS_FILE_HR},
	{N_LC_IT,N_LOCALIZED_STRINGS_FILE_IT},
	{N_LC_PL,N_LOCALIZED_STRINGS_FILE_PL},
	{N_LC_PT,N_LOCALIZED_STRINGS_FILE_PT},
	{N_LC_RU,N_LOCALIZED_STRINGS_FILE_RU},
	//{N_LC_PS,N_LOCALIZED_STRINGS_FILE_PS}, //this is Pseudoloc (faked)
};

void CFmsLogo::LoadLocalizedStringFile(const wxString& lang)
{
	wxString name;
	wxString lc = wxSetlocale(LC_CTYPE, (const char*)lang);


	//lang = "":USE SYSTEM LOCALE (for mbtowc)
	if (lc.length() > 0) {

		lc.MakeLower();

		for (int i = 0; i < (signed)ARRAYSIZE(Pairs); i++)
		{
			wxString ln = Pairs[i].Language;
			wxString sn = Pairs[i].ShortName;
			wxString un = sn;
			un.Replace(L'-', L'_');

			if (lc.Contains(ln) || lc.Contains(sn) || lc.Contains(un)) {
				name = sn;
				break;
			}
		}

	}
	if (name.length() == 0) {
		//default is en
		name = N_LOCALIZED_STRINGS_FILE_EN;
	}
	
	wxString path = g_FmslogoBaseDirectory + N_LOCALIZED_STRINGS_FILE_START + name + N_LOCALIZED_STRINGS_FILE_END;

	if (wxFileExists(path)) {
		LoadLocalizedStringsFromFile(path);
	}
	else
	{
		name.MakeUpper();

		wxString lsname = wxString(N_LOCALIZED_STRINGS_FILE_TYPE) + wxString(L"_") + name;

		LoadLocalizedStringsFromResource(lsname, N_LOCALIZED_STRINGS_FILE_TYPE);
	}
}

bool CFmsLogo::OnInit()
{
	bool rval = true;

#ifdef MEM_DEBUG
#ifdef __WXMSW__
	g_Fmslogo = NULL;
	g_User32 = GetModuleHandle("user32.dll");
	if (g_User32 != NULL)
	{
		g_GetGuiResources = (GETGUIRESOURCES)GetProcAddress(g_User32, "GetGuiResources");
		if (g_GetGuiResources != NULL)
		{
			g_Fmslogo = OpenProcess(
				PROCESS_QUERY_INFORMATION,
				FALSE,
				GetCurrentProcessId());
			if (g_Fmslogo != NULL)
			{
				g_OriginalGuiObjects = g_GetGuiResources(g_Fmslogo, GR_GDIOBJECTS);
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

	g_FmslogoBaseDirectory = fmslogoPath;

	this->LoadLocalizedStringFile(
		this->ProcessCommandLine(
			GetConfigurationString(L"locale", L"")
		));

#ifndef WX_PURE

	// Grab the single instance lock.
	g_SingleInstanceMutex = CreateMutex(
		NULL,  // default security attributes
		FALSE, // no initial owner
		L"LogoForWindowsMutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// A copy of Logo is already running.
		if (g_FileToLoad.length() == 0)
		{
			// No logo scripts were specified on the command-line.
			// We should re-use the existing window instead of creating a new 
			// instance of logo, since this was probably just an accident.

			// Find that running copy of Logo and make it visible.
			HWND runningInstance = FindWindow(NULL, GetResourceString(L"LOCALIZED_GENERAL_PRODUCTNAME"));
			if (runningInstance != NULL)
			{
				// bring running instance to the the foreground
				::SetForegroundWindow(runningInstance);
				if (::IsIconic(runningInstance) ||
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
			int frameWidth = wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X);
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
			BitMapHeight = (int)(maxHeight * ScreenSz);
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
		h = std::min(h, (int)(maxHeight * ScreenSz));

		GetConfigurationQuadruple(L"Screen", &x, &y, &w, &h);

		// the smallest reasonable size is 400 x 400.
		h = std::max(h, 480);
		w = std::max(w, 640);

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
	size_t guard = 0;


	// If -P was specified on the command line, enter perspective mode.
	if (g_EnterPerspectiveMode)
	{
		g_EnterPerspectiveMode = false;
		lperspective(NIL);
	}


	// run the script that localizes FMSLogo
	if (!this->hasRunStartup)
	{
		this->hasRunStartup = true;
		wxString stsc = g_FmslogoBaseDirectory + L"startup.logoscript";
		silent_load(NIL, stsc);
	}

	// If a file to load was given on the command line, then execute it.
	if (!this->hasLoadedFileToLoad && g_FileToLoad.length() > 0)
	{
		// Set that we have loaded the file before we actually do
		// in case loading the file causes and idle event to be sent
		// and re-executes this function.
		this->hasLoadedFileToLoad = true;
		silent_load(NIL, g_FileToLoad);
	}

	// Process logo events
	checkqueue();

	// Continue with the default processing
	IdleEvent.Skip();

}

void single_step_box(NODE * the_line)
{
	// Print the line into a buffer, honoring the current printing limits
	CStringPrintedNode printedLine(the_line, CStringPrintedNode::WithPrintLimits);

	// pop up single step box showing line of code
	if (wxMessageBox(
		printedLine,
		GetResourceString(L"LOCALIZED_STEPPING"),
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

wxString promptuser(const wchar_t *prompt)
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
	return CMainFrame::PopupEditorForFile(FileName, EditArguments);
}

void
ShowProcedureMiniEditor(
	const wxString&    ToLine,
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
	wxString message;
	// Format and print the message to stderr
	va_list args;
	va_start(args, FormatString);
	message = wxString::FormatV(FormatString, args);
	//vfwprintf(stderr, FormatString, args);
	va_end(args);

#ifdef __WXMSW__
	OutputDebugString(message);
#endif
}


BEGIN_EVENT_TABLE(CFmsLogo, wxApp)
EVT_IDLE(CFmsLogo::OnIdle)
END_EVENT_TABLE()
