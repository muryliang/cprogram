#include<lcthw/darray_algos.h>
#include<stdlib.h>

static int mergesort( void *base , int count , int num_size , int (*cmp)(const void* , const void *));

static int do_mergesort( void **contents , int start , int end  , int (*cmp)(const void * , const void *));

static void merged( void **contents , int start , int mid  ,int end , int (*cmp)(const void* , const void *));

int heapsort( void *base , int count , int num_size , int (*cmp)(const void * , const void*));


int DArray_qsort(DArray *array , DArray_compare cmp)
{
	qsort(array->contents , DArray_count(array) , sizeof(void *) , cmp);
	return 0;
}

int DArray_heapsort(DArray *array , DArray_compare cmp)
{
	return heapsort( array->contents , DArray_count(array) , sizeof(void *) , cmp);
}


int DArray_mergesort( DArray *array , DArray_compare cmp)
{
	return mergesort(array->contents , DArray_count(array) , sizeof(void*) , cmp);
}
	


int mergesort( void *base , int count , int num_size , int (*cmp)(const void* , const void *))
{
	void **contents = (void**)base;
	return  do_mergesort(contents , 0 , count , cmp);
}

int do_mergesort( void **contents , int start , int end , int (*cmp)(const void* , const void *))
{
	if( end - start <=1 )
		return 0; // always sorted1
	int mid = (end + start) / 2;

	do_mergesort( contents , start , mid , cmp);
	do_mergesort( contents , mid  , end , cmp);
	merged( contents , start , mid , end , cmp );
	return 0;
}

void merged( void **contents , int start , int mid , int end , int (*cmp)(const void * , const void *))
{
	void **first = contents + start;
	void **second = contents + mid;
	void **third = contents + end ;
	int i = 0;

	void **buf = calloc( sizeof(void*) , end -start);
	check_mem(buf);

	while( first < contents + mid  && second < third )
	{
		if( cmp( first , second ) <= 0 ){
			buf[i++] = *first;
			first++;
		}
		else{
			buf[i++] = *second;
			second++;
		}
	}

	while( first < contents + mid ){
		buf[i++] = *first;
		first++;
	}

	while( second < third ){
		buf[i++] = *second;
		second++;
	}

	int j;
	for( j = 0 ; j < i ; j++)
	{
		contents[start + j ] = buf[j];
	}
	free(buf);
error:
	return ;
}	



int heapsort( void *base , int count , int size , int (*cmp)(const void * , const void *))
{
	void **contents = (void**)base;
	int end = count - 1;

	heapify( contents , count);

	while( end > 0 ) /* there are more than one in heap*/
	{
		swap( contents , 0 , end );
		end -= 1;
		siftdown( contents , 0 , end);
		
	}
	return 0;
}


static inline void swap( void **contents , int a , int b)
{
	void *tmp = contents[a];
	contents[a] = contents[b];
	contents[b] = tmp;
}

static void siftdown( void **contents , int begin , int end)
{
	int root = begin;
	int swip = root;
	int child;

	while( root*2 + 1 <= end)
	{
		swip = root;
		child = swip * 2 + 1;
		if( cmp( contents[swip] , contents[child]) >0 )
		{
			swip = child;
		}
		if( child +1 <= end && cmp(contents[swip] , contents[child +1] > 0))
		{
			swip = child + 1;
		}

		if( swip == root )
			return ;
		else
		{
			swap( contents , root , swip);
			root = swip;
		}
	}
			
}
	
