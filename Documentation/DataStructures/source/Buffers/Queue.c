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
 * Oct 17, 2015
 */

#include <Buffers/Queue.h>


/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
static Boolean push( self(Buffer), void* element )
{

}

static void* pop( self(Buffer) )
{

}

static void* peek( self(Buffer) )
{

}

static void reset( self(Buffer) )
{
	MemberOf(Queue);
	private( ).head = private( ).tail;
	protected(Buffer).length = 0;
}


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
static void destroy( self(Object) )
{
	MemberOf(Queue);

	LinkedListNode* currentNode;
	LinkedListNode* nextNode;

	currentNode = private( ).tail;
	while( currentNode != NULL )
	{
		/* Get the next node. */
		nextNode = LLNGetNext( currentNode );

		/* Free the current node. */
		private( ).allocator->free( private( ).allocator, currentNode );
		currentNode = nextNode;
	}

	/* Call super class' destructor. */
	super( )->destroy( (Object*) self );
}

Queue* createQueue
(
	self(Queue),
	TAllocator* allocator,
	uint32_t size,
	uint32_t* actual
)
{
	/* Virtual function linkage and super class creation. */
	MemberOf(Queue);
	objASSERT( allocator );
	createObject( (Object*) self );
	LinkMethod( push );
	LinkMethod(pop );
	LinkMethod(peek );
	LinkMethod(reset );
	SoftOverrideMethod( Object, destroy );

	/* Beginning of constructor. */
	LinkedListNode* currentNode;
	LinkedListNode*	previousNode;
	uint32_t iter;

	/* Set up member data. */
	private( ).allocator = allocator;

	/* If, for some reason, a queue of size zero is being constructed, */
	/* return now. */
	if( size == 0 ){ return self; }

	/* Allocate first node. If this fails, the queue is of size 0. */
	previousNode = allocator->malloc( allocator, sizeof(LinkedListNode) );
	if( previousNode == NULL ){ return self; }
	private( ).tail = previousNode;
	private( ).head = previousNode;

	/* Begin allocating the rest of the nodes. */
	for( iter = 1; iter < size; ++iter )
	{
		currentNode = allocator->malloc( allocator, sizeof(LinkedListNode) );
		if( currentNode == NULL ){ break; }

		/* Concatenate the nodes. */
		LLNSetNext( previousNode, currentNode );
		previousNode = currentNode;
	}

	/* Now we know the absolute top node and the maximum size of the queue. */
	private( ).absoluteTop = currentNode;
	protected(Buffer).maxLength = iter;

	return self;
}
