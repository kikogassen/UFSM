/*********************************************************************
//  Esse arquivo é o cabeçalho da classe Wheel.cpp
// *********************************************************************/

#pragma once

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "Structs.hpp"

#include <vector>
#include <cmath>
#include <iostream>

// raio do pneu
#define WHEEL_RADIUS 50

// número de aros em cada pneu
#define NUMBER_OF_HOOPS 8

using namespace std;

class Wheel {

private:

	// centro do pneu
	Point center;

	// array de aros
	vector<Line> hoops;

	// escala da bicicleta
	double bicicle_scale;

	// função que rotaciona cada um dos aros
	void rotate_hoop(float rad, Line& hoop);

	// função que inicializa os aros
	void instantiate_hoops();

	// escala a distância passada por parâmetro
	double scale_value(int value);

public:

	// construtor da classe
	Wheel(Point center_, double bicicle_scale_);

	// rotaciona o pneu recebendo uma velocidade
	void rotate_wheel(double speed);

	// desenha o pneu
	void draw_wheel();
};
