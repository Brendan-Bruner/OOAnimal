#ifndef POINT_H
#define POINT_H

#include "Class.h"



typedef void* Point_t;
extern Point_t Point;

struct PointSymbolTable_t
{
  Class_t pointClass;
  void (*move)( Point_t, int, int );
  void (*draw)( Point_t );
};

struct Point_t
{
  struct PointSymbolTable_t symbolRef_;
  struct PointSymbolTable_t* mySymbols_;

  int x;
  int y;
};

Point_t createPoint( struct Point_t* self );

#endif /* POINT_H */
