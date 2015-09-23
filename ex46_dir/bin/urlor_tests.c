#include <lcthw/tstree.h>
#include <stdio.h>
#include <lcthw/bstrlib.h>
#include <lcthw/dbg.h>

TSTree *add_route_data(TSTree *routes , bstring line )
/* take line from load route func , break into two parts 
 * store into the tstree  , first as key , second as data
 */
{
	struct bstrList *data = bsplit(line , ' ');
	check(data->qty == 2 , "line '%s' does not have  2 columns" ,
		bdata(line));

	routes = TSTree_insert(routes , 
		bdata(data->entry[0] ), blength(data->entry[0]),
		bstrcpy(data->entry[1]));

	bstrListDestroy(data);

	return routes;

error:
	return NULL;
}

TSTree *load_routes(const char *file)
/* open file , read line by line  the pairs of key & data
 * use add route data to store them in the tree
 */
{
	TSTree *routes = NULL;
	bstring line = NULL;
	FILE *routes_map = NULL;
	
	routes_map = fopen(file , "r");
	check(routes_map != NULL , "failed to open routes: %s " , file );
	
	while((line = bgets((bNgetc)fgetc , routes_map ,'\n')) != NULL )
	{
		check(btrimws(line) == BSTR_OK , "failed to trim line");
		routes = add_route_data(routes , line);
		check(routes != NULL , "failed to add route");
		bdestroy(line);
	}

	fclose(routes_map);
	return routes;
error:
	if(routes_map) fclose(routes_map);
	if(line) bdestroy(line);
	
	return NULL;

}

bstring match_url(TSTree *routes , bstring url)
{
/*just use TSTree_search  and search_prefix to search urls
 */
	bstring route = TSTree_search(routes , bdata(url) , blength(url));

	if(route == NULL ){
		printf("no exact match found , trying prefix .\n");
		route = TSTree_search_prefix(routes , bdata(url) , blength(url));
	}
	return route;
}

bstring read_line(const char *prompt)
{
	printf("%s" , prompt);
	
	bstring result = bgets((bNgetc)fgetc , stdin , '\n');
	check_debug(result != NULL , "stdin closed");
	
	check(btrimws(result) == BSTR_OK , "failed to trim.");

	return result;
error:
	return NULL;
}

void bdestroy_cb(void *value , void *ignored)
{
	(void)ignored;
	bdestroy((bstring)value);
}

void destroy_routes(TSTree *routes)
{
	TSTree_traverse(routes , bdestroy_cb , NULL );
	TSTree_destroy(routes);
}

int main(int argc , char *argv[])
{
/*just echo the prompt and wait for a line to be enterred in
 *then search the url as the key to find data
 * then output
 */
	bstring url = NULL ;
	bstring route = NULL;
	check(argc == 2 , "usage: urlor <urlfile>");

	TSTree *routes = load_routes(argv[1]);
	check(routes != NULL , "your route file has an errro.");

	while(1){
		url = read_line("URL>");
		check_debug(url != NULL , "goodbye");
		route = match_url(routes , url);

		if(route) {
			printf("match %s == %s\n" , bdata(url) , bdata(route));
		} else{
			printf("fail;%s \n" , bdata(url));
		}
		
		bdestroy(url);
	}

	destroy_routes(routes);
	return 0;
error:
	destroy_routes(routes);
	return 1;
}




