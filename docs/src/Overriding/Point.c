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