CC = gcc
CFLAGS = -g -ansi -pedantic-errors -Wall -Werror -Wshadow -Wwrite-strings

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x

sss.o: sss-implementation.h sss.h split.h sss.c
	$(CC) -c $(CFLAGS) sss.c

public01.o: sss.h public01.c sss-implementation.h
	$(CC) -c $(CFLAGS) public01.c

public02.o: sss.h public02.c sss-implementation.h
	$(CC) -c $(CFLAGS) public02.c

public03.o: sss.h memory-checking.h public03.c sss-implementation.h
	$(CC) -c $(CFLAGS) public03.c

public04.o: sss.h public04.c sss-implementation.h
	$(CC) -c $(CFLAGS) public04.c

public05.o: sss.h public05.c sss-implementation.h
	$(CC) -c $(CFLAGS) public05.c

public06.o: sss.h memory-checking.h public01.c sss-implementation.h 
	$(CC) -c $(CFLAGS) public06.c

public07.o: sss.h public07.c sss-implementation.h
	$(CC) -c $(CFLAGS) public07.c

public08.o: sss.h public08.c sss-implementation.h
	$(CC) -c $(CFLAGS) public08.c

public09.o: sss.h public09.c sss-implementation.h
	$(CC) -c $(CFLAGS) public09.c

public10.o: sss.h public10.c sss-implementation.h
	$(CC) -c $(CFLAGS) public10.c

public01.x: sss.o public01.o split.o 
	$(CC) $(CFLAGS) sss.o public01.o split.o -o public01.x

public02.x: sss.o public02.o split.o
	$(CC) $(CFLAGS) sss.o public02.o split.o -o public02.x

public03.x: sss.o public03.o memory-checking.o split.o
	$(CC) $(CFLAGS) sss.o public03.o memory-checking.o split.o -o public03.x

public04.x: sss.o public04.o split.o
	$(CC) $(CFLAGS) sss.o public04.o split.o -o public04.x

public05.x: sss.o public05.o split.o
	$(CC) $(CFLAGS) sss.o public05.o split.o -o public05.x

public06.x: sss.o public06.o  memory-checking.o split.o
	$(CC) $(CFLAGS) sss.o public06.o memory-checking.o split.o -o public06.x

public07.x: sss.o public07.o split.o
	$(CC) $(CFLAGS) sss.o public07.o split.o -o public07.x

public08.x: sss.o public08.o split.o
	$(CC) $(CFLAGS) sss.o public08.o split.o -o public08.x

public09.x: sss.o public09.o split.o
	$(CC) $(CFLAGS) sss.o public09.o split.o -o public09.x

public10.x: sss.o public10.o split.o
	$(CC) $(CFLAGS) sss.o public10.o split.o -o public10.x


clean:
	rm sss.o public01.o public02.o public03.o public04.o public05.o public06.o public07.o public08.o public09.o public10.o public01.x public02.x public03.x public04.x public05.x public06.x public07.x public08.x public09.x public10.x
