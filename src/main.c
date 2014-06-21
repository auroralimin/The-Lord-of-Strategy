#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "basis.h"
#include "interface.h"
#include "logic.h"

int main()
{
	unit hobbit;
	pthread_t key_thread;

	init_locks();
	init_interface();
	init_thread(&key_thread);

	menu();
	init_interface();
	keypad(stdscr, TRUE);

	aloc_map();
	init_map();
	get_art();
	hobbit = race_init(HOBBIT);

	load_build("ASCII art/house_frodo.txt", FRODO_ROW, FRODO_COL);
	load_build("ASCII art/mordor_tower.txt", MORDOR_ROW, MORDOR_COL);
	lim_map = sqrt(pow(size_col-SIZE_COLUMN+1, 2));

	while(1)
	{
		printmap_unit(hobbit);
		pthread_mutex_lock(&l_sync);
		printw_map();
		clear_unit(hobbit);
		pthread_mutex_unlock(&l_sync);
		move_unit(&hobbit);
		usleep(REFRESH_TIME);
	}

	free_map();
	endwin();
	return 0;
}

