/*
 * main.c
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 *
 *  Compile without optimization to ensure compiler doesn't optimize away variable
 *  assignment in test cases.
 */

#include "Whelp.h"
#include "FlameGuard.h"
#include "FireBreath.h"
#include "FireElement.h"
#include "LivingFlameThrower.h"
#include "FlameLord.h"
#include "Dragon.h"
#include "InnerFire.h"
#include "VolatileCore.h"
#include <stdio.h>

/* Asserts A and B are not equal with == operator */
#define ASSERT_EQUAL(N,A,B) if((A) == (B)) { printf("Test %d passed\n", (N)); } else \
													printf("Test %d failed\n", (N))

#define ASSERT_NOT_EQUAL(N, A, B) if((A) != (B)) { printf("Test %d passed\n", (N)); } else \
													printf("Test %d failed\n", (N))

/**
 * Tests that a derived class can override a traits function where
 * the super class uses the trait.
 */
void testTraitOverride(void);

/**
 * Tests that a class which uses multiple traits implements them
 * properly.
 */
void testMultipleTraits(void);

/**
 * Test that a base class can be cast down to its derived class
 */
void testClassCastToDerived(void);

/**
 * Test that derived classes can override their super classes functions.
 */
void testFunctionOverride(void);

/**
 * Test that a classes methods and data work by using setters and getters
 */
void testClass(void);

/**
 * Test that an array of FireBreath's all have a method flames. It should
 * not matter what class is using this trait (ie, teenager or dragon),
 * just that when the flames method is called on the object. The
 * appropriate implementation of flames should then be called
 */
void testTraitPolymorphism(void);

/**
 * Test an array of Whelp's. This performs the same test as
 * testTraitPolymorphism except it is testing classes, not traits,
 * for polymorphism.
 */
void testClassPolymorphism(void);

int main(int argc, char **argv)
{
	/* Supress compiler warnings about unused variables. */
	(void) argc;
	(void) argv;

	testTraitPolymorphism();
	testClassPolymorphism();
	testClass();
	testFunctionOverride();
	testClassCastToDerived();
	testMultipleTraits();
	testTraitOverride();
	return 0;
}

void testTraitPolymorphism(void)
{
	FireBreath 			*breathers[8];
	FlameGuard 			guard1, guard2, guard3;
	FireElement 		element1, element2, element3;
	LivingFlameThrower 	lft1, lft2;

	newFlameGuard(&guard1);
	newFlameGuard(&guard2);
	newFlameGuard(&guard3);
	newFireElement(&element1);
	newFireElement(&element2);
	newFireElement(&element3);
	newLivingFlameThrower(&lft1);
	newLivingFlameThrower(&lft2);

	breathers[0] = trait( FireBreath, &guard1 );
	breathers[1] = trait( FireBreath, &guard2 );
	breathers[2] = trait( FireBreath, &guard3 );
	breathers[3] = trait( FireBreath, &element1 );
	breathers[4] = trait( FireBreath, &element2 );
	breathers[5] = trait( FireBreath, &element3 );
	breathers[6] = trait( FireBreath, &lft1 );
	breathers[7] = trait( FireBreath, &lft2 );

	ASSERT_EQUAL(0, trait( FireBreath, &guard1 )->flames( trait( FireBreath, &guard1 ) ), breathers[0]->flames(breathers[0]));
	ASSERT_EQUAL(1, trait( FireBreath, &guard2 )->flames( trait( FireBreath, &guard2 ) ), breathers[1]->flames(breathers[1]));
	ASSERT_EQUAL(2, trait( FireBreath, &guard3 )->flames( trait( FireBreath, &guard3 ) ), breathers[2]->flames(breathers[2]));
	ASSERT_EQUAL(3, trait( FireBreath, &element1 )->flames( trait( FireBreath, &element1 ) ), breathers[3]->flames(breathers[3]));
	ASSERT_EQUAL(4, trait( FireBreath, &element2 )->flames( trait( FireBreath, &element2 ) ), breathers[4]->flames(breathers[4]));
	ASSERT_EQUAL(5, trait( FireBreath, &element3 )->flames( trait( FireBreath, &element3 ) ), breathers[5]->flames(breathers[5]));
	ASSERT_EQUAL(6, trait( FireBreath, &lft1 )->flames( trait( FireBreath, &lft1 ) ), breathers[6]->flames(breathers[6]));
	ASSERT_EQUAL(7, trait( FireBreath, &lft2 )->flames( trait( FireBreath, &lft2 ) ), breathers[7]->flames(breathers[7]));
}

void testClassPolymorphism(void)
{
	Whelp 		*whelps[8];
	Whelp 		whelp1, whelp2;
	FlameGuard 	guard1, guard2;
	FlameLord 	lord1, lord2;
	Dragon 		dragon1,  dragon2;

	newWhelp(&whelp1);
	newWhelp(&whelp2);
	newFlameGuard(&guard1);
	newFlameGuard(&guard2);
	newFlameLord(&lord1);
	newFlameLord(&lord2);
	newDragon(&dragon1);
	newDragon(&dragon2);

	whelps[0] = &whelp1;
	whelps[1] = &whelp2;
	whelps[2] = (Whelp *) &guard1;
	whelps[3] = (Whelp *) &guard2;
	whelps[4] = (Whelp *) &lord1;
	whelps[5] = (Whelp *) &lord2;
	whelps[6] = (Whelp *) &dragon1;
	whelps[7] = (Whelp *) &dragon2;

	ASSERT_EQUAL(8, whelp1.attack(&whelp1), whelps[0]->attack(whelps[0]));
	ASSERT_EQUAL(9, whelp2.attack(&whelp2), whelps[1]->attack(whelps[1]));
	ASSERT_EQUAL(10, ((Whelp *) &guard1)->attack((Whelp *) &guard1), whelps[2]->attack(whelps[2]));
	ASSERT_EQUAL(11, ((Whelp *) &guard2)->attack((Whelp *) &guard2), whelps[3]->attack(whelps[3]));
	ASSERT_EQUAL(12, ((Whelp *) &lord1)->attack((Whelp *) &lord1), whelps[4]->attack(whelps[4]));
	ASSERT_EQUAL(13, ((Whelp *) &lord2)->attack((Whelp *) &lord2), whelps[5]->attack(whelps[5]));
	ASSERT_EQUAL(14, ((Whelp *) &dragon1)->attack((Whelp *) &dragon1), whelps[6]->attack(whelps[6]));
	ASSERT_EQUAL(15, ((Whelp *) &dragon2)->attack((Whelp *) &dragon2), whelps[7]->attack(whelps[7]));
}

void testClass(void)
{
	Whelp whelp;
	int level = 78;
	int agility = 23;

	newWhelp(&whelp);
	whelp.setLevel(&whelp, level);
	whelp.setAgility(&whelp, agility);

	ASSERT_EQUAL(16, whelp.getLevel(&whelp), level);
	ASSERT_EQUAL(17, whelp.getAgility(&whelp), agility);
}

void testFunctionOverride(void)
{
	/*
	 * Implementation of special() is made different for each class. Therefore, these tests
	 * ought to pass.
	 */
	Whelp whelp;
	FlameGuard guard;
	FlameLord lord;
	Dragon dragon;

	newWhelp(&whelp);
	newFlameGuard(&guard);
	newFlameLord(&lord);
	newDragon(&dragon);

	ASSERT_NOT_EQUAL(18, whelp.special(&whelp), ((Whelp *) &guard)->special((Whelp *) &guard));
	ASSERT_NOT_EQUAL(19, whelp.special(&whelp), ((Whelp *) &lord)->special((Whelp *) &lord));
	ASSERT_NOT_EQUAL(20, whelp.special(&whelp), ((Whelp *) &dragon)->special((Whelp *) &dragon));
	ASSERT_NOT_EQUAL(21, ((Whelp *) &guard)->special((Whelp *) &guard), ((Whelp *) &lord)->special((Whelp *) &lord));
	ASSERT_NOT_EQUAL(22, ((Whelp *) &guard)->special((Whelp *) &guard), ((Whelp *) &dragon)->special((Whelp *) &dragon));
	ASSERT_NOT_EQUAL(23, ((Whelp *) &lord)->special((Whelp *) &guard), ((Whelp *) &dragon)->special((Whelp *) &dragon));

}

void testClassCastToDerived(void)
{
	Whelp *whelp;
	FlameLord lord;

	newFlameLord(&lord);
	whelp = (Whelp *) &lord;

	ASSERT_EQUAL(24, whelp->attack(whelp), ((Whelp *) &lord)->attack((Whelp *) &lord));
	ASSERT_EQUAL(25, ((FlameLord *) whelp)->reap((FlameLord *) whelp), lord.reap(&lord));
}

void testMultipleTraits(void)
{
	FireElement elemental;

	newFireElement(&elemental);

	/* A fire elements flames is set to do 2*magic as damage */
	ASSERT_EQUAL(28, trait( FireBreath, &elemental )->flames( trait( FireBreath, &elemental ) ), elemental.getMagic(&elemental)*2);
	/* A fire elements heatWave is set to do 4*magic as a damage */
	ASSERT_EQUAL(29, trait( InnerFire, &elemental )->heatWave( trait( InnerFire, &elemental ) ), elemental.getMagic(&elemental)*4);
	/* A fire elements explosion is set to do 2*heatWave damage => 8*magic as a damage */
	ASSERT_EQUAL(30, trait( VolatileCore, &elemental )->explosion( trait( VolatileCore, &elemental ) ), elemental.getMagic(&elemental)*8);
}

void testTraitOverride(void)
{
	FlameLord lord;
	FlameGuard guard;

	newFlameLord(&lord);
	newFlameGuard(&guard);

	ASSERT_NOT_EQUAL(31, trait( FireBreath, (FlameGuard *) &lord )->flames( trait( FireBreath, (FlameGuard *) &lord ) ), trait( FireBreath, &guard )->flames( trait( FireBreath, &guard ) ));
}
