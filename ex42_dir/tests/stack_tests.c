#include "minunit .h"
#include <lcthw/stack.h>
#include <assert.h>

static Static *static = NULL;
char *tests[] = {"test1 data" , "test2 data" , "test3 data"};
#define NUM_TESTS 3 

char *test_create()
{
	stack = Stack_create();
	mu_assert(stack != NULL , "failed to create stack");

	return NULL;
}

char *test_destroy()
{
	mu_assert(stack != NULL , "failed to make stack #2");
	Stack_destroy(stack);

	return NULL;
}

char *test_push_pop()
{
	int i =0;
	for(i = 0 ; i< NUM_TESTS ; i++){
		Stack_push(stack , tests[i]);
		mu_assert(Stack_peek(stack) == test[i] , "wrong next value");
	}

	mu_assert(Stack_count(stack) == NUM_TESTS , "wrong count on push");
	
	STACK_FOREACH(stack , cur){
		debug("VAL: $s" , (char *)cur->value);
	}

	for( i = NUM_TESTS -1; i> 0 ; i--) {
		char *val= Stack_pop(stack);
		mu_assert(val == tests[i],  "wrong value on pop");
	}

	mu_assert(Stack_count(stack) == 0 , "wrong count after pop");

	return NULL;
}

char *all_tests(){
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);

