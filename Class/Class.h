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
#define COT_IS_COT_DYNAMIC_OBJECT 		_id
#define COT_DYNAMIC_OBJECT				1
#define COT_STATIC_OBJECT				2

/* Data type of the base object class. */
#define COT_CLASS_OBJECT 				COTObject

/* All classes and interfaces contain a pointer to their highest */
/* super class, the base object, this is the name of that pointer. */
#define COT_CLASS_OBJECT_NAME			_co

/* An anonymous struct inside the class is used to help hide the virtual table. */
/* This is that structs name. */
#define COT_VIRTUAL_TABLE_HIDER_NAME	_vt

/* An anonymous struct inside the class is used to help hide the override table. */
/* This is that structs name. */
#define COT_OVERRIDE_TABLE_HIDER_NAME	_ot

/* If a class inherits, it will contain an instance of the class it */
/* is inheriting from. This is the name of that instance. */
#define COT_SUPER_NAME 					_sp

/* When a class implementings an interface, it contains an */
/* instance of the interface. This is prefixed / posfixed to the data type */
/* of the interface and used as the variable name. */
#define COT_INTERFACE_PREFIX 			_if
#define COT_INTERFACE_POSIFX
#define COT_TO_IFACE_VAR_NAME( i ) \
	COT_INTERFACE_PREFIX##i##COT_INTERFACE_POSFIX

/* Interfaces contain a pointer offset from the class implemeting them. */
/* This is the name of the variable used to save the offset. */
#define COT_INTERFACE_OFFSET_NAME 		_io

/* Name used to reference the object within class methods. This variable */
/* is 'self' in python and 'this' in java / C++. Note, making this variable */
/* 'this' will prevent compatibility with C++ code. */
#define COT_OBJECT_REFERENCE	 		self

/* Used as an intermediate variable name while casting to the */
/* COT_OBJECT_REFERENCE_NAME. */
#define COT_OBJECT_PRE_REFERENCE_NAME	self_

/* Used at the beginning of all functions to pass in the object. */
#define self( C )					C* COT_OBJECT_PRE_REFERENCE_NAME


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
typedef struct COT_CLASS_OBJECT COT_CLASS_OBJECT;
struct COT_CLASS_OBJECT
{
	struct
	{
		void (*destroy)( COT_CLASS_OBJECT* );
	} COT_VIRTUAL_TABLE_HIDER_NAME;
	char COT_IS_COT_DYNAMIC_OBJECT;
};
extern void COTCreateObject( COT_CLASS_OBJECT* );


/******************************************************************************/
/* Used to create and destroy objects. */
/******************************************************************************/
#define COTCreateNew( type, objectP, constructor )											\
	do {																					\
		type* object = COTMalloc( sizeof(type) );											\
		if( (object) != NULL ){ 															\
			((COT_CLASS_OBJECT*) (object) )->COT_IS_COT_DYNAMIC_OBJECT = COT_DYNAMIC_OBJECT;\
			COTCreateObject( (COT_CLASS_OBJECT*) (object) );								\
			(objectP) = object;																\
			constructor;																	\
		} else {																			\
			(objectP) = NULL;																\
		}																					\
	} while( 0 )

#define COTCreate( object, constructor )												\
	do {																				\
		COT_CLASS_OBJECT* mem = (COT_CLASS_OBJECT*) (object);							\
		((COT_CLASS_OBJECT*) (mem))->COT_IS_COT_DYNAMIC_OBJECT = COT_STATIC_OBJECT;		\
		COTCreateObject( (COT_CLASS_OBJECT*) (mem) );									\
		constructor;																	\
	} while( 0 )

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


/******************************************************************************/
/* Class Declaration */
/******************************************************************************/
/* The two macros below select one of two possible class declaration. */
#define COT_CLASS_DECLARE_SELECTION( _1, _2, SELECTION, ... ) SELECTION
#define COTClass( ... ) \
	COT_CLASS_DECLARE_SELECTION( __VA_ARGS__, COT_CLASS_EXTENDS_SELECT, COT_CLASS_EXTENDS_OBJECT)( __VA_ARGS__ )

/* Start a class declaration with manually selected inheritance. */
#define COT_CLASS_EXTENDS_SELECT( D, S )									\
	typedef struct D D;														\
	struct D																\
	{																		\
		S COT_SUPER_NAME;

/* Start a class declaration with automatic inheritance, ie, the base object. */
#define COT_CLASS_EXTENDS_OBJECT( D )										\
	typedef struct D D;														\
	struct D																\
	{																		\
		COT_CLASS_OBJECT COT_SUPER_NAME;

/* Declare all virtual methods. */
#define COTVirtual( ... )													\
		struct																\
		{																	\
			__VA_ARGS__														\
		} COT_VIRTUAL_TABLE_HIDER_NAME;

/* Used to override super class / interface methods. */
#define COTOverride( ... )													\
		struct																\
		{																	\
			__VA_ARGS__														\
		} COT_OVERRIDE_TABLE_HIDER_NAME;
/* Used to override destructor. */
#define COTDestructor( ) \
			void (*destroy)( self(COT_CLASS_OBJECT) )

/* End the definition of a class. */
#define COTClassEnd															\
		COT_CLASS_OBJECT* COT_CLASS_OBJECT_NAME;							\
	};


/******************************************************************************/
/* Interface Declaration */
/******************************************************************************/
/* Open a interface declaration. */
#define COTInterface(T) 	\
	typedef struct T T;		\
	struct T				\
	{

/* Close a interface declaration. */
#define COTInterfaceEnd												\
		void* COT_INTERFACE_OFFSET_NAME;							\
		COT_CLASS_OBJECT* COT_CLASS_OBJECT_NAME;					\
	};


/******************************************************************************/
/* Use a interface within a class */
/******************************************************************************/
/* Adds a interface to a class declaration, used after opening a class */
#define COTImplements( iface )	\
	iface COT_TO_IFACE_VAR_NAME( iface );

/* Bind the interface data at run time. Use in constructor */
#define COTCreateInterface(t) \
	COT_OBJECT_REFERENCE->COT_TO_IFACE_VAR_NAME( t ).COT_INTERFACE_OFFSET_NAME = \
	(void *) (((char *) &(COT_OBJECT_REFERENCE->COT_TO_IFACE_VAR_NAME( t ))) - (char *) COT_OBJECT_REFERENCE); \
	COT_OBJECT_REFERENCE->COT_TO_IFACE_VAR_NAME( t ).COT_CLASS_OBJECT_NAME = (COT_CLASS_OBJECT*) COT_OBJECT_REFERENCE


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
	( (class*) COT_OBJECT_REFERENCE)->COT_TO_IFACE_VAR_NAME( iface ).COT_VIRTUAL_TABLE_HIDER_NAME.method = method

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

#define COTConstructorOf( C )														\
	if( COT_OBJECT_PRE_REFERENCE_NAME == 0 ){ return; }								\
	C* COT_OBJECT_REFERENCE = (C*) COT_OBJECT_PRE_REFERENCE_NAME;						\
	COT_OBJECT_REFERENCE->COT_CLASS_OBJECT_NAME = (COT_CLASS_OBJECT*) COT_OBJECT_REFERENCE

#define COTInterfaceOf(C) 															\
	COT_ASSERT( COT_OBJECT_PRE_REFERENCE_NAME ); 										\
	C *COT_OBJECT_REFERENCE = (C *) ((char *)COT_OBJECT_PRE_REFERENCE_NAME - 				\
						(char *)COT_OBJECT_PRE_REFERENCE_NAME->COT_INTERFACE_OFFSET_NAME); 	\

#define COTVirtualDestructor( )\
	static void destroy( self(COTObject) )
#define COTDestructorOf( C )\
	COTMemberOf(C)

/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define COTCast(i,O) \
	(&(O)->COT_TO_IFACE_VAR_NAME( i ))

#endif /* CLASS_H_ */
