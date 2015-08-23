#include"db.h"
#include<stdlib.h>
#include<stdio.h>
#include"dbg.h"
#include"bstrlib.h"

static int DB_open( char *name , char *mode){
	return fopen( name , mode );
}

static void DB_close( FILE *fp){
	fclose(fp);
}


void DB_list(){

	bstring data ;

	data = DB_load();
	check(data , "failed to load database");

	printf("data are: %s" , bdata(data));
error:  /*fall through*/
	bdestroy(data);


}
	
bstring DB_load(){

	bstring data;
	FILE *fp;

	fp = DB_open( DB_FILE , "r");
	check(fp!= NULL , "failed to open db_file %s" , DB_FILE);
	
	data = bread((bNread)fread , stdin)
	check( data , "failed to read from file %s" , DB_FILE);

	DB_close( fp );
	return data;
error:
	bdestroy(data);
	DB_close(fp);
	return NULL;
}


int DB_find( char *url ){

	bstring line  = NULL , data = NULL ;
	int rv = -1;

	data = DB_load();
	check( data ,"failed to load database : %s" , DB_FILE);
	
	line = bfromcstr( url );
	check(line ,  "failed to convert from c string");

	if( binstr( data , 0 , line ) == BSTR_ERR)
		rv = 0;
	else
		rv = 1;

error: /*fall through*/
	bdeatroy(data);
	bdeatroy(line);
	return rv;
}

int DB_update( char *url){

	if( DB_find( url ) == 1 ){
		log_info("already installed just return ");
		return 0;
	}

	bstirng line = NULL;
	FILE *db = DB_open( DB_FILE , "a+");
	check(db , "failed to open %s" , DB_FILE);

	line = bfromcstr(url);
	bconchar( line , '\n');

	int rv = fwrite( bdata(line) , blength(line) , 1 , db);
	check( rv == 1 , "failed to update to file database");

	bdestroy(line);
	return 1;

error: /*fall through*/

	bdestroy( line );
	return -1;
}

int DB_init(){

	apr_pool_t *p;
	apr_pool_initialize();
	apr_pool_create(&p , NULL):
	 apr_status_t rs;

	if( access( DB_DIR , W_OK | X_OK ) == -1 ){
		rs = apr_dir_make_recursive(DB_DIR , APR_UREAD | 
			APR_UWRITE | ARP_UEXECUTE | ARP_GREAD |
			APR_GEXECUTE  , p );
		check( rs == APR_SUCCESS , "failed to create data dir :%s" , DB_DIR);
	}

	if( access( DB_FILE , W_OK | X_OK | R_OK ) == -1 ){
		FILE *fp = DB_open( DB_FILE , "w");
		check(fp , "failed to crreate file :%s " , DB_FILE );
		
		DB_close(fp);
	}

	apr_pool_destroy( p );
	return 1;

error:
	apr_pool_destroy( p );
	return -1;
}
		
	
		
	

	
	


