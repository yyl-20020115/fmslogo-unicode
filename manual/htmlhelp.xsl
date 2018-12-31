<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/htmlhelp/profile-htmlhelp.xsl"/>

  <xsl:param name="htmlhelp.only" select="0"/>

  <xsl:param name="htmlhelp.chm">logohelp.chm</xsl:param>

  <xsl:param name="htmlhelp.hhc.show.root"             select="0"/>
  <xsl:param name="htmlhelp.hhc.folders.instead.books" select="1"/>
  <xsl:param name="htmlhelp.hhc.binary"                select="1"/>

  <xsl:param name="html.stylesheet">logohelp.css</xsl:param>
  <xsl:param name="html.stylesheet.type">text/css</xsl:param>

  <xsl:param name="toc.section.depth"    select="5"/>
  <xsl:param name="chunk.section.depth"  select="5"/>
  <xsl:param name="chunk.first.sections" select="1"/>

  <!-- using short filenames removes 3% from the file size -->
  <xsl:param name="use.id.as.filename"   select="0"/>

  <xsl:param name="html.ext">.htm</xsl:param>

  <xsl:param name="generate.section.toc.level" select="3"/>

  <xsl:param name="generate.toc">
book      toc,title,figure,table,example,equation
chapter   toc
preface   toc
section   toc
  </xsl:param>

</xsl:stylesheet>
