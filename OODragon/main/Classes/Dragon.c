/*
 * Dragon.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#include "Dragon.h"

static int special(Dragon *this)
{
	return ((Whelp *) this)->getAgility(this) + 130;
}

Constructor(Dragon)
{
	Super(Whelp);
	//newWhelp(this);
	OverrideMethod(Whelp, special);
}
