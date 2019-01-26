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
/**
 * @file
 */

#ifndef CLASS_H_
#define CLASS_H_		

/*
 * ==========================================================================
 * ------------------------------ Includes ----------------------------------
 * ==========================================================================
 */
#include <stddef.h>
#include <stdlib.h>

/*
 * ==========================================================================
 * ---------------------------- Structures ----------------------------------
 * ==========================================================================
 */
/**
 * @struct cclass_t
 * @brief
 *	First variables in every object's structure definition
 * @details
 * 	This appears as the first member in all class and interface
 *	structures. The cobject_t and cinterface_t structure has this as
 *	their first member. 
 *	By doing this a pointer to any object which has cclass_t as its first
 *	can be safely type cast to a struct cclass_t.
 *	This is used to back track to the base address of an object and the base 
 *	address of the virtual table. It is very important that this 
 *	structure is the first member in every class/interface structure.
 *	This works because of the C99 standard in ISO/IEC 9899 6.7.2.1.13,
 *	which says in part:
 *	"A pointer to a structure object,  suitably  converted,  points  to
 *	its  initial  member  (or  if  that  member  is  a bit-field,  then  to
 *	the  unit  in  which  it  resides),  and  vice  versa.   There may  be  unnamed
 *	padding within a structure object, but not at its beginning."
 *	<br>Consider a class hierchy:
 * @verbatim
|-------------------------|       |-------------------------|        |---------|
| ClassB                  | ----> | ClassA                  | -----> | CObject |
|-------------------------|       |-------------------------|   |    |---------|
| int varB                |       | int varA                |   |
|-------------------------|       |-------------------------|   |--> |-----------------------------|
| void methodB( ClassB* ) |       | void methodA( ClassA* ) |   |    | Interface0                  |
|-------------------------|       |-------------------------|   |    |-----------------------------|
                                                                |    | void method0( Interface0* ) |
                                                                |    |-----------------------------|
                                                                |
                                                                |--> |-----------------------------|
                                                                     | Interface1                  |
                                                                     |-----------------------------|
                                                                     | void method1( Interface1* ) |
                                                                     |-----------------------------|
@endverbatim
 *	where ClassA inherits from CObject and implements Interface0 and Interface1.
 *	ClassB inherits from ClassA. A variable of type ClassB has the following memory layout:
 * @verbatim
                      --------------------------------------------
   ClassB pointer =   |                                    |  |  |
    ClassA pointer =  |                                    |  |  |
     CObject pointer: --->  | void* C_ROOT               | -  |  |
                            | size_t C_VTABLE_OFFSET = 0 |    |  |
         -------------------| const void* C_VTABLE       |    |  |                         
         |                  | void (*free)( void* )      |    |  |
         |     Interface0:  | void* C_ROOT               | ---   |
         |                  | size_t C_VTABLE_OFFSET = 2 |       |
         |     Interface1:  | void* C_ROOT               | -------
         |                  | size_t C_VTABLE_OFFSET = 3 |
         |         ClassA:  | int varA                   |
         |         ClassB:  | int varB                   |
         |
         |
         ----> vtable --> | void (*CDestructor)( void* )    |
                          | void (*methodA)( ClassA* )      |
                          | void (*method0)( Interface0* )  |
                          | void (*method1)( Interface1* ) |
                          | void (*methodB)( ClassB* )      |
@endverbatim
 *	Given this mapping of pointers, the virtual table can always be found and the entire
 *	objects memory location known with a pointer to ClassB, ClassA, CObject, Interface0,
 *      and Interface1.
 *      For example, with a reference to Interface0 (5'th row in layout above), the virtual
 *      table is found by using C_ROOT to find the top of the object's memory, then going to the
 *      third row to get a pointer to the virtual table. Then, the offset into the virtual table of
 *	Interface0's methods is found by using the C_VTABLE_OFFSET from the Interface0 reference.
 *	Note, the layout of the virtual table is different when function overriding is used. In this
 *	example, ClassA doesn't override any methods from CObject and ClassB doesn't override 
 *      any methods from ClassA and/or CObject.
 *
 *	The virtual tables leverage the 6.7.2.1.13 rule as well. Each class' table is declared
 *	such that the super class' virtual table is always the first member of the structure.
 *	By doing this, a class' virtual table can always be safetly type cast to a table
 *	of the super class. The same is not true of interfaces, hence, their table offset value
 *	is never zero.
 */
struct cclass_t
{
    /* Reference to the vtable.
     */
    const void*     cvtable;

    /* This contains a pointer to the top of an objects memory. It is used
     * to back track to the top of an objects memory regardless of what
     * super class reference is used. Using the above example, with a reference to
     * Interface0 (pointer to 5'th row in memory layout table above), the
     * C_ROOT variable can resolve the top of the memory block. 
     */
    void*  croot;
};

/*
 * ==========================================================================
 * ----------------------- Function Declarations ----------------------------
 * ==========================================================================
 */

/**
 * @ingroup cclass_t
 * @details
 *	Cast an object to it's derived class. This is used when implementing interface
 *      methods or overriding methods in a base class.
 *
 *	@code
 *		static void inteface_method( struct interface_type* self_ )
 *		{
 *			struct derived_class* self = CCast(self_);
 *			...
 *		}
 *	@endcode      
 * @param reference
 *	object to cast to derived class.
 * @return
 *	Pointer to casted object.
 */
void* ccast( void const* reference );

/**
 * @memberof class_t
 * @details
 *	Used within a classes constructor to give the object instance
 *	the location of the class' virtual table.
 *	This must always be called after constructing the super class 
 *	and before constructing any interfaces. For example,
 *	@code
 *		void ArrayList( struct ArrayList* self )
 *		{
 *			cobject(self);
 *			cvtable(self, arraylist_vtable( ));
 *			...
 *		}
 *	@endcode
 * @param self
 *	The object which needs a virtual table reference.
 * @param vtable
 *	The pointer to the class' virtual table.
 */
void cclass_set_cvtable( void* self, const void* vtable);

/**
 * @memberof cclass_t
 * @details
 *	This is used to get a pointer to the objects vtable.
 *	For example, say we have a class inheritance chain like such:
 *		struct square_t :: struct point_t :: struct cobject_t
 *	Due to polymorphism, having a reference to an object of type struct point_t
 *	does not guarentee that objects virtual table is, in fact, that of struct point_t.
 *	We might have an instance of struct square_t, and the correct virtual table
 *      is that of struct square_t.
 *	Using this method guarentees we will get a pointer to the correct virtual table.
 *
 *	This method should only be used in a wrapper function for calling virtual methods.
 *	For example, say struct point_t has a method Point::move. 
 *	@code
 *		void point_move( struct point_t* self )
 *		{
 *			((struct point_vtable_t*) cclass_vtable(self))->move(self);
 *		}
 *	@endcode
 *
 *	Then, application code simply calls point_move, which has the
 *	code for actually finding and calling the virtual method. 
 *
 *	This method works on references to objects and interfaces.
 *
 * @param self
 *	A pointer to the object whos virtual table is needed. 
 * @returns
 *	A pointer to the objects virtual table.
 */
const void* cclass_get_vtable( void* self );


#endif /* CLASS_H_ */
