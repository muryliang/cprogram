#ifndef __sh_h
#define __sh_h

#define MAX_COMMAND_ARGS 100

typedef struct Shell {
	char *dir,
	char *cmd,
	char *args[ MAX_COMMAND_ARGS ],
	apr_procattr_t *attr;
	apr_proc_t proc;
	apr_exit_why_e exit_why;
	int exit_code;
} Shell ;

int Shell_exe( Shell cmd , ...);
int shell_run( apr_pool_t *p , Shell *cmd );

extern Shell CLEAN_UP;
extern Shell GIT_SH;
extern Shell TAR_SH;
extern Shell CURL_SH;
extern Shell CONFIGURE_SH;
extern Shell MAKE_SH;
extern Shell INSTALL_SH;

#endif
