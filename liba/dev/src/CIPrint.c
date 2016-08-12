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
 * Aug 12, 2016
 */
/**
 * @file
 */
#include <CIPrint.h>

/************************************************************************/
/* Virtual method call wrappers.					*/
/************************************************************************/
void CIPrint_String( struct CIPrint* self, const char* string )
{
	CAssertObject(self);
	const struct CIPrint_VTable* vtable = CGetVTable(self);
	CAssertVirtual(vtable);
	CAssertVirtual(vtable->string);
	vtable->string(self, string);
}

void CIPrint_StringF( struct CIPrint* self, const char* string, ... )
{
	CAssertObject(self);
	const struct CIPrint_VTable* vtable = CGetVTable(self);
	CAssertVirtual(vtable);
	CAssertVirtual(vtable->stringf);

	va_list args;
	va_start(args, string);
	vtable->stringf(self, string, args);
	va_end(args);
}

char CIPrint_GetChar( struct CIPrint* self )
{
	CAssertObject(self);
	const struct CIPrint_VTable* vtable = CGetVTable(self);
	CAssertVirtual(vtable);
	CAssertVirtual(vtable->getcharacter);
	return vtable->getcharacter(self);
}
