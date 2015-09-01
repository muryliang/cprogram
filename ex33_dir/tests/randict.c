#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<lcthw/dbg.h>

#define LEN  9

char * random_words( void ){

	int length = rand()%LEN + 1 ;
	int i;
	char *tmp = malloc(10*sizeof(char));
	
	check_mem(tmp);

	for( i = 0 ; i < length ; i++){
		tmp[i] = 'a' + rand()%26;
	}
	tmp[i] = '\0';
	return tmp;
error:
	return NULL;
}
		
		

int main( int argc , char *argv[]){

	FILE *fp ;
	char *word;

	check( argc == 2  , "must one argument");

	int counts = atoi(argv[1]);

	fp = fopen("/tmp/words" , "wb");
	check( fp , "fail to open file fp");

	while( counts-- != 0){
		word = random_words();
		fprintf(fp , "%s\n" , word);
	}
	fclose(fp);
	return 0;
error: 
	return -1;
}

	
