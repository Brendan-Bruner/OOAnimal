CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -pedantic -g -Os

# Build directory for executable
BUILDDIR := debug/main
# Name of binary executable
EXEC = main
# Path to all header files used
INCLUDES := -IClass -I. -Itests -Itests/test_classes
# Path to all source files used
SOURCES := $(shell echo tests/*.c) $(shell echo tests/**/*.c)
# All object files
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%.o))

# sources/includes/objects for static util lib
LIB_SRC := $(shell echo util/src/*.c) $(shell echo Class/*c)
LIB_INC := -I. -IClass
LIB_DIR := debug/lib
LIB_NAME := cutil
LIB_OBJ := $(addprefix $(LIB_DIR)/,$(LIB_SRC:%.c=%.o))

all : MKDIR $(OBJECTS) libutil
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BUILDDIR)/$(EXEC) $(LIB_DIR)/$(addprefix lib,$(LIB_NAME).a)

$(BUILDDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

MKDIR :
	mkdir -p $(addprefix $(BUILDDIR)/,$(SOURCES:%.c=%))

clean :
	rm -rf $(EXEC) $(BUILDDIR) $(LIB_DIR)

run:
	./$(BUILDDIR)/$(EXEC)

libutil : MKLIBDIR $(LIB_OBJ)
	$(AR) rcs $(LIB_DIR)/$(addprefix lib,$(LIB_NAME).a) $(LIB_OBJ)

MKLIBDIR :
	mkdir -p $(addprefix $(LIB_DIR)/,$(LIB_SRC:%.c=%))

$(LIB_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(LIB_INC) $< -o $@
