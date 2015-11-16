CC = gcc
CFLAGS = -Wall -Wextra

# Build directory
BUILDDIR := Debug
SOURCEDIR := ./

# Path to all header files used
INCLUDES := -IClass -Iunit -I.
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))

EXEC = bin

all : MKDIR $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

$(BUILDDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

MKDIR :
	mkdir -p $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%))

clean :
	rm -rf $(EXEC) $(BUILDDIR)
