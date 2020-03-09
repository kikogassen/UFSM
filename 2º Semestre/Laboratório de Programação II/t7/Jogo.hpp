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
    std::vector<std::stack<Carta>> pilhas;   // as 7 pilhas principais do jogo
    tela::Tela tela;                        // a tela onde são desenhadas as cartas
    Estado estado;                          // estado global do jogo
    int tecla;                              // última tecla apertada pelo usuario

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
};
