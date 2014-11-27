CC=gcc
CFLAGS=-c -std=c99 -Wall -g
LDFLAGS=
SOURCES=array_sum.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=array_sum

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

