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
 * Jun 24, 2016
 */
#ifndef UTIL_CIQUEUE_H_
#define UTIL_CIQUEUE_H_

#include <Class.h>


/****************************************************************************/
/* Error codes. 															*/
/****************************************************************************/
typedef enum
{
	CIQUEUE_OK = 0,
	CIQUEUE_ERR_OVERFLOW = 1,
	CIQUEUE_ERR_UNDERFLOW = 2
} CIQueueError;


/****************************************************************************/
/* Declare interface.														*/
/****************************************************************************/
struct CIQueue_VTable;
struct CIQueue
{
	struct CInterface interface;
	struct CIQueue_VTable* vtable;
};


/****************************************************************************/
/* Declare vtable. 															*/
/****************************************************************************/
struct CIQueue_VTable
{
	CIQueueError (*CIQueue_PureVirtual_Insert)( struct CIQueue*, const void* );
	CIQueueError (*CIQueue_PureVirtual_Remove)( struct CIQueue*, void* );
	CIQueueError (*CIQueue_PureVirtual_Peek)( struct CIQueue*, void* );
	size_t (*CIQueue_PureVirtual_Size)( struct CIQueue* );
	size_t (*CIQueue_PureVirtual_MaxSize)( struct CIQueue* );
};


/****************************************************************************/
/* Class methods. 															*/
/****************************************************************************/
static inline CIQueueError CIQueue_Insert( struct CIQueue* self, const void* element )
{
	CAssertObject(self);
	CAssertVirtual(self->vtable);
	CAssertVirtual(self->vtable->CIQueue_PureVirtual_Insert);
	return self->vtable->CIQueue_PureVirtual_Insert(self, element);
}

static inline CIQueueError CIQueue_Remove( struct CIQueue* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(self->vtable);
	CAssertVirtual(self->vtable->CIQueue_PureVirtual_Remove);
	return self->vtable->CIQueue_PureVirtual_Remove(self, element);
}

static inline CIQueueError CIQueue_Peek( struct CIQueue* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(self->vtable);
	CAssertVirtual(self->vtable->CIQueue_PureVirtual_Peek);
	return self->vtable->CIQueue_PureVirtual_Peek(self, element);
}

static inline size_t CIQueue_Size( struct CIQueue* self )
{
	CAssertObject(self);
	CAssertVirtual(self->vtable);
	CAssertVirtual(self->vtable->CIQueue_PureVirtual_Size);
	return self->vtable->CIQueue_PureVirtual_Size(self);
}

static inline size_t CIQueue_MaxSize( struct CIQueue* self )
{
	CAssertObject(self);
	CAssertVirtual(self->vtable);
	CAssertVirtual(self->vtable->CIQueue_PureVirtual_MaxSize);
	return self->vtable->CIQueue_PureVirtual_MaxSize(self);
}

#endif /* UTIL_CIQUEUE_H_ */
