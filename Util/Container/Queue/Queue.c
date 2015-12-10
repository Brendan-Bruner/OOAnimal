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

#include "Queue.h"
 

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
#if (configUSE_CCONTAINER == 1)
static Boolean CContainerVirtual_Add( struct CContainer* self_, void* element )
{
	struct CQueue* self = CCast(self_);

	return CQueue_Insert( self, element );
}

#if (configUSE_CITERATOR == 1)
static size_t CContainerVirtual_AddAll( struct CContainer* self_, CContainer* container )
{
	struct CQueue* self = CCast(self_);
	CAssertObject(container);

	struct CIterator* 	iter;
	size_t				count;

	/* Get an iterator. */
	iter = CContainer_GetIterator(container);
	if( iter == NULL )
		return 0; /* Failed to get an iterator. */

	/* Copy all the elements from the container into self. */
	count = 0;
	while( CIterator_HasNext(iter) )
	{
		if( !CQueue_Insert(self, CIterator_Next(iter)) )
			break; /* Failed to insert element into queue. */

		/* Element successfully added. */
		++count; /* Increment number of elements successfully added. */
	}

	/* Destroy the iterator. */
	CDestroy(iter);
	return count;
}

#endif /* configUSE_CITERATOR */
#endif /* configUSE_CCONTAINER */

Boolean CQueue_Insert( struct CQueue* self, void* element )
{
	CAssertVirtual(self, CQueueVirtual_Insert)
	return self->CQueueVirtual_Insert(self, element);
}

void* CQueue_Remove( struct CQueue* self )
{
	CAssertVirtual(self, CQueueVirtual_Remove);
	return self->CQueueVirtual_Remove(self);
}

void* CQueue_Peek( struct CQueue* self )
{
	CAssertVirtual(self, CQueueVirtual_Peek);
	return self->CQueueVirtual_Peek(self);
}

#if (configCQUEUE_SIZE == 1)
size_t CQueue_Size( struct CQueue* self )
{
	CAssertVirtual(self, CQueueVirtual_Size);
	return self->CQueueVirtual_Size(self);
}
#endif /* configCQUEUE_SIZE */


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
struct CQueue* CQueue_( struct CQueue* self )
{
	CConstructor(self);
	CObject((struct CObject*) self);
	CInterface(&self->container);

	/* Link all implemented methods. */
	#if (configUSE_CCONTAINER == 1)
	CLinkVirtual(&self->container, CContainerVirtual_Add);
	#if (configUSE_CITERATOR == 1)
	CLinkVirtual(&self->container, CContainerVirtual_AddAll);
	#endif
	#endif /* configUSE_CCONTAINER */	

	return self;
}
