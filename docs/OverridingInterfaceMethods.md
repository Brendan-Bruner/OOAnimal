#Overriding and Overwriting Interface Methods
---

This is done in the exact same way it was done with virtual methods. Continueing from last time, [Interfaces](https://github.com/bandren/CObject/blob/master/docs/Interfaces.md), we will rewrite the Square class to override Printable_Print( ). Overwriting won't be explicitly shown since it follows almost the same procedure as overriding.

It will be revealed here, using interfaces comes at a cost:

* The application developer must be away of class hierchy. Using Java as an example, the developer must know the ```add( )``` method he uses on an ArrayList object is inherited from the List interface. 

###Header

```C
#ifndef SQUARE_H_
#define SQUARE_H_

#include <Point.h>

struct Square
{
	/* Super class must be first variable in struct. */
	struct Point super;

	/* IMPORTANT */
	/* We are overriding the method Printable_Print( ). In order to */
	/* keep a reference to the original implementation, we need */
	/* a method pointer here to save that reference. */
	/* The method pointer must have the same name and signature as */
	/* the method being overrode. */
	void (*PrintableVirtual_Print)( struct Printable* );


	/* Member variables. */
	int length;
};

/* Constructor. */
extern struct Square* Square( struct Square* self, int x, int y, int length );

/* Non virtual method, Square_Scale( ). */
extern void Square_Scale( struct Square* self, int factor );

#endif /* SQUARE_H_ */
```

###Source
 
```C
#include <Square.h>

static void PrintableVirtual_Print( struct Printable* );

/* Constructor. */
struct Square* Square( struct Square* self, int x, int y, int length )
{
	/* Like before, CConstructor( ) must be first operation. */
	CConstructor(self);
	/* Like before, must call super class' constructor. */
	Point(&self->super, x, y);

	/* IMPORTANT */
	/* Must always call the super class constructor before overriding */
	/* a method. */
	/* The first argument is a pointer to the object being constructed. */
	/* The second argument is a pointer to the struct where the */
	/* method being overrode is defined. */
	/* The last argument is the name of method pointer being overrode. */
	/* This resolves to exactly: */
	COverrideVirtual(self, &self->super.printable, PrintableVirtual_Print);

	/* Set up member variables. */
	self->length = length;

	return self;
}

static void PrintableVirtual_Print( struct Printable* self_ )
{
	/* Must always call this as the first operation in any virtual method. */
	struct Square* self = CCast(self_);

	/* Print the squares length. */
	printf("Square of length: %d\n", self->length);

	/* IMPORTANT */
	/* Here, we are going to use the super's method to print the square's location */
	/* instead of rewriting the same code. */
	/* Before calling a super method, we must always assert it has been linked. */
	/* Then, it is safe to call. */
	printf( "with top left " ); 
	CAssertSuper(self, PrintableVirtual_Print);
	self->PrintableVirtual_Print(&self->super.printable);

	/* The above code will come out on the console like: */
	/* 		Square of length: 5 						*/
	/*		with top left point at (3,3)				*/
}

/* The new scale method. */
void Square_Scale( struct Square* self, int factor )
{
	/* As usual, assert for NULL input. */
	CAssertObject(self);

	/* Interesting note, what if factor was MIN_INT? Because, */
	/* -MIN_INT = MAX_INT+1 due to two's complement. */
	if( factor < 0 )
	    self->length = self->length / -factor;
	else
	    self->length = self->length * factor;
}
```

###Main

```C
#include <Square.h>

int main( int argc, char** argv )
{
    (void)argc; (void)argv;
    struct Square square;

    /* Create the square. */
    Square(&square, 0, 0, 10); 

    /* Print the square's location and length. */
    Printable_Print(&square.super.printable);  

    /* Move the square to (3,2) and reduce side length by 50%. */
    Point_Move(&square.super, 3, 2);
    Square_Scale(&square, -2);
    
    /* Print the square's new parameters. */
    Printable_Print(&square.super.printable);  
    
    CDestroy(&square);  

    return 1;
}
```

### Compiling

Assuming a directory structures like this:

./
<br>|-> Class
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.h
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.c
<br>|-> Printable.h
<br>|-> Square.h
<br>|-> Square.c
<br>|-> Point.h
<br>|-> Point.c
<br>|-> main.c

```
gcc -I. -DDEBUG -Wall Class/Class.c Point.c Square.c main.c -o main
./main
```
