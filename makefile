RM=rm -f
MKDIR_P=mkdir -p

CC=gcc
INC=-I ./include
CFLAGS=-std=gnu11 -pedantic-errors $(INC) -c -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes -g
LDFLAGS=-lncurses -lrt -lasound

CFLAGS_T =-std=gnu11 -pedantic-errors $(INC) -Wall -g
LDFLAGS_T=-lcmocka -ltap

#dirs
SRCDIR=src
OUTPUTDIR=bin
BUILDDIR=build
TESTDIR=tests

MAIN_SRC=main

#EXT_DIR=external
#EXT_BUILDDIR=$(BUILDDIR)/$(EXT_DIR)

#files
SOURCES=$(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:%.c=%.o))
TARGET=$(OUTPUTDIR)/main

SOURCES_T=$(shell find $(TESTDIR) -type f -name '*.c')
OBJECTS_T=$(SOURCES_T:%.c=%.o)

#EXT_SOURCES=$(shell find $(EXT_DIR) -type f -name '*.c')

##
all: $(SOURCES) $(TARGET)# builddirs

#deps: $(EXT_SOURCES) builddirs
#	$(CC) $(CFLAGS) $<
#	mv *.o $(EXT_BUILDDIR)/

#project
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

#utils
#builddirs:
#	$(MKDIR_P) $(EXT_BUILDDIR)

test: all $(OBJECTS_T)

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	@printf "\n\
--------------------------------------------------------------------------------\n\
RUNNING TEST: $<\n\
--------------------------------------------------------------------------------\n"
	$(CC) $(CFLAGS_T) $(LDFLAGS) $(LDFLAGS_T) $(filter-out $(BUILDDIR)/$(MAIN_SRC).o, $(OBJECTS)) $< -o $<.o
	LD_LIBRARY_PATH=/usr/local/lib ./$<.o ; rm ./$<.o


run: all
	./$(TARGET)

clean:
	$(RM) $(BUILDDIR)/*.o

cleandeps:
	$(RM) $(EXT_BUILDDIR)/*.o

remove:
	$(RM) $(TARGET)

.PHONY: all clean cleandeps remove builddirs test run
