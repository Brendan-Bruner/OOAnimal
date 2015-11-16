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
 * Oct 23, 2015
 */
#ifndef INCLUDE_QUEUE_QUEUE_H_
#define INCLUDE_QUEUE_QUEUE_H_

#include <Class.h>
#include <Container.h>
#include <ContainerConfig.h>

#if (configUSE_QUEUE == 1)
#if (configUSE_CONTAINER == 1)
/**
 * @struct Queue
 * @extends Container
 */
#endif
/**
 * @struct Queue
 * @extends Object
 * @brief
 * 		Abstract class for all FIFO like containers.
 * @details
 * 		Abstract class for all FIFO like containers.
 * 		Defines an insert, remove, and peek operation. It uses
 * 		the Container interface if configUSE_CONTAINER is set to 1.
 */
CLASS( Queue )
#if (configUSE_CONTAINER == 1)
IMPLEMENTS( Container )
#endif
	VIRTUAL
	(
		Boolean (*insert)( self(Queue), void* );
		void* (*remove)( self(Queue) );
		#if (configQUEUE_PEEK == 1)
			void* (*peek)( self(Queue) );
		#endif
	)
END_CLASS

Boolean QueueInsert( self(Queue), void* );
void* QueueRemove( self(Queue) );
#if (configQUEUE_PEEK == 1)
void* QueuePeek( self(Queue) );
#endif

void createQueue_( self(Queue) );

#endif

#endif /* INCLUDE_QUEUE_QUEUE_H_ */
