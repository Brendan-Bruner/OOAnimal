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
    /* If we implemented 2 more interfaces, we would call this two */
    /* more times on each of those interfaces. */
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
    /* IMPORTANT */
    /* Must call this as first thing in any non virtual method. */
    /* It checks for a NULL object pointer. */
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