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
 * March 24, 2017
 */
/**
 * @file
 */

#ifndef UTIL_CCSOFTSERIALBUS_H_
#define UTIL_CCSOFTSERIALBUS_H_

#include <CCSoftSerialDev.h>
#include <CCThreadedQueue.h>

/************************************************************************/
/* Declare Class and vtable.						*/
/************************************************************************/
/**
 * @struct CCSoftSerialBus
 * @ingroup InterTaskCommunication
 * @brief
 *	Implements a bus used to faciliate the communication between
 *	CCSoftSerial objects.
 * @details
 *	Implements a bus used to faciliate the communication between
 *	CCSoftSerial objects.
 */
struct CCSoftSerialBus
{
	/* Super class must always be first member */
	/* of a class' struct. */
	struct CObject cObject;

	/* Private member variables. */
	struct
	{
		struct CCSoftSerialDev* master;
		struct CCSoftSerialDev* slave;
		struct CIQueue* misoChannel;
		struct CIQueue* mosiChannel;
		CBool isStatic;
	}_;
};

/**
 * @ingroup VTable
 * @brief
 *	CCSoftSerialBus vtable
 */
struct CCSoftSerialBus_VTable
{
	/* Space for a carbon copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	/* This is where we will override inherited members. */
	struct CObject_VTable  CObject_VTable;

	/* Since we are overriding the destructor, and need to call the */
	/* originally implementation in the new implementation, we need to */
	/* keep a reference to the super class' vtable. */
	const struct CObject_VTable* CObject_VTable_Ref;
};

/**
 * @memberof CCSoftSerialBus
 * @ingroup VTable
 * @details
 *	Get reference to the struct CCSoftSerialBus's vtable.
 */
const struct CCSoftSerialBus_VTable* CCSoftSerialBus_VTable_Key( );


/************************************************************************/
/* Class Methods							*/
/************************************************************************/
/**
 * @memberof CCSoftSerialBus
 * @constructor
 * @sa CCSoftSerialDevMaster()
 * @details
 * @param self
 *	The serial bus to construct.
 * @param tokenSize
 *	The length of data arrays which are written/read by devices with CCSoftSerialDev_Read()
 *	and CCSoftSerialDev_Write().
 * @param channelSize
 *	The number of tokens which can fit into the read/write channel before causing an
 *	overflow condition.
 */
CError CCSoftSerialBus( struct CCSoftSerialBus* self, size_t tokenSize, size_t channelSize );

/**
 * @memberof CCSoftSerialBus
 * @constructor
 * @note
 *	Master in Slave out (miso) and Master out Slave in (mosi)
 * @details
 *	Same as CCSoftSerialBus, except the programmer is reponsible for constructing the miso and
 *	mosi data channels (the channels are just thread safe queues).
 *	When the destructor for the bus object is called, these queues will be have their destructor called too.
 */
CError CCSoftSerialBusStatic( struct CCSoftSerialBus* self, struct CCThreadedQueue* misoChannel, struct CCThreadedQueue* mosiChannel );

/**
 * @memberof CCSoftSerialBus
 * @details
 */
CCSoftSerialError CCSoftSerialBus_Write( struct CCSoftSerialBus* self, struct CCSoftSerial* controller, void* data );

/**
 * @memberof CCSoftSerialBus
 * @details
 */
CCSoftSerialError CCSoftSerialBus_Read( struct CCSoftSerialBus* self, struct CCSoftSerial* controller, void** data );

/**
 * @memberof CCSoftSerialBus
 * @details
 */
CCSoftSerialError CCSoftSerialBus_Select( struct CCSoftSerialBus* self, struct CCSoftSerial* controller, CCSoftSerialID id );

/**
 * @memberof CCSoftSerialBus
 * @details
 */
CCSoftSerialError CCSoftSerialBus_Unselect( struct CCSoftSerialBus* self, struct CCSoftSerial* controller );

/**
 * @memberof CCSoftSerialBus
 * @details
 */
CCSoftSerialError CCSoftSerialBus_Isselect( struct CCSoftSerialBus* self, struct CCSoftSerial* controller );


#endif /* UTIL_CCSOFTSERIALBUS_H_ */

