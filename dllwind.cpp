/*
 *   Copyright (C) 1995 by the Regents of the University of California
 *   Copyright (C) 1995 by George Mills
 *   Copyright (C) 1995 by Telmo Carmo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <windows.h>
   #include <windowsx.h> // for GlobalFreePtr()
   #include <assert.h>
   #include <stdio.h>

   #include "logocore.h"
   #include "mem.h" // for newnode
   #include "appendablelist.h"
   #include "stringprintednode.h"
   #include "eval.h"
   #include "init.h"
   #include "error.h"
   #include "logodata.h"
   #include "parse.h"
   #include "screenwindow.h" // for TraceOutput
//   #include "debugheap.h"
#include <wx/string.h>
#endif
//
//#ifdef __BORLANDC__
//
//extern "C" 
//{
//    void PASCAL pushl(DWORD);
//}
//
//#elif defined __GNUC__
//
//#define pushl(D)                                     \
//    asm ("pushl %0;"                                 \
//         :               /* output */                \
//         :"r"((int)D)    /* input  */                \
//         :"%esp"         /* clobbered register */    \
//         );
//
//#else
//  #error Unsupported compiler
//#endif

extern "C" void __stdcall _do_push(void*); //implemented in helpers32.asm or helpers64.asm

class CLoadedDll
{
    friend class CLoadedDlls;
    friend class CLoadedDllInvariant;

public:
    CLoadedDll();
    ~CLoadedDll();

    bool         Load(const wxString& DllName);
    HMODULE      GetHandle();
    const wxString& GetFileName() const;
    void         AddReference();

private:
    wxString     m_DllName;
    HMODULE      m_Dll;
    int          m_RefCount;
    CLoadedDll * m_Next;
};


#ifdef NDEBUG
#  define ASSERT_LOADEDDLL_INVARIANT
#else
#  define ASSERT_LOADEDDLL_INVARIANT CLoadedDllInvariant invariant(*this)

class CLoadedDllInvariant
{
public:
    CLoadedDllInvariant(const CLoadedDll & LoadedDll)
        : m_LoadedDll(LoadedDll)
    {
        AssertInvariant();
    }

    ~CLoadedDllInvariant()
    {
        AssertInvariant();
    }

    void AssertInvariant() const
    {
        assert(m_LoadedDll.m_RefCount >= 0);

        if (m_LoadedDll.m_RefCount == 0)
        {
            // the DLL has not been loaded, yet
            assert(m_LoadedDll.m_DllName.length() == 0);
            assert(m_LoadedDll.m_Dll        == NULL);
        }
        else
        {
            // the DLL should have been loaded
            assert(m_LoadedDll.m_Dll != NULL);
            assert(m_LoadedDll.m_DllName.length() != 0);
        }
    }

private:
    const CLoadedDll & m_LoadedDll;
};

#endif // NDEBUG

CLoadedDll::CLoadedDll() :
    m_Dll(NULL),
    m_RefCount(0),
    m_Next(NULL),
	m_DllName()
{
}

CLoadedDll::~CLoadedDll() 
{
    assert(m_RefCount == 0);
    assert(m_Next     == NULL);

    FreeLibrary(m_Dll);
}

void CLoadedDll::AddReference()
{
    ASSERT_LOADEDDLL_INVARIANT;
    m_RefCount++;
}

HMODULE CLoadedDll::GetHandle()
{
    ASSERT_LOADEDDLL_INVARIANT;
    return m_Dll;
}

const wxString& CLoadedDll::GetFileName() const
{
    ASSERT_LOADEDDLL_INVARIANT;
    return m_DllName;
}

bool CLoadedDll::Load(const wxString& DllName)
{
    // this should not have been loaded before
    ASSERT_LOADEDDLL_INVARIANT;
    assert(m_RefCount   == 0);
    assert(m_Dll        == NULL);
    assert(m_DllName.length() == 0);

    m_Dll = LoadLibrary(DllName);
    if (m_Dll == NULL)
    {
        return false;
    }
   
    // store the name of the DLL for later use
	this->m_DllName = DllName;

    // the library now has a reference
    m_RefCount = 1;

    return true;
}

class CLoadedDlls
{
public:
    CLoadedDlls();
    ~CLoadedDlls();

    void         Insert(CLoadedDll * NewEntry);
    void         Remove(CLoadedDll * EntryToRemove);
    CLoadedDll * FindByName(const wxString& DllName);
    CLoadedDll * GetFirst();
    CLoadedDll * GetNext(CLoadedDll * CurrentDll);

    bool         IsEmpty() const;

private:
    CLoadedDll * m_ListHead;
};

CLoadedDlls::CLoadedDlls() :
    m_ListHead(NULL)
{
}

CLoadedDlls::~CLoadedDlls() 
{
    assert(m_ListHead == NULL); // memory leak
}

void CLoadedDlls::Insert(CLoadedDll * NewEntry)
{
    assert(NewEntry != NULL);
    assert(NewEntry->m_Next == NULL);                    // this is already in a list
    assert(FindByName(NewEntry->GetFileName()) == NULL); // this DLL is already in the list

    // add this to the front of the list
    NewEntry->m_Next = m_ListHead;
    m_ListHead       = NewEntry;
}

void CLoadedDlls::Remove(CLoadedDll * EntryToRemove)
{
    assert(EntryToRemove != NULL);
    assert(FindByName(EntryToRemove->GetFileName()) == EntryToRemove); // is in this list

    // decrement the reference count
    EntryToRemove->m_RefCount--;

    if (EntryToRemove->m_RefCount == 0)
    {
        // that was the final reference, so we must remove it from the list
        for (CLoadedDll ** dllPtr = &m_ListHead;
             *dllPtr != NULL;
             dllPtr = &(*dllPtr)->m_Next)
        {
            CLoadedDll * dll = *dllPtr;
            if (dll == EntryToRemove)
            {
                // found it.  Unlink it from the list and delete it
                *dllPtr = (*dllPtr)->m_Next;
                dll->m_Next = NULL;

                delete dll;
                break;
            }
        }
    }
}

CLoadedDll * CLoadedDlls::FindByName(const wxString& TargetDllName)
{
    for (CLoadedDll * dll = m_ListHead; dll != NULL; dll = dll->m_Next)
    {
        assert(dll->m_RefCount != 0);  // every DLL in the list should have a reference

        if (dll->m_DllName.IsSameAs( TargetDllName,false))
        {
            // found it
            return dll;
        }
    }

    // the requested DLL is not in this list
    return NULL;
}

CLoadedDll * CLoadedDlls::GetNext(CLoadedDll * Current)
{
#ifndef NDEBUG
    // make sure that Current is part of this list in debug builds
    bool currentDllIsInList = false;
    for (CLoadedDll * dll = m_ListHead; dll != NULL; dll = dll->m_Next)
    {
        if (dll == Current)
        {
            // found it
            currentDllIsInList = true;
            break;
        }
    }
    assert(currentDllIsInList);
#endif // NDEBUG

    return Current->m_Next;
}

CLoadedDll * CLoadedDlls::GetFirst()
{
    return m_ListHead;
}

bool CLoadedDlls::IsEmpty() const
{
    return m_ListHead == NULL;
}

static CLoadedDlls g_LoadedDlls;

NODE *ldllload(NODE *arg)
{
    // read the name of the DLL that we're supposed to load
    CStringPrintedNode dllName(car(arg));

    if (stopping_flag == THROWING)
    {
        return Unbound;
    }

    // look for this DLL in the list
    CLoadedDll * dll = g_LoadedDlls.FindByName(dllName);
    if (dll != NULL)
    {
        // Found it.  So all we need to do is increment the reference count.
        dll->AddReference();
    }
    else
    {
        // This DLL hasn't been loaded before, so load it
        dll = new CLoadedDll();
        if (!dll->Load(dllName))
        {
            delete dll;

            err_logo(DLL_LOAD_FAILED, NIL);
            return Unbound;
        }

        // add this to the list of DLLs that we loaded
        g_LoadedDlls.Insert(dll);
    }

    return Unbound;
}

NODE *ldllfree(NODE * args)
{
    CLoadedDll * dll;

    if (args != NIL)
    {
        // we are freeing a DLL by name
        CStringPrintedNode dllName(car(args));

        if (stopping_flag == THROWING)
        {
            return Unbound;
        }

        // look for this DLL in the list
        dll = g_LoadedDlls.FindByName(dllName);
    }
    else
    {
        // we are freeing the first DLL in the list
        dll = g_LoadedDlls.GetFirst();
    }

    if (dll == NULL)
    {
        // The DLL wasn't loaded
        err_logo(DLL_NOT_LOADED, NIL);
        return Unbound;
    }

    g_LoadedDlls.Remove(dll);
    return Unbound;
}

static
FARPROC
GetFunctionFromDll(
    HMODULE      Dll,
    const wxString& FunctionName
    )
{
    FARPROC theFunc = GetProcAddress(Dll, (const char*)(FunctionName));
    if (!theFunc) 
    {
        // try to get the name as an ordinal
        wchar_t * ptr = 0;
#ifdef _WIN64
		long long ordinal = wcstoll(FunctionName, &ptr, 0);
#else
        unsigned long ordinal = wcstoul(FunctionName, &ptr, 0);
#endif
        if (*ptr == '\0' && ordinal <= 0xFFFF)
        {
            // FunctionName was a number, so try to treat it as an ordinal
            theFunc = GetProcAddress(Dll, (const char *) ordinal);
        }
    }

    return theFunc;
}

static
NODE*
make_buffer(
    int  length
    )
{
	int fulllen = sizeof(unsigned short) + (length + 1) * sizeof(wchar_t);
	wchar_t * strhead = (wchar_t *)malloc(fulllen);

	if (strhead == NULL)
    {
        err_logo(OUT_OF_MEM, NIL);
        return Unbound;
    }
	memset(strhead, 0, fulllen);

    // set the "string pointer" to just after the header
	wchar_t * strptr = (wchar_t*)((char*)strhead + sizeof(unsigned short));

    // set the reference count to 1.
    unsigned short *header = (unsigned short *) strhead;
    setstrrefcnt(header, 1);

    NODE * strnode = newnode(VBAR_STRING);
    setstrlen(strnode, length);
    setstrptr(strnode, strptr);
    setstrhead(strnode, strhead);
    return strnode;
}

NODE *ldllcall(NODE *args)
{
    if (g_LoadedDlls.IsEmpty())
    {
        err_logo(DLL_NOT_LOADED, NIL);
        return Unbound;
    }

    // get function name and its parameters
    NODE * functionArgs = car(args);

    // must be a list that contains something
    if (!is_list(functionArgs) || (functionArgs == NIL))
    {
        err_logo(BAD_DATA_UNREC, functionArgs);
        return Unbound;
    }

    // count items in list and check that they are pairs
    int total_args = list_length(functionArgs);
    bool even_args = even_p(total_args);

    // we need pairs of inputs (type/value pairs) to continue
    if (!even_args)
    {
        err_logo(DLL_TYPE_DATA_NOT_PAIRED, NIL);
        return Unbound;
    }

    NODE * functionArg = functionArgs;

    // get the return type of the function
    CStringPrintedNode fkind(car(functionArg));
    functionArg = cdr(functionArg);

    // get the name of the function
    CStringPrintedNode fname(car(functionArg));
    functionArg = cdr(functionArg);


    // Determine which DLL the function belongs to
    // First, let's see if we're told which DLL this function belongs to
    FARPROC theFunc = NULL;

    NODE * dllNameArg = cdr(args);
    if (dllNameArg != NIL)
    {
        // an DLL name was given, so let's use that one
        CStringPrintedNode dllName(car(dllNameArg));

        CLoadedDll * dll = g_LoadedDlls.FindByName(dllName);
        if (dll == NULL)
        {
            // The requested DLL is not loaded.
            err_logo(DLL_NOT_LOADED, NIL);
            return Unbound;
        }

        theFunc = GetFunctionFromDll(dll->GetHandle(), fname);
    }
    else
    {
        // a DLL name was not given, which means we have to walk
        // the list of DLLs looking for one that contains this function.
        for (CLoadedDll * dll = g_LoadedDlls.GetFirst();
             dll != NULL;
             dll = g_LoadedDlls.GetNext(dll))
        {
            theFunc = GetFunctionFromDll(dll->GetHandle(), fname);
            if (theFunc != NULL)
            {
                // we found a DLL that contains this function
                break;
            }
        }
    }

    if (theFunc == NULL)
    {
        err_logo(DLL_FUNCTION_NOT_FOUND, NIL);
        return Unbound;
    }

	//TODO: FIXME
    const wchar_t returnType = ((const wxString&)fkind)[0];

    CAppendableList outParameters; // a list of "out" parameter lists to return

    // BUG: Both of these stacks, values and parameters, can be overflowed.
    // This should be fixed, but it's not a problem in practice because
    // any malformed call to DLLCALL can also corrupt memory and it's
    // unlikely that a user will exhaust either stack in proper usage.

    wchar_t *values[1024];   // strings we must free
    int nextValue = 0;
#ifdef _WIN64
    long long 
#else
	int
#endif
		parameters[1024]; // a stack of parsed parameters to pass to the function
    int nextParameter = 0;

    // fill queue with type/data pairs
    while (functionArg != NIL && stopping_flag != THROWING)
    {
        NODE * kindNode = car(functionArg);
        CStringPrintedNode kind(kindNode);
        functionArg = cdr(functionArg);

        NODE * valueNode = car(functionArg);
        CStringPrintedNode value(valueNode);
        functionArg = cdr(functionArg);
		const wxString k = kind;
		wchar_t ck = k.length() > 0 ? k[0] : L'\0';
		wchar_t dk = k.length() > 1 ? k[1] : L'\0';
        switch (ck)
        {
        case L'w':
        case L'W':
            parameters[nextParameter++] = (int) (_wtoi((const wxString&)value) & 0xFFFF);
            break;

        case L'l':
        case L'L':
            parameters[nextParameter++] = (int) _wtol((const wxString&)value);
            break;

        case L'f':
        case L'F':
            {
                // A double is 8 bytes, so we must push it
                // as two four-byte parameters.
                double number = _wtof((const wxString&)value);
                parameters[nextParameter++] = ((int*)(&number))[1];
                parameters[nextParameter++] = ((int*)(&number))[0];
                assert(sizeof(number) == 2 * sizeof(*parameters));
            }
            break;

        case L's':
        case L'S':
            values[nextValue] = _wcsdup((const wxString&)value);
            parameters[nextParameter++] = 
#ifdef _WIN64
			(long long)
#else
			(int)
#endif
			values[nextValue];
            nextValue++;
            break;

        case L'b':
        case L'B':
            {
                // This is a buffer type.
                // Unlike the other types which predate FMSLogo and are maintained
                // as only checking the first character for backward-compatibility,
                // we check the "B" type specifier for strict conformance.
                if (dk != L'\0')
                {
                    err_logo(BAD_DATA_UNREC, functionArgs);
                    break;
                }

                // The "value" of the buffer type is its size.
                // Unlike the other types, the buffer is not provided by
                // the caller as a value.  Doing so would violate the
                // immutability of strings, since the native function
                // would overwrite it.
                wchar_t * endPtr;
                long int size = wcstol((const wxString&)value, &endPtr, 10);
                if (size == LONG_MAX || size < 0 || *endPtr != L'\0')
                {
                    // value is a bad number for an allocation size
                    // (negative, too large, or not a number all).
                    err_logo(BAD_DATA_UNREC, functionArgs);
                    break;
                }
                if (INT_MAX < size)
                {
                    // Prevent integer overflow from making us think we
                    // allocated the correctly-sized buffer.
                    err_logo(OUT_OF_MEM, NIL);
                    break;
                }

                NODE * bufferNode = make_buffer(size);
                if (bufferNode == Unbound) 
                {
                    // The buffer could not be allocated.
                    break;
                }

                // Use the allocated buffer for the function parameter.
                parameters[nextParameter++] = 
#ifdef _WIN64
					(long long)
#else
					(int) 
#endif
					getstrptr(bufferNode);

                // After the call is complete, we return all of the buffers.
                outParameters.AppendElement(bufferNode);
            }
            break;

        case L'v':
        case L'V':
            // void type
            break;

        default:
            err_logo(DLL_INVALID_DATA_TYPE, NIL);
            break;
        }
    }

	wxString areturn;
    if (stopping_flag != THROWING)
    {
        // Now that we have all of the parameters, it's time to copy them
        // them from the "parameters" stack variable to the real stack.
		for (int i = 0; i < nextParameter; i++)
		{
			//TODO: fix me
			//pushl(parameters[i]);
			_do_push((void*)parameters[i]);
        }

        // IMPORTANT: From here until we call theFunc, there cannot be any
        // instructions that would change the stack pointer, such as calling
        // a function.

        switch (returnType)
        {
        case L'w':
        case L'W':
            {
                WORD w = (*(WORD(WINAPI *)()) theFunc)();
				areturn = wxString::Format(L"%d", w);
            }
            break;

		case L'l':
        case L'L':
            {
                DWORD dw = (*(DWORD(WINAPI *)()) theFunc)();
				areturn = wxString::Format(L"%ld", dw);
		}
            break;

        case L'f':
        case L'F':
            {
                double dw = (*(double (WINAPI *)()) theFunc)();
				areturn = wxString::Format(L"%f", dw);
            }
            break;

        case L's':
        case L'S':
            {
                LPWSTR lp = (*(LPWSTR(WINAPI *)()) theFunc)();

                // This should not be like this because lp[]
                // can be bigger than areturn[] but for now...
				areturn = lp;

                // free global string mem.
                GlobalFreePtr(lp);
            }
            break;

        case L'v':
        case L'V':
            // "void" return type
            (*(void (WINAPI *)()) theFunc)();
			//areturen = L"";
            break;

        default:
            err_logo(DLL_INVALID_OUTPUT_TYPE, NIL);
            break;
        }
    }

    // Free any string parameters which we allocated.
    while (nextValue != 0) 
    {
        nextValue--;
        free(values[nextValue]);
    }

    if (stopping_flag == THROWING)
    {
        gcref(outParameters.GetList());
        return Unbound;
    }

    NODE * val;
    if (areturn.length()>0)
    {
        // something was returned
        NODE * targ = make_strnode(areturn);
        val = parser(targ, false);

        // Append the "out" parameters to the end of the parsed list.
        if (outParameters.GetList() != NIL)
        {
            NODE * listTail = val;
            while (cdr(listTail) != NIL)
            {
                listTail = cdr(listTail);
            }
            setcdr(listTail, outParameters.GetList());
        }
    }
    else
    {
        // The function returned void.
        // If there were "out" parameters, return those.
        // Otherwise return nothing.
        if (outParameters.GetList() != NIL)
        {
            val = outParameters.GetList();
        }
        else
        {
            val = Unbound;
        }
    }

    return val;
}

void uninitialize_dlls()
{
    // Unload all DLLs which have not been unloaded by the Logo programmer.
    while (!g_LoadedDlls.IsEmpty())
    {
        CLoadedDll * leakedDll = g_LoadedDlls.GetFirst();
        TraceOutput(L"DLLFREE not called on \"%s\".\n", leakedDll->GetFileName());

        g_LoadedDlls.Remove(leakedDll);
    }
}
