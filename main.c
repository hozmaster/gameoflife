#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define GRID_WIDTH  20
#define GRID_HEIGTH 20

char start_set [] = {
    0,0,0,
    1,1,1,
    0,0,0
};

static int groundc = 0;
static int start_living_grid_members = 0;
static int end_living_grid_members = 0;

typedef struct gridMember
{
    bool alive;
    int xcoord;
    int ycoord;
} gridMember;

gridMember grid[GRID_WIDTH][GRID_HEIGTH];

void printLayout ()
{
	int	i, j;
	/* for each row */
	printf ("round %d \n\n", groundc);
	for (j=0; j<GRID_HEIGTH; j++) {
		/* print each column position... */
		for (i=0; i<GRID_WIDTH; i++) {
			printf (" %2c ", grid[i][j].alive ? 'x' : 'o');
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
            if (grid[y][x].alive == true) {
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

void init_game ()
{
	int y=0;
	int x=0;

    int newly=0, newlx =0;
    for (y=0; y < GRID_WIDTH; y++)  {
        for (x=0; x < GRID_HEIGTH; x++)  {
            grid[y][x].xcoord = x;
            grid[y][x].ycoord = y;
            grid[y][x].alive = false;
        }
    }

    while (1) {
        printf("Enter new living cell y (0-19) coord: ");
        scanf(" %d", &newly);
        printf("Enter new living cell x (0-19) coord: ");
        scanf(" %d", &newlx);
        if ( (newly >= 0 && newly <= 19) && (newlx >= 0 && newlx <= 19) ) {
            grid[newlx][newly].alive = true;
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
    init_game ();

    printf ("living_cells : %d ", living_cells ());

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
    return 0;
}
