#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "basis.h"
#include "logic.h"
#include "interface.h"

int main(void)
{
	int opt, x, y;
	WINDOW *menu_win = NULL;
	MEVENT event;

	init_interface();

	y = (size_row-MENU_ROW)/2;
	x = (size_col-MENU_COL)/2;
	menu_win = create_win(MENU_ROW, MENU_COL, y, x);
	aloc_options();
	init_options();
	print_menu(menu_win, -1);

	while(1)
	{
		keypad(menu_win, TRUE);
		if ((getch() == KEY_MOUSE) && (getmouse(&event) == OK) &&
		   (event.bstate == BUTTON1_CLICKED))
		{
			opt = report_option(event.y-3, event.x-3, y, x);
			if (opt == 3)
			{
				endwin();
				exit(1);
			}
			print_menu(menu_win, opt);
		}
	}
	endwin();
	return 0;
}


