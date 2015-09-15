#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

typedef void* Circle_t;
extern Circle_t Circle;

struct CircleSymbolTable_t
{
  Class_t circleClass;
  void (*draw)( Point_t );
  void (*scale)( Circle_t, int );
};

struct Circle_t
{
  struct Point_t super;
  struct CircleSymbolTable_t symbolRef_;
  struct CircleSymbolTable_t* mySymbols_;

  int rad;
};

Circle_t createCircle( struct Circle_t* );

#endif /* CIRCLE_H */
