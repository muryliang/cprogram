#include "minunit.h"
#include <lcthw/BSTree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>
#include <time.h>

BSTree *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("the value 1");
struct tagbstring expect2 = bsStatic("the value 2");
struct tagbstring expect3 = bsStatic("the value 3");

static int traverse_good_cb(BSTreeNode *node)
{
	debug("key :%s" , bdata((bstring)node->key));
	traverse_called++;
	return 0;
}

static int traverse_fail_cb(BSTreeNode *node)
{
	debug("key: %s" , bdata((bstring)node->key));
	traverse_called++;

	if(traverse_called == 2 ){
		return 1;
	}else {
		return 0;
	}
}

char *test_create()
{
	map = BSTree_create(NULL);
	mu_assert(map!=NULL , "fail to create map");
	
	return NULL;
}

char *test_destroy()
{
	BSTree_destroy(map);
	
	return NULL;
}

char *test_get_set()
{
	int rc=  BSTree_set(map , &test1 , &expect1);
	mu_assert(rc == 0 , "fail to set &test1");
	bstring result = BSTree_get(map , &test1);
	mu_assert(result == &expect1 , "wrong value for test1");

	rc=  BSTree_set(map , &test2 , &expect2);
	mu_assert(rc == 0 , "fail to set &test1");
	result = BSTree_get(map , &test2);
	mu_assert(result == &expect2 , "wrong value for test1");

	rc=  BSTree_set(map , &test3 , &expect3);
	mu_assert(rc == 0 , "fail to set &test1");
	result = BSTree_get(map , &test3);
	mu_assert(result == &expect3 , "wrong value for test1");

	return NULL;

}

char *test_traverse()
{
	int rc = BSTree_traverse(map , traverse_good_cb);
	mu_assert(rc == 0 , "failed to traverse");
	mu_assert(traverse_called == 3 , "wrong count traverse");
	
	traverse_called = 0;
	rc = BSTree_traverse(map , traverse_fail_cb);
	mu_assert(rc == 1 , "failed to traverse");
	mu_assert(traverse_called == 2 , "wrong count traverse for fail");

	return NULL;
}

char *test_delete()
{
	bstring deleted = (bstring)BSTree_delete(map , &test1);
	mu_assert(deleted != NULL , "got null on delete");
	mu_assert(deleted == &expect1 , "should get test1");
	bstring result = BSTree_get(map , &test1);
	mu_assert(result == NULL , "should deleted");

	deleted = (bstring)BSTree_delete(map , &test1);
	mu_assert(result == NULL , "should get null on delete");

	deleted = (bstring)BSTree_delete(map , &test2);
	mu_assert(deleted != NULL , "got null on delete");
	mu_assert(deleted == &expect2 , "should get test2");
	result = BSTree_get(map , &test2);
	mu_assert(result == NULL , "should deleted");

	deleted = (bstring)BSTree_delete(map , &test2);
	mu_assert(result == NULL , "should get null on delete");
	
	deleted = (bstring)BSTree_delete(map , &test3);
	mu_assert(deleted != NULL , "got null on delete");
	mu_assert(deleted == &expect3 , "should get test3");
	result = BSTree_get(map , &test3);
	mu_assert(result == NULL , "should deleted");

	deleted = (bstring)BSTree_delete(map , &test3);
	mu_assert(result == NULL , "should get null on delete");


	return 	NULL;
}


char *test_fuzzing()
{
	BSTree *store = BSTree_create(NULL);
	int i = 0;
	int j = 0;
	bstring numbers[100] = {NULL};
	bstring data[100] = {NULL};
	srand((unsigned int )time(NULL));
	
	for( i = 0; i<100 ; i++){
		int num = rand();
		numbers[i] = bformat("%d" , num );
		data[i] = bformat("data %d " , num );
		BSTree_set(store , numbers[i] ,data[i]);
	}

	for( i = 0 ; i < 100 ; i++){
		bstring value = BSTree_delete(store , numbers[i]);
		mu_assert(value == data[i] ,"failed to delete the right number");
		mu_assert(BSTree_delete(store , numbers[i])==NULL , "should get nothing");
		
		for( j = i+1 ; j < 99-i ; j++){
			bstring value = BSTree_get(store , numbers[j]);				    mu_assert(value == data[j] , "failed to get the right numbers");
		}
		bdestroy(value);
		bdestroy(numbers[i]);
	}

	BSTree_destroy(store);
	return NULL;
}


char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_get_set);
	mu_run_test(test_traverse);
	mu_run_test(test_delete);
	mu_run_test(test_destroy);
	mu_run_test(test_fuzzing);
	return NULL;
}

RUN_TESTS(all_tests);
