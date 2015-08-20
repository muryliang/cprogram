#include<stdio.h>
#include<string.h>
#include"dbg.h"

int normal_copy( char *from , char *to , int count){

	int i = 0;
	
	for( i = 0 ; i < count ; i++){
		to[i] = from[i];
	}
	return i;
}

#define LOOP(N)  case N:*to++=*from++;\
		case N-1 : *to++ = *from++;\
		case N-2 : *to++ = *from++;\
		case N-3: *to++ = *from++;\
		case N-4: *to++ = *from++;\
		case N-5: *to++ = *from++;\
		case N-6: *to++ = *from++

int duffs_device( char *from , char *to , int count)

{
		int n = (count + 7 ) / 8 ;

/*		switch( count % 8 ){
			case 0 :do{ *to++ = *from++;
				case 7: *to++ = *from++;
				case 6: *to++ = *from++;
				case 5: *to++ = *from++;
				case 4: *to++ = *from++;
				case 3: *to++ = *from++;
				case 2: *to++ = *from++;
				case 1: *to++ = *from++;
			} while( --n > 0);
		}
*/
		switch( count % 8 ){
			case 0: do{ *to++ = *from++;
				LOOP(7);
			} while( --n > 0);
		}
	return count;
}

int zeds_device( char *from , char *to , int count){
	{
		int n = (count + 7 ) / 8;

		switch( count % 8 ){
			case 0:
			again: *to++ = *from++;
			
			case 7 : *to++ = *from;
			case 6:  *to++ = *from;
			case 5 : *to++ = *from;
			case 4 : *to++ = *from;
			case 3 : *to++ = *from;
			case 2 : *to++ = *from;
			case 1 : *to++ = *from;
				if( --n > 0) goto again;
		}
	}
	return count;
}

int valid_copy( char *data , int count , char expects){

	int i = 0;
	for( i = 0 ; i < count ; i++){
		if( data[i] != expects ){
			log_err("[%d] %c != %c" , i , data[i] , expects);
			return 0;
		}
	}	
	return 1;
}

int main(int ac ,char *av[]){

	char from[1000] = {'a'};
	char to[1000] = {'c'};
	int rc = 0;

	/*setup the from to have some stuff*/
	memset(from , 'x' , 1000);
	/*set it to a failure mode*/
	memset(to , 'y' , 1000);
	check(valid_copy(to , 1000 , 'y') , "not initialized right");
	 
	/*use normal copy to*/
	rc = normal_copy(from , to , 1000);
	check(rc == 1000 , "normal copy failed: %d" , rc);
	check(valid_copy(to , 1000 , 'x'),"normal copy failed");
	
	/*reset*/
	memset(to , 'y' , 1000);
	
	/*duffs version*/
	rc = duffs_device(from , to , 1000);
	check( rc == 1000 , "duff's device failed: %d" , rc);
	check( valid_copy(to ,1000 , 'x') , "duff's device failed copy");
	
	/*reset*/
	memset(to , 'y' ,1000);

	/*my version*/
	rc = zeds_device(from , to , 1000);
	check(rc == 1000 , "zed's device failed: %d" , rc);
	check(valid_copy(to , 1000 , 'x'), "zed's device failed copy");
	
	return 0;
error:
	return 1;
}
			
