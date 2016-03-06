# -I/usr/include/libxml2 -lxml2
CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -I./include -lxml2 -L./lib -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixe
EXEC = main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC) *.exe *~ *.*~
