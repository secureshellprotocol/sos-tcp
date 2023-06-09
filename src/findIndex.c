#include <stdio.h>
#include <sos.h>

int findIndexInt(int col, int row, int *c, int *r){
	//takes row, multiplies it by c (the amount of total columns in the table
	//takes col and adds the adjusted row to it
	/*EX: *c = 5, *r = 5
	 * 	A	B	C	D	E	
	 * 	0	1	2	3	4	0
	 *	5	6	7	8	9	1
	 *	10	11	12	13	14	2
	 *	15	16	17	18	19	3
	 *	20	21	22	23	24	4
	 */

	//EX: 1(B), 2
	//	1 + ((2) * 5) = 1 + 10 = 11
	return (col) + ((row) * (*c));
}

int findIndexChar(char ltr, char num, int *c, int *r){
	//ltr corresponds to column
	//num corresponds to row
	
	//Take the letter, convert to an int in range 1 to *ltr. 
	//Take the num, convert to int range 0 to *num-1, multiply by *ltr. 
	//Sum the terms.
	//
	//see findIndexInt.

	return ((ltr - 'A')) + ((num - '0') * (*c));
}
