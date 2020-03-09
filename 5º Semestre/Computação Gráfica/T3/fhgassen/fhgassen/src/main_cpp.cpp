/*
 *  Frederico Hansel dos Santos Gassen
 *  CG T3
 *
 *  Use as teclas WASD para mover a visualização do objeto
 *  M troca o modo de visualização
 *  Setas mudam o número de camadas e fatias
 *  Arraste os pontos de controle para mover a bezier
 *
 *  Foi implementado todos os requisitos básicos
 *
 */


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include "gl_canvas2d.h"
#include "Structs.hpp"
#include "Object.hpp"

using namespace std;

// dimensão da tela
#define DIM_X 1280
#define DIM_Y 640

//ponto origem da curva de bezier
#define SOURCE {100, 100, 0}

//ponto origem do desenho do objeto
#define SOURCE_OBJECT {DIM_X*3/4, 200, 0}

Point source = SOURCE;
Point source_object = SOURCE_OBJECT;

Object* object = nullptr;

//id do ponto de controle que está sendo arrastado pelo mouse
int editingId = -1;

//x final do eixo x
float end_source_x = DIM_X/2-20;

//y final do eixo y
float end_source_y = DIM_Y-20;

void drawBackground(); // função que desenha os traços de fundo do programa
bool exitedEditingArea(int x, int y); // função que verifica se o mouse saiu da área de edição
void clickButton(int x, int y, int state); // função que verifica o clique do botão esquerdo
bool clickInsideEditingArea(int x, int y); // função que verifica se clicou dentro da área de edição
void subtitle(); // função que mostra as legendas do trabalho

void render(){
    object->drawObject(); // desenha o objeto
    drawBackground(); // desenha o fundo
    object->drawBezierCurve(); // desenha a curva de bezier
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key){
    switch (key){
        case 119: //w
            object->angle_x+=0.1;
            break;
        case 97: //a
            object->angle_y+=0.1;
            break;
        case 115: //s
            object->angle_x-=0.1;
            break;
        case 100: //d
            object->angle_y-=0.1;
            break;
        case 109: //m
            if (object->projection==0){
                object->projection=1;
            } else {
                object->projection=0;
            }
            break;
        case 201: //up
            object->num_fatias++;
            break;
        case 203: //down
            if (object->num_fatias>3){
                object->num_fatias--;
            }
            break;
        case 200: //left
            if (object->num_camadas>3){
                object->num_camadas--;
            }
            break;
        case 202: //right
            object->num_camadas++;
            break;
        default:
            return;
    }

    //se muda o angulo de visualização do objeto, gira o mesmo
    object->calculate();
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key){

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y){
    y = DIM_Y-y;

    if (state==1) {
        editingId = -1;
    }

    if (editingId != -1){
        if (exitedEditingArea(x, y)){
            return;
        }

        //quando move um ponto de controle, recalcula os pontos do objeto
        object->setX(x-source.x, editingId);
        object->setY(y-source.y, editingId);
        object->calculate();
    }

    if (button==0){
        clickButton(x, y, state);
    }
}

bool exitedEditingArea(int x, int y){
    return !clickInsideEditingArea(x, y);
}

bool clickInsideEditingArea(int x, int y){
    if (x<source.x || x>end_source_x || y<source.y || y>end_source_y){
        return false;
    }
    return true;
}

void clickButton(int x, int y, int state){
    for (int i=0;i<object->getVectorBezierSize();i++){
        if (object->clickedInsidePoint(i, {x-source.x, y-source.y, 0})){
            if (state==0){
                editingId = i;
            }
        }
    }
}

void drawBackground(){
    color(1, 1, 1);
    rectFill(0, 0, DIM_X/2, DIM_Y);

    color(0, 0, 0);

    //axis
    line(0, source.y, end_source_x, source.y);
    line(source.x, 0, source.x, end_source_y);

    //arrow_y
    line(source.x, end_source_y, source.x-10, end_source_y-10);
    line(source.x, end_source_y, source.x+10, end_source_y-10);

    //arrow_x
    line(end_source_x, source.y, end_source_x-10, source.y-10);
    line(end_source_x, source.y, end_source_x-10, source.y+10);

    //divisória central
    rectFill(DIM_X/2-5, 0, DIM_X/2+5, DIM_Y);
}

void subtitle(){
    printf("\nWASD muda a visualizacao do objeto");
    printf("\nM troca o modo de visualizacao");
    printf("\nSetas mudam o numero de camadas e fatias");
    printf("\nArraste os pontos de controle para mover a bezier");
}

int main(void){
    initCanvas(DIM_X, DIM_Y, "CGT3 - Frederico H. dos S. Gassen");

    subtitle();

    //cria os pontos de controle
    Point p1 = {100, 200, 0};
    Point p2 = {100, 150, 0};
    Point p3 = {100, 100, 0};
    Point p4 = {100, 50, 0};
    vector<Point> vectorBezier {p1, p2, p3, p4};

    //instancia o objeto
    object = new Object(vectorBezier, source, source_object);

    //calcula os pontos do objeto
    object->calculate();

    runCanvas();
}
