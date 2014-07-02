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
	return 0;
}

int init_logic(void)
{
	aloc_options();
	aloc_map();
	init_map();
	return 0;
}

int clean_logic(void)
{
	free_options();
	free_map();
	return 0;
}

int init_interf(void)
{
	aloc_options();
	init_options();
	return 0;
}

int clean_interface(void)
{
	return 0;
}

/* basis tests fucntions */
void aloc_map_test(void)
{
	int i;

	aloc_map();
	CU_ASSERT(map != NULL);

	for (i = 0; i < MAP_ROW; i++)
		CU_ASSERT(map[i] != NULL);
}

void init_map_test(void)
{
	int i, j;

	init_map();
	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			CU_ASSERT(map[i][j] == ' ');
}

void free_map_test(void)
{
	free_map();
	CU_ASSERT(map == NULL);
}

void read_file_test(void)
{
	CU_ASSERT((read_file("ASCII art/hobbit.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/elf.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/dwarf.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/ent.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/goblin.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/orc.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/warg.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/troll.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/house_frodo.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/mordor_tower.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/new_game.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/load_game.txt")) != NULL);
	CU_ASSERT((read_file("ASCII art/exit.txt")) != NULL);
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

void insert_b_test(void)
{
	int aux = insert_build(0);

	CU_ASSERT(aux == 1);
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

void load_build_test(void)
{
	int aux = load_build("ASCII art/house_frodo.txt", FRODO_ROW, FRODO_COL);

	CU_ASSERT(aux == 1);
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

void clear_unit_test(void)
{
	int aux_x = hobbit.position[1], aux_y = hobbit.position[0] + 9;

	clear_unit(hobbit);
	CU_ASSERT(map[aux_y][aux_x] == ' ');
}

void move_unit_test(void)
{
	int aux;

	aux = hobbit.position[1];
	hobbit.destination[1] = hobbit.position[1] + 10;
	move_unit(&hobbit);

	CU_ASSERT(hobbit.position[0] == MAP_ROW - hobbit.height);
	CU_ASSERT(hobbit.position[1] == aux + 9);
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
void click_test(void)
{
	CU_ASSERT((click_option(1)) == 0);
	CU_ASSERT((click_option(2)) == 1);
}
