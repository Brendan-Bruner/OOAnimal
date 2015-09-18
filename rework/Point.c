#include "Point.h"
#include <stdio.h>

static void move( Point* self_, int x, int y )
{
  MEMBER_OF( Point );

  self->x = x;
  self->y = y;
}

static void draw( Point* self_ )
{
  MEMBER_OF( Point );

  printf( "Point (%d,%d)\n", self->x, self->y );
}

static void destroy( Class_t self_ )
{
  (void) self_;
}

static struct Class_t class_ = { .destroy = destroy };
static struct _PointVirtualTable_t const point_ = { .CLASS_CLASS_NAME = (Class_t) &class_,
					    .move = move,
					    .draw = draw };

Point* newPoint( Point* self_ )
{
  MEMBER_OF( Point );
  self->OBJECT_VIRTUAL_TABLE_NAME = point_;
  self->CLASS_VIRTUAL_TABLE_NAME = &point_;

  self->x = 0;
  self->y = 0;

  return (Point_t*) self;
}

