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


/************************************************************************/
/* Declare class and vtable.						*/
/************************************************************************/
struct CCArrayQueue
{
	/* Super class must always be first member */
	/* of a class' struct. */
	struct CObject cObject;

	/* Implement the CIQueue interface. */
	struct CIQueue cIQueue;

	/* Private member variables. */
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

struct CCArrayQueue_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	/* Since we are overriding the destructor, we need to keep */
	/* keep a reference to the super class' implementation of */
	/* the destructor. */
	struct CObject_VTable* CObject_VTable_Ref;

	/* Space for a copy of the implemented interface's virtual table */
	struct CIQueue_VTable CIQueue_VTable;
};

const struct CCArrayQueue_VTable* CCArrayQueue_VTable_Key( );


/************************************************************************/
/* Constructor								*/
/************************************************************************/
CError CCArrayQueue( struct CCArrayQueue*, size_t, size_t );
CError CCArrayQueueStatic( struct CCArrayQueue*, void*, size_t, size_t );

#endif /* UTIL_CCARRAYQUEUE_H_ */
