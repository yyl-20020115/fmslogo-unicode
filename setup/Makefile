MAKENSIS='C:\Program Files\NSIS\makensis.exe'

include ../lcids.mk
include ../version.mk

EXECUTABLES    = $(addprefix ../src/fmslogo-,       $(addsuffix .exe,        $(LCIDS)))
STARTUPFILES   = $(addprefix ../src/startup-,       $(addsuffix .logoscript, $(LCIDS)))
HELPFILES      = $(addprefix ../manual/logohelp-,   $(addsuffix .chm,        $(LCIDS)))
RESOURCEFILES  = ../src/License.txt ../src/fmslogo.ico fmslogo-header-icon.bmp 

NSISDEFINES =
NSISDEFINES += /DFMSLOGO_MAJOR_VERSION=$(FMSLOGO_MAJOR_VERSION)
NSISDEFINES += /DFMSLOGO_MINOR_VERSION=$(FMSLOGO_MINOR_VERSION)
NSISDEFINES += /DFMSLOGO_MICRO_VERSION=$(FMSLOGO_MICRO_VERSION)
NSISDEFINES += /DFMSLOGO_VERSION=$(FMSLOGO_VERSION)

default : fmslogo.exe

all : fmslogo.exe

# Build the installer
fmslogo.exe : fmslogo.nsi ../version.mk $(EXECUTABLES) $(STARTUPFILES) $(HELPFILES) $(RESOURCEFILES)
	$(MAKENSIS) $(NSISDEFINES) /DFMSLOGO_OUTPUT_FILE=$@ /DFMSLOGO_EXE_PATH=src $<

clean :
	$(RM) fmslogo.exe
	$(RM) *.bak
	$(RM) *~
