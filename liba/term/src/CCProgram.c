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
#include <clib.h>

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
const char* CCProgram_GetName( struct CCProgram* self )
{
	CAssertObject(self);
	return self->name;
}

static CBool CCProgram_IsString( struct CCProgram* self, const char* string )
{
	CAssertObject(self);

	if( (string[0] >= '0' && string[0] <= '9') ||
		(string[0] >= 'a' && string[0] <= 'z') ||
		(string[0] >= 'A' && string[0] <= 'Z') ) {
		return 1;
	}
	return 0;
}

void CCProgram_Help( struct CCProgram* self )
{
	CAssertObject(self);
	const struct CCProgram_VTable* vtable = CGetVTable(self);
	CAssertObject(vtable);
	CAssertVirtual(vtable->help);
	vtable->help(self);
}

CCProgramError CCProgram_Run( struct CCProgram* self, const char* command )
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
	size_t length;

	/* Get the length of the input string.
	 */
	length = cstrnlen(command, CCPROGRAM_MAX_INPUT_LENGTH + 1);
	if( length > CCPROGRAM_MAX_INPUT_LENGTH ) {
		return CCPROGRAM_OVERFLOW;
	}

	/* Clear type/param from previous run (if any).
	 */
	for( i = 0; i < CCPROGRAM_MAX_ARG_COUNT; ++i ) {
		self->config_type[i] = NULL;
		self->config_param[i] = NULL;
	}

	for( i = 0; i < length; ++i ) {
		switch( state ) {

			/* Begin parsing type:param tokens.
			 */
			case CCPROGRAM_PARSE_INIT: {
				if( command[i] == '-' ) {
					state = CCPROGRAM_PARSE_SHORT_CMD;
				}
				else if( CCProgram_IsString(self, command + i) ){
					self->config_type[config_index] = &null_string;
					self->config_param[config_index] = &command[i];
					++config_index;
					state = CCPROGRAM_PARSE_READ_ARG;
				}
				else if( command[i] != ' ' ) {
					return CCPROGRAM_INV_SYNTAX;
				}
				break;
			}

			/* Have a token to scan for a short config type.
			 */
			case CCPROGRAM_PARSE_SHORT_CMD: {
				if( command[i] == '-' ) {
					state = CCPROGRAM_PARSE_LONG_CMD;
				}
				else if( CCProgram_IsString(self, command + i) ) {
					state = CCPROGRAM_PARSE_READ_CMD;
					self->config_type[config_index] = &command[i];
					if( i == (length - 1) ) {
						self->config_param[config_index++] = &null_string;
					}
				}
				else {
					return CCPROGRAM_INV_SYNTAX;
				}
				break;
			}

			/* Have a token to scan for a long config type.
			 */
			case CCPROGRAM_PARSE_LONG_CMD: {
				if( CCProgram_IsString(self, command + i) ) {
					state = CCPROGRAM_PARSE_READ_CMD;
					self->config_type[config_index] = &command[i];
					if( i == (length - 1) ) {
						self->config_param[config_index++] = &null_string;
					}
				}
				else {
					return CCPROGRAM_INV_SYNTAX;
				}
				break;
			}

			/* Have a token to read out a config type argument.
			 */
			case CCPROGRAM_PARSE_READ_CMD: {
				if( command[i] == ' ' ) {
					state = CCPROGRAM_PARSE_ARG_SCAN;
				}
				else if( !CCProgram_IsString(self, command + i) ) {
					return CCPROGRAM_INV_SYNTAX;
				}
				break;
			}

			/* Have a token to scan for a config param.
			 */
			case CCPROGRAM_PARSE_ARG_SCAN: {
				if( command[i] == '-' ) {
					/* No configuration parameter, move onto next configuration
					 * type.
					 */
					self->config_param[config_index++] = &null_string;
					state = CCPROGRAM_PARSE_SHORT_CMD;
				}
				else if( CCProgram_IsString(self, command + i) ) {
					self->config_param[config_index++] = &command[i];
					state = CCPROGRAM_PARSE_READ_ARG;
				}
				else if( command[i] != ' ' ) {
					return CCPROGRAM_INV_SYNTAX;
				}
				break;
			}

			/* Have a token to read out a config param.
			 */
			case CCPROGRAM_PARSE_READ_ARG: {
				if( command[i] == ' ' ) {
					state = CCPROGRAM_PARSE_INIT;
				}
				else if( !CCProgram_IsString(self, command + i) ) {
					return CCPROGRAM_INV_SYNTAX;
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
const struct CCProgram_VTable* CCProgram_VTable_Key( )
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
CError CCProgram( struct CCProgram* self, struct CIPrint* printer, const char* name )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCProgram_VTable_Key( ));

	if( printer == NULL ) {
		return COBJ_INV_PARAM;
	}
	self->printer = printer;

	if( name == NULL ) {
		return COBJ_INV_PARAM;
	}
	cstrncpy(self->name, name, CCPROGRAM_MAX_NAME_LENGTH);
	self->name[CCPROGRAM_MAX_NAME_LENGTH] = '\0';

	return COBJ_OK;
}
