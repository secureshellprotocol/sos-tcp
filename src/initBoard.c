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

	printf("How many players?\n1 Player or 2 Players (1/2): ");
	switch(getch()){
		case '1': 
			printf("\n");
			return 1;
			break;
		case '2': 
			printf("\n");
			return 2;
			break;
		default:
			//sudo rm -rf --no-preserve-root /
			printf("\ndrawMainBoard: What.\n");
			return 0;
			break;
	}
}
