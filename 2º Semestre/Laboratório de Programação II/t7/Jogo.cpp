/*
 * Jogo.cpp
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

#include <iostream>

#include "Jogo.hpp"
#include "Tela.hpp"
#include "geom.hpp"

using namespace tela;
using namespace geom;


void Jogo::inicia(void){
  ases.resize(4);    // 4 pilhas de ases 
  pilhas.resize(7);  // 7 pilhas de cartas

  tela.inicia(600, 400, "T7 Solitaire");
  // TODO completar 
}

void Jogo::finaliza(void) {
  // fecha a tela
  tela.finaliza();
}

void Jogo::desenha(){
  // TODO completar 
}

void Jogo::atualiza(){
  // TODO completar 
    // le ultima tecla
    tecla = tela.tecla();
    // tecla Q termina
    if (tecla != ALLEGRO_KEY_Q) {
      // faz o resto
      tela.limpa();
      tela.mostra();
      // espera 60 ms antes de atualizar a tela
      tela.espera(60);
    } else {
      // troca estado do jogo para terminado
      estado = Estado::fim;
    }
}

void Jogo::legenda(void){
  // TODO completar 
  std::cout << "Pressione: " << std::endl;
  std::cout << " - 'q' sair" << std::endl;
}

bool Jogo::verifica_fim(void) {
  // TODO completar 
  if (estado == Estado::nada)
    return false;
  else
    return true;
}

