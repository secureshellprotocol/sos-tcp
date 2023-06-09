#include <stdio.h>
#include <stdlib.h>
#include <sos.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//note: when a player gets a score, replace SOS with 111, ofc correspond to player num
//add an option to forefit
//add a "wimp" option for the user to have a computer play

struct Player {
	int score;
	int wins;
	char *name;
};

int twoPlayerGame(char* board, int *c, int *r){
	srand(time(NULL));
	struct Player guvnors[] = { //felt british
		0, 0, "Player 1",
		0, 0, "Player 2"
	};
	
	int turn = rand()%2;
	
	printf("Our first player will be decided by a coin flip.\nThe first turn goes to ");
	(turn == 0) ? printf("%s.\n", guvnors[0].name) : printf("%s.\n", guvnors[1].name);

	//infinite loop, breaks when win is achieved
	while(1){
		printf("It is your turn, %s. Your score is %d.\n", guvnors[turn].name, guvnors[turn].score);
		drawMainBoard(board, c, r);

		//starts turn, returns a value >0 if an SOS is made. val is dependent on amt of SOS's made.
		int toBeAwarded = playerMove(board, c, r); //kept since we need this for a check later
		guvnors[turn].score += toBeAwarded;
		printf("%s's score is now: %d\n", guvnors[turn].name, guvnors[turn].score);
		if(!(toBeAwarded)){ //winner goes again
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
