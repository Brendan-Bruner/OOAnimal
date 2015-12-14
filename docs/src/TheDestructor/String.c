#include <String.h>
#include <string.h>

/* IMPORTANT */
/* Declare the new destructor implementation before the constructor. */
/* Just like when overriding any other method. */
static void CDestructor( struct CObject* );

/* Constructor. */
struct String* String( struct String* self, const char* string )
{
	/* Called first, as usual. */
	CConstructor(self);

	/* Super class constructor. */
	CObject((struct CObject*) self);

	/* IMPORTANT */
	/* We override the destructor just like when overriding any other method. */
	/* As usual, this MUST be after calling the super class constructor. */
	COverrideVirtual(self, (struct CObject*) self, CDestructor);

	/* Allocate memory for the string and copy it into the String class. */
	self->string = malloc(sizeof(char) * strlen(string));
	if( self->string == NULL )
		return NULL;
	strcpy(self->string, string);

	return self;
}

/* Override */
static void CDestructor( struct CObject* self_ )
{
	/* As usually, cast the input pointer. */
	struct String* self = CCast(self_);

	/* free the memory used. */
	free(self->string);

	/* IMPORTANT */
	/* Must ALWAYS call the super destructor as last operation. */
	CAssertSuper(self, CDestructor);
	self->CDestructor((struct CObject*) self);
}

void String_Print( struct String* self )
{
	/* All the usual stuff for a non virtual method. */
	CAssertObject(self);

	printf("%s\n", self->string);
}