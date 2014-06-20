#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "basis.h"
#include "interface.h"

int main()
{
	int lim_map, i = 0;
	unit vet[8];

	initscr();
	noecho();
	get_dimension();
	aloc_map();
	init_map();
	get_art();
	vet[0] = race_init(HOBBIT);
	vet[1] = race_init(ELF);
	vet[2] = race_init(DWARF);
	vet[3] = race_init(ENT);
	vet[4] = race_init(GOBLIN);
	vet[5] = race_init(ORC);
	vet[6] = race_init(WARG);
	vet[7] = race_init(TROLL);

	load_build("ASCII art/house_frodo.txt", FRODO_ROW, FRODO_COL);
	load_build("ASCII art/mordor_tower.txt", MORDOR_ROW, MORDOR_COL);
	lim_map = sqrt(pow(size_col-SIZE_COLUMN+1, 2));

	while(1)
	{
		erase();
		printmap_unit(vet[i]);
		printmap_unit(vet[i+4]);
		printw_map();
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
		clear_unit(vet[i]);
		clear_unit(vet[i+4]);
		i++;
		if (i == 4)
			i = 0;
	}

	free_map();
	endwin();
	return 0;
}

