#ifndef __db_h
#define __db_h

#define DB_DIR "/usr/local/.database"
#define DB_FILE "/usr/local/.database/db"

int DB_init();
void DB_list();
int DB_find( char *url );
int DB_update( char *url);
bstring DB_load();

#endif
