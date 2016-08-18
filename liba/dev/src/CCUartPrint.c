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

#include <CCUartPrint.h>
#include <clib.h>

/************************************************************************/
/* Methods																*/
/************************************************************************/
static void CCDebugPrint_String_Def( struct CIPrint* self_, const char* string )
{
	struct CCUartPrint* self = CCast(self_);

	size_t string_len = cstrnlen(string, CCUART_PRINTER_MAX_STRING);
	if( string_len > CCUART_PRINTER_MAX_STRING ) {
		string_len = CCUART_PRINTER_MAX_STRING;
	}

	CCUart_Tx(self->uart, string, string_len);
}

static void CCDebugPrint_StringF_Def( struct CIPrint* self_, const char* string, va_list args )
{
	struct CCUartPrint* self = CCast(self_);

	int size = vsnprintf(self->string_buffer, CCUART_PRINTER_MAX_STRING, string, args);
	if( size <= 0 ) {
		return;
	}
	if( size > CCUART_PRINTER_MAX_STRING ) {
		size = CCUART_PRINTER_MAX_STRING;
	}

	CCUart_Tx(self->uart, self->string_buffer, (size_t) size);
}

static char CCDebugPrint_GetC_Def( struct CIPrint* self_ )
{
	struct CCUartPrint* self = CCast(self_);

	char input;
	CCUart_RxBlocking(self->uart, &input, sizeof(input), BLOCK_UNTIL_READY);

	return input;
}


/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCUartPrint_VTable* CCUartPrint_VTable_Key( )
{
	static struct CCUartPrint_VTable vtable  =
		{
			/* Assigned implementation of this class' methods and
			 * methods of all interfaces implemented by this class.
			 */
			.cIPrint_VTable.string = CCDebugPrint_String_Def,
			.cIPrint_VTable.stringf = CCDebugPrint_StringF_Def,
			.cIPrint_VTable.getcharacter = CCDebugPrint_GetC_Def
		};

	/* Copy of super's vtable. */
	vtable.cObject_VTable = *CObject_VTable_Key( );

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
CError CCUartPrint( struct CCUartPrint* self, struct CCUart* uart )
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCUartPrint_VTable_Key( ));

	/* Third thing in constructor must be calling interface's constructor. 
	 */
	CInterface(self, &self->cIPrint, &CCUartPrint_VTable_Key( )->cIPrint_VTable);

	/* Setup aggregate data.
	 */
	if( uart == NULL ) {
		return COBJ_INV_PARAM;
	}
	self->uart = uart;

	return COBJ_OK;
}
