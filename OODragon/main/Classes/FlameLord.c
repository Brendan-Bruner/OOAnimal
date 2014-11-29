/*
 * FlameLord.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */
#include "FlameLord.h"

/* Override trait method flames in super class */
static int flames(FireBreath *trait)
{
	FlameLord *this = (FlameLord *) CastTrait(trait);
	return 89999;
}

/* Override super classes special method */
static int special(FlameLord *this)
{
	return 723;
}

static int reap(FlameLord *this)
{
	return ((Whelp *) this)->getAgility(this) * 3 + 89;
}

Constructor(FlameLord)
{
	Super(FlameGuard);
	OverrideMethod(Whelp, special);
	OverrideTraitMethod(FlameGuard, FireBreath, flames);
	LinkMethod(reap);
}
