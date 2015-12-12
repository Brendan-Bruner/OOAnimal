#include <Point.h>

int main( int argc, char** argv )
{
    (void)argc; (void)argv;
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
    
    clonedPoint = Point_Clone(heapPoint); /* Pretend the previous Point_Clone( ) call was commented out, and */
                                          /* the program got to this point. */
                                          /* This will fail, execution will stop and console have a message */
                                          /* printed to it, explaining this is a pure virtual method with */
                                          /* no implementation. */
    
    CDestroy(heapPoint);     /* Call destructor on object, this will also free the memory. */
    
    return 1;
}