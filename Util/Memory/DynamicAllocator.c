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
 * Nov. 2015
 */

#include "DynamicAllocator.h"

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
void* memoryAllocate( self(COTAllocator), size_t bytes )
{
	COTInterfaceOf(COTDynamicAllocator);
	(void) self;
	if( bytes == 0 ){ return NULL; }
	return COTMalloc( bytes );
}

void memoryFree( self(COTAllocator), void* memory )
{
	COTInterfaceOf(COTDynamicAllocator);
	(void) self;
	if( memory == NULL ){ return; }
	COTFree( memory );
}

/****************************************************************************/
/* Non Virtual Methods														*/
/****************************************************************************/
static void COTDynamicAllocatorCreate( self(COTDynamicAllocator) );
COTDynamicAllocator* COTDynamicAllocator_GetInstance( )
{
	static COTDynamicAllocator self_;
	static COTDynamicAllocator* self = NULL;
	if( self == NULL )
	{
		self = &self_;
		COTCreate( self, COTDynamicAllocatorCreate( self ) );
	}
	return self;
}

/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
/**
 * @memberof COTDynamicAllocator
 * @private
 * @brief
 * 		<b>Constructor</b>.
 * @details
 *		<b>Constructor</b>.
 */
static void COTDynamicAllocatorCreate( self(COTDynamicAllocator) )
{
	COTConstructorOf(COTDynamicAllocator);
	COTCreateInterface(COTAllocator);
	COTLinkVirtual(COTDynamicAllocator, COTAllocator, memoryAllocate);
	COTLinkVirtual(COTDynamicAllocator, COTAllocator, memoryFree);
}