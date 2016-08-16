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
#include <term_defines.h>
#include <rtos.h>
#include <CCProgramList.h>


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
 *			// This is used to store all programs the terminal can run.
 * 			static struct CCProgramList program_list;
 *
 * 			// These are all the programs the terminal can run.
 * 			static struct CCPing ping;
 * 			static struct CCEcho echo;
 *
 * 			// This is the terminal and the object used for printing.
 * 			static struct CCTerminal terminal;
 *
 * 			void start_debug_terminal( )
 * 			{
 * 				struct CIPrint* printer = CCDebugPrinter_GetInstance( )->cIPrint;
 *
 *				// Construct the program list and the programs.
 *				CCProgramList(&program_list, printer);
 *				CCPing(&ping, printer);
 *				CCEcho(&echo, printer);
 *
 *				// Add the programs to the program list.
 *				CCProgramList_Add(&program_list, &ping.cCProgram);
 *				CCProgramList_Add(&program_list, &echo.cCProgram);
 *
 *				// Create the terminal
 * 				CCTerminal(&terminal, &printer->cIPrint, "prompt$ ", &program_list);
 *
 * 				// Start the terminal
 * 				CCTerminal_Start(&terminal);
 * 			}
 * 		@endcode
 * 		Since the CCDebugPrinter uses stdio functions getchar() and printf()
 * 		the terminal will be run by using printf() and getchar() for output/input.
 */
struct CCTerminal
{
	/* Super class must always be first member
	 * of a C class struct.
	 */
	struct CObject cObject;

	/* Private data.
	 */
	char prompt[CCTERMINAL_PROMPT_LENGTH+1];
	struct CIPrint* printer;
	CTask task_handle;
	CSemaphore task_control;
	struct CCProgramList* list;
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
const struct CCTerminal_VTable* CCTerminal_VTable_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCTerminal
 * @constructor
 * @details
 * 		Create a terminal object which is initially not active.
 * 		The terminal will start running when CCTerminal_Start()
 * 		is called on it.
 * @param self
 * 		The terminal to construct.
 * @param printer
 * 		The object to for printing to a console and taking
 * 		input from a console.
 * @param prompt
 * 		A NULL terminated string which is copied. This is the
 * 		command prompt displayed. A maximum of CCTERMINAL_PROMPT_LENGTH
 * 		characters will be copied.
 * @param list
 * 		The list which will be used to find programs.
 * @returns
 * 		Error code.
 */
CError CCTerminal(
					struct CCTerminal* self,
					struct CIPrint* printer,
					const char* prompt,
					struct CCProgramList* list
				  );


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
