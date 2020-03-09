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

#include <cmath>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

using namespace std;

#define ALT 500
#define LARG 500

double angle_inicial = 0;

void render(){
    color(0, 0, 0);
    double radius = 10;
    int num_voltas = 3;
    for (double i=angle_inicial;i<(PI_2*num_voltas)+angle_inicial;i+=0.01, radius+=0.1){
        point(LARG/2+(cos(i)*radius), ALT/2+(sin(i)*radius));
    }
    angle_inicial -= 0.1;
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
   initCanvas(ALT, LARG, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3, 4 ou 5");

   runCanvas();
}
