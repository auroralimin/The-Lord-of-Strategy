#include <ncurses.h>

#define MAP_ROW 40
#define MAP_COL 1530
#define REFRESH_TIME 500000
#define MINIMUM_ROW 50
#define MINIMUN_COL 110

#define STATUS_MOUSE_MOVED 0
#define STATUS_MOUSE_CLICK 1
#define STATUS_UP 2
#define STATUS_DOWN 3
#define STATUS_ENTER 4
#define STATUS_RIGHT 5
#define STATUS_LEFT 6

#define STATUS_MENU 0
#define STATUS_GAME 1
#define STATUS_EXIT -1

#define EXIT 'k'
#define ENTER '\n'

#define SCROLL_RIGHT 9
#define SCROLL_LEFT -9

#define MENU_ROW 40
#define MENU_COL 110
#define N_OPTIONS 3
#define OPTIONS_WIDTH 8
#define NEW_GAME 103
#define LOAD_GAME 116
#define EXIT_GAME 52

#define N_BUILDS 6
#define MORDOR_WIDTH 86
#define MORDOR_ROW 40
#define MORDOR_COL MAP_COL - MORDOR_WIDTH
#define FRODO_WIDTH 121
#define FRODO_ROW 27
#define FRODO_COL 0

#define GOLD_COL1 FRODO_WIDTH + 1
#define FOOD_COL1 FRODO_WIDTH + 87
#define WOOD_COL1 FRODO_WIDTH + 176
#define METAL_COL1 FRODO_WIDTH + 255
#define HOBBIT_GOLD GOLD_COL1 + 8
#define HOBBIT_FOOD FOOD_COL1 + 2
#define HOBBIT_WOOD WOOD_COL1 + 4
#define HOBBIT_METAL METAL_COL1 + 23
#define GOOD_ROW 6

#define USER 0
#define COMP 1

/* races */
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

/* buildings */
#define MAX_BUILD_LVL 3
#define CURRENT_INCOME(x) 20 + x * 10
#define MAX_FORTRESS_HP 100000;

typedef struct str_unit
{
	int race;
	int hp;
	int spd;
	int dmg;
	int height;
	int position[2];
	int destination[2];
	int spwan_time;
	int backpack[N_BUILDS - 2];
	struct str_unit *next;
} unit;

typedef struct str_build
{
	int id;
	int level;
	int storage;
	int income;
	struct str_build *next;
} build;

typedef struct str_fortress
{
	int id;
	int level;
	int hp;
	int unlock_race;
	int work_time;
} fortress;

typedef struct str_player
{
	int id;
	int gold;
	int food;
	int wood;
	int metal;
} player;

extern pthread_mutex_t l_key;
extern char **map;
extern char **options[N_OPTIONS];

void init_locks();
void init_thread();
void prepare_map();
void aloc_map();
void init_map();
void free_map();
FILE* read_file(char *name);
void aloc_options();
void free_options();
int insert_unit(unit **top, int race);
void free_units(unit **top);
void create_listbuild();
int insert_build(int id);
void free_build();
