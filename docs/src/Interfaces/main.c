#include <Point.h>

int main( int argc, char** argv )
{
    (void)argc; (void)argv;
    struct Point point;

    Point(&point, 0, 0); /* Create the point, and put it at (0,0). */
    Printable_Print(&point.printable);  /* Print the point's location to console. */
    Point_Move(&point, 3, 2); /* Move the point to (3,2). */
    Printable_Print(&point.printable);  /* Print the points new location to console. */
    CDestroy(&point);    /* Call destructor on the object. */
    /* If all we had was a reference to the interface, we can call the destructor */
    /* on that too. The point object will still be cleanly destroyed. */
    /*      CDestroy(&point.printable); */
    /* Will do the same thing. */
    /*      struct Printable* printable = &point.printable; */
    /*      CDestroy(printable); */
    /* Exact same thing. */

    return 1;
}