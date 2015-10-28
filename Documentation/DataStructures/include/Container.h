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

#include <StandardConfig.h>
#include <Class.h>
#include <stdint.h>

#if (configUSE_CONTAINER == 1)
#if (configCONTAINER_ITERATOR == 1) && (configUSE_ITERATOR == 1)
#include <Iterator/Iterator.h>
#endif
/**
 * @struct Container
 * @brief
 * 		Defines an interface which all container data structures implement.
 * @details
 * 		Defines an interface which all container data structures implement.
 * 		containers are data structures like queues and lists. The description
 * 		of each method describes the behaviour implementing classes must
 * 		have.
 * @var Container::add
 * 		@code
 * 			Boolean add( self,  void* element );
 * 		@endcode
 * 		Adds an element to the container. Returns <b>true</b> when the element
 * 		is successfully added and <b>false</b> when the element did not get
 * 		added.
 * @var Container::addAll
 * 		@code
 * 			uint32_t addAll( self, Container* container );
 * 		@endcode
 * 		Adds all the elements in the Container pointed to by <b>container</b>.
 * 		Returns the number of elements successfully added.
 * @var Container::iterator
 * 		@code
 * 			Iterator* iterator( self );
 * 		@endcode
 * 		Returns a valid Iterator which will iterate through all the elements in
 * 		the list. Even if the container has a size of zero. May return NULL
 * 		in the event of some failure.
 * @var Container::size
 * 		@code
 * 			uint32_t size( self );
 * 		@endcode
 * 		Returns the number of elements currently in the container.
 * @var Container::reset
 * 		@code
 * 			void reset( self );
 * 		@endcode
 * 		Resets the container to have zero elements. Memory clean up is not
 * 		done and must be done by the application prior to calling this method.
 * @var Container::isEmpty
 * 		@code
 * 			Boolean isEmpty( self );
 * 		@endcode
 * 		Returns <b>true</b> when the size of the list is zero. Returns
 * 		<b>false</b> otherwise.
 * @var Container::addCapacity
 * 		@code
 * 			uint32_t addCapacity( self, uint32_t capacity );
 * 		@endcode
 * 		Attempts to increase the maximum number of elements the container can hold
 * 		by <b>capacity</b> units. Although capacity is usually automatically
 * 		increased when the container hits its maximum size, it can be
 * 		more efficient to increase it in a large chunk. Returns the
 * 		actually number of units the capacity was actually increased by.
 */
Interface( Container )
#if (configCONTAINER_ADD == 1)
	Boolean (*add)( self(Container), void* );
#endif
#if (configCONTAINER_ADD_ALL == 1) && (configCONTAINER_ITERATOR == 1) \
	&& (configUSE_ITERATOR == 1)
	uint32_t (*addAll)( self(Container), Container* );
#endif
#if (configCONTAINER_ITERATOR == 1) && (configUSE_ITERATOR == 1)
	Iterator* (*iterator)( self(Container) );
#endif
#if (configCONTAINER_SIZE == 1)
	uint32_t (*size)( self(Container) );
#endif
#if (configCONTAINER_RESET == 1 )
	void (*reset)( self(Container) );
#endif
#if (configCONTAINER_IS_EMPTY == 1)
	Boolean (*isEmpty)( self(Container) );
#endif
#if (configCONTAINER_ADD_CAPACITY == 1)
	uint32_t (*addCapacity)( self(Container), uint32_t );
#endif
EndInterface;
#endif

#endif /* INCLUDE_CONTAINER_H_ */
