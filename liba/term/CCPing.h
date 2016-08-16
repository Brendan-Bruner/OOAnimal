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
#ifndef TERM_PING
#define TERM_PING

#include <CCProgram.h>

/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCPing
 * @extends CCProgram
 * @ingroup Programs
 * @details
 * 		This program provides a quick way to test system connection.
 * 		When run, it simply prints "pong" to the console.
 * 		@code
 * 			struct CIPrint* debug_printer;
 * 			struct CCPing ping;
 *
 * 			debug_printer = CCDebugPrinter_GetInstance()->cIPrint;
 * 			CCPing(&ping, debug_printer);
 *
 * 			CCProgram_Run(&ping.cCProgram, NULL, NULL, 0);
 *		@endcode
 *		The above code will cause the string "pong" to be printed to
 *		the debug console.
 */
struct CCPing
{
	/* Super class must always be first member
	 * of a C class struct.
	 */
	struct CCProgram cCProgram;
};

/**
 * @ingroup VTable
 * @brief
 *	CCPing's vtable declaration.
 */
struct CCPing_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CCProgram_VTable  CCProgram_VTable;
};

/**
 * @memberof CCPing
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCPing class.
 */
const struct CCPing_VTable* CCPing_VTable_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCPing
 * @constructor
 * @details
 * 		Constructs a ping program. When run, the program prints
 * 		"pong" to the console using the CIPrint object provided at
 * 		construction time.
 * @param printer
 * 		The CIPrint object to use when this program is run.
 */
CError CCPing( struct CCPing* self, struct CIPrint* printer );


/************************************************************************/
/* Methods																*/
/************************************************************************/


#endif /* TERM_PING */
