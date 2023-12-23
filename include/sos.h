#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>

typedef struct board_t 
	board;

//	Constructs an SOS board with row size r and col size c
board *constructBoard(unsigned int r, unsigned int c);

//	deallocates the board, and all associated data
void deallocBoard(board *b);

//	Makes a move on a certain index
//	user should specify the index, and then this fcn jumps into
//	an internal routine asking for which piece to place
//	
//	normally, the board includes a predefined set of pieces (in our case,
//		S, O, -, and invalid), and all the player should be doing is stating
//		a row num and col char
int play(board *b, char c, unsigned int r);


//	Internal functions -- usually you shouldnt touch these

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
unsigned int __getIndex(board *b, char c, unsigned int r);

int __makeMove(board *b, char opt);

void __printBoardState(board *b);
#endif //_BOARD_H
