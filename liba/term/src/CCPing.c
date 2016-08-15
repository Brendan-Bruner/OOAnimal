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

#include <CCPing.h>

/************************************************************************/
/* Methods																*/
/************************************************************************/
static void CCPing_Help_Def( struct CCProgram* self_ )
{
	struct CCPing* self = CCast(self_);
	struct CIPrint* printer = self->cCProgram.printer;

	CIPrint_String( printer,
					"Usage: ping\n"
					"Respond with \"pong\"");
}

static struct CCProgram* CCPing_Clone_Def( struct CCProgram* self_ )
{
	struct CCPing* self = CCast(self_);

	struct CCPing* clone = CMalloc(sizeof(*self));
	if( clone == NULL ) {
		return NULL;
	}

	if( CCPing(clone, self->cCProgram.printer) != COBJ_OK ) {
		CFree(clone);
	}

	CDynamic(clone);
	return &clone->cCProgram;
}

static CCProgramError CCPing_RunHook_Def( struct CCProgram* self_, const char** config_type, const char** config_param, size_t count )
{
	struct CCPing* self = CCast(self_);
	CIPrint_String(self->cCProgram.printer, "pong\n");

	return CCPROGRAM_OK;
}


/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCPing_VTable* CCPing_VTable_Key( )
{
	static struct CCPing_VTable vtable;

	/* Copy of super's vtable. */
	vtable.CCProgram_VTable = *CCProgram_VTable_Key( );

	/* Override all super class methods and methods of
	 * interfaces implemented by super classes in the copy. 
   	 */
	vtable.CCProgram_VTable.help = CCPing_Help_Def;
	vtable.CCProgram_VTable.clone = CCPing_Clone_Def;
	vtable.CCProgram_VTable.run_hook = CCPing_RunHook_Def;

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
CError CCPing( struct CCPing* self, struct CIPrint* printer )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CError err = CCProgram(&self->cCProgram, printer, CCPING_PROGRAM_NAME);
	if( err != COBJ_OK ) {
		return err;
	}

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCPing_VTable_Key( ));

	return COBJ_OK;
}
