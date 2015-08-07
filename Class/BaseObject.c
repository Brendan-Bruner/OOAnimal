/* Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 *
 *  Created on: 2015-07-29
 *      Author: Brendan Bruner
 */

#include "Class.h"

/* Base destroy method. */
static void destroy( self(BASE_OBJECT) )
{
	MemberOf( BASE_OBJECT );
	ObjectUnused( );
	return;
}

/* Base constructor. */
void BASE_CONSTRUCTOR( self(BASE_OBJECT) )
{
	MemberOf( BASE_OBJECT );
	LinkMethod( destroy );
}
