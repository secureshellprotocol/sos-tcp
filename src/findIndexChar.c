#include <stdio.h>
#include <sos.h>

int findIndexChar(char ltr, char num, int *c, int *r){
	//ltr corresponds to column
	//num corresponds to row
	
	//Take the letter, convert to an int in range 1 to *ltr. Take the num, convert to int range 0 to *num-1, multiply by *ltr. Sum the terms.
	//see findIndexInt.

	return ((ltr - 'A')) + ((num - '0') * (*c));
}
