#include "minunit.h"
#include<lcthw/radixmap.h>
#include<time.h>

static int make_random(RadixMap *map)
{
	size_t i = 0;
	
	for(i = 0 ; i < map->max -1 ; i++)
	{
		uint32_t key = (uint32_t)(rand() | (rand()<<16));
		check(RadixMap_add(map , key , i)== 0 , "failed to add key %u ." , key);
	}
	return i;
error:
	return 0;
}

static int check_order(RadixMap *map)
{
	RMElement d1 , d2;
	unsigned int i = 0;

	// only signal errors if any (should not be)
	
	for(i = 0 ; map->end >0 && i < map->end -1; i++)
	{
		d1 = map->contents[i];
		d2 = map->contents[i+1];
		
		if(d1.data.key > d2.data.key){
			debug("faile:i=%u , key: %u , value : %u , equals max ? %d\n" , i , d1.data.key , d1.data.value,
		d2.data.key == UINT32_MAX);
		return 0;
		}
	}	
	return 1;
}

static int test_search(RadixMap *map)
{
	unsigned i = 0;
	RMElement *d = NULL;
	RMElement *found = NULL;
	
	for( i = map->end / 2 ; i < map->end ; i++)
	{
		d= &map->contents[i];
		found = RadixMap_find(map , d->data.key);
		check(found != NULL , "didn't find %u at %u." , d->data.key ,i);
		check(found->data.key == d->data.key , "got the wrong result: %p:%u looking for %u at %u",
			found , found->data.key , d->data.key , i);
	}
	return 1;
error:
	return 0;
}

/*test for big number of element*/
static char *test_operations()
{
	size_t N = 200;

	RadixMap *map = RadixMap_create(N);
	mu_assert(map!= NULL , "failed to make the map");
	mu_assert(make_random(map) , "didn't make a random fake radixmap");

	RadixMap_sort(map);
	mu_assert(check_order(map),"failed to porperly sort the Radixmap.");
	
	mu_assert(test_search(map), "failed the search test");
	mu_assert(check_order(map), "radixmap didn't stay sorted after search");
	
	while(map->end > 0 ){
		RMElement *el = RadixMap_find(map , map->contents[map->end /2].data.key);
	mu_assert(el != NULL , "should get a result");
	
	size_t old_end  = map->end;

	mu_assert(RadixMap_delete(map, el) == 0 , "didn't delete it");
	mu_assert(old_end -1 == map->end , "wrong size after delete");
	
	/*test that the end is now the old value , but uint32 max so ti trails off*/
	mu_assert(check_order(map), "radixmap didn't stay ordered after delete.");
	}

	RadixMap_destroy(map);
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	srand(time(NULL));
	
	mu_run_test(test_operations);
	return NULL;

}

RUN_TESTS(all_tests);
