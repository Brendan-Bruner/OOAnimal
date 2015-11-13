/*
 * Point.h
 *
 *  Created on: Nov 13, 2015
 *      Author: bbruner
 */

#ifndef POINT_H_
#define POINT_H_

#include "Class.h"

CLASS( Point_t )
	VIRTUAL
	(
		void (*draw)( self(Point_t) );
		void (*move)( self(Point_t), int, int );
	)
	int x;
	int y;
END_CLASS

void PointDraw( self(Point_t) );
void PointMove( self(Point_t), int, int );

Point_t* Point( self(Point_t), int, int );

#endif /* POINT_H_ */
