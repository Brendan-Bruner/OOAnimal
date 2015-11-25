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
 * Nov, 2015
 */

#include "TestSuites.h"
#include <Util/Memory/DynamicAllocator.h>

TEST_SETUP( )
{
}
TEST_TEARDOWN( )
{
}

TEST( null_queue )
{

}
	
TEST( size_one_queue )
{

}
	
TEST( unbounded_overflow )
{
	/* Inserting into a full queue adds space. insertion is successful. */
}
	
TEST( bounded_overflow )
{
	/* Inserting into a full queue fails to add space, inerstion fails. */
	/* Should be able to remove one element then successfully insert once. */
}

#if (configUSE_COTCONTAINER == 1)
TEST( container )
{

}
#endif

TEST( destructor_memory_cleanup )
{

}

TEST( destructor_overflow_memory_cleanup )
{

}

TEST_SUITE( COTLinkedQueue )
{
	ADD_TEST( null_queue );
	ADD_TEST( size_one_queue );
	ADD_TEST( unbounded_overflow );
	ADD_TEST( bounded_overflow );
	ADD_TEST( destructor_memory_cleanup );
	ADD_TEST( destructor_overflow_memory_cleanup );
	#if (configUSE_COTCONTAINER == 1)
	ADD_TEST( container );
	#endif
}
