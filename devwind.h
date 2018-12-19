// Copyright (C) 2005 by David Costanzo

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __DEVWIND_H_
#define __DEVWIND_H_

struct NODE;

enum KEYBOARDCAPTURE
{
    KEYBOARDCAPTURE_Off,
    KEYBOARDCAPTURE_KeyDown,
    KEYBOARDCAPTURE_KeyDownKeyUp,
};

// global variables
extern wchar_t *keyboard_status;
extern wchar_t *keyboard_keydown;
extern wchar_t *keyboard_keyup;
extern wchar_t *mouse_lbuttondown;
extern wchar_t *mouse_lbuttonup;
extern wchar_t *mouse_rbuttondown;
extern wchar_t *mouse_rbuttonup;
extern wchar_t *mouse_mousemove;

extern enum KEYBOARDCAPTURE KeyboardCapture;
extern int keyboard_value;
extern bool MouseCaptureIsEnabled;
extern int mouse_posx;
extern int mouse_posy;

// function declarations
extern bool CheckOnScreenControls();
extern NODE *ldebugwindows(NODE *args);
extern NODE *lmouseon(NODE *args);
extern NODE *lmouseoff(NODE *arg);
extern NODE *lkeyboardon(NODE *args);
extern NODE *lkeyboardoff(NODE *arg);

extern NODE *lportopen(NODE *args);
extern NODE *lportclose(NODE *arg);
extern NODE *lportreadchar(NODE *arg);
extern NODE *lportwritechar(NODE *args);
extern NODE *lportreadarray(NODE *args);
extern NODE *lportwritearray(NODE *args);
extern NODE *lportflush(NODE *args);
extern NODE *lportmode(NODE *args);
extern NODE *linportb(NODE *args);
extern NODE *loutportb(NODE *args);
extern NODE *linport(NODE *args);
extern NODE *loutport(NODE *args);
extern NODE *lingameport(NODE *args);

#endif // __DEVWIND_H_
