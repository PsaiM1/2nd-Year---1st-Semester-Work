CC = gcc
CFLAGS = -g -ansi -pedantic-errors -Wall -Werror -Wshadow -Wwrite-strings

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x secret01.x secret02.x secret03.x secret04.x secret05.x secret06.x secret07.x secret08.x secret09.x secret10.x secret11.x secret12.x secret13.x secret14.x secret15.x

graph.o: graph.h graph-implementation.h graph.c
	$(CC) -c $(CFLAGS) graph.c

public01.o: graph.h public01.c graph-implementation.h
	$(CC) -c $(CFLAGS) public01.c

public02.o: graph.h public02.c graph-implementation.h
	$(CC) -c $(CFLAGS) public02.c

public03.o: graph.h public03.c graph-implementation.h
	$(CC) -c $(CFLAGS) public03.c

public04.o: graph.h public04.c graph-implementation.h
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

public10.o: graph.h public10.c graph-implementation.h
	$(CC) -c $(CFLAGS) public10.c

secret01.o: graph.h secret01.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret01.c

secret02.o: graph.h secret02.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret02.c

secret03.o: graph.h secret03.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret03.c

secret04.o: graph.h secret04.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret04.c

secret05.o: graph.h secret05.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret05.c

secret06.o: graph.h secret06.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret06.c

secret07.o: graph.h secret07.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret07.c

secret08.o: graph.h secret08.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret08.c

secret09.o: graph.h secret09.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret09.c

secret10.o: graph.h secret10.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret10.c

secret11.o: graph.h secret11.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret11.c

secret12.o: graph.h secret12.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret12.c

secret13.o: graph.h secret13.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret13.c

secret14.o: graph.h secret14.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret14.c

secret15.o: graph.h secret15.c graph-implementation.h
	$(CC) -c $(CFLAGS) secret15.c

public01.x: public01.o graph.o
	$(CC) $(CFLAGS) public01.o graph.o -o public01.x

public02.x: public02.o graph.o
	$(CC) $(CFLAGS) public02.o graph.o -o public02.x

public03.x: public03.o graph.o
	$(CC) $(CFLAGS) public03.o graph.o -o public03.x

public04.x: public04.o graph.o
	$(CC) $(CFLAGS) public04.o graph.o -o public04.x

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

public10.x: public10.o graph.o
	$(CC) $(CFLAGS) public10.o graph.o -o public10.x

secret01.x: secret01.o graph.o
	$(CC) $(CFLAGS) secret01.o graph.o -o secret01.x

secret02.x: secret02.o graph.o
	$(CC) $(CFLAGS) secret02.o graph.o -o secret02.x

secret03.x: secret03.o graph.o
	$(CC) $(CFLAGS) secret03.o graph.o -o secret03.x

secret04.x: secret04.o graph.o
	$(CC) $(CFLAGS) secret04.o graph.o -o secret04.x

secret05.x: secret05.o graph.o
	$(CC) $(CFLAGS) secret05.o graph.o -o secret05.x

secret06.x: secret06.o graph.o
	$(CC) $(CFLAGS) secret06.o graph.o -o secret06.x

secret07.x: secret07.o graph.o
	$(CC) $(CFLAGS) secret07.o graph.o -o secret07.x

secret08.x: secret08.o graph.o
	$(CC) $(CFLAGS) secret08.o graph.o -o secret08.x

secret09.x: secret09.o graph.o
	$(CC) $(CFLAGS) secret09.o graph.o -o secret09.x

secret10.x: secret10.o graph.o
	$(CC) $(CFLAGS) secret10.o graph.o -o secret10.x

secret11.x: secret11.o graph.o
	$(CC) $(CFLAGS) secret11.o graph.o -o secret11.x

secret12.x: secret12.o graph.o
	$(CC) $(CFLAGS) secret12.o graph.o -o secret12.x

secret13.x: secret13.o graph.o
	$(CC) $(CFLAGS) secret13.o graph.o -o secret13.x

secret14.x: secret14.o graph.o
	$(CC) $(CFLAGS) secret14.o graph.o -o secret14.x

secret15.x: secret15.o graph.o
	$(CC) $(CFLAGS) secret15.o graph.o -o secret15.x

clean:
	rm *.o *.x
