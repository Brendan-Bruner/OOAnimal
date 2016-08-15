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
#ifndef TERM_CCPROGRAM_LIST
#define TERM_CCPROGRAM_LIST

#include <CCArrayList.h>
#include <term_defines.h>
#include <CCProgram.h>

/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCProgramList
 * @ingroup Programs
 * @details
 * 		Provides a list like interface for keeping track of programs. List
 * 		items are weakly aggregated and therefore are not destroyed when
 * 		this object is destroyed.
 */
struct CCProgramList
{
	/* Super class must always be first member
	 * of a C class struct.
	 */
	struct CObject cObject;

	/* Private data.
	 */
	char list_memory[CCARRAY_LIST_SIZE(sizeof(struct CCProgram*), CCPROGRAM_LIST_MAX_PROGRAMS)];
	struct CCArrayList list;
};

/**
 * @ingroup VTable
 * @brief
 *	CCProgramList's vtable declaration.
 */
struct CCProgramList_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;
};

/**
 * @memberof CCProgramList
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCProgramList class.
 */
const struct CCProgramList_VTable* CCProgramList_VTable_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCProgramList
 * @constructor
 */
CError CCProgramList( struct CCProgramList* self );


/************************************************************************/
/* Methods																*/
/************************************************************************/
/**
 * @memberof CCProgramList
 * @details
 * 		Adds the program to the list.
 * @param program
 * 		The program to add.
 * @returns
 * 		A logical true value when the program is inserted, or a logical false
 * 		if the list is full and the program was not inserted.
 */
CBool CCProgramList_Add( struct CCProgramList* self, struct CCProgram* program );

/**
 * @memberof CCProgramList
 * @details
 * 		Removes the named program from the list.
 * @param name
 * 		The name of the program to remove.
 * @returns
 * 		A pointer to the program removed. NULL if a program by the given
 * 		name doesn't exist in the list.
 */
struct CCProgram* CCProgramList_Remove( struct CCProgramList* self, const char* name );

/**
 * @memberof CCProgramList
 * @details
 * 		Get the named program from the list without removing it.
 * @param name
 * 		The name of the program to get.
 * @param length
 * 		Length of name string.
 * @returns
 * 		A pointer to the program returned. NULL if a program by the given
 * 		name doesn't exist in the list.
 */
struct CCProgram* CCProgramList_Get( struct CCProgramList* self, const char* name, size_t length );

#endif /* TERM_CCPROGRAM_LIST */
