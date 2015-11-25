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
 * Nov. 2015
 */

#ifndef UTIL_MEMORY_CONFIG_H_
#define UTIL_MEMORY_CONFIG_H_

/****************************************************************************/
/* Allocator Configuration													*/
/****************************************************************************/
/*
 * (0) Does not include COTBlockAllocator class in the build.
 * (1) Includes the COTBlockAllocator class in the build.
 */
#define configUSE_COTBLOCKALLOCATOR				(1)

#endif /* UTIL_MEMORY_CONFIG_H_ */
