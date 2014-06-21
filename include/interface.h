void init_interface();
void get_dimension();
WINDOW* create_win(int win_y, int win_x, int starty, int startx);
void destroy_win(WINDOW **local_win);
void print_menu(WINDOW *menu_win, int highlight);
void printw_map();
