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
 * Jun 25, 2016
 */

#include <unit.h>
#include <util/CCArrayQueue.h>

TEST_SETUP( ) { }
TEST_TEARDOWN( ) { }

#define DEFAULT_LENGTH 12
#define DEFAULT_ELEMENT_SIZE 7

struct CCArrayQueue queue;

TEST(underflow)
{
	CIQueueError 		err;
	size_t				queue_size;
	char				test_element[DEFAULT_ELEMENT_SIZE];

	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 0, "Queue should be size zero, not %zu", queue_size);

	err = CIQueue_Remove(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_UNDERFLOW, "No underflow error on remove, got %d instead", err);

	err = CIQueue_Peek(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_UNDERFLOW, "No underflow error on peek, got %d instead", err);

	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 0, "Queue should still be size zero after underflow error, not %zu", queue_size);
}

TEST(middle)
{
	CIQueueError 		err;
	size_t				queue_size;
	char				test_element[DEFAULT_ELEMENT_SIZE];
	int i;

	/* fill in data. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		test_element[i] = (char) i;
	}

	/* Insert element. */
	err = CIQueue_Insert(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_OK, "error on first insert, got %d instead of OK", err);
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 1, "Queue should be size one after insert, not %zu", queue_size);

	/* Insert new test data. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		test_element[i] = (char) (i + DEFAULT_ELEMENT_SIZE);
	}

	/* Insert element. */
	err = CIQueue_Insert(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_OK, "error on second insert, got %d instead of OK", err);
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 2, "Queue should be size two after second insert, not %zu", queue_size);

	/* Peek first element. */
	err = CIQueue_Peek(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_OK, "error on first peek, got %d instead of OK", err);
	/* Assert elements of peeked item. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		ASSERT(test_element[i] == i, "element %d is %d, instead of %d", i, test_element[i], i);
	}
	/* Assert queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 2, "Queue should be size two after peek, not %zu", queue_size);
	/* Zero out test element for remove. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		test_element[i] = 0;
	}
	/* Get first element. */
	err = CIQueue_Remove(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_OK, "error on first remove, got %d instead of OK", err);
	/* Assert elements of removed item. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		ASSERT(test_element[i] == i, "element %d is %d, instead of %d", i, test_element[i], i);
	}
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 1, "Queue should be size one after remove, not %zu", queue_size);


	/* Peek second element. */
	err = CIQueue_Peek(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_OK, "error on second peek, got %d instead of OK", err);
	/* Assert elements of peeked item. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		ASSERT(test_element[i] == i + DEFAULT_ELEMENT_SIZE, "element %d is %d, instead of %d", i, test_element[i], i);
	}
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 1, "Queue should be size one after second peek, not %zu", queue_size);
	/* Zero out test element for remove. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		test_element[i] = 0;
	}
	/* Get second element. */
	err = CIQueue_Remove(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_OK, "error on second remove, got %d instead of OK", err);
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 0, "Queue should be size one after second remove, not %zu", queue_size);
	/* Assert elements of removed item. */
	for( i = 0; i < DEFAULT_ELEMENT_SIZE; ++i ) {
		ASSERT(test_element[i] == i + DEFAULT_ELEMENT_SIZE, "element %d is %d, instead of %d", i, test_element[i], i + DEFAULT_ELEMENT_SIZE);
	}

	/* Assert underflow error. */
	err = CIQueue_Peek(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_UNDERFLOW, "no underflow error on peek, got %d instead", err);
	err = CIQueue_Remove(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_UNDERFLOW, "no underflow error on remove, got %d instead", err);
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 0, "Queue should be size zero after underflow, not %zu", queue_size);
}

TEST(overflow)
{
	CIQueueError 		err;
	size_t				queue_size;
	unsigned char		test_element[DEFAULT_ELEMENT_SIZE];
	size_t i, j;

	/* fill up the queue. */
	for( i = 0; i < DEFAULT_LENGTH; ++i ) {
		for( j = 0; j < DEFAULT_ELEMENT_SIZE; ++j ) {
			test_element[j] = (unsigned char) (i + j);
		}
		err = CIQueue_Insert(&queue.CIQueue, test_element);
		ASSERT(err == CIQUEUE_OK, "Error inserting, got %d during insert %zu, instead of %d", err, i, CIQUEUE_OK);

		/* Assert queue size. */
		queue_size = CIQueue_Size(&queue.CIQueue);
		ASSERT(queue_size == i + 1, "Queue should be size %zu after %zu'th insert, not %zu", i + 1, i, queue_size);
	}

	/* This insert should give overflow error. */
	err = CIQueue_Insert(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_OVERFLOW, "No overflow error, got %d instead of %d", err, CIQUEUE_ERR_OVERFLOW);

	/* Remove back to size zero. */
	for( i = 0; i < DEFAULT_LENGTH; ++i ) {

		/* Test peek. */
		err = CIQueue_Peek(&queue.CIQueue, test_element);
		ASSERT(err == CIQUEUE_OK, "Error peeking, got %d during removal %zu, instead of %d", err, i, CIQUEUE_OK);
		for( j = 0; j < DEFAULT_ELEMENT_SIZE; ++j ) {
			ASSERT(test_element[j] == i + j, "Peeked item is incorrect during removal %zu, got %d instead of %zu", i, test_element[j], i + j);
		}

		/* Zero out test element. */
		for( j = 0; j < DEFAULT_ELEMENT_SIZE; ++j ) {
			test_element[j] = 0;
		}

		/* Test remove. */
		err = CIQueue_Remove(&queue.CIQueue, test_element);
		ASSERT(err == CIQUEUE_OK, "Error removing, got %d during removal %zu, instead of %d", err, i, CIQUEUE_OK);
		for( j = 0; j < DEFAULT_ELEMENT_SIZE; ++j ) {
			ASSERT(test_element[j] == i + j, "Removed item is incorrect during removal %zu, got %d instead of %zu", i, test_element[j], i + j);
		}

		/* Assert new queue size. */
		queue_size = CIQueue_Size(&queue.CIQueue);
		ASSERT(queue_size == DEFAULT_LENGTH - i - 1, "Queue should be size %zu after %zu'th remove, not %zu", DEFAULT_LENGTH - i - 1, i, queue_size);
	}

	/* Should get underflow error now. */
	err = CIQueue_Peek(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_UNDERFLOW, "No underflow error on peek, got %d instead of %d", err, CIQUEUE_ERR_UNDERFLOW);
	err = CIQueue_Remove(&queue.CIQueue, test_element);
	ASSERT(err == CIQUEUE_ERR_UNDERFLOW, "No underflow error on remove, got %d instead of %d", err, CIQUEUE_ERR_UNDERFLOW);
	/* Assert new queue size. */
	queue_size = CIQueue_Size(&queue.CIQueue);
	ASSERT(queue_size == 0, "Queue should be size zero after underflow, not %zu", queue_size);
}

TEST_SUITE(array_queue)
{
	/* Construct queue. */
	if( CCArrayQueue(&queue, DEFAULT_ELEMENT_SIZE, DEFAULT_LENGTH) != COBJ_OK ) {
		ABORT_TEST("Failed to construct queue");
	}

	ADD_TEST(underflow);
	ADD_TEST(middle);
	ADD_TEST(overflow);

	CDestroy(&queue);
}
