CC = g++
CXXFLAGS ?= -g -std=c++0x -pedantic -Wall -Wextra -Wconversion
SOURCES = pd.cc strategy.cc
OBJECTS = $(SOURCES:.cc=.o)
EXEC = pd

all: $(EXEC)

$(EXEC): $(OBJECTS)

$(OBJECTS):

clean:
	$(RM) $(OBJECTS) *~

distclean: clean
	$(RM) $(EXEC)
