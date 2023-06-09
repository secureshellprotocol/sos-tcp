#include <stdio.h>
#include <sos.h>

int main(){
	int c, r;
	
	printf("\nWelcome to James's game of SOS!\nTo start, please state the length and width of the board you would like!\n");
	while(1){
		//scanf("%d", &c);
		//scanf("%d", &r);
		printf("Enter Length: ");
		c = getch() - '0';
		printf("Enter Width: ");
		r = getch() - '0';
		if(c >= 3 && r >= 3){
			break;
		}
		printf("SOS: Invalid Input, try again.\n");
	}
	printf("\n");
	char board[(c * r)];
	
	//creates a board full of empties
	//takes the return and starts a game based on the result
	switch(initBoard(board, &c, &r, 0)){
		case 1:
			while(420){
				if(onePlayerGame(board, &c, &r)){
					initBoard(board, &c, &r, 1);
					continue;
				}
				break;
			}
			break;
		case 2:
			while(420){
				if(twoPlayerGame(board, &c, &r)){
					initBoard(board, &c, &r, 1);
					continue;
				}
				break;
			}
			break;
		default:
			
			break;
	}
	return 0;
}
