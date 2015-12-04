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

void COTAssert( void* exp, char const* msg, char const* file, int line )
{
 	if( exp == NULL ) { 												
 		COT_PRINT( "In file: %s\nOn line: %d\nCOTClass failure with message:\n%s\n", file, line, msg );									
 		COT_FAILED_ASSERT_HANDLE( );
 	}												
}

/*
 * Find the memory location of the object which belongs to the class
 * given by classID. classID is the string name of the class the object
 * is a part of.
 * For example, Fox extends Animal.
 * Fox is a class which inherits from the class Animal.
 *		// This will find the memory Location of the Animal component of Fox.
 * 		extern Fox* fox;
 *		Animal* animal = COTFindSuper_( (void*) fox, "Animal" );
 *
 *		// This will return a NULL pointer, Animal does not have a Fox component.
 *		extern Animal* animal;
 *		Fox* fox = COTFindSuper_( (void*) animal, "Fox" );
 */
void* COTFindSuper_( void* object, char const* classID )
{
	COTClassClass* classLookup = ((COTObject*) object)->COT_CLASS_CLASS;
	for( ;; )
	{
		if( 0 == COT_STRNCMP( classLookup->classID, classID, COT_LONGEST_CLASS_NAME ) )
			return classLookup.object; /* Found the class of the object being lookedup. */

		if( classLookup->next == NULL )
			return NULL; /* This object does not belong to this class. */

		classLookup = classLookup->next;
	}
}

void* COTConstructor_( COTObject* self, size_t size, const COTClass* class )
{
	static COTClass COTClassInstance = (COTClass) { .classID = "COTObject", 
	                                                .object = (void* const) self,
	                                                .next = NULL }; 	                                                              
	if( self->COT_CLASS_CLASS == NULL )
	{
		/* This is constructor for highest level of class hierchy. */
		/* ie, if B inherits from A, this is B's constructs. */
		
		/* Zero out all memory locations, this makes all virtual methods (function */
		/* pointer) NULL. This will catch, at run time, missing linkages. */
		COT_INIT_OBJECT( self, size );

		/* Add reference to COTObjects class class. */
		self->COT_CLASS_CLASS = &COTClassInstance;

		/* Link virtual methods of COTObject. */
		COTObjectCreate_( (COTObject*) self );
	}
	else
	{
		/* Not the highest level, go through classes until an empty slot is found. */
		COTClass** nextClass = &self->COT_CLASS->next;
		for( ;; )
		{
			if( *nextClass == NULL )
				*nextClass = class; /* Found a free slot. */
			else
				nextClass = &(*nextClass)->next;
		}
	}

	return (void*) self;
}

void COTObject_Destroy( COTObject* self )
{
	COTCallVirtual( COTObject, self, COTObjectVirtual_Destructor )( self );
}

void COTObject_IsDynamic( COTObject* self )
{
	COT_ASSERT_OBJECT( self );
	self->COTObject_Free = COTDefaultFree;
}

void COTObject_SetFree( COTObject* self, COTFreeType objectFree )
{
	COT_ASSERT_OBJECT( self );
	self->COTObject_Free = objectFree;
}

static void COTObjectVirtual_Destructor( COTObject* self )
{
	if( self->COTObject_Free != NULL )
	{
		self->COTObject_Free( (void*) self );
	}
}

void COTObjectCreate_( COTObject* self )
{
	self->COTObjectVirtual_Destructor = COTObjectVirtual_Destructor;
	self->COTObject_Free = NULL;
}
