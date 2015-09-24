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
#define PRIVATE_STRUCT_NAME _p0
#define PROTECTED_STRUCT_NAME _p1


/******************************************************************************/
/* Class Declaration */
/******************************************************************************/
/* Start the declaration of a class. */
#define Class(D)		typedef struct D D;			\
				struct D				\
				{
/* Optionally inherit after the Class() declaration. */					
#define Extends(S)		        S SUPER_NAME;
/* Declare private member data/methods. */
#define Private( ... )			struct				\
					{				\
					  __VA_ARGS__			\
					} PRVIATE_STRUCT_NAME;
/* Declare protected member data/methods. */
#define Protected( ... )		struct			     	\
					{				\
					  __VA_ARGS__			\
					} PROTECTED_STRUCT_NAME;
/* Declare public member data/methods. */
#define Public( ... )			__VA_ARGS__
/* Optionally declare methods in super */
/* class which will be overrode and then */
/* referenced in the overrode method. */
#define SoftOverrides( ... )		struct				\
					{				\
					  __VA_ARGS__			\
				        } RECURSIVE_STRUCT_NAME;
/* End the declaration of a class. */
#define EndClass		}



/******************************************************************************/
/* Link class methods to an object an construction time */
/******************************************************************************/
/* Link a virtual method on a class by class basis. */
#define LinkMethod(M)		/* Assign function to pointer. */	\
				OBJ_REFERENCE-> M = & M
/* Override a virtual method on a class by class basis. */
#define OverrideMethod(S,M)	/* Reassign function to a pointer */	\
				/* in super class. */			\
				((S *) OBJ_REFERENCE)-> M = & M
#define SoftOverrideMethod(S,M) \
  do {										\
    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = ((S*) OBJ_REFERENCE)-> M; 	\
    OverrideMethod(S,M);							\
  } while( 0 )


/******************************************************************************/
/* Bind a class' implementation to the class implementing the method */
/******************************************************************************/
/* Used to register a function with a class, on a function by function basis. */
#define MemberOf( C ) \
  C *OBJ_REFERENCE = (C *) PRE_OBJ_REFERENCE


/******************************************************************************/
/* Access super classes methods which are softly overrode. */
/******************************************************************************/
#define Super \
  (&(OBJ_REFERENCE->RECURSIVE_STRUCT_NAME))


/* Simple macro to do forward declaration. */
#define Forward(C)		typedef struct C C

#endif /* CLASS_H_ */
