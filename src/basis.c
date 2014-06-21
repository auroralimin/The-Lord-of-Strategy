#include <stdlib.h>
#include <ncurses.h>
#include "basis.h"

char **map;
int size_row, size_col;
int term_col;
char **options[N_OPTIONS];

int options_len[] = { NEW_GAME, LOAD_GAME, EXIT_GAME};

/* aloca uma matriz na memoria para guardar o mapa do jogo */
void aloc_map()
{
	map = (char**) calloc(size_row, sizeof(char*));
	for (int i = 0; i < size_row; i++)
		map[i] = (char*) calloc(SIZE_COLUMN, sizeof(char));
}

/* inicializa o mapa com espaços */
void init_map(){
	for (int i = 0; i < size_row; i++)
		for (int j = 0; j < SIZE_COLUMN; j++)
                   map[i][j] = ' ';
}

/* libera o mapa */
void free_map()
{
	for (int i = 0; i < size_row; i++)
		free(map[i]);
	free(map);
}

/* le os arquivos .txt contendo a ascii art do jogo */
FILE* read_file(char *name)
{
	FILE *fp = NULL;

	fp = fopen(name, "r");
	if (fp == NULL)
	{
		endwin();
		printf("%s not found\n", name);
		free_map();
		exit(1);
	}

	return fp;
}

void aloc_options()
{
	for (int i = 0; i < N_OPTIONS; i++)
	{
		options[i] = (char**) calloc(OPTIONS_WIDTH, sizeof(char*));
		for (int j = 0; j < OPTIONS_WIDTH; j++)
			options[i][j] = calloc(options_len[i],sizeof(char));
	}
}

