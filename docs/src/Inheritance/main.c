#include <Square.h>

int main( int argv, char** argc )
{
    (void)argv; (void)argc;
    struct Square square;

    Square(&square, 0, 0, 5); /* Make a square at (0,0) with sides of lenght 5. */
    Point_Draw((struct Point*) &square); /* Will print to console the squares */
                                         /* location, that is, (0,0). */
    Point_Move((struct Point*) &square, 3, 3); /* Move the point to (3,3). */
    Point_Draw((struct Point*) &square); /* Will print to console the squares */
                                         /* location, that is, (3,3). */    
        /* Clone will make an exact copy of square, and return it */
    struct Point* clone = Point_Clone((struct Point*) &square);
    Point_Draw(clone); /* Will print the clones location to console, that is, (3,3). */
    CDestroy(clone);

    Square_Scale(&square, 2); /* Double the length of the squares sides. */
    CDestroy(&square);
}
