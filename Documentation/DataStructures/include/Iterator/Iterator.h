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
#ifndef INCLUDE_ITERATOR_ITERATOR_H_
#define INCLUDE_ITERATOR_ITERATOR_H_

#include <StandardConfig.h>
#include <Class.h>

#if (configUSE_ITERATOR == 1 )
/**
 * @struct Iterator
 * @brief
 * 		Defines an interface to iterate something.
 * @details
 * 		Defines an interface to iterate something. The behaviour each
 * 		method must have by implementing classes is described bellow.
 * @var Iterator::reset
 * 		@code
 * 			void reset( self );
 * 		@endcode
 * 		Resets the iterator to start iterating from the beginning.
 * @var Iterator::hasNext( self );
 * 		@code
 * 			Boolean hasNext( self );
 * 		@endcode
 * 		Returns <b>true</b> if the iterator has more elements to iterate
 * 		over, <b>false</b> otherwise.
 * @var Iterator::next
 * 		@code
 * 			void* next( self );
 * 		@endcode
 * 		Returns the next element in the iteration. NULL if there are
 * 		no more elements.
 */
Interface( Iterator )
#if (configITERATOR_RESET == 1)
	void (*reset)( self(Iterator) );
#endif
#if (configITERATOR_HAS_NEXT == 1)
	Boolean (*hasNext)( self(Iterator) );
#endif
	void* (*next)( self(Iterator) );
EndInterface;
#endif

#endif /* INCLUDE_ITERATOR_ITERATOR_H_ */
