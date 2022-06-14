CC=gcc
CFLAGS=-Wall
LDLIBS=-lm


main_prog: main_prog.c nww.o nwd.o library.a
	$(CC) $(CFLAGS) -o main_prog main_prog.c library.a

library.a: nww.o nwd.o
	ar rs library.a nww.o nwd.o

nww.o: nww.c
	$(CC) $(CFLAGS) -c nww.c

nwd.o: nwd.c
	$(CC) $(CFLAGS) -c nwd.c

clean:
	rm -f *~
	rm -f *.o
	rm -f *.a

cleanall: clean
	rm -f main_prog
