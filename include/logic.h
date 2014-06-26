typedef struct str_scrll
{
	int col;
	int row;
	int position;
}scrll;

void* read_key(void *arg);
MEVENT get_event();
int get_keystatus();
void set_keystatus(int key_status);
int get_gamestatus();
void set_gamestatus(int key_status);
int get_termcol();
void set_maplim(int lim);
void init_options();
int report_option(int mouse_row, int mouse_col);
void mouse_scroll(int mouse_col);
void arrow_scroll(int direction);
scrll get_mapscroll();
void set_mapscroll(scrll scroll_map);
void term_coltest();
unit race_init(int race);
int load_build(char *file_name, int art_row, int art_col);
int get_art();
void map_spaces();
void put_builds();
void printmap_unit(unit chr);
void clear_unit(unit chr);
void move_unit(unit *chr);
void good_generator();
build* get_buildtop();
void set_buildtop(build *top);
void print_good();
