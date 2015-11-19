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


#ifndef INCLUDE_TYPE_STRING_H_
#define INCLUDE_TYPE_STRING_H_

#include "TypeConfig.h"

#if (configUSE_COTSTRING == 1)
 #include <Class.h>
/**
 * @struct COTString
 * @brief
 *		Immutable string class.
 * @details
 *		Immutable string class.
 */
COTClass(COTString)
	COTOverride
	(
		COTDestructor( );
	)
	struct
	{
		size_t length;
		#if (configUSE_COTSTRING_DYNAMIC == 1)
		char* string;
		#else
		char string[configCOTSTRING_LENGTH];
		#endif
	}_; /* Private data. */
COTClassEnd

#if (configCOTSTRING_SUBSTRING == 1)
COTString* COTString_SubstringNew( self(COTString), size_t start, size_t end );
COTString* COTString_Substring( self(COTString), COTString* insertTo, size_t start, size_t end );
#endif /* configCOTSTRING_SUBSTRING */
#if (configCOTSTRING_APPEND == 1)
COTString* COTString_AppendNew( self(COTString), COTString* appendString );
COTString* COTString_AppendNewChar( self(COTString), COTString* appendTo, char const* appendChar );
COTString* COTString_Append( self(COTString), COTString* appendTo, COTString* appendString );
COTString* COTString_AppendChar( self(COTString), char const* appendChar );
#endif /* configCOTSTRING_APPEND */
#if (configCOTSTRING_PREPEND == 1)
COTString* COTString_PrependNew( self(COTString), COTString* prependString );
COTString* COTString_PrependNewChar( self(COTString), char const* prependChar );
COTString* COTString_Prepend( self(COTString), COTString* prependTo, COTString* prependString );
COTString* COTString_PrependChar( self(COTString), COTString* prependTo, char const* prependChar );
#endif /* configCOTSTRING_PREPEND */
char const* COTString_ToChar( self(COTString) );
char* COTString_ToCharCopyNew( self(COTString) );
char*  COTString_ToCharCopy( self(COTString), char* copyTo, size_t charArrayLength );
size_t COTString_Length( self(COTString) );

void COTStringCopy( self(COTString), Boolean* status, COTString* original );
void COTStringNChar( self(COTString), Boolean* status, char const* charArray, size_t charArrayLength );
void COTStringChar( self(COTString), Boolean* status, char const* charArray );

#endif /* configUSE_COTSTRING */
#endif /* INCLUDE_TYPE_STRING_H_ */