#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define GRID_WIDTH  6
#define GRID_HEIGHT 6

#define EMPTY_CELL  0
#define LIVING_CELL 1

//  O O O O O 0
//  O O O O O 0
//  O O O O O 0
//  O O O O O 0
//  O O O O O 0
//  O O O O O 0

// If the cell is alive:
//    1. If it has 1 or no neighbors, it will turn "dead". As if by solitude.
//    2. if it has 4 or more neighbors, it will turn "dead". As if by overpopulation.
//    3. If it has 2 or 3 neighbors, it will remain "alive".
// If the cell is dead:
//    1. If it has exactly three neighbors, it will turn "alive", as if by regrowth

char start_set [] = {
    0,0,0,
    1,1,1,
    0,0,0
};

static int groundc = 0;
static int start_living_grid_members = 0;
static int end_living_grid_members = 0;

int gameOfLifeBoard[GRID_WIDTH][GRID_HEIGHT];

#define AMOUNT_LIVING_CELLS 15

void printLayout ()
{
	int	i, j;
	/* for each row */
	printf ("round %d \n\n", groundc);
    for (j=0; j<GRID_WIDTH; j++) {
		/* print each column position... */
        for (i=0; i<GRID_HEIGHT; i++) {
            printf (" %2c ", gameOfLifeBoard[i][j] ? 'X' : 'O');
		}
		/* followed by a carriage return */
		printf ("\n");
	}
	printf ("\n");
}

int get_neighborous_count(int y_t, int x_t)
{
    int count = 0;
    for (int z = y_t -1; z <= y_t+1; z++)  {
        for (int c = x_t - 1; c <= x_t + 1; c++ ) {
            if (z < 0 || z > GRID_WIDTH)
                continue;
            if (c < 0 || c > GRID_HEIGHT)
                continue;
            if (z != y_t && c != x_t)
                // this works on if cell value is 0 or 1 ...
                count += gameOfLifeBoard[z][c];
        }
    }
    return count;
}

int living_cells ()
{
    int cells_living = 0;
    int y=0;
    int x=0;

    int newBoard[GRID_WIDTH][GRID_HEIGHT];

    memcpy (newBoard, &gameOfLifeBoard, sizeof(gameOfLifeBoard));

    for (y=0; y < GRID_WIDTH; y++)  {
        for (x=0; x < GRID_HEIGHT; x++)  {
            int is_alive = gameOfLifeBoard[y][x];
            int adjacents = get_neighborous_count(y,x);
            switch (adjacents)  {
                case 0:
                case 1:
                    newBoard[y][x] = EMPTY_CELL;
                    break;
                case 2:
                case 3:
                    if (is_alive)  {
                        newBoard[y][x] = LIVING_CELL;
                    } else {
                        if (adjacents == 3)
                            newBoard[y][x] = LIVING_CELL;
                    }
                    break;
                default:
                    newBoard[y][x] = EMPTY_CELL;
                    break;
            }
        }
    }
    memcpy (gameOfLifeBoard, &newBoard, sizeof(gameOfLifeBoard));
    printLayout();
    return cells_living;
}

void save_status ()
{
	FILE *op = fopen ("gameoflife.status", "a+");
    fprintf (op, "\n starting : %d, end : %d", start_living_grid_members, end_living_grid_members);
	fclose (op);
}

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

void init_game ()
{
	int y=0;
	int x=0;

    printf("Init game, add some pre filled living cells. q-char will end init phase.");

}

int main()
{
    srand(time(0));
    memset(*gameOfLifeBoard, sizeof(gameOfLifeBoard), 0);

    random_init_game();
    printLayout ();
    for (int f =0; f< 40; f++) {
        living_cells();
        groundc++;
    }

    int count = get_neighborous_count(0,0);
    get_neighborous_count(3,3);


    //    random_init_game ();
    //    printf ("living_cells : %d ", living_cells ());
    //    printLayout ();
    return 0;
}
