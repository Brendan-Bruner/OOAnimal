/*
 * Copyright 2019 Brendan Bruner
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

#ifndef INTERFACE_H_
#define INTERFACE_H_		

/*
 * ==========================================================================
 * ------------------------------ Includes ----------------------------------
 * ==========================================================================
 */
#include "cclass.h"

/*
 * ==========================================================================
 * ---------------------------- Structures ----------------------------------
 * ==========================================================================
 */
/**
 * @struct CInterface
 * @ingroup Class
 * @brief
 *	Base interface.
 * @details
 *	All interfaces must include this as their first structure member.
 */
struct cinterface_t
{
    /* cclass must be the first member of this struct.
     * Do not change. 
     * Used to back track from a pointer to an interface, to its implementing
     * class' vtable, and the offset into that vtable where the implemented
     * methods are located.
     */
    struct cclass_t cclass;
};


/*
 * ==========================================================================
 * ----------------------- Function Declarations ----------------------------
 * ==========================================================================
 */
/**
 * @memberof cinterface_t
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
static inline void cinterface_init( void* self, void* iface, const void* vtable )
{
        /* iface is suppose to be an interface, therefore, we assume that
         * the first variable in the structures definition is of type
         * cclass_t
         */
        struct cclass_t* iface_class = iface;
        
	iface_class->croot = self;
        cclass_set_cvtable(iface, vtable);
}



#endif /* INTERFACE_H_ */
