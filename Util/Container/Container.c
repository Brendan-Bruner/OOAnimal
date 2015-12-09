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
Boolean CContainer_Add( struct CContainer* self, void* element )
{
	CAssertVirtual(CContainerVirtual_Add);
	return self->CContainerVirtual_Add(self, element);
}

#if (configUSE_CITERATOR == 1)
size_t CContainer_AddAll( struct CContainer* self, struct CContainer* container )
{
	CAssertVirtual(CContainerVirtual_AddAll);
	return self->CContainerVirtual_AddAll(self, container);
}

struct CIterator* CContainer_GetIterator( struct CContainer* self )
{
	CAssertVirtual(CContainerVirtual_GetIterator);
	return self->CContainerVirtual_GetIterator(self);
}
#endif

#if (configCCONTAINER_EXTRA == 1)
size_t CContainer_Size( struct CContainer* self )
{
	CAssertVirtual(CContainerVirtual_Size);
	return self->CContainerVirtual_Size(self);
}

void CContainer_Reset( struct CContainer* self )
{
	CAssertVirtual(CContainerVirtual_Reset);
	self->CContainerVirtual_Reset(self);
}

size_t CContainer_AddCapacity( struct CContainer* self, size_t capacity )
{
	CAssertVirtual(CContainer_AddCapacity)
	return self->CContainerVirtual_AddCapacity(self, capacity);
}
#endif /* configCCONTAINER_EXTRA */
