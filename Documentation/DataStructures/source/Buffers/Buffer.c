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
 * Oct 13, 2015
 */

#include <Buffers/Buffer.h>

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
/**
 * @memberof Buffer
 * @brief
 * 		Puts an element into the buffer.
 * @details
 * 		Puts an element into the buffer.
 * @param element[in]
 * 		A pointer to add to the buffer. This
 * 		pointer will typically point to the data of interest.
 * @returns
 * 		<b>true</b> when the element is successfully added to
 * 		the buffer. <b>false</b> otherwise. The reason for a return
 * 		value of false is up the implementing class to document.
 */
static Boolean push( self(Buffer), void* element )
{
	MemberOf( Buffer );
	return false;
}

/**
 * @memberof Buffer
 * @brief
 * 		Remove an element from the buffer.
 * @details
 * 		Remove an element from the buffer.
 * @returns
 * 		The element removed from the buffer.
 */
static void* pop( self(Buffer) )
{
	MemberOf(Buffer);
	return NULL;
}

/**
 * @memberof Buffer
 * @brief
 * 		Peek at an element from the buffer.
 * @details
 * 		Peek at an element from the buffer.
 * @returns
 * 		The element peeked at from the buffer.
 */
static void* peek( self(Buffer) )
{
	MemberOf( Buffer );
	return NULL;
}

/**
 * @memberof Buffer
 * @brief
 * 		Reset the buffer to empty.
 * @details
 * 		Reset the buffer to empty. All elements which have been
 * 		pushed into the buffer will be lost. This means memory
 * 		must be cleaned up before calling reset.
 */
static void reset( self(Buffer) )
{
	MemberOf( Buffer );
}

/**
 * @memberof Buffer
 * @brief
 * 		The current length of the buffer.
 * @details
 * 		Returns the current number of elements which are in the
 * 		buffer (not the max length of the buffer).
 * @returns
 * 		The number of elements in the buffer.
 */
static uint32_t length( self(Buffer) )
{
	MemberOf( Buffer );
	return protected(Buffer).length;
}

/**
 * @memberof Buffer
 * @brief
 * 		Returns the maximum length of the buffer.
 * @details
 * 		Returns the maximum number of elements that can ever
 * 		fit into the buffer.
 * @returns
 * 		The maximum number of elements which can ever fit
 * 		into the buffer. If space for elements is dynamically
 * 		added then this method would return the maximum size of
 * 		a uint32_t type.
 */
static uint32_t maxLength( self(Buffer) )
{
	MemberOf( Buffer );
	return protected(Buffer).maxLength;
}

/**
 * @memberof Buffer
 * @brief
 * 		Check if the buffer is empty.
 * @details
 * 		Check if the buffer is empty.
 * @returns
 * 		<b>true</b> if there are no elements in the buffer, <b>false</b>
 * 		otherwise.
 */
static Boolean isEmpty( self(Buffer ) )
{
	MemberOf( Buffer );

	if( self->length( self ) == 0 )
	{
		return true;
	}
	return false;
}

/**
 * @memberof Buffer
 * @brief
 * 		Check if the buffer is full.
 * @details
 * 		Check if the buffer is full.
 * @returns
 * 		<b>true</b> if the buffer is full (no more elements will be
 * 		successfully added), <b>false</b> otherwise.
 */
static Boolean isFull( self(Buffer) )
{
	MemberOf( Buffer );

	if( self->length( self ) >= self->maxLength( self ) )
	{
		return true;
	}
	return false;
}


/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
/**
 * @memberof Buffer
 * @protected
 * @brief
 * 		Constructor for abstract Buffer class.
 * @details
 * 		Constructor for abstract Buffer class.
 */
Buffer* createBuffer_( self(Buffer) )
{
	MemberOf( Buffer );

	LinkMethod( push );
	LinkMethod( pop );
	LinkMethod( peek );
	LinkMethod( reset );
	LinkMethod( length );
	LinkMethod( maxLength );
	LinkMethod( isEmpty );
	LinkMethod( isFull );

	protected(Buffer).length = 0;
	protected(Buffer).maxLength = 0;

	return self;
}
