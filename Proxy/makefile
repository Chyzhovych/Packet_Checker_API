CC= gcc

CFLAGS=-c

all: proxy

proxy: proxy.o psocket.o 
	$(CC) proxy.o psocket.o -o proxy -lpthread 

proxy.o: proxy.cpp
	$(CC) $(CFLAGS) -lpthread proxy.cpp

psocket.o: psocket.cpp psocket.hpp
	$(CC) $(CFLAGS) -lpthread -fpermissive psocket.cpp


clean:
	rm -rf *.o proxy psocket 