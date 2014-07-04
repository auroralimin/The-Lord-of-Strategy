/** @file basis.h
  *
  * @brief Header contendo todos os defines e funcoes basicas do programa
  */

#include <ncurses.h>

#define MAP_ROW 40
#define MAP_COL 1000
#define REFRESH_TIME 200000
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
#define STATUS_PAUSED 2
#define STATUS_EXIT -1

#define EXIT 'q'
#define ENTER '\n'
#define PAUSE 'p'
#define YES 'y'
#define NO 'n'

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
#define METAL_COL1 FRODO_WIDTH + 260
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

/** @struct str_unit basis.h
  *
  * @brief Estrutura contendo as informacoes de cada unidade.
  *
  * @param race Indica a raca da unidade.
  *
  * @param hp Indica o quanto de pontos de vida a unidade possui. Varia de
  * acordo com a raca.
  *
  * @param spd_delay Indica o tempo que a unidade precisa para se movimentar
  * antes de poder se movimentar de novo. Varia de acordo com a raca.
  *
  * @param count_delay Conta o tempo nescessario para a unidade se mover de
  * novo. Varia de acordo com a raca.
  *
  * @param dmg Indica o quanto de pontos de vida essa unidade causa a unidades
  * inimigas. varia de acordo com a raca.
  *
  * @param height Indica a altura da unidade.
  *
  * @param position Indica a posicao atual da unidade no mapa.
  *
  * @param destination Indica a posicao do mapa a qual a unidade tentara chegar.
  *
  * @param good_type ...
  *
  * @param backpack ...
  *
  * @param next Indica qual e' a proxima unidade na lista encadadeada.
  */
typedef struct str_unit
{
	int race;
	int hp;
	int spd_delay;
	int count_delay;
	int dmg;
	int height;
	int position[2];
	int destination[2];
	int good_type;
	int backpack;
	struct str_unit *next;
} unit;

/** @struct str_build basis.h
  *
  * @brief Estrutura contendo as informacoes de cada construcao.
  *
  * @param id Indica o tipo de construcao.
  *
  * @param level Indica o nivel de aprimoramento da construcao.
  *
  * @param storage Indica a quantidade de recurso que construcao possui
  * armazenado.
  *
  * @param income Indica a quantidade de recurso que a construcao recebe por
  * looping. Varia de acordo com o nivel da construcao.
  *
  * @param position Indica a posicao da construcao no mapa.
  *
  * @param next Indica qual e' a proxima unidade na lista encadeada.
  */
typedef struct str_build
{
	int id;
	int level;
	int storage;
	int income;
	int position[2];
	struct str_build *next;
} build;


/** @struct str_fortress basis.h
  *
  * @brief Estrutura que contem as informacoes da fortaleza.
  *
  * @param id Indica o tipo da fortaleza: usuario ou computador.
  *
  * @param hp Indica quantos pontos de vida a fortaleza possui.
  *
  * @param level Indica o nivel atual da fortaleza.
  *
  * @param work_time ...
  */
typedef struct str_fortress
{
	int id;
	int hp;
	int level;
	int work_time;
} fortress;

/** @struct str_player basis.h
  *
  * @brief Estrutura contendo as informacoes do jogador.
  *
  * @param id Indica o tipo de jogador: usuario ou computador.
  *
  * @param good ...
  */
typedef struct str_player
{
	int id;
	int good[4];
} player;

extern int click_sync;
extern pthread_mutex_t l_key, l_scroll, l_printmap, l_pause, l_unit;
extern char **map;
extern char **options[N_OPTIONS];


/** Funcao: ??.
  *
  * Descricao: ??
  *
  * @return Nao possui retorno.
  *
  * Requistos: N/A.
  */
void init_locks();


/** Funcao: Inicializar as threas usadas no programa.
  *
  * Descricao: Inicializa uma thread, caso nao seja possivel inicializar a
  *            thread, a funcao mostra um erro na tela e sai do programa.
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void init_thread();

/** Funcao: Chama as funcoes de preparacao do mapa na ordem correta.
  *
  * Descricao: ??
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void prepare_map();

/** Funcao: Alocar o espaco nescessario na memoria para o uso do mapa.
  *
  * Descricao: Aloca uma matriz na memoria para guardar o mapa.
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void aloc_map();

/** Funcao: Inicializar a matriz do mapa.
  *
  * Descricao: Inicializa a matriz contendo o mapa do jogo com espacos ' '.
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void init_map();

/** Funcao: Liberar a matriz do mapa.
  *
  * Descricao: Libera a matriz, contendo o mapa, da memoria do computador. Se a
  *            matriz foi liberada corretamente, a variavel mapa e' igualada a 
  *            NULL.
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void free_map();

/** Funcao: Abre o arquivo .txt a ser usado.
  *
  * Descricao: Abre o arquivo .txt. Caso nao seja possivel abrir o arquivo, o
  *            programa mostra uma mensagem de erro, libera as possiveis
  *            alocacoes e sai. Caso consiga abrir, a funcao retorna o ponteiro
  *            do arquivo.
  *
  * @param name Contem o endereco do arquivo .txt a ser aberto.
  *
  * @return O ponteiro do arquivo .txt.
  *
  * Requisitos: Possuir os arquivos .txt nescessarios para o programa.
  */
FILE* read_file(char *name);

/** Funcao: Aloca o espaco na memoria para a matriz de opcoes.
  *
  * Descricao: Aloca uma matriz na memoria para guardar as opcoes
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void aloc_options();

/** Funcao: Libera a matriz de opcoes.
  *
  * Descricao: Libera o espaco alocado para a matriz de opcoes. Se a matriz for
  *            liberada corretamente, a variavel options e' igualada 'a NULL.
  *
  * @return Nao possui rentorno.
  *
  * Requisitos: options != NULL.
  */
void free_options();

/** Funcao: Cria e insere uma unidade.
  *
  * Descricao: Cria e insere uma nova unidade na lista de unidades.
  *
  * @param top Ponteiro de ponteiro do topo da lista de unidades.
  * @param race Indica qual raca o jogador deseja criar.
  *
  * @return -1, caso nao seja possivel criar a nova unidade.
  * @return  1, caso consiga criar e inserir a nova unidade.
  *
  * Requisitos: O parametro race deve estar entre 1 e 8.
  */
int insert_unit(unit **top, int race);

/** Funcao: Libera as unidades.
  *
  * Descricao: Libera a lista encadeada de unidades. Se a lista for liberada
  *            corretamente, a variavel top e' igualada 'a NULL.
  *
  * @param top Ponteiro de ponteiro contendo o topo da lista de unidades.
  *
  * @return Nao possui retorno.
  *
  * Requistos: N/A.
  */
void free_units(unit **top);

/** Funcao: Cria a lista de construcoes.
  *
  * Descricao: Cria a lista de construcoes a serem usadas. Caso nao seja
  *            possivel criar a lista, o programa mostra uma mensaem de erro, e
  *            sai.
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A.
  */
void create_listbuild();

/** Funcao: Cria e insere uma nova construcao.
  *
  * Descricao: Cria e insere uma nova construcao na lista de construcoes. Caso
  *            nao seja possivel criar, o programa sai da funcao e retorna -1.
  *
  * @param id Indica qual tipo de construcao sera criada.
  *
  * @return -1, caso nao seja possivel alocar o espaco para a nova construcao.
  * @return  1, caso consiga criar e inserir a nova construcao.
  *
  * Requisitos: O parametro id deve estar entre 1 e 6.
  */
int insert_build(int id);

/** Funcao: Liberar a lista de construcoes.
  *
  * Descricao: Libera a lista encadeada de construcoes. Se a lista for liberada
  *	       corretamente, a variavel build_top e' igualada 'a NULL.
  *
  * @return Nao possui retorno.
  *
  * Requisitos: N/A
  */
void free_build();

/** Funcao: Encapsulamento da variavel good_col.
  *
  * @param i Indica qual das construcoes do usuario deseja-se saber o numero de
  *          colunas.
  *
  * @return good_col[i]
  *
  * Requisitos: N/A.
  */
int get_goodcol(int i);

/** Funcao: Sai do jogo.
  *
  * Descricao: Chama as funcoes de liberar construcoes e mapa na ordem, e sai do
  *            programa.
  *
  * Requisitos: N/A.
  */
int exit_game();
