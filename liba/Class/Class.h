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

/************************************************************************/
/* Bool type								*/
/************************************************************************/
#define CBool unsigned char

/************************************************************************/
/* Configuration options						*/
/************************************************************************/
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
#define CFree				CDefaultFree	

/* Default memory allocation method to use. */
#define CMalloc				malloc

/* Method declaration of memory free method. */
typedef void (*CFreeType)( void* );

/* All classes and interfaces contain a pointer to their class */
/* this is the name of that pointer. */
#define C_CLASS				_cc

/* All classes and interfaces contain a pointer to their highest */
/* super class, the base object, this is the name of that pointer. */
#define C_ROOT				_rt

/* All classes and interfaces contain a pointer to their virtual table, */
/* this is the name of that pointer. */
#define C_VTABLE			_vt

#define C_VTABLE_OFFSET			_vo

/* These define how to print formatted strings and what to */
/* do when an assertion fails. */
#include <stdio.h>
#define C_PRINT( ... ) 			printf( __VA_ARGS__ )
#define C_FAILED_ASSERT_HANDLE( ) 	for( ;; )


/************************************************************************/
/* Assert Messages							*/
/************************************************************************/
/* Different reasons for asserting. */
#if C_DEBUG_DIAG_LEVEL == 2

#define C_ASSERT_VIRTUAL_MESSAGE \
	"Virtual method not linked. Possible causes:\n"\
	"\t* [A0] Class constructor did not link virtual table with CVTable\n"\
	"\t* [A1] Constructor was never called on object\n"\
	"\t* [A2] Constructor was called, but super's constructor was not called\n"\
	"\t* [A3] Virtual table function assignment is incomplete\n"

#define C_ASSERT_OBJECT_MESSAGE \
	"NULL pointer used as input\n"

#define C_ASSERT_CAST_MESSAGE \
	"Failure to cast object. Possible causes:\n"\
	"\t* [C0] Did not call interface constructor, CInterface( )\n"\
	"\t* [C1] Did not call super's constructor.\n"

extern const char* CAssertVirtualMessage_;
extern const char* CAssertObjectMessage_;
extern const char* CAssertCastMessage_;

#else

#define CAssertVirtualMessage_ 		NULL
#define CAssertObjectMessage_ 		NULL
#define CAssertCastMessage_ 		NULL

#endif


/************************************************************************/
/* Assert macros							*/
/************************************************************************/
#if defined( DEBUG )
extern void CAssert( char exp, char const* msg, char const* file, int line );
#else
#define CAssert( exp, msg, file, line ) \
	do {				\
		(void) (exp);		\
		(void) (file);		\
		(void) (line);		\
	} while( 0 )
#endif

#define C_ASSERT_VIRTUAL( method )\
	CAssert( ((method)==NULL), CAssertVirtualMessage_, __FILE__, __LINE__ )
#define C_ASSERT_OBJECT( object )\
	CAssert( ((object)==NULL), CAssertObjectMessage_, __FILE__, __LINE__ )
#define C_ASSERT_CAST( object, file, line )\
	CAssert( (object) == NULL, CAssertCastMessage_, file, line )


/************************************************************************/
/* Base object structures						*/
/************************************************************************/
/**
 * @struct CClass
 * @details
 *	This is at the base of all interfaces and classes. It is used 
 *	to back track to the base address of an object and the base 
 *	address of the virtual table. 
 * @var C_ROOT
 *	This contains a pointer to the top of an objects memory. It is used
 *	to back track to the top of an objects memory regardless of what
 *	super class reference is used. 
 * @var C_VTABLE_OFFSET
 *	This is used to find the offset into the  virtual table where a
 *	classes virtual methods are.
 */
struct CClass
{
	/* C_ROOT must be first variable in this struct. */
	/* Do not change. */
	void* C_ROOT;
	size_t C_VTABLE_OFFSET;
};

/**
 * @struct CObject
 * @details
 *	This is the class object. All classes inherit from this class. Basically,
 *	it tells an object how to be an object. It does this by having a struct CClass
 *	instance and a pointer to the objects virtual table. Although the struct CClass
 *	contains redundent information (ie, C_ROOT will point itself and C_VTABLE_OFFSET
 *	will be zero) it enables a consistent interface for class and interface references
 *	to locate the C_VTABLE pointer within an object and find the displacement into the
 *	vtable of virtual functions of interest.
 * @var C_CLASS
 *	Used to provide consistent interface for finding virtual functions when dealing with
 *	object and interface references.
 * @var C_VTABLE
 *	Pointer to an objects vtable. 
 * @var CObject_Free
 *	Pointer to a memory free method used in the objects destructor. Will be NULL by default
 *	(ie, assumes automatic variable) and can be set by application code.
 */
struct CObject
{
	/* C_CLASS must be first variable in this struct. */
	/* Do not change. */
	struct CClass C_CLASS; 
	const void* C_VTABLE;
	CFreeType CObject_Free;
};

/**
 * @struct CObject_VTable
 * @memberof struct CObject
 * @details
 *	Contains the virtual function members of struct CObject. There is only one
 *	virtual table instance for every object instance of a class. To get a handle 
 *	to a specific virtual table instance, use the function $(CLASS_NAME)_VTable_Key( ), 
 *	which returns a const pointer to the table. All classes written in the CObject
 *	library used the convention $(CLASS_NAME)_VTable_Key( ).
 * @var CDestructor
 *	This is an objects destructor method.
 */
struct CObject_VTable
{
	void (*CDestructor)( void* );
};

/**
 * @memberof struct CObject
 * @details
 *	Return a reference to class CObject's virtual table. There is only one
 *	virtual table per class, which is shared by every instance of that class.
 *	This pointer must not be written to, only read from, hence the const return
 *	value.
 * @returns
 *	A read only pointer to class CObject's virtual table.
 */
const struct CObject_VTable* CObject_VTable_Key( );

/**
 * @memberof struct CObject
 * @details
 *	Constructor. To construct an instance of struct CObject, call this method on
 *	it. This method has a macro shortcut, CObject( ), to reduce the amount of typing
 *	for creating an instance of struct CObject.
 * @param self
 *	The instance of struct CObject to construct
 * @returns
 *	Returns a pointer the constructed instance, the same as the input argument.
 */
struct CObject* CObject_Constructor( struct CObject* self );

/**
 * @memberof struct CObject
 * @details
 *	Destructor. This is the destructor for all objects. Its polymorphic, meaning
 *	A reference to any class instance / interface can be given and the entire object will
 *	be destroyed. If a memory free method was set with CObject_SetFree( ), CDynamic( ), or
 *	CFreeWith( ), that method will be at the end of destruction. This method has a macro short cut, 
 *	CDestroy( ), to reduce the amount of typing for destroying an object.
 * @param self
 *	The object to destroy
 */
void CObject_Destroy( struct CObject* self );

/**
 * @memberof struct CObject
 * @details
 *	Set a memory free method to be called at the end of destruction.
 * @param self
 *	The object to have a memory free method set.
 * @param free_method
 *	The method to call when destruction finishes. Has declaration void(*)( void* ).
 */
void CObject_SetFree( struct CObject* self, CFreeType free_method );

/* Help macro for object construction. */
#define CObject( self )	\
	CObject_Constructor(self)

/* Helper macro for object destruction. */
#define CDestroy( mem )	\
	CObject_Destroy((void*) (mem))

/* Helper macro for declaring object dynamic. */
#define CDynamic( obj ) \
	CObject_SetFree(((struct CClass*) (obj))->C_ROOT, CDefaultFree)

/* Helper macro for declaring free method for object. */
#define CFreeWith( obj, freep ) \
	CObject_SetFree(((struct CClass*) (obj))->C_ROOT, (freep))


/************************************************************************/
/* Base interface structures						*/
/************************************************************************/
/**
 * @struct CInterface
 * @details
 *	All interfaces must include this as there first structure member.
 *	It tells an interface how to be an interface. The instance of 
 *	struct CClass is used to back track from the interface reference
 *	to its implementing class' vtable.
 * @var C_CLASS
 *	Used to back track from a pointer to an interface, to its implementing
 *	class' vtable, and the offset into that vtable where the implemented
 *	methods are located.
 */
struct CInterface
{
	/* C_CLASS must be the first member of this struct. */
	/* Do not change. */
	struct CClass C_CLASS;
};

/**
 * @memberof struct CInterface
 * @details
 *	This is the constructor for interfaces. All implementing classes must call this in
 *	their constructor AFTER mapping their virtual table with CVTable( ). This method
 *	will setup the interfaces data such that one can back track from the interface reference,
 *	param iface, to the object reference, param self, and find the offset into the class'
 *	virtual table where the implemented interface methods are located.
 * @param self
 *	This is a pointer to the object whose class is implementing the interface.
 * @param iface
 *	This is a pointer to the interface instance within the classes declaration. For example,
 *	if param self is of type struct A, and struct A implements interface struct I, then this
 *	parameter would be a pointer to A::I.
 * @param vtable
 *	This is a pointer to the interfaces virtual table. For example, say, param self is of type
 *	struct A, which implements interface struct I, and we are calling this constructor to
 *	construct A::I. struct A's vtable, struct A_VT, will contain an instance of struct I's
 *	vtable, struct I_VT. This would be a pointer to A_VT::I_VT.
 */
void CInterface( void* self, void* iface, const void* vtable );


/************************************************************************/
/* Helper macros for asserting and defining class methods		*/
/************************************************************************/
/* Asserts virtual method before calling it. */
#define CAssertVirtual( func )\
	C_ASSERT_VIRTUAL(func)

/* Helper macro for asserting pointers. */
#define CAssertObject( object )\
	C_ASSERT_OBJECT((object))

/* Cast object pointer to desired class. */
#if C_DEBUG_DIAG_LEVEL == 0
#define CCast( self_ )\
	CObjectCast_(self_, NULL, 0)
#else
#define CCast( self_ )\
	CObjectCast_( self_, __FILE__, __LINE__ )
#endif


/************************************************************************/
/* Casting and virtual table handling.					*/
/************************************************************************/
/**
 * @memberof struct CObject
 * @details
 *	This is used to cast an object. It must only be used in virtual
 *	method definitions. The usage would be this, say we are overriding
 *	the destructor, the destructors declaration looks like this
 *	void (*)( struct CObject* ). However, we are overriding the method in
 *	class struct ArrayList. We know we the input to the method is from
 *	an object of that type. This method will cast the input pointer to
 *	that type.
 *
 * 	The method has a macro wrapper to simply its call signature,
 *	CCast( ), which only takes one input, the object refernce.
 *
 *	void* CCast( void* );
 *
 *	@code
 *		static void ArrayList_Destructor( struct CObject* self_ )
 *		{
 *			struct ArrayList* self = CCast(self_);
 *			...
 *		}
 *	@endcode      
 * @param super_reference
 *	Reference to cast.
 * @param file_name
 *	Name of the file casting is done in - for debugging.
 * @param line_num
 *	Line number in the file casting is done - for debugging.
 * @return
 *	Pointer to casted object.
 */
void* CObjectCast_( void* super_reference, const char* file_name, int line_num );


/**
 * @memberof struct CObject
 * @details
 *	Used within a classes constructor to give the object instance
 *	the location of the class' virtual table.
 *	This must always be called after constructing the super class 
 *	and before constructing any interfaces. For example,
 *	@code
 *		void ArrayList( struct ArrayList* self )
 *		{
 *			CObject(self);
 *			CVTable(self, ArrayList_VTable_Key( ));
 *			...
 *		}
 *	@endcode
 * @param self
 *	The object which needs a virtual table reference.
 * @param vtable
 *	The pointer to the class' virtual table.
 */
void CVTable( void* self, const void* vtable);

/**
 * @memberof struct CObject
 * @details
 *	This is used to get a pointer to the objects vtable. When calling a 
 *	virtual method, this should always be used over $(CLASS_NAME)_VTable_Key( ).
 *	For example, say we have a class inheritance chain like such:
 *		struct Square :: struct Point :: struct CObject
 *	Due to polymorphism, having a reference to an object of type struct Point
 *	does not guarentee that objects virtual table is given by Point_VTable_Key( ).
 *	We might have an instance of struct Square, and the correct virtual table
 *	is Square_VTable_Key( ). There is no way of knowing. 
 *	Using this method guarentees we will get a pointer to the correct virtual table.
 *
 *	This method should only be used in a wrapper function for calling virtual methods.
 *	For example, say struct Point has a method struct Point::move. 
 *	@code
 *		void Point_Move( struct Point* self )
 *		{
 *			((struct Point_VTable*) CGetVTAble(self))->move(self);
 *		}
 *	@endcode
 *
 *	Then, application code simply calls Point_Move, which has the more cumbersome
 *	code for actually finding and calling the virtual method. 
 *
 *	This method works on references to objects and interfaces.
 *
 * @param self_
 *	A pointer to the object whos virtual table is needed. 
 * @returns
 *	A pointer to the objects virtual table.
 */
const void* CGetVTable( void* self_ );


#endif /* CLASS_H_ */
