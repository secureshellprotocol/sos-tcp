#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../include/sos.h"

#define BITS_PER_SQUARE 2

//	todo: implement a garbage collector to take note of the board
//	and deallocate when done

//	Board type
typedef struct board_t{
	//square cheat sheet
	//	00 - empty
	//	01 - S
	//	10 - O
	//	11 - unused / delimiter?
	//	
	//	this lets us make comparisons based on just the lsb
	//		if its 1, its an s
	//		if its 0, its an o (woh)
	//		GAMING!!!!!!

	unsigned int row_c;	//number of rows
	unsigned int col_c; //number of cols
	
	unsigned int gridsize; //number of total squares
	
	//We're building a grid of chars, which have the smallest decade of sizeof(char) bits. 
	//	each "square" takes up BITS_PER_SQUARE bits, so we allocate BITS_PER_SQUARE * row_c * (col_c+1) bits
	//	times (1 byte / sizeof(char) bits) to get what we want. the plus 1 ensures we never
	//	end up with a deficiency.
	char * grid;

} board;

//	Constructs an SOS board with row size r and col size c
//		boards cannot exceed 16 columns or 16 rows or go below 3 columns or 3 rows
//		will return a nullptr if it does
//
//	Generally, players will request a board size and of their choices, one player's size
//	will be randomly elected as the canon size, and the other player will get first move
//		The election generally throws out bullshit and asks the player to repick, but more
//		error checking is always good
board *constructBoard(unsigned int r, unsigned int c){
	//invalid board size -- you are ded, no big surprise
	if(r >= 16 || r <= 3 || c >= 16 || r <= 3){
		return NULL;
	}

	board *b = (board *) malloc(sizeof(board));
	b->row_c = r;
	b->col_c = c;
	
	b->gridsize = ( r * (c + 1) * BITS_PER_SQUARE ) / sizeof(char); 
	b->grid = (char *) malloc(b->gridsize * sizeof(char));

	memset(b->grid, 0, b->gridsize);
	return b;
}

void deallocBoard(board *b){
	free(b);
}

//	gets the numerical index for accessing the array
//	convention: (c,r)
//			(0,0) , (1,0)	--	...		--> (col_c - 1,0) (c-axis)
//			(0,1)
//			|
//			:
//			|
//			\/				--	...		--> 
//		(0,row_c - 1)
//		(r-axis)
unsigned int getIndex(board *b, unsigned int c, unsigned int r) {
	if(r >= b->row_c || c >= b->col_c) { return -1; }
	
	return (r * b->row_c) + c;
}

void printBoardState(board *b){
	for(int i = 0; i < b->gridsize; i++){
	
	} 

	printf("\n");
	return;
}
