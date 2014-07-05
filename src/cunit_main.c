#include "CUnit/Basic.h"
#include "cunit_test.h"

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
	if ((NULL==CU_add_test(pSuite_basis, "free_map", free_map_test))||
	   (NULL==CU_add_test(pSuite_basis, "open_file", open_file_test))||
	   (NULL==CU_add_test(pSuite_basis, "aloc_options", aloc_opt_test))||
	   (NULL==CU_add_test(pSuite_basis, "free_options", free_opt_test))||
	   (NULL==CU_add_test(pSuite_basis, "free_build", free_build_test)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add Logic suite to the registry */
	pSuite_logic = CU_add_suite("Suite: Logic", init_logic, clean_logic);

	/* add tests to the Logic suite */
	if ((NULL==CU_add_test(pSuite_logic, "map_spaces", map_spaces_test))
	   ||(NULL==CU_add_test(pSuite_logic, "init_options", init_opt_test))
	   ||(NULL==CU_add_test(pSuite_logic, "race_init", race_init_test))
	   ||(NULL==CU_add_test(pSuite_logic, "get_art", get_art_test))
	   ||(NULL==CU_add_test(pSuite_logic, "printmap_unit", print_unit_test))
	   ||(NULL==CU_add_test(pSuite_logic, "all_move", all_move_test)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/* add Interface suite to the registry*/
	pSuite_interface =
	CU_add_suite("Suite: Interface", init_interf, clean_interface);

	/* add tests to the suite*/
	if ((NULL==CU_add_test(pSuite_interface, "createmap_win", c_mapwin_test))
	   ||(NULL==CU_add_test(pSuite_interface, "createmsg_win", c_msgwin_test)))
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
