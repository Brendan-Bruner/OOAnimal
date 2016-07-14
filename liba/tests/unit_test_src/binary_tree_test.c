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
}

TEST(get)
{
}

TEST(delete)
{
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
	ADD_TEST(delete);
	ADD_TEST(one_node);
	ADD_TEST(no_nodes);
	ADD_TEST(normal_operation);
}
