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

#include <Class.h>

/**
 * @struct Iterator
 * @brief
 * 		Defines an interface to iterate something.
 * @details
 * 		Defines an interface to iterate something.
 */
Interface( Iterator )
	void (*reset)( self(Iterator) );
	Boolean (*hasNext)( self(Iterator) );
	void* (*next)( self(Iterator) );
EndInterface;

#endif /* INCLUDE_ITERATOR_ITERATOR_H_ */
