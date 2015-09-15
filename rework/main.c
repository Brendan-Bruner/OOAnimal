#include "Circle.h"
//#include "Point.h"
#include <stdio.h>

int main( int argc, char **argv )
{
  struct Point_t mem;
  struct Point_t* point;
  struct Circle_t cmem;
  struct Circle_t* circle;

  circle = (struct Circle_t*) createCircle( &cmem );
  point = (struct Point_t*) createPoint( &mem );

  point->symbolRef_.move( point, 3, 4 );
  point->symbolRef_.draw( point );

  ((struct Point_t*) circle)->symbolRef_.move( (struct Point_t*) circle, 10, 11 );  
  circle->symbolRef_.scale( circle, 5 );
  ((struct Point_t*) circle)->symbolRef_.draw( (struct Point_t*) circle );

  return 0;
}
