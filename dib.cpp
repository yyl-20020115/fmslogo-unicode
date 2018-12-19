/*
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/

//-----------------------------------------------------------------------------
// DIB.C
//
// This is a collection of useful DIB manipulation/information gathering
// functions.  Many functions are supplied simply to take the burden
// of taking into account whether a DIB is a Win30 style or OS/2 style
// DIB away from the application.
//
// The functions in this module assume that the DIB pointers or handles
// passed to them point to a block of memory in one of two formats:
//
//       a) BITMAPINFOHEADER + color table + DIB bits (3.0 style DIB)
//       b) BITMAPCOREHEADER + color table + DIB bits (OS/2 PM style)
//
// The SDK Reference, Volume 2 describes these data structures.
//
// A number of functions in this module were lifted from SHOWDIB,
// and modified to handle OS/2 DIBs.
//
// The functions in this module could be streamlined (made faster and
// smaller) by removing the OS/2 DIB specific code, and assuming all
// DIBs passed to it are Win30 style DIBs.  The DIB file reading code
// would need to be modified to always convert DIBs to Win30 style
// DIBs.  The only reason this isn't done in DIBView is because DIBView
// was written to test display and printer drivers (which are supposed
// to support OS/2 DIBs wherever they support Win30 style DIBs).  SHOWDIB
// is a great example of how to go about doing this.
//-----------------------------------------------------------------------------

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "dib.h"
   #include "messagebox.h"
   #include "screenwindow.h"
   #include "localizedstrings.h"
   #include "debugheap.h"
#endif

extern LPSTR FindDIBBits(LPSTR lpbi);
extern WORD DIBNumColors(LPSTR lpbi);
extern WORD PaletteSize(LPSTR lpbi);
extern DWORD DIBHeight(LPSTR lpDIB);
extern DWORD DIBWidth(LPSTR lpDIB);
extern HBITMAP DIBToBitmap(HANDLE hDIB, HPALETTE hPal);
extern void InitBitmapInfoHeader(LPBITMAPINFOHEADER lpBmInfoHdr, DWORD dwWidth, DWORD dwHeight, int nBPP);
extern HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal);

//---------------------------------------------------------------------
//
// Function:   FindDIBBits
//
// Purpose:    Given a pointer to a DIB, returns a pointer to the
//             DIB's bitmap bits.
//
// Parms:      lpbi == pointer to DIB header (either BITMAPINFOHEADER
//                       or BITMAPCOREHEADER)
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

LPSTR FindDIBBits(LPSTR lpbi)
{
    return (lpbi + *(LPDWORD) lpbi + PaletteSize(lpbi));
}

//---------------------------------------------------------------------
//
// Function:   DIBNumColors
//
// Purpose:    Given a pointer to a DIB, returns a number of colors in
//             the DIB's color table.
//
// Parms:      lpbi == pointer to DIB header (either BITMAPINFOHEADER
//                       or BITMAPCOREHEADER)
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

WORD DIBNumColors(LPSTR lpbi)
{
    WORD wBitCount;

    // If this is a Windows style DIB, the number of colors in the
    // color table can be less than the number of bits per pixel
    // allows for (i.e. lpbi->biClrUsed can be set to some value).
    // If this is the case, return the appropriate value.

    if (IS_WIN30_DIB(lpbi))
    {
        DWORD dwClrUsed;

        dwClrUsed = ((LPBITMAPINFOHEADER) lpbi)->biClrUsed;

        if (dwClrUsed) return (WORD) dwClrUsed;
    }


    // Calculate the number of colors in the color table based on
    //  the number of bits per pixel for the DIB.

    if (IS_WIN30_DIB(lpbi))
    {
        wBitCount = ((LPBITMAPINFOHEADER) lpbi)->biBitCount;
    }
    else 
    {
        wBitCount = ((LPBITMAPCOREHEADER) lpbi)->bcBitCount;
    }

    switch (wBitCount)
    {
    case 1: return 2;

    case 4: return 16;

    case 8: return 256;

    default: return 0;
    }
}

//---------------------------------------------------------------------
//
// Function:   PaletteSize
//
// Purpose:    Given a pointer to a DIB, returns number of bytes
//             in the DIB's color table.
//
// Parms:      lpbi == pointer to DIB header (either BITMAPINFOHEADER
//                       or BITMAPCOREHEADER)
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

WORD PaletteSize(LPSTR lpbi)
{
    if (IS_WIN30_DIB(lpbi))
    {
        return (DIBNumColors(lpbi) * sizeof(RGBQUAD));
    }
    else 
    {
        return (DIBNumColors(lpbi) * sizeof(RGBTRIPLE));
    }
}

//---------------------------------------------------------------------
//
// Function:   DIBHeight
//
// Purpose:    Given a pointer to a DIB, returns its height.  Note
//             that it returns a DWORD (since a Win30 DIB can have
//             a DWORD in its height field), but under Win30, the
//             high order word isn't used!
//
// Parms:      lpDIB == pointer to DIB header (either BITMAPINFOHEADER
//                       or BITMAPCOREHEADER)
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

DWORD DIBHeight(LPSTR lpDIB)
{
    LPBITMAPINFOHEADER lpbmi;
    LPBITMAPCOREHEADER lpbmc;

    lpbmi = (LPBITMAPINFOHEADER) lpDIB;
    lpbmc = (LPBITMAPCOREHEADER) lpDIB;

    if (lpbmi->biSize == sizeof(BITMAPINFOHEADER)) 
    {
        return lpbmi->biHeight;
    }
    else 
    {
        return (DWORD) lpbmc->bcHeight;
    }
}

//---------------------------------------------------------------------
//
// Function:   DIBWidth
//
// Purpose:    Given a pointer to a DIB, returns its width.  Note
//             that it returns a DWORD (since a Win30 DIB can have
//             a DWORD in its width field), but under Win30, the
//             high order word isn't used!
//
// Parms:      lpDIB == pointer to DIB header (either BITMAPINFOHEADER
//                       or BITMAPCOREHEADER)
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

DWORD DIBWidth(LPSTR lpDIB)
{
    LPBITMAPINFOHEADER lpbmi;
    LPBITMAPCOREHEADER lpbmc;

    lpbmi = (LPBITMAPINFOHEADER) lpDIB;
    lpbmc = (LPBITMAPCOREHEADER) lpDIB;

    if (lpbmi->biSize == sizeof(BITMAPINFOHEADER)) 
    {
        return lpbmi->biWidth;
    }
    else 
    {
        return (DWORD) lpbmc->bcWidth;
    }
}

//---------------------------------------------------------------------
//
// Function:   DIBToBitmap
//
// Purpose:    Given a handle to global memory with a DIB spec in it,
//             and a palette, returns a device dependent bitmap.  The
//             The DDB will be rendered with the specified palette.
//
// Parms:      hDIB == HANDLE to global memory containing a DIB spec
//                     (either BITMAPINFOHEADER or BITMAPCOREHEADER)
//             hPal == Palette to render the DDB with.  If it's NULL,
//                     use the default palette.
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

HBITMAP DIBToBitmap(HANDLE hDIB, HPALETTE hPal)
{
    if (!hDIB)
    {
        return NULL;
    }

    LPSTR lpDIBHdr = (char *) GlobalLock(hDIB);
    LPSTR lpDIBBits = FindDIBBits(lpDIBHdr);
    HDC hDC = GetDC(GetScreenWindow());
    if (!hDC)
    {
        GlobalUnlock(hDIB);
        return NULL;
    }

    HPALETTE hOldPal = NULL;
    if (hPal)
    {
        hOldPal = SelectPalette(hDC, hPal, FALSE);
    }

    RealizePalette(hDC);

    HBITMAP hBitmap = CreateDIBitmap(
        hDC,
        (LPBITMAPINFOHEADER) lpDIBHdr,
        CBM_INIT,
        lpDIBBits,
        (LPBITMAPINFO) lpDIBHdr,
        DIB_RGB_COLORS);

    if (!hBitmap)
    {
        ShowErrorMessageAndStop(LOCALIZED_ERROR_OUTOFMEMORY);
    }
    // DIBError (ERR_CREATEDDB);

    if (hOldPal) 
    {
        SelectPalette(hDC, hOldPal, FALSE);
    }

    ReleaseDC(GetScreenWindow(), hDC);
    GlobalUnlock(hDIB);

    return hBitmap;
}




//---------------------------------------------------------------------
//
// Function:   InitBitmapInfoHeader
//
// Purpose:    Does a "standard" initialization of a BITMAPINFOHEADER,
//             given the Width, Height, and Bits per Pixel for the
//             DIB.
//
//             By standard, I mean that all the relevant fields are set
//             to the specified values.  biSizeImage is computed, the
//             biCompression field is set to "no compression," and all
//             other fields are 0.
//
//             Note that DIBs only allow BitsPixel values of 1, 4, 8, or
//             24.  This routine makes sure that one of these values is
//             used (whichever is most appropriate for the specified
//             nBPP).
//
// Parms:      lpBmInfoHdr == Far pointer to a BITMAPINFOHEADER structure
//                            to be filled in.
//             dwWidth     == Width of DIB (not in Win 3.0 & 3.1, high
//                            word MUST be 0).
//             dwHeight    == Height of DIB (not in Win 3.0 & 3.1, high
//                            word MUST be 0).
//             nBPP        == Bits per Pixel for the DIB.
//
// History:   Date      Reason
//            11/07/91  Created
//
//---------------------------------------------------------------------

void InitBitmapInfoHeader(LPBITMAPINFOHEADER lpBmInfoHdr, DWORD dwWidth, DWORD dwHeight, int nBPP)
{
    memset(lpBmInfoHdr, 0, sizeof(BITMAPINFOHEADER));

    lpBmInfoHdr->biSize = sizeof(BITMAPINFOHEADER);
    lpBmInfoHdr->biWidth = dwWidth;
    lpBmInfoHdr->biHeight = dwHeight;
    lpBmInfoHdr->biPlanes = 1;

    if (nBPP <= 1) nBPP = 1;
    else if (nBPP <= 4) nBPP = 4;
    else if (nBPP <= 8) nBPP = 8;
    else nBPP = 24;

    lpBmInfoHdr->biBitCount = nBPP;
    lpBmInfoHdr->biSizeImage = WIDTHBYTES(dwWidth * nBPP) * dwHeight;
}

//---------------------------------------------------------------------
//
// Function:   BitmapToDIB
//
// Purpose:    Given a device dependent bitmap and a palette, returns
//             a handle to global memory with a DIB spec in it.  The
//             DIB is rendered using the colors of the palette passed in.
//
//             Stolen almost verbatim from ShowDIB.
//
// Parms:      hBitmap == Handle to device dependent bitmap compatible
//                        with default screen display device.
//             hPal    == Palette to render the DDB with.  If it's NULL,
//                        use the default palette.
//
// History:   Date      Reason
//             6/01/91  Created
//
//---------------------------------------------------------------------

HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal)
{
    BITMAP Bitmap;
    BITMAPINFOHEADER bmInfoHdr;
    LPBITMAPINFOHEADER lpbmInfoHdr;
    LPSTR lpBits;
    HDC hMemDC;
    HANDLE hDIB;
    HPALETTE hOldPal = NULL;

    // Do some setup -- make sure the Bitmap passed in is valid,
    // get info on the bitmap (like its height, width, etc.),
    // then setup a BITMAPINFOHEADER.

    if (!hBitmap) 
    {
        return NULL;
    }

    if (!GetObject(hBitmap, sizeof(Bitmap), (LPSTR) & Bitmap)) 
    {
        return NULL;
    }

    InitBitmapInfoHeader(&bmInfoHdr, Bitmap.bmWidth, Bitmap.bmHeight, Bitmap.bmPlanes * Bitmap.bmBitsPixel);

    // Now allocate memory for the DIB.  Then, set the BITMAPINFOHEADER
    // into this memory, and find out where the bitmap bits go.

    hDIB = GlobalAlloc(
        GHND, 
        sizeof(BITMAPINFOHEADER) + PaletteSize((LPSTR) & bmInfoHdr) + bmInfoHdr.biSizeImage);
    if (!hDIB) 
    {
        return NULL;
    }

    lpbmInfoHdr = (LPBITMAPINFOHEADER) GlobalLock(hDIB);
    *lpbmInfoHdr = bmInfoHdr;
    lpBits = FindDIBBits((LPSTR) lpbmInfoHdr);

    // Now, we need a DC to hold our bitmap.  If the app passed us
    //  a palette, it should be selected into the DC.

    hMemDC = GetDC(NULL);

    if (hPal)
    {
        hOldPal = SelectPalette(hMemDC, hPal, FALSE);
        RealizePalette(hMemDC);
    }

    // We're finally ready to get the DIB.  Call the driver and let
    //  it party on our bitmap.  It will fill in the color table,
    //  and bitmap bits of our global memory block.

    if (!GetDIBits(hMemDC, hBitmap, 0, Bitmap.bmHeight, lpBits, (LPBITMAPINFO) lpbmInfoHdr, DIB_RGB_COLORS))
    {
        GlobalUnlock(hDIB);
        GlobalFree(hDIB);
        hDIB = NULL;
    }
    else 
    {
        GlobalUnlock(hDIB);
    }

   // Finally, clean up and return.

   if (hOldPal)
   {
       SelectPalette(hMemDC, hOldPal, FALSE);
   }

   ReleaseDC(NULL, hMemDC);

   return hDIB;
}
