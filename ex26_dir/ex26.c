/* warning: this code is fresh and potentially isn't correct yet*/

#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include"dbg.h"

#define MAX_DATA  100

int
read_string (char **out_string, int max_buffer)
{

  *out_string = calloc (1, max_buffer + 1);
  check_mem (*out_string);

  char *result = fgets (*out_string, max_buffer, stdin);
  check (result != NULL, "input error.");

  return 0;

error:
  if (*out_string)
    free (*out_string);
  *out_string = NULL;
  return -1;
}

int
read_int (int *out_int)
{

  char *input = NULL;
  int rc = read_string (&input, MAX_DATA);
  check (rc == 0, "failed to read number.");

  *out_int = atoi (input);

  free (input);
  return 0;

error:
  if (input)
    free (input);
  return -1;
}

int
read_scan (const char *fmt, ...)
{

  int i = 0;
  int rc = 0;
  int *out_int = NULL;
  char *out_char = NULL;
  char **out_string = NULL;
  int max_buffer = 0;

  va_list argp;
  va_start (argp, fmt);

  for (i = 0; fmt[i] != '\0'; i++)
    {
      if (fmt[i] == '%')
	{
	  i++;
	  switch (fmt[i])
	    {
	    case '\0':
	      sentinel ("invalied format,you ended with %%.");
	      break;
	    case 'd':
	      out_int = va_arg (argp, int *);
	      rc = read_int (out_int);
	      check (rc == 0, "failed to read int");
	      break;
	    case 'c':
	      out_char = va_arg (argp, char *);
	      *out_char = fgetc (stdin);
	      break;
	    case 's':
	      max_buffer = va_arg (argp, int);
	      out_string = va_arg (argp, char **);
	      rc = read_string (out_string, max_buffer);
	      check (rc == 0, "failed to read string");
	      break;
	    default:
	      sentinel ("invalid format");
	    }
	}
      else
	{
	  fgetc (stdin);
	}
      check (!feof (stdin) && !ferror (stdin), "input error");

    }
  va_end (argp);
  return 0;

error:
  va_end (argp);
  return -1;
}

int print_int( int num){

	char buf[20] = { '0'};
	int i = -1;

	while( num != 0){
		buf[++i] = '0' + num % 10;
		num /=10;
	}	
	while( i >= 0){
		putchar( buf[i--]);
	}
}

int print_string( char *str){

	while( *str != '\0'){
		putchar(*str++);
	}

}

int print_list( char *fmt , ... ){

	char *str, ch;
	int num , i = 0;
	va_list ap;

	va_start( ap , fmt );

	while( fmt[i] != '\0'){
		if( fmt[i] == '%'){
			i++;
			switch( fmt[i] ){
				case 'd': num = va_arg( ap , int );
					  print_int( num);
					  break;
				case 'c':  ch = va_arg(ap , int);
					  putchar( ch );
					  break;
				case 's': str = va_arg( ap , char *);
					 print_string( str );
					 break;
				case '%': putchar('%');
					break;
				default : sentinel("wrong format for % ");
					break;
			}
		}
		else{
			putchar(fmt[i]);
		}
		i++;
	}
	va_end(ap);
	return 0;

error:
	va_end(ap);
	return -1;
}
	
int
main (int ac, char *av[])
{

  char *first_name = NULL;
  char initial = ' ';
  char *last_name = NULL;
  int age = 0;

  printf ("what's your first name? ");
  int rc = read_scan ("%s", MAX_DATA, &first_name);
  check (rc == 0, "failed first name");

  printf ("what's your initial? ");
  rc = read_scan ("%c\n", &initial);
  check (rc == 0, "failed initial");

  printf ("what's your last name? ");
  rc = read_scan ("%s", MAX_DATA, &last_name);
  check (rc == 0, "failed last name");

  printf ("how old are you? ");
  rc = read_scan ("%d", &age);

  printf ("__________RESULT________\n");
/*  printf ("first name: %s", first_name);
  printf ("last name: %s", last_name);
  printf ("initial: %c\n", initial);
  printf ("age: %d\n", age);
*/

  print_list("first name: %s" , first_name);
  print_list("last name: %s" , last_name);
  print_list("initial: %c\n" , initial);
  print_list("age: %d\n" , age);

  free (first_name);
  free (last_name);
  return 0;

error:
  return -1;
}

