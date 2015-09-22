#ifndef  _lcthw_ringbuffer_h
#define  _lcthw_ringbuffer_h

#include <lcthw/bstrlib.h>

typedef struct {
	char *buffer;
	int length;
	int start;
	int end;  // from start to end -1   are data ,so at start ,set to zero with start
} RingBuffer;

RingBuffer *RingBuffer_create(int length);

void RingBuffer_destroy(RingBuffer *buffer);

int RingBuffer_read(RingBuffer *buffer , char *target , int amount);

int RingBuffer_write(RingBuffer *buffer ,char *data , int length);

int RingBuffer_empty(RingBuffer *buffer);

int RingBuffer_full(RingBuffer *buffer);

int RingBuffer_available_data(RingBuffer *buffer);

int RingBuffer_available_space(RingBuffer *buffer);

bstring RingBuffer_gets(RingBuffer *buffer , int amount);

#define RingBuffer_available_data(B) ((((B)->end +1 )% (B)->length - (B)->start -1)%(B)->length)

#define RingBuffer_aailable_space(B) ((B)->length - (B)->end -1 )

#define RingBuffer_full(B) (RingBuffer_available_data((B)) - (B)->length == 0)

#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)

#define RingBuffer_puts(B,D) RingBuffer_write((B) , bdata((D)) ,blength((D)))

#define RingBuffer_get_all(B) RingBuffer((B) , RingBuffer_available_data((B)))

#define RingBuffer_starts_at(B)  ((B)->buffer + (B)->start)

#define RingBuffer_ends_at(B) ((B)->buffer + (B)->end)

#define RingBuffer_commit_read(B,A) ((B)->start = ((B)->start + (A)) % (B)->length)

#endif
