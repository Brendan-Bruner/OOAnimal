#all:
#	$(CC) -std:=c99 -Wall -Wextra -pedantic -I../Class -I./test_classes -I. ../Class/Class.c ./*.c ./**/*.c -o main



CC := gcc
CFLAGS := -Wall -Wextra -pedantic -g

# Build directory
BUILDDIR := debug
# Name of binary executable
EXEC = main
# Source directory start
SOURCEDIR := ./
# Path to all header files used
INCLUDES := -IClass -I. -Itests -Itests/test_classes

# Path to all source files used
# use ' ! -wholename '*/Tutorials/**.c' )' to exclude files
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
# Name and location for all object files
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))

all : MKDIR $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BUILDDIR)/$(EXEC)

$(BUILDDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

MKDIR :
	mkdir -p $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%))

clean :
	rm -rf $(EXEC) $(BUILDDIR)

run:
	./$(BUILDDIR)/$(EXEC)
