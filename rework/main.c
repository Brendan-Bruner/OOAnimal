//#include "Circle.h"
#include "Point.h"
#include <stdio.h>

int main( int argc, char **argv )
{
  Point pmem, *point;
  //struct Circle_t cmem;
  //  Circle_t circle;

  //  circle = Circle( &cmem );
  point = newPoint( &pmem );

  class( Point, point )->move( point, 3, 4 );
  class( Point, point )->draw( point );

  //  PointMove( (Point_t) circle, 10, 11 );  
  //  CircleScale( circle, 5 );
  //  PointDraw( (Point_t) circle );

  return 0;
}
