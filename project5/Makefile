CC = gcc
CFLAGS = -g -ansi -pedantic-errors -Wall -Werror -Wshadow -Wwrite-strings

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x

graph.o: graph.h graph-implementation.h graph.c
	$(CC) -c $(CFLAGS) graph.c

name-list-to-string.o: name-list-to-string.h name-list-to-string.c
	$(CC) -c $(CFLAGS) name-list-to-string.c

public01.o: graph.h public01.c graph-implementation.h memory-checking.h
	$(CC) -c $(CFLAGS) public01.c

public02.o: graph.h public02.c graph-implementation.h memory-checking.h
	$(CC) -c $(CFLAGS) public02.c

public03.o: graph.h public03.c graph-implementation.h 
	$(CC) -c $(CFLAGS) public03.c

public04.o: graph.h public04.c graph-implementation.h memory-checking.h
	$(CC) -c $(CFLAGS) public04.c

public05.o: graph.h public05.c graph-implementation.h
	$(CC) -c $(CFLAGS) public05.c

public06.o: graph.h public06.c graph-implementation.h
	$(CC) -c $(CFLAGS) public06.c

public07.o: graph.h public07.c graph-implementation.h
	$(CC) -c $(CFLAGS) public07.c

public08.o: graph.h public08.c graph-implementation.h
	$(CC) -c $(CFLAGS) public08.c

public09.o: graph.h public09.c graph-implementation.h
	$(CC) -c $(CFLAGS) public09.c

public10.o: graph.h public10.c graph-implementation.h memory-checking.h name-list-to-string.h 
	$(CC) -c $(CFLAGS) public10.c

public01.x: public01.o graph.o memory-checking.o
	$(CC) $(CFLAGS) public01.o graph.o memory-checking.o -o public01.x

public02.x: public02.o graph.o memory-checking.o
	$(CC) $(CFLAGS) public02.o graph.o memory-checking.o -o public02.x

public03.x: public03.o graph.o
	$(CC) $(CFLAGS) public03.o graph.o -o public03.x

public04.x: public04.o graph.o memory-checking.o
	$(CC) $(CFLAGS) public04.o graph.o memory-checking.o -o public04.x

public05.x: public05.o graph.o
	$(CC) $(CFLAGS) public05.o graph.o -o public05.x

public06.x: public06.o graph.o
	$(CC) $(CFLAGS) public06.o graph.o -o public06.x

public07.x: public07.o graph.o
	$(CC) $(CFLAGS) public07.o graph.o -o public07.x

public08.x: public08.o graph.o
	$(CC) $(CFLAGS) public08.o graph.o -o public08.x

public09.x: public09.o graph.o
	$(CC) $(CFLAGS) public09.o graph.o -o public09.x

public10.x: public10.o graph.o memory-checking.o name-list-to-string.o
	$(CC) $(CFLAGS) public10.o graph.o memory-checking.o name-list-to-string.o -o public10.x

clean:
	rm public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x public01.o public02.o public03.o public04.o public05.o public06.o public07.o public08.o public09.o public10.o name-list-to-string.o
