/*
 * Jogo.hpp
 * TAD que implementa o jogo de cartas "solitaire".
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014, 2015, 2017 João V. Lima, UFSM
 *               2005             Benhur Stein, UFSM
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <stack>
#include <vector>
#include "Carta.hpp"
#include "Tela.hpp"

/* estados para o jogo */
enum Estado { nada, fim };

struct Jogo {
    std::stack<Carta> monte;                 // monte de cartas de onde se pode comprar
    std::stack<Carta> descartes;             // cartas ja abertas do monte; a de cima pode ser usada
    std::vector<std::stack<Carta>> ases;     // as 4 pilhas de cartas da saída (criar vetor)
    std::vector<std::vector<Carta>> pilhas;  // as 7 pilhas principais do jogo
    tela::Tela tela;                        // a tela onde são desenhadas as cartas
    Estado estado;                          // estado global do jogo
    int tecla;                              // última tecla apertada pelo usuario
    int cursor;                    // cursor para realizacao das jogadas 0 = descarte, 1-7 = pilhas
    int cursor_origem;              // local origem para movimentacao de cartas

    // acrescente mais variáveis se necessário

    ///////////////////////////////////////////////////////
    // Métodos do jogo
    ///////////////////////////////////////////////////////

    // inicia jogo e tela
    void inicia(void);

    // finaliza o jogo
    void finaliza(void);

    // desenha a mesa do jogo
    void desenha(void);

    //  atualiza estado do jogo
    void atualiza(void);

    // imprime legenda no terminal
    void legenda(void);

    // verifica se jogo terminou
    bool verifica_fim(void);

    //desenha o fundo do jogo
    void desenha_fundo(void);

    //desenha as cartas do jogo
    void desenha_cartas(void);

    //embaralha e distribui as cartas iniciais
    void inicia_cartas(void);

    //funcao que desenha uma carta, recebendo a mesma como parametro e o ponto superior esquerdo da mesma
    void desenha_uma_carta(Carta c, Ponto p);

    //funcao que retorna o ponto onde a carta deve ser desenhada
    //ex: pilha 1, carta 1: retorna coordenadas da segunda carta da segunda pilha
    Ponto ponto_pilha(int pilha, int carta);

    //funcao que desenha os dois cursores manipulados pelo W
    void desenha_cursor(void);

    //funcao que desenha uma flecha em um ponto
    void desenha_uma_flecha(Ponto p);

    //funcao que retorna a ultima carta de uma pilha onde esta o cursor, retornando-a com o valor 0 caso nao ha cartas
    Carta ultima_carta_cursor(void);

    //funcao que bota a carta do cursor na respectiva pilha de ases
    void bota_carta_cursor_as(int pilha_as);

    //funcao quando aperta D
    void funcao_descarte(void);

    //funcao quando aperta A
    void funcao_ases(void);

    //funcao quando aperta RIGHT
    void funcao_right(void);

    //funcao quando aperta LEFT
    void funcao_left(void);

    //funcao quando aperta W
    void funcao_movimentacao(void);
};
