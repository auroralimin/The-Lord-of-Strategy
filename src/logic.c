#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <math.h>
#include "basis.h"
#include "logic.h"
#include "interface.h"

struct build_art
{
	char name[50];
	int row, col;
};

char *options_files[] = { "ASCII art/new_game.txt",
			"ASCII art/load_game.txt",
			"ASCII art/exit.txt"};


struct build_art builds[]={
{"ASCII art/house_frodo.txt", MAP_ROW - FRODO_ROW, FRODO_COL},
{"ASCII art/mordor_tower.txt",  MAP_ROW - MORDOR_ROW, MORDOR_COL},
{"ASCII art/gold_build.txt", 1,  GOLD_COL1},
{"ASCII art/food_build.txt", 1, FOOD_COL1},
{"ASCII art/wood_build.txt", 1, WOOD_COL1},
{"ASCII art/metal_build.txt", 1, METAL_COL1}
};

/* matriz contendo o endereço da ascii art do jogo */
static char *name_filearts[] = { "ASCII art/hobbit.txt",
			         "ASCII art/elf.txt",
				 "ASCII art/dwarf.txt",
				 "ASCII art/ent.txt",
				 "ASCII art/goblin.txt",
				 "ASCII art/orc.txt",
				 "ASCII art/warg.txt",
				 "ASCII art/troll.txt"
};

static unit attr[] = {
{HOBBIT, 100, 1, 10, 10, {30, 40}, {30, 40}, 100},
{ELF, 130, 4, 40, 12, {28, 40}, {26, 40}, 200},
{DWARF, 250, 2, 30, 10, {30, 40}, {38, 40}, 250},
{ENT, 500, 1, 50, 15, {25, 40}, {23, 40}, 300},
{GOBLIN, 100, 1, 10, 10, {30, 34+MORDOR_COL}, {30, 34+MORDOR_COL}, 100},
{ORC, 200, 2, 30, 12, {28, 34+MORDOR_COL}, {28, 34+MORDOR_COL}, 200},
{WARG, 120, 5, 25, 8, {31, 34+MORDOR_COL}, {31, 34+MORDOR_COL}, 250},
{TROLL, 500, 1, 50, 15, {25, 34+MORDOR_COL}, {25, 34+MORDOR_COL}, 300}
};

char mat_races[N_RACES + 1][RACE_HEIGHT][RACE_WIDTH];

void* read_key(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&l_key);
		switch(getch())
		{
			case (KEY_MOUSE):
				if(getmouse(&event) == OK)
				{
					key_status = STATUS_MOUSE_MOVED;
					if (event.bstate == BUTTON1_CLICKED)
					{
						key_status = STATUS_MOUSE_CLICK;
						if ((event.y >= scroll_row-1) &&
						   (event.y <= scroll_row+1))
							mouse_scroll(event.x);
					}
				}
				break;
			case (KEY_UP):
				key_status = STATUS_UP;
				break;
			case (KEY_DOWN):
				key_status = STATUS_DOWN;
				break;
			case (KEY_RIGHT):
				if (game_status != STATUS_MENU)
					arrow_scroll(SCROLL_RIGHT);
				break;
			case (KEY_LEFT):
				if (game_status != STATUS_MENU)
					arrow_scroll(SCROLL_LEFT);
				break;
			case (EXIT):
				free_build();
				free_map();
				endwin();
				exit(1);
			case (ENTER):
				key_status = STATUS_ENTER;
		}
		pthread_mutex_unlock(&l_key);
		usleep(2);
	}

	return arg;
}

void init_options()
{
	int i, j;
	FILE *fp = NULL;

	for (i = 0; i < N_OPTIONS; i++)
	{
		fp = read_file(options_files[i]);
		for (j = 0; j < OPTIONS_WIDTH; j++)
		{
			fscanf(fp, "%[^\n]s", options[i][j]);
			if (feof(fp))
				break;
			fgetc(fp);
		}
		fclose(fp);
	}
}

int report_option(int mouse_row, int mouse_col)
{
	if ((mouse_row > 1) && (mouse_row < MENU_ROW - 2) &&
	   (mouse_col > 1) && (mouse_col < MENU_COL - 2))
		return 1 + (mouse_row/ 13);
	return 0;
}

void mouse_scroll(int mouse_col)
{
	int n;

	n = MAP_COL / scroll_col + 1;
	if ((mouse_col > 0) && (mouse_col <= scroll_col) &&
	   (MAP_COL > size_col))
	{
		scroll_position = mouse_col - 1;
		term_col = n * scroll_position;
		term_coltest();
		wprintw_map();
	}
}

void arrow_scroll(int direction)
{
	if ((term_col <= lim_map) && (MAP_COL > size_col) && (term_col >= 0))
	{
		term_col+=direction;
		term_coltest();
		scroll_position = term_col / (MAP_COL / scroll_col + 1);
		wprintw_map();
	}
}

void term_coltest()
{
	if (term_col < 0)
		term_col = 0;
	if (term_col > lim_map)
		term_col = lim_map;
}

/* inicializa as unidades com os atributos pre-definidos */
unit race_init(int race)
{
	int i;
	unit new_unit;

	for (i = 0; i < N_RACES; i++)
		if (attr[i].race == race)
		{
			new_unit.race = attr[i].race;
			new_unit.hp = attr[i].hp;
			new_unit.spd = attr[i].spd;
			new_unit.dmg = attr[i].dmg;
			new_unit.height = attr[i].height;
			new_unit.position[0] = attr[i].position[0];
			new_unit.position[1] = attr[i].position[1];
			new_unit.destination[0] = attr[i].destination[0];
			new_unit.destination[1] = attr[i].destination[1];
			new_unit.spwan_time = attr[i].spwan_time;
			break;
		}

	return new_unit;
}

/* carrega o mapa com as fortalezas do jogador e do computador */
int load_build(char *file_name, int art_row, int art_col)
{
	int i;
	FILE *fp = NULL;

	fp = read_file(file_name);

	for (i = art_row; i < MAP_ROW; i++)
	{
		fscanf(fp, "%[^\n]s", map[i] + art_col);
		fgetc(fp);
		if (feof(fp))
			break;
	}
	fclose(fp);

	return 1;
}

void put_builds()
{
	int i;

	for (i = 0; i < N_BUILDS; i++)
		load_build(builds[i].name, builds[i].row, builds[i].col);
}

/* le a ascii art das racas */
int get_art()
{
	int i, j;
	FILE *fp = NULL;

	for (i = 0; i < N_RACES; i++)
	{
		fp = read_file(name_filearts[i]);
		for (j = 0; j < 15; j++)
		{
			fscanf(fp, "%[^\n]s", mat_races[i][j]);
			fgetc(fp);
			if (feof(fp))
				break;
		}
		fclose(fp);
	}

	return 1;
}

void map_spaces()
{
	int i, j;

	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			if (map[i][j] == '\0')
				map[i][j] = ' ';
}

/* printa as unidades na tela do terminal */
void printmap_unit(unit chr)
{
	int i, j, row = chr.position[0], col = chr.position[1];

	for (i = RACE_HEIGHT - chr.height; i < RACE_HEIGHT; i++)
	{
		for (j = 0; j < RACE_WIDTH; j++)
		{
			if (mat_races[chr.race-1][i][j] != ' ')
				map[row][col] = mat_races[chr.race-1][i][j];
			col++;
		}
		col = chr.position[1];
		row++;
	}
}

void clear_unit(unit chr)
{
	int i, j, row = chr.position[0], col = chr.position[1];

	for (i = RACE_HEIGHT - chr.height; i < RACE_HEIGHT; i++)
	{
		for (j = 0; j < RACE_WIDTH; j++)
			map[row][col++] = ' ';
		col = chr.position[1];
		row++;
	}

	if (col < FRODO_WIDTH)
		load_build(builds[0].name, builds[0].row, builds[0].col);
	else if (col > MORDOR_COL)
		load_build(builds[1].name, builds[1].row, builds[1].col);
	map_spaces();
}

void move_unit(unit *chr)
{
	int dest = 1, n = 1;

	if (chr->race > 4)
		dest = -1;
	if ((chr->position[1]*dest >= chr->destination[1]*dest) &&
	   (chr->position[0] != chr->destination[0]))
	{
		n = 0;
	}

	if (chr->position[n]*dest > chr->destination[n]*dest)
		dest = dest * -1;
	if (chr->position[n]*dest < chr->destination[n]*dest)
	{
		if (n == 0)
			chr->position[0]+= chr->height * dest;
		else
			chr->position[1]+= 9 * dest;
		if (chr->position[n]*dest > chr->destination[n]*dest)
			chr->position[n] = chr->destination[n];
	}
}

void good_generator()
{
	build *aux;

	for (aux = build_top; aux != NULL; aux = aux->next)
	{
		if (aux->storage != pow(10, aux->level+2) / 2)
			aux->storage+=aux->income;
	}
}

void print_good()
{
	int i = 0, j = 0, n = 2, storage = 0, num = 0;
	build *aux = NULL;

	for (i = MAP_COL - FRODO_COL; i < MAP_COL - MORDOR_COL; i++)
		map[0][i] = ' ';

	i = 0;
	for (aux = build_top; aux != NULL; aux = aux->next)
	{
		storage = aux->storage;
		for (i = 999999; i > 0; i = i/10)
		{
			if (storage > i)
			{
				num = storage/(i+1);
				map[0][builds[n].col+j++] = num + 48;
				storage = storage - ((i + 1) * num);
			}
			else if (j > 0)
				map[0][builds[n].col+j++] = 48;
		}
		map[0][builds[n].col+j] = storage + 48;
		n++;
		j = 0;
	}
}
