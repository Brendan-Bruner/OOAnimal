CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -pedantic -g -Os

# sources/includes/objects for static util lib
LIB_SRC := $(shell echo src/*.c)
LIB_INC := -I. -I../Class
LIB_DIR := debug
LIB_NAME := cutil
LIB_OBJ := $(addprefix $(LIB_DIR)/,$(LIB_SRC:%.c=%.o))

clean :
	rm -rf $(LIB_DIR)

rmbackup :
	rm -f *~ **/*~

all : MKDIR $(LIB_OBJ)
	$(AR) rcs $(LIB_DIR)/$(addprefix lib,$(LIB_NAME).a) $(LIB_OBJ)

MKDIR :
	mkdir -p $(dir $(addprefix $(LIB_DIR)/,$(LIB_SRC:%.c=%)))

$(LIB_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(LIB_INC) $< -o $@

syntax :
	$(CC) -fsyntax-only -c $(LIB_SRC)  $(LIB_INC)
