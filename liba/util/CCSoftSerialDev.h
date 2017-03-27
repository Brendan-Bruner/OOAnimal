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
#ifndef UTIL_CCSOFTSERIALDEV_H_
#define UTIL_CCSOFTSERIALDEV_H_

/************************************************************************/
/* Error codes.								*/
/************************************************************************/
/**
 * @enum CCSoftSerialDevError
 * @ingroup InterTaskCommunication
 * @var CCSOFTSERIALDEV_OK
 *	No error
 * @var CCSOFTSERIALDEV_ERR_NOT_SELECTED
 *	Slave device attempting to use the serial bus when it's not
 *	selected.
 * @var CCSOFTSERIALDEV_ERR_CONTENTION
 *	One of two possibilities:
 *		- Master attempting to use the bus when another
 *		  master already has access to the bus. Read/write will have
 *		  no effect.
 *		- Master attempting to select a slave when a another
 *		  master already has access to the bus. slave select
 *		  will fail.
 * @var CCSOFTSERIALDEV_ERR_PREEMPTED
 *	On a bus which allows for pre-emption, this means the slave/master
 *	was thrown off the bus by a higher priority master. This will be
 *	returned only one time by ether of read/write to indicate you've
 *	been pre-empted. slave select has to be used again to regain bus
 *	controll. Remaining calls to read/write will return 
 *	CCSOFTSERIALDEV_ERR_NOT_SELECTED.
 * @var CCSOFTSERIALDEV_ERR_TIMEOUT
 *	Timeout trying to select a slave. This means a higher priority
 *	master still has control of the bus. 
 * @var CCSOFTSERIALDEV_ERR_PRIV
 *	Slave device attempting to do somethign that only a master device
 *	has the privileges to do.
 */
typedef enum
{
	CCSOFTSERIALDEV_OK = 0,
	CCSOFTSERIALDEV_ERR_NOT_SELECTED = 1,
	CCSOFTSERIALDEV_ERR_CONTENTION = 2,
	CCSOFTSERIALDEV_ERR_PREEMPTED = 3,
	CCSOFTSERIALDEV_ERR_TIMEOUT = 4,
} CCSoftSerialDevError;


/**
 * @enum CCSoftSerialDevID
 * @ingroup InterTaskCommunication
 * @details
 *	ID of serial controllers (CCSoftSerialDev objects). Replace this with
 *	better mnemonics for your project.
 */
typedef enum
{
	CCSOFTSERIALDEV_ID0 = 1,
	CCSOFTSERIALDEV_ID1 = 2
} CCSoftSerialDevID;

/*
 * Lowest possible priority level. Serial objects with this priority 
 * will be treated as slaves.
 */
#define CCSOFTSERIALDEV_SLAVE 0

/* 
 * Forward declar serial bus class
 */
struct CCSoftSerialBus;



/************************************************************************/
/* Declare Class and vtable.						*/
/************************************************************************/
/**
 * @struct CCSoftSerialDev
 * @ingroup InterTaskCommunication
 * @brief
 *	Implements an interface to a software defined  multi master 
 *	priority encoded serial bus.
 * @details
 *	Implements an interface to a software defined  multi master 
 *	priority encoded serial bus. This class acts as a single controller
 *	attached to the bus which manages writing/reading to the bus. An object 
 *	of this class can write/read to a bus which has other controllers attached
 *	to it.
 */
struct CCSoftSerialDev
{
	/* Super class must always be first member */
	/* of a class' struct. */
	struct CObject cObject;

	/* Private member variables. */
	struct
	{
		CCSoftSerialDevID id;
		char priority;
		struct CCSoftSerialBus* bus;
	}_;
};

/**
 * @ingroup VTable
 * @brief
 *	CCSoftSerialDev vtable
 */
struct CCSoftSerialDev_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;	
};

/**
 * @memberof CCSoftSerialDev
 * @ingroup VTable
 * @details
 *	Get reference to the struct CCSoftSerialDev's vtable.
 */
const struct CCSoftSerialDev_VTable* CCSoftSerialDev_VTable_Key( );


/************************************************************************/
/* Class Methods							*/
/************************************************************************/
/**
 * @memberof CCSoftSerialDev
 * @constructor
 * @sa CCSoftSerialDevSlave()
 * @details
 *	Creates a CCSoftSerialDev controller object as a master device on the
 *	bus. As a master, the device can use CCSoftSerialDev_Select() to 
 *	select other masters or slaves to write/read from. Only one master
 *	can control the bus at a time. The master must release the bus when done
 *	with CCSoftSerialDev_Unselect().
 *
 *	An example of creating a bus and attaching a master and a slave. The master
 *	writes a message to the slave, then waits for a response. The slave waits until
 *	it's selected, then listens for a message, then gives a reponse.
 *
 *	@code
 *	struct CCSoftSerialBus bus; 
 *	struct CCSoftSerialDev master;
 *	struct CCSoftSerialDev slave;
 *	char* masterMsg = "hello";
 *	int masterMsgLen = 5
 *	char* slaveMsg = "world";
 *	int slaveMsgLen = 5
 *
 *	void main()
 *	{
 *		// Construct bus and devices to read/write to the bus.
 *		CCSoftSerialBus(&bus, sizeof(char), BUFFER_LENGTH);
 *		CCSoftSerialDevMaster(&master, 1, CCSOFTSERIALDEV_0, &bus);
 *		CCSoftSerialDevSlave(&slave, CCSOFTSERIALDEV_1, &bus);
 *
 *		// Using a pretend function to create a task for the slave and master
 *		newTask(slaveIO);
 *		newTask(masterIO);
 *
 *		// Wait for tasks to end and destroy bus and device.
 *		taskJoin(slaveIO);
 *		taskJoin(masterIO);
 *		
 *		CDestroy(&slave);
 *		CDestroy(&master);
 *		CDestroy(&bus);
 *	}
 *
 *	void masterIO()
 *	{		
 *		char msgBuf[slaveMsgLen];
 *
 *		// Select slave.
 *		CCSoftSerialDev_Select(&master, CCSOFTSERIALDEV_1, COS_BLOCK_FOREVER);
 *
 *		// Write a message.
 *		for( int i = 0; i < masterMsgLen; ++i ) {
 *			CCSoftSerialDev_Write(&master, masterMsg, COS_BLOCK_FOREVER);
 *		}
 *	
 *		// Get responce and unselect.
 *		for( int i = 0; i < slaveMsgLen; ++i ) {
 *			CCSoftSerialDev_Read(&master, &msgBuf, COS_BLOCK_FOREVER);
 *		}
 *
 *		// Unselect the slave device.
 *		CCSoftSerialDev_Unselect(&master);
 *	}
 *
 *	void slaveIO()
 *	{
 *		char msgBuf[masterMsgLen];
 *
 *		// Wait until selected.
 *		CCSoftSerialDev_Isselected(&slave, COS_BLOCK_FOREVER);
 *
 *		// Read message.
 *		for( int i = 0; i < masterMsgLen; ++i ) {
 *			CCSoftSerialDev_Read(&slave, &msgBuf, COS_BLOCK_FOREVER);
 *		}
 *	
 *		// Give response.
 *		for( int i = 0; i < slaveMsgLen; ++i ) {
 *			CCSoftSerialDev_Write(&master, slaveMsg, COS_BLOCK_FOREVER);
 *		}
 *	}
 *	@endcode
 * @param self
 *	The object to construct.
 * @param priority
 *	The priority this controller will have on the bus. Once set, it 
 *	cannot be changed. A higher numeric value has a higher logical 
 *	priority. The lowest priority is one, a priority of zero will result
 *	in silent automatic reassignment to priority one. All devices on a bus must
 *	have different priority levels (although two devices on different busses can
 *	have the same priority). See CCSoftSerialDev_Select()
 *	for a description of how contention is handled.
 * @param id
 *	An identification for this controller on the bus. This is the identification used
 *	to select this device with CCSoftSerialDev_Select(). The id must be unique to
 *	the bus, it is up to the programmer to ensure this happens. There is no functionality
 *	for the soft serial interface to check this.
 * @param bus
 *	The bus that this controller will write/read from. It can only write/read from devices who
 *	have the same bus attached to them. The bus cannot be changed once constructed.
 */
CError CCSoftSerialDevMaster( struct CCSoftSerialDev* self, char priority, CCSoftSerialDevID id, struct CCSoftSerialBus* bus );

/**
 * @memberof CCSoftSerialDev
 * @sa CCSoftSerialDevMaster()
 * @constructor
 * @details
 *	Creates a CCSoftSerialDev controller object as a slave device on the
 *	bus. As a slave, the object can only write/read from the bus when
 *	it's been selected. It will know it's selected when a call to
 *	CCSoftSerialDev_Isselected() returns true.
 * @param self
 *	The object to construct.
 * @param id
 *	An identification for this controller on the bus. This is the identification used
 *	to select this device with CCSoftSerialDev_Select(). The id must be unique to
 *	the bus, it is up to the programmer to ensure this happens. There is no functionality
 *	for the soft serial interface to check this.
 * @param bus
 *	The bus that this controller will write/read from. It can only write/read from devices who
 *	have the same bus attached to them. 
 */
CError CCSoftSerialDevSlave( struct CCSoftSerialDev* self, CCSoftSerialDevID id, struct CCSoftSerialBus* bus );


/**
 * @memberof CCSoftSerialDev
 * @details
 *	The the devices ID
 * @param self
 *	The device.
 */
CCSoftSerialDevID CCSoftSerialDev_GetID( struct CCSoftSerialDev* self );

/**
 * @memberof CCSoftSerialDev
 * @details
 *	Get the priority of the device. A slave device will return
 *	a priority of CCSOFTSERIALDEV_SLAVE.
 * @param self
 *	The device.
 */
char CCSoftSerialDev_GetPriority( struct CCSoftSerialDev* self );

/**
 * @memberof CCSoftSerialDev
 * @details
 *	Attempt to select a device on the bus for communication. If the device
 *	was constructed as a slave, this will always fail and return an error.
 *	If the bus is currently being used by another device, it will block
 *	until the bus becomes available, or a timeout occurs. Once the bus 
 *	becomes available, the highest priority device will be given access to the.
 *	When finished with writing/reading from the bus, a call to CCSoftSerialDev_Unselect()
 *	must be made, otherwise the bus will remain locked to other devices. If the device
 *	aleady has access to the bus, this function has no effect.
 * @param self
 *	The device.
 * @param id
 *	The id of the device to write/read from.
 * @param blockTime
 *	The number of ms to block for while waiting for the bus to become available.
 */
CCSoftSerialDevError CCSoftSerialDev_Select( struct CCSoftSerialDev* self, CCSoftSerialDevID id, COSTimemsec blockTime );

/**
 * @memberof CCSoftSerialDev
 * @details
 *	Release the bus when finished writing/reading from it so that another
 *	master device can use it. Returns an error if called by a slave device.
 */
CCSoftSerialDevError CCSoftSerialDev_Unselect( struct CCSoftSerialDev* self );

/**
 * @memberof CCSoftSerialDev
 * @details
 *	Determine if you're selected by a master on the bus
 * @param blockTime
 *	The amount of time in ms to block for waiting to be selected. 
 * @returns
 *	true if selected, false otherwise. 
 */
CBool CCSoftSerialDev_Isselected( struct CCSoftSerialDev* self, COSTimemsec blockTime );

/**
 * @memberof CCSoftSerialDev
 * @details
 *	Write data to the bus according to the buses data size. See 
 *	CCSoftSerialBus() for data size. If you currently don't have
 *	control of the bus this function immediately returns with an error code.
 * @param data
 *	A pointer to the location where a token of data will be
 *	copied onto the bus. 
 * @param blockTime
 *	The amount of time in ms to block for trying to write to the bus. The only
 *	time a block is done is if bus cannot buffer any more
 *	data. Likely due to you writing data too fast for the selected device to
 *	keep up with, or the selected device reading data too sow.
 *	If you don't currently have access to the bus this does nothing.
 *	If for some reason you lose control of the bus (for example, you are a slave and
 *	the master has unselected you), the block will end immediately and the function will
 *	return.
 */
CCSoftSerialDevError CCSoftSerialDev_Write( struct CCSoftSerialDev* self, void* data, COSTimemsec blockTime );

/**
 * @memberof CCSoftSerialDev
 * @details
 *	Read from the bus according to the buses data size. See 
 *	CCSoftSerialBus() for data size. If you currently don't have
 *	control of the bus this function immediately returns with an error code.
 * @param data
 *	Pointer to variable which points to location where data will be
 *	copied to. For exampe, if you have an array, myArray, where data
 *	will be copied to:
 *	@code
 *		char myArray[MSG_LEN];
 *		CCSoftSerial_Read(device, &myArray, COS_NO_BLOCK);
 *	@endcode
 * @param blockTime
 *	The amount of time in ms to block for trying to read from the bus. The only
 *	time a block is done is if the bus currently has no data in it.
 *	If you don't currently have access to the bus this does nothing.
 *	If for some reason you lose control of the bus (for example, you are a slave and
 *	the master has unselected you), the block will end immediately and the function will
 *	return.
 */
CCSoftSerialDevError CCSoftSerialDev_Read( struct CCSoftSerialDev* self, void** data, COSTimemsec blockTime );


#endif /* UTIL_CCSOFTSERIALDEV_H_ */
