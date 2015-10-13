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
 * Oct 11, 2015
 */
#ifndef INCLUDE_TRAITS_TBUFFER_H_
#define INCLUDE_TRAITS_TBUFFER_H_

#include <Class.h>

Trait( TBuffer )
	Boolean (*push)( self(TBuffer), void* );
	void* (*pop)( self(TBuffer) );
	void* (*peek)( self(TBuffer) );
	void (*reset)( self(TBuffer) );
	uint32_t (*length)( self(TBuffer) );
	uint32_t (*maxLength)( self(TBuffer) );
	Boolean (*isEmpty)( self(TBuffer ) );
	Boolean (*isFull)( self(TBuffer) );
EndTrait;

/**
 * @struct TBuffer
 * @brief
 * 		Defines an interface for buffers.
 * @details
 * 		Defines an interface for buffers.
 * 		Elements are added with TBuffer::push( ) and removed with
 * 		TBuffer::pop( ).
 * 		There is no interface for removing elements from the
 * 		buffer at arbitrary positions. For example, if five
 * 		elements are added with TBuffer::push( ), the only
 * 		way to remove an element is with TBuffer::pop( ).
 * 		The element that gets popped is entirely up to
 * 		the algorithm implemented.
 *
 * 		The general behaviour of each method is explained. Implementing
 * 		classes must implement this behaviour.
 * @var TBuffer::push
 * 		@code
 * 			Boolean push( self, void* element );
 * 		@endcode
 * 		Puts an element into the buffer.
 *
 * 		<b>Parameters</b>
 * 		<ul><li><b>element</b>: A pointer to add to the buffer. This
 * 		pointer will typically point to the data of interest.</li></ul>
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> when the element is successfully added to
 * 		the buffer. <b>false</b> otherwise. The reason for a return
 * 		value of false is up the implementing class to document.
 * @var TBuffer::pop
 * 		@code
 * 			void* pop( self );
 * 		@endcode
 * 		Remove an element from the buffer.
 *
 * 		<b>Returns</b>
 * 		<br>The element removed from the buffer.
 * @var TBuffer::peek
 * 		@code
 * 			void* peek( self );
 * 		@endcode
 * 		Peek at an element from the buffer.
 *
 * 		<b>Returns</b>
 * 		<br>The element peeked at from the buffer.
 * @var TBuffer::reset
 * 		@code
 * 			void reset( self );
 * 		@endcode
 * 		Reset the buffer to empty. All elements which have been
 * 		pushed into the buffer will be lost. This means memory
 * 		must be cleaned up before calling reset.
 * @var TBuffer::length
 * 		@code
 * 			uint32_t length( self );
 * 		@endcode
 * 		Returns the current number of elements which are in the
 * 		buffer (not the max length of the buffer).
 *
 * 		<b>Returns</b>
 * 		<br>The number of elements in the buffer.
 * @var TBuffer::maxLength
 * 		@code
 * 			uint32_t maxLength( self );
 * 		@endcode
 * 		Returns the maximum number of elements that can ever
 * 		fit into the buffer.
 *
 * 		<b>Returns</b>
 * 		<br>The maximum number of elements which can ever fit
 * 		into the buffer. If space for elements is dynamically
 * 		added then this method would return the maximum size of
 * 		a uint32_t type.
 * @var TBuffer::isEmpty
 * 		@code
 * 			Boolean isEmpty( self );
 * 		@endcode
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> if there are no elements in the buffer, <b>false</b>
 * 		otherwise.
 * @var TBuffer::isFull
 * 		@code
 * 			Boolean isFull( self );
 * 		@endcode
 *
 * 		<b>Returns</b>
 * 		<br><b>true</b> if the buffer is full (no more elements will be
 * 		successfully added), <b>false</b> otherwise.
 */

#endif /* INCLUDE_TRAITS_TBUFFER_H_ */
