CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c11 -O0 -ggdb -no-pie
LIBS:=-lm

all: cachesim

cachesim: cachesim.o parceador.o cache.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

cache.o: cache.c cache.h parceador.h
	$(CC) $(CFLAGS) -c $< -o $@

parceador.o: parceador.c parceador.h 
	$(CC) $(CFLAGS) -c $< -o $@

cachesim.o: cachesim.c parceador.h cache.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f cachesim
	

