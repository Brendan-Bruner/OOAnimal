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
 * @defgroup Programs
 */
#ifndef TERM_CCPROGRAM
#define TERM_CCPROGRAM

#include <CIPrint.h>
#include <Class.h>
#include <CError.h>
#include <term_defines.h>

/************************************************************************/
/* Error codes															*/
/************************************************************************/
/**
 * @enum CCProgramError
 * @ingroup Programs
 * @var CCPROGRAM_OK
 * 		No error running the program.
 * @var CCPROGRAM_INV_ARGS
 * 		Invalid arguments given to the program.
 * @var CCPROGRAM_INV_SYNTAX
 * 		Invalid syntax for program arguments, unable to parse them.
 * @var CCPROGRAM_HARD_ERR
 * 		Error in associated objects occurred.
 */
typedef enum
{
	CCPROGRAM_OK = 0,
	CCPROGRAM_INV_ARGS = 1,
	CCPROGRAM_INV_SYNTAX = 2,
	CCPROGRAM_HARD_ERR = 3,
	CCPROGRAM_OVERFLOW = 4
} CCProgramError;

/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCProgram
 * @ingroup Programs
 * @details
 * 		Abstract class which describes the interface for executable programs.
 * 		Sub classes implement the help and run_hook methods to
 * 		define what the program does. Calling CCProgram_Run() will execute the
 * 		program. Calling CCProgram_Help() will print a help message for the
 * 		program to the console.
 *
 * 		Programs have the following syntax:
 * 		@code
 * 			program ::=
 * 					["program name" {configuration} {operation}]
 *
 * 			configuration ::=
 * 					(("-" character) | ("--" string)) {string}
 *
 * 			character ::=
 * 					("0" | "1" | ... | "a" | "b" | ... | "A" | "B" | ...)
 *
 * 			string ::=
 * 					character {string}
 *
 * 			operation ::=
 * 					string
 * 		@endcode
 *
 * 		At construction time, the program aggregates a CIPrint object. This object
 * 		must be used for any printing messages. In addition, a name (ascii string) is given to the
 * 		program at construction time. The name is used to reference the program by a user.
 */
struct CCProgram
{
	/* Super class must always be first member
	 * of a C class struct.
	 */
	struct CObject cObject;

	/* Private data.
	 */
	const char* config_type[CCPROGRAM_MAX_ARG_COUNT];
	const char* config_param[CCPROGRAM_MAX_ARG_COUNT];
	struct CIPrint* printer;
	char name[CCPROGRAM_MAX_NAME_LENGTH+1];
};

/**
 * @ingroup VTable
 * @brief
 *	CCProgram's vtable declaration.
 */
struct CCProgram_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	void (*help)( struct CCProgram* );

	/* @details
	 * 		This is a like a protected pure virtual method. Sub classes must be provide an
	 * 		implementation of this method.
	 * 		It's a hook for running programs which gets called by CCProgram_Run().
	 * 		The inputs to the function can be
	 * 		switched to provide additional options for the program. The syntax of a program
	 * 		is given in the CCProgram description.
	 * @var config_type
	 * 		Pointer to command strings passed to the program. For example:
	 * 			git commit -a -m "this is a commit"
	 * 		config_type[0] = "a -m "this is a commit""
	 * 		config_type[1] = "m "this is a commit""
	 * 		Notice that a white space character is also used to terminate the config type. This means
	 * 		when parsing config_type[i] for any 'i', that only the characters up to the next NULL or white
	 * 		space character should be considered.
	 * @var config_param
	 * 		The command arguments. For example:
	 * 			git commit -a -m "this is a commit"
	 * 		config_param[0] = ""
	 * 		config_param[1] = "this is a commit"
	 * 		If there were more type:param pairs after the string "this is a commit", then config_param[1] would
	 * 		be terminated with a space character, not a NULL character, just like for the config_type
	 * 		parameter. This means when parsing config_param[i] for any 'i', that only the
	 * 		characters up to the next NULL or white space character should be considered.
	 * @var count
	 * 		The number of command:arg pairs there are. For example:
	 *	 		git commit -a -m "this is a commit"
	 * 		count = 2
	 * 		If count = 0, then config_type and config_param are not valid and may be NULL pointers.
	 * 		If count > 0 then only config_type[i] and config_param[i] for 0 < i < count are valid pointers.
	 * 		For indices where the index > count the pointers are not valid and may be NULL.
	 * @details
	 *		Some programs have a type:param pair where config_type[i] = "" for only one 'i',
	 * 		this means the config_param is a final input to the program. For example:
	 * 			echo "hello world"
	 * 		the "hello world" is a final parameter with no config type.
	 * 			config_type[0] = ""
	 * 			config_param[0] = "hello world"
	 * 		Refering to the syntax given for CCProgram, the type:param pair where config_type = "" is the
	 * 		operation.
	 * 		The maximum number of type:param pairs a program can accept is defined by CCPROGRAM_MAX_ARG_COUNT.
	 * @returns
	 * 		An applicable error code.
	 */
	CCProgramError (*run_hook)( struct CCProgram*, const char** config_type, const char** config_param, size_t count );
};

/**
 * @memberof CCProgram
 * @ingroup VTable
 * @details
 *		Get vtable reference for CCProgram class.
 */
const struct CCProgram_VTable* CCProgram_VTable_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCProgram
 * @constructor
 * @var self
 * 		The program to construct.
 * @var printer
 * 		The printer to use for sending messages to console.
 * @var name
 * 		The name of the command. This is taken by copy and can be at most
 * 		CCPROGRAM_MAX_NAME_LENGTH bytes long.
 * @return
 * 		Error code.
 */
CError CCProgram( struct CCProgram* self, struct CIPrint* printer, const char* name );


/************************************************************************/
/* Methods																*/
/************************************************************************/
/**
 * @memberof CCProgram
 * @details
 * 		Print a help message to console for this program.
 */
void CCProgram_Help( struct CCProgram* self );

/**
 * @memberof CCProgram
 * @details
 * 		Runs the program.
 * @param command
 * 		The unparsed command string given to the program. For example:
 * 		@code
 * 			git commit -a -m "this is a git commit"
 * 		@endcode
 * 		For this program, the unparsed command string is: "-a -m \"this is a git commit\"\0".
 * 		The programs name is "git commit"
 * 		This string must be NULL terminated.
 * @param length
 * 		The length of the command string.
 * @returns
 * 		Error code
 */
CCProgramError CCProgram_Run( struct CCProgram* self, const char* command );

/**
 * @memberof CCProgram
 * @details
 * 		Get the name of the program.
 * @returns
 * 		Null terminated string which is the name of the program.
 */
const char* CCProgram_GetName( struct CCProgram* self );


#endif /* TERM_CCPROGRAM */
