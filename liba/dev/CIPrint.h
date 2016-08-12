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
 * @defgroup Printers
 */
#ifndef DEV_CIPRINT
#define DEV_CIPRINT

#include <Class.h>
#include <stdarg.h>

/************************************************************************/
/* Interface declaration.						*/
/************************************************************************/
/**
 * @struct CIPrint
 * @ingroup Printers
 * @brief
 *	Interface for printing data to a console
 * @details
 *	Interface for printing data to a console
 */
struct CIPrint
{
	/* CInterface must always be first member of */
	/* an interface's struct .*/
	struct CInterface interface;
};

/**
 * @ingroup VTable
 * @brief
 *	CIPrint virtual table.
 */
struct CIPrint_VTable
{
	void (*string)( struct CIPrint* self, const char* string );
	void (*stringf)( struct CIPrint* self, const char* string, va_list args );
	char (*getcharacter)( struct CIPrint* self );
};

/************************************************************************/
/* Member functions.							*/
/************************************************************************/
/**
 * @memberof CIPrint
 * @details
 *		Print the input string.
 * @param self
 * 		The printer to use.
 * @param string
 * 		The string to print
 */
void CIPrint_String( struct CIPrint* self, const char* string );

/**
 * @memberof CIPrint
 * @details
 *		Print a formatted string.
 * @param self
 * 		The printer to use.
 * @param string
 * 		The string to print. Optionally arguments are the string format.
 * 		The format is the same as when using printf().
 */
void CIPrint_StringF( struct CIPrint* self, const char* string, ... );

/**
 * @memberof CIPrint
 * @details
 * 		Block until a character from the printers input is available.
 * @param self
 * 		The printer to use.
 * @returns
 * 		The retrieved character.
 */
char CIPrint_GetChar( struct CIPrint* self );

#endif /* DEV_CIPRINT */
