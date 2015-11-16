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

#include "Class.h"
#include <stdlib.h>

COTMallocType COTMalloc = COT_MALLOC;
COTFreeType COTFree = COT_FREE;

static void virtualDestructor( self(COT_CLASS_OBJECT) )
{
	COTMemberOf( COT_CLASS_OBJECT );
}
void COTCreateObject( self(COT_CLASS_OBJECT) )
{
	COT_CLASS_OBJECT* self = self_;
	COTLinkVirtual(virtualDestructor);
}
