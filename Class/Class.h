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
/* Define this to reduce the memory footprint used in .bss */
/* for error messages. Error messages will be much smaller, */
/* but less descriptive. */
//#define C_MINIMAL_DEBUG

/* The variable name used to reference an object, this is */
/* 'this' in C++/Java and 'self' in Python. */
/* Some helper macros assume the object reference has this name. */
/* In class method definitions. */
#define C_OBJ_REF 				self

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
#define C_PRINT( ... ) printf( __VA_ARGS__ )
#define C_FAILED_ASSERT_HANDLE( ) for( ;; )

/* Used to zero out a structure. */
/* This assumes that NULL resolves to 0, which is requried by C standard. */
/* If your C library doesn't have memset, you will have to write your own, */
/* or opt not use it; however, the debuging features won't work without it. */
#if defined( DEBUG )
#include <string.h>
#define C_INIT_OBJECT( object )							\
	do {												\
		memset( (object), 0, sizeof(*object) );			\
	} while( 0 )
#else
#define C_INIT_OBJECT( object ) (void) object
#endif

/* End of configuration options. */

/****************************************************************************/
/* Assert Messages															*/
/****************************************************************************/
#if defined( DEBUG )
extern void CAssert( char exp, char const* msg, char const* line, int lineNumber );
extern void CAssert2( char exp, char const* msg1, char const* msg2, char const* line, int lineNumber );
#else
#define CAssert( exp, msg, line, lineNumber ) 
#define CAssert2( exp, msg1, msg2, line, lineNumber )
#endif

/* Different reasons for asserting. */
#if defined( C_MINIMAL_DEBUG )
#define C_ASSERT_VIRTUAL_MESSAGE NULL
#else
#define C_ASSERT_VIRTUAL_MESSAGE \
	"Virtual method not linked. Possible causes:\n"\
	"\t* Class constructor did not call CLinkVirtual( ) for the method\n"\
	"\t* If the method is from an interface, class constructor did not\n"\
	"\t  call CLinkInterface( )\n"\
	"\t* Constructor was never called on object\n"\
	"\t* Constructor was called, but CConstructor( ) was not called by\n"\
	"\t  constructor\n"\
	"\t* Constructor was called, but super constructor was not called\n"\
	"\t  For example, say B extends A, and an instance of B was created,\n"\
	"\t  the constructor for B was called, but within B's constructor, the\n"\
	"\t  constructor for A was not called.\n"
#endif
extern const char* CAssertVirtualMessage_;
#define C_ASSERT_VIRTUAL( method, funcName )\
	CAssert2( ((method)==NULL), CAssertVirtualMessage_, funcName, __FILE__, __LINE__ )

#if defined( C_MINIMAL_DEBUG )
#define C_ASSERT_SUPER_METHOD_MESSAGE NULL
#else
#define C_ASSERT_SUPER_METHOD_MESSAGE \
	"Super method not linked: Possible causes:\n"\
	"\t* This failure is hard to get. I have not been able to get it\n"\
	"\t  to fire through normal use. Likely, there is stack stomping at\n"\
	"\t  play. The error is due to a method pointer for overriding a\n"\
	"\t  virtual method being NULL\n"
#endif
extern const char* CAssertSuperMethodMessage_;
#define C_ASSERT_SUPER_METHOD( method, name )\
	CAssert2( ((method)==NULL), CAssertSuperMethodMessage_, name, __FILE__, __LINE__ )

#if defined( C_MINIMAL_DEBUG )
#define C_ASSERT_OBJECT_MESSAGE NULL
#else
#define C_ASSERT_OBJECT_MESSAGE \
	"Attempt to call class method on NULL object\n"
#endif
extern const char* CAssertObjectMessage_;
#define C_ASSERT_OBJECT( object )\
	CAssert( ((object)==NULL), CAssertObjectMessage_, __FILE__, __LINE__ )


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
extern void CObject( struct CObject* );
extern void CObject_Destroy( struct CObject* );
extern void CObject_IsDynamic( struct CObject* );
extern void CObject_SetFree( struct CObject*, CFreeType );

/* Helper macro for object destruction. */
#define CDestroy( mem )	\
	CObject_Destroy( ((struct CObject*) (mem))->C_ROOT )

/* Helper macro for declaring object dynamic. */
#define CDynamic( obj ) \
	CObject_IsDynamic( (struct CObject*) (obj) )

/* Helper macro for declaring free method for object. */
#define CFreeWith( obj, freep ) \
	CObject_SetFree( (struct CObject*) (obj), (freep) )

/* Must be put at beginning of an interface. */
struct CInterface
{
	void* C_ROOT;
};

/****************************************************************************/
/* Constructor specific setup												*/
/****************************************************************************/
#define CConstructor( )							\
	do {										\
		C_ASSERT_OBJECT( C_OBJ_REF );			\
		C_INIT_OBJECT( C_OBJ_REF );				\
		((struct CObject*) C_OBJ_REF)->C_ROOT = C_OBJ_REF;\
	} while( 0 )

/* Bind the interface data at run time. Use in constructor */
#define CInterface( iface )											\
	do {															\
		((struct CInterface*) (iface))->C_ROOT = C_OBJ_REF;	\
	} while( 0 )

/* Helper macro for linking virtual methods. */
#define CLinkVirtual( self, method ) \
	do { (self)-> method = method; } while( 0 )

/* Helper macro for overwriting virtual methods. Unlike overriding, the */
/* reference to the super's method is lost. */
#define COverwriteVirtual( self, method ) \
	do { (self)-> method = method; } while( 0 )

/* Helper macro for overriding virtual methods. Unlike overwriting, a */
/* reference to the super's method is retained. */
#define COverrideVirtual( self, method ) 		\
	do {										\
		C_OBJ_REF-> method = (self)-> method; 	\
		(self)-> method = method;				\
	} while( 0 )


/****************************************************************************/
/* Helper macros for asserting and using defining class methods				*/
/****************************************************************************/
/* Assert a super class method before calling it. */
#define CAssertSuper( method ) \
	C_ASSERT_SUPER_METHOD( C_OBJ_REF-> method, #method ); \

/* Asserts virtual method before calling it. */
#define CAssertVirtual( name )				\
	C_ASSERT_OBJECT( C_OBJ_REF );			\
	C_ASSERT_VIRTUAL( C_OBJ_REF-> name, #name ); 	\

/* Asserts an object point in a non virtual method. */
#define CMethod( ) C_ASSERT_OBJECT( C_OBJ_REF )

/* Cast object pointer to desired class. */
extern void* CVirtualMethod_( void* );
#define CVirtualMethod( self_ )\
	CVirtualMethod_( self_ )


#endif /* CLASS_H_ */
