/*
 * Copyright 2017 Brendan Bruner
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
 * April 5, 2017
 */

#include <unit.h>
#include <CCSoftSerialBus.h>
#include <CCSoftSerialDev.h>

/* Cannot test arbitration unless the number is
 * two or higher.
 */
#if CCSOFTSERIAL_MAX_PENDING_MASTERS < 2
#error "Cannot perform soft serial tests. See this file for reason why"
#endif

#define TEST_MASTERS (CCSOFTSERIAL_MAX_PENDING_MASTERS+1)
#define TEST_CHANNEL_LENGTH 10
#define TEST_SLAVE_ID (TEST_MASTERS+1)
struct CCSoftSerialDev master[TEST_MASTERS];
struct CCSoftSerialDev slave;
struct CCSoftSerialBus bus;

TEST_SETUP( )
{
	CError err;
	int i;

	err = CCSoftSerialBus(&bus, sizeof(char), TEST_CHANNEL_LENGTH);
	if( err != COBJ_OK ) {
		UNIT_PRINT("Fatal error during test setup."
			   "Test result are unreliable");
	}
	
	for( i = 0; i < TEST_MASTERS; ++i ) {
		err = CCSoftSerialDevMaster(&master[i],
					    (unsigned char) i,
					    (CCSoftSerialDevID) i,
					    &bus);
		if( err != COBJ_OK ) {
			UNIT_PRINT("Fatal error during test setup."
				   "Test result are unreliable");
		}
	}
	err = CCSoftSerialDevSlave(&slave,
				   (CCSoftSerialDevID) TEST_SLAVE_ID,
				   &bus);
	if( err != COBJ_OK ) {
		UNIT_PRINT("Fatal error during test setup."
			   "Test result are unreliable");
	}
	
}

TEST_TEARDOWN( )
{
	int i;

	for( i = 0; i < TEST_MASTERS; ++i ) {
		CDestroy(&master[i]);
	}
	CDestroy(&slave);
	CDestroy(&bus);
}

static void* arbitration_tree_fill( void* args )
{
	(void) args;
	pthread_exit(NULL);
}

static void* arbitration_lower_prio_master( void* args )
{
	(void) args;
	pthread_exit(NULL);
}

static void* arbitration_higher_prio_master( void* args )
{
	(void) args;
	pthread_exit(NULL);
}

TEST(arbitration)
{
}

TEST(bus_release)
{
}

static void* is_selected_do_selection( void* args )
{
	(void) args;
	pthread_exit(NULL);
}

TEST(is_selected)
{
}

static void* data_transfer_slave( void* args )
{
	(void) args;
	pthread_exit(NULL);
}

static void* data_transfer_master( void* args )
{
	(void) args;
	pthread_exit(NULL);
}

TEST(data_transfer)
{
}

TEST_SUITE(soft_serial)
{
	ADD_TEST(arbitration);
	ADD_TEST(bus_release);
	ADD_TEST(is_selected);
	ADD_TEST(data_transfer);
}
