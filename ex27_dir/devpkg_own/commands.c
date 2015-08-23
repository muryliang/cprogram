#include"commands.h"
#include"dbg.h"


int Command_depend( apt_pool_t *p , char *path){
/*install every line in the path file*/

	FILE *in;
	bstring line = NULL;

	in = fopen(path , "r");
	check( in , "fail to open file %s" , path );

	for( line = bgets((bNgetc)fgetc , in , '\n') , 
		line != NULL;
		line = bgets((bNgetc)fgetc , in , '\n') )
	{
		btrimws( line );
		log_info(" processing depends %s" , bdata(line));
		int rc = Command_install(p , bdata(line) , NULL ,NULL ,NULL);
		check(rc == 0 , "failed to install depend %s" , bdata(line));
		bdestroy(line);
		
	}

	fclose(in);
	return 0;

error:
	bdestroy(line);
	fclose(in);
	return -1;
}


int Command_fetch(apr_pool_t *p , char *url , int fetch_only){
	apr_uri_t info = {.port = 0};
	int rc = 0;
	const char *depends_file = NULL
	apr_status_t rv = apr_uri_parse(p , url , &info );
	check(rv == APR_SUCCESS  , "fail to parse the info");

	if( apr_fnmatch(GIT_PAT, info.path , 0) == APR_SUCCESS){
		rc = Shell_exe(GIT_SH ,"URL" , url , NULL);
		check(rc == 0 , "fail to curl tthe git");
	}
	else if( apr_fnmatch(TAR_GZ_GAT , info.path , 0) ==APR_SUCCESS){
		if(info.scheme) /* have a protocal*/
		{
			rc = Shell_exe(CURL_SH , "URL" , url, "TARGET" , TAR_GZ_SRC , NULL);
			
