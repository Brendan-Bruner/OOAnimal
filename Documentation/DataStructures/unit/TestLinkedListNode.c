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
#include <LinkedListNode.h>

#define TEST_NODES_LENGTH 15
static LinkedListNode nodes[TEST_NODES_LENGTH];

TEST_SETUP( )
{
	uint32_t iter;
	for( iter = 0; iter < TEST_NODES_LENGTH; ++iter )
	{
		createLinkedListNode( &nodes[iter] );
	}

	/* Set up a linked list. */
	for( iter = 0; iter < TEST_NODES_LENGTH-1; ++iter )
	{
		nodes[iter].setNext( &nodes[iter], &nodes[iter+1] );
	}
}
TEST_TEARDOWN( )
{
	uint32_t iter;
	for( iter = 0; iter < TEST_NODES_LENGTH; ++iter )
	{
		((Object*) &nodes[iter])->destroy( (Object*) &nodes[iter] );
	}
}

TEST( setters_and_getters )
{
	LinkedListNode* node;
	LinkedListNode nextNode;
	uint32_t nodeData;
	#define nodeDataValue 20320

	node = &nodes[0];
	nodeData = nodeDataValue;

	node->setData( node, (void*) &nodeData );
	node->setNext( node, &nextNode );

	ASSERT( "Node data incorrect", *((uint32_t*) node->getData( node )) == nodeDataValue );
	ASSERT( "Next node incorrect", node->getNext( node ) == &nextNode );
}

TEST( getAt )
{
	LinkedListNode* node;
	#define GET_AT_NODE_N 7

	if( TEST_NODES_LENGTH <= GET_AT_NODE_N )
	{
		ABORT_TEST( "Linked list too short to run test" );
	}

	node = &nodes[0];
	ASSERT( "depth=0 failed", node->getAt( node, 0 ) == node );
	ASSERT( "depth=1 failed", node->getAt( node, 1 ) == &nodes[1] );
	ASSERT( "depth=n failed", node->getAt( node, GET_AT_NODE_N ) == &nodes[GET_AT_NODE_N] );
	ASSERT( "depth=x, x > length(list), failed", node->getAt( node, TEST_NODES_LENGTH ) == NULL );
}

TEST( getLast )
{
	#define GET_LAST_NODE_N 3

	if( TEST_NODES_LENGTH <= GET_LAST_NODE_N )
	{
		ABORT_TEST( "Linked list too short to run test" );
	}

	ASSERT( "Get last failed", nodes[0].getLast( &nodes[0] ) == &nodes[TEST_NODES_LENGTH-1] );
	ASSERT( "Get last at last failed", nodes[TEST_NODES_LENGTH-1].getLast( &nodes[TEST_NODES_LENGTH-1] ) == &nodes[TEST_NODES_LENGTH-1] );
	nodes[TEST_NODES_LENGTH-1].setNext( &nodes[TEST_NODES_LENGTH-1], &nodes[GET_LAST_NODE_N] );
	ASSERT( "Get last failed with circular list", nodes[0].getLast( &nodes[0] ) == NULL );
	ASSERT( "Get last failed with circular list at head", nodes[GET_LAST_NODE_N].getLast( &nodes[GET_LAST_NODE_N] ) == NULL );
}

TEST( isCircular )
{
	#define IS_CIRCULAR_NODE_N 3

	if( TEST_NODES_LENGTH <= IS_CIRCULAR_NODE_N )
	{
		ABORT_TEST( "Linked list too short to run test" );
	}

	ASSERT( "failed with linear list", nodes[0].isCircular( &nodes[0] ) == LINEAR_LINKED_LIST );
	nodes[TEST_NODES_LENGTH-1].setNext( &nodes[TEST_NODES_LENGTH-1], &nodes[IS_CIRCULAR_NODE_N] );
	ASSERT( "failed with circular list", nodes[0].isCircular( &nodes[0] ) == CIRCULAR_LINKED_LIST );
	ASSERT( "failed with circular list at head", nodes[IS_CIRCULAR_NODE_N].isCircular( &nodes[IS_CIRCULAR_NODE_N] ) == CIRCULAR_LINKED_LIST );
}

TEST_SUITE( LinkedListNode )
{
	ADD_TEST( setters_and_getters );
	ADD_TEST( getAt );
	ADD_TEST( getLast );
	ADD_TEST( isCircular );
}
