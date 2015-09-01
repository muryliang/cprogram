#include"list_algos.h"
#include<assert.h>
#include"dbg.h"
#include"list.h"
#include<stdio.h>

static void List_swap( ListNode *cur , ListNode *next){

	void *tmp;

	tmp = cur->value;
	next->value = cur->value;
	cur->value = tmp;
}

void  List_travers( List *words){

	ListNode *cur = words->first;

	while( cur!= NULL ){

		printf("%s  "  ,(char *)cur->value);
		cur = cur->next;
	}
	putchar('\n');
}

static List * List_split( List *words , int pos){

	List *second;
	assert( pos <= words->count);
	ListNode *middle = words->first; 

	int position = pos;
		
	while( pos != 0){
		middle = middle->next;
		assert(middle != NULL);
		pos--;
	}

	second =List_create();
	second->count = words->count - position;
	second->first = middle;
	second->last = words->last;
	
	words->count = position;
	words->last = middle->prev;
	words->last->next = NULL;
	middle->prev = NULL;
	
	return second;
}

static List *merge_two_parts( List *first , List * second , List_compare cmp){

/* get frist node in each  , cmp  copy to another 
 * make new list to copy into 
 * return
 */
	List *dest = List_create();
	assert( dest != NULL);

	ListNode *r1 ,*r2;

	r1 = first->first;
	r2 = second->first;

	while( r1 != NULL && r2 != NULL ){
		if( cmp( r1->value , r2->value) <= 0){
			List_push(dest , r1->value);
			r1 = r1->next;
		} 
		else{
			List_push(dest , r2->value);
			r2 = r2->next;
		}
	}

	while( r1 != NULL){
		List_push(dest , r1->value);
		r1 = r1->next;
	}

	while(r2 != NULL){
		List_push(dest , r2->value);
		r2 = r2->next;
	}

	List_destroy( first );
	List_destroy( second);

	return dest;
}
	

		

	
int List_bubble_sort( List *words , List_compare cmp){

	
/* for each node  and next node != NULL , 
 * 	cmp cur , next  >0
 * 		swap
 * 		cur = next , next = next.next
 */
	ListNode *cur , *next;
	int swaped = 0;

	assert( words != NULL );

	if( words->count == 0 || words->count == 1){
		log_info(" no need to sort just return");
		return 0;
	}
	
	do{
		swaped = 0;
		for( cur = words->first , next = cur->next;
			cur != NULL && next !=NULL;
			cur = next , next = next->next)
		{
			if( cmp( (char*)cur->value , (char*)next->value) > 0)
			{
				List_swap( cur , next);
				swaped = 1;
			}
		}
	}while(swaped != 0 );

	return 0;

error:
	return -1;
}

List *List_merge_sort( List* words , List_compare cmp){

/* find middle  , split into two lists
 * recursively do this ,until only one left 
 * then recursively merge two lists
 */

	int middle;
	static int i = 1;
	List *second;

	if( words->count == 0 || words->count == 1 )
		return words;

	middle = words->count / 2;

	second = List_split( words , middle);
	assert( second != NULL );
	/*after this  words stores the first part before middle
 * 	  and second begin with middle-th node
 */
	words = List_merge_sort(words , cmp);
	second = List_merge_sort(second , cmp);
	
//	printf("times: %d\n" , i++);
/*	List_travers( words);
	List_travers( second);	
*/
	List *dest = merge_two_parts( words , second , cmp);
	log_info("now merge");
	
	return dest ;

}

