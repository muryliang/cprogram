#include"minunit.h"
#include<sys/time.h>
#include<lcthw/list_algos.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>

char *value[] = {"XXXX" , "1234" , "abcd" , "xjvef" , "NDSS"};
#define NUM_VALUES 5

List *create_words(){
	int i = 0;
	List *words = List_create();
	char tmpbuf[20] , *store;
	
/*	for( i = 0 ; i < NUM_VALUES; i++){
		List_push(words , value[i]);
	}
*/
	FILE *fp = fopen("/tmp/words" , "rb"); /*use a random file full of words*/
	check_mem(fp);

	while( fgets( tmpbuf , 20 , fp) ){
		store = malloc(20);
		strcpy( store , tmpbuf);	
		List_push( words , store);
	} 
	

	return words;
error:
	return NULL;
}

int is_sorted(List *words){

	LIST_FOREACH(words , first , next , cur){
		if(cur->next && strcmp(cur->value ,cur->next->value )>0){
			debug("%s %s" , (char*)cur->value , (char*)cur->next->value);
			return 0;
		}
	}
	return 1;
}

char *test_bubble_sort(){
	List *words = create_words();
	struct timeval tv , tva;

	/*should work on a list that needs sorting*/
	gettimeofday( &tv , NULL );
	int rc = List_bubble_sort(words , (List_compare)strcmp);
	gettimeofday(&tva , NULL);

	printf("the diff of time bubble is %dsecs and %d usecs\n" , tva.tv_sec-tv.tv_sec , 
		tva.tv_usec - tv.tv_usec);

	mu_assert(rc == 0 , "bubble sort failed");
	mu_assert(is_sorted(words) , "words are not sorted after bubble sort");
	
	/*should work on an already sorted list*/
	rc = List_bubble_sort(words , (List_compare)strcmp);
	mu_assert(rc == 0 , "bubble sort of already sorted failed.");
	mu_assert(is_sorted(words) , "words should be sorted if already bubble sort");

	List_destroy(words);

	/*should work on an empty list*/
	words = List_create(words);
	rc = List_bubble_sort(words , (List_compare)strcmp);
	mu_assert(rc == 0 , "bubble sort failed on empty list");
	mu_assert(is_sorted(words) , "words should be sortd if empty");
	
	List_destroy(words);

	return NULL;
}


char *test_merge_sort(){
	
	List *words = create_words();
	struct timeval  tv , tva;

	/*should work on a list that needs sorting*/
	gettimeofday( &tv , NULL );
	List *res = List_merge_sort(words , (List_compare)strcmp);
	gettimeofday(&tva , NULL);

	printf("the diff of time merge is %dsecs and %d usecs\n" , tva.tv_sec-tv.tv_sec , 
		tva.tv_usec - tv.tv_usec);
//	printf("pass unsorted\n");
	mu_assert(is_sorted(res), "words are not sorted after merge sort");

//	List *res2 = List_merge_sort(res , (List_compare)strcmp);
	printf("pass sorted\n");
	mu_assert(is_sorted(res) , "should stil be sorted after merge sort");
//	List_destroy(res2);
	//List_destroy(res);

	//List_destroy(words);

	return NULL;
}

char *all_tests(){

	mu_suite_start();

	mu_run_test( test_bubble_sort);
//	mu_run_test( test_merge_sort);
	
	return NULL;
}

RUN_TESTS(all_tests);

