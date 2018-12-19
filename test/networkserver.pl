#! /usr/bin/perl -W
############################################################
# A simple test application that opens a socket to a given
# host/port, sends some data, then closes the socket.
#
# Usage: networkserver.pl <test> <port>
#
# This is part of network.lgo
#
############################################################

use Socket;
use strict;

my $test = shift @ARGV or die "not enough parameters";
my $port = shift @ARGV or die "not enough parameters";

my $proto = getprotobyname('tcp');
socket(SERVER, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
setsockopt(SERVER, SOL_SOCKET, SO_REUSEADDR, pack("l", 1)) or die "setsockopt: $!";

bind(SERVER, sockaddr_in($port, INADDR_ANY)) or die "bind: $!";
listen(SERVER, SOMAXCONN) or die "listen: $!";

my $paddr = accept(CLIENT, SERVER);
my ($remoteport, $iaddr) = sockaddr_in($paddr);

# change the server's behavior, depending on the test we're running
if ($test eq 'simple')
{
  print CLIENT "hello\0";
}
elsif ($test eq 'nonul')
{
  print CLIENT "Hello";
}
elsif ($test eq 'largepacket')
{
  print CLIENT ("abcdefghijklmnopqrstuvwxyz" x 1000), "\0";
}
elsif ($test eq 'echo')
{
  my $data = '';
  recv(CLIENT, $data, 1024, 0) or die "recv: $!";
  print CLIENT $data;
}

close CLIENT;
close SERVER;
