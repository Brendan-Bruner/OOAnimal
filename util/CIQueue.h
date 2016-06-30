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


/************************************************************************/
/* Error codes.								*/
/************************************************************************/
typedef enum
{
	CIQUEUE_OK = 0,
	CIQUEUE_ERR_OVERFLOW = 1,
	CIQUEUE_ERR_UNDERFLOW = 2
} CIQueueError;


/************************************************************************/
/* Declare interface and vtable.					*/
/************************************************************************/
struct CIQueue
{
	/* CInterface must always be first member of */
	/* an interfaces struct .*/
	struct CInterface interface;
};

struct CIQueue_VTable
{
	CIQueueError (*insert)( struct CIQueue*, const void* );
	CIQueueError (*remove)( struct CIQueue*, void* );
	CIQueueError (*peek)( struct CIQueue*, void* );
	size_t (*size)( struct CIQueue* );
	size_t (*maxSize)( struct CIQueue* );
};


/************************************************************************/
/* Class methods. 							*/
/************************************************************************/
static inline CIQueueError CIQueue_Insert( struct CIQueue* self, const void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->insert);
	return ((struct CIQueue_VTable*) CGetVTable(self))->insert(self, element);
}

static inline CIQueueError CIQueue_Remove( struct CIQueue* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->remove);
	return ((struct CIQueue_VTable*) CGetVTable(self))->remove(self, element);
}

static inline CIQueueError CIQueue_Peek( struct CIQueue* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->peek);
	return ((struct CIQueue_VTable*) CGetVTable(self))->peek(self, element);
}

static inline size_t CIQueue_Size( struct CIQueue* self )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->size);
	return ((struct CIQueue_VTable*) CGetVTable(self))->size(self);
}

static inline size_t CIQueue_MaxSize( struct CIQueue* self )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIQueue_VTable*) CGetVTable(self))->maxSize);
	return ((struct CIQueue_VTable*) CGetVTable(self))->maxSize(self);
}

#endif /* UTIL_CIQUEUE_H_ */
