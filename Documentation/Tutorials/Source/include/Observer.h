/*
 * Observer.h
 *
 *  Created on: Oct 2, 2015
 *      Author: brendan
 */

#include <Interface.h>

#ifndef SOURCE_INCLUDE_OBSERVER_H_
#define SOURCE_INCLUDE_OBSERVER_H_

Interface( TObserver )
	void (*update)( self(TObserver) );
EndInterface;

#endif /* SOURCE_INCLUDE_OBSERVER_H_ */
