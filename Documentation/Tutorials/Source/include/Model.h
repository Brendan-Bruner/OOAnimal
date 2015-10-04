#ifndef INCLUDE_MODEL_H
#define INCLUDE_MODEL_H

#include <Class.h>
#include "Observer.h"

#define MAX_OBSERVERS 5

Class( Model ) Extends( Object )
	Private
	(
		TObserver*	observers[MAX_OBSERVERS];
		int 		totalObservers;
	);
	Public
	(
		char (*observe)( self(Model), TObserver* );
		void (*notify)( self(Model) );
	);
EndClass;

void createModel( self(Model) );

#endif /* INCLUDE_MODEL_H */
