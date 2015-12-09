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
    /* Super class. Must always be first member of a class' struct. */
    struct CObject super;
    
    /* Member data. */
    int x;
    int y;
};

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

* The most important rule is: **the first structure member must be the super class**. In the case of Point, its super class is ```struct CObject```. 
* All class methods have their **first argument as a pointer to the class they operate on**. In the case of the Point class, all methods have ```struct Point*``` as their first argument.
* The **constructors are just regular C functions**. 

On to the source file:

##Source

```C
#include <Point.h>
#include <stdio.h>

/* Constructor. */
void Point( struct Point* self, int x, int y )
{
    /* Must call generic constructor as first operation in any class' constructor. */
    CConstructor(self);
    
    /* Must call super classes constructor next. */
    CObject((struct CObject*) self);
    
    /* Set up member data. */
    self->x = x;
    self->y = y;
}

/* Point_Move( ). */
void Point_Move( struct Point* self, int x, int y )
{
    /* Must call this as first thing in any non virtual method. */
    CMethod(self);
    
    self->x = x;
    self->y = y;
}

/* Point_Draw( ). */
void Point_Draw( struct Point* self )
{
    /* Must call this as first thing in any non virtual method. */
    CMethod(self);
    
    printf( "point at (%d,%d)\n", self->x, self->y );
}
```

###Constructor definition

* The first line of code in a constructor is CConstructor( ). Nothing is allowed to be done before calling it. Although it's a macro (with side effects), it will be refered to as method. It accomplishes two objectives:
    * Initialize object data so that virtual methods and interfaces can be used
    * Initialize object data to enable run time checking
* Call the super class constructor. This can be done anywhere in the constructor's definition. There are two exceptions, though, which will be discussed in the overriding and overwriting virtual methods section. In addition, there are two valid ways to call the super's constructor:
    * First: ```CObject(&self->super);```. Here, we explicitly give the address of the super class to construct.
    * Second, the way shown in Point.c:  ```CObject((struct CObject*) self);```. A pointer can always be safetly cast to a pointer to its super class (and the super class' super class, and so on). This has the advantage of making the super class variable name irrelevant.

###Method Definition

* The first line of code in a non virtual methods definition should be CMethod( ). This is a macro which asserts the object pointer is non NULL.

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
