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

#ifndef UTIL_CCBINARYTREE_H_
#define UTIL_CCBINARYTREE_H_

#include <CITree.h>
#include <CCArrayList.h>

/************************************************************************/
/* Class and vtable decalre.						*/
/************************************************************************/
/**
 * @struct CCBinaryTree
 * @extends CITree
 * @ingroup Trees
 * @brief
 *	Implements the CITree interface with a binaray tree/heap.
 */
struct CCBinaryTree
{
	/* Super class must always be first member */
	/* of a C class struct. */
	struct CObject cObject;

	/* Implementing the CITree interface. */
	struct CITree cITree;

	/* Private data. */	
	struct CCArrayList tree_backend;
	unsigned char* swap_space_1;
	unsigned char* swap_space_2;
	unsigned char* key_space_1;
	unsigned char* key_space_1;
	signed char (*compare)(const void*, const void*);
	size_t index;
	size_t element_size;
	size_t key_size;
};

/**
 * @ingroup VTable
 * @brief
 *	CCBinaryTree's vtable declaration.
 */
struct CCBinaryTree_VTable
{
	/* Space for a copy of the super class' virtual table must  */
	/* be the first member of a class virtual table declaration. */
	struct CObject_VTable  CObject_VTable;

	/* Since we are overriding the destructor, we need to keep */
	/* keep a reference to the super class' implementation of */
	/* the destructor. */
	const struct CObject_VTable* CObject_VTable_Ref;

	/* Space for a copy of the implemented interface's virtual table */
	struct CITree_VTable CITree_VTable;
};

/**
 * @memberof CCBinaryTree
 * @ingroup VTable
 * @details
 *	Get vtable reference for CCBinaryTree class.	
 */
const struct CCBinaryTree_VTable* CCBinaryTree_Get_Key( );
	

/************************************************************************/
/* Constructor								*/
/************************************************************************/
/**
 * @memberof CCBinaryTree
 * @constructor
 * @details
 *	Construct a binary tree.
 */
CError CCBinaryTree
(
	struct CCBinaryTree* self,
	size_t element_size,
	size_t max_size,
	signed char (*compare)( const void*, const void* ),
	size_t key_size
);


#endif /* UTIL_CCBINARYTREE_H_ */
