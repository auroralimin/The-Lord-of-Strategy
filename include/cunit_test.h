/* suites initializations and clean functions */
int init_basis(void);
int clean_basis(void);
int init_logic(void);
int clean_logic(void);
int init_interf(void);
int clean_interface(void);

/* basis tests functions */
void aloc_map_test(void);
void init_map_test(void);
void free_map_test(void);
void read_file_test(void);
void aloc_opt_test(void);
void free_opt_test(void);
void insert_b_test(void);
void free_build_test(void);

/* logic tests functions */
void map_spaces_test(void);
void init_opt_test(void);
void race_init_test(void);
void load_build_test(void);
void get_art_test(void);
void print_unit_test(void);
void clear_unit_test(void);
void move_unit_test(void);
void get_freer_test(void);
void set_freer_test(void);

/* interface test function */
void click_test(void);
