/*
 * Model.c
 *
 *  Created on: Oct 2, 2015
 *      Author: brendan
 */
#include <include/Model.h>

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
static char observe( self(Model), TObserver* observer )
{
	MemberOf( Model );
	ObjectASSERT( observer );

	if( private( ).totalObservers >= MAX_OBSERVERS )
	{
		return 0;
	}

	private( ).observers[private( ).totalObservers++] = observer;
	return 1;
}

static void notify( self(Model) )
{
	MemberOf( Model );

	int iter;
	for( iter = 0; iter < private( ).totalObservers; ++iter )
	{
		private( ).observers[iter]->update( private( ).observers[iter] );
	}
}

/****************************************************************************/
/* Destructor																*/
/****************************************************************************/


/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
void createModel( self(Model) )
{
	MemberOf( Model );
	LinkMethod( observe );
	LinkMethod( notify );

	/* No one is observing the model. */
	private( ).totalObservers = 0;
}
