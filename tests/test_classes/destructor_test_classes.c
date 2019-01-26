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
const struct DTClassA_VTable* DTClassA_VTable_Key( )
{
	/* Only one vtable for all instances of DTClassB. */
	static struct DTClassA_VTable vtable;

	/* Not changing the super's vtable, so just copy it in. */
	vtable.CObject_VTable = *cobject_vtable( );

	/* Return pointer. */
	return &vtable;
}
void newDTClassA( struct DTClassA* self, int* testVar )
{
	/* Call super's constructor. */
	cobject_init(&self->cobject);

	/* Map vtable. */
	cclass_set_cvtable(self, DTClassA_VTable_Key( ));

	/* Set test var to zero. */
	*testVar = 0;
	self->destructorTestVar = testVar;
}


/****************************************************************************/
/* Class B																	*/
/****************************************************************************/
const struct DTClassB_VTable* DTClassB_VTable_Key( )
{
	/* Only one vtable for all instances of DTClassB. */
	static struct DTClassB_VTable vtable;

	/* Not changing super's vtable, so just copy it. */
	vtable.DTClassA_VTable = *DTClassA_VTable_Key( );

	/* return pointer. */
	return &vtable;
}
void newDTClassB( struct DTClassB* self, int* testVar )
{
	/* Call super's constructor. */
	newDTClassA(&self->dtClassA, testVar);

	/* Map vtable. */
	cclass_set_cvtable(self, DTClassB_VTable_Key( ));
}


/****************************************************************************/
/* Class C																	*/
/****************************************************************************/
static void dtClassCDestroy( void* self_ )
{
	/* This is DTClassC's implementation, so cast object to type DTClassC. */
	struct DTClassC* self = ccast(self_);

	/* Increment test var */
	++*(self->dtClassA).destructorTestVar;

	/* Call super's destructor. */
	void (*dest)( void* );
	const struct DTClassC_VTable* vtable;
	vtable = cclass_get_vtable(self);
	dest = vtable->Supers_DTClassA_VTable->CObject_VTable.cdestructor;
	dest(self);
}

const struct DTClassC_VTable* DTClassC_VTable_Key( )
{
	/* Only one vtable for all instances of DTClassB. */
	static struct DTClassC_VTable vtable;

	/* Going to override destructor, but before we do that, */
	/* Start with a clean copy of super's vtable. */
	vtable.DTClassA_VTable = *DTClassA_VTable_Key( );

	/* Override destructor. */
	vtable.DTClassA_VTable.CObject_VTable.cdestructor = dtClassCDestroy;

	/* Since we need to call the super's destructor in our destructor, */
	/* keep a reference to the super's vtable. */
	vtable.Supers_DTClassA_VTable = DTClassA_VTable_Key( );

	/* Return pointer. */
	return &vtable;
}
void newDTClassC( struct DTClassC* self, int* testVar )
{
	/* Call super's constructor. */
	newDTClassA(&self->dtClassA, testVar);

	/* Remap super's vtable and assign self's vtable. */
	cclass_set_cvtable(self, DTClassC_VTable_Key( ));
}


/****************************************************************************/
/* Class D																	*/
/****************************************************************************/
static void dtClassDDestroy( void* self_ )
{
	/* This is DTClassD's implementation, so cast object to type DTClassD. */
	struct DTClassD* self = ccast(self_);

	/* Increment test var. */
	++*(self->dtClassB.dtClassA).destructorTestVar;

	/* Call super's destructor. */
	((struct DTClassD_VTable*) cclass_get_vtable(self))->Supers_DTClassB_VTable->DTClassA_VTable.CObject_VTable.cdestructor(self);
}

const struct DTClassD_VTable* DTClassD_VTable_Key( )
{
	/* Only one vtable for all instances of DTClassB. */
	static struct DTClassD_VTable vtable;

	/* Going to override destructor, but before we do that, */
	/* Start with a clean copy of super's vtable. */
	vtable.DTClassB_VTable = *DTClassB_VTable_Key( );

	/* Override destructor. */
	vtable.DTClassB_VTable.DTClassA_VTable.CObject_VTable.cdestructor = dtClassDDestroy;

	/* Since we need to call the super's destructor in our destructor, */
	/* keep a reference to the super's vtable. */
	vtable.Supers_DTClassB_VTable = DTClassB_VTable_Key( );

	/* Return pointer. */
	return &vtable;
}

void newDTClassD( struct DTClassD* self, int* testVar )
{
	/* Call super's constructor. */
	newDTClassB(&self->dtClassB, testVar);

	/* Map vtable. */
	cclass_set_cvtable(self, DTClassD_VTable_Key( ));
}


/****************************************************************************/
/* Class E																	*/
/****************************************************************************/
static void dtClassEDestroy( void* self_ )
{
	/* This is DTClassE's implementation, so cast object to type DTClassE. */
	struct DTClassE* self = ccast(self_);

	/* Set test var. */
	*(self->dtClassC.dtClassA).destructorTestVar = DT_CLASS_E_VAL;

	/* Call super's destructor. */
	((struct DTClassE_VTable*) cclass_get_vtable(self))->Supers_DTClassC_VTable->DTClassA_VTable.CObject_VTable.cdestructor(self);
}

const struct DTClassE_VTable* DTClassE_VTable_Key( )
{
	/* Only one vtable for all instances of DTClassB. */
	static struct DTClassE_VTable vtable;

	/* Going to override destructor, but before we do that, */
	/* Start with a clean copy of super's vtable. */
	vtable.DTClassC_VTable = *DTClassC_VTable_Key( );

	/* Override destructor. */
	((struct cobject_vtable_t*) &vtable)->cdestructor = dtClassEDestroy;

	/* Since we need to call the super's destructor in our destructor, */
	/* keep a reference to the super's vtable. */
	vtable.Supers_DTClassC_VTable = DTClassC_VTable_Key( );

	/* Return pointer. */
	return &vtable;
}

void newDTClassE( struct DTClassE* self, int* testVar )
{
	/* Call super's constructor. */
	newDTClassC(&self->dtClassC, testVar);

	/* Override destructor. */
	cclass_set_cvtable(self, DTClassE_VTable_Key( ));
}
