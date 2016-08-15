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
 * Aug 15, 2016
 */
/**
 * @file
 */

#include <CCListIterator.h>
#include <CCProgramList.h>
#include <clib.h>


/************************************************************************/
/* Methods																*/
/************************************************************************/
CBool CCProgramList_Add( struct CCProgramList* self, struct CCProgram* program )
{
	CAssertObject(self);

	if( program == NULL ) {
		return 0;
	}

	if( CIList_Add(&self->list.cIList, &program) != CILIST_OK ) {
		return 0;
	}

	return 1;
}

struct CCProgram* CCProgramList_Remove( struct CCProgramList* self, const char* name )
{
	CAssertObject(self);
	struct CCListIterator iter;
	struct CCProgram* prog;

	if( name == NULL ) {
		return NULL;
	}

	if( CCListIterator(&iter, &self->list.cIList) != COBJ_OK ) {
		return NULL;
	}

	while( CIIterator_HasNext(&iter.cIIterator) ) {
		CIIterator_Next(&iter.cIIterator, &prog);
		if( cstrncmp(name, CCProgram_GetName(prog), CCPROGRAM_MAX_NAME_LENGTH) == 0 ) {
			CIIterator_Remove(&iter.cIIterator);
			CDestroy(&iter);
			return prog;
		}
	}

	CDestroy(&iter);
	return NULL;
}

struct CCProgram* CCProgramList_Get( struct CCProgramList* self, const char* name, size_t length )
{
	CAssertObject(self);
	struct CCListIterator iter;
	struct CCProgram* prog;

	if( name == NULL ) {
		return NULL;
	}

	if( length > CCPROGRAM_MAX_NAME_LENGTH ) {
		length = CCPROGRAM_MAX_NAME_LENGTH;
	}

	if( CCListIterator(&iter, &self->list.cIList) != COBJ_OK ) {
		return NULL;
	}

	while( CIIterator_HasNext(&iter.cIIterator) ) {
		CIIterator_Next(&iter.cIIterator, &prog);
		if( cstrncmp(name, CCProgram_GetName(prog), length) == 0 ) {
			CDestroy(&iter);
			return prog;
		}
	}

	CDestroy(&iter);
	return NULL;
}


/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCProgramList_VTable* CCProgramList_VTable_Key( )
{
	static struct CCProgramList_VTable vtable;

	/* Copy of super's vtable. */
	vtable.CObject_VTable = *CObject_VTable_Key( );

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
CError CCProgramList( struct CCProgramList* self )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCProgramList_VTable_Key( ));

	return CCArrayListStatic(&self->list, sizeof(struct CCProgram*), CCPROGRAM_LIST_MAX_PROGRAMS, self->list_memory);
}
