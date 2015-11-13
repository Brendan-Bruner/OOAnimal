/*
 * Point.c
 *
 *  Created on: Nov 13, 2015
 *      Author: bbruner
 */

#include "Point.h"
#include <stdio.h>

void PointDraw( self(Point_t) )
{
	VIRTUAL_METHOD( Point_t, draw )( self );
}
static void draw( self(Point_t) )
{
	MEMBER_OF(Point_t);
	printf( "Point at (%d, %d)\n", self->x, self->y );
}

void PointMove( self(Point_t), int x, int y )
{
	MEMBER_OF(Point_t);
	self->x = x;
	self->y = y;
}


Point_t* Point( self(Point_t), int x, int y )
{
	CONSTRUCTOR_OF(Point_t);
	LINK_VIRTUAL_METHOD( draw );
	self->x = x;
	self->y = y;
	return self;
}
