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
#ifndef INCLUDE_QUEUE_QUEUE_H_
#define INCLUDE_QUEUE_QUEUE_H_

#include "../../ContainerConfig.h"

#if (configUSE_COTQUEUE == 1)

#include <Class.h>
#include <Boolean.h>

#if (configUSE_COTCONTAINER == 1)
#include <Container/Container.h>
/**
 * @struct COTQueue
 * @extends COTContainer
 */
#endif
/**
 * @struct COTQueue
 * @brief
 * 		Abstract class for all FIFO containers.
 * @details
 * 		Abstract class for all FIFO like containers.
 * 		Defines an insert, remove, and peek operation. It uses
 * 		the Container interface if configUSE_COTCONTAINER is set to 1.
 *
 *		<b>Implemented, from COTContainer</b>
 *		<ul>
 *		<li>COTContainer_Add( )</li>
 *		<li>COTContainer_AddAll( )</li>
 *		</ul>
 * @attention
 * 		configUSE_COTQUEUE must be defined as 1 for this class to be included.
 *		See ContainerConfig.h.
 */
COTClass( COTQueue )
#if (configUSE_COTCONTAINER == 1)
COTImplements( COTContainer )
#endif
	COTVirtual
	(
		Boolean (*COTQueueVirtual_Insert)( self(COTQueue), void* );
		void* (*COTQueueVirtual_Remove)( self(COTQueue) );
		#if (configCOTQUEUE_PEEK == 1)
			void* (*COTQueueVirtual_Peek)( self(COTQueue) );
		#endif
		#if (configCOTQUEUE_SIZE == 1)
			size_t (*COTQueueVirtual_Size)( self(COTQueue) );
		#endif
	)
COTClassEnd

typedef struct COTQueue
{
	COTClass( COTObject );
	#if (configUSE_COTCONTAINER == 1)
	COTInterface( COTContainer )
	#endif

	Boolean (*COTQueueVirtual_Insert)( self(COTQueue), void* );
	void* (*COTQueueVirtual_Remove)( self(COTQueue) );
	#if (configCOTQUEUE_PEEK == 1)
	void* (*COTQueueVirtual_Peek)( self(COTQueue) );
	#endif
	#if (configCOTQUEUE_SIZE == 1)
	size_t (*COTQueueVirtual_Size)( self(COTQueue) );
	#endif
} COTQueue;

/**
 * @memberof COTQueue
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
Boolean COTQueue_Insert( self(COTQueue), void* element );

/**
 * @memberof COTQueue
 * @brief
 *		Remove an element from the tail of the queue.
 * @details
 *		Remove an element from the tail of the queue.
 * @returns
 *		The element removed from the tail of the queue. <b>NULL</b> if
 *		the queue is empty.
 */
void* COTQueue_Remove( self(COTQueue) );

#if (configCOTQUEUE_PEEK == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		Peek at the element in the tail of the queue.
 * @details
 *		Peek at the element in the tail of the queue. This does not
 *		remove the element from the queue.
 * @attention
 *		configCOTQUEUE_PEEK must be defined as one for this method to be
 *		included in the build. See ContainerConfig.h.
 * @returns
 *		The element in the tail of the queue. <b>NULL</b> if the queue is empty.
 */
void* COTQueue_Peek( self(COTQueue) );
#endif /* configCOTQUEUE_PEEK */

#if (configCOTQUEUE_SIZE == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		Get the current size of the queue.
 * @details
 *		Get the current size of the queue, ie, how many elements
 *		have been inserted in it.
 * @returns
 *		The actual size of the queue.
 */
size_t COTQueue_Size( self(COTQueue) );
#endif /* configCOTQUEUE_SIZE */

/**
 * @memberof COTQueue
 * @protected
 * @brief
 *		<b>Constructor.</b>
 * @details
 *		<b>Constructor.</b>
 */
void COTQueueCreate_( self(COTQueue) );


#endif /* configUSE_COTQUEUE */
#endif /* INCLUDE_QUEUE_QUEUE_H_ */
