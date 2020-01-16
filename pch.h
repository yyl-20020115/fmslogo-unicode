#ifndef __PCH_H__
#define __PCH_H__
#ifndef wxDEBUG_LEVEL
#define wxDEBUG_LEVEL 0
#endif
#ifdef _WINDOWS
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif
#else
//NOTICE: NEVER include <wx/setup.h> in windows version!
#ifdef LINUX
#include <wx/setup.h>
#endif
#endif

#endif

