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
 *
 * These classes are used to test:
 *
 * 		Implementing an interface's methods. (A->I2).
 * 			* Can implement i2method0
 * 			* Can implement i2method1
 *
 * 		Implementing methods in an interface which are inherited from an interface. (A->I1->I0).
 * 			* Can implement i0method0
 * 			* Can implement i0method1
 * 			* Can implement i1method0
 *
 * 		Overriding and relinking inherited interface methods in B. (B->A).
 * 			* Can override i0method0
 * 			* Can relink i0method1
 * 			* Can override i2method0
 * 			* Can relink i2method1
 *
 * 		Overriding inherited interface methods in C. (C->B->A).
 * 			* Can override i0method0
 * 			* Can override i2method0
 * 			* Can override i1method0
 */
#ifndef TESTS_TEST_CLASSES_INTERFACE_TEST_CLASSES_H_
#define TESTS_TEST_CLASSES_INTERFACE_TEST_CLASSES_H_

#include <Class.h>

#define IT_CLASSA_I0_METHOD0 1
#define IT_CLASSA_I0_METHOD1 2
#define IT_CLASSA_I2_METHOD0 3
#define IT_CLASSA_I2_METHOD1 4
#define IT_CLASSA_I1_METHOD0 5

#define IT_CLASSB_I0_METHOD0 6
#define IT_CLASSB_I0_METHOD1 7
#define IT_CLASSB_I2_METHOD0 8
#define IT_CLASSB_I2_METHOD1 9

#define IT_CLASSC_I0_METHOD0 10
#define IT_CLASSC_I1_METHOD0 12
#define IT_CLASSC_I2_METHOD0 11

/****************************************************************************/
/* Interface 0																*/
/****************************************************************************/
struct ITInterface0
{
	/* Must be first member of an interface. */
	struct CInterface interface;

	/* Inheriting classes must implement these methods. */
	int (*i0method0)( struct ITInterface0* );
	int (*i0method1)( struct ITInterface0* );
};

/* Wrapper for calling interface method. */
static inline int ITInterface0_Method0( struct ITInterface0* self )
{
	CAssertObject(self);
	CAssertVirtual(self->i0method0);
	return self->i0method0(self);
}

/* Wrapper for calling interface method. */
static inline int ITInterface0_Method1( struct ITInterface0* self )
{
	CAssertObject(self);
	CAssertVirtual(self->i0method1);
	return self->i0method1(self);
}


/****************************************************************************/
/* Interface 1																*/
/****************************************************************************/
struct ITInterface1
{
	/* Must be first member of an interface. */
	struct CInterface interface;

	/* Inherit from interface0. */
	struct ITInterface0 itInterface0;

	/* Inheriting classes must implement these methods. */
	int (*i1method0)( struct ITInterface1* );
};

/* Wrapper for calling interface method. */
static inline int ITInterface1_Method0( struct ITInterface1* self )
{
	CAssertObject(self);
	CAssertVirtual(self->i1method0);
	return self->i1method0(self);
}


/****************************************************************************/
/* Interface 2																*/
/****************************************************************************/
struct ITInterface2
{
	/* Must be first member of an interface. */
	struct CInterface interface;

	/* Inheriting classes must implement these methods. */
	int (*i2method0)( struct ITInterface2* );
	int (*i2method1)( struct ITInterface2* );
};

/* Wrapper for calling interface method. */
static inline int ITInterface2_Method0( struct ITInterface2* self )
{
	CAssertObject(self);
	CAssertVirtual(self->i2method0);
	return self->i2method0(self);
}

/* Wrapper for calling interface method. */
static inline int ITInterface2_Method1( struct ITInterface2* self )
{
	CAssertObject(self);
	CAssertVirtual(self->i2method1);
	return self->i2method1(self);
}


/****************************************************************************/
/* Class A																	*/
/****************************************************************************/
struct ITClassA
{
	/* Base class, so inherit from class object. */
	struct CObject cobject;

	/* Inherit from these interfaces */
	struct ITInterface2 itInterface2;
	struct ITInterface1 itInterface1;
};

/* Constructor. */
void newITClassA( struct ITClassA* );


/****************************************************************************/
/* Class B																	*/
/****************************************************************************/
struct ITClassB
{
	/* Inherit from this class. */
	struct ITClassA classA;

	/* Override this methods inherited from ITClassA. */
	int (*i0method0)( struct ITInterface0* );
	int (*i2method0)( struct ITInterface2* );
};

/* Constructor. */
void newITClassB( struct ITClassB* );


/****************************************************************************/
/* Class C																	*/
/****************************************************************************/
struct ITClassC
{
	/* Inherit from this class. */
	struct ITClassB classB;

	/* Override these methods. */
	int (*i0method0)( struct ITInterface0* );
	int (*i1method0)( struct ITInterface1* );
	int (*i2method0)( struct ITInterface2* );
};

/* Constructor. */
void newITClassC( struct ITClassC* );

#endif /* TESTS_TEST_CLASSES_INTERFACE_TEST_CLASSES_H_ */
