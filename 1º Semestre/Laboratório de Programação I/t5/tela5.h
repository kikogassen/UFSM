#ifndef _tela_h_
#define _tela_h_

//
// tela5.h
// -------
// definição de funções de acesso a tela
//
// para uso na disciplina Laboratório de Programação I - 2017a
//


#include <stdbool.h>

// tipo de dados que representa um ponto na tela.
typedef struct {
  float x;
  float y;
} ponto;

// tipo de dados que representa um tamanho retangular
typedef struct {
  float l;
  float h;
} tamanho;

// tipo de dados que representa um retângulo
typedef struct {
  ponto origem;
  tamanho tam;
} retangulo;

// tipo de dados que representa um círculo
typedef struct {
  ponto centro;
  float raio;
} circulo;

// tipo de dados para representar uma cor
typedef int cor;

// algumas cores que são inicializadas automaticamente
cor transparente, azul, vermelho, verde, amarelo,
    preto, laranja, rosa, branco, marrom;

// cria uma nova cor, com suas componentes (entre 0 e 1)
//   vm: componente vermelha
//   vd: componente verde
//   az: componente azul
cor tela_cria_cor(float vm, float vd, float az);

// muda uma cor já anteriormente definida
//   c: a cor a ser mudada
//   vm, vd, az: componentes que a cor passa a ter
void tela_muda_cor(cor c, float vm, float vd, float az);


// inicialização da tela
//   tam: dimensões da janela a ser criada
// deve ser executada antes do uso de qualquer outra função da tela
void tela_inicio(tamanho tam);


// finalização da tela
// deve ser chamada no final da utilização da tela, nenhuma outra função da
// tela deve ser chamada depois desta.
void tela_fim(void);


// atualiza a tela
// faz com o que foi desenhado na tela realmente apareça.
// antes da chamada a esta funcao, nada aparece, o conteúdo
// da tela fica só na memória
void tela_atualiza(void);


// limpeza da tela
// apaga tudo o que tem na tela, faz toda a tela ficar preta
// (como as demais funções que desenham, só altera a representação da tela
//  em memória, até que a tela seja atualizada)
void tela_limpa(void);


// desenha um círculo
//   c: círculo a ser desenhado
//   l: largura da linha
//   corl: cor da linha
//   corint: cor do interior do círculo
void tela_circulo(circulo c, float l, cor corl, cor corint);

// desenha uma reta
//   p1, p2: coordenadas das extremidades da reta
//   l: largura da linha
//   corl: cor da linha
void tela_linha(ponto p1, ponto p2, float l, cor corl);

// desenha um retangulo
//   r: retangulo
//   l: largura da linha
//   corl: cor da linha
//   corint: cor do interior do retangulo
void tela_retangulo(retangulo r, float l, cor corl, cor corint);


// desenha texto centrado
//   p: coordenadas do centro do texto
//   tam: tamanho das letras
//   c: cor dos caracteres
//   t: texto
void tela_texto(ponto p, int tam, cor c, char *t);

// desenha texto à esquerda
//   p: coordenadas do fim do texto
//   tam: tamanho das letras
//   c: cor dos caracteres
//   t: texto
void tela_texto_esq(ponto p, int tam, cor c, char *t);

// desenha texto à direita
//   p: coordenadas do inicio do texto
//   tam: tamanho das letras
//   c: cor dos caracteres
//   t: texto
void tela_texto_dir(ponto p, int tam, cor c, char *t);


// retorna a posição do mouse
ponto tela_pos_rato(void);

// retorna se o botão do mouse está apertado
bool tela_rato_apertado(void);

// retorna uma tecla digitada
// pode retornar um caractere imprimível ou '\b' para backspace ou '\n' para
// enter ou '\0' para qualquer outra coisa ou se não tiver sido digitado nada.
char tela_le_tecla(void);

// retorna a hora atual, medida em segundos desde que o programa comecou
double tela_agora(void);

#endif
