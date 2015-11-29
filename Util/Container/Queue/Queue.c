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
#if (configUSE_COTCONTAINER == 1)
#if (configCOTCONTAINER_ADD == 1)
static Boolean COTContainerVirtual_Add( self(COTContainer), void* element )
{
	COTInterfaceOf(COTQueue);
	return COTQueue_Insert( self, element );
}
#endif

#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1) \
	&& (configUSE_COTITERATOR == 1)
static size_t COTContainerVirtual_AddAll( self(COTContainer), COTContainer* container )
{
	COTInterfaceOf(COTQueue);
	COT_ASSERT(container);

	COTIterator* 	iter;
	size_t			count;

	/* Get an iterator. */
	iter = COTContainer_GetIterator( container );
	if( iter == NULL )
	{
		/* Failed to get an iterator. */
		return 0;
	}

	/* Copy all the elements from the container into self. */
	count = 0;
	while( COTIterator_HasNext( iter ) )
	{
		if( !COTQueue_Insert(self, COTIterator_Next(iter)) )
		{
			/* Failed to insert element into queue. */
			break;
		}
		++count;
	}

	/* Destroy the iterator. */
	COTDestroy(COTIterator, iter);
	return count;
}
#endif

#endif /* configUSE_COTCONTAINER */

Boolean COTQueue_Insert( self(COTQueue), void* element )
{
	COTCallVirtual(COTQueue, COTQueueVirtual_Insert)( self, element );
}

void* COTQueue_Remove( self(COTQueue) )
{
	COTCallVirtual(COTQueue, COTQueueVirtual_Remove)( self );
}

#if (configCOTQUEUE_PEEK == 1)
void* COTQueue_Peek( self(COTQueue) )
{
	COTCallVirtual(COTQueue, COTQueueVirtual_Peek)( self );
}
#endif

#if (configCOTQUEUE_SIZE == 1)
size_t COTQueue_Size( self(COTQueue) )
{
	COTCallVirtual(COTQueue, COTQueueVirtual_Size)( self );
}
#endif /* configCOTQUEUE_SIZE */


/****************************************************************************/
/* Constructor / Destructor													*/
/****************************************************************************/
void COTQueueCreate_( self(COTQueue) )
{
	COTConstructorOf(COTQueue);

	/* Create the interfaces used by this class. */
	COTCreateInterface(COTContainer);

	/* Link all virtual methods. */
	/* Methods gained from COTContainer interface. */
	#if (configUSE_COTCONTAINER == 1)
	#if (configCOTCONTAINER_ADD == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_Add);
	#endif
	#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1)	&& (configUSE_COTITERATOR == 1)
	COTLinkVirtual(COTQueue, COTContainer, COTContainerVirtual_AddAll);
	#endif
	#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
	COTLinkAbstract(COTQueue, COTContainer, COTContainerVirtual_GetIterator);
	#endif
	#if (configCOTCONTAINER_SIZE == 1)
	COTLinkAbstract(COTQueue, COTContainer, COTContainerVirtual_Size);
	#endif
	#if (configCOTCONTAINER_RESET == 1)
	COTLinkAbstract(COTQueue, COTContainer, COTContainerVirtual_Reset);
	#endif
	#if (configCOTCONTAINER_IS_EMPTY == 1)
	COTLinkAbstract(COTQueue, COTContainer, COTContainerVirtual_IsEmpty);
	#endif
	#if (configCOTCONTAINER_ADD_CAPACITY == 1)
	COTLinkAbstract(COTQueue, COTContainer, COTContainerVirtual_AddCapacity);
	#endif
	#endif /* configUSE_COTCONTAINER */	

	/* COTQueue virtual methods. */
	COTLinkAbstract(COTQueue, COTQueueVirtual_Insert);
	COTLinkAbstract(COTQueue, COTQueueVirtual_Remove);
	#if (configCOTQUEUE_PEEK == 1)
	COTLinkAbstract(COTQueue, COTQueueVirtual_Peek);
	#endif
	#if (configCOTQUEUE_SIZE == 1)
	COTLinkAbstract(COTQueue, COTQueueVirtual_Size);
	#endif
}
