CC = gcc
CFLAGS = -Wall
#LFLAGS = `pkg-config --libs glib-2.0` -I/usr/include/libxml2  -lxml2 -L./lib -I./include -lSDL2 -lm
LFLAGS = `pkg-config --libs glib-2.0` -I/usr/include/libxml2  -lxml2 -L./lib -I./include -lSDL2-2.0 -lm -lSDL2_gfx
EXEC = main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all : $(EXEC)

$(EXEC) : main.o interface.o operation.o parser.o objs.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o interface.o operation.o parser.o objs.o $(LFLAGS)

interface.o : interface.c interface.h
	$(CC) -o $@ -c $< $(LFLAGS)

operation.o : operation.c operation.h
	$(CC) -o $@ -c $< $(LFLAGS)

objs.o : objs.c objs.h
	$(CC) -o $@ -c $< $(LFLAGS)

parser.o : parser.c parser.h
	$(CC) -o $@ -c $< $(LFLAGS)

main.o : main.c
	$(CC) -o $@ -c $< $(LFLAGS)
	
run :
	./$(EXEC) 01_denver_lafayette.osm

test :
	./$(EXEC) vosges.osm

valgd:
	valgrind ./$(EXEC) 01_denver_lafayette.osm

clean :
	rm -f $(OBJECTS) $(EXEC) *.exe *.stackdump *~ *.*~
