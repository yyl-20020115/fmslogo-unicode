This directory contains the source code for the FMSLogo manual.

The manual is built using an open soure framework called DocBook
that was created and is maintained by O'Rielly Associates, a
respected publisher of technology books.  DocBook is powerful
and flexible enough for them, so it should be sufficient for
FMSLogo.

= OVERVIEW =
DocBook is an XML schema and a collection of XSLT transformations
which convert the XML source into various formats (HTML, PDF, and HHP).

There is only one logical XML document, which is split into multiple
physical files for convenience.  These files are concatenated into
a single document before being transformed into other formats.

The XML document starts with "logohelp.xml".  The other files are
loaded as "entities".  For example, this

    <!ENTITY graphics SYSTEM "graphics.xml">

Will load the contents of graphics.xml into an entity named "graphics".
Then, whenever "&graphics;" appears in the XML, it is replaced with
the contents of graphics.xml.

= CONVENTIONS =
The manual uses some conventions for consistency, which are enforced
by the Perl script "check-manual.pl".  In short:

* All commands are in upper case.
* Logo is referred to as &PRODUCTNAME; when talking about something
  specific to FMSLogo.
* Logo is referred to as &GENERICNAME; when talking about the language,
  in general.
* Every command has a table of contents entry (so that it can be found
  using F1 in FMSLogo.

= BUILDING =
To convert the manual to HTML, you need the following command-line tools:

* make     (the tool that runs the other tools, according to Makefile)
* docbook  (the DocBook schema and basic transformation tools)
* xsltproc (the XML processor that applies the transforms)

Once the tools are in the correct place, open a command prompt,
change to this directory, and run "make website".

If you cannot move the tools, then you can change the file
paths to the tools that are within the Makefile.  The only path
that isn't in Makefile is the path to docbook.xsl, which is in
logohelp.xml.

The following tools are required for doing additional tasks.
* fop (to build the PDF)
* perl (to do quick tests and part of building the .CHM)
* Microsoft HTML Help Workshop (to build the .CHM)

= ERRORS =

There are three main classes of errors that you'll see when building.

1) The tools cannot be found.  In this case, you must download
   the tools and put them in the correct location, or modify
   Makefile and logohelp.xml to your versions.

2) Badly-formed XML.  Once the XML has been concatenated into a
   single document it must be well-formed according to the rules
   of XML.  All tags must be closed, all special characters must
   be escaped, etc.

3) Invalid XML.  The XML must be valid relative to the DocBook
   schema.  Some elements are only permitted under other elements.
   Some attributes are only permitted on some elements. See

   http://www.oasis-open.org/docbook/documentation/reference/html/docbook.html

= EXTENDING THE MANUAL =

If you wish to add new content, such as a new file translation,
create a new file ending in XML.

For example, suppose you are documenting a new Logo command named
MYCOMMAND.  Start by creating a new file named

    command-mycommand.xml

Next, add an <!ENTITY> processer directive that will load your
file into a character entity to logohelp.xml.

    <!ENTITY mycommand SYSTEM "command-mycommand.xml">

Next, insert the character entity for the documentation where
it belongs within some other file that's already part of the manual.
Do this by adding

    &command-mycommand;

Finally, write the documentation according to DocBook schema,
starting with a <section> tag.

At this point, you should be able to run "make website", debug
the errors, then wait to see how the manual looks.

= SUPPORT =

For assistence, open a ticket on SourceForge and be patient.
You must be logged in with a SourceForge account to do this.

   https://sourceforge.net/p/fmslogo/support-requests/

