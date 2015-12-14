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