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

#include <util/CCArrayQueue.h>
#include <string.h>


/****************************************************************************/
/* Private methods															*/
/****************************************************************************/
static inline void CCArrayQueue_IncrementTail( struct CCArrayQueue* self )
{
	CAssertObject(self);

	/* Move pointer to next element in queue. */
	self->_.tail += self->_.element_size % (self->_.element_size * self->_.max_size);
}

static inline void CCArrayQueue_IncrementHead( struct CCArrayQueue* self )
{
	CAssertObject(self);

	/* Move pointer to next element in queue. */
	self->_.head += self->_.element_size % (self->_.element_size * self->_.max_size);
}

/****************************************************************************/
/* Virtual methods															*/
/****************************************************************************/
static CIQueueError CIQueue_Insert_Implementation( struct CIQueue* self_, const void* element )
{
	struct CCArrayQueue* self = CCast(self_);

	/* If the queue is full, return an overflow error. */
	if( self->_.size == self->_.max_size ) {
		return CIQUEUE_ERR_OVERFLOW;
	}

	/* Queue is not full, insert element. */
	memcpy(self->_.queueBase + self->_.head, element, self->_.element_size);

	/* Increment head to next queue element. */
	CCArrayQueue_IncrementHead(self);

	/* Increase current size of queue. */
	++self->_.size;

	return CIQUEUE_OK;
}

static CIQueueError CIQueue_Remove_Implementation( struct CIQueue* self_, void* element )
{
	struct CCArrayQueue* self = CCast(self_);

	/* Check if the queue is empty. */
	if( self->_.size == 0 ) {
		return CIQUEUE_ERR_UNDERFLOW;
	}

	/* Queue is not full, remove element. */
	memcpy(element, self->_.queueBase + self->_.tail, self->_.element_size);

	/* Increment tail to next element. */
	CCArrayQueue_IncrementTail(self);

	/* Decrease size of queue. */
	--self->_.size;

	return CIQUEUE_OK;
}

static CIQueueError CIQueue_Peek_Implementation( struct CIQueue* self_, void* element )
{
	struct CCArrayQueue* self = CCast(self_);

	/* Check if the queue is empty. */
	if( self->_.size == 0 ) {
		return CIQUEUE_ERR_UNDERFLOW;
	}

	/* Queue is not full, peek at element. */
	memcpy(element, self->_.queueBase + self->_.tail, self->_.element_size);

	return CIQUEUE_OK;
}

static size_t CIQueue_Size_Implementation( struct CIQueue* self_ )
{
	struct CCArrayQueue* self = CCast(self_);

	return self->_.size;
}

static size_t CIQueue_MaxSize_Implementation( struct CIQueue* self_ )
{
	struct CCArrayQueue* self = CCast(self_);

	return self->_.max_size;
}

/****************************************************************************/
/* vtable define															*/
/****************************************************************************/
struct CIQueue_VTable CCArrayQueue_CIQueue_VTable =
		{
			.CIQueue_PureVirtual_Insert = CIQueue_Insert_Implementation,
			.CIQueue_PureVirtual_Remove = CIQueue_Remove_Implementation,
			.CIQueue_PureVirtual_Peek = CIQueue_Peek_Implementation,
			.CIQueue_PureVirtual_Size = CIQueue_Size_Implementation,
			.CIQueue_PureVirtual_MaxSize = CIQueue_MaxSize_Implementation
		};

/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
/* TODO, need to free queue base on destruction. */
CError CCArrayQueue( struct CCArrayQueue* self, size_t element_size, size_t queue_size )
{
	CObject(&self->CObject);
	CInterface(self, &self->CIQueue);

	/* Link virtual functions from interface. */
	self->CIQueue.vtable = &CCArrayQueue_CIQueue_VTable;

	/* Allocate space for the array. */
	self->_.queueBase = CMalloc(queue_size * element_size);
	if( self->_.queueBase == NULL ) {
		return COBJ_ALLOC_FAIL;
	}

	/* Initialize member variables. */
	self->_.element_size = element_size;
	self->_.head = 0;
	self->_.tail = 0;
	self->_.max_size = queue_size;
	self->_.size = 0;

	return COBJ_OK;
}
