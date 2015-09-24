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

#include "ClassConfig.h"

#define TRAIT_PREFIX _trait
#define TRAIT_OFFSET _

/******************************************************************************/
/* Trait Declaration */
/******************************************************************************/
/* Open a trait declaration. */
#define Trait(T) 	typedef struct T T;	\
			struct T		\
			{			\
				/* Methods */
/* Close a trait declaration. */
#define EndTrait	        void * TRAIT_OFFSET;	\
       			}


/******************************************************************************/
/* Use a trait within a class */
/******************************************************************************/
/* Adds a trait to a class declaration, used after opening a class declaration and any inheritance. */
#define Uses(t)	\
  t TRAIT_PREFIX##t;


/******************************************************************************/
/* Link traits to an object at construction time */
/******************************************************************************/
/* Link a trait to a class, called in constructor. */
#define LinkTrait(t) \
  OBJ_REFERENCE->TRAIT_PREFIX##t.TRAIT_OFFSET = \
  (void *) (((unsigned char *) &(OBJ_REFERENCE->TRAIT_PREFIX##t)) - (unsigned char *) OBJ_REFERENCE)

/* Link a trait method to a class. */
#define LinkTraitMethod(t,M) \
  OBJ_REFERENCE->TRAIT_PREFIX##t. M = & M

/* Override a trait method defined in a super class. */
#define OverrideTraitMethod(S,t,M) \
  ((S *) OBJ_REFERENCE)->TRAIT_PREFIX##t. M = & M

/* Override a trait method in immediate super class, but retain reference to */
/* original implementation so that it can be called in the overrode method. */
#define SoftOverrideTraitMethod(S,t,M) \
  do {												\
    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = ((S*) OBJ_REFERENCE)->TRAIT_PREFIX##t. M; 	\
    OverrideTraitMethod(S,t,M);									\
  } while( 0 )


/******************************************************************************/
/* Bind a trait's method implementation to the class using it */
/******************************************************************************/
/* Cast a pointer to a trait into the class it is a part of. */
/* Must only be called inside of trait method definitions. */
#define TraitOf(C) \
  C *OBJ_REFERENCE = (C *) ((unsigned char *)PRE_OBJ_REFERENCE - (unsigned char *)PRE_OBJ_REFERENCE->TRAIT_OFFSET)


/******************************************************************************/
/* Call trait methods on an object using the trait */
/******************************************************************************/
#define trait(t,O) \
  (&(O)->TRAIT_PREFIX##t)


#endif /* TRAIT_H_ */
