CC := gcc
AR := ar

CFLAGS := -Wall -Wextra -pedantic -g -Os

# Build directory for executable
BUILDDIR := debug

# Name of binary executable
EXEC = main

# Path to all header files used
INCLUDES := -I../CObject -I../tests

# Path to all source files used
SOURCES := main.c

# All object files
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))

# All libraries
STATIC_LIB_SRC := ../CObject ../tests
STATIC_LIB_NAME := ctests cclass

STATIC_LIBS := $(addprefix -l,$(STATIC_LIB_NAME));
STATIC_LIB_BUILD := $(addsuffix /debug,$(addprefix -L,$(STATIC_LIB_SRC)))

all : MKDIR BUILD_LIBS $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BUILDDIR)/$(EXEC) $(STATIC_LIB_BUILD) $(STATIC_LIBS)
	cp $(BUILDDIR)/$(EXEC) ./

$(BUILDDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

BUILD_LIBS :
	make -C ../tests/ all
	make -C ../CObject all

MKDIR :
	mkdir -p $(dir $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%)))

clean :
	rm -rf $(BUILDDIR)
	make -C ../tests/ clean
	make -C ../CObject clean


run:
	./$(BUILDDIR)/$(EXEC)

crun: clean all run
