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
 * Jun 20, 2016
 */

#include "virtual_test_classes.h"

/****************************************************************************/
/* Class A																	*/
/****************************************************************************/
static int method0( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSA_METHOD0;
}

static int method1( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSA_METHOD1;
}

static int method2( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSA_METHOD2;
}

static int method3( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSA_METHOD3;
}

static int method4( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSA_METHOD4;
}

void newVTClassA( struct VTClassA* self )
{
	CAssertObject(self);

	/* Call super's constructor. */
	CObject(&self->cobject);

	CLinkVirtual(self->method0, method0);
	CLinkVirtual(self->method1, method1);
	CLinkVirtual(self->method2, method2);
	CLinkVirtual(self->method3, method3);
	CLinkVirtual(self->method4, method4);
}

/****************************************************************************/
/* Class B																	*/
/****************************************************************************/
static int classBMethod1( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSB_METHOD1;
}

static int classBMethod2( struct VTClassA* self_ )
{
	/* This is VTClassB's implementation, so cast object back to type VTClassB. */
	struct VTClassB* self = CCast(self_);

	CAssertSuper(self->method2);
	/* Call super's (VTClassA)  implementation of this method. */
	return VT_CLASSB_METHOD2 + self->method2(&self->classA);
}

static int classBMethod3( struct VTClassA* self )
{
	CAssertObject(self);
	return VT_CLASSB_METHOD3;
}

static int classBMethod4( struct VTClassA* self_ )
{
	/* This is VTClassB's implementation, so cast object back to type VTClassB. */
	struct VTClassB* self = CCast(self_);

	CAssertSuper(self->method4);
	/* Call super's (VTClassA) implementation of this method. */
	return VT_CLASSB_METHOD4 + self->method4(&self->classA);
}

void newVTClassB( struct VTClassB* self )
{
	CAssertObject(self);

	/* Call super's constructor. */
	newVTClassA(&self->classA);

	/* Relink method 1, loosing the super's implementation. */
	CLinkVirtual(self->classA.method1, classBMethod1);

	/* Relink method 3, loosing the super's implementation. */
	CLinkVirtual(((struct VTClassA*) self)->method3, classBMethod3);

	/* Override method 2. */
	COverrideVirtual(self->method2, self->classA.method2, classBMethod2);

	/* Override method 4. */
	COverrideVirtual(self->method4, self->classA.method4, classBMethod4);

}

/****************************************************************************/
/* Class C																	*/
/****************************************************************************/
static int classCMethod3( struct VTClassA* self_ )
{
	/* This is VTClassC's implementation, so cast object back to type VTClassC. */
	struct VTClassC* self = CCast(self_);

	CAssertSuper(self->method3);
	/* Calls super's (VTClassB) implementation of this method. */
	return VT_CLASSC_METHOD3 + self->method3((struct VTClassA*) self);
}

static int classCMethod4( struct VTClassA* self_ )
{
	/* This is VTClassC's implementation, so cast object back to type VTClassC. */
	struct VTClassC* self = CCast(self_);

	CAssertSuper(self->method3);
	/* Calls super's (VTClassB) implementation of this method. */
	return VT_CLASSC_METHOD4 + self->method4((struct VTClassA*) self);
}

void newVTClassC( struct VTClassC* self )
{
	CAssertObject(self);

	/* Call super's constructor. */
	newVTClassB(&self->classB);

	/* Override method3. */
	COverrideVirtual(self->method3, self->classB.classA.method3, classCMethod3);

	/* Override method4. */
	COverrideVirtual(self->method4, self->classB.classA.method4, classCMethod4);
}
