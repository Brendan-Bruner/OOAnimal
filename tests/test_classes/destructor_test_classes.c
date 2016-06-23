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
 * Jun 19, 2016
 */

#include <test_classes/destructor_test_classes.h>


/****************************************************************************/
/* Class A																	*/
/****************************************************************************/
void newDTClassA( struct DTClassA* self, int* testVar )
{
	CAssertObject(self);
	CAssertObject(testVar);

	/* Call super's constructor. */
	CObject(&self->object);

	/* Set test var to zero. */
	*testVar = 0;
	self->destructorTestVar = testVar;
}


/****************************************************************************/
/* Class B																	*/
/****************************************************************************/
void newDTClassB( struct DTClassB* self, int* testVar )
{
	CAssertObject(self);
	CAssertObject(testVar);

	/* Call super's constructor. */
	newDTClassA(&self->dtClassA, testVar);
}


/****************************************************************************/
/* Class C																	*/
/****************************************************************************/
static void dtClassCDestroy( struct CObject* self_ )
{
	/* This is DTClassC's implementation, so cast object to type DTClassC. */
	struct DTClassC* self = CCast(self_);

	/* Increment test var */
	++*(self->dtClassA).destructorTestVar;

	/* Call super's destructor. */
	CAssertSuper(self->CDestructorDTC);
	self->CDestructorDTC(&self->dtClassA.object);
}
void newDTClassC( struct DTClassC* self, int* testVar )
{
	CAssertObject(self);
	CAssertObject(testVar);

	/* Call super's constructor. */
	newDTClassA(&self->dtClassA, testVar);

	/* Override destructor. */
	COverrideVirtual(self->CDestructorDTC, self->dtClassA.object.CDestructor, dtClassCDestroy);
}


/****************************************************************************/
/* Class D																	*/
/****************************************************************************/
static void dtClassDDestroy( struct CObject* self_ )
{
	/* This is DTClassD's implementation, so cast object to type DTClassD. */
	struct DTClassD* self = CCast(self_);

	/* Increment test var. */
	++*(self->dtClassB.dtClassA).destructorTestVar;

	/* Call super's destructor. */
	CAssertSuper(self->CDestructorDTD);
	self->CDestructorDTD(&self->dtClassB.dtClassA.object);
}
void newDTClassD( struct DTClassD* self, int* testVar )
{
	CAssertObject(self);
	CAssertObject(testVar);

	/* Call super's constructor. */
	newDTClassB(&self->dtClassB, testVar);

	/* Override destructor. */
	COverrideVirtual(self->CDestructorDTD, self->dtClassB.dtClassA.object.CDestructor, dtClassDDestroy);
}


/****************************************************************************/
/* Class E																	*/
/****************************************************************************/
static void dtClassEDestroy( struct CObject* self_ )
{
	/* This is DTClassE's implementation, so cast object to type DTClassE. */
	struct DTClassE* self = CCast(self_);

	/* Set test var. */
	*(self->dtClassC.dtClassA).destructorTestVar = DT_CLASS_E_VAL;

	/* Call super's destructor. */
	CAssertSuper(self->CDestructorDTE);
	self->CDestructorDTE(&self->dtClassC.dtClassA.object);
}
void newDTClassE( struct DTClassE* self, int* testVar )
{
	CAssertObject(self);
	CAssertObject(testVar);

	/* Call super's constructor. */
	newDTClassC(&self->dtClassC, testVar);

	/* Override destructor. */
	COverrideVirtual(self->CDestructorDTE, self->dtClassC.dtClassA.object.CDestructor, dtClassEDestroy);
}
