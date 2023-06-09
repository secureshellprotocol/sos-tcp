#include <stdio.h>
#include <sos.h>

int winCond(char *board, int *c, int *r){
	for(int i = 0; i < *c; i++){
		for(int j = 0; j < *r; j++){
			if(board[findIndexInt(j, i, c, r)] == ' '){
				return 0; //if there is ANY free space, you suffer the fate of having to go through another turn
			}
		}
	}
	return 1;
}
