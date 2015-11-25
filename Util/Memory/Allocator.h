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


#ifndef INCLUDE_MEMORY_ALLOCATOR_H_
#define INCLUDE_MEMORY_ALLOCATOR_H_

#include <Class.h>

/**
 * @struct COTAllocator
 * @brief
 *		Defines an interface for allocating and freeing memory.
 * @details
 *		Defines an interface for allocating and freeing memory.
 * @attention
 *		configUSE_COTALLOCATOR must be defined as 1 for inclusion. See MemoryConfig.h.
 */
#define COTAllocatorCast(obj) COTCast(COTAllocator, (obj))
COTInterface(COTAllocator)
	COTVirtual
	(
		void* (*memoryAllocate)( self(COTAllocator), size_t );
		void (*memoryFree)( self(COTAllocator), void* );
	)
COTInterfaceEnd

/**
 * @memberof COTAlloctor
 * @brief
 *		Allocate a block of memory.
 * @details
 *		Allocate a block of memory. The memory allocated must be freed with
 *		COTAllocator_Free( ) when no longer needed.
 * @param bytes
 *		The size in bytes of the memory block to allocate. If 0, <b>NULL</b> will
 *		be returned.
 * @returns
 *		A pointer to the allocated memory. <b>NULL</b> if allocation fails.
 */
void* COTAllocator_Malloc( self(COTAllocator), size_t bytes );

/**
 * @memberof COTAllocator
 * @brief
 *		Free memory allocated by COTAllocator_Free( ).
 * @details
 *		Free memory allocated by COTAllocator_Free( ).
 * @param memory[in]
 *		A pointer to the memory to free.
 */
void COTAllocator_Free( self(COTAllocator), void* memory );

#endif /* INCLUDE_MEMORY_ALLOCATOR_H_ */
