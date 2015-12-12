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

#include "Class.h"
#include <stdlib.h>

const char* CAssertVirtualMessage_ = C_ASSERT_VIRTUAL_MESSAGE;
const char* CAssertSuperMethodMessage_ = C_ASSERT_SUPER_METHOD_MESSAGE;
const char* CAssertObjectMessage_ = C_ASSERT_OBJECT_MESSAGE;
const char* CAssertCastMessage_ = C_ASSERT_CAST_MESSAGE;

#if defined( DEBUG )
void CAssert( char exp, char const* msg, char const* file, int line )
{
 	if( exp ) { 	
#if defined( C_MINIMAL_DEBUG )
 		(void) msg;
 		C_PRINT( "In file: %s\nOn line: %d\n", file, line );									
#else
 		C_PRINT( "In file: %s\nOn line: %d\nCClass failure with message:\n%s\n", file, line, msg );
#endif
 		C_FAILED_ASSERT_HANDLE( );
 	}												
}

void CAssert2( char exp, char const* msg1, char const* msg2, char const* file, int line )
{
 	if( exp ) { 												
 #if defined( C_MINIMAL_DEBUG )
 		(void) msg1; (void) msg2;
 		C_PRINT( "In file: %s\nOn line: %d\n", file, line );									
#else
 		C_PRINT( "In file: %s\nOn line: %d (function %s)\nCClass failure with message:\n%s\n", file, line, msg2, msg1 );									
#endif
 		C_FAILED_ASSERT_HANDLE( );
 	}												
}
#endif

void* CVirtualMethod_( void* self, const char* file, int line )
{
	C_ASSERT_CAST( ((struct CRoot*) self)->C_ROOT, file, line );
	return ((struct CRoot*) self)->C_ROOT;	
}

void CObject_Destroy( struct CObject* self )
{
	CAssertVirtual(self, CDestructor);
	self->CDestructor(self);
}

void CObject_IsDynamic( struct CObject* self )
{
	CAssertObject(self);
	self->CObject_Free = CDefaultFree;
}

void CObject_SetFree( struct CObject* self, CFreeType objectFree )
{
	CAssertObject(self);
	CAssertObject(objectFree);
	self->CObject_Free = objectFree;
}

static void CDestructor( struct  CObject* self )
{
	if( self->CObject_Free != NULL )
	{
		self->CObject_Free((void*) self);
	}
}

struct CObject* CObject( struct CObject* self )
{
	self->C_ROOT = (void*) self;
	self->CDestructor = CDestructor;
	self->CObject_Free = NULL;
	return self;
}
