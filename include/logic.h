/** @file logic.h
  *
  * @brief Header contendo todas funçoes logicas do programa
  */

/** @struct str_scrll logic.h
  *
  * @brief Estrutura contendo as informacoes nescessarias para realizar o
  *	   side-scrolling do mapa.
  *
  * @param col Indica o numero de colunas do scroll.
  *
  * @param row Indica em que linha do terminal esta desenhado o scroll.
  *
  * @param position Indica a posicao no mapa.
  *
  * @param proportion Indica a proporcao de numero de colunas do mapa pelo
  * numero de colunas do scroll
  *
  * @param residue Quando um personagem e' simbolizado no scroll, sua posicao
  * pode estar entre um traco do scroll e outro. E feito uma conta para
  * arredondar isso e saber em que traco do scroll o personagem e' desenhado
  * Essa variavel guarda a sobra (residuo) dessa conta.
  */
typedef struct str_scrll
{
	int col;
	int row;
	int position;
	int proportion;
	int residue;
}scrll;


/** Funcao: Le e interpreta a entrada de dados do usuario
  *
  * Descricao/Hipotese: Essa funcao foi feita pra ser executada por uma thread
  *                     paralela a principal e tem como proposito captar a
  *                     entrada de dados do teclado e do mouse, interpretar
  *                     esses dados e chamar as funcoes necessarias dependendo
  *                     dos dados. Desta forma, ela tem o poder de interpretar
  *                     uma acao do usuario e reponder mudando o status do jogo,
  *                     deixando-o pausado, por exemplo. Alem do pause ela pode
  *                     comandar o "save", o "load" e "quit". Tambem e' a
  *                     responsavel por comandar o scroll do jogo e pela
  *                     interpretacao de cliques em botoes no mapa.
  *
  * Interface explicita: @param arg Parametro inutilizado, mas necessario para
  *                      a funcao se adequar a assinatura padrao necessaria para
  *                      criar uma thread baseando ela como funcao principal.
  *
  * Interface implicita: -event: Variavel global que guarda os dados captados
  *                      por movimentos do mouse.
  *                      -l_key: Variavel externa do modulo basis que serve como
  *                      mecanismo de sincronizacao.
  *
  * Contrato/Requisitos: Deve ser chamada por uma funcao que cria uma thread
  *                      (funcao create_thread) e nao somente com "read_key()".
  *                      Alem disso, antes de ser chamada, todos os mecanismos
  *                      de sincronizacao declarados como extern na basis (os
  *                      mutex) devem estar inicializados.
  *
  * @return Ponteiro de void. Mas esse valor de retorno nao e' importante, so
  *         existe porque como a funcao e' feita para ser executada como sendo
  *         a principal de uma thread paralela, o padrao determina que ela deve
  *         ter como retorno um ponteiro de void.
  */
void* read_key(void *arg);

/** Funcao: Conferir qual opcao o usuario clicou e seguir de acordo.
  *
  * Descricao/Hipotese: Confirma qual opcao o usuario selecionou no menu de
  *                     opcoes in-game e segue de acordo. Caso o usuario clicou
  *                     em Resume, ele voltara ao jogo. Caso ele clicou em Exit,
  *                     ele saira do jogo.
  *
  * Interface explifica: @param options: indica qual opcao foi selecionada.
  *
  * Interface implicita: -status: contem o status atual do jogo.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void, nao possui retorno.
  */
void quit_select(int option);

/** Funcao: Recuperar as informacoes da fortaleza do Frodo
  *
  * Descricao/Hipotese: Encpasula as informacoes da casa do Frodo para nao serem
  *                     alteradas por qualquer funcao.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -frodo_house: contem as informacoes da casa do Frodo.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return frodo_house, estrutura contendo as informacoes da casa do frodo
  */
fortress get_frodohouse();

/** Funcao: Recuperar as informacoes do usuario.
  *
  * Descricao/Hipotese: Encpasula as informacoes do usuario para nao serem
  *                     alteradas por qualquer funcao.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -user: contem as informacoes do usuario.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return user, estrutura contendo as informacoes do usaurio.
  */
player get_user();

/** Funcao: Recupercao das informacoes de eventos do mouse.
  *
  * Descricao/Hipotese: Encapsula a variavel que guarda as informacoes da
  *                     movimentacao do mouse.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -event: Variavel global que guarda as informacoes das
  *                      movimentacoes do mouse.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return event, informacoes da movimentacao do mouse.
  */
MEVENT get_event();

/** Funcao: Recuperacao do status das teclas.
  *
  * Descricao/Hipotese: Encapsula a variavel que guarda o status da entrada
  *                     de dados. Assim, apenas funcoes que precisam mudar o
  *                     status tem acesso 'a variavel.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -status: contem o status atual da entrada de dados do
  *                       jogo.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return status, estado atual da entrada de dados do jogo.
  */
int get_keystatus();

/** Funcao: Atribuir um novo valor para o status das teclas.
  *
  * Descricao/Hipotese: Encapusla a variavel de status das teclas. Assim, apenas
  *                     funcoes que precisam mudar o status tem acesso 'a
  *                     variavel.
  *
  * Interface explicita: @param key_status Indica o novo status das teclas.
  *
  * Interface implicita: -status: contem o status atual do jogo.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void, nao possui retorno.
  */
void set_keystatus(int key_status);

/** Funcao: Recuperar do status do jogo.
  *
  * Descricao/Hipotese: Encapsula a variavel de status do jogo. Assim, apenas
  *                     funcoes que precisam dessa variavel conseguem recuperar
  *                     seu valor.
  *
  * Interface explifica: N/A.
  *
  * Interface Implicita: -status: contem o status atual do jogo.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return status, estado atual do jogo.
  */
int get_gamestatus();

/** Funcao: Atribuir um novo valor ao status do jogo.
  *
  * Descricao/Hipotese: Encapsula a variavel de status do jogo. Deste modo,
  *            apenas as as funcoes que precisam mudar o valor do status do
  *            jogo conseguem ter acesso.
  *
  * Interface explicita: @param key_status Indica o novo valor do status do
  *                                        jogo.
  *
  * Interface implicita: -status: contem o status atual do jogo.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void, nao possui retorno.
  */
void set_gamestatus(int key_status);

/** Funcao: Recuperacao da quantidade de colunas do terminal.
  *
  * Descricao/Hipotese: Encapsula a variavel que contem a quantidade de colunas
  *            do terminal. Assim, apenas as funcoes que precisam saber do valor
  *            da variavel possuem acesso.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -term_co:l contem a quantidade de colunas que o
  *                                      terminal do usuario possui.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return term_col
  */
int get_termcol();

/** Funcao: Atribuir um valor para o limite do mapa.
  *
  * Descricao/Hipotese: Encapsula a variavel que contem o limite do mapa. Assim,
  *                     apenas as funcoes que precisam alterar esse valor possuem
  *                     acesso 'a variavel.
  *
  * Interface explicita: @param lim Indica o novo limite do mapa.
  *
  * Interface implicita: -lim_map: contem o limite do mapa.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void
  */
void set_maplim(int lim);

/** Funcao: Inicializa a matriz de opcoes.
  *
  * Descricao/Hipotese: Le dos arquivos contendo as ASCII art das opcoes do
  *                     menu, e as colocas em suas devidas posicoes na matriz
  *                     de opcoes.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -options: matriz que contem as ascii art das
  *                                     opcoes do menu.
  * Contrato/Requisitos: A matriz de opcoes do menu deve estar alocada, ou seja
  *                      diferente de NULL.
  * @return void
  */
void init_options();

/** Funcao: Interpreta que opcao do menu foi clicada.
  *
  * Descricao/Hipotese: Recebe como parametro as coordanadas de onde o usuario
  *                     clicou no menu e interpreta isso. Retorna a opcao
  *                     clicada.
  *
  * Interface explicita: @param mouse_row Linha que o mouse clicou no terminal.
  *                      @aram mouse_col Coluna que o mouse clicou no terminal.
  *
  * Interface implicita: N/A.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return A opcao selecionada, se o usuario clicou em um campo correspondente
  *         a uma opcao do menu.
  * @return 0, caso contrario.
  */
int report_option(int mouse_row, int mouse_col);

/** Funcao: Recuperar as informacoes de scroll do mapa.
  *
  * Descricao/Hipotese: Encapsula a variavel contendo as informacoes do scroll
  *            do mapa. Assim, apenas as funcoes que precisam saber desse valor
  *            tem acesso.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -map_scrol:l contem as informacoes do scroll do mapa.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return srcll
  */
scrll get_mapscroll();

/** Funcao: Atribuir um novo valor para o scroll do mapa.
  *
  * Descricao/Hipotese: Encapsula a variavel contendo as informacoes do scroll
  *            do mapa.  Assim, apenas as funcoes que precisam mudar esse valor
  *            podem ter acesso 'a variavel.
  *
  * Interface explicita: @param scroll_map Contem as novas informacoes sobre o
  *                                        scroll do mapa.
  *
  * Interface implicita: -map_scroll: contem as informacoes sobre o scroll
  *                                        do mapa.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void.
  */
void set_mapscroll(scrll scroll_map);

/** Funcao: Incializar uma nova unidade.
  *
  * Descricao/Hipotese: Inicializa uma nova unidade de acordo com os atributos
  *                     de cada raca.
  *
  * Interface explicita: @param chr Ponteiro da unidade a ser inicializada.
  *                      @param race Indica a qual raca a nova unidade pertence.
  *
  * Interface implicita: N/A.
  *
  * Contrato/Requisitos: o ponteiro da unidade a ser inicializada deve ser
  *                      diferente de NULL (char != NULL). E a entrada de race
  *                      deve estar entre 1 e 8.
  *
  * @return void
  */
void race_init(unit *chr, int race);

/** Funcao: Ler as ASCII art das racas.
  *
  * Descricao/Hipotese: Le os arquivos .txt contendo as ASCII art de cada raca
  *            e suas sombras, e as colocas em suas respecitivas matrizes.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -mat_races: matriz contendo as ascii art dos
  *                                       personagens.
  *                      -mat_shadows: matriz contendo as sombras dos
  *                                         personagens.
  *
  * Contrato/Requisitos: Os arquivos contendo as ascii art de cada personagem e
  *                      suas sombras devem estar na mesma pasta deste arquivo:
  *                      logic.h
  *
  * @return 1, caso tudo tenha dado certo.
  * @return -1, caso falhe.
  */
int get_art();

/** Funcao: Coloca no mapa os predios produtores de recursos.
  *
  * Descricao/Hipotese: Le todos os arquivos .txt que contem as artes dos
  *                     predios e coloca-os nos lugares devidos na matriz do
  *                     mapa;
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -map: Variavel externa do modulo basis que guarda o
  *                      mapa do jogo.
  *                      -builds: vetor de elementos de struct build_art que
  *                      guarda as informacoes necessarias para saber qual o
  *                      nome do arquivo texto que guarda as artes de um dado
  *                      predio e as coordenadas de onde ele deve ser inserido
  *                      no mapa.
  *
  * Contrato/ Requisitos: Os arquivos texto que guardas as artes devem existir.
  *
  * @return void
  *
  * Requisitos: N/A.
  */
void put_builds();

/** Funcao: Prencher o mapa com espacos.
  *
  * Descricao/Hipotese: Prenche a matriz do mapa com espacos ' ' onde tem '\0'.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -map: matriz contendo mapa do jogo.
  *
  * Contrato/Requisitos: A matriz do mapa devera ter sido devidamente alocada,
  *                      ou seja, ela devera ser diferente de NULL
  *                      (map != NULL).
  *
  * @return void
  */
void map_spaces();

/** Funcao: Imprimir uma unidade no mapa.
  *
  * Descricao/Hipotese: Imprime uma unidade na matriz do mapa em sua devida
  *                     posicao.
  *
  * Interface explicita: @param chr Indica qual unidade sera impressa no mapa.
  *
  * Interface implicita: -l_unit: promove um mecanismo de sincronizacao que
  *                                    visa impedir que a lista encadeada que
  *                                    guarda as unidades seja modificada por
  *                                    mais de uma thread ao mesmo tempo.
  *                      -map: matriz contendo o mapa do jogo.
  *
  * Contrato/Requisitos: O ponteiro da unidade a ser impressa no mapa e o mapa
  *                      deverao ter sido alocados corretamente, ou seja
  *                      diferente de NULL.
  *
  * @return void
  */
void printmap_unit(unit chr);

/** Funcao: Atualizar o armazem das construcoes.
  *
  * Descricao/Hipotese: Atualiza o armazem das construcoes de acordo com a
  *            producao de cada construcao. Se o armazem ja nao estiver em sua
  *            capacidade maxima, ele para de produzir recursos.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -build_top: indica o inicio da lista encadeada
  *                                       contendo as informacoes das
  *                                       construcoes do jogador.
  *
  * Contrato/Requisitos: Para que se possa atualizar o armazem das construcoes,
  *                      deve existir pelomenos uma, logo build_top deve ser
  *                      diferente de NULL.
  *
  * @return void
  */
void good_generator();

/** Funcao: Recuperar a variavel free_races.
  *
  * Descricao/Hipotese: Encapsula o ponteiro do inicio da lista das unidades do
  *                     usuario. Assim, apenas as funcoes que precisam desta
  *                     variavel podem ter acesso 'a lista das unidades.
  *
  * Interace explicita: N/A.
  *
  * Interface implicita: -free_races: ponteiro do inicio da lista de
  *                                        unidades do usuario.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return free_races
  */
unit* get_freeraces();

/** Funcao: Atribuir um novo inicio para a lista de unidades.
	  *
  * Descricao/Hipotese: Encapsula o ponteiro de inicio da lista de uniades do
  *            usuario. Assim, apenas as funcoes que criam ou removem novas
  *            unidades podem mudar o inicio da lista.
  *
  * Interface explicita: @param top Nova unidade a ser incluida na lista de
  *                                 unidades.
  *
  * Interface implicita: -free_races: ponteiro do inicio da lista de
  *                                        unidades do usuario.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void
  */
void set_freeraces(unit *top);

/** Funcao: Recuperar o inicio da lista de construcoes.
  *
  * Descricao/Hipotese: Encapsula o ponteiro de inicio da lista de construcoes
  *            do usauario. Assim, apenas as funcoes que preicam da da lista tem
  *            acesso 'as construcoes.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -build_top: ponteiro do inicio da lista contendo
  *                                       as informacoes das construcoes do
  *                                       usuario.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return build_top, inicio da lista de construcoes do usuario.
  */
build* get_buildtop();

/** Funcao: Atribuir um novo inicio para  lista de construcoes.
  *
  * Descricao/Hipotese: Encapsula o ponteiro de inicio da lista de construcoes
  *                     do usuario. Assim, apenas as funcoes que criam
  *                     construcoes podem mudar o inicio da lista.
  *
  * Interface explicita: @param top Nova construcao a ser adicionada 'a lista de
  *                                 construcoes do usuario.
  *
  * Interface implicita: -build_top: ponteiro do inicio da lista contendo
  *                                       as informacoes das construcoes do
  *                                       usuario.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void
  */
void set_buildtop(build *top);

/** Funcao: Imprimir a quantidade de recursos.
  *
  * Descricao/Hipotese: Imprime a quantidade de recusros armazendas em cada
  *                     construcao.
  *
  * Interface explicita: @param build_top Ponteiro do inicio da lista contendo
  *                                       as informacoes das construcoes do
  *                                       usuario.
  *
  * Interface implicita: -map: matriz contendo o mapa do jogo.
  *
  * Contrato/Requisitos: Tanto as construcoes tanto quanto o mapa devem estar
  *                      alocados na memoria, ou seja diferente de NULL.
  *
  * @return void
  */
void print_good();

/** Funcao: Coletar os recuros.
  *
  * Descricao/Hipotese: Faz com que os hobbits coltem os recursos caso eles
  *                     estejam perto da construcao a qual estao trabalhando.
  *                     Caso eles estejam perto da fortaleza, eles depositam os
  *                     recursos.
  *
  * Interface explicita: @param chr Unidade coletando os recursos.
  *
  * Interface implicita: -build_top: ponteiro do inicio da lista contendo
  *                                       as informacoes das costrucoes do
  *                                       usario.
  *
  * Contrato/Requisitos: Tanto o mapa quanto a unidade coletando os recursos
  *                      devem estar alocados na memoria, ou seja diferente de
  *                      NULL.
  * @return void
  */
void check_good();

/** Funcao: Mover os hobbits para a construcao.
  *
  * Descricao/Hipotese: Move os hobbits para a construcao a qual eles estao
  *                     trabalhando.
  *
  * Interface explicita: -chr: unidade a ser movida para sua construcao.
  *                      -n_build: identificador da construcao a qual a
  *                       unidade esta trablhando.
  *
  * Contrato/Requisitos: Tanto o mapa quanto a unidade devem estar alocados na
  *                      memoria, ou seja diferentes de NULL. A variavel
  *                      n_builds deve estar enre 1 e 6.
  *
  * @return void
  */
void goto_build(unit *chr, int n_build);

/** Funcao: Imprimir as opcoes da fortaleza do usaurio.
  *
  * Descricao/Hipotese: Imprime o menu de opces da fortaleza do usuario, as quais
  *                     sao: Aumentar o nivel da fortaleza e comprar uma unidade
  *                     de uma raca, se a fortaleza estiver com nivel suficiente
  *                     para produzir a raca.
  *
  * Interface explicita: @param int n Indica qual opcao sera impressa.
  *
  * Interface implicita: -map: matriz contendo o mapa atual do jogo.
  *
  * Contrato/Requisito: O mapa deve estar devidamente alocado na memoria e os
  *                     arquivos contendo as ascii art das opcoes devem estar
  *                     na mesma pasta desse arquivo (logic.h).
  *
  * @return void
  */
void load_houseoption(int n);

/** Funcao: Desbloquear a proxima raca aliada ou comprar unidades.
  *
  * Descricao/Hipotese: Permite o usuario desbloquear a proxima raca aliada e
  *                     comecar a produzir unidades de alguma raca liberada
  *
  * Interface explicita: @param col Indica o numero da coluna da opcao de gerar
  *                                 uma tropa foi clicada.
  *
  * Interface implicita: -user: variavel contendo as informacoes do usuario.
  *                      -frodo_house.level: contem o nivel atual da
  *                                               fortaleza do usuario.
  *
  * Contrato/Requisito: N/A.
  *
  * @return void
  */
void fortress_buy(int col);

/** Funcao: Aumentar o nivel da fortaleza.
 *
 * Descricao/Hipotese: Permite o usuario a aumentar o nivel de suas construcoes,
 *                     liberando novas racas aliadas para produzir unidades.
 *                     Caso a construcao ja esteja no nivel maximo, a opcao de
 *                     comprar niveis e' apagada do mapa.
 *
 * Interface explicita: @param level Indica o nivel atual da fortaleza do
 *                      usuario.
 *
 * Interface implicita: -map: matriz contendo o mapa do jogo.
 *
 * Contrato/Requisitos: A matriz contendo o mapa do jogo deve estar devidamente
 *                      alocada na memoria. A variavel level deve estar entre 1
 *                      e 4.
 *
 * @return void
 */
void option_upgrade(int level);

/** Funcao: Mover todas as unidades.
  *
  * Descricao/Hipotese: Move todas as unidades de acordo com sua posicao atual
  *                    (caso ja  estejam em seu destino, as unidades nao se
  *                    movem mais) e do tempo nescessario para se mover (o qual 
  *                    varia de raca para raca).
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -free_races: ponteiro do inicio da lista de
  *                                        unidades d usuario.
  *
  * Contrato/Requisitos: A matriz contendo o mapa do jogo deve estar devidamente
  *                      alocada na memoria.
  *
  * @return void
  */
void all_move();

/** Funcao: Salvar o estado atual do jogo.
  *
  * Descricao/Hipotese: Salva o estado atual do jogo em arquivos binarios, para
  *                     que o usuario possa continuar de onde parou sem nenhuma
  *                     perda.
  *
  * Interface explicita: @param save_game Nome do diretoria a se salvar o jogo.
  *
  * Interface implicita: -free_races: ponteiro do inicio da lista encadeada das
  *                                   unidades do usuario.
  *                      -build_top: ponteiro do inicio da lista encadeada das
  *                                  construcoes do usuario.
  *                      -user: variavel contendo as informcaoes do usuario,
  *                             como quantidade de cada recurso que ele possui.
  *
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void, sem retorno.
  */
void save(char *save_name);

/** Funcao: Carregar um jogo salvo.
  *
  * Descricao/Hipotese: O programa carrega um jogo salvo anteriormente. Assim,
  *                     o usuario podera continuar a sua campanha do momento em
  *                     que salvou.
  *
  * Interface explicita: @param load_dir Nome do diretorio a ser carregado o
  *                                      os dados salvos.
  *
  * Interface implicita: -free_races: ponteiro do inicio da lista encadeada das
  *                                   unidades do usuario.
  *                      -build_top: ponteiro do inicio da lista encadeada das
  *                                  construcoes do usuario.
  *                      -user: varivale contendo as informacoes do usuario,
  *                             como a quantidade de cada recurso que ele
  *                             possui.
  *
  * Contrato/Requisitos: Para que se carregue um jogo, deve existir um diretorio
  *                      contendo um jogo salvo. Caso nao exista, o programa
  *                      exibe uma mensagem de erro dizendo que nao exite
  *                      nenhum jogo salvo. Caso exista, o programa ira
  *                      carregar o jogo e o usuario podera continuar de onde
  *                      parou.
  *
  * @return void, sem retorno.
  */
void load(char *load_dir);

/** Funcao: Mostrar as opcoes de load game.
  *
  * Descricao/Hipotese: Mostra as opcoes de load game, e dependendo da opcao
  *                     que o usuario selecionou, o programa segue de acordo.
  *                     Por exemplo: se o usuario selecionou load, o programa
  *                     ira carregar o ultimo save que foi feito.
  *
  * Interface explicita: @param options Opcao que o usuario selecionou.
  *
  * Interface implicita: -status: variavel que contem o estado atual do jogo.
  *                      -free_races: ponteiro do inicio da lista encadeada das
  *                                   unidades do usuario.
  *
  * Contrato/Requisito: N/A.
  *
  * @return void, sem retorno.
  */
void load_select(int option);


/** Funcao: Modificar o valor de n_workers de um predio de recursos.
  *
  * Descricao/Hipotese: Procura o predio com o id igual ao primeiro parametro
  *                     passado e, se encontar, acrescenta o valor do segundo
  *                     parametro ao valor de n_workers do predio.
  *
  * Interface explicita: @param id: Identificador do predio de recursos.
  *                      @param add: Valor a ser somado ao valor de n_workers.
  *
  * Interface implicita: -build_top: Topo da lista de predios
  *
  * Contrato/Requisito: O valor de id ser o id de um predio existente
  *
  * @return void, sem retorno.
  */
void change_nworkers(int id, int add);

void attack_fortress();
void printall_units();
