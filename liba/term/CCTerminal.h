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
 * @defgroup Terminal
 */
#ifndef TERM_CCTERMINAL
#define TERM_CCTERMINAL

#include <CIPrint.h>
#include <CError.h>
#include <rtos.h>


/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCTerminal
 * @ingroup Terminal
 * @details
 * 		This is an active class which acts as a mediator between input
 * 		over an aggregate stream and programs which can be dynamically
 * 		run. For example:
 * 		@code
 * 			void start_debug_terminal( )
 * 			{
 * 				struct CCTerminal terminal;
 * 				struct CCDebugPrinter* printer;
 *
 * 				printer = CCDebugPrinter_GetInstance( );
 * 				CCTerminal(&terminal, &printer->cIPrint);
 * 				CCTerminal_Start(&terminal);
 * 			}
 * 		@endcode
 * 		Since the CCDebugPrinter uses stdio functions getchar() and printf()
 * 		the terminal will run by using printf() and getchar() for output/input.
 */
struct CCTerminal
{
	/* Super class must always be first member
	 * of a C class struct.
	 */
	struct CObject cObject;

	/* Private data.
	 */
	struct CIPrint* printer;
	CTask task_handle;
	CSemaphore task_control;
};

/**
 * @ingroup VTable
 * @brief
 *	CCTerminal's vtable declaration.
 */
struct CCTerminal_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	/* Since we are overriding the destructor, we need to keep */
	/* keep a reference to the super class' implementation of */
	/* the destructor. */
	const struct CObject_VTable* CObject_VTable_Ref;
};

/**
 * @memberof CCTerminal
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCTerminal class.
 */
const struct CCTerminal_VTable* CCTerminal_Get_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCTerminal
 * @constructor
 * @details
 * 		Create a terminal object which is initally not active.
 * 		The terminal will start runnign when CCTerminal_Start()
 * 		is called on it.
 * @param self
 * 		The terminal to construct.
 * @param printer
 * 		The object to for printing to a console and taking
 * 		input from a console.
 * @returns
 * 		Error code.
 */
CError CCTerminal( struct CCTerminal* self, struct CIPrint* printer );


/************************************************************************/
/* Methods																*/
/************************************************************************/
/**
 * @memberof CCTerminal
 * @details
 * 		Start the terminal.
 * @param self
 * 		The terminal to start.
 */
void CCTerminal_Start( struct CCTerminal* self );


#endif /* TERM_CCTERMINAL */
