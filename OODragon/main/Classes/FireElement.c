/*
 * FireElement.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */
#include "FireElement.h"

/* Use FireBreath trait */
static int flames(FireBreath *trait)
{
	FireElement *this = (FireElement *) CastTrait(trait);
	return this->data._magic * 2;
}

/* Use InnerFire trait */
static int heatWave(InnerFire *trait)
{
	FireElement *this = (FireElement *) CastTrait(trait);
	return this->data._magic * 4;
}

/* Use VolatileCore trait */
static int explosion(VolatileCore *trait)
{
	FireElement *this = (FireElement *) CastTrait(trait);
	return this->InnerFireT.heatWave(&this->InnerFireT) * 2;
}

/* Get magic */
static int getMagic(FireElement *this)
{
	return this->data._magic;
}

Constructor(FireElement)
{
	LinkTrait(this, FireBreath);
	this->FireBreathT.flames = &flames;

	LinkTrait(this, InnerFire);
	this->InnerFireT.heatWave = &heatWave;

	LinkTrait(this, VolatileCore);
	this->VolatileCoreT.explosion = &explosion;

	this->getMagic = &getMagic;

	this->data._magic = 7;
}
