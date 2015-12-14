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