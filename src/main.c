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
		if ((hobbit.position[0] == GOOD_ROW) &&
		   (hobbit.position[1] == HOBBIT_GOLD))
		{
			hobbit.destination[0] = 30;
			hobbit.destination[1] = 40;
		}
		else if ((hobbit.position[0] == 30) &&
			(hobbit.position[1] == 40))
		{
			hobbit.destination[0] = GOOD_ROW;
			hobbit.destination[1] = HOBBIT_GOLD;
		}
		if ((hobbit.position[0] != hobbit.destination[0]) ||
		   (hobbit.position[1] != hobbit.destination[1]))
		{
			printmap_unit(hobbit);
			wprintw_map();
			good_generator();
			print_good();
			clear_unit(hobbit);
			move_unit(&hobbit);
		}
		usleep(REFRESH_TIME);
	}

	free_map();
	endwin();
	return 0;
}

