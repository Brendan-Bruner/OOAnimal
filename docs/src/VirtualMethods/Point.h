#ifndef POINT_H_
#define POINT_H_

#include <Class/Class.h>

struct Point
{
    /* Super class. Must ALWAYS be first member of a class' struct. */
    struct CObject super;
    
    /* IMPORTANT */
    /* Virtual and pure virtual methods must be added as function pointers to the class' struct */
    /* definition. Notice, the only different between virtual and pure virtual is the comments */
    /* describing them. ie, there is only a semantical difference. */
    /* Virtual method. */
    void (*PointVirtual_Draw)( struct Point* );
    /* Pure virtual method. */
    struct Point* (*PointPureVirtual_Clone)( struct Point* );
    
    /* Member data. */
    int x;
    int y;
};

/* Constructor. */
extern void Point( struct Point* self, int x, int y );

/* move( ) method. */
extern void Point_Move( struct Point* self, int x, int y );

/* IMPORTANT */
/* Even though the draw and clone methods are added as function pointers to the class' */
/* struct definition, they still require a method definition. */

/* clone( ) method. */
extern struct Point* Point_Clone( struct Point* self );

/* draw( ) method. */
extern void Point_Draw( struct Point* self );

#endif /* POINT_H_ */