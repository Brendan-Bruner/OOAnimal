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

#define CCTERMINAL_SEMAPHORE_SIZE 1
#define CCTERMINAL_SEMAPHORE_INIT_COUNT 0

/************************************************************************/
/* Methods																*/
/************************************************************************/
void CCTerminal_Start( struct CCTerminal* self )
{
	CAssertObject(self);
	xSemaphoreGive(self->task_control);
}

static void CDestructor( void* self_ )
{
	struct CCTerminal* self = CCast(self_);

	/* Destroy running task and controller semaphore.
	 */
	vTaskDelete(self->task_handle);
	vSemaphoreDelete(self->task_control);

	/* Call super's destructor.
	 */
	const struct CCTerminal_VTable* vtable = CGetVTable(self);
	vtable->CObject_VTable_Ref->CDestructor(self);
}


/************************************************************************/
/* Task																	*/
/************************************************************************/
void CCTerminal_Task_Def( void* self_ )
{
	struct CCTerminal* self = CCast(self_);

	for( ;; ) {
		xQueuePeek((xQueueHandle) self->task_control, NULL, portMAX_DELAY);
		char input = CIPrint_GetChar(self->printer);
		CIPrint_StringF(self->printer, "%c", input);
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
CError CCTerminal( struct CCTerminal* self, struct CIPrint* printer )
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

	/* Create controller semaphore.
	 */
	self->task_control = xSemaphoreCreateCounting(CCTERMINAL_SEMAPHORE_SIZE, CCTERMINAL_SEMAPHORE_INIT_COUNT);
	if( self->task_control == NULL ) {
		return COBJ_ALLOC_FAIL;
	}
	xSemaphoreTake(self->task_control, POLL);

	/* Create the terminal's task.
	 */
	portBASE_TYPE status = xTaskCreate(	CCTerminal_Task_Def,
										CCTERMINAL_TASK_NAME,
										CCTERMINAL_TASK_STACK,
										self,
										CCTERMINAL_TASK_PRIO,
										&self->task_handle	);
	if( status != pdPASS ) {
		vSemaphoreDelete(self->task_control);
		return COBJ_ALLOC_FAIL;
	}

	return COBJ_OK;
}

