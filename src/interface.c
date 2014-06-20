#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "basis.h"
#include "interface.h"

void init_interface()
{
	initscr();
	cbreak();
	start_color();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	get_dimension();
}

/* alerta o usuario se a janela do terminal nao tiver altura suficiente
para o jogo */
void get_dimension()
{
	getmaxyx(stdscr, size_row, size_col);

	if (size_row < MINIMUM_ROW)
	{
		endwin();
		printf("The terminal's dimension isn't big enough.\n");
		printf("We suggest you use a smaller font.\n");
		exit (1);
	}
}

WINDOW *create_win(int win_y, int win_x, int starty, int startx)
{
	WINDOW *local_win;

	refresh();
	local_win = newwin(win_y, win_x, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	refresh();

	return local_win;
}

void destroy_win(WINDOW **local_win)
{
	werase(*local_win);
	wrefresh(*local_win);
	delwin(*local_win);
	*local_win = NULL;
}

/* printa o mapa na janela do terminal */
void printw_map()
{
	for (int i = 0; i < size_row; i++)
		for (int j = 0; (j < SIZE_COLUMN) && (j < size_col); j++)
			mvprintw(i, j, "%c", map[i][j + term_col]);
	refresh();
}
