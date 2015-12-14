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