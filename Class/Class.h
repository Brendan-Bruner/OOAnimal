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
/* The .bss footprint when this is not defined is: 	~1400 bytes. */
/* The .bss footprint when this is defined is:		~16 bytes.   */
//#define C_MINIMAL_DEBUG

/* The variable name used to reference an object, this is */
/* 'this' in C++/Java and 'self' in Python. */
/* Some helper macros assume the object reference has this name. */
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
#define C_PRINT( ... ) 				printf( __VA_ARGS__ )
#define C_FAILED_ASSERT_HANDLE( ) 	for( ;; )

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
#define C_INIT_OBJECT( object )
#endif

/* End of configuration options. */

/****************************************************************************/
/* Assert Messages															*/
/****************************************************************************/
#if defined( DEBUG )
extern void CAssert( char exp, char const* msg, char const* file, int line );
extern void CAssert2( char exp, char const* msg1, char const* msg2, char const* file, int line );
#else
#define CAssert( exp, msg, file, line ) (void)file; (void) line;
#define CAssert2( exp, msg1, msg2, file, line ) (void)file; (void)line;
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
	"\t* Constructor was called, but super constructor was not called\n"\
	"\t  For example, say B extends A, and an instance of B was created.\n"\
	"\t  The error is reported to have happened in the source file for A.\n"\
	"\t  Then, the constructor for B was called, but within B's constructor,\n"\
	"\t  the constructor for A was not called.\n"\
	"\t* The method is ment to be pure virtual, an object of this class\n"\
	"\t  should never be instantiated\n"
#endif
extern const char* CAssertVirtualMessage_;
#define C_ASSERT_VIRTUAL( method, funcName )\
	CAssert2( ((method)==NULL), CAssertVirtualMessage_, funcName, __FILE__, __LINE__ )

#if defined( C_MINIMAL_DEBUG )
#define C_ASSERT_SUPER_METHOD_MESSAGE NULL
#else
#define C_ASSERT_SUPER_METHOD_MESSAGE \
	"Super method not linked. Possible causes:\n"\
	"\t* Did not call super class constructor. ie, if B inherits\n"\
	"\t  from A and the failure happened in B, then B's constructor\n"\
	"\t  did not call its super constructor, that is, A's constructor.\n"
#endif
extern const char* CAssertSuperMethodMessage_;
#define C_ASSERT_SUPER_METHOD( method, name )\
	CAssert2( ((method)==NULL), CAssertSuperMethodMessage_, name, __FILE__, __LINE__ )

#if defined( C_MINIMAL_DEBUG )
#define C_ASSERT_OBJECT_MESSAGE NULL
#else
#define C_ASSERT_OBJECT_MESSAGE \
	"NULL pointer used as input\n"
#endif
extern const char* CAssertObjectMessage_;
#define C_ASSERT_OBJECT( object )\
	CAssert( ((object)==NULL), CAssertObjectMessage_, __FILE__, __LINE__ )

#if defined( C_MINIMAL_DEBUG )
#define C_ASSERT_CAST_MESSAGE NULL
#else
#define C_ASSERT_CAST_MESSAGE \
	"Class method called on NULL object. Possible causes:\n"\
	"\t* If this error occurred in an interface method, then the\n"\
	"\t* constructor did not call CInterface( ) to construct the\n"\
	"\t  interface.\n"\
	"\t* It this error occurred in an interface method. Say B extends\n"\
	"\t  A and A implements I. The error occurred in source file A for\n"\
	"\t  a method defined in I, and the method was called on an instance\n"\
	"\t  of B. Then, B's constructor did not call it's super constructor,\n"\
	"\t  ie, A's constructor.\n"\
	"\t* If this error occured in a class method, then the constructor for\n"\
	"\t  that class did not call CConstructor( ) as the FIRST thing it does\n"
#endif
extern const char* CAssertCastMessage_;
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
extern struct CObject* CObject( struct CObject* );
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
#define CConstructor( self )					\
	do {										\
		C_ASSERT_OBJECT( self );				\
		C_INIT_OBJECT( self );					\
		((struct CObject*) self)->C_ROOT = self;\
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
/* Note, never overwrite CDestructor( ). Always override it. */
#define COverwriteVirtual( self, method ) \
	do { (self)-> method = method; } while( 0 )

/* Helper macro for overriding virtual methods. Unlike overwriting, a */
/* reference to the super's method is retained. */
/* Expects a variable C_OBJ_REF is defined. */
#define COverrideVirtual( self, super, method ) \
	do {										\
		self-> method = (super)-> method; 		\
		(super)-> method = method;				\
	} while( 0 )


/****************************************************************************/
/* Helper macros for asserting and defining class methods					*/
/****************************************************************************/
/* Assert a super class method before calling it. */
#define CAssertSuper( self, method ) \
	C_ASSERT_SUPER_METHOD( self->method, #method ); \

/* Asserts virtual method before calling it. */
#define CAssertVirtual( self, name )				\
	C_ASSERT_OBJECT( self );			\
	C_ASSERT_VIRTUAL( self-> name, #name ); 	\

/* Helper macro for asserting pointers. */
#define CAssertObject( object ) \
	C_ASSERT_OBJECT( (object) )

/* Asserts an object point in a non virtual method. */
#define CMethod( self ) C_ASSERT_OBJECT( self )

/* Cast object pointer to desired class. */
struct CRoot{ void* C_ROOT; };
extern void* CVirtualMethod_( void*, const char*, int );
#define CCast( self_ )\
	CVirtualMethod_( self_, __FILE__, __LINE__ )
//	CVirtualMethod_( self_ )


#endif /* CLASS_H_ */
