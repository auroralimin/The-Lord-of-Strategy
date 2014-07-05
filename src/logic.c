#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
{HOBBIT, 100, 3, 2, 10, 10, {30, 40}, {30, 40},-1, 0, NULL},
{ELF,    130, 2, 1, 40, 12, {28, 40}, {28, MORDOR_COL-19},-1, 0, NULL},
{DWARF,  250, 3, 2, 30, 11, {29, 40}, {29, MORDOR_COL-19},-1, 0, NULL},
{ENT,    500, 4, 3, 50, 15, {25, 40}, {25, MORDOR_COL-19},-1, 0, NULL},
{GOBLIN, 100, 4, 3, 10, 10, {30, 34+MORDOR_COL}, {0, 0}, -1, 0, NULL},
{ORC,    200, 3, 2, 30, 12, {28, 34+MORDOR_COL}, {28, FRODO_WIDTH},-1, 0, NULL},
{WARG,   120, 2, 1, 25,  8, {32, 34+MORDOR_COL}, {32, FRODO_WIDTH},-1, 0, NULL},
{TROLL,  500, 3, 2, 50, 15, {25, 34+MORDOR_COL}, {25, FRODO_WIDTH},-1, 0, NULL}
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
player user = {1, {10000, 10000, 10000, 10000}};
char *hobbit_good[] = {"GOLD ", "FOOD ", "WOOD ", "METAL"};

void mouse_clicked();
void game_paused();
void mouse_scroll(int mouse_col);
void arrow_scroll(int direction);
void term_coltest();
int load_build(char *file_name, int art_row, int art_col);
void clear_unit(unit chr);
void move_unit(unit *chr);

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
						mouse_clicked();
				}
				break;

			case (PAUSE):
				if ((status[1] != STATUS_EXIT) &&
				   (status[1] != STATUS_MENU))
					game_paused();
				break;
			case (KEY_UP):
				if (status[1] == STATUS_MENU)
					status[0] = STATUS_UP;
				break;

			case (KEY_DOWN):
				if (status[1] == STATUS_MENU)
					status[0] = STATUS_DOWN;
				break;

			case (KEY_RIGHT):
				if (status[1] == STATUS_GAME)
					arrow_scroll(SCROLL_RIGHT);
				break;

			case (KEY_LEFT):
				if (status[1] == STATUS_GAME)
					arrow_scroll(SCROLL_LEFT);
				break;

			case (YES):
				quit_select(2);
				break;

			case (NO):
				quit_select(3);
				break;

			case (EXIT):
				if (status[1] != STATUS_MENU)
					quit_select(1);
				break;

			case (ENTER):
				if (status[1] == STATUS_MENU)
					status[0] = STATUS_ENTER;
		}
		pthread_mutex_unlock(&l_key);
		usleep(2);
	}

	return arg;
}

void mouse_clicked()
{
	int term_row = get_sizerow(), term_col = get_sizecol();

	status[0] = STATUS_MOUSE_CLICK;

	if (status[1] == STATUS_EXIT)
		quit_answer();

	else if ((event.y > (term_row-MAP_ROW-2)/2 - 3) &&
	        (event.y < (term_row-MAP_ROW-2)/2 + 1))
	{
		if ((event.x > term_col - 25) && (event.x < term_col - 19))
			game_paused();

		else if (event.x > term_col - 7)
			quit_select(1);
	}
	else if ((status[1] != STATUS_PAUSED) &&
		(event.y >= map_scroll.row-1) && (event.y <= map_scroll.row+1))
		mouse_scroll(event.x);

	else if ((status[1] != STATUS_PAUSED) && (!click_frodooption()))
		change_hobbit(event.y, event.x);
}

void quit_select(int option)
{
	switch (option)
	{
		case 1:
			if (status[1] != STATUS_PAUSED)
			{
				game_paused();
				status[1] = STATUS_EXIT;
			}
			else
				status[1] = STATUS_EXIT;
			refresh_allgame();
			break;
		case 2:
			if (status[1] == STATUS_EXIT)
			{
				save("saves/save1");
				exit_game();
			}
			break;
		case 3:
			if (status[1] == STATUS_EXIT)
				{
					status[1] = STATUS_PAUSED;
					game_paused();
				}
	}
}

void game_paused()
{
	if (status[1] == STATUS_PAUSED)
	{
		status[1] = STATUS_GAME;
		pthread_mutex_unlock(&l_pause);
		move_msg(0);
	}
	else
	{
		status[1] = STATUS_PAUSED;
		pthread_mutex_lock(&l_pause);
		move_msg(1);
		refresh_allgame();
	}
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
		fp = open_file(options_files[i], "r");
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

	fp = open_file(file_name, "r");

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
		fp1 = open_file(name_filearts[i], "r");
		fp2 = open_file(name_fileshadows[i], "r");
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

	pthread_mutex_lock(&l_unit);
	if (chr.good_type >= 0)
		snprintf(map[row+1]+col+13, 6,"%s", hobbit_good[chr.good_type]);
	snprintf(map[row]+col+13, 7,  "HP:%3d", chr.hp);

	for (i = RACE_HEIGHT - chr.height; i < RACE_HEIGHT; i++)
	{
		for (j = 0; j < RACE_WIDTH; j++)
		{
			if ((mat_shadows[chr.race-1][i][j] == 'r') &&
			   (row < MAP_ROW) && (col < get_sizecol()))
				map[row][col] = mat_races[chr.race-1][i][j];
			col++;
		}
		col = chr.position[1];
		row++;
	}
	pthread_mutex_unlock(&l_unit);
}

void clear_unit(unit chr)
{
	int i, j, row = chr.position[0], col = chr.position[1];

	pthread_mutex_lock(&l_unit);
	for (i = RACE_HEIGHT - chr.height; i < RACE_HEIGHT; i++)
	{
		for (j = 0; j < RACE_WIDTH; j++)
			if ((row < MAP_ROW) && (col < get_sizecol()))
				map[row][col++] = ' ';
		col = chr.position[1];
		row++;
	}

	if (col <= FRODO_WIDTH)
		load_build(builds[0].name, builds[0].row, builds[0].col);
	else if (col >= builds[1].col - RACE_WIDTH)
		load_build(builds[1].name, builds[1].row, builds[1].col);
	map_spaces();
	pthread_mutex_unlock(&l_unit);
}

void move_unit(unit *chr)
{
	int dest = 1, n = 1;

	pthread_mutex_lock(&l_unit);
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
	pthread_mutex_unlock(&l_unit);
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
		snprintf(map[0] + builds[n++].col, 6, "%5d", aux->storage);
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
				user.good[chr->good_type]+=chr->backpack;
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
	FILE *fp = open_file(options_frodo[n], "r");

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 13; j++)
			fscanf(fp, "%c", &map[builds[0].row-7+i][n*15+j+5]);
		fgetc(fp);
	}
}

void fortress_buy(int col)
{
	int i, j, option = 0, level = frodo_house.level;
	unit *aux;

	for (i = 5; i < 80; i+=15)
	{
		if ((col >= i) && (col <= i+13))
		{
			if ((option != 0) && (level >= option))
			{
				if ((user.good[0] < prices[option - 1][0]) ||
			   	   (user.good[1] < prices[option - 1][1]) ||
			   	   (user.good[2] < prices[option - 1][2]) ||
			   	   (user.good[3] < prices[option - 1][3]))
					break;

				for (j = 0; j < 3; j++)
					user.good[j]-=prices[option-1][j];
				insert_unit(&free_races, option, NULL);
				if (option == 1)
				{
					aux = free_races;
					while (aux != NULL)
					{
						if (aux->race == HOBBIT)
						{
							frodo_colect(aux);
							break;
						}
						aux = aux->next;
					}
				}
				break;
			}
			else if ((option == 0) && (frodo_house.level < 4))
			{
				if ((user.good[0] < 1000 * (level+1)) ||
				   (user.good[1] < 1000 * (level+1))  ||
				   (user.good[2] < 1000 * (level+1)))
					break;

				for (j = 0; j < 3; j++)
					user.good[j]-=
					1000 * (frodo_house.level + 1);
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

void save(char *save_dir)
{
	char *unit_file, *build_file, *player_file;
	struct stat st;
	unit *aux_u;
	build *aux_b;
	FILE *fp;

	if (stat(save_dir, &st) == -1)
	    	mkdir(save_dir, 0700);

	unit_file = (char*) calloc(strlen(save_dir)+11, sizeof(char));
	strcpy(unit_file, save_dir);
	strcat(unit_file, "/units.bin");
	fp = open_file(unit_file, "wb");
	for (aux_u = free_races; aux_u != NULL; aux_u = aux_u->next)
		fwrite(aux_u, sizeof(unit), 1, fp);
	fclose(fp);

	build_file = (char*) calloc(strlen(save_dir)+12, sizeof(char));
	strcpy(build_file, save_dir);
	strcat(build_file, "/builds.bin");
	fp = open_file(build_file, "wb");
	for (aux_b = build_top; aux_b != NULL; aux_b = aux_b->next)
		fwrite(aux_b, sizeof(build), 1, fp);
	fclose(fp);

	player_file = (char*) calloc(strlen(save_dir)+13,sizeof(char));
	strcpy(player_file, save_dir);
	strcat(player_file, "/players.bin");
	fp = open_file(player_file, "wb");
	fwrite(&user, sizeof(player), 1, fp);
	fclose(fp);
}

void load(char *load_dir)
{
	char *unit_file, *build_file, *player_file;
	struct stat st;
	unit *aux_u = (unit*) calloc(1, sizeof(unit));
	build *aux_b1 = (build*) calloc(1, sizeof(build));
	build *aux_b2 = build_top;
	FILE *fp;

	if (stat(load_dir, &st) != -1)
	{
		unit_file = (char*) calloc(strlen(load_dir)+11, sizeof(char));
		strcpy(unit_file, load_dir);
		strcat(unit_file, "/units.bin");
		fp = open_file(unit_file, "rb");
		while (fread(aux_u, sizeof(unit), 1, fp) > 0)
			insert_unit(&free_races, aux_u->race, aux_u);
		fclose(fp);

		build_file = (char*) calloc(strlen(load_dir)+12, sizeof(char));
		strcpy(build_file, load_dir);
		strcat(build_file, "/builds.bin");
		fp = open_file(build_file, "rb");
		while (fread(aux_b1, sizeof(build), 1, fp) > 0)
		{
			if (aux_b2 != NULL)
			{
				aux_b2->level = aux_b1->level;
				aux_b2->storage = aux_b1->storage;
				aux_b2->income = aux_b1->income;
				aux_b2 = aux_b2->next;
			}
		}
		fclose(fp);

		player_file = (char*) calloc(strlen(load_dir)+13,sizeof(char));
		strcpy(player_file, load_dir);
		strcat(player_file, "/players.bin");
		fp = open_file(player_file, "rb");
		fread(&user, sizeof(player), 1, fp);
		fclose(fp);

		free(aux_u);
		free(aux_b1);
	}
	else
		exit_game();
}
