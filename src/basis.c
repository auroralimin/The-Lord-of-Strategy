#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include "basis.h"
#include "logic.h"

pthread_mutex_t l_key, l_sync;
int key_status;
MEVENT event;
char **map;
int lim_map;
int size_row, size_col;
int term_col;
char **options[N_OPTIONS];

int options_len[] = { NEW_GAME, LOAD_GAME, EXIT_GAME};

void init_locks()
{
	pthread_mutex_init(&l_key, NULL);
	pthread_mutex_init(&l_sync, NULL);
}

void init_thread(pthread_t *thread)
{
	if (pthread_create(thread, NULL, &read_key, NULL))
	{
		endwin();
		fprintf(stderr, "Cannot create thread read_key\n");
		exit(-1);
	}
}

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
		if(map[i] != NULL)
			free(map[i]);
	if (map != NULL)
	{
		free(map);
		map = NULL;
	}
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

