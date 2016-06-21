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
 * Jun 21, 2016
 */

#include "interface_test_classes.h"

/****************************************************************************/
/* Class A																	*/
/****************************************************************************/
/* Implementation of inherited interface method. */
static int ITInterface0_ClassA_Method0( struct ITInterface0* self_ )
{
	CAssertObject(self_);
	return IT_CLASSA_I0_METHOD0;
}

/* Implementation of inherited interface method. */
static int ITInterface0_ClassA_Method1( struct ITInterface0* self_ )
{
	CAssertObject(self_);
	return IT_CLASSA_I0_METHOD1;
}

/* Implementation of inherited interface method. */
static int ITInterface1_ClassA_Method0( struct ITInterface1* self_ )
{
	CAssertObject(self_);
	return IT_CLASSA_I1_METHOD0;
}

/* Implementation of inherited interface method. */
static int ITInterface2_ClassA_Method0( struct ITInterface2* self_ )
{
	CAssertObject(self_);
	return IT_CLASSA_I2_METHOD0;
}

/* Implementation of inherited interface method. */
static int ITInterface2_ClassA_Method1( struct ITInterface2* self_ )
{
	CAssertObject(self_);
	return IT_CLASSA_I2_METHOD1;
}

/* Constructor. */
void newITClassA( struct ITClassA* self )
{
	/* Construct super class. */
	CObject(&self->cobject);

	/* Construct inherited interfaces */
	CInterface(self, &self->itInterface2);
	CInterface(self, &self->itInterface1);
	CInterface(self, &self->itInterface1.itInterface0);

	/* Link interface2 method implementations. */
	self->itInterface2.i2method0 = ITInterface2_ClassA_Method0;
	self->itInterface2.i2method1 = ITInterface2_ClassA_Method1;

	/* Link interface 1 method implementations. */
	self->itInterface1.i1method0 = ITInterface1_ClassA_Method0;

	/* Link interface 0 methods implementations.*/
	self->itInterface1.itInterface0.i0method0 = ITInterface0_ClassA_Method0;
	self->itInterface1.itInterface0.i0method1 = ITInterface0_ClassA_Method1;
}


/****************************************************************************/
/* Class B																	*/
/****************************************************************************/
/* Override this inherited method. */
static int ITInterface0_ClassB_Method0( struct ITInterface0* self_ )
{
	CAssertObject(self_);
	struct ITClassB* self = CCast(self_);

	/* Return sum of this macro plus value returned by super's implementation. */
	CAssertSuper(self->i0method0);
	return IT_CLASSB_I0_METHOD0 + self->i0method0(&self->classA.itInterface1.itInterface0);
}

/* Override this inherited method. */
static int ITInterface2_ClassB_Method0( struct ITInterface2* self_ )
{
	CAssertObject(self_);
	struct ITClassB* self = CCast(self_);

	/* Return sum of this macro plus value returned by super's implementation. */
	CAssertSuper(self->i2method0);
	return IT_CLASSB_I2_METHOD0 + self->i2method0(&self->classA.itInterface2);
}

/* Relink this method. */
static int ITInterface0_ClassB_Method1( struct ITInterface0* self_ )
{
	CAssertObject(self_);

	return IT_CLASSB_I0_METHOD1;
}

/* Relink this method. */
static int ITInterface2_ClassB_Method1( struct ITInterface2* self_ )
{
	CAssertObject(self_);

	return IT_CLASSB_I2_METHOD1;
}

void newITClassB( struct ITClassB* self )
{
	/* Construct super class. */
	newITClassA(&self->classA);

	/* Relink these methods. */
	self->classA.itInterface1.itInterface0.i0method1 = ITInterface0_ClassB_Method1;
	self->classA.itInterface2.i2method1 = ITInterface2_ClassB_Method1;

	/* Override these methods. */
	self->i0method0 = self->classA.itInterface1.itInterface0.i0method0;				/* Keep reference to super's implementation. */
	self->classA.itInterface1.itInterface0.i0method0 = ITInterface0_ClassB_Method0;	/* Override with new implementation. */

	self->i2method0 = self->classA.itInterface2.i2method0;				/* Keep reference to super's implementation. */
	self->classA.itInterface2.i2method0 = ITInterface2_ClassB_Method0;	/* Override with new implementation. */
}


/****************************************************************************/
/* Class C																	*/
/****************************************************************************/
/* Override this inherited method. */
static int ITInterface0_ClassC_Method0( struct ITInterface0* self_ )
{
	CAssertObject(self_);
	struct ITClassC* self = CCast(self_);

	/* Return sum of this macro plus value returned by super's implementation. */
	CAssertSuper(self->i0method0);
	return IT_CLASSC_I0_METHOD0 + self->i0method0(&self->classB.classA.itInterface1.itInterface0);
}

/* Override this inherited method. */
static int ITInterface1_ClassC_Method0( struct ITInterface1* self_ )
{
	CAssertObject(self_);
	struct ITClassC* self = CCast(self_);

	/* Return sum of this macro plus value returned by super's implementation. */
	CAssertSuper(self->i2method0);
	return IT_CLASSC_I1_METHOD0 + self->i1method0(&self->classB.classA.itInterface2);
}

/* Override this inherited method. */
static int ITInterface2_ClassC_Method0( struct ITInterface2* self_ )
{
	CAssertObject(self_);
	struct ITClassC* self = CCast(self_);

	/* Return sum of this macro plus value returned by super's implementation. */
	CAssertSuper(self->i2method0);
	return IT_CLASSC_I2_METHOD0 + self->i2method0(&self->classB.classA.itInterface2);
}

void newITClassC( struct ITClassC* self )
{
	/* Construct super class. */
	newITClassB(&self->classB);

	/* Override these methods. */
	self->i0method0 = self->classB.classA.itInterface1.itInterface0.i0method0;				/* Keep reference to super's implementation. */
	self->classB.classA.itInterface1.itInterface0.i0method0 = ITInterface0_ClassC_Method0;	/* Override with new implementation. */

	self->i1method0 = self->classB.classA.itInterface1.i1method0;				/* Keep reference to super's implementation. */
	self->classB.classA.itInterface1.i1method0 = ITInterface1_ClassC_Method0;	/* Override with new implementation. */

	self->i2method0 = self->classB.classA.itInterface2.i2method0;				/* Keep reference to super's implementation. */
	self->classB.classA.itInterface2.i2method0 = ITInterface2_ClassC_Method0;	/* Override with new implementation. */
}
