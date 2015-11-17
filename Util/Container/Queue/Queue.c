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

#include <Container/Queue/Queue.h>


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
 * 			COTContainer_Add( COTCast(COTContainer, someQueue), someElement );
 * 		@endcode
 * 		Adds an element to the head of the queue. Has the
 * 		same effect as calling COTQueue_Insert( ).
 */
static Boolean add( self(COTContainer), void const* element )
{
	COTInterfaceOf(COTQueue);
	return COTQueue_Insert( self, element );
}
#endif

#if (configCONTAINER_ADD_ALL == 1) && (configCONTAINER_ITERATOR == 1) \
	&& (configUSE_ITERATOR == 1)
/**
 * @memberof COTQueue
 * @brief
 * 		<b>Implements</b> COTContainer_AddAll( ).
 * @details
 *		<b>Implements</b> COTContainer_AddAll( ).
 * 		@code
 *			extern COTQueue* someQueue;
 *			extern COTContainer* someContainer;
 * 			COTContainer_AddAll( COTCast(COTContainer, someQueue), someContainer );
 * 		@endcode
 */
static size_t addAll( self(COTContainer), COTContainer* container )
{
	COTInterfaceOf(COTQueue);
	COT_ASSERT(container);

	COTIterator* 	iter;
	size_t			count;

	/* Get an iterator. */
	iter = COTContainer_Iterator( container );
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
	COTDestroy( iter );
}
#endif

#if (configCONTAINER_ITERATOR == 1) && (configUSE_ITERATOR == 1)
	Iterator* (*iterator)( self(Container) );
#endif

#if (configCONTAINER_SIZE == 1)
	uint32_t (*size)( self(Container) );
#endif

#if (configCONTAINER_RESET == 1 )
	void (*reset)( self(Container) );
#endif

#if (configCONTAINER_IS_EMPTY == 1)
	Boolean (*isEmpty)( self(Container) );
#endif

#if (configCONTAINER_ADD_CAPACITY == 1)
	uint32_t (*addCapacity)( self(Container), uint32_t );
#endif

#endif /* configUSE_COTCONTAINER */

Boolean QueueInsert( self(Queue), void* element )
{
	VIRTUAL_METHOD( Queue, insert )( self, element );
}
static Boolean insert( self(Queue), void* );

void* QueueRemove( self(Queue) )
{
	VIRTUAL_METHOD( Queue, remove )( self );
}
static void* remove( self(Queue) );

#if (configQUEUE_PEEK == 1)
void* QueuePeek( self(Queue) )
{
	VIRTUAL_METHOD( Queue, peek )( self );
}
static void* peek( self(Queue) );
#endif


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
void COTQueueCreate_( self(COTQueue) )
{
	COTConstructorOf(COTQueue);

	/* Create the interfaces used by this class. */
	COTCreateInterface( COTContainer );

	/* Link all virtual methods. */
	LINK_VIRTUAL_METHOD( insert );
	LINK_VIRTUAL_METHOD( remove );
	#if (configQUEUE_PEEK == 1)
		LINK_VIRTUAL_METHOD( peek );
	#endif

	/* Link all interface methods. */

}
