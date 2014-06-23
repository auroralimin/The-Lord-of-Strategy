#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include "basis.h"
#include "interface.h"
#include "logic.h"

int main()
{
	unit hobbit;

	init_locks();
	init_interface();
	init_thread();

	menu();
	init_interface();
	keypad(stdscr, TRUE);

	create_listbuild();
	prepare_map();
	createmap_win();
	hobbit = race_init(HOBBIT);

	while(1)
	{
		good_generator();
		printmap_unit(hobbit);
		print_good();
		wprintw_map();
		clear_unit(hobbit);
		move_unit(&hobbit);
		usleep(REFRESH_TIME);
	}

	free_map();
	endwin();
	return 0;
}

