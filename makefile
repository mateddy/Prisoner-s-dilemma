CC = gcc
CFLAGS ?= -g -std=c99 -pedantic -Wall -Wextra -Wconversion
SOURCES = match.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = match

all: $(EXEC)

$(EXEC): $(OBJECTS)

$(OBJECTS):

clean:
	$(RM) $(OBJECTS) *~

distclean: clean
	$(RM) $(EXEC)
