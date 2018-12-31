#ifndef __PCH_H__
#define __PCH_H__
#ifdef _WINDOWS
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif
#endif

#include <wx/setup.h>
#endif
