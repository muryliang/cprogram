#ifndef __dbg_h__
#define __dbg_h__

#include<stdio.h>
#include<errno.h>
#include<string.h>

/* these macros are for debug  
 * you can use the -DNBEBUG to prevent the check_debug output and
 * 	just go to error
 *
 * check_men used to test null pointers
 *
 * check used to test conditions and if wrong  goto error
 *
 * sentinel just tell wrong and go to error ;similar to perror and exit
 * 	of course  all of these have filename and line numbers and will 
 * 	clean the error number
 *
 * check_debug just like check , but if NDEBUG , no output
 *
 * all  these need an error place to goto
 *
 */

#ifdef NDEBUG
#define debug(M , ...)
#else
#define debug(M , ...) fprintf(stderr , "DEBUG %s:%d " M "\n" , __FILE__ ,\
__LINE__ , ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "NONE" : strerror(errno))

#define log_err(M , ...)  fprintf(stderr , "(ERROR) %s:%d:errno: %s) " M "\n", __FILE__ , __LINE__ , clean_errno(),##__VA_ARGS__)

#define log_warn(M , ...)  fprintf(stderr , "(WARN) %s:%d:errno: %s) " M "\n", __FILE__ , __LINE__ , clean_errno(),##__VA_ARGS__)

#define log_info(M , ...)  fprintf(stderr , "(INFO) %s:%d:errno: %s) " M "\n", __FILE__ , __LINE__ , clean_errno(),##__VA_ARGS__)

#define check(A,M, ... ) if(!(A)) {log_err(M , ##__VA_ARGS__);errno = 0;goto error;}

#define sentinel(M , ...) {log_err(M , ##__VA_ARGS__);errno=0; goto error;}

#define check_mem(A) check((A) , "out of memeory")
#define check_debug(A , M , ...) if(!(A)) {debug(M, ##__VA_ARGS__);errno=0;goto error;}

#endif

