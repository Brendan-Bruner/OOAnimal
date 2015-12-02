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

/* This is used to assert points are non null before dereferencing them. */
/* The pointers asserted with this should never be null. This defines how */
/* to handle a failed assertion. */
#include <stdio.h>
#define COT_ASSERT( O )																\
				do {																\
				   if( (O) == 0 ) { 												\
				   	printf("NULL pointer exception:\nfile %s\nline %d\n", 			\
				   				(char *) __FILE__, __LINE__ ); 						\
					for( ;; );														\
				   }																\
				} while( 0 )


/* Define the memory management functions to use when dynamically allocating. */
#define COT_MALLOC malloc
#define COT_FREE free

/* Name of a variable indicating allocation scheme. */
#define COT_FREE						_cf

/* All classes and interfaces contain a pointer to their highest */
/* super class, the base object, this is the name of that pointer. */
#define COT_BASE_CLASS					_co

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
#define COT_INTERFACE_OFFSET	 		_io

/* Name used to reference the object within class methods. This variable */
/* is 'self' in python and 'this' in java / C++. Note, making this variable */
/* 'this' will prevent compatibility with C++ code. */
#define COT_OBJECT_REFERENCE	 		self


/****************************************************************************/
/* Memory Management 														*/
/****************************************************************************/
typedef void* (*COTMallocType)( size_t );
typedef void (*COTFreeType)( void* );
extern COTMallocType COTMalloc;
extern COTFreeType COTFree;


/****************************************************************************/
/* Base object																*/
/****************************************************************************/
typedef struct COTObject
{
	void (*COTObjectVirtual_Destructor)( struct COTObject* );
	void (*COTObjectVirtual_Free)( void* );

} COTObject;
extern void COTObjectCreate_( COTObject* );


/******************************************************************************/
/* Used to create and destroy objects. */
/******************************************************************************/
/* Used to select COT_MALLOC_AND_SETUP_OBJ or COT_SETUP_OBJ */
#define COT_SETUP_SELECTION( _1, _2, SELECTION, ... ) SELECTION
#define COTNew( ... ) \
	COT_SETUP_SELECTION( __VA_ARGS__, COT_MALLOC_AND_SETUP_OBJ, COT_SETUP_OBJ )( __VA_ARGS__ )

static inline void* COTNew_( size_t size )
{
	void* obj = COTMalloc( size );
	if( obj == NULL ){ return NULL; }
	((COT_CLASS_OBJECT*) obj)->COT_IS_COT_DYNAMIC_OBJECT = COT_DYNAMIC_OBJECT;
	COTCreateObject( (COT_CLASS_OBJECT*) obj );
	return obj;	
}
#define COT_MALLOC_AND_SETUP_OBJ( type ) \
	(type*) COTNew_( sizeof(type) )

static inline void* COTCreate_( COT_CLASS_OBJECT* obj )
{
	obj->COT_IS_COT_DYNAMIC_OBJECT = COT_STATIC_OBJECT;
	COTCreateObject( obj );
	return obj;
}
#define COT_SETUP_OBJ( type, obj )															\
	(type*) COTCreate_( (COT_CLASS_OBJECT*) obj )

static inline void COTDestroy_( void* mem, size_t offset )
#define COTDestroy( type, mem )																\
	do {																					\
		type * COT##type##Object = (mem);													\
		COT_ASSERT( (COT##type##Object) );													\
		COT_CLASS_OBJECT* object = (COT##type##Object)->COT_CLASS_OBJECT_NAME;				\
		COT_ASSERT( object->COT_VIRTUAL_TABLE_HIDER_NAME.destroy );				\
		object->COT_VIRTUAL_TABLE_HIDER_NAME. destroy( object );					\
		if( object->COT_IS_COT_DYNAMIC_OBJECT == COT_DYNAMIC_OBJECT ){						\
			COTFree( (void*) object );														\
		}																					\
	} while( 0 )


/********************************************************************************/
/* Helper macros for defining a class and interface								*/
/********************************************************************************/
/* Must be first in any class. */
#define COTClass( COTSuper )				\
	struct {								\
		struct COTSuper		COT_SUPER;		\
		struct COTObject*	COT_BASE_CLASS;	\
	}_
/* Must be in any interface. */
#define COTInterface( )								\
	struct {										\
		void*				COT_INTERFACE_OFFSET;	\
		struct COTObject* 	COT_BASE_CLASS;			\
	}_
/* Used to override destructor. */
#define COTDestructor( ) \
			void (*COTObjectVirtual_Destructor)( COTObject* )
/* Used to implement an interface in a class' definition. */
#define COTImplements( iface )	\
	iface COT_TO_IFACE_VAR_NAME( iface );

/****************************************************************************/
/* Constructor specific setup												*/
/****************************************************************************/
#define COTConstructorOf( C )														\
	if( COT_OBJECT_PRE_REFERENCE_NAME == 0 ){ return; }								\
	C* COT_OBJECT_REFERENCE = (C*) COT_OBJECT_PRE_REFERENCE_NAME;						\
	COT_OBJECT_REFERENCE->COT_CLASS_OBJECT_NAME = (COT_CLASS_OBJECT*) COT_OBJECT_REFERENCE

/* Bind the interface data at run time. Use in constructor */
#define COTCreateInterface(t) 												\
	do {																	\
		COT_OBJECT_REFERENCE->COT_TO_IFACE_VAR(t) = (t) { 0 };				\
		COT_OBJECT_REFERENCE->COT_IFACE_VAR( t ).COT_INTERFACE_OFFSET = 	\
		(void *) (((char *) &(COT_OBJECT_REFERENCE->COT_IFACE_VAR( t ))) - (char *) COT_OBJECT_REFERENCE); 	\
		COT_OBJECT_REFERENCE->COT_IFACE_VAR( t ).COT_CLASS_OBJECT = (COTObject*) COT_OBJECT_REFERENCE		\
	} while( 0 )


/******************************************************************************/
/* Used to dynamically link methods at run time. */
/******************************************************************************/
/* The two macros below select one of two virtual linkage macros. */
#define COT_LINK_VIRTUAL_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define COTLinkVirtual( ... ) \
	COT_LINK_VIRTUAL_SELECTION( __VA_ARGS__, COT_LINK_INTERFACE_VIRTUAL, COT_LINK_CLASS_VIRTUAL )( __VA_ARGS__ )

#define COT_LINK_CLASS_VIRTUAL( class, method ) \
	((class*) COT_OBJECT_REFERENCE)->COT_VIRTUAL_TABLE_HIDER_NAME. method = method

#define COT_LINK_INTERFACE_VIRTUAL( class, iface, method ) \
	((class*) COT_OBJECT_REFERENCE)->COT_TO_IFACE_VAR_NAME( iface ).COT_VIRTUAL_TABLE_HIDER_NAME. method = method

/* The two macros below link abstract methods. */
#define COT_LINK_ABSTRACT_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define COTLinkAbstract( ... ) \
	COT_LINK_ABSTRACT_SELECTION( __VA_ARGS__, COT_LINK_INTERFACE_ABSTRACT, COT_LINK_CLASS_ABSTRACT )( __VA_ARGS__ )

#define COT_LINK_CLASS_ABSTRACT( class, method ) \
	((class*) COT_OBJECT_REFERENCE)->COT_VIRTUAL_TABLE_HIDER_NAME. method = NULL

#define COT_LINK_INTERFACE_ABSTRACT( class, iface, method ) \
	((class*) COT_OBJECT_REFERENCE)->COT_TO_IFACE_VAR_NAME( iface ).COT_VIRTUAL_TABLE_HIDER_NAME. method = NULL

/******************************************************************************/
/* Used to override methods in super class / interface. */
/******************************************************************************/
/* The two macros below select one of two virtual linkage macros. */
#define COT_OVERRIDE_VIRTUAL_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define COTOverrideVirtual( ... ) \
	COT_OVERRIDE_VIRTUAL_SELECTION( __VA_ARGS__, COT_OVERRIDE_INTERFACE_VIRTUAL, COT_OVERRIDE_CLASS_VIRTUAL )( __VA_ARGS__ )

#define COT_OVERRIDE_CLASS_VIRTUAL( class, method )							\
	COT_OBJECT_REFERENCE->COT_OVERRIDE_TABLE_HIDER_NAME. method = ((class*) COT_OBJECT_REFERENCE)->COT_VIRTUAL_TABLE_HIDER_NAME. method; \
	((class*) COT_OBJECT_REFERENCE)->COT_VIRTUAL_TABLE_HIDER_NAME. method = method

#define COT_OVERRIDE_INTERFACE_VIRTUAL( class, iface, method )					\
	COT_OBJECT_REFERENCE->COT_OVERRIDE_TABLE_HIDER_NAME. method = ( (class*) COT_OBJECT_REFERENCE)->COT_TO_IFACE_VAR_NAME( iface ).COT_VIRTUAL_TABLE_HIDER_NAME. method; \
	((class*) COT_OBJECT_REFERENCE)->COT_TO_IFACE_VAR_NAME( iface ).COT_VIRTUAL_TABLE_HIDER_NAME.method = method

/* For overriding destructor. */
#define COTOverrideDestructor( )\
	COTOverrideVirtual(COTObject, destroy)

/******************************************************************************/
/* Used to access super class' implementation of a method. */
/******************************************************************************/
#define COTSuper( method ) \
	COT_ASSERT( COT_OBJECT_REFERENCE->COT_OVERRIDE_TABLE_HIDER_NAME. method ); \
	COT_OBJECT_REFERENCE->COT_OVERRIDE_TABLE_HIDER_NAME. method


/******************************************************************************/
/* Used to implement virtual methods and interface methods. */
/******************************************************************************/
#define COTCallVirtual( C, name )												\
	COT_ASSERT( COT_OBJECT_PRE_REFERENCE_NAME );										\
	COT_ASSERT( COT_OBJECT_PRE_REFERENCE_NAME->COT_VIRTUAL_TABLE_HIDER_NAME. name ); 	\
	C* COT_OBJECT_REFERENCE = (C*) COT_OBJECT_PRE_REFERENCE_NAME;						\
	return COT_OBJECT_PRE_REFERENCE_NAME->COT_VIRTUAL_TABLE_HIDER_NAME. name

#define COTMemberOf( C )															\
	COT_ASSERT( COT_OBJECT_PRE_REFERENCE_NAME );										\
	C* COT_OBJECT_REFERENCE = (C*) COT_OBJECT_PRE_REFERENCE_NAME


#define COTInterfaceOf(C) 															\
	COT_ASSERT( COT_OBJECT_PRE_REFERENCE_NAME ); 										\
	C *COT_OBJECT_REFERENCE = (C *) (((char*) COT_OBJECT_PRE_REFERENCE_NAME) - 				\
						((char*) COT_OBJECT_PRE_REFERENCE_NAME->COT_INTERFACE_OFFSET_NAME)); 	\

#define COTVirtualDestructor( )\
	static void destroy( self(COTObject) )
#define COTDestructorOf( C )\
	COTMemberOf(C)
#define COTSuperDestructor( )\
	COTSuper( destroy )( (COTObject*) self )

/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define COTCast(i,O) \
	(&(O)->COT_TO_IFACE_VAR_NAME( i ))

#endif /* CLASS_H_ */
