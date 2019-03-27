CC = gcc
CFLAGS = -Wall -fPIC -g

LDFLAGS = -L.

build:tema1

tema1: fctAux.o main.o opElem.o opHash.o libhash.so
	$(CC) $(CFLAGS)  $^ -o $@ -lhash $(LDFLAGS)

fctAux.o: fctAux.c
main.o: main.c
opElem.o: opElem.c
opHash.o: opHash.c

clean:
	rm -rf *.o tema1
