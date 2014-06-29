#include <stdlib.h>
#include <pthread.h>
#include "basis.h"
#include "logic.h"

pthread_mutex_t l_key;
char **map = NULL;
int options_len[] = { NEW_GAME, LOAD_GAME, EXIT_GAME};

pthread_t key_thread;
char **options[N_OPTIONS];

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
	put_builds();
	map_spaces();
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
		free_build();
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
			options[i][j] = (char*)
			calloc(options_len[i], sizeof(char));
	}
}

char*** get_options()
{
	return options;
}

void free_options()
{
	int i, j;

	for (i = 0; i < N_OPTIONS; i++){
		for (j = 0; j < OPTIONS_WIDTH; j++)
		{
			if (options[i][j] != NULL)
				free(options[i][j]);
		}
		if (options[i] != NULL)
		{
			free(options[i]);
			options[i] = NULL;
		}
	}
}

int insert_unit(unit **top, int race)
{
	unit *new = (unit*) calloc(1, sizeof(unit));

	if (new == NULL)
		return -1;

	race_init(new, race);

	if (*top == NULL)
	{
		*top = new;
		return 1;
	}

	new->next = *top;
	*top = new;

	return 1;
}

void free_units(unit **top)
{
	unit *aux;

	while (aux != NULL)
	{
		aux = aux->next;
		free(*top);
		*top = aux;
	}

	*top = NULL;
}

void create_listbuild()
{
	int i;

	for (i = 3; i >= 0; i--)
		if (!insert_build(i))
		{
			endwin();
			printf("Insufficient memory\n");
			exit(1);
		}
}

int insert_build(int id)
{
	build *build_top = get_buildtop();
	build *new = (build*) calloc(1, sizeof(build));

	if (new == NULL)
		return -1;

	new->id = id;
	new->level = 1;
	new->storage = 0;
	new->income = 50;

	if (build_top == NULL)
	{
		set_buildtop(new);
		return 1;
	}

	new->next = build_top;
	build_top = new;
	set_buildtop(build_top);

	return 1;
}

void free_build()
{
	build *build_top = get_buildtop();
	build *aux = build_top;

	while (aux != NULL) {
		aux = aux->next;
		free(build_top);
		build_top = aux;
	}
	set_buildtop(NULL);
}

