#include <stdio.h>
#include <sos.h>

char getch(){
	char c = getchar();
	while(getchar() != '\n');//clears input and cleans up
	return c;

}
