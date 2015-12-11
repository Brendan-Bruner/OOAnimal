#Inheritance and Implementing Pure Virtual Methods
---

Continuing the example from the last section, we will create a Square class which inherits from point. It will provide a new method, Square_Scale( ), and implement the pure virtual method, Point_Clone( ).

![](https://raw.githubusercontent.com/Brendan-Bruner/CObject/docs/Inheritance.jpg)

###Header

```C
#ifndef SQUARE_H_
#define SQUARE_H_

#include <Point.h>

struct Square
{
	/* IMPORTANT */
	/* Super class must be first variable in struct. */
	/* Since we are inheriting from Point, we make this */
	/* an instance of struct Point. */
	struct Point super;

	/* Member variables. */
	int length;
}

/* Constructor. */
extern struct Square* Square( struct Square* self, int x, int y, int length );

/* Non virtual method, Square_Scale( ). */
extern void Square_Scale( struct Square* self, int factor );

#endif /* SQUARE_H_ */
```

###Source

```C
#include <Square.h>

/* Implementation declare for Point_Clone( ). */
static struct Point* PointPureVirtual_Clone( struct Point* );

/* Constructor. */
struct Square* Square( struct Square* self, int x, int y, int length )
{
	/* Like before, CConstructor( ) must be first operation. */
	CConstructor(self);

	/* Like before, must call super class' constructor. */
	Point(&self->super, x, y);

	/* IMPORTANT */
	/* The super classes constructor must be called before linking the */
	/* implementation of Point_Clone( ). */

	/* IMPORTANT */
	/* Link the pure virtual method implementation. */
	/* The first argument is the path to the function */
	/* pointer that is documented as pure virtual. */
	/* The second argument is the name of the function pointer. */
	/* This resolves to exactly: */
	/* 			&self->super.PointPureVirtual_Clone = PointPureVirtual_Clone; */
	/* After doing this, the assert discussed in the last section will stop failing. */
	/* When someone calls Point_Clone( ), the assert passes, then this */
	/* method gets called. */
	CLinkMethod(&self->super, PointPureVirtual_Clone);

	return self;
}

static struct Point* PointPureVirtual_Clone( struct Point* self_ )
{
	/* IMPORTANT */
	/* Must always call this as the first operation in any virtual method. It does some */
	/* run time checking and casts the input pointer to a pointer of the implementing */ 
	/* class. It will safetly cast the pointer to a struct Point to a pointer to a */
	/* struct Square. Even though its safe to cast a pointer to any of its super */
	/* classes, the reverse should be avoided. When we discuss interfaces, the reverse. */
	/* is never true. */
	struct Square* self = CCast(self_);

	/* Start making the clone */
	struct Square* clone = malloc(sizeof(struct Square));
	if( clone == NULL )
	    return NULL;

	/* Construct the allocated memory for a clone. */
	if( Square(clone, self->super.x, self->super.y, self->length) == NULL ) {
		free(clone);
		return NULL;
	}

	/* Flag the clone as being dynamically allocated. */
	CDynamic(clone);

	/* Return the clone. Recalling it is always safe to cast a pointer to any */
	/* of its super classes. */
	return ((struct Point*) self);
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

int main( int argv, char** argc )
{
	struct Square square;

	Square(&square, 0, 0, 5); /* Make a square at (0,0) with sides of lenght 5. */
	Point_Draw((struct Point*) &square); /* Will print to console the squares */
	                                     /* location, that is, (0,0). */
    Point_Move((struct Point*) &square, 3, 3); /* Move the point to (3,3). */
    Point_Draw((struct Point*) &square); /* Will print to console the squares */
	                                     /* location, that is, (3,3). */    
        /* Clone will make an exact copy of square, and return it */
    struct Point* clone = Point_Clone((struct Point*) &square);
    Point_Draw(clone); /* Will print the clones location to console, that is, (3,3). */
    CDestroy(clone);

    Square_Scale(&square, 2); /* Double the length of the squares sides. */
    CDestroy(&square);
}

```