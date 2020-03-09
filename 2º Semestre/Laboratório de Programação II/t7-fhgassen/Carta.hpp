/*
 * Carta.hpp
 * TAD que implementa o tipo de dados carta, que representa uma carta
 * de baralho.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015, 2017 João V. Lima, UFSM
 *               2005       Benhur Stein, UFSM
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

#include <iostream>
#include <string>

enum Naipe { COPAS = 1, OUROS = 2, PAUS = 3, ESPADAS = 4 };

enum Valor { AS = 1, VALETE = 11, DAMA = 12, REI = 13 };

struct Carta {
	Valor v;
	Naipe t;
	bool aberta;

  // inicia uma carta fechada
  void inicia(Valor _v, Naipe _t) {
    v = _v;
    t = _t;
    aberta = false;
  }

  Valor valor(void){
    return v;
  }

  Naipe naipe(void){
    return t;
  }

  void abre(void){
    aberta = true;
  }

  void fecha(void){
    aberta = false;
  }

  bool testa_aberta(void){
    return (aberta == true);
  }
};


