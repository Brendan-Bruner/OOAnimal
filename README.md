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

For now, lets treat move( ) and draw( ) as non virtual methods. The header file would look like this:

**Point.h**
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
extern void Point( struct Point* self );

/* move( ) method. */
extern void Point_Move( struct Point* self, int x, int y );

/* draw( ) method. */
extern void Point_Draw( struct Point* self );

#endif /* POINT_H_
```

* First, and most important rule, **the first structure member must be the super class**. In the case of Point, it super class is ```struct CObject```. 
* Next rule, all class methods have their **first argument as a pointer to the class they operate on**. In the case of the Point class, all methods have ```struct Point*``` as their first argument.
* Finally, class **constructors are just regular C functions**. 

On to the source file:

**Point.c**
```C
#include <Point.h>

void Point( struct Point* self )
{
    /* Must call generic constructor as first operation in any class' constructor. */
}

```
