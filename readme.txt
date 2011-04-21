
UPDATE 12/27/04 security fix in -e option for Windows

Netcat 1.11 for NT - nc111nt.zip

The original version of Netcat was written by *hobbit* <hobbit@avian.org>
The NT version was done by Weld Pond <weld@vulnwatch.org>

Netcat for NT is the tcp/ip "Swiss Army knife" that never made it into any 
of the resource kits.  It has proved to be an extremely versatile tool on 
the unix platform. So why should NT always be unix's poor cousin when it 
comes to tcp/ip testing and exploration?  I bet many NT admins out there
keep a unix box around to use tools such as Netcat or to test their systems
with the unix version of an NT vulnerability exploit.  With Netcat for NT
part of that feeling disempowerment is over.

Included with this release is Hobbit's original description of the powers 
of Netcat.  In this document I will briefly describe some of the things an
NT admin might want to do and know about with Netcat on NT.  For more
detailed technical information please read hobbit.txt included in the
nc11nt.zip archive.

     Basic Features

     * Outbound or inbound connections, TCP or UDP, to or from any ports
     * Full DNS forward/reverse checking, with appropriate warnings
     * Ability to use any local source port
     * Ability to use any locally-configured network source address
     * Built-in port-scanning capabilities, with randomizer
     * Can read command line arguments from standard input
     * Slow-send mode, one line every N seconds
     * Hex dump of transmitted and received data
     * Ability to let another program service established
       connections
     * Telnet-options responder

     New for NT

     * Ability to run in the background without a console window
     * Ability to restart as a single-threaded server to handle a new
       connection


A simple example of using Netcat is to pull down a web page from a web
server.  With Netcat you get to see the full HTTP header so you can see
which web server a particular site is running.

Since NT has a rather anemic command processor, some of the things that are
easy in unix may be a bit more clunky in NT. For the web page example first
create a file get.txt that contains the following line and then a blank
line:

GET / HTTP/1.0

To use Netcat to retrieve the home page of a web site use the command:
nc -v www.website.com 80 < get.txt

You will see Netcat make a connection to port 80, send the text contained
in the file get.txt, and then output the web server's response to stdout.
The -v is for verbose.  It tells you a little info about the connection
when it starts.

It is a bit easier to just open the connection and then type at the console
to do the same thing. 
nc -v www.website.com 80

Then just type in GET / HTTP/1.0 and hit a couple of returns.  You will 
see the same thing as above.

A far more exciting thing to do is to get a quick shell going on a remote
machine by using the -l or "listen" option and the -e or "execute"
option.  You run Netcat listening on particular port for a connection.
When a connection is made, Netcat executes the program of your choice
and connects the stdin and stdout of the program to the network connection.

nc -l -p 23 -t -e cmd.exe

will get Netcat listening on port 23 (telnet).  When it gets connected to
by a client it will spawn a shell (cmd.exe).  The -t option tells Netcat
to handle any telnet negotiation the client might expect.

This will allow you to telnet to the machine you have Netcat listening on
and get a cmd.exe shell when you connect.  You could just as well use 
Netcat instead of telnet:

nc xxx.xxx.xxx.xxx 23

will get the job done.  There is no authentication on the listening side
so be a bit careful here.  The shell is running with the permissions of the
process that started Netcat so be very careful.  If you were to use the
AT program to schedule Netcat to run listening on a port with the 
-e cmd.exe option, when you connected you would get a shell with user
NT AUTHORITY\SYSTEM.

The beauty of Netcat really shines when you realize that you can get it
listening on ANY port doing the same thing.  Do a little exploring and
see if the firewall you may be behind lets port 53 through.  Run Netcat
listening behind the firewall on port 53.  

nc -L -p 53 -e cmd.exe

Then from outside the firewall connect to the listening machine:

nc -v xxx.xxx.xxx.xx 53

If you get a command prompt then you are executing commands on the
listening machine.  Use 'exit' at the command prompt for a clean
disconnect. The -L (note the capital L) option will restart Netcat with
the same command line when the connection is terminated.  This way you can
connect over and over to the same Netcat process.

A new feature for the NT version is the -d or detach from console flag.
This will let Netcat run without an ugly console window cluttering up the
screen or showing up in the task list.

You can even get Netcat to listen on the NETBIOS ports that are probably
running on most NT machines.  This way you can get a connection to a
machine that may have port filtering enabled in the TCP/IP Security Network
control panel.  Unlike Unix, NT does not seem to have any security around
which ports that user programs are allowed to bind to.  This means any
user can run a program that will bind to the NETBIOS ports.

You will need to bind "in front of" some services that may already be
listening on those ports.  An example is the NETBIOS Session Service that
is running on port 139 of NT machines that are sharing files.  You need
to bind to a specific source address (one of the IP addresses of the 
machine) to accomplish this.  This gives Netcat priority over the NETBIOS
service which is at a lower priority because it is bound to ANY IP address.
This is done with the Netcat -s option:

nc -v -L -e cmd.exe -p 139 -s xxx.xxx.xxx.xxx

Now you can connect to the machine on port 139 and Netcat will field
the connection before NETBIOS does.  You have effectively shut off
file sharing on this machine by the way.  You have done this with just
user privileges to boot.

PROBLEMS with Netcat 1.1 for NT

There are a few known problems that will eventually be fixed.  One is
the -w or timeout option.  This works for final net reads but not
for connections.  Another problem is using the -e option in UDP mode.
You may find that some of the features work on Windows 95.  Most
of the listening features will not work on Windows 95 however.   These will
be fixed in a later release.

Netcat is distributed with full source code so that people can build
upon this work.  If you add something useful or discover something 
interesting about NT TCP/IP let met know.

Weld Pond <weld@l0pht.com>, 2/2/98




