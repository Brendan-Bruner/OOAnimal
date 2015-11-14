/*
 * Circle.h
 *
 *  Created on: Nov 13, 2015
 *      Author: brendan
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <Class.h>
#include "Point.h"

CLASS( Circle_t EXTENDS Point_t )
	OVERRIDE
	(
		void (*draw)( self(Point_t) );
	)
	int radius;
END_CLASS

void Circle( self(Circle_t), int, int, int );


#endif /* CIRCLE_H_ */
