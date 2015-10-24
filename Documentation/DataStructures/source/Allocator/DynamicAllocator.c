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
 * Oct 4, 2015
 */

#include <DynamicAllocator.h>
#include <stdlib.h>

/****************************************************************************/
/* Virtual Methods															*/
/****************************************************************************/
static void* allocatorMalloc( self(Allocator), size_t bytes )
{
	InterfaceOf( DynamicAllocator );
	return malloc( bytes );
}

static void allocatorFree( self(Allocator), void* memory )
{
	InterfaceOf( DynamicAllocator );
	free( memory );
}


/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
DynamicAllocator* createDynamicAllocator( )
{
	static DynamicAllocator self_;
	static DynamicAllocator* self = NULL;

	if( self == NULL )
	{
		self = &self_;
		createObject( (Object*) self );
		LinkInterface( Allocator );
		LinkInterfaceMethodConflictingNames( Allocator, malloc, allocatorMalloc );
		LinkInterfaceMethodConflictingNames( Allocator, free, allocatorFree );
	}

	return self;
}
