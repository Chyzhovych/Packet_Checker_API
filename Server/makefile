CC= gcc

CFLAGS=-c

all: server

server: server.o socket.o checksum.o
	$(CC) server.o socket.o checksum.o -o server -lpthread 

server.o: server.cpp
	$(CC) $(CFLAGS) -lpthread server.cpp

checksum.o: checksum.cpp
	$(CC) $(CFLAGS)  checksum.cpp

socket.o: socket.cpp socket.hpp
	$(CC) $(CFLAGS) -lpthread -fpermissive socket.cpp 


clean:
	rm -rf *.o server socket checksum