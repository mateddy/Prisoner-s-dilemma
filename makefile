CC = gcc
CFLAGS ?= -g -std=c99 -pedantic -Wall -Wextra -Wconversion -lm
SOURCES = match.c
OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -lm
EXEC = match

all: $(EXEC)

$(EXEC): $(OBJECTS) $(LDFLAGS)

$(OBJECTS):

clean:
	$(RM) $(OBJECTS) *~

distclean: clean
	$(RM) $(EXEC)
