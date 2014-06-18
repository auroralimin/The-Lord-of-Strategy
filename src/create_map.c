#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "interface.h"

int main()
{
	int col = 0, lim_map;

	initscr();
	noecho();
	get_dimension();
	aloc_map();
	init_map();

	read_art("ASCII art/house_frodo.txt", 31, 0);
	read_art("ASCII art/mordor_tower.txt", 40, SIZE_COLUMN - 86);
	lim_map = sqrt(pow(size_col-SIZE_COLUMN+1, 2));

	while(1)
	{
		erase();
		printw_map(col);
		switch (getch())
		{
			case 'a':
				if (col > 0)
					col-=2;
				break;
			case 'd':
				if ((col < lim_map) && (SIZE_COLUMN > size_col))
					col+=2;
				break;
			case 'k':
				free_map();
				endwin();
				return 0;
		}
	}

	free_map();
	endwin();
	return 0;
}

