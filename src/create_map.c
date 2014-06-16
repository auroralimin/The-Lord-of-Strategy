#include <stdlib.h>
#include <ncurses.h>
#include <math.h>

#define SIZE_COLUMN 300

int size_row, size_col;
char **map;

void aloc_map();
void init_map();
void read_art(char *file_name, int art_row, int art_col);
void printw_map(int col);
void free_map();

int main()
{
	int i, j, row = 0, col = 0;
	char c;

	initscr();
	getmaxyx(stdscr, size_row, size_col);

	aloc_map();
	init_map();
	read_art("../ASCII art/house_frodo.txt", 31, 0);
	read_art("../ASCII art/mordor_tower.txt", 40, SIZE_COLUMN - 86);

	if (size_row < 50)
	{
		endwin();
		printf("The terminal's dimension isn't big enough.\n");
		printf("We suggest you use a smaller font.\n");
		return 0;
	}

	while(1)
	{
		erase();
		printw_map(col);
		switch (getch())
		{
			case 'a':
				if (col > 0)
					col--;
				break;
			case 'd':
				if (col < sqrt((size_col-299)*(size_col-299)))
					col++;
				break;
			case 'k':
				free_map();
				endwin();
				return 0;
		}
	}

	free_map();
	endwin();
	return 0;
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
	}

	for (int i = size_row - art_row; i < size_row; i++)
	{
		fscanf(fp, "%[^\n]s", map[i] + art_col);
		fgetc(fp);
	}
	fclose(fp);

}

void printw_map(int col)
{
	for (int i = 0; i < size_row; i++)
		for (int j = 0; j < size_col; j++)
			mvprintw(i, j, "%c", map[i][j + col]);
	refresh();
}

void free_map()
{
	for (int i = 0; i < size_row; i++)
		free(map[i]);
	free(map);
}
