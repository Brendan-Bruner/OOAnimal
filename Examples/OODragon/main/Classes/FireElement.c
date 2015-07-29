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
 * FireElement.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */
#include "FireElement.h"

/* Use FireBreath trait */
static int flames( trait(FireBreath) )
{
	TraitOf( FireElement );
	return self->_magic * 2;
}

/* Use InnerFire trait */
static int heatWave( trait(InnerFire) )
{
	TraitOf( FireElement );
	return self->_magic * 4;
}

/* Use VolatileCore trait */
static int explosion( trait(VolatileCore) )
{
	TraitOf( FireElement );
	return self->traitInnerFire->heatWave( self->traitInnerFire ) * 2;
}

/* Get magic */
static int getMagic( self(FireElement) )
{
	return self->_magic;
}

void newFireElement( self(FireElement) )
{
	/* Link FireBreath trait. */
	LinkTrait(FireBreath);
	LinkTraitMethod(FireBreath, flames);

	/* Link InnerFire trait. */
	LinkTrait(InnerFire);
	LinkTraitMethod(InnerFire, heatWave);

	/* Link VolatileCore trait. */
	LinkTrait(VolatileCore);
	LinkTraitMethod(VolatileCore, explosion);

	/* Link class methods. */
	LinkMethod(getMagic);

	self->_magic = 7;
}
