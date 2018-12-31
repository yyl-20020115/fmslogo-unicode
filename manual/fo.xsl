<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/fo/docbook.xsl"/>

  <xsl:param name="fop1.extensions"            select="1"/>

  <xsl:param name="generate.section.toc.level" select="3"/>

  <xsl:param name="generate.toc">
book      toc,title,figure,table,example,equation
chapter   toc
preface   toc
section   toc
  </xsl:param>

</xsl:stylesheet>
