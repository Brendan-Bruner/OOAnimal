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
	CObject(&self->object);

	*testVar = 0;
	self->destructorTestVar = testVar;
}


/****************************************************************************/
/* Class B																	*/
/****************************************************************************/
void newDTClassB( struct DTClassB* self, int* testVar )
{
	newDTClassA(&self->dtClassA, testVar);
}


/****************************************************************************/
/* Class C																	*/
/****************************************************************************/
static void dtClassCDestroy( struct CObject* self_ )
{
	/* Cast back to class we are working with. */
	struct DTClassC* self = CCast(self_);

	/* Increment test var */
	++*(self->dtClassA).destructorTestVar;

	/* Call super's destructor. */
	CAssertSuper(self->CDestructorDTC);
	self->CDestructorDTC((struct CObject*) self);
}
void newDTClassC( struct DTClassC* self, int* testVar )
{
	newDTClassA(&self->dtClassA, testVar);

	/* Override destructor. */
	self->CDestructorDTC = ((struct CObject*) self)->CDestructor;	/* Keep reference to super's implementation */
	((struct CObject*) self)->CDestructor = dtClassCDestroy;		/* Override with new implementation			*/
}


/****************************************************************************/
/* Class D																	*/
/****************************************************************************/
static void dtClassDDestroy( struct CObject* self_ )
{
	/* Cast back to class we're working with. */
	struct DTClassD* self = CCast(self_);

	/* Increment test var. */
	++*(self->dtClassB.dtClassA).destructorTestVar;

	/* Call super's destructor. */
	CAssertSuper(self->CDestructorDTD);
	self->CDestructorDTD((struct CObject*) self);
}
void newDTClassD( struct DTClassD* self, int* testVar )
{
	newDTClassB(&self->dtClassB, testVar);

	/* Override destructor. */
	self->CDestructorDTD = ((struct CObject*) self)->CDestructor;	/* Keep reference to super's implementation */
	((struct CObject*) self)->CDestructor = dtClassDDestroy;		/* Override with new implementation			*/
}


/****************************************************************************/
/* Class E																	*/
/****************************************************************************/
static void dtClassEDestroy( struct CObject* self_ )
{
	/* Cast back to class we're working with. */
		struct DTClassE* self = CCast(self_);

	/* Set test var. */
	*(self->dtClassC.dtClassA).destructorTestVar = DT_CLASS_E_VAL;

	/* Call super's destructor. */
	CAssertSuper(self->CDestructorDTE);
	self->CDestructorDTE((struct CObject*) self);
}
void newDTClassE( struct DTClassE* self, int* testVar )
{
	newDTClassC(&self->dtClassC, testVar);

	/* Override destructor. */
	self->CDestructorDTE = ((struct CObject*) self)->CDestructor;		/* Keep reference to super's implementation */
	((struct CObject*) self)->CDestructor = dtClassEDestroy;			/* Override with new implementation			*/
}
