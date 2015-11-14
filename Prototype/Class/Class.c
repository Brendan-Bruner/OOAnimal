/*
 * Class.c
 *
 *  Created on: Nov 13, 2015
 *      Author: bbruner
 */

#include "Class.h"

void OONullDestroy( CLASS_OBJECT* self )
{
	objASSERT( self );
}
void OOCreateObject( CLASS_OBJECT* self )
{
	if( self == NULL ){ return; }
	self->_vt.virtualDestroy = OONullDestroy;
}
