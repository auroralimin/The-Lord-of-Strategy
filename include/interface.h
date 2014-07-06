/** @file interface.h
  *
  * @brief Header contendo as funcoes usadas para a interface do programa.
  */


/** Funcao: Inicializar a interface.
  *
  * Descricao/Hipotese: Chama as funcoes nescessarias para inicializar a
  *                     interface na ordem correta.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -lim_map: variavel contendo o limite do mapa.
  *                      -map_scrool: variavel contendo as informacoes do scroll
  *                                   do mapa.
  *
  * Contrato/Requisitos: O terminal deve suportar eventos de mouse, como saber
  *                      onde o mouse clicou, onde ele estao, etc.
  *
  * @return void, sem retorno.
  *
  */
void init_interface();

/** Funcao: Recuperar o numero de linha do terminal.
  *
  * Descricao/Hipotese: Encapsula a variavel size para que apenas funcoes que
  *                     precisem saber desse valor podem ter acesso 'a variavel.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -size: variavel contendo as dimensoes de terminal.
  *
  * Contrato/Requisito: N/A.
  *
  * @return size[0], numero de linhas do terminal.
  */
int get_sizerow();

/** Funcao: Recuperar o numero de colunas do terminal.
  *
  * Descricao/Hipotese: Encapsula a variavel size para que apenas funcoes que
  *                     precisem saber desse valor podem ter acesso 'a variavel.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -size: variavel contendo as dimensoes do terminal.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return size[1], numero de colunas do terminal.
  */
int get_sizecol();

/** Funcao: Recuperar a janela do mapa.
  *
  * Descricao/Hipotese: Encapsula a variavel map_win para que apenas funcoes que
  *                     precisam da jenale do mapa, podem ter acesso 'a variavel.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -map_win: varivavel da n_curses, ponteiro para a janela
  *                                do mapa.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return map_win, contem o ponteiro para a janela do mapa.
  */
WINDOW* get_mapwin();

/** Funcao: Mostra o menu de opcoes para o usuario.
  *
  * Descricao/Hipotese: Mostra o menu de opcoes iniciais para o usuario, e segue
  *                     de acordo com a selecao do usuario, por exemplo: se o
  *                     usuario selecionou new game, ele comecara um jogo novo,
  *                     se o usuario selecionou load game, ele carregara um jogo
  *                     salvo, se existir, e se o usuario selecionou exit game,
  *                     o programa saira.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -menu_win: variavel da n_curses. Ponteiro para a janela
  *                                 de opcoes.
  *                      -key_status: estado atual das chaves.
  *                      -l_key: promove um mecanismo de sincronizacao que visa
  *                              impedir que o status do teclado seja ascessado
  *                              ou modificado por mais de uma thread ao mesmo
  *                              tempo.
  *
  * Contrato/Requisitos: A matriz contendo as ascii art das opcoes devera ter
  *                      sido alocada corretamente. Caso nao tenha sido, o
  *                      programa avisara que nao possui memoria suficiente para
  *                      alocar a matriz.
  *
  * @return void, sem retorno.
  */
void menu();

/** Funcao: Criar a janela do mapa.
  *
  * Descricao/Hipotese: Aloca um ponteiro com o tamanho da janela que contera
  *                     o mapa.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -map_win: variavel da n_curses. Ponteiro para janela do
  *                                mapa.
  *                      -map_panel: associada 'a janela do mapa (map_win),
  *                                  permite que a janela do mapa possa
  *                                  sobrepor outras janelas, esconder a
  *                                  janela, mover o mapa de lugar, etc.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return -1, caso nao foi possivel cirar a janela do mapa ou a variavel
  *             msg_panel.
  * @return  1, caso a janela do mapa e a variavel map_mapel foram criadas com
  *             sucesso.
  */
int createmap_win();

/** Funcao: Criar janelas de mensagem.
  *
  * Descricao/Hipotese: Cria janelas de mensagem para melhorar a comunicacao
  *                     da interface com o usuario.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -msg_win: variavel da n_curses. Ponteiro para a janela
  *                                de mensagens.
  *                      -msg_panel: associada 'a janela de mensagem (msg_win),
  *                                  permite que a janela de mensagens possa
  *                                  sobrepor outras janelas, que possa esconder
  *                                  a janela de mensganes, mover a janela de
  *                                  mensagens.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return -1, caso nao seja possivel cirar a janela de mensagens ou a variavel
  *             msg_panel.
  * @return  1, caso a janela de mensagens e a variavel msg_panel foram ciradas
  *             com sucesso.
  */
int createmsg_win();

/** Funcao: Atualizacao da interface.
  *
  * Descicao/Hipotese: Atualiza a interface e confere em que estado o jogo se
  *                    encontra: estado de saida, de pause de jogo, save, load
  *                    e falha no load. Dependendo do estado do jogo. Assim o
  *                    programa chama outras funcoes para continuar de acordo.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -l_printmap: promove um mecanismo de sincronizacao que
  *                                   visa impedir que a interface seja
  *                                   atualizada por mais de uma thread ao mesmo
  *                                   tempo.
  *	                 -msg_win: variavel da ncurses. Ponteiro para a janela
  *                                de mensagens.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void, sem retorno.
  */
void refresh_allgame();

/** Funcao: Verificar em qual opcao de compra na fortaleza foi clicada.
  *
  * Descricao/Hipotese: Verifica se o usuario clicou em alguma opcao de upgrade
  *                     da fortaleza ou de compra de unidades.
  *
  * Interface explicitas: N/A.
  *
  * Interface implicita: N/A.
  *
  * Contrato/Requisitos: N/A.
  *
  * @return void, sem retorno.
  */
int click_frodooption();

/** Funcao: Mudar o recurso sendo coletado por uma unidade trabalhadora.
  *
  * Descricao/Hipotese: Permite o usuario a mudar o recurso que a unidade
  *                     trabalhadora, que foi clicada, esta recolhendo, Por
  *                     exemplo: Um hobbit esta recolhendo madeira, porem o
  *                     usuario deseja que este hobbit passe a recolher outro.
  *                     Basta o usuario clicar no hobbit e selecionar ouro.
  *
  * Interface explicita: @param chr Ponteiro do hobbit que foi clicado.
  *
  * Interface implicita: N/A.
  *
  * Contrato/Requisitos: A variavel chr nao pode ser nula, ou seja chr != NULL.
  *
  * @return void, sem retorno.
  */
void frodo_colect(unit *chr);

/** Funcao: Identificar cliques em cima de hobbit.
  *
  * Desricao/Hipotese: Indentifica se o usuario clicou em cima de um hobbit.
  *
  * Interface explicita: @param row Linha to terminal em que o usuario cliclou.
  *                      @param col Coluna do terminal em que o usuario clicou.
  *
  * Interface implicita: N/A.
  *
  * Contrato/Requisitos: As variaveis row e col devem ambas ser do tipo inteiro.
  *
  * @return void, sem retorno.
  */
void change_hobbit(int row, int col);

/** Funcao: Mostra ou esconde uma janela e mensagens.
  *
  * Descricao/Hipotese: Mostra ou esconde uma janela de mensagens de acordo com
  *                     o nescessario.
  *
  * Interface explicita: @param n Indica que acao a janela de mensagens ira fazer.
  *
  * Interface implicita: -msg_panel: associada 'a janela de mensagens (msg_win),
  *                                  permite que a janela de mensanges possa
  *                                  sobrepor, ser sobreposta, ser movida,
  *                                  escondida e mostrada.
  *                      -map_panel: associada 'a janela do mapa (map_win),
  *                                  permite que a janela do mapa possa ser
  *                                  sobreposta, ser movida, escondida e
  *                                  mostrada.
  *
  * Contrato/Requisito: N/A.
  *
  * @return void, sem retorno.
  */
void move_msg(int n);

/** Funcao: Identificar qual opcao o usuario selecionou na janela de quit.
  *
  * Descricao/Hipotese: Identifica qual opcao o usuario selecionou na janela de
  *                     quit e age de acordo. Caso o usuario tenha clicado em
  *                     'cancel', o programa volta para o jogo. Caso ele tenha
  *                     clicado em 'save and quit', o jogo salva e sai. Caso ele
  *                     tenha clicado em 'quit without saving', o jogo sai sem
  *                     salvar.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -msg_win: ponteiro para a janela de mensagens.
  *
  * @return void, sem retorno.
  */
void quit_answer();

/** Funcao: Identificar qual opcao o usuario selecionou na janela de load.
  *
  * Descricao/Hipotese: Identifica qual opcao o usuario selecionou na janela de
  *                     load e age de acordo. Caso o usuario tenha clicado em
  *                     'yes', o jogo ira carregar o ultimo save. Caso o usuario
  *                     tenha clicado em 'no', o programa cancela a mensagem de
  *                     load e volta ao jogo.
  *
  * Interface explicita: N/A.
  *
  * Interface implicita: -msg_win: ponteiro para a janela de mensagens.
  *
  * @return void, sem retorno.
  */
void load_answer();
void delete_panels();
