#Virtual and Pure Virtual Methods
---

To demonstrate virtual methods, lets take the class Point, and make ```Point_Draw( )``` virtual. In addition, lets add a method, ```Point_Clone( )```, and make it pure virtual. As will become evident, there is no way to stop compilation when application code attempts to instantiate a class with a pure virtual method. This can only be caught at run time when the application calls the pure virtual method. 

![](https://raw.githubusercontent.com/Brendan-Bruner/CObject/docs/VirtualMethods.jpg)

###Header

```C
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
    CObject(&self->super);
    
    /* IMPORTANT */
    /* Virtual methods must be manually linked in the constructor. */
    /* This is a helper macro do that. It resolves to exactly: */
    /*      self->PointVirtual_Draw = PointVirtual_Draw; */
    /* If you forget to do this, run time checking will notify you the first */
    /* time the unlinked virtual method is called. */
    CLinkVirtual(self, PointVirtual_Draw);
    
    /* IMPORTANT */
    /* We do not link the PointPureVirtual_Clone method because we want it to be pure virtual. */
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
    CAssertObject(self);
    
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
    /* It checks for a NULL object pointer and an unlinked virtual method. */
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
    /* More on why casting is important in the section on overriding and overwriting. */
    struct Point* self = CCast(self_);
    
    printf( "point at (%d,%d)\n", self->x, self->y );
}

/* IMPORTANT */
/* Pure virtual methods have only the public wrapper method. An implementation has to be written */
/* and linked in the an inheriting  class. */
/* Point_Clone( ) wrapper method. */
struct Point* Point_Clone( struct Point* self )
{
    /* IMPORTANT */
    /* Must call this as first thing in any virtual method wrapper. */
    /* It checks for a NULL object pointer and an unlinked virtual method. */
    /* ie, if the the programmer forgot to link this method in the constructor, */
    /* then this assert will fail. */
    /* However, we purposely did not link the method because we want it to be */
    /* pure virtual. Therefore, we want this assert to fail and notify us that we */
    /* instantiated an object with a pure virtual method. */
    /* The assert will only pass for inheriting classes which implement */
    /* this method. */
    CAssertVirtual(self, PointPureVirtual_Clone);
    
    /* IMPORTANT */
    /* Must then call the virtual method using the function pointer. */
    return self->PointPureVirtual_Clone(self);
}
```

###Main

The new version of Point can be used in the exact same way as before and will have the exact same behaviour. The compiler doesn't know any better. However, if at any time, ```Point_Clone( )``` is called, a run time check will fail, program execution will be halted, and a message printed to console explaining why this error occurred.

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
    
    clonedPoint = Point_Clone(&heapPoint); /* Pretend the previous Point_Clone( ) call was commented out, and */
                                            /* the program got to this point. */
                                            /* This will fail, execution will stop and console have a message */
                                            /* printed to it, explaining this is a pure virtual method with */
                                            /* no implementation. */
    
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
