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
#include <TestSuites.h>

static Allocator* allocator;

TEST_SETUP( )
{
	allocator = interface( Allocator, createDynamicAllocator( ) );
}
TEST_TEARDOWN( )
{
	allocator->destroy( (Interface*) allocator );
}

TEST( malloc_and_free )
{
	int* testVar;

	testVar = allocator->malloc( allocator, sizeof(int) );
	ASSERT( "did not get valid pointer", testVar != NULL );
	allocator->free( allocator, testVar );
}

TEST_SUITE( DynamicAllocator )
{
	ADD_TEST( malloc_and_free );
}
