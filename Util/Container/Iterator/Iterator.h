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
 * Oct 23, 2015
 */
#ifndef UTIL_CONTAINER_ITERATOR_ITERATOR_H_
#define UTIL_CONTAINER_ITERATOR_ITERATOR_H_

#include "../../ContainerConfig.h"

#if (configUSE_CITERATOR == 1 )
#include <Class.h>
#include <Boolean.h>
/**
 * @struct COTIterator
 * @brief
 * 		Defines an interface to iterate something.
 * @details
 * 		Defines an interface to iterate something. For example:
 * 		@code
 * 		void printContainerElements( struct CContainer* container )
 * 		{
 * 			struct CIterator* iter = CContainer_GetIterator(container);
 *				while( CIterator_HasNext(iter) )
 *				{
 *					printf("element = %p\n", CIterator_Next(iter));
 *				}
 * 		}
 * 		@endcode
 * 		The above function takes a container pointer and prints the addresses
 * 		of all elements in the container.
 * @attention
 * 		Requires configUSE_CITERATOR is defined as 1 for this interface
 * 		to be included in the build. See ContainerConfig.h.
 */
struct CIterator
{
	/* Super interface.*/
	struct CInterface super;

	/* virtual methods. */
	void (*CIteratorVirtual_Reset)( struct CIterator* );
	Boolean (*CIteratorVirtual_HasNext)( struct CIterator* );
	void* (*CIteratorVirtual_Next)( struct CIterator* );
};

/**
 * @memberof COTIterator
 * @brief
 * 		Resets the iterator.
 * @details
 * 		Resets the iterator. For example, if the iterator has 7
 * 		elements to iterate over, calling this method will reset it
 * 		so that it iterates over those 7 elements from the beginning.
 * @attention
 * 		configCOTITERATOR_RESET must be defined as 1 for this method to be
 * 		included in the build.
 */
extern void CIterator_Reset( struct CIterator* );

/**
 * @memberof COTIterator
 * @brief
 * 		Check if the iterator has more elements to return.
 * @details
 * 		Check if the iterator has more elements to return. When
 * 		this method returns <b>true</b> then COTIterator_Next( ) will
 * 		always return a non null value.
 * @returns
 * 		<b>true</b> when there are more elements in the iterator.
 * 		<b>false</b> when the iterator is empty. COTIterator_Next( )
 * 		will return <b>NULL</b> if this method returns <b>false</b>.
 */
extern Boolean CIterator_HasNext( struct CIterator* );

/**
 * @memberof COTIterator
 * @brief
 * 		Returns the next element in the iterator.
 * @details
 * 		Returns the next element in the iterator. The next call
 * 		then returns the next, next element, and so on. For example,
 * 		if the iterator contains 7 elements, then calling this method
 * 		7 times will return each of those 7 elements. The order
 * 		cannot be known. Once all elements are returned, this method
 * 		will return <b>NULL</b>. Note, if COTIterator_HasNext( ) returns
 * 		<b>true</b> then this method will never return <b>NULL</b>.
 * 		For example:
 * 		@code
 * 		extern CIterator* someIter;
 * 		if( CIterator_HasNext( someIter ) )
 * 		{
 * 			// Will never return NULL.
 * 			CIterator_Next( someIter );
 *
 * 			// May or may not return NULL. Can check return value or
 * 			// call CIterator_HasNext( ) again to check.
 * 			CIterator_Next( someIter );
 * 		}
 * 		@endcode
 * @returns
 * 		The next element in the iterator, or <b>NULL</b> if there are
 * 		no more elements.
 */
extern void* CIterator_Next( struct CIterator* );

#endif /* configUSE_CITERATOR */

#endif /* INCLUDE_ITERATOR_H_ */
