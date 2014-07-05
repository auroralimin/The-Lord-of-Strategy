#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "cunit_test.h"
#include "basis.h"
#include "logic.h"
#include "interface.h"

unit hobbit;
unit *free_races;
build *build_top;

/* suites initialization and clean fuctions */
int init_basis(void)
{
	init_interface();
	endwin();
	return 0;
}

int clean_basis(void)
{
	endwin();
	exit_game();
	return 0;
}

int init_logic(void)
{
	prepare_map();
	aloc_options();
	endwin();
	return 0;
}

int clean_logic(void)
{
	endwin();
	exit_game();
	return 0;
}

int init_interf(void)
{
	aloc_options();
	init_options();
	init_interface();
	endwin();
	return 0;
}

int clean_interface(void)
{
	endwin();
	exit_game();
	return 0;
}

/* basis tests fucntions */
void free_map_test(void)
{
	free_map();
	CU_ASSERT(map == NULL);
}

void open_file_test(void)
{
	CU_ASSERT((open_file("ASCII art/hobbit.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/elf.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/dwarf.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/ent.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/goblin.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/orc.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/warg.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/troll.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/house_frodo.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/mordor_tower.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/new_game.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/load_game.txt", "r")) != NULL);
	CU_ASSERT((open_file("ASCII art/exit.txt", "r")) != NULL);
}

void aloc_opt_test(void)
{
	aloc_options();
	CU_ASSERT(options != NULL);
	CU_ASSERT(options[0] != NULL);
	CU_ASSERT(options[1] != NULL);
	CU_ASSERT(options[2] != NULL);
}

void free_opt_test(void)
{
	free_options();
	CU_ASSERT(options[0] == NULL);
	CU_ASSERT(options[1] == NULL);
	CU_ASSERT(options[2] == NULL);
}


void free_build_test(void)
{
	free_build();
	build_top = get_buildtop();
	CU_ASSERT(build_top == NULL);
}

/* logic tests functions */
void map_spaces_test(void)
{
	int i, j;

	map_spaces();

	for(i = 0; i < MAP_ROW; i++)
		for(j = 0; j < MAP_COL; j++)
			CU_ASSERT(map[i][j] == ' ');
}

void init_opt_test(void)
{
	init_options();
	CU_ASSERT(options != NULL);
	CU_ASSERT(options[0][1][1] != ' ');
	CU_ASSERT(options[1][0][4] != ' ');
	CU_ASSERT(options[2][3][3] != ' ');
}

void race_init_test(void)
{
	race_init(&hobbit, HOBBIT);
	CU_ASSERT(hobbit.race == HOBBIT);
	CU_ASSERT(hobbit.hp == 100);
	CU_ASSERT(hobbit.spd_delay == 3);
	CU_ASSERT(hobbit.dmg == 10);
}

void get_art_test(void)
{
	CU_ASSERT((get_art()) == 1);
}

void print_unit_test(void)
{
	printmap_unit(hobbit);
	CU_ASSERT(map[hobbit.position[0]+9][hobbit.position[1]] != ' ');
}

void all_move_test(void)
{
	int aux;

	aux = hobbit.position[1];
	hobbit.destination[1] = hobbit.position[1] + 10;
	set_freeraces(&hobbit);
	all_move();

	CU_ASSERT(hobbit.position[0] == MAP_ROW - hobbit.height);
	CU_ASSERT(hobbit.position[1] == aux + 9);

	free_units(&free_races);
}

void get_freer_test(void)
{
	CU_ASSERT(get_freeraces() == NULL);
}

void set_freer_test(void)
{
	unit elf;

	race_init(&elf, ELF);

	set_freeraces(&elf);

	CU_ASSERT(free_races->race == 2);
}

/* interface tests functions */
void c_mapwin_test(void)
{
	CU_ASSERT(createmap_win() == 1);
	endwin();
}

void c_msgwin_test(void)
{
	CU_ASSERT(createmsg_win() == 1);
	endwin();
}
