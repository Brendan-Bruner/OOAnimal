#ifndef POINT_H
#define POINT_H

#include "Class.h"

/*
 * Class Declare.
 */
CLASS
( 
 Point, EXTENDS( Object ),
 VIRTUAL(
	 void (*move)( Point*, int, int );
	 void (*draw)( Point* );
	),
 DATA(
      int x;
      int y;
     )
)

/*
 * Method declares.
 */
Point* newPoint( Point* );

#endif /* POINT_H */
