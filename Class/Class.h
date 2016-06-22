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

/****************************************************************************/
/* Configuration options													*/
/****************************************************************************/
/*
 * Define this to reduce the memory footprint used in .bss
 * for error messages when an assert fails. Error messages will be much smaller,
 * but less descriptive.
 * 	2:
 * 		Error message prints line, file, and description of error,
 * 		then calls assert hook.
 * 	1:
 * 		Error message prints line and file of error, then calls assert
 * 		failure hook.
 * 	0:
 * 		No error message, only calls assert failure hook.
 *
 * Note, the symbol DEBUG must be defined for run time checks to be enabled.
 * If DEBUG is not defined then asserts resolve to empty statements and the
 * assert failure hook is never called on failed asserts.
 */
#define C_DEBUG_DIAG_LEVEL	2

/* Default memory clean up method used. */
/* Calling CDynamic( ) on an object will invoke this free method */
/* being called after destruction. */
/* Note, this must resolve to a method with an address in memory. */
/* ie, the default free method cannot be a macro function. */
#define CDefaultFree 			free

/* All classes and interfaces contain a pointer to their highest */
/* super class, the base object, this is the name of that pointer. */
#define C_ROOT					_rt

/* These define how to print formatted strings and what to */
/* do when an assertion fails. */
#include <stdio.h>
#define C_PRINT( ... ) 				printf( __VA_ARGS__ )
#define C_FAILED_ASSERT_HANDLE( ) 	for( ;; )

/* Used to zero out a structure. */
/* This assumes that NULL resolves to 0, which is requried by C standard. */
/* If your C library doesn't have memset, you will have to write your own, */
/* or opt not use it; the debugging features won't work without it. */
#if defined( DEBUG )
#include <string.h>
#define C_INIT_OBJECT( object, size )					\
	do {												\
		memset( (object), 0, (size) );					\
	} while( 0 )
#else
#define C_INIT_OBJECT( object, size )					\
	do {												\
		(void) (object);								\
		(void) (size);									\
	} while( 0 )
#endif


/****************************************************************************/
/* Assert Messages															*/
/****************************************************************************/
/* Different reasons for asserting. */
#if C_DEBUG_DIAG_LEVEL == 2

#define C_ASSERT_VIRTUAL_MESSAGE \
	"Virtual method not linked. Possible causes:\n"\
	"\t* [A0] Class constructor did not link function pointer for the method\n"\
	"\t* [A1] Constructor was never called on object\n"\
	"\t* [A2] Constructor was called, but super's constructor was not called\n"

#define C_ASSERT_SUPER_METHOD_MESSAGE \
	"Super method not linked. Possible causes:\n"\
	"\t* [B0] Did not call super class constructor.\n"\
	"\t* [B1] Did not correctly keep reference to super's implementation of method\n"

#define C_ASSERT_OBJECT_MESSAGE \
	"NULL pointer used as input\n"

#define C_ASSERT_CAST_MESSAGE \
	"Failure to cast object. Possible causes:\n"\
	"\t* [C0] In an interface's method, the constructor did not call\n"\
	"\t  CInterface( ) to construct the interface.\n"\
	"\t* [C1] Did not call super's constructor.\n"

extern const char* CAssertVirtualMessage_;
extern const char* CAssertSuperMethodMessage_;
extern const char* CAssertObjectMessage_;
extern const char* CAssertCastMessage_;

#else

#define CAssertVirtualMessage_ 		NULL
#define CAssertSuperMethodMessage_ 	NULL
#define CAssertObjectMessage_ 		NULL
#define CAssertCastMessage_ 		NULL

#endif


/****************************************************************************/
/* Assert macros															*/
/****************************************************************************/
#if defined( DEBUG )
extern void CAssert( char exp, char const* msg, char const* file, int line );
#else
#define CAssert( exp, msg, file, line ) \
	do {								\
		(void) (exp);					\
		(void) (file);					\
		(void) (line);					\
	} while( 0 )
#endif


#define C_ASSERT_VIRTUAL( method )\
	CAssert( ((method)==NULL), CAssertVirtualMessage_, __FILE__, __LINE__ )
#define C_ASSERT_SUPER_METHOD( method )\
	CAssert( ((method)==NULL), CAssertSuperMethodMessage_, __FILE__, __LINE__ )
#define C_ASSERT_OBJECT( object )\
	CAssert( ((object)==NULL), CAssertObjectMessage_, __FILE__, __LINE__ )
#define C_ASSERT_CAST( object, file, line )\
	CAssert( (object) == NULL, CAssertCastMessage_, file, line )

/****************************************************************************/
/* Base object and interface structures										*/
/****************************************************************************/
typedef void (*CFreeType)( void* );
struct CObject
{
	void* C_ROOT; /* MUST be first variable in this struct. */
	void (*CDestructor)( struct CObject* );
	CFreeType CObject_Free;
};
extern struct CObject* CObject_Constructor( struct CObject*, size_t );
extern void CObject_Destroy( struct CObject* );
extern void CObject_SetFree( struct CObject*, CFreeType );

/* Help macro for object construction. Macro has side effects. */
#define CObject( self )	\
	CObject_Constructor(self, sizeof(*self))

/* Helper macro for object destruction. */
#define CDestroy( mem )	\
	CObject_Destroy( ((struct CObject*) (mem))->C_ROOT )

/* Helper macro for declaring object dynamic. */
#define CDynamic( obj ) \
	CObject_SetFree((struct CObject*) (obj), CDefaultFree)

/* Helper macro for declaring free method for object. */
#define CFreeWith( obj, freep ) \
	CObject_SetFree((struct CObject*) (obj), (freep))

/* Must be put at beginning of an interface. */
struct CInterface
{
	void* C_ROOT;
};

/* Interface constructor. */
#define CInterface( self, iface )									\
	do {															\
		((struct CInterface*) (iface))->C_ROOT = self;				\
	} while( 0 )


/****************************************************************************/
/* Helper macros for asserting and defining class methods					*/
/****************************************************************************/
/* Assert a super class method before calling it. */
#define CAssertSuper( method ) 						\
	C_ASSERT_SUPER_METHOD( method ); 				\

/* Asserts virtual method before calling it. */
#define CAssertVirtual( func )				\
	C_ASSERT_VIRTUAL( func );

/* Helper macro for asserting pointers. */
#define CAssertObject( object ) 					\
	C_ASSERT_OBJECT( (object) )

/* Cast object pointer to desired class. */
struct CRoot{ void* C_ROOT; };
extern void* CObjectCast_( void*, const char*, int );
#define CCast( self_ )\
	CObjectCast_( self_, __FILE__, __LINE__ )


#endif /* CLASS_H_ */
