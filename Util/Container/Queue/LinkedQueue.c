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
 }

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
 #if (configUSE_COTCONTAINER == 1)
 #if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
static COTIterator* iterator( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	(void) self;
	return NULL;
}
#endif

#if (configCOTCONTAINER_SIZE == 1)
static size_t size( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	return self->_.size;
}
#endif

#if (configCOTCONTAINER_RESET == 1 )
static void reset( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
	self->_.head = self->_.tail;
}
#endif

#if (configCOTCONTAINER_IS_EMPTY == 1)
static Boolean isEmpty( self(COTContainer) )
{
	COTInterfaceOf(COTQueue);
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
	COTInterfaceOf(COTQueue);
	(void) self;
	(void) capacity;
	return 0;
}
#endif /* configUSE_COTCONTAINER */

static Boolean insert( self(COTQueue), void* element )
{
	COTMemberOf(COTLinkedQueue);
	
	COTLinkedListNode* next;
	#define ADD_ONE_CAPACITY 1

	if( element == NULL )
	{
		return false;
	}

	/* Get the next link element to put the data into. */
	next = COTLinkedListNode_GetNext( self->_.head );
	if( next == NULL )
	{
		/* Queue is out of capacity, try to add some. */
		 if( COTLinkedQueue_AddCapacity( self, ADD_ONE_CAPACITY ) != ADD_ONE_CAPACITY )
		 {
		 	/* Can't add more capacity. */
		 	return false;
		 }
		 /* Try again to get the next link. */
		 next = COTLinkedListNode_GetNext( self->_.head );
		 if( next == NULL )
		 {
		 	/* This should not have happened. */
		 	return false;
		 }
	}

	/* Insert the element. */
	COTLinkedListNode_SetData( next, element );

	/* Update the head element. */
	self->_.head = next;
}

static void* removeElement( self(COTQueue) )
{
	COTMemberOf(COTQueue);
	(void) self;
	return NULL;
}

#if (configCOTQUEUE_PEEK == 1)
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