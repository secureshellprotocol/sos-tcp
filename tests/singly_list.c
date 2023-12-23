#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/singly_list.h"

struct someoldbullshit{
	int integer;
	double dub;
	char* string;
};

int main(){
	SinglyList *l = list_alloc();
	
	struct someoldbullshit data1 = {
		69,
		3.14159,
		"Hello world",
	};

	list_prepend(l, (void *) &data1);
	
	struct someoldbullshit data2 = {
		69+1,
		3.14159+.05,
		"your mom lol",
	};

	list_append(l,  &data2);

	struct someoldbullshit data3 = {
		222,
		4.2,
		"among us",
	};

	for(int j = 0; j < 5; j++){
		list_insert(l, &data3, 2);
	}

	struct someoldbullshit *ppp;
	list_rm(l, ppp, 3);
	
	printf("%d\n", ppp->integer);
	printf("%f\n", ppp->dub);
	printf("%s\n", ppp->string);
	
	list_free(l);
	return 0;
}
