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
		LLNSetNext( &nodes[iter], &nodes[iter+1] );
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
	LinkedListNode prevNode;
	uint32_t nodeData;
	#define nodeDataValue 20320

	node = &nodes[0];
	nodeData = nodeDataValue;

	LLNSetData( node, (void*) &nodeData );
	LLNSetNext( node, &nextNode );
	LLNSetPrevious( node, &prevNode );

	ASSERT( "Node data incorrect", *((uint32_t*) LLNGetData( node )) == nodeDataValue );
	ASSERT( "Next node incorrect", LLNGetNext( node ) == &nextNode );
	ASSERT( "Previous node incorrect", LLNGetPrevious( node ) == &prevNode );
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
	ASSERT( "depth=0 failed", LLNGetAt( node, 0 ) == node );
	ASSERT( "depth=1 failed", LLNGetAt( node, 1 ) == &nodes[1] );
	ASSERT( "depth=n failed", LLNGetAt( node, GET_AT_NODE_N ) == &nodes[GET_AT_NODE_N] );
	ASSERT( "depth=x, x > length(list), failed", LLNGetAt( node, TEST_NODES_LENGTH ) == NULL );
}

TEST( getLast )
{
	#define GET_LAST_NODE_N 3

	if( TEST_NODES_LENGTH <= GET_LAST_NODE_N )
	{
		ABORT_TEST( "Linked list too short to run test" );
	}

	ASSERT( "Get last failed", LLNGetLast( &nodes[0] ) == &nodes[TEST_NODES_LENGTH-1] );
	ASSERT( "Get last at last faile", LLNGetLast( &nodes[TEST_NODES_LENGTH-1] ) == &nodes[TEST_NODES_LENGTH-1] );
	LLNSetNext( &nodes[TEST_NODES_LENGTH-1], &nodes[GET_LAST_NODE_N] );
	ASSERT( "Get last failed with circular list", LLNGetLast( &nodes[0] ) == NULL );
	ASSERT( "Get last failed with circular list at head", LLNGetLast( &nodes[GET_LAST_NODE_N] ) == NULL );
}

TEST( isCircular )
{
	#define IS_CIRCULAR_NODE_N 3

	if( TEST_NODES_LENGTH <= IS_CIRCULAR_NODE_N )
	{
		ABORT_TEST( "Linked list too short to run test" );
	}

	ASSERT( "failed with linear list", LLNIsCircular( &nodes[0] ) == false );
	LLNSetNext( &nodes[TEST_NODES_LENGTH-1], &nodes[IS_CIRCULAR_NODE_N] );
	ASSERT( "failed with circular list", LLNIsCircular( &nodes[0] ) == true );
	ASSERT( "failed with circular list at head", LLNIsCircular( &nodes[IS_CIRCULAR_NODE_N] ) == true );
}

TEST_SUITE( LinkedListNode )
{
	ADD_TEST( setters_and_getters );
	ADD_TEST( getAt );
	ADD_TEST( getLast );
	ADD_TEST( isCircular );
}
