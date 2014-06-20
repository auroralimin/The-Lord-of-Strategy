#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "basis.h"
#include "interface.h"

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

/* printa o mapa na janela do terminal */
void printw_map()
{
	for (int i = 0; i < size_row; i++)
		for (int j = 0; (j < SIZE_COLUMN) && (j < size_col); j++)
			mvprintw(i, j, "%c", map[i][j + term_col]);
	refresh();
}
