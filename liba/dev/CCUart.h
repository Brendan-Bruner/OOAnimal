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
#ifndef DEV_UART
#define DEV_UART

#include <rtos.h>
#include <dev_defines.h>
#include <Class.h>
#ifdef __LPC17XX__
#include <chip.h>
#endif

/************************************************************************/
/* Class and vtable decalre.											*/
/************************************************************************/
/**
 * @struct CCUart
 * @extends 
 * @ingroup 
 * @details
 */
struct CCUart
{
	/* Super class must always be first member
	 * of a C class struct. 
	 */
	struct CObject cObject;

	/* Private data.
	 */
#ifdef __LPC17XX__
	COSQueue		tx_queue;
	COSQueue		rx_queue;
	LPC_USART_T* 	uart_port_type;
	IRQn_Type 		irq_vector;
#else
#error "CCUart included in project without a valid declaration"
#endif
};

/**
 * @ingroup VTable
 * @brief
 *	CCUart's vtable declaration.
 */
struct CCUart_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	/* Since we are overriding the destructor, we need to keep */
	/* keep a reference to the super class' implementation of */
	/* the destructor. */
	const struct CObject_VTable* CObject_VTable_Ref;

	/* Space for a copy of the implemented interface's virtual table */
};

/**
 * @memberof CCUart
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCUart class.
 */
const struct CCUart_VTable* CCUart_VTable_Key( );


/************************************************************************/
/* Methods																*/
/************************************************************************/
/**
 * @memberof CCUart
 * @constructor
 * @details
 * 		Get the uart object for uart 0. Default device configurations are
 * 		defined in dev_defines.h
 * @returns
 * 		The uart object for serial communication of uart 0. NULL on failure to
 * 		construct the uart object. This method will never return NULL if any previously
 * 		call returned a non NULL value.
 */
struct CCUart* CCUart_GetDev0( );

/**
 * @memberof CCUart
 * @constructor
 * @details
 * 		Get the uart object for uart 1. Default device configurations are
 * 		defined in dev_defines.h
 * @returns
 * 		The uart object for serial communication of uart 1. NULL on failure to
 * 		construct the uart object. This method will never return NULL if any previously
 * 		call returned a non NULL value.
 */
struct CCUart* CCUart_GetDev1( );

/**
 * @memberof CCUart
 * @constructor
 * @details
 * 		Get the uart object for uart 2. Default device configurations are
 * 		defined in dev_defines.h
 * @returns
 * 		The uart object for serial communication of uart 2. NULL on failure to
 * 		construct the uart object. This method will never return NULL if any previously
 * 		call returned a non NULL value.
 */
struct CCUart* CCUart_GetDev2( );

/**
 * @memberof CCUart
 * @constructor
 * @details
 * 		Get the uart object for uart 3. Default device configurations are
 * 		defined in dev_defines.h
 * @returns
 * 		The uart object for serial communication of uart 3. NULL on failure to
 * 		construct the uart object. This method will never return NULL if any previously
 * 		call returned a non NULL value.
 */
struct CCUart* CCUart_GetDev3( );

size_t CCUart_Tx( struct CCUart* self, const char* buffer, size_t length );
size_t CCUart_Rx( struct CCUart* self, char* buffer, size_t length );
size_t CCUart_RxBlocking( struct CCUart* self, char* buffer, size_t length, COSTime block );
size_t CCUart_Available( struct CCUart* self );
void CCUart_FlushTx( struct CCUart* self );
void CCUart_FlushRx( struct CCUart* self );

#endif /* DEV_UART */
