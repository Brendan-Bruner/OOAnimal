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
	
	COTLinkedListNode* next;
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

	/* Get the data to return. */
	element = COTLinkedListNode_GetData( self->_.tail );
	if( element == NULL )
	{
		/* Queue is empty. */
		return NULL;
	}
	/* Set nodes data to NULL. */
	COTLinkedListNode_SetData( self->_.tail, NULL );

	/* The tail node needs to be moved, add it to the end of the list. */
	COTLinkedListNode_SetNext( self->_.endOfList, self->_.tail );
	/* Update the new end of list. */
	self->_.endOfList = self->_.tail;
	/* The new end of list should not have a next node. */
	COTLinkedListNode_SetNext( self->_.endOfList, NULL );

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
	return COTLinkedListNode_GetData( self->_.tail );
}
#endif


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
static void destroy( self(COTObject) )
{
	COTMemberOf(COTLinkedQueue);

	COTSuper( destroy )( (COTObject*) self );
}