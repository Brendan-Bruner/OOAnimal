/*
 * Dragon.c
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#include "Dragon.h"

static int special(Whelp *this)
{
	return this->getAgility(this) + 130;
}

Constructor(Dragon)
{
	Super(Whelp);
	OverrideMethod(Whelp, special);
}
