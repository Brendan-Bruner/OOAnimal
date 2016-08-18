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

#include <CCTerminal.h>
#include <term_defines.h>
#include <clib.h>
#include <string.h>

#define CCTERMINAL_SEMAPHORE_SIZE 1
#define CCTERMINAL_SEMAPHORE_INIT_COUNT 0

/************************************************************************/
/* Methods																*/
/************************************************************************/
void CCTerminal_Start( struct CCTerminal* self )
{
	CAssertObject(self);
	CSemaphore_Give(self->task_control);
}

static void CDestructor( void* self_ )
{
	struct CCTerminal* self = CCast(self_);

	/* Destroy running task and controller semaphore.
	 */
	CTaskDelete(self->task_handle);
	CSemaphoreDelete(self->task_control);

	/* Call super's destructor.
	 */
	const struct CCTerminal_VTable* vtable = CGetVTable(self);
	vtable->CObject_VTable_Ref->CDestructor(self);
}

static CBool CCTerminal_IsValidChar( struct CCTerminal* self, char input )
{
	CAssertObject(self);

	if(	(input >= '0' && input <= '9') ||
		(input >= 'a' && input <= 'z') ||
		(input >= 'A' && input <= 'Z')) {
		return 1;
	}
	return 0;
}

static const char* CCTerminal_ExtractName(struct CCTerminal* self, const char* command_string, size_t max_length, size_t* prog_name_length)
{
	CAssertObject(self);

	size_t i = 0;
	while( CCTerminal_IsValidChar(self, command_string[i]) && i < max_length ) {
		++i;
	}

	*prog_name_length = i;
	return command_string;
}

static void CCTerminal_NoProgramMessage( struct CCTerminal* self, const char* prog_name, size_t prog_name_length )
{
	CAssertObject(self);
	CIPrint_StringF(self->printer, "%.*s: %s\r\n", prog_name_length, prog_name, CCTERMINAL_UNKOWN_PROGRAM_MSG);
}

static void CCTerminal_ProgramErrMessage( struct CCTerminal* self, const char* prog_name, size_t prog_name_length, CCProgramError err, const char* msg )
{
	CAssertObject(self);
	CIPrint_StringF(self->printer, "%.*s: error (%d): %s\r\n", prog_name_length, prog_name, (int) err, msg);
}

/*
 * Blocks until a line of input is read from the console. A line is terminated
 * by a '\n' character.
 */
static void CCTerminal_RunProgram(struct CCTerminal* self, char* command_string, size_t length)
{
	CAssertObject(self);

	const char* prog_name;
	size_t prog_name_length;
	char* prog_args;
	size_t prog_args_length;

	/* If the user only entered a new line (ie, only hit enter with no text)
	 * then skip the code below which searches for and runs the entered program.
	 */
	if( length > 0 ) {
		/* Extract name of program and arguments.
		 */
		prog_name = CCTerminal_ExtractName(self, command_string, length, &prog_name_length);
		prog_args = command_string + prog_name_length;
		prog_args_length = length - prog_name_length;
		prog_args[prog_args_length] = '\0';

		/* Try to find the program so it can be run.
		 */
		struct CCProgram* program = CCProgramList_Get(self->list, prog_name, prog_name_length);
		if( program != NULL ) {
			CCProgramError err = CCProgram_Run(program, prog_args);

			/* Switch on the possible error conditions when running the
			 * program. Print a message to console if there was an error.
			 */
			if( err == CCPROGRAM_HARD_ERR) {
				CCTerminal_ProgramErrMessage(self, prog_name, prog_name_length, err, CCTERMINAL_HARD_ERROR_MSG);
			}
			else if( err == CCPROGRAM_INV_SYNTAX ) {
				CCTerminal_ProgramErrMessage(self, prog_name, prog_name_length, err, CCTERMINAL_SYNTAX_ERROR_MSG);
				CCProgram_Help(program);
			}
			else if( err == CCPROGRAM_INV_ARGS ) {
				CCTerminal_ProgramErrMessage(self, prog_name, prog_name_length, err, CCTERMINAL_ARGS_ERROR_MSG);
				CCProgram_Help(program);
			}
		}
		else {
			/* No such program exists.
			 */
			CCTerminal_NoProgramMessage(self, prog_name, prog_name_length);
		}
	}
}

/************************************************************************/
/* Task																	*/
/************************************************************************/
void CCTerminal_Task_Def( void* self_ )
{
	struct CCTerminal* self = CCast(self_);
	char command_string[CCTERMINAL_MAX_INPUT_LENGTH];
	char input, prev_input = '\0';
	size_t length = 0;

	CSemaphore_Peek(self->task_control, BLOCK_UNTIL_READY);
	CIPrint_String(self->printer, self->prompt);

	for( ;; ) {


		input = CIPrint_GetChar(self->printer);

		switch( input ) {
			case '\x03': {
				/* CTRL - C
				 */
				CIPrint_String(self->printer, "\r\n");
				CIPrint_String(self->printer, self->prompt);
				break;
			}
			case '\b': {
				/* Backspace.
				 */
				if( length > 0 ) {
					CIPrint_String(self->printer, "\b \b");
					--length;
				}
				break;
			}
			case '\n': {
				if( prev_input != '\r' ) {
					CIPrint_String(self->printer, "\r\n");
					CCTerminal_RunProgram(self, command_string, length);
					CIPrint_String(self->printer, self->prompt);
					length = 0;
				}
				break;
			}
			case '\r': {
				if( prev_input != '\n' ) {
					CIPrint_String(self->printer, "\r\n");
					CCTerminal_RunProgram(self, command_string, length);
					CIPrint_String(self->printer, self->prompt);
					length = 0;
				}
				break;
			}
			default: {
				char ch[] = {input, '\0'};
				CIPrint_String(self->printer, ch);
				command_string[length] = input;
				++length;
				break;
			}
		}

		prev_input = input;
	}
}


/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCTerminal_VTable* CCTerminal_VTable_Key( )
{
	static struct CCTerminal_VTable vtable;

	/* Copy of super's vtable. */
	vtable.CObject_VTable = *CObject_VTable_Key( );

	/* Override all super class methods and methods of
	 * interfaces implemented by super classes in the copy. 
   	 */
	vtable.CObject_VTable.CDestructor = CDestructor;

	/* Reference to super's vtable (pointer). 
  	 */
	vtable.CObject_VTable_Ref = CObject_VTable_Key( );

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
CError CCTerminal(
					struct CCTerminal* self,
					struct CIPrint* printer,
					const char* prompt,
					struct CCProgramList* list
				  )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCTerminal_VTable_Key( ));

	/* Aggregate printer and program list.
	 */
	self->printer = printer;
	self->list = list;

	/* Command prompt.
	 */
	size_t prompt_length = cstrnlen(prompt, CCTERMINAL_PROMPT_LENGTH);
	strncpy(self->prompt, prompt, prompt_length);
	self->prompt[prompt_length] = '\0';

	/* Create controller semaphore.
	 */
	self->task_control = CSemaphoreCreate(CCTERMINAL_SEMAPHORE_SIZE, CCTERMINAL_SEMAPHORE_INIT_COUNT);
	if( self->task_control == NULL ) {
		return COBJ_ALLOC_FAIL;
	}
	CSemaphore_Take(self->task_control, POLL);

	/* Create the terminal's task.
	 */
	COSBase status = CTaskCreate(	CCTerminal_Task_Def,
									CCTERMINAL_TASK_NAME,
									CCTERMINAL_TASK_STACK,
									self,
									CCTERMINAL_TASK_PRIO,
									&self->task_handle	);
	if( status != CTASK_CREATED) {
		CSemaphoreDelete(self->task_control);
		return COBJ_ALLOC_FAIL;
	}

	return COBJ_OK;
}

