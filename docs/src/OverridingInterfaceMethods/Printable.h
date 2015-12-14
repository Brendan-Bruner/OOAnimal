#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <Class/Class.h>

struct Printable
{
	/* IMPORTANT */
	/* Must always be first in an interface struct. */
	struct CInterface iface;

	/* IMPORTANT */
	/* All methods of an interface are virtual methods. */
	void (*PrintableVirtual_Print)( struct Printable* );
};

/* Printable_Print( ) method. */
static inline void Printable_Print( struct Printable* self )
{
	CAssertVirtual(self, PrintableVirtual_Print);
	self->PrintableVirtual_Print(self);
}

#endif /* PRINTABLE_H_ */