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
 * Aug 17, 2016
 */
/**
 * @file
 */
#ifndef DEV_CCUART_PRINTN
#define DEV_CCUART_PRINT

#include <CIPrint.h>
#include <CError.h>
#include <CCUart.h>

/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCUartPrint
 * @extends CIPrint
 * @ingroup Printers
 * @details
 * 		Uses a uart serial line to print/get characters.
 */
struct CCUartPrint
{
	/* Super class must always be first member
	 * of a C class struct. 
	 */
	struct CObject cObject;

	/* Implementing interfaces. 
	 */
	struct CIPrint cIPrint;

	/* Private data.
	 */
	struct CCUart* uart;
	char string_buffer[CCUART_PRINTER_MAX_STRING];
};

/**
 * @ingroup VTable
 * @brief
 *	CCUartPrint's vtable declaration.
 */
struct CCUartPrint_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  cObject_VTable;

	/* Space for a copy of the implemented interface's virtual table */
	struct CIPrint_VTable cIPrint_VTable;
};

/**
 * @memberof CCUartPrint
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCUartPrint class.
 */
const struct CCUartPrint_VTable* CCUartPrint_VTable_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCUartPrint
 * @constructor
 * @details
 * 		Creates a printing object that will use uart for stdin/stdout.
 * @param uart
 * 		The uart object to use for input/output.
 * @returns
 * 		An error code
 */
CError CCUartPrint( struct CCUartPrint* self, struct CCUart* uart );


/************************************************************************/
/* Methods																*/
/************************************************************************/


#endif /* DEV_CCUART_PRINT */
