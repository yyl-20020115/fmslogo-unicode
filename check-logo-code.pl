use strict;
use IO::File;

my $exitCode = 0;

foreach my $filename (@ARGV) {

  next if -d $filename;

  my $lineNumber = 1;
  my $fh = new IO::File "<$filename" or die $!;
  while (<$fh>) {

    my $logoTokenDelimiter = '(^|$|[^a-zA-Z0-9_\.~])';

    if (m/$logoTokenDelimiter(ct)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses CT, which means HIDETURTLE in French.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(bl)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses BL, which means PENDOWN in Spanish.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(rc)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses RC, which means SQRT in Spanish.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(se)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses SE, which means IF in Portuguese and Italian.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(pd)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses PD, which means RT in Portuguese.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(pe)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses PE, which means LT in Portuguese.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(rw)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses RW, which means BACK in German.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(pr)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses PR, which means TO in German.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(er)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses ER, which means FIRST in German.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(st)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses ST, which means PR in Italian.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter((set)?(screen|pen|flood)colour)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses $1, which only exists in the English translation.\n";
      $exitCode = 1;
    }

    if (m/$logoTokenDelimiter(map.sentence)$logoTokenDelimiter/i) {
      print "$filename:$lineNumber file uses MAP.SENTENCE, which is probably a bug caused by replacing SE with SENTENCE.\n";
      $exitCode = 1;
    }

    $lineNumber++;
  }
  $fh->close;
}


exit $exitCode;
