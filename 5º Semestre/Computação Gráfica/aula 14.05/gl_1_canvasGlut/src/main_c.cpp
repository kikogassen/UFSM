/*********************************************************************
// Canvas para desenho - Versao C.
//  Autor: Cesar Tadeu Pozzer
//         10/2007
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 5
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "gl_canvas2d.h"
#define DIM_TELA 600

void drawMatrix(){
  color(0, 0, 0);
  line(DIM_TELA/2, DIM_TELA, DIM_TELA/2, 0);
  line(DIM_TELA, DIM_TELA/2, 0, DIM_TELA/2);
}

void drawSin(){
  color(0, 0, 1);
  double angle;
  double fator = 10;
  for (angle = 0;angle<DIM_TELA;angle+=0.01){
    point((angle*fator)+DIM_TELA/2, (sin(angle)*10)+DIM_TELA/2);
  }
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render(){
  for (double u=0; u<8; u++){
    for (double x=0; x<8; x+=0.01){
      double y = cos(((2*x+1)*PI*u)/16.0);
      point(x*10+DIM_TELA/2, y*10+DIM_TELA/2);
    }
  }
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

   initCanvas(DIM_TELA, DIM_TELA, "Demo CanvasGlut. Pressione 1, 2, 3, 4, 5");

   runCanvas();

}
