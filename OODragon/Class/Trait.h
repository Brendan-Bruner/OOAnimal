/*
 * Trait.h
 *
 *  Created on: 2014-11-26
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
