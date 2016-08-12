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
#ifndef DEV_CCDEBUG_PRINT
#define DEV_CCDEBUG_PRINT

#include <CIPrint.h>
#include <FreeRTOS.h>
#include <semphr.h>

/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCDebugPrint
 * @extends CIPrint
 * @ingroup Printers
 * @details
 * 		Implements the CIPrint interface using the stdio
 * 		library of functions.
 * @warning
 * 		This is a singleton class. To get a reference to it, call the
 * 		method:
 * 		*  * CCDebugPrint_GetInstance();
 */
struct CCDebugPrint
{
	/* Super class must always be first member */
	/* of a C class struct. */
	struct CObject cObject;

	/* Implementing the CIPrint interface. */
	struct CIPrint cIPrint;

	/* Private data.
	 */
	xSemaphoreHandle io_mutex;
};

/**
 * @ingroup VTable
 * @brief
 *	CCDebugPrint's vtable declaration.
 */
struct CCDebugPrint_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  cObject_VTable;

	/* Space for a copy of the implemented interface's virtual table */
	struct CIPrint_VTable cIPrint_VTable;
};

/**
 * @memberof CCDebugPrint
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCDebugPrint class.
 */
const struct CCDebugPrint_VTable* CCDebugPrint_Get_Key( );


/************************************************************************/
/* Constructor															*/
/************************************************************************/
/**
 * @memberof CCDebugPrint
 * @constructor
 * @details
 * 		Get the instance of the CCDebugPrint object.
 * @returns
 * 		Always returns the instance of the CCDebugPrint object.
 */
struct CCDebugPrint* CCDebugPrint_GetInstance( );


#endif /* DEV_CCDEBUG_PRINT */
