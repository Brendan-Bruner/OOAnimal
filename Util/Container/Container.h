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
#ifndef INCLUDE_CONTAINER_H_
#define INCLUDE_CONTAINER_H_

#include <Class.h>
#include "ContainerConfig.h"

#if (configUSE_COTCONTAINER == 1)
#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
#include <Iterator/Iterator.h>
#endif
/**
 * @struct COTContainer
 * @brief
 * 		Defines an interface for containing pointers.
 * @details
 * 		Defines an interface for containing pointers.
 * 		Containers are data structures like queues and lists. This interface
 * 		defines an opaque way of interacting with concrete containers like
 * 		queues and lists.
 * 		added.
 * @attention
 * 		configUSE_COTCONTAINER must be defined as 1 for this interface to
 * 		be included in the build. See ContainerConfig.h.
 */
COTInterface( COTContainer )
	COTVirtual
	(
		#if (configCOTCONTAINER_ADD == 1)
			Boolean (*add)( self(COTContainer), void const* );
		#endif
		#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1) \
		&& (configUSE_COTITERATOR == 1)
			size_t (*addAll)( self(COTContainer), COTContainer* );
		#endif
		#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
			COTIterator* (*iterator)( self(COTContainer) );
		#endif
		#if (configCOTCONTAINER_SIZE == 1)
			size_t (*size)( self(COTContainer) );
		#endif
		#if (configCOTCONTAINER_RESET == 1 )
			void (*reset)( self(COTContainer) );
		#endif
		#if (configCOTCONTAINER_IS_EMPTY == 1)
			Boolean (*isEmpty)( self(COTContainer) );
		#endif
		#if (configCOTCONTAINER_ADD_CAPACITY == 1)
			size_t (*addCapacity)( self(COTContainer), size_t );
		#endif
	)
COTInterfaceEnd

#if (configCOTCONTAINER_ADD == 1)
/**
 * @memberof COTContainer
 * @brief
 * 		Add an element to the container.
 * @details
 * 		Adds an element to the container. See implementing classes
 * 		for details on where the element is added.
 * @attention
 * 		configCOTCONTAINER_ADD must be defined as 1 for this method
 * 		to be included in the interface. See ContainerConfig.h.
 * @param element[in]
 * 		The element to add to the container. The container will save
 * 		a copy of the pointer.
 * @returns
 * 		<b>true</b> when the element is successfully added
 * 		and <b>false</b> otherwise.
 */
extern Boolean COTContainer_Add( self(COTContainer), void const* element );
#endif

#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
/**
 * @memberof COTContainer
 * @brief
 * 		Adds all the elements of <b>container</b> into self.
 * @details
 * 		Adds all the elements of <b>container</b> into self without
 * 		removing the elements.
 * @attention
 * 		configCOTCONTAINER_ADD_ALL, configCOTCONTAINER_ITERATOR, and
 * 		configUSE_COTITERATOR must be defined as 1 for this method
 * 		to be included. See ContainerConfig.h.
 * @param container
 * 		The container object to copy all the elements from.
 * @returns
 * 		The number of elements actually copied.
 */
extern size_t COTContainer_AddAll( self(COTContainer), COTContainer* container );
#endif

#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
/**
 * @memberof COTContainer
 * @brief
 * 		Get a COTIterator pointer for the container.
 * @details
 * 		Get a COTIterator pointer for the container. The iterator
 * 		is dynamically allocated and must be destroyed with
 * 		COTDestroy( ) to free memory.
 * @attention
 * 		configCOTCONTAINER_ITERATOR and configUSE_COTITERATOR must
 * 		be defined as 1 for this method to be included. See
 * 		ContainerConfig.h.
 * @returns
 * 		A pointer to an iterator for the container. Returns <b>NULL</b>
 * 		if there is a failure to allocate the iterator.
 */
extern COTIterator* COTContainer_GetIterator( self(COTContainer) );
#endif

#if (configCOTCONTAINER_SIZE == 1)
/**
 * @memberof COTContainer
 * @brief
 * 		Gets the number of elements in the container.
 * @details
 * 		Gets the number of elements in the container.
 * @attention
 * 		configCOTCONTAINER_SIZE must be defined as 1 for
 * 		this method to be included. See ContainerConfig.h.
 * @returns
 * 		The number of elements in the container.
 */
extern size_t COTContainer_Size( self(COTContainer) );
#endif

#if (configCOTCONTAINER_RESET == 1 )
/**
 * @memberof COTContainer
 * @brief
 * 		Empties all elements of the container.
 * @details
 * 		Empties all elements of the container. Resets its
 * 		size to zero. Memory clean up must be done before
 * 		calling this method.
 * @attention
 * 		configCOTCONTAINER_RESET must be defined as for this
 * 		method to be included. See ContainerConfig.h.
 */
extern void COTContainer_Reset( self(COTContainer) );
#endif

#if (configCOTCONTAINER_IS_EMPTY == 1)
/**
 * @memberof COTContainer
 * @brief
 * 		Query if the container is empty.
 * @details
 * 		Query if the container is empty.
 * @attention
 * 		configCOTCONTAINER_IS_EMPTY must be defined as 1 for this
 * 		method to be included. See ContainerConfig.h.
 * @returns
 * 		<b>true</b> when the container is emtpy, <b>false</b>
 * 		if the container has one or more elements in it.
 */
extern Boolean COTContainer_IsEmpty( self(COTContainer) );
#endif

#if (configCOTCONTAINER_ADD_CAPACITY == 1)
/**
 * @memberof COTContainer
 * @brief
 * 		Attempts to increase the maximum capacity.
 * @details
 *		Attempts to increase the maximum number of elements the container can hold
 * 		by <b>capacity</b> elements. Although capacity is usually automatically
 * 		increased when the container hits its maximum size, it can be
 * 		more efficient to increase it in a large chunk. Returns the
 * 		number of elements the container was actually increased to hold.
 * 		For example:
 * 		@code
 * 		extern COTContainer* someContainer;
 * 		size_t increase;
 *
 * 		// Try to increase max size by 100 elements.
 * 		increase = COTContainer_AddCapacity( someContainer, 100 );
 *
 * 		// Actual increase in maximum capacity.
 * 		printf( "Increase = %d", increase );
 * 		@endcode
 * @attention
 * 		configCOTCONTAINER_ADD_CAPACITY must be defined as 1 for
 * 		this method to be included. See ContainerConfig.h.
 * @param capacity
 * 		The amount of capacity to add.
 * @returns
 * 		The amount of capcity actually added.
 */
extern size_t COTContainer_AddCapacity( self(COTContainer), size_t );
#endif

#endif

#endif /* INCLUDE_CONTAINER_H_ */
