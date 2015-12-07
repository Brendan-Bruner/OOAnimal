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

/* The variable name used to reference an object, this is */
/* 'this' in C++/Java and 'self' in Python. */
#define C_OBJ_REF 				self

/*
 * The assert macros are used to trap user errors. 
 * These defined how to print formatted strings and what to
 * do when an assertion fails.
 */
#include <stdio.h>
#define C_PRINT( ... ) printf( __VA_ARGS__ )
#define C_FAILED_ASSERT_HANDLE( ) for( ;; )

#if defined( DEBUG )
extern void CAssert( void* exp, char const* msg, char const* line, int lineNumber );
extern void CAssert2( void* exp, char const* msg1, char const* msg2, char const* line, int lineNumber );
#else
#define CAssert( exp, msg, line, lineNumber ) (void)exp; (void)msg; (void)line; (void) lineNumber;
#define CAssert2( exp, msg1, msg2, line, lineNumber ) (void)exp; (void)msg1; (void)msg2; (void)line; (void) lineNumber;
#endif

/* All classes and interfaces contain a pointer to their  */
/* super class, the base object, this is the name of that pointer. */
#define C_ROOT						_rt

/* If a class inherits, it will contain an instance of the class it */
/* is inheriting from. This is the name of that instance. */
#define C_SUPER	 					_sp

/* When a class implementings an interface, it contains an */
/* instance of the interface. This is prefixed / posfixed to the data type */
/* of the interface and used as the variable name. */
#define C_INTERFACE_PREFIX 			_if
#define C_INTERFACE_POSIFX
#define C_IFACE_VAR( i ) \
	C_INTERFACE_PREFIX##i##C_INTERFACE_POSFIX

/* Used to zero out a structure. */
/* This assumes that NULL resolves to 0, which is requried by C standard. */
/* If your C library doesn't have memset, you will have to write your own, */
/* or opt not use it. */
#if defined( DEBUG )
#include <string.h>
#define C_INIT_OBJECT( object )							\
	do {												\
		memset( (void*) (object), 0, sizeof(*object) );	\
	} while( 0 )
#else
#define C_INIT_OBJECT( object ) (void) object
#endif

/* Default memory clean up method used. */
/* Calling CObject_IsDynamic( ) on an object will invoke this free method */
/* being called after destruction. */
#define CDefaultFree free


/****************************************************************************/
/* Assert Messages															*/
/****************************************************************************/
/* Different reasons for asserting. */
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
#define C_ASSERT_VIRTUAL( method, funcName )\
	CAssert2( (void*) (method), C_ASSERT_VIRTUAL_MESSAGE, funcName, __FILE__, __LINE__ )

#define C_ASSERT_SUPER_METHOD_MESSAGE \
	"Super method not linked: Possible causes:\n"\
	"\t* This failure is hard to get. I have not been able to get it\n"\
	"\t  to fire through normal use. Likely, there is stack stomping at\n"\
	"\t  play. The error is due to a method pointer for overriding a\n"\
	"\t  virtual method being NULL\n"
#define C_ASSERT_SUPER_METHOD( method, name )\
	CAssert2( (void*) (method), C_ASSERT_SUPER_METHOD_MESSAGE, name, __FILE__, __LINE__ )

#define C_ASSERT_OBJECT_MESSAGE \
	"Attempt to call class method on NULL object\n"
#define C_ASSERT_OBJECT( object )\
	CAssert( (void*) (object), C_ASSERT_OBJECT_MESSAGE, __FILE__, __LINE__ )


/****************************************************************************/
/* Base object																*/
/****************************************************************************/
typedef void (*CFreeType)( void* );
extern CFreeType CFree_;
typedef struct CObject CObject;
struct CObject
{
	void (*CDestructor)( CObject* );
	CFreeType CObject_Free;
	struct
	{
		void* C_ROOT;
	}_;
};
extern void newCObject( CObject* );
extern void CObject_Destroy( CObject* );
extern void CObject_IsDynamic( CObject* );
extern void CObject_SetFree( CObject*, CFreeType );


/****************************************************************************/
/* Used destroy objects. 													*/
/****************************************************************************/
#define CDestroy( mem )	\
	CObject_Destroy( (CObject*) (mem)->_.C_ROOT );


/********************************************************************************/
/* Helper macros for defining a class and interface								*/
/********************************************************************************/
/* Must be first in any class. */
#define CClass( CSuper )				\
	struct {							\
		CSuper			C_SUPER;		\
		void*			C_ROOT;			\
	}_

/* Can be put anywhere in an interface. */
#define CInterface( )					\
	struct {							\
		void*		C_ROOT;				\
	}_
/* Used to implement an interface in a class' definition. */
#define CImplements( iface )	\
	iface C_IFACE_VAR( iface );

/****************************************************************************/
/* Constructor specific setup												*/
/****************************************************************************/
#define CConstructor( )							\
	do {										\
		C_ASSERT_OBJECT( C_OBJ_REF );			\
		C_INIT_OBJECT( C_OBJ_REF );				\
		C_OBJ_REF->_.C_ROOT = (void*) C_OBJ_REF;\
	} while( 0 )

/* Bind the interface data at run time. Use in constructor */
#define CLinkInterface( iface )								\
	do {													\
		C_OBJ_REF->C_IFACE_VAR( iface ).C_ROOT = (void*) C_OBJ_REF;	 \
	} while( 0 )


/******************************************************************************/
/* Used to dynamically link methods at run time. */
/******************************************************************************/
/* The two macros below select one of two virtual linkage macros. */
#define C_LINK_VIRTUAL_SELECTION( _1, _2, SELECTION, ... ) SELECTION
#define CLinkVirtual( ... ) \
	C_LINK_VIRTUAL_SELECTION( __VA_ARGS__, C_LINK_INTERFACE_VIRTUAL, C_LINK_CLASS_VIRTUAL )( __VA_ARGS__ )
#define C_LINK_CLASS_VIRTUAL( method ) \
	do { C_OBJ_REF-> method = method; } while( 0 )
#define C_LINK_INTERFACE_VIRTUAL( iface, method ) \
	do { C_OBJ_REF->C_IFACE_VAR( iface ). method = method; } while( 0 )

/* The two macros below are used to override a virtual method. */
/* They can be used in lue of COverrideVirtual( ) when the super class' implementation */
/* will never be call within the subclass class. */
#define C_RE_LINK_VIRTUAL_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define CReLinkVirtual( ... ) \
	C_RE_LINK_VIRTUAL_SELECTION( __VA_ARGS__, C_RE_LINK_INTERFACE_VIRTUAL, C_RE_LINK_CLASS_VIRTUAL )( __VA_ARGS__ )
#define C_RE_LINK_CLASS_VIRTUAL( class, method ) \
	do { ((class) C_OBJ_REF)-> method = method; } while( 0 )
#define C_RE_LINK_INTERFACE_VIRTUAL( iface, class, method ) \
	do { ((class) C_OBJ_REF)->C_IFACE_VAR( iface ). method = method; } while( 0 )

/* The two macros below select one of two virtual linkage macros for overriding methods. */
/* Use this in lue of CReLinkVirtual( ) when the subclass must use the super classes */
/* implementation of the overriden method. */
#define C_OVERRIDE_VIRTUAL_SELECTION( _1, _2, _3, SELECTION, ... ) SELECTION
#define COverrideVirtual( ... ) \
	C_OVERRIDE_VIRTUAL_SELECTION( __VA_ARGS__, C_OVERRIDE_INTERFACE_VIRTUAL, C_OVERRIDE_CLASS_VIRTUAL )( __VA_ARGS__ )
#define C_OVERRIDE_CLASS_VIRTUAL( class, method )									\
	do {																			\
		C_OBJ_REF-> method = ((class) C_OBJ_REF)-> method; 	\
		((class) C_OBJ_REF)-> method = method;							\
	} while( 0 )
#define C_OVERRIDE_INTERFACE_VIRTUAL( class, iface, method )					\
	do {																		\
		C_OBJ_REF-> method = ((class) C_OBJ_REF)->C_IFACE_VAR( iface ). method; \
		((class) C_OBJ_REF)->C_IFACE_VAR( iface ).method = method;\
	} while( 0 )


/****************************************************************************/
/* Used to access super class' implementation of a method. 					*/
/****************************************************************************/
#define CSuper( method ) \
	C_ASSERT_SUPER_METHOD( C_OBJ_REF-> method, #method ); \
	C_OBJ_REF-> method


/****************************************************************************/
/* Helper macros for calling and setting up virtual methods					*/
/****************************************************************************/
/* Asserts and then calls the virtual method. */
#define CCallVirtual( name )				\
	C_ASSERT_OBJECT( C_OBJ_REF );			\
	C_ASSERT_VIRTUAL( C_OBJ_REF-> name, #name ); 	\
	return C_OBJ_REF-> name

/* Sets up the 'self' variable in a class method. */
#define CMethod( ) C_ASSERT_OBJECT( C_OBJ_REF )
#define CVirtualMethod( C, self_ ) 				\
	C C_OBJ_REF;							\
	do {									\
		C_ASSERT_OBJECT( self_ );			\
		C_OBJ_REF = (C) self_->_.C_ROOT;	\
	} while( 0 )

/******************************************************************************/
/* Call interface methods on an object using the interface */
/******************************************************************************/
#define CCast(i,O) \
	(&(O)->C_IFACE_VAR( i ))

#endif /* CLASS_H_ */
