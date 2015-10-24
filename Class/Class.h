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

#define DESTRUCTOR_NAME destroy

#define SUPER_NAME _s
#define BASE_OBJECT_REFERENCE _
#define RECURSIVE_STRUCT_NAME _r
#define PRIVATE_STRUCT_NAME _p0
#define PROTECTED_STRUCT_NAME _p1

#define TRAIT_PREFIX _interface
#define TRAIT_OFFSET _


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
/* Start the declaration of a class. */
#define Class(D) \
	typedef struct D D;					\
	struct D							\
	{
/* Optionally inherit after the Class() declaration. */					
#define Extends(S) \
		S SUPER_NAME;
/* Declare private member data/methods. */
#define Private( ... ) \
		struct							\
		{								\
			__VA_ARGS__					\
		} PRIVATE_STRUCT_NAME;
/* Declare protected member data/methods. */
#define Protected( ... ) \
		struct			     			\
		{								\
			__VA_ARGS__					\
		} PROTECTED_STRUCT_NAME;
/* Declare public member data/methods. */
#define Public( ... ) \
		__VA_ARGS__
/* Optionally declare methods in super */
/* class which will be overrode and then */
/* referenced in the overrode method. */
#define SoftOverride( ... ) \
		struct							\
		{								\
			__VA_ARGS__					\
		} RECURSIVE_STRUCT_NAME;
/* End the declaration of a class. */
#define EndClass \
		void* BASE_OBJECT_REFERENCE;	\
	}


/******************************************************************************/
/* Interface Declaration */
/******************************************************************************/
typedef struct BASE_TRAIT BASE_TRAIT;
struct BASE_TRAIT
{
	void* TRAIT_OFFSET;
};

/* Open a interface declaration. */
#define Interface(T) \
	typedef struct T T;		\
	struct T				\
	{						\
		void* TRAIT_OFFSET; /* MUST be first variable in a interface. */
/* Close a interface declaration. */
#define EndInterface \
		void (*DESTRUCTOR_NAME)( self( BASE_TRAIT ) ); \
	}


/******************************************************************************/
/* Use a interface within a class */
/******************************************************************************/
/* Adds a interface to a class declaration, used after opening a class declaration and any inheritance. */
#define Uses(t)	\
  t TRAIT_PREFIX##t;


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
/* Accessors to public and protected data. 									  */
/******************************************************************************/
#define private( ) \
	OBJ_REFERENCE->PRIVATE_STRUCT_NAME
#define protected( C ) \
	((C*) OBJ_REFERENCE)->PROTECTED_STRUCT_NAME


/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define interface(t,O) \
	(&(O)->TRAIT_PREFIX##t)


/****************************************************************************/
/* Destructor for all objects												*/
/****************************************************************************/


/* Simple macro to do forward declaration. */
#define Forward(C)		typedef struct C C

#endif /* CLASS_H_ */
