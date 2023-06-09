#include <stdio.h>
#include <stdlib.h>
#include <sos.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct Player {
	int score;
	int wins;
	char *name;
};

int onePlayerGame(char* board, int *c, int *r){
	srand(time(NULL));
	struct Player guvnors[] = { //felt british
		0, 0, "Player 1",
		0, 0, "Computer"
	};
	
	int turn = rand()%2;
	
	printf("\nOur first player will be decided by a coin flip.\nThe first turn goes to ");
	(turn == 0) ? printf("%s.\n", guvnors[0].name) : printf("%s.\n", guvnors[1].name);

	//infinite loop, breaks when win is achieved
	while(1){
		int toBeAwarded;
		if(turn == 0){
			printf("\nIt is your turn, %s. Your score is %d.\n", guvnors[turn].name, guvnors[turn].score);
		drawMainBoard(board, c, r);
		toBeAwarded = playerMove(board, c, r); //kept since we need this for a check later
		} else{
			toBeAwarded = compyMove(board, c, r);
		}

		//starts turn, returns a value >0 if an SOS is made. val is dependent on amt of SOS's made.
		guvnors[turn].score += toBeAwarded;
		printf("%s's score is now: %d\n", guvnors[turn].name, guvnors[turn].score);
		if(!(toBeAwarded)){
			turn = !(turn);
		}
		if(winCond(board, c, r)){	
			break;
		}
	}
	int winner;
	if(guvnors[0].score == guvnors[1].score){
		winner = 0;
		guvnors[0].name = "Nobody";
	}
	else if(guvnors[0].score > guvnors[1].score){
		winner = 0;
	} else{
		winner = 1;
	}
	printf("\n****************************\nGAME END. The final scores: \n%s's score: %d\n%s's score: %d\nThe winner is: %s\n\nPlay again? (Y/N): ", guvnors[0].name, guvnors[0].score, guvnors[1].name, guvnors[1].score, guvnors[winner].name);
	switch(getch()){
		case 'Y':
			return 1;
			break;
		case 'N':
			return 0;
			break;
		default:
			return 0;
			break;
	}
}
