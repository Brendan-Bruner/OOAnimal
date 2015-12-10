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
 * Nov, 2015
 */

#include "TestSuites.h"
#include <Util/Container/Queue/LinkedQueue.h>

#define MED_QUEUE_SIZE 10

TEST_SETUP( )
{
}
TEST_TEARDOWN( )
{
}

/* 
 * Creates an empty queue and 
 */
TEST( null_queue )
{

}
	
TEST( size_one_queue )
{

}

/*
 * This test is for insertion, removal, peeking, and size. 
 * It will insert several elements, then remove them one at a time until the
 * queue is empty.
 * Then, it inserts several elements again and removes them one at a time until
 * the queue is empty.
 * This will testing inserting elements into an empty queue, and inserting elements
 * into a queue which was drained to empty.
 */
TEST( insert_remove )
{
	COTLinkedQueue queue;
	size_t actualSize;
	size_t size;
	int iter;
	void* output;
	Boolean err;

	COTCreate( &queue, COTLinkedQueueDynamic( &queue, MED_QUEUE_SIZE, &actualSize ) );
	if( actualSize != MED_QUEUE_SIZE )
	{
		COTDestroy( COTLinkedQueue, &queue );
		ABORT_TEST( "Failed to allocate memory for queue object" );
	}

	/* Insert elements, then assert peek and remove. */
	for( iter = 0; iter < MED_QUEUE_SIZE; ++iter )
	{
		err = COTQueue_Insert( (COTQueue*) &queue, (void*) iter+1 );
		if( !err )
		{
			COTDestroy( COTLinkedQueue, &queue );
			ABORT_TEST( "Failed to add elements into queue" );
		}
	}

	for( iter = 0; iter < MED_QUEUE_SIZE; ++iter )
	{
#if (configCOTQUEUE_PEEK == 1)
		output = COTQueue_Peek( (COTQueue*) &queue );
		ASSERT( "Peek should be %d, not %zu",  output == (void*) iter+1, iter+1, (size_t) output );
#endif
#if (configCOTQUEUE_SIZE == 1)
		ASSERT( "Size should be %d", COTQueue_Size( (COTQueue*) &queue ) == (size_t) MED_QUEUE_SIZE-iter, MED_QUEUE_SIZE-iter );
#endif
#if (configUSE_COTCONTAINER == 1 && configCOTCONTAINER_SIZE == 1)
		size = COTContainer_Size(COTContainerCast( (COTQueue*) &queue ));
		ASSERT( "COTContainer size should be %d, not %zu",  size == (size_t) MED_QUEUE_SIZE-iter, MED_QUEUE_SIZE-iter, size );
#endif
		output = COTQueue_Remove( (COTQueue*) &queue );
		ASSERT( "Remove should be %d, not %zu",  output == (void*) iter+1, iter+1, (size_t) output );
	}
	
	/* Can we insert elements after draining queue? */
	for( iter = 0; iter < MED_QUEUE_SIZE; ++iter )
	{
		err = COTQueue_Insert( (COTQueue*) &queue, (void*) iter+1 );
		if( !err )
		{
			COTDestroy( COTLinkedQueue, &queue );
			ABORT_TEST( "Failed to add elements into queue" );
		}
	}

	/* Should be able to insert beyond queues current size. */
	err = COTQueue_Insert( (COTQueue*) &queue, (void*) iter+1 );
	if( !err )
	{
		COTDestroy( COTLinkedQueue, &queue );
		ABORT_TEST( "Failed to add elements into queue" );
	}

	for( iter = 0; iter < MED_QUEUE_SIZE+1; ++iter )
	{
#if (configCOTQUEUE_PEEK == 1)
		output = COTQueue_Peek( (COTQueue*) &queue );
		ASSERT( "After draining, peek should be %d, not %zu",  output == (void*) iter+1, iter+1, (size_t) output );
#endif
#if (configCOTQUEUE_SIZE == 1)
		ASSERT( "After draining, size should be %d", COTQueue_Size( (COTQueue*) &queue ) == (size_t) MED_QUEUE_SIZE-iter+1, MED_QUEUE_SIZE-iter+1 );
#endif
#if (configUSE_COTCONTAINER == 1 && configCOTCONTAINER_SIZE == 1)
		ASSERT( "After draing, COTContainer size should be %d", COTContainer_Size(COTContainerCast( (COTQueue*) &queue )) == (size_t) MED_QUEUE_SIZE-iter+1, MED_QUEUE_SIZE-iter+1 );
#endif
		output = COTQueue_Remove( (COTQueue*) &queue );
		ASSERT( "Afer draining, remove should be %d, not %zu",  output == (void*) iter+1, iter+1, (size_t) output );
	}

	COTDestroy( COTLinkedQueue, &queue );
}
	
TEST( bounded_overflow )
{
	/* Inserting into a full queue fails to add space, inerstion fails. */
	/* Should be able to remove one element then successfully insert once. */
}

#if (configUSE_COTCONTAINER == 1)
TEST( add_all )
{

}

TEST( iterator )
{

}
	
TEST( reset )
{

}

TEST( is_empty )
{

}

TEST( add_capacity )
{

}
#endif

TEST( destructor_memory_cleanup )
{

}

TEST( destructor_overflow_memory_cleanup )
{

}

TEST_SUITE( COTLinkedQueue )
{
	ADD_TEST( null_queue );
	ADD_TEST( size_one_queue );
	ADD_TEST( insert_remove );
	ADD_TEST( bounded_overflow );
	ADD_TEST( destructor_memory_cleanup );
	ADD_TEST( destructor_overflow_memory_cleanup );
	#if (configUSE_COTCONTAINER == 1)
	ADD_TEST( add_all );
	ADD_TEST( iterator );
	ADD_TEST( reset );
	ADD_TEST( is_empty );
	ADD_TEST( add_capacity );
	#endif
}
