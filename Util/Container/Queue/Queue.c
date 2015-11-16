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

#include <Queue/Queue.h>


/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
#if (configUSE_CONTAINER == 1)
#if (configCONTAINER_ADD == 1)
/**
 * @memberof Queue
 * @brief
 * 		Adds an element to the head of the queue.
 * @details
 * 		@code
 * 			interface( Container, self )->add( );
 * 		@endcode
 * 		Adds an element to the head of the queue. Has the
 * 		same effect as calling Queue::insert( ).
 * @attention Implementation of Container::add( ).
 */
static Boolean add( self(Container), void* element )
{
	INTERFACE_OF(Queue);
	return QueueInsert( self, element );
}
#endif

#if (configCONTAINER_ADD_ALL == 1) && (configCONTAINER_ITERATOR == 1) \
	&& (configUSE_ITERATOR == 1)
/**
 * @memberof Queue
 * @brief
 * 		Adds all elements from the container to the queue.
 * @details
 * 		@code
 * 			interface( Container, self )->addAll( );
 * 		@endcode
 */
static uint32_t addAll( self(Container), Container* container )
{
	INTERFACE_OF(Queue);
	objASSERT(container);

	Iterator* 	iter;
	uint32_t	count;

	/* Get an iterator. */
	iter = ContainerIterator( container );
	if( iter == NULL )
	{
		/* Failed to get an iterator. */
		return 0;
	}

	/* Copy all the elements from the container into self. */
	count = 0;
	while( IteratorHasNext( iter ) )
	{
		if( !QueueInsert(self, IteratorNext(iter)) )
		{
			break;
		}
		++count;
	}

	/* Destroy the iterator. */
	destroy( iter );
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
#endif

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
/**
 * @memberof Queue
 * @protected
 * @brief
 * 		Constructor for abstract Queue class.
 * @details
 * 		Constructor for abstract Queue class.
 */
void createQueue_( self(Queue) )
{
	CONSTRUCTOR_OF(Queue);

	/* Create the interfaces used by this class. */
	CREATE_INTERFACE( Container );

	/* Link all virtual methods. */
	LINK_VIRTUAL_METHOD( insert );
	LINK_VIRTUAL_METHOD( remove );
	#if (configQUEUE_PEEK == 1)
		LINK_VIRTUAL_METHOD( peek );
	#endif

	/* Link all interface methods. */

}
