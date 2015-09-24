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
 *  Created on: 2014-11-19
 *      Author: brendan
 */
/*
 * FlameLord.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */
#include "FlameLord.h"

/* Override trait method flames in super class */
static int flames( self(FireBreath) )
{
  	TraitOf( FlameLord );
	ObjectUnused( );
	return 89999;
}

/* Override super classes special method */
static int special( self(Whelp) )
{
	MemberOf(FlameLord);
	ObjectUnused( );
	return 723;
}

static int reap( self(FlameLord) )
{
	MemberOf(FlameLord);
	return ((Whelp *) self)->getAgility((Whelp *) self) * 3 + 89;
}

void newFlameLord( self(FlameLord) )
{
	MemberOf(FlameLord);

	/* Initialize super class and override methods in it. */
	newFlameGuard( (FlameGuard *) self );
	OverrideMethod(Whelp, special);
	
	/* Override trait method. */
	OverrideTraitMethod(FlameGuard, FireBreath, flames);

	/* Link class methods. */
	LinkMethod(reap);
}
