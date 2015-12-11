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

#if (configUSE_CLINKEDQUEUE == 1 && configUSE_CQUEUE == 1)
/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
 /**
  * @memberof CLinkedQueue
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
static size_t CLinkedQueue_AddCapacity( struct CLinkedQueue* self, size_t capacity )
{
	CMethod(self);

	struct CLinkedNode* node1;
 	struct CLinkedNode* node2;
 	size_t iter;

 	/* Validate the increase in capacity. */
 	if( capacity == 0 )
 		return 0;

 	/* If the queue was initially size zero, allocate its first element. */
 	iter = capacity;
 	if( self->endOfLinks == NULL )
 	{
 		--iter;
 		self->endOfLinks = self->nodeMalloc(sizeof(*self->endOfLinks));
 		if( self->endOfLinks == NULL )
 			return 0;
 		if( CLinkedNode( self->endOfLinks ) == NULL ) { /* If construction failed. */
 			self->nodeFree(self->endOfLinks);
 			return 0;
 		}
 		CFreeWith(self->endOfLinks, self->nodeFree);
 		self->head = self->endOfLinks;
 	}	

 	/* Begin allocating the reset of the requested elements. */
 	node1 = self->_.endOfLinks;
 	for(; iter > 0; --iter )
 	{
 		node2 = (CLinkedNode*) CAllocator_Malloc( self->_.allocator, sizeof(CLinkedNode) );
 		if( node2 == NULL ){ break; }	
 		CCreate(node2, CLinkedNodeCreate( node2 ));
 		CLinkedNode_SetNext( node1, node2 );
 		node1 = node2;	
 	}
 	self->_.endOfLinks = node1;

 	return capacity - iter;
 }

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
 #if (configUSE_CCONTAINER == 1)
 #if (configCCONTAINER_ITERATOR == 1) && (configUSE_CITERATOR == 1)
static CIterator* CContainerVirtual_GetIterator( self(CContainer) )
{
	CInterfaceOf(CLinkedQueue);
	(void) self;
	return NULL;
}
#endif

#if (configCCONTAINER_SIZE == 1)
static size_t CContainerVirtual_Size( self(CContainer) )
{
	CInterfaceOf(CLinkedQueue);
	return self->_.size;
}
#endif

#if (configCCONTAINER_RESET == 1 )
static void CContainerVirtual_Reset( self(CContainer) )
{
	CInterfaceOf(CLinkedQueue);
	self->_.head = self->_.tail;
}
#endif

#if (configCCONTAINER_IS_EMPTY == 1)
static Boolean CContainerVirtual_IsEmpty( self(CContainer) )
{
	CInterfaceOf(CLinkedQueue);
	if( self->_.size == 0 )
	{
		return true;
	}
	return false;
}
#endif

#if (configCCONTAINER_ADD_CAPACITY == 1)
static size_t CContainerVirtual_AddCapacity( self(CContainer), size_t capacity )
{
	CInterfaceOf(CLinkedQueue);
	return CLinkedQueue_AddCapacity( self, capacity );
}
#endif

#endif /* configUSE_CCONTAINER */

static Boolean CQueueVirtual_Insert( self(CQueue), void* element )
{
	CMemberOf(CLinkedQueue);
	
	#define ADD_ONE_CAPACITY 1

	if( element == NULL )
	{
		return false;
	}

	if( self->_.head == NULL )
	{
		/* Queue is full. Add capacity */
		if( CLinkedQueue_AddCapacity( self, ADD_ONE_CAPACITY ) != ADD_ONE_CAPACITY )
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

static void* CQueueVirtual_Remove( self(CQueue) )
{
	CMemberOf(CLinkedQueue);

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

#if (configCQUEUE_PEEK == 1)
static void* CQueueVirtual_Peek( self(CQueue) )
{
	CMemberOf(CLinkedQueue);

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

#if (configCQUEUE_SIZE == 1)
static size_t CQueueVirtual_Size( self(CQueue) )
{
	CMemberOf(CLinkedQueue);
	return self->_.size;
}
#endif /* configCQUEUE_SIZE */

/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
static void CDestructor( struct CObject* self_ )
{
	struct CLinkedQueue* self = CCast(self_);

	if( self->usingDynamicNodes ) {
		/* Using dynamic nodes, need to free them. */
		/* TODO */
	}

	CAssertSuper(self, CDestructor);
	self->CDestructor(self);
}

/**
 * @memberof CLinkedQueue
 * @private
 * @brief
 * 		Link the methods used by CLinkedQueue.
 * @details
 *		Link the methods used by CLinkedQueue.
 */
static void CLinkedQueue_LinkMethod( struct CLinkedQueue* self )
{
	CMethod(self);

		/* Link virtual interface methods. */
	#if (configUSE_CCONTAINER == 1)
	#if (configUSE_CITERATOR == 1)
	CLinkVirtual(&self->queue.container, CContainerVirtual_GetIterator);
	#endif
	#if (configCCONTAINER_EXTRA == 1)
	CLinkVirtual(&self->queue.container, CContainerVirtual_Size);
	CLinkVirtual(&self->queue.container, CContainerVirtual_Reset);
	CLinkVirtual(&self->queue.container, CContainerVirtual_AddCapacity);
	#endif /* configCCONTAINER_EXTRA */
	#endif /* configUSE_CCONTAINER */

	/* Link virtual queue methods. */
	CLinkVirtual(&self->queue, CQueueVirtual_Insert);
	CLinkVirtual(&self->queue, CQueueVirtual_Remove);
	CLinkVirtual(&self->queue, CQueueVirtual_Peek)
	#if (configCQUEUE_SIZE == 1)
	CLinkVirtual(&self->queue, CQueueVirtual_Size);
	#endif

	/* Override destructor. */
	COverrideVirtual(self, &self->queue.object, CDestructor);
}

static void CLinkedQueue_InitNodes( struct CLinkedQueue* self, size_t size, struct CLinkedNode* nodes )
{
	CMethod(self);
	CAssertObject(nodes);
}

struct CLinkedQueue* CLinkedQueue( struct CLinkedQueue* self, size_t size )
{
	CConstructor(self);
	CQueue_(&self->queue.object);

	struct CLinkedNode* nodes;

	/* Set up member data. */
	self->usingDynamicNodes = true;
	self->tail = NULL;
	self->head = NULL;
	self->endOfLinks = NULL;
	self->size = 0;

	/* Allocate nodes. */
	nodes = CUtilMalloc(size * sizeof(*nodes));
	if( nodes == NULL )
		return NULL;

	CLinkedQueue_InitNodes(self, size, nodes);
	return self;
}

struct CLinkedQueue* CLinkedQueueStatic( struct CLinkedQueue*, size_t size, struct CLinkedNode* nodes)
{
	CConstructor(self);
	CQueue_(&self->queue.object);

	/* Set up member data. */
	self->usingDynamicNodes = false;
	self->tail = NULL;
	self->head = NULL;
	self->endOfLinks = NULL;
	self->size = 0;

	CLinkedQueue_InitNodes(self, size, nodes);
	return self;
}

#endif /* configUSE_CLINKEDQUEUE && configUSE_CQUEUE */