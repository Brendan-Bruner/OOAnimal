#This is a makefile for Blink.c
#Use "make all" to compile and link
#Use "make run" to run the exectuable (after make all)
#Use "make clean" to delete object files and executable

# General Options
PROG=OOAnimal
SOURCES=main.c Animal.c Cat.c Bird.c Crow.c
OBJECTS=main.o Animal.o Cat.o Bird.o Crow.o

# Compiler and Linker options
GCC=gcc
CFLAGS=-Os -Wall
LFLAGS=-Wall

all:$(OBJECTS)
	$(GCC) $(LFLAGS) $(OBJECTS) -o $(PROG)

$(OBJECTS):$(SOURCES)
	$(GCC) $(CFLAGS) -c $(SOURCES)

run:
	./$(PROG)

clean:
	rm $(OBJECTS) $(PROG)
