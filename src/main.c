#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include "basis.h"
#include "interface.h"
#include "logic.h"

int main()
{
	int lim_map;
	unit hobbit;

	init_interface();
	menu();
	init_interface();

	aloc_map();
	init_map();
	get_art();
	hobbit = race_init(HOBBIT);

	load_build("ASCII art/house_frodo.txt", FRODO_ROW, FRODO_COL);
	load_build("ASCII art/mordor_tower.txt", MORDOR_ROW, MORDOR_COL);
	lim_map = sqrt(pow(size_col-SIZE_COLUMN+1, 2));

	while(1)
	{
		erase();
		printmap_unit(hobbit);
		printw_map();
		clear_unit(hobbit);
		move_unit(&hobbit);
		timeout(500);
		switch (getch())
		{
			case 'a':
				if (term_col > 0)
					term_col-=9;
				break;
			case 'd':
				if ((term_col < lim_map) &&
				   (SIZE_COLUMN > size_col))
					term_col+=9;
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

