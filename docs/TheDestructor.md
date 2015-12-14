#The Destructor
---

The destructor is a virtual method defined in ```struct CObject```. It is called with ```CDestroy(void* object)```. This section will demonstrate how to override the destructor. Before that, there is an important feature of destructors which must be understood. Destruction is done in the reverse order of construction. When we construct an object, the child class calls its parent's constructor, which calls its parent's, and so on. The highest super class is constructed then the next child, all the way down to first child. The destructor is the oppisite; the child class destructs itself, then calls its parent's destructor, and so on.

With CObject, it is the duty of the programmer to ensure they call the parent's destructor as the last thing they do.

This will be demonstrated with a String class. It is an immutable object with one method, ```String_Print( )```. For simplicitly, we assume strings are null terminated.

![](https://raw.githubusercontent.com/bandren/CObject/master/docs/TheDestructor.jpg)

###Header

```C
#ifndef STRING_H_
#define STRING_H_

#include <Class/Class.h>

struct String
{
	/* Super class first, as usualy. */
	struct CObject super;

	/* IMPORTANT */
	/* When overriding the destructor, we add a function pointer to the */
	/* structure just like we would when overriding any other method. */
	/* This is the name and signature of the destructor. */
	void (*CDestructor)( struct CObject* );

	/* The string. */
	char* string;
};

/* Constructor. */
extern struct String* String( struct String* self, const char* string );

/* Print_String( ). */
extern void String_Print( struct String* self );

#endif /* STRING_H_ */
```

###Source

```C
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
```

###Main

```C
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
```

###Compiling

Assuming a directory structures like this:

./
<br>|-> Class
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.h
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.c
<br>|-> String.h
<br>|-> String.c
<br>|-> main.c

```
gcc -I. -DDEBUG -Wall Class/Class.c String.c main.c -o main
./main
```
