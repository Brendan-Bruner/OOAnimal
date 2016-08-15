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

#include <CCProgram.h>

/************************************************************************/
/* Enum																	*/
/************************************************************************/
/* @enum CCProgramParseState
 * @var CCPROGRAM_PARSE_INIT
 * 		Initial state.
 * @var CCPROGRAM_PARSE_SHORT_CMD
 * 		About to read in a short command
 * @var CCPROGRAM_PARSE_LONG_CMD
 * 		About to read in a long command
 * @var CCPROGRAM_PARSE_READ_CMD
 * 		Reading in a command
 * @var CCPROGRAM_PARSE_ARG_SCAN
 * 		Finished reading in a command, checking for command
 * 		argument.
 * @var CCPROGRAM_PARSE_READ_ARG
 * 		Reading in a command argument.
 */
typedef enum
{
	CCPROGRAM_PARSE_INIT = 0,
	CCPROGRAM_PARSE_SHORT_CMD = 1,
	CCPROGRAM_PARSE_LONG_CMD = 2,
	CCPROGRAM_PARSE_READ_CMD = 3,
	CCPROGRAM_PARSE_ARG_SCAN = 4,
	CCPROGRAM_PARSE_READ_ARG = 5
} CCProgramParseState;

/************************************************************************/
/* Methods																*/
/************************************************************************/
void CCProgram_Help( struct CCProgram* self )
{
	CAssertObject(self);
	const struct CCProgram_VTable* vtable = CGetVTable(self);
	CAssertObject(vtable);
	CAssertVirtual(vtable->help);
	vtable->help(self);
}

struct CCProgram* CCProgram_Clone( struct CCProgram* self )
{
	CAssertObject(self);
	const struct CCProgram_VTable* vtable = CGetVTable(self);
	CAssertObject(vtable);
	CAssertVirtual(vtable->clone);
	return vtable->clone(self);
}

CCProgramError CCProgram_Run( struct CCProgram* self, const char* command, size_t length )
{
	CAssertObject(self);
	const struct CCProgram_VTable* vtable = CGetVTable(self);
	CAssertObject(vtable);
	CAssertVirtual(vtable->run_hook);

	/* Parse the command string into command:argument pairs.
	 */
	size_t i;
	size_t config_index = 0;
	CCProgramParseState state = CCPROGRAM_PARSE_INIT;
	char null_string = '\0';

	for( i = 0; i < length; ++i ) {
		switch( state ) {

			case CCPROGRAM_PARSE_INIT: {
				if( command[i] == '-' ) {
					state = CCPROGRAM_PARSE_SHORT_CMD;
				}
				else if( command[i] != ' ' ){
					self->config_type[config_index] = &null_string;
					self->config_param[config_index] = &command[i];
					++config_index;
					state = CCPROGRAM_PARSE_READ_ARG;
				}
				break;
			}

			case CCPROGRAM_PARSE_SHORT_CMD: {
				if( command[i] == '-' ) {
					state = CCPROGRAM_PARSE_LONG_CMD;
				}
				else if( command[i] != ' ' ) {
					state = CCPROGRAM_PARSE_READ_CMD;
					self->config_type[config_index] = &command[i];
				}
				break;
			}

			case CCPROGRAM_PARSE_LONG_CMD: {
				state = CCPROGRAM_PARSE_READ_CMD;
				self->config_type[config_index] = &command[i];
				break;
			}

			case CCPROGRAM_PARSE_READ_CMD: {
				if( command[i] == ' ' ) {
					state = CCPROGRAM_PARSE_ARG_SCAN;
				}
				break;
			}

			case CCPROGRAM_PARSE_ARG_SCAN: {
				if( command[i] == '-' ) {
					/* No configuration paramter, move onto next configuration
					 * type.
					 */
					self->config_param[config_index++] = &null_string;
					state = CCPROGRAM_PARSE_SHORT_CMD;
				}
				else if( command[i] != ' ' ){
					self->config_param[config_index++] = &command[i];
					state = CCPROGRAM_PARSE_READ_ARG;
				}
				break;
			}

			case CCPROGRAM_PARSE_READ_ARG: {
				if( command[i] == ' ' ) {
					state = CCPROGRAM_PARSE_INIT;
				}
				break;
			}

			default: {
				return CCPROGRAM_INV_SYNTAX;
			}
		}
	}

	return vtable->run_hook(self, self->config_type, self->config_param, config_index);
}

/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCProgram_VTable* CCProgram_Get_Key( )
{
	static struct CCProgram_VTable vtable;

	/* Copy of super's vtable. */
	vtable.CObject_VTable = *CObject_VTable_Key( );

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
CError CCProgram( struct CCProgram* self, struct CIPrint* printer )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCProgram_Get_Key( ));

	if( printer == NULL ) {
		return COBJ_INV_PARAM;
	}
	self->printer = printer;

	return COBJ_OK;
}
