#include <stdio.h>
#include "basis.h"
#include "logic.h"

char *options_files[] = { "ASCII art/new_game.txt",
			"ASCII art/load_game.txt",
			"ASCII art/exit.txt"};

/* matriz contendo o endereço da ascii art do jogo */
static char *name_filearts[] = { "ASCII art/race_blank.txt",
	                  "ASCII art/hobbit.txt",
			  "ASCII art/elf.txt",
			  "ASCII art/dwarf.txt",
			  "ASCII art/ent.txt",
			  "ASCII art/goblin.txt",
			  "ASCII art/orc.txt",
			  "ASCII art/warg.txt",
			  "ASCII art/troll.txt"
};

static unit attr[] = {
{HOBBIT, 100, 1, 10, 10, {19-FRODO_ROW, 40}, {0, MORDOR_COL}, RIGHT, 100},
{ELF, 130, 4, 40, 12, {17-FRODO_ROW, 40}, {0, MORDOR_COL}, RIGHT, 200},
{DWARF, 250, 2, 30, 10, {19-FRODO_ROW, 40}, {0, MORDOR_COL}, RIGHT, 250},
{ENT, 500, 1, 50, 15, {14-FRODO_ROW, 40}, {0, MORDOR_COL}, RIGHT, 300},
{GOBLIN, 100, 1, 10, 10, {30-MORDOR_ROW, 34+MORDOR_COL}, {0, 0}, LEFT, 100},
{ORC, 200, 2, 30, 12, {28-MORDOR_ROW, 34+MORDOR_COL}, {0, 0}, LEFT, 200},
{WARG, 120, 5, 25, 8, {32-MORDOR_ROW, 34+MORDOR_COL}, {0, 0}, LEFT, 250},
{TROLL, 500, 1, 50, 15, {25-MORDOR_ROW, 34+MORDOR_COL}, {0, 0}, LEFT, 300}
};

char mat_races[N_RACES + 1][RACE_HEIGHT][RACE_WIDTH];

void init_options()
{
	FILE *fp = NULL;

	for (int i = 0; i < N_OPTIONS; i++)
	{
		fp = read_file(options_files[i]);
		for (int j = 0; j < OPTIONS_WIDTH; j++)
		{
			fscanf(fp, "%[^\n]s", options[i][j]);
			fgetc(fp);
		}
		fclose(fp);
	}
}

int report_option(int mouse_row, int mouse_col, int start_y, int start_x)
{
	if ((mouse_row > start_y) && (mouse_row < start_y + MENU_ROW - 2) &&
	   (mouse_col > start_x) && (mouse_col < start_x + MENU_COL - 2))
		return 1 + (mouse_row / 13);
	return 0;
}

/* inicializa as unidades com os atributos pre-definidos */
unit race_init(int race)
{
	unit new_unit;

	for (int i = 0; i < N_RACES; i++)
		if (attr[i].race == race)
		{
			new_unit.race = attr[i].race;
			new_unit.hp = attr[i].hp;
			new_unit.spd = attr[i].spd;
			new_unit.dmg = attr[i].dmg;
			new_unit.height = attr[i].height;
			new_unit.position[0] = attr[i].position[0]+size_row;
			new_unit.position[1] = attr[i].position[1];
			new_unit.destination[0] = attr[i].destination[0];
			new_unit.destination[1] = attr[i].destination[1];
			new_unit.direction = attr[i].direction;
			new_unit.spwan_time = attr[i].spwan_time;
			break;
		}
	return new_unit;
}

/* carrega o mapa com as fortalezas do jogador e do computador */
void load_build(char *file_name, int art_row, int art_col)
{
	FILE *fp = NULL;

	fp = read_file(file_name);

	for (int i = size_row - art_row; i < size_row; i++)
	{
		fscanf(fp, "%[^\n]s", map[i] + art_col);
		fgetc(fp);
		if (feof(fp))
			break;
	}
	fclose(fp);

}

/* le a ascii art das racas */
void get_art()
{
	FILE *fp = NULL;

	for (int i = 0; i <= N_RACES; i++)
	{
		fp = read_file(name_filearts[i]);
		for (int j = 0; j < 15; j++)
		{
			fscanf(fp, "%[^\n]s", mat_races[i][j]);
			fgetc(fp);
			if (feof(fp))
				break;
		}
		fclose(fp);
	}
}

/* printa as unidades na tela do terminal */
void printmap_unit(unit chr)
{
	int row = chr.position[0], col = chr.position[1];

	for (int i = RACE_HEIGHT - chr.height; i < RACE_HEIGHT; i++)
	{
		for (int j = 0; j < RACE_WIDTH; j++)
		{
			if (mat_races[chr.race][i][j] != ' ')
				map[row][col] = mat_races[chr.race][i][j];
			col++;
		}
		col = chr.position[1];
		row++;
	}
}

void clear_unit(unit chr)
{
	int row = chr.position[0], col = chr.position[1];

	for (int i = RACE_HEIGHT - chr.height; i < RACE_HEIGHT; i++)
	{
		for (int j = 0; j < RACE_WIDTH; j++)
			map[row][col++] = ' ';
		col = chr.position[1];
		row++;
	}
	if (col < FRODO_WIDTH)
		load_build("ASCII art/house_frodo.txt", FRODO_ROW, FRODO_COL);
	else if (col > MORDOR_COL)
		load_build("ASCII art/mordor_tower.txt",MORDOR_ROW,MORDOR_COL);
}

void move_unit(unit *chr)
{
	if (chr->position[1]+28 <= chr->destination[1])
	{
		chr->position[0] = size_row - chr->height;
		chr->position[1]+= 9;
	}
}
