#ifndef POINT_H_
#define POINT_H_

#include <Class/Class.h>

struct Point
{
    /* IMPORTANT */
    /* Super class. Must ALWAYS be first member of a class' struct. */
    /* Since Point has no super class, we must make CObject its super. */
    struct CObject super;
    
    /* Member data. */
    int x;
    int y;
};

/* IMPORTANT */
/* class methods always take a pointer to themselves as their */
/* (preferably) first argument. */

/* IMPORTANT */
/* The constructor is just a regular C function. */
/* Constructor. */
extern void Point( struct Point* self, int x, int y );

/* move( ) method. */
extern void Point_Move( struct Point* self, int x, int y );

/* draw( ) method. */
extern void Point_Draw( struct Point* self );

#endif /* POINT_H_ */