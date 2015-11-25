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

 #include "LinkedQueue.h"
 #include <Memory/DynamicAllocator.h>


/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
 /**
  * @memberof COTLinkedQueue
  * @private
  * @brief
  *		Add capacity to the linked queue.
  * @details
  *		Add capacity to the linked queue.
  * @param capacity
  *		The amount of capacity to add.
  * @returns
  *		The amount of capacity actually added.
  */
 static size_t COTLinkedQueue_AddCapacity( self(COTLinkedQueue), size_t capacity )
 {
 	COTMemberOf(COTLinkedQueue);
 	(void) capacity;
 	(void) self;
 	return 0;
 }

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
 #if (configUSE_COTCONTAINER == 1)
 #if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
static COTIterator* iterator( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	(void) self;
	return NULL;
}
#endif

#if (configCOTCONTAINER_SIZE == 1)
static size_t size( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	return self->_.size;
}
#endif

#if (configCOTCONTAINER_RESET == 1 )
static void reset( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	self->_.head = self->_.tail;
}
#endif

#if (configCOTCONTAINER_IS_EMPTY == 1)
static Boolean isEmpty( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	if( self->_.size == 0 )
	{
		return true;
	}
	return false;
}
#endif

#if (configCOTCONTAINER_ADD_CAPACITY == 1)
static size_t addCapacity( self(COTContainer), size_t capacity )
{
	COTInterfaceOf(COTLinkedQueue);
	return COTLinkedQueue_AddCapacity( self, capacity );
}
#endif

#endif /* configUSE_COTCONTAINER */

/**
 * @memberof COTLinkedQueue
 * @brief
 *		<b>Implements</b> COTQueue_Insert( ).
 * @details
 *		<b>Implements</b> COTQueue_Insert( ).
 *		<br>This method always has O(1) insertion time, even if memory
 *		has to be allocated.
 *		<br>When the queue is full, space is allocated for one
 *		additional element. If allocation is successful, the element
 *		is inserted. To allocate more space at one time, see
 *		COTContainer_AddCapacity( ).
 *		@code
 *			extern COTLinkedQueue* someQueue;
 *			extern void* someElement;
 *			COTQueue_Insert( (COTQueue*) someQueue, someElement );
 *		@endcode
 */
static Boolean insert( self(COTQueue), void* element )
{
	COTMemberOf(COTLinkedQueue);
	
	#define ADD_ONE_CAPACITY 1

	if( element == NULL )
	{
		return false;
	}

	if( self->_.head == NULL )
	{
		/* Queue is full. Add capacity */
		if( COTLinkedQueue_AddCapacity( self, ADD_ONE_CAPACITY ) != ADD_ONE_CAPACITY )
		 {
		 	/* Can't add more capacity. */
		 	return false;
		 }
	}

	/* If capacity was added, head cannot be NULL anymore. */
	COTLinkedListNode_SetData( self->_.head, element );
	/* Move head to next node. */
	self->_.head = COTLinkedListNode_GetNext( self->_.head );

	return true;
}

/**
 * @memberof COTLinkedQueue
 * @brief
 *		<b>Implements</b> COTQueue_Remove( ).
 * @details
 *		<b>Implements</b> COTQueue_Remove( ).
 *		<br>This method always has O(1) removal time.
 *		@code
 *			extern COTLinkedQueue* someQueue;
 *			void* removedElement = COTQueue_Remove( (COTQueue*) someQueue );
 *		@endcode
 */
static void* removeElement( self(COTQueue) )
{
	COTMemberOf(COTLinkedQueue);

	void* element;

	if( self->_.tail == NULL )
	{
		/* Queue of size 0. */
		return NULL;
	}

	if( self->_.tail == self->_.head )
	{
		/* Queue has no data in it. */
		return NULL;
	}

	/* Get the data to return. */
	element = COTLinkedListNode_GetData( self->_.tail );
	/* Set nodes new data to NULL. */
	COTLinkedListNode_SetData( self->_.tail, NULL );

	/* The following code will increment the tail to the next node. It will also */
	/* recycle the old tail node by appending it to the end of the list and making */
	/* that the new end of list. */
	/* The tail node needs to be moved, mode it to the end of the list. */
	COTLinkedListNode_SetNext( self->_.endOfLinks, self->_.tail );
	/* Update the new end of list. */
	self->_.endOfLinks = self->_.tail;
	/* Update the new tail. */
	self->_.tail = COTLinkedListNode_GetNext( self->_.tail );
	/* The new end of list should not have a next node. */
	COTLinkedListNode_SetNext( self->_.endOfLinks, NULL );

	return element;
} 

#if (configCOTQUEUE_PEEK == 1)
/**
 * @memberof COTLinkedQueue
 * @brief
 *		<b>Implements</b> COTQueue_Peek( ).
 * @details
 *		<b>Implements</b> COTQueue_Peek( ).
 *		<br>This method always has O(1) time.
 *		@code
 *			extern COTLinkedQueue* someQueue;
 *			void* tail = COTQueue_Peek( (COTQueue*) someQueue );
 *		@endcode
 */
static void* peek( self(COTQueue) )
{
	COTMemberOf(COTLinkedQueue);

	if( self->_.tail == NULL )
	{
		/* Queue of size zero. */
		return NULL;
	}
	if( self->_.tail == self->_.head )
	{
		/* Queue is empty. */
		return NULL;
	}
	return COTLinkedListNode_GetData( self->_.tail );
}
#endif


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
/**
 * @memberof COTLinkedQueue
 * @private
 * @brief
 * 		Internal constructor for linked queue.
 * @details
 *		Internal constructor for linked queue. To be called by constructor only.
 */
static size_t COTLinkedQueue_InternalConstructor( self(COTLinkedQueue), size_t initSize )
{
	COTMemberof(COTLinkedQueue);

	COTLinkedListNode* node1;
	COTLinkedListNode* node2;
	size_t iter;

	if( initSize == 0 )
	{
		return 0;
	}

	/* Allocate first node. */
	node1 = COTAllocator_Malloc( self->_.allocator, sizeof(COTLinkedListNode) );
	if( node1 == NULL )
	{
		return 0;
	}
	/* Construct first node. */
	COTCreate( node1, COTLinkedListNodeCreate( node1 ) );
	/* Head of the queue is this node. */
	self->_.head = node1;

	for( iter = 0; iter < initSize; ++iter )
	{
		/* Allocate nodes unil desired queue size is reached. */
		node2 = COTAllocator_Malloc( self->_.allocator, sizeof(COTLinkedListNode) );
		if( node == NULL )
		{
			/* Failed to allocate node. */
			break;
		}
		COTCreate( node2, COTLinkedListNodeCreate( node2 ) );

		/* Continue to create linked list until desired queue size is reached. */
		COTLinkedListNode_SetNext( node1, node2 );
		node1 = node2;

	}
	
	/* Keep a reference to the end of the list. */
	/* For example: */
	/* nodeA -> nodeB -> nodeC -> nodeD -> ... -> nodeQ */
	/* the head is nodeA and the end of the list is nodeQ. */
	self->_.endOfLinks = node1;

	/* There should be no next node after the end of the list. */
	COTLinkedListNode_SetNext( node1, NULL );

	/* Return the number of nodes created. */
	return iter;
}

COTVirtualDestructor( )
{
	COTDestructorOf(COTLinkedQueue);



	COTSuper( destroy )( (COTObject*) self );
}

void COTLinkedQueueDynamic( self(COTLinkedQueue), size_t initSize, size_t* actualSize )
{
	COTConstructorOf(COTLinkedQueue);

	/* Link virtual interface methods. */
	#if (configUSE_COTCONTAINER == 1)
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

	/* Link virtual queue methods. */
	COTLinkVirtual(COTQueue, insert);
	COTLinkVirtual(COTQueue, removeElement);
	#if (configCOTQUEUE_PEEK == 1)
	COTLinkVirtual(COTQueue, peek);
	#endif	

	/* Override destructor. */
	COTOverrideDestructor( );

	/* Set up member data. */
	self->_.allocator = COTAllocatorCast( COTDynamicAllocator_GetInstance( ) );
	self->_.tail = NULL;
	self->_.head = NULL;
	self->_.endOfLinks = NULL;

	/* Setup linked list. */
	if( actualSize == NULL )
	{
		COTLinkedQueue_InternalConstructor( self, initSize );
	}
	else
	{
		*actualSize = COTLinkedQueue_InternalConstructor( self, initSize );
	}
}