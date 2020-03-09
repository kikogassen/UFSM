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

#include <vector>

#include "gl_canvas2d.h"

#define ORIGEM_X 300
#define ORIGEM_Y 300
#define DIM_X 600
#define DIM_Y 600

float rotationX(float x, float y);
float rotationY(float x, float y);

struct Ponto{
   float x;
   float y;
   float raio;
   bool editing;
};

int scale(float x);
float blendingFunction(float t, int indice, bool scaled);
Ponto bSpline(int start, double t);
void testIfClickButton(int x, int y, int state);
float distanceBetween2Points(Ponto p1, Ponto p2);

Ponto p1 = {150, 150, 5, false};
Ponto p2 = {150, 450, 5, false};
Ponto p3 = {450, 450, 5, false};
Ponto p4 = {450, 150, 5, false};
Ponto p5 = {200, 150, 5, false};
std::vector<Ponto> vetorPontos {p1, p2, p3, p4, p5};

void render(){
   color(0, 0, 0);
   line(0, ORIGEM_Y, DIM_X, ORIGEM_Y);
   line(ORIGEM_X, 0, ORIGEM_X, DIM_Y);

   for (int i=1;i<vetorPontos.size();i++){
      line(vetorPontos[i-1].x, vetorPontos[i-1].y, vetorPontos[i].x, vetorPontos[i].y);
   }

   for (int i=0;i<vetorPontos.size();i++){
      circleFill(vetorPontos[i].x, vetorPontos[i].y, vetorPontos[i].raio, 30);
   }

   color(0, 0, 1);
   /*for (float t=0;t<=1;t+=0.001){
      point(scale(t), blendingFunctionBSpline(t, 0, true));
      point(scale(t), blendingFunctionBSpline(t, 1, true));
      point(scale(t), blendingFunctionBSpline(t, 2, true));
      point(scale(t), blendingFunctionBSpline(t, 3, true));
   }*/

   color(1, 0, 0);

   //bezier
   /*for (float t=0;t<=1;t+=0.001){
      float x = 0.0, y = 0.0;
      for (int i=0;i<vetorPontos.size();i++){
         x += vetorPontos[i].x * blendingFunctionBSpline(t, i, false);
         y += vetorPontos[i].y * blendingFunctionBSpline(t, i, false);
      }
      circleFill(x, y, 1, 10);
   }*/

   //b spline
   /*
   for (int i=0;i<vetorPontos.size();i++){
        for (float t=0;t<=1;t+=0.001){
            float x = 0.0, y = 0.0;
            for (int j=i-1;j<=i+2;j++){
                int id = j;
                if (id<0) id+=4;
                if (id>4) id-=4;
                x += vetorPontos[id].x * blendingFunctionBSpline(t, id, true);
                y += vetorPontos[id].y * blendingFunctionBSpline(t, id, true);
            }
            circleFill(x, y, 1, 10);
        }
   }
   */
   for (double t=0.0; t<vetorPontos.size();t+=0.01){
        int start = (int) t;
        Ponto p = bSpline(start, t-start);
        circleFill(p.x, p.y, p.raio, 10);
   }
   //Sleep(10000);
}

Ponto bSpline(int start, double t){
    int id0 = start-3;
    int id1 = start-2;
    int id2 = start-1;
    int id3 = start;

    if (id0<0) id0+=vetorPontos.size();
    if (id1<0) id1+=vetorPontos.size();
    if (id2<0) id2+=vetorPontos.size();
    if (id3<0) id3+=vetorPontos.size();

    //printf("%d %f: %d %d %d %d\n", start, t, id0, id1, id2, id3);
    Ponto p;
    p.x = (pow(1-t, 3)*vetorPontos[id0].x) + ((3*pow(t, 3) - 6*pow(t, 2) + 4)*vetorPontos[id1].x) + ((-3*pow(t, 3)+3*pow(t, 2)+3*t+1)*vetorPontos[id2].x) + (pow(t, 3)*vetorPontos[id3].x);
    p.x /= 6.0;
    p.y = (pow(1-t, 3)*vetorPontos[id0].y) + ((3*pow(t, 3) - 6*pow(t, 2) + 4)*vetorPontos[id1].y) + ((-3*pow(t, 3)+3*pow(t, 2)+3*t+1)*vetorPontos[id2].y) + (pow(t, 3)*vetorPontos[id3].y);
    p.y /= 6.0;
    p.raio = 2;
    return p;
}

float blendingFunction(float t, int indice, bool scaled){
   if (indice==0){
      return (scaled ? scale((1-t)*(1-t)*(1-t)) : ((1-t)*(1-t)*(1-t)));
   } else if (indice==1){
      return (scaled ? scale((3*t)*(1-t)*(1-t)) : ((3*t)*(1-t)*(1-t)));
   } else if (indice==2){
      return (scaled ? scale((3*t*t)*(1-t)) : ((3*t*t)*(1-t)));
   } else if (indice==3){
      return (scaled ? scale((t*t*t)) : ((t*t*t)));
   }
}

int scale(float x){
   return (int)(x*100+ORIGEM_X);
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key){

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key){

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y){
   //printf("\n%d %d %d %d %d %d", button, state, wheel, direction, x, y);
   //0 = down
   //1 = up
   y = DIM_Y-y;

   for (int i=0;i<vetorPontos.size();i++){
      if (vetorPontos[i].editing){
         vetorPontos[i].x = x;
         vetorPontos[i].y = y;
      }
   }

   if (button==0){
      testIfClickButton(x, y, state);
   }
}

void testIfClickButton(int x, int y, int state){
   for (int i=0;i<vetorPontos.size();i++){
      if (distanceBetween2Points(vetorPontos[i], {x, y, 5, false})<=vetorPontos[i].raio){
         if (state==0){
            vetorPontos[i].editing = true;
         } else if (state==1) {
            vetorPontos[i].editing = false;
         }
      }
   }
}

float distanceBetween2Points(Ponto p1, Ponto p2){
   return (float) sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y));
}

int main(void){
   initCanvas(DIM_X, DIM_Y, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3, 4 ou 5");

   runCanvas();
}
