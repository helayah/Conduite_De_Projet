# -I/usr/include/libxml2 -lxml2
CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -I./include -lxml2 -L./lib -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixe
EXEC = interface
EXEC_PARS = interface
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

parser : $(EXEC_PARS)

$(EXEC_PARS): main.c parser.c
	$(CC) -o $@ $^

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC) *~ *.*~
