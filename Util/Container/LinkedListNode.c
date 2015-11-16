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
 * Oct. 2, 2015
 */

#include <LinkedListNode.h>


/****************************************************************************/
/* Methods																	*/
/****************************************************************************/
/**
 * @memberof COTLinkedListNode
 * @private
 * @brief
 * 		Traverse a list to find the last node or if its circular.
 * @details
 * 		Traverse a list to find the last node or if its circular.
 * @returns
 * 		NULL if the list is circular, otherwise it will return a
 * 		pointer to the last node in the list.
 */
static COTLinkedListNode* COTLinkedListNode_TraverseList( self(COTLinkedListNode) )
{
	COTMemberOf(COTLinkedListNode);

	COTLinkedListNode* turtle;
	COTLinkedListNode* hare;
	COTLinkedListNode* harePrevious;

	turtle = self;
	hare = self;
	for( ;; )
	{
		turtle = COTLinkedListNode_GetNext( turtle );
		harePrevious = hare;
		hare = COTLinkedListNode_GetNext( hare );
		if( hare != NULL )
		{
			harePrevious = hare;
			hare = COTLinkedListNode_GetNext( hare );
		}

		if( hare == NULL )
		{
			/* Reached end of list, it is not circular. */
			/* Return the node at the end of the list. */
			return harePrevious;
		}

		if( hare == turtle )
		{
			/* List is circular. */
			return NULL;
		}
	}
	/* Suppress compiler warnings about return value. */
	return NULL;
}

void COTLinkedListNode_SetData( self(COTLinkedListNode), void const* data )
{
	COTMemberOf(COTLinkedListNode);
	self->data = data;
}

void* COTLinkedListNode_GetData( self(COTLinkedListNode) )
{
	COTMemberOf(COTLinkedListNode);
	return self->data;
}

void COTLinkedListNode_SetPrevious( self(COTLinkedListNode), COTLinkedListNode const* previous )
{
	COTMemberOf(COTLinkedListNode);
	self->previous = previous;
}

void COTLinkedListNode_SetNext( self(COTLinkedListNode), COTLinkedListNode const* next )
{
	COTMemberOf(COTLinkedListNode);
	self->next = next;
}


COTLinkedListNode* COTLinkedListNode_GetNext( self(COTLinkedListNode) )
{
	COTMemberOf(COTLinkedListNode);
	return self->next;
}


COTLinkedListNode* COTLinkedListNode_GetPrevious( self(COTLinkedListNode) )
{
	COTMemberOf(COTLinkedListNode);
	return self->previous;
}

COTLinkedListNode* COTLinkedListNode_GetAt( self(COTLinkedListNode), size_t depth )
{
	COTMemberOf(COTLinkedListNode);
	COTLinkedListNode* nextNode;
	size_t iter;

	nextNode = self;
	for( iter = 0; iter < depth; ++iter )
	{
		nextNode = COTLinkedListNode_GetNext( nextNode );
		if( nextNode == NULL )
		{
			/* List does not go 'depth' nodes deep. */
			return NULL;
		}
	}
	return nextNode;
}

COTLinkedListNode* COTLinkedListNode_GetLast( self(COTLinkedListNode) )
{
	COTMemberOf(COTLinkedListNode);
	return COTLinkedListNode_TraverseList( self );
}

Boolean COTLinkedListNode_IsCircular( self(COTLinkedListNode ) )
{
	COTMemberOf(COTLinkedListNode);

	if( COTLinkedListNode_TraverseList( self ) == NULL )
	{
		/* Circular list. */
		return true;
	}
	else
	{
		/* Not circular. */
		return false;
	}
}


/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
void COTLinkedListNodeCreate( self(COTLinkedListNode) )
{
	COTConstructorOf(COTLinkedListNode);

	self->data = NULL;
	self->next = NULL;
	self->previous = NULL;
}
