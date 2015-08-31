#include"minunit.h"
#include<dlfcn.h>

typedef int (*lib_function) (const char *data);
char *lib_file = "build/libYOUR_LIBRARY.so";
void *lib = NULL;

int check_function( const char *func_to_run , const char *data , int expected){
	lib_function func=dlsym(lib , func_to_run);
	check(func != NULL  , "did not find %s function in the library %s: %s" ,func_to_run , lib_file , dlerror());

	int rc = func(data);
	check(rc == expected , "function %s return %d for data: %s" , func_to_run , rc , data);
	return 1;
error:
	return 0;
}

char *test_dlopen(){
	lib = dlopen(lib_file , RTLD_NOW);
	mu_assert(lib != NULL , "failed to open the library to test");
	return NULL;
}

char *test_functions(){
	mu_assert(check_function("print_a_message" , "hello" , 0),"print_a_message failed.");
	mu_assert(check_function("uppercase","hello" ,0), "uppercase failed");
	mu_assert(check_function("lowercase" , "HELLO" ,0),"lowercase failed");
	return NULL;
}

char *test_failure(){
	mu_assert(check_function("fail_on_purpose","hello" ,1),"failed on purpose ");
	return NULL;
}

char *test_dlclose(){
	int rc = dlclose(lib);
	mu_assert(rc == 0 , "failed to close lib");
	return NULL;
}

char *all_tests(){
	mu_suite_start();
	
	mu_run_test(test_dlopen);
	mu_run_test(test_functions);
	mu_run_test(test_failure);
	mu_run_test(test_dlclose);

	return NULL;
}

RUN_TESTS(all_tests);

