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

/**
 * @struct LinkedListNode
 * @brief
 * 		A single node in a linked list.
 * @details
 * 		A single node in a linked list.
 */
Class( LinkedListNode ) Extends( Object )
	Private
	(
		void* data;
		LinkedListNode* next;
		LinkedListNode* previous;
	);
EndClass;

void LLNSetData( self(LinkedListNode), void* );
void* LLNGetData( self(LinkedListNode) );
void LLNSetNext( self(LinkedListNode), LinkedListNode* );
void LLNSetPrevious( self(LinkedListNode), LinkedListNode* );
LinkedListNode* LLNGetNext( self(LinkedListNode) );
LinkedListNode* LLNGetPrevious( self(LinkedListNode) );
LinkedListNode* LLNGetAt( self(LinkedListNode), uint32_t );
LinkedListNode* LLNGetLast( self(LinkedListNode) );
Boolean LLNIsCircular( self(LinkedListNode ) );

void createLinkedListNode( self(LinkedListNode) );

#endif /* INCLUDE_LINKEDLISTNODE_H_ */
