#Interfaces
---

An interface is the equivelent of a C++ class with only pure virtual methods, or a Java interface. This section will show how to write an interface and implement it. We will use the Point class from the **Classes** section and implement a Printable interface which has a method ```Printable_Print( )``` instead of declaring a class method, ```Point_Draw( )```.

![](https://raw.githubusercontent.com/bandren/CObject/master/docs/Interfaces.jpg)

An interface needs a source and a header file. However, for the sake of simplicity, we will inline a method and only use a header file for the interface. We will revist the header and source file of Point and then write a new main to demonstrate usage. The example main contains an important point on destruction. 

###Interface Header

```C
#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <Class/Class.h>

struct Printable
{
	/* IMPORTANT */
	/* Must always be first in an interface struct. */
	struct CInterface iface;

	/* IMPORTANT */
	/* All methods of an interface are virtual methods. */
	void (*PrintableVirtual_Print)( struct Printable* );
};

/* Printable_Print( ) method. */
static inline void Printable_Print( struct Printable* self )
{
	/* IMPORTANT */
	/* An interface method follows the same format as a virtual method. */
	/* It asserts the funciton pointer, then calls the function pointer's */
	/* method. The implementing class will assign a method to this pointer. */
	CAssertVirtual(self, PrintableVirtual_Print);
	self->PrintableVirtual_Print(self);
}

#endif /* PRINTABLE_H_ */
```

###Point Header

```C
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
```

###Header Source

```C
#include <Point.h>
#include <stdio.h>

/* Declare implementation method for interface. */
static void PrintableVirtual_Print( struct Printable* );

/* Constructor. */
void Point( struct Point* self, int x, int y )
{
    /* First operation, as usual. */
    CConstructor(self);
    /* Super class constructed as usual. */
    CObject(&self->super); 

    /* IMPORTANT */
    /* Must always call this on the interfaces being implemented. */ 
    /* If we implemented two more interfaces, we would call this two */
    /* more times on each of those interfaces. */
    /* If the interface implemented an interface, we would call this */
    /* twice, once for the interface implemented by the interface, and */
    /* a second time for the interface implemented by the class. */
    CInterface(&self->printable);

    /* IMPORTANT */
    /* Must link implemented interface method. */
    CLinkVirtual(&self->printable, PrintableVirtual_Print);
    
    /* Set up member data. */
    self->x = x;
    self->y = y;
}

/* Point_Move( ). */
void Point_Move( struct Point* self, int x, int y )
{
    CAssertObject(self);
    
    self->x = x;
    self->y = y;
}

/* Printable_Print( ) implementation. */
static void PrintableVirtual_Print( struct Printable* self_ )
{
    /* IMPORTANT */
    /* Just like with virtual methods inherited from a super class, we */
    /* must call this on interface methods to. It casts the pointer to */
    /* the interface to a pointer to our class. */
    struct Point* self = CCast(self_);
    
    printf( "point at (%d,%d)\n", self->x, self->y );
}
```

###Main

```C
#include <Point.h>

int main( int argc, char** argv )
{
    (void)argc; (void)argv;
    struct Point point;

    /* Create the point, and put it at (0,0). */
    Point(&point, 0, 0); 
    
    /* Print the point's location to console. */
    Printable_Print(&point.printable);
    
    /* Move the point to (3,2). */
    Point_Move(&point, 3, 2); 
    
    /* Print the points new location to console. */
    Printable_Print(&point.printable);  
    
    /* IMPORTANT */
    /* Call destructor on the object. */
    /* If all we had was a reference to the interface, we can call the destructor */
    /* on that too. The point object will still be cleanly destroyed. */
    /*      CDestroy(&point.printable); */
    /* Will do the same thing. */
    /*      struct Printable* printable = &point.printable; */
    /*      CDestroy(printable); */
    CDestroy(&point);    

    return 1;
}
```
### Compiling

Assuming a directory structures like this:

./
<br>|-> Class
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.h
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.c
<br>|-> Printable.h
<br>|-> Point.h
<br>|-> Point.c
<br>|-> main.c

```
gcc -I. -DDEBUG -Wall Class/Class.c Point.c main.c -o main
./main
```
