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
 * Oct 3, 2015
 */

#include "TestSuites.h"
#include <Container/LinkedNode/LinkedNode.h>

#define TEST_NODES_LENGTH 15
static struct CLinkedNode nodes[TEST_NODES_LENGTH];

TEST_SETUP( )
{
	size_t iter;
	for( iter = 0; iter < TEST_NODES_LENGTH; ++iter )
		CLinkedNode(&nodes[iter]);

	/* Set up a linked list. */
	for( iter = 0; iter < TEST_NODES_LENGTH-1; ++iter )
		CLinkedNode_SetNext(&nodes[iter], &nodes[iter+1]);
}

TEST_TEARDOWN( )
{
	size_t iter;
	for( iter = 0; iter < TEST_NODES_LENGTH; ++iter )
		CDestroy(&nodes[iter]);
}

TEST( setters_and_getters )
{
	struct CLinkedNode* node;
	struct CLinkedNode nextNode;
	uint32_t nodeData;
	#define nodeDataValue 20320

	node = &nodes[0];
	nodeData = nodeDataValue;

	CLinkedNode_SetData( node, (void*) &nodeData );
	CLinkedNode_SetNext( node, &nextNode );

	ASSERT(*((uint32_t*) CLinkedNode_GetData( node )) == nodeDataValue, "Node data incorrect" );
	ASSERT(CLinkedNode_GetNext( node ) == &nextNode, "Next node incorrect" );
}

TEST( getAt )
{
	struct CLinkedNode* node;
	#define GET_AT_NODE_N 7

	if( TEST_NODES_LENGTH <= GET_AT_NODE_N )
		ABORT_TEST( "Linked list too short to run test" );

	node = &nodes[0];
	ASSERT(CLinkedNode_GetAt( node, 0 ) == node, "depth=0 failed");
	ASSERT(CLinkedNode_GetAt( node, 1 ) == &nodes[1], "depth=1 failed");
	ASSERT(CLinkedNode_GetAt( node, GET_AT_NODE_N ) == &nodes[GET_AT_NODE_N], "depth=n failed");
	ASSERT(CLinkedNode_GetAt( node, TEST_NODES_LENGTH ) == NULL, "depth=x, x > length(list), failed");
}

TEST( getLast )
{
	#define GET_LAST_NODE_N 3

	if( TEST_NODES_LENGTH <= GET_LAST_NODE_N )
		ABORT_TEST( "Linked list too short to run test" );

	ASSERT(CLinkedNode_GetLast( &nodes[0] ) == &nodes[TEST_NODES_LENGTH-1], "Get last failed");
	ASSERT(CLinkedNode_GetLast( &nodes[TEST_NODES_LENGTH-1] ) == &nodes[TEST_NODES_LENGTH-1], "Get last at last faile");
	CLinkedNode_SetNext( &nodes[TEST_NODES_LENGTH-1], &nodes[GET_LAST_NODE_N] );
	ASSERT(CLinkedNode_GetLast( &nodes[0] ) == NULL, "Get last failed with circular list");
	ASSERT(CLinkedNode_GetLast( &nodes[GET_LAST_NODE_N] ) == NULL, "Get last failed with circular list at head");
}

TEST( isCircular )
{
	#define IS_CIRCULAR_NODE_N 3

	if( TEST_NODES_LENGTH <= IS_CIRCULAR_NODE_N )
		ABORT_TEST( "Linked list too short to run test" );

	ASSERT(CLinkedNode_IsCircular( &nodes[0] ) == false, "failed with linear list");
	CLinkedNode_SetNext( &nodes[TEST_NODES_LENGTH-1], &nodes[IS_CIRCULAR_NODE_N] );
	ASSERT(CLinkedNode_IsCircular( &nodes[0] ) == true, "failed with circular list");
	ASSERT(CLinkedNode_IsCircular( &nodes[IS_CIRCULAR_NODE_N] ) == true, "failed with circular list at head");
}

TEST_SUITE( CLinkedNode )
{
	ADD_TEST( setters_and_getters );
	ADD_TEST( getAt );
	ADD_TEST( getLast );
	ADD_TEST( isCircular );
}
