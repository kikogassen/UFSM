// Frederico Hansel dos Santos Gassen
// Trabalho 5 de Laboratório de Programação I - 2017/1
// Marble Lines


#include "tela5.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//tamanho da janela
#define LARG 800
#define ALT 600


/***********************/
/* definicao dos dados */
/***********************/

// define uma estrutura com a bolinha
typedef struct {
  circulo circ;     // coordenadas x e y do centro da bolinha
  ponto vel;        // velocidade em x e y
  cor c;
  bool ativa;       // bolinha foi ativada
} bola;

// define uma estrutura com o estado do jogo
typedef struct {
  bola vetor[100];// a bolinha
  int pontos;       // numero de pontos
  ponto mira_canhao;
  int fase;
  ponto posicoes_trilha[3]; // as 3 posições chave para a trilha
  bola tiro; // bolinha que saiu do canhão
  int total_bolinhas; //total de bolinhas que nascerÃ¡ na fase
  cor prox_cor; // proxima cor
  cor prox_prox_cor; // proxima cor depois da proxima
  int teste;
  bool pause; // se o jogo tá pausado, não altera estado
  int idx_ultima_bolinhas_ativada; // indice da ultima bolinha ativada
} estado;

//define uma estrutura para o recorde
typedef struct{
  char nome[4];
  int pontos;
} recorde;


/**********************/
/* programa principal */
/**********************/

// declaracao de funcoes auxiliares
void desenha_tela(estado *t); // função que desenha a tela, recebendo o estado do jogo como argumento
void altera_estado(estado *t); // função que altera as variáveis responsáveis por controlar o jogo
void abertura(void); // função que cria o arquivo dos recordes caso não exista
void encerramento(estado *t); // função responsável por mostrar os recordes e inserir um novo
bool acabou(estado *t); // função que diz se o jogo acabou ou não
void inicializa_estado(estado *t, int fase, int pontos); // função que inicializa as variáveis do jogo, recebendo a fase e os pontos atuais
void testa_se_acabou_fase(estado *t); // função que testa se a fase acabou
void pausa_tela(int segs); // função que pausa a tela por determinados segundos
void desenha_recordes(recorde vetor[10]); // função que desenha os recordes na tela
void desenha_anotacao(); // função que desenha as anotações auxiliares dos recordes na tela

// funcao principal
int main()
{
  estado mundo;
  srand((unsigned)time(NULL));

  tamanho tam_tela = {LARG, ALT};
  tela_inicio(tam_tela);

  inicializa_estado(&mundo, 1, 0);
  abertura();

  while (!acabou(&mundo)) {
    altera_estado(&mundo);
    desenha_tela(&mundo);
    testa_se_acabou_fase(&mundo);
  }

  encerramento(&mundo);
  tela_fim();

  return 0;
}


/********************************/
/* Manutencao do estado do jogo */
/********************************/


// declaracao de funcoes auxiliares
void movimenta_vetor(estado *t); // função que movimenta o vetor pra frente
void verifica_rato(estado *t); // função que testa se o mouse está apertado
bool verifica_se_houve_colisao(bola b1, bola b2); // função que verifica se houve colisão entre duas bolinhas
void testa_se_vetor_chegou_ponto_chave(estado *t); // função que testa se o vetor chegou em um dos pontos chave da trilha que realizam funções específicas
void torna_ativa_posicao_anterior(estado *t); // função que ativa a posição anterior do vetor caso caiba mais uma bolinha no vetor
cor retorna_cor_random(); // função que retorna uma cor aleatória das 4 disponíveis
void move_tiro(estado *t); // função que move o tiro
int indice_ultima_bola_vetor(estado *t); // função que diz qual o índice da última bolinha ativa do vetor
void gera_prox_cor_canhao(estado *t);// função que gera a proxima cor do canhao
int testa_se_destroi(estado *t, int bola_nova, int bolas_antes, int bolas_depois, int pontos_por_bola); // função que testa se vai destruir um
//conjunto de bolinhas, recebendo a bola nova, quantas bolas formavam sequencias antes, quantas formavam sequencia depois e quantos pontos serão creditados caso exploda
int aloca_bolinha_vetor(estado *t, int indice); // função que aloca uma bolinha ao vetor, retornando onde foi alocada
int quantas_bolas_formam_sequencia(estado *t); // função que retorna quantas bolinhas formam sequencias de 3 ou mais no vetor
int quantas_bolas_ativas(estado *t); // função que retorna quantas bolas ativas tem no vetor

/* funcao principal de alteracao do estado do jogo */

// altera a posicao do que se mexe na tela, reage a acao do mouse
void altera_estado(estado *t)
{
  if (tela_le_tecla()=='h'){
    if (t->pause==true){
      t->pause=false;
    } else {
      t->pause=true;
    }
  }


  if (!t->pause){
    verifica_rato(t);
    torna_ativa_posicao_anterior(t);
    movimenta_vetor(t);
    testa_se_vetor_chegou_ponto_chave(t);
    move_tiro(t);
  }
}

void testa_se_acabou_fase(estado *t){
  if (quantas_bolas_ativas(t)==0 && t->total_bolinhas==0){
    int pontos_pela_distancia = (t->posicoes_trilha[2].x - t->vetor[0].circ.centro.x)/16 * 7;
    t->pontos += pontos_pela_distancia;
    t->fase++;
    inicializa_estado(t, t->fase, t->pontos);
  }
}

int aloca_bolinha_vetor(estado *t, int indice){

  //calcula a variação do X da bolinha do vetor e do tiro
  double delta_xv = sqrt((t->vetor[indice].circ.centro.x-LARG/2)*(t->vetor[indice].circ.centro.x-LARG/2));
  double delta_xt = sqrt((t->tiro.circ.centro.x-LARG/2)*(t->tiro.circ.centro.x-LARG/2));

  //calcula a hipotenusa dos triângulos retangulos formados pelo centro e pelas bolinhas
  double delta_yv = sqrt((t->vetor[indice].circ.centro.y-LARG/2)*(t->vetor[indice].circ.centro.y-LARG/2));
  double delta_yt = sqrt((t->tiro.circ.centro.y-LARG/2)*(t->tiro.circ.centro.y-LARG/2));
  double hip_v = sqrt(delta_xv * delta_xv + delta_yv * delta_yv);
  double hip_t = sqrt(delta_xt * delta_xt + delta_yt * delta_yt);

  //compara os senos dos angulos. O seno que der maior representa o maior angulo, já que o angulo está no primeiro quadrante
  double sen_v = delta_xv / hip_v;
  double sen_t = delta_xt / hip_t;

  //adiciona-se uma nova bolinha pra posteriormente acelerar a fila pra parecer que andou
  if (t->total_bolinhas>0){ // se ainda tem bolinhas por vir
    t->total_bolinhas++; // acrescenta uma bolinha no final da trilha
  } else { // se não tem bolinhas por vir, tem que criar uma nova bolinha e inseri-la no final da trilha
    int ultima_bola = indice_ultima_bola_vetor(t);
    t->vetor[ultima_bola+1].ativa=true;
    t->vetor[ultima_bola+1].circ.centro.x = t->vetor[ultima_bola].circ.centro.x - 16;
    if (t->vetor[ultima_bola+1].circ.centro.x<t->posicoes_trilha[1].x && t->vetor[ultima_bola].circ.centro.x>t->posicoes_trilha[1].x){ // se a nova bolinha deve nascer na divisa da posicao 1
      t->vetor[ultima_bola+1].circ.centro.y =  t->posicoes_trilha[0].y - ((t->vetor[ultima_bola+1].circ.centro.x - t->posicoes_trilha[0].x) * 3 / 4);
    } else if (t->vetor[ultima_bola].circ.centro.x<t->posicoes_trilha[1].x){
      t->vetor[ultima_bola+1].circ.centro.y = t->vetor[ultima_bola].circ.centro.y + 12;
    } else {
      t->vetor[ultima_bola+1].circ.centro.y = t->vetor[ultima_bola].circ.centro.y - 12;
    }
  }

  // acha a última bolinha ativa e vai trazendo as cores pra trás
  int ultima_bola = indice_ultima_bola_vetor(t);
  int var;
  for (var=ultima_bola;var>indice;var--){
    t->vetor[var+1].c=t->vetor[var].c;
  }


  int retorno;
  if (sen_v>sen_t){ // aloca na direita
    t->vetor[indice+1].c=t->vetor[indice].c;
    t->vetor[indice].c=t->tiro.c;
    retorno = indice;
  } else {// aloca na esquerda
    t->vetor[indice+1].c=t->tiro.c;
    retorno = indice+1;
  }

  //movimenta o vetor uma bolinha pra frente, ou seja, 400 vezes:
  for (var=0;var<16/(0.04 * t->fase);var++){
    movimenta_vetor(t);
    testa_se_vetor_chegou_ponto_chave(t);
    torna_ativa_posicao_anterior(t);
  }

  return retorno;
}

int indice_ultima_bola_vetor(estado *t){
  int indice;
  for (indice=0;t->vetor[indice].ativa==true;indice++);
  t->teste=indice-1;
  return indice-1;
}

void move_tiro(estado *t){
  if (!t->tiro.ativa) return;

  t->tiro.circ.centro.x += t->tiro.vel.x;
  t->tiro.circ.centro.y += t->tiro.vel.y;

  if (t->tiro.circ.centro.x<0 || t->tiro.circ.centro.x>LARG || t->tiro.circ.centro.y<0 || t->tiro.circ.centro.y>ALT){ // tiro saiu do mapa
    if (t->pontos<7){
      t->pontos=0;
    } else {
      t->pontos -= 7;
    }
    t->tiro.ativa=false;
    t->tiro.circ.centro.x = LARG/2;
    t->tiro.circ.centro.y = ALT/2;
  }

  // testa se bateu em alguma bolinha
  int indice;
  for (indice=0;indice<(sizeof(t->vetor)/sizeof(t->vetor[0]));indice++){
    if (verifica_se_houve_colisao(t->tiro, t->vetor[indice]) && (t->vetor[indice].ativa)){
      int bolas_antes = quantas_bolas_formam_sequencia(t);
      int bola_nova = aloca_bolinha_vetor(t, indice);
      int bolas_depois = quantas_bolas_formam_sequencia(t);
      int retorno=bola_nova;
      int pontos_por_bola=10;
      while (retorno!=-1){
        bola_nova=retorno;
        retorno = testa_se_destroi(t, bola_nova, bolas_antes, bolas_depois, pontos_por_bola);
        pontos_por_bola += 5;
      }
      t->tiro.ativa=false;
      t->tiro.circ.centro.x = LARG/2;
      t->tiro.circ.centro.y = ALT/2;
      break;
    }
  }

}

int testa_se_destroi(estado *t, int bola_nova, int bolas_antes, int bolas_depois, int pontos_por_bola){
  //descobre quantas bolas formavam as sequencias antes. Se aumentou, é pq formou uma nova
  if (bolas_antes<bolas_depois){//criou uma nova sequencia, ou seja, explode

    //acha o inicio da sequencia que vai explodir
    int idx_inicio=bola_nova;
    while (t->vetor[idx_inicio].c==t->vetor[bola_nova].c && idx_inicio>0){
      idx_inicio--;
    }
    if (t->vetor[idx_inicio].c!=t->vetor[bola_nova].c){
      idx_inicio++;
    }

    //acha o final da sequencia que vai explodir
    int idx_final=bola_nova;
    while (t->vetor[idx_final].c==t->vetor[bola_nova].c && t->vetor[idx_final+1].ativa){
      idx_final++;
    }
    if (t->vetor[idx_final].c!=t->vetor[bola_nova].c){
      idx_final--;
    }

    //calcula o total de bolinhas explodidas
    int total_bolinhas_explodidas = idx_final-idx_inicio+1;

    //soma pontuacao
    t->pontos += pontos_por_bola * total_bolinhas_explodidas;

    //move as cores do inicio da fila pra esquerda
    int idx=idx_final;
    while (idx-total_bolinhas_explodidas>=0){
      t->vetor[idx].c = t->vetor[idx-total_bolinhas_explodidas].c;
      idx--;
    }

    //desativa as ultimas bolinhas referente as bolinhas destruidas
    for (idx=0;idx<total_bolinhas_explodidas;idx++){
      t->vetor[idx].ativa=false;
    }

    //diminui o indice de todas as bolinhas da trilha
    for (idx=total_bolinhas_explodidas;idx<(sizeof(t->vetor)/sizeof(t->vetor[0]));idx++){
      t->vetor[idx-total_bolinhas_explodidas]=t->vetor[idx];
    }

    //diminui o indice da ultima bolinha ativada para controle
    t->idx_ultima_bolinhas_ativada -= total_bolinhas_explodidas;

    int bolas_depois_depois = quantas_bolas_formam_sequencia(t);
    if (bolas_depois_depois>bolas_depois-total_bolinhas_explodidas){ // explodir de novo
      return idx_inicio-1;
    }

  }

  return -1;

}

int quantas_bolas_formam_sequencia(estado *t){
  int indice, total_bolas=0, tmp_cont=1;
  cor tmp_cor = t->vetor[0].c;
  for (indice=1;t->vetor[indice].ativa;indice++){
    if (tmp_cor==t->vetor[indice].c){
      tmp_cont++;
    } else {
      if (tmp_cont>=3){
        total_bolas += tmp_cont;
      }
      tmp_cont=1;
      tmp_cor=t->vetor[indice].c;
    }
  }
  if (tmp_cont>=3){
    total_bolas += tmp_cont;
  }
  return total_bolas;
}

void torna_ativa_posicao_anterior(estado *t){
  if (t->vetor[t->idx_ultima_bolinhas_ativada].circ.centro.x-16>t->posicoes_trilha[0].x && t->total_bolinhas>0){
    t->vetor[t->idx_ultima_bolinhas_ativada+1].ativa = true;
    t->total_bolinhas -= 1;
    t->idx_ultima_bolinhas_ativada += 1;
  }
}

void movimenta_vetor(estado *t){
  int indice;
  for (indice=0;t->vetor[indice].ativa;indice++){
    t->vetor[indice].circ.centro.x+=t->vetor[indice].vel.x;
    t->vetor[indice].circ.centro.y+=t->vetor[indice].vel.y;
  }
  if (indice==0 && t->total_bolinhas>0){
    t->vetor[t->idx_ultima_bolinhas_ativada+1].ativa = true;
    t->total_bolinhas -= 1;
    t->idx_ultima_bolinhas_ativada += 1;
  }
}

void testa_se_vetor_chegou_ponto_chave(estado *t){
  int indice;
  for (indice=0;indice<(sizeof(t->vetor)/sizeof(t->vetor[0]));indice++){
    if (t->vetor[indice].ativa && t->vetor[indice].vel.y<0 && t->vetor[indice].circ.centro.x>t->posicoes_trilha[1].x){
      t->vetor[indice].vel.y*=-1;
    }
  }
}

//
bool verifica_se_houve_colisao(bola b1, bola b2){
  double distancia = sqrt((b1.circ.centro.x-b2.circ.centro.x)*(b1.circ.centro.x-b2.circ.centro.x)+(b1.circ.centro.y-b2.circ.centro.y)*(b1.circ.centro.y-b2.circ.centro.y));
  double soma_raios = b1.circ.raio + b2.circ.raio;
  if (distancia<=soma_raios){
    return true;
  }
  return false;
}


/****************************/
/* processamento da entrada */
/****************************/

// funcao auxiliar
void lanca_bolinha(estado *t); // função que lança a bolinha no jogo

// o botao do mouse serve para liberar a bolinha.
// quanto mais tempo ele fica apertado, mais rapido ela vai
void verifica_rato(estado *t)
{
  // se o mouse ta apertado, aumenta a forca
  if (tela_rato_apertado()) {
    lanca_bolinha(t);
  }
}

// lanca a bolinha em direcao ao alvo, com velocidade proporcional a forca
void lanca_bolinha(estado *t)
{
  // se a bolinha ja ta ativa, ignora
  if (t->tiro.ativa) return;

  // calcula a direcao da bolinha -- direto para o alvo
  ponto dir;
  ponto rato = tela_pos_rato();
  dir.x = rato.x - t->tiro.circ.centro.x;
  dir.y = rato.y - t->tiro.circ.centro.y;
  // transforma em um vetor unitario -- divide pela distancia
  float modulo;
  modulo = sqrt(dir.x * dir.x + dir.y * dir.y);
  dir.x /= modulo;
  dir.y /= modulo;
  // a velocidade da bolinha sera proporcional a forca, na dir calculada
  t->tiro.vel.x = dir.x * 10;
  t->tiro.vel.y = dir.y * 10;
  // libera a bolinha, em cor de batalha
  t->tiro.c = t->prox_cor;
  t->tiro.ativa = true;

  //gera as proximas cores
  gera_prox_cor_canhao(t);
}

void gera_prox_cor_canhao(estado *t){
  t->prox_cor = t->prox_prox_cor;
  bool controle_geracao_cor=false;
  do {
    t->prox_prox_cor = retorna_cor_random();
    int indice;
    for (indice=0;indice<(sizeof(t->vetor)/sizeof(t->vetor[0]));indice++){
      if (t->vetor[indice].ativa == true && t->vetor[indice].c==t->prox_prox_cor){
        controle_geracao_cor=true;
        break;
      }
    }
  } while (controle_geracao_cor==false);
}

cor retorna_cor_random(){
  cor color;
  switch (rand()%4){
    case 0:
      color = azul;
      break;
    case 1:
      color = vermelho;
      break;
    case 2:
      color = verde;
      break;
    case 3:
      color = amarelo;
      break;
    default:
      break;
  }
  return color;
}



/*******************/
/* Desenho da tela */
/*******************/

// declaracao de funcoes auxiliares
void desenha_canhao(estado *t); // função que desenha o canhão
void desenha_posicao_mouse(); // função que desenha a posição do mouse
void desenha_linha_tampa_inicio(estado *t); // função que desenha a linha que tampa o ínicio da trilha
void desenha_vetor(estado *t); // função que desenha o vetor de bolinhas
void desenha_fim_trilha(estado *t); // função que desenha a bola preta do fim da trilha
void desenha_tiro(estado *t); // função que desenha o tiro
void desenha_prox_tiros(estado *t, ponto linha_final_canhao, ponto centro); // função que desenha os proximos tiros
void desenha_help(estado *t); // função que desenha o help
void desenha_titulo_help(); // função que desenha o título do help
void desenha_fase(estado *t); // função que mostra em qual fase está
void desenha_pontos(estado *t); // função que mostra quantos pontos o jogador tem

/* funcao principal do desenho da tela */

// Desenho de uma tela
// limpa a tela, desenha todos os elementos visuais de acordo com o estado,
// faz a tela ser mostrada
void desenha_tela(estado *t)
{
  tela_limpa();


  if (!t->pause){
    desenha_titulo_help();
    desenha_pontos(t);
    desenha_fase(t);
    desenha_fim_trilha(t);
    desenha_vetor(t);
    desenha_linha_tampa_inicio(t);
    desenha_tiro(t);
    desenha_canhao(t);
    desenha_posicao_mouse();
  } else {
    desenha_help(t);
  }



  tela_atualiza();
}

/* funcoes auxiliares para o desenho da tela */

void desenha_pontos(estado *t){
  ponto p1 = { LARG/2, 10 };
  char s[10];
  sprintf(s, "%d pts", t->pontos);
  tela_texto(p1, 15, verde, s);
}

void desenha_fase(estado *t){
  ponto p1 = { LARG-30, 10 };
  char s[10];
  sprintf(s, "Fase %d", t->fase);
  tela_texto(p1, 15, verde, s);
}

void desenha_titulo_help(){
  ponto p1 = { 80, 10 };
  tela_texto(p1, 15, verde, "Aperte h para ajuda");
}

void desenha_help(estado *t){
  ponto p1 = { 10, 10 };
  ponto p2 = { 10, 30 };
  ponto p3 = { 10, 50 };
  ponto p4 = { 10, 70 };
  char s[200];
  sprintf(s, "Seu objetivo eh atirar bolinhas na trilha, formando 3 bolas consecutivas da mesma cor. Caso isso ocorra, voce as destroi.");
  tela_texto_dir(p1, 10, verde, s);
  sprintf(s, "Cada fase gera (10 x fase) bolinhas. Caso a trilha chegue no final, voce perde.");
  tela_texto_dir(p2, 10, verde, s);
  sprintf(s, "Pontuacao: -7 por tiro errado, +10 por bolinha destruida (aumentando para combos de destruicao) e ");
  tela_texto_dir(p3, 10, verde, s);
  sprintf(s, "+7 por espaco sobrando ate o final da trilha quando finaliza a fase");
  tela_texto_dir(p4, 10, verde, s);
}

void desenha_tiro(estado *t){
  if (t->tiro.ativa){
    tela_circulo(t->tiro.circ, 1, t->tiro.c, t->tiro.c);
  }
}


void desenha_fim_trilha(estado *t){
  circulo fim_trilha = {t->posicoes_trilha[2], 13};
  tela_circulo(fim_trilha, 1, vermelho, preto);
}

void desenha_vetor(estado *t){
  int indice;
  for (indice=0;indice<(sizeof(t->vetor)/sizeof(t->vetor[0]));indice++){
    if (t->vetor[indice].ativa){
      tela_circulo(t->vetor[indice].circ, 1, t->vetor[indice].c, t->vetor[indice].c);
    }
  }
}

void desenha_linha_tampa_inicio(estado *t){
  ponto norte = {t->posicoes_trilha[0].x-12, t->posicoes_trilha[0].y-16};
  ponto sul = {t->posicoes_trilha[0].x+12, t->posicoes_trilha[0].y+16};
  tela_linha(norte, sul, 20, preto);
}

void desenha_posicao_mouse(){
  ponto mouse = tela_pos_rato();
  circulo centro_mouse = {mouse, 1};
  tela_circulo(centro_mouse, 1, azul, azul);
}

void desenha_canhao(estado *t){
  ponto mouse = tela_pos_rato();
  double hipot = sqrt(((mouse.x-400)*(mouse.x-400))+((mouse.y-400)*(mouse.y-400)));
  t->mira_canhao.x = 30*(mouse.x-400) / hipot;
  t->mira_canhao.y = 30*(mouse.y-400) / hipot;
  ponto centro = {LARG/2, ALT/2};
  circulo canhao = {centro, 20};
  ponto linha_final_canhao = {t->mira_canhao.x+centro.x, t->mira_canhao.y+centro.y};


  tela_linha(centro, linha_final_canhao, 20, laranja);
  tela_circulo(canhao, 1, laranja, laranja);


  desenha_prox_tiros(t, linha_final_canhao, centro);
}

void desenha_prox_tiros(estado *t, ponto linha_final_canhao, ponto centro){
  circulo prox_bolinha = {linha_final_canhao, 10};
  tela_circulo(prox_bolinha, 1, t->prox_cor, t->prox_cor);

  circulo prox_prox_bolinhas = {centro, 10};
  tela_circulo(prox_prox_bolinhas, 1, t->prox_prox_cor, t->prox_prox_cor);
}




/* funcoes complementares */

void inicializa_estado(estado *t, int fase, int pontos)
{
  ponto ponto1 = {LARG/2-240, 230};
  ponto ponto2 = {LARG/2, 50};
  ponto ponto3 = {LARG/2+240, 230};
  t->posicoes_trilha[0]=ponto1;
  t->posicoes_trilha[1]=ponto2;
  t->posicoes_trilha[2]=ponto3;

  t->pontos = pontos;
  t->fase = fase;
  t->total_bolinhas = 10 * t->fase;

  // inicializa a bolinha
  int indice;
  for (indice=0;indice<(sizeof(t->vetor)/sizeof(t->vetor[0]));indice++){
    t->vetor[indice].circ.centro.x = t->posicoes_trilha[0].x;
    t->vetor[indice].circ.centro.y = t->posicoes_trilha[0].y;
    t->vetor[indice].circ.raio = 10;
    t->vetor[indice].vel.x = 0.04 * t->fase;
    t->vetor[indice].vel.y = -0.03 * t->fase;
    t->vetor[indice].c = retorna_cor_random();
    t->vetor[indice].ativa = false;
  }
  t->vetor[0].ativa = true;
  t->total_bolinhas--;
  t->idx_ultima_bolinhas_ativada=0;

  t->prox_cor = t->vetor[0].c;
  t->prox_prox_cor = t->vetor[0].c;
  t->pause=false;

  t->tiro.circ.centro.x = LARG/2;
  t->tiro.circ.centro.y = ALT/2;
  t->tiro.ativa=false;
  t->tiro.vel.x = 3;
  t->tiro.vel.y = 3;
  t->tiro.circ.raio = 10;

}


// animacao fantastica que aparece quando o jogo comeca
void abertura(void)
{
  //cria o arquivo dos recordes
  FILE *pont_arq;
  pont_arq = fopen("recordes.txt", "r");
  if (pont_arq == NULL){
    pont_arq = fopen("recordes.txt", "w");
    int idx;
    for (idx=0;idx<10;idx++){
      fprintf(pont_arq, "AAA 0\n");
    }
    fclose(pont_arq);
  }

}

// animacao de despedida
void encerramento(estado *t)
{
  //cria o vetor de recordes
  recorde vetor[10];

  //le os recordes do arquivo
  FILE *pont_arq;
  char texto[20];
  int idx;
  pont_arq = fopen("recordes.txt", "r");
  //testa se existe o arquivo
  if(pont_arq == NULL){
     return;
  }
  for (idx=0;idx<10;idx++){
    fgets(texto, 20, pont_arq);
    strncpy(vetor[idx].nome, texto, 3);
    vetor[idx].nome[3] = '\0';
    //ajeita o texto pra ter só o numero
    strcpy(texto, &texto[4]);
    vetor[idx].pontos = atoi(texto);
  }
  fclose(pont_arq);
  tela_limpa();
  desenha_recordes(vetor);
  desenha_anotacao();
  tela_atualiza();

  printf ("pts:%d - vetor:%d", t->pontos, vetor[9].pontos);
  //se a pontuacao foi maior que a 10ª pontuacao, bateu recorde
  if (t->pontos>vetor[9].pontos){
    char nome[4] = {'\0'};
    while (strlen(nome)<3){
      char tecla = tela_le_tecla();
      if (tecla!='\0' && ((tecla>=97 && tecla<=122)||(tecla>=65 && tecla<=90))){
        tela_limpa();
        desenha_anotacao();
        desenha_recordes(vetor);
        nome[strlen(nome)+1] = '\0';
        nome[strlen(nome)] = tecla;
        ponto p3 = {LARG/2, 175};
        tela_texto(p3, 20, verde, nome);
        tela_atualiza();
      }
    }
    //achar em qual posicao do vetor encaixar
    int idx;
    for (idx=0;idx<10;idx++){
      if (t->pontos>vetor[idx].pontos){
        break;
      }
    }
    int idx2;
    for (idx2=9;idx2<idx;idx2--){
      vetor[idx2]=vetor[idx2-1];
    }
    strcpy(vetor[idx].nome, nome);
    vetor[idx].pontos=t->pontos;

    //regravar o arquivo
    pont_arq = fopen("recordes.txt", "w");

    for (idx=0;idx<10;idx++){
      char s[30];
      sprintf(s, "%s %d\n", vetor[idx].nome, vetor[idx].pontos);
      fprintf(pont_arq, s);
    }
    fclose(pont_arq);
  } else {
    while (!tela_rato_apertado()){
      tela_limpa();
      desenha_recordes(vetor);
      char s1[40]="Voce não bateu um recorde!";
      char s2[30]="Clique para sair";
      ponto p1 = {LARG/2, 50};
      ponto p2 = {LARG/2, 100};
      tela_texto(p1, 20, verde, s1);
      tela_texto(p2, 20, verde, s2);
      tela_atualiza();
    }
  }
}

void desenha_recordes(recorde vetor[10]){
  int idx;
  //mostra os recordes
  for (idx=0;idx<10;idx++){
    char mostra[20];
    sprintf(mostra, "%d - %s %d", idx+1, vetor[idx].nome, vetor[idx].pontos);
    ponto p = {20, 20*idx};
    tela_texto_dir(p, 20, verde, mostra);
  }

}

void desenha_anotacao(){
  char s1[40]="Parabens, voce bateu um novo recorde!";
  char s2[30]="Insira seu nome:";
  ponto p1 = {LARG/2, 50};
  ponto p2 = {LARG/2, 100};
  tela_texto(p1, 20, verde, s1);
  tela_texto(p2, 20, verde, s2);
  tamanho t = {100, 50};
  ponto origem = {350, 150};
  retangulo r = {origem, t};
  tela_retangulo(r, 1, verde, preto);
}

void pausa_tela(int segs){
  double tempo = tela_agora();
  while (tela_agora()-segs<tempo){

  }
}

// o jogo terminou?
bool acabou(estado *t)
{
  return t->vetor[0].circ.centro.x>t->posicoes_trilha[2].x;
}

//retorna quantas bolas ativas tem
int quantas_bolas_ativas(estado *t){
  int contador=0, idx;
  for (idx=0;idx<(sizeof(t->vetor)/sizeof(t->vetor[0]));idx++){
    if (t->vetor[idx].ativa){
      contador++;
    }
  }
  return contador;
}


/* acabou, é só isso */

