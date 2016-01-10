CC = gcc
CFLAGS = -g -ansi -pedantic-errors -Wall -Werror -Wshadow -Wwrite-strings

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x 

machine.o: machine.c machine.h
	$(CC) -c $(CFLAGS) machine.c

interpreter.o: interpreter.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) interpreter.c

public01.o: public01.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public01.c

public02.o: public02.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public02.c

public03.o: public03.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public03.c

public04.o: public04.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public04.c

public05.o: public05.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public05.c

public06.o: public06.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public06.c

public07.o: public07.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public07.c

public08.o: public08.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public08.c

public09.o: public09.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public09.c

public10.o: public10.c machine.h interpreter.h
	$(CC) -c $(CFLAGS) public10.c

public01.x: public01.o machine.o interpreter.o
	$(CC) public01.o machine.o interpreter.o -o public01.x

public02.x: public02.o machine.o interpreter.o
	$(CC) public02.o machine.o interpreter.o -o public02.x

public03.x: public03.o machine.o interpreter.o
	$(CC) public03.o machine.o interpreter.o -o public03.x

public04.x: public04.o machine.o interpreter.o
	$(CC) public04.o machine.o interpreter.o -o public04.x

public05.x: public05.o machine.o interpreter.o
	$(CC) public05.o machine.o interpreter.o -o public05.x

public06.x: public06.o machine.o interpreter.o
	$(CC) public06.o machine.o interpreter.o -o public06.x

public07.x: public07.o machine.o interpreter.o
	$(CC) public07.o machine.o interpreter.o -o public07.x

public08.x: public08.o machine.o interpreter.o
	$(CC) public08.o machine.o interpreter.o -o public08.x

public09.x: public09.o machine.o interpreter.o
	$(CC) public09.o machine.o interpreter.o -o public09.x

public10.x: public10.o machine.o interpreter.o
	$(CC) public10.o machine.o interpreter.o -o public10.x

clean:
	rm machine.o interpreter.o public01.o public02.o public03.o public04.o public05.o public06.o public07.o public08.o public09.o public10.o public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x
