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
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#include "Jogo.hpp"
#include "Tela.hpp"
#include "geom.hpp"

using namespace tela;
using namespace geom;

#define LARG 610
#define ALT 400

Ponto p_monte = {5, 5};
Ponto descarte = {5, 105};
Ponto pilha0 = {70, 5};
Ponto as0 = {LARG-55, 5};
Tamanho t_carta = {50, 90};

void Jogo::inicia(void){
  ases.resize(4);    // 4 pilhas de ases
  pilhas.resize(7);  // 7 pilhas de cartas
  cursor = 0; // seta o cursor pra pilha de descartes
  cursor_origem = -1; // local origem pra movimentacao nao ta setado
  inicia_cartas();

  tela.inicia(LARG, ALT, "T7 Solitaire");
  estado = Estado::nada;
  // TODO completar
}

void Jogo::inicia_cartas(void){
	std::vector<Carta> tmp;
	for (auto nai=1;nai<=4;nai++){
		for (auto val=1;val<=13;val++){
			tmp.push_back({static_cast<Valor>(val), static_cast<Naipe>(nai), false});
		}
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle (tmp.begin(), tmp.end(), std::default_random_engine(seed));

	for (int x=0;x<24;x++){
		monte.push(tmp.back());
		tmp.pop_back();
	}

	for (int pilha=0;pilha<7;pilha++){
      //pilhas[pilha].resize(20);
		for (int car=0;car<=pilha;car++){
			pilhas[pilha].push_back(tmp.back());
			tmp.pop_back();
			if (car==pilha){// se eh a carta mais de cima
				pilhas[pilha][car].abre();
			}
		}
	}


}

void Jogo::finaliza(void) {
  // fecha a tela
  tela.finaliza();
}

void Jogo::desenha(){
  // TODO completar

  tela.limpa();


  desenha_fundo();
  desenha_cartas();
  desenha_cursor();


  tela.mostra();
  // espera 60 ms antes de atualizar a tela
  tela.espera(60);


}

void Jogo::atualiza(){
  // TODO completar
    // le ultima tecla
    tecla = tela.tecla();
    // tecla Q termina

    switch (tecla){
    	case ALLEGRO_KEY_Q:
    		estado = Estado::fim;
    		break;
    	case ALLEGRO_KEY_D:
    		funcao_descarte();
    		break;
    	case ALLEGRO_KEY_A:
    		//ases
    		funcao_ases();
    		break;
    	case ALLEGRO_KEY_RIGHT:
    		funcao_right();
    		break;
    	case ALLEGRO_KEY_LEFT:
    		funcao_left();
    		break;
    	case ALLEGRO_KEY_W:
    		funcao_movimentacao();
    		break;
    }
}

void Jogo::legenda(void){
  // TODO completar
  std::cout << "Pressione: " << std::endl;
  std::cout << " - 'q' sair" << std::endl;
  std::cout << " - 'd' virar uma carta do monte sobre o descarte. Caso esteja vazio, volta o descarte para o monte" << std::endl;
  std::cout << " - 'a' botar a carta que o cursor aponta pros ases" << std::endl;
  std::cout << " - 'w' seleciona pilha/descarte origem para mover ou seleciona pilha destino" << std::endl;
  std::cout << " - '->' move o cursor pra direita" << std::endl;
  std::cout << " - '<-' move o cursor pra esquerda" << std::endl;
}

bool Jogo::verifica_fim(void) {
  // TODO completar
  if (estado == Estado::nada)
    return false;
  else
    return true;
}

void Jogo::desenha_fundo(void){
  tela.cor({0.133, 0.543, 0.133});
  tela.retangulo({{0, 0}, {LARG, ALT}});

  tela.cor({0.195, 0.8, 0.195});
  tela.retangulo({{60, 0}, {LARG-120, ALT}});

  //ases
  for (int x=0;x<4;x++){
  	tela.cor({0.56, 0.73, 0.56});
  	tela.retangulo({{as0.x, as0.y+(100*x)}, t_carta});

  	tela.cor({1, 1, 1});
  	if (x==0){
  		tela.texto({as0.x+40, as0.y+(100*x)}, "C");
  	} else if (x==1){
  		tela.texto({as0.x+40, as0.y+(100*x)}, "O");
  	} else if (x==2){
  		tela.texto({as0.x+40, as0.y+(100*x)}, "P");
  	} else if (x==3){
  		tela.texto({as0.x+40, as0.y+(100*x)}, "E");
  	}
  }

  tela.cor({0.56, 0.73, 0.56});
  //pilhas
  for (int x=0;x<7;x++){
  	tela.retangulo({ponto_pilha(x, 0), t_carta});
  }

  //monte
  tela.retangulo({p_monte, t_carta});

  //descarte
  tela.retangulo({descarte, t_carta});
}

void Jogo::desenha_cartas(void){
	//desenha o monte
	if (!monte.empty()){
		desenha_uma_carta(monte.top(), p_monte);
	}
	//desenha o descarte
	if (!descartes.empty()){
		desenha_uma_carta(descartes.top(), descarte);
	}

	//desenha as 7 pilhas
	for (int x=0;x<7;x++){
		for (int y=0;y<pilhas[x].size();y++){
			desenha_uma_carta(pilhas[x][y], ponto_pilha(x, y));
		}
	}

	//desenha os 4 ases
	for (int x=0;x<4;x++){
		if (!ases[x].empty()){
			desenha_uma_carta(ases[x].top(), {as0.x, as0.y+(100*x)});
		}
	}
}
//♥♦♣♠
void Jogo::desenha_uma_carta(Carta c, Ponto p){
	//borda
	tela.cor({0, 0, 1});
	tela.retangulo({p, t_carta});

	//preenchimento

	Tamanho t_preench = {48, 88};
	if (c.testa_aberta()){
		tela.cor({1, 1, 1});
		tela.retangulo({{p.x+1, p.y+1}, t_preench});

		tela.cor({0, 0, 0});
		//desenha o naipe da carta
		switch (c.naipe()){
			case PAUS://♥♦♣♠
				tela.texto({p.x+40, p.y+1}, "P");
				break;
			case ESPADAS:
				tela.texto({p.x+40, p.y+1}, "E");
				break;
			case OUROS:
				tela.cor({1, 0, 0});
				tela.texto({p.x+40, p.y+1}, "O");
				break;
			case COPAS:
				tela.cor({1, 0, 0});
				tela.texto({p.x+40, p.y+1}, "C");
				break;
		}

		//desenha o numero da carta
		switch (c.valor()){
			case AS:
				tela.texto({p.x+1, p.y+1}, "1");
				break;
			case VALETE:
				tela.texto({p.x+1, p.y+1}, "11");
				break;
			case DAMA:
				tela.texto({p.x+1, p.y+1}, "12");
				break;
			case REI:
				tela.texto({p.x+1, p.y+1}, "13");
				break;
			default:
				if (c.valor()==10){
					tela.texto({p.x+1, p.y+1}, "10");
				} else {
					char num[2];
					num[1]='\0';
					num[0]=c.valor()+'0';
					tela.texto({p.x+1, p.y+1}, num);
				}
				break;
		}

	} else {
		tela.cor({0.12, 0.56, 1});
		tela.retangulo({{p.x+1, p.y+1}, t_preench});
	}
}

Ponto Jogo::ponto_pilha(int pilha, int carta){
	Ponto p = {pilha0.x+(70*pilha), pilha0.y + (20*carta)};
	return p;
}

void Jogo::desenha_cursor(void){
	//desenha o cursor normal
	tela.cor({0, 0, 1});
	switch (cursor){
		case 0:
			desenha_uma_flecha({descarte.x+25, ALT-50});
			break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			desenha_uma_flecha({(pilha0.x+25)+(cursor-1)*70, ALT-50});
			break;
	}

	//desenha o cursor selecionado
	tela.cor({1, 0, 1});
	switch (cursor_origem){
		case 0:
			desenha_uma_flecha({descarte.x+25, ALT-50});
			break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			desenha_uma_flecha({(pilha0.x+25)+(cursor_origem-1)*70, ALT-50});
			break;
	}
}

void Jogo::desenha_uma_flecha(Ponto p){

	tela.linha(p, {p.x, p.y+20});
	tela.linha({p.x+1, p.y}, {p.x+1, p.y+20});

	tela.linha(p, {p.x-5, p.y+5});
	tela.linha({p.x, p.y-1}, {p.x-5, p.y+4});

	tela.linha(p, {p.x+5, p.y+5});
	tela.linha({p.x, p.y-1}, {p.x+5, p.y+4});
}

Carta Jogo::ultima_carta_cursor(void){
	Carta retorno = {static_cast<Valor>(0), static_cast<Naipe>(PAUS), false};
	switch (cursor){
		case 0:
			if (!descartes.empty()){
				retorno = descartes.top();
			}
			break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			if (pilhas[cursor-1].size()>0){
				retorno = pilhas[cursor-1][pilhas[cursor-1].size()-1];
			}
			break;
	}
	return retorno;
}

void Jogo::bota_carta_cursor_as(int pilha_as){
	switch (cursor){
		case 0:
			ases[pilha_as].push(descartes.top());
			descartes.pop();
			break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			ases[pilha_as].push(pilhas[cursor-1][pilhas[cursor-1].size()-1]);
			pilhas[cursor-1].pop_back();
			pilhas[cursor-1][pilhas[cursor-1].size()-1].abre();
			break;
	}
}

void Jogo::funcao_descarte(void){
	if (monte.empty()){
  	while (!descartes.empty()){
  		descartes.top().fecha();
  		monte.push(descartes.top());
  		descartes.pop();
  	}
  } else {
  	monte.top().abre();
  	descartes.push(monte.top());
  	monte.pop();
  }
}

void Jogo::funcao_ases(void){
	Carta carta_selec;
  carta_selec = ultima_carta_cursor();
  if (carta_selec.valor()!=0){
  	switch (carta_selec.naipe()){
	 		case COPAS:
	 			if (carta_selec.valor()==ases[0].size()+1){
	 				bota_carta_cursor_as(0);
	 			}
				break;
	 		case OUROS:
	 			if (carta_selec.valor()==ases[1].size()+1){
	  			bota_carta_cursor_as(1);
	  		}
	  		break;
	  	case PAUS:
	  		if (carta_selec.valor()==ases[2].size()+1){
	  			bota_carta_cursor_as(2);
	  		}
	  		break;
	  	case ESPADAS:
	  		if (carta_selec.valor()==ases[3].size()+1){
	  			bota_carta_cursor_as(3);
	  		}
	  		break;
	  }
  }
}

void Jogo::funcao_right(void){
	if (cursor<7){
  	cursor++;
  }
}

void Jogo::funcao_left(void){
	if (cursor_origem==-1){
    if (cursor>0){
    	cursor--;
    }
  } else {
  	if (cursor>1){
  		cursor--;
  	}
  }
}

void Jogo::funcao_movimentacao(void){
	if (cursor_origem==-1){ // nao tem pilha selecionada
    if (cursor==0 && descartes.empty()){

    } else {
      cursor_origem = cursor;
    }
  } else { // ja tem pilha selecionada
  	//tira todas as cartas da pilha selecionada
  	std::vector<Carta> tmp;
  	if (cursor_origem==0 && !descartes.empty()){
  		tmp.push_back(descartes.top());
  		descartes.pop();
  	} else if (cursor_origem>0 && pilhas[cursor_origem-1].size()>0) {
  		while (pilhas[cursor_origem-1].size()>0 && pilhas[cursor_origem-1][pilhas[cursor_origem-1].size()-1].testa_aberta()){
  			tmp.push_back(pilhas[cursor_origem-1][pilhas[cursor_origem-1].size()-1]);
  			pilhas[cursor_origem-1].pop_back();
  		}
  	}
  	//testa se é valida
  	Carta topo_cursor;
  	topo_cursor = ultima_carta_cursor();
  	if (topo_cursor.valor()!=0){ // se n ta vazio a pilha que eu tentei botar
			if (tmp.back().valor()+1==topo_cursor.valor() && tmp.back().naipe()!=topo_cursor.naipe()){ // se da pra botar no lugar
				while (tmp.size()>0){
					pilhas[cursor-1].push_back(tmp[tmp.size()-1]);// ERROOOOOOOOOOOOOOOOO
					tmp.pop_back();
				}
				if (cursor_origem!=0){
	  			pilhas[cursor_origem-1][pilhas[cursor_origem-1].size()-1].abre();
	  		}
	  	} else { // se n da, esvazia de volta
	  		if (cursor_origem==0){
	  			descartes.push(tmp.back());
	  			tmp.pop_back();
	  		} else {
	  			while (!tmp.empty()){
						pilhas[cursor_origem-1].push_back(tmp.back());
						tmp.pop_back();
					}
	  		}
	  	}
    } else { // se ta vazio a pilha que eu to tentando colocar
    	while (!tmp.empty()){
	  		pilhas[cursor-1].push_back(tmp[tmp.size()-1]); // ERROOOOOOOOOOOO
	  		tmp.pop_back();
	  	}
	  	if (cursor_origem!=0 && pilhas[cursor_origem-1].size()>0){
	  		pilhas[cursor_origem-1][pilhas[cursor_origem-1].size()-1].abre();
	  	}
    }
    cursor_origem=-1;
  }
}