CC = gcc
CFLAGS ?= -g -std=c99 -pedantic -Wall -Wextra -Wconversion -lm
SOURCES = match.c
OBJECTS = $(SOURCES:.c=.o)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lm
endif

EXEC = match

all: $(EXEC)

$(EXEC): $(OBJECTS) $(LDFLAGS)

$(OBJECTS):

clean:
	$(RM) $(OBJECTS) *~

distclean: clean
	$(RM) $(EXEC)
