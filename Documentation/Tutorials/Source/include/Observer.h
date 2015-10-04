/*
 * Observer.h
 *
 *  Created on: Oct 2, 2015
 *      Author: brendan
 */

#include <Trait.h>

#ifndef SOURCE_INCLUDE_OBSERVER_H_
#define SOURCE_INCLUDE_OBSERVER_H_

Trait( TObserver )
	void (*update)( self(TObserver) );
EndTrait;

#endif /* SOURCE_INCLUDE_OBSERVER_H_ */
