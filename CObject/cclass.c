/*
 * Copyright 2015 Brendan Bruner
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
#include "cclass.h"

/*
 * ==========================================================================
 * ----------------------- Function Definitions- ----------------------------
 * ==========================================================================
 */
void cclass_set_cvtable( void* self, const void* vtable)
{
	((struct cclass_t*) self)->cvtable = vtable;
}

const void* cclass_get_vtable( void* self )
{
	return ((struct cclass_t*) self)->cvtable;
}

void* ccast( void const* self )
{
	return ((struct cclass_t*) self)->croot;
}

