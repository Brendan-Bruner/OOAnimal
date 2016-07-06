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
 * July 6, 2016
 */
/**
 * @file
 */
#ifndef UTIL_CCARRAYLISTITERATOR_H_
#define UTIL_CCARRAYLISTITERATOR_H_

#include <CIIterator.h>
#include <CError.h>

/************************************************************************/
/* Class and vtable decalre.						*/
/************************************************************************/
/* Must forward declare this. Declarations are included in source file.
 */
struct CIList;

/**
 * @struct CCListIterator
 * @ingroup Iterators
 */
struct CCListIterator
{
	/* Super class must always be first member */
	/* of a C class struct. */
	struct CObject cObject;

	/* Implementing the CIIterator interface. */
	struct CIIterator cIIterator;

	struct CIList* list;
	size_t index;
	size_t next_index;
	size_t previous_index;
	size_t last_index_used;
	CBool is_next_valid;
	CBool is_previous_valid;
	CBool is_last_index_used_valid;
};

/**
 * @cond HIDDEN_SYMBOL
 * @brief
 *	Virtual table for CCListIterator
 */
struct CCListIterator_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	/* Space for a copy of the implemented interface's virtual table */
	struct CIIterator_VTable CIIterator_VTable;
};

/**
 * @memberof CCListIterator
 * @details
 *	Get vtable reference for CCListIterator class.	
 */
const struct CCListIterator_VTable* CCListIterator_Get_Key( );

/**
 * @endcond
 */


/************************************************************************/
/* Constructor								*/
/************************************************************************/
/**
 * @memberof CCListIterator
 * @constructor
 * @details
 *	Constructs an interator capable of iterating over a list.
 * @param self
 *	The iterator.
 * @param list
 *	The list to iterate through.
 * @returns
 *	Error code.
 */
CError CCListIterator( struct CCListIterator* self, struct CIList* list );

#endif /* UTIL_CCARRAYLISTITERATOR_H_ */