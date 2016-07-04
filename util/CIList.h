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
 * Jun 24, 2016
 */
#ifndef UTIL_CILIST_H_
#define UTIL_CILIST_H_

#include <Class.h>
#include <stdlib.h>

typedef enum
{
	CILIST_OK = 0,
	CILIST_ERR_FULL = 1,
	CILIST_ERR_EMPTY = 2,
	CILIST_ERR_INDEX = 3
} CIListError;

/************************************************************************/
/* Interface declaration.						*/
/************************************************************************/
struct CIList
{
	/* CInterface must always be first member of */
	/* an interface's struct .*/
	struct CInterface interface;
};

struct CIList_VTable
{
	CIListError (*add)( struct CIList*, void* );
	CIListError (*addAt)( struct CIList*, void*, size_t );
	CIListError (*get)( struct CIList*, void*, size_t );
	CIListError (*remove)( struct CIList*, void*, size_t );
	void (*clear)( struct CIList* );
	size_t (*size)( struct CIList* );
	size_t (*maxSize)( struct CIList* );
};

/**
 * @memberof struct ICList
 * @details
 * 	Add parameter element, by copy, to the first empty spot in the list. If 
 *	there are no empty spots, the list will be resized or an error returned.
 * @param self
 *	The list.
 * @param element
 *	A pointer to the data which will be copied into the list.
 * @returns
 *	CILIST_OK:		The element was inserted into the list
 *	CILIST_ERR_FULL:	No room in the list, and if a resize was attempted
 *				it failed. the element wasn't added.
 */
static inline CIListError CIList_Add( struct CIList* self, void* element )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->add);
	return ((struct CIList_VTable*) CGetVTable(self))->add(self, element);
}

/**
 * @memberof struct CIList
 * @details
 *	Insert the element into the specefied index of the list. If there is already something
 *	at that index in the list, it gets overwritten.
 * @param self
 * 	The list.
 * @param element
 *	Pointer to the data that is copied into the list.
 * @param index
 *	The index in the list to copy the data.
 * @returns
 *	CILIST_OK:		Element was inserted.
 *	CILIST_ERR_INDEX:	Index out of bounds.
 */
static inline CIListError CIList_AddAt( struct CIList* self, void* element, size_t index )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->addAt);
	return ((struct CIList_VTable*) CGetVTable(self))->addAt(self, element, index);
}

/**
 * @memberof struct CIList
 * @details
 *	Get an element from the list at the specified index. The element is not removed
 *	from the list.
 * @param self
 *	The list.
 * @param element
 *	Data will be copied from the list into the location pointed to by this. If a NULL
 *	pointer is provided, no data is copied.
 * @param index
 *	The location in the list to get an item from.
 * @returns
 *	CILIST_OK:		Retrieved the element.
 *	CILIST_ERR_EMPTY:	Nothing at the location given by parameter index. 
 *	CILIST_ERR_INDEX:	The index is out of bounds, not a valid index.
 */	
static inline CIListError CIList_Get( struct CIList* self, void* element, size_t index )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->get);
	return ((struct CIList_VTable*) CGetVTable(self))->get(self, element, index);
}

/**
 * @memberof struct CIList
 * @details
 *	Remove an element from the list at the specified index.
 * @param self
 *	The list.
 * @param element
 *	Pointer to location where data removed from the list will be copied into. If this is
 *	a NULL pointer, no data is copied.
 * @param index
 *	Index in the list to remove data. 
 * @returns
 *	CILIST_OK:		Element removed from given index.
 *	CILIST_ERR_EMPTY:	No element at the given index.
 *	CILIST_ERR_INDEX:	Index is out of bounds.
 */
static inline CIListError CIList_Remove( struct CIList* self, void* element, size_t index )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->remove);
	return ((struct CIList_VTable*) CGetVTable(self))->remove(self, element, index);
}

static inline void CIList_Clear( struct CIList* self)
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->clear);
	((struct CIList_VTable*) CGetVTable(self))->clear(self);
}

static inline size_t CIList_Size( struct CIList* self )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->size);
	return ((struct CIList_VTable*) CGetVTable(self))->size(self);
}

static inline size_t CIList_MaxSize( struct CIList* self )
{
	CAssertObject(self);
	CAssertVirtual(((struct CIList_VTable*) CGetVTable(self))->maxSize);
	return ((struct CIList_VTable*) CGetVTable(self))->maxSize(self);
}

#endif /* UTIL_CILIST_H_ */
