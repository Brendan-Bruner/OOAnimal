CC = gcc

# Path to object directories / files
COREOBJ = obj/
# Path to the start of all source files
COREMAIN = main/

# Path to all header files used
INC = -I../../Class -Imain/Classes/include -Imain/Traits

OBJDIR = obj/Classes/
OBJ = Dragon.o FlameGuard.o Whelp.o FireElement.o FlameLord.o LivingFlameThrower.o
OBJECTS = $(addprefix $(OBJDIR),$(OBJ)) obj/main.o

EXEC = OODragon

all : MKDIR $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

$(addprefix $(COREOBJ),%.o) : $(addprefix $(COREMAIN),%.c)
	$(CC) -Wall -c $(INC) $< -o $@

MKDIR :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(COREOBJ) $(EXEC)
