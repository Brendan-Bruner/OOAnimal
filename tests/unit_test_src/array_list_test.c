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
 * July 3, 2016
 */

#include <unit.h>
#include <util/CCArrayList.h>

#define DEFAULT_LENGTH 12
#define UNITY_LENGTH 1
#define DEFAULT_ELEMENT_SIZE sizeof(int)

struct CCArrayList list;

TEST_SETUP( )
{
	CCArrayList(&list, DEFAULT_ELEMENT_SIZE, DEFAULT_LENGTH);
}
TEST_TEARDOWN( )
{
	CDestroy(&list);
}


TEST(add_at)
{
	CIListError 	err;
	int		test_var = 3;

	/* Insert with an out of bounds index.
	 */
	err = CIList_AddAt(&list.cIList, &test_var, DEFAULT_LENGTH+1);
	ASSERT(err == CILIST_ERR_INDEX, "Failure to catch out of bounds index");

	/* Inserting within bounds should return OK. 
	 */
	err = CIList_AddAt(&list.cIList, &test_var, 0);
	ASSERT(err == CILIST_OK, "Failure to do clean insert");
}

TEST(get)
{
	CIListError 	err;
	int 		test_var = 0;

	/* Try to get element with out of bounds index.
	 */
	err = CIList_Get(&list.cIList, &test_var, DEFAULT_LENGTH+1);
	ASSERT(err == CILIST_ERR_INDEX, "Failure to catch out of bounds index");

	/* Try to get element at empty location. All locations are
	 * empty at this point, so can use any index in bounds.
	 */
	err = CIList_Get(&list.cIList, &test_var, 0);
	ASSERT(err == CILIST_ERR_EMPTY, "Failure to catch empty index");

	/* Insert an element into the list to assert the get method
	 * works with in bounds, non empty indices.
	 */
	CIList_AddAt(&list.cIList, &test_var, 0);

	/* Assert we can get this element without error now.
	 */
	test_var = !test_var;
	err = CIList_Get(&list.cIList, &test_var, 0);
	ASSERT(err == CILIST_OK, "Failed to get element at clean index");
	ASSERT(test_var == 0, "Failed to get correct element at clean index");

	/* Assert we can get the same element, but ignoring its value.
	 */
	err = CIList_Get(&list.cIList, NULL, 0);
	ASSERT(err == CILIST_OK, "Failed to get element at clean index");
}

TEST(remove)
{
	CIListError	err;
	int		test_var = 0;

	/* Test this method fails with an error on the same conditions
	 * that CIList_Get( ) would.
	 */
	err = CIList_Remove(&list.cIList, &test_var, DEFAULT_LENGTH+1);
	ASSERT(err == CILIST_ERR_INDEX, "Failed to throw same error as CIList_Get");

	/* Insert an element into the list to assert the remove method
	 * works with clean parameters.
	 */
	CIList_AddAt(&list.cIList, &test_var, 0);

	/* Assert we can get this element without error now.
	 */
	test_var = !test_var;
	err = CIList_Remove(&list.cIList, &test_var, 0);
	ASSERT(err == CILIST_OK, "Failed to remove element at clean index");
	ASSERT(test_var == 0, "Failed to remove correct element at clean index");

	/* Removing at this index should now return an empty error.
	 */
	err = CIList_Remove(&list.cIList, &test_var, 0);
	ASSERT(err == CILIST_ERR_EMPTY, "Failed to throw error on empty index");
}

TEST(add)
{
	CIListError	err;
	int		test_var = 0;
	int i;

	/* Assert no error when adding at an empty index.
	 */
	err = CIList_Add(&list.cIList, &test_var);
	ASSERT(err == CILIST_OK, "Failed to insert with clean parameters");

	/* Assert a new index can be found, do this by adding something
	 * to index one, which is the index CIList_Add will use for
	 * its next insert.
	 */
	++test_var;
	CIList_AddAt(&list.cIList, &test_var, 1);
	++test_var;
	err = CIList_Add(&list.cIList, &test_var);
	ASSERT(err == CILIST_OK, "Failed to find new index with clean parameters");

	/* Fill the entire list, this way we can test a new index will
	 * not be found.
	 */
	for( i = 3; i < DEFAULT_LENGTH; ++i ) {
		++test_var;
		CIList_AddAt(&list.cIList, &test_var, i);
	}

	/* Now test a new index can't be found.
	 */
	++test_var;
	err = CIList_Add(&list.cIList, &test_var);
	ASSERT(err == CILIST_ERR_FULL, "Failed to throw a full list error");
}

TEST_SUITE(array_list)
{
	ADD_TEST(add_at);
	ADD_TEST(get);
	ADD_TEST(remove);
	ADD_TEST(add);
}

