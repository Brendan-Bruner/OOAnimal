/* Copyright (C) 2014 Brendan Bruner
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
 *  Created on: 2015-07-29
 *      Author: Brendan Bruner
 */

#ifndef TRAITCONFIG_H_
#define TRAITCONFIG_H_

/* Variable name of a trait. This will never be used directly */
/* so it should be named to avoid naming conflicts only. */
#define TRAIT_REFERENCE 	traitReference

/* Do not change what is being defined, change the definition. */
/* This is the macro used when prototyping a trait method. */
#define trait(T)		T *TRAIT_REFERENCE

#endif /* TRAITCONFIG_H_ */
