#include <stdio.h>
#include <sos.h>

//Player places one s or o, ok cool move on. return 0
//player places one s or o and makes SOS, ok cool, return the score to be added
//	This is determined by the didScore function, score should be 1 * the amount of sos's made

//Make this player-agnostic so we can adapt the computer moves to this later


int playerMove(char *board, int *c, int *r){
	char ltr;
	char num;
	
	while(666){ //Happy Halloween! This code will terrify you!
		printf("Please enter what spot you'd like to look at.\n");
		printf("Enter Letter: ");
		ltr = getch();
		printf("Enter Number: ");
		num = getch();
		
		//Sanity Checks:
		//Ensures ltr is valid based on board size
		if(ltr < 'A' || ltr >= ('A' + *c)){
			printf("playerMove: Bullshit! Repick! (Check the case of your input!)\n");
			continue;
		}
		//ensures num is valid based on board size
		if(num < '0' || num >= ('0' + *r)){
			printf("playerMove: Bullshit! Repick! (Check the case of your input!)\n");
			continue;
		}
		//ensures the spot isnt occupied already
		if((board[findIndexChar(ltr, num, c, r)] == 'S') || (board[findIndexChar(ltr, num, c, r)] == 'O')){
			printf("playerMove: Taken! Repick!\n");
			continue;
		}
		
		char in;
		board[findIndexChar(ltr, num, c, r)] = '#'; //temp spot to sanity-check the player and make sure they are choosing the right spot.
		drawMainBoard(board, c, r);
		
		printf("Place an S or O at %c%c? (R to repick a spot): ", ltr,num);	
		in = getch();
		if((in == 'S') || (in == 'O')){
			board[findIndexChar(ltr, num, c, r)] = in;
			drawMainBoard(board, c, r);
			int toBeAwarded = didScore(board, c, r, findIndexChar(ltr, num, c, r)); 
			if(toBeAwarded){ //determines if sos is achieved
				printf("\nYou Scored! Good job!!\n");	
				return toBeAwarded;
			} else{
				return 0;
			}
			break;
		} else if(in == 'R'){
			board[findIndexChar(ltr, num, c, r)] = ' ';
			continue;
		} else{
			printf("playerMove: Invalid! Repick!\n");
			board[findIndexChar(ltr, num, c, r)] = ' ';
			//this is basically the same as repicking
		}

	}
}
