/*
 *
 *
 *  Cabeçalho da classe Object, responsável pelas informações do objeto gerado a partir da curva de bezier
 *
 *
 */



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

#define BEZIER_POINT_RADIUS 7 // tamanho raio de desenho do ponto da curva de bezier

using namespace std;

class Object {

private:
    Point source_object; // origem do sistema de coordenadas do desenho do objeto
    Point source; // origem do sistema de coordenadas do desenho da bezier
	vector<Point> vectorBezier; // vetor com os 4 pontos da bezier
	vector<vector<Point>> matrixPoints; // matriz de pontos do objeto
	vector<vector<Point>> matrixTransformed; // matriz de pontos do objeto transformado para visualização

	void printaMatrix(); // função de debug pra printar a matriz do objeto
	Point project(Point p); // função que calcula a projeção de um ponto
	void calculateBezierPoints(); // função que calcula os pontos da curva de bezier para depois rotacionar em torno do eixo y
	void calculateObjectPoints(); // função que calcula os pontos ao rotacionar no eixo y
    void calculateProjectedObject(); // função que calcula os pontos para projetar o objeto
    Point translade(Point p); // função que translada um ponto
    Point rotate_x(Point p); // função que rotaciona um ponto em torno do eixo x
    Point rotate_y(Point p); // função que rotaciona um ponto em torno do eixo y

public:
	float angle_x; // angulo atual de rotação no eixo x do objeto projetado
	float angle_y; // angulo atual de rotação no eixo y do objeto projetado
	int projection = 0; //0 = perspectiva, 1 = ortográfica
	int num_camadas = 20; // numero de camadas verticais do objeto gerado
	int num_fatias = 63; // numero de camadas horizontais do objeto gerado

	Object(vector<Point> vectorBezier_, Point source_, Point source_object_); // construtor
    void calculate(); // função que calcula os pontos do objeto
	bool clickedInsidePoint(int id, Point mouse); // função que verifica se eu cliquei num ponto de controle
	void drawPoints(); // função que desenha os pontos da curva de bezier
	void drawObject(); // função que desenha o objeto na metade direita da tela
	float blendingFunction(float t, int id); // função que calcula a blending de um valor
	void drawBezierCurve(); // função que desenha a curva de bezier
	float distance(Point p1, Point p2);  //função que retorna a distancia entre dois pontos
	int getVectorBezierSize(); //função que retorna o tamanho do vetor de bezier
	void setX(float x, int id); // função que seta x no ponto de controle[id] da bezier
	void setY(float y, int id);// função que seta y no ponto de controle[id] da bezier

};
