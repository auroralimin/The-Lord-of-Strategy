#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include "basis.h"
#include "interface.h"
#include "logic.h"

int main()
{
	unit *chr;

	init_locks();
	init_interface();
	init_thread();

	menu();
	init_interface();
	keypad(stdscr, TRUE);

	create_listbuild();
	prepare_map();
	createmap_win();
	chr = get_freeraces();
	insert_unit(&chr, 1);
	goto_build(chr, 0);
	set_freeraces(chr);
	load_houseoption(0);
	load_houseoption(1);
	while(1)
	{
		for (chr = get_freeraces(); chr != NULL; chr = chr->next)
		{
			printmap_unit(*chr);
		}
		wprintw_map();
		good_generator();
		print_good();
		all_move();
		for (chr = get_freeraces(); chr != NULL; chr = chr->next)
		{
			check_good(chr);
		}
		usleep(REFRESH_TIME);
	}

	free_map();
	free_build();
	endwin();
	return 0;
}

