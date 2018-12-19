//////////////////////////////////////////////////////////////////////////////
// testfunction.cpp
// 
// This file contains some functions that get exported from a DLL that can
// be used to test various aspects of DLLCALL.
//
#include <windows.h>
#include <stdio.h>


// A simple function that takes a double as a parameter and returns a double.
//
// It can be called like
//   DLLCALL [F MakeSquare@8 F 2.2 ]
//
extern "C"
__declspec(dllexport)
double
WINAPI
MakeSquare(double Number)
{
    return Number * Number;
}


// A simple function that takes a double as a parameter and returns a string.
//
// It can be called like
//   DLLCALL [S FormatFloat@8 F 2.2 ]
//
extern "C"
__declspec(dllexport)
char *
WINAPI
FormatFloat(double Number)
{
    // Allocate a buffer to hold the return string
    size_t bufferSize     = 64;
    char * formattedFloat = static_cast<char*>(GlobalAlloc(GPTR, bufferSize));

    // Format the number to the string
    snprintf(formattedFloat, bufferSize, "%f", Number);

    // Return the string
    return formattedFloat;
}

// A simple function that takes a WORD as a parameter and returns a string.
//
// It can be called like
//   DLLCALL [S FormatWord@4 W 123 ]
//
extern "C"
__declspec(dllexport)
PSTR
WINAPI
FormatWord(WORD Number)
{
    // Allocate a buffer to hold the return string
    size_t bufferSize     = 64;
    char * formattedWord = static_cast<char*>(GlobalAlloc(GPTR, bufferSize));

    // Format the number to the string
    snprintf(formattedWord, bufferSize, "%d", Number);

    // Return the string
    return formattedWord;
}


// A simple function that applies the "rot13" algorithm to a string.
//
// It can be called like
//   DLLCALL [S UpperCase@4 S MyString ]
//
extern "C"
__declspec(dllexport)
PSTR
WINAPI
Rot13(PCSTR String)
{
    // Allocate a buffer to hold the return string
    size_t stringLength = strlen(String);
    char * rot13String  = static_cast<char*>(GlobalAlloc(GPTR, stringLength + 1));

    // Copy and translate the string.
    for (int i = 0; i <= stringLength; i++)
    {
        int ch = String[i];
        if ('A' <= ch && ch <= 'Z')
        {
            ch += 13;
            if ('Z' < ch)
            {
                ch -= 26;
            }
        }
        else if ('a' <= ch && ch <= 'z')
        {
            ch += 13;
            if ('z' < ch)
            {
                ch -= 26;
            }
        }

        rot13String[i] = ch;
    }
    rot13String[stringLength] = '\0';

    // Return the string
    return rot13String;
}

// A function that takes no parameters and always returns 123
//
// It can be called like
//   DLLCALL [S Word123@0 ]
//
extern "C"
__declspec(dllexport)
WORD
WINAPI
Word123()
{
    return 123;
}


// A function that accepts two buffer parameters and a character to
// use to start filling each of the buffers.  The first buffer is filled
// with starting with fillChar, then fillChar+1, etc.  The second buffer
// is filled incrementing fillChar by two.
//
// The function returns to number of bytes written.
//
// It can be called like
//   DLLCALL [L FillBuffers@20 B 10 L 10 W 65 L 20 B 20 ]
//
extern "C"
__declspec(dllexport)
DWORD
WINAPI
FillBuffers(
    PBYTE Buffer1,
    DWORD Buffer1Size,
    CHAR  FillChar,
    DWORD Buffer2Size,
    PBYTE Buffer2
    )
{
    for (int i = 0; i < Buffer1Size; i++)
    {
        Buffer1[i] = (FillChar + i) & 0xFF;
    }

    for (int i = 0; i < Buffer2Size; i++)
    {
        Buffer2[i] = (FillChar + i*2) & 0xFF;
    }

    return Buffer1Size + Buffer2Size;
}


// A function that accepts a buffer parameter returns VOID.
// The buffer must be 10 bytes.
//
// The function is designed to test that out parameters can
// be returned from void functions.
//
// It can be called like
//   DLLCALL [V FillBuffer@4 B 10 ]
//
extern "C"
__declspec(dllexport)
void
WINAPI
FillBuffer(
    PBYTE Buffer
    )
{
    // Fill 10 bytes of the buffer
    memcpy(Buffer, "0123456789", 10);
}

// A function that accepts a buffer parameter returns a PSTR.
// The buffer must be 10 bytes.
//
// The function is designed to test appending the out parameter
// to an arbitrary list.
//
// It can be called like
//   DLLCALL [S EchoString@8 B 10 S ABCDEF ]
//
extern "C"
__declspec(dllexport)
PSTR
WINAPI
EchoString(
    PCSTR String,
    PBYTE Buffer
    )
{
    // Fill 10 bytes of the buffer
    memcpy(Buffer, "0123456789", 10);

    // Allocate a buffer to hold the echo'd string
    size_t stringLength = strlen(String);
    char * echoedString = static_cast<char*>(GlobalAlloc(GPTR, stringLength + 1));

    // Copy the string.
    strcpy(echoedString, String);

    // Return the copy of String.
    return echoedString;
}
