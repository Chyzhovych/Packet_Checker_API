CC= gcc

CFLAGS=-c

all: client

client: client.o csocket.o 
	$(CC) client.o csocket.o -lpthread -o client

client.o: client.cpp
	$(CC) $(CFLAGS) -lpthread client.cpp

csocket.o: csocket.cpp csocket.hpp
	$(CC) $(CFLAGS) -lpthread -fpermissive csocket.cpp


clean:
	rm -rf *.o client csocket