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

#ifndef CLASS_H_
#define CLASS_H_		

#include <stddef.h>
#include <stdlib.h>

/*
 * The assert macros are used to trap user errors. 
 */
#include <stdio.h>
#define COT_PRINT( ... ) printf( __VA_ARGS__ )
#define COT_FAILED_ASSERT_HANDLE( ) for( ;; )
extern void COTAssert( void* exp, char const* msg, char const* line, int lineNumber );

#define COT_ASSERT_VIRTUAL_MESSAGE \
	"Virtual method not linked. Possible causes:\n"\
	"\t* Class constructor did not call COTLinkVirtual( ) for the method\n"\
	"\t* If the method is from an interface, class constructor did not\n\t  call COTLinkInterface( )\n"\
	"\t* Constructor was never called on object\n"
#define COT_ASSERT_VIRTUAL( method )\
	COTAssert( (void*) (method), COT_ASSERT_VIRTUAL_MESSAGE, __FILE__, __LINE__ )

#define COT_ASSERT_SUPER_METHOD_MESSAGE \
	"Super method not linked: Possible causes:\n"\
	"\t* Class constructor did not call COTOverrideVirtual( ) for\n\t  the method\n"
#define COT_ASSERT_SUPER_METHOD( method )\
	COTAssert( (void*) (method), COT_ASSERT_SUPER_METHOD_MESSAGE, __FILE__, __LINE__ )

#define COT_ASSERT_OBJECT_MESSAGE \
	"Attempt to call class method on NULL object\n"
#define COT_ASSERT_OBJECT( object )\
	COTAssert( (void*) (object), COT_ASSERT_OBJECT_MESSAGE, __FILE__, __LINE__ )

/* All classes and interfaces contain a pointer to their highest */
/* super class, the base object, this is the name of that pointer. */
#define COT_BASE_CLASS					_co

/* All classes have a pointer to the class class, ie, the class */
/* that tells a class how to be a class. */
#define	COT_CLASS						_cc

/* If a class inherits, it will contain an instance of the class it */
/* is inheriting from. This is the name of that instance. */
#define COT_SUPER	 					_sp

/* When a class implementings an interface, it contains an */
/* instance of the interface. This is prefixed / posfixed to the data type */
/* of the interface and used as the variable name. */
#define COT_INTERFACE_PREFIX 			_if
#define COT_INTERFACE_POSIFX
#define COT_IFACE_VAR( i ) \
	COT_INTERFACE_PREFIX##i##COT_INTERFACE_POSFIX

/* Interfaces contain a pointer offset from the class implemeting them. */
/* This is the name of the variable used to save the offset. */
#define COT_OBJECT_OFFSET	 			_io

/* Name used to reference the object within class methods. This variable */
/* is 'self' in python and 'this' in java / C++. Note, making this variable */
/* 'this' will prevent compatibility with C++ code. */
#define COT_OBJECT_REFERENCE	 		self

/* Used to zero out a structure. */
/* This assumes that NULL resolves to 0, which is requried by C standard. */
#include <string.h>
#define COT_INIT_OBJECT( object, size )					\
	do {												\
		memset( (void*) (object), 0, size );			\
	} while( 0 )

/* Used to compare strings. */
#define COT_STRNCMP( str1, str2, size )
	strncmp( str1, str2, size )

/* Default memory clean up method used. */
/* Calling COTObject_IsDynamic( ) on an object will invoke this free method */
/* being called after destruction. */
#define COTDefaultFree free


/****************************************************************************/
/* Class class																*/
/****************************************************************************/
typedef struct COTClass COTClass
struct COTClass
{
	const char* const classID;
	void* const object;
	const COTClass* next;
};

/****************************************************************************/
/* Class object																*/
/****************************************************************************/
typedef void (*COTFreeType)( void* );
typedef struct COTObject COTObject;
struct COTObject
{
	void (*COTObjectVirtual_Destructor)( COTObject* );
	COTFreeType COTObject_Free;

};
extern void COTObjectCreate_( COTObject* );
extern void COTObject_Destroy( COTObject* );
extern void COTObject_IsDynamic( COTObject* );
extern void COTObject_SetFree( COTObject*, COTFreeType );


/****************************************************************************/
/* Used destroy objects. 													*/
/****************************************************************************/
static inline void* COT_( void* object )
{
	((COTObject*) object)->COT_CLASS = NULL;
	return object;
}
#define COT( object ) \
	COT_( (void*) object )

static inline void COTDestroy_( COTObject** object )
{
	COTAssert( (void*) (object), COT_ASSERT_OBJECT_MESSAGE, __FILE__, __LINE__ );
	COTObject_Destroy( *object );
}
#define COTDestroy( mem )	\
	COTDestroy_ ( &((mem)->_.COT_BASE_CLASS) )


/********************************************************************************/
/* Helper macros for defining a class and interface								*/
/********************************************************************************/
/* Must be first in any class. */
/* The COTClass pointer must always be first. */
#define COTExtends( COTSuper )						\
	struct {										\
		COTClass* COT_CLASS; /* MUST be first. */	\
		COTSuper				COT_SUPER;			\
		void*					COT_OBJECT_OFFSET;	\
	}_


/****************************************************************************/
/* Constructor specific setup												*/
/****************************************************************************/
#define COTObjectInit( C, self_ )														\
	static COTClass COTClassInstance = (COTClass)										\
	{ .classID = #C, .object = (void* const) self_, .next = NULL };						\
	C* COT_OBJECT_REFERENCE = NULL;														\
	do {																				\
		COT_ASSERT_OBJECT( self_ );														\
		extern void* COTConstructor_( COTObject*, size_t, const COTClass* );			\
		COT_OBJECT_REFERENCE = (C*) COTConstructor_( (COTObject*) self_, 				\
			                                         sizeof( *self_ ),					\
			                                         &COTClassInstance );				\
		COT_OBJECT_REFERENCE->_.COT_OBJECT_OFFSET = 									\
		(void *) (((char *) &(COT_OBJECT_REFERENCE)) - ((char *) COT_OBJECT_REFERENCE));\
	} while( 0 )


/******************************************************************************/
/* Used to dynamically link methods at run time. */
/******************************************************************************/
/* The two macros below select one of two virtual linkage macros. */
#define COT_LINK_VIRTUAL_SELECTION( _1, _2, SELECTION, ... ) SELECTION
#define COTLinkVirtual( ... ) \
	COT_LINK_VIRTUAL_SELECTION( __VA_ARGS__, COT_LINK_INTERFACE_VIRTUAL, COT_LINK_CLASS_VIRTUAL )( __VA_ARGS__ )
#define COT_LINK_CLASS_VIRTUAL( method ) \
	do { COT_OBJECT_REFERENCE-> method = method; } while( 0 )
#define COT_LINK_INTERFACE_VIRTUAL( iface, method ) \
	do { COT_OBJECT_REFERENCE->COT_IFACE_VAR( iface ). method = method; } while( 0 )

/* The two macros below are used to override a virtual method. */
/* They can be used in lue of COTOverrideVirtual( ) when the super class' implementation */
/* will never be call within the subclass class. */
#define COT_RE_LINK_VIRTUAL_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define COTReLinkVirtual( ... ) \
	COT_RE_LINK_VIRTUAL_SELECTION( __VA_ARGS__, COT_RE_LINK_INTERFACE_VIRTUAL, COT_RE_LINK_CLASS_VIRTUAL )( __VA_ARGS__ )
#define COT_RE_LINK_CLASS_VIRTUAL( class, method ) \
	do { ((class*) COT_OBJECT_REFERENCE)-> method = method; } while( 0 )
#define COT_RE_LINK_INTERFACE_VIRTUAL( iface, class, method ) \
	do { ((class*) COT_OBJECT_REFERENCE)->COT_IFACE_VAR( iface ). method = method; } while( 0 )

/* The two macros below select one of two virtual linkage macros for overriding methods. */
/* Use this in lue of COTReLinkVirtual( ) when the subclass must use the super classes */
/* implementation of the overriden method. */
#define COT_OVERRIDE_VIRTUAL_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define COTOverrideVirtual( ... ) \
	COT_OVERRIDE_VIRTUAL_SELECTION( __VA_ARGS__, COT_OVERRIDE_INTERFACE_VIRTUAL, COT_OVERRIDE_CLASS_VIRTUAL )( __VA_ARGS__ )
#define COT_OVERRIDE_CLASS_VIRTUAL( class, method )									\
	do {																			\
		COT_OBJECT_REFERENCE-> method = ((class*) COT_OBJECT_REFERENCE)-> method; 	\
		((class*) COT_OBJECT_REFERENCE)-> method = method;							\
	} while( 0 )
#define COT_OVERRIDE_INTERFACE_VIRTUAL( class, iface, method )					\
	do {																		\
		COT_OBJECT_REFERENCE-> method = ( (class*) COT_OBJECT_REFERENCE)->COT_IFACE_VAR( iface ). method; \
		((class*) COT_OBJECT_REFERENCE)->COT_IFACE_VAR( iface ).method = method;\
	} while( 0 )

/* Helper macros for overriding destructor. */
/* Call this one in constructor to setup linkage. */
#define COTOverrideDestructor( )\
	COTOverrideVirtual(COTObject, COTObjectVirtual_Destroy)
/* Put this in class definition. */
#define COTDestructor( ) \
			void (*COTObjectVirtual_Destructor)( COTObject* )

/******************************************************************************/
/* Used to access super class' implementation of a method. */
/******************************************************************************/
#define COTSuper( class, method ) \
	COT_ASSERT_SUPER_METHOD( ((class*) COT_OBJECT_REFERENCE)-> method ); \
	((class*) COT_OBJECT_REFERENCE)->COT_OVERRIDE_TABLE_HIDER_NAME. method


/****************************************************************************/
/* Helper macros for calling and setting up virtual methods					*/
/****************************************************************************/
extern void* COTFindSuper_( void*, char const* );
/* Asserts and then calls the virtual method. */
#define COTCallVirtual( type, self_, name )								\
	COT_ASSERT_OBJECT( self_ );											\
	type* object_ = COTFindSuper( (void*) self_, #type ); 				\
	COT_ASSERT_VIRTUAL( object-> name ); 								\
	return object_-> name

/* Sets up the 'self' variable in a class method. */
#define COTMethod( C, self_ ) 															\
	C* COT_OBJECT_REFERENCE;															\
	do {																				\
		COT_ASSERT_OBJECT( self_ );				 										\
		COT_OBJECT_REFERENCE = (C*) self_;												\
	} while( 0 )

#define COTVirtualDestructor( )\
	static void COTObjectVirtual_Destroy( COTObject* self_ )
#define COTSuperDestructor( class )\
	COTSuper( class, destroy )( (COTObject*) COT_OBJECT_REFERENCE )

/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define COTCast(i,O) \
	(&(O)->COT_IFACE_VAR( i ))

#endif /* CLASS_H_ */
