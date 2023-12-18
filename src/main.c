#include "../include/sos.h"

//collect players + names
//	shld be struct w name and sockfd
//start game
//probe for board size
//once both enter valid board, randomly select board from either player
//other player starts
//

int main(){
	board *main_board = constructBoard(3, 3);
	printBoardState(main_board);

	deallocBoard(main_board);

	main_board = constructBoard(6, 6);
	printBoardState(main_board);

	deallocBoard(main_board);

	return 0;
}
