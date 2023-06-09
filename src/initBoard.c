#include <stdio.h>
#include <sos.h>

int initBoard(char *board, int *c, int *r, int rematch){

	/*
	 * say: c=5,r=3
	 * 
	 * 1	2	3	4	5
	 * 6	7	8	9	10
	 * 11	12	13	14	15
	*/
	for(int i = 0; i < ((*c) * (*r)); i++){
		board[i] = ' ';
	}
	if(rematch == 1){
		return 1;
	}
	//draws board for the first time
	//this is passing pointers to addresses
	drawMainBoard(board, c, r);

	printf("Will this be against a computer (c) or player (p)?: ");
	switch(getch()){
		case 'c': 
			printf("\n");
			return 1;
			break;
		case 'p': 
			printf("\n");
			return 2;
			break;
		default:
			printf("\ndrawMainBoard: please enter 'c' or 'p'.\n");
			break;
	}
	return 0;
}
