#ifndef _stack_h
#define _stack_h

typedef void *Stack;
static int sp = -1;

typedef struct curstruct {
	void *value;
} curstruct;

int j = 0;

curstruct curbase;
curstruct *cur = &curbase;

#define MAX 100

#define Stack_create() calloc(MAX ,sizeof(void*))

#define Stack_count(a)  (sp+1)

#define Stack_destroy(a)  free(a)

#define Stack_push(stack,element)   (stack[++sp] = element)
#define Stack_pop(stack)  stack[sp--]
#define Stack_peek(stack) stack[sp]
#define STACK_FOREACH(stack,cu)  for(  cu->value=stack[0], j = 0 ; \
					(j <= sp) && (cu->value = stack[j] ); j++) 

#endif
