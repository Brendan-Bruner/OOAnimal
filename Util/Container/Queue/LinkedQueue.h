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

#ifndef INCLUDE_QUEUE_LINKED_QUEUE_H_
#define INCLUDE_QUEUE_LINKED_QUEUE_H_

#include <../ContainerConfig.h>

#if (configUSE_COTLINKEDQUEUE == 1)
#include "Queue.h"
#include <Container/LinkedListNode/LinkedListNode.h>

/**
 * @struct COTLinkedQueue
 * @extends COTQueue
 * @brief
 *		Implements a queue backed by a linked list.
 * @details
 *		Implements a queue backed by a linked list. Insertion and removal times
 *		are O( 1 ). Increasing the queues maximum capacity is an O( n ) operation where
 *		n = additional capacity. For example, if increasing capacity by 10, n = 10.
 *
 *		<b>Memory Usage</b>
 *		<ul>
 *		<li><b>x * sizeof(void*) + sizeof(size_t) + sizeof(char)</b></li>
 *		<li>x changes depending on how many functions are included (ie, like COTContainer_Add( ), COTQueue_Peek( ),
 *			etc.) As a minimum, <b>x = 7</b> plus 1 for each optional function included and plus an additional
 *			2 if the COTContainer is included in the build. This gives a max
 *			x of <b>x = 16</b>.</li>
 *		<li>On a 32 bit system, this gives <b>33 <= total bytes <= 69</b>.</li>
 *		<li>A queue which can buffer a maximum of 1 element requires an additional 3*sizeof(void*) bytes.</li>
 *		<li>A queue which can buffer a maximum of 13 elements requires an additional 13*3*sizeof(void*) bytes. </li>
 *		<li>On a 32 bit system, this gives <b>12*max_size + 33 <= total bytes <= 12*max_size + 69</b>.</li>
 *		</ul>
 * @attention
 *		configUSE_COTLINKEDQUEUE must be defined as 1 for inclusion in the build. See ContainerConfig.h.
 */
COTClass(COTLinkedQueue, COTQueue)
	COTOverride
	(
		COTDestructor( );
	)
	struct
	{
		COTLinkedListNode* 	head;
		COTLinkedListNode* 	tail;
		COTLinkedListNode*	endOfLinks;
		size_t 				size;
	}_; /* Hide private data in this struct. */
COTClassEnd

#endif

#endif /* INCLUDE_QUEUE_LINKED_QUEUE_H_ */