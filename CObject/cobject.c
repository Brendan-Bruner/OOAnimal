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

/*
 * ==========================================================================
 * ------------------------------ Includes ----------------------------------
 * ==========================================================================
 */
#include "cobject.h"


/*
 * ==========================================================================
 * -------------------Static Function Declarations --------------------------
 * ==========================================================================
 */
static void cobject_destructor( void* self_ );

/*
 * ==========================================================================
 * -------------------Static Function Definitions ---------------------------
 * ==========================================================================
 */
static void cobject_destructor( void* self_ )
{
	struct cobject_t* self;

        self = ccast(self_);
	if( self->cfree != NULL ) {
		self->cfree(self);
	}
}

/*
 * ==========================================================================
 * ----------------------- Function Definitions- ----------------------------
 * ==========================================================================
 */
void cdestroy( void* self_ )
{
	const struct cobject_vtable_t* vtable;
        struct cobject_t*              self;

	/* May be given a pointer to an interface object. Need
         * to find the base address of the object. 
         */
	self = ccast(self_);

	/* Get this objects vtable. */
	vtable = cclass_get_vtable(self);

	/* Call the destructor. */
	 vtable->cdestructor(self);
}

void cmalloc( void* self_, cobject_free_ft free_method )
{
        struct cobject_t* self;

        self = ccast(self_);
	self->cfree = free_method;
}

const struct cobject_vtable_t* cobject_vtable( )
{
	static const struct cobject_vtable_t vtable =
	{
		.cdestructor = cobject_destructor
	};
	return &vtable;
}

void cobject_init( struct cobject_t* self )
{
	/* Map vtable.
         */
	cclass_set_cvtable(self, cobject_vtable());

	/* Setup object data.
         */
	self->cclass.croot = self;
	self->cfree = NULL;
}
