/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "mainwind.h"

   #include <algorithm>

   #include <wx/gdicmn.h>
   #include <wx/dc.h>
   #ifdef __WXMSW__
     #include <wx/msw/dc.h> // for wxDCTemp
   #endif

   #include "const.h"
   #include "activearea.h"
   #include "screenwindow.h"
   #include "startup.h"
   #include "graphwin.h"
   #include "cursor.h"
   #include "FMSLogo.h"
//   #include "debugheap.h"

   #ifdef max // MS compilers #define max in windows.h
      #undef max
   #endif

   #ifdef min // MS compilers #define min in windows.h
      #undef min
   #endif
#endif

// Writes the contents of the screen window that is
// within the ACTIVEAREA window to the screen to the given
// file stream as a Windows Bitmap.
//
// File - a FILE* that was opened for binary writing.
// MaxBitmapBitDepth - the bitcount to use for the bitmap.
//    Must be 1, 4, 8, 16, 24, or 32.
//
// Returns SUCCESS if the bitmap was successfully written.
// Returns an error code, otherwise.
static
ERR_TYPES WriteDIB(FILE* File, int MaxBitmapBitDepth)
{
    ERR_TYPES status = SUCCESS;

#ifdef WX_PURE
    status = FILE_ERROR;
#else
    // grab a DC
    HDC dc = GetMemoryDeviceContext();

    // Determine the bit depth of the screen.
    WORD bitmapBitDepth = GetDeviceCaps(dc, BITSPIXEL);
    bitmapBitDepth *= GetDeviceCaps(dc, PLANES);

    // If we were asked to save a bitmap with a very low bit-depth
    // (one that uses a palette), then honor the request.
    if (MaxBitmapBitDepth < bitmapBitDepth)
    {
        if ((MaxBitmapBitDepth == 1) || (MaxBitmapBitDepth == 4) || (MaxBitmapBitDepth == 8))
        {
            bitmapBitDepth = MaxBitmapBitDepth;
        }
    }

    // If we're saving a true-color bitmap, use 24bpp.
    if (bitmapBitDepth == 16 || bitmapBitDepth == 32)
    {
        bitmapBitDepth = 24;
    }

    size_t size;
    if (bitmapBitDepth <= 8)
    {
        // Allocate space for a palette of 2^bitmapBitDepth colors
        size = sizeof(BITMAPINFOHEADER) + ((
#ifdef _WIN64
			1LL
#else
			1
#endif
			<< bitmapBitDepth) * sizeof(RGBQUAD));
    }
    else
    {
        size = sizeof(BITMAPINFOHEADER);
    }

    char * bitmapInfoBuffer = new char[size];
    BITMAPINFO * bitmapInfo = reinterpret_cast<BITMAPINFO *>(bitmapInfoBuffer);

    const int bitmapWidth  = g_PrinterAreaXHigh - g_PrinterAreaXLow;
    const int bitmapHeight = g_PrinterAreaYHigh - g_PrinterAreaYLow;

    bitmapInfo->bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
    bitmapInfo->bmiHeader.biWidth         = bitmapWidth;
    bitmapInfo->bmiHeader.biHeight        = bitmapHeight;
    bitmapInfo->bmiHeader.biPlanes        = 1;
    bitmapInfo->bmiHeader.biBitCount      = bitmapBitDepth;
    bitmapInfo->bmiHeader.biCompression   = BI_RGB;
    bitmapInfo->bmiHeader.biXPelsPerMeter = 0;
    bitmapInfo->bmiHeader.biYPelsPerMeter = 0;
    bitmapInfo->bmiHeader.biClrUsed       = 0;
    bitmapInfo->bmiHeader.biClrImportant  = 0;

    const int rowBits = bitmapInfo->bmiHeader.biWidth * bitmapInfo->bmiHeader.biBitCount;
    const int lineBytes = ((rowBits + 31) / 32) * 4; // pad to 32-bit alignment
    bitmapInfo->bmiHeader.biSizeImage = lineBytes * bitmapInfo->bmiHeader.biHeight;

    // If the bitmap is too large, then the call to GetDIBits() below will fail.
    // To account for this, we repeatedly call it for a smaller region until we
    // have extracted the entire bitmap.
    const size_t TARGET_BUFFER_SIZE = 1024 * 1024;
    size_t dibBufferSize;
    size_t areaBitmapHeight;
    HBITMAP bitmapToSave;
    if (8 < bitmapBitDepth && TARGET_BUFFER_SIZE < bitmapInfo->bmiHeader.biSizeImage)
    {
        // Get enough lines so that we reach our target buffer size.
        // Always round up, so that we won't ever end up getting zero
        // bytes in each iteration.
        areaBitmapHeight = (TARGET_BUFFER_SIZE + lineBytes - 1) / lineBytes;
        dibBufferSize    = lineBytes * areaBitmapHeight;

        // GetDiBits() fails if we try to get the bitmap data in a piecemiel
        // fashion, so we must BLT the parts we want to a separate bitmap
        // and then call GetDiBits() on that.
        bitmapToSave = CreateCompatibleBitmap(
            dc,
            bitmapWidth,
            areaBitmapHeight);

    }
    else
    {
        // Put the entire bitmap into a single buffer.
        areaBitmapHeight = bitmapInfo->bmiHeader.biHeight;
        dibBufferSize    = bitmapInfo->bmiHeader.biSizeImage;

        if (IsActiveAreaOneToOneWithScreen())
        {
            // As an optimization, we can extract the bitmap data directly from
            // the memory bitmap without any BLTs.
            bitmapToSave = MemoryBitMap;
        }
        else
        {
            // The active area has a different size than the screen,
            // so we must BLT the area we want to a bitmap of the desired
            // size that matches the memory bitmap's format.
            bitmapToSave = CreateCompatibleBitmap(
                dc,
                bitmapWidth,
                areaBitmapHeight);
        }
    }
    if (bitmapToSave == NULL)
    {
        status = OUT_OF_MEM;
    }
    else
    {
        // Allocate space for the raw DIB data
        void * dibBuffer = malloc(dibBufferSize);
        if (dibBuffer == NULL)
        {
            status = OUT_OF_MEM;
        }
        else
        {
            // build file header
            BITMAPFILEHEADER bitmapFileHeader;
            bitmapFileHeader.bfType = 19778;
            bitmapFileHeader.bfSize = sizeof(bitmapFileHeader) + size + bitmapInfo->bmiHeader.biSizeImage;
            bitmapFileHeader.bfReserved1 = 0;
            bitmapFileHeader.bfReserved2 = 0;
            bitmapFileHeader.bfOffBits = size + sizeof(BITMAPFILEHEADER);

            // Write out the file header.
            fwrite(&bitmapFileHeader, sizeof bitmapFileHeader, 1, File);

            if (bitmapToSave == MemoryBitMap)
            {
                // Convert the device-dependent bitmap to raw DIB in dibBuffer.
                int rval = GetDIBits(
                    dc,
                    bitmapToSave,
                    0,
                    bitmapHeight,
                    dibBuffer,
                    bitmapInfo,
                    DIB_RGB_COLORS);
                if (rval != bitmapHeight)
                {
                    status = IMAGE_GENERAL;
                }

                // Write out the bitmap header (and optional palette)
                fwrite(bitmapInfo, sizeof(char), size, File);

                // write out raw DIB data to file
                fwrite(dibBuffer, sizeof(char), dibBufferSize, File);
            }
            else
            {
                // Write out the bitmap header.  For large bitmaps, we change the
                // header below, so we want to write it out while it still reflects
                // the overall bitmap.
                fwrite(bitmapInfo, sizeof(bitmapInfo->bmiHeader), 1, File);

                // Select the in-memory image of the picture.
                HBITMAP savedMemoryBitmap = (HBITMAP) SelectObject(dc, MemoryBitMap);

                // Select the correctly-size bitmap.
                HDC areaMemoryDC = CreateCompatibleDC(dc);
                SelectObject(areaMemoryDC, bitmapToSave);

                // Read the bitmap in chunks of areaBitmapHeight scanlines
                // so that GetDIBits() doesn't fail.
                for (int linesWritten = 0;
                     linesWritten < bitmapHeight;
                     linesWritten += areaBitmapHeight)
                {
                    // Figure out how many lines we should read, being
                    // careful to not read past the end of the bitmap.
                    int linesToGet;
                    if (bitmapHeight < linesWritten + (int)areaBitmapHeight)
                    {
                        linesToGet = bitmapHeight - linesWritten;
                    }
                    else
                    {
                        linesToGet = areaBitmapHeight;
                    }

                    // Copy the correct portion from memory to the temporary bitmap.
                    // Because the bits in a bitmap are drawn bottom-up, we request
                    // the bottom chunks first and then move up chunk by chunk.
                    BOOL isOk = BitBlt(
                        areaMemoryDC,
                        0,
                        0,
                        bitmapWidth,
                        linesToGet,
                        dc,
                        xoffset + g_PrinterAreaXLow,
                        yoffset - g_PrinterAreaYLow - linesWritten - linesToGet,
                        SRCCOPY);
                    if (!isOk)
                    {
                        status = IMAGE_GENERAL;
                        break;
                    }

                    bitmapInfo->bmiHeader.biHeight    = linesToGet;
                    bitmapInfo->bmiHeader.biSizeImage = lineBytes * linesToGet;
                    
                    // Convert the device-dependent bitmap to raw DIB in dibBuffer.
                    int rval = GetDIBits(
                        areaMemoryDC,
                        bitmapToSave,
                        0,
                        linesToGet,
                        dibBuffer,
                        bitmapInfo,
                        DIB_RGB_COLORS);
                    if (rval != linesToGet)
                    {
                        status = IMAGE_GENERAL;
                        break;
                    }

                    // Write out the palette for paletted bitmaps.
                    // We always write out the entire bitmap in one iteration for paletted
                    // bitmaps, so there's no risk of writing the palette more than once.
                    if (bitmapBitDepth <= 8)
                    {
                        fwrite(&bitmapInfo->bmiColors, sizeof(char), size - sizeof(bitmapInfo->bmiHeader), File);
                    }

                    // write out raw DIB data to file
                    fwrite(dibBuffer, sizeof(char), linesToGet * lineBytes, File);
                }

                // Release the device context that we created
                DeleteDC(areaMemoryDC);

                // Restore the original bitmap
                SelectObject(dc, savedMemoryBitmap);
            }

            if (bitmapToSave != MemoryBitMap && bitmapToSave != NULL)
            {
                // Cleanup the bitmap, if we created it.
                DeleteObject(bitmapToSave);
            }

            // restore some of the resources
            free(dibBuffer);
        }
    }

    delete [] bitmapInfoBuffer;
#endif // WX_PURE

    return status;
}

ERR_TYPES DumpBitmapFile(const wxString& Filename, int MaxBitCount)
{
    // open and check if ok
    FILE* file = 0;
#ifdef _WINDOWS
    file =_wfopen(Filename, L"wb");
#else
    file = fopen(Filename,"wb");
#endif
    if (file == NULL)
    {
        return IMAGE_BMP_OPEN_FAILED;
    }

    // Load hour-glass cursor.
    lsetcursorwait(NIL);

    // do it and if error then let user know 
    ERR_TYPES status = WriteDIB(file, MaxBitCount);

    // Restore the arrow cursor
    lsetcursorarrow(NIL);
    
    int rval = fclose(file);
    if (rval != 0)
    {
        status = IMAGE_BMP_WRITE_FAILED;
    }

    if (status != SUCCESS)
    {
        // The bitmap was not written out correctly.
        // Remove the file that we created, instead
        // of leaving around a corrupt file.
        remove(wxString(Filename));
    }

    return status;
}

#ifndef WX_PURE

// Attempt to open a Windows 3.0 device independent bitmap
static
bool
OpenDIB(
    FILE         * File,
    unsigned int & dwPixelWidth,
    unsigned int & dwPixelHeight
    )
{
    // get header 
    rewind(File);

    BITMAPFILEHEADER BitmapFileHeader;
    fread(&BitmapFileHeader, sizeof(char), sizeof(BitmapFileHeader), File);

    // bfOffbits should be equal to BitmapInfoHeader
    BITMAPINFO * ReadBitmapInfo = (BITMAPINFO *) new char[BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader)];
    fread(ReadBitmapInfo, sizeof(char), BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader), File);

    // save some typing 
    DWORD NewPixelWidth  = ReadBitmapInfo->bmiHeader.biWidth;
    DWORD NewPixelHeight = ReadBitmapInfo->bmiHeader.biHeight;

    if (dwPixelWidth)
    {
        // do what the spec says 
        if (ReadBitmapInfo->bmiHeader.biClrUsed == 0)
        {
            ReadBitmapInfo->bmiHeader.biClrUsed = 1 << ReadBitmapInfo->bmiHeader.biBitCount;
        }

        // compute image size if not set
        if (ReadBitmapInfo->bmiHeader.biSizeImage == 0)
        {
            /* only allow bitcount equal to display capability */
            WORD ReadbitCount = ReadBitmapInfo->bmiHeader.biBitCount;

            long longWidth = (((NewPixelWidth * ReadbitCount) + 31) / 32) * 4;

            ReadBitmapInfo->bmiHeader.biSizeImage = longWidth * NewPixelHeight;
        }

        // pack and allocate
        unsigned char * bitsPtr = new unsigned char[ReadBitmapInfo->bmiHeader.biSizeImage];
        memset(bitsPtr, 0x00, ReadBitmapInfo->bmiHeader.biSizeImage);

        // read the file into the bitmap
        fread(bitsPtr, sizeof(char), ReadBitmapInfo->bmiHeader.biSizeImage, File);

        // Create DC comaptible with screen 
        HDC screen   = GetScreenDeviceContext();
        HDC memoryDC = GetMemoryDeviceContext();

        HDC DCHandle = CreateCompatibleDC(screen);

        // now create the bitmap with the bits just loaded
        HBITMAP NewBitmapHandle = CreateDIBitmap(
            screen,
            &ReadBitmapInfo->bmiHeader,
            CBM_INIT,
            bitsPtr,
            ReadBitmapInfo,
            0);

        // now dump the bits 
        delete [] bitsPtr;
      
        // now that things are clean we can check if we are ok 
        if (!NewBitmapHandle)
        {
            return false;
        }

        // We've now made a bonefide bitmap. 
        // But we want to copy it into the existing backing store.
        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(DCHandle, NewBitmapHandle);

        /* if either dimension is more than half then put in corner */
        if (((int)NewPixelWidth > (BitMapWidth / 2)) || ((int)NewPixelHeight > (BitMapHeight / 2)))
        {
            BitBlt(
                memoryDC,
                0,
                0,
                NewPixelWidth,
                NewPixelHeight,
                DCHandle,
                0,
                0,
                SRCCOPY);
        }
        else
        {
            /* else put at turtle */
            wxPoint dest;

            if (current_mode == perspectivemode)
            {
                VECTOR from3d;

                from3d.x = g_SelectedTurtle->Position.x / WorldWidth;
                from3d.y = g_SelectedTurtle->Position.y / WorldHeight;
                from3d.z = g_SelectedTurtle->Position.z / WorldDepth;

                if (!ThreeD.TransformPoint(from3d, dest))
                {
                    return true;
                }
            }
            else
            {
                dest.x = g_round(g_SelectedTurtle->Position.x);
                dest.y = g_round(g_SelectedTurtle->Position.y);
            }

            BitBlt(
                memoryDC,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - NewPixelHeight,
                NewPixelWidth,
                NewPixelHeight, 
                DCHandle, 
                0, 
                0, 
                SRCCOPY);
        }

        // return resources
        SelectObject(DCHandle, oldBitmap2);
        DeleteDC(DCHandle);

        DeleteObject(NewBitmapHandle);
    }

    delete [] ReadBitmapInfo;

    dwPixelWidth  = NewPixelWidth;
    dwPixelHeight = NewPixelHeight;
    return true;
}

#endif // WX_PURE

ERR_TYPES
LoadBitmapFile(
    const wxString& Filename,
    unsigned int & dwPixelWidth,
    unsigned int & dwPixelHeight
    )
{
    // Test if Filename is a Windows 3.0 DIB bitmap and if so read it

    // open then check if open 
    FILE* file = 0;
#ifdef _WINDOWS
    file =_wfopen(Filename, L"rb");
#else
    file = fopen(Filename,"rb");
#endif
    if (file == NULL)
    {
        return IMAGE_BMP_OPEN_FAILED;
    }

    // check if valid bitmap
    ERR_TYPES status = SUCCESS;
    fseek(file, 14, SEEK_SET);

    long TestWin30Bitmap = 0;
    fread(&TestWin30Bitmap, sizeof(char), sizeof(TestWin30Bitmap), file);
    if (TestWin30Bitmap == 40)
    {
        // Load hour-glass cursor.
        lsetcursorwait(NIL);

#ifdef WX_PURE
        status = FILE_ERROR;
#else
        // if loaded ok then invalidate to display 
        if (OpenDIB(file, dwPixelWidth, dwPixelHeight))
        {
            ::InvalidateRect(GetScreenWindow(), NULL, FALSE);
        }
        else
        {
            status = IMAGE_BMP_CREATE_FAILED;
        }
#endif // WX_PURE

        // Restore the arrow cursor
        lsetcursorarrow(NIL);
    }
    else
    {
        // not a bitmap
        status = IMAGE_BMP_INVALID;
    }
    fclose(file);

    return status;
}

void
PaintToScreen(
    wxDC     & PaintDeviceContext,
    wxRegion   UpdateRegion,
    int        ScrollX,
    int        ScrollY
    )
{
    // This is a compromise between speed and memory (as is most code).
    // All drawing is written to the backing store 1 to 1 even when zoomed.
    // When zoomed all drawing and painting is scaled to the display on the fly.
    // Painting can be a bit slow while zoomed. It also can be inaccurate when
    // mixing scaled painting and scaled drawing. Printing is never zoomed.
    // User can use Bitfit if he/she wants data scaled.

    // Use a back buffer if we are drawing sprite turtles
    // (turtles with rotating bitmaps).
    bool useBackBuffer = false;
    for (int j = 0; j <= g_MaxTurtle; j++)
    {
        if (g_Turtles[j].IsShown && g_Turtles[j].IsSprite)
        {
            useBackBuffer = true;
            break;
        }
    }

    wxDC * sourceDeviceContext;
    if (useBackBuffer)
    {
        // Allocate the back buffer (if needed)
        sourceDeviceContext = GetBackBufferDeviceContext();

        // Copy the portion of the memory image to the back buffer
        // that corresponds to the portion of the screen that is
        // being be painted.
        for (wxRegionIterator regionIterator(UpdateRegion);
             regionIterator;
             regionIterator++)
        {
            // regionIterator gives coordinates in terms of the client area.
            // We need to determine what rectangle in memoryBitmap corresponds
            // to this rectangle.
            FLONUM sourceRectLeft   = regionIterator.GetX();
            FLONUM sourceRectTop    = regionIterator.GetY();
            FLONUM sourceRectRight  = sourceRectLeft + regionIterator.GetWidth();
            FLONUM sourceRectBottom = sourceRectTop  + regionIterator.GetHeight();

            // Shift the rectangle based on the scroll position.
            sourceRectLeft   += ScrollX;
            sourceRectRight  += ScrollX;
            sourceRectTop    += ScrollY;
            sourceRectBottom += ScrollY;

            // If the screen is zoomed, then we must do some additional
            // calculation to determine what part of the source image
            // needs repainting.
            if (zoom_flag)
            {
                // Expand the source rectangle a little bit based zoom factor,
                // It doesn't hurt to copy a little more than necessary, but copying
                // less can result in jaggies.
                const FLONUM inflateIncrement = (the_zoom+0.5)*2.0;
                sourceRectLeft   -= inflateIncrement;
                sourceRectTop    -= inflateIncrement;
                sourceRectRight  += inflateIncrement;
                sourceRectBottom += inflateIncrement;

                // Second, scale based on the zoom factor.
                // We divide by the zoom factor to convert from screen coordinates
                // to turtle coordinates.  If we're zoomed in, the_zoom greater
                // than 1, so dividing by it will shrink the rectangle that
                // we're going to copy from.
                FLONUM scaledSourceRectLeft   = sourceRectLeft   / the_zoom;
                FLONUM scaledSourceRectTop    = sourceRectTop    / the_zoom;
                FLONUM scaledSourceRectRight  = sourceRectRight  / the_zoom;
                FLONUM scaledSourceRectBottom = sourceRectBottom / the_zoom;

                // Make sure that none of rectangle's borders are off-screen
                // after we inflated it.
                sourceRectLeft   = (int) (std::min(std::max(0.0, scaledSourceRectLeft),   (double)BitMapWidth));
                sourceRectTop    = (int) (std::min(std::max(0.0, scaledSourceRectTop),    (double)BitMapHeight));
                sourceRectRight  = (int) (std::min(std::max(0.0, scaledSourceRectRight),  (double)BitMapWidth));
                sourceRectBottom = (int) (std::min(std::max(0.0, scaledSourceRectBottom), (double)BitMapHeight));
            }

            sourceDeviceContext->Blit(
                sourceRectLeft,
                sourceRectTop,
                sourceRectRight - sourceRectLeft + 1,
                sourceRectBottom - sourceRectTop + 1,
                GetWxMemoryDeviceContext(),
                sourceRectLeft,
                sourceRectTop);
        }

        // draw the turtles on top of the image
        paste_all_turtles(*sourceDeviceContext, 1.0);
    }
    else
    {
        sourceDeviceContext = GetWxMemoryDeviceContext();
    }


    if (!zoom_flag)
    {
        // The image is not zoomed.  Do a normal BLIT

        // Determine the size of the viewable area
        const wxSize & screenSize = PaintDeviceContext.GetSize();

        for (wxRegionIterator regionIterator(UpdateRegion);
             regionIterator;
             regionIterator++)
        {
            // The x,y coordinates are on the client area
            wxCoord x      = regionIterator.GetX();
            wxCoord y      = regionIterator.GetY();
            wxCoord width  = regionIterator.GetWidth();
            wxCoord height = regionIterator.GetHeight();

            // Fill the part to the right of the screen.
            if (BitMapWidth <= x + width)
            {
                PaintDeviceContext.SetBrush(*wxWHITE_BRUSH);
                PaintDeviceContext.SetPen(*wxWHITE_PEN);

                PaintDeviceContext.DrawRectangle(
                    BitMapWidth,                         // x
                    0,                                   // y
                    screenSize.GetWidth() - BitMapWidth, // width
                    BitMapHeight);                       // height
            }

            // Fill the part below the screen.
            if (BitMapHeight <= y + height)
            {
                PaintDeviceContext.SetBrush(*wxWHITE_BRUSH);
                PaintDeviceContext.SetPen(*wxWHITE_PEN);

                PaintDeviceContext.DrawRectangle(
                    x,                                       // x
                    BitMapHeight,                            // y
                    BitMapWidth,                             // width
                    screenSize.GetHeight() - BitMapHeight);  // height
            }

            PaintDeviceContext.Blit(
                x + ScrollX,
                y + ScrollY,
                width,
                height,
                sourceDeviceContext,
                x + ScrollX,
                y + ScrollY);
        }
    }
#ifndef WX_PURE
    else
    {
        HDC paintHdc = static_cast<HDC>(PaintDeviceContext.GetHDC());

        // We are zoomed.  Compute scaling and then display.
        // Enable anti-aliasing
        SetStretchBltMode(paintHdc, HALFTONE);

        for (wxRegionIterator regionIterator(UpdateRegion);
             regionIterator;
             regionIterator++)
        {
            // regionIterator gives coordinates in terms of the
            // client area.
            // We need to determine what rectangle in memoryBitmap corresponds
            // to this rectangle.
            FLONUM sourceRectLeft   = regionIterator.GetX();
            FLONUM sourceRectTop    = regionIterator.GetY();
            FLONUM sourceRectRight  = sourceRectLeft + regionIterator.GetWidth();
            FLONUM sourceRectBottom = sourceRectTop  + regionIterator.GetHeight();

            // Shift the rectangle based on the scroll position.
            sourceRectLeft   += ScrollX;
            sourceRectRight  += ScrollX;
            sourceRectTop    += ScrollY;
            sourceRectBottom += ScrollY;

            // First, expand the source rectangle a little bit based zoom factor,
            // It doesn't hurt to copy a little more than necessary, but copying
            // less can result in jaggies.
            const FLONUM inflateIncrement = (the_zoom+0.5)*2.0;
            sourceRectLeft   -= inflateIncrement;
            sourceRectTop    -= inflateIncrement;
            sourceRectRight  += inflateIncrement;
            sourceRectBottom += inflateIncrement;

            // Second, scale based on the zoom factor.
            // We divide by the zoom factor to convert from screen coordinates
            // to turtle coordinates.  If we're zoomed in, the_zoom greater
            // than 1, so dividing by it will shrink the rectangle that
            // we're going to copy from.
            FLONUM scaledSourceRectLeft   = sourceRectLeft   / the_zoom;
            FLONUM scaledSourceRectTop    = sourceRectTop    / the_zoom;
            FLONUM scaledSourceRectRight  = sourceRectRight  / the_zoom;
            FLONUM scaledSourceRectBottom = sourceRectBottom / the_zoom;

            // fill the part to the right of the screen.
            if (BitMapWidth < scaledSourceRectRight)
            {
                PaintDeviceContext.SetBrush(*wxWHITE_BRUSH);
                PaintDeviceContext.SetPen(*wxWHITE_PEN);

                PaintDeviceContext.DrawRectangle(
                    BitMapWidth * the_zoom,
                    0,
                    sourceRectRight,
                    BitMapHeight * the_zoom);
            }

            // fill the part below the screen.
            if (BitMapHeight < scaledSourceRectBottom)
            {
                PaintDeviceContext.SetBrush(*wxWHITE_BRUSH);
                PaintDeviceContext.SetPen(*wxWHITE_PEN);

                PaintDeviceContext.DrawRectangle(
                    sourceRectLeft,                              // x
                    BitMapHeight * the_zoom,                     // y
                    sourceRectRight - sourceRectLeft,            // width
                    sourceRectBottom - BitMapHeight * the_zoom); // height
            }

            // Make sure that none of rectangle's borders are off-screen
            // after we inflated it.
            RECT sourceRect;
            sourceRect.left   = (int) (std::min(std::max(0.0, scaledSourceRectLeft),   (double)BitMapWidth));
            sourceRect.top    = (int) (std::min(std::max(0.0, scaledSourceRectTop),    (double)BitMapHeight));
            sourceRect.right  = (int) (std::min(std::max(0.0, scaledSourceRectRight),  (double)BitMapWidth));
            sourceRect.bottom = (int) (std::min(std::max(0.0, scaledSourceRectBottom), (double)BitMapHeight));

            // Now project the source rectangle back onto the screen.
            // This should be roughtly the same as the original regionIterator,
            // but may be larger due to rounding and may be smaller due to 
            // trucation of the off-world areas that still fit on the screen.
            RECT destRect;
            destRect.left   = sourceRect.left   * the_zoom;
            destRect.top    = sourceRect.top    * the_zoom;
            destRect.right  = sourceRect.right  * the_zoom;
            destRect.bottom = sourceRect.bottom * the_zoom;

            // Copy the corresponding part of the image to the screen
            StretchBlt(
                paintHdc,
                destRect.left,
                destRect.top,
                destRect.right  - destRect.left,
                destRect.bottom - destRect.top,
                static_cast<HDC>(sourceDeviceContext->GetHDC()),
                sourceRect.left,
                sourceRect.top,
                sourceRect.right  - sourceRect.left,
                sourceRect.bottom - sourceRect.top,
                SRCCOPY);
        }
    }
#endif // WX_PURE

    // draw the turtles on top of the image
    if (!useBackBuffer)
    {
        paste_all_turtles(PaintDeviceContext, the_zoom);
    }
}
