# =========================================================================
# NOTE: Linux (Ubuntu) Makefile of the KDE4 Makefile Project
# =========================================================================

TOOLKIT = GTK

WXCONFIG = wx-config

PREFIX =  $(shell $(WXCONFIG) --prefix)

LDFLAGS  =  $(shell $(WXCONFIG)  --libs base,core,stc,richtext,html,xml,net)


CPPFLAGS += $(shell $(WXCONFIG) --cppflags) -DWX_PURE -DLINUX
CXXFLAGS += -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-unused-but-set-variable


SCINTILLA_INCLUDES = scintilla/include
TOOLCHAIN_FULLNAME = $(shell $(WXCONFIG) --release)


CPPFLAGS += -DDEBUG -D__LINUX_ALSA__
CXXFLAGS += -O0 -g -ggdb


INCLUDES =. ${SCINTILLA_INCLUDES} $(PREFIX)/include/wx-$(TOOLCHAIN_FULLNAME)/ $(PREFIX)/lib/wx/include/gtk3-unicode-static-$(TOOLCHAIN_FULLNAME)/

CPPFLAGS += $(addprefix -I, $(INCLUDES))
CXXFLAGS += -Wall 
#-fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_WXWIDGETS

LIBDIRNAME = /usr/local/lib/ 
LIBDIRNAME_EXT =/usr/lib
CXX = g++

CXXFLAGS  += -D__WX$(TOOLKIT)__ $(CPPFLAGS)
LDFLAGS += -g
LDFLAGS += -lcharset -liconv -lasound -lrtaudio 
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
CUTF16FileTextStream.o \
CUTF8FileTextStream.o \
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
mmwind.o \
messagebox.o \
minieditor.o \
minieditortextctrl.o \
netwind.o \
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
sound.o \
wav_parser.o \
CCheckQueueEvent.o \
RtAudio.o \
CNodePrinter.o \
CUThread.o \
CSoundPlayerThread.o \
CEncodingConverter.o \
CEncodingFileTextStream.o \
scintilla/LexFmsLogo.o



LS_OBJECTS = localizedstrings-de-ucs2le.o \
localizedstrings-en-ucs2le.o \
localizedstrings-es-ucs2le.o \
localizedstrings-fr-ucs2le.o \
localizedstrings-gr-ucs2le.o \
localizedstrings-hr-ucs2le.o \
localizedstrings-it-ucs2le.o \
localizedstrings-pl-ucs2le.o \
localizedstrings-pt-ucs2le.o \
localizedstrings-ru-ucs2le.o \
localizedstrings-zh-cn-ucs2le.o
#localizedstrings-ps-ucs2le.o #ps is not real language


OBJECTS = $(WX_OBJECTS) 
OBJECTS += $(LS_OBJECTS)

### Targets: ###

default : fmslogo 

	
fmslogo: $(OBJECTS)
	$(CXX) -o fmslogo-unicode $(OBJECTS) -L$(LIBDIRNAME) -L$(LIBDIRNAME_EXT) $(LDFLAGS)

scintilla/LexFmsLogo.o : scintilla/LexFmsLogo.cxx
	$(CXX) -c $(CXXFLAGS) scintilla/LexFmsLogo.cxx  -o scintilla/LexFmsLogo.o 

localizedstrings-de-ucs2le.o: localizedstrings-de-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-de-ucs2le.h localizedstrings-de-ucs2le.o

localizedstrings-en-ucs2le.o: localizedstrings-en-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-en-ucs2le.h localizedstrings-en-ucs2le.o

localizedstrings-es-ucs2le.o: localizedstrings-es-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-es-ucs2le.h localizedstrings-es-ucs2le.o

localizedstrings-fr-ucs2le.o: localizedstrings-fr-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-fr-ucs2le.h localizedstrings-fr-ucs2le.o

localizedstrings-gr-ucs2le.o: localizedstrings-gr-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-gr-ucs2le.h localizedstrings-gr-ucs2le.o

localizedstrings-hr-ucs2le.o: localizedstrings-hr-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-hr-ucs2le.h localizedstrings-hr-ucs2le.o

localizedstrings-it-ucs2le.o: localizedstrings-it-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-it-ucs2le.h localizedstrings-it-ucs2le.o

localizedstrings-pl-ucs2le.o: localizedstrings-pl-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-pl-ucs2le.h localizedstrings-pl-ucs2le.o

localizedstrings-pt-ucs2le.o: localizedstrings-pt-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-pt-ucs2le.h localizedstrings-pt-ucs2le.o

localizedstrings-ru-ucs2le.o: localizedstrings-ru-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-ru-ucs2le.h localizedstrings-ru-ucs2le.o

localizedstrings-zh-cn-ucs2le.o: localizedstrings-zh-cn-ucs2le.h
	objcopy -I binary -O elf64-x86-64 -B i386 localizedstrings-zh-cn-ucs2le.h localizedstrings-zh-cn-ucs2le.o

	
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
