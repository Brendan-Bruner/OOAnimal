CC := gcc
CFLAGS := -Wall -Wextra

# Build directory
BUILDDIR := Debug
# Name of binary executable
EXEC = bin
# Source directory start
SOURCEDIR := ./
# Path to all header files used
INCLUDES := -IClass -Iunit -ITests -IUtil -I.

# Path to all source files used
SOURCES := $(shell find $(SOURCEDIR) -name '*.c' ! -wholename '*/Tutorials/**.c' )
# Name and location for all object files
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))

all : MKDIR $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

$(BUILDDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

MKDIR :
	mkdir -p $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%))

clean :
	rm -rf $(EXEC) $(BUILDDIR)
