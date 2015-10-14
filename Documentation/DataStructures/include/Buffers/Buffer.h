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
#ifndef INCLUDE_BUFFERS_BUFFER_H_
#define INCLUDE_BUFFERS_BUFFER_H_

#include <Class.h>
#include <LinkedListNode.h>

/**
 * @struct Buffer
 * @brief
 * 		Abstract template class for buffers.
 * @details
 * 		Defines an abstract template class for buffers.
 * 		Elements are added with Buffer::push( ) and removed with
 * 		Buffer::pop( ).
 * 		There is no interface for removing elements from the
 * 		buffer at arbitrary positions. For example, if five
 * 		elements are added with Buffer::push( ), the only
 * 		way to remove an element is with Buffer::pop( ).
 * 		The element that gets popped is entirely up to
 * 		the algorithm implemented.
 *
 * 		The general behaviour of each method is explained. Implementing
 * 		classes must implement this behaviour. Note, some methods already
 * 		have an implementation.
 */
Class( Buffer ) Extends( Object )
	Public
	(
		Boolean (*push)( self(Buffer), void* );
		void* (*pop)( self(Buffer) );
		void* (*peek)( self(Buffer) );
		void (*reset)( self(Buffer) );
		uint32_t (*length)( self(Buffer) );
		uint32_t (*maxLength)( self(Buffer) );
		Boolean (*isEmpty)( self(Buffer ) );
		Boolean (*isFull)( self(Buffer) );
	);
	Protected
	(
		LinkedListNode* head;
		LinkedListNode* tail;
		uint32_t length;
		uint32_t maxLength;
	);
EndClass;

/**
 * @memberof Buffer
 * @protected
 * @brief
 * 		Constructor for abstract Buffer class.
 * @details
 * 		Constructor for abstract Buffer class.
 */
Buffer* createBuffer_( self(Buffer) );


#endif /* INCLUDE_BUFFERS_BUFFER_H_ */
