#ifndef __cmd_h
#define __cmd_h

#include<apr_pool.h>

#define DEPENDS_PATH "/tmp/DEPENDS"
#define TAR_GZ_SRC  "/tmp/pkg-src,tar.gz"
#define TAR_BZ2_SRC "/tmp/pkg-src.tar.bz2"
#define BUILD_DIR "/tmp/pkg-build"
#define CONFIGURE_SCIRPT "/tmp/pkg-build/configure"
#define GIT_PAT "*.git"
#define DEPENDS_PAT "*DEPENDS"
#define TAR_GZ_PAT "*.tar.gz"
#define TAR_BZ2_PAT "*.tar.bz2"


enum CommandType {
	COMMAND_NONE , COMMAND_INSTALL , COMMAND_LIST , COMMAND_FETCH,
	COMMAND_INIT ,COMMAND_BUILD
};

int Command_fetch(apr_pool_t *t , const char *url , int fetch_only);
int Command_install(apr_pool_t *t , const char *url , const char*configure_opt , 
			const char *make_opt , const char *install_opt);
int Command_depends(apr_pool_t *t ,const char *path);
int Command_install(apr_pool_t *t , const char *url , const char*configure_opt , 
			const char *make_opt , const char *install_opt);

#endif
