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

static char *options_files[] = { "ASCII art/new_game.txt",
                 		"ASCII art/load_game.txt",
				"ASCII art/exit.txt"};


static struct build_art builds[]={
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

static char *name_fileshadows[] = { "ASCII art/hobbit_shadow.txt",
			            "ASCII art/elf_shadow.txt",
				    "ASCII art/dwarf_shadow.txt",
				    "ASCII art/ent_shadow.txt",
				    "ASCII art/goblin_shadow.txt",
				    "ASCII art/orc_shadow.txt",
				    "ASCII art/warg_shadow.txt",
			            "ASCII art/troll_shadow.txt"
};

static char *options_frodo[] = { "ASCII art/house_option0.txt",
				 "ASCII art/house_option1.txt",
				 "ASCII art/house_option2.txt",
				 "ASCII art/house_option3.txt",
				 "ASCII art/house_option4.txt"
};

static const unit attr[] = {
{HOBBIT, 100, 3, 2, 10, 10, {30, 40}, {30, 40}, -1, 0, NULL},
{ELF,    130, 2, 1, 40, 12, {28, 40}, {28, MORDOR_COL-19}, 0, 0, NULL},
{DWARF,  250, 3, 2, 30, 11, {29, 40}, {29, MORDOR_COL-19}, 0, 0, NULL},
{ENT,    500, 4, 3, 50, 15, {25, 40}, {25, MORDOR_COL-19}, 0, 0, NULL},
{GOBLIN, 100, 4, 3, 10, 10, {30, 34+MORDOR_COL}, {0, 0}, -1, 0, NULL},
{ORC,    200, 3, 2, 30, 12, {28, 34+MORDOR_COL}, {28, FRODO_WIDTH}, 0, 0, NULL},
{WARG,   120, 2, 1, 25,  8, {32, 34+MORDOR_COL}, {32, FRODO_WIDTH}, 0, 0, NULL},
{TROLL,  500, 3, 2, 50, 15, {25, 34+MORDOR_COL}, {25, FRODO_WIDTH}, 0, 0, NULL}
};

static int prices[4][4] = {{500,  500,    0,    0},
	                  { 800,  800,    0, 1500},
		          {1000, 1500,    0,  500},
		          {1500, 1500, 3000,    0}
};

scrll map_scroll;
int status[2];
int lim_map = 0;
int term_col = 1;
char mat_races[N_RACES + 1][RACE_HEIGHT][RACE_WIDTH];
char mat_shadows[N_RACES + 1][RACE_HEIGHT][RACE_WIDTH];
MEVENT event;
build *build_top = NULL;
unit *free_races = NULL;
fortress frodo_house = {1, 15000, 1, 0};
player user = {10000, 10000, 10000, 10000, 10000};

void* read_key(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&l_key);
		switch(getch())
		{
	 		case (KEY_MOUSE):
			if (getmouse(&event) == OK)
			{
				status[0] = STATUS_MOUSE_MOVED;
				if (event.bstate == BUTTON1_CLICKED)
				{
					status[0] = STATUS_MOUSE_CLICK;
					if ((event.y >= map_scroll.row-1) &&
					   (event.y <= map_scroll.row+1))
						mouse_scroll(event.x);
					else
						click_frodooption();
				}
			}
			break;

			case (KEY_UP):
			status[0] = STATUS_UP;
			break;

			case (KEY_DOWN):
			status[0] = STATUS_DOWN;
			break;

			case (KEY_RIGHT):
			if (status[1] != STATUS_MENU)
				arrow_scroll(SCROLL_RIGHT);
			break;

			case (KEY_LEFT):
			if (status[1] != STATUS_MENU)
				arrow_scroll(SCROLL_LEFT);
			break;

			case (EXIT):
			free_build();
			free_map();
			endwin();
			exit(1);

			case (ENTER):
			status[0] = STATUS_ENTER;
		}
		pthread_mutex_unlock(&l_key);
		usleep(2);
	}

	return arg;
}

player get_user()
{
	return user;
}

MEVENT get_event()
{
	return event;
}

int get_keystatus()
{
	return status[0];
}

void set_keystatus(int key_status)
{
	status[0] = key_status;
}

int get_gamestatus()
{
	return status[1];
}

void set_gamestatus(int game_status)
{
	status[1] = game_status;
}

int get_termcol()
{
	return term_col;
}

void set_maplim(int lim)
{
	lim_map = lim;
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
	if ((mouse_col > 0) && (mouse_col <= map_scroll.col) &&
	   (term_col != 0) && (term_col != lim_map))
	{
		pthread_mutex_lock(&l_scroll);
		map_scroll.position = mouse_col;
		map_scroll.residue = 0;
		term_col = map_scroll.proportion * (map_scroll.position - 1);
		term_coltest();
		pthread_mutex_unlock(&l_scroll);
		refresh_allgame();
	}
}

void arrow_scroll(int direction)
{
	int residue;

	if ((term_col <= lim_map) && (MAP_COL > get_sizecol()) &&
	   (term_col >= 0))
	{
		pthread_mutex_lock(&l_scroll);
		term_col+=direction;
		map_scroll.residue+=sqrt(pow(direction, 2));
		if (map_scroll.residue > map_scroll.proportion)
		{
			residue = map_scroll.residue / map_scroll.proportion;
			if (direction > 0)
				map_scroll.position+=residue;
			else
				map_scroll.position-=residue;
			map_scroll.residue-=map_scroll.proportion*residue;
		}
		term_coltest();
		pthread_mutex_unlock(&l_scroll);
		refresh_allgame();
	}
}

scrll get_mapscroll()
{
	return map_scroll;
}

void set_mapscroll(scrll scroll_map)
{
	map_scroll = scroll_map;
}

void term_coltest()
{
	if (term_col < 0)
	{
		term_col = 0;
		map_scroll.position = 1;
		map_scroll.residue = 0;
	}
	if (term_col > lim_map)
	{
		term_col = lim_map;
		map_scroll.position = map_scroll.col;
		map_scroll.position-=map_scroll.col / map_scroll.proportion;
		map_scroll.residue = 0;
	}
}

/* inicializa as unidades com os atributos pre-definidos */
void race_init(unit *chr, int race)
{
	int i;

	for (i = 0; i < N_RACES; i++)
		if (attr[i].race == race)
		{
			chr->race = attr[i].race;
			chr->hp = attr[i].hp;
			chr->spd_delay = attr[i].spd_delay;
			chr->count_delay = attr[i].count_delay;
			chr->dmg = attr[i].dmg;
			chr->height = attr[i].height;
			chr->position[0] = attr[i].position[0];
			chr->position[1] = attr[i].position[1];
			chr->destination[0] = attr[i].destination[0];
			chr->destination[1] = attr[i].destination[1];
			chr->good_type = attr[i].good_type;
			chr->backpack = attr[i].backpack;

			break;
		}
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
	FILE *fp1 = NULL, *fp2 = NULL;

	for (i = 0; i < N_RACES; i++)
	{
		fp1 = read_file(name_filearts[i]);
		fp2 = read_file(name_fileshadows[i]);
		for (j = 0; j < 15; j++)
		{
			fscanf(fp1, "%[^\n]s", mat_races[i][j]);
			fscanf(fp2, "%[^\n]s", mat_shadows[i][j]);
			fgetc(fp1);
			fgetc(fp2);
			if ((feof(fp1)) || (feof(fp2)))
				break;
		}
		fclose(fp1);
		fclose(fp2);
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
			if (mat_shadows[chr.race-1][i][j] == 'r')
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

	if (col <= FRODO_WIDTH)
		load_build(builds[0].name, builds[0].row, builds[0].col);
	else if (col >= builds[1].col - RACE_WIDTH)
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

unit* get_freeraces()
{
	return free_races;
}

void set_freeraces(unit *top)
{
	free_races = top;
}

build* get_buildtop()
{
	return build_top;
}

void set_buildtop(build *top)
{
	build_top = top;
}

void print_good()
{
	int n = 2;
	build *aux = NULL;

	for (aux = build_top; aux != NULL; aux = aux->next)
	{
		sprintf(map[0] + builds[n++].col, "%5d", aux->storage);
	}
}

void check_good(unit *chr)
{
	build *aux;

	for (aux = build_top; aux != NULL; aux = aux->next)
	{
		if ((chr->position[0] == aux->position[0]) &&
		    (chr->position[1] == aux->position[1]))
		{
			chr->backpack+=aux->storage;
			aux->storage = 0;
			chr->destination[0] = 30;
			chr->destination[1] = 40;
		}
		else if ((chr->position[1] == 40) && (chr->position[0] == 30) &&
			(chr->good_type != -1))
		{
			if (chr->race == HOBBIT)
			{
				switch (chr->good_type)
				{
					case 0:
						user.gold+=chr->backpack;
						break;
					case 1:
						user.food+=chr->backpack;
						break;
					case 2:
						user.wood+=chr->backpack;
						break;
					case 3:
						user.metal+=chr->backpack;
				}
				chr->backpack = 0;
				chr->destination[0] = GOOD_ROW;
				chr->destination[1] =
				get_goodcol(chr->good_type);
			}
		}
	}
}

void goto_build(unit *chr, int n_build)
{
	int i;

	if (chr->race == HOBBIT)
		for (i = 0; i < N_BUILDS - 2; i++)
			if (i == n_build)
			{
				chr->destination[0] = GOOD_ROW;
				chr->destination[1] = get_goodcol(i);
				break;
			}
}

void load_houseoption(int n)
{
	int i, j;
	FILE *fp = read_file(options_frodo[n]);

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 13; j++)
			fscanf(fp, "%c", &map[builds[0].row-7+i][n*15+j+5]);
		fgetc(fp);
	}
}

void fortress_buy(int col)
{
	int i, option = 0;

	for (i = 5; i < 80; i+=15)
	{
		if ((col >= i) && (col <= i+13))
		{
			if ((option != 0) && (frodo_house.level >= option) &&
			   (user.gold >= prices[option - 1][0]) &&
			   (user.food >= prices[option - 1][1]) &&
			   (user.wood >= prices[option - 1][2]) &&
			   (user.metal >= prices[option - 1][3]))
			{
				insert_unit(&free_races, option);
				if (option == 1)
					frodo_colect(free_races);
				break;
			}
			else if ((option == 0) && (frodo_house.level < 4) &&
				(user.gold >= 1000 * (frodo_house.level+1)) &&
				(user.food >= 1000 * (frodo_house.level+1)) &&
				(user.wood >= 1000 * (frodo_house.level+1)))
			{
				user.gold-=1000 * (frodo_house.level + 1);
				user.food-=1000 * (frodo_house.level + 1);
				user.wood-=1000 * (frodo_house.level + 1);
				frodo_house.level++;
				option_upgrade(frodo_house.level);
			}
		}
		option++;
	}
}

void option_upgrade(int level)
{
	int i, j;

	if ((level > 1) && (level < 4))
	{
		load_houseoption(level);
		for (i = 0; i < 3; i++)
			map[builds[0].row-5+i][12] = level + 1 + 48;
	}
	else if (level == 4)
	{
		load_houseoption(level);
		for (i = 0; i < 6; i++)
			for (j = 0; j < 13; j++)
				map[builds[0].row-7+i][5+j] = ' ';
	}
}

void all_move()
{
	unit *aux;

	for (aux = free_races; aux!= NULL; aux = aux->next)
	{
		if ((aux->position[0] != aux->destination[0]) ||
				(aux->position[1] != aux->destination[1]))
		{
			aux->count_delay++;
			if (aux->count_delay == aux->spd_delay)
			{
				aux->count_delay = 0;
				clear_unit(*aux);
				move_unit(aux);
			}
		}
	}
}
