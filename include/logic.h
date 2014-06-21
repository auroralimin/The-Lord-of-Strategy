void init_options();
int report_option(int mouse_row, int mouse_col, int start_y, int start_x);
unit race_init(int race);
void load_build(char *file_name, int art_row, int art_col);
void get_art();
void printmap_unit(unit chr);
void clear_unit(unit chr);
void move_unit(unit *chr);
