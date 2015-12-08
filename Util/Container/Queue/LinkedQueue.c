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

 	CLinkedNode* node1;
 	CLinkedNode* node2;
 	size_t iter;

 	/* Validate the increase in capacity. */
 	if( capacity == 0 )
 	{
 		return 0;
 	}

 	/* If the queue was initially size zero, allocate its first element. */
 	iter = capacity;
 	if( self->_.endOfLinks == NULL )
 	{
 		--iter;
 		self->_.endOfLinks = (CLinkedNode*) COTAllocator_Malloc( self->_.allocator, sizeof(CLinkedNode) );
 		if( self->_.endOfLinks == NULL )
 		{
 			return 0;
 		}
 		COTCreate(self->_.endOfLinks, CLinkedNodeCreate( self->_.endOfLinks ));
 		self->_.head = self->_.endOfLinks;
 	}	

 	/* Begin allocating the reset of the requested elements. */
 	node1 = self->_.endOfLinks;
 	for(; iter > 0; --iter )
 	{
 		node2 = (CLinkedNode*) COTAllocator_Malloc( self->_.allocator, sizeof(CLinkedNode) );
 		if( node2 == NULL ){ break; }	
 		COTCreate(node2, CLinkedNodeCreate( node2 ));
 		CLinkedNode_SetNext( node1, node2 );
 		node1 = node2;	
 	}
 	self->_.endOfLinks = node1;

 	return capacity - iter;
 }

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
 #if (configUSE_COTCONTAINER == 1)
 #if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
static COTIterator* COTContainerVirtual_GetIterator( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	(void) self;
	return NULL;
}
#endif

#if (configCOTCONTAINER_SIZE == 1)
static size_t COTContainerVirtual_Size( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	return self->_.size;
}
#endif

#if (configCOTCONTAINER_RESET == 1 )
static void COTContainerVirtual_Reset( self(COTContainer) )
{
	COTInterfaceOf(COTLinkedQueue);
	self->_.head = self->_.tail;
}
#endif

#if (configCOTCONTAINER_IS_EMPTY == 1)
static Boolean COTContainerVirtual_IsEmpty( self(COTContainer) )
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
static size_t COTContainerVirtual_AddCapacity( self(COTContainer), size_t capacity )
{
	COTInterfaceOf(COTLinkedQueue);
	return COTLinkedQueue_AddCapacity( self, capacity );
}
#endif

#endif /* configUSE_COTCONTAINER */

static Boolean COTQueueVirtual_Insert( self(COTQueue), void* element )
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
	CLinkedNode_SetData( self->_.head, element );
	/* Move head to next node. */
	self->_.head = CLinkedNode_GetNext( self->_.head );
	/* Size of the queue increased. */
	++self->_.size;

	return true;
}

static void* COTQueueVirtual_Remove( self(COTQueue) )
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
	element = CLinkedNode_GetData( self->_.tail );
	/* Set nodes new data to NULL. */
	CLinkedNode_SetData( self->_.tail, NULL );

	/* The following code will increment the tail to the next node. It will also */
	/* recycle the old tail node by appending it to the end of the list and making */
	/* that the new end of list. */
	/* The tail node needs to be moved, mode it to the end of the list. */
	CLinkedNode_SetNext( self->_.endOfLinks, self->_.tail );
	/* Update the new end of list. */
	self->_.endOfLinks = self->_.tail;
	/* Update the new tail. */
	self->_.tail = CLinkedNode_GetNext( self->_.tail );
	/* The new end of list should not have a next node. */
	CLinkedNode_SetNext( self->_.endOfLinks, NULL );
	/* Size of the queue decreased. */
	--self->_.size;

	return element;
} 

#if (configCOTQUEUE_PEEK == 1)
static void* COTQueueVirtual_Peek( self(COTQueue) )
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
	return CLinkedNode_GetData( self->_.tail );
}
#endif

#if (configCOTQUEUE_SIZE == 1)
static size_t COTQueueVirtual_Size( self(COTQueue) )
{
	COTMemberOf(COTLinkedQueue);
	return self->_.size;
}
#endif /* configCOTQUEUE_SIZE */

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
	COTMemberOf(COTLinkedQueue);

	CLinkedNode* node1;
	CLinkedNode* node2;
	size_t iter;

	if( initSize == 0 )
	{
		return 0;
	}

	/* Allocate first node. */
	node1 = COTAllocator_Malloc( self->_.allocator, sizeof(CLinkedNode) );
	if( node1 == NULL )
	{
		return 0;
	}
	/* Construct first node. */
	COTCreate( node1, CLinkedNodeCreate( node1 ) );
	/* Head of the queue is this node. */
	self->_.head = node1;
	/* Will also be the tail. */
	self->_.tail = node1;

	for( iter = 0; iter < initSize; ++iter )
	{
		/* Allocate nodes unil desired queue size is reached. */
		node2 = COTAllocator_Malloc( self->_.allocator, sizeof(CLinkedNode) );
		if( node2 == NULL )
		{
			/* Failed to allocate node. */
			break;
		}
		COTCreate( node2, CLinkedNodeCreate( node2 ) );

		/* Continue to create linked list until desired queue size is reached. */
		CLinkedNode_SetNext( node1, node2 );
		node1 = node2;

	}
	
	/* Keep a reference to the end of the list. */
	/* For example: */
	/* nodeA -> nodeB -> nodeC -> nodeD -> ... -> nodeQ */
	/* the head is nodeA and the end of the list is nodeQ. */
	self->_.endOfLinks = node1;

	/* There should be no next node after the end of the list. */
	CLinkedNode_SetNext( node1, NULL );

	/* Return the number of nodes created. */
	return iter;
}

COTVirtualDestructor( )
{
	COTDestructorOf(COTLinkedQueue);

	CLinkedNode* node;
	CLinkedNode* nextNode;

	node = self->_.tail;
	if( node == NULL )
	{
		/* No nodes to destroy. */
		COTSuperDestructor( );
		return;
	}
	
	do
	{
		nextNode = CLinkedNode_GetNext( node );
		COTDestroy( CLinkedNode, node );
		node = nextNode;
	}
	while( node != NULL );

	COTSuperDestructor( );
}

void COTLinkedQueueDynamic( self(COTLinkedQueue), size_t initSize, size_t* actualSize )
{
	COTConstructorOf(COTLinkedQueue);

	/* Call super's constructor. */
	COTQueueCreate_( (COTQueue*) self );

	/* Link virtual interface methods. */
	#if (configUSE_COTCONTAINER == 1)
	#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_GetIterator);
	#endif
	#if (configCOTCONTAINER_SIZE == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_Size);
	#endif
	#if (configCOTCONTAINER_RESET == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_Reset);
	#endif
	#if (configCOTCONTAINER_IS_EMPTY == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_IsEmpty);
	#endif
	#if (configCOTCONTAINER_ADD_CAPACITY == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_AddCapacity);
	#endif
	#endif /* configUSE_COTCONTAINER */

	/* Link virtual queue methods. */
	COTLinkVirtual(COTQueue, COTQueueVirtual_Insert);
	COTLinkVirtual(COTQueue, COTQueueVirtual_Remove);
	#if (configCOTQUEUE_PEEK == 1)
	COTLinkVirtual(COTQueue, COTQueueVirtual_Peek);
	#endif	
	#if (configCOTQUEUE_SIZE == 1)
	COTLinkVirtual(COTQueue, COTQueueVirtual_Size);
	#endif

	/* Override destructor. */
	COTOverrideDestructor( );

	/* Set up member data. */
	self->_.allocator = COTAllocatorCast( COTDynamicAllocator_GetInstance( ) );
	self->_.tail = NULL;
	self->_.head = NULL;
	self->_.endOfLinks = NULL;
	self->_.size = 0;

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