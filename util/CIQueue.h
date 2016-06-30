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
 * Jun 24, 2016
 */
#ifndef UTIL_CIQUEUE_H_
#define UTIL_CIQUEUE_H_

#include <Class.h>


/************************************************************************/
/* Error codes.								*/
/************************************************************************/
/**
 * @memberof struct CIQueue
 * @details
 *	Error codes for queue methods.
 *
 * @var CIQUEUE_OK
 *	No error.
 *
 * @var CIQUEUE_ERR_OVERFLOW
 *	Queue is full, element not inserted.
 *
 * @var CIQueue_ERR_UNDERFLOW
 *	Queue is empty, nothing popped/peeked.
 */
typedef enum
{
	CIQUEUE_OK = 0,
	CIQUEUE_ERR_OVERFLOW = 1,
	CIQUEUE_ERR_UNDERFLOW = 2
} CIQueueError;


/************************************************************************/
/* Declare interface and vtable.					*/
/************************************************************************/
/**
 * @struct CIQueue
 * @details
 *	Interface for queues. Provides methods for inserting, popping,
 *	peeking, and polling the queue's size. 
 *
 *	Implementing classes must implement the behaviour specified in the
 *	functions described below.
 *
 *	This is a copy by value queue. That means a pointer to data is
 *	is given to the queues functions, and the data pointed to is then copied
 *	into the queue.
 *
 *	Implementing classes must provide a way to define the length of data
 *	copied in/out of the queue.
 */
struct CIQueue
{
	/* CInterface must always be first member of */
	/* an interfaces struct .*/
	struct CInterface interface;
};

/**
 * @struct CIQueue_VTable
 * @memberof struct CIQueue
 * @details
 *	Virtual table declaration for CIQueue interface.
 */
struct CIQueue_VTable
{
	CIQueueError (*insert)( struct CIQueue*, const void* );
	CIQueueError (*remove)( struct CIQueue*, void* );
	CIQueueError (*peek)( struct CIQueue*, void* );
	size_t (*size)( struct CIQueue* );
	size_t (*maxSize)( struct CIQueue* );
};


/************************************************************************/
/* Class methods. 							*/
/************************************************************************/
/**
 * @memberof struct CIQueue
 * @details
 *	Insert an element into the tail of the queue by copy.
 * @param self
 *	The queue.
 * @param element
 *	Pointer to data to copy into queue.
 * @returns
 *	Error code.
 */
static inline CIQueueError CIQueue_Insert( struct CIQueue* self, const void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->insert);
	return ((struct CIQueue_VTable*) CGetVTable(self))->insert(self, element);
}

/**
 * @memberof struct CIQueue
 * @details
 *	Remove an element from the head of the queue by copy.
 * @param self
 *	The queue
 * @param element
 *	Data in the head of the queue will be copied into the location pointed to
 *	by this. Pass in NULL to remove the the head of the queue without copying
 *	out the data.
 * @returns
 *	An error code.    
 */
static inline CIQueueError CIQueue_Remove( struct CIQueue* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->remove);
	return ((struct CIQueue_VTable*) CGetVTable(self))->remove(self, element);
}

/**
 * @memberof struct CIQueue
 * @details
 *	Peek at the element in the head of the queue by copy. This does
 *	remove the head.
 * @param self
 *	The queue.
 * @param element
 *	Data in the head of the queue will be copied to the location pointed to
 *	by this.
 * @returns
 *	An error code.
 */
static inline CIQueueError CIQueue_Peek( struct CIQueue* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->peek);
	return ((struct CIQueue_VTable*) CGetVTable(self))->peek(self, element);
}

/**
 * @memberof struct CIQueue
 * @details
 *	Get the number of elements currently in the queue.
 * @param self
 *	The queue.
 * @returns
 *	Number of elements currently in the queue. 
 */
static inline size_t CIQueue_Size( struct CIQueue* self )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->size);
	return ((struct CIQueue_VTable*) CGetVTable(self))->size(self);
}

/**
 * @memberof struct CIQueue
 * @details
 *	Get the maximum number of elements allowed in the queue.
 * @param self
 *	The queue.
 * @returns
 *	The maximum number of elements allowed in the queue. 
 */	
static inline size_t CIQueue_MaxSize( struct CIQueue* self )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->maxSize);
	return ((struct CIQueue_VTable*) CGetVTable(self))->maxSize(self);
}

#endif /* UTIL_CIQUEUE_H_ */
