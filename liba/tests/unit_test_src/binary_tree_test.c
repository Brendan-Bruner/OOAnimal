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

#include <unit.h>
#include <CCBinaryTree.h>

#define TREE_NODE_SIZE sizeof(int)
#define TREE_MAX_SIZE 8
#define TREE_KEY_SIZE sizeof(int)
#define INITIAL_KEY 0

struct CCBinaryTree* tree;
struct CCBinaryTree dynamic_tree;

static signed char compare( const void* key1_, const void* key2_ )
{
	int key1 = *((int*) key1_);
	int key2 = *((int*) key2_);

	return key1 < key2 ? -1 : (key1 > key2 ? 1 : 0);
}

TEST_SETUP( )
{
	CCBinaryTree(&dynamic_tree,
		     TREE_NODE_SIZE,
		     TREE_MAX_SIZE,
		     compare,
		     TREE_KEY_SIZE);
}

TEST_TEARDOWN( )
{
	CDestroy(&dynamic_tree);
}

TEST(push)
{
	int item = 0;
	int key = INITIAL_KEY + 1;
	CITreeError err;

	/* Empty tree, push an item into it.
	 */
	err = CITree_Push(&tree->cITree, &item, &key);
	ASSERT(err == CITREE_OK, "Error %d inserting into empty tree", err);

	/* Insert two item's that will be children of the above insert. */
	key += 2;
	++item;
	err = CITree_Push(&tree->cITree, &item, &key);
	ASSERT(err == CITREE_OK, "Error %d inserting child 1", err);
	++key;
	++item;
	err = CITree_Push(&tree->cITree, &item, &key);
	ASSERT(err == CITREE_OK, "Error %d inserting child 2", err);

	/* Insert a fourth element that gets heapified up only one time.
	 */
	key = INITIAL_KEY + 2;
	++item;
	err = CITree_Push(&tree->cITree, &item, &key);
	ASSERT(err == CITREE_OK, "Error %d with heapify before root", err);

	/* Insert a fifth element that gets heapified up to the root.
	 */
	key = INITIAL_KEY;
	++item;
	err = CITree_Push(&tree->cITree, &item, &key);
	ASSERT(err == CITREE_OK, "Error %d with heapify up to root", err);

	/* Fill the tree and assert it returns a tree full error.
	 */
	int i;
	for( i = CITree_Size(&tree->cITree); i < TREE_MAX_SIZE; ++i ) {
		++item;
		++key;
		err = CITree_Push(&tree->cITree, &item, &key);
		ASSERT(err == CITREE_OK, "Error %d inserting during push %d", err, i);
	}
	err = CITree_Push(&tree->cITree, &item, &key);
	ASSERT(err == CITREE_ERR_FULL, "No full error on full tree, got %d", err);
}

TEST(get)
{
	int item = 299;
	int key = 0;
	CITreeError err;

	/* Empty tree, get should return an error.
	 */
	err = CITree_Get(&tree->cITree, &item, 0);
	ASSERT(err == CITREE_ERR_EMPTY, "No empty error pulling from empty tree, got %d", err);

	/* Put an itme into tree and get it.
	 */
	CITree_Push(&tree->cITree, &item, &key);
	item = 0;
	err = CITree_Get(&tree->cITree, &item, 0);
	ASSERT(err == CITREE_OK, "Error %d getting from tree", err);
	ASSERT(item == 299, "Got wrong item, %d, from tree", item);
}

TEST(remove)
{
	int item = 0;
	int key = 0;
	CITreeError err;
	size_t size;

	/* Tree is empty, delete should return empty error. 
	 */
	err = CITree_Delete(&tree->cITree, &item, 0);
	ASSERT(err == CITREE_ERR_EMPTY, "No empty error deleting from epty tree, got %d", err);

	/* Insert an element, then assert tree is empty after removing it.
	 */
	item = 1;
	CITree_Push(&tree->cITree, &item, &key);
	item = 0;
	err = CITree_Delete(&tree->cITree, &item, 0);
	size = CITree_Size(&tree->cITree);
	ASSERT(err == CITREE_OK, "Got err %d deleting tree of size one", err);
	ASSERT(item == 1, "Removed wrong item from tree, got %d", item);
	ASSERT(size == 0, "Tree should be size zero, not %zu", size);

	/* Build a tree to test a dimension of heapify.
	 */
	item = 0;
	key = 0;
	CITree_Push(&tree->cITree, &item, &key);
	++item;
	key = 4;
	CITree_Push(&tree->cITree, &item, &key);
	++item;
	key = 7;
	CITree_Push(&tree->cITree, &item, &key);
	++item;
	key = 6;
	CITree_Push(&tree->cITree, &item, &key);
	++item;
	key = 5;
	CITree_Push(&tree->cITree, &item, &key);

	/* When we remove the root now, key 5 should be heapified
	 * to a child of the root with one child.
	 */
	err = CITree_Delete(&tree->cITree, &item, 0);
	ASSERT(err == CITREE_OK, "heapify test 1: incorrectly got err %d", err);
	ASSERT(item == 0, "heapify test 1: incorrectly deleted item value %d", item);

	/* Key 5 should be at index 1 now.
	 */
	CITree_Get(&tree->cITree, &item, 1);
	ASSERT(item == 4," heapify test 1: key 5 item's value is incorrectly %d", item);
}

TEST(one_node)
{
}

TEST(no_nodes)
{
}

TEST(normal_operation)
{
}

TEST_SUITE(binary_tree)
{
	tree = &dynamic_tree;
	
	ADD_TEST(push);
	ADD_TEST(get);
	ADD_TEST(remove);
	ADD_TEST(one_node);
	ADD_TEST(no_nodes);
	ADD_TEST(normal_operation);
}
