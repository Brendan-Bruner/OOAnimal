/* Trait header
 * Copyright (C) 2014 Brendan Bruner
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

#ifndef TRAIT_H_
#define TRAIT_H_

typedef void * delta_t;

#define Trait(T) 	typedef struct _##T T;	\
					struct _##T				\
					{						\

						/* Methods */
#define EndTrait		delta_t _delta;		\
					}

#define Uses(t)		t t##T;

#define LinkTrait(t) 				this->t##T._delta = (delta_t)(((void *) &(this->t##T)) - (void *)this)
#define LinkTraitMethod(t,M)		this->t##T. M = & M
#define OverrideTraitMethod(S,t,M)	((S *) this)-> t##T. M = & M

#define CastTrait(t)	((void *)t - (void *)t->_delta)

#endif /* TRAIT_H_ */
