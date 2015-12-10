CC := gcc # compiler 
LD := gcc # linker
CFLAGS := -Wall -Wextra -pedantic
LFLAGS := -Wall -Wextra -pedantic

# Symbols
SYMBOLS := -DDEBUG 

# Build directory
BUILDDIR := debug
# Name of binary executable
EXEC = bin
# Source directory start
SOURCEDIR := ./
# Path to all header files used
INCLUDES := -I../Class -I../unit -ITests -I.

# Path to all source files used
SOURCES := $(shell find $(SOURCEDIR) -name '*.c' )
# Name and location for all object files
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))

all : MKDIR CLASS $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS) $(BUILDDIR)/Class.o -o $(EXEC)

$(BUILDDIR)/%.o : %.c
	$(CC) $(CFLAGS) $(SYMBOLS) $(INCLUDES) -c $< -o $@

MKDIR :
	mkdir -p $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%))

CLASS:
	$(CC) $(CFLAGS) $(SYMBOLS) -c ../Class/Class.c -o $(BUILDDIR)/Class.o

clean :
	rm -rf $(EXEC) $(BUILDDIR)
