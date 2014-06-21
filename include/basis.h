#include <ncurses.h>

#define REFRESH_TIME 500000
#define SIZE_COLUMN 1530
#define MINIMUM_ROW 41
#define MINIMUN_COL 110

#define STATUS_MOUSE_MOVED 0
#define STATUS_MOUSE_CLICK 1
#define STATUS_UP 2
#define STATUS_DOWN 3
#define STATUS_ENTER 4
#define STATUS_RIGHT 5
#define STATUS_LEFT 6
#define STATUS_EXIT -1

#define EXIT 'k'
#define ENTER '\n'

#define MENU_ROW 40
#define MENU_COL 110
#define N_OPTIONS 3
#define OPTIONS_WIDTH 8
#define NEW_GAME 92
#define LOAD_GAME 105
#define EXIT_GAME 41

#define MORDOR_WIDTH 86
#define MORDOR_ROW 40
#define MORDOR_COL SIZE_COLUMN - MORDOR_WIDTH
#define FRODO_WIDTH 127
#define FRODO_ROW 31
#define FRODO_COL 0

#define RIGHT 1
#define LEFT 0
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
	int direction;
	int spwan_time;
} unit;

typedef struct str_build
{
	int id;
	int level;
	int income;
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
	int mithril;
	int wood;
	int food;
} player;


extern pthread_mutex_t l_key, l_sync;
extern pthread_t key_thread;
extern int key_status;
extern MEVENT event;
extern char **map;
extern int lim_map;
extern int size_row, size_col;
extern int term_col;
extern char **options[N_OPTIONS];

void init_locks();
void init_thread();
void aloc_map();
void init_map();
void free_map();
FILE* read_file(char *name);
void aloc_options();
