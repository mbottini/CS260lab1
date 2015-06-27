CC=g++

CFLAGS=-c -Wall -Wno-write-strings

all: lab1

lab1: item.o itemnode.o inventory.o main.o
	$(CC) -o lab1 item.o itemnode.o inventory.o main.o 

item.o: item.cpp
	$(CC) $(CFLAGS) item.cpp

itemnode.o: item.o itemnode.cpp
	$(CC) $(CFLAGS) itemnode.cpp

inventory.o: item.o itemnode.o inventory.cpp
	$(CC) $(CFLAGS) inventory.cpp

main.o: item.o itemnode.o inventory.o main.cpp
	$(CC) $(CFLAGS) main.cpp
clean:
	rm *.o
