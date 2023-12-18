#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>

//	Find a better way later
//
//	Square data type
//	One bit is defined for every "square", and one bit is a "match"
//		"match" is a checksum basically -- if its NOT equal to match, that means
//		something went wrong.

typedef struct board_t 
	board;

//	todo: implement a garbage collector to take note of the board
//	and deallocate when done

//	Constructs an SOS board with row size r and col size c
board *constructBoard(unsigned int r, unsigned int c);

void deallocBoard(board *b);

//	gets the numerical index for accessing the array
//	convention: (c,r)
//			(0,0) , (1,0)	--	...		--> (col_l - 1,0) (c-axis)
//			(0,1)
//			|
//			:
//			|
//			\/				--	...		--> 
//		(0,row_l - 1)
//		(r-axis)
unsigned int getIndex(board *b, unsigned int c, unsigned int r);

void printBoardState(board *b);
#endif //_BOARD_H
