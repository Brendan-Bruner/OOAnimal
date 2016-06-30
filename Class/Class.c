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

/* This puts large diag messages in .bss instead of on function stack */
/* when called in the CAssert( ) function. */
#if C_DEBUG_DIAG_LEVEL == 2
const char* CAssertVirtualMessage_ = C_ASSERT_VIRTUAL_MESSAGE;
const char* CAssertSuperMethodMessage_ = C_ASSERT_SUPER_METHOD_MESSAGE;
const char* CAssertObjectMessage_ = C_ASSERT_OBJECT_MESSAGE;
const char* CAssertCastMessage_ = C_ASSERT_CAST_MESSAGE;
#endif

/* Assert method. */
#if defined( DEBUG )
void CAssert( char exp, char const* msg, char const* file, int line )
{
 	if( exp ) { 	
#if C_DEBUG_DIAG_LEVEL == 1
 		(void) msg;
 		C_PRINT( "In file: %s\nOn line: %d\n", file, line );									
#elif C_DEBUG_DIAG_LEVEL == 2
 		C_PRINT( "In file: %s\nOn line: %d\nCClass failure with message:\n%s\n", file, line, msg );
#elif C_DEBUG_DIAG_LEVEL == 0
 		(void) msg;
 		(void) file;
 		(void) line;
#endif
 		C_FAILED_ASSERT_HANDLE( );
 	}												
}
#endif

/* Cast object back to its original class type. */
void* CObjectCast_( void* self, const char* file, int line )
{
	CAssert( self == NULL, CAssertObjectMessage_, file, line);
	C_ASSERT_CAST( ((struct CClass*) self)->C_ROOT, file, line );
	return ((struct CClass*) self)->C_ROOT;
}

/* Wrapper for calling destructor. */
void CObject_Destroy( struct CObject* self )
{
	CAssertObject(self);
	((struct CObject_VTable*) CGetVTable(self))->CDestructor(self);
}

/* Set memory free method called in destructor. */
void CObject_SetFree( struct CObject* self, CFreeType objectFree )
{
	CAssertObject(self);
	CAssertObject(objectFree);
	self->CObject_Free = objectFree;
}

/* Destructor. */
static void CDestructor( void* self_ )
{
	struct CObject* self = CCast(self_);

	if( self->CObject_Free != NULL )
	{
		self->CObject_Free(self);
	}
}

/* Create vtable. */
const struct CObject_VTable* CObject_VTable_Create( )
{
	static const struct CObject_VTable CObject_VTable =
	{
		.CDestructor = CDestructor
	};
	return &CObject_VTable;
}

/* Constructor for base object. */
struct CObject* CObject_Constructor( struct CObject* self, size_t objectSize )
{
	/* Assert non NULL pointer. */
	C_ASSERT_OBJECT(self);

	/* Set entire object to 0 for run time checks. */
	C_INIT_OBJECT(self, objectSize);

	/* Map vtable. */
	CVTable(self, CObject_VTable_Create( ));

	/* Setup object data. */
	self->C_CLASS.C_ROOT = self;
	self->C_CLASS.C_VTABLE_OFFSET = 0;
	self->CObject_Free = NULL;
	return self;
}
