CC = gcc
CFLAGS = -Wall -Wextra -pedantic

CLASS_SRC = ../../Class/*.c
COREOBJ = obj/
COREMAIN = main/
COREDIR = animal/ bird/ cat/ crow/ ./
INCLUDES = ../../Class

SRCNAME = Animal.c Bird.c Cat.c Crow.c main.c 
OBJNAME = $(SRCNAME:.c=.o)

# Path to the source files and object files
SRCDIR = $(addprefix $(COREMAIN),$(COREDIR))
OBJDIR = $(addprefix $(COREOBJ),$(COREDIR))

# Path to all header files used
INC = -I../../Class $(addprefix -I,$(SRCDIR))

# Each object file in a space sperated list
# ie: obj/animal/Animal.o obj/bird/bird.o ...
OBJECTS = $(join $(OBJDIR),$(OBJNAME))

EXEC = OOAnimal

all : MKDIR $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CLASS_SRC) -o $(EXEC)

$(addprefix $(COREOBJ),%.o) : $(addprefix $(COREMAIN),%.c)
	$(CC) $(CFLAGS) -c $(INC) $< -o $@

MKDIR :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(COREOBJ) $(EXEC)
