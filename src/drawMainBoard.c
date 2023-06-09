#include <stdio.h>
#include <sos.h>

void drawMainBoard(char *board, int *c, int *r){
	// int c is a column
	// int r is a row
	printf("<");
	for(int k = 0; k < *c; k++){//prints out le letters for organization of board
		printf(" %c  ", 'A' + k);
	}
	printf(">\n");
	for(int i = 0; i < *r; i++){ //start on row
		
		for(int j = 0; j < *c; j++){ //print out entire row
			printf("| %c ", board[findIndexInt(j, i, c, r)]); //rinse and repeat, moving down 1 column space
		}
		printf("|} %d\n", i);
		if(i == *r - 1){
			break;
		}
		for(int k = 0; k < ((*c) * 4) + 1; k++){
			printf("-");
		}
		printf("\n");
	}
	return;
}
