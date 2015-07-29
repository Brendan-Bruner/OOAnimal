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
 *  Created on: 2015-07-29
 *      Author: Brendan Bruner
 */

/* Memory allocation scheme */
/* DYNAMIC: object allocation is done with malloc and free. */
/* LINKED_LIST: object allocation is done used a linked list allocated at start */
/* 		up. */
/* CUSTOM: allows your own allocator implementation to be used. */
#define DYNAMIC
/* #define LINKED_LIST */
/* #define CUSTOM */

/* Name of the base object class. */
#define BASE_OBJECT		Object

/* This will be the variable name of an object. */
#define OBJ_REFERENCE		self

/* Do not change what is defined, instead, change the define's name. */
/* This is the macro that is used in function prototypes. */
#define self( class )		class *OBJ_REFERENCE	

/* Used to validate a pointer to an object. */					
#define OBJECT_ASSERT( O )	do{ (void) O } while( 0 )

/* Base class of all classes. Add variables and function pointers here. */
/* For example, adding a 'serialize( )' function here will reliable give */
/* every class a 'serialize( )' method. */
/** 
 * @struct BASE_OBJECT
 * @brief
 *	Base class for everything.
 * @details
 *	Base class for everything.
 * @var BASE_OBJECT::destroy
 *	@code
 *	void destroy( self(BASE_OBJECT) );
 *	@endcode
 *	Destroys the object. This method can be used to clean up memory allocation.
 *	
 *	<b>Parameters</b>
 *	<ul>
 *	<li><b>OBJ_REFERENCE</b>: Pointer to itself.</li>
 *	</ul>
 *
 *	<b>Returns</b>
 *	<br>Nothing.
 */
typedef struct
{
  void (*destroy)( self(BASE_OBJECT) );
} BASE_OBJECT;
