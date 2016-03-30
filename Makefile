GCC 		= 	gcc
CFLAGS 		= 	-Wall
LFLAGS 		= 	`pkg-config --libs glib-2.0` -I/usr/include/libxml2 -lxml2 -L./lib -I./include -lSDL2-2.0 -lm -lSDL2_gfx
EXEC 		= 	main
#TEST		= 	main
HEADERS 	= 	$(wildcard include/*.h)
SOURCES		= 	$(wildcard *.c) \
				$(wildcard src/*.c)
OBJECTS 	= 	$(patsubst %.c, %.o, $(SOURCES))
GARBAGES	= 	*.exe *.stackdump *~ *.*~ */*~ */*.*~ *.o


all: $(EXEC) cleanobj

run:
	./main
	
vlg:
	valgrind ./main

#$(EXEC): $(OBJECTS)
#	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
	
$(EXEC): main.o objs.o parser.o map.o operations.o trie.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o parser.o objs.o map.o operations.o trie.o $(LFLAGS)
	
parser.o: src/parser.c include/parser.h
	$(CC) -o $@ -c $< $(LFLAGS)
	
objs.o: src/objs.c include/objs.h
	$(CC) -o $@ -c $< $(LFLAGS)
	
map.o: src/map.c include/map.h
	$(CC) -o $@ -c $< $(LFLAGS)
	
operations.o: src/operations.c include/operations.h
	$(CC) -o $@ -c $< $(LFLAGS)	

trie.o: src/trie.c include/trie.h
	$(CC) -o $@ -c $< $(LFLAGS)	

main.o: main.c
	$(CC) -o $@ -c $< $(LFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(LFLAGS)

cleanobj:
	rm -f $(OBJECTS) $(GARBAGES)

clean: cleanobj
	rm -f $(EXEC)

