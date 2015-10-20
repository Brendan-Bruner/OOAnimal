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
 * Oct 15, 2015
 */
#ifndef INCLUDE_BUFFERS_QUEUE_H_
#define INCLUDE_BUFFERS_QUEUE_H_

#include "Buffer.h"
#include <Allocators/TAllocator.h>

#define QUEUE_NODE_SIZE sizeof(LinkedListNode)

/**
 * @struct Queue
 * @extends Buffer
 * @brief
 * 		A queue (FIFO) buffer.
 * @details
 * 		A queue (FIFO) buffer. The queue is initialized with a
 * 		specified size.
 */
Class( Queue ) Extends( Object )
	Public
	(
		Boolean (*insert)( self(Queue), void* );
		void* (*remove)( self(Queue) );
		void* (*peek)( self(Queue) );
		void (*reset)( self(Queue) );
		uint32_t (*length)( self(Queue) );
		uint32_t (*maxLength)( self(Queue) );
		Boolean (*isEmpty)( self(Queue) );
		Boolean (*isFull)( self(Queue) );
	);
	Private
	(
		TAllocator* allocator;
		LinkedListNode* absoluteTop;
		LinkedListNode* head;
		LinkedListNode* tail;
		uint32_t length;
		uint32_t maxLength;
	);
	SoftOverride
	(
		/* Destructor. */
		void (*destroy)( self(Object) );
	);
EndClass;

/**
 * @memberof Queue
 * @brief
 * 		Constructor.
 * @details
 * 		Constructor.
 * @param allocator[in]
 * 		This object is used to allocate memory for the queue. It must
 * 		be able to allocate blocks that are at least the size of
 * 		<b>QUEUE_NODE_SIZE</b>. In addition, it must remain valid in memory
 * 		for the duration the queue exists.
 * @param size
 * 		The initial size of the queue. If it fails to create a queue of this
 * 		size it will create the largest one it can. See <b>actual</b> for
 * 		how large the queue actually is.
 * @param actual[out]
 * 		Will contain the actual size allocated for the queue.
 * @returns
 * 		Always a valid pointer to a constructed queue.
 */
Queue* createQueue( self(Queue), TAllocator* allocator, uint32_t size, uint32_t* actual );

#endif /* INCLUDE_BUFFERS_QUEUE_H_ */
