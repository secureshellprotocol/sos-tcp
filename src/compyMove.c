#include <stdio.h>
#include <sos.h>
#include <stdlib.h>

int botGuesstimate(char *board, int *c, int *r, char considering, int *index);

//Player places one s or o, ok cool move on. return 0
//player places one s or o and makes SOS, ok cool, return the score to be added
//	This is determined by the didScore function, score should be 1 * the amount of sos's made

int compyMove(char *board, int *c, int *r){
	//char ltr;
	//char num;
	//keeping printf's around so we know whats happening. Outwardly, the player will just see:
	//"The Computer has made a move! 'S' has been placed at 'A1'
	//the quoted stuff can be whatever, man
	while(666){
		char in;
		int index;
		int indexS;
		int indexO;
		if(botGuesstimate(board, c, r, 'S', &indexS) < botGuesstimate(board, c, r, 'O', &indexO)){
			in = 'O';
			index = indexO;
		} else{
			in = 'S';
			index = indexS;
		}
		board[index] = in;
		int toBeAwarded = didScore(board, c, r, index);
		
		//index corresponds to a letter.
		//c = 5
		//r = 4
		//	A	B	C	D	E	
		//						0
		//						1
		//				13		2
		//						3
		//
		//	D --> 3
		//	13 = 3 + (2 * c)

		drawMainBoard(board, c, r);
		printf("Computer placed %c at index %d", in, index);
		if(toBeAwarded){
			return toBeAwarded;
		} else{
			return 0;
		}
			
	}
}

int botGuesstimate(char *board, int *c, int *r, char considering, int *index){ //This is not completely original, I had help from Evan, who set me on the path for developing this algorithm
	int worthy[(*c) * (*r)];
	int max;

	for(int i = 0; i < (*c) * (*r); i++){
		if(board[i] != ' '){
			worthy[i] = -1;
		} else {
			worthy[i] = 0;
			max = i;
		}
	}
	int score = 0;
	for(int i = 0; i < (*c) * (*r); i++){
		if(worthy[i] != -1){
			board[i] = considering;
			//printf("%d", i);
			int test = didScore(board, c, r, i);
			//printf("%d\n", test);
			if(score < test){
				max = i;
				score = test;
			}
			board[i] = ' ';
		}
	}
	
	*index = max;

	//printf("SCORE: %d\n", score);
	//printf("MAX: %d\n", max);	
	return score;
}

