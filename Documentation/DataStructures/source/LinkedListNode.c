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
/* Virtual Methods															*/
/****************************************************************************/
/**
 * @memberof LinkedListNode
 * @private
 * @brief
 * 		Traverse a list to find the last node or if its circular.
 * @details
 * 		Traverse a list to find the last node or if its circular.
 * @returns
 * 		NULL if the list is circular, otherwise it will return a
 * 		pointer to the last node in the list.
 */
static LinkedListNode* traverseList( self(LinkedListNode) )
{
	MemberOf( LinkedListNode );

	LinkedListNode* turtle;
	LinkedListNode* hare;
	LinkedListNode* harePrevious;

	turtle = self;
	hare = self;
	for( ;; )
	{
		turtle = turtle->getNext( turtle );
		harePrevious = hare;
		hare = hare->getNext( hare );
		if( hare != NULL )
		{
			harePrevious = hare;
			hare = hare->getNext( hare );
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

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Save a pointer to a location in memory.
 * @details
 * 		Save a pointer to a location in memory.
 * @param data[in]
 * 		A pointer to a location in memory. The node
 * 		will save this pointer. It can then be retrieved with
 * 		a call to LinkedListNode::getData( ).
 */
static void setData( self(LinkedListNode), void* data )
{
	MemberOf( LinkedListNode );
	private( ).data = data;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Get the data saved in node.
 * @details
 * 		Get the data saved in node.
 * @returns
 * 		A void pointer to a location in memory set by
 * 		LinkedListNode::setData( ). If the set function was
 * 		has never been called then this will default to return
 * 		NULL.
 */
static void* getData( self(LinkedListNode) )
{
	MemberOf( LinkedListNode );
	return private( ).data;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Set the previous node in the list.
 * @details
 * 		Set the previous node in the list.
 * @param next[in]
 * 		A pointer to the previous node in the list. Passing in NULL
 * 		will remove the previous node, making this node the first one
 * 		in the list.
 */
static void setPrevious( self(LinkedListNode), LinkedListNode* previous )
{
	MemberOf( LinkedListNode );
	private( ).previous = previous;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Set the next node in the list.
 * @details
 * 		Set the next node in the list.
 * @param next[in]
 * 		A pointer to the next node in the list. Passing in NULL
 * 		will remove the next node, making this node the last one
 * 		in the list.
 */
static void setNext( self(LinkedListNode), LinkedListNode* next )
{
	MemberOf( LinkedListNode );
	private( ).next = next;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Get the next node in the list.
 * @details
 * 		Get the next node in the list.
 * @returns
 * 		The next node in the list. If NULL is returned then there
 * 		is no next node and this is the last node.
 */
static LinkedListNode* getNext( self(LinkedListNode) )
{
	MemberOf( LinkedListNode );
	return private( ).next;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Get the previous node in the list.
 * @details
 * 		Get the previous node in the list.
 * @returns
 * 		The previous node in the list. If NULL is returned then there
 * 		is no previous node and this is the first node.
 */
static LinkedListNode* getPrevious( self(LinkedListNode) )
{
	MemberOf( LinkedListNode );
	return private( ).previous;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 *		Traverse the linked list <b>depth</b> nodes deep.
 * @details
 * 		Traverse the linked list <b>depth</b> nodes deep.
 * 		If the list does not extend <b>depth</b> nodes deep
 * 		then NULL will be returned.
 * @param depth
 * 		How many nodes deep to go into the list.
 * @returns
 * 		The nodes at <b>depth</b> nodes deep. A value of zero will
 * 		cause this node to be returned, a value of one causes the
 * 		next node to be returned, etc. However, if there are not
 * 		<b>depth</b> nodes in the list, NULL will be returned.
 */
static LinkedListNode* getAt( self(LinkedListNode), uint32_t depth )
{
	MemberOf( LinkedListNode );
	LinkedListNode* nextNode;
	uint32_t iter;

	nextNode = self;
	for( iter = 0; iter < depth; ++iter )
	{
		nextNode = nextNode->getNext( nextNode );
		if( nextNode == NULL )
		{
			/* List does not go 'depth' nodes deep. */
			return NULL;
		}
	}
	return nextNode;
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Search for the last node in the linked list.
 * @details
 * 		Search for the last node in the linked list.
 * 		If there is no last node (due to the list being circular)
 * 		then NULL will be returned.
 * @returns
 * 		A pointer to the last node in the list. NULL if there is
 * 		no last node due to a circular list.
 */
static LinkedListNode* getLast( self(LinkedListNode) )
{
	MemberOf( LinkedListNode );

	return traverseList( self );
}

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		Traverse the linked list to find out if it is circular.
 * @details
 * 		Traverse the linked list to find out if it is circular.
 * @returns
 * 		<b>true</b> if the list is circular.
 * 		<br><b>false</b> if the list is not circular.
 */
static Boolean isCircular( self(LinkedListNode ) )
{
	MemberOf( LinkedListNode );

	if( traverseList( self ) == NULL )
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
/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		<b>Constructor</b>
 * @details
 * 		<b>Constructor</b>
 * 		<br>Takes a pointer to an allocated LinkedListNode and
 * 		constructs it.
 */
void createLinkedListNode( self(LinkedListNode) )
{
	MemberOf( LinkedListNode );
	newObject( (Object*) self );
	LinkMethod( getData );
	LinkMethod( setData );
	LinkMethod( setNext );
	LinkMethod( setPrevious );
	LinkMethod( getNext );
	LinkMethod( getPrevious );
	LinkMethod( getAt );
	LinkMethod( getLast );
	LinkMethod( isCircular );

	private( ).data = NULL;
	private( ).next = NULL;
	private( ).previous = NULL;
}
