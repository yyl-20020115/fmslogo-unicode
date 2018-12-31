# =========================================================================
# NOTE: this makefile is a stop-gap solution for me (david costanzo) to
# to build the FMSlogo on my machines.  I don't expect this to work for
# anyone else without modification.
# =========================================================================

TOOLKIT = GTK

WXCONFIG = wx-config

PREFIX =  $(shell $(WXCONFIG) --prefix)

LDFLAGS  =  $(shell $(WXCONFIG) --debug=yes --libs base,core,stc,richtext,html,xml)


CPPFLAGS += $(shell $(WXCONFIG) --cppflags) -DWX_PURE -DUNIX
CXXFLAGS += -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-unused-but-set-variable


SCINTILLA_INCLUDES = scintilla/include
TOOLCHAIN_FULLNAME = $(shell $(WXCONFIG) --release)


CPPFLAGS += -DDEBUG
CXXFLAGS += -O0 -g -ggdb


INCLUDES =. $(PREFIX)/include/wx-$(TOOLCHAIN_FULLNAME)/ $(PREFIX)/lib/wx/include/gtk3-unicode-static-$(TOOLCHAIN_FULLNAME)/

CPPFLAGS += $(addprefix -I, $(INCLUDES))
CXXFLAGS += -Wall -fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_WXWIDGETS

LIBDIRNAME = /usr/local/lib/
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
logocodectrl.o \
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
screen.o \
term.o \
threed.o \
unix.o \
utils.o \
vector.o \
workspaceeditor.o \
wrksp.o \
wxpurestubs.o \


#mmwind.o \
#netwind.o \
#screen.o \
#debugheap.o \

OBJECTS = $(WX_OBJECTS)

### Targets: ###

default : fmslogo 


	
fmslogo: $(OBJECTS)
	$(CXX) -o fmslogo $(OBJECTS) -L$(LIBDIRNAME) $(LDFLAGS)

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
