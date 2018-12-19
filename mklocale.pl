#!/usr/bin/perl -w

use strict;
use IO::File;

sub UpdateLocalizationFiles($$$) {

  my $CountryCode = shift or die "too few arguments";
  my $LocaleName  = shift or die "too few arguments";
  my $Translator  = shift or die "too few arguments";

  my %translations = ();

  #
  # Build a table of everything that has already been translated
  #
  my $existingStringTable = new IO::File "localizedstrings-$CountryCode.h";
  if ($existingStringTable) {

    while (<$existingStringTable>) {
      chomp;
      if (m/^\#define\s+([\w\d_]+)\s*(.*)$/) {
        my $symbolicName = $1;
        my $translation  = $2;
        if ($translation !~ m!// NOT_YET_LOCALIZED!) {
            $translations{$symbolicName} = $translation;
        }
      }
    }
    $existingStringTable->close();
  }

  my $newFile = new IO::File "> localizedstrings-$CountryCode.h" or die $!;


  #
  # Write out the new localization using the English one as a basis
  #
  my $original = new IO::File "localizedstrings-en.h" or die $!;
  while (<$original>) {
    chomp;
    my $line = $_;

    if ($line =~ m/^\#define\s+([\w\d_]+)(\s*)(.*)$/) {
      my $token       = $1;
      my $space       = $2;
      my $translation = $3;

      if ($translations{$1}) {
        # this has already been localized
        print $newFile "#define $token$space$translations{$token}\n";
      }
      else {
        # this has not yet been translated
        if ($CountryCode eq 'ps') {
          # This is the pseudo locale, which means that the
          # translation is to added "pseudo." to the front of the
          # english translation.
          $translation =~ s/^"(\s*)/"$1pseudo./;
          print $newFile "#define $token$space$translation\n";
        }
        else {
          # append a stylized comment indicating that this should be localized
          print $newFile "$line // NOT_YET_LOCALIZED\n";
        }
      }
    }
    elsif ($line =~ m/localized strings for English/) {
      # translate the locale English
      $line =~ s/English/$LocaleName by $Translator/;
      print $newFile "$line\n";
    }
    else {
      # this line is not localizable
      print $newFile "$line\n";
    }
  }

  $original->close();
  $newFile->close();
}


UpdateLocalizationFiles('zh-cn', 'Chinese',    'Pachleng');
UpdateLocalizationFiles('fr',    'French',     'Bertrand CARETTE');
UpdateLocalizationFiles('gr',    'Greek',      'Theodoros Chatzigiannakis');
UpdateLocalizationFiles('es',    'Spanish',    'Daniel Ajoy');
UpdateLocalizationFiles('it',    'Italian',    'Stefano Federici and Francesco Simone Carta');
UpdateLocalizationFiles('pt',    'Portuguese', 'Alexandre R Soares');
UpdateLocalizationFiles('de',    'German',     'Stephan Vogel');
UpdateLocalizationFiles('ru',    'Russian',    'Igor Baglaev');
UpdateLocalizationFiles('hr',    'Croatian',   'Domagoj Kuna');
UpdateLocalizationFiles('pl',    'Polish',     'Andrzej Pruszynski');
UpdateLocalizationFiles('ps',    'Pseudoloc',  'David Costanzo');
