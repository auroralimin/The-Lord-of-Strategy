#include <stdio.h>
#include <stdlib.h>
#include "basis.h"
#include "logic.h"
#include "interface.h"
#include  "CUnit/Basic.h"

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
/*
int init_logic(void)
{
	return 0;
}

int clean_logic(void)
{
	return 0;
}

int init_interface(void)
{
	return 0;
}

int clean_interface(void)
{
	return 0;
} */

/* basis tests fucntions */
void aloc_map_test(void)
{
	aloc_map();
	CU_ASSERT(map != NULL);
}

void init_map_test(void)
{
	init_map();
	CU_ASSERT(map[0][0] == ' ');
}

void free_map_test(void)
{
	free_map();
	CU_ASSERT(map == NULL);
}

void read_file_test(void)
{
	CU_ASSERT((read_file("ASCII art/hobbit.txt")) != NULL);
}

void aloc_options_test(void)
{
	aloc_options();
	CU_ASSERT(options != NULL);
}

/* logic tests functions */

/* interface tests functions */

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
	/*pSuite_logic = CU_add_suite("Suite: Logic", init_logic, clean_logic);*/

	/* add tests to the suite */



	/* add Interface suite to the registry */
	/*pSuite_interface = CU_add_suite("Suite: Interface", init_interface,
	clean_interface);*/

	/* add tests to the suite */



	/* run all tests using CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
