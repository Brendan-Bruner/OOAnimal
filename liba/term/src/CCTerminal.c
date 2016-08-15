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
#include <CCPing.h>
#include <string.h>

#define CCTERMINAL_SEMAPHORE_SIZE 1
#define CCTERMINAL_SEMAPHORE_INIT_COUNT 0

/************************************************************************/
/* Methods																*/
/************************************************************************/
static size_t CCTerminal_StringLength( const char* string, size_t max_length )
{
	size_t i;
	for( i = 0; i < max_length; ++i ) {
		if( string[i] == '\0' ) {
			break;
		}
	}
	return i;
}

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

static size_t CCTerminal_BlockOnInput(struct CCTerminal* self, char* command_string, size_t max_length)
{
	CAssertObject(self);

	size_t length = 0;
	char input = '\0';

	while( input != '\n' ) {
		input = CIPrint_GetChar(self->printer);
		if( length < max_length ) {
			command_string[length++] = input;
		}
	}
	return length;
}
/************************************************************************/
/* Task																	*/
/************************************************************************/
void CCTerminal_Task_Def( void* self_ )
{
	struct CCTerminal* self = CCast(self_);
	char command_string[CCTERMINAL_MAX_INPUT_LENGTH];
	size_t input_length;

	for( ;; ) {
		CSemaphore_Peek(self->task_control, BLOCK_UNTIL_READY);
		CIPrint_String(self->printer, self->prompt);

		input_length = CCTerminal_BlockOnInput(self, command_string, CCTERMINAL_MAX_INPUT_LENGTH);
		if( command_string[0] != '\n' ) {
//			if( strncmp("ping", command_string, 4) == 0 ) {
//				CCPing(&ping, self->printer);
//				CCProgram_Run(&ping.cCProgram, command_string+4, input_length-5);
//				CDestroy(&ping);
//			}
			CIPrint_StringF(self->printer, "%.*s", input_length, command_string);
		}
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
					const char* prompt
				  )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCTerminal_VTable_Key( ));

	/* Aggregate printer.
	 */
	self->printer = printer;

	/* Command prompt.
	 */
	size_t prompt_length = CCTerminal_StringLength(prompt, CCTERMINAL_PROMPT_LENGTH);
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

