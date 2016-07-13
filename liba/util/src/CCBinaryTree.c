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
 * July 13, 2016
 */
/**
 * @file
 */

#define CCBINARY_TREE_ROOT 0

/* The parents index is floor(index/2) where index=1 is used for the
 * first element in the array. To calculate this with index=0 being
 * the first element, we do floor((index+1)/2) - 1.
 */
#define PARENTS_INDEX( index ) ((((index) + 1) >> 1) - 1)
#define LCHILD_INDEX( index ) ((((index) + 1) << 1 ) - 1)
#define RCHILD_INDEX( index ) (((index) + 1) << 1 )

/************************************************************************/
/* Private methods.							*/
/************************************************************************/
static void CCBinaryTree_EncodeSwap( struct CCBinaryTree* self, void* element, void* key )
{
	CAssertObject(self);
	memcpy(self->swap_space_1, element, self->element_size);
	memcpy(self->swap_space_1 + self->element_size, key, self->key_size);
}

static void CCBinaryTree_DecodeSwap( struct CCBinaryTree* self, void* element, void* key )
{
	CAssertObject(self);
	if( element != NULL ) {
		memcpy(element, self->swap_space_1, self->element_size);
	}
	if( key != NULL ) {
		memcpy(key, self->swap_space_1 + self->element_size, self->key_size);
	}
}

static void CCBinaryTree_CacheKey( struct CCBinaryTree* self, size_t index, signed char* key_space )
{
	CAssertObject(self);
	
	CIList_Get(&self->tree_backend.cIList, self->swap_space_1, index);
	CCBinaryTree_DecodeSwap(self, NULL, key_space);
}

static void CCBinaryTree_SwapElements( struct CCBinaryTree* self, size_t indexA, size_t indexB )
{
	CAssertObject(self);

	/* Read out elements at index A and B.
	 */
	CIList_Remove(&self->tree_backend.cIList, self->swap_space_1, indexA);
	CIList_Remove(&self->tree_backend.cIList, self->swap_space_2, indexB);

	/* Write back in different order.
	 */
	CIList_AddAt(&self->tree_backend.cIList, self->swap_space_2, indexA);
	CIList_AddAt(&self->tree_backend.cIList, self->swap_space_1, indexB);
}

static void CCBinaryTree_HeapifyUp( struct CCBinaryTree* self, size_t index )
{
	CAssertObject(self);
	
	for( ;; ) {
		if( index == CCBINARY_TREE_ROOT ) {
			/* This is the root node, nothing to heapify up to.
			 */
			break;
		}

		/* Cache the keys. 
		 */
		CCBinaryTree_CacheKey(self, index, self->key_space_1);
		CCBinaryTree_CacheKey(self, PARENTS_INDEX(index), self->key_space_2);

		/* Compare the keys and swap if needed.
		 */
		if( self->compare(self->key_space_1, self->key_space_2) < 0 ) {			
			/* space1 < space2 => child key < parent's key. 
			 * Need to swap with parent.
			 */
			CCBinaryTree_SwapElements(self, index, PARENTS_INDEX(index));
			index = PARENTS_INDEX(index);
		}
		else {
			/* No need to swap anymore, heap property is satisfied.
			 */
			break;
		}	
	}
}

static void CCBinaryTree_HeapifyDown( struct CCBinaryTree* self, size_t index )
{
	CAssertObject(self);

	size_t child_index;

	for( ;; ) {
		if( LCHILD_INDEX(index) >= self->current_size - 1 ) {
			/* No children to swap with.
			 */
			break;
		}
		else if( LCHILD_INDEX(index) < self->current_size - 1 ) {
			/* Find the child with the smallest key. 
			 */
			CCBinaryTree_CacheKey(self, LCHILD_INDEX(index), self->key_space_1);
			CCBinaryTree_CacheKey(self, RCHILD_INDEX(index), self->key_space_2);
			if( self->compare(self->key_space_1, self->key_space_2) < 0 ) {
				/* space1 < space 2 => lchild key < rchild key.
				 */
				child_index = LCHILD_INDEX(index);
			}
			else {
				child_index = RCHILD_INDEX(index);
			}
		}
		else {
			/* The is only a left child, no right child.
			 */
			child_index = LCHILD_INDEX(index);
		}		
		
		CCBinaryTree_CacheKey(self, child_index, self->key_space_1);
		CCBinaryTree_CacheKey(self, index, self->key_space_2);
		if( self->compare(self->key_space_1, self->key_space_2)  < 0 ) {
			/* space1 < space2 => child index < parent index.
			 * Need to swap child and parent.
			 */
			CCBinaryTree_SwapElements(self, child_index, index);
			index = child_index;
		}
		else {
			/* There is no need to swap. Heap property is satisfied.
			 */
			break;
		}
	}
}


/************************************************************************/
/* Virtual methods.							*/
/************************************************************************/
CITreeError CITree_Push_Def( struct CITree* self_, const void* element, const void* key )
{
	CAssertObject(self_);
	struct CCBinaryTree* self = CCast(self_);

	/* Copy the element and the key into the swap space.
	 */
	CCBinaryTree_EncodeSwap(self, element, key);

	/* Put the combined element/key pair into the list. 
	 */
	CIListError err = CIList_AddAt(&self->tree_backend.cIList, self->swap_space, self->index);
	if( err == CILIST_ERR_FULL ) {
		return CITREE_ERR_FULL;
	}

	/* Move the new element up the heap such that the heap
	 * property remains satisfied.
	 */
	CCBinaryTree_HeapifyUp(self, self->index);

	/* Increment index so that this function will insert into the
	 * next element of the list when its called again.
	 */
	++self->index;

	return CITREE_OK;
}

CITreeError CITree_Pop_Def( struct CITree* self_, void* element )
{
	CAssertObject(self_);
	struct CCBinaryTree* self = CCast(self_);

	return CITree_Delete(&self->cITree, element, CCBINARY_TREE_ROOT);
}

CITreeError CITree_Peek_Def( struct CITree* self_, void* element )
{
	CAssertObject(self_);
	struct CCBinaryTree* self = CCast(self_);

	/* Get the root of the heap.
	 */
	CIListError err = CIList_Get(&self->tree_backend.cIList, self->swap_space, CCBINARY_TREE_ROOT);
	if( err == CILIST_ERR_EMPTY ) {
		return CITREE_ERR_EMPTY;
	}

	/* Copy the data into the provided input. 
	 */
	CCBinaryTree_DecodeSwap(self, element, NULL);
	
	return CITREE_OK;
}

CITreeError CITree_Get_Def( struct CITree* self_, void* element, size_t index )
{
	CAssertObject(self_);
	struct CCBinaryTree* self = CCast(self_);
}

CITreeError CITree_Delete_Def( struct CITree* self_, void* element, size_t index )
{
	CAssertObject(self_);
	struct CCBinaryTree* self = CCast(self_);

	/* Get at the index of the heap.
	 */
	CIListError err = CIList_Remove(&self->tree_backend.cIList, self->swap_space, index);
	if( err == CILIST_ERR_EMPTY ) {
		return CITREE_ERR_EMPTY;
	}

	/* Copy the data into the provided input. 
	 */
	CCBinaryTree_DecodeSwap(self, element, NULL);
	
	/* Check if there are more elements in the heap.
	 * If there are, the heap property needs to be
	 * satisfied. If there are no other elements,
	 * then the heap property will be satisfied.
	 */
	if( self->index <= 1 ) {
		/* This was the only element in the heap.
		 */
		self->index = CCBINARY_TREE_ROOT;
	}
	else {
		/* Place the element at the end of tree into the removed index.
		 */
		--self->index;
		CIList_Remove(&self->tree_backend.cIList, self->swap_space, self->index);
		CIList_AddAt(&self->tree_backend.cIList, self->swap_space, index);
		CCBinaryTree_HeapifyDown(self, index);
	}

	return CITREE_OK;
}


/************************************************************************/
/* Constructor								*/
/************************************************************************/
CError CCBinaryTree
(
	struct CCBinaryTree* self,
	size_t element_size,
	size_t max_size,
	signed char (*compare)( const void*, const void* ),
	size_t key_size
)
{
	CAssertObject(self);

	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCBinaryTree_VTable_Key( ));

	/* Third thing in constructor must be calling interface's constructor. 
	 */
	CInterface(self, &self->cITree, &CCBinaryTree_VTable_Key( )->CITree_VTable);	

	/* Allocate the swap space.
	 */
	self->swap_space = CMalloc(element_size + key_size);
	if( self->swap_space == NULL ) {
		return COBJ_ALLOC_FAIL;
	}
	
	/* Construct the backend of the tree.
	 */
	CError err = CCArrayList(&self->tree_backend, element_size + key_size, max_size);
	if( err != COBJ_OK ) {
		CFree(self->swap_space);
		return err;
	}

	/* Assign the compare method. 
	 */
	self->compare = compare;

	/* Current index is the root (0). 
	 */
	self->index = CCBINARY_TREE_ROOT;

	/* Done.
	 */
	return COBJ_OK;
}
