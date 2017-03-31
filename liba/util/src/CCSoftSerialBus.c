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
#include <CCSoftSerialBus.h>


/************************************************************************/
/* Private Class Methods						*/
/************************************************************************/
static CError CCSoftSerialBus_CreateLocks( struct CCSoftSerialBus* self )
{
	CAssertObject(self);

	if( pthread_mutex_init(&self->priv.device_lock, NULL) != 0 ) {
		return COBJ_EXT_FAIL;
	}
	if( pthread_cond_init(&self->priv.select_cond, NULL) != 0 ) {
		pthread_mutex_destroy(&self->priv.device_lock);
		return COBJ_EXT_FAIL;
	}
	return COBJ_OK;
}
static CError CCSoftSerialBus_CreateChannel( struct CCSoftSerialBus* self,
					     struct CCThreadedQueue **temp_channel,
					     size_t token_size,
					     size_t channel_size )
{		
	struct CCArrayQueue* channel_backend;
	struct CCThreadedQueue* channel;
	CError err;

	CAssertObject(self);
	if( temp_channel == NULL || *temp_channel == NULL ) {
		return COBJ_INV_PARAM;
	}
	
	/* Create the backend.
	 */
	channel_backend = CMalloc(sizeof(*channel_backend));
	if( channel_backend == NULL ) {
		return COBJ_ALLOC_FAIL;
	}
	err = CCArrayQueue(channel_backend, token_size, channel_size);
	if( err != COBJ_OK ) {
		CFree(channel_backend);
		return err;
	}
	CDynamic(channel_backend);

	/* Create the thread safe channel
	 */
	channel = CMalloc(sizeof(*channel));
	if( channel == NULL ) {
		CDestroy(channel_backend);
		return COBJ_ALLOC_FAIL;
	}
	err = CCThreadedQueue(channel, &channel_backend->ciqueue);
	if( err != COBJ_OK ) {
		CDestroy(channel_backend);
		CFree(channel);
		return err;
	}
	CDynamic(channel);

	*temp_channel = channel;
	return COBJ_OK;
}


/************************************************************************/
/* Class Methods							*/
/************************************************************************/
CCSoftSerialError CCSoftSerialBus_Write( struct CCSoftSerialBus* self,
					 struct CCSoftSerialDev* device,
					 void* data,
					 COS_Timemsec block_time )
{
	(void) self;
	(void) device;
	(void) data;
	(void) block_time;
}

CCSoftSerialError CCSoftSerialBus_Read( struct CCSoftSerialBus* self,
					struct CCSoftSerialDev* device,
					void** data,
					COS_Timemsec block_time )
{
	(void) self;
	(void) device;
	(void) data;
	(void) block_time;
}

CCSoftSerialError CCSoftSerialBus_Select( struct CCSoftSerialBus* self,
					  struct CCSoftSerialDev* querying_device,
					  CCSoftSerialDevID slave_id,
					  COS_Timemsec block_time )
{
	struct timespec abstime;
	CCSoftSerialDevID master_id;
	int err;
	CAssertObject(self);

	if( querying_device == NULL ) {
		return CCSOFTSERIAL_ERR_INV_PARAM;
	}

	master_id = CCSoftSerialDev_GetID(querying_device);
	if( master_id == CCSOFTSERIALDEV_SLAVE ) {
		/* Slave device attempting to make a selection.
		 */
		return CCSOFTSERIAL_ERR_PRIV;
	}

	/* At this point, the querying device is a valid master. Aquire 
	 * mututal exclusion on member variables before checking for
	 * bus activity.
	 */
	if( block_time == COS_BLOCK_FOREVER ) {
		pthread_mutex_lock(&self->priv.device_lock);
	}
	else {
		clock_gettime(CLOCK_REALTIME, &abstime);
		abstime.tv_sec += block_time / MS_PER_SECOND;
		abstime.tv_nsec += (block_time % MS_PER_SECOND) * NS_PER_MS;

		if( pthread_mutex_timedlock(&self->priv.device_lock, &abstime) != 0 ) {
			/* Timed out. */
			return CCSOFTSERIAL_ERR_TIMEOUT;
		}		
	}

	/* Have mutual exclusion, check for bus activity.
	 */
	for( ;; ) {
		if( self->priv.masterID == CCSOFTSERIAL_NO_ID ) {
			/* No bus activity, do the selection.
			 */
			self->priv.masterID = master_id;
			self->priv.slaveID = slave_id;
			pthread_cond_broadcast(&self->priv.select_cond);
			pthread_mutex_unlock(&self->priv.device_lock);
			return CCSOFTSERIAL_OK;
		}

		/* Wait until signalled the bus is empty. 
		 */
		if( block_time == COS_BLOCK_FOREVER ) {
			pthread_cond_wait(&self->priv.idle_cond, &self->priv.device_lock);
		}
		else {
			err = pthread_cond_timedwait(&self->priv.idle_cond, &self->priv.device_lock, &abstime);
			if( err != 0 ) {
				/* Timed out.
				 */
				pthread_mutex_unlock(&self->priv.device_lock);
				return CCSOFTSERIAL_ERR_TIMEOUT;
			}
		}
	}
}

CCSoftSerialError CCSoftSerialBus_Unselect( struct CCSoftSerialBus* self,
					    struct CCSoftSerialDev* querying_device )
{
	CCSoftSerialError err;
	CAssertObject(self);

	if( querying_device == NULL ) {
		return CCSOFTSERIAL_ERR_INV_PARAM;
	}

	pthread_mutex_lock(&self->priv.device_lock);
	if( CCSoftSerialDev_GetID(querying_device) == self->priv.masterID ) {
		/* The querying device is indeed the current bus master.
		 * release the bus and signal the idle bus condition.
		 */
		self->priv.slaveID = CCSOFTSERIAL_NO_ID;
		self->priv.masterID = CCSOFTSERIAL_NO_ID;
		pthread_cond_broadcast(&self->priv.idle_cond);
		err = CCSOFTSERIAL_OK;
	}
	else {
		err = CCSOFTSERIAL_ERR_CONTENTION;
	}
	pthread_mutex_unlock(&self->priv.device_lock);

	return err;
}

CCSoftSerialError CCSoftSerialBus_Isselected( struct CCSoftSerialBus* self,
					      struct CCSoftSerialDev* querying_device,
					      COS_Timemsec block_time )
{
	struct timespec abstime;
	int err;
	
	/* Parameter bounds checks.
	 */
	CAssertObject(self);
	if( querying_device == NULL ) {
		return CCSOFTSERIAL_ERR_INV_PARAM;
	}


	/* Get mutual exclusion on member variables.
	 */
	if( block_time == COS_BLOCK_FOREVER ) {
		pthread_mutex_lock(&self->priv.device_lock);
	}
	else {
		clock_gettime(CLOCK_REALTIME, &abstime);
		abstime.tv_sec += block_time / MS_PER_SECOND;
		abstime.tv_nsec += (block_time % MS_PER_SECOND) * NS_PER_MS;

		if( pthread_mutex_timedlock(&self->priv.device_lock, &abstime) != 0 ) {
			/* Timed out. */
			return CCSOFTSERIAL_ERR_TIMEOUT;
		}		
	}
		
	for( ;; ) {
		/* If the current slave is the same as the querying device, there is
		 * nothing to do but return sucessfully.
		 */
		if( CCSoftSerialDev_GetID(querying_device) == self->priv.slaveID ) {
			pthread_mutex_unlock(&self->priv.device_lock);
			return CCSOFTSERIAL_OK;
		}

		/* The querying device is not the current slave. Wait until we're signalled
		 * that a new slave has been selected.
		 */
		if( block_time == COS_BLOCK_FOREVER ) {
			pthread_cond_wait(&self->priv.select_cond, &self->priv.device_lock);
		}
		else {
			err = pthread_cond_timedwait(&self->priv.select_cond, &self->priv.device_lock, &abstime);
			if( err != 0 ) {
				/* Timed out.
				 */
				pthread_mutex_unlock(&self->priv.device_lock);
				return CCSOFTSERIAL_ERR_TIMEOUT;
			}
		}
	}
}


/************************************************************************/
/* Overriding 								*/
/************************************************************************/
static void CDestructor( void* self_ )
{
	struct CCSoftSerialBus* self = CCast(self_);

	CDestroy(self->priv.miso_channel);
	CDestroy(self->priv.mosi_channel);
	pthread_mutex_destroy(&self->priv.device_lock);
	pthread_cond_destroy(&self->priv.select_cond);

	/* Call super's destructor
	 */
	const struct CCSoftSerialBus_VTable* vtable = CGetVTable(self);
	vtable->cobject->CDestructor(self);
}


/************************************************************************/
/* vtable key								*/
/************************************************************************/
const struct CCSoftSerialBus_VTable* CCSoftSerialBus_GetVTable( )
{
	static struct CCSoftSerialBus_VTable vtable;

	/* Inherit super's methods
	 */
	vtable.cobject_override = *CObject_GetVTable( );

	/* Override Destructor
	 */
	vtable.cobject_override.CDestructor = CDestructor;

	/* Keep reference to super's original vtable.
	 * so that we can cascade the destructor.
	 */
	vtable.cobject = CObject_GetVTable( );
	
	/* Return pointer to vtable. */
	return &vtable;
}


/************************************************************************/
/* Constructors Methods							*/
/************************************************************************/
CError CCSoftSerialBus( struct CCSoftSerialBus* self,
			size_t token_size,
			size_t channel_size )
{
	struct CCThreadedQueue* temp_channel;
	CError err;
	
	CAssertObject(self);

	/* Construct super class.
	 */
	CObject(&self->cobject);

	/* Bind this classes vtable to the object.
	 */
	CVTable(self, CCSoftSerialBus_GetVTable( ));

	/* Create miso channel.
	 */
	err = CCSoftSerialBus_CreateChannel(self, &temp_channel, token_size, channel_size);
	if( err != COBJ_OK ) {
		return err;
	}
	self->priv.miso_channel = temp_channel;

	/* Create mosi channel.
	 */
	err = CCSoftSerialBus_CreateChannel(self, &temp_channel, token_size, channel_size);
	if( err != COBJ_OK ) {
		CDestroy(self->priv.miso_channel);
		return err;
	}
	self->priv.mosi_channel = temp_channel;

	err = CCSoftSerialBus_CreateLocks(self);
	if( err != COBJ_OK ) {
		CDestroy(self->priv.mosi_channel);
		CDestroy(self->priv.miso_channel);
		return err;
	}
	
	/* Initially, the bus is unused.
	 */
	self->priv.masterID = CCSOFTSERIAL_NO_ID;
	self->priv.slaveID = CCSOFTSERIAL_NO_ID;

	return COBJ_OK;
}

CError CCSoftSerialBusStatic( struct CCSoftSerialBus* self,
			      struct CCThreadedQueue* miso_channel,
			      struct CCThreadedQueue* mosi_channel )
{
	CError err;
	CAssertObject(self);

	/* Construct super class.
	 */
	CObject(&self->cobject);

	/* Bind this classes vtable to the object.
	 */
	CVTable(self, CCSoftSerialBus_GetVTable( ));

	/* Assert non NULL channel inputs. 
	 */
	if( miso_channel == NULL || mosi_channel == NULL ) {
		return COBJ_INV_PARAM;
	}
	self->priv.miso_channel = miso_channel;
	self->priv.mosi_channel = mosi_channel;

	err = CCSoftSerialBus_CreateLocks(self);
	if( err != COBJ_OK ) {
		return err;
	}
	
	/* Initially, the bus is unused.
	 */
	self->priv.masterID = CCSOFTSERIAL_NO_ID;
	self->priv.slaveID = CCSOFTSERIAL_NO_ID;

	return COBJ_OK;	
}


