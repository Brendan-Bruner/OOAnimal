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
#ifndef UTIL_CONTAINER_QUEUE_QUEUE_H_
#define UTIL_CONTAINER_QUEUE_QUEUE_H_

#include "../../ContainerConfig.h"

#if (configUSE_CQUEUE == 1)

#include <Class.h>
#include <Boolean.h>

#if (configUSE_CCONTAINER == 1)
#include <Container/Container.h>
/**
 * @struct CQueue
 * @implements CContainer
 */
#endif
/**
 * @struct CQueue
 * @extends CObject
 * @brief
 * 		Abstract class for all FIFO containers.
 * @details
 * 		Abstract class for all FIFO like containers.
 * 		Defines an insert, remove, and peek operation. It uses
 * 		the Container interface if configUSE_CCONTAINER is set to 1.
 *
 *		<b>Implemented, from CContainer</b>
 *		<ul>
 *		<li>CContainer_Add( )</li>
 *		<li>CContainer_AddAll( )</li>
 *		</ul>
 *
 *		<b>Pure Virtual Methods</b>
 *		<ul>
 *		<li>CQueue_Insert( )</li>
 *		<li>CQueue_Remove( )</li>
 *		<li>CQueue_Peek( )</li>
 *		<li>CQueue_Size( )</li>
 *		</ul>
 * @attention
 * 		configUSE_CQUEUE must be defined as 1 for this class to be included.
 *		See ContainerConfig.h.
 */
struct CQueue
{
	/* Super class. */
	struct CObject object;

	/* Interfaces. */
	#if (configUSE_CCONTAINER == 1)
	struct CContainer container;
	#endif

	/* Virtual Methods. */
	Boolean (*CQueueVirtual_Insert)( struct CQueue*, void* );
	void* (*CQueueVirtual_Remove)( struct CQueue* );
	void* (*CQueueVirtual_Peek)( struct CQueue* );
	#if (configCQUEUE_SIZE == 1)
	size_t (*CQueueVirtual_Size)( struct CQueue* );
	#endif
};

/**
 * @memberof CQueue
 * @brief
 *		Insert an element into the queue.
 * @details
 *		Insert an element into the queue. 
 * @param element[in]
 *		A pointer which is copied into the head of the queue. The data
 *		pointed to is untouched.
 * @returns
 *		<b>true</b> when the element is successfully added to the
 *		queue, <b>false</b> otherwise. 
 */
Boolean CQueue_Insert( struct CQueue*, void* element );

/**
 * @memberof CQueue
 * @brief
 *		Remove an element from the tail of the queue.
 * @details
 *		Remove an element from the tail of the queue.
 * @returns
 *		The element removed from the tail of the queue. <b>NULL</b> if
 *		the queue is empty.
 */
void* CQueue_Remove( struct CQueue* );

/**
 * @memberof CQueue
 * @brief
 * 		Peek at the element in the tail of the queue.
 * @details
 *		Peek at the element in the tail of the queue. This does not
 *		remove the element from the queue.
 * @attention
 *		configCQUEUE_PEEK must be defined as one for this method to be
 *		included in the build. See ContainerConfig.h.
 * @returns
 *		The element in the tail of the queue. <b>NULL</b> if the queue is empty.
 */
void* CQueue_Peek( struct CQueue* );

#if (configCQUEUE_SIZE == 1)
/**
 * @memberof CQueue
 * @brief
 * 		Get the current size of the queue.
 * @details
 *		Get the current size of the queue, ie, how many elements
 *		have been inserted in it.
 * @returns
 *		The actual size of the queue.
 */
size_t CQueue_Size( struct CQueue* );
#endif /* configCQUEUE_SIZE */

/**
 * @memberof CQueue
 * @protected
 * @brief
 *		<b>Constructor.</b>
 * @details
 *		<b>Constructor.</b>
 */
struct CQueue* CQueue_( struct CQueue* );

#endif /* configUSE_CQUEUE */
#endif /* UTIL_CONTAINER_QUEUE_QUEUE_H_ */
