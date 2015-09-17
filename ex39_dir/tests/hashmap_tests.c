#include "minunit.h"
#include <lcthw/hashmap.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

Hashmap *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(HashmapNode *node)
{
	debug("key: %s" , bdata((bstring)node->key));
	traverse_called++;
	return 0;
}

static int traverse_fail_cb(HashmapNode *node)
{
	debug("key:%s" , bdata((bstring)node->key));
	traverse_called++;
	
	if(traverse_called== 2)
	{
		return 1;
	}else{
		return 0;
	}
}

char *test_create()
{
	map = Hashmap_create(NULL ,NULL);
	mu_assert(map != NULL , "failed to create map");
	return NULL;
}
char *test_destroy()
{
	Hashmap_destroy( map);
	return NULL;
}

char *test_get_set()
{
	/*be attention that bsStatic return value only
 * 	can be used as tagstring type  ,the point to which is the bstring
 */
	int rc =Hashmap_set(map , &test1 , &expect1);
	mu_assert(rc == 0 , "failed to set &test1");
	bstring result = Hashmap_get(map , &test1);
	mu_assert(result == &expect1, "wrong value for test1");
	
	rc = Hashmap_set(map , &test2 , &expect2);
	mu_assert(rc == 0 , "failed to set test2");
	result = Hashmap_get(map , &test2);
	mu_assert(result == &expect2 , "wrong values for test2 ");

	rc = Hashmap_set(map , &test3 , &expect3);
	mu_assert(rc == 0 , "failed to set test2");
	result = Hashmap_get(map , &test3);
	mu_assert(result == &expect3 , "wrong values for test2 ");
	
	return NULL;
}

char *test_traverse()
{
	int rc = Hashmap_traverse(map, traverse_good_cb);
	mu_assert(rc == 0 , "failed to traverse");
	mu_assert(traverse_called == 3 , "wrong count traverse");
	
	traverse_called = 0;
	rc = Hashmap_traverse(map , traverse_fail_cb);
	mu_assert(rc == 1 , "failed to traverse");
	mu_assert(traverse_called == 2 , "wrong count traverse for fail");

	return NULL;
}

char *test_delete()
{
	bstring deleted = (bstring)Hashmap_delete(map , &test1);
	mu_assert(deleted != NULL , "got null on delete");
	mu_assert(deleted == &expect1 , "should get test1 ");
	bstring result = Hashmap_get(map , &test1);
	mu_assert(result == NULL , "should delete");

	deleted = (bstring)Hashmap_delete(map , &test2);
	mu_assert(deleted != NULL , "got null on delete");
	mu_assert(deleted == &expect2 , "should get test2 ");
	result = Hashmap_get(map , &test2);
	mu_assert(result == NULL , "should delete");

	deleted = (bstring)Hashmap_delete(map , &test3);
	mu_assert(deleted != NULL , "got null on delete");
	mu_assert(deleted == &expect3 , "should get test3 ");
	result = Hashmap_get(map , &test3);
	mu_assert(result == NULL , "should delete");

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

	return NULL;
}

RUN_TESTS(all_tests);

	
