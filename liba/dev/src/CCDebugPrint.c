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
#include <CCDebugPrint.h>
#include <stdio.h>


/************************************************************************/
/* Methods																*/
/************************************************************************/
static void CCDebugPrint_String_Def( struct CIPrint* self_, const char* string )
{
	struct CCDebugPrint* self = CCast(self_);

	xSemaphoreTake(self->io_mutex, portMAX_DELAY);
	printf(string);
	xSemaphoreGive(self->io_mutex);
}

static void CCDebugPrint_StringF_Def( struct CIPrint* self_, const char* string, va_list args )
{
	struct CCDebugPrint* self = CCast(self_);

	xSemaphoreTake(self->io_mutex, portMAX_DELAY);
	vprintf(string, args);
	xSemaphoreGive(self->io_mutex);
}

static char CCDebugPrint_GetC_Def( struct CIPrint* self_ )
{
	struct CCDebugPrint* self = CCast(self_);

	xSemaphoreTake(self->io_mutex, portMAX_DELAY);
	char input = (char) getchar( );
	xSemaphoreGive(self->io_mutex);
	return input;
}

/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCDebugPrint_VTable* CCDebugPrint_VTable_Key( )
{
	static struct CCDebugPrint_VTable vtable  =
		{
			/* Assigned implementation of this class' methods and
			 * methods of all interfaces implemented by this class.
 			 */
			.cIPrint_VTable.string = CCDebugPrint_String_Def,
			.cIPrint_VTable.stringf = CCDebugPrint_StringF_Def,
			.cIPrint_VTable.getcharacter = CCDebugPrint_GetC_Def
		};

	/* Copy of super's vtable. */
	vtable.cObject_VTable = *CObject_VTable_Key( );

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
static void CCDebugPrint( struct CCDebugPrint* self )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCDebugPrint_VTable_Key( ));

	/* Third thing in constructor must be calling interface's constructor. 
	 */
	CInterface(self, &self->cIPrint, &CCDebugPrint_VTable_Key( )->cIPrint_VTable);

	/* Create mutex.
	 */
	self->io_mutex = xSemaphoreCreateMutex( );
	CAssertObject(self->io_mutex);
}

struct CCDebugPrint* CCDebugPrint_GetInstance( )
{
	static struct CCDebugPrint cCDebugPrint;
	static struct CCDebugPrint* cCDebugPrint_Pointer = NULL;

	if( cCDebugPrint_Pointer == NULL ) {
		CCDebugPrint(&cCDebugPrint);
		cCDebugPrint_Pointer = &cCDebugPrint;
	}

	return cCDebugPrint_Pointer;
}
