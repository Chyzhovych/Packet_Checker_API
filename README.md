# Viktor Chyzhovych

Project description:

Application check packets.
 
Application support the next functionality:
Proxy application (that is in the middle).
Application logic:

Client sends data just forwards it to server.
Proxy does modifications in payload and resend them to server.
Server must figure out that data has been changed in the middle (calculating packet checksum).

Technologies: C++, Networking, Multithreading, Linux, Make.

