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
						struct				\
						{
							/* Methods */
#define EndTrait		} method;			\
						delta_t delta;		\
					}

#define uses(T)		T trait##T;

#define LinkTrait(C, T) C->trait##T.delta = (delta_t)(&C->trait##T - C)
#define UseTrait(C, O)	C *this = (C *)(O - O->delta)

#endif /* TRAIT_H_ */
