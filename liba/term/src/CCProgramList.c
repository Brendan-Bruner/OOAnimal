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


static void CCProgramList_Help_Def( struct CCProgram* self_ )
{
	struct CCProgramList* self = CCast(self_);
	struct CIPrint* printer = self->cCProgram.printer;

	CIPrint_String( printer,
					"Usage: help\n"
					"makes a list of all known programs\n");
}

static struct CCProgram* CCProgramList_Clone_Def( struct CCProgram* self_ )
{
	struct CCProgramList* self = CCast(self_);

	struct CCProgramList* clone = CMalloc(sizeof(*self));
	if( clone == NULL ) {
		return NULL;
	}

	if( CCProgramList(clone, self->cCProgram.printer) != COBJ_OK ) {
		CFree(clone);
	}

	CDynamic(clone);
	return &clone->cCProgram;
}

static CCProgramError CCProgramList_RunHook_Def( struct CCProgram* self_, const char** config_type, const char** config_param, size_t count )
{
	struct CCProgramList* self = CCast(self_);
	struct CCListIterator iter;
	struct CCProgram* prog;
	struct CIPrint* printer;

	if( count > 0 ) {
		return CCPROGRAM_INV_ARGS;
	}

	if( CCListIterator(&iter, &self->list.cIList) != COBJ_OK ) {
		return CCPROGRAM_HARD_ERR;
	}

	printer = self->cCProgram.printer;
	CIPrint_String(printer, "Known programs:\n");
	while( CIIterator_HasNext(&iter.cIIterator) ) {
		CIIterator_Next(&iter.cIIterator, &prog);
		const char* prog_name = CCProgram_GetName(prog);
		CIPrint_StringF(printer, "\t%s\n", prog_name);
	}

	CDestroy(&iter);
	return CCPROGRAM_OK;
}


/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCProgramList_VTable* CCProgramList_VTable_Key( )
{
	static struct CCProgramList_VTable vtable;

	/* Copy of super's vtable. */
	vtable.CCProgram_VTable = *CCProgram_VTable_Key( );

	/* Override all super class methods and methods of
	 * interfaces implemented by super classes in the copy.
   	 */
	vtable.CCProgram_VTable.help = CCProgramList_Help_Def;
	vtable.CCProgram_VTable.clone = CCProgramList_Clone_Def;
	vtable.CCProgram_VTable.run_hook = CCProgramList_RunHook_Def;

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
CError CCProgramList( struct CCProgramList* self, struct CIPrint* printer )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CError err = CCProgram(&self->cCProgram, printer, CCPROGRAM_LIST_NAME);
	if( err != COBJ_OK ) {
		return err;
	}

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCProgramList_VTable_Key( ));

	err = CCArrayListStatic(&self->list, sizeof(struct CCProgram*), CCPROGRAM_LIST_MAX_PROGRAMS, self->list_memory);
	if( err != COBJ_OK ) {
		return err;
	}

	if( !CCProgramList_Add(self, &self->cCProgram) ) {
		return COBJ_ALLOC_FAIL;
	}

	return COBJ_OK;
}
