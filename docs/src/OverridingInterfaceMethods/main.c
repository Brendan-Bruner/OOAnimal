#include <Square.h>

int main( int argc, char** argv )
{
    (void)argc; (void)argv;
    struct Square square;

    /* Create the square. */
    Square(&square, 0, 0, 10); 

    /* Print the square's location and length. */
    Printable_Print(&square.super.printable);  

    /* Move the square to (3,2) and reduce side length by 50%. */
    Point_Move(&square.super, 3, 2);
    Square_Scale(&square, -2);
    
    /* Print the square's new parameters. */
    Printable_Print(&square.super.printable);  
    
    CDestroy(&square);  

    return 1;
}