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

#include <StandardConfig.h>
#include <Class.h>
#include <Container.h>

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
 */
Class( Queue ) Extends( Object )
#if (configUSE_CONTAINER == 1)
Uses( Container )
#endif
	Boolean (*insert)( self(Queue), void* );
	void* (*remove)( self(Queue) );
#if (configQUEUE_PEEK == 1)
	void* (*peek)( self(Queue) );
#endif
EndClass;


#endif /* INCLUDE_QUEUE_QUEUE_H_ */
