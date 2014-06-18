#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "interface.h"

int size_row, size_col;
char **map;

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

void aloc_map()
{
	map = (char**) calloc(size_row, sizeof(char*));
	for (int i = 0; i < size_row; i++)
		map[i] = (char*) calloc(SIZE_COLUMN, sizeof(char));
}

void init_map(){
	for (int i = 0; i < size_row; i++)
		for (int j = 0; j < SIZE_COLUMN; j++)
                   map[i][j] = '\0';
}

void read_art(char *file_name, int art_row, int art_col)
{
	FILE *fp = NULL;

	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		free_map();
		endwin();
		printf("Arquivo %s inexistente\n", file_name);
		exit(1);
	}

	for (int i = size_row - art_row; i < size_row; i++)
	{
		fscanf(fp, "%[^\n]s", map[i] + art_col);
		fgetc(fp);
		if (feof(fp))
			break;
	}
	fclose(fp);

}

void printw_map(int col)
{
	for (int i = 0; i < size_row; i++)
		for (int j = 0; (j < SIZE_COLUMN) && (j < size_col); j++)
			mvprintw(i, j, "%c", map[i][j + col]);
	refresh();
}

void free_map()
{
	for (int i = 0; i < size_row; i++)
		free(map[i]);
	free(map);
}
