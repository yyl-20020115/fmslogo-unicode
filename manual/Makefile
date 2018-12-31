include ../version.mk
include ../lcids.mk

TEMPORARY_FILES = translations.xml locale.xml
HHP_STYLESHEET  = htmlhelp.xsl 
HTML_STYLESHEET = html.xsl
FO_STYLESHEET   = fo.xsl
ROOTFILE        = logohelp.xml
SOURCEFILES     = $(filter-out $(TEMPORARY_FILES), $(wildcard *.xml)) logoversion.xml

XMLLINT  = xmllint
XSLTPROC = xsltproc
HHC      = 'C:\Program Files\HTML Help Workshop\hhc.exe'
FOP      = 'E:\fop-1.1\fop.bat'

# prevent the hhp files from being automatically deleted
.SECONDARY : $(addprefix htmlhelp-, $(addsuffix .hhp, $(LCIDS)))

MANUALS = $(addprefix logohelp-, $(addsuffix .chm, $(LCIDS)))

# by default, build the English CHM file
logohelp.chm : logohelp-1033.chm
	cp $^ $@

index.html : $(SOURCEFILES) $(HTML_STYLESHEET)
	cp translations-1033.xml translations.xml
	echo -n $* > locale.xml
	$(XMLLINT) --valid --noout --nonet $(ROOTFILE)
	$(XSLTPROC) --novalid --nonet $(HTML_STYLESHEET) $(ROOTFILE)

logohelp.fo : $(SOURCEFILES) $(FO_STYLESHEET)
	cp translations-1033.xml translations.xml
	echo -n $* > locale.xml
	$(XMLLINT) --valid --noout --nonet $(ROOTFILE)
	$(XSLTPROC) --novalid --nonet --output $@ $(FO_STYLESHEET) $(ROOTFILE)

logohelp-%.chm : htmlhelp-%.hhp logohelp.css
	perl -W clean-html.pl
	-$(HHC) htmlhelp-$*.hhp

# German CHM has been hand-translated so we shouldn't overwrite it
logohelp-1031.chm : ;

# Portuguese CHM has been hand-translated so we shouldn't overwrite it
logohelp-2070.chm : ;

# Greek builds require a different character set
logohelp-1032.chm : htmlhelp-1032.hhp logohelp.css
	perl -W clean-html.pl windows-1253
	-$(HHC) htmlhelp-1032.hhp

# Russian builds require a different character set
logohelp-1049.chm : htmlhelp-1049.hhp logohelp.css
	perl -W clean-html.pl windows-1251
	-$(HHC) htmlhelp-1049.hhp

# Croatian builds require a different character set
logohelp-1050.chm : htmlhelp-1050.hhp logohelp.css
	perl -W clean-html.pl windows-1250
	-$(HHC) htmlhelp-1050.hhp

htmlhelp-%.hhp : translations-%.xml $(SOURCEFILES) $(HHP_STYLESHEET)
	cp translations-$*.xml translations.xml
	echo -n $* > locale.xml
	$(XMLLINT) --valid --noout --nonet $(ROOTFILE)
	$(XSLTPROC) --novalid --nonet --param htmlhelp.chm \"'logohelp-$*.chm'\" $(HHP_STYLESHEET) $(ROOTFILE)
	mv htmlhelp.hhp htmlhelp-$*.hhp

# The "all" target builds all translations of the .chm
all : $(MANUALS)

logohelp.ps : $(SOURCEFILES)
	docbook2ps $(ROOTFILE)

logohelp.pdf : logohelp.fo
	$(FOP) -q -fo $< -pdf $@

logohelp.rtf : $(SOURCEFILES)
	docbook2rtf $(ROOTFILE)

website : index.html media/*.png
	-mkdir www
	cp $(shell /usr/bin/find -maxdepth 1 -name '*.html') www
	cp logohelp.css www
	-mkdir www/media
	cp media/*.png www/media

# Experimental Spanish manual
logohelp-1034-experimental.chm : $(wildcard 1034/*.xml) logoversion.xml translations-1034.xml $(HHP_STYLESHEET)
	$(XMLLINT) --valid --noout --nonet 1034/$(ROOTFILE)
#	$(XSLTPROC) --novalid --nonet $(HTML_STYLESHEET) 1034/$(ROOTFILE)
	$(XSLTPROC) --novalid --nonet --param htmlhelp.chm \"'logohelp-1034-experimental.chm'\" $(HHP_STYLESHEET) 1034/$(ROOTFILE)
	mv htmlhelp.hhp htmlhelp-1034.hhp
	-$(HHC) htmlhelp-1034.hhp

spanish : logohelp-1034-experimental.chm ;

# Generate an XML file that contains the version
# We use the UNIX version of echo to make sure there is no newline
logoversion.xml : ../version.mk
	echo -n $(FMSLOGO_VERSION) > $@

clean :
	$(RM) logohelp.rtf
	$(RM) logohelp.pdf
	$(RM) logohelp.dvi
	$(RM) logohelp.ps
	$(RM) logohelp.fo
	$(RM) logoversion.xml
	$(RM) $(wildcard *.html)
	$(RM) $(wildcard *.htm)
	$(RM) $(wildcard *.hhp)
	$(RM) $(wildcard *.hhc)
	$(RM) $(wildcard *.hhk)
	$(RM) $(wildcard *.chw)
	$(RM) $(filter-out logohelp-1031.chm logohelp-2070.chm,$(wildcard *.chm))
	$(RM) $(wildcard *~)
	$(RM) $(wildcard *.bak)
	$(RM) $(wildcard www/*.html)
	$(RM) $(wildcard www/*.css)
	$(RM) $(TEMPORARY_FILES)

test :
	perl -W check-manual.pl
