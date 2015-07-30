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

#include "TraitConfig.h"
#include "ClassConfig.h"

/* Open a trait declaration. */
#define Trait(T) 	typedef struct _##T T;	\
			struct _##T		\
			{			\
				/* Methods */
/* Close a trait declaration. */
#define EndTrait	        void * _trait_offset_;	\
       			}



/* Adds a trait to a class declaration, used after opening a class declaration and any inheritance. */
#define Uses(t)		t _trait##t##_; t *trait##t;



/* Link a trait to a class, called in constructor. */
#define LinkTrait(t)			OBJ_REFERENCE->trait##t = &OBJ_REFERENCE->_trait##t##_;			\
  					OBJ_REFERENCE->trait##t->_trait_offset_ =				\
					  (void *) (((unsigned char *) (OBJ_REFERENCE->trait##t)) - (unsigned char *)OBJ_REFERENCE)
/* Link a trait method to a class. */
#define LinkTraitMethod(t,M)		OBJ_REFERENCE->trait##t-> M = & M
/* Override a trait method defined in a super class. */
#define OverrideTraitMethod(S,t,M)	((S *) OBJ_REFERENCE)-> trait##t-> M = & M



/* Cast a pointer to a trait into the class it is a part of. */
/* Must only be called inside of trait method definitions. */
#define TraitOf(C)		C *OBJ_REFERENCE = \
    				(C *) ((unsigned char *)TRAIT_REFERENCE - (unsigned char *)TRAIT_REFERENCE->_trait_offset_)

#endif /* TRAIT_H_ */
