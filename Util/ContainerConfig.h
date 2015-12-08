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
#ifndef UTIL_CONTAINER_CONTAINERCONFIG_H_
#define UTIL_CONTAINER_CONTAINERCONFIG_H_


/****************************************************************************/
/* Iterator Configuration													*/
/****************************************************************************/
/*
 * (0) Does not include CIterator interface in the build.
 * (1) Includes the CIterator interface in the build.
 * If this interface is excluded, then all implementing classes
 * are also excluded.
 */
#define configUSE_CITERATOR 			(1)


/****************************************************************************/
/* Container Configuration													*/
/****************************************************************************/
/*
 * (0) Does not include CContainer interface in build.
 * (1) Includes CContainer interface in build.
 * If this interface is excluded from the build then all
 * classes which implement it will still exist, but they won't
 * implement this interface.
 */
#define configUSE_CCONTAINER 			(1)

/*
 * Note, CContainer_GetIterator( self ): struct CIterator* is only 
 * included in the interface when configUSE_CITERATOR is set to 1.
 *
 * Note, CContainer_AddAll( self, struct CContaienr* ): size_t is only
 * included in the interface when configUSE_CITERATOR is set to 1.
 */

/*
 * For the configurations below, configUSE_CCONTAINER must be set to (1),
 * otherwise it has no effect.
 * (0) Does not includes the methods in the interface.
 * (1) Includes the methods below in the interface.
 * CContainer_Size( self ): size_t
 * CContainer_Reset( self ): void
 * CContainer_AddCapacity( self, size_t ): size_t
 */
#define configCCONTAINER_EXTRA 			(1)


/****************************************************************************/
/* Queue Configuration														*/
/****************************************************************************/
/*
 * (0) Does not include abstract CQueue class in the build.
 * 	   Any subclasses of CQueue will not be included ether.
 * (1) Includes the abstract CQueue class in the build.
 * 	   Classes extending CQueue can be selectively included / excluded
 * Note, the abstract CQueue class implements the Container interface
 * only if configUSE_CONTAINER is defined as (1).
 */
#define configUSE_CQUEUE				(1)

 /*
  * For the configuration below, configUSE_CQUEUE must be set to (1),
  * otherwise, it has no effect.
  * Setting this to (1) will include a size method with the queue class.
  * Note, if using CContainer and using the extra, this method is redundent.
  * By default, it is only set to (1) when CContainer_Size( self ): size_t
  * is excluded from the build.
  * (0) Does not include method in build.
  * (1) Includes method in build.
  * CQueue_Size( self ): size_t.
  */
#if (configUSE_CCONTAINER == 1 && configCCONTAINER_EXTRA == 1)
#define configCQUEUE_SIZE			(0)
#else
#define configCQUEUE_SIZE			(1)
#endif

 /*
 * (0) Does not include CLinkedQueue class in the build.
 * 	   Any subclasses of CLinkedQueue will not be included ether.
 * (1) Includes the CLinkedQueue class in the build.
 * 	   Classes extending CLinkedQueue can be selectively included / excluded
 */
#define configUSE_CLINKEDQUEUE		(1)


#endif /* UTIL_CONTAINER_CONTAINERCONFIG_H_ */
