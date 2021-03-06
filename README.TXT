FMSLogo-Unicode for Windows / Linux / MacOSX

The original FMSLogo is based on ANSI/MBCS encoding.
And there are some serious issues when you code in local language, e.g. comments written in your own language
which is not ANSI encoding could not be preserved during save/load cycles.

The improvement seems minimal, however, it's huge work because you have to rewrite almost every
corner of the program to ensure the encoding is correct.

Besides, the port of the original Windows version to other platforms takes much effort,
and not fully functional yet.

Best Regars,
Yilin

Donation
BTC address: bc1qrlxjcefukp839lz0m80mfvheazzcvyu4sg4pvc

email:
yyl_20050115@hotmail.com

NOTICE on compiling on Windows:
Both fmslogo-unicode and wxWidgets can be compiled with toolset 
Visual Studio 2017 - Windows XP (v141_xp) -- for old machines such as xp
and the RuntimeLibrary mode should be set to MT (multi-threading) or MTd (for debug). 

NOT MD (multi-threading DLL) or MDd (for debug).

Put wxWidgets into D:\wxWidgets if you don't want to change settings of the project.
If any error about WEBKIT, just simply disable by 
#define wxUSE_WEBVIEW 0
before #if 
since it's faulty and we don't need web browser control at all.



----------------------------------------------------------------------
FMSLogo Version 7.4.0 for Microsoft Windows
----------------------------------------------------------------------

   I. Kit Description/Location
  II. New features/bugs fixed
 III. Standard features
  IV. Recommended usage
   V. Reporting bugs
  VI. Sources
 VII. Minimum System Requirements
VIII. Acknowledgements

I. Kit Description/Location (http://sourceforge.net/projects/fmslogo)

  fmslogo-7.4.0.exe - Installer for the Logo environment
  fmslogo-7.4.0.zip - ZIP of the Logo environment

II. New features/bugs fixed:

  Changed in 7.4.0
  o Fix Bug #521; The warning message about saving an empty workspace in the
    Spanish FMSLogo is now gramatically correct.
  o Fix Bug #520; In the Spanish FMSLogo, CASCADA now throws a Spanish "bad
    input" error message when given a negative number for the first input.
  o Fix Bug #519; In the Spanish FMSLogo, CASCADA no longer leaks variables.
  o Improvements to the Russian version of FMSLogo.
  o Improvements to the manual.

  For a complete history of changes across all versions of FMSLogo, see
  https://sourceforge.net/p/fmslogo/source/HEAD/tree/trunk/logo/src/CHANGELOG.TXT

III. Standard features

  * Supports TCP/IP WinSock Networking.
  * Supports Text in all available fonts and sizes.
  * Supports 1024 independent Turtles.
  * Supports Bitmapped Turtles.
  * Supports Cut, Paste and stretching bitmaps.
  * Supports Clipboard Text and Bitmaps.
  * Supports MIDI devices.
  * Supports Direct I/O for Controlling External hardware.
  * Supports Serial and Parallel Port communications.
  * Supports Zooming.
  * Supports Tail recursion (optimizes most recursive functions).
  * Supports User error handling.
  * Supports "Standard" Logo parsing.
  * Supports Floodfill.
  * Supports Save and restore images in .BMP format files.
  * Supports standard Windows Hypertext Help.
  * Supports standard Windows Printing.
  * Supports separate library and work area.
  * Supports construction of Windows Dialog Boxes.
  * Supports Event Driven programming (Mouse, Keyboard, Timer).
  * Supports MultiMedia Devices (.WAV sound files, CD-ROM control etc.)
  * Supports Event Timers allowing multiprocessing.
  * Supports 3D Perspective drawing (Wireframe and Solids).
  * Supports Animated GIF generation.

IV. Recommended usage

  * Ages 6 and up
     o Beginner     - Forward 100, Right 90
     o Intermediate - Explore mathematics, art, music, robotics, language, and more
     o Expert       - Create games

V. Reporting bugs

  Report bugs at http://sourceforge.net/projects/fmslogo/

VI. Sources

  Source code is available.  It's your legal right!  (See LICENSE.TXT).

  The FMSLogo sources were written/compiled with:

    MinGW w64 (for .EXE and screen saver)
    wxWidgets (GUI toolkit for .EXE and screen saver)
    DocBook, xsltproc, and Microsoft Help Workshop (for online help)
    Nullsoft Scriptable Install System (NSIS) (for the installer)

VII. Minimum System Requirements

   Windows XP with 512 MB of RAM.

VIII. Acknowledgements

  I wish to extend my sincerest thanks to everyone who has used, supported,
  criticized, praised, filed a bug on, or otherwise contributed to either
  FMSLogo or MSWLogo.

  Thanks to:
    Alexandre Soares
    Andreas Micheler
    Andrzej Pruszynski
    Andy Owen
    Anthony Barnett
    Ayurzanaeva Aryuna
    Bertrand Carette
    Bob Gorman
    Bruce Mardle
    Carl Bogardus
    Clem Rutter
    Daniel Ajoy
    Domagoj Kuna
    Francesco Simone Carta
    Hensley Bass
    Igor Baglaev
    Jan Grabe
    Jason Gervich
    Jim Foster
    Juan J. Paredes G.
    Kari Hoijarvi
    Lion Nik Kucev
    Lionel Laske
    Michael Malin
    Mike Sandy
    Narayanan Chitoor
    Pachleng
    Pavel Boytchev
    Peter De Wachter
    Ralf Kurth
    Relja Medic
    Serio Adamo
    Stefano Federici
    Stephan Vogel
    Tankhasaev Ayur
    Theodoros Chatzigiannakis

  Special thanks to:
    George Mills
    Brian Harvey
    Jim Muller
    Erich Neuwirth
    Yehuda Katz
