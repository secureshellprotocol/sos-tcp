SOS is a game like tic tac toe, except its with S's and O's, and instead of  
making a line of the same character, each player can choose to place either  
an S or an O. A player scores when they make a sequence S-O-S in any direction.  

Building:
Makefile is provided.  
Run "make" in the directory containing this README, a binary should appear in bin/  
Run "make clean" to rm all binaries and .o files  

This is just a personal project.  
goals for myself  
* working TCP implementation for over the network play.
	* simple telnet implementation that transmits all/parts of stdout to users,  
	and waits for input from users we care about. Like a dumb terminal  
![Dumb Terminal, wikipedia](https://upload.wikimedia.org/wikipedia/commons/thumb/7/70/Stdstreams-notitle.svg/1920px-Stdstreams-notitle.svg.png)
	
* proper AI with tune-able difficulty
	* once a static map is made, a "nav mesh" is made so its quicker to know
	where specific tiles are relative to a specific index on the board.
	* generating AI moves with a helper program, making use of whatever
	game theory i can make sense of because it seems fun idk 
