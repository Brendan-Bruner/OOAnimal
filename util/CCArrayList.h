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
 * July 3, 2016
 */
#ifndef UTIL_CIARRAYLIST_H_
#define UTIL_CIARRAYLIST_H_

#include "CIList.h"
#include <CError.h>

/************************************************************************/
/* Class and vtable decalre.						*/
/************************************************************************/
struct CCArrayList
{
	/* Super class must always be first member */
	/* of a C class struct. */
	struct CObject cObject;

	/* Implementing the CIList interface. */
	struct CIList cIList;

	/* Private member variables. */
	struct
	{
		char* list_base;
		unsigned char* list_mask;
		size_t max_size;
		size_t current_size;
		size_t element_size;
		size_t add_index;
	} _;
};

struct CCArrayList_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	/* Since we are overriding the destructor, we need to keep */
	/* keep a reference to the super class' implementation of */
	/* the destructor. */
	const struct CObject_VTable* CObject_VTable_Ref;

	/* Space for a copy of the implemented interface's virtual table */
	struct CIList_VTable CIList_VTable;
};

const struct CCArrayList_VTable* CCArrayList_Get_Key( );

/************************************************************************/
/* Constructor								*/
/************************************************************************/
CError CCArrayList( struct CCArrayList* self, size_t element_size, size_t max_size );

#endif /* UTIL_CIARRAYLIST_H_ */
