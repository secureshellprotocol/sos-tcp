#include <stdio.h>
#include <sos.h>

	//Identify what we're looking at
	//take that letter and check around
	//if its an s, look for o's
	//	if an o is discovered, continue on track and check for an s
	//	EX: (0,-1) is an o, check (0,-2) if its an S
	//if its an o, look for s's
	//	if an s is discovered, check opposite side for an s
	//	EX: (-1,-1) is an s, check (1,1)
	//
	//	CHECK FOR BOUNDS ALWAYS!!!!
	//	CHECK FOR MULTIPLE SUCCESSES ALWAYS!!!!!!!
	/*
	 *	(-1,-1)	(0,-1)	(1,-1)
	 *	(-1,0)	curInd	(1,0)
	 *	(-1,1)	(0,1)	(1,1)
	 */

int didScore(char *board, int *c, int *r, int currentIndex){
	int toBeAwarded = 0;

	//Each gets their own if statement so each statement is checked, and a short circuit doesnt occur (unlike using an OR)
	
	if(checkHoriz(board, c, r, currentIndex)){
		toBeAwarded++;
	}	
	
	if(checkVert(board, c, r, currentIndex)){
		toBeAwarded++;
	}
	
	if(checkDiagLtoR(board, c, r, currentIndex)){ 
		toBeAwarded++;
	}
	
	if(checkDiagRtoL(board, c, r, currentIndex)){
		toBeAwarded++;
	}
	return toBeAwarded;
}

/*	Cancerous boundary check functions
 * 	
 */

/* topOrBottom
 * A function which returns whether the value is bounded on
 * (T) The Topmost Row
 * (B) The Bottommost Row
 * or not (0)
 */

char topOrBottom(char *board, int *c, int *r, int *currentIndex){
	
	//max is always (*c) * (*r)
	//so that means bounds are:
      //le top row: 0 --> (c-1)
      //  (c-1)-i, where i is 0 to <c
      //le bottom : c*(r-1) --> (c*r)-1
      //  ((c*r)-1)-i, where i is 0 to c
      //le left side: c*0 --> c*(r-1)
      //  c*(r-i), where i is 0 to r-1
      //le right side: (c*1)-1 --> (c*r)-1
      //  (c*i)-1, where i is 1 to r
      //WHEN BOUNDARY IS HIT, JUST DONT EVEN BOTHER CHECKING

	/*EX: c=7, r=4
	 *
	 * 	A	B	C	D	E	F	G
	 * 	----------------------------
	 * 	0	1	2	3	4	5	6	| 0
	 * 	7	8	9	10	11	12	13	| 1
	 * 	14	15	16	17	18	19	20	| 2
	 * 	21	22	23	24	25	26	27	| 3
	 *
	 */

	if((*currentIndex - *c) < 0){ //Tests if in top row
		return 'T';
	}
	if((*currentIndex + *c) > ((*c) * (*r) - 1)){ //Tests if in bottom row
		return 'B';
	}

	return '0';
}

/* leftOrRight
 * a function which returns whether the value is bounded on
 * (L) The Leftmost Column
 * (R) The Rightmost Column
 * or not (0)
 */

char leftOrRight(char *board, int *c, int *r, int *currentIndex){

	if((*currentIndex - 1) == *currentIndex % *c){ //tests if leftmost
		return 'L';
 	}
 	if((*currentIndex + 1) % *c == 0){ //tests if rightmost
 		return 'R';
	}
	return '0';
}



//Returns 1 if SOS is found diagonally.
//Returns 0 if SOS is not found.

int checkDiag(char *board, int *c, int *r, int currentIndex){
	short topMost = currentIndex - (*c);
	short bottomMost = currentIndex + (*c);
	short leftMost = currentIndex - 1;
	short rightMost = currentIndex + 1; 
	
	if(topOrBottom(board, c, r, &currentIndex) == 'T'){ 
		topMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'B'){ 
		bottomMost = currentIndex;
 	}
	if(leftOrRight(board, c, r, &currentIndex) == 'L'){
		leftMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'R'){
		rightMost = currentIndex;
 	}
 	
	//case if O: check both sides for S
	//case if S: check both sides for O, recurse into function if O is found.
	//	To add on, if SOS is found, 1 is returned.
	switch(board[currentIndex]){
		case 'O':
			if((topMost == currentIndex) || (bottomMost == currentIndex) || (leftMost == currentIndex || rightMost == currentIndex)){
				return 0;
				break;
			} //check if upleft & lowright == 'S'
			else if(board[topMost - 1] == 'S' && board[bottomMost + 1] == 'S'){
				return 1;
				break;
			} else if(board[topMost + 1] == 'S' && board[bottomMost - 1] == 'S'){
				return 1;
				break;
			}
			else{
				return 0;
				break;
			}
		case 'S':		
			if(topMost != currentIndex){
				if(leftMost != currentIndex){ //test top left
					if(board[topMost - 1] == 'O'){
						return(checkDiag(board, c, r, topMost - 1));
						break;
					}
				} 
				if(rightMost != currentIndex){ //test top right
					if(board[topMost + 1] == 'O'){
						return(checkDiag(board, c, r, topMost + 1));
						break;
					}
				}
			} else if(bottomMost != currentIndex){	
				if(leftMost != currentIndex){ //test bottom left
					if(board[bottomMost - 1] == 'O'){
						return(checkDiag(board, c, r, bottomMost - 1));
						break;
					}	
				} 
				else if(rightMost != currentIndex){ //test bottom right
					if(board[bottomMost + 1] == 'O'){
						return(checkDiag(board, c, r, bottomMost + 1));
						break;
					}
				}
			}
			return 0;
			break;
	}
	//something went wrong -- oops!
	return 0;
}

/*
 * checks a score from top left to bottom right
 * #
 *  #
 *   #
 */
int checkDiagLtoR(char *board, int *c, int *r, int currentIndex){
	//bound check
	short topMost = currentIndex - (*c);
	short bottomMost = currentIndex + (*c);
	short leftMost = currentIndex - 1;
	short rightMost = currentIndex + 1; 
	if(topOrBottom(board, c, r, &currentIndex) == 'T'){
		topMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'B'){
		bottomMost = currentIndex;
 	}
	if(leftOrRight(board, c, r, &currentIndex) == 'L'){
		leftMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'R'){
		rightMost = currentIndex;
 	}
	//case if O: check both sides for s
	//case if S: check both sides for O, recurse into function if O is found. GAMER
	//	To add on, if SOS is found, 1 is returned. 1 is returned then.
	switch(board[currentIndex]){
		case 'O':
			if((topMost == currentIndex) || (bottomMost == currentIndex) || (leftMost == currentIndex || rightMost == currentIndex)){
				return 0;
				break;
			} //check if upleft & lowright == 'S'
			else if(board[topMost - 1] == 'S' && board[bottomMost + 1] == 'S'){
				return 1;
				break;
			}
			else{
				return 0;
				break;
			}
		case 'S':		
			if(topMost != currentIndex){
				if(leftMost != currentIndex){ //test top left
					if(board[topMost - 1] == 'O'){
						return(checkDiagLtoR(board, c, r, topMost - 1));
						break;
					}
				} 
			} else if(bottomMost != currentIndex){	 
				if(rightMost != currentIndex){ //test bottom right
					if(board[bottomMost + 1] == 'O'){
						return(checkDiagLtoR(board, c, r, bottomMost + 1));
						break;
					}
				}
			}
			return 0;
			break;
	}
	return 0;
}
/*
 * checks a score from top right to bottom left
 *    #
 *   #
 *  #
 */
int checkDiagRtoL(char *board, int *c, int *r, int currentIndex){
	//bound check
	short topMost = currentIndex - (*c);
	short bottomMost = currentIndex + (*c);
	short leftMost = currentIndex - 1;
	short rightMost = currentIndex + 1; 
	if(topOrBottom(board, c, r, &currentIndex) == 'T'){
		topMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'B'){
		bottomMost = currentIndex;
 	}
	if(leftOrRight(board, c, r, &currentIndex) == 'L'){
		leftMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'R'){
		rightMost = currentIndex;
 	}
	//case if O: check both sides for s
	//case if S: check both sides for O, recurse into function if O is found. GAMER
	//	To add on, if SOS is found, 1 is returned. 1 is returned then.
	switch(board[currentIndex]){
		case 'O':
			if((topMost == currentIndex) || (bottomMost == currentIndex) || (leftMost == currentIndex || rightMost == currentIndex)){
				return 0;
				break; 
			} else if(board[topMost + 1] == 'S' && board[bottomMost - 1] == 'S'){
				return 1;
				break;
			}
			else{
				return 0;
				break;
			}
		case 'S':		
			if(topMost != currentIndex){ 
				if(rightMost != currentIndex){ //test top right
					if(board[topMost + 1] == 'O'){
						return(checkDiagRtoL(board, c, r, topMost + 1));
						break;
					}
				}
			} else if(bottomMost != currentIndex){	
				if(leftMost != currentIndex){ //test bottom left
					if(board[bottomMost - 1] == 'O'){
						return(checkDiagRtoL(board, c, r, bottomMost - 1));
						break;
					}	
				} 	
			}
			return 0;
			break;
	}
	return 0;
}

//Returns 1 if SOS is found horizontally.
//Returns 0 if SOS is not found.

int checkHoriz(char *board, int *c, int *r, int currentIndex){
	//bound check
	short leftMost = currentIndex - 1;
	short rightMost = currentIndex + 1;
	if(leftOrRight(board, c, r, &currentIndex) == 'L'){
		leftMost = currentIndex;
 	} else if(leftOrRight(board, c, r, &currentIndex) == 'R'){
		rightMost = currentIndex;
 	}
	//case if O: check both sides for s
	//case if S: check both sides for O, recurse into function if O is found. GAMER
	//	To add on, if SOS is found, 1 is returned. 1 is returned then.
	switch(board[currentIndex]){
		case 'O':
			if((leftMost == currentIndex) || (rightMost == currentIndex)){
				return 0;
				break;
			} else if(board[leftMost] == 'S' && board[rightMost] == 'S'){
				return 1;
				break;
			} else{
				return 0;
				break;
			}
		case 'S': //le framework is built. O worky as intended.
			if(leftMost != currentIndex){
				if(board[leftMost] == 'O'){
					return checkHoriz(board, c, r, leftMost);
					break;
				}
			} else{
				return 0;
				break;
			} 
			if(rightMost != currentIndex){
				if(board[rightMost] == 'O'){
					return checkHoriz(board, c, r, rightMost);
					break;
				}
			} else{
				return 0;
				break;
			}
			return 0;
			break;
	}
	return 0;
}

//Returns 1 if SOS is found horizontally.
//Returns 0 if SOS is not found.

int checkVert(char *board, int *c, int *r, int currentIndex){
	//bound check
	short topMost = currentIndex - (*c);
	short bottomMost = currentIndex + (*c);
	if(topOrBottom(board, c, r, &currentIndex) == 'T'){
		topMost = currentIndex;
 	} else if(topOrBottom(board, c, r, &currentIndex) == 'B'){
		bottomMost = currentIndex;
 	}
	//case if O: check both sides for s
	//case if S: check both sides for O, recurse into function if O is found. GAMER
	//	To add on, if SOS is found, 1 is returned. 1 is returned then.
	switch(board[currentIndex]){
		case 'O':
			if((topMost == currentIndex) || (bottomMost == currentIndex)){
				return 0;
				break;
			} else if(board[topMost] == 'S' && board[bottomMost] == 'S'){
				return 1;
				break;
			} else{
				return 0;
				break;
			}
		case 'S': 
			if(topMost != currentIndex){
				if(board[topMost] == 'O'){
					return checkHoriz(board, c, r, topMost);
					break;
				}
			} else{
				return 0;
				break;
			} 
			if(bottomMost != currentIndex){
				if(board[bottomMost] == 'O'){
					return checkHoriz(board, c, r, bottomMost);
					break;
				}
			} else{
				return 0;
				break;
			}
			return 0;
			break;
	}
	return 0;
}
