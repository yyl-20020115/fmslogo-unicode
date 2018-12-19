#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "debugutils.h"
   #include "screenwindow.h"

   #include <wx/event.h>
#endif

const char *
KeyCodeToString(
    int keyCode
    )
{
#define DOKEY(KEY)                 case KEY:  return #KEY + 4
#define DOCHAR(CHAR, LETTER)       case CHAR: return #LETTER
#define DOQUOTEDCHAR(CHAR, STRING) case CHAR: return STRING

    switch (keyCode)
    {
        DOCHAR('!', !);
        DOQUOTEDCHAR('\"', "\"");
        DOCHAR('#', #);
        DOCHAR('$', $);
        DOCHAR('%', %);
        DOCHAR('&', &);
        DOQUOTEDCHAR('\'', "'");
        DOQUOTEDCHAR('(', "(");
        DOQUOTEDCHAR(')', ")");
        DOCHAR('*', *);
        DOCHAR('+', +);
        DOQUOTEDCHAR(',', ",");
        DOCHAR('-', -);
        DOCHAR('.', .);
        DOCHAR('/', /);
        DOCHAR('0', 0);
        DOCHAR('1', 1);
        DOCHAR('2', 2);
        DOCHAR('3', 3);
        DOCHAR('4', 4);
        DOCHAR('5', 5);
        DOCHAR('6', 6);
        DOCHAR('7', 7);
        DOCHAR('8', 8);
        DOCHAR('9', 9);
        DOCHAR(':', :);
        DOCHAR(';', ;);
        DOCHAR('<', <);
        DOCHAR('=', =);
        DOCHAR('>', >);
        DOCHAR('?', ?);
        DOCHAR('@', @);
        DOCHAR('A', A);
        DOCHAR('B', B);
        DOCHAR('C', C);
        DOCHAR('D', D);
        DOCHAR('E', E);
        DOCHAR('F', F);
        DOCHAR('G', G);
        DOCHAR('H', H);
        DOCHAR('I', I);
        DOCHAR('J', J);
        DOCHAR('K', K);
        DOCHAR('L', L);
        DOCHAR('M', M);
        DOCHAR('N', N);
        DOCHAR('O', O);
        DOCHAR('P', P);
        DOCHAR('Q', Q);
        DOCHAR('R', R);
        DOCHAR('S', S);
        DOCHAR('T', T);
        DOCHAR('U', U);
        DOCHAR('V', V);
        DOCHAR('W', W);
        DOCHAR('X', X);
        DOCHAR('Y', Y);
        DOCHAR('Z', Z);
        DOQUOTEDCHAR('[', "[");
        DOQUOTEDCHAR('\\', "\\");
        DOQUOTEDCHAR(']', "]");
        DOCHAR('^', ^);
        DOCHAR('_', _);
        DOCHAR('`', `);
        DOCHAR('{', {);
        DOCHAR('|', |);
        DOCHAR('}', });
        DOCHAR('~', ~);
        DOKEY(WXK_BACK);
        DOKEY(WXK_TAB);
        DOKEY(WXK_RETURN);
        DOKEY(WXK_ESCAPE);
        DOKEY(WXK_SPACE);
        DOKEY(WXK_DELETE);
        DOKEY(WXK_START);
        DOKEY(WXK_LBUTTON);
        DOKEY(WXK_RBUTTON);
        DOKEY(WXK_CANCEL);
        DOKEY(WXK_MBUTTON);
        DOKEY(WXK_CLEAR);
        DOKEY(WXK_SHIFT);
        DOKEY(WXK_ALT);
        DOKEY(WXK_CONTROL);
        DOKEY(WXK_MENU);
        DOKEY(WXK_PAUSE);
        DOKEY(WXK_CAPITAL);
        DOKEY(WXK_END);
        DOKEY(WXK_HOME);
        DOKEY(WXK_LEFT);
        DOKEY(WXK_UP);
        DOKEY(WXK_RIGHT);
        DOKEY(WXK_DOWN);
        DOKEY(WXK_SELECT);
        DOKEY(WXK_PRINT);
        DOKEY(WXK_EXECUTE);
        DOKEY(WXK_SNAPSHOT);
        DOKEY(WXK_INSERT);
        DOKEY(WXK_HELP);
        DOKEY(WXK_NUMPAD0);
        DOKEY(WXK_NUMPAD1);
        DOKEY(WXK_NUMPAD2);
        DOKEY(WXK_NUMPAD3);
        DOKEY(WXK_NUMPAD4);
        DOKEY(WXK_NUMPAD5);
        DOKEY(WXK_NUMPAD6);
        DOKEY(WXK_NUMPAD7);
        DOKEY(WXK_NUMPAD8);
        DOKEY(WXK_NUMPAD9);
        DOKEY(WXK_MULTIPLY);
        DOKEY(WXK_ADD);
        DOKEY(WXK_SEPARATOR);
        DOKEY(WXK_SUBTRACT);
        DOKEY(WXK_DECIMAL);
        DOKEY(WXK_DIVIDE);
        DOKEY(WXK_F1);
        DOKEY(WXK_F2);
        DOKEY(WXK_F3);
        DOKEY(WXK_F4);
        DOKEY(WXK_F5);
        DOKEY(WXK_F6);
        DOKEY(WXK_F7);
        DOKEY(WXK_F8);
        DOKEY(WXK_F9);
        DOKEY(WXK_F10);
        DOKEY(WXK_F11);
        DOKEY(WXK_F12);
        DOKEY(WXK_F13);
        DOKEY(WXK_F14);
        DOKEY(WXK_F15);
        DOKEY(WXK_F16);
        DOKEY(WXK_F17);
        DOKEY(WXK_F18);
        DOKEY(WXK_F19);
        DOKEY(WXK_F20);
        DOKEY(WXK_F21);
        DOKEY(WXK_F22);
        DOKEY(WXK_F23);
        DOKEY(WXK_F24);
        DOKEY(WXK_NUMLOCK);
        DOKEY(WXK_SCROLL);
        DOKEY(WXK_PAGEUP);
        DOKEY(WXK_PAGEDOWN);
        DOKEY(WXK_NUMPAD_SPACE);
        DOKEY(WXK_NUMPAD_TAB);
        DOKEY(WXK_NUMPAD_ENTER);
        DOKEY(WXK_NUMPAD_F1);
        DOKEY(WXK_NUMPAD_F2);
        DOKEY(WXK_NUMPAD_F3);
        DOKEY(WXK_NUMPAD_F4);
        DOKEY(WXK_NUMPAD_HOME);
        DOKEY(WXK_NUMPAD_LEFT);
        DOKEY(WXK_NUMPAD_UP);
        DOKEY(WXK_NUMPAD_RIGHT);
        DOKEY(WXK_NUMPAD_DOWN);
        DOKEY(WXK_NUMPAD_PAGEUP);
        DOKEY(WXK_NUMPAD_PAGEDOWN);
        DOKEY(WXK_NUMPAD_END);
        DOKEY(WXK_NUMPAD_BEGIN);
        DOKEY(WXK_NUMPAD_INSERT);
        DOKEY(WXK_NUMPAD_DELETE);
        DOKEY(WXK_NUMPAD_EQUAL);
        DOKEY(WXK_NUMPAD_MULTIPLY);
        DOKEY(WXK_NUMPAD_ADD);
        DOKEY(WXK_NUMPAD_SEPARATOR);
        DOKEY(WXK_NUMPAD_SUBTRACT);
        DOKEY(WXK_NUMPAD_DECIMAL);
        DOKEY(WXK_NUMPAD_DIVIDE);
        DOKEY(WXK_WINDOWS_LEFT);
        DOKEY(WXK_WINDOWS_RIGHT);
        DOKEY(WXK_WINDOWS_MENU);
        DOKEY(WXK_COMMAND);
        DOKEY(WXK_SPECIAL1);
        DOKEY(WXK_SPECIAL2);
        DOKEY(WXK_SPECIAL3);
        DOKEY(WXK_SPECIAL4);
        DOKEY(WXK_SPECIAL5);
        DOKEY(WXK_SPECIAL6);
        DOKEY(WXK_SPECIAL7);
        DOKEY(WXK_SPECIAL8);
        DOKEY(WXK_SPECIAL9);
        DOKEY(WXK_SPECIAL10);
        DOKEY(WXK_SPECIAL11);
        DOKEY(WXK_SPECIAL12);
        DOKEY(WXK_SPECIAL13);
        DOKEY(WXK_SPECIAL14);
        DOKEY(WXK_SPECIAL15);
        DOKEY(WXK_SPECIAL16);
        DOKEY(WXK_SPECIAL17);
        DOKEY(WXK_SPECIAL18);
        DOKEY(WXK_SPECIAL19);
        DOKEY(WXK_SPECIAL20);
    }

    return "unknown";
}

void
TraceKeyCode(
    const char * Prefix,
    wxKeyEvent & Event
    )
{
    TraceOutput(
        "%s: %u (%s)%s%s\n",
        Prefix,
        Event.GetKeyCode(),
        KeyCodeToString(Event.GetKeyCode()),
        Event.GetKeyCode() != WXK_SHIFT   && Event.ShiftDown() ? " +Shift" : "", 
        Event.GetKeyCode() != WXK_CONTROL && Event.ControlDown() ? " +Ctrl" : "");
}
