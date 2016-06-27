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
#ifndef UTIL_CCARRAYQUEUE_H_
#define UTIL_CCARRAYQUEUE_H_

#include <Class.h>
#include <CError.h>
#include "CIQueue.h"


/****************************************************************************/
/* Declare class.															*/
/****************************************************************************/
struct CCArrayQueue
{
	struct CObject CObject;				/* Super class. */
	struct CIQueue CIQueue;				/* Queue interface. */

	struct
	{
		size_t size;
		size_t max_size;
		size_t element_size;
		size_t head;
		size_t tail;
		unsigned char* queueBase;
	} _;
};


/****************************************************************************/
/* vtable declare															*/
/****************************************************************************/
struct CCArrayQueue_VTable
{
	/* Keep reference to super classes vtable. */
	struct CObject_VTable* Super_CObject_VTable;

	/* new vtable for super class. */
	struct CObject_VTable  CObject_VTable;

	/* vtable for CIQueue interface. */
	struct CIQueue_VTable CIQueue_VTable;

	/* CCArrayQueue has no virtual methods. */
};

extern struct CIQueue_VTable CCArrayQueue_CIQueue_VTable;


/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
CError CCArrayQueue( struct CCArrayQueue*, size_t, size_t );
CError CCArrayQueueStatic( struct CCArrayQueue*, void*, size_t, size_t );

#endif /* UTIL_CCARRAYQUEUE_H_ */
