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
 * Oct 15, 2015
 */
#ifndef INCLUDE_BUFFERS_QUEUE_H_
#define INCLUDE_BUFFERS_QUEUE_H_

#include "Buffer.h"

Class( Queue ) Extends( Buffer )
	Private
	(
		Boolean isFixedSized;
		TAllocator* allocator;
	);
	SoftOverride
	(
		/* Destructor. */
		void (*destroy)( self(Object) );
	);
EndClass;

Queue* createFixedQueue( self(Queue), TAllocator*, uint32_t );
Queue* createExpandingQueue( self(Queue), TAllocator*, uint32_t );

#endif /* INCLUDE_BUFFERS_QUEUE_H_ */
