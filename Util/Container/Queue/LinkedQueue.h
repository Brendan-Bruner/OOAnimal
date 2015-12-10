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
 * Nov. 2015
 */

#ifndef UTIL_CONTAINER_QUEUE_LINKEDQUEUE_H_
#define UTIL_CONTAINER_QUEUE_LINKEDQUEUE_H_

#include "../../ContainerConfig.h"

#if (configUSE_CLINKEDQUEUE == 1)
#include "Queue.h"
#include <Container/LinkedNode/LinkedNode.h>
#include <Memory/Allocator.h>

/**
 * @struct CLinkedQueue
 * @extends CQueue
 * @brief
 *		Implements a queue backed by a linked list.
 * @details
 *		Implements a queue backed by a linked list.
 *
 *		<b>Memory Usage</b>
 *		<ul>
 *		<li>RAM footprint:</li>
 *		</ul>
 *
 *		<b>Execution Time</b>
 *		<ul>
 *		<li>Insertion: O(1), even when queue is full and memory is added for new
 *		element</li>
 *		<li>Removal: O(1)</li>
 *		<li>Peeking: O(1)</li>
 *		<li>Capacity Increase: O(n), where n = increase in size</li>
 *		</ul>
 *
 *		<b>Implemented, from CContainer</b>
 *		<ul>
 *		<li>CContainer_GetIterator( )</li>
 *		<li>CContainer_Size( )</li>
 *		<li>CContainer_Reset( )</li>
 *		<li>CContainer_AddCapacity( )</li>
 *		</ul>
 *
 *		<b>Implemented, from CQueue</b>
 *		<ul>
 *		<li>CQueue_Insert( )</li>
 *		<li>CQueue_Remove( )</li>
 *		<li>CQueue_Peek( )</li>
 *		<li>CQueue_Size( )</li>
 *		</ul>
 * @attention
 *		configUSE_CLINKEDQUEUE must be defined as 1 for inclusion in the build. See ContainerConfig.h.
 */
struct CLinkedQueue
{
	/* Super class. */
	struct CQueue super;

	/* Overriding these methods: */
	void (*CDestructor)( struct CObject* );

	/* Member data. */
	struct CLinkedNode* 	head;
	struct CLinkedNode* 	tail;
	struct CLinkedNode*		endOfLinks;
	size_t 					size;
	struct CAllocator*		allocator;

};

/**
 * @memberof CLinkedQueue
 * @brief
 *		<b>Constructor</b>.
 * @details
 *		<b>Constructor</b>.
 *		The CLinkedQueue object is constructed to
 *		use dynamic memory allocation, ie, CMalloc( ) and CFree( ).
 * @param initSize
 *		The initial size of the queue. This is the initial number of elements
 *		the queue can hold before having to allocate more space.
 * @param actualSize[out]
 *		After construction, dereferencing this pointer will reveal how many
 *		elements were actually allocated. This must point to valid memory
 *		when the constructor is called. 
 */
struct CLinkedQueue* CLinkedQueue( struct CLinkedQueue*, size_t initSize, CAllocator* allocator );

#endif /* configUSE_CLINKEDQUEUE */
#endif /* UTIL_CONTAINER_QUEUE_LINKEDQUEUE_H_ */