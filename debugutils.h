// -*- c++ -*-
#include "version.h"

#ifndef FMSLOGO_PRIVATE_BUILD
#error Nothing should use debug utilities in an official release
#endif

const char *
KeyCodeToString(
    int keyCode
    );

void
TraceKeyCode(
    const char       * Prefix,
    class wxKeyEvent & KeyEvent
    );
