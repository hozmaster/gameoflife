#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <time.h>

#define GRID_WIDTH  6
#define GRID_HEIGTH 6

//  O O O O O 0
//  O O O O O 0
//  O O O O O 0
//  O O O O O 0
//  O O O O O 0
//  O O O O O 0


char start_set [] = {
    0,0,0,
    1,1,1,
    0,0,0
};

static int groundc = 0;
static int start_living_grid_members = 0;
static int end_living_grid_members = 0;

typedef struct GridBoard
{
    bool alive;
} GridBoard;

GridBoard gridBoard[GRID_WIDTH][GRID_HEIGTH];
GridBoard gridBoardTemp[GRID_WIDTH][GRID_HEIGTH];

#define amount_living_ells = u8;


void printLayout ()
{
	int	i, j;
	/* for each row */
	printf ("round %d \n\n", groundc);
	for (j=0; j<GRID_HEIGTH; j++) {
		/* print each column position... */
		for (i=0; i<GRID_WIDTH; i++) {
            printf (" %2c ", gridBoard[i][j].alive ? 'X' : 'O');
		}
		/* followed by a carriage return */
		printf ("\n");
	}
	printf ("\n");
}

int living_cells ()
{
    int cells_living = 0;
    int y=0;
    int x=0;

    for (y=0; y < GRID_WIDTH; y++)  {
        for (x=0; x < GRID_HEIGTH; x++)  {
            if (gridBoard[y][x].alive == true) {
                cells_living++;
            }
        }
    }
    return cells_living;
}

void save_status ()
{
	FILE *op = fopen ("gameoflife.status", "a+");
	fprintf (op, "\n starting : %d, end : %d ", start_living_grid_members, end_living_grid_members);
	fclose (op);
}

void random_init_game ()
{
    int upper = GRID_WIDTH;
    int lower = 0;
    int x, y = 0;
    for (int i = 0; i < amount_cells; i++) {
        x = rand() % (upper - lower + 1) + lower;
        y = rand() % (upper - lower + 1) + lower;
        gridBoard[y][x].alive = true;
    }
}

void proceedGame()
{
    int neighborous_count = 0;
    for ( int y = 0; y < GRID_WIDTH; y++ ) {
        for ( int x = 0; x < GRID_HEIGTH; x++) {
            get_neighborous_count (x,y);
        }
    }
}

void init_game ()
{
	int y=0;
	int x=0;

    printf("Init game, add some pre filled living cells. q-char will end init phase.");

    int newly=0, newlx =0;
    for (y=0; y < GRID_WIDTH; y++)  {
        for (x=0; x < GRID_HEIGTH; x++)  {
            gridBoard[y][x].alive = false;
        }
    }

    while (1) {
        printf("Enter new living cell y (0-19) coord: ");
        scanf(" %d", &newly);
        printf("Enter new living cell x (0-19) coord: ");
        scanf(" %d", &newlx);
        if ( (newly >= 0 && newly <= 19) && (newlx >= 0 && newlx <= 19) ) {
            gridBoard[newlx][newly].alive = true;
        } else {
            printf(" Skip ...");
        }

        if ( newly == -1 && newlx == -1)  {
            break;
        }
        printLayout ();
    }
}

int main()
{
    char cmd='c';
    int loop = 1;
    srand(time(0));

    random_init_game ();
    printf ("living_cells : %d ", living_cells ());
    printLayout ();

    /*
    while (loop)  {
		if (groundc != 0 && groundc % 50 == 0)  {
			printf ("round : %d, q = quit, c = continue \n", groundc);
			scanf(" %c", &cmd);
		} else {
			char cmd='c';
		}
		switch (cmd) {
			case 'q':
				loop = 0;
				break;
			case 'c':
				groundc ++;
				// next round
				printLayout ();
				break;
		}
	}
	save_status ();
	printf ("\n");
	*/
    return 0;
}
