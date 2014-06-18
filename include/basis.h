#include <stdio.h>

#define SIZE_COLUMN 300
#define MINIMUM_ROW 41

#define MORDOR_ROW 40
#define MORDOR_COL SIZE_COLUMN - 86
#define FRODO_ROW 31
#define FRODO_COL 0

#define RIGHT 1
#define LEFT 0

#define N_RACES 8
#define RACE_HEIGHT 15
#define RACE_WIDTH 19
#define HOBBIT 1
#define ELF 2
#define DWARF 3
#define ENT 4
#define GOBLIN 5
#define ORC 6
#define WARG 7
#define TROLL 8

typedef struct str_unit
{
	int race;
	int hp;
	int spd;
	int dmg;
	int height;
	int position[2];
	int destination[2];
	int direction;
} unit;

extern char **map;
extern int size_row, size_col;

void aloc_map();
void init_map();
void free_map();
FILE* read_file(char *name);
unit race_init(int race);
