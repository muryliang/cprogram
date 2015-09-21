#ifndef _queue_h
#define _queue_h

#include<lcthw/list.h>

typedef List Queue;
struct curstruct{
	void *value;
};
struct curstruct  curbase;
struct curstruct *cur = &curbase;
int count = 0;
ListNode *p;

#define Queue_create()  List_create()
#define Qeueu_destroy(q) List_dewtroy(q)
#define Queue_send(q,element)  List_push(q, element)
#define Queue_recv(q )  List_shift(q)
#define Queue_count(q)  q->count
#define QUEUE_FOREACH(q,cu)  for( cur->value = q->first->value ,p = q->first ; count < q->count;count++,p=p->next)

#define Queue_destroy(q)  List_destroy(q)
#define Queue_peek(q)  q->first->value

#endif
