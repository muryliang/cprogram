#include<lcthw/dbg.h>
#include<lcthw/bstrlib.h>
#include<string.h>
#include "minunit.h"


/* this file  when compiled  with -Wall  , will trigger that "null argumnet where non-null
 * is required  , if you don't want to see that ,just make a char * to get the data of bdata()
 * then use that in the strcmp function
 */

static char * test_operations()
{
	char *a = "muryliang";
	char *b = "hailing";
	char *search = "ry";
	char *cmp = "hailing";

	int rc;

	bstring aa = bfromcstr( a );
	char *tmpstr = bdata(aa);
	rc = strcmp( (const char *)tmpstr, (const char *)a );
	check( rc == 0 , "bad string cmp in bstring");

	bstring bb = bfromcstr( b );
	bassign( aa , bb );
	check( strcmp( bdata(aa) , bdata(bb)) == 0 , "wrong assign or bdata");

	check( bstricmp( aa , bb ) == 0 , "wrong bstricmp");

	bstring tmp = bstrcpy( bb );
	check( bstricmp( tmp  , bb ) == 0 , "wrong bstrcpy");

	bassigncstr( bb , b );
	bassigncstr( aa , a );
	bconcat(aa , bb );
	check( strcmp( bdata(aa) , "murylianghailing"), "worng bconcat");
	
	bassigncstr( bb , b );
	bassigncstr( aa , a );
	check( biseq( aa , bb ) == 1 , "wrong biseq");

	bassigncstr( aa , a );
	bstring sea = bfromcstr(search);
	bstring rep = bfromcstr("hello");
	bfindreplace( aa , sea , rep , 0);
	check( strcmp(bdata(aa) , "muhelloliang") == 0 , "bfindreplace not correct");


	bdestroy( aa) ;
	bdestroy( bb );
	bdestroy(tmp);
	bdestroy(sea);
	bdestroy(rep);

	return NULL;
error:
	return NULL ;
}

char * test_all(){
	mu_suite_start();
	
	mu_run_test( test_operations);
	return NULL;
}
	
	
	
	
	
RUN_TESTS(test_all);
