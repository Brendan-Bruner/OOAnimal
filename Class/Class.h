/* Class header
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
 *      Author: Brendan Bruner
 */

#ifndef CLASS_H_
#define CLASS_H_		

#include "ClassConfig.h"

#define SUPER_NAME _s
#define RECURSIVE_DESTRUCTOR _d
#define RECURSIVE_STRUCT_NAME _r


/******************************************************************************/
/* Class Declaration
/******************************************************************************/
/* Start the declaration of a class. */
#define Class(D)		typedef struct D D;			\
				struct D				\
				{
/* Optionally inherit after the Class() declaration. */					
#define Extends(S)			/* Super class */		\
				        S SUPER_NAME;
/* Optionally declare methods in super */
/* class which will be overrode and then */
/* referenced in the overrode method. */
#define RecursivelyOverride( ... )	struct				\
					{				\
  						__VA_ARGS__		\
				        } RECURSIVE_STRUCT_NAME;
/* End the declaration of a class. */
#define EndClass			destructor RECURSIVE_DESTRUCTOR;\
  				}



/******************************************************************************/
/* Link class methods to an object an construction time
/******************************************************************************/
/* Link a virtual method on a class by class basis. */
#define LinkMethod(M)		/* Assign function to pointer. */	\
				OBJ_REFERENCE-> M = & M
/* Override a virtual method on a class by class basis. */
#define OverrideMethod(S,M)	/* Reassign function to a pointer */	\
				/* in super class. */			\
				((S *) OBJ_REFERENCE)-> M = & M
#define RecursivelyOverrideMethod(M) \
  OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = OBJ_REFERENCE->SUPER_NAME-> M; \
  OBJ_REFERENCE->SUPER_NAME-> M = & M


/******************************************************************************/
/* Bind a class' implementation to the class implementing the method
/******************************************************************************/
/* Used to register a function with a class, on a function by function basis. */
#define MemberOf( C ) \
  C *OBJ_REFERENCE = (C *) PRE_OBJ_REFERENCE


/******************************************************************************/
/* Being a class' constructor implementation to the class.
/******************************************************************************/
#define ConstructorOf( C ) \
  MemberOf( C );	   \
  OBJ_REFERENCE->RECURSIVE_DESTRUCTOR = OBJ_REFERENCE->SUPER_NAME->DESTRUCTOR_NAME; \
  OverrideMethod( BASE_OBJECT, DESTRUCTOR_NAME )


/******************************************************************************/
/* Access super classes methods which are recursively overrode.
/******************************************************************************/
#define Super \
  (&(OBJ_REFERENCE->RECURSIVE_STRUCT_NAME))


/* Simple macro to do forward declaration. */
#define Forward(C)		typedef struct C C

#endif /* CLASS_H_ */
