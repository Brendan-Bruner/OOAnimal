#Overriding
---

In this section, we're going to continue with the Square class by overriding the super class' method, Point_Draw( ). Overriding has two implications.

* The method implemented by the super class is changed to a new implementation by the sub class
* The super class' implementation can still be called, but only within the overriding sub class. 

Both these concepts will be demonstrated by overriding the original Point_Draw( ), and calling the original Point_Draw( ) in the new implementation.

![](https://raw.githubusercontent.com/Brendan-Bruner/CObject/docs/Inheritance.jpg)

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
	/* We are overriding the method Point_Draw( ). In order to */
	/* keep a reference to the original implementation, we need */
	/* a method pointer here to save that reference. */
	/* The method pointer must have the same name and signature as */
	/* the method being overrode. */
	void (*PointVirtual_Draw)( struct Point* );


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

/* Implementation declare for Point_Clone( ). */
static struct Point* PointPureVirtual_Clone( struct Point* );
static void PointVirtual_Draw( struct Point* );

/* Constructor. */
struct Square* Square( struct Square* self, int x, int y, int length )
{
	/* Like before, CConstructor( ) must be first operation. */
	CConstructor(self);

	/* Like before, must call super class' constructor. */
	Point(&self->super, x, y);

	/* Link the pure virtual method implementation. */
	CLinkVirtual(&self->super, PointPureVirtual_Clone);

	/* IMPORTANT */
	/* Must always call the super class constructor before overriding */
	/* a method. */
	/* The first argument is a pointer to the object being constructed. */
	/* The second argument is a pointer to the super class where the */
	/* method being overrode is defined. */
	/* The last argument is the name of method pointer being overrode. */
	/* This resolves to exactly: */
	/* 		self->PointVirtual_Draw = (&self->super)->PointVirtual_Draw; */
	/*		(&self->super)->PointVirtual_Draw = PointVirtual_Draw; */
	/* The first line saves a reference to the previous implementation. */
	/* The second line overrides the old implementation with the new implementation. */
	COverrideVirtual(self, &self->super, PointVirtual_Draw);

	/* Set up member variables. */
	self->length = length;

	return self;
}

static void PointVirtual_Draw( struct Point* self_ )
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
	CAssertSuper(self, PointVirtual_Draw);
	self->PointVirtual_Draw(&self->super);

	/* The above code will come out on the console like: */
	/* 		Square of length: 5 						*/
	/*		with top left point at (3,3)				*/
}

static struct Point* PointPureVirtual_Clone( struct Point* self_ )
{
	/* Must always call this as the first operation in any virtual method. */
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
    (void)argv; (void)argc;
    struct Square square;

    Square(&square, 0, 0, 5); /* Make a square at (0,0) with sides of lenght 5. */
    Point_Draw((struct Point*) &square); /* Will print to console the squares */
                                         /* location, that is, (0,0). */
                                         /* AND it's length, 5. */
    Point_Move((struct Point*) &square, 3, 3); /* Move the point to (3,3). */
    Point_Draw((struct Point*) &square); /* Will print to console the squares */
                                         /* location, that is, (3,3). */    
                                         /* AND its length, 5 */
        /* Clone will make an exact copy of square, and return it */
    struct Point* clone = Point_Clone((struct Point*) &square);
    Point_Draw(clone); /* Will print the clones location to console, that is, (3,3). */
    CDestroy(clone);

    Square_Scale(&square, 2); /* Double the length of the squares sides. */
    Point_Draw((struct Point*) &square); /* Will print the location, (3,3) and */
                                         /* the new length, 10. */
    CDestroy(&square);
}
```

### Compiling

Assuming a directory structures like this:

./
<br>|-> Class
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.h
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.c
<br>|-> Square.h
<br>|-> Square.c
<br>|-> Point.h
<br>|-> Point.c
<br>|-> main.c

```
gcc -I. -DDEBUG -Wall Class/Class.c Point.c Square.c main.c -o main
./main
```