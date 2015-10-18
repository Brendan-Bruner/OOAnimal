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

#define TRAIT_PREFIX _trait
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
/* Trait Declaration */
/******************************************************************************/
typedef struct BASE_TRAIT BASE_TRAIT;
struct BASE_TRAIT
{
	void* TRAIT_OFFSET;
};

/* Open a trait declaration. */
#define Trait(T) \
	typedef struct T T;		\
	struct T				\
	{						\
		void* TRAIT_OFFSET; /* MUST be first variable in a trait. */
/* Close a trait declaration. */
#define EndTrait \
		void (*DESTRUCTOR_NAME)( self( TraitBase ) ); \
	}


/******************************************************************************/
/* Use a trait within a class */
/******************************************************************************/
/* Adds a trait to a class declaration, used after opening a class declaration and any inheritance. */
#define Uses(t)	\
  t TRAIT_PREFIX##t;


/******************************************************************************/
/* Link class methods to an object an construction time */
/******************************************************************************/
#define LinkDestructor(D) \

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
/* Link traits to an object at construction time */
/******************************************************************************/
/* Link a trait to a class, called in constructor. */
extern void traitBaseDestructor( self( TraitBase ) );
#define LinkTrait(t) \
	OBJ_REFERENCE->TRAIT_PREFIX##t.DESTRUCTOR_NAME = traitBaseDestructor; \
	OBJ_REFERENCE->TRAIT_PREFIX##t.TRAIT_OFFSET = \
	(void *) (((unsigned char *) &(OBJ_REFERENCE->TRAIT_PREFIX##t)) - (unsigned char *) OBJ_REFERENCE)

/* Link a trait method to a class. */
#define LinkTraitMethod(t,M) \
  OBJ_REFERENCE->TRAIT_PREFIX##t. M = & M
#define LinkTraitMethodConflictingNames(t,MP,MD) \
	OBJ_REFERENCE->TRAIT_PREFIX##t. MP = & MD

/* Override a trait method defined in a super class. */
#define HardOverrideTraitMethod(S,t,M) \
  ((S *) OBJ_REFERENCE)->TRAIT_PREFIX##t. M = & M
#define HardOverrideTraitMethodConflictingNames(S,t,MP,MD) \
	((S *) OBJ_REFERENCE)->TRAIT_PREFIX##t. MP = & MD

/* Override a trait method in immediate super class, but retain reference to */
/* original implementation so that it can be called in the overrode method. */
#define SoftOverrideTraitMethod(S,t,M) \
  do {												\
    OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> M = ((S*) OBJ_REFERENCE)->TRAIT_PREFIX##t. M; 	\
    HardOverrideTraitMethod(S,t,M);									\
  } while( 0 )
#define SoftOverrideTraitMethodConflictingNames(S,t,MP,MD) \
		do {												\
			OBJ_REFERENCE->RECURSIVE_STRUCT_NAME-> MP = ((S*) OBJ_REFERENCE)->TRAIT_PREFIX##t. MP; 	\
			HardOverrideTraitMethodConflictingNames(S,t,MP,MD);									\
		} while( 0 )


/******************************************************************************/
/* Bind a class' implementation to the class implementing the method */
/******************************************************************************/
/* Used to register a function with a class, on a function by function basis. */
#define MemberOf( C ) \
  C *OBJ_REFERENCE = (C *) PRE_OBJ_REFERENCE

#define ConstructorOf( C ) \
	C* self;									\
	do {										\
		self = (C*) OOMemMangAlloc( sizeof(C) );\
		if( self == NULL ){ return self; }		\
	} while( 0 )



/******************************************************************************/
/* Bind a trait's method implementation to the class using it */
/******************************************************************************/
/* Cast a pointer to a trait into the class it is a part of. */
/* Must only be called inside of trait method definitions. */
#define TraitOf(C) \
  C *OBJ_REFERENCE = (C *) ((unsigned char *)PRE_OBJ_REFERENCE - (unsigned char *)PRE_OBJ_REFERENCE->TRAIT_OFFSET)


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
/* Call trait methods on an object using the trait */
/******************************************************************************/
#define trait(t,O) \
  (&(O)->TRAIT_PREFIX##t)


/****************************************************************************/
/* Destructor for all objects												*/
/****************************************************************************/
#define kill( O ) \
	((BASE_OBJECT*) (O)->BASE_OBJECT_REFERENCE)->


/* Simple macro to do forward declaration. */
#define Forward(C)		typedef struct C C

#endif /* CLASS_H_ */
