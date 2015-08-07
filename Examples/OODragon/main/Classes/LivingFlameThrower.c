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
 * LivingFlameThrower.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */
#include "LivingFlameThrower.h"

/* Use FireBreath trait */
static int flames( trait(FireBreath) )
{
	TraitOf( LivingFlameThrower );
	return self->_fuelPower;
}

void newLivingFlameThrower( self(LivingFlameThrower) )
{
	MemberOf(LivingFlameThrower);

	/* Initialize super class. */
	newObject( (Object *) self );
	
	/* Link FireBreath trait. */
	LinkTrait(FireBreath);
	LinkTraitMethod(FireBreath, flames);

	self->_fuelPower = 21;
}
