#!/bin/bash
#
#This shell script is used to generate deb package for fmslogo

mkdir -p ~/fmslogo-deb
mkdir -p ~/fmslogo-deb/usr
mkdir -p ~/fmslogo-deb/usr/bin
mkdir -p ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp fmslogo-unicode ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp fmslogo-unicode.ini ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp startup.logoscript ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp -r logolib ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp -r Examples ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp README.TXT ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp LICENSE.TXT ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp turtle.bmp ~/fmslogo-deb/usr/bin/fmslogo-unicode
cp manual/logohelp.chm ~/fmslogo-deb/usr/bin/fmslogo-unicode

mkdir -p ~/fmslogo-deb/usr/share
mkdir -p ~/fmslogo-deb/usr/share/icons
cp fmslogo.png ~/fmslogo-deb/usr/share/icons
mkdir -p ~/fmslogo-deb/usr/share/applications
cp fmslogo-unicode.desktop ~/fmslogo-deb/usr/share/applications
mkdir -p ~/fmslogo-deb/DEBIAN
cp control ~/fmslogo-deb/DEBIAN
dpkg -b ~/fmslogo-deb ./fmslogo-unicode_7.3.0.0_i386.deb

