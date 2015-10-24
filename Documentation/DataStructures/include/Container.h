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
#ifndef INCLUDE_CONTAINER_H_
#define INCLUDE_CONTAINER_H_

#include <StandardConfig.h>
#include <Class.h>
#include <stdint.h>

#if (configUSE_CONTAINER == 1)
#if (configCONTAINER_ITERATOR == 1)
#include <Iterator/Iterator.h>
#endif
/**
 * @struct Container
 * @brief
 * 		Defines an interface which all container data structures implement.
 * @details
 * 		Defines an interface which all container data structures implement.
 * 		containers are data structures like queues and lists.
 */
Interface( Container )
#if (configCONTAINER_ADD == 1)
	Boolean (*add)( self(Container), void* );
#endif
#if (configCONTAINER_ADD_ALL == 1 )
	uint32_t (*addAll)( self(Container), Container* );
#endif
#if (configCONTAINER_ITERATOR == 1 )
	Iterator* (*iterator)( self(Container) );
#endif
	uint32_t (*size)( self(Container) );
	void (*reset)( self(Container) );
	Boolean (*isEmpty)( self(Container) );
	uint32_t (*addCapacity)( self(Container), uint32_t );
EndInterface;
#endif

#endif /* INCLUDE_CONTAINER_H_ */
