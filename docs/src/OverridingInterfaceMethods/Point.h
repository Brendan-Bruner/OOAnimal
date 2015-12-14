#ifndef POINT_H_
#define POINT_H_

#include <Class/Class.h>
#include <Printable.h>

struct Point
{
    /* Super class. First member as usual. */
    struct CObject super;
    
    /* IMPORTANT */
    /* Interfaces being implemented are added as struct members. */
    struct Printable printable;

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

#endif /* POINT_H_ */