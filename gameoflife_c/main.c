#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define GRID_WIDTH  10
#define GRID_HEIGHT 10

#define EMPTY_CELL  0
#define LIVING_CELL 1

// If the cell is alive:
//    1. If it has 1 or no neighbors, it will turn "dead". As if by solitude.
//    2. if it has 4 or more neighbors, it will turn "dead". As if by overpopulation.
//    3. If it has 2 or 3 neighbors, it will remain "alive".
// If the cell is dead:
//    1. If it has exactly three neighbors, it will turn "alive", as if by regrowth

int gameOfLifeBoard[GRID_WIDTH][GRID_HEIGHT] =
    {   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

int testBoard [GRID_WIDTH][GRID_HEIGHT] =
    {   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

#define AMOUNT_LIVING_CELLS 27

void printLayout ()
{
	int	i, j;
    for (j=0; j<GRID_WIDTH; j++) {
		/* print each column position... */
        for (i=0; i<GRID_HEIGHT; i++) {
            printf (" %2c ", gameOfLifeBoard[j][i] ? 'X' : 'O');
		}
		/* followed by a carriage return */
		printf ("\n");
	}
	printf ("\n");
}

int get_neighborous_count(int y_t, int x_t)
{
    int count = 0;
    for (int z = y_t -1; z <= y_t; z++)  {
        for (int c = x_t - 1; c <= x_t;  c++ ) {
            if (z < 0 )
                continue;
            if (c < 0 )
                continue;
             if(!(z == 0 && c == 0)) {
                // this works on if cell value is 0 or 1 ...
                count += gameOfLifeBoard[z][c];
            }
        }
    }
    return count;
}


void print_grid ( int *theBoard )
{
    for (int i = 0; i < GRID_WIDTH; i++) {
      for (int j = 0; j < GRID_HEIGHT; j++) {
        printf (" %2c ", *(theBoard + i * GRID_HEIGHT + j) ? 'X' : '0');
      }
      printf("\n");
    }
}

int play_game ()
{
    int cells_living = 0;
    int y=0;
    int x=0;

    // create the board and set it to zero
    int newBoard[GRID_WIDTH][GRID_HEIGHT];    
    memcpy(newBoard, gameOfLifeBoard, sizeof(gameOfLifeBoard));
    print_grid(newBoard);

    int loop = 1;
    while (loop) {

        loop = 0;   // for testing purposes ...
    }

    //    for (y=0; y < GRID_WIDTH; y++)  {
    //        for (x=0; x < GRID_HEIGHT; x++)  {
    //            int is_alive = gameOfLifeBoard[y][x];
    //            int adjacents = get_neighborous_count(y,x);
    //            switch (adjacents)  {
    //                case 0:
    //                case 1:
    //                    newBoard[y][x] = EMPTY_CELL;
    //                    break;
    //                case 2:
    //                case 3:
    //                    if (is_alive)  {
    //                        newBoard[y][x] = LIVING_CELL;
    //                    } else {
    //                        if (adjacents == 3)
    //                            newBoard[y][x] = LIVING_CELL;
    //                    }
    //                    break;
    //                default:
    //                    newBoard[y][x] = EMPTY_CELL;
    //                    break;
    //            }
    //        }
    //}
    //    memcpy (gameOfLifeBoard, newBoard, sizeof(gameOfLifeBoard));
    //    printLayout();
    return cells_living;
}

//void save_status ()
//{
//	FILE *op = fopen ("gameoflife.status", "a+");
//    fprintf (op, "\n starting : %d, end : %d", start_living_grid_members, end_living_grid_members);
//	fclose (op);
//}

void random_init_game ()
{
    int upper = GRID_WIDTH;
    int lower = 0;
    int loop, x, y = 0;

    for (loop = 0; loop < AMOUNT_LIVING_CELLS; loop++) {
        x = rand() % (upper - lower + 1) + lower;
        y = rand() % (upper - lower + 1) + lower;
        gameOfLifeBoard[y][x] = LIVING_CELL;
    }
}

void proceedGame()
{
    int neighborous_count = 0;
    int y, x, temp, tempBoard[GRID_WIDTH][GRID_HEIGHT];

    for ( int x = 0; x < GRID_WIDTH; x++ ) {
        for ( int y = 0; x < GRID_HEIGHT; y++) {
            neighborous_count = get_neighborous_count (x,y);            
        }
    }
}

int main()
{
    srand(time(0));
    play_game();
    return 0;
}
