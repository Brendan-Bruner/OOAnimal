/*
 ============================================================================
 Name        : Prototype.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Point.h"
#include "Circle.h"

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	Point_t* point1 = createNew( point1, Point( point1, 1, 2 ) );
	PointDraw( point1 );
	PointMove( point1, 54, 23 );
	PointDraw( point1 );
	destroy( point1 );

	Circle_t* circle = createNew( circle, Circle( circle, 4, 4, 9 ) );
	PointDraw( (Point_t*) circle );
	PointMove( (Point_t*) circle, 54, 23 );
	PointDraw( (Point_t*) circle );
	destroy( circle );

	return EXIT_SUCCESS;
}
