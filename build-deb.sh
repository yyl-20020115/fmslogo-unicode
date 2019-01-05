#!/bin/bash
#
#This shell script is used to generate deb package for fmslogo

mkdir -p ~/fmslogo-deb
mkdir -p ~/fmslogo-deb/usr
mkdir -p ~/fmslogo-deb/usr/bin
mkdir -p ~/fmslogo-deb/usr/bin/fmslogo
cp fmslogo ~/fmslogo-deb/usr/bin/fmslogo
cp startup.logoscript ~/fmslogo-deb/usr/bin/fmslogo
cp -r logolib ~/fmslogo-deb/usr/bin/fmslogo
cp -r Examples ~/fmslogo-deb/usr/bin/fmslogo
cp README.TXT ~/fmslogo-deb/usr/bin/fmslogo
cp LICENSE.TXT ~/fmslogo-deb/usr/bin/fmslogo
cp turtle.bmp ~/fmslogo-deb/usr/bin/fmslogo
cp manual/logohelp.chm ~/fmslogo-deb/usr/bin/fmslogo

mkdir -p ~/fmslogo-deb/usr/share
mkdir -p ~/fmslogo-deb/usr/share/icons
cp fmslogo.png ~/fmslogo-deb/usr/share/icons
mkdir -p ~/fmslogo-deb/usr/share/applications
cp fmslogo.desktop ~/fmslogo-deb/usr/share/applications
mkdir -p ~/fmslogo-deb/DEBIAN
cp control ~/fmslogo-deb/DEBIAN
dpkg -b ~/fmslogo-deb ./fmslogo_7.3.0.0_i386.deb

