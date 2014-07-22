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
	chr = get_freeraces();
	insert_unit(&chr, ORC, NULL);
	goto_build(chr, 4);
	insert_unit(&chr, GOBLIN, NULL);
	goto_build(chr, 5);
	insert_unit(&chr, GOBLIN, NULL);
	goto_build(chr, 6);
	insert_unit(&chr, GOBLIN, NULL);
	goto_build(chr, 7);
	set_freeraces(chr);

	while(1)
	{
		pthread_mutex_lock(&l_pause);

		printall_units();
		refresh_allgame();
		good_generator();
		print_good();
		all_move();
		check_good(chr);
		attack_fortress();

		pthread_mutex_unlock(&l_pause);
		usleep(REFRESH_TIME);
	}

	free_map();
	free_build();
	endwin();
	return 0;
}

