#!/usr/bin/perl -W
#################################################################
# A simple Perl script that calls out to convert from ImageMagick
# to create small square images that demonstrate a color.
#################################################################

use strict;

sub MakeColor($$$)
{
    my ($Red, $Green, $Blue) = @_;
    my $color = sprintf('%2.2X%2.2X%2.2X', $Red, $Green, $Blue);   
    system("convert -bordercolor Black -border 1x1 -size 18x18 xc:#$color rgb$color.png");
}

# SETCOLOR by index 0-15
MakeColor(0,     0,   0); # black
MakeColor(0,     0, 255); # blue
MakeColor(0,   255,   0); # lime
MakeColor(0,   255, 255); # cyan
MakeColor(255,   0,   0); # red
MakeColor(255,   0, 255); # magenta
MakeColor(255, 255,   0); # yellow
MakeColor(255, 255, 255); # white

MakeColor(155,  96,  59); # brown (almost)
MakeColor(197, 136,  18); # tan (almost)
MakeColor(100, 162,  64); # olive drab (almost)
MakeColor(120, 187, 187); # sky blue (almost)
MakeColor(255, 149, 119); # salmon (almost)
MakeColor(144, 113, 208); # medium purple (almost)
MakeColor(255, 163,   0); # orange (almost)
MakeColor(183, 183, 183); # dark grey (almost)

# SETCOLOR by name
MakeColor(240, 248, 255); # alice blue
MakeColor(250, 235, 215); # antique white
MakeColor(127, 255, 212); # aquamarine
MakeColor(240, 255, 255); # azure
MakeColor(245, 245, 220); # beige
MakeColor(255, 228, 196); # bisque
MakeColor(255, 235, 205); # blanched almond
MakeColor(138,  43, 226); # blue violet
MakeColor(165,  42,  42); # brown
MakeColor(222, 184, 135); # burly wood
MakeColor(95,  158, 160); # cadet blue
MakeColor(127, 255,   0); # chartreuse
MakeColor(210, 105,  30); # chocolate
MakeColor(255, 127,  80); # coral
MakeColor(100, 149, 237); # cornflower blue
MakeColor(255, 248, 220); # cornsilk
MakeColor(220,  20,  60); # crimson
MakeColor(  0,   0, 139); # dark blue
MakeColor(  0, 139, 139); # dark cyan
MakeColor(184, 134,  11); # dark goldenrod
MakeColor(169, 169, 169); # dark grey
MakeColor(  0, 100,   0); # dark green
MakeColor(189, 183, 107); # dark khaki
MakeColor(139,   0, 139); # dark magenta
MakeColor( 85, 107,  47); # dark olive green
MakeColor(255, 140,   0); # dark orange
MakeColor(153,  50, 204); # dark orchid
MakeColor(139,   0,   0); # dark red
MakeColor(233, 150, 122); # dark salmon
MakeColor(143, 188, 143); # dark sea green
MakeColor( 72,  61, 139); # dark slate blue
MakeColor( 47,  79,  79); # dark slate grey
MakeColor(  0, 206, 209); # dark turquiose
MakeColor(148,   0, 211); # dark violet
MakeColor(255,  20, 147); # deep pink
MakeColor(  0, 191, 255); # deep sky blue
MakeColor(105, 105, 105); # dim grey
MakeColor( 30, 144, 255); # dodger blue
MakeColor(178,  34,  34); # fire brick
MakeColor(255, 250, 240); # floral white
MakeColor( 34, 139,  34); # forest green
MakeColor(255,   0, 255); # fuchsia
MakeColor(220, 220, 220); # gainsboro
MakeColor(248, 248, 255); # ghostwhite
MakeColor(255, 215,   0); # gold
MakeColor(218, 165,  32); # goldenrod
MakeColor(128, 128, 128); # gray
MakeColor(  0, 128,   0); # green
MakeColor(173, 255,  47); # greenyellow
MakeColor(128, 128, 128); # grey
MakeColor(240, 255, 240); # honeydew
MakeColor(255, 105, 180); # hotpink
MakeColor(205,  92,  92); # indianred
MakeColor( 75,   0, 130); # indigo
MakeColor(255, 255, 240); # ivory
MakeColor(240, 230, 140); # khaki
MakeColor(230, 230, 250); # lavender
MakeColor(255, 240, 245); # lavenderblush
MakeColor(124, 252,   0); # lawngreen
MakeColor(255, 250, 205); # lemonchiffon
MakeColor(173, 216, 230); # light blue
MakeColor(240, 128, 128); # light coral
MakeColor(224, 255, 255); # light cyan
MakeColor(250, 250, 210); # light goldenrod yellow
MakeColor(211, 211, 211); # light gray
MakeColor(144, 238, 144); # light green
MakeColor(255, 182, 193); # light pink
MakeColor(255, 160, 122); # light salmon
MakeColor( 32, 178, 170); # light seagreen
MakeColor(135, 206, 250); # light skyblue
MakeColor(119, 136, 153); # light slate gray
MakeColor(176, 196, 222); # light steel blue
MakeColor(255, 255, 224); # light yellow
MakeColor(  0, 255,   0); # lime
MakeColor( 50, 205,  50); # limegreen
MakeColor(250, 240, 230); # linen
MakeColor(255,   0, 255); # magenta
MakeColor(128,   0,   0); # maroon
MakeColor(102, 205, 170); # medium aquamarine
MakeColor(  0,   0, 205); # medium blue
MakeColor(186,  85, 211); # medium orchid
MakeColor(147, 112, 216); # medium purple
MakeColor( 60, 179, 113); # medium seagreen
MakeColor(123, 104, 238); # medium slateblue
MakeColor(  0, 250, 154); # medium springgreen
MakeColor( 72, 209, 204); # medium turquoise
MakeColor(199,  21, 133); # medium violet red
MakeColor( 25,  25, 112); # midnight blue
MakeColor(245, 255, 250); # mintcream
MakeColor(255, 228, 225); # mistyrose
MakeColor(255, 228, 181); # moccasin
MakeColor(255, 222, 173); # navajo white
MakeColor(  0,   0, 128); # navy
MakeColor(253, 245, 230); # oldlace
MakeColor(128, 128,   0); # olive
MakeColor(107, 142,  35); # olivedrab
MakeColor(255, 165,   0); # orange
MakeColor(255,  69,   0); # orangered
MakeColor(218, 112, 214); # orchid
MakeColor(238, 232, 170); # palegoldenrod
MakeColor(152, 251, 152); # palegreen
MakeColor(175, 238, 238); # paleturquoise
MakeColor(216, 112, 147); # palevioletred
MakeColor(255, 239, 213); # papayawhip
MakeColor(255, 218, 185); # peachpuff
MakeColor(205, 133,  63); # peru
MakeColor(255, 192, 203); # pink
MakeColor(221, 160, 221); # plum
MakeColor(176, 224, 230); # powderblue
MakeColor(128,   0, 128); # purple
MakeColor(188, 143, 143); # rosybrown
MakeColor( 65, 105, 225); # royalblue
MakeColor(139,  69,  19); # saddlebrown
MakeColor(250, 128, 114); # salmon
MakeColor(244, 164,  96); # sandybrown
MakeColor( 46, 139,  87); # seagreen
MakeColor(255, 245, 238); # seashell
MakeColor(160,  82,  45); # sienna
MakeColor(192, 192, 192); # silver
MakeColor(135, 206, 235); # skyblue
MakeColor(106,  90, 205); # slateblue
MakeColor(112, 128, 144); # slategrey
MakeColor(255, 250, 250); # snow
MakeColor(  0, 255, 127); # springgreen
MakeColor( 70, 130, 180); # steelblue
MakeColor(210, 180, 140); # tan
MakeColor(  0, 128, 128); # teal
MakeColor(216, 191, 216); # thistle
MakeColor(255,  99,  71); # tomato
MakeColor( 64, 224, 208); # turquoise
MakeColor(238, 130, 238); # violet
MakeColor(245, 222, 179); # wheat
MakeColor(255, 255, 255); # white
MakeColor(245, 245, 245); # whitesmoke
MakeColor(255, 255,   0); # yellow
MakeColor(154, 205,  50); # yellowgreen
