#include <stdio.h>
#include <time.h>
#include "../include/sos.h"

//collect players + names
//	shld be struct w name and sockfd
//start game
//probe for board size
//once both enter valid board, randomly select board from either player
//other player starts
//

int main(){

	unsigned int rows = 0;
	printf("Num of rows: ");
	scanf("%ud", &rows);
	unsigned int cols = 0;
	printf("Num of cols: ");
	scanf("%ud", &cols);

	clock_t start, end;
	double cpu_time;
	start = clock();
	board *main_board = constructBoard(cols,rows);
	printBoardState(main_board);

	deallocBoard(main_board);
	end = clock();
	cpu_time = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("\nTime to generate board in seconds: %f\n", cpu_time);

	return 0;
}
