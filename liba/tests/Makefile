CC := gcc
AR := ar
CFLAGS := -Wall -Wextra -pedantic -g -Os

# sources/includes/objects for static util lib
LIB_SRC := $(shell echo ./*.c) $(shell echo ./**/*.c)
LIB_INC := -I. -I../Class -I../util
LIB_DIR := debug
LIB_NAME := ctests
LIB_OBJ := $(addprefix $(LIB_DIR)/,$(LIB_SRC:%.c=%.o))

clean :
	rm -rf $(LIB_DIR)

rmbackup:
	rm -f ./*~ ./**/*~

all : MKDIR $(LIB_OBJ)
	$(AR) rcs $(LIB_DIR)/$(addprefix lib,$(LIB_NAME).a) $(LIB_OBJ)

MKDIR :
	mkdir -p $(addprefix $(LIB_DIR)/,$(LIB_SRC:%.c=%))

$(LIB_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $(LIB_INC) $< -o $@
