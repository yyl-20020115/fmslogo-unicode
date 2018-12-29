# =========================================================================
# NOTE: this makefile is a stop-gap solution for me (david costanzo) to
# to build the FMSlogo on my machines.  I don't expect this to work for
# anyone else without modification.
# =========================================================================

EXEEXT =

TOOLKIT = GTK

WXCONFIG = wx-config

ifeq "$(DEBUG)" "1"
LDFLAGS  = $(shell $(WXCONFIG) --debug=yes --libs base,core,stc,richtext,html)
TOOLCHAIN_FULLNAME = /usr/local/include/wx-$(shell $(WXCONFIG) --release)
else
LDFLAGS  = $(shell $(WXCONFIG) --debug=no --libs base,core,stc,richtext,html)
TOOLCHAIN_FULLNAME = /usr/local/include/wx-$(shell $(WXCONFIG) --release)
endif

CPPFLAGS += $(shell $(WXCONFIG) --cppflags) -DWX_PURE -DUNIX
CXXFLAGS += -pthread -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-unused-but-set-variable
LDFLAGS  += -pthread

SCINTILLA_INCLUDES = scintilla/include

ifeq "$(DEBUG)" "1"
CPPFLAGS += -D__WXDEBUG__ -DMEM_DEBUG -DDEBUG
CXXFLAGS += -O0 -g -ggdb
else
CPPFLAGS += -DNDEBUG -DwxDEBUG_LEVEL=0
CXXFLAGS += -O2

ifneq "$(PROFILE)"  "1"
ifneq "$(COVERAGE)" "1"
# On retail builds, strip symbols unless we need them for profiling.
# CONSIDER: using a separate variable for offical releases to strip. 
LDFLAGS  += -s
endif
endif

endif

# Setup the build for profiling, if requested.
ifeq "$(PROFILE)" "1"
CFLAGS   += -pg -g
CXXFLAGS += -pg -g
LDFLAGS  += -pg -g
endif

# Setup the build for code coverage, if requested.
ifeq "$(COVERAGE)" "1"
CFLAGS   += --coverage
CXXFLAGS += --coverage
LDFLAGS  += --coverage
endif

CXXFLAGS += -Wall -fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_WXWIDGETS

LIBS = -lm
LIBDIRNAME = /usr/local/lib
CXX = g++

CXXFLAGS  += -D__WX$(TOOLKIT)__ $(CPPFLAGS)

WX_OBJECTS = 3dsolid.o \
aboutfmslogo.o \
aboutmultiplesclerosis.o \
activearea.o \
appendablelist.o \
argumentutils.o \
avltree.o \
CConstStringTextReadonlyStream.o \
CFileTextStream.o \
CLocalizedStringProvider.o \
CMbcsFileTextStream.o \
commanderbutton.o \
commander.o \
commanderhistory.o \
commanderinput.o \
commandertogglebutton.o \
coms.o \
CStringTextStream.o \
CTextStream.o \
CUnicodeFileTextStream.o \
cursor.o \
debugheap.o \
devwind.o \
dynamicbuffer.o \
editproceduredialog.o \
eraseproceduredialog.o \
error.o \
eval.o \
files.o \
fileswnd.o \
FMSLogo.o \
fontutils.o \
gbmbmp.o \
gbm.o \
gbmgif.o \
gbmhelp.o \
gbmsize.o \
graphics.o \
graphwin.o \
guiutils.o \
helputils.o \
ibmterm.o \
init.o \
intern.o \
lists.o \
localizednode.o \
localizedstrings.o \
logodata.o \
logodialogboxes.o \
logoeventqueue.o \
logomath.o \
mainframe.o \
mainwind.o \
mem.o \
messagebox.o \
minieditor.o \
minieditortextctrl.o \
paren.o \
parse.o \
print.o \
questionbox.o \
savebeforeexitdialog.o \
selectbox.o \
selectproceduredialog.o \
selectstartupinstruction.o \
setactivearea.o \
setcolor.o \
setpensize.o \
sort.o \
startup.o \
statusdialog.o \
stringprintednode.o \
term.o \
threed.o \
unix.o \
utils.o \
vector.o \
workspaceeditor.o \
wrksp.o \
wxpurestubs.o \

#logocodectrl.o \
#mmwind.o \
#netwind.o \
#screen.o \

OBJECTS = $(WX_OBJECTS)

### Targets: ###

default : fmslogo 


	
fmslogo: $(OBJECTS)
	$(CXX) -o fmslogo $(LDFLAGS) -L$(LIBDIRNAME) $(LIBS) $(EXTRALIBS) $(OBJECTS)

clean: 
	$(RM) -rf $(OBJECTS)


screensaver :
	$(MAKE) -C ../screensaver

#test :
#	perl check-logo-code.pl Logolib/*
#	perl check-logo-code.pl Examples/3d/*.LGO
#	perl check-logo-code.pl Examples/Misc/*.LGO
#	perl check-logo-code.pl Examples/Multimed/*.LGO
#	perl check-logo-code.pl Examples/Network/*.LGO
#	perl check-logo-code.pl Examples/Pascal/*.LGO
#	perl check-logo-code.pl Examples/UCBLogo/*.LGO
#	perl check-logo-code.pl Examples/Windows/*.LGO


.PHONY: all clean default test
