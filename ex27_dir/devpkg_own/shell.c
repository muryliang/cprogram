#include"dbg.h"
#include<stdio.h>
#include<stdlib.h>
#include"shell.h"

int Shell_exe( Shell cmd , ... ){

	apr_pool_t *p;
	apr_pool_initialize();
	apr_status_t rv = apr_pool_create(&p , NULL);
	check(rv == APR_SUCCESS ,"failed to create pool");
	va_list ap;
	va_start(ap , cmd );

	char *k = NULL;
	char *args = NULL;
	int i ;

	for( k = va_arg( ap , char *),
	     k != NULL,
	     k = va_arg(ap , char *)){
		
		
		args = va_arg(ap , char *);
		for( i = 0 ; cmd.arg[i] != NULL; i++){
			if( strcmp( cmd.arg[i] , k ) == 0){
				cmd.arg[i] = args;
				break;
			}
		}
	}

	int rc = Shell_run( p , &cmd );
	check( rc == 1 , "failed to run shell");
	apr_pool_destroy(p);
	va_end(ap);
	return 1;
error:
	apr_pool_destroy(p);
	va_end(ap);
	return -1;
}
		
	
int Shell_run( apr_pool_t *p , Shell *cmd ){  /*use the apr process thread lib to run*/

	apr_procattr_t *attr;
	apr_proc_t proc;

	apr_procattr_create( &attr , p );
	int rv = apr_procattr_io_set(attr , APR_NO_PIPE ,APR_NO_PIPE, APR_NO_PIPE);
	check( rv == ARP_SUCCESS , "fail to set io attr ");

	rv = apr_procattr_dir_set( attr , cmd->dir);
	check( rv == ARP_SUCCESS , "fail to set dir attr ");

	rv = apr_procattr_cmdtype_set(attr , APR_PROGRAM_PATH);
	check( rv == ARP_SUCCESS , "fail to set cmd type attr ");
	
	rv = apr_proc_create( &proc , cmd->cmd , cmd->args , NULL , attr , p );
	check( rv == ARP_SUCCESS , "fail to create proc to run  ");

	rv = apr_proc_wait( proc , &cmd->exit_code , &cmd->exit_why , APR_WAIT);
	check( rv == ARP_SUCCESS , "fail to wait proc to run  ");
	check( cmd->exit_code == 0 , "exit code abnormally");
	check( cmd->exit_why == APR_PROC_EXIT ," exited by signal or else");


	return 1;
error:
	return -1;
}
	
	
Shell CLEAN_UP{
	.exe = "rm",
	.dir = "/tmp",
	.args = {"rm" ,"-rf" , "/tmp/pkg-build" , "/tmp/pkg-src.tar.gz" , 
			"/tmp/pkg-src.tar.bz2" , "/tmp/DEPENDS" ,NULL}
};

Shell GIT_SH{
	.exe = "git",
	.dir = "/tmp",
	.args = {"git" , "clone" , "URL" , "pkg-build" , NULL}
};

Shell TAR_SH{
	.exe = "tar",
	.dir = "/tmp/pkg-build"",
	.args = {"tar" , "-zxf" , "FILE" , "--strip-components" , "1" , NULL}
};

	
