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
 * Nov 14, 2015
 */

#include <Util/Container/Container.h>

/****************************************************************************/
/* Interface Methods														*/
/****************************************************************************/
#if (configCOTCONTAINER_ADD == 1)
Boolean COTContainer_Add( self(COTContainer), void* element )
{
	COTCallVirtual( COTContainer, add )( self, element );
}
#endif

#if (configCOTCONTAINER_ADD_ALL == 1) && (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
size_t COTContainer_AddAll( self(COTContainer), COTContainer* container )
{
	COTCallVirtual( COTContainer, addAll )( self, container );
}
#endif

#if (configCOTCONTAINER_ITERATOR == 1) && (configUSE_COTITERATOR == 1)
COTIterator* COTContainer_GetIterator( self(COTContainer) )
{
	COTCallVirtual( COTContainer, iterator )( self );
}
#endif

#if (configCOTCONTAINER_SIZE == 1)
size_t COTContainer_Size( self(COTContainer) )
{
	COTCallVirtual( COTContainer, size )( self );
}
#endif

#if (configCOTCONTAINER_RESET == 1 )
void COTContainer_Reset( self(COTContainer) )
{
	COTCallVirtual( COTContainer, reset )( self );
}
#endif

#if (configCOTCONTAINER_IS_EMPTY == 1)
Boolean COTContainer_IsEmpty( self(COTContainer) )
{
	COTCallVirtual( COTContainer, isEmpty )( self );
}
#endif

#if (configCOTCONTAINER_ADD_CAPACITY == 1)
size_t COTContainer_AddCapacity( self(COTContainer), size_t capacity )
{
	COTCallVirtual( COTContainer, addCapacity )( self, capacity );
}
#endif
