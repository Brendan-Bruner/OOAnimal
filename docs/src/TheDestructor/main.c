#include <String.h>

int main( int argc, char** argv )
{
	(void)argc; (void)argv;

	struct String stackString;
	struct String* heapString;

	String(&stackString, "Hello World");
	String_Print(&stackString);
	CDestroy(&stackString); /* Will free the memory allocated for the string. */

	heapString = malloc(sizeof(*heapString));
	if( heapString == NULL )
		return 0;
	String(heapString, "Hello World");
	CDynamic(heapString); /* Declare the object as being dynamically allocated. */
	String_Print(heapString);
	CDestroy(heapString); /* Will free the memory allocated for the string, then */
	                      /* free the object itself. */

	return 1;
}