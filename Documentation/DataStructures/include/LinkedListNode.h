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

#define CIRCULAR_LINKED_LIST (char) 1
#define LINEAR_LINKED_LIST (char) 0

/**
 * @struct LinkedListNode
 * @brief
 * 		A single node in a linked list.
 * @details
 * 		A single node in a linked list.
 */
Class( LinkedListNode ) Extends( Object )
	Public
	(
		void (*setData)( self(LinkedListNode), void* );
		void* (*getData)( self(LinkedListNode) );
		void (*setNext)( self(LinkedListNode), LinkedListNode* );
		LinkedListNode* (*getNext)( self(LinkedListNode) );
		LinkedListNode* (*getAt)( self(LinkedListNode), uint32_t );
		LinkedListNode* (*getLast)( self(LinkedListNode) );
		char (*isCircular)( self(LinkedListNode ) );
	);
	Private
	(
		void* data;
		LinkedListNode* next;
	);
EndClass;

void createLinkedListNode( self(LinkedListNode) );

#endif /* INCLUDE_LINKEDLISTNODE_H_ */
