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
 * Jun 18, 2016
 *
 * These classes are used to test:
 * 		Memory free hook in destructor is correctly called in base class A.
 *
 *		Destructor call is correctly made when B inherits from A. (B->A).
 *
 * 		Destructor calls are correctly cascaded when C overrides destructor. (C->A).
 *
 * 		Destructor calls are correctly cascaded when D overrides destructor from B. (D->B->A).
 *
 * 		Destructor calls are correctly cascaded when E overrides destructor in C. (E->C->A).
 */
#ifndef TESTS_TEST_CLASSES_H_
#define TESTS_TEST_CLASSES_H_

#include <Class.h>

#define DT_CLASS_A_VAL 0
#define DT_CLASS_E_VAL -4

/****************************************************************************/
/* Test classes																*/
/****************************************************************************/

struct DTClassA
{
	struct CObject object;

	int* destructorTestVar;
};

struct DTClassB
{
	struct DTClassA dtClassA;
};

struct DTClassC
{
	struct DTClassA dtClassA;

	/* Overriding */
	void (*CDestructorDTC)( struct CObject* );
};

struct DTClassD
{
	struct DTClassB dtClassB;

	/* Overriding */
	void (*CDestructorDTD)( struct CObject* );
};

struct DTClassE
{
	struct DTClassC dtClassC;

	/* Overriding */
	void (*CDestructorDTE)( struct CObject* );
};

extern void newDTClassA( struct DTClassA*, int* );
extern void newDTClassB( struct DTClassB*, int* );
extern void newDTClassC( struct DTClassC*, int* );
extern void newDTClassD( struct DTClassD*, int* );
extern void newDTClassE( struct DTClassE*, int* );

#endif /* TESTS_TEST_CLASSES_H_ */
