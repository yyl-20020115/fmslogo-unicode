// This is a header file that includes all #include files that
// must be included by any source code in FMSlogo.
//
// The intention is for it to be used as a precompiled header to
// improve build times.
//
// Because some compilers require that a precompiled header be listed
// first in the source code the basic usage pattern is:
//
// #include "pch.h"
// #ifndef USE_PRECOMPILED_HEADER
//    #include "header-for-this-file.h"
//    ..
// #endif
//
// To avoid including unneeded header files for a translation unit when
// precompiled header files are not used, we compile this pch.h to nothing
// when not using precompiled headers.  This only leaves what's in the
// #ifndef clause.
//

#ifdef USE_PRECOMPILED_HEADER

#ifdef __WXMSW__
  #include <windows.h>  // for LOGFONT
  #include <windowsx.h> // for GlobalFreePtr()
  #include <commctrl.h> // for combobox style manifest constants
  #include <shlobj.h>

  #ifdef min // MS compilers #define min in windows.h
    #undef min
  #endif
  #ifdef max // MS compilers #define max in windows.h
    #undef max
  #endif

  #define BOOLEAN_DEFINED // For gbm.h
#endif


// C header files
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <malloc.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef WX_PURE
  #include <unistd.h>
#else
  #include <io.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>

// C++ header files
#include <algorithm>

// wxWidgets header files
#include <wx/arrstr.h>
#include <wx/app.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/cursor.h>
#include <wx/clipbrd.h>
#include <wx/combobox.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/dcmirror.h>
#include <wx/defs.h>
#include <wx/dialog.h>
#include <wx/dir.h>
#include <wx/event.h>
#include <wx/filename.h>
#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/fontdlg.h>
#include <wx/fontutil.h>
#include <wx/frame.h>
#include <wx/gdicmn.h> 
#include <wx/help.h>
#include <wx/listbox.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/printdlg.h>
#include <wx/radiobut.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/scrolbar.h>
#include <wx/scrolwin.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/splitter.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/utils.h>

#ifdef __WXMSW__
  #include <wx/msw/private.h>
  #include <wx/msw/dc.h>
#endif

#ifdef WX_PURE
  #define GetRValue(rgb) (((rgb) >> 0)  & 0xFF)
  #define GetGValue(rgb) (((rgb) >> 8)  & 0xFF)
  #define GetBValue(rgb) (((rgb) >> 16) & 0xFF)
  #define RGB(r, g, b) (((r) & 0xFF) | (((g) & 0xFF) << 8) | (((b) & 0xFF) << 16))

  struct LOGPEN;
  typedef struct __PEN         * HPEN;
  typedef struct __HDC         * HDC;
  typedef struct __BITMAP      * HBITMAP;
  typedef struct __LOGPALLETTE * PLOGPALETTE;
  typedef struct __WND         * HWND;

  typedef int LONG;

  struct RECT {
      int left;
      int top;
      int right;
      int bottom;
  };
#endif

// FMSLogo header files
#include "3dsolid.h"
#include "aboutfmslogo.h"
#include "aboutmultiplesclerosis.h"
#include "activearea.h"
#include "appendablelist.h"
#include "appendablelist.h"
#include "argumentutils.h"
#include "avltree.h"
#include "commander.h"
#include "commanderbutton.h"
#include "commanderhistory.h"
#include "commanderinput.h"
#include "commandertogglebutton.h"
#include "const.h"
#include "coms.h"
#include "cursor.h"
#include "devwind.h"
#include "dib.h"
#include "dllwind.h"
#include "dlgwind.h"
#include "dynamicbuffer.h"
#include "editproceduredialog.h"
#include "eraseproceduredialog.h"
#include "error.h"
#include "eval.h"
#include "gbm.h"
#include "gbmhelp.h"
#include "gbmbmp.h"
#include "gbmgif.h"
#include "intern.h"
#include "fmslogo.h"
#include "fileswnd.h"
#include "files.h"
#include "fontutils.h"
#include "graphics.h"
#include "graphwin.h"
#include "guiutils.h"
#include "helputils.h"
#include "ibmterm.h"
#include "init.h"
#include "lists.h"
#include "logocore.h"
#include "logorc.h"
#include "logoeventqueue.h"
#include "logomath.h"
#include "mainframe.h"
#include "mainwind.h"
#include "mem.h"
#include "messagebox.h"
#include "minieditor.h"
#include "minieditortextctrl.h"
#include "mmwind.h"
#include "netwind.h"
#include "paren.h"
#include "parse.h"
#include "print.h"
#include "questionbox.h"
#include "savebeforeexitdialog.h"
#include "screen.h"
#include "screenwindow.h"
#include "selectbox.h"
#include "selectstartupinstruction.h"
#include "setactivearea.h"
#include "setcolor.h"
#include "setpensize.h"
#include "startup.h"
#include "status.h"
#include "statusdialog.h"
#include "stringadapter.h"
#include "stringprintednode.h"
#include "sort.h"
#include "term.h"
#include "unix.h"
#include "utils.h"
#include "vector.h"
#include "workspaceeditor.h"
#include "wrksp.h"

#include "localizedstrings.h"
#include "debugheap.h"

#endif // USE_PRECOMPILED_HEADER
