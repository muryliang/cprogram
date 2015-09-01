#include"minunit.h"
#include<lcthw/list.h>
#include<assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create(){

	list = List_create();
	mu_assert(list != NULL , "failed to create list");
	return NULL;
}

char *test_destroy(){
	List_clear_destroy(list);
	return NULL;
}

char *test_push_pop(){

	List_push(list, test1);
	mu_assert(List_last(list) == test1 , "wrong last value");
	
	List_push(list,test2);
	mu_assert(List_last(list) == test2 , "wrong last value2");

	List_push(list,test3);
	mu_assert(List_last(list) == test3 , "wrong last value3");
	mu_assert(List_count(list) == 3, "worng count on push");

	char *val = List_pop(list);
	mu_assert(val == test3 , "wrong value on pop");
	
	val = List_pop(list);
	mu_assert(val == test2 , "wrong value on pop");

	val = List_pop(list);
	mu_assert(val == test1 , "wrong value on pop");
	mu_assert(List_count(list) == 0 , "wrong count after pop");

	return NULL;
}

char *test_unshift(){

	List_unshift(list , test1);
	mu_assert(List_first(list) == test1 , "wrong first value");
	
	List_unshift(list , test2);
	mu_assert(List_first(list) == test2 , "wrong first value");

	List_unshift(list , test3);
	mu_assert(List_first(list) == test3 , "wrong first value");
	mu_assert(List_count(list) == 3 , "wrong count on unshift");

	return NULL;
}


char *test_remove(){

/* we only need to test the middle remove case since push/shift
 * alread tests the other cases
 */

	char *val = List_remove(list , list->first->next);
	mu_assert(val == test2 ,"wrong removed element");
	mu_assert(List_count(list) == 2 , "wrong count after remove");
	mu_assert(List_first(list) == test3 , "wrong first after remove");
	mu_assert(List_last(list) == test1 , "wrong last after remove");

	return NULL;
}

char *test_shift(){

	mu_assert(List_count(list) != 0 , "wrong count before shift");
	
	char *val = List_shift(list);
	mu_assert(val == test3 , "wrong value on shfit");
	
	val = List_shift(list);
	mu_assert(val == test1 , "wrong value on shift.");
	mu_assert(List_count(list) == 0 , "wrong count after shfit");
	
	return NULL;
}


char *all_tests(){
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_destroy);

	return NULL;
}


RUN_TESTS(all_tests);

