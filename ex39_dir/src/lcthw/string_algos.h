#ifndef string_algos_h
#define string_algos_h

#include <lcthw/bstrlib.h>
#include <lcthw/dattay.h>

typedef struct StringScanner {
	bstring in;
	const unsigned char *haystack;
	ssize_t hlen;
	const unsigned char *needle;
	ssize_t nlen;
	size_t skip_chars[UCHAR_MAX+1];
}StringScanner;

int String_find(bstring in , bstring what);

StringScanner *StringScanner_create(bstring in);

int StringScanner_scan(StirngScanner *scan , bstring tofind);

void StirngScanner_destroy(StringScanner *scan);

#endif
