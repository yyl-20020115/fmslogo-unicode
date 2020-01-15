// -*- c++ -*-
// Copyright (C) 1995 by George Mills
//
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

// This file defines an abstraction layer which the logo
// core can use to talk to the different FMSLogo front-ends:
//
// * Main FMSLogo Environment
// * Screensaver


#ifndef __SCREENWINDOW_H_
#define __SCREENWINDOW_H_

#ifndef WX_PURE
  #include <windows.h>
#endif // WX_PURE

#include "logodata.h"

#ifndef WX_PURE
HWND GetScreenWindow();
HWND GetMainWindow();
HWND GetCommanderWindow();
#endif

class wxWindow * GetMainWxWindow();
class wxWindow * GetScreenWxWindow();
class wxWindow * GetEditorWxWindow();
class wxWindow * GetParentWindowForDialog();

int GetScreenHorizontalScrollPosition();
int GetScreenVerticalScrollPosition();
void SetScreenScrollPosition(int X, int Y);

bool IsEditorOpen();

// This is called when FMSLogo attempts to load a file, such
// as one that was passed on the command line, and an error
// is encountered while evaluating the contents.
void OpenEditorToLocationOfFirstError(const wchar_t *FileName);

#ifndef WX_PURE
// Returns the device context for the main drawing surface (the screen).
HDC GetScreenDeviceContext();

// Returns the device context for MemoryBitMap
HDC GetMemoryDeviceContext();

// Locates the window for which the message was generated and attempts to
// translate it as a keyboard accelerator (keyboard shortcut) using that
// window's accelerator table.
//
// Returns true if the message was translated (in which case it does
// not need to be handled further).  Returns false, otherwise (in which
// case it should be translated and dispatched).
//
// Note that this routine exists because the Logo engine is executed from
// the context of the message pump and we still want to be able to process
// user input while it's running.
bool MainframeTranslateKeyboardShortcut(MSG & Message);

#endif

// Returns a device context of a bitmap that is distinct from MemoryBitMap,
// but has the same characteristics (bit depth, width, height, etc.)
class wxDC * GetBackBufferDeviceContext();

// Returns a device context of the main bitmap.
class wxDC * GetWxMemoryDeviceContext();

// Returns a device context of the main bitmap.
class wxDC * GetWxScreenDeviceContext();

// Instructs the UI to update its state to reflect that FMSLogo has either
// begin or stopped executing Logo instructions.
void UpdateUiExecutionState();

void OpenStatusWindow();
void CloseStatusWindow();
class CStatusDialog * GetStatusDialog();

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor);
void UndockCommanderWindow();
void DockCommanderWindow();
int  ShowEditorForFile(const wchar_t *FileName, NODE *args);

// ShowProcedureMiniEditor is called when TO is executed and
// the input is expected to come from stdin (which is typically
// implemented as a modal dialog box.
//
// ToLine     - A text buffer that holds the TO instruction that
//              is being executed.
// ReadBuffer - A buffer to hold a new definition that was read.
//
void
ShowProcedureMiniEditor(
    const wxString&        ToLine,
    class CDynamicBuffer & ReadBuffer
    );

void TraceOutput(const wchar_t * FormatString, ...);

#endif // __SCREENWINDOW_H_
