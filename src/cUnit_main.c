#include <stdio.h>
#include <stdlib.h>
#include "basis.h"
#include "logic.h"
#include "interface.h"
#include  "CUnit/Basic.h"

unit hobbit;

/* suites initialization and clean fuctions and fuctions */
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
	aloc_map();
	init_map();
	return 0;
}

int clean_logic(void)
{
	free_map();
	return 0;
}

int init_interf(void)
{
	return 0;
}

int clean_interface(void)
{
	endwin();
	return 0;
}

/* basis tests fucntions */
void aloc_map_test(void)
{
	int i;

	aloc_map();
	CU_ASSERT(map != NULL);

	for (i = 0; i < size_row; i++)
		CU_ASSERT(map[i] != NULL);
}

void init_map_test(void)
{
	int i, j;

	init_map();
	for (i = 0; i < size_row; i++)
		for (j = 0; j < SIZE_COLUMN; j++)
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

void aloc_options_test(void)
{
	aloc_options();
	CU_ASSERT(options != NULL);
	CU_ASSERT(options[0] != NULL);
	CU_ASSERT(options[1] != NULL);
	CU_ASSERT(options[2] != NULL);
}

/* logic tests functions */
void init_options_test(void)
{
	init_options();
	CU_ASSERT(options != NULL);
	CU_ASSERT(options[0][1][1] != ' ');
	CU_ASSERT(options[1][0][4] != ' ');
	CU_ASSERT(options[2][3][3] != ' ');
}

void race_init_test(void)
{
	hobbit = race_init(HOBBIT);
	CU_ASSERT(hobbit.race == HOBBIT);
	CU_ASSERT(hobbit.hp == 100);
	CU_ASSERT(hobbit.spd == 1);
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
	move_unit(&hobbit);

	CU_ASSERT(hobbit.position[0] == size_row - hobbit.height);
	CU_ASSERT(hobbit.position[1] == aux + 9);
}

/* interface tests functions */
void click_test(void)
{
	CU_ASSERT((click_option(1)) == 0);
	CU_ASSERT((click_option(2)) == 1);
}

int main()
{
	CU_pSuite pSuite_basis = NULL;
	CU_pSuite pSuite_logic = NULL;
	CU_pSuite pSuite_interface = NULL;


	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add Basis suite to the registry */
	pSuite_basis = CU_add_suite("Suite: Basis", init_basis, clean_basis);

	/* add tests to the Basis suite */
	if ((NULL==CU_add_test(pSuite_basis, "aloc_map", aloc_map_test))||
	   (NULL==CU_add_test(pSuite_basis, "init_map", init_map_test))||
	   (NULL==CU_add_test(pSuite_basis, "free_map", free_map_test))||
	   (NULL==CU_add_test(pSuite_basis, "read_fil", read_file_test))||
	   (NULL==CU_add_test(pSuite_basis, "aloc_options",aloc_options_test)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add Logic suite to the registry */
	pSuite_logic = CU_add_suite("Suite: Logic", init_logic, clean_logic);

	/* add tests to the Logic suite */
	if ((NULL==CU_add_test(pSuite_logic, "init_options", init_options_test))
	   ||(NULL==CU_add_test(pSuite_logic, "race_init", race_init_test))
	   ||(NULL==CU_add_test(pSuite_logic, "load_build", load_build_test))
	   ||(NULL==CU_add_test(pSuite_logic, "get_art", get_art_test))
	   ||(NULL==CU_add_test(pSuite_logic, "printmap_unit", print_unit_test))
	   ||(NULL==CU_add_test(pSuite_logic, "clear_unit", clear_unit_test))
	   ||(NULL==CU_add_test(pSuite_logic, "move_unit", move_unit_test)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add Interface suite to the registry */
	pSuite_interface =
	CU_add_suite("Suite: Interface", init_interf, clean_interface);

	/* add tests to the suite */
	if (NULL==CU_add_test(pSuite_interface, "click_option", click_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* run all tests using CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
