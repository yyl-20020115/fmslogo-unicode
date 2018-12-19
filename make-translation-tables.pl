#!/usr/bin/perl -w
############################################################
# make-translation-tables.pl
#
# This script reads the source code and startup files for
# each language, LANG, and outputs the "LANG-to-English" and
# "English-to-LANG" tables that are built into the online
# documentation.
############################################################
use locale; # case-insensitive sorting
use IO::File;
use Encode qw(encode_utf8);
use strict;

# Procedures whose documentation is located in the documentation
# for some other function.
$main::EnglishAbbreviation{'bk'}    = 'back';
$main::EnglishAbbreviation{'bf'}    = 'butfirst';
$main::EnglishAbbreviation{'bfs'}   = 'butfirsts';
$main::EnglishAbbreviation{'bl'}    = 'butlast';
$main::EnglishAbbreviation{'cs'}    = 'clearscreen';
$main::EnglishAbbreviation{'ct'}    = 'cleartext';
$main::EnglishAbbreviation{'co'}    = 'continue';
$main::EnglishAbbreviation{'down'}  = 'downpitch';
$main::EnglishAbbreviation{'ed'}    = 'edit';
$main::EnglishAbbreviation{'er'}    = 'erase';
$main::EnglishAbbreviation{'erf'}   = 'erasefile';
$main::EnglishAbbreviation{'fd'}    = 'forward';
$main::EnglishAbbreviation{'fs'}    = 'fullscreen';
$main::EnglishAbbreviation{'ht'}    = 'hideturtle';
$main::EnglishAbbreviation{'iff'}   = 'iffalse';
$main::EnglishAbbreviation{'ift'}   = 'iftrue';
$main::EnglishAbbreviation{'lr'}    = 'leftroll';
$main::EnglishAbbreviation{'lt'}    = 'left';
$main::EnglishAbbreviation{'op'}    = 'output';
$main::EnglishAbbreviation{'pc'}    = 'pencolor';
$main::EnglishAbbreviation{'pd'}    = 'pendown';
$main::EnglishAbbreviation{'pe'}    = 'penerase';
$main::EnglishAbbreviation{'ppt'}   = 'penpaint';
$main::EnglishAbbreviation{'px'}    = 'penreverse';
$main::EnglishAbbreviation{'pu'}    = 'penup';
$main::EnglishAbbreviation{'pr'}    = 'print';
$main::EnglishAbbreviation{'rc'}    = 'readchar';
$main::EnglishAbbreviation{'rcs'}   = 'readchars';
$main::EnglishAbbreviation{'rl'}    = 'readlist';
$main::EnglishAbbreviation{'rr'}    = 'rightroll';
$main::EnglishAbbreviation{'rt'}    = 'right';
$main::EnglishAbbreviation{'rw'}    = 'readword';
$main::EnglishAbbreviation{'se'}    = 'sentence';
$main::EnglishAbbreviation{'setfc'} = 'setfloodcolor';
$main::EnglishAbbreviation{'seth'}  = 'setheading';
$main::EnglishAbbreviation{'setpc'} = 'setpencolor';
$main::EnglishAbbreviation{'setsc'} = 'setscreencolor';
$main::EnglishAbbreviation{'st'}    = 'showturtle';
$main::EnglishAbbreviation{'ss'}    = 'splitscreen';
$main::EnglishAbbreviation{'ts'}    = 'textscreen';
$main::EnglishAbbreviation{'up'}    = 'uppitch';

# Populates the colors and their RGB codes
%main::EnglishColorToRgbCode = ();

# Procedures which are undocumented cannot be put into
# the translation tables because they don't link to anything.
sub IsDocumentedEnglishProcedure($) {
  my $EnglishProcedureName = shift or die "not enough arguments";

  # filenames and abbreviations are lowercase
  $EnglishProcedureName = lc $EnglishProcedureName;

  # predicates are documented by their 'P' suffix.
  $EnglishProcedureName =~ s/\?$/p/;

  # The documentation files for goto/tag exist, but are omitted from the manual.
  return
    $main::EnglishAbbreviation{$EnglishProcedureName} ||
    (-f "../manual/command-$EnglishProcedureName.xml" && $EnglishProcedureName ne 'goto' && $EnglishProcedureName ne 'tag');
}

sub InitializeColorTable() {
  # Parse the colors from the source code.
  # This is an additional check to make sure that the documented color
  # matches the implemented color.
  my $colorSourceCode = new IO::File "graphics.cpp" or die $!;
  while (<$colorSourceCode>) {
    # The rows that we're looking for look something like
    # """
    # {"AliceBlue", LOCALIZED_COLOR_ALICEBLUE, 0x00FFF8F0},
    # """
    if (m/^\s+{"(\w+)",\s+LOCALIZED_COLOR_\w+,\s+0x00(\w\w)(\w\w)(\w\w)}.*$/) {
      $main::EnglishColorToRgbCode{$1} = uc "$4$3$2"; # convert 0x00GGBBRR -> RRGGBB
    }
  }
  $colorSourceCode->close();
}

# Returns a file path to an image that shows a color for an English color.
# dies if no such file exists.
sub GetColorFileRef($) {
  my $EnglishColorName = shift or die "not enough arguments";

  my $rgbCode = $main::EnglishColorToRgbCode{$EnglishColorName};

  # If we don't have an RGB code for this color, something has gone wrong.
  if (not $rgbCode) {
    die "Could not find RGB code for $EnglishColorName";
  }

  # If the image file does not exist, then something is wrong.
  if (not -e "../manual/media/rgb$rgbCode.png") {
    die "No RGB color image found for $EnglishColorName (../manual/media/rgb$rgbCode.png)";
  }

  return "media/rgb$rgbCode.png";
}

sub PrintShadowedProcedures($$$) {
  my $LocaleName         = shift or die "not enough arguments";
  my $English            = shift or die "not enough arguments";
  my $LocalizedToEnglish = shift or die "not enough arguments";

  # For each localized procedure name L of an English procedure name E check that
  # L is not the name of an English procedure other than E
  foreach my $localizedProcedureName (keys %{$LocalizedToEnglish}) {
    my $localizedProcedureNameInEnglish = $$LocalizedToEnglish{$localizedProcedureName};

    # Check this localization against all English procedure names.
    foreach my $otherEnglishProcedureName (values %{$English}) {

      # If the localization matches the English procedure name, then the
      # localization is redundant, but it's not shadowing.
      if ($localizedProcedureNameInEnglish eq $otherEnglishProcedureName) {
        next;
      }

      # If the localized name doesn't match this English procedure name, then
      # it's not shadowing this English procedure name.
      if ($otherEnglishProcedureName ne $localizedProcedureName) {
        next;
      }

      # It's okay if predicates that end in "?" shadow the "p"
      # form of the English predicate.
      # The Spanish translation does this because "p" has no meaning, so it
      # redefines some English library procedures predicates using their "?" names.
      if ($localizedProcedureName =~ m/^(.*)\?$/ and $localizedProcedureNameInEnglish eq "$1p") {
        next;
      }

      # The localized procedure name matches the name of some other English
      # procedure name, which makes that English procedure inaccessible
      # in this locale.
      print "WARNING: $LocaleName shadows the English procedure `$otherEnglishProcedureName' as a translations for `$localizedProcedureNameInEnglish'\n";
    }
  }
}

sub NormalizeEnglishProcedureName($) {
  my $EnglishProcedure = shift or die "not enough arguments";

  # Expand any abbreviations to get the unabreviated name.  (ST -> SHOWTURTLE)
  $EnglishProcedure = $main::EnglishAbbreviation{lc $EnglishProcedure} || $EnglishProcedure;

  # "?" predicates are normalized to their "P" suffix.
  $EnglishProcedure =~ s/\?$/p/;

  # Normalize case
  return lc $EnglishProcedure;
}

sub PrintAmbiguousTranslations($$) {
  my $LocaleName         = shift or die "not enough arguments";
  my $EnglishToLocalized = shift or die "not enough arguments";

  # For each translation, make sure that translation doesn't appear
  # as a translation for some other English name.
  my @englishNames = keys %{$EnglishToLocalized};
  foreach my $englishNameA (@englishNames) {
    my $normalizedEnglishNameA = NormalizeEnglishProcedureName($englishNameA);

    foreach my $englishNameB (@englishNames) {
      # It's obviously not a conflict when the names are the same.
      # We don't want to report the same problem twice, so we
      # only check when name A is less than name B.
      if ($englishNameA ge $englishNameB) {
        next;
      }

      # If the normalized names are the same, then these are multiple
      # translations for what is implemented as the same procedure, so
      # translating them as the same is redundant, but not conflicting.
      # For example "ST" and "SHOWTURTLE" or "defined?" and "definedp".
      my $normalizedEnglishNameB = NormalizeEnglishProcedureName($englishNameB);
      if ($normalizedEnglishNameA eq $normalizedEnglishNameB) {
        next;
      }

      # Now that we know A and B are distict, make sure that they aren't
      # translated with the same word.
      foreach my $localizedNameA (@{$$EnglishToLocalized{$englishNameA}}) {
        foreach my $localizedNameB (@{$$EnglishToLocalized{$englishNameB}}) {
          if ($localizedNameA eq $localizedNameB) {
            print "WARNING: $LocaleName tranlates both `$englishNameA' and `$englishNameB' to `$localizedNameA'\n";
          }
        }
      }
    }
  }
}

sub PrintTranslationsAsText($$$) {

  my $LocaleId           = shift or die "not enough arguments";
  my $EnglishToLocalized = shift or die "not enough arguments";
  my $LocalizedToEnglish = shift or die "not enough arguments";

  my $fromenglish = new IO::File "> fromenglish-$LocaleId.txt" or die $!;
  my $longestlength = 0;
  foreach my $english (sort keys %{$EnglishToLocalized}) {
    $longestlength = length $english if $longestlength < length $english;
  }
  foreach my $english (sort keys %{$EnglishToLocalized}) {
    my $spacing = ' ' x ($longestlength - length $english);
    foreach my $translation (@{$$EnglishToLocalized{$english}}) {
      $fromenglish->print("$english $spacing $translation\n");
    }
  }
  $fromenglish->close();


  my $toenglish = new IO::File "> toenglish-$LocaleId.txt" or die $!;
  $longestlength = 0;
  foreach my $translation (sort keys %{$LocalizedToEnglish}) {
    $longestlength = length $translation if $longestlength < length $translation;
  }
  foreach my $translation (sort keys %{$LocalizedToEnglish}) {
    my $spacing = ' ' x ($longestlength - length $translation);
    $toenglish->print("$translation $spacing $$LocalizedToEnglish{$translation}\n");
  }
  $toenglish->close();
}

sub GetLinkend($) {

  my $EnglishProcedure = shift or die "not enough arguments";

  # If this procedure is an abbreviation, we must link to the documentation for
  # what it abbreviates, since there is no documentation for the abbreviation.
  $EnglishProcedure = NormalizeEnglishProcedureName($EnglishProcedure);

  return "command-$EnglishProcedure";
}

sub PrintTranslationsAsDocBook($$$$$$) {

  my $LocaleName                  = shift or die "not enough arguments";
  my $LocaleId                    = shift or die "not enough arguments";
  my $EnglishToLocalizedProcedure = shift or die "not enough arguments";
  my $LocalizedToEnglishProcedure = shift or die "not enough arguments";
  my $EnglishToLocalizedColor     = shift or die "not enough arguments";
  my $LocalizedToEnglishColor     = shift or die "not enough arguments";

  # To keep the the Help menu clean, there is only one link into the appendix
  # from the menu for each direction of the translations.  Since the procedure
  # name table can become large, it would be easy for a user not to notice the
  # translation for the color names that follow it.  To make sure that the
  # translated color names are discoverable, we add navigation links.
  my $navigationLinks = '';
  if (%{$EnglishToLocalizedColor} or %{$LocalizedToEnglishColor}) {
    $navigationLinks .= "<para>";
    $navigationLinks .= "See Also: ";
    $navigationLinks .= "English to $LocaleName (";
    $navigationLinks .= "<link linkend='from-english-procedure-names'>procedures</link> | ";
    $navigationLinks .= "<link linkend='from-english-color-names'>colors</link>";
    $navigationLinks .= ")";
    $navigationLinks .= " and ";
    $navigationLinks .= "$LocaleName to English (";
    $navigationLinks .= "<link linkend='to-english-procedure-names'>procedures</link> | ";
    $navigationLinks .= "<link linkend='to-english-color-names'>colors</link>";
    $navigationLinks .= ")";
    $navigationLinks .= "</para>\n";
  }


  my $docbook = '';

  $docbook .= "<appendix id='from-english-procedure-names'>\n";
  $docbook .= "<title>English to $LocaleName: Procedure Names</title>\n";
  $docbook .= "<indexterm><primary>From English (procedure names)</primary></indexterm>\n";

  $docbook .= $navigationLinks;
  $docbook .= "<informaltable>\n";
  $docbook .= "  <tgroup cols='2'>\n";
  $docbook .= "    <thead>\n";
  $docbook .= "      <row>\n";
  $docbook .= "        <entry>English Procedure</entry>\n";
  $docbook .= "        <entry>$LocaleName Procedure</entry>\n";
  $docbook .= "      </row>\n";
  $docbook .= "    </thead>\n";
  $docbook .= "    <tbody>\n";

  # add a row for each english to localized translation
  foreach my $english (sort keys %{$EnglishToLocalizedProcedure}) {
    my $englishLinkend      = GetLinkend($english);
    my @encodedTranslations = map { encode_utf8 $_ } @{$$EnglishToLocalizedProcedure{$english}};

    $docbook .= "      <row>\n";
    $docbook .= "        <entry><link linkend='$englishLinkend'>$english</link></entry>\n";
    $docbook .= "        <entry><literallayout>" . join("\n", @encodedTranslations) . "</literallayout></entry>\n";
    $docbook .= "      </row>\n";
  }

  $docbook .= "    </tbody>\n";
  $docbook .= "  </tgroup>\n";
  $docbook .= "</informaltable>\n";
  $docbook .= "</appendix>\n";

  # If the color names have been translated, include a table for those.
  if (%{$EnglishToLocalizedColor}) {
    $docbook .= "<appendix id='from-english-color-names'>\n";
    $docbook .= "<title>English to $LocaleName: Color Names</title>\n";
    $docbook .= "<indexterm><primary>From English (color names)</primary></indexterm>\n";

    $docbook .= $navigationLinks;
    $docbook .= "<informaltable>\n";
    $docbook .= "  <tgroup cols='3'>\n";
    $docbook .= "    <thead>\n";
    $docbook .= "      <row>\n";
    $docbook .= "        <entry>English Color</entry>\n";
    $docbook .= "        <entry>$LocaleName Color</entry>\n";
    $docbook .= "        <entry>Sample</entry>\n";
    $docbook .= "      </row>\n";
    $docbook .= "    </thead>\n";
    $docbook .= "    <tbody>\n";

    # add a row for each english to localized translation
    foreach my $english (sort keys %{$EnglishToLocalizedColor}) {
      foreach my $translation (map { encode_utf8 $_ } @{$$EnglishToLocalizedColor{$english}}) {
        my $colorImagePath = GetColorFileRef($english);
        $docbook .= "      <row>\n";
        $docbook .= "        <entry>$english</entry>\n";
        $docbook .= "        <entry>$translation</entry>\n";
        $docbook .= "        <entry><mediaobject><imageobject><imagedata align='center' fileref='$colorImagePath'/></imageobject></mediaobject></entry>\n";
        $docbook .= "      </row>\n";
      }
    }

    $docbook .= "    </tbody>\n";
    $docbook .= "  </tgroup>\n";
    $docbook .= "</informaltable>\n";
    $docbook .= "</appendix>\n";
  }

  $docbook .= "\n";

  $docbook .= "<appendix id='to-english-procedure-names'>\n";
  $docbook .= "<title>$LocaleName to English: Procedure Names</title>\n";
  $docbook .= "<indexterm><primary>To English (procedure names)</primary></indexterm>\n";

  $docbook .= $navigationLinks;
  $docbook .= "<informaltable>\n";
  $docbook .= "  <tgroup cols='2'>\n";
  $docbook .= "    <thead>\n";
  $docbook .= "      <row>\n";
  $docbook .= "        <entry>$LocaleName Procedure</entry>\n";
  $docbook .= "        <entry>English Procedure</entry>\n";
  $docbook .= "      </row>\n";
  $docbook .= "    </thead>\n";
  $docbook .= "    <tbody>\n";

  # add a row for each localized to English translation
  foreach my $translation (sort keys %{$LocalizedToEnglishProcedure}) {
    my $english        = $$LocalizedToEnglishProcedure{$translation};
    my $translation    = encode_utf8 $translation;
    my $englishLinkend = GetLinkend($english);

    $docbook .= "      <row>\n";
    $docbook .= "        <entry>$translation</entry>\n";
    $docbook .= "        <entry><link linkend='$englishLinkend'>$english</link></entry>\n";
    $docbook .= "      </row>\n";
  }

  $docbook .= "    </tbody>\n";
  $docbook .= "  </tgroup>\n";
  $docbook .= "</informaltable>\n";
  $docbook .= "</appendix>\n";


  # If the color names have been translated, include a table for those.
  if (%{$LocalizedToEnglishColor}) {
    $docbook .= "<appendix id='to-english-color-names'>\n";
    $docbook .= "<title>$LocaleName to English: Color Names</title>\n";
    $docbook .= "<indexterm><primary>To English (color names)</primary></indexterm>\n";

    $docbook .= $navigationLinks;
    $docbook .= "<informaltable>\n";
    $docbook .= "  <tgroup cols='3'>\n";
    $docbook .= "    <thead>\n";
    $docbook .= "      <row>\n";
    $docbook .= "        <entry>$LocaleName Color</entry>\n";
    $docbook .= "        <entry>English Color</entry>\n";
    $docbook .= "        <entry>Sample</entry>\n";
    $docbook .= "      </row>\n";
    $docbook .= "    </thead>\n";
    $docbook .= "    <tbody>\n";

    # add a row for each english to localized translation
    foreach my $translation (sort keys %{$LocalizedToEnglishColor}) {
      my $english = $$LocalizedToEnglishColor{$translation};
      $translation = encode_utf8 $translation;

      my $colorImagePath = GetColorFileRef($english);

      $docbook .= "      <row>\n";
      $docbook .= "        <entry>$translation</entry>\n";
      $docbook .= "        <entry>$english</entry>\n";
      $docbook .= "        <entry><mediaobject><imageobject><imagedata align='center' fileref='$colorImagePath'/></imageobject></mediaobject></entry>\n";
      $docbook .= "      </row>\n";
    }

    $docbook .= "    </tbody>\n";
    $docbook .= "  </tgroup>\n";
    $docbook .= "</informaltable>\n";
    $docbook .= "</appendix>\n";
  }

  my $translations = new IO::File "> translations-$LocaleId.xml" or die $!;
  $translations->print($docbook);
  $translations->close();
}

# Adds English <-> Locale mappings to the given hashes
sub AddTranslation($$$$) {
  my $EnglishWord        = shift or die "not enough arguments";
  my $TranslatedWord     = shift or die "not enough arguments";
  my $EnglishToLocalized = shift or die "not enough arguments";
  my $LocalizedToEnglish = shift or die "not enough arguments";

  # English -> Localized is a list, since the same English word may
  # have multiple translations.
  if (not $$EnglishToLocalized{$EnglishWord}) {
    @$EnglishToLocalized{$EnglishWord} = \();
  }

  # Add this word to the list of translations for $EnglishWord (if it's not already there)
  if (not grep(/^\Q$TranslatedWord\E$/, @{$$EnglishToLocalized{$EnglishWord}})) {
    push @{$$EnglishToLocalized{$EnglishWord}}, $TranslatedWord;
  }

  $$LocalizedToEnglish{$TranslatedWord} = $EnglishWord;
}

sub MakeTranslationTables($$$) {

  my $LocaleName  = shift or die "not enough arguments";
  my $CountryCode = shift or die "not enough arguments";
  my $LocaleId    = shift or die "not enough arguments";

  my %symbolToEnglishProcedure    = ();
  my %englishToLocalizedProcedure = ();
  my %localizedToEnglishProcedure = ();

  my %symbolToEnglishColor        = ();
  my %localizedToEnglishColor     = ();
  my %englishToLocalizedColor     = ();

  #
  # Build a table of everything that can be translated
  #
  my $englishfile = new IO::File "localizedstrings-en.h" or die $!;
  while (<$englishfile>) {
    if (m/^\#define\s+LOCALIZED_ALTERNATE_(\w+)\s*"([^"]+)"/) {
      $symbolToEnglishProcedure{$1} = $2;
    } elsif (m/^\#define\s+LOCALIZED_COLOR_(\w+)\s*"([^"]+)"/) {
      $symbolToEnglishColor{$1}     = $2;
    }
  }
  $englishfile->close();

  #
  # extract the primitives and colors that were translated
  #
  my $localizedfile = new IO::File "localizedstrings-$CountryCode.h" or die $!;
  while (<$localizedfile>) {
    if (m/^\#define\s+LOCALIZED_(ALTERNATE|COLOR)_(\w+)\s*"([^"]+)"/) {
      my $symbolType    = $1;
      my $symbolicName  = $2;
      my $localizedName = $3;

      my $englishWord;
      if ($symbolType eq 'ALTERNATE') {
          $englishWord = $symbolToEnglishProcedure{$symbolicName};
      } else {
          $englishWord = $symbolToEnglishColor{$symbolicName};
      }

      $englishWord or die "Found a localization for $symbolicName that is not present in the English localization";

      unless (m/NOT_YET_LOCALIZED/) {
        # This is translated
        if (lc $englishWord ne lc $localizedName) {
          # The translation is different from the English name
          if ($symbolType eq 'ALTERNATE') {
            # only add documented procedures to the translation tables.
            if (IsDocumentedEnglishProcedure($englishWord)) {
              AddTranslation(
                $englishWord,
                $localizedName,
                \%englishToLocalizedProcedure,
                \%localizedToEnglishProcedure);
            }
          } else {
            # This is a color name
            AddTranslation(
              $englishWord,
              $localizedName,
              \%englishToLocalizedColor,
              \%localizedToEnglishColor);
          }
        }
      }
    }
  }
  $localizedfile->close();


  #
  # extract the library routines and primitives that were translated with COPYDEF
  #
  my $inProcedureDefinition = 0;

  my @to = ('to');
  push @to, @{$englishToLocalizedProcedure{'to'}} if $englishToLocalizedProcedure{'to'};
  my $toLineRegExp = "^\\s*(" . join('|', @to) . ")\\b";

  my @end = ('end');
  push @end, @{$englishToLocalizedProcedure{'end'}} if $englishToLocalizedProcedure{'end'};
  my $endLineRegExp = "^\\s*(" . join('|', @end) . ")\\b";

  $localizedfile = new IO::File "startup-$LocaleId.logoscript" or die $!;
  while (<$localizedfile>) {
    if (/$toLineRegExp/i) {
      # This is a TO line
      $inProcedureDefinition = 1;
    } elsif (/$endLineRegExp/i) {
      # This is an END line
      $inProcedureDefinition = 0;
    } elsif (not $inProcedureDefinition and /copydef\s+"([\S]+)\s+"([^]\s]+)/i) {
      # This is a COPYDEF that is at the top-level (not within a procedure definition)
      my $newname  = lc $1;
      my $original = lc $2;

      # They probably copydef'd the localized version, so keep looking
      # until we find the original.
      while ($localizedToEnglishProcedure{$original} &&
             $localizedToEnglishProcedure{$original} ne $original) {
        $original = lc $localizedToEnglishProcedure{$original};
      }

      if ($original ne $newname) {
        # Only add procedures to the translation tables which are documented.
        if (IsDocumentedEnglishProcedure($original)) {
          AddTranslation(
            $original,
            $newname,
            \%englishToLocalizedProcedure,
            \%localizedToEnglishProcedure);
        }
      }
    }
  }
  $localizedfile->close();

  PrintTranslationsAsText(
    $LocaleId,
    \%englishToLocalizedProcedure,
    \%localizedToEnglishProcedure);

  PrintTranslationsAsDocBook(
    $LocaleName,
    $LocaleId,
    \%englishToLocalizedProcedure,
    \%localizedToEnglishProcedure,
    \%englishToLocalizedColor,
    \%localizedToEnglishColor);

  PrintShadowedProcedures(
    $LocaleName,
    \%symbolToEnglishProcedure,
    \%localizedToEnglishProcedure);

  PrintAmbiguousTranslations(
    $LocaleName,
    \%englishToLocalizedProcedure);
}


InitializeColorTable();
MakeTranslationTables('German',     'de', 1031);
MakeTranslationTables('Greek',      'gr', 1032);
MakeTranslationTables('Spanish',    'es', 1034);
MakeTranslationTables('French',     'fr', 1036);
MakeTranslationTables('Italian',    'it', 1040);
MakeTranslationTables('Polish',     'pl', 1045);
MakeTranslationTables('Russian',    'ru', 1049);
MakeTranslationTables('Croatian',   'hr', 1050);
MakeTranslationTables('Portuguese', 'pt', 2070);
MakeTranslationTables('Pseudoloc',  'ps', 9999);
