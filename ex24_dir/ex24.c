#include<stdio.h>
#include"dbg.h"

#define MAX_DATA 100

typedef enum EyeColor{
	BLUE_EYES , GREEN_EYES , BROWN_EYES , 
	BLACK_EYES , OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
	"Blue" , "Green" , "Brown" , "Black" , "Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

int main( int ac ,char *av[]){
	Person you = { .age = 0};
	int i = 0;
	char *in = NULL;

	printf("what's your first name? ");
//	in = fgets(you.first_name , MAX_DATA -1 , stdin);
	in = gets( you.first_name);
	check(in != NULL , "failed to read first name");
	

	printf("how old are you? ");
	int rc = fscanf(stdin , "%d" , &you.age);
	check(rc > 0 , "you have to enter a number");

	printf("what color are your eyes? ");
	for( i = 0 ; i <= OTHER_EYES ; i++){
		printf("%d) %s\n" , i+1 , EYE_COLOR_NAMES[i]);
	}
	printf("> ");

	int eyes = -1;
	rc = fscanf(stdin , "%d" , &eyes);
	check( rc > 0 , "you have to enter a number");

	you.eyes = eyes -1;
//	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "do it right, "
//		"that's not an option");

	printf(" how much do you make an hour? ");
	rc = fscanf(stdin , "%f" , &you.income);
	check( rc >0 , "enter a floating pointer number");
	
	printf("--------RESULT-------------\n");
	
	printf("first name : %s" , you.first_name);
	printf("last name  : %s" , you.last_name);
	printf("age: %d\n" , you.age);
	printf("eye: %s\n" , EYE_COLOR_NAMES[you.eyes]);
	printf("income: %f\n" , you.income);

	return 0;
error:
	return -1;
}
