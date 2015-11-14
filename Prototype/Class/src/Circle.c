/*
 * Circle.c
 *
 *  Created on: Nov 13, 2015
 *      Author: brendan
 */

#include "Circle.h"

static void draw( self(Point_t) )
{
	MEMBER_OF(Circle_t);

	SUPER( )->draw( (Point_t*) self );
	printf( "radius is: %d\n", self->radius );
}

void Circle( self(Circle_t), int x, int y, int radius )
{
	CONSTRUCTOR_OF(Circle_t);
	Point( (Point_t*) self, x, y );
	OVERRIDE_VIRTUAL_METHOD( Point_t, draw );

	self->radius = radius;
}
