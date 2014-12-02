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
 *      Author: brendan
 */

#ifndef CLASS_H_
#define CLASS_H_

#define Constructor(D)	void new##D(D *this)

#define Class(D)		typedef struct _##D D;			\
						Constructor(D);					\
						struct _##D						\
						{
							/* Super class */
#define Data				struct						\
							{
								/* Class data */
#define Methods			} data;
							/* Function pointers */
#define EndClass		}

#define Extends(S)		S super;
#define Super(S)		new##S(( S *) this);

#define LinkMethod(M)		this-> M = & M
#define OverrideMethod(S,M) ((S *) this)-> M = & M

#endif /* CLASS_H_ */
