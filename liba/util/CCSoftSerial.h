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
 * @defgroup InterTaskCommunication
 * Inter task communication classes
 */
#ifndef UTIL_CCSOFTSERIAL_H_
#define UTIL_CCSOFTSERIAL_H_

/************************************************************************/
/* Error codes.								*/
/************************************************************************/
/**
 * @enum CCSoftSerialError
 * @ingroup InterTaskCommunication
 * @var CCSOFTSERIAL_OK
 *	No error
 * @var CCSOFTSERIAL_ERR_NOT_SELECTED
 *	Slave device attempting to use the serial bus when it's not
 *	selected.
 * @var CCSOFTSERIAL_ERR_CONTENTION
 *	One of two possibilities:
 *		- Master attempting to use the bus when another
 *		  master already has access to the bus. Read/write will have
 *		  no effect.
 *		- Master attempting to select a slave when a another
 *		  master already has access to the bus. slave select
 *		  will fail.
 * @var CCSOFTSERIAL_ERR_PREEMPTED
 *	On a bus which allows for pre-emption, this means the slave/master
 *	was thrown off the bus by a higher priority master. This will be
 *	returned only one time by ether of read/write to indicate you've
 *	been pre-empted. slave select has to be used again to regain bus
 *	controll. Remaining calls to read/write will return 
 *	CCSOFTSERIAL_ERR_NOT_SELECTED.
 * @var CCSOFTSERIAL_ERR_TIMEOUT
 *	Timeout trying to select a slave. This means a higher priority
 *	master still has control of the bus. 
 */
typedef enum
{
	CCSOFTSERIAL_OK = 0,
	CCSOFTSERIAL_ERR_NOT_SELECTED = 1,
	CCSOFTSERIAL_ERR_CONTENTION = 2,
	CCSOFTSERIAL_ERR_PREEMPTED = 3,
	CCSOFTSERIAL_ERR_TIMEOUT = 4,
} CCSoftSerialError;


/**
 * @enum CCSoftSerialID
 * @ingroup InterTaskCommunication
 * @details
 *	ID of serial controllers (CCSoftSerial objects).
 */
typedef enum
{
	CCSOFTSERIAL_ID0 = 0,
	CCSOFTSERIAL_ID1 = 1
} CCSoftSerialID;

/*
 * Lowest possible priority level. Serial objects with this priority 
 * will be treated as slaves.
 */
#define CCSOFTSERIAL_SLAVE 0

/* 
 * Forward declar serial bus class
 */
struct CCSoftSerialBus;



/************************************************************************/
/* Declare Class and vtable.						*/
/************************************************************************/
/**
 * @struct CCSoftSerial
 * @ingroup InterTaskCommunication
 * @brief
 *	Implements an interface to a software defined  multi master 
 *	priority encoded serial bus.
 * @details
 *	Implements an interface to a software defined  multi master 
 *	priority encoded serial bus. Think of this as an SPI bus
 *	with priority.
 */
struct CCSoftSerial
{
	/* Super class must always be first member */
	/* of a class' struct. */
	struct CObject cObject;

	/* Private member variables. */
	struct
	{
		CCSoftSerialID id;
		char priority;
		struct CCSoftSerialBus* bus;
	}_;
};

/**
 * @ingroup VTable
 * @brief
 *	CCSoftSerial vtable
 */
struct CCSoftSerial_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;	
};


/************************************************************************/
/* Class Methods							*/
/************************************************************************/
/**
 * @memberof CCSoftSerial
 * @constructor
 * @details
 */
CError CCSoftSerial( struct CCSoftSerial* self, char priority, CCSoftSerialID id, struct CCSoftSerialBus* bus );

/**
 * @memberof CCSoftSerial
 * @details
 */
CCSoftSerialID CCSoftSerial_GetID( struct CCSoftSerial* self );

/**
 * @memberof CCSoftSerial
 * @details
 */
char CCSoftSerial_GetPriority( struct CCSoftSerial* self );

/**
 * @memberof CCSoftSerial
 * @details
 */
CCSoftSerialError CCSoftSerial_Select( struct CCSoftSerial* self, CCSoftSerialID id );

/**
 * @memberof CCSoftSerial
 * @details
 */
CCSoftSerialError CCSoftSerial_Unselect( struct CCSoftSerial* self );

/**
 * @memberof CCSoftSerial
 * @details
 */
CBool CCSoftSerial_Isselected( struct CCSoftSerial* self );


#endif /* UTIL_CCSOFTSERIAL_H_ */

