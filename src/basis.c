#include <stdlib.h>
#include <pthread.h>
#include "basis.h"
#include "logic.h"

pthread_mutex_t l_key;
pthread_t key_thread;
int key_status = 0;
int game_status = 0;
MEVENT event;
int scroll_row = 0, scroll_col = 0, scroll_position = 0;
char **map = NULL;
int lim_map = 0;
int size_row = 0, size_col = 0;
int term_col = 1;
char **options[N_OPTIONS];

int options_len[] = { NEW_GAME, LOAD_GAME, EXIT_GAME};

void init_locks()
{
	pthread_mutex_init(&l_key, NULL);
}

void init_thread()
{
	if (pthread_create(&key_thread, NULL, &read_key, NULL))
	{
		endwin();
		fprintf(stderr, "Cannot create thread read_key\n");
		exit(-1);
	}
}

void prepare_map()
{
	aloc_map();
	init_map();
	get_art();
	load_build("ASCII art/house_frodo.txt", FRODO_ROW, FRODO_COL);
	load_build("ASCII art/mordor_tower.txt", MORDOR_ROW, MORDOR_COL);
}

/* aloca uma matriz na memoria para guardar o mapa do jogo */
void aloc_map()
{
	int i;

	map = (char**) calloc(MAP_ROW, sizeof(char*));
	for (i = 0; i < MAP_ROW; i++)
		map[i] = (char*) calloc(MAP_COL, sizeof(char));
}

/* inicializa o mapa com espaços */
void init_map()
{
	int i, j;

	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
                   map[i][j] = ' ';
}

/* libera o mapa */
void free_map()
{
	int i;

	if (map != NULL)
	{
		for (i = 0; i < MAP_ROW; i++)
			if (map[i] != NULL)
				free(map[i]);
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
	int i, j;

	for (i = 0; i < N_OPTIONS; i++)
	{
		options[i] = (char**) calloc(OPTIONS_WIDTH, sizeof(char*));
		for (j = 0; j < OPTIONS_WIDTH; j++)
			options[i][j] = calloc(options_len[i],sizeof(char));
	}
}

