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
 * Aug 12, 2016
 */
/**
 * @file
 */
#ifndef TERM_CCONSOLEIO
#define TERM_CCONSOLEIO

#include <Class.h>
#include <FreeRTOS.h>
#include <semphr.h>

/************************************************************************/
/* Class and vtable decalre.						*/
/************************************************************************/
/**
 * @struct CConsoleIO
 * @ingroup console
 */
struct CConsoleIO
{
	/* Super class must always be first member */
	/* of a C class struct. */
	struct CObject cObject;

	xSemaphoreHandle io_mutex;
};

#endif /* TERM_CCONSOLEIO */
