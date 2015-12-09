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

#include "Iterator.h"

/****************************************************************************/
/* Interface Methods														*/
/****************************************************************************/
void CIterator_Reset( struct CIterator* self )
{
	CAssertVirtual(CIteratorVirtual_Reset);
	self->CIteratorVirtual_Reset(self);
}

Boolean CIterator_HasNext( struct CIterator* self )
{
	CAssertVirtual(CIteratorVirtual_HasNext);
	self->CIteratorVirtual_HasNext(self);
}

void* CIterator_Next( struct CIterator* self )
{
	CAssertVirtual(CIteratorVirtual_Next);
	self->CIteratorVirtual_Next(self);
}
