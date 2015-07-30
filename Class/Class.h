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



/* Start the declaration of a class. */
#define Class(D)		typedef struct _##D D;			\
				struct _##D				\
				{
/* Optionally inherit after the Class() declaration. */					
#define Extends(S)			/* Super class */		\
					S _super##S;
/* End the declaration of a class. */
#define EndClass		}




/* Link a virtual method. */
#define LinkMethod(M)		/* Assign function to pointer. */	\
				OBJ_REFERENCE-> M = & M
/* Override a virtual method. */
#define OverrideMethod(S,M)	/* Reassign function to a pointer */	\
				/* in super class. */			\
				((S *) OBJ_REFERENCE)-> M = & M



/* Used at the beginning of virtual methods which override a super class */
/* method. */
#define MemberOf( C )		C *OBJ_REFERENCE = (C *) SUPER_OBJ_REFERENCE



/* Simple macro to do forward declaration. */
#define Forward(C)		typedef struct _##C C

#endif /* CLASS_H_ */
