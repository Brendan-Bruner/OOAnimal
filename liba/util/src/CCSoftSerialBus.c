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
static CError CCSoftSerialBus_CreateChannel( struct CCSoftSerialBus* self,
					     struct CCThreadedQueue **temp_channel,
					     size_t token_size,
					     size_t channel_size )
{		
	struct CCArrayList* channel_backend;
	struct CCThreadedQueue* channel;

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
	err = CCArrayQueue(channel_channel, token_size, channel_size);
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
					 COS_Timemsec blockTime )
{
}

CCSoftSerialError CCSoftSerialBus_Read( struct CCSoftSerialBus* self,
					struct CCSoftSerialDev* device,
					void** data,
					COS_Timemsec blockTime )
{
}

CCSoftSerialError CCSoftSerialBus_Select( struct CCSoftSerialBus* self,
					  struct CCSoftSerialDev* device,
					  CCSoftSerialDevID id,
					  COS_Timemsec blockTime )
{
}

CCSoftSerialError CCSoftSerialBus_Unselect( struct CCSoftSerialBus* self,
					    struct CCSoftSerialDev* device )
{
}

CCSoftSerialError CCSoftSerialBus_Isselected( struct CCSoftSerialBus* self,
					      struct CCSoftSerialDev* querying_device,
					      COS_Timemsec blockTime )
{
	/* Parameter bounds checks.
	 */
	CAssertObject(self);
	if( querying_device == NULL ) {
		CCSOFTSERIAL_ERR_INV_PARAM;
	}

	pthread_mutex_lock(&self->priv.device_lock);
	for( ;; ) {		
		if( CCSoftSerialDev_GetID(querying_device) == self->priv.slaveID ) {
			pthread_mutex_unlock(&self->priv.device_lock);
			return CCSOFTSERIAL_OK;
		}
		err = pthread_cond_timedwait(&self->priv.select_cond, &self->priv.device_lock, blockTime);
		if( err == TIMED_OUT ) {
			pthread_mutex_unlock(&self->priv.device_lock);
			return CCSOFTSERIAL_ERR_TIMEOUT;
		}
	}
}


/************************************************************************/
/* Overriding 								*/
/************************************************************************/
static void CDestructor( void* self_ )
{
	struct CCSoftSerialBus* self = CCast(self_);

	CFree(self->priv.miso_channel);
	CFree(self->priv.mosi_channel);

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
	CVTable(self, CCSoftSerialBus_GetVtable( ));

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

	/* Initially, the bus is unused.
	 */
	self->priv.master = NULL;
	self->priv.slave = NULL;

	return COBJ_OK;
}

CError CCSoftSerialBusStatic( struct CCSoftSerialBus* self,
			      struct CCThreadedQueue* miso_channel,
			      struct CCThreadedQueue* mosi_channel )
{
	CAssertObject(self);

	/* Construct super class.
	 */
	CObject(&self->cobject);

	/* Bind this classes vtable to the object.
	 */
	CVTable(self, CCSoftSerialBus_GetVtable( ));

	/* Assert non NULL channel inputs. 
	 */
	if( miso_channel == NULL || mosi_channel == NULL ) {
		return COBJ_INV_PARAM;
	}
	self->priv.miso_channel = miso_channel;
	self->priv.mosi_channel = mosi_channel;

	/* Initially, the bus is unused.
	 */
	self->priv.master = NULL;
	self->priv.slave = NULL;

	return COBJ_OK;	
}


