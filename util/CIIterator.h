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
 * July 7, 2016
 */
/**
 * @file
 * @defgroup Iterators
 * All list type data structures.
 */
#ifndef UTIL_CIITERATOR_H_
#define UTIL_CIITERATOR_H_

#include <Class.h>

/************************************************************************/
/* Interface declaration.						*/
/************************************************************************/
/**
 * @struct CIIterator
 * @ingroup Iterators
 * @details
 *	Defines an interface for traversing collections of data.
 */
struct CIIterator
{
	/* CInterface must always be first member of */
	/* an interface's struct .*/
	struct CInterface interface;
};

/**
 * @cond HIDDEN_SYMBOL
 * @brief
 *	CIIterator virtual table.
 */
struct CIIterator_VTable
{
	CBool (*hasNext)( struct CIIterator* );
	void (*next)( struct CIIterator*, void* );
	CBool (*hasPrevious)( struct CIIterator* );
	void (*previous)( struct CIIterator*, void* );
	void (*add)( struct CIIterator*, void* );
	void (*set)( struct CIIterator*, void* );
	void (*remove)( struct CIIterator* );
	void (*index)( struct CIIterator* );
};
/**
 * @endcond
 */

/************************************************************************/
/* Method declarations. 						*/
/************************************************************************/
CBool CIIterator_HasNext( struct CIIterator* self );
void CIIterator_Next( struct CIIterator* self, void* element );
CBool CIIterator_HasPrevious( struct CIIterator* self );
void CIIterator_Previous( struct CIIterator* self, void* element );
void CIIterator_Add( struct CIIterator* self, void* element );
void CIIterator_Set( struct CIIterator* self, void* element );
void CIIterator_Remove( struct CIIterator* self );
void CIIterator_Index( struct CIIterator* self );


#endif /* UTIL_CIITERATOR_H_ */
