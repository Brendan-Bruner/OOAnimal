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

#include <CCSoftSerial.h>
#include <CIQueue.h>

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
		CCSoftSerialID selected;
		struct CIQueue* misoChannel;
		struct CIQueue* mosiChannel;
	}_;
};

/**
 * @ingroup VTable
 * @brief
 *	CCSoftSerialBus vtable
 */
struct CCSoftSerialBus_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;	
};

/************************************************************************/
/* Class Methods							*/
/************************************************************************/
/**
 * @memberof CCSoftSerialBus
 * @constructor
 * @details
 */
CError CCSoftSerialBus( struct CCSoftSerialBus* self );

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

