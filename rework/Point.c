#include "Point.h"
#include <stdio.h>

static void move( Point_t self_, int x, int y )
{
  struct Point_t* self = (struct Point_t*) self_;

  self->x = x;
  self->y = y;
}

static void draw( Point_t self_ )
{
  struct Point_t* self = (struct Point_t*) self_;

  printf( "Point (%d,%d)\n", self->x, self->y );
}

static void destroy( Class_t self_ )
{
  (void) self_;
}

static struct Class_t class_ = { .destroy = destroy };
static struct PointSymbolTable_t point_ = { .pointClass = (Class_t) &class_,
					    .move = move,
					    .draw = draw };

Point_t Point = (Point_t) &point_;

Point_t createPoint( struct Point_t* self )
{
  self->symbolRef_ = point_;
  self->mySymbols_ = &point_;

  self->x = 0;
  self->y = 0;

  return (Point_t) self;
}
