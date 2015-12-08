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

#ifndef UTIL_CONTAINER_LINKEDNODE_LINKEDNODE_H_
#define UTIL_CONTAINER_LINKEDNODE_LINKEDNODE_H_

#include <Class.h>
#include <stdint.h>
#include <Boolean.h>

/**
 * @struct CLinkedNode
 * @brief
 * 		A single node in a linked list.
 * @details
 * 		A single node in a linked list.
 */
struct CLinkedNode
{
	/* Super class. */
	struct CObject super;

	/* Class data members. */
	struct CLinkedNode* next;
	void* data;
};

/**
 * @memberof CLinkedNode
 * @public
 * @brief
 * 		Save a pointer to a location in memory.
 * @details
 * 		Save a pointer to a location in memory.
 * @param data[in]
 * 		A pointer to a location in memory. The node
 * 		will save this pointer. It can then be retrieved with
 * 		a call to CLinkedNode_GetData( ).
 */
void CLinkedNode_SetData( struct CLinkedNode*, void* data );

/**
 * @memberof CLinkedNode
 * @public
 * @brief
 * 		Get the data saved in node.
 * @details
 * 		Get the data saved in node.
 * @returns
 * 		A void pointer to a location in memory set by
 * 		CLinkedNode_SetData( ). If the set function was
 * 		has never been called then this will default to return
 * 		NULL.
 */
void* CLinkedNode_GetData( struct CLinkedNode* );

/**
 * @memberof CLinkedNode
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
void CLinkedNode_SetNext( struct CLinkedNode*, struct CLinkedNode* next );

/**
 * @memberof CLinkedNode
 * @public
 * @brief
 * 		Get the next node in the list.
 * @details
 * 		Get the next node in the list.
 * @returns
 * 		The next node in the list. If NULL is returned then there
 * 		is no next node and this is the last node.
 */
struct CLinkedNode* CLinkedNode_GetNext( struct CLinkedNode* );

/**
 * @memberof CLinkedNode
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
struct CLinkedNode* CLinkedNode_GetAt( struct CLinkedNode*, size_t depth );

/**
 * @memberof CLinkedNode
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
struct CLinkedNode* CLinkedNode_GetLast( struct CLinkedNode* );

/**
 * @memberof CLinkedNode
 * @public
 * @brief
 * 		Traverse the linked list to find out if it is circular.
 * @details
 * 		Traverse the linked list to find out if it is circular.
 * @returns
 * 		<b>true</b> if the list is circular.
 * 		<br><b>false</b> if the list is not circular.
 */
Boolean CLinkedNode_IsCircular( struct CLinkedNode* );

/**
 * @memberof LinkedNode
 * @public
 * @brief
 * 		<b>Constructor</b>
 * @details
 * 		<b>Constructor</b>
 */
struct CLinkedNode* CLinkedNode( struct CLinkedNode* );

#endif /* UTIL_CONTAINER_LINKEDNODE_LINKEDNODE_H_ */
