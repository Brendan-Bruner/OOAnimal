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

#ifndef UTIL_MEMORY_DYNAMIC_ALLOCATOR_H_
#define UTIL_MEMORY_DYNAMIC_ALLOCATOR_H_

#include "Allocator.h"
/**
 * @struct COTDynamicAllocator
 * @extends COTAllocator
 * @brief
 *		Uses COTMalloc and COTFree to allocate and free memory.
 * @details
 *		Uses COTMalloc and COTFree to allocate and free memory. See Class.h for 
 *		Those methods.
 *		<br>This class is a singleton, use COTDynamicAllocator_GetInstance( ) to
 *		get the instance.
 */
COTClass(COTDynamicAllocator)
COTImplements(COTAllocator)
COTClassEnd

/**
 * @membeof COTDynamicAllocator
 * @brief
 *		Get the singleton instance of COTDynamicAllocator class.
 * @details
 *		Get the singleton instance of COTDynamicAllocator class.
 *		Never returns <b>NULL</b>.
 */
COTDynamicAllocator* COTDynamicAllocator_GetInstance( );

#endif /* UTIL_MEMORY_DYNAMIC_ALLOCATOR_H_ */