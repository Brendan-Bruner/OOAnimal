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
/* Iterator Configuration													*/
/****************************************************************************/
/*
 * (0) Does not include COTIterator interface in the build.
 * (1) Includes the COTIterator interface in the build.
 * If this interface is excluded, then all implementing classes
 * are also excluded.
 */
#define configUSE_COTITERATOR 			(1)

/*
 * For the configurations below, configUSE_COTITERATOR must be set to (1),
 * otherwise, they are excluded from the build.
 * The configurations have the following options and effects:
 * (0) Does not include method in build.
 * (1) Includes method in build.
 */

/* COTIterator_Reset( self ): void */
#define configCOTITERATOR_RESET			(1)

/****************************************************************************/
/* Container Configuration													*/
/****************************************************************************/
/*
 * (0) Does not include COTContainer interface in build.
 * (1) Includes COTContainer interface in build.
 * If this interface is excluded from the build then all
 * classes which implement it will still exist, but they won't
 * implement this interface.
 */
#define configUSE_COTCONTAINER 			(1)

/*
 * For the configurations below, configUSE_COTCONTAINER must be set to (1),
 * otherwise, they are excluded from the build.
 * The configurations have the following options and effects:
 * (0) Does not include method in build.
 * (1) Includes method in build.
 */

/* COTContainer_Add( self, void* ): Boolean */
#define configCOTCONTAINER_ADD 			(1)

/* COTContainer_AddAll( self, COTContainer* ): size_t */
/* configUSE_COTITERATOR and configCOTCONTAINER_ITERATOR must be (1) also. */
#define configCOTCONTAINER_ADD_ALL 		(1)

/* COTContainer_Iterator( self ): COTIterator* */
/* configUSE_COTITERATOR must also be set to (1) for inclusion */
#define configCOTCONTAINER_ITERATOR 	(1)

/* COTContainer_Size( self ): size_t */
#define configCOTCONTAINER_SIZE 		(1)

/* COTContainer_Reset( self ): void */
#define configCOTCONTAINER_RESET 		(1)

/* COTContainer_IsEmpty( self ): Boolean */
#define configCOTCONTAINER_IS_EMPTY 	(1)

/* COTContainer_AddCapacity( self, size_t ): size_t */
#define configCOTCONTAINER_ADD_CAPACITY	(1)


/****************************************************************************/
/* Queue Configuration														*/
/****************************************************************************/
/*
 * (0) Does not include abstract COTQueue class in the build.
 * 	   Any subclasses of COTQueue will not be included ether.
 * (1) Includes the abstract COTQueue class in the build.
 * 	   Classes extending COTQueue can be selectively included / excluded
 * Note, the abstract COTQueue class implements the Container interface
 * only if configUSE_CONTAINER is defined as (1).
 */
#define configUSE_COTQUEUE				(1)

 /*
 * For the configurations below, configUSE_COTQUEUE must be set to (1),
 * otherwise, they are excluded from the build.
 * The configurations have the following options and effects:
 * (0) Does not include method in build.
 * (1) Includes method in build.
 */
 /* COTQueue_Peek( ). */
 #define configCOTQUEUE_PEEK			(1)
 /* COTQueue_Size( ). */
 #define configCOTQUEUE_SIZE			(1)

 /*
 * (0) Does not include COTLinkedQueue class in the build.
 * 	   Any subclasses of COTLinkedQueue will not be included ether.
 * (1) Includes the COTLinkedQueue class in the build.
 * 	   Classes extending COTLinkedQueue can be selectively included / excluded
 */
#define configUSE_COTLINKEDQUEUE		(1)


#endif /* INCLUDE_STANDARDCONFIG_H_ */
