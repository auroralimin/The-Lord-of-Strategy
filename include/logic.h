/** @file logic.h
  *
  * @brief Header contendo todas funçoes logicas do programa
  */

/** @struct str_scrll logic.h
  *
  * @brief Estrutura contendo as informacoes nescessarias para realizar o
  *	   side-scrolling do mapa.
  *
  * @param col Indica a coluna do mapa.
  *
  * @param row Indica a linha do mapa
  *
  * @param position Indica a posicao no mapa.
  *
  * @param proportion Indica a proporcao ...?
  *
  * @param residue ???
  */
typedef struct str_scrll
{
	int col;
	int row;
	int position;
	int proportion;
	int residue;
}scrll;


/** Funcao: Ler qual opcao esta sendo clicada.
  *
  * Descricao: ??
  *
  * @param arg ??
  *
  * @return void, nao possui retorno.
  *
  * Requisitos: ??
  */
void* read_key(void *arg);

/** Funcao: Conferir qual opcao o usuario clicou e seguir de acordo.
  *
  * Descricao: ??
  *
  * @param option Indica qual opcao o usuario clicou.
  *
  * @return void, nao possui retorno.
  *
  * Requisitos: A variavel option deve estar entre 1 e 3.
  */
void quit_select(int option);

/** Funcao: Recuperacao das informacoes do usuario.
  *
  * Descricao: Encpasula as informacoes do usuario para nao serem alteradas por
  *            qualquer funcao.
  *
  * @return user, estrutura contendo as informacoes do usaurio.
  *
  * Requisitos: N/A.
  */
player get_user();

/** Funcao: Recupercao das informacoes de eventos.
  *
  * Descricao: ??
  *
  * @return event
  *
  * Requisitos: N/A.
  */
MEVENT get_event();

/** Funcao: Recuperacao do status das chaves (?)
  *
  * Descricao: ??
  *
  * @return status, estado atual do jogo.
  *
  * Requisitos: N/A
  */
int get_keystatus();

/** Funcao: Atribuir um novo valor para o status das chaves (?)
  *
  * Descricao: Encapusla a variavel de status das chaves. Assim, apenas funcoes
  *            que precisam mudar o status tem acesso 'a variavel. (?)
  *
  * @param key_status Variavel que contem o status das chaves (?)
  *
  * @return void, nao possui retorno.
  *
  * Requisitos: N/A.
  */
void set_keystatus(int key_status);

/** Funcao: Recuperacao do status do jogo.
  *
  * Descricao: Encapsula a variavel de status do jogo. Assim, apenas funcoes que
  *            precisam dessa variavel conseguem recuperar seu valor.
  *
  * @return status, estado atual do jogo.
  *
  * Requisitos: N/A.
  */
int get_gamestatus();

/** Funcao: Atribuir um novo valor ao status do jogo.
  *
  * Descricao: Encapsula a variavel de status do jogo. Deste modo, apenas as
  *            as funcoes que precisam mudar o valor do status do jogo conseguem
  *            ter acesso.
  *
  * @param key_status Novo valor a ser atribuido ao status do jogo.
  *
  * @return void, nao possui retorno.
  *
  * Requisitos: N/A.
  */
void set_gamestatus(int key_status);

/** Funcao: Recuperacao da quantidade de colunas do terminal.
  *
  * Descricao: Encapsula a variavel que contem a quantidade de colunas do
  *            terminal. Assim, apenas as funcoes que precisam saber do valor
  *            da variavel possuem acesso.
  *
  * @return term_col
  *
  * Requisitos: N/A.
  */
int get_termcol();

/** Funcao: Atribuir um valor para o limite do mapa.
  *
  * Descricao: Encapsula a variavel que contem o limite do mapa. Assim, apenas
  *            as funcoes que precisam alterar esse valor possuem acesso 'a
  *            variavel.
  *
  * @return void
  *
  * Requisitos: N/A.
  */
void set_maplim(int lim);

/** Funcao: Inicializa a matriz de opcoes.
  *
  * Descricao: Le dos arquivos .txt as ascii art das opcoes, e as colocas na
  *            matriz de opcoes.
  *
  * @return void
  *
  * Requisitos: Os arquivos .txt contendo as ascii art das opcoes.
  */
void init_options();

/** Funcao: ??
  *
  * Descricao: ??
  *
  * @return 1, se...
  * @return 0, se...
  *
  * Requisitos:??
  */
int report_option(int mouse_row, int mouse_col);

/** Funcao: Recuperar as informacoes de scroll do mapa.
  *
  * Descricao: Encapsula a variavel contendo as informacoes do scroll do mapa.
  *            Assim, apenas as funcoes que precisam saber desse valor tem
  	       acesso.
  *
  * @return srcll
  *
  * Requisitos: N/A.
  */
scrll get_mapscroll();

/** Funcao: Atribuir um novo valor para o scroll do mapa.
  *
  * Descricao: Encapsula a variavel contendo as informacoes do scroll do mapa.
  *	       Assim, apenas as funcoes que precisam mudar esse valor podem ter
  *            ter acesso 'a variavel.
  *
  * @return void.
  *
  * Requisitos: N/A.
  */
void set_mapscroll(scrll scroll_map);

/** Funcao: Incializar uma nova unidade.
  *
  * Descricao: Inicializa uma nova unidade de acordo com os atributos de cada 
  *	       raca.
  *
  * @param chr Ponteiro da unidade a ser incializada.
  *
  * @param race Indica a qual raca a nova unidade pertence.
  *
  * @return void
  *
  * Requisitos: chr != NULL e race deve estar entre 1 e 8.
  */
void race_init(unit *chr, int race);

/** Funcao: Ler as ascii art das racas.
  *
  * Descricao: Le os arquivos .txt contendo as ascii art de cada raca e suas
  *            sombras, e as colocas em suas respecitivas matrizes.
  *
  * @return 1, caso tudo tenha dado certo.
  *
  * Requisitos: Os .txt contendo as ascii art de cada raca.
  */
int get_art();

/** Funcao: ??
  *
  * Descricao: ??
  *
  * @return void
  *
  * Requisitos: N/A.
  */
void put_builds();

/** Funcao: Prencher o mapa com espacos.
  *
  * Descricao: Prenche a matriz do mapa com espacos ' ' onde tem '\0'.
  *
  * @return void
  *
  * Requisitos: map != NULL
  */
void map_spaces();

/** Funcao: Imprimir uma unidade no mapa.
  *
  * Descricao: Imprime uma unidade na matriz do mapa em sua devida posicao.
  *
  * @param chr Indica qual unidade sera impressa no mapa.
  *
  * @return void
  *
  * Requisitos: chr != NULL
  */
void printmap_unit(unit chr);

/** Funcao: Atualizar o armazem das construcoes.
  *
  * Descricao: Atualiza o armazem de acordo com a renda de cada construcao, se
  *            o armazem ja nao estiver em sua capacidade maxima.
  *
  * @return void
  *
  * Requisitos: build_top != NULL
  */
void good_generator();

/** Funcao: Recuperar a variavel free_races.
  *
  * Descricao: Encapsula o ponteiro de inicio da lista das unidades do usuario.
  *            Assim, apenas as funcoes que precisam desta variavel podem ter
  *            acesso 'a lista das unidades.
  *
  * @return free_races
  *
  * Requisitos: N/A.
  */
unit* get_freeraces();

/** Funcao: Atribuir um novo inicio para a lista de unidades.
  *
  * Descricao: Encapsula o ponteiro de inicio da lista de uniades do usuario.
  *            Assim, apenas as funcoes que criam ou removem novas unidades
  *            podem mudar o inicio da lista.
  *
  * @param top Inicio da lista de unidades do usuario.
  *
  * @return void
  *
  * Requisitos: N/A.
  */
void set_freeraces(unit *top);

/** Funcao: Recuperar o inicio da lista de construcoes.
  *
  * Descricao: Encapsula o ponteiro de inicio da lista de construcoes do
  *            usauario. Assim, apenas as funcoes que preicam da da lista tem
  *            acesso 'as construcoes.
  *
  * @return build_top, inicio da lista de construcoes do usuario.
  *
  * Requisitos: N/A.
  */
build* get_buildtop();

/** Funcao: Atribuir um novo inicio para  lista de construcoes.
  *
  * Descricao: Encapsula o ponteiro de inicio da lista de construcoes do
  *            usuario. Assim, apenas as funcoes que criam construcoes podem
  *            mudar o inicio da lista.
  *
  * @param top Inicio da lista construcoes do usuario.
  *
  * @return void
  *
  * Requisitos: N/A.
  */
void set_buildtop(build *top);

/** Funcao: Imprimir a quantidade de recursos.
  *
  * Descricao: Imprime a quantidade de recusros armazendas em cada construcao.
  *
  * @return void
  *
  * Requisitos: map != NULL
  */
void print_good();

/** Funcao: Coletar os recuros.
  *
  * Descricao: Faz com que os hobbits coltem os recursos caso eles estejam
  *            perto da construcao a qual estao trabalhando. Caso eles estejam
  *            perto da fortaleza, eles depositam os recursos.
  *
  * @param chr Unidade que esta coletando os recursos.
  *
  * @return void
  *
  * Requisitos: map != NULL e chr != NULL
  */
void check_good(unit *chr);

/** Funcao: Mover os hobbits para a construcao.
  *
  * Descricao: Move os hobbits para a construcao a qual eles estao trabalhando.
  *
  * @param chr Unidade que sera movida.
  *
  * @param n_build Indica que construcao o a unidade deve ir.
  *
  * @return void
  *
  * Requisitos: map != NULL, chr != NULL, n_build entre 1 e 6.
  */
void goto_build(unit *chr, int n_build);

/** Funcao: ??
  *
  * Descricao: ??
  *
  * @param n ??
  *
  * @return void
  *
  * Requisitos: map != NULL, .txt das ascii art das opcoes do usuario (?)
  */
void load_houseoption(int n);

/** Funcao: Desbloquear a proxima raca aliada.
  *
  * Descricao: Permite o usuario desbloquear a proxima raca aliada e comecar a
  *            produzir unidades dessa raca.
  *
  * @param col ??
  *
  * @return void
  *
  * Reqquisitos: N/A.
  */
void fortress_buy(int col);

/** Funcao: Aumentar o nivel da fortaleza.
 *
 * Descricao: Permite o usuario a aumentar o nivel de suas construcoes,
 *            liberando novas racas aliadas para produzir unidades. Caso a
 *            construcao ja esteja no nivel maximo, a opcao de comprar niveis
 *            e' apagada do mapa.
 *
 * @param level Indica nivel atual da construcao.
 *
 * @return void
 *
 * Requisitos: map != NULL, level entre 1 e 4
 */
void option_upgrade(int level);

/** Funcao: Mover todas as unidades.
  *
  * Descricao: Move todas as unidades de acordo com sua posicao atual (caso ja
  *            estejam em seu destino, as unidades nao se movem mais) e do
  *            tempo nescessario para se mover (o qual varia de raca para raca).
  *
  * @return void
  *
  * Requisitos: map != NULL
  */
void all_move();

/** Funcao: Mudar o o trabalho de um hobbit. (?)
  *
  * Descricao: Permite o usuario mudar o tipo de recurso que o hobbit esta
  *            recolhendo.(?)
  * @return void
  *
  * Requisitos: N/A.
  */
void save(char *save_name);
void load(char *load_dir);
