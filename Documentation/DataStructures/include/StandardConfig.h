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
#ifndef INCLUDE_STANDARDCONFIG_H_
#define INCLUDE_STANDARDCONFIG_H_


/****************************************************************************/
/* Container Configuration													*/
/****************************************************************************/
/*
 * (0) Does not include Container interface in build.
 * (1) Includes Container interface in build.
 */
#define configUSE_CONTAINER 			(1)
/*
 * For the configurations below, configUSE_CONTAINER must be set to (1),
 * otherwise, they are excluded from the build.
 * The configurations have the following options and effects:
 * (0) Does not include method in build.
 * (1) Includes method in build.
 */
/* Container::add( element: void* ): Boolean */
#define configCONTAINER_ADD 			(1)
/* Container::addAll( container: Container* ): uint32_t */
#define configCONTAINER_ADD_ALL 		(1)
/* Container::iterator( ): Iterator* */
#define configCONTAINER_ITERATOR 		(1)
/* Container::size( ): uint32_t */
#define configCONTAINER_SIZE 			(1)
/* Container::reset( ): void */
#define configCONTAINER_RESET 			(1)
/* Container::isEmpty( ): Boolean */
#define configCONTAINER_IS_EMPTY 		(1)
/* Container::addCapacity( capacity: uint32_t ): uint32_t */
#define configCONTAINER_ADD_CAPACITY	(1)

#endif /* INCLUDE_STANDARDCONFIG_H_ */
