#include <Point.h>
#include <stdio.h>

/* Constructor. */
void Point( struct Point* self, int x, int y )
{
    /* IMPORTANT */
    /* Must always call generic constructor as FIRST operation in any class' constructor. */
    /* This initializes object data and, if DEBUG is defined, sets up object data to */
    /* catch errors at run time. */
    CConstructor(self);
    
    /* IMPORTANT */
    /* Must call super classes constructor at some point. */
    /* Alternatively, it is always safe to cast an object to a pointer to */
    /* its super class: */
    /*     CObject((struct CObject*) self); */
    /* is valid too. */
    CObject(&self->super); 
    
    /* Set up member data. */
    self->x = x;
    self->y = y;
}

/* Point_Move( ). */
void Point_Move( struct Point* self, int x, int y )
{
    /* IMPORTANT */
    /* Must call this as first thing in any non virtual method. */
    /* It checks for a NULL object pointer. */
    CAssertObject(self);
    
    self->x = x;
    self->y = y;
}

/* Point_Draw( ). */
void Point_Draw( struct Point* self )
{
    /* IMPORTANT */
    /* Must call this as first thing in any non virtual method. */
    /* It checks for a NULL object pointer. */
    CAssertObject(self);
    
    printf( "point at (%d,%d)\n", self->x, self->y );
}