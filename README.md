#CObject
---

CObject is a small set of macros and functions that enable fundamental object oriented concepts (OO) in the C language. Using C++ and Java terminology, CObject enables classes, abstract classes, single inheritance, interfaces, virtual methods, and pure virtual methods. In addition to supporting OO concepts, CObject was designed to use minimal boiler plate code and reveal as much of the implementation as possible. With a transparent implementation, CObject is easier to debug and more intuitive to develop with.

##Compile Time and Run Time Checks

Since C is not an OO language, compile time checks are very limited. For example, the compiler can't know if a class has forgot to implement a method inherited from an interface. To remedy this, run time checks are (optionally) done. When compiling, if the symbol DEBUG is defined, run time checking will be compiled into the program, otherwise, it isn't done. 

When a run time check fails, an error will be printed to console and the program execution halted. The printed message will explain the most likely cause of failure and common solutions. Since different systems have different requirements, hooks are provided to changed the behaviour when checks fail, and information is printed to console. For example, on an embedded system, the print hook can be used to power on an LED instead or print over a UART connection.

Some of the run time checks will catch the following errors:

* Passing in NULL pointers where a valid object is expected
* Failing to implement an inherited interface or pure virtual method

More information on this will be provided later.

##A Simple Class

A class must have a header and source file. For example, take a class Point. Point has two methods, draw and move, and two member variables, x and y location.

|Point 
---
|- x: int
|- y: int
|+ move( x: int, y: int ): void
|+ draw( ): void 

For now, lets treat move( ) and draw( ) as non virtual methods. 

###Header

```C
#ifndef POINT_H_
#define POINT_H_

#include <Class.h>

struct Point
{
    /* Super class. Must ALWAYS be first member of a class' struct. */
    struct CObject super;
    
    /* Member data. */
    int x;
    int y;
};

/* NOTE, class methods always take a pointer to themselves as their */
/* (preferably) first argument. */

/* Constructor. */
/* Note, struct name space is seperate from function name space. */
/* It is valid to have 'struct Point' and function 'Point( )'. */
extern void Point( struct Point* self, int x, int y );

/* move( ) method. */
extern void Point_Move( struct Point* self, int x, int y );

/* draw( ) method. */
extern void Point_Draw( struct Point* self );

#endif /* POINT_H_
```

On to the source file:

##Source

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
    CObject((struct CObject*) self);
    
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
    CMethod(self);
    
    self->x = x;
    self->y = y;
}

/* Point_Draw( ). */
void Point_Draw( struct Point* self )
{
    /* IMPORTANT */
    /* Must call this as first thing in any non virtual method. */
    /* It checks for a NULL object pointer. */
    CMethod(self);
    
    printf( "point at (%d,%d)\n", self->x, self->y );
}
```

###Creating an Instance of Point

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
    Point_Draw(heapPoint);   /* Print the points location to console. */
    Point_Move(heapPoint, 3, 2); /* Move the point to (3,2). */
    Point_Draw(heapPoint);   /* Print the points location to console. */
    CDestroy(heapPoint);     /* Call destructor on object, this will also free the memory. */
    
    return 1;
}
```

##Virtual and Pure Virtual Methods
---

To demonstrate virtual methods, lets take the class Point, and make ```Point_Draw( )``` virtual. In addition, lets add
a method, ```Point_Clone( )```, and make it pure virtual. As will become evident, there is no way to stop compilation when application code attempts to instantiate a class with a pure virtual method. This can only be caught at run time when the application calls the pure virtual method. 

###Header

```C
#ifndef POINT_H_
#define POINT_H_

#include <Class.h>

struct Point
{
    /* Super class. Must ALWAYS be first member of a class' struct. */
    struct CObject super;
    
    /* IMPORTANT */
    /* Virtual and pure virtual methods must be added as function pointers to the class' struct */
    /* definition. */
    
    /* Virtual method. */
    void (*PointVirtual_Draw)( struct Point* );
    /* Pure virtual method. */
    struct Point* (*PointVirtual_Clone)( struct Point* );
    
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

#endif /* POINT_H_
```
