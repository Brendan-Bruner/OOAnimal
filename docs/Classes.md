#Classes
---

A class must have a header and source file. For example, take a class Point. Point has two methods, draw and move, and two member variables, x and y location.

![](https://raw.githubusercontent.com/bandren/CObject/master/docs/Classes.jpg)

For now, lets treat move( ) and draw( ) as non virtual methods. Important points will be labelled with ```/* IMPORTANT */```.

###Header

```C
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

#endif /* POINT_H_
```

On to the source file:

###Source

```C
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
```

###Main

```C
#include <Point.h>

int main( int argc, char** argv )
{
    struct Point stackPoint;
    struct Point* heapPoint;
    
    /* We will work with two instances of Point, one on the function's stack, */
    /* the other put on heap with malloc. */
    
    /* First, the stack point. */
    Point(&stackPoint, 0, 0); /* Create the point, and put it at (0,0). */
    Point_Draw(&stackPoint);  /* Print the point's location to console. */
    Point_Move(&stackPoint, 3, 2); /* Move the point to (3,2). */
    Point_Draw(&stackPoint);  /* Print the points new location to console. */
    CDestroy(&stackPoint);    /* Call destructor on the object. */
    
    /* Next, the heap point. */
    heapPoint = malloc(sizeof(*heapPoint));
    if( heapPoint == NULL )
        return 0;
    Point(heapPoint, 0, 0);  /* Create the point, and put it at (0,0). */
    CDynamic(heapPoint);     /* Declare the object as being dynamically allocated. */
                             /* This must never precede the constructor. */
    Point_Draw(heapPoint);   /* Print the points location to console. */
    Point_Move(heapPoint, 3, 2); /* Move the point to (3,2). */
    Point_Draw(heapPoint);   /* Print the points location to console. */
    CDestroy(heapPoint);     /* Call destructor on object, this will also free the memory. */
    
    return 1;
}
```

###Compiling

Assuming a directory structures like this:

./
<br>|-> Class
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.h
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.c
<br>|-> Point.h
<br>|-> Point.c
<br>|-> main.c

```
gcc -I. -DDEBUG -Wall Class/Class.c Point.c main.c -o main
./main
```
