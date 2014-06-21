#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	mousemask(ALL_MOUSE_EVENTS, NULL);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	get_dimension();
}

/* alerta o usuario se a janela do terminal nao tiver altura suficiente
para o jogo */
void get_dimension()
{
	getmaxyx(stdscr, size_row, size_col);

	if ((size_row < MINIMUM_ROW) || (size_col < MINIMUN_COL))
	{
		endwin();
		printf("The terminal's dimension isn't big enough.\n");
		printf("We suggest you use a smaller font.\n");
		exit (1);
	}
}

WINDOW* create_win(int win_y, int win_x, int starty, int startx)
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

void print_menu(WINDOW *menu_win, int highlight)
{
	int i, row = 3, col = 3;

	for(i = 0; i < N_OPTIONS; ++i)
	{
		col = (MENU_COL-strlen(options[i][0]))/2;
		if(highlight == i + 1)
			wattron(menu_win, COLOR_PAIR(1));
		else
			wattron(menu_win, COLOR_PAIR(2));
		for(int j = 0; j < OPTIONS_WIDTH; j++)
			mvwprintw(menu_win, row++, col, "%s", options[i][j]);
		row+=3;
	}
	wattroff(menu_win, COLOR_PAIR(1));
	wattroff(menu_win, COLOR_PAIR(2));
	box(menu_win, 0, 0);
	wrefresh(menu_win);
}

/* printa o mapa na janela do terminal */
void printw_map()
{
	for (int i = 0; i < size_row; i++)
		for (int j = 0; (j < SIZE_COLUMN) && (j < size_col); j++)
			mvprintw(i, j, "%c", map[i][j + term_col]);
	refresh();
}
