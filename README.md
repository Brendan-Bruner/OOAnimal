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

###Source

```C
#include <Point.h>
#include <stdio.h>

static void PointVirtual_Draw( struct Point* );

/* Constructor. */
void Point( struct Point* self, int x, int y )
{
    /* Must always call generic constructor as FIRST operation in any class' constructor. */
    CConstructor(self);
    /* Must call super classes constructor at some point. */
    CObject((struct CObject*) self);
    
    /* IMPORTANT */
    /* Virtual methods must be manually linked in the constructor. */
    /* This is a helper macro do that. It resolves to exactly: */
    /*      self->PointVirtual_Draw = PointVirtual_Draw; */
    /* If you forget to do this, run time checking will notify you the first */
    /* time the unlinked virtual method is called. */
    CLinkVirtual(self, PointVirtual_Draw);
    
    /* IMPORTANT */
    /* We do not link the PointVirtual_Clone method because we want it to be pure virtual. */
    /* Since this is C, the compiler will not complain when an instance of struct Point is */
    /* created. This will be caught by run time checks, when the application code calls */
    /* Point_Clone( ) on an instance of Point. See Point_Clone( ) below for more. */
    
    /* Set up member data. */
    self->x = x;
    self->y = y;
}

/* Point_Move( ). */
void Point_Move( struct Point* self, int x, int y )
{
    CMethod(self);
    
    self->x = x;
    self->y = y;
}

/* IMPORTANT */
/* Virtual methods have two functions. The first is a public wrapper method to call the */
/* the virtual function, 'Point_Draw( )' is the wrapper. The next is a private implementation of the */
/* virtual method, 'static PointVirtual_Draw( )'. */
/* Point_Draw( ) public wrapper function. */
void Point_Draw( struct Point* self )
{
    /* IMPORTANT */
    /* Must call this as first thing in any virtual method wrapper. */
    /* It checks for a NULL object pointer and and unlinked virtual method. */
    /* ie, if the the programmer forgot to link this method in the constructor, */
    /* then this assert will fail. */
    CAssertVirtual(self, PointVirtual_Draw);
    
    /* IMPORTANT */
    /* Must then call the virtual method using the function pointer. */
    self->PointVirtual_Draw(self);
}
/* Point_Draw( ) private implementation. */
static void PointVirtual_Draw( struct Point* self_ )
{
    /* IMPORTANT */
    /* Must always call this as the first operation in any virtual method. It does some */
    /* run time checking and casts the input pointer to a pointer of the implementing class. */
    /* More on why casting is important in the section on inheritance, overriding, and overwriting. */
    struct Point* self = CCast(self_);
    
    printf( "point at (%d,%d)\n", self->x, self->y );
}

/* IMPORTANT */
/* Pure virtual methods have only the public wrapper method. An implementation has to be written */
/* and linked in the an inheriting  class. */
/* Point_Clone( ) wrapper method. */
struct Point* Point_Clone( struct Point* )
{
    /* IMPORTANT */
    /* Must call this as first thing in any virtual method. */
    /* It checks for a NULL object pointer and and unlinked virtual method. */
    /* Since this is a pure virtual method, ie, the constructor has provided no */
    /* assignment to the struct Point::PointVirtual_Clone function pointer, this */
    /* assert will fail. The inheriting class has to provide an implementation for this */
    /* assert to pass. */
    CAssertVirtual(self, PointVirtual_Draw);
    
    /* IMPORTANT */
    /* Must then call the virtual method using the function pointer. */
    self->PointVirtual_Draw(self);
}
```

###Main

The new iteration of struct Point can be used in the exact same way as before and will have the exact same behaviour. The compiler doesn't know any better. However, if at any time, ```Point_Clone( )``` is called, a run time check will fail, program execution will be halted, and a message printed to console explaining why this error occurred.

```C
#include <Point.h>

int main( int argc, char** argv )
{
    struct Point stackPoint;
    struct Point* heapPoint;
    struct Point* clonedPoint;
    
    /* This is the same code as before. It will work exactly the same. */
    /* However, if Point_Clone( ) is called on ether instance of struct Point, */
    /* the executing program will halt and a message to console will explain a pure virtual */
    /* method with no implementation was called. */
    
    /* First, the stack point. */
    Point(&stackPoint, 0, 0); /* Create the point, and put it at (0,0). */
    Point_Draw(&stackPoint);  /* Print the point's location to console. */
    Point_Move(&stackPoint, 3, 2); /* Move the point to (3,2). */
    Point_Draw(&stackPoint);  /* Print the points new location to console. */
    
    clonedPoint = Point_Clone(&stackPoint); /* This will fail, execution will stop and console have a message */
                                            /* printed to it, explaining this is a pure virtual method with */
                                            /* no implementation. */
    
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
    
    clonedPoint = Point_Clone(&stackPoint); /* Pretend the previous Point_Clone( ) call was commented out, and */
                                            /* the program got to this point. */
                                            /* This will fail, execution will stop and console have a message */
                                            /* printed to it, explaining this is a pure virtual method with */
                                            /* no implementation. */
    
    CDestroy(heapPoint);     /* Call destructor on object, this will also free the memory. */
    
    return 1;
}
```
