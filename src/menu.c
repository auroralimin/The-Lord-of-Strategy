#include <ncurses.h>
#include "basis.h"
#include "logic.h"
#include "interface.h"

int main(void)
{
	int x, y;
	WINDOW *menu_win = NULL;

	init_interface();

	y = (size_row-MENU_ROW)/2;
	x = (size_col-MENU_COL)/2;
	menu_win = create_win(MENU_ROW, MENU_COL, y, x);
	aloc_options();
	init_options();

	print_menu(menu_win, 1);
	getch();

	endwin();
	return 0;
}


