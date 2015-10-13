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
 * Oct 12, 2015
 */
#ifndef INCLUDE_TRAITS_TLIST_H_
#define INCLUDE_TRAITS_TLIST_H_

#include <Class.h>

Trait( TList )
	Boolean (*insert)( self(TList), void*, uint32_t );
	Boolean (*add)( self(TList), void* );
	void* (*remove)( self(TList), uint32_t );
	void* (*removeElement)( self(TList), void* );
	void* (*get)( self(TList), uint32_t );
	void (*reset)( self(TList) );
	uint32_t (*length)( self(TList) );
	uint32_t (*maxLength)( self(TList) );
	Boolean (*isEmpty)( self(TList ) );
	Boolean (*isFull)( self(TList) );
EndTrait;

/**
 * @struct TList
 * @brief
 * 		Defines an interface for lists
 * @details
 * 		Defines an interface for lists. The general behaviour
 * 		of each method is explained below. Implementing classes
 * 		must implement the described behaviour.
 * @var TList::insert
 * 		@code
 * 			Boolean insert( self, void* element, uint32_t key );
 * 		@endcode
 * 		Insert an element into the list. Typically the inserted
 * 		element points to the data of interest.
 *
 * 		<b>Parameters</b>
 * 		<ul>
 * 		<li><b>element</b>: A pointer to add to the buffer. This
 * 		pointer will typically point to the data of interest.</li>
 * 		<li><b>key</b>: The location in the list where the element
 * 		will be inserted. The method used to handle collisions is
 * 		up to the implementing class.</li>
 * 		</ul>
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> on successful insertion. <b>false</b> on unsuccessful
 * 		insertion. It is up to the implementing to define what an unsuccessful
 * 		insertion means.
 * @var TList::add
 * 		@code
 * 			Boolean add( self, void* element );
 * 		@endcode
 * 		Insert an element into the list. The location in the
 * 		list where the element is inserted is defined by the
 * 		implementing class. Typically the inserted
 * 		element points to the data of interest.
 *
 * 		<b>Parameters</b>
 * 		<ul>
 * 		<li><b>element</b>: A pointer to add to the buffer. This
 * 		pointer will typically point to the data of interest.</li>
 * 		</ul>
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> on successful insertion. <b>false</b> on unsuccessful
 * 		insertion. It is up to the implementing to define what an unsuccessful
 * 		insertion means.
 * @var TList::remove
 * 		@code
 * 			void* remove( self, uint32_t key );
 * 		@endcode
 * 		Remove an element from the list.
 *
 * 		<b>Parameters</b>
 * 		<ul><li><b>key</b>: The location in the list where an element
 * 		is removed.</li></ul>
 *
 * 		<b>Returns</b>
 * 		<br>On successful removal, the removed element. On unsuccessful
 * 		removal <b>NULL</b>. It is up to the implementing class to
 * 		define what unsuccessful removal means.
 * @var TList::removeElement
 * 		@code
 * 			void* removeElement( self, void* element );
 * 		@endcode
 * 		Remove an element from the list.
 *
 * 		<b>Parameters</b>
 * 		<ul><li><b>element</b>: The element to remove from the list.</li></ul>
 *
 * 		<b>Returns</b>
 * 		<br>On successful removal, the removed element. On unsuccessful
 * 		removal <b>NULL</b>. It is up to the implementing class to
 * 		define what unsuccessful removal means.
 * @var TList::get
 * 		@code
 * 			void* get( self, uint32_t key );
 * 		@endcode
 * 		Get (peek at) an element from the list without actually
 * 		removing it.
 *
 * 		<b>Parameters</b>
 * 		<ul><li><b>key</b>: The location in the list for the element
 * 		go get.</li></ul>
 *
 * 		<b>Returns</b>
 * 		<br>On success, a pointer to the element retrieved. On unsuccessful retrieval,
 * 		<b>NULL</b> is returned. It is up to the implementing class to define
 * 		what unsuccessful retrieval means.
 * @var TList::reset
 * 		@code
 * 			void reset( self );
 * 		@endcode
 * 		Reset the list to empty. All elements which have been
 * 		inserted into the list will be lost. This means memory
 * 		must be cleaned up before calling reset.
 * @var TList::length
 * 		@code
 * 			uint32_t length( self );
 * 		@endcode
 * 		Returns the current number of elements which are in the
 * 		list (not the max length of the list).
 *
 * 		<b>Returns</b>
 * 		<br>The number of elements in the list.
 * @var TList::maxLength
 * 		@code
 * 			uint32_t maxLength( self );
 * 		@endcode
 * 		Returns the maximum number of elements that can ever
 * 		fit into the list.
 *
 * 		<b>Returns</b>
 * 		<br>The maximum number of elements which can ever fit
 * 		into the list. If space for elements is dynamically
 * 		added then this method would return the maximum size of
 * 		a uint32_t type.
 * @var TList::isEmpty
 * 		@code
 * 			Boolean isEmpty( self );
 * 		@endcode
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> if there are no elements in the list, <b>false</b>
 * 		otherwise.
 * @var TList::isFull
 * 		@code
 * 			Boolean isFull( self );
 * 		@endcode
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> if the list is full (no more elements will be
 * 		successfully added), <b>false</b> otherwise.
 */

#endif /* INCLUDE_TRAITS_TLIST_H_ */
