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
	InterfaceOf(Queue);
	return self->insert( self, element );
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
	InterfaceOf(Queue);
	objASSERT(container);

	Iterator* 	iter;
	uint32_t	count;

	/* Get an iterator. */
	iter = container->iterator(container);
	if( iter == NULL )
	{
		/* Failed to get an iterator. */
		return 0;
	}

	/* Copy all the elements from the container into self. */
	count = 0;
	while( iter->hasNext(iter) )
	{
		self->insert( self, iter->next(iter) );
		++count;
		/* TODO: error check insert. */
	}

	/* Destroy the iterator. */
	((Object*) iter)->destroy((Object*) iter);
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
static Boolean push( self(Buffer), void* element )
{

}

static void* pop( self(Buffer) )
{

}

static void* peek( self(Buffer) )
{

}

static void reset( self(Buffer) )
{
	MemberOf(Queue);
	private( ).head = private( ).tail;
	protected(Buffer).length = 0;
}


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
Queue* createQueue_
(
	self(Queue),
	TAllocator* allocator,
	uint32_t size,
	uint32_t* actual
)
{
	/* Virtual function linkage and super class creation. */
	MemberOf(Queue);
	objASSERT( allocator );
	createObject( (Object*) self );
	LinkMethod( push );
	LinkMethod(pop );
	LinkMethod(peek );
	LinkMethod(reset );
	SoftOverrideMethod( Object, destroy );

	/* Beginning of constructor. */
	LinkedListNode* currentNode;
	LinkedListNode*	previousNode;
	uint32_t iter;

	/* Set up member data. */
	private( ).allocator = allocator;

	/* If, for some reason, a queue of size zero is being constructed, */
	/* return now. */
	if( size == 0 ){ return self; }

	/* Allocate first node. If this fails, the queue is of size 0. */
	previousNode = allocator->malloc( allocator, sizeof(LinkedListNode) );
	if( previousNode == NULL ){ return self; }
	private( ).tail = previousNode;
	private( ).head = previousNode;

	/* Begin allocating the rest of the nodes. */
	for( iter = 1; iter < size; ++iter )
	{
		currentNode = allocator->malloc( allocator, sizeof(LinkedListNode) );
		if( currentNode == NULL ){ break; }

		/* Concatenate the nodes. */
		LLNSetNext( previousNode, currentNode );
		previousNode = currentNode;
	}

	/* Now we know the absolute top node and the maximum size of the queue. */
	private( ).absoluteTop = currentNode;
	protected(Buffer).maxLength = iter;

	return self;
}
