/*********************************************************************
// Canvas para desenho - Versao CPP.
//  Autor: Cesar Tadeu Pozzer
//         10/2007
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Instruções:
//    Para compilar em C, basta comentar o comando #define _CPP_
//	  Para alterar a animacao, digite numeros entre 1 e 7
// *********************************************************************/

/*
  Autor: Cesar Tadeu Pozzer
         04/2013

  Instruções:
	  Para alterar a animacao, digite numeros entre 1 e 7
*/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "Bola.h"
#include "Relogio.h"

#define ORIGEM_X 300
#define ORIGEM_Y 300
#define DIM_X 600
#define DIM_Y 600

float rotationX(float x, float y);
float rotationY(float x, float y);

struct Ponto{
   float x;
   float y;
};

struct Rectangol{
   Ponto p1;
   Ponto p2;
};

Rectangol r1 = {{20, 20}, {40, 40}};
Rectangol r2 = {{-10, -10}, {10, 10}};

float angle = 0.0;

void render(){
   color(0, 0, 0);
   angle += 0.1;
   r1.p1.x = rotationX(r1.p1.x, r1.p2.y);
   r1.p1.y = rotationY(r1.p1.x, r1.p2.y);
   r1.p2.x = rotationX(r2.p1.x, r2.p2.y);
   r1.p2.y = rotationY(r2.p1.x, r2.p2.y);
   line(0, ORIGEM_Y, DIM_X, ORIGEM_Y);
   line(ORIGEM_X, 0, ORIGEM_X, DIM_Y);
   rect(r1.p1.x+ORIGEM_X, r1.p1.y+ORIGEM_Y, r1.p2.x+ORIGEM_X, r1.p2.y+ORIGEM_Y);
   rect(r2.p1.x+ORIGEM_X, r2.p1.y+ORIGEM_Y, r2.p2.x+ORIGEM_X, r2.p2.y+ORIGEM_Y);

   Sleep(500);
}

float rotationX(float x, float y){
   return x*cos(angle) - y*sin(angle);
}

float rotationY(float x, float y){
   return x*sin(angle) + y*cos(angle);
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key){

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key){

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y){

}

int main(void){
   initCanvas(DIM_X, DIM_Y, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3, 4 ou 5");

   runCanvas();
}
