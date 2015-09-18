
#include "Circle.h"
#include <stdio.h>

static void draw( Point_t self_ )
{
  struct Circle_t* self = (struct Circle_t*) self_;

  /* super version of draw. */
  ((struct Point_t*) self)->staticTable_->draw( (struct Point_t*) self );
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
static struct CircleVirtualTable_t const circle_ = { .class = (Class_t) &class_,
					    .scale = scale,
					    .draw = draw };

Circle_t Circle( struct Circle_t* self )
{
  Point((struct Point_t*) self);


  ((struct Point_t*) self)->virtualTable_.draw = draw;
  self->virtualTable_ = circle_;
  self->circleTable_ = &circle_;

  self->rad = 0;

  return (Circle_t) self;
}

void CircleScale( Circle_t self_, int rad )
{
  struct Circle_t* self = (struct Circle_t*) self_;
  self->virtualTable_.scale( self, rad );
}
