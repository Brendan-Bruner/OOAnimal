/*
 * Copyright 2019 Brendan Bruner
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * bbruner@ualberta.ca
 * Nov. 2015
 */
/**
 * @file
 */

#ifndef COBJECT_H_
#define COBJECT_H_		

/*
 * ==========================================================================
 * ------------------------------ Includes ----------------------------------
 * ==========================================================================
 */
#include "cclass.h"

/*
 * ==========================================================================
 * ---------------------------- Structures ----------------------------------
 * ==========================================================================
 */
/* Method declaration of memory free method. 
 */
typedef void (*cobject_free_f)( void* );

/**
 * @struct cobject_t
 * @brief
 *	Base class.
 * @details
 *	This is the base Class. All classes inherit from it. It must be the
 *	first member of any class' structure declaration (unless they're inheriting from 
 *	from a user defined class, in that case, the user defined class must be the first
 *	member).
 */
struct cobject_t
{
    /* cclass must be first variable in this struct.
     * Do not change. 
     */
    struct cclass_t cclass;
    
    /* Pointer to a memory free method used in the objects destructor. Will be NULL by default
     * and can be set by application code.
     */
    cobject_free_f   cfree;
};


/**
 * @struct cobject_vtable_t
 * @brief
 *	Virtual table declaration for cobject_t.
 * @details
 *	Contains the virtual function members of struct cobject_t. There is only one
 *	virtual table instance per class structure (ie, each instance of cobject_t uses
 *      the same cobject_vtable_t reference). 
 */
struct cobject_vtable_t
{
    /* This is an objects destructor method.
     */
    void (*cdestructor)( void* );
};


/*
 * ==========================================================================
 * ----------------------- Function Declarations ----------------------------
 * ==========================================================================
 */
/**
 * @memberof cobject_t
 * @details
 *	Return a reference to class CObject's virtual table. There is only one
 *	virtual table per class, which is shared by every instance of that class.
 *	This pointer must not be written to, only read from, hence the const return
 *	value.
 * @returns
 *	A read only pointer to the vtable for cobject_t instances.
 */
const struct cobject_vtable_t* cobject_vtable( );

/**
 * @memberof cobject_t
 * @constructor
 * @details
 *	Constructor. To construct an instance of struct CObject, call this method on
 *	it. 
 * @param self
 *	The instance of struct CObject to construct
 */
void cobject_init( struct cobject_t* self );

/**
 * @memberof cobject_t
 * @details
 *	Destructor. This is the destructor for all objects. Its polymorphic, meaning
 *	A reference to any class instance / interface can be given and the entire object will
 *	be destroyed. If a memory free method was set with cmalloc() that method will be
 *      called at the end of destruction.
 * @param self
 *	The object to destroy
 */
void cdestroy( void* self );

/**
 * @memberof cobject_t
 * @details
 *	Set a memory free method to be called at the end of destruction.
 * @param self
 *	The object to have a memory free method set. When the destructor
 *      gets called, it will do free_method( self )
 * @param free_method
 *	The method to call when destruction finishes. Has declaration void(*)( void* ).
 */
void cmalloc( void* self, cobject_free_f free_method );


#endif /* COBJECT_H_ */
