#ifndef SQUARE_H_
#define SQUARE_H_

#include <Point.h>

struct Square
{
	/* Super class must be first variable in struct. */
	struct Point super;

	/* Member variables. */
	int length;
};

/* Constructor. */
extern struct Square* Square( struct Square* self, int x, int y, int length );

/* Non virtual method, Square_Scale( ). */
extern void Square_Scale( struct Square* self, int factor );

#endif /* SQUARE_H_ */