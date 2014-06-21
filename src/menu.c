#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "basis.h"
#include "logic.h"
#include "interface.h"

int main(void)
{
	int opt = 1, x, y;
	WINDOW *menu_win = NULL;
	MEVENT event;

	init_interface();

	y = (size_row-MENU_ROW)/2;
	x = (size_col-MENU_COL)/2;
	menu_win = create_win(MENU_ROW, MENU_COL, y, x);

	aloc_options();
	init_options();
	print_menu(menu_win, opt);
	system("TERM=xterm-1003");

	while(1)
	{
		keypad(menu_win, TRUE);
		switch (getch())
		{
		case (KEY_MOUSE):
			if(getmouse(&event) == OK)
				opt = report_option(event.y-3, event.x-3, y, x);
			if ((opt == 3) && (event.bstate == BUTTON1_CLICKED))
			{
				endwin();
				exit(1);
			}
			print_menu(menu_win, opt);
			break;

		case (KEY_DOWN):
			if (opt != N_OPTIONS)
				opt++;
			else
				opt = 0;
			print_menu(menu_win, opt);
			break;

		case (KEY_UP):
			if (opt != 0)
				opt--;
			else
				opt = N_OPTIONS;
			print_menu(menu_win, opt);
			break;

		case (KEY_ENTER):
			if (opt == 3)
			{
				endwin();
				exit(1);
			}
		}
		refresh();
	}
}
