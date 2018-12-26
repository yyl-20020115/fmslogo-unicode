#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "screen.h"

    #include <algorithm>

    #include <wx/event.h>
    #include <wx/dc.h>
    #include <wx/dcmemory.h>
    #include <wx/dcclient.h>

    #include "devwind.h"
    #include "logoeventqueue.h"
    #include "fmslogo.h"
    #include "commander.h"
    #include "commanderinput.h"
    #include "mainframe.h"
    #include "graphwin.h"
    #include "mainwind.h"
    #include "screenwindow.h"
    #include "startup.h"
    #include "logocore.h"
#endif

// ----------------------------------------------------------------------------
// CScreen
// ----------------------------------------------------------------------------

CScreen::CScreen(
    wxWindow* parent,
    int       logicalScreenWidth,
    int       logicalScreenHeight
    ) : 
    wxScrolled<wxWindow>(
        parent, 
        wxID_ANY, 
        wxDefaultPosition,
        wxDefaultSize,
        wxHSCROLL | wxVSCROLL |
            wxCLIP_CHILDREN | // to eliminate flicker when there are child controls
            wxWANTS_CHARS),   // to get Enter and Tab for KEYBOARDON
    m_ScreenDeviceContext(0),
    m_MemoryDeviceContext(0),
    m_MemoryBitmap(0),
    m_BackBufferDeviceContext(0),
    m_BackBuffer(0),
    m_XScrollRatio(0.5),
    m_YScrollRatio(0.5)
{
    if (bFixed)
    {
        // Set the screen client area to match what the user passed
        // in on the command line.
        SetClientSize(logicalScreenWidth, logicalScreenHeight);
    }
    else
    {
        // Prepare the scrollbars
        SetVirtualSize(logicalScreenWidth, logicalScreenHeight);
        SetScrollRate(1, 1);

        // Scroll to the center
        ScrollToRatio();
    }

    m_ScreenDeviceContext = new wxClientDC(this);
    m_MemoryBitmap        = new wxBitmap(logicalScreenWidth, logicalScreenHeight);
    m_MemoryDeviceContext = new wxMemoryDC(*m_MemoryBitmap);

    if (!m_MemoryDeviceContext->IsOk())
    {
        // TODO: report an error to the user
        TraceOutput(L"Failed to initialize memory device context\n");
    }

#ifndef WX_PURE
    // Get a pointer to the native in-memory image of the screen
    MemoryBitMap = static_cast<HBITMAP>(m_MemoryBitmap->GetHBITMAP());
#endif

    // clear the bitmap to all white
    SetBackgroundColour(*wxWHITE);
    m_MemoryDeviceContext->SetBackground(*wxWHITE_BRUSH);
    m_MemoryDeviceContext->Clear();
}

CScreen::~CScreen()
{
    if (m_MemoryDeviceContext)
    {
        m_MemoryDeviceContext->SelectObject(wxNullBitmap);
#ifndef WX_PURE
        MemoryBitMap = NULL;
#endif
    }

    if (m_BackBufferDeviceContext)
    {
        m_BackBufferDeviceContext->SelectObject(wxNullBitmap);
    }

    delete m_ScreenDeviceContext;
    delete m_MemoryBitmap;
    delete m_MemoryDeviceContext;
    delete m_BackBuffer;
    delete m_BackBufferDeviceContext;
}

static
FLONUM
GetScrollRatio(int CurrentPosition, int TotalLength)
{
    FLONUM ratio;

    if (TotalLength <= 1)
    {
        ratio = 0;
    }
    else
    {
        ratio = (FLONUM) CurrentPosition / (FLONUM) (TotalLength);
    }

    return ratio;
}

void CScreen::ScrollToRatio()
{
    // Get the virtual size.
    // This is the size of the drawable areas scaled to the
    // current zoom factor.
    int virtualWidth;
    int virtualHeight;
    GetVirtualSize(&virtualWidth, &virtualHeight);

    // Get the size of the viewable area.
    const wxRect & screenRect = GetClientSize();

    // Calculate the scroll positions that correspond to
    // the scroll ratios.
    int newXScrollPosition = -1;
    if (screenRect.GetWidth() <= virtualWidth)
    {
        int totalRange = virtualWidth - screenRect.GetWidth();
        newXScrollPosition = static_cast<int>(totalRange * m_XScrollRatio);
    }

    int newYScrollPosition = -1;
    if (screenRect.GetHeight() <= virtualHeight)
    {
        int totalRange = virtualHeight - screenRect.GetHeight();
        newYScrollPosition = static_cast<int>(totalRange * m_YScrollRatio);
    }

    // Scroll to the new location
    Scroll(newXScrollPosition, newYScrollPosition);
}

void CScreen::AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor)
{
    SetVirtualSize(
        BitMapWidth  * NewZoomFactor,
        BitMapHeight * NewZoomFactor);

    ScrollToRatio();
}


void CScreen::OnPaint(wxPaintEvent& PaintEvent)
{
    wxPaintDC paintContext(this);
    DoPrepareDC(paintContext); // set origin to account for scrollbar

    // Determine the top left corner of where the window is scrolled
    int vbX;
    int vbY; 
    GetViewStart(&vbX, &vbY);

    PaintToScreen(paintContext, GetUpdateRegion(), vbX, vbY);
}

wxClientDC & CScreen::GetScreenDeviceContext()
{
    return *m_ScreenDeviceContext;
}

wxMemoryDC & CScreen::GetMemoryDeviceContext()
{
    return *m_MemoryDeviceContext;
}

wxMemoryDC & CScreen::GetBackBufferDeviceContext()
{
    // The back buffer is only needed if there are sprite bitmaps.
    // To avoid making all programmer pay the cost of creating a
    // duplicate memory bitmap, we create it lazily.
    if (m_BackBufferDeviceContext == NULL)
    {
        m_BackBuffer = new wxBitmap(BitMapWidth, BitMapHeight);
        m_BackBufferDeviceContext = new wxMemoryDC(*m_BackBuffer);
    }

    return *m_BackBufferDeviceContext;
}

void CScreen::OnScroll(wxScrollWinEvent& Event)
{
    if (Event.GetEventType() == wxEVT_SCROLLWIN_THUMBRELEASE)
    {
        // The user has just let go of the mouse after scrolling.

        // Get the virtual size.
        // This is the size of the drawable areas scaled to the
        // current zoom factor.
        int virtualWidth;
        int virtualHeight;
        GetVirtualSize(&virtualWidth, &virtualHeight);

        // Get the size of the viewable area, which is also
        // the scroll range, since we scroll 1:1 with pixels.
        int viewWidth;
        int viewHeight;
        GetClientSize(&viewWidth, &viewHeight);

        // Update the scroll ratio that corresponds to this event.
        switch (Event.GetOrientation())
        {
        case wxHORIZONTAL:
            m_XScrollRatio = GetScrollRatio(Event.GetPosition(), virtualWidth - viewWidth);
            break;

        case wxVERTICAL:
            m_YScrollRatio = GetScrollRatio(Event.GetPosition(), virtualHeight - viewHeight);
            break;
        }
    }

    // Force a screen repaint
    Update();

    // continue with the default processing
    Event.Skip();
}

// The following key codes are Windows Virtual Key Codes, which is what MSWLogo
// used for its KEYBOARDON events, and for compatibility is what FMSLogo also uses.
// On Windows, these are defined with as VK_*, but since FMSLogo can be compiled
// on non-Windows platforms, the definitions are duplicated.
#ifdef KEY_EXECUTE
#  undef KEY_EXECUTE  // This is defined on Windows platforms as registry permissions
#endif
static const unsigned char KEY_CONTROL_BREAK     = 3;
static const unsigned char KEY_BACKSPACE         = 8;
static const unsigned char KEY_TAB               = 9;
static const unsigned char KEY_CLEAR             = 12;
static const unsigned char KEY_ENTER             = 13;
static const unsigned char KEY_SHIFT             = 16;
static const unsigned char KEY_CONTROL           = 17;
static const unsigned char KEY_ALT               = 18;
static const unsigned char KEY_PAUSE             = 19;
static const unsigned char KEY_CAPSLOCK          = 20;
static const unsigned char KEY_ESCAPE            = 27;
static const unsigned char KEY_SPACEBAR          = 32;
static const unsigned char KEY_PAGE_UP           = 33;
static const unsigned char KEY_PAGE_DOWN         = 34;
static const unsigned char KEY_END               = 35;
static const unsigned char KEY_HOME              = 36;
static const unsigned char KEY_LEFT_ARROW        = 37;
static const unsigned char KEY_UP_ARROW          = 38;
static const unsigned char KEY_RIGHT_ARROW       = 39;
static const unsigned char KEY_DOWN_ARROW        = 40;
static const unsigned char KEY_SELECT            = 41;
static const unsigned char KEY_PRINT             = 42;
static const unsigned char KEY_EXECUTE           = 43;
static const unsigned char KEY_PRINTSCREEN       = 44;
static const unsigned char KEY_INSERT            = 45;
static const unsigned char KEY_DELETE            = 46;
static const unsigned char KEY_HELP              = 47;
static const unsigned char KEY_NUMPAD_0          = 96;
static const unsigned char KEY_NUMPAD_1          = 97;
static const unsigned char KEY_NUMPAD_2          = 98;
static const unsigned char KEY_NUMPAD_3          = 99;
static const unsigned char KEY_NUMPAD_4          = 100;
static const unsigned char KEY_NUMPAD_5          = 101;
static const unsigned char KEY_NUMPAD_6          = 102;
static const unsigned char KEY_NUMPAD_7          = 103;
static const unsigned char KEY_NUMPAD_8          = 104;
static const unsigned char KEY_NUMPAD_9          = 105;
static const unsigned char KEY_NUMPAD_MULTIPLY   = 106;
static const unsigned char KEY_NUMPAD_ADD        = 107;
static const unsigned char KEY_NUMPAD_SUBTRACT   = 109;
static const unsigned char KEY_NUMPAD_DECIMAL    = 110;
static const unsigned char KEY_NUMPAD_DIVIDE     = 111;
static const unsigned char KEY_F1                = 112;
static const unsigned char KEY_F2                = 113;
static const unsigned char KEY_F3                = 114;
static const unsigned char KEY_F4                = 115;
static const unsigned char KEY_F5                = 116;
static const unsigned char KEY_F6                = 117;
static const unsigned char KEY_F7                = 118;
static const unsigned char KEY_F8                = 119;
static const unsigned char KEY_F9                = 120;
static const unsigned char KEY_F10               = 121;
static const unsigned char KEY_F11               = 122;
static const unsigned char KEY_F12               = 123;
static const unsigned char KEY_F13               = 124;
static const unsigned char KEY_F14               = 125;
static const unsigned char KEY_F15               = 126;
static const unsigned char KEY_F16               = 127;
static const unsigned char KEY_F17               = 128;
static const unsigned char KEY_F18               = 129;
static const unsigned char KEY_F19               = 130;
static const unsigned char KEY_F20               = 131;
static const unsigned char KEY_F21               = 132;
static const unsigned char KEY_F22               = 133;
static const unsigned char KEY_F23               = 134;
static const unsigned char KEY_F24               = 135;
static const unsigned char KEY_NUM_LOCK          = 144;
static const unsigned char KEY_SCROLL_LOCK       = 145;
static const unsigned char KEY_LEFT_WINDOWS      = 91;
static const unsigned char KEY_RIGHT_WINDOWS     = 92;
static const unsigned char KEY_APPLICATIONS      = 93;
static const unsigned char KEY_BROWSER_BACK      = 166;
static const unsigned char KEY_BROWSER_FORWARD   = 167;
static const unsigned char KEY_BROWSER_REFRESH   = 168;
static const unsigned char KEY_BROWSER_STOP      = 169;
static const unsigned char KEY_BROWSER_SEARCH    = 170;
static const unsigned char KEY_BROWSER_FAVORITES = 171;
static const unsigned char KEY_BROWSER_HOME      = 172;
static const unsigned char KEY_VOLUME_MUTE       = 173;
static const unsigned char KEY_VOLUME_DOWN       = 174;
static const unsigned char KEY_VOLUME_UP         = 175;
static const unsigned char KEY_MEDIA_NEXT_TRACK  = 176;
static const unsigned char KEY_MEDIA_PREV_TRACK  = 177;
static const unsigned char KEY_MEDIA_STOP        = 178;
static const unsigned char KEY_MEDIA_PLAY_PAUSE  = 179;
static const unsigned char KEY_LAUNCH_MAIL       = 180;
static const unsigned char KEY_LAUNCH_APP1       = 181;
static const unsigned char KEY_LAUNCH_APP2       = 182;
static const unsigned char KEY_PLUS              = 187;
static const unsigned char KEY_COMMA             = 188;
static const unsigned char KEY_MINUS             = 189;
static const unsigned char KEY_PERIOD            = 190;

static const unsigned char KEY_US_SEMICOLON      = 186;
static const unsigned char KEY_US_SLASH          = 191;
static const unsigned char KEY_US_BACKTICK       = 192;
static const unsigned char KEY_US_OPEN_BRACKET   = 219;
static const unsigned char KEY_US_BACKSLASH      = 220;
static const unsigned char KEY_US_CLOSE_BRACKET  = 221;
static const unsigned char KEY_US_QUOTE          = 222;
static const unsigned char KEY_US_EQUALS         = KEY_PLUS;


// This function converts wxWidgets virtual key codes to Windows Virtual
// Key Code, which is what FMSLogo programs expect to be given.
// The code is based on WXToVK() in wxWidgets/src/msw/window.cpp,
// but unlike wxKeyEvent::GetRawKeyCode(), it returns the windows key code
// on non-Windows platforms.
static
int
WxKeyCodeToVirtualKeyCode(
    int WxKeyCode
    )
{
    static const struct wxKeyMapping
    {
        unsigned char  LogoKeyCode;
        wxKeyCode      WxKeyCode;
    } specialKeys[] =
    {
        {KEY_CONTROL_BREAK,      WXK_CANCEL},
        {KEY_BACKSPACE,          WXK_BACK},
        {KEY_TAB,                WXK_TAB},
        {KEY_CLEAR,              WXK_CLEAR},
        {KEY_SHIFT,              WXK_SHIFT},
        {KEY_CONTROL,            WXK_CONTROL},
        {KEY_ALT,                WXK_ALT},
        {KEY_PAUSE,              WXK_PAUSE},
        {KEY_CAPSLOCK,           WXK_CAPITAL},
        {KEY_SPACEBAR,           WXK_SPACE},
        {KEY_ESCAPE,             WXK_ESCAPE},
        {KEY_SELECT,             WXK_SELECT},
        {KEY_PRINT,              WXK_PRINT},
        {KEY_EXECUTE,            WXK_EXECUTE},
        {KEY_PRINTSCREEN,        WXK_SNAPSHOT},
        {KEY_HELP,               WXK_HELP},

        {KEY_NUMPAD_0,           WXK_NUMPAD0},
        {KEY_NUMPAD_1,           WXK_NUMPAD1},
        {KEY_NUMPAD_2,           WXK_NUMPAD2},
        {KEY_NUMPAD_3,           WXK_NUMPAD3},
        {KEY_NUMPAD_4,           WXK_NUMPAD4},
        {KEY_NUMPAD_5,           WXK_NUMPAD5},
        {KEY_NUMPAD_6,           WXK_NUMPAD6},
        {KEY_NUMPAD_7,           WXK_NUMPAD7},
        {KEY_NUMPAD_8,           WXK_NUMPAD8},
        {KEY_NUMPAD_9,           WXK_NUMPAD9},
        {KEY_NUMPAD_MULTIPLY,    WXK_NUMPAD_MULTIPLY},
        {KEY_NUMPAD_ADD,         WXK_NUMPAD_ADD},
        {KEY_NUMPAD_SUBTRACT,    WXK_NUMPAD_SUBTRACT},
        {KEY_NUMPAD_DECIMAL,     WXK_NUMPAD_DECIMAL},
        {KEY_NUMPAD_DIVIDE,      WXK_NUMPAD_DIVIDE},

        {KEY_F1,                 WXK_F1},
        {KEY_F2,                 WXK_F2},
        {KEY_F3,                 WXK_F3},
        {KEY_F4,                 WXK_F4},
        {KEY_F5,                 WXK_F5},
        {KEY_F6,                 WXK_F6},
        {KEY_F7,                 WXK_F7},
        {KEY_F8,                 WXK_F8},
        {KEY_F9,                 WXK_F9},
        {KEY_F10,                WXK_F10},
        {KEY_F11,                WXK_F11},
        {KEY_F12,                WXK_F12},
        {KEY_F13,                WXK_F13},
        {KEY_F14,                WXK_F14},
        {KEY_F15,                WXK_F15},
        {KEY_F16,                WXK_F16},
        {KEY_F17,                WXK_F17},
        {KEY_F18,                WXK_F18},
        {KEY_F19,                WXK_F19},
        {KEY_F20,                WXK_F20},
        {KEY_F21,                WXK_F21},
        {KEY_F22,                WXK_F22},
        {KEY_F23,                WXK_F23},
        {KEY_F24,                WXK_F24},

        {KEY_NUM_LOCK,           WXK_NUMLOCK},
        {KEY_SCROLL_LOCK,        WXK_SCROLL},

        {KEY_LEFT_WINDOWS,       WXK_WINDOWS_LEFT},
        {KEY_RIGHT_WINDOWS,      WXK_WINDOWS_RIGHT},
        {KEY_APPLICATIONS,       WXK_WINDOWS_MENU},
#if wxCHECK_VERSION(3, 1, 0)
        {KEY_BROWSER_BACK,        WXK_BROWSER_BACK},
        {KEY_BROWSER_FORWARD,     WXK_BROWSER_FORWARD},
        {KEY_BROWSER_REFRESH,     WXK_BROWSER_REFRESH},
        {KEY_BROWSER_STOP,        WXK_BROWSER_STOP},
        {KEY_BROWSER_SEARCH,      WXK_BROWSER_SEARCH},
        {KEY_BROWSER_FAVORITES,   WXK_BROWSER_FAVORITES},
        {KEY_BROWSER_HOME,        WXK_BROWSER_HOME},
        {KEY_VOLUME_MUTE,         WXK_VOLUME_MUTE},
        {KEY_VOLUME_DOWN,         WXK_VOLUME_DOWN},
        {KEY_VOLUME_UP,           WXK_VOLUME_UP},
        {KEY_MEDIA_NEXT_TRACK,    WXK_MEDIA_NEXT_TRACK},
        {KEY_MEDIA_PREV_TRACK,    WXK_MEDIA_PREV_TRACK},
        {KEY_MEDIA_STOP,          WXK_MEDIA_STOP},
        {KEY_MEDIA_PLAY_PAUSE,    WXK_MEDIA_PLAY_PAUSE},
        {KEY_LAUNCH_MAIL,         WXK_LAUNCH_MAIL},
        {KEY_LAUNCH_APP1,         WXK_LAUNCH_APP1},
        {KEY_LAUNCH_APP2,         WXK_LAUNCH_APP2},
#endif
        // Add some keys codes that are not 1:1
        {KEY_PAGE_UP,      WXK_PAGEUP},
        {KEY_PAGE_UP,      WXK_NUMPAD_PAGEUP},

        {KEY_PAGE_DOWN,    WXK_PAGEDOWN},
        {KEY_PAGE_DOWN,    WXK_NUMPAD_PAGEDOWN},

        {KEY_END,          WXK_END},
        {KEY_END,          WXK_NUMPAD_END},

        {KEY_HOME,         WXK_HOME},
        {KEY_HOME,         WXK_NUMPAD_HOME},

        {KEY_LEFT_ARROW,   WXK_LEFT},
        {KEY_LEFT_ARROW,   WXK_NUMPAD_LEFT},

        {KEY_UP_ARROW,     WXK_UP},
        {KEY_UP_ARROW,     WXK_NUMPAD_UP},

        {KEY_RIGHT_ARROW,  WXK_RIGHT},
        {KEY_RIGHT_ARROW,  WXK_NUMPAD_RIGHT},

        {KEY_DOWN_ARROW,   WXK_DOWN},
        {KEY_DOWN_ARROW,   WXK_NUMPAD_DOWN},

        {KEY_INSERT,       WXK_INSERT},
        {KEY_INSERT,       WXK_NUMPAD_INSERT},

        {KEY_DELETE,       WXK_DELETE},
        {KEY_DELETE,       WXK_NUMPAD_DELETE},

        {KEY_ENTER,        WXK_NUMPAD_ENTER},


        // Many WXK_ codes use ASCII instead of a symbolic value,
        // some of which are different from the corresponding
        // virtual key code.
        {KEY_PLUS,               static_cast<wxKeyCode>('+')},
        {KEY_COMMA,              static_cast<wxKeyCode>(',')},
        {KEY_MINUS,              static_cast<wxKeyCode>('-')},
        {KEY_PERIOD,             static_cast<wxKeyCode>('.')},

        // Furthermoe, some of the ASCII values clash with the
        // virtual key codes, creating ambiguitity.  From example,
        // the ASCII value of "'" is 39, but this is KEY_LEFT_ARROW.
        // Another problem is that [;:] on a US keyboard has the code
        // VK_OEM_1 (186) but the ASCII value of ";" is 59.
        // We can create a mapping for these characters, but they
        // probably only work on US keyboard layouts.
        {KEY_US_SEMICOLON,       static_cast<wxKeyCode>(';')},
        {KEY_US_SLASH,           static_cast<wxKeyCode>('/')},
        {KEY_US_BACKTICK,        static_cast<wxKeyCode>('`')},
        {KEY_US_OPEN_BRACKET,    static_cast<wxKeyCode>('[')},
        {KEY_US_BACKSLASH,       static_cast<wxKeyCode>('\\')},
        {KEY_US_CLOSE_BRACKET,   static_cast<wxKeyCode>(']')},
        {KEY_US_QUOTE,           static_cast<wxKeyCode>('\'')},
        {KEY_PLUS,               static_cast<wxKeyCode>('=')},
    };

    // check the table first
    for (size_t i = 0; i < ARRAYSIZE(specialKeys); i++)
    {
        if (specialKeys[i].WxKeyCode == WxKeyCode)
        {
            return specialKeys[i].LogoKeyCode;
        }
    }

    // This key code has no special mapping, so it's likely to be
    // an ASCII code.
    return WxKeyCode;
}

void CScreen::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    if (KeyboardCapture == KEYBOARDCAPTURE_Off)
    {
        if (keyCode == WXK_TAB)
        {
            // Because we use the wxWANTS_CHARS to capture WKX_TAB
            // and WXK_RETURN codes for KEYBOARDON, we must
            // we must explicitly convert tabs to navigation
            // in the cases where no keyboard capture is requested.
            int flags;
            if (Event.ShiftDown())
            {
                flags = wxNavigationKeyEvent::IsBackward;
            }
            else
            {
                flags = wxNavigationKeyEvent::IsForward;
            }

            if (Event.ControlDown())
            {
                CFmsLogo::GetMainFrame()->KeyboardNavigateTopLevelWindow(
                    this,
                    flags);
            }
            else
            {
                Navigate(flags);
            }
        }
        else if (Event.GetModifiers() == wxMOD_NONE && keyCode == WXK_F1)
        {
            // F1 displays the help when keyboard capture isn't on
            do_help(NULL);
        }
    }

    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
    {
        // KEYBOARDON for up and down events is enabled, so we send the
        // keystroke to the Logo program, instead of to the window.

        // Map the WX keycode to the virtual key code that Logo programs expect.
#ifdef __WXMSW__
        // On Windows use the raw key code with is what MSWLogo used and
        // so is guaranteed to be correct.
        int windowsKeyCode = static_cast<int>(Event.GetRawKeyCode());

        // Confirm that our logic for converting the key to a virtual key code
        // matches the guaranteed-to-be-correct virtual key code.
        assert(windowsKeyCode == WxKeyCodeToVirtualKeyCode(keyCode));
#else // !__WXMSW__
        // Translate the wxWidgets key code to a virtual key code.
        int windowsKeyCode = WxKeyCodeToVirtualKeyCode(keyCode);
#endif

        // Post the event to the logo event queue
        callthing *callevent = callthing::CreateKeyboardEvent(
            keyboard_keydown,
            windowsKeyCode);

        calllists.insert(callevent);
        checkqueue();
    }
    else if (keyCode == WXK_PAGEUP   ||
             keyCode == WXK_UP       ||
             keyCode == WXK_PAGEDOWN ||
             keyCode == WXK_DOWN     ||
             keyCode == WXK_LEFT     ||
             keyCode == WXK_RIGHT)
    {
        // scroll main window with arrow keys
        Event.Skip();
    }
    else if (KeyboardCapture == KEYBOARDCAPTURE_Off &&
             CCommanderInput::WantsKeyEvent(keyCode))
    {
        CCommander * commander = CFmsLogo::GetMainFrame()->GetCommander();

        // We don't handle this key.
        // Give focus to the edit box and send the press to it.
        commander->ProcessKeyDownEventAtInputControl(Event);
    }
    else
    {
        // default processing
        Event.Skip();
    }
}

void CScreen::OnKeyUp(wxKeyEvent& Event)
{
    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
    {
        // Map WX keycodes to Windows key codes
        int wxKeyCode      = Event.GetKeyCode();
        int windowsKeyCode = WxKeyCodeToVirtualKeyCode(wxKeyCode);

        // Post the event to the logo event queue
        callthing *callevent = callthing::CreateKeyboardEvent(
            keyboard_keyup,
            windowsKeyCode);

        calllists.insert(callevent);
        checkqueue();
    }
    else
    {
        // else do your normal stuff
        Event.Skip();
    }
}

static
bool
IsLogoCharCode(
    int WxKeyCode
    )
{
    // MSWLogo did not consider all keys to be "KeyDown" keycodes.
    // For example, the function keys and the shift key did not
    // generate a KeyDown event.  For compatibility, we only
    // forward a keyboard event when MSWLogo would have.

    // Look for "bad" codes, rather than the "good" key codes 
    // because it's better to err on the side of generating too many
    // events (which will likely be ignored by the Logo program)
    // than generating too few, which could cause some Logo programs
    // to misbehave.
    switch (WxKeyCode)
    {
    case WXK_CANCEL:
    case WXK_CLEAR:
    case WXK_SHIFT:
    case WXK_CONTROL:
    case WXK_ALT:
    case WXK_PAUSE:
    case WXK_SELECT:
    case WXK_PRINT:
    case WXK_SNAPSHOT:
    case WXK_HELP:

    case WXK_F1:
    case WXK_F2:
    case WXK_F3:
    case WXK_F4:
    case WXK_F5:
    case WXK_F6:
    case WXK_F7:
    case WXK_F8:
    case WXK_F9:
    case WXK_F10:
    case WXK_F11:
    case WXK_F12:
    case WXK_F13:
    case WXK_F14:
    case WXK_F15:
    case WXK_F16:
    case WXK_F17:
    case WXK_F18:
    case WXK_F19:
    case WXK_F20:
    case WXK_F21:
    case WXK_F22:
    case WXK_F23:
    case WXK_F24:

    case WXK_NUMLOCK:
    case WXK_SCROLL:

    case WXK_WINDOWS_LEFT:
    case WXK_WINDOWS_RIGHT:
    case WXK_WINDOWS_MENU:

    case WXK_END:
    case WXK_NUMPAD_END:
    case WXK_HOME:
    case WXK_NUMPAD_HOME:
    case WXK_LEFT:
    case WXK_NUMPAD_LEFT:
    case WXK_UP:
    case WXK_NUMPAD_UP:
    case WXK_RIGHT:
    case WXK_NUMPAD_RIGHT:
    case WXK_DOWN:
    case WXK_NUMPAD_DOWN:
    case WXK_INSERT:
    case WXK_NUMPAD_INSERT:
    case WXK_DELETE:
    case WXK_NUMPAD_DELETE:
    case WXK_PAGEUP:
    case WXK_NUMPAD_PAGEUP:
    case WXK_PAGEDOWN:
    case WXK_NUMPAD_PAGEDOWN:
        return false;
    }

    return true;
}

static
bool
IsLogoScrollingCharCode(
    int WxKeyCode
    )
{
    switch (WxKeyCode)
    {
    case WXK_LEFT:
    case WXK_UP:
    case WXK_RIGHT:
    case WXK_DOWN:
    case WXK_PAGEUP:
    case WXK_NUMPAD_PAGEUP:
    case WXK_PAGEDOWN:
    case WXK_NUMPAD_PAGEDOWN:
        return true;
    }

    return false;
}

void CScreen::OnChar(wxKeyEvent& Event)
{
    int wxKeyCode = Event.GetKeyCode();

    // If KEYBOARDON was run with a single parameter, then MSWLogo converts
    // WM_CHAR messages, instead of WM_KEY_DOWN messages.
    // WM_CHAR is similar to EVT_CHAR events in wxWidgets, except that EVT_CHAR
    // over-generates, so we filter out the extras using IsLogoCharCode().
    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDown)
    {
        if (IsLogoCharCode(wxKeyCode))
        {
            // Forward the event to Logo
            callthing * callevent = callthing::CreateKeyboardEvent(
                keyboard_keyup,
                wxKeyCode);

            calllists.insert(callevent);
            checkqueue();
        }
        else if (IsLogoScrollingCharCode(wxKeyCode))
        {
            // For compatiblity with MSWLogo, we let a few "char" events
            // through to wxWidgets for their default behavior, which is
            // mostly just to scroll the screen.
            Event.Skip();
        }
        else
        {
            // Ignore the event
        }
    }
    else
    {
        // else do your normal stuff
        Event.Skip();
    }
}

static void ProcessMouseEvent(wxMouseEvent & Event, const wxString&  Callback)
{
    if (MouseCaptureIsEnabled)
    {
        // if user turned on mouse the queue up event
        callthing * callevent = callthing::CreateMouseEvent(
            Callback,
            Event.GetX(),
            Event.GetY());

        calllists.insert(callevent);
        checkqueue();
    }

    // Always do default processing
    Event.Skip();
}

void CScreen::OnRightMouseButtonDown(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_rbuttondown);
}

void CScreen::OnRightMouseButtonUp(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_rbuttonup);
}

void CScreen::OnLeftMouseButtonDown(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_lbuttondown);
}

void CScreen::OnLeftMouseButtonUp(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_lbuttonup);
}

void CScreen::OnMouseMove(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_mousemove);
}

void CScreen::OnSize(wxSizeEvent& Event)
{
    ScrollToRatio();
    Refresh(false);
    Event.Skip();
}

BEGIN_EVENT_TABLE(CScreen, wxScrolled<wxWindow>)
    EVT_KEY_DOWN(CScreen::OnKeyDown)
    EVT_KEY_UP(CScreen::OnKeyUp)
    EVT_CHAR(CScreen::OnChar)
    EVT_LEFT_DOWN(CScreen::OnLeftMouseButtonDown)
    EVT_LEFT_UP(CScreen::OnLeftMouseButtonUp)
    EVT_RIGHT_DOWN(CScreen::OnRightMouseButtonDown)
    EVT_RIGHT_UP(CScreen::OnRightMouseButtonUp)
    EVT_MOTION(CScreen::OnMouseMove)
    EVT_PAINT(CScreen::OnPaint)
    EVT_SIZE(CScreen::OnSize)
    EVT_SCROLLWIN(CScreen::OnScroll)
END_EVENT_TABLE()
