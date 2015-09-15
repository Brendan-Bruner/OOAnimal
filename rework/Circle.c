
#include "Circle.h"
#include <stdio.h>

static void draw( Point_t self_ )
{
  struct Circle_t* self = (struct Circle_t*) self_;

  /* super version of draw. */
  ((struct Point_t*) self)->mySymbols_->draw( (struct Point_t*) self );
  printf( "Circle with radius (%d)\n", self->rad );
}

static void scale( Circle_t self_, int rad )
{
  struct Circle_t* self = (struct Circle_t*) self_;
  self->rad = rad;
}

static void destroy( Class_t self_ )
{
  (void) self_;
}

static struct Class_t class_ = { .destroy = destroy };
static struct CircleSymbolTable_t circle_ = { .circleClass = (Class_t) &class_,
					    .scale = scale,
					    .draw = draw };

Circle_t Circle = (Circle_t) &circle_;

Circle_t createCircle( struct Circle_t* self )
{
  createPoint((struct Point_t*) self);


  ((struct Point_t*) self)->symbolRef_.draw = draw;
  self->symbolRef_ = circle_;
  self->mySymbols_ = &circle_;

  self->rad = 0;

  return (Circle_t) self;
}
