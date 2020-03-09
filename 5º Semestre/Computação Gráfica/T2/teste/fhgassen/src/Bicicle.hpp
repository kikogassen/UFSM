/*********************************************************************
//  Esse arquivo é o cabeçalho da classe Bicicle.cpp
// *********************************************************************/

#pragma once

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
#include "Structs.hpp"
#include "Wheel.hpp"

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Bicicle {

private:

	// escala da bicicleta
    double bicicle_scale;

    // pontos da bicicleta. Não vejo como necessário explicar cada um, sua tradução já indica sua função
	Point seat;
	Point seat_coupler;
	Point handlebar;
	Point handlebar_coupler;
	Point crossbar_coupler;
	Point wheel_back_center;
	Point wheel_front_center;
	Point pedal_center;
	vector<Point> pedal_outside;
	Wheel* wheel_back;
	Wheel* wheel_front;

	// pontos do ciclista. Não vejo como necessário explicar cada um, sua tradução já indica sua função
	Point shoulder;
	Point head;
	Point left_elbow;
	Point right_elbow;
	Point right_knee;
	Point left_knee;

	// distância do joelho pra cintura e do joelho pro pé
	double leg_size;

	// desenha uma linha entre 2 pontos
	void draw_line(Point p1, Point p2);

	// rotaciona o pedal passado por parâmetro o ângulo de rad
	void rotate_pedal(float rad, Point center, Point& pedal);

	// calcula a nova coordenada do joelho após rotacionar o pedal
	void calculate_knee(Point& knee, Point pedal);

	// escala a distância passada por parâmetro
	double scale_value(int value);

public:
	// construtor da classe
	Bicicle(Point center_, double bicicle_scale_);

	// desenha a bicicleta
	void draw_bike();

	// movimenta a bicicleta, passando a velocidade como parâmetro
	void move_bike(double speed);
};
