<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/html/profile-chunk.xsl"/>

  <xsl:param name="toc.section.depth"    select="5"/>
  <xsl:param name="use.id.as.filename"   select="1"/>

  <xsl:param name="chunk.section.depth"  select="5"/>
  <xsl:param name="chunk.first.sections" select="1"/>

  <xsl:param name="generate.section.toc.level" select="3"/>

  <xsl:param name="html.stylesheet">logohelp.css</xsl:param>
  <xsl:param name="html.stylesheet.type">text/css</xsl:param>

  <xsl:param name="generate.toc">
book      toc,title,figure,table,example,equation
chapter   toc
preface   toc
section   toc
  </xsl:param>


  <xsl:template name="user.footer.navigation">

    <!-- this image required to be hosted on sourceforge -->
    <br/>
    <a href="http://sourceforge.net"><img 
        src="http://sflogo.sourceforge.net/sflogo.php?group_id=149686&amp;type=1" 
        width="88" 
        height="31"
        border="0" 
        alt="SourceForge.net Logo" /></a>

  </xsl:template>

</xsl:stylesheet>
