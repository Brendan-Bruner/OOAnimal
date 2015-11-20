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
 * Oct 17, 2015
 */

#include "Queue.h"
 

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
#if (configUSE_COTCONTAINER == 1)
#if (configCOTCONTAINER_ADD == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_Add( ).
 * @details
 *		<b>Implements</b> COTContainer_Add( ).
 * 		@code
 *			extern COTQueue* someQueue;
 * 			COTContainer_Add( COTContainerCast(someQueue), someElement );
 * 		@endcode
 * 		Adds an element to the head of the queue. Has the
 * 		same effect as calling COTQueue_Insert( ).
 */
static Boolean add( self(COTContainer), void* element )
{
	COTInterfaceOf(COTQueue);
	return COTQueue_Insert( self, element );
}
#endif

#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1) \
	&& (configUSE_COTITERATOR == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_AddAll( ).
 * @details
 *		<b>Implements</b> COTContainer_AddAll( ).
 * 		@code
 *			extern COTQueue* someQueue;
 *			extern COTContainer* someContainer;
 * 			COTContainer_AddAll( COTContainerCast(someQueue), someContainer );
 * 		@endcode
 */
static size_t addAll( self(COTContainer), COTContainer* container )
{
	COTInterfaceOf(COTQueue);
	COT_ASSERT(container);

	COTIterator* 	iter;
	size_t			count;

	/* Get an iterator. */
	iter = COTContainer_GetIterator( container );
	if( iter == NULL )
	{
		/* Failed to get an iterator. */
		return 0;
	}

	/* Copy all the elements from the container into self. */
	count = 0;
	while( COTIterator_HasNext( iter ) )
	{
		if( !COTQueue_Insert(self, COTIterator_Next(iter)) )
		{
			/* Failed to insert element into queue. */
			break;
		}
		++count;
	}

	/* Destroy the iterator. */
	COTDestroy(COTIterator, iter);
	return count;
}
#endif

#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_GetIterator( ).
 * @details
 *		<b>Implements</b> COTContainer_GetIterator( ).
 * 		@code
 *			extern COTQueue* someQueue;
 * 			COTIterator* iter = COTContainer_GetIterator( COTContainerCast(someQueue) );
 *		@endcode
 * @attention
 *		Subclasses must provide an implementation.
 */
static COTIterator* iterator( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	(void) self;
	return NULL;
}
#endif

#if (configCOTCONTAINER_SIZE == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_Size( ).
 * @details
 *		<b>Implements</b> COTContainer_Size( ).
 *		@code
 *			extern COTQueue* someQueue;
 * 			size_t queueSize = COTContainer_Size( COTContainerCast(someQueue) );
 *		@endcode
 * @attention
 *		Subclasses must provide an implementation.
 */
static size_t size( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	(void) self;
	return 0;
}
#endif

#if (configCOTCONTAINER_RESET == 1 )
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_Reset( ).
 * @details
 *		<b>Implements</b> COTContainer_Reset( ).
 *		@code
 *			extern COTQueue* someQueue;
 * 			COTContainer_Reset( COTContainerCast(someQueue) );
 *		@endcode
 * @attention
 *		Subclasses must provide an implementation.
 */
static void reset( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	(void) self;
}
#endif

#if (configCOTCONTAINER_IS_EMPTY == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_IsEmpty( ).
 * @details
 *		<b>Implements</b> COTContainer_IsEmpty( ).
 *		@code
 *			extern COTQueue* someQueue;
 * 			Boolean isEmpty = COTContainer_IsEmpty( COTContainerCast(someQueue) );
 *		@endcode
 * @attention
 *		Subclasses must provide an implementation.
 */
static Boolean isEmpty( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	(void) self;
	return true;
}
#endif

#if (configCOTCONTAINER_ADD_CAPACITY == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_AddCapacity( ).
 * @details
 *		<b>Implements</b> COTContainer_AddCapacity( ).
 *		@code
 *			extern COTQueue* someQueue;
 * 			Boolean isEmpty = COTContainer_AddCapacity( COTContainerCast(someQueue) );
 *		@endcode
 * @attention
 *		Subclasses must provide an implementation.
 */
static size_t addCapacity( self(COTContainer), size_t capacity )
{
	COTInterfaceOf(COTQueue);
	(void) self;
	(void) capacity;
	return 0;
}
#endif

#endif /* configUSE_COTCONTAINER */

Boolean COTQueue_Insert( self(COTQueue), void* element )
{
	COTCallVirtual(COTQueue, insert)( self, element );
}
static Boolean insert( self(COTQueue), void* element )
{
	COTMemberOf(COTQueue);
	(void) self;
	(void) element;
	return false;
}

void* COTQueue_Remove( self(COTQueue) )
{
	COTCallVirtual(COTQueue, removeElement)( self );
}
static void* removeElement( self(COTQueue) )
{
	COTMemberOf(COTQueue);
	(void) self;
	return NULL;
}

#if (configCOTQUEUE_PEEK == 1)
void* COTQueue_Peek( self(COTQueue) )
{
	COTCallVirtual(COTQueue, peek)( self );
}
static void* peek( self(COTQueue) )
{
	COTMemberOf(COTQueue);
	(void) self;
	return NULL;
}
#endif


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
void COTQueueCreate_( self(COTQueue) )
{
	COTConstructorOf(COTQueue);

	/* Create the interfaces used by this class. */
	COTCreateInterface(COTContainer);

	/* Link all virtual methods. */
	/* Methods gained from COTContainer interface. */
	#if (configUSE_COTCONTAINER == 1)
	#if (configCOTCONTAINER_ADD == 1)
	COTLinkVirtual(COTQueue, COTContainer, add);
	#endif
	#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1)	&& (configUSE_COTITERATOR == 1)
	COTLinkVirtual(COTQueue, COTContainer, addAll);
	#endif
	#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
	COTLinkVirtual(COTQueue, COTContainer, iterator);
	#endif
	#if (configCOTCONTAINER_SIZE == 1)
	COTLinkVirtual(COTQueue, COTContainer, size);
	#endif
	#if (configCOTCONTAINER_RESET == 1)
	COTLinkVirtual(COTQueue, COTContainer, reset);
	#endif
	#if (configCOTCONTAINER_IS_EMPTY == 1)
	COTLinkVirtual(COTQueue, COTContainer, isEmpty);
	#endif
	#if (configCOTCONTAINER_ADD_CAPACITY == 1)
	COTLinkVirtual(COTQueue, COTContainer, addCapacity);
	#endif
	#endif /* configUSE_COTCONTAINER */	

	/* COTQueue virtual methods. */
	COTLinkVirtual(COTQueue, insert);
	COTLinkVirtual(COTQueue, removeElement);
	#if (configCOTQUEUE_PEEK == 1)
	COTLinkVirtual(COTQueue, peek);
	#endif
}
