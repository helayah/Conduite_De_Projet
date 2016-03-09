CC = gcc
CFLAGS = -Wall
LFLAGS = `pkg-config --libs glib-2.0` -I/usr/include/libxml2  -lxml2 -L./lib -I./include -lSDL2 -lm
EXEC = main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all : $(EXEC)

$(EXEC) : main.o interface.o draw.o parser.o objs.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o interface.o draw.o parser.o objs.o $(LFLAGS)

interface.o : interface.c interface.h
	$(CC) -o $@ -c $< $(LFLAGS)

draw.o : draw.c draw.h
	$(CC) -o $@ -c $< $(LFLAGS)

objs.o : objs.c objs.h
	$(CC) -o $@ -c $< $(LFLAGS)

parser.o : parser.c parser.h
	$(CC) -o $@ -c $< $(LFLAGS)

main.o : main.c
	$(CC) -o $@ -c $< $(LFLAGS)


clean :
	rm -f $(OBJECTS) $(EXEC) *.exe *~ *.*~
