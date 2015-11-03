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

#include "ClassConfig.h"
#include <stdlib.h>

/* Name of the base object class. */
#define CLASS_OBJECT 				Object

/* Every class contains a pointer to a CLASS_OBJECT data type. */
/* This is the name of the pointer. */
#define CLASS_OBJECT_GLOBAL			_og

/* Every class contains an instance of a CLASS_OBJECT data type. */
/* This is the name of the variable. */
#define CLASS_OBJECT_LOCAL			_ol

/* Every class has a unique virtual table data type. The data type's name is */
/* the class name posfixed /prefixed with this name. */
#define VIRTUAL_TABLE_NAME_POSFIX	VirtualTable
#define VIRTUAL_TABLE_NAME_PREFIX
#define TO_VTABLE_TYPE_NAME( class ) \
	VIRTUAL_TABLE_NAME_POSFIX##class##VIRTUAL_TABLE_NAME_PREFIX

/* An anonymous struct inside the class is used to help hide the virtual table. */
/* This is that structs name. */
#define VIRTUAL_TABLE_HIDER_NAME	_

/* Each class contains a pointer to their virtual table. This is */
/* the pointer's name. */
#define CLASS_VIRTUAL_TABLE_NAME	_ct

/* Each class contains an instance of their virtual table. This is */
/* the instance's name. */
#define OBJECT_VIRTUAL_TABLE_NAME	_ot

/* If a class inherits, it will contain an instance of the class it */
/* is inheriting from. This is the name of that instance. */
#define SUPER_NAME 					_sp/* Name of the base object class. */

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

/* All objects of a class share a virtual table. The virtual table is */
/* is declared as a static variable in the class source file. This is */
/* the name of that variable. */
#define VIRTUAL_TABLE_DEFINE_NAME	_ClassVirtualTable

/* Name used to reference the object within class methods. This variable */
/* is 'self' in python and 'this' in java / C++. Note, making this varaible */
/* 'this' will prevent compatibility with C++ code. */
#define OBJECT_REFERENCE_NAME 		self

/* Used as an intermediate variable name while casting to the */
/* OBJECT_REFERENCE_NAME. */
#define OBJECT_PRE_REFERENCE_NAME	self_

/****************************************************************************/
/* Memory Management 														*/
/****************************************************************************/
static inline void* OOMalloc( size_t size )
{
	return malloc( size );
}
static inline void OOFree( void* mem )
{
	free( mem );
}


/******************************************************************************/
/* Class Declaration */
/******************************************************************************/
/* Start the definition of a class. */
#define CLASS(D)															\
	typedef struct D D;														\
	typedef struct TO_VTABLE_TYPE_NAME( D ) TO_VTABLE_TYPE_NAME( D );		\
	struct D																\
	{

/* Optionally inherit after the Class() declaration. */					
#define EXTENDS(S) \
		S SUPER_NAME;

/* Declare all virtual methods. */
#define VIRTUAL( D, ... )													\
		struct																\
		{																	\
			struct TO_VTABLE_TYPE_NAME( D )									\
			{																\
				__VA_ARGS__													\
			} const *CLASS_VIRTUAL_TABLE_NAME;								\
			TO_VTABLE_TYPE_NAME( D ) OBJECT_VIRTUAL_TABLE_NAME;				\
		} VIRTUAL_TABLE_HIDER_NAME;

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
#define END_INTERFACE 														\
		struct																\
		{																	\
			void* INTERFACE_OFFSET_NAME;									\
			CLASS_OBJECT* CLASS_OBJECT_NAME;								\
		} INTERFACE_META_DATA_NAME;											\
	}


/******************************************************************************/
/* Use a interface within a class */
/******************************************************************************/
/* Adds a interface to a class declaration, used after opening a class */
#define IMPLEMENTS( iface )	\
	iface TO_IFACE_VAR_NAME( iface );


/******************************************************************************/
/* Put a class' virtual table into memory */
/******************************************************************************/
/* Used to put a classes virtual table into memory. */
#define CLASS_VIRTUAL_TABLE( C, ... )										\
		static TO_VTABLE_TYPE_NAME( C ) VIRTUAL_TABLE_DEFINE_NAME = 		\
		{ __VA_ARGS__ };


/******************************************************************************/
/* Used to override methods in super class. */
/******************************************************************************/
#define OVERRIDE_VIRTUAL_METHOD( class, method )							\
	(class)->VIRTUAL_TABLE_HIDER_NAME.OBJECT_VIRTUAL_TABLE_NAME.method = method

#define OVERRIDE_INTERFACE_METHOD( iface, class, method )					\
	(class)->TO_IFACE_VAR_NAME( iface ).OBJECT_VIRTUAL_TABLE_NAME.method = method

/******************************************************************************/
/* Used to access super class' implementation of a method. */
/******************************************************************************/
#define SUPER_CLASS \
	OBJECT_REFERENCE_NAME->SUPER_NAME.VIRTUAL_TABLE_HIDER_NAME.CLASS_VIRTUAL_TABLE_NAME

#define SUPER_INTERFACE( iface ) \
	(&(OBJECT_REFERENCE_NAME->SUPER_NAME.TO_IFACE_VAR_NAME( iface ).CLASS_VIRTUAL_TABLE_NAME))


/******************************************************************************/
/* Used to implement virtual methods and interface methods. */
/******************************************************************************/
#define VIRTUAL_METHOD( ret, name, arg )									\
	ret name arg															\
	{																		\
		objASSERT( OBJECT_PRE_REFERENCE_NAME );								\
		objASSERT( OBJECT_PRE_REFERENCE_NAME->name );						\
		return OBJECT_PRE_REFERENCE->name( OBJECT_PRE_REFERENCE, arg );		\
	}																		\
	static ret name arg														\

/******************************************************************************/
/* Link class methods to an object an construction time */
/******************************************************************************/
/* Link a virtual method on a class by class basis. */
#define LinkMethod(M)		/* Assign function to pointer. */	\
				OBJ_REFERENCE-> M = & M
#define LinkMethodConflictingNames( MP, MD ) \
				OBJ_REFERENCE-> MP = & MD

/* Override a virtual method on a class by class basis. */
#define HardOverrideMethod(S,M)	/* Reassign function to a pointer */	\
		/* in super class. */			\
		((S *) OBJ_REFERENCE)-> M = & M
#define HardOverrideProtectedMethod(S,M) \
		((S*) OBJ_REFERENCE)->PROTECTED_STRUCT_NAME. M = & M
#define HardOverrideMethodConflictingNames(S,MP,MD) \
		((S*) OBJ_REFERENCE)-> MP = & MD
#define HardOverrideProtectedMethodConflictingNames(S,MP,MD) \
		((S*) OBJ_REFERENCE)->PROTECTED_STRUCT_NAME. MP = & MD

#define SoftOverrideMethod(S,M) \
  do {										\
    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = ((S*) OBJ_REFERENCE)-> M; 	\
    HardOverrideMethod(S,M);							\
  } while( 0 )
#define SoftOverrideProtectedMethod(S,M) \
  do {										\
    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = ((S*) OBJ_REFERENCE)->PROTECTED_STRUCT_NAME. M; 	\
    HardOverrideProtectedMethod(S,M);							\
  } while( 0 )
#define SoftOverrideMethodConflictingNames(S,MP,MD) \
		do {										\
		    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> MP = ((S*) OBJ_REFERENCE)-> MP; 	\
		    HardOverrideMethodConflictingNames(S,MP,MD);							\
		  } while( 0 )
#define SoftOverrideProtectedMethodConflictingNames(S,MP,MD) \
		do {										\
		    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> MP = ((S*) OBJ_REFERENCE)->PROTECTED_STRUCT_NAME. MP; 	\
		    HardOverrideProtectedMethodConflictingNames(S,MP,MD);							\
		  } while( 0 )

/******************************************************************************/
/* Link interfaces to an object at construction time */
/******************************************************************************/
/* Used to call an objects destructor when only a refrence */
/* to its interface exists. */
extern void destroyInterface( self( BASE_TRAIT ) );

/* Link a interface to a class, called in constructor. */
#define LinkInterface(t) \
	OBJ_REFERENCE->TRAIT_PREFIX##t.DESTRUCTOR_NAME = destroyInterface; \
	OBJ_REFERENCE->TRAIT_PREFIX##t.TRAIT_OFFSET = \
	(void *) (((unsigned char *) &(OBJ_REFERENCE->TRAIT_PREFIX##t)) - (unsigned char *) OBJ_REFERENCE)

/* Link a interface method to a class. */
#define LinkInterfaceMethod(t,M) \
  OBJ_REFERENCE->TRAIT_PREFIX##t. M = & M
#define LinkInterfaceMethodConflictingNames(t,MP,MD) \
	OBJ_REFERENCE->TRAIT_PREFIX##t. MP = & MD

/* Override a interface method defined in a super class. */
#define HardOverrideInterfaceMethod(S,t,M) \
  ((S *) OBJ_REFERENCE)->TRAIT_PREFIX##t. M = & M
#define HardOverrideInterfaceMethodConflictingNames(S,t,MP,MD) \
	((S *) OBJ_REFERENCE)->TRAIT_PREFIX##t. MP = & MD

/* Override a interface method in immediate super class, but retain reference to */
/* original implementation so that it can be called in the overrode method. */
#define SoftOverrideInterfaceMethod(S,t,M) \
  do {												\
    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = ((S*) OBJ_REFERENCE)->TRAIT_PREFIX##t. M; 	\
    HardOverrideInterfaceMethod(S,t,M);									\
  } while( 0 )
#define SoftOverrideInterfaceMethodConflictingNames(S,t,MP,MD) \
		do {												\
			OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> MP = ((S*) OBJ_REFERENCE)->TRAIT_PREFIX##t. MP; 	\
			HardOverrideInterfaceMethodConflictingNames(S,t,MP,MD);									\
		} while( 0 )


/******************************************************************************/
/* Bind a class' implementation to the class implementing the method */
/******************************************************************************/
/* Used to register a function with a class, on a function by function basis. */
#define MemberOf( C ) \
	C *OBJ_REFERENCE = (C *) PRE_OBJ_REFERENCE; \
	objASSERT( OBJ_REFERENCE );


/******************************************************************************/
/* Bind a interface's method implementation to the class using it */
/******************************************************************************/
/* Cast a pointer to a interface into the class it is a part of. */
/* Must only be called inside of interface method definitions. */
#define InterfaceOf(C) \
	objASSERT( PRE_OBJ_REFERENCE ); \
	C *OBJ_REFERENCE = (C *) ((unsigned char *)PRE_OBJ_REFERENCE - (unsigned char *)PRE_OBJ_REFERENCE->TRAIT_OFFSET); \
	objASSERT( OBJ_REFERENCE )


/******************************************************************************/
/* Access super classes methods which are softly overrode. */
/******************************************************************************/
#define super( ) \
  (&(OBJ_REFERENCE->RECURSIVE_STRUCT_NAME))


/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define interface(i,O) \
	(&(O)->INTERFACE_PREFIX##i)

#endif /* CLASS_H_ */
