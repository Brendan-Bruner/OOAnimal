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
#include "FireLord.h"
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
static void testTraitOverride(void);

/**
 * Tests that a class which uses multiple traits implements them
 * properly.
 */
static void testMultipleTraits(void);

/**
 * Test that a trait can be cast down to its derived class
 */
static void testTraitCastToDerived(void);

/**
 * Test that a base class can be cast down to its derived class
 */
static void testClassCastToDerived(void);

/**
 * Test that derived classes can override their super classes functions.
 */
static void testFunctionOverride(void);

/**
 * Test that a classes methods and data work by using setters and getters
 */
static void testClass(void);

/**
 * Test that an array of FireBreath's all have a method flames. It should
 * not matter what class is using this trait (ie, teenager or dragon),
 * just that when the flames method is called on the object. The
 * appropriate implementation of flames should then be called
 */
static void testTraitPolymorphism(void);

/**
 * Test an array of Whelp's. This performs the same test as
 * testTraitPolymorphism except it is testing classes, not traits,
 * for polymorphism.
 */
static void testClassPolymorphism(void);

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}

static void testTraitPolymorphism(void)
{
	int 				i, damage;
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

	breathers[0] = &guard1.FireBreathT;
	breathers[1] = &guard2.FireBreathT;
	breathers[2] = &guard3.FireBreathT;
	breathers[3] = &element1.FireBreathT;
	breathers[4] = &element2.FireBreathT;
	breathers[5] = &element3.FireBreathT;
	breathers[6] = &lft1.FireBreathT;
	breathers[7] = &lft2.FireBreathT;

	ASSERT_EQUAL(0, guard1.FireBreathT.flames(&guard1.FireBreathT), breathers[0]->flames(breathers[0]));
	ASSERT_EQUAL(1, guard2.FireBreathT.flames(&guard2.FireBreathT), breathers[1]->flames(breathers[1]));
	ASSERT_EQUAL(2, guard3.FireBreathT.flames(&guard3.FireBreathT), breathers[2]->flames(breathers[2]));
	ASSERT_EQUAL(3, element1.FireBreathT.flames(&element1.FireBreathT), breathers[3]->flames(breathers[3]));
	ASSERT_EQUAL(4, element2.FireBreathT.flames(&element2.FireBreathT), breathers[4]->flames(breathers[4]));
	ASSERT_EQUAL(5, element3.FireBreathT.flames(&element3.FireBreathT), breathers[5]->flames(breathers[5]));
	ASSERT_EQUAL(6, lft1.FireBreathT.flames(&lft1), breathers[6]->flames(breathers[6]));
	ASSERT_EQUAL(7, lft2.FireBreathT.flames(&lft2), breathers[7]->flames(breathers[7]));
}

static void testClassPolymorphism(void)
{
	int i, damage;
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
	whelps[2] = &guard1;
	whelps[3] = &guard2;
	whelps[4] = &lord1;
	whelps[5] = &lord2;
	whelps[6] = &dragon1;
	whelps[7] = &dragon2;

	ASSERT_EQUAL(8, whelp1.attack(&whelp1), whelps[0]->attack(whelps[0]));
	ASSERT_EQUAL(9, whelp2.attack(&whelp2), whelps[1]->attack(whelps[1]));
	ASSERT_EQUAL(10, ((Whelp *) &guard1)->attack(&guard1), whelps[2]->attack(whelps[2]));
	ASSERT_EQUAL(11, ((Whelp *) &guard2)->attack(&guard2), whelps[3]->attack(whelps[3]));
	ASSERT_EQUAL(12, ((Whelp *) &lord1)->attack(&lord1), whelps[4]->attack(whelps[4]));
	ASSERT_EQUAL(13, ((Whelp *) &lord2)->attack(&lord2), whelps[5]->attack(whelps[5]));
	ASSERT_EQUAL(14, ((Whelp *) &dragon1)->attack(&dragon1), whelps[6]->attack(whelps[6]));
	ASSERT_EQUAL(15, ((Whelp *) &dragon2)->attack(&dragon2), whelps[7]->attack(whelps[7]));
}

static void testClass(void)
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

static void testFunctionOverride(void)
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

	ASSERT_NOT_EQUAL(18, whelp.special(&whelp), ((Whelp *) &guard)->special(&guard));
	ASSERT_NOT_EQUAL(19, whelp.special(&whelp), ((Whelp *) &lord)->special(&lord));
	ASSERT_NOT_EQUAL(20, whelp.special(&whelp), ((Whelp *) &dragon)->special(&dragon));
	ASSERT_NOT_EQUAL(21, ((Whelp *) &guard)->special(&guard), ((Whelp *) &lord)->special(&lord));
	ASSERT_NOT_EQUAL(22, ((Whelp *) &guard)->special(&guard), ((Whelp *) &dragon)->special(&dragon));
	ASSERT_NOT_EQUAL(23, ((Whelp *) &lord)->special(&guard), ((Whelp *) &dragon)->special(&dragon));

}

static void testClassCastToDerived(void)
{
	Whelp *whelp;
	FlameLord lord;

	newFlameLord(&lord);
	whelp = &lord;

	ASSERT_EQUAL(24, whelp->attack(whelp), ((Whelp *) &lord)->attack(&lord));
	ASSERT_EQUAL(25, ((FlameLord *) whelp)->reap(whelp), lord.reap(&lord));
}

static void testTraitCastToDerived(void)
{
	FireBreath *trait;
	FlameGuard guard;

	newFlameGuard(&guard);
	trait = &guard.FireBreathT;

	ASSERT_EQUAL(26, guard.FireBreathT.flames(&guard.FireBreathT), trait->flames(trait));
	ASSERT_EQUAL(27, guard.FireBreathT.flames(&guard.FireBreathT), ((FlameGuard *) CastTrait(trait))->FireBreathT.flames(trait));
}

static void testMultipleTraits(void)
{
	FireElement elemental;

	newFireElement(&elemental);

	/* A fire elements flames is set to do 2*magic as damage */
	ASSERT_EQUAL(28, elemental.FireBreathT.flames(&elemental.FireBreathT), elemental.getMagic(&elemental)*2);
	/* A fire elements heatWave is set to do 4*magic as a damage */
	ASSERT_EQUAL(29, elemental.InnerFireT.heatWave(&elemental.InnerFireT), elemental.getMagic(&elemental)*2);
	/* A fire elements explosion is set to do 2*heatWave damage => 8*magic as a damage */
	ASSERT_EQUAL(30, elemental.VolatileCoreT.explosion(&elemental.VolatileCoreT), elemental.getMagic(&elemental)*8);
}

static void testTraitOverride(void)
{
	FireLord lord;
	FireGuard guard;

	newFireLord(&lord);
	newGuard(&guard);

	ASSERT_NOT_EQUAL(31, ((FireGuard *) &lord)->FireBreathT.flames(&((FireGuard *) &lord)->FireBreathT), guard.FireBreathT.flames(&guard.FireBreathT));
}
