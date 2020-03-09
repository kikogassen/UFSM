/*********************************************************************
// Trabalho 2 da disciplina de Computação Gráfica
//  Autor: Frederico Hansel dos Santos Gassen
//         14/05/2019
//
//  Esse arquivo é a main executável do trabalho 2
// *********************************************************************/


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <cmath>
#include <iostream>
#include <string>

#include "gl_canvas2d.h"

#include "Bicicle.hpp"
#include "Structs.hpp"

using namespace std;

// largura da tela
#define DIM_X 1280

// altura da tela
#define DIM_Y 640

// velocidade de rotação (é negativa pois é pra direita)
#define ROTATION_SPEED -0.05

// escala da bicicleta, quanto maior, maior ela será
#define BICICLE_SCALE 3

// inicializa uma bicicleta no meio da tela
Bicicle* bike = new Bicicle({DIM_X/2, DIM_Y/2}, BICICLE_SCALE);

void render(){
	// desenha a bicicleta
	bike->draw_bike();

	// movimenta a bicicleta
	bike->move_bike(ROTATION_SPEED);
}

void keyboard(int key){
	// se clicar ESC, sai do programa
	if (key==27){
		exit(0);
	}
}

void keyboardUp(int key){

}

void mouse(int button, int state, int wheel, int direction, int x, int y){

}

int main(void){

	initCanvas(DIM_X, DIM_Y, "Trabalho 2 - Frederico H. dos S. Gassen");

	runCanvas();
}
