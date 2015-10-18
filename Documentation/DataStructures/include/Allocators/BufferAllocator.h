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
 * Oct 4, 2015
 */
#ifndef INCLUDE_BUFFERALLOCATOR_H_
#define INCLUDE_BUFFERALLOCATOR_H_

#include <Class.h>
#include <traits/TAllocator.h>
#include <LinkedListNode.h>
#include <stdint.h>

Class( BufferAllocator ) Extends( Object ) Uses( TAllocator )
	Private
	(
		LinkedListNode** buffers;
		uint32_t numBuffers;
	);
EndClass;

#endif /* INCLUDE_BUFFERALLOCATOR_H_ */
