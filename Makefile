CC=gcc
CFLAGS=-Wall -Os
LDFLAGS=

PREFIX=/usr/local
BINDIR=/bin

SOURCES=locktray.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=locktray

all : obj bin

bin :
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(CFLAGS) $(LDFLAGS)

obj:
	$(CC) -c $(CFLAGS) $(SOURCES) -o $(OBJECTS)

install: 
	install -d $(DESTDIR)$(PREFIX)$(BINDIR) # create directory if nonexistant 
	install $(EXECUTABLE) $(DESTDIR)$(PREFIX)$(BINDIR)

clean:
	rm $(EXECUTABLE) $(OBJECTS)
