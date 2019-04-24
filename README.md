The Game of Life 

Create a Game of Life. Game of Life is zero-player game or
a simulation of a cellular automaton. Our Game of Life will
be played in a 20x20 grid. Each gridmember will be defined
as a struct with following information:
		bool alive;
		int x-coord;
		int y-coord;

First the user sets the initial conditions by changing gridmembers 
alive. After he is satisfied with the initial conditions, the game
starts. It follows the rules in each round. Rules are:

		- Each gridmember with zero or one living neighbour: dies
		- Each gridmember with two or three living neighbours: lives
		- Each gridmember with four or more living neighbours: dies
		- Each dead gridmember with three living neighbours becomes alive

The grid should span between the borders so row 20 is a neighbour of row 1 and
same with columns. Create a menu system to handle the setting of initial conditions.
During the game, display the current round (or generation). Make the game pause every
50 rounds to allow the user to either (c)ontinue or (q)uit. Quit message should display
rounds played, living gridmembers at start and at end. Store this info into a file with
date and time played.

There are about a million implementations of this program in the internet. Find the
ones that will help you to finish.

