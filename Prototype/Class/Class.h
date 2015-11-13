/* Class header
 * Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 *
 *  Created on: 2014-11-19
 *      Author: Brendan Bruner
 */

#ifndef CLASS_H_
#define CLASS_H_		

#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>
#define objASSERT( O )	do{										\
				   if( (O) == 0 ) { 								\
				   	printf("NULL pointer exception:\nfile %s\nline %d\n", 			\
						(char *) __FILE__, __LINE__ ); 					\
					for( ;; );	}							\
				} while( 0 )

/* Name of a variable indicating allocation scheme. */
#define IS_DYNAMIC_OBJECT 			_id
#define DYNAMIC_OBJECT				1
#define STATIC_OBJECT				2

/* Data type of the base object class. */
#define CLASS_OBJECT 				Object_t

/* All classes and interfaces contain a pointer to their highest */
/* super class, the base object, this is the name of that pointer. */
#define CLASS_OBJECT_NAME			_co

/* An anonymous struct inside the class is used to help hide the virtual table. */
/* This is that structs name. */
#define VIRTUAL_TABLE_HIDER_NAME	_vt

/* An anonymous struct inside the class is used to help hide the override table. */
/* This is that structs name. */
#define OVERRIDE_TABLE_HIDER_NAME	_ot

/* If a class inherits, it will contain an instance of the class it */
/* is inheriting from. This is the name of that instance. */
#define SUPER_NAME 					_sp

/* When a class implementings an interface, it contains an */
/* instance of the interface. This is prefixed / posfixed to the data type */
/* of the interface and used as the variable name. */
#define INTERFACE_PREFIX 			_if
#define INTERFACE_POSIFX
#define TO_IFACE_VAR_NAME( i ) \
	INTERFACE_PREFIX##i##INTERFACE_POSFIX

/* Interfaces contain a pointer offset from the class implemeting them. */
/* This is the name of the variable used to save the offset. */
#define INTERFACE_OFFSET_NAME 		_io

/* In an effort to help hide data, all system variables of an interface */
/* are put inside an anonymous struct with this name. */
#define INTERFACE_META_DATA_NAME	_im

/* Name used to reference the object within class methods. This variable */
/* is 'self' in python and 'this' in java / C++. Note, making this variable */
/* 'this' will prevent compatibility with C++ code. */
#define OBJECT_REFERENCE	 		self

/* Used as an intermediate variable name while casting to the */
/* OBJECT_REFERENCE_NAME. */
#define OBJECT_PRE_REFERENCE_NAME	self_

/* Used at the beginning of all functions to pass in the object. */
#define self( C )					C* OBJECT_PRE_REFERENCE_NAME


/****************************************************************************/
/* Memory Management 														*/
/****************************************************************************/
typedef void* (*OOMallocType)( size_t );
typedef void (*OOFreeType)( void* );
static OOMallocType OOMalloc = malloc;
static OOFreeType OOFree = free;
static inline void suppressOOFreeWarning( ){ (void) OOFree( NULL ); }


/****************************************************************************/
/* Base object																*/
/****************************************************************************/
typedef struct CLASS_OBJECT CLASS_OBJECT;
struct CLASS_OBJECT
{
	struct
	{
		void (*virtualDestroy)( CLASS_OBJECT* );
	} VIRTUAL_TABLE_HIDER_NAME;
	char IS_DYNAMIC_OBJECT;
};
extern void OOCreateObject( CLASS_OBJECT* );


/******************************************************************************/
/* Used to create and destroy objects. */
/******************************************************************************/
#include <stdio.h>
static void* newObjectMemLocation_;
static inline void* createNewInline( size_t size )
{
	void* object = (void*) OOMalloc( size );
	newObjectMemLocation_ = object;
	return object;
}
static inline void* createInline( void* mem )
{
	newObjectMemLocation_ = mem;
	return mem;
}

#define createNew( class, constructor )													\
	createNewInline( sizeof( class ) );													\
	if( newObjectMemLocation_ != NULL ){ 												\
		((CLASS_OBJECT*) newObjectMemLocation_)->IS_DYNAMIC_OBJECT = DYNAMIC_OBJECT; 	\
	}																					\
	OOCreateObject( (CLASS_OBJECT*) newObjectMemLocation_ );							\
	constructor


#define create( class, constructor, mem )										\
	createInline( &mem );														\
	((CLASS_OBJECT*) &mem)->IS_DYNAMIC_OBJECT = STATIC_OBJECT;					\
	createObject( (CLASS_OBJECT*) &mem );										\
	constructor

#define destroy( mem )																	\
	do {																				\
	objASSERT( mem );																	\
	CLASS_OBJECT* object = mem->CLASS_OBJECT_NAME;										\
	objASSERT( object->VIRTUAL_TABLE_HIDER_NAME.virtualDestroy );						\
	object->VIRTUAL_TABLE_HIDER_NAME. virtualDestroy( object );							\
	if( object->IS_DYNAMIC_OBJECT == DYNAMIC_OBJECT ){									\
		OOFree( (void*) object );														\
		printf( "delete dynamic\n" );\
	}																					\
	} while( 0 )


/******************************************************************************/
/* Class Declaration */
/******************************************************************************/
/* The two macros below select one of two possible class declaration. */
#define CLASS_DECLARE_SELECTION( _1, _2, SELECTION, ... ) SELECTION
#define CLASS( ... ) \
	CLASS_DECLARE_SELECTION( __VA_ARGS__, CLASS_EXTENDS_SELECT, CLASS_EXTENDS_OBJECT)( __VA_ARGS__ )

/* Start a class declaration with manually selected inheritance. */
#define CLASS_EXTENDS_SELECT( D, S )										\
	typedef struct D D;														\
	struct D																\
	{																		\
		S SUPER_NAME;

/* Start a class declaration with automatic inheritance, ie, the base object. */
#define CLASS_EXTENDS_OBJECT( D )											\
	typedef struct D D;														\
	struct D																\
	{																		\
		CLASS_OBJECT SUPER_NAME;

/* Declare all virtual methods. */
#define VIRTUAL( ... )														\
		struct																\
		{																	\
			__VA_ARGS__														\
		} VIRTUAL_TABLE_HIDER_NAME;

/* Used to override super class / interface methods. */
#define OVERRIDE( ... )														\
		struct																\
		{																	\
			__VA_ARGS__														\
		} OVERRIDE_TABLE_HIDER_NAME;

/* End the definition of a class. */
#define END_CLASS															\
		CLASS_OBJECT* CLASS_OBJECT_NAME;									\
	};


/******************************************************************************/
/* Interface Declaration */
/******************************************************************************/
/* Open a interface declaration. */
#define INTERFACE(T) 		\
	typedef struct T T;		\
	struct T				\
	{

/* Close a interface declaration. */
#define END_INTERFACE 														\															\
		void* INTERFACE_OFFSET_NAME;										\									\
		CLASS_OBJECT* CLASS_OBJECT_NAME;									\
	}


/******************************************************************************/
/* Use a interface within a class */
/******************************************************************************/
/* Adds a interface to a class declaration, used after opening a class */
#define IMPLEMENTS( iface )	\
	iface TO_IFACE_VAR_NAME( iface );

/* Bind the interface data at run time. Use in constructor */
#define CREATE_INTERFACE(t) \
	OBJECT_REFERENCE->TO_IFACE_VAR_NAME( t ).INTERFACE_OFFSET_NAME = \
	(void *) (((char *) &(OBJECT_REFERENCE->TO_IFACE_VAR_NAME( t ))) - (char *) OBJECT_REFERENCE); \
	OBJECT_REFERENCE->TO_IFACE_VAR_NAME( t ).CLASS_OBJECT_NAME = (CLASS_OBJECT*) OBJECT_REFERENCE


/******************************************************************************/
/* Used to dynamically link methods at run time. */
/******************************************************************************/
#define LINK_VIRTUAL_METHOD( method ) \
	OBJECT_REFERENCE->VIRTUAL_TABLE_HIDER_NAME. method = method

#define LINK_INTERFACE_METHOD( iface, method ) \
	OBJECT_REFERENCE->TO_IFACE_VAR_NAME( iface ).VIRTUAL_TABLE_HIDER_NAME. method = method

/******************************************************************************/
/* Used to override methods in super class / interface. */
/******************************************************************************/
#define OVERRIDE_VIRTUAL_METHOD( class, method )							\
	OBJECT_REFERENCE->OVERRIDE_TABLE_HIDER_NAME. method = (class* OBJECT_REFERENCE)->VIRTUAL_TABLE_HIDER_NAME. method; \
	(class* OBJECT_REFERENCE)->VIRTUAL_TABLE_HIDER_NAME. method = method

#define OVERRIDE_INTERFACE_METHOD( class, iface, method )					\
	OBJECT_REFERENCE->OVERRIDE_TABLE_HIDER_NAME. method = (class* OBJECT_REFERENCE)->TO_IFACE_VAR_NAME( iface ).VIRTUAL_TABLE_HIDER_NAME. method; \
	(class* OBJECT_REFERENCE)->TO_IFACE_VAR_NAME( iface ).VIRTUAL_TABLE_HIDER_NAME.method = method


/******************************************************************************/
/* Used to access super class' implementation of a method. */
/******************************************************************************/
#define SUPER( ) \
	(&(OBJECT_REFERENCE->OVERRIDE_TABLE_HIDER_NAME))


/******************************************************************************/
/* Used to implement virtual methods and interface methods. */
/******************************************************************************/
#define VIRTUAL_METHOD( C, name )												\
	objASSERT( OBJECT_PRE_REFERENCE_NAME );										\
	objASSERT( OBJECT_PRE_REFERENCE_NAME->VIRTUAL_TABLE_HIDER_NAME. name ); 	\
	C* OBJECT_REFERENCE = (C*) OBJECT_PRE_REFERENCE_NAME;						\
	return OBJECT_PRE_REFERENCE_NAME->VIRTUAL_TABLE_HIDER_NAME. name

#define MEMBER_OF( C )															\
	objASSERT( OBJECT_PRE_REFERENCE_NAME );										\
	C* OBJECT_REFERENCE = (C*) OBJECT_PRE_REFERENCE_NAME

#define CONSTRUCTOR_OF( C )														\
	if( OBJECT_PRE_REFERENCE == 0 ){ return 0; }								\
	C* OBJECT_REFERENCE = (C*) OBJECT_PRE_REFERENCE_NAME;						\
	OBJECT_REFERENCE->CLASS_OBJECT_NAME = (CLASS_OBJECT*) OBJECT_REFERENCE

#define INTERFACE_OF(C) 															\
	objASSERT( OBJECT_PRE_REFERENCE_NAME ); 										\
	C *OBJECT_REFERENCE = (C *) ((char *)OBJECT_PRE_REFERENCE_NAME - 				\
						(char *)OBJECT_PRE_REFERENCE_NAME->INTERFACE_OFFSET_NAME); 	\


/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define interface(i,O) \
	(&(O)->INTERFACE_PREFIX##i)

#endif /* CLASS_H_ */
