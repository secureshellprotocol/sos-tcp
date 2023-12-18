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
	//		if its false, its not
	//		GAMING!!!!!!

	//	To be Precomputed.
	unsigned int bitsPerRow;
	unsigned int bytesPerRow;
	unsigned int trim;
	
	unsigned int row_c;	//number of rows
	unsigned int col_c; //number of cols
	
	unsigned int gridsize; //number of total squares
	
	//We're building a grid of chars, which have the smallest decade of 8 bits. 
	//	each "square" takes up BITS_PER_SQUARE bits, so we allocate BITS_PER_SQUARE * row_c * (col_c+1) bits
	//	times (1 byte / 8 bits) to get what we want. the plus 1 ensures we never
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
	if(r > 16 || r < 3 || c > 16 || r < 3){
		return NULL;
	}

	board *b = (board *) malloc(sizeof(board));
	b->row_c = r;
	b->col_c = c;
	
	b->bitsPerRow = c * BITS_PER_SQUARE;
	b->bytesPerRow = (b->bitsPerRow + 7) / 8;
	b->trim = ((b->bytesPerRow * 8) - b->bitsPerRow) / b->bytesPerRow;
	
	b->gridsize = ((r * b->bytesPerRow)); 
	b->grid = (char *) malloc(b->gridsize * sizeof(char));

	memset(b->grid, 0x00, b->gridsize);
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

	for(unsigned int i = 0; i < b->gridsize; i++){ //iterate every byte
		if(i % b->bytesPerRow == 0){
			printf("%c",'\n');
		}

		//keep in mind, for every i, we're observing a byte
		//so that means we have to do a little trolling and go bit by bit
		//for ease, we chop off excess on every row
		//so for a 3x3 row, with BITS_PER_SQUARE = 2:
		//	bits per row: 3 colums * 2 bits per square = 6 bits
		//	byte per row: ((6) + 7) / 8 = 13/8 = 1
		//		Where did 7 come from?
		//		magic number
		//		just guarantees we'll round down and get the min amt of bytes
		//		we need, but not undershoot
		//
		//	alloc'd 3 rows * 1 byte per row = 3 bytes
		//	trim (8 bits per byte * 1 byte per row) - 6 bits per row = 2 bits from every row
		//	so we have some shit like
		//		000000000000000000000000
		//	and we have 3 columns, so in every row we need 3*2 = 6 bits
		//		000000
		//		000000
		//		000000000000
		//	WTF?????????????
		//	ok chill we allocated in decades of 8
		//	so we have something more like
		//		00000000
		//		00000000
		//		00000000
		//	except the last 2 bits are kinda cringe
		//	so we ignore them!
		//	every time we iterate, we iterate 8 bits minus our trim
		//	8 - 2 = 6 bits
		//		000000<skipped>
		//		000000	...
		//		000000	...
		//	then we just newline once we iterate
		//
		//	what if we have more than 1 byte per row, you may be asking????
		//	bits per row = 6 columns * 2 bits per square = 12 bits
		//	bytes per row = ((12) + 7) / 8 = 19/8 = 2 bytes
		//	alloc'd 6 rows * 2 bytes per row = 12 bytes
		//	trim (8 bits per byte * 2 bytes per row) - 12 bits per row = 4 bits from every row
		//		from every byte: 4 bits to trim from every row / 2 bits per row = 2 bits from every byte
		//	trim 2 bits from every byte
		//	we add a precondition to newline on byte i % bytesPerRow
		//	win

		for (unsigned int j = 0; j < (8 - b->trim) ; j++) { //iterate every bit up to trim
			printf("%d", !!((b->grid[i] << j) & 0x80));
		}
	} 

	printf("\n");
	return;
}
