#include"ex22.h"
#include"dbg.h"

const char * MY_NAME = "Zed A. Shaw";

void scope_demo( int count ){

	log_info("count is : %d" , count);

	if( count > 10 ){
		int count = 100; /* BAD! BUGS*/

		log_info("count in this scope is%d " , count);
	}

	log_info("count is at exit: %d" , count);


	count = 3000;
	log_info("count after assign : %d" , count);
}

int main(int ac ,char *av[] ){

	/*test out THE_AGE accessor*/
	log_info("my name: %s , age %d" , MY_NAME ,  get_age());
	
	set_age(100);
		
	log_info("my age is now : %d" , get_age());

	/*test out THE_SIZE extern*/
	log_info("THE_SIZE is: %d" , THE_SIZE);
	print_size();

	THE_SIZE = 9;
 
	log_info("the SIZE is now : %d"  , THE_SIZE);
	print_size();

	/*test the ratio function static*/
	log_info("ratio at first: %f" , update_ratio(2.0));
	log_info("ratio again: %f" , update_ratio(10.0));
	log_info("ratio once more: %f" , update_ratio(300.0));

	/*test the scope demo*/
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20 );
	
	log_info("count after calling scope_demo: %d" , count);
	
	int *ptr = get_age_ptr();
	printf("I have got the age ptr: %p" , ptr);
	printf("and the age now is %d\n" , *ptr);
	*ptr = 32;
	printf(" the age now is %d\n", get_age());
	
	return 0;
}	
