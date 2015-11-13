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

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	Point_t* point = createNew( Point_t, Point )( point, 1, 2 );
	PointDraw( point );
	PointMove( point, 54, 23 );
	PointDraw( point );

	//point->_co->_vt.virtualDestroy( point );

	destroy( point );

	return EXIT_SUCCESS;
}
