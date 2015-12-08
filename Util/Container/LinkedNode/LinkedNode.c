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

#include <Container/LinkedNode/LinkedNode.h>


/****************************************************************************/
/* Methods																	*/
/****************************************************************************/
/**
 * @memberof CLinkedNode
 * @private
 * @brief
 * 		Traverse a list to find the last node or if its circular.
 * @details
 * 		Traverse a list to find the last node or if its circular.
 * @returns
 * 		NULL if the list is circular, otherwise it will return a
 * 		pointer to the last node in the list.
 */
static struct CLinkedNode* CLinkedNode_TraverseList( struct CLinkedNode* self )
{
	CMethod( );

	struct CLinkedNode* turtle;
	struct CLinkedNode* hare;
	struct CLinkedNode* harePrevious;

	turtle = self;
	hare = self;
	for( ;; )
	{
		turtle = CLinkedNode_GetNext( turtle );
		harePrevious = hare;
		hare = CLinkedNode_GetNext( hare );
		if( hare != NULL )
		{
			harePrevious = hare;
			hare = CLinkedNode_GetNext( hare );
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

void CLinkedNode_SetData( struct CLinkedNode* self, void* data )
{
	CMethod( );
	self->data = data;
}

void* CLinkedNode_GetData( struct CLinkedNode* self)
{
	CMethod( );
	return self->data;
}

void CLinkedNode_SetNext( struct CLinkedNode* self, struct CLinkedNode* next )
{
	CMethod( );
	self->next = next;
}


struct CLinkedNode* CLinkedNode_GetNext( struct CLinkedNode* self )
{
	CMethod( );
	return self->next;
}

struct CLinkedNode* CLinkedNode_GetAt( struct CLinkedNode* self, size_t depth )
{
	CMethod( );
	struct CLinkedNode* nextNode;
	size_t iter;

	nextNode = self;
	for( iter = 0; iter < depth; ++iter )
	{
		nextNode = CLinkedNode_GetNext( nextNode );
		if( nextNode == NULL )
		{
			/* List does not go 'depth' nodes deep. */
			return NULL;
		}
	}
	return nextNode;
}

struct CLinkedNode* CLinkedNode_GetLast( struct CLinkedNode* self )
{
	CMethod( );
	return CLinkedNode_TraverseList( self );
}

Boolean CLinkedNode_IsCircular( struct CLinkedNode* self )
{
	CMethod( );

	if( CLinkedNode_TraverseList( self ) == NULL )
		return true; /* Circular list. */
	else
		return false; /* Not circular. */
}


/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
struct CLinkedNode* CLinkedNode( struct CLinkedNode* self )
{
	CConstructor( );
	/* Create super class. */
	if( CObject((struct CObject*) self) == NULL )
		return NULL;

	self->data = NULL;
	self->next = NULL;

	return self;
}
