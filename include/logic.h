void* read_key(void *arg);
void init_options();
int report_option(int mouse_row, int mouse_col);
unit race_init(int race);
int load_build(char *file_name, int art_row, int art_col);
int get_art();
void printmap_unit(unit chr);
void clear_unit(unit chr);
void move_unit(unit *chr);
