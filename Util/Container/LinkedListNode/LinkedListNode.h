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

#ifndef INCLUDE_LINKEDLISTNODE_H_
#define INCLUDE_LINKEDLISTNODE_H_

#include <Class.h>
#include <stdint.h>
#include <Boolean.h>

/**
 * @struct COTLinkedListNode
 * @brief
 * 		A single node in a linked list.
 * @details
 * 		A single node in a linked list.
 */
COTClass( COTLinkedListNode )
	void* data;
	COTLinkedListNode* next;
	COTLinkedListNode* previous;
COTClassEnd

/**
 * @memberof COTLinkedListNode
 * @public
 * @brief
 * 		Save a pointer to a location in memory.
 * @details
 * 		Save a pointer to a location in memory.
 * @param data[in]
 * 		A pointer to a location in memory. The node
 * 		will save this pointer. It can then be retrieved with
 * 		a call to COTLinkedListNode_GetData( ).
 */
void COTLinkedListNode_SetData( self(COTLinkedListNode), void* data );

/**
 * @memberof COTLinkedListNode
 * @public
 * @brief
 * 		Get the data saved in node.
 * @details
 * 		Get the data saved in node.
 * @returns
 * 		A void pointer to a location in memory set by
 * 		COTLinkedListNode_SetData( ). If the set function was
 * 		has never been called then this will default to return
 * 		NULL.
 */
void* COTLinkedListNode_GetData( self(COTLinkedListNode) );

/**
 * @memberof COTLinkedListNode
 * @public
 * @brief
 * 		Set the previous node in the list.
 * @details
 * 		Set the previous node in the list.
 * @param previous[in]
 * 		A pointer to the previous node in the list. Passing in NULL
 * 		will remove the previous node, making this node the first one
 * 		in the list.
 */
void COTLinkedListNode_SetPrevious( self(COTLinkedListNode), COTLinkedListNode* previous );

/**
 * @memberof COTLinkedListNode
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
void COTLinkedListNode_SetNext( self(COTLinkedListNode), COTLinkedListNode* next );

/**
 * @memberof COTLinkedListNode
 * @public
 * @brief
 * 		Get the next node in the list.
 * @details
 * 		Get the next node in the list.
 * @returns
 * 		The next node in the list. If NULL is returned then there
 * 		is no next node and this is the last node.
 */
COTLinkedListNode* COTLinkedListNode_GetNext( self(COTLinkedListNode) );

/**
 * @memberof COTLinkedListNode
 * @public
 * @brief
 * 		Get the previous node in the list.
 * @details
 * 		Get the previous node in the list.
 * @returns
 * 		The previous node in the list. If NULL is returned then there
 * 		is no previous node and this is the first node.
 */
COTLinkedListNode* COTLinkedListNode_GetPrevious( self(COTLinkedListNode) );

/**
 * @memberof COTLinkedListNode
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
 * 		The node at <b>depth</b> nodes deep. A value of zero will
 * 		cause this node to be returned, a value of one causes the
 * 		next node to be returned, etc. However, if there are not
 * 		<b>depth</b> nodes in the list, NULL will be returned.
 */
COTLinkedListNode* COTLinkedListNode_GetAt( self(COTLinkedListNode), size_t depth );

/**
 * @memberof COTLinkedListNode
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
COTLinkedListNode* COTLinkedListNode_GetLast( self(COTLinkedListNode) );

/**
 * @memberof COTLinkedListNode
 * @public
 * @brief
 * 		Traverse the linked list to find out if it is circular.
 * @details
 * 		Traverse the linked list to find out if it is circular.
 * @returns
 * 		<b>true</b> if the list is circular.
 * 		<br><b>false</b> if the list is not circular.
 */
Boolean COTLinkedListNode_IsCircular( self(COTLinkedListNode ) );

/**
 * @memberof LinkedListNode
 * @public
 * @brief
 * 		<b>Constructor</b>
 * @details
 * 		<b>Constructor</b>
 */
void COTLinkedListNodeCreate( self(COTLinkedListNode) );

#endif /* INCLUDE_LINKEDLISTNODE_H_ */
