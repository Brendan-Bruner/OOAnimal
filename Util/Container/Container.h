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
#ifndef UTIL_CONTAINER_CONTAINER_H_
#define UTIL_CONTAINER_CONTAINER_H_

#include "../ContainerConfig.h"

#if (configUSE_CCONTAINER == 1)
#include <Class.h>

#if (configUSE_CITERATOR == 1)
#include <Container/Iterator/Iterator.h>
#endif

/**
 * @struct CContainer
 * @brief
 * 		Defines an interface for containing pointers.
 * @details
 * 		Defines an interface for containing pointers.
 * 		Containers are data structures like queues and lists. This interface
 * 		defines an opaque way of interacting with concrete containers like
 * 		queues and lists.
 * 		added.
 * @attention
 * 		configUSE_CCONTAINER must be defined as 1 for this interface to
 * 		be included in the build. See ContainerConfig.h.
 */
struct CContainer
{
	/* Super Interface. */
	struct CInterface super_;

	Boolean (*CContainerVirtual_Add)( struct CContainer*, void* );

	#if (configUSE_CITERATOR == 1)
	size_t (*CContainerVirtual_AddAll)( struct CContainer*, struct CContainer* );
	struct CIterator* (*CContainerVirtual_GetIterator)( struct CContainer* );
	#endif

	#if (configCCONTAINER_EXTRA == 1)
	size_t (*CContainerVirtual_Size)( struct CContainer* );
	void (*CContainerVirtual_Reset)( struct CContainer* );
	size_t (*CContainerVirtual_AddCapacity)( struct CContainer*, size_t );
	#endif
};

#if (configCCONTAINER_ADD == 1)
/**
 * @memberof CContainer
 * @brief
 * 		Add an element to the container.
 * @details
 * 		Adds an element to the container. See implementing classes
 * 		for details on where the element is added.
 * @attention
 * 		configCCONTAINER_ADD must be defined as 1 for this method
 * 		to be included in the interface. See ContainerConfig.h.
 * @param element[in]
 * 		The element to add to the container. The container will save
 * 		a copy of the pointer.
 * @returns
 * 		<b>true</b> when the element is successfully added
 * 		and <b>false</b> otherwise.
 */
extern Boolean CContainer_Add( self(CContainer), void* element );
#endif

#if (configCCONTAINER_ADD_ALL == 1) && (configCCONTAINER_ITERATOR == 1) && (configUSE_CITERATOR == 1)
/**
 * @memberof CContainer
 * @brief
 * 		Adds all the elements of <b>container</b> into self.
 * @details
 * 		Adds all the elements of <b>container</b> into self without
 * 		removing the elements.
 * @attention
 * 		configCCONTAINER_ADD_ALL, configCCONTAINER_ITERATOR, and
 * 		configUSE_CITERATOR must be defined as 1 for this method
 * 		to be included. See ContainerConfig.h.
 * @param container
 * 		The container object to copy all the elements from.
 * @returns
 * 		The number of elements actually copied.
 */
extern size_t CContainer_AddAll( self(CContainer), CContainer* container );
#endif

#if (configCCONTAINER_ITERATOR == 1) && (configUSE_CITERATOR == 1)
/**
 * @memberof CContainer
 * @brief
 * 		Get a CIterator pointer for the container.
 * @details
 * 		Get a CIterator pointer for the container. The iterator
 * 		is dynamically allocated and must be destroyed with
 * 		CDestroy( ) to free memory.
 * @attention
 * 		configCCONTAINER_ITERATOR and configUSE_CITERATOR must
 * 		be defined as 1 for this method to be included. See
 * 		ContainerConfig.h.
 * @returns
 * 		A pointer to an iterator for the container. Returns <b>NULL</b>
 * 		if there is a failure to allocate the iterator.
 */
extern CIterator* CContainer_GetIterator( self(CContainer) );
#endif

#if (configCCONTAINER_SIZE == 1)
/**
 * @memberof CContainer
 * @brief
 * 		Gets the number of elements in the container.
 * @details
 * 		Gets the number of elements in the container.
 * @attention
 * 		configCCONTAINER_SIZE must be defined as 1 for
 * 		this method to be included. See ContainerConfig.h.
 * @returns
 * 		The number of elements in the container.
 */
extern size_t CContainer_Size( self(CContainer) );
#endif

#if (configCCONTAINER_RESET == 1 )
/**
 * @memberof CContainer
 * @brief
 * 		Empties all elements of the container.
 * @details
 * 		Empties all elements of the container. Resets its
 * 		size to zero. Memory clean up must be done before
 * 		calling this method.
 * @attention
 * 		configCCONTAINER_RESET must be defined as for this
 * 		method to be included. See ContainerConfig.h.
 */
extern void CContainer_Reset( self(CContainer) );
#endif

#if (configCCONTAINER_IS_EMPTY == 1)
/**
 * @memberof CContainer
 * @brief
 * 		Query if the container is empty.
 * @details
 * 		Query if the container is empty.
 * @attention
 * 		configCCONTAINER_IS_EMPTY must be defined as 1 for this
 * 		method to be included. See ContainerConfig.h.
 * @returns
 * 		<b>true</b> when the container is emtpy, <b>false</b>
 * 		if the container has one or more elements in it.
 */
extern Boolean CContainer_IsEmpty( self(CContainer) );
#endif

#if (configCCONTAINER_ADD_CAPACITY == 1)
/**
 * @memberof CContainer
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
 * 		extern CContainer* someContainer;
 * 		size_t increase;
 *
 * 		// Try to increase max size by 100 elements.
 * 		increase = CContainer_AddCapacity( someContainer, 100 );
 *
 * 		// Actual increase in maximum capacity.
 * 		printf( "Increase = %d", increase );
 * 		@endcode
 * @attention
 * 		configCCONTAINER_ADD_CAPACITY must be defined as 1 for
 * 		this method to be included. See ContainerConfig.h.
 * @param capacity
 * 		The amount of capacity to add.
 * @returns
 * 		The amount of capcity actually added.
 */
extern size_t CContainer_AddCapacity( self(CContainer), size_t );
#endif

#endif

#endif /* UTIL_CONTAINER_CONTAINER_H_ */
