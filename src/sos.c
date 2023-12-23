#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "../include/sos.h"

#define BITS_PER_SQUARE 2


// https://www.chiefdelphi.com/t/extracting-individual-bits-in-c/48028
//get a bit from a variable
#define GETBIT(var, bit)	(((var) >> (bit)) & 1)

//set a bit to 1
#define SETBIT(var, bit)	var |= (1 << (bit))

//set a bit to 0
#define CLRBIT(var, bit)	var &= (~(1 << (bit)))

static char letterMap[] = {'-', 'S', 'O', ' '};

//	todo: implement a garbage collector to take note of the board
//	and deallocate when done

//	Board type
typedef struct board_t{
	//	this lets us make comparisons based on just the lsb
	//		if its 1, its an s
	//		if its 0, its an o (woh)
	//		if its false, its not
	//		GAMING!!!!!!

	unsigned int bitsPerRow;
	unsigned int bytesPerRow;
	unsigned int trim;
	
	unsigned int row_c;	//number of rows
	unsigned int col_c; //number of cols
	
	unsigned int gridsize;
	
	char * grid;

	typedef struct player_t{
		char* name;
		unsigned int score;
	} GamePlayer;

	//	Linked List of players
	GamePlayer *player;
	unsigned int turn;

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

	//construct the board
	board *b = (board *) malloc(sizeof(board));
	b->row_c = r;
	b->col_c = c;
	
	b->bitsPerRow = c * BITS_PER_SQUARE; // bits alloc'd for every row
	b->gridsize = ( ((r * b->bitsPerRow) + 7) / 8 ); // bytes alloc'd

	b->grid = (char *) malloc(b->gridsize * sizeof(char));

	memset(b->grid, 0x00, b->gridsize);

	//fill with empty players, we can allocate them later
	
	return b;
}

void deallocBoard(board *b){
	free(b);
}

int play(board *b, char c, unsigned int r){
	//grabs the current player from board state
	
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
unsigned int __getIndex(board *b, char c_let, unsigned int r) {
	//sanitize
	c_let = toupper(c_let);
	if(c_let > 'Z' || c_let < 'A') { return -1; }
	
	//check within bounds
	unsigned int c = c_let - 'A';	
	if(r >= b->row_c || c >= b->col_c) { return -1; }	

	//ok so this does exist
	//calculate what bit we're on
	unsigned int currentBits = ( (b->row_c * r) + c * BITS_PER_SQUARE );
	unsigned int jump = (currentBits % 8) + 1;
	

	//todo work for arbitrary bits_per_square
	//	have it loop and append to a temporary char *
	//	depending on the number, have it eval against some
	//	known list of square values (map num --> letter)
	//	see: letterMap[]
	switch ( GETBIT(b->grid[ currentBits / 8 ], jump) ){
		case 0:
			goto l_false;	
		
		case 1:
			goto l_true;
	}
	
	//case 0
	l_false:
	switch ( GETBIT(b->grid[ currentBits / 8 ], jump + 1) ){
		case 0: //00
			return 0;
		case 1: //01
			return 1;
	}
	
	//case 1
	l_true:
	switch ( GETBIT(b->grid[ currentBits / 8 ], jump + 1) ){
		case 0: //10
			return 2;
		case 1: //11
			return 3;
	}

	//how did we get here?
	return -1;	
}



void __printBoardState(board *b){
	printf("%d\n", b->bitsPerRow);

	//print column chars
	printf("\t");
	for(char c = 0 + 'A'; c < (char)b->col_c + 'A'; c++){
		printf("%c ", c); 
	}

	for(unsigned int r = 0; r < b->row_c; r++){
		printf("\n%d\t", r);
		for(char c = 0 + 'A'; c < (char)b->col_c + 'A'; c++){
			printf("%c ", letterMap[ __getIndex(b, c, r) ]);
		}

	}

	printf("\n"); 
	return;
}
