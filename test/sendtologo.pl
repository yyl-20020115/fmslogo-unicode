#! /usr/bin/perl -W
############################################################
# A simple test application that opens a socket to a given
# host/port, sends some data, then closes the socket.
#
# Usage: sendtologo.pl <hostname> <port>
#
# This is part of network.lgo
#
############################################################

use Socket;
use strict;

my $hostname = shift @ARGV or die "not enough parameters";
my $port     = shift @ARGV or die "not enough parameters";

my $proto = getprotobyname('tcp');
socket(SOCKET, PF_INET, SOCK_STREAM, $proto) or die $!;
my $sin = sockaddr_in($port, inet_aton($hostname));

connect(SOCKET, $sin) or die $!;

print SOCKET "hello" or die $!;

close (SOCKET) or die $!;
