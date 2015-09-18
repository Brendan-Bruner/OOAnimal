#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

typedef void* Circle_t;

struct CircleVirtualTable_t
{
  Class_t class;
  void (*draw)( Point_t );
  void (*scale)( Circle_t, int );
};

struct Circle_t
{
  struct Point_t super;
  struct CircleVirtualTable_t virtualTable_;
  struct CircleVirtualTable_t const* circleTable_;

  int rad;
};

void CircleScale( Circle_t, int );
Circle_t Circle( struct Circle_t* self );

#endif /* CIRCLE_H */
