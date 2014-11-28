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

#define uses(t)		t t##T;

#define LinkTrait(C, t) C->t##T._delta = (delta_t)(((void *) &(C->t##T)) - (void *)C)
#define getClass(t)		((void *)t - (void *)t->_delta)

#endif /* TRAIT_H_ */
