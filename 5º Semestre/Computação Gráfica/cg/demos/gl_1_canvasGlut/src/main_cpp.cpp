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

Bola    *b = NULL;
Relogio *r = NULL;

//variaveis globais
int   opcao  = 50;
float global = 0;

//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
//#pragma comment(lib, "glut32.lib")


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
//   renderCubo();
//   renderSphere();
   for(float i=0; i<250; i++)
   {
	   color(i/200, i/200, i/200);
	   point((int)(i+100), (int)(200));
   }

   text(20,500,"Programa Demo Canvas C++.");

   if( opcao == 49 ) // = '1' relogio
   {
      r->anima();
   }
   if( opcao == '2' ) // = 50 bola
   {
      b->anima();
   }
   if( opcao == 51) // = '3' linha animada
   {
      clear(1,1,1); //limpa a tela de branco
      color(0.7, 0.7, 0);
      line((int)global, 100, (int)global, 400);
      global += 0.1;
   }
   if( opcao == 52 ) // = '4' relogio
   {
      int x = (int)(cos(global) * 60);
      int y = (int)(sin(global) * 60);
      clear(1,  1,  1);
      color(1,0,1);
      circle(80, 80, 70, 19);
      line(80, 80, x + 80, y + 80);
      global -= 0.001;
   }
   if( opcao == 53 ) // = '5' linha andando
   {
      clear(0,0,0);
      color(1, 1, 0);
      rect(200-(int)global, 200-(int)global, 200+(int)global, 200 + (int)global);
      global += 0.05;
   }
   if( opcao == 54) //= '6' quadrados parados
   {
        clear(0,0,0);
        color(0.7, 0.7, 0);
        circleFill(20,20, 10, 4);
        //rectFill(40,40,140,140);
        rect(140,140,240,240);
        color(0, 1, 0);
        point(300, 300);
   }
   if( opcao == 55 ) // = '7' senoide
   {
       //line( 10,10, 300,300 );
       //circle( 300,300, 100, 1150);
       float x=0, y;
       color(0, 1, 0);
       for(float i=0; i < 68; i+=0.001)
       {
          y = sin(i)*50;
          point((int)x, y+100);
          x+=0.01;
       }
       //rectFill( 20,20,230,130 );
   }
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      opcao = key;
   }

   switch(key)
   {
      case 27:
	     exit(0);
	  break;

	  //seta para a esquerda
      case 200:
         b->move(-10);
	  break;

	  //seta para a direita
	  case 202:
         b->move(10);
	  break;
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
}

int main(void)
{
   initCanvas(500,500, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3, 4 ou 5");

   b = new Bola();
   r = new Relogio();

   runCanvas();
}
